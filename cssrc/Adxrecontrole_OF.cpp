// ===============================================================================================================
//		Project: Sage Enterprise Management Weighing Module
//		Program: Adxrecontrole_OF.cpp
//	Description: This program handles the processing needed to verify the Product/Lot/Sublot info 
//				 (Re-check/Recontrole).
// ===============================================================================================================
//
//	DLL			Date Last		
//	Version		Modified		By						Change#		Description
//	=======		==========		====================	========	==============================================
//  6.4.2.2     04/25/2018      Neil/John               X3-70592	Invalid data was not returning to the same field
//	6.4.2.1		03/29/2018		John Bromley			X3-84572	Honor starting position in barcode setup
//	6.4.2.0		02/02/2015		MM									Original development of program

// ===============================================================================================================
#include "stdafx.h"
#include "AdxRecontrole_OF.h"

#include "AdxInterface.h"
#include "AdxClavier_tactile.h"
#include "AdxPesee_OF.h"
#include "AdxMessage.h"
#include "AdxData.h"
#include "AdxComposant.h"	// 03.10 mm - modification du recontrole OF
#include "AdxLot.h"			// 03.10 mm - modification du recontrole OF
#include "AdxBalance.h"		// APCPRD-2636 mm 08.2013
#include "AdxWeighingInterface.h"	// 01.2015 mm 13422 - découpage CAB
// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------

//---------------------------------------------------------------------------
void AdxRecontrole_OF::SaisiContenuCabCB(IlvGraphic* g)
{
	// 103422 mm 01.2015
	// découpage du CAB selon les règles passées en paramètres
	// Cutting of the BARCODE according to the rules passed in parameters

	AdxData* m_data = getInterface()->getDonnees()	;

	if ( m_data->getTypeCAB() ==1)	// caratère séparateur entre les champs à récupérer  Character seperator
	{
		char* _separateurArt = NULL;
		char* _separateurLot = NULL;
		char* _separateurSlo = NULL;
		switch (m_data->getRecontroleArticleCode())
		{
			case 2 :	// lot
					_separateurLot = m_data->getSeparateurLot();
					alimentationZones(_separateurLot,"","");
					break;
			case 3 :	// article + lot 
						_separateurArt = m_data->getSeparateurArt();
						_separateurLot = m_data->getSeparateurLot();
						if (m_data->getNumZoneArt()< m_data->getNumZoneLot())  //article avant lot
							alimentationZones( _separateurArt,_separateurLot,"");		
						else		 // lot avant article 	
							alimentationZones(_separateurLot,_separateurArt,"");		
						break;
			case 4 :	// lot + slo
						_separateurLot = m_data->getSeparateurLot();
						_separateurSlo = m_data->getSeparateurSlo();
						if (m_data->getNumZoneLot()< m_data->getNumZoneSlo())  // lot avant slo	
							alimentationZones(_separateurLot,_separateurSlo,"");	
						else
							alimentationZones(_separateurSlo,_separateurLot,"");
						break;
			
			case 5 :	// article + lot + slo
						_separateurArt = m_data->getSeparateurArt();
						_separateurLot = m_data->getSeparateurLot();
						_separateurSlo = m_data->getSeparateurSlo();
						
						if  ((m_data->getNumZoneArt()< m_data->getNumZoneLot()) 
						&&	(m_data->getNumZoneLot()< m_data->getNumZoneSlo())) // article avant lot et lot avant slo	
							// art/lot/slo
							alimentationZones(_separateurArt,_separateurLot,_separateurSlo);	
						else if ((m_data->getNumZoneLot()< m_data->getNumZoneSlo())	   
						&&		( m_data->getNumZoneSlo() < m_data->getNumZoneArt())) // lot avant slo et slo avant article
							// lot/slo/art
							alimentationZones(_separateurLot,_separateurSlo,_separateurArt);
						else if ((m_data->getNumZoneSlo()< m_data->getNumZoneLot()) 
						&&		(m_data->getNumZoneLot()< m_data->getNumZoneArt())) //slo avant lot et lot avant article
							// slo/lot/art
							alimentationZones(_separateurSlo,_separateurLot,_separateurArt);
						else if ((m_data->getNumZoneLot()< m_data->getNumZoneArt())		
						&&	 (m_data->getNumZoneArt()< m_data->getNumZoneSlo()))	 //lot avant article et article avant slo		
							// lot/art/slo
							alimentationZones(_separateurLot,_separateurArt,_separateurSlo);
						break;
			default:	break;
		}
	}
	else if ( m_data->getTypeCAB() ==2) // longueur fixe -- Fixed length
	{

		switch (m_data->getRecontroleArticleCode())
		{
			case 2 :	// lot
						alimentationZonesLF(m_data->getLongueurLot2(),0 ,0);
						break;
			case 3 :	// article + lot 
						if (m_data->getDebutArt() < m_data->getDebutLot())	//article avant lot
							alimentationZonesLF(m_data->getLongueurArt(), m_data->getLongueurLot2(), 0);
						else
							alimentationZonesLF( m_data->getLongueurLot2(),m_data->getLongueurArt(),0);
						break;
			case 4 :	// lot + slo
						if (m_data->getDebutLot() < m_data->getDebutSlo())	//lot avant slo
							alimentationZonesLF( m_data->getLongueurLot2(), m_data->getLongueurSlo(), 0);
						else
							alimentationZonesLF( m_data->getLongueurSlo(),m_data->getLongueurLot2(),0);
						break;
			case 5 :	// article + lot + slo
						if ((m_data->getDebutArt() < m_data->getDebutLot()) 
						&&	(m_data->getDebutLot() < m_data->getDebutSlo()))// article avant lot et lot avant slo	
							// art/lot/slo
							alimentationZonesLF(m_data->getLongueurArt(), m_data->getLongueurLot2(),m_data->getLongueurSlo());
						else if ((m_data->getDebutLot() < m_data->getDebutSlo())
						&& (m_data->getDebutSlo() < m_data->getDebutArt()))
							// lot/slo/art
							alimentationZonesLF(m_data->getLongueurLot2(), m_data->getLongueurSlo(),m_data->getLongueurArt());
						else if ((m_data->getDebutSlo() < m_data->getDebutLot())
						&& (m_data->getDebutLot() < m_data->getDebutArt()))
							// slo/lot/art
							alimentationZonesLF(m_data->getLongueurSlo(), m_data->getLongueurLot2(),m_data->getLongueurArt());
						else if ((m_data->getDebutLot() < m_data->getDebutArt())
						&&	(m_data->getDebutArt() < m_data->getDebutSlo()))
							// lot/art/slo
							alimentationZonesLF(m_data->getLongueurLot2(), m_data->getLongueurArt(),m_data->getLongueurSlo());
						break;
			default:	break;

		}
	}	
	controleValiditeZones();
}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::controleValiditeZones()
{
	AdxData* m_data = getInterface()->getDonnees();
	AdxInterface* m_interface = getInterface();
	// contrôle de validité des zones
	// validate the fields
	_composantOK = false;
	_lotOK = false ;
	_souslotOK = false ;	


	// envoyer un message : le re-contrôle a échoué
	// Send a message that the re-check failed
	char* message = new char[80];
	switch (m_data->getRecontroleArticleCode())
	{
		case 2 :	// lot
					// 12607 mm 11.2015 
					_composantOK = true;
					_souslotOK = true ;
					if (strcmp(m_data->getCurrentLot()->getLot(), getSaisieLot()->getLabel()) == 0)
						_lotOK = true ;
					if ( _lotOK)
					{
						setFocus(getSaisieLot());	
						break;		
					}
					if (!_lotOK)
						validiteLotKo(&message);
					getInterface()->getMessage()->setPanneauAppelant(this);
					getInterface()->envoieMessage(message, false);
					getSaisieLot()->setLabel("");
					bufferedDraw(getSaisieLot());
					reinitialiseEcran();
					break;
		case 3 :   // article + lot 
				   // product + lot
				   // 12607 mm 11.2015 
					_souslotOK = true ;
					if (strcmp(m_data->getCurrentComposant()->getComposant(), getSaisieComposant()->getLabel()) == 0)
						_composantOK = true ;	
					if (strcmp(m_data->getCurrentLot()->getLot(), getSaisieLot()->getLabel()) == 0)
						_lotOK = true ;
					if (_composantOK && _lotOK )
					{
						// 108093 mm 06.2015 - put the focus on the last graspable field
						setFocus(getSaisieLot());
						break;
					}
					
					if ( (!_composantOK) && ( !_lotOK))
						validiteComposantLotKO(&message);
					else if ( !_composantOK)
						validiteComposantKo(&message);
					else if ( !_lotOK)
						validiteLotKo(&message);	
					getInterface()->getMessage()->setPanneauAppelant(this);
					getInterface()->envoieMessage(message, false);
					getSaisieComposant()->setLabel("");
					getSaisieLot()->setLabel("");
					bufferedDraw(getSaisieComposant());
					bufferedDraw(getSaisieLot());
					reinitialiseEcran();
					break;
		case 4 :	// lot + sub-lot
					// 12607 mm 11.2015 
					_composantOK = true;
					if (strcmp(m_data->getCurrentLot()->getLot(), getSaisieLot()->getLabel()) == 0)
						_lotOK = true ;
					if (strcmp(m_data->getCurrentLot()->getSlo(), getSaisieSousLot()->getLabel()) == 0)
						_souslotOK = true ;
					if (_lotOK && _souslotOK)
					{
						// 108093 mm 06.2015 - put the focus on the last graspable field
						setFocus(getSaisieSousLot()) ;
						break;
					}

					if ( (!_lotOK) && ( !_souslotOK))
						validiteLotSloKo(&message);
					else if ( !_lotOK)
						validiteLotKo(&message);
					else if ( !_souslotOK)
						validiteSloKo(&message);
					getInterface()->getMessage()->setPanneauAppelant(this);
					getInterface()->envoieMessage(message, false);
					getSaisieLot()->setLabel("");
					getSaisieSousLot()->setLabel("");
					bufferedDraw(getSaisieLot());
					bufferedDraw(getSaisieSousLot());
					reinitialiseEcran();
					break;
		case 5 :	// article + lot + slo
					// product + lot + sub-lot
					if (strcmp(m_data->getCurrentComposant()->getComposant(), getSaisieComposant()->getLabel()) == 0)
						_composantOK = true ;	
					if (strcmp(m_data->getCurrentLot()->getLot(), getSaisieLot()->getLabel()) == 0)
						_lotOK = true ;
					if (strcmp(m_data->getCurrentLot()->getSlo(), getSaisieSousLot()->getLabel()) == 0)
						_souslotOK = true ;
					if ( _composantOK && _lotOK && _souslotOK)
					{
						// 108093 mm 06.2015 - put the focus on the last graspable field
						setFocus(getSaisieSousLot()) ;
						break;
					}

					if ( (!_composantOK) && ( !_lotOK)&& ( !_souslotOK))
						validiteComposantLotSloKO(&message);
					else if ( (!_composantOK) && ( !_lotOK))
						validiteComposantLotKO(&message);
					else if ( (!_lotOK) && ( !_souslotOK))
						validiteLotSloKo(&message);
					else if ( (!_composantOK) && ( !_souslotOK))
						validiteComposantSloKo(&message);
					else if ( !_composantOK)
						validiteComposantKo(&message);
					else if ( !_lotOK)
						validiteLotKo(&message);
					else if ( !_souslotOK)
						validiteSloKo(&message);
					getInterface()->getMessage()->setPanneauAppelant(this);
					getInterface()->envoieMessage(message, false);
					getSaisieComposant()->setLabel("");
					getSaisieLot()->setLabel("");
					getSaisieSousLot()->setLabel("");
					bufferedDraw(getSaisieComposant());
					bufferedDraw(getSaisieLot());
					bufferedDraw(getSaisieSousLot());
					reinitialiseEcran();
					break;
	}
	delete [] message;	
}
//---------------------------------------------------------------------------
void AdxRecontrole_OF::reinitialiseEcran()
{
	getSaisiContenuCab()->setLabel("");
	bufferedDraw(getSaisiContenuCab());
	setFocus(getSaisiContenuCab());
}
//---------------------------------------------------------------------------
void AdxRecontrole_OF::validiteComposantKo(char** message)
{
	sprintf(*(message),"%s : %s ", IlvGetMessage(getInterface()->getDisplay(),
		"&EchecRecontrôle"),
		IlvGetMessage(getInterface()->getDisplay(),
		"&ComposantIncorrect"));
}
//---------------------------------------------------------------------------
void AdxRecontrole_OF::validiteLotKo(char** message)
{
	sprintf(*(message),"%s : %s ", IlvGetMessage(getInterface()->getDisplay(),
		"&EchecRecontrôle"),
		IlvGetMessage(getInterface()->getDisplay(),
		"&LotIncorrect"));
}
//---------------------------------------------------------------------------
void AdxRecontrole_OF::validiteSloKo(char** message)
{
	sprintf(*(message),"%s : %s ", IlvGetMessage(getInterface()->getDisplay(),
		"&EchecRecontrôle"),
		IlvGetMessage(getInterface()->getDisplay(),
		"&SloIncorrect"));
}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::validiteComposantLotKO(char** message)
{
	sprintf(*(message),"%s : %s ", IlvGetMessage(getInterface()->getDisplay(),
		"&EchecRecontrôle"),
		IlvGetMessage(getInterface()->getDisplay(),
		"&ComposantLotIncorrects"));
}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::validiteLotSloKo(char** message)
{
	sprintf(*(message),"%s : %s ", IlvGetMessage(getInterface()->getDisplay(),
		"&EchecRecontrôle"),
		IlvGetMessage(getInterface()->getDisplay(),
		"&LotSloIncorrects"));
}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::validiteComposantSloKo(char** message)
{
	sprintf(*(message),"%s : %s ", IlvGetMessage(getInterface()->getDisplay(),
		"&EchecRecontrôle"),
		IlvGetMessage(getInterface()->getDisplay(),
		"&ComposantSloIncorrects"));
}
//---------------------------------------------------------------------------
void AdxRecontrole_OF::validiteComposantLotSloKO(char** message)
{
	sprintf(*(message),"%s : %s ", IlvGetMessage(getInterface()->getDisplay(),
		"&EchecRecontrôle"),
		IlvGetMessage(getInterface()->getDisplay(),
		"&ComposantLotSloIncorrects"));
}
//---------------------------------------------------------------------------
void AdxRecontrole_OF::alimentationZones(char *sep1 , char *sep2, char *sep3)
{
	AdxData* m_data = getInterface()->getDonnees()	;
	const char* _cab;
	const char* _composant = NULL;
	const char* _composant2 = NULL;
	const char* _composant3 = NULL;
	char* _zone1 = NULL ;
	char* _zone2 = NULL ;
	char* _zone3 = NULL ;
	char* _tmp = NULL ;


	_cab = getSaisiContenuCab()->getLabel();
	int lng = strlen(getSaisiContenuCab()->getLabel());

	// zone1
	_zone1  = new char[lng+1]; 
	_composant = strchr(_cab,sep1[0]);
	if (_composant )
	{
		strncpy(_zone1,_cab,(lng -strlen(_composant)));
		_zone1[lng -strlen(_composant)] ='\0';
	}
	else
	{
		delete[] _zone1;
		separateurNonTrouve();
		return;
	}

	if (sep2!="")
	{	
		// zone2
		_composant = _composant+1;	// élimination du sep1
		_zone2 = new char [strlen(_composant)+1];
		_composant2 = strchr(_composant,sep2[0]);
		if (_composant2 )
		{
			strncpy( _zone2, _composant,(strlen(_composant)-strlen(_composant2)));
			_zone2[strlen(_composant)-strlen(_composant2)]='\0';
		}
		else
		{
			delete[] _zone2;
			separateurNonTrouve();
			return;
		}
	}

	if (sep3!="")
	{
		// zone3
		_composant2 = _composant2+1;	// élimination du sep2
		_zone3 = new char [strlen(_composant2)+1];
		_composant3 = strchr(_composant2,sep3[0]);
		if (_composant3 )
		{
			strncpy( _zone3, _composant2,(strlen(_composant2)-strlen(_composant3)));
			_zone3[strlen(_composant2)-strlen(_composant3)]='\0';
		}
		else
		{
			delete[] _zone3;
			separateurNonTrouve();
			return;
		}
	}

	// Suppression des blancs
	// Suppress blanks
	if (m_data->getSuppBlanc()==2 )
		suppressionBlancs( &_zone1,&_zone2,&_zone3);
	

	// remise dans l'ordre article/lot/slo avant affichage
	// deliver in order of product/lot/sub-lot before display
	switch (m_data->getRecontroleArticleCode())
	{
		case 2 :	// lot
			getSaisieLot()->setLabel(_zone1) ;
			bufferedDraw(getSaisieLot());
			delete[] _zone1;
			break;
		case 3 :	// article + lot 
			if ( m_data->getNumZoneLot()<m_data->getNumZoneArt())  // lot avant article 
			{
				_tmp =_zone1;
				_zone1 = _zone2;	// article
				_zone2 = _tmp;		// lot
			}
			getSaisieComposant()->setLabel(_zone1) ;
			bufferedDraw(getSaisieComposant());
			getSaisieLot()->setLabel(_zone2) ;
			bufferedDraw(getSaisieLot());
			delete[] _zone1;
			delete[] _zone2;
			break;
		case 4 :	// lot + slo
			if (m_data->getNumZoneSlo()< m_data->getNumZoneLot())
			{
				_tmp =_zone1;
				_zone1 = _zone2;	// lot
				_zone2 = _tmp;		// slo
			}
			getSaisieLot()->setLabel(_zone1) ;
			bufferedDraw(getSaisieLot());
			getSaisieSousLot()->setLabel(_zone2) ;
			bufferedDraw(getSaisieSousLot());
			delete[] _zone1;
			delete[] _zone2;
			break;
		case 5 :	// article + lot + slo
			if ((m_data->getNumZoneLot()< m_data->getNumZoneSlo())	   
			&&	( m_data->getNumZoneSlo() < m_data->getNumZoneArt())) 
			{
				// lot/slo/art
				_tmp =_zone1;
				_zone1 = _zone3;
				_zone3 = _zone2;
				_zone2 = _tmp;
			}
			else if ((m_data->getNumZoneSlo()< m_data->getNumZoneLot()) 
			&&	(m_data->getNumZoneLot()< m_data->getNumZoneArt()))
			{
				// slo/lot/art
				_tmp =_zone1;
				_zone1 = _zone3;
				_zone3 = _tmp ;
			}
			else if ((m_data->getNumZoneLot()< m_data->getNumZoneArt())		
			&&	 (m_data->getNumZoneArt()< m_data->getNumZoneSlo()))
			{
				// lot/art/slo
				_tmp =_zone1;
				_zone1 = _zone2;
				_zone2 = _tmp;
			}
			getSaisieComposant()->setLabel(_zone1) ;
			bufferedDraw(getSaisieComposant());
			getSaisieLot()->setLabel(_zone2) ;
			bufferedDraw(getSaisieLot());
			getSaisieSousLot()->setLabel(_zone3) ;
			bufferedDraw(getSaisieSousLot());
			delete[] _zone1;
			delete[] _zone2;
			delete[] _zone3;
			break;
	}
}
//---------------------------------------------------------------------------
void AdxRecontrole_OF::separateurNonTrouve()
{
	char* message = new char[100];
	// séparateur non trouvé, vérifiez le paramétrage du découpage du CAB
	// Seperator not found, check the barcode setting/setup
	sprintf( message,"%s ", IlvGetMessage(getInterface()->getDisplay(),"&SeparateurNonTrouve"));
	getInterface()->getMessage()->setPanneauAppelant(this);
	getInterface()->envoieMessage(message, false);
	delete [] message;	
}
//---------------------------------------------------------------------------
void AdxRecontrole_OF::suppressionBlancs(char** zone1, char** zone2, char** zone3)
{
	AdxWeighingInterface* m_WInterface = getInterface()->getWeighingInterface();
	if (*(zone1)!= NULL)
	{
		m_WInterface->afChLTrim(*(zone1));
		m_WInterface->afChRTrim(*(zone1));
	}

	if (*(zone2)!= NULL)
	{
		m_WInterface->afChLTrim(*(zone2));
		m_WInterface->afChRTrim(*(zone2));
	}

	if (*(zone3)!= NULL)
	{
		m_WInterface->afChLTrim(*(zone3));
		m_WInterface->afChRTrim(*(zone3));
	}
}
//---------------------------------------------------------------------------
void AdxRecontrole_OF::alimentationZonesLF(int lgZone1, int lgZone2 ,int lgZone3)
{
	AdxData* m_data = getInterface()->getDonnees()	;
	const char* _cab =  getSaisiContenuCab()->getLabel();
	char* _zone1 = NULL;
	char* _zone2 = NULL;
	char* _zone3 = NULL;
	char* _tmp = NULL ;
	int offset1, offset2, offset3;  // Jira X3-84572
	
	_zone1= new char[lgZone1 + 1]; 

	// X3-84572.sn  
	// We must consider the starting positions BEFORE we divide up the string into 
	// the individual fields (product, lot, sub-lot)
	offset1 = 0;
	offset2 = 0;
	offset3 = 0;
	
	switch (m_data->getRecontroleArticleCode())
	{
		case 2 : // lot
			offset1 = m_data->getDebutLot() - 1;
			break;
		case 3 : // article + lot 
			if (m_data->getDebutLot() < m_data->getDebutArt())
			{
				offset1 = m_data->getDebutLot() - 1;
				if ((m_data->getDebutLot() + lgZone1) < m_data->getDebutArt())
					offset2 = m_data->getDebutArt() - (m_data->getDebutLot() + lgZone1);
			}
			else
			{
				offset1 = m_data->getDebutArt() - 1;
				if ((m_data->getDebutArt() + lgZone1) < m_data->getDebutLot())
					offset2 = m_data->getDebutLot() - (m_data->getDebutArt() + lgZone1);
			}
			break;
		 case 4 :	// lot + slo
		 	if (m_data->getDebutSlo() < m_data->getDebutLot())
			{
				offset1 = m_data->getDebutSlo() - 1;
				if ((m_data->getDebutSlo() + lgZone1) < m_data->getDebutLot())
					offset2 = m_data->getDebutLot() - (m_data->getDebutSlo() + lgZone1);
			}
			else
			{
				offset1 = m_data->getDebutLot() - 1;
				if ((m_data->getDebutLot() + lgZone1) < m_data->getDebutSlo())
					offset2 = m_data->getDebutSlo() - (m_data->getDebutLot() + lgZone1);
			}
			break;
		  case 5 :	// article + lot + slo

		    // Product is the first one
			if ((m_data->getDebutArt() < m_data->getDebutLot()) && (m_data->getDebutArt() < m_data->getDebutSlo()))
			{
				offset1 = m_data->getDebutArt() - 1;
				if (m_data->getDebutLot() < m_data->getDebutSlo())	// Lot is 2nd
				{
					if ((m_data->getDebutArt() + lgZone1) < m_data->getDebutLot())
						offset2 = m_data->getDebutLot() - (m_data->getDebutArt() + lgZone1);
					if ((m_data->getDebutArt() + lgZone1 + offset2 + lgZone2) < m_data->getDebutSlo())
						offset3 = m_data->getDebutSlo() - (m_data->getDebutArt() + lgZone1 + offset2 + lgZone2);
				}
				else												// Sub-lot is 2nd
				{
					if ((m_data->getDebutArt() + lgZone1) < m_data->getDebutSlo())
						offset2 = m_data->getDebutSlo() - (m_data->getDebutArt() + lgZone1);
					if ((m_data->getDebutArt() + lgZone1 + offset2 + lgZone2) < m_data->getDebutLot())
						offset3 = m_data->getDebutLot() - (m_data->getDebutArt() + lgZone1 + offset2 + lgZone2);
				}
				break;
			}

			//  Lot is the first one
			if ((m_data->getDebutLot() < m_data->getDebutArt()) && (m_data->getDebutLot() < m_data->getDebutSlo()))
			{
				offset1 = m_data->getDebutLot() - 1;
				if (m_data->getDebutArt() < m_data->getDebutSlo())	// Product is 2nd
				{
					if ((m_data->getDebutLot() + lgZone1) < m_data->getDebutArt())
						offset2 = m_data->getDebutArt() - (m_data->getDebutLot() + lgZone1);
					if ((m_data->getDebutLot() + lgZone1 + offset2 + lgZone2) < m_data->getDebutSlo())
						offset3 = m_data->getDebutSlo() - (m_data->getDebutLot() + lgZone1 + offset2 + lgZone2);
				}
				else												// Sub-lot is 2nd
				{
					if ((m_data->getDebutLot() + lgZone1) < m_data->getDebutSlo())
						offset2 = m_data->getDebutSlo() - (m_data->getDebutLot() + lgZone1);
					if ((m_data->getDebutLot() + lgZone1 + offset2 + lgZone2) < m_data->getDebutArt())
						offset3 = m_data->getDebutArt() - (m_data->getDebutLot() + lgZone1 + offset2 + lgZone2);
				}
				break;
			}

			//  Sub-lot is the first one (strange)
			if ((m_data->getDebutSlo() < m_data->getDebutArt()) && (m_data->getDebutSlo() < m_data->getDebutLot()))
			{
				offset1 = m_data->getDebutSlo() - 1;
				if (m_data->getDebutArt() < m_data->getDebutLot())	// Product is 2nd
				{
					if ((m_data->getDebutSlo() + lgZone1) < m_data->getDebutArt())
						offset2 = m_data->getDebutArt() - (m_data->getDebutSlo() + lgZone1);
					if ((m_data->getDebutSlo() + lgZone1 + offset2 + lgZone2) < m_data->getDebutLot())
						offset3 = m_data->getDebutLot() - (m_data->getDebutSlo() + lgZone1 + offset2 + lgZone2);
				}
				else												// Lot is 2nd
				{
					if ((m_data->getDebutSlo() + lgZone1) < m_data->getDebutLot())
						offset2 = m_data->getDebutLot() - (m_data->getDebutSlo() + lgZone1);
					if ((m_data->getDebutSlo() + lgZone1 + offset2 + lgZone2) < m_data->getDebutArt())
						offset3 = m_data->getDebutArt() - (m_data->getDebutSlo() + lgZone1 + offset2 + lgZone2);
				}
				break;
			}
		    break;
	}
	// X3-84572.en
	
//	strncpy( _zone1,_cab,lgZone1);			X3-84572.o
	strncpy( _zone1,_cab+offset1,lgZone1);  // X3-84572.n
	_zone1[lgZone1] = '\0';

	if (lgZone2)
	{
		_zone2= new char[lgZone2 + 1]; 
//		strncpy( _zone2, _cab+lgZone1, lgZone2);					X3-84572.o
		strncpy( _zone2, _cab+offset1+lgZone1+offset2, lgZone2);	// X3-84572.n

		_zone2[lgZone2] = '\0';
	}

	if (lgZone3)
	{
		_zone3= new char[lgZone3 + 1]; 
//		strncpy( _zone3, _cab+lgZone1+lgZone2, lgZone3);							X3-84572.o
		strncpy( _zone3, _cab+offset1+lgZone1+offset2+lgZone2+offset3, lgZone3);	// X3-84572.n
		_zone3[lgZone3] = '\0';
	}

	// Suppression des blancs
	// Suppress blanks
	if (m_data->getSuppBlanc()==2 )
	{
		suppressionBlancs( &_zone1,&_zone2,&_zone3);
	}

	// remise dans l'ordre article/lot/slo avant affichage
	// deliver in order of product/lot/sub-lot before display
	switch (m_data->getRecontroleArticleCode())
	{
		case 2 : // lot
				getSaisieLot()->setLabel(_zone1) ;
				bufferedDraw(getSaisieLot());
				delete[] _zone1;
				break;
		case 3 :// article + lot 
				if (m_data->getDebutLot() < m_data->getDebutArt())	// lot avant article
				{
					_tmp =_zone1;
					_zone1 = _zone2;	// article
					_zone2 = _tmp;		// lot
				}
				getSaisieComposant()->setLabel(_zone1) ;
				bufferedDraw(getSaisieComposant());
				getSaisieLot()->setLabel(_zone2) ;
				bufferedDraw(getSaisieLot());
				delete[] _zone1;
				delete[] _zone2;
				break;
		case 4 :	// lot + slo
				if (m_data->getDebutSlo()< m_data->getDebutLot())
				{
					_tmp =_zone1;
					_zone1 = _zone2;	// lot
					_zone2 = _tmp;		// slo
				}
				getSaisieLot()->setLabel(_zone1) ;
				bufferedDraw(getSaisieLot());
				getSaisieSousLot()->setLabel(_zone2) ;
				bufferedDraw(getSaisieSousLot());
				delete[] _zone1;
				delete[] _zone2;
				break;
		case 5 :	// article + lot + slo
				if ((m_data->getDebutLot() < m_data->getDebutSlo())
				&& (m_data->getDebutSlo() < m_data->getDebutArt()))
				{
					// lot/slo/art
					_tmp =_zone1;
					_zone1 = _zone3;
					_zone3 = _zone2;
					_zone2 = _tmp;
				}
				else if ((m_data->getDebutSlo() < m_data->getDebutLot())
				&& (m_data->getDebutLot() < m_data->getDebutArt()))
				{
					// slo/lot/art
					_tmp =_zone1;
					_zone1 = _zone3;
					_zone3 = _tmp ;
				}
				else if ((m_data->getDebutLot() < m_data->getDebutArt())
				&&	(m_data->getDebutArt() < m_data->getDebutSlo()))
				{
					// lot/art/slo
					_tmp =_zone1;
					_zone1 = _zone2;
					_zone2 = _tmp;
				}
				getSaisieComposant()->setLabel(_zone1) ;
				bufferedDraw(getSaisieComposant());
				getSaisieLot()->setLabel(_zone2) ;
				bufferedDraw(getSaisieLot());
				getSaisieSousLot()->setLabel(_zone3) ;
				bufferedDraw(getSaisieSousLot());
				delete[] _zone1;
				delete[] _zone2;
				delete[] _zone3;
	}


}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::EntreeTextFieldCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();	
	AdxData* m_data = getInterface()->getDonnees();
	// mm 06.2015 - découpage du CAB
	// cutting of the barcode
	if (m_data->getDecoupageCAB() == 2) return ;

	_controleFait = false;
	_champAppelant = (IlvTextField*) g;	
// constitution du bandeau des messages
// constitution of the message banner
	CString string(IlvGetMessage(getDisplay(), "&Saisir"));
	string += " ";
	if (_champAppelant == getSaisieComposant())
		string += IlvGetMessage(getDisplay(),"&Composant1");
	if (_champAppelant == getSaisieLot())	
		if (m_interface->getFonctionEnCours() == 3
		&& m_interface->getPeseeEnCuve())
			string += IlvGetMessage(getDisplay(),"&Cuve1");
		else
			string += IlvGetMessage(getDisplay(),"&Lot1");
	// mm 03.10 - modification du recontrôle
	if (_champAppelant == getSaisieSousLot())	
		string += IlvGetMessage(getDisplay(),"&SousLot1");


	getmessage()->setLabel(string);
	bufferedDraw(getmessage()); 
}


//---------------------------------------------------------------------------
void AdxRecontrole_OF::SaisieComposantCB(IlvGraphic* g)
{
	AdxData* m_data = getInterface()->getDonnees();
	// mm 06.2015 - découpage du CAB
	if (m_data->getDecoupageCAB() == 2) return ;

	if (strcmp(getSaisieComposant()->getLabel(), "") == 0)
	{
		_composantOK = false;
		getSaisieComposant()->setChangeFocusOnValidation(false);
	}
	if (!_controleFait && strcmp(getSaisieComposant()->getLabel(), "") != 0)
	{
		controleComposant();
	}
}
//---------------------------------------------------------------------------
void AdxRecontrole_OF::SaisieLotCB(IlvGraphic* g)
{
	// 10.30 mm - modification du recontrole OF
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();

	// mm 06.2015 - découpage du CAB
	if ((m_data->getDecoupageCAB() == 2) && (getInterface()->getFonctionEnCours()!= 3))	// hors pesee en fabrication
	{	
		// mm 12.2015
		if (!_composantOK && !_lotOK &&! _souslotOK)
			return ;
		else
		{
			if ( _composantOK && _lotOK && _souslotOK)
			{
				quitter();
				retourOK();
				return ;
			}
		}
	}

	if (strcmp(getSaisieLot()->getLabel(), "") == 0)
	{
		_lotOK = false;
		getSaisieLot()->setChangeFocusOnValidation(false);
	}

	if (!_controleFait && strcmp(getSaisieLot()->getLabel(), "") != 0)
	{
		controleLot();	
		if (!_lotOK)		// X3-70592
			getSaisieLot()->setChangeFocusOnValidation(false);  
	}

	if (!m_interface->getRecontrole_OF()->getSaisieSousLot()->isActive())		// champs sous-lot inactif
	{
		if (m_interface->getRecontrole_OF()->getSaisieComposant()->isActive())  // champs composant actif
		{
			if (_composantOK && _lotOK )
			{
				quitter();
				retourOK();
			}
		}
		else
		{
			if (_lotOK )
			{
				quitter();
				retourOK();	
			}
		}

	}

}
//---------------------------------------------------------------------------
// 03.10 mm - modification recontrole OF
void AdxRecontrole_OF::SaisieSousLotCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	// mm 06.2015 - découpage du CAB
	if ((m_data->getDecoupageCAB() == 2) && (getInterface()->getFonctionEnCours() != 3))	// hors pesee en fabrication
	{	
		// mm 12.2015
		if (!_composantOK && !_lotOK &&! _souslotOK)
			return ;
		else
		{
			if ( _composantOK && _lotOK && _souslotOK)
			{
				quitter();
				retourOK();
				return ;
			}
		}
	}

	if (strcmp(getSaisieSousLot()->getLabel(),"")== 0)
	{
		_souslotOK = false;
		getSaisieSousLot()->setChangeFocusOnValidation(false);
	}

	if (!_controleFait && strcmp(getSaisieSousLot()->getLabel(),"") != 0)
	{
		controleSousLot();
		if (!_souslotOK)		// X3-70592
			getSaisieSousLot()->setChangeFocusOnValidation(false);  
		
		if (m_interface->getRecontrole_OF()->getSaisieComposant()->isActive())  // champs composant actif
		{
			if (_souslotOK && _composantOK && _lotOK)
			{
				quitter();
				retourOK();		
			}
		}
		else
		{
			if (_souslotOK && _lotOK)
			{
				quitter();
				retourOK();	
			}
		}
	}
}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::TactileCB(IlvGraphic* g)
{
	if (_champAppelant->isEditable() == false)
		return;
	AdxInterface* m_interface = getInterface();
	IlvRect m_rect = 0;
	boundingBox (m_rect);
	initClavier_Tactile();
	this->hide();
	m_interface->getClavier_Tactile()->show();
}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::initClavier_Tactile()
{
	AdxClavier_Tactile* tactile = getInterface()->getClavier_Tactile();
	tactile->setPanneauAppelant(this);
// 3 appels possibles du clavier dans Recontrole_OF
// 3 possible keyboard calls in Recontrole_OF
	if (_champAppelant == (IlvTextField*)getSaisieComposant())
	{
		tactile->setSaisie(getSaisieComposant()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Composant1");
		tactile->getchampMessage()->setLabel(string);
	}

	if (_champAppelant == (IlvTextField*)getSaisieLot())
	{
		tactile->setSaisie(getSaisieLot()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		if (getInterface()->getFonctionEnCours() == 3
		&& getInterface()->getPeseeEnCuve())
			string += IlvGetMessage(getDisplay(),"&Cuve1");
		else
			string += IlvGetMessage(getDisplay(),"&Lot1");
		tactile->getchampMessage()->setLabel(string);
	}

	// 03.10 mm - modification du recontrole OF
	if (_champAppelant == (IlvTextField*)getSaisieSousLot())
	{
		tactile->setSaisie(getSaisieSousLot()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&SousLot1" );
		tactile->getchampMessage()->setLabel(string);
	}

	tactile->getchampSaisie()->setLabel(tactile->getSaisie());
	tactile->reDrawObj(tactile->getchampSaisie());
}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::ValiderCB(IlvGraphic* g)
{
	quitter();
}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::QuitterCB(IlvGraphic* g)
{
	AdxPesee_OF* pesee_OF = getInterface()->getPesee_OF();
	AdxData* m_data = getInterface()->getDonnees();
	quitter();
	// 03.10 mm - Si on répond non au recontrôle OF, il faut permettre de saisir à nouveau le lot
	// et la balance, qui ont été RAZ.
	pesee_OF->getSaisieRecipient()->setEditable(true);
	pesee_OF->getSaisieBalance()->setEditable(true);
	if(!_composantOK)
	{
		if (m_data->getModifLigneStockCode() != 1) // modifiable
			pesee_OF->attenteSaisieLot();
		else
			pesee_OF->propositionLot();
		return;
	}
	if(!_lotOK)
	{
		if (m_data->getModifLigneStockCode() != 1) // modifiable
			pesee_OF->attenteSaisieLot();
		else
			pesee_OF->propositionLot();
		return;
	}
	// mm 03.10 - modification du recontrôle
	if(!_souslotOK)
	{
		if (m_data->getModifLigneStockCode() != 1) // modifiable
			pesee_OF->attenteSaisieLot();
		else
			pesee_OF->propositionLot();
		return;
	}

	retourOK();
}

//---------------------------------------------------------------------------
bool AdxRecontrole_OF::controleComposant()
{
	AdxInterface* m_interface = getInterface();
	AdxPesee_OF* m_peseeOF = m_interface->getPesee_OF();		// 12.08 mm
	AdxData* m_data = m_interface->getDonnees();

	if (strcmp(m_data->getCurrentComposant()->getComposant(),
		getSaisieComposant()->getLabel()) == 0)
	{
		_composantOK = true;
		setFocus(getSaisieLot());
	}
	else
	{
		_composantOK = false;
		char* message = new char[80];
		sprintf(message,"%s = %s : %s ",
				IlvGetMessage(m_interface->getDisplay(),
					"&ComposantControleDifferent"),
				getSaisieComposant()->getLabel(),
				IlvGetMessage(m_interface->getDisplay(),
					"&Recontroler?")); 
		m_interface->getMessage()->setPanneauAppelant(this);
		_controleFait = true;
		if (m_interface->envoieMessage(message,true) == true)
		{
			delete [] message;
			getSaisieComposant()->setLabel("");
			setFocus(getSaisieComposant());
		}
		else
		{
			delete [] message;
			getSaisieComposant()->setLabel("");
			// 12.08 mm - Si on répond non au recontrôle OF, il faut permettre de saisir à nouveau le lot
			// et la balance, qui ont été RAZ.
			m_peseeOF->getSaisieRecipient()->setEditable(true);
			m_peseeOF->getSaisieBalance()->setEditable(true);
			quitter();
			if (m_interface->getDonnees()->getModifLigneStockCode() != 1) // modifiable
				m_interface->getPesee_OF()->attenteSaisieLot();
			else
				m_interface->getPesee_OF()->propositionLot();
		}
	}
	return _composantOK;
}
//---------------------------------------------------------------------------
bool AdxRecontrole_OF::controleLot()
{
	AdxInterface* m_interface = getInterface();
	AdxPesee_OF* m_peseeOF = m_interface->getPesee_OF();		// 12.08 mm
	AdxData* m_data = m_interface->getDonnees();
    char* szTemp = new char[40];								// 03.10 mm
	int j = 0;

	// 03.10 mm - modification du re-contrôle OF
	if ((m_interface->getFonctionEnCours() == 3) && (m_interface->getPeseeEnCuve()) )
		j = sprintf(szTemp,"%s", m_data->getCurrentLot()->getCuve());
	else 
		j = sprintf(szTemp,"%s", m_data->getCurrentLot()->getLot());	
	if (strcmp(szTemp, getSaisieLot()->getLabel()) == 0)
	{
		_lotOK = true;
		if (m_interface->getFonctionEnCours() != 3)
		{
			if (m_data->getRecontroleArticleCode() == 4 ||m_data->getRecontroleArticleCode() == 5 )
				setFocus(getSaisieSousLot()) ;
		}
	}
	else
	{
		_lotOK = false;
		char* message = new char[80];
		if (m_interface->getFonctionEnCours() == 3
		&& m_interface->getPeseeEnCuve())
			sprintf(message,"%s = %s : %s ",
				IlvGetMessage(m_interface->getDisplay(),
					"&CuveControleeDifferente"),
				getSaisieLot()->getLabel(),
				IlvGetMessage(m_interface->getDisplay(),
					"&Recontroler?")); 
		else
			sprintf(message,"%s = %s : %s ",
				IlvGetMessage(m_interface->getDisplay(),
					"&LotControleDifferent"),
				getSaisieLot()->getLabel(),
				IlvGetMessage(m_interface->getDisplay(),
					"&Recontroler?")); 
		getInterface()->getMessage()->setPanneauAppelant(this);
		_controleFait = true;
		if (m_interface->envoieMessage(message,true) == true) 
		{
			delete [] message;
//			MessageBox(NULL,getSaisieLot()->getLabel(),"getSaisieLot()",MB_OK);
			getSaisieLot()->setLabel("");
			setFocus(getSaisieLot());
		}
		else
		{
			delete [] message;
			getSaisieLot()->setLabel("");
			// 12.08 mm - Si on répond non au recontrôle OF, il faut permettre de saisir à nouveau le lot
			// et la balance, qui ont été RAZ.
			m_peseeOF->getSaisieRecipient()->setEditable(true);
			m_peseeOF->getSaisieBalance()->setEditable(true);
			quitter();
			if (m_interface->getDonnees()->getModifLigneStockCode() != 1) // modifiable
				m_interface->getPesee_OF()->attenteSaisieLot();
			else
				m_interface->getPesee_OF()->propositionLot();
		}
	}
	delete [] szTemp;
	return _lotOK;
}

//---------------------------------------------------------------------------
bool AdxRecontrole_OF::controleSousLot()
{
	AdxInterface* m_interface = getInterface();
	AdxPesee_OF* m_peseeOF = m_interface->getPesee_OF();		// 12.08 mm
	AdxData* m_data = m_interface->getDonnees();

	if (strcmp(m_data->getCurrentLot()->getSlo(),
		getSaisieSousLot()->getLabel()) == 0)
	{
		_souslotOK = true;
	}
	else
	{
		_souslotOK = false;
		char* message = new char[80];
		sprintf(message,"%s = %s : %s ",
				IlvGetMessage(m_interface->getDisplay(),
					"&SousLotControleDifferent"),
				getSaisieSousLot()->getLabel(),
				IlvGetMessage(m_interface->getDisplay(),
					"&Recontroler?")); 
		m_interface->getMessage()->setPanneauAppelant(this);
		_controleFait = true;
		if (m_interface->envoieMessage(message,true) == true)
		{
			delete [] message;
			getSaisieSousLot()->setLabel("");
			setFocus(getSaisieSousLot());
		}
		else
		{
			delete [] message;
			getSaisieSousLot()->setLabel("");
			// 12.08 mm - Si on répond non au recontrôle OF, il faut permettre de saisir à nouveau le lot
			// et la balance, qui ont été RAZ.
			m_peseeOF->getSaisieRecipient()->setEditable(true);
			m_peseeOF->getSaisieBalance()->setEditable(true);
			quitter();
			m_interface->getPesee_OF()->attenteSaisieRecipient();
		}
	}

	return _souslotOK ;
}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::retourOK()
{
	AdxPesee_OF* pesee_OF = getInterface()->getPesee_OF();
	pesee_OF->setRecontroleFait(true);
	pesee_OF->reDraw();

	// APCPRD-2636 mm 08.2013
	if ((!pesee_OF->getSaisiePoidsPese()->isEditable()) && (!pesee_OF->getBalanceChoisie()->getConnecte()))
	{
		 pesee_OF->getSaisiePoidsPese()->setEditable(true);	  
	}


	if (pesee_OF->getBoutonAppelant() == 
		pesee_OF->gettarer())
	{
		pesee_OF->tarerCB(pesee_OF->gettarer());
		return;
	}

	if (pesee_OF->getBoutonAppelant() == pesee_OF->getpeser())
	{
			pesee_OF->peserCB(pesee_OF->getpeser());
	}

}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::quitter()
{
	AdxInterface* m_interface = getInterface();
	AdxRecontrole_OF* m_recontrole_OF = m_interface->getRecontrole_OF();
 	m_recontrole_OF->hide();
	_panneauAppelant->show();
}

//---------------------------------------------------------------------------
void AdxRecontrole_OF::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));


	char szFileIcons[_MAX_PATH];

	// bouton Valider
/*	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\thumb_up.png",
		_interface->getPathX3());
	IlvBitmap* bitmap =	getDisplay()->readBitmap(szFileIcons);
	getValider()->setBitmap(bitmap);*/

	// bouton Tactile
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\keyboard.png",
		_interface->getPathX3());
	IlvBitmap* bitmap = getDisplay()->readBitmap(szFileIcons);
	getTactile()->setBitmap(bitmap);

	// bouton Quitter
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\exit.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getQuitter()->setBitmap(bitmap);

	IlvRect bbox;
	boundingBox(bbox);

	IlvRect monecran;
	IlvRect boundingBox;
	this->boundingBox(boundingBox);

	getDisplay()->screenBBox(monecran,true,&boundingBox);

	IlvDim sizeScreenW = monecran.w();
	IlvDim sizeScreenH = monecran.h();

	setMinimumSize (sizeScreenW, bbox.h());
	setMaximumSize (sizeScreenW, bbox.h());

	// masque bouton Valider
    //setVisible(getValider(),IlvFalse, IlvFalse);
	_controleFait = false;
}
