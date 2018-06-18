// AdxData.cpp
// ----------------
// project : Adonix X3 Centrales
// author : EP 14/05/2001
//--------------------------------------------------------------
//
#include "stdafx.h"
#include "AdxData.h"
#include <ilviews/base/message.h>
//#include <windows.h>
#include <cmath>
#include "x3centr1.h"                        

#include "AdxUnit.h"
#include "AdxOrder.h"
#include "AdxPhase.h"
#include "AdxComposant.h"
#include "AdxLot.h"
#include "AdxBalance.h"
#include "AdxFicheISM.h"
#include "AdxFicheISMRecipient.h"
#include "AdxRecipient.h"
#include "AdxAccueil.h"

#include "AdxDate.h"
#include "AdxInterface.h"
#include "AdxCsvFiles.h"
#include "AdxMessage.h"
#include "AdxGadgetContainer.h"
#include "AdxPesee_OF.h"
#include "AdxPesee_Etalon.h"
#include "AdxChoix_OF.h"
#include "AdxEtalon.h"
#include "AdxEtalonLigne.h"
#include "win unicode.h"				// 06.04 Unicode

using std::ios;

using std::endl;


//--------------------------------------------------------------
AdxData::~AdxData()
{
	if( _szCheminCsv1 != NULL)
		delete [] _szCheminCsv1;
	if( _szCheminCsv2 != NULL)
		delete [] _szCheminCsv2;
	if( _szCheminCsv3 != NULL)
		delete [] _szCheminCsv3;
	if( _szCheminCsv4 != NULL)
		delete [] _szCheminCsv4;
	if( _szCheminCsv5 != NULL)
		delete [] _szCheminCsv5;
	if( _szCheminCsv6 != NULL)
		delete [] _szCheminCsv6;
	if( _szCheminCsv7 != NULL)
		delete [] _szCheminCsv7;
	if( _szCheminCsv8 != NULL)
		delete [] _szCheminCsv8;
	if( _szCheminCsv9 != NULL)
		delete [] _szCheminCsv9;
	if( _szCheminCsv10 != NULL)
		delete [] _szCheminCsv10;
	if( _szCheminCsv11 != NULL)
		delete [] _szCheminCsv11;
	if( _szCheminCsv12 != NULL)
		delete [] _szCheminCsv12;
	if( _szCheminCsv13 != NULL)
		delete [] _szCheminCsv13;
	if( _szCheminCsv14 != NULL)				//X3-67237
		delete [] _szCheminCsv14;			//X3-67237	

	if( _dateJour != NULL)
		delete  _dateJour;
	if( _language != NULL)
		delete [] _language;
	if( _utilisateur != NULL)
		delete [] _utilisateur;
	if( _application != NULL)
		delete [] _application;
	if( _lieu != NULL)
		delete [] _lieu;
	if( _box != NULL)
		delete [] _box;
	if( _ouvertureBox != NULL)
		delete [] _ouvertureBox;
	if( _videBoxFinOF != NULL)
		delete [] _videBoxFinOF;
	if( _videBoxFinPhase != NULL)
		delete [] _videBoxFinPhase;
	if( _videBoxFinMatiere != NULL)
		delete [] _videBoxFinMatiere; // SMO : STD-PR-OO1 : Pesee Matiere
	if( _peseePartielle != NULL)
		delete [] _peseePartielle;
	if( _modifLigneStock != NULL)
		delete [] _modifLigneStock;
	if( _recontroleArticle != NULL)
		delete [] _recontroleArticle;
	if( _libOFEnCoursPesee != NULL)
		delete [] _libOFEnCoursPesee;
	if( _libOFPeseBox != NULL)
		delete [] _libOFPeseBox;
	if( _libMatEnCoursPesee != NULL)
		delete [] _libMatEnCoursPesee;
	if( _libMatPese != NULL)
		delete [] _libMatPese;

	if(_orderList != NULL)
	{
		if (_nbOrders > 0)
		{
			for (int i = 0; i < _nbOrders; i++)
			{
				delete (AdxOrder*)(*_orderList)[i];
			}
		}
		_orderList->empty();
		delete _orderList;
	}
	if(_balanceList != NULL)
	{
		if (_nbBalances > 0)
		{
			for (int i = 0; i < _nbBalances; i++)
			{
				delete (AdxBalance*)(*_balanceList)[i];
			}
		}
		_balanceList->empty();
		delete _balanceList;
	}
	if(_recipientList != NULL)
	{
		if (_nbRecipients > 0)
		{
			for (int i = 0; i < _nbRecipients; i++)
			{
				delete (AdxRecipient*)(*_recipientList)[i];
			}
		}
		_recipientList->empty();
		delete _recipientList;
	}
	if(_composantList_Art != NULL)
	{
		_composantList_Art->empty();
		delete _composantList_Art;
	}
	if(_phaseList != NULL)
	{
		if (_nbPhases > 0)
		{
			for (int i = 0; i < _nbPhases; i++)
			{
				delete (AdxPhase*)(*_phaseList)[i];
			}
		}
		_phaseList->empty();
		delete _phaseList;
	}
	if(_ficheISMList != NULL)
	{
		if (_nbFichesISM > 0)
		{
			for (int i = 0; i < _nbFichesISM; i++)
			{
				delete (AdxFicheISM*)(*_ficheISMList)[i];
			}
		}
		_ficheISMList->empty();
		delete _ficheISMList;
	}
	if(_lotList != NULL)
	{
		if (_nbLots > 0)
		{
			for (int i = 0; i < _nbLots; i++)
			{
				delete (AdxLot*)(*_lotList)[i];
			}
		}
		_lotList->empty();
		delete _lotList;
	}
	if(_ficheISMRecipientList != NULL)
	{
		if (_nbFichesISMRecipient > 0)
		{
			for (int i = 0; i < _nbFichesISMRecipient; i++)
			{
				delete (AdxFicheISMRecipient*)(*_ficheISMRecipientList)[i];
			}
		}
		_ficheISMRecipientList->empty();
		delete _ficheISMRecipientList;
	}
	if(_unitList != NULL)
	{
		if (_nbUnits > 0)
		{
			for (int i = 0; i < _nbUnits; i++)
			{
				delete (AdxUnit*)(*_unitList)[i];
			}
		}
		_unitList->empty();
		delete _unitList;
	}
	if(_etalonList != NULL)
	{
		if (_nbEtalons > 0)
		{
			for (int i = 0; i < _nbEtalons; i++)
			{
				delete (AdxEtalon*)(*_etalonList)[i];
			}
		}
		_etalonList->empty();
		delete _etalonList;
	}

	if( _X3UserID != NULL)			//X3-67237
		delete [] _X3UserID;		//X3-67237

}

//--------------------------------------------------------------
// Load data
//

bool AdxData::loadData( const char* PARfileName,	//parameters
						const char* MWFfileName,	//orders
						const char* PHAfileName,	//phases
						const char* MATfileName,	//matieres
						const char* SLEfileName,	//balances
						const char* HSHfileName,	//fiches ISM
						const char* CTNfileName,	//fiches ISM récipient
						const char* TCOfileName,	//unite
						const char* CGDfileName,	//guides etalonnage
						const char* UIDfileName		//X3-67237 - UID File
					  ) 
{
	bool dataOK = false;

	// A. parameters

	if( (PARfileName != NULL) && strcmp( PARfileName, "") != 0) 
	{
		dataOK = loadParameters( PARfileName);
	}

	// B. orders

	if( dataOK && (MWFfileName != NULL) && strcmp( MWFfileName, "") != 0) 
	{
		dataOK = loadOrders( MWFfileName);
	}

	// C. phases

	if( dataOK && (PHAfileName != NULL) && strcmp( PHAfileName, "") != 0) 
	{
		dataOK = loadPhases( PHAfileName);
	}

	// G. fiches ISM lecture avancee pour que setCurrentComposantIndex()
	//    fonctionne bien

	if( dataOK && (HSHfileName != NULL) && strcmp( HSHfileName, "") != 0) 
	{
		dataOK = loadFichesISM( HSHfileName);
	}

	// D. matieres

	if( dataOK && (MATfileName != NULL) && strcmp( MATfileName, "") != 0) 
	{
		dataOK = loadComposants( MATfileName, 0);
	}

	// F. balances

	if( dataOK && (SLEfileName != NULL) && strcmp( SLEfileName, "") != 0) 
	{
		dataOK = loadBalances( SLEfileName);
	}

	// H. unites

	if( dataOK && (TCOfileName != NULL) && strcmp( TCOfileName, "") != 0) 
	{
		dataOK = loadUnits( TCOfileName);
	}
	// I. guides etalonnage

	if( dataOK && (CGDfileName != NULL) && strcmp( CGDfileName, "") != 0) 
	{
		dataOK = loadEtalons( CGDfileName);
	}

	if( dataOK && (UIDfileName != NULL) && strcmp( UIDfileName, "") != 0)		//NSH
	{																			//NSH
		dataOK = loadUserID( UIDfileName);										//NSH
	}																			//NSH

	return dataOK;
}

//--------------------------------------------------------------
bool AdxData::loadParameters( const char* ParamfileName)
{
	const int DATJOU	= 0;
	const int LANCOD	= 1;
	const int UTICOD	= 2;
	const int NAPPLI	= 3;
	const int LIECOD	= 4;
	const int BOXCOD	= 5;
	const int OUVBOX	= 6;
	const int OUVOBL	= 7;
	const int VIDEOF	= 8;
	const int OFOBLI	= 9;
	const int VIDPHA	= 10;
	const int PHAOBL	= 11;
	const int PARCOD	= 12;
	const int PARLIB	= 13;
	const int MODCOD	= 14;
	const int MODLIB	= 15;
	const int RECCOD	= 16;
	const int RECLIB	= 17;
	const int CUVCOD	= 18;
    const int CUVLIB    = 19;
	const int PRICOD	= 20;
	const int PRILIB	= 21;
	const int WRHBOX	= 22;
	const int LOCBOX	= 23;
	const int AUTCOD	= 24;
	const int AUTLIB	= 25;
	const int LENCOD    = 26;
	const int REDCOD    = 27;
	const int MAECOD	= 28;
	const int MAELIB	= 29;
	const int MAPCOD	= 30;
	const int MAPLIB	= 31;
	const int OFECOD	= 32;
	const int OFELIB	= 33;
	const int OFPCOD	= 34;
	const int OFPLIB	= 35;
	const int VIDMAT	= 36;	// SMO : STD-PR-OO1 : Pesee Matiere : 20/05/2010
	const int MATOBL	= 37;	// SMO : STD-PR-OO1 : Pesee Matiere : 20/05/2010
    const int LISMAT	= 38;	// 90456 mm 06.13 - Gestion chargement liste matière
	const int ATPOPW	= 39;	// 113445 mm 07.2016 - Appplication of weighing tolerances
	const int POSTOL	= 40;	// 116324 mm 08.2016 - Authorization to exceed the tolerance +

	//Récupération des règles de découpage du CAB si besoin - 83201 mm 10.2014 
	const int CUTCOD	= 41;
	const int CUTLIB	= 42;
	const int TYPCAB	= 43;
	const int SUPBLC	= 44;
	const int NUMITM    = 45;
	const int ITMSET	= 46;
	const int NUMLOT	= 47;
	const int LOTSET    = 48;
	const int NUMSLO	= 49;
	const int SLOSET	= 50;
	const int ITMLON    = 51;
	const int ITMDEB	= 52;
	const int LOTLON	= 53;
	const int LOTDEB	= 54;
	const int SLOLON	= 55;
	const int SLODEB    = 56;

	bool isOk = false;
	AdxCsvFileReader PARfile( ParamfileName, FieldSeparator, Decimal);

	if( PARfile.ok())
	{
		PARfile.skipLinesBeginningWith( Comment);
		AdxCsvLine line = *PARfile;

//X3-67237		// mm 08.2016 - & remplaced by ||
//X3-67237		if (( line.getNbOfFields() < 43) ||
//X3-67237		 ((line.getNbOfFields() > 43)  &&   (line.getNbOfFields() < 57)) ||
//X3-67237		 ( line.getNbOfFields() > 57))
//X3-67237		{
//X3-67237			getInterface()->getMessage()->setPanneauAppelant(NULL);
//X3-67237			getInterface()->envoieMessage("&ErrorX3ScalesBox.csv",false);
//X3-67237			isOk = false;
//X3-67237			return isOk;
//X3-67237		}

//X3-67237: Added below block to set the _X3Ver field based on which version the file layout is in
		setX3Ver(0);
		
		if ((line.getNbOfFields() == 43) || (line.getNbOfFields() == 57))
		{
			setX3Ver(10);
		}
	
		if ((line.getNbOfFields() == 48) || (line.getNbOfFields() == 62))
		{
			setX3Ver(11);
		}

		if ( getX3Ver() == 0)
		{
			getInterface()->getMessage()->setPanneauAppelant(NULL);
			getInterface()->envoieMessage("&ErrorX3ScalesBox.csv",false);
			isOk = false;
			return isOk;
		}
//X3-67237: End of added block


		// 06.04 Unicode
		setCodepage(GetACP());

		// 06.04 Unicode
		// Tous les getString sont replacés par getStringUnicode

		_dateJour = new AdxDate( getStringUnicode(&line, DATJOU), YYYYMMDD);
		setLanguage(getStringUnicode(&line, LANCOD));
		setUtilisateur(getStringUnicode(&line, UTICOD));
		setApplication(getStringUnicode(&line, NAPPLI));
		setLieu(getStringUnicode(&line, LIECOD));
		setBox(getStringUnicode(&line, BOXCOD));
		setOuvertureBox(getStringUnicode(&line, OUVBOX));
		setOuvertureBoxOblig(line.getLong( OUVOBL));
		setVideBoxFinOF(getStringUnicode(&line, VIDEOF));
		setVideBoxFinOFOblig(line.getLong( OFOBLI));
		setVideBoxFinPhase(getStringUnicode(&line, VIDPHA));
		setVideBoxFinPhaseOblig(line.getLong( PHAOBL));
		setPeseePartielleCode(line.getLong( PARCOD));
		setPeseePartielle(getStringUnicode(&line, PARLIB));
		setModifLigneStockCode(line.getLong( MODCOD));
		setModifLigneStock(getStringUnicode(&line, MODLIB));
		setRecontroleArticleCode(line.getLong( RECCOD));
		setRecontroleArticle(getStringUnicode(&line, RECLIB));
		setRecontroleCuveCode(line.getLong(CUVCOD));
		setRecontroleCuve(getStringUnicode(&line, CUVLIB));

		setPrioriteAllocationCode(line.getLong(PRICOD));
		setPrioriteAllocation(getStringUnicode(&line, PRILIB));
		setDepotBox(getStringUnicode(&line, WRHBOX));
		setEmplacementBox(getStringUnicode(&line, LOCBOX));
		setAllocationAutoCode(line.getLong(AUTCOD));
		setAllocationAuto(getStringUnicode(&line, AUTLIB));

		setLongueurLot(line.getLong( LENCOD));
		setRedressementNegatif(line.getLong(REDCOD));
		setCodeMatEnCoursPesee(line.getLong( MAECOD));
		setLibMatEnCoursPesee(getStringUnicode(&line, MAELIB));
		setCodeMatPese(line.getLong( MAPCOD));
		setLibMatPese(getStringUnicode(&line, MAPLIB));
		setCodeOFEnCoursPesee(line.getLong( OFECOD));
		setLibOFEnCoursPesee(getStringUnicode(&line, OFELIB));
		setCodeOFPeseBox(line.getLong( OFPCOD));
		setLibOFPeseBox(getStringUnicode(&line, OFPLIB));
		setVideBoxFinMatiere(getStringUnicode(&line, VIDMAT));	// SMO : STD-PR-OO1 : Pesee Matiere : 20/05/2010
		setVideBoxFinMatiereOblig(line.getLong( MATOBL));		// SMO : STD-PR-OO1 : Pesee Matiere : 20/05/2010

		setChargementListMat(line.getLong(LISMAT));				// 06.2013 mm 90456 
		setApplicationTolerance(line.getLong(ATPOPW));			// 113445 mm 07.2016
		setExceedingTolerancePos(line.getLong(POSTOL));			// 116324 mm 08.2016

		// 01.2015 mm 103422 - découpage CAB et recontrole
		setDecoupageCAB(line.getLong(CUTCOD));						
		setLibDecoupageCAB(getStringUnicode(&line,CUTLIB));
		if (getDecoupageCAB()== 2)
		{
			setTypeCAB(line.getLong(TYPCAB));
			setSuppBlanc(line.getLong(SUPBLC));
			setNumZoneArt(line.getLong(NUMITM));
			setSeparateurArt(getStringUnicode(&line,ITMSET));
			//if (getSeparateurArt() == "V")
			if (strcmp(getSeparateurArt(),"V") == 0)
						setSeparateurArt(",");
			else if (strcmp(getSeparateurArt(),"P")==0)			// 111598 mm 08.2016
						setSeparateurArt(";");
			setNumZoneLot(line.getLong(NUMLOT));
			setSeparateurLot(getStringUnicode(&line,LOTSET));
			//if (getSeparateurLot() == "V")
			if (strcmp(getSeparateurLot(),"V") == 0)
						setSeparateurLot(",");
			else if (strcmp(getSeparateurLot(),"P")== 0)		// 111598 mm 08.2016
						setSeparateurLot(";");
			setNumZoneSlo(line.getLong(NUMSLO));
			setSeparateurSlo(getStringUnicode(&line,SLOSET));
			//if (getSeparateurSlo() == "V")
			if (strcmp(getSeparateurSlo(),"V") == 0)
						setSeparateurSlo(",");
			else if (strcmp(getSeparateurSlo(),"P")== 0)		// 111598 mm 08.2016
						setSeparateurSlo(";");
			setLongueurArt(line.getLong(ITMLON));
			setDebutArt(line.getLong(ITMDEB));
			setLongueurLot2(line.getLong(LOTLON));
			setDebutLot(line.getLong(LOTDEB));
			setLongueurSlo(line.getLong(SLOLON));
			setDebutSlo(line.getLong(SLODEB));
		}

//X3-67237: Added below sention to determine whether we are pre V11 or not
		if ( getX3Ver() == 11)
		{
			if (getDecoupageCAB() == 1)
			{
				setUsrWei(line.getLong(43));
				setBoxPwd(line.getLong(44));
				setEwoPwd(line.getLong(45));
				setPhaPwd(line.getLong(46));
				setMatPwd(line.getLong(47));
			}														
			else
			{
				setUsrWei(line.getLong(57));
				setBoxPwd(line.getLong(58));
				setEwoPwd(line.getLong(59));
				setPhaPwd(line.getLong(60));
				setMatPwd(line.getLong(61));
			}
		}
//X3-67237: End of added block

		// lecture dictionnaire langue choisie
		if (!getInterface()->lectureDictionnaire(1))
		{
			isOk = false;
			return isOk;
		}
		isOk = true;
	}

	if (isOk == false)
	{
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage("&ErrorX3ScalesBox.csv",false);
	}
	return isOk;
}

//--------------------------------------------------------------
bool AdxData::loadOrders( const char* OrderfileName)
{
	const int NUMOF		= 0;
	const int ARTCOD	= 1;
	const int ARTLIB	= 2;
	const int LOTLAN	= 3;
	const int QTELAN	= 4;
	const int UNILAN	= 5;
	const int STACOD	= 6;
	const int STALIB	= 7;
	const int DATFIN	= 8;
	const int PRICOD	= 9;
	const int PRILIB	= 10;
	const int QTEPOI	= 11;
	const int UNIPOI	= 12;
	const int TTAPSR    = 13; //     : 18/08/2010 : ajout champs infos colonnes: total a peser
	const int MATWEU    = 14; //     : 18/08/2010 : ajout champs infos colonnes: unite de poids matiere


	int noEnr = 0;
	bool isOk = false;
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadOrders Entree" << endl;
	}
	AdxCsvFileReader MWFfile( OrderfileName, FieldSeparator, Decimal);

	if( MWFfile.ok()) 
	{
		MWFfile.skipLinesBeginningWith( Comment);
		if (_nbOrders > 0)
		{
			for (int i = 0; i < _nbOrders; i++)
			{
				delete (AdxOrder*)(*_orderList)[i];
			}

		}
		_nbOrders = 0;
		_orderList->empty();
		for( ; MWFfile.ok() ; ++MWFfile)	
		{
			AdxCsvLine line = *MWFfile;

			noEnr++;

			if (line.getNbOfFields() != 15)	
			{
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				char* message = new char[60];
				sprintf(message,"%s : %s = %d",
					IlvGetMessage(getInterface()->getDisplay(),"&ErrorX3ScalesMwg.csv"),
					IlvGetMessage(getInterface()->getDisplay(),"&Rang"),
					noEnr); 
				getInterface()->envoieMessage(message,false);
				delete [] message;
				isOk = false;
				return isOk;
			}
			
			AdxOrder* order = new AdxOrder;
		
			order->setNumOF( getStringUnicode(&line, NUMOF));
			order->setArticle( getStringUnicode(&line, ARTCOD));
			order->setLibArticle( getStringUnicode(&line, ARTLIB));
			order->setLotLance( getStringUnicode(&line, LOTLAN));
			order->setQuantiteLance( line.getDouble( QTELAN));
			order->setUnite( getStringUnicode(&line, UNILAN));
			order->setStatut( line.getLong( STACOD));
			order->setLibStatut( getStringUnicode(&line, STALIB));
			order->setDateFin( new AdxDate( getStringUnicode(&line, DATFIN), YYYYMMDD));
			order->setPriorite( line.getLong( PRICOD));
			order->setLibPriorite( getStringUnicode(&line, PRILIB));
			order->setQuantiteLanceeEnPoids( line.getDouble( QTEPOI));
			order->setUnitePoids( getStringUnicode(&line, UNIPOI));
			// SMO : 18/08/2010 : champs pour pesee matiere
			order->setTotalAPeser( line.getDouble( TTAPSR));
			order->setUnitePoidsCompo( getStringUnicode(&line, MATWEU));

			getOrderList()->append(order);

			isOk = true;
		}
	}

	if (isOk == false)
	{
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage("&AucunOF",false);
		return isOk;
	}

	_nbOrders = noEnr;
	// mm 08.10 - initialisation par défaut seulement en cas de pesée par OF ou pesée en fabrication
	if  (getInterface()->getFonctionEnCours() != 2 )
		setCurrentOrderIndex(0,1);
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadOrders Sortie return("<<isOk<<")" << endl;
	}
	return isOk;
}

//--------------------------------------------------------------
bool AdxData::loadPhases( const char* PhasefileName)
{
	const int NUMOF		= 0;
	const int NUMPHA	= 1;
	const int STACOD	= 2;
	const int STALIB	= 3;
	const int DATE  	= 4;
	const int PRICOD	= 5;
	const int PRILIB	= 6;
	const int RETQTY    = 7;
	const int ALLQTY    = 8;
	const int ITMWEU    = 9;


	int noEnr = 0;
	bool isOk = false;
	setEnCoursDePeseeParArticle (false);
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadPhases Entree" << endl;
	}

	AdxCsvFileReader PHAfile( PhasefileName, FieldSeparator, Decimal);

	if( PHAfile.ok()) 
	{
		PHAfile.skipLinesBeginningWith( Comment);
		if (_nbPhases > 0)
		{
			for (int i = 0; i < _nbPhases; i++)
			{
				delete (AdxPhase*)(*_phaseList)[i];
			}

		}
		_nbPhases = 0;
		_phaseList->empty();
		for( ; PHAfile.ok() ; ++PHAfile)	
		{
			AdxCsvLine line = *PHAfile;

			noEnr++;

			if ( line.getNbOfFields() != 10 && (strcmp(getStringUnicode(&line, NUMOF),getCurrentOrder()->getNumOF()) == 0))
			{ 
				getInterface()->envoieMessage("&ArticleEnCoursDePesee",false);
				_currentOrder = NULL;
				_currentOrderIndex = 0;
				setEnCoursDePeseeParArticle (true);
				isOk = false;
				return isOk;
			}
			
			if (line.getNbOfFields() != 10)	
			{
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				char* message = new char[60];
				sprintf(message,"%s : %s = %d",
					IlvGetMessage(getInterface()->getDisplay(),"&ErrorX3ScalesPha.csv"),
					IlvGetMessage(getInterface()->getDisplay(),"&Rang"),
					noEnr); 
				getInterface()->envoieMessage(message,false);
				delete [] message;
				isOk = false;
				return isOk;
			}
		
			if (strcmp(getStringUnicode(&line, NUMOF),getCurrentOrder()->getNumOF()) != 0)
			{
				isOk = false;
				return isOk;
			}

			AdxPhase* phase = new AdxPhase;
		
			phase->setNumOF( getStringUnicode(&line, NUMOF));
			phase->setNumPhase( line.getLong( NUMPHA));
			phase->setStatut( line.getLong( STACOD));
			phase->setLibStatut( getStringUnicode(&line, STALIB));
			phase->setDate( new AdxDate( getStringUnicode(&line, DATE), YYYYMMDD));
			phase->setPriorite( line.getLong( PRICOD));
			phase->setLibPriorite( getStringUnicode(&line, PRILIB));
			phase->setNbComposants(0);
			phase->setNbComposantsPeses(0);
			// SMO : 18/08/2010
			phase->setQteRestaPeser( line.getDouble(RETQTY));
			phase->setQteAllouee( line.getDouble(ALLQTY));
			phase->setUnite( getStringUnicode(&line, ITMWEU));

			// sr 06.02 Si une phase est en réconciliation ou réconciliée,
			// il faut la considérer comme pesée
			if ((phase->getStatut() > 2)){
				phase->setTotalementPese(true);
				setNbPhasesPesees(getNbPhasesPesees() + 1);
			}

			getPhaseList()->append(phase);

			isOk = true;
		}
	}

	if (isOk == false)
	{
		// pour test mm 04.2016
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage("&AucunePhase",false);
		return isOk;
	}

	_nbPhases = noEnr;
	// mm initialisation par défaut seulement en cas de pesée par OF ou pesée en fabrication
	if  (getInterface()->getFonctionEnCours() != 2 )
		setCurrentPhaseIndex(0);
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadPhases Sortie return("<<isOk<<")" << endl;
	}

	return isOk;
}

//--------------------------------------------------------------
bool AdxData::loadComposants( const char* MatierefileName, int lcode)
{
	const int NUMOF		= 0;
	const int NUMPHA	= 1;
	const int COMCOD	= 2;
	const int COMLIB	= 3;
	const int QTEPRE	= 4;
	const int QTERES	= 5;
	const int QTECON	= 6;
	const int UNICOD	= 7;
	const int UNISTO	= 8;
	const int SERCOD	= 9;
	const int SERLIB	= 10;
	const int GESCOD	= 11;
	const int GESLIB	= 12;
	const int TITTHE	= 13;
	const int INFCOD	= 14;
	const int INFLIB	= 15;
	const int LANCOD	= 16;
	const int LANLIB	= 17;
	const int ISMFIC	= 18;
	const int NUMLIG	= 19;
	const int SEQBOM	= 20;
	const int DECPOI	= 21;
	const int ITMTOLPOS = 22; // 05.10 mm - tolérance +/- stoqués au niveau nomenclature
	const int ITMTOLNEG = 23; // 05.10 mm - tolérance +/- stoqués au niveau nomenclature
	const int QTEDISPO  = 24; // SMO : 19/08/2010 : quantite dispo pour pesee matiere
	const int QTEALL	= 25; // mm : qté allouée avant d'entrer dans la Cdp
	const int QTEPEC	= 26; // 93535 mm 10.2013
	const int REDMOD	= 27;
	
// a reactiver si besoin
//    const int QTEDOS	= 23;
// On vide la table composant avant de la reremplir
// mm 03.2013 - vrai seulement en cas de pesée par OF/Fabrication
// + 06.2013 mm 90456 - gestion du paramètre GLISMAT
	if ((getInterface()->getFonctionEnCours() != 2 ) ||
		((getInterface()->getFonctionEnCours() == 2 ) && (getChargementListMat() == 2 ) )||
		((getInterface()->getFonctionEnCours() == 2 ) && (getNbComposants_Art()== 0) && (getChargementListMat() == 1))) 
	{
		if(_composantList_Art != NULL)
		{
			_composantList_Art->empty();
			setNbComposants_Art(0);
		}
	}

	int noEnr = 0;
	int i;
	bool isOk = false;
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadComposants Entree" << endl;
	}

	AdxCsvFileReader MATfile( MatierefileName, FieldSeparator, Decimal);

	if( MATfile.ok()) 
	{
		MATfile.skipLinesBeginningWith( Comment);

		for( ; MATfile.ok() ; ++MATfile)	
		{
			AdxCsvLine line = *MATfile;

			noEnr++;

			if ((line.getNbOfFields() < 27)	| (line.getNbOfFields() > 28))
			{
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				char* message = new char[60];
				sprintf(message,"%s : %s = %d",
					IlvGetMessage(getInterface()->getDisplay(),"&ErrorX3ScalesMat.csv"),
					IlvGetMessage(getInterface()->getDisplay(),"&Rang"),
					noEnr); 
				getInterface()->envoieMessage(message,false);
				delete [] message;
				isOk = false;
				return isOk;
			}

			// il faut que le numero de l OF soit le numero de l'OF en cours
			// SMO : JUNE 10 2010 : STD-PR-OO1 : Pesee Matiere
			// ==> fonctionnement different en pesee matiere : pas de verification du Num OF
			if ((getInterface()->getFonctionEnCours()==1 ||  getInterface()->getFonctionEnCours()== 3)&&
				(strcmp(getStringUnicode(&line, NUMOF),getCurrentOrder()->getNumOF()) != 0))
			{
				isOk = false;
				return isOk;
			}
			else
			{
				AdxComposant* composant = new AdxComposant;
			
				composant->setComposant( getStringUnicode(&line, COMCOD));
				composant->setLibComposant( getStringUnicode(&line, COMLIB));
				composant->setQuantitePrevue( line.getDouble( QTEPRE)); 
				composant->setQuantiteRestante( line.getDouble( QTERES));
				composant->setQuantiteConsommee( line.getDouble( QTECON));
				composant->setUnite( getStringUnicode(&line, UNICOD));
				composant->setUniteStock( getStringUnicode(&line, UNISTO));
				composant->setCodeAServir( line.getLong( SERCOD));
				composant->setLibCodeAServir( getStringUnicode(&line, SERLIB));
				composant->setGestionStock( line.getLong( GESCOD));
				composant->setLibGestionStock( getStringUnicode(&line, GESLIB));
				composant->setTitreTheo( line.getDouble( TITTHE));
				composant->setStockInfZero( line.getLong( INFCOD));
				composant->setLibStockInfZero( getStringUnicode(&line, INFLIB));
				composant->setLancementSiRupture( line.getLong( LANCOD));
				composant->setLibLancementSiRupture( getStringUnicode(&line, LANLIB));
				composant->setFicheISM( getStringUnicode(&line, ISMFIC));
				composant->setNumeroLigne( line.getLong( NUMLIG));
				composant->setSequenceNomenclature( line.getLong( SEQBOM));
				composant->setDecimalePoids( line.getLong( DECPOI));
				composant->setToleranceArticlePositive( line.getDouble( ITMTOLPOS));
				composant->setToleranceArticleNegative( line.getDouble( ITMTOLNEG));
				composant->setQteDispoCompo( line.getDouble( QTEDISPO)); // SMO : 19/08/2010 
				composant->setQuantiteAlloueeRestante(line.getDouble( QTEALL)); 
               	composant->setQuantiteAlloueeDpOF(line.getDouble( QTEALL)); 
				composant->setQuantitePEC(line.getDouble(QTEPEC));

				if (line.getNbOfFields() == 28)
				{
       				composant->setRedMod( line.getLong( REDMOD));
			    }
				else
				{
					composant->setRedMod(1);
				}
					
				// composant->setQuantiteDose( line.getDouble( QTEDOS));
				composant->setQuantiteDose(0);
				char* format = new char[10];
				switch (composant->getDecimalePoids())
				{
					case 0:
						strcpy(format,"%12.0f");
						break;
					case 1:
						strcpy(format,"%12.1f");
						break;
					case 2:
						strcpy(format,"%12.2f");
						break;
					case 3:
						strcpy(format,"%12.3f");
						break;
					case 4:
						strcpy(format,"%12.4f");
						break;
					case 5:
						strcpy(format,"%12.5f");
						break;
					case 6:
						strcpy(format,"%12.6f");
						break;
					default:
						strcpy(format,"%12.3f");
						break;
				}
				composant->setFormat(format);
				delete [] format;
				composant->setPhase(line.getDouble( NUMPHA));
				composant->setNumOF(getStringUnicode(&line, NUMOF));

				// recherche de la phase correspondante
				// on ajoute le composant a la liste des composants de la phase
				i = getIndexPhase(composant->getPhase());
				if (i < getNbPhases())
				{
					getPhase(i)->getComposantList()->append(composant);
					getPhase(i)->setNbComposants(getPhase(i)->getNbComposants()+1);
					if (composant->getQuantiteRestante() == 0)
					{
						composant->setTotalementPese(true);
    					getPhase(i)->setNbComposantsPeses(getPhase(i)->getNbComposantsPeses()+1);
					}
					if ((composant->getCodeAServir() == 8) | (composant->getCodeAServir() == 9))
						  getPhase(i)->setRectif(1);

				}
				// on ajoute le composant à la liste des composants de AdxData en triant les composants
				// mm 03.2013 Performances - Si Pesée par matière, alimentation de la liste 
				// seulement en cas de LCODE = 049, afin de ne la charger qu'une seule fois
				// + 06.2013 mm 90456 - gestion du paramètre GLISMAT
				if  ((getInterface()->getFonctionEnCours() != 2 ) ||
					((getInterface()->getFonctionEnCours() == 2 ) && (getChargementListMat() == 2))||
					((getInterface()->getFonctionEnCours() == 2 ) && (lcode == 49)))
				{
					bool composantNonEnregistre = true;
					IlList* composantList_Art = getComposantList_Art();
					int n = 0;
					for (n = 0;n < getNbComposants_Art();n++)
					{					
						AdxComposant* composantCompare = (AdxComposant*)(*composantList_Art)[n];
						// on insere le composant avant celui compare si compare est superieur
						if (strcmp(composantCompare->getComposant(),composant->getComposant()) > 0)
						{
							composantList_Art->insert(composant,n);
							composantNonEnregistre = false;
							break;
						}
					}
					if (composantNonEnregistre)		// si non-insere on l'ajoute a la fin
						composantList_Art->append(composant);	
					setNbComposants_Art(getNbComposants_Art()+1);
					// on commence la liste des phases de cet article avec la phase de ce composant
					composant->getPhaseList_Art()->append(getPhase(getIndexPhase(composant->getPhase())));
					composant->setNbPhases_Art(composant->getNbPhases_Art() +1);
					// mise a jour de la table des phases du composant avec les autres phases ou ce composant existe deja
					for (int m = 0; m < n; m++)
					{
						AdxComposant* composantCmpPha = (AdxComposant*)(*composantList_Art)[m];
						if (strcmp(composantCmpPha->getComposant(),
								   composant->getComposant()) == 0)
						{
							// on ajoute au composant identique la phase du composant en cours
							composantCmpPha->getPhaseList_Art()->append(getPhase(getIndexPhase(composant->getPhase())));
							composantCmpPha->setNbPhases_Art(composantCmpPha->getNbPhases_Art() +1);
							// on ajoute au composant en cours la phase principale du composant identique
							composant->getPhaseList_Art()->append(getPhase(getIndexPhase(composantCmpPha->getPhase())));
							composant->setNbPhases_Art(composant->getNbPhases_Art() +1);	
						}
					
					}
				}
				isOk = true;
			}
		}
	}

	if (isOk == false)
	{
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage("&AucunComposant",false);
		return isOk;
	}

	
	if  (getInterface()->getFonctionEnCours() != 2 )
	{
		setCurrentComposantIndex(0);
		// 86892 mm 02.2013 - Pas de fiche ISM liée à l'article 
		/*if (strcmp ((_currentComposant = getCurrentPhase()->getComposant(0))->getFicheISM(),"")==0)
		{
			// si autre composant ds la même phase -> orienter sur celui là
			// si non, si autre composant dans l'OF -> orienter sur celui là
			// si non, pas d'autre composant que celui sans fiche ISM - > changer d'OF isOk = false;
			//int numPhase = _currentComposant->getPhase();
			//if (AdxPhase * phase->getNbComposants(numPhase)==0)
			//	isOk = false;
		}*/
	}
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadComposants Sortie return("<<isOk<<")" << endl;
	}
	
	return isOk;
}

//--------------------------------------------------------------
bool AdxData::loadLots( const char* LotfileName)
{
	const int COMCOD	= 0;
	const int LOT		= 1;
    const int SLO		= 2;
    const int EMP		= 3;
	const int WLIBEMP	= 4;
	const int QTEDIS	= 5;
	const int QTEALL	= 6;
	const int QTETOT	= 7;
    const int UNITE  	= 8;
	const int DATPER	= 9;
	const int STACOD	= 10;
	const int STALIB  	= 11;
	const int TITRE     = 12;
	const int CUVE		= 13;
	const int WLIBCUV 	= 14;
	const int VANNE		= 15;
	const int CHRONO	= 16;
	const int SEQUEN	= 17;
  	const int QTEREELDIS= 18;
	const int QTEINI 	= 19;
	const int LOTINVALIDE = 20;	// mm 09.2013

	AdxInterface* m_interface = getInterface();
	IlvBoolean err;
	int noEnr = 0;
	bool isOk = false;
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadLots Entree" << endl;
	}
	AdxCsvFileReader LOTfile( LotfileName, FieldSeparator, Decimal);
	double quantiteActiveAllouee = 0;

// quand le fichier n'est pas bon on vide la liste pour pas tout melanger
	if (_nbLots > 0)
		{
			for (int i = 0; i < _nbLots; i++)
			{
				delete (AdxLot*)(*_lotList)[i];
			}
			_nbLots = 0;
		}
	getInterface()->setPeseeEnCuve(false);

	if( LOTfile.ok()) 
	{
		LOTfile.skipLinesBeginningWith( Comment);
	
		_lotList->empty();
		getCurrentComposant()->setQuantiteAllouee(0);
		getCurrentComposant()->setQuantiteDisponible(0);
		for( ; LOTfile.ok() ; ++LOTfile)	
		{
			AdxCsvLine line = *LOTfile;

			noEnr++;
			const char* composant = getStringUnicode(&line, COMCOD);

			if (line.getNbOfFields() != 21
				|| strcmp( getCurrentComposant()->getComposant(), composant) != 0)	
			{
				getInterface()->getMessage()->setPanneauAppelant(NULL);	
				getInterface()->envoieMessage("&Aucunlot",false);	// mm 01.09 - ancien message : "&ErrorX3ScalesSto.csv" +"&Rang"
				isOk = false;
				return isOk;
			}
			
			AdxLot* lot = new AdxLot;
		
			lot->setLot( getStringUnicode(&line, LOT));
			lot->setSlo( getStringUnicode(&line, SLO));
            lot->setEmplacement( getStringUnicode(&line, EMP));
		    lot->setLibEmplacement( getStringUnicode(&line, EMP));
			lot->setQuantiteDisponible( line.getDouble( QTEDIS));
			lot->setQuantiteAllouee( line.getDouble( QTEALL));
            lot->setQuantiteTotale( line.getDouble( QTETOT));
			lot->setUnite( getStringUnicode(&line, UNITE));
			lot->setDatePeremption( new AdxDate( getStringUnicode(&line, DATPER), YYYYMMDD));
			lot->setStatut( getStringUnicode(&line, STACOD));
			lot->setLibStatut(getStringUnicode(&line, STALIB));
			lot->setTitre( line.getDouble( TITRE));
			lot->setCuve( getStringUnicode(&line, CUVE));
			lot->setLibSaisieCuve( getStringUnicode(&line, CUVE));
			lot->setVanne( getStringUnicode(&line, VANNE));
			lot->setChrono( line.getDouble( CHRONO));
			lot->setSequence( line.getDouble( SEQUEN));
			lot->setQuantiteReelDispo( line.getDouble( QTEREELDIS));
			lot->setQuantiteInitiale( line.getDouble( QTEINI));

			getCurrentComposant()->setQuantiteAllouee(getCurrentComposant()->getQuantiteAllouee() 
					+ lot->getQuantiteAllouee());
			getCurrentComposant()->setQuantiteDisponible(getCurrentComposant()->getQuantiteDisponible() 
					+ lot->getQuantiteDisponible());
			if (getCurrentComposant()->getGestionStock() == 3)
				quantiteActiveAllouee += (lot->getQuantiteAllouee() * lot->getTitre()/100);
			else
				quantiteActiveAllouee += lot->getQuantiteAllouee();
			// APCPRD-2438 09.2013 mm
			getCurrentComposant()->setLotAlloueInvalide( line.getDouble( LOTINVALIDE));

			getLotList()->append(lot);
			// on pourra a acceder au cuve vanne des lors qu'une ligne de stock 
			// comportera de ces informations
			if (strcmp (lot->getCuve(),"") != 0
				|| strcmp (lot->getVanne(),"") != 0)
				getInterface()->setPeseeEnCuve(true);

			isOk = true;
		}
	}
	// SR 03.12 APCPRD-990 si pas d'allocations redescendue
	if (getCurrentComposant()->getQuantiteAllouee() == 0)
		getCurrentComposant()->setQuantiteAlloueeDpOF(0);
	if (isOk == false)
	{
		m_interface->getMessage()->setPanneauAppelant(NULL);
		m_interface->envoieMessage("&AucunLot",false);
		return isOk;
	}
	if (quantiteActiveAllouee == 0)
	{
		_nbLots = noEnr;
		setCurrentLotIndex(0);
		return isOk;
	}


//	double ecartTolere = pow(10,(-getCurrentComposant()->getDecimalePoids()));
	double ecartTolere; 
	double ecartCalcule; 
	bool ecartDecele = false;

// si pesée multi article en cours
	if (m_interface->getPesee_OF()->getEnPeseeMultiArticle() == true)
	{
		//107040 mm 11.2015 - some customers work without using tolerance
		if (getCurrentComposant()->getToleranceArticleNegative())
		{
			ecartTolere = getCurrentComposant()->getQuantiteTheorique() 
			* (getCurrentComposant()->getToleranceArticleNegative() / 100);
			if (getCurrentComposant()->getGestionStock() == 3)
			{
				ecartCalcule = getCurrentComposant()->getQuantiteTheorique()
					- (quantiteActiveAllouee / getCurrentComposant()->getTitreTheo() * 100);

				if (fabs(getCurrentComposant()->getQuantiteTheorique()
					- (quantiteActiveAllouee / getCurrentComposant()->getTitreTheo() * 100)) > ecartTolere)
					ecartDecele = true;
			}
			else
			{
				if (fabs(getCurrentComposant()->getQuantiteTheorique()
					- quantiteActiveAllouee) > ecartTolere)
					ecartDecele = true;
			}
		}
	}
	else
	{	
	// on ne teste pas sur la quantite nomenclature mais la qte affichee car calculee pour titre et QSP
		if (m_interface->getPanneauAppelant() == (AdxGadgetContainer*) m_interface->getChoix_OF())
		{
			//107040 mm 11.2015 - some customers work without using tolerance
			if (getCurrentComposant()->getToleranceArticleNegative())
			{
				ecartTolere = m_interface->getChoix_OF()->getAffQuantiteAPeser()->getFloatValue(err) 
				* (getCurrentComposant()->getToleranceArticleNegative() / 100);
				if (getCurrentComposant()->getGestionStock() == 3)
				{
					if (fabs(m_interface->getChoix_OF()->getAffQuantiteAPeser()->getFloatValue(err)
						- ((float)quantiteActiveAllouee / getCurrentComposant()->getTitreTheo() * 100)) > ecartTolere)
						ecartDecele = true;
				}
				else
				{
					if (fabs(m_interface->getChoix_OF()->getAffQuantiteAPeser()->getFloatValue(err) 
						- quantiteActiveAllouee) > ecartTolere)
						ecartDecele = true;
				}
			}
		}

		if (m_interface->getPanneauAppelant() == (AdxGadgetContainer*) m_interface->getPesee_OF())
		{
			//107040 mm 11.2015 - some customers work without using tolerance
			if (getCurrentComposant()->getToleranceArticleNegative())
			{
				ecartTolere = m_interface->getPesee_OF()->getAffTotalAPeser()->getFloatValue(err) 
				* (getCurrentComposant()->getToleranceArticleNegative() / 100);
				if (getCurrentComposant()->getGestionStock() == 3)
				{
					if (fabs(m_interface->getPesee_OF()->getAffTotalAPeser()->getFloatValue(err) 
						- ((float)quantiteActiveAllouee / getCurrentComposant()->getTitreTheo() * 100)) > ecartTolere)
						ecartDecele = true;
				}
				else
				{
					if (fabs(m_interface->getPesee_OF()->getAffTotalAPeser()->getFloatValue(err) 
						- quantiteActiveAllouee) > ecartTolere)
						ecartDecele = true;
				}
			}
		}
	}
	// sr 12.11 APCPRD-722
	if (m_interface->getPesee_OF()->getEnPeseeMultiArticle() == true & getAllocationAutoCode() == 2)
	{
		ecartDecele = false;
	}

	// 121455 mm 02.2017 - It's allowed to allocate only a part of need quantity from Pese_OF screen
	if ((ecartDecele) && (m_interface->getPanneauAppelant() == (AdxGadgetContainer*) m_interface->getChoix_OF()))
	{
		m_interface->getMessage()->setPanneauAppelant(NULL);
		m_interface->envoieMessage("&QuantiteAlloueeInsuffisante",false);
	
	}

	_nbLots = noEnr;
	setCurrentLotIndex(0);
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadLots Sortie return("<<isOk<<")" << endl;
	}
	return isOk;
}


//--------------------------------------------------------------
bool AdxData::loadBalances( const char* BalancefileName)
{
	
	const int BALCOD	= 0;
	const int BALLIB	= 1;
	const int PORT  	= 2;
	const int PILOTE	= 3;
	const int NBENT 	= 4;
	const int NBDEC 	= 5;
	const int SEPAR 	= 6;
	const int SEPLIB	= 7;
	const int CONSIG	= 8;
	const int UNITE 	= 9;
	const int PORMIN	= 10;
	const int PORMAX	= 11;
	const int TARMAX  	= 12;
	const int TOLER 	= 13;
	const int CODCBT 	= 14;
	const int LIBCBT 	= 15;
	const int GUICBT 	= 16;
	const int NBJOUR 	= 17;
	const int NBPESE	= 18;
	const int AVACOD 	= 19;
	const int AVALIB 	= 20;
	const int LASCBT 	= 21;
	const int NBPCBT 	= 22;
	const int CBTLBE	= 23;
	const int VITESS 	= 24;
	const int PARITE 	= 25;
	const int STOBIT 	= 26;
	const int FORMAT	= 27;
	const int TEMPO 	= 28;
	const int SERNUM    = 29;
	const int KEYRAZSCA = 30; 
	const int KEYTARSCA = 31;

	int noEnr = 0;
	_nbBalancesAEtalonner = 0;
	bool isOk = false;
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadBalances Entree" << endl;
	}

	AdxCsvFileReader SLEfile( BalancefileName, FieldSeparator, Decimal);

	if( SLEfile.ok()) 
	{
		SLEfile.skipLinesBeginningWith( Comment);
		if (_nbBalances > 0)
		{
			for (int i = 0; i < _nbBalances; i++)
			{
				delete (AdxBalance*)(*_balanceList)[i];
			}

		}
		_nbBalances = 0;
		_balanceList->empty();

		for( ; SLEfile.ok() ; ++SLEfile)	
		{
			AdxCsvLine line = *SLEfile;

			noEnr++;

			if (line.getNbOfFields() != 32)	
			{
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				char* message = new char[60];
				sprintf(message,"%s : %s = %d",
					IlvGetMessage(getInterface()->getDisplay(),"&ErrorX3ScalesSle.csv"),
					IlvGetMessage(getInterface()->getDisplay(),"&Rang"),
					noEnr); 
				getInterface()->envoieMessage(message,false);
				delete [] message;
				isOk = false;
				return isOk;
			}
			
			AdxBalance* balance = new AdxBalance;

		
			balance->setBalance( getStringUnicode(&line, BALCOD));
			balance->setLibBalance( getStringUnicode(&line, BALLIB));
			balance->setPort( line.getLong( PORT));
			balance->setPilote( getStringUnicode(&line, PILOTE));
			balance->setNbEntiers( line.getLong( NBENT));
			balance->setNbDecimales( line.getLong( NBDEC));
			balance->setSeparateur( getStringUnicode(&line, SEPAR));
			balance->setLibSeparateur( getStringUnicode(&line, SEPLIB));
			// sr 01.03 récupération correcte du séparateur
			// bien qu'il semble que dans la DLL on assume que le point
			// est le séparateur même si dans balance d'est la , !!!
			if (balance->getLibSeparateur() == "V")
			{
				balance->setLibSeparateur(",");
			}
			if ( line.getDouble( CONSIG) == 1)
				balance->setConsigne(false);
			else
				balance->setConsigne(true);
			balance->setUnite( getStringUnicode(&line, UNITE));
			balance->setPorteeMini( line.getDouble( PORMIN));
			balance->setPorteeMaxi( line.getDouble( PORMAX));
			balance->setTareMaxi( line.getDouble( TARMAX));
			balance->setTolerance( line.getDouble( TOLER));
			balance->setCodeCalibrage( line.getLong( CODCBT));
			balance->setLibCalibrage( getStringUnicode(&line, LIBCBT));
			balance->setGuideCalibrage( getStringUnicode(&line, GUICBT));
			balance->setNbJours( line.getLong( NBJOUR));
			balance->setNbPesees( line.getLong( NBPESE));
			balance->setCodeDispo( line.getLong( AVACOD));
			balance->setLibCodeDispo( getStringUnicode(&line, AVALIB));
			balance->setDateDernierCalibrage(
				new AdxDate( getStringUnicode(&line, LASCBT), YYYYMMDD));
			balance->setNbPeseesCalibrage( line.getLong( NBPCBT));
			balance->setEtiquetteCalibrage( getStringUnicode(&line, CBTLBE));
			balance->setVitesse(line.getLong( VITESS));
			balance->setParite(line.getLong( PARITE) - 1);
			balance->setStopBit(line.getLong( STOBIT));
			balance->setFormat(line.getLong( FORMAT));
			balance->setTempo( line.getLong( TEMPO));
			if(balance->getTempo() == 0)
			{
				// GBE le cas zero est maintenant un cas voulu !!!
		//		balance->setTempo(25);
			}
			balance->setSerialNumber( getStringUnicode(&line, SERNUM));

			// mm 09.2016
			// Get Commande number of RAZ and Tare Functions - only for MTSICS Driver
			if (strcmp ( balance->getPilote(),"SIC")== 0)
			{
				if (strcmp (getStringUnicode(&line ,KEYRAZSCA),"")!=0)
					balance->setKeyRazSca( getStringUnicode(&line,KEYRAZSCA));
				else
					balance->setKeyRazSca("2");
				// Commande number of Tare Function
				if (strcmp (getStringUnicode(&line ,KEYTARSCA),"")!=0)
					balance->setKeyTarSca( getStringUnicode(&line,KEYTARSCA));
				else
					balance->setKeyTarSca("3");
			}


			// comptage balances à étalonner
			long nbJours = (long) (_dateJour->getAbsolute()
				- balance->getDateDernierCalibrage()->getAbsolute());
			if (((balance->getCodeCalibrage() == 2 || balance->getCodeCalibrage() == 4) 
					&& (balance->getNbJours() <= nbJours))	// APCPRD 2452 - mm 10.12 - <= au lieu de <
				|| ((balance->getCodeCalibrage() == 3 || balance->getCodeCalibrage() == 4) 
					&& (balance->getNbPesees() < balance->getNbPeseesCalibrage()))
				|| ((balance->getCodeCalibrage() == 5) 
					&& (balance->getNbPeseesCalibrage() > 0)))
			{
				_nbBalancesAEtalonner++;
				balance->setEtalonnee(false);
			}
			else
			{
				balance->setEtalonnee(true);
			}

// les balances a ne jamais etalonner sont en fin de liste pour que les autres apparaissent
// dans les premiers boutons dans l'ecran choix_Balance
			if (balance->getCodeCalibrage() == 1)
				getBalanceList()->append(balance);
			else
				getBalanceList()->insert(balance);

			isOk = true;
		}
	}

	if (isOk == false)
	{
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage("&AucuneBalance",false);
		return isOk;
	}

	_nbBalances = noEnr;
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadBalances Sortie return("<<isOk<<")" << endl;
	}
	return isOk;
}


//--------------------------------------------------------------
bool AdxData::loadFichesISM( const char* FicheISMfileName)
{
	
	const int ISMCOD	= 0;
	const int LOTSEV	= 1;
	const int LOSLIB  	= 2;
	const int PLACTL	= 3;
	const int PLCLIB 	= 4;
//	const int QLYCTL 	= 5;
//	const int QLCLIB 	= 6;
//	const int ITMTOLPOS = 5;
//	const int ITMTOLNEG = 6;	// 06.07 mm - Differenciation tolerance +/-
	const int PCK   	= 5;
	const int PCKLIB 	= 6;
  	const int CLECTNAUT	= 7;
    const int WEIMOD   	= 8;
	const int WEMLIB 	= 9;
	const int OBL		= 10;	// 06.07 mm - Forcer la lecture d'une icone
	const int PCN1  	= 11;
	const int PICTO1	= 12;
	const int PCN2  	= 13;
	const int PICTO2 	= 14;
	const int PCN3   	= 15;
	const int PICTO3 	= 16;
	const int PCN4  	= 17;
	const int PICTO4	= 18;
	const int PCN5  	= 19;
	const int PICTO5	= 20;
	const int PCN6  	= 21;
	const int PICTO6 	= 22;
	const int PCN7   	= 23;
	const int PICTO7 	= 24;
	const int PCN8  	= 25;
	const int PICTO8	= 26;
	const int TXC1  	= 27;
	const int PICTO9	= 28;
	const int TXC2  	= 29;
	const int PICT10 	= 30;
	const int TXC3   	= 31;
	const int PICT11 	= 32;
	const int TXC4  	= 33;
	const int PICT12	= 34;
	const int LBECTS	= 35;
	const int SVRITM    = 36;		// mm 08.11 - Pesée multi-article
    const int REDMAN	= 37;	

	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadFichesISM Entree" << endl;
	}

	int noEnr = 0;
	bool isOk = false;
	AdxCsvFileReader HSHfile( FicheISMfileName, FieldSeparator, Decimal);

	if( HSHfile.ok()) 
	{
		HSHfile.skipLinesBeginningWith( Comment);
		if (_nbFichesISM > 0)
		{
			for (int i = 0; i < _nbFichesISM; i++)
			{
				delete (AdxFicheISM*)(*_ficheISMList)[i];
			}

		}
		_nbFichesISM = 0;
		_ficheISMList->empty();

		for( ; HSHfile.ok() ; ++HSHfile)	
		{
			AdxCsvLine line = *HSHfile;

			noEnr++;

			if ((line.getNbOfFields() < 37) | (line.getNbOfFields() > 39))
			{
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				char* message = new char[60];
				sprintf(message,"%s : %s = %d",
					IlvGetMessage(getInterface()->getDisplay(),"&ErrorX3ScalesHsh.csv"),
					IlvGetMessage(getInterface()->getDisplay(),"&Rang"),
					noEnr); 
				getInterface()->envoieMessage(message,false);
				delete [] message;
				isOk = false;
				return isOk;
			}
			
			AdxFicheISM* ficheISM = new AdxFicheISM;
		
			ficheISM->setFicheISM( getStringUnicode(&line, ISMCOD));
			ficheISM->setMelangeLotCode( line.getLong( LOTSEV));
			ficheISM->setMelangeLotLib( getStringUnicode(&line, LOSLIB));
			ficheISM->setControlePeseurCode( line.getLong( PLACTL));
			ficheISM->setControlePeseurLib( getStringUnicode(&line, PLCLIB));
//			ficheISM->setControleQualiteCode( line.getLong( QLYCTL));
//			ficheISM->setControleQualiteLib( getStringUnicode(&line, QLCLIB));
			ficheISM->setCodeEmballage( line.getLong( PCK));
			ficheISM->setCodeEmballageLib( getStringUnicode(&line, PCKLIB));
            ficheISM->setSoldeEmballage( line.getDouble( CLECTNAUT));			
            ficheISM->setModePeseeCode( line.getLong( WEIMOD));
			ficheISM->setModePeseeLib( getStringUnicode(&line, WEMLIB));
			ficheISM->setMessageObligatoire( line.getLong(OBL));

			if( strcmp( getStringUnicode(&line, PCN1), "") != 0)
			{
				ficheISM->setPrecaution1( getStringUnicode(&line, PCN1));
			}
			if( strcmp( getStringUnicode(&line, PICTO1), "") != 0)
			{
					ficheISM->setPictogramme1( getStringUnicode(&line, PICTO1));
			}
			if( strcmp( getStringUnicode(&line, PCN2), "") != 0)
			{
				ficheISM->setPrecaution2( getStringUnicode(&line, PCN2));
			}
			if( strcmp( getStringUnicode(&line, PICTO2), "") != 0)
			{
				ficheISM->setPictogramme2( getStringUnicode(&line, PICTO2));
			}
			if( strcmp( getStringUnicode(&line, PCN3), "") != 0)
			{
				ficheISM->setPrecaution3( getStringUnicode(&line, PCN3));
			}
			if( strcmp( getStringUnicode(&line, PICTO3), "") != 0)
			{
				ficheISM->setPictogramme3( getStringUnicode(&line, PICTO3));
			}
			if( strcmp( getStringUnicode(&line, PCN4), "") != 0)
			{
				ficheISM->setPrecaution4( getStringUnicode(&line, PCN4));
			}
			if( strcmp( getStringUnicode(&line, PICTO4), "") != 0)
			{
				ficheISM->setPictogramme4( getStringUnicode(&line, PICTO4));
			}
			if( strcmp( getStringUnicode(&line, PCN5), "") != 0)
			{
				ficheISM->setPrecaution5( getStringUnicode(&line, PCN5));
			}
			if( strcmp( getStringUnicode(&line, PICTO5), "") != 0)
			{
				ficheISM->setPictogramme5( getStringUnicode(&line, PICTO5));
			}
			if( strcmp( getStringUnicode(&line, PCN6), "") != 0)
			{
				ficheISM->setPrecaution6( getStringUnicode(&line, PCN6));
			}
			if( strcmp( getStringUnicode(&line, PICTO6), "") != 0)
			{
				ficheISM->setPictogramme6( getStringUnicode(&line, PICTO6));
			}
			if( strcmp( getStringUnicode(&line, PCN7), "") != 0)
			{
				ficheISM->setPrecaution7( getStringUnicode(&line, PCN7));
			}
			if( strcmp( getStringUnicode(&line, PICTO7), "") != 0)
			{
				ficheISM->setPictogramme7( getStringUnicode(&line, PICTO7));
			}
			if( strcmp( getStringUnicode(&line, PCN8), "") != 0)
			{
				ficheISM->setPrecaution8( getStringUnicode(&line, PCN8));
			}
			if( strcmp( getStringUnicode(&line, PICTO8), "") != 0)
			{
				ficheISM->setPictogramme8( getStringUnicode(&line, PICTO8));
			}
			if( strcmp( getStringUnicode(&line, TXC1), "") != 0)
			{
				ficheISM->setCodeToxicite1( getStringUnicode(&line, TXC1));
			}
			if( strcmp( getStringUnicode(&line, PICTO9), "") != 0)
			{
				ficheISM->setPictogramme9( getStringUnicode(&line, PICTO9));
			}
			if( strcmp( getStringUnicode(&line, TXC2), "") != 0)
			{
				ficheISM->setCodeToxicite2( getStringUnicode(&line, TXC2));
			}
			if( strcmp( getStringUnicode(&line, PICT10), "") != 0)
			{
				ficheISM->setPictogramme10( getStringUnicode(&line, PICT10));
			}
			if( strcmp( getStringUnicode(&line, TXC3), "") != 0)
			{
				ficheISM->setCodeToxicite3( getStringUnicode(&line, TXC3));
			}
			if( strcmp( getStringUnicode(&line, PICT11), "") != 0)
			{
				ficheISM->setPictogramme11( getStringUnicode(&line, PICT11));
			}
			if( strcmp( getStringUnicode(&line, TXC4), "") != 0)
			{
				ficheISM->setCodeToxicite4( getStringUnicode(&line, TXC4));
			}
			if( strcmp( getStringUnicode(&line, PICT12), "") != 0)
			{
				ficheISM->setPictogramme12( getStringUnicode(&line, PICT12));
			}
			if( strcmp( getStringUnicode(&line, LBECTS), "") != 0)
			{
				ficheISM->setContenuEtiquette( getStringUnicode(&line, LBECTS));
			}
			if( strcmp( getStringUnicode(&line, SVRITM), "") != 0)
			{
				ficheISM->setPeseeMultiArticle( line.getLong(SVRITM));
			}
            if (line.getNbOfFields() == 38)	
            {
                    ficheISM->setRedressementManuel( line.getLong( REDMAN));
            }
            else
            {
       			ficheISM->setRedressementManuel(1);
            }
			getFicheISMList()->append(ficheISM);

			isOk = true;
		}
	}

	if (isOk == false)
	{
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage("&AucuneFicheISM",false);
		return isOk;
	}

	_nbFichesISM = noEnr;
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadFichesISM Sortie return("<<isOk<<")" << endl;
	}


	return isOk;
}

//--------------------------------------------------------------
bool AdxData::loadFichesISMRecipient( const char* FicheISMRecipientfileName)
{
	
	const int ISMCOD	= 0;
	const int CTNCOD	= 1;
	const int WEU	  	= 2;
	const int WEIMAX	= 3;
	const int CTNDES	= 4;
	const int CTNTYP	= 5;
	const int CTNTYD	= 6;
	const int CTNTHETAR	= 7;
	const int CTNTOLTAR = 8;
//	const int CTNWEU	= 8;
	const int CTNUGD	= 9;
	const int CTNLBEFMT	= 10;
	const int CTNMODTAR = 11;	//04.07 gestion d'une tare modifiable 
	const int CTNSAIMAN	= 12;	//10.07 saisie poids

	int noEnr = 0;
	bool isOk = false;
	AdxCsvFileReader HSRfile(  FicheISMRecipientfileName, FieldSeparator, Decimal);
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadFichesISMRecipient Entree" << endl;
	}

	if( HSRfile.ok()) 
	{
		HSRfile.skipLinesBeginningWith( Comment);
		if (_nbFichesISMRecipient > 0)
		{
			for (int i = 0; i < _nbFichesISMRecipient; i++)
			{
				delete (AdxFicheISMRecipient*)(*_ficheISMRecipientList)[i];
			}

		}
		_nbFichesISMRecipient = 0;
		_ficheISMRecipientList->empty();

		for( ; HSRfile.ok() ; ++HSRfile)	
		{
			AdxCsvLine line = *HSRfile;

			noEnr++;

			if (line.getNbOfFields() != 13)	
			{
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				char* message = new char[60];
				sprintf(message,"%s : %s = %d",
					IlvGetMessage(getInterface()->getDisplay(),"&ErrorX3ScalesCnt.csv"),
					IlvGetMessage(getInterface()->getDisplay(),"&Rang"),
					noEnr); 
				getInterface()->envoieMessage(message,false);
				delete [] message;
				isOk = false;
				return isOk;
			}
			
			AdxFicheISMRecipient* ficheISMRecipient = new AdxFicheISMRecipient;
		
			ficheISMRecipient->setFicheISMRecipient( getStringUnicode(&line, ISMCOD));
			ficheISMRecipient->setRecipient( getStringUnicode(&line, CTNCOD));
			ficheISMRecipient->setUnitePoids( getStringUnicode(&line, WEU));
			ficheISMRecipient->setPoidsMaxi( line.getDouble( WEIMAX));

			ficheISMRecipient->setLibRecipient( getStringUnicode(&line, CTNDES));
			ficheISMRecipient->setTypeRecipient( line.getLong( CTNTYP));
			ficheISMRecipient->setLibTypeRecipient( getStringUnicode(&line, CTNTYD));
			ficheISMRecipient->setTareTheo( line.getDouble( CTNTHETAR));
			ficheISMRecipient->setToleranceTare( line.getDouble( CTNTOLTAR));
//			ficheISMRecipient->setUnite2( getStringUnicode(&line, CTNWEU));
			ficheISMRecipient->setGuideOperateur( getStringUnicode(&line, CTNUGD));
			ficheISMRecipient->setFormatEtiquette( getStringUnicode(&line, CTNLBEFMT));
			ficheISMRecipient->setTareModifiable(line.getLong(CTNMODTAR));
			ficheISMRecipient->setSaisiePoids(line.getLong(CTNSAIMAN));	// 10.07 pesee en mode degrade selon la valeur de saisie Poids

			getFicheISMRecipientList()->append(ficheISMRecipient);

			isOk = true;
		}
	}

	if (isOk == false)
	{
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage("&AucuneFicheISMRecipient",false);
		return isOk;
	}

	_nbFichesISMRecipient = noEnr;
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadFichesISMRecipient Sortie return("<<isOk<<")" << endl;
	}
	return isOk;
}

//--------------------------------------------------------------
bool AdxData::loadUnits( const char* UnitfileName)
{
	const int UNITE1	= 0;
	const int UNITE2	= 1;
	const int COEFF		= 2;

	int noEnr = 0;
	bool isOk = false;
	AdxCsvFileReader TCOfile( UnitfileName, FieldSeparator, Decimal);
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadUnits Entree" << endl;
	}


	if( TCOfile.ok()) 
	{
		TCOfile.skipLinesBeginningWith( Comment);
		if (_nbUnits > 0)
		{
			for (int i = 0; i < _nbUnits; i++)
			{
				delete (AdxUnit*)(*_unitList)[i];
			}

		}
		_nbUnits = 0;
		_unitList->empty();
		for( ; TCOfile.ok() ; ++TCOfile)	
		{
			AdxCsvLine line = *TCOfile;

			noEnr++;

			if (line.getNbOfFields() != 3)	
			{
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				char* message = new char[60];
				sprintf(message,"%s : %s = %d",
					IlvGetMessage(getInterface()->getDisplay(),"&ErrorX3ScalesTco.csv"),
					IlvGetMessage(getInterface()->getDisplay(),"&Rang"),
					noEnr); 
				getInterface()->envoieMessage(message,false);
				delete [] message;
				printf("Error X3ScalesTco.csv");
				isOk = false;
				return isOk;
			}
			
			AdxUnit* unit = new AdxUnit;
		
			unit->setUnite1( getStringUnicode(&line, UNITE1));
			unit->setUnite2( getStringUnicode(&line, UNITE2));
			unit->setCoefficient( line.getDouble( COEFF));

			getUnitList()->append(unit);

			isOk = true;
		}
	}

	if (isOk == false)
	{
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage("&AucuneUnite",false);
		return isOk;
	}

	_nbUnits = noEnr;
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadUnits Sortie return("<<isOk<<")" << endl;
	}
	return isOk;
}

//--------------------------------------------------------------
bool AdxData::loadEtalons( const char* EtalonfileName)
{
	const int NUMETALON	  = 0;
	const int LIBETALON	  = 1;
	const int NUMLIG	  = 2;
	const int POIDS 	  = 3;
	const int UNITE  	  = 4;
	const int NBPESEES	  = 5;
	const int TYPPESEE	  = 6;
	const int LIBTYPPESEE = 7;
	const int TOLERANCE   = 8;
	const int DECPOIDS    = 9;

	int   noEnr		  = 0;
	int   noEnrLignes = 0;
	bool  isOk		  = true;
	char* memo_etalon = new char[9];

	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadEtalons Entree" << endl;
	}

	AdxCsvFileReader CGDfile( EtalonfileName, FieldSeparator, Decimal);

	if( CGDfile.ok()) 
	{
		CGDfile.skipLinesBeginningWith( Comment);
		if (_nbEtalons > 0)
		{
			for (int i = 0; i < _nbEtalons; i++)
			{
				delete (AdxEtalon*)(*_etalonList)[i];
			}
		}

		_nbEtalons		= 0;
		_etalonList->empty();

		for( ; CGDfile.ok() ; ++CGDfile)	
		{
			AdxCsvLine line = *CGDfile;
			noEnrLignes ++;

			if (line.getNbOfFields() != 10)	
			{
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				char* message = new char[60];
				sprintf(message,"%s : %s = %d",
					IlvGetMessage(getInterface()->getDisplay(),"&ErrorX3ScalesCgd.csv"),
					IlvGetMessage(getInterface()->getDisplay(),"&Rang"),
					noEnrLignes); 
				getInterface()->envoieMessage(message,false);
				delete [] message;
				isOk = false;
				return isOk;
			}
			if ((memo_etalon == NULL) || strcmp(getStringUnicode(&line, NUMETALON),memo_etalon) != 0) 
			{
				AdxEtalon* etalon = new AdxEtalon;
				noEnr ++;
				etalon->setEtalon( getStringUnicode(&line, NUMETALON));
				sprintf(memo_etalon,"%s",etalon->getEtalon());
				etalon->setLibEtalon( getStringUnicode(&line, LIBETALON));
				etalon->setNbLignesValidees(0);
				etalon->setNbLignesEffectuees(0);
				etalon->setTotalementEtalonne(false);
				getEtalonList()->append(etalon);
				setCurrentEtalonIndex(getEtalonList()->length() - 1);
			}


			AdxEtalonLigne* etalonLigne = new AdxEtalonLigne;
			etalonLigne->setEtalon(getCurrentEtalon());
			etalonLigne->setLigne( line.getLong( NUMLIG));
			etalonLigne->setPoids( line.getDouble( POIDS)); 
			etalonLigne->setUnite( getStringUnicode(&line, UNITE));
			etalonLigne->setNbPesees( line.getLong( NBPESEES));
			etalonLigne->setTypPesee( line.getLong( TYPPESEE));
			etalonLigne->setLibTypPesee( getStringUnicode(&line, LIBTYPPESEE));
			etalonLigne->setTolerance( line.getDouble( TOLERANCE));
			etalonLigne->setEcartMaxi(line.getDouble(POIDS) * (line.getDouble(TOLERANCE)/100));
			etalonLigne->setPeseeEffectuee(0);
			etalonLigne->setPeseeValidee(0);
			etalonLigne->setPoidsPese(0);
			etalonLigne->setNbPeseesEffectuees(0);
			etalonLigne->setNbPeseesOk(0);
			etalonLigne->setDecimalePoids( line.getLong( DECPOIDS));
			if (etalonLigne->getNbPesees() != 0)
			{
				etalonLigne->_arrPoidsPese = new double[etalonLigne->getNbPesees()];
				for (int i =0; i<etalonLigne->getNbPesees();i++)
				{
					etalonLigne->setArrPoidsPese(i,0);
				}
			}

			char* format = new char[10];
			switch (etalonLigne->getDecimalePoids())
				{
					case 0:
						strcpy(format,"%12.0f");
						break;
					case 1:
						strcpy(format,"%12.1f");
						break;
					case 2:
						strcpy(format,"%12.2f");
						break;
					case 3:
						strcpy(format,"%12.3f");
						break;
					case 4:
						strcpy(format,"%12.4f");
						break;
					case 5:
						strcpy(format,"%12.5f");
						break;
					case 6:
						strcpy(format,"%12.6f");
						break;
					default:
						strcpy(format,"%12.3f");
						break;
				}
				etalonLigne->setFormat(format);
				delete [] format;

			getCurrentEtalon()->getEtalonLigneList()->append(etalonLigne);
			getCurrentEtalon()->setNbLignes(getCurrentEtalon()->getNbLignes() + 1);

			isOk = true;
		}
	}
/*
	if (isOk == false)
	{
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage("&Aucunguide",false);
		isOk = true;
	}
*/
	_nbEtalons = noEnr;	
	delete memo_etalon;
	// GBE 20/12/12 Ajout Trace pour les échanges avec X3
	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadEtalons Sortie return("<<isOk<<")" << endl;
	}
	return isOk;
}

//--------------------------------------------------------------
//X3-67237: Added below section to load the User ID
bool AdxData::loadUserID( const char* UserIDfileName)
{
	const int USERFLD	  = 0;

	int   noUidLignes = 0;
	bool  isOk		  = true;


	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "loadUserID Start" << endl;
	}

	AdxCsvFileReader UIDfile( UserIDfileName, FieldSeparator, Decimal);

	if( UIDfile.ok()) 
	{
		for( ; UIDfile.ok() ; ++UIDfile)	
		{
			AdxCsvLine line = *UIDfile;
			noUidLignes ++;

			if (line.getNbOfFields() != 1)	
			{
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				char* message = new char[60];
				sprintf(message,"%s : %s = %d",
					IlvGetMessage(getInterface()->getDisplay(),"&ErrorX3ScalesUid.csv"),
					IlvGetMessage(getInterface()->getDisplay(),"&Rang"),
					noUidLignes); 
				getInterface()->envoieMessage(message,false);
				delete [] message;
				isOk = false;
			}
			else
			{
				setUserID(getStringUnicode(&line, USERFLD));

				isOk = true;
			}
		}
	}

	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "Load UserID Finished ("<<isOk<<")" << endl;
	}

	return isOk;
}




//--------------------------------------------------------------
// renvoie le poidsAConvertir exprime dans l'uniteDepart, converti dans l'unite d arrivee
double AdxData::convertir(double poidsAConvertir,
						  const char* uniteDepart,
						  const char* uniteArrivee)
{
	// mm 12.09 - passage en majuscule des unités
	char* wunite1 = majuscule(uniteDepart);
	char* wunite2 = majuscule(uniteArrivee);

	if (strcmp(wunite1, wunite2) == 0)
		return poidsAConvertir;
	double poidsConverti;
	double coefficient = 1;

     // recherche du coefficient
	AdxUnit* tabUnit;
	IlList* unitList = getUnitList();
	int i = 0;
	for (i = 0; i < _nbUnits; i++) 
	{
		tabUnit = (AdxUnit*)(*unitList)[i];
		if (strcmp(wunite1,tabUnit->getUnite1()) == 0 &&
		strcmp(wunite2,tabUnit->getUnite2()) == 0)
		{
			coefficient = tabUnit->getCoefficient();
			break;
		}
	}
	if (i >= _nbUnits)
	{
		CString string(IlvGetMessage(getInterface()->getDisplay(),
			"&TableConversionNonTrouve"));
		string += " ";
		string += uniteDepart;
		string += "->";
		string += uniteArrivee;
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage(string,false);
	}

    delete [] wunite1;
    delete [] wunite2;

// calcul du resultat
	poidsConverti = poidsAConvertir * coefficient;
	return poidsConverti;
}


//--------------------------------------------------------------
// renvoie le poidsAConvertir exprime dans l'uniteDepart, converti dans l'unite d arrivee
// sr 10.03 on travaille en passant toutes les unités en majuscule (à cause pb tare) 
// les unités passée sont déjà en majuscule
double AdxData::convertir2(double poidsAConvertir,
						   const char* uniteDepart,
						   const char* uniteArrivee)
{
	if (strcmp(uniteDepart, uniteArrivee) == 0)
        return poidsAConvertir;

	double poidsConverti;
	double coefficient = 1;
    char* wunite1 = new char[4];
    char* wunite2 = new char[4];

    // recherche du coefficient
	AdxUnit* tabUnit;
	IlList* unitList = getUnitList();
	int i = 0;
	for (i = 0; i < _nbUnits; i++) 
	{
		tabUnit = (AdxUnit*)(*unitList)[i];
        //on transforme les unités de la table des coefficients
        strcpy(wunite1,tabUnit->getUnite1());
        strcpy(wunite2,tabUnit->getUnite2());
        strupr(wunite1);
        strupr(wunite2);
        //on compare, en majuscule, les unités passées en paramètre et les unités de la table
        //si équivalence, on récupère le coefficient
		if (strcmp(uniteDepart, wunite1) == 0 &&
			strcmp(uniteArrivee, wunite2) == 0)
		{
			coefficient = tabUnit->getCoefficient();
			break;
		}
	}
	if (i >= _nbUnits)
	{
		CString string(IlvGetMessage(getInterface()->getDisplay(),
			"&TableConversionNonTrouve"));
		string += " ";
		string += uniteDepart;
		string += "->";
		string += uniteArrivee;
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage(string,false);
	}
 
    delete [] wunite1;
    delete [] wunite2;

    // calcul du resultat
	poidsConverti = poidsAConvertir * coefficient;
	return poidsConverti;
}

//--------------------------------------------------------------
char * AdxData::majuscule(const char *unite)
{
// passage des unités en majuscules
char* wunite = new char[ strlen( unite) +1];

strcpy(wunite,unite);
strupr(wunite);
return wunite;

}   
//--------------------------------------------------------------
// prend en parametre l'index dans la table m_data->getOrderList()
void AdxData::setCurrentOrderIndex(unsigned long index, bool premiereFois)
{
	if (premiereFois)
	{
		_currentOrder = getOrder(index);
		_currentOrderIndex = index;
		_orderBegin = false;
		_nbPhasesPesees = 0;
	}
	else
	{
		if ( getInterface()->getFonctionEnCours() == 1 ||  getInterface()->getFonctionEnCours() == 3)
		{
			if  (_currentOrderIndex != index)
			{
				unsigned long savIndex = _currentOrderIndex;
				bool savBegin = _orderBegin;
				int savNbPhasePesees = _nbPhasesPesees;
				_currentOrder = getOrder(index);
				_currentOrderIndex = index;
				_orderBegin = false;
				_nbPhasesPesees = 0;

				bool dataOK = acquisitionOF(savIndex,index);
		// si le chargement des donnees pas bon on se repositionne sur l OF courant
				if (!dataOK)
				{			
					_currentOrder = getOrder(savIndex);
					_currentOrderIndex = savIndex;
					_orderBegin = savBegin;
					_nbPhasesPesees = savNbPhasePesees;

		// sr 05.02 Il ne faut surtout pas toucher au statut 
		//de l'OF inaccessible FI n° 17
		// astuce : On passe deux fois le même index
		//				dataOK = acquisitionOF(index,savIndex);
						dataOK = acquisitionOF(savIndex,savIndex);
		// si le chargement des donnees encore pas bon on a echoue
					if (!dataOK)
					{
						getInterface()->getMessage()->setPanneauAppelant(NULL);
						getInterface()->envoieMessage("&EchecOF",false);
						getInterface()->getAccueil()->quitter();
					}
				}
			}
		}
		// pesée par article
		else 
		{
			bool savBegin = _orderBegin;
			int savNbPhasePesees = _nbPhasesPesees;
			_currentOrder = getOrder(index);
			_currentOrderIndex = index;
			_orderBegin = false;
			_nbPhasesPesees = 0;

			bool dataOK = true;
			dataOK = acquisitionOF(index,index); 

			// si le chargement des donnees encore pas bon on a echoue
			if (!dataOK)
			{
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				getInterface()->envoieMessage("&EchecOF",false);
				getInterface()->getAccueil()->quitter();
			}
		}
	}
}


//--------------------------------------------------------------
// renvoie l'index precis de l'OF dans la table m_data->getOrderList()
int AdxData::getIndexNumOF(const char* numOF)
{
	int i=0;
	while (i < getNbOrders())
	{
		if (strcmp(numOF,getOrder(i)->getNumOF()) == 0)
			return i;
		i++;
	}
	return _nbOrders;
}


//--------------------------------------------------------------
// prend en parametre l'index dans la table m_data->getBalanceList()
void AdxData::setCurrentBalanceIndex(unsigned long index)
{
	_currentBalance = getBalance(index);
	_currentBalanceIndex = index;
}


//--------------------------------------------------------------
// prend en parametre l'index dans la table m_data->getEtalonList()
void AdxData::setCurrentEtalonIndex(unsigned long index)
{
	_currentEtalon = getEtalon(index);
	_currentEtalonIndex = index;
}

//--------------------------------------------------------------
// renvoie l'index precis de l'etalon dans la table m_data->getEtalonList()
int AdxData::getIndexEtalon(const char* numEtalon)
{
	int i=0;
	while (i < getNbEtalons())
	{
		if (strcmp(numEtalon,getEtalon(i)->getEtalon()) == 0)
			return i;
		i++;
	}
	return _nbEtalons;
}


//--------------------------------------------------------------
// prend en parametre l'index dans la table m_data->getPhaseList()
// sauf dans le cas de la pesée par matière, où l'index provient du tableau des phases
void AdxData::setCurrentPhaseIndex(unsigned long index)
{
// sr 02.02 Pourquoi effacer le nombre de composants pesée (ils ont pu
// etre pesés lors d'un précédent appel aux centrales
// Si on perd cette information et qu'il nous reste une matière à peser
// pour cette phase, on va la peser mais on ne fera jamais la fin de phase

//	getPhase(index)->setNbComposantsPeses(0);
	_currentPhase = getPhase(index);
	_currentPhaseIndex = index;
	_phaseBegin = false;
}

//--------------------------------------------------------------
// renvoie l'index precis de la phase dans la table m_data->getPhaseList
int AdxData::getIndexPhase(const int phase)
{
	int i=0;
	while (i < getNbPhases())
	{
		if (phase == getPhase(i)->getNumPhase())
			return i;
		i++;
	}
	return _nbPhases;
}

//--------------------------------------------------------------
// renvoie l'index precis du composant dans la table m_data->getComposantList_Art
int AdxData::getIndexComposant_Art(const AdxComposant* composant)
{
	int i=0;
	while (i < getNbComposants_Art())
	{
		if (composant == getComposant_Art(i))
			return i;
		i++;
	}
	return _nbComposants_Art;
}

//--------------------------------------------------------------
// permet de retrouver un composant par saisie du libelle
// renvoie l'index du premier composant de meme libelle, dans la table m_data->getComposantList_Art
int AdxData::getIndexComposant_Art(const char* composant)
{
	int i=0;
	while (i < getNbComposants_Art())
	{
		if (strcmp(composant,getComposant_Art(i)->getComposant()) == 0)
			return i;
		i++;
	}
	return _nbComposants_Art;
}

//--------------------------------------------------------------
// prend en parametre l'index dans la table m_data->getCurrentPhase()->getComposantList
void AdxData::setCurrentComposantIndex(unsigned long index)
{
	
	_currentComposant = getCurrentPhase()->getComposant(index);

	_currentComposantIndex = index;
	_composantBegin = false;
	_composantAlloue = false;
	_nbLotsPeses = 0;
	AdxFicheISM* _ficheISM ;
	_currentFicheISM = NULL;
	IlList* ficheISMList = getFicheISMList();

	if (_nbFichesISM > 0)
	{
		for (long i = 0; i < getNbFichesISM(); i++) 
		{
			_ficheISM = (AdxFicheISM*)(*ficheISMList)[i];
			if (strcmp(_ficheISM->getFicheISM(), getCurrentComposant()->getFicheISM()) == 0)
			{
				_currentFicheISM = _ficheISM;
				return;
			}
		}
		if (_currentFicheISM == NULL)
		{
			getInterface()->getMessage()->setPanneauAppelant(NULL);
			// 86892 mm - 02.2013  modification du message
			CString string ( _currentComposant->getComposant());
			string += " ";
			string += IlvGetMessage(getInterface()->getDisplay(),"&AucuneFicheISM");
			getInterface()->envoieMessage(string,false);
		}
	}
}

//--------------------------------------------------------------
// utilisé exclusivement pour l'affichage en pesée par matière, alors que seule la matière a été sélectionnée
void AdxData::setCurrentComposantIndexPseMat(const char* composant, const char* libComposant,int index)
{
  if( _pseMat_currentMat != NULL)
	{
		delete [] _pseMat_currentMat;
	}
	_pseMat_currentMat	 = new char [ strlen(composant)+1];
	strcpy( _pseMat_currentMat	, composant);

	if( _pseMat_currentMatLib  != NULL)
	{
		delete [] _pseMat_currentMatLib ;
	}
	_pseMat_currentMatLib = new char [strlen(libComposant)+1];
	strcpy(_pseMat_currentMatLib, libComposant);

	_pseMat_currentIndexComposant = index ;
}

//--------------------------------------------------------------
void AdxData::setCurrentLotIndex(unsigned long index)
{
	if (index == this->getNbLots())
		_currentLot = NULL;
	else
		_currentLot = getLot(index);
	_currentLotIndex = index;
	_lotBegin = false;
}

//--------------------------------------------------------------
// retourne la premier lot rencontre pour lequel le lot vaut celui passe en parametre
int AdxData::getIndexLot(const char* lot)
{
	int i=0;
	while (i < _nbLots)
	{
		if (strcmp (lot, getLot(i)->getLot()) == 0)
			return i;
		i++;
	}
	return _nbLots;
}

//--------------------------------------------------------------
// retourne la premier lot rencontre pour lequel la cuve vaut celle passe en parametre
int AdxData::getIndexLotParCuve(const char* cuve)
{
	int i=0;
	while (i < _nbLots)
	{
		if (strcmp (cuve, getLot(i)->getCuve()) == 0)
			return i;
		i++;
	}
	return _nbLots;
}

//--------------------------------------------------------------
bool AdxData::acquisitionOF(unsigned long indexAncien,unsigned long indexNouveau )
{
	sendX3_ChangeOF(indexAncien, indexNouveau);

	bool dataOK =loadPhases( getSzCheminCsv3());
	if ( !dataOK && (getEnCoursDePeseeParArticle ()== true))
	{
		dataOK = true;
		return dataOK;
	}

	if (dataOK )
		dataOK = loadFichesISM( getSzCheminCsv7());
		if (dataOK)
			dataOK = loadComposants( getSzCheminCsv4(), 0);
	return dataOK;
}

//--------------------------------------------------------------
void AdxData::sendX3_ChangeOF(unsigned long indexAncien,unsigned long indexNouveau)
{

	//  47764 mm 07.08 - Statut OF KO - Voir comment passer une chaine vide plutôt que le nouvel OF en 1er param
	if (getInterface()->getFonctionEnCours() == 1 ||  getInterface()->getFonctionEnCours() == 3)
	{
		if (getOrder(indexAncien)->getTotalementPese() == true)
			X3Ilog_SendX3(getInterface()->getStructX3(),
    				  X3_CHANGEOF,
					  1,
					  "%s%s%s",
					  getOrder(indexNouveau)->getNumOF(),
					  getOrder(indexNouveau)->getNumOF(),
					   "null");
		else
			X3Ilog_SendX3(getInterface()->getStructX3(),
    				  X3_CHANGEOF,
					  1,
					  "%s%s%s",
					  getOrder(indexAncien)->getNumOF(),
					  getOrder(indexNouveau)->getNumOF(),
					  "null");
	}
	else
	{
		X3Ilog_SendX3(getInterface()->getStructX3(),
			  X3_CHANGEOF,
			  1,
			  "%s%s%s",
			  getOrder(indexAncien)->getNumOF(),		
			  getOrder(indexNouveau)->getNumOF(),
			  getPseMatCurrentMat());	 
	}		
}

//--------------------------------------------------------------
bool AdxData::sendX3_GetMatMat(const char* composant)
{	// SMO : STD-PR-OO1 : Pesee Matiere : 14/06/2010 : recuperation de la liste des composants
	
	X3Ilog_SendX3(getInterface()->getStructX3(),
		  X3_PSEMAT_MAT,
		  IlvTrue,
		  "%s",
		  composant);
	
	bool dataOK = loadComposants( getSzCheminCsv4(), X3_PSEMAT_MAT);

	return dataOK;
}

//--------------------------------------------------------------
bool AdxData::sendX3_GetMatOF()
{	// SMO : STD-PR-OO1 : Pesee Matiere : 14/06/2010 : recuperation de la liste des OF par composant

	X3Ilog_SendX3(getInterface()->getStructX3(),
			  X3_PSEMAT_OF,
			  IlvTrue,
			  "%s",
			  getPseMatCurrentMat()	);

	bool dataOK = loadOrders( getSzCheminCsv2() );
	//_currentOrder = NULL;

	return dataOK;
}

//--------------------------------------------------------------
bool AdxData::acquisitionLots(double quantite)
{
	sendX3_AllocLot(quantite);

	getInterface()->setSequenceAppelante(0);
	bool dataOK = loadLots(getSzCheminCsv5());

	if( dataOK && (getSzCheminCsv8() != NULL)
		&& strcmp( getSzCheminCsv8(), "") != 0) 
	{
		dataOK = loadFichesISMRecipient( getSzCheminCsv8());
	}
	return dataOK;
}


//--------------------------------------------------------------
bool AdxData::ReloadAll()
{
		// la première ligne récupérée dans ScaleSto.csv n'est pas forcément celle 
		// sur laquelle la matière a été consommée :
		// sauvegarde des n° de lot/slo courant pour retrouver la ligne de stock
		AdxLot* lotCourant = getCurrentLot();
		char* _lot = new char [strlen(lotCourant->getLot()) +1];
		char* _slo = new char [strlen(lotCourant->getSlo()) +1];
		strcpy( _lot ,(char*)lotCourant->getLot());
		strcpy( _slo ,(char*)lotCourant->getSlo());
		double _quantiteTotale = lotCourant->getQuantiteTotale();

		bool dataOK = loadLots(getSzCheminCsv5());
		if (!dataOK)
		{
			getInterface()->getMessage()->setPanneauAppelant(NULL);
			getInterface()->envoieMessage("&EchecLots",false);
		}

		// recherche de la ligne de stock sur laquelle la matière a été consommée
		AdxLot* lot;
		IlList* lotList = getLotList();

		for (int i = 0; i <getNbLots(); i++)
		{
			lot = (AdxLot*) (*lotList)[i];
			if ((strcmp(lot->getLot(), _lot)==0) &&
				(strcmp(lot->getSlo(), _slo)==0 ) &&
				(lot->getQuantiteTotale()== _quantiteTotale))
			{
				_currentLot = getLot(i);
				break;
			}
		}
		delete [] _lot;
		delete [] _slo;
		
		return dataOK;
}


//--------------------------------------------------------------
void AdxData::imprimeLots()
{
	saveLots();		// permet au serveur de savoir quelles allocations imprimer
	X3Ilog_SendX3(getInterface()->getStructX3(),
    			  X3_IMPRIMELOTS,
				  IlvTrue,
				  "");
	bool dataOK = loadLots(getSzCheminCsv5());
}

//--------------------------------------------------------------
void AdxData::imprimeEtAlloueLots()
{
	saveLots();
	X3Ilog_SendX3(getInterface()->getStructX3(),
    			  X3_IMPRIMEETALLOUELOTS,
				  IlvTrue,
				  "");
	bool dataOK = loadLots(getSzCheminCsv5());
}

//--------------------------------------------------------------
void AdxData::alloueLots()
{
	saveLots();
	X3Ilog_SendX3(getInterface()->getStructX3(),
    			  X3_MODIFALLOC,
				  IlvTrue,
				  "");
	bool dataOK = loadLots(getSzCheminCsv5());
}

//--------------------------------------------------------------
void AdxData::saveLots()
{
// creation du fichier
	const char* const SEP = ";";
	ofstream res(getSzCheminCsv10());	
	char szbuffer[100]="";

	AdxLot* lot;
	if (_nbLots > 0)
	{
		for (int i = 0; i < _nbLots; i++)
		{
			lot = (AdxLot*)(*_lotList)[i];
            // sr 06.04 ne renvoyer que les lignes allouées (pb performances)
            if (lot->getQuantiteAllouee() != 0)
            {
    			res<<getCurrentComposant()->getComposant()<<SEP;
	    		res<<lot->getLot()<<SEP;
		    	res<<lot->getSlo()<<SEP;
                res<<lot->getEmplacement()<<SEP;
				// mm APCPRD-2631 01.2013
				sprintf(szbuffer,getCurrentComposant()->getFormat(),lot->getQuantiteAllouee());
				res<<szbuffer<<SEP ; 		
    			res<<lot->getUnite()<<SEP;
				res<<lot->getChrono()<<SEP;		// mm 10.08 - Pb d'allocation
	    		res<<getCurrentComposant()->getUniteStock()<<SEP;
		    	res<<getCurrentComposant()->getNumeroLigne()<<SEP;
    			res<<getCurrentComposant()->getSequenceNomenclature()<<SEP;
	    		res<<getCurrentOrder()->getNumOF()<<SEP<<"Finenr"<<endl;
		    }
        }
	}
	res.close();
}

//--------------------------------------------------------------
void AdxData::savePesee(int fin)
{
// creation du fichier
	const char* const SEP = ";";
	ofstream res(getSzCheminCsv11());
	char szbuffer[100]="";
	char szbuffer2[100]="";
	AdxPesee_OF* peseeOF = getInterface()->getPesee_OF();

	res<<getCurrentOrder()->getNumOF()<<SEP;
	res<<getCurrentPhase()->getNumPhase()<<SEP;
	res<<getCurrentComposant()->getComposant()<<SEP;
	res<<getCurrentComposant()->getNumeroLigne()<<SEP;
	res<<getCurrentComposant()->getSequenceNomenclature()<<SEP<<flush;

	if (fin < 3)
	{
		if (peseeOF->getBalancePrevue() != NULL)
			res<<peseeOF->getBalancePrevue()->getBalance()<<SEP;
		else
		{
			res<<""<<SEP;
		}
		res<<peseeOF->getBalanceChoisie()->getBalance()<<SEP;
		res<<peseeOF->getBalanceChoisie()->getCodeCalibrage()<<SEP;
		// mm 11.11 - Balance connectée oui/non
		res<<peseeOF->getBalanceChoisie()->getConnecte()<<SEP;

	    if (peseeOF->getRecipientPrevu() != NULL)
	 		res<<peseeOF->getRecipientPrevu()->getRecipient() <<SEP;
	    else
		{
			res<<""<<SEP;
		}
		res<<peseeOF->getRecipientChoisi()->getRecipient() <<SEP;
		res<<peseeOF->_poidsTare<<SEP;
		}
	else
	{
		res<<""<<SEP;
		res<<""<<SEP;
		res<<""<<SEP;
		res<<""<<SEP;
		res<<""<<SEP;
		res<<""<<SEP;	
		res<<""<<SEP;
	}
	
	// mm 10.11 - Pesée multi-article
	res<<peseeOF->getEnPeseeMultiArticle()<<SEP;	
	// mm 10.12 - APCPRD 1596
	if (peseeOF->getEnPeseeMultiArticle())
		res<<peseeOF->getMat1()<<SEP;
	else
		res<<""<<SEP;
	res<<""<<SEP;
	res<<""<<SEP<<flush;	

	res<<getCurrentComposant()->getCodeAServir()<<SEP;
	if (fin <3)
	{
		res<<getCurrentLot()->getLot()<<SEP;	
		res<<getCurrentLot()->getSlo()<<SEP;	
        res<<getCurrentLot()->getEmplacement()<<SEP;
		res<<getCurrentLot()->getStatut()<<SEP<<flush;
	}
	else
	{
		res<<""<<SEP;
		res<<""<<SEP;		// mm 07.14
		res<<""<<SEP;
		res<<""<<SEP;
	}
	res<<getCurrentComposant()->getTitreTheo()<<SEP;
	if (fin <3)
	{
		res<<getCurrentLot()->getTitre()<<SEP;
	}
	else
	{
		res<<""<<SEP;
	}
	res<<getCurrentComposant()->getUniteStock()<<SEP;
	res<<getCurrentComposant()->getUnite()<<SEP<<flush;

	if (fin <3)
	{
		//res<<peseeOF->_poidsPese<<SEP;
		//res<<peseeOF->_poidsAPeser<<SEP;
		// suite APCPRD-2631 - mm - 01.2013 : arrondi intempestif effectué par l'opérateur <<
		// parade : on met le double dans une string
		sprintf(szbuffer,getCurrentComposant()->getFormat(),peseeOF->_poidsPese);
		res<<szbuffer<<SEP;
		sprintf(szbuffer2,getCurrentComposant()->getFormat(),peseeOF->_poidsAPeser);
		res<<szbuffer2<<SEP;
	}
	else
	{
		res<<""<<SEP;
		res<<""<<SEP;
	}
	// mm 08.2016 - peser au-delà du poids max autorisé 
	if (getExceedingTolerancePos()==2)
		res<<peseeOF->getDepassementPoidsMax()<<SEP;
	else
		res<<""<<SEP;

	res<<getCurrentComposant()->getFicheISM()<<SEP;
// option de pesee: 1 = pesee par OF; 2 = pesee par Article; 3 = pesee fabrication
	
	res<<getInterface()->getFonctionEnCours()<<SEP;	
	if (fin <3)
	{
		res<<getCurrentLot()->getChrono()<<SEP;
		res<<getCurrentLot()->getSequence()<<SEP<<flush;

		if (getCurrentFicheISM()->getContenuEtiquette() != NULL)
			res<<getCurrentFicheISM()->getContenuEtiquette()<<SEP;
		else
			res<<""<<SEP;

		if (peseeOF->getRecipientChoisi()->getFormatEtiquette() != NULL)
			res<<peseeOF->getRecipientChoisi()->getFormatEtiquette()<<SEP;
		else
			res<<""<<SEP;
	}
	else
	{
		res<<""<<SEP;
		res<<""<<SEP;
		res<<""<<SEP;
		res<<""<<SEP;
	}

	if ((fin == 0) || (fin == 3))	// pas de vide de box
		res<<""<<SEP;
	if ((fin == 1) || (fin == 4))	// vide de box fin phase si obligatoire
		if (getVideBoxFinPhaseOblig() == 2)
			res<<getVideBoxFinPhase()<<SEP;
		else
			res<<""<<SEP;
	if ((fin == 2) || (fin == 5))	// vide de box fin OF si obligatoire
		if (this->getVideBoxFinOFOblig() == 2)
			res<<getVideBoxFinOF()<<SEP;
		else
			res<<""<<SEP;

	res<<"Finenr"<<endl;
	res.close();


}


//--------------------------------------------------------------
void AdxData::saveLigneEtalonnage()
{
	// creation du fichier
	const char* const SEP = ";";
	ofstream res(getSzCheminCsv13());

	AdxPesee_Etalon* peseeEtalon = getInterface()->getPesee_Etalon();
	for(int i = 0;i < getCurrentEtalon()->getNbLignes();i++)
	{
		 getCurrentEtalon()->setCurrentEtalonLigneIndex(i);	
		 for (int j = 0; j < getCurrentEtalon()->getCurrentEtalonLigne()->getNbPesees();j++)
		 {
			res<<getCurrentBalance()->getBalance()<<SEP<<flush;
			res<<getCurrentEtalon()->getCurrentEtalonLigne()->getUnite()<<SEP;
			res<<getCurrentEtalon()->getCurrentEtalonLigne()->getArrPoidsPese(j)<<SEP;

			res<<getCurrentEtalon()->getCurrentEtalonLigne()->getPoids()<<SEP;
			res<<getCurrentEtalon()->getCurrentEtalonLigne()->getEcartMaxi()<<SEP;

			res<<getCurrentBalance()->getGuideCalibrage()<<SEP;

			res<<getCurrentEtalon()->getCurrentEtalonLigne()->getLigne()<<SEP;
			res<<getCurrentEtalon()->getCurrentEtalonLigne()->getTypPesee()<<SEP;
			res<<j+1<<SEP;
			
			res<<"Finenr"<<endl;
		 }
	}
	res.close();
}

//--------------------------------------------------------------
void AdxData::sendX3_AllocLot(double quantite)
{
  char szBuffer[100] = "";
  double val;
// provisoirement : on passe par l'entier pour traiter la double précision
// en multipliant la valeur par 1000 (3 chiffres significatifs après la virgule)
// llc conversion de la muerte de double à long via une chaine
/* if (getCurrentComposant()->getCodeAServir() > 3)
		val = quantite * 1000;
   else 
		val = 0;
   sprintf(szBuffer, "%.0f", val);
   long qteRest = atoi(szBuffer);
*/

	// APCPRD-2753 mm 02.2013 Passer directement la quantité décimalisée via une string
	// l'ancienne méthode posait un problème d'arrondi si nb de décimales > 3
	if (getCurrentComposant()->getCodeAServir() > 3)
		sprintf(szBuffer, getCurrentComposant()->getFormat(), quantite);	
	else
		sprintf(szBuffer, getCurrentComposant()->getFormat(), 0);	

	int peseeParArticle =0 ;
	if ( getInterface()->getFonctionEnCours() == 2) 
		peseeParArticle = 2;

	X3Ilog_SendX3(getInterface()->getStructX3(),
			  X3_ALLOCLOT,
			  IlvTrue,
			  "%s%s%s%d%d%s%d",
			  getCurrentOrder()->getNumOF(),
			  getCurrentComposant()->getComposant(),
			  szBuffer,
			  getCurrentComposant()->getNumeroLigne(),
			  getCurrentComposant()->getSequenceNomenclature(),
			  getCurrentComposant()->getFicheISM(),
			  peseeParArticle);
}
//--------------------------------------------------------------
/*bool AdxData::acquisitionPhase()
{
	bool dataOK = true;
	sendX3_ChangePhase();
	if (getSzCheminCsv5() != NULL)
	{
		getInterface()->setSequenceAppelante(0);
		dataOK = loadLots(getSzCheminCsv5());
	}
	return dataOK;
}*/
//--------------------------------------------------------------
// appelé exclusivement dans le cas q'une pesée par article
// permet de verrouiller le couple matière/ phase d'un OF afin 
// d'empêcher qu'il soit choisi de façon simultannée par un autre utilisateur
void AdxData::sendX3_ChangePhase()
{
	X3Ilog_SendX3(getInterface()->getStructX3(),
				  X3_PESEEPARMAT,
				  IlvTrue,
				  "%s%s%d%d%d",
				  getCurrentOrder()->getNumOF(),
				  getCurrentComposant()->getComposant(),
				  getCurrentComposant()->getNumeroLigne(),
				  getCurrentComposant()->getSequenceNomenclature());
}
//--------------------------------------------------------------
// pas appelé finalement, fait dp X3 après chaque MAJ du suivi, 
// on recharge le fichier des lignes de stock
void AdxData::SendX3_ReloadAll()
{
    X3Ilog_SendX3(getInterface()->getStructX3(),
				  X3_RELOADALL,
				  IlvTrue,
				  "%s%s%d%d",
				  getCurrentOrder()->getNumOF(),
				  getCurrentComposant()->getComposant(),
				  getCurrentComposant()->getNumeroLigne(),
				  getCurrentComposant()->getSequenceNomenclature());
}
//--------------------------------------------------------------
void AdxData::SendX3_ConsultationStockDetaille()
{	
	if (getInterface()->getSequenceAppelante() == 0)
	{
		getInterface()->getPanneauAppelant()->setSensitive(false);
		getInterface()->setSequenceAppelante(17);
		X3Ilog_SendX3( getInterface()->getStructX3(),
				  X3_CONSULTATIONSTOCK,
				  IlvFalse,
				  "%s",
				  getCurrentComposant()->getComposant());
	}
	else
	{
		getInterface()->setSequenceAppelante(0);
		getInterface()->getPanneauAppelant()->setSensitive(true);
	}

}
//--------------------------------------------------------------
void AdxData::sendX3_soldeMatiereSansQuantite()
{
	savePesee(3);
	X3Ilog_SendX3(getInterface()->getStructX3(),
				X3_SOLDEMATIERE,
				IlvTrue,
				"");
}


//--------------------------------------------------------------
void AdxData::sendX3_FinPhaseBis()
{
	savePesee(4);
	X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_FINPHASEBIS,
			IlvTrue,
			"%s%s%d%d",
			getCurrentOrder()->getNumOF(),
			getCurrentComposant()->getComposant(),
			getCurrentComposant()->getNumeroLigne(),
			getCurrentComposant()->getSequenceNomenclature());
}

//--------------------------------------------------------------
void AdxData::sendX3_FinOFBis()
{
	savePesee(5);
	X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_FINOFBIS,
			IlvTrue,
			"%s%s%d%d",
			getCurrentOrder()->getNumOF(),
			getCurrentComposant()->getComposant(),
			getCurrentComposant()->getNumeroLigne(),
			getCurrentComposant()->getSequenceNomenclature());
}
//--------------------------------------------------------------
void AdxData::sendX3_PeseePartielle()
{
	int peseeParArticle =0 ;
	if ( getInterface()->getFonctionEnCours() == 2) 
		peseeParArticle = 2;

	savePesee(0);
	X3Ilog_SendX3(getInterface()->getStructX3(),
				X3_PESEEPARTIELLE,
				IlvTrue,
				"%d",
				peseeParArticle);
}

//--------------------------------------------------------------
void AdxData::sendX3_FinLot()
{
	int peseeParArticle =0 ;
	if ( getInterface()->getFonctionEnCours() == 2) 
		peseeParArticle = 2;

	savePesee(0);
	X3Ilog_SendX3(getInterface()->getStructX3(),
				X3_FINLOT,
        		IlvTrue,
				"%d",
				peseeParArticle);
}

//--------------------------------------------------------------
void AdxData::sendX3_FinComposant()
{	
	savePesee(0);
	X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_FINCOMPOSANT,
			IlvTrue,
			"%s%s%d%d",
			getCurrentOrder()->getNumOF(),
			getCurrentComposant()->getComposant(),
			getCurrentComposant()->getNumeroLigne(),
			getCurrentComposant()->getSequenceNomenclature());
}

//--------------------------------------------------------------
void AdxData::sendX3_FinComposant_Art()
{	
	savePesee(0);
	X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_FINCOMPOSANT_ART,
			IlvTrue,
			"%s%s%d%d",
			getCurrentOrder()->getNumOF(),
			getCurrentComposant()->getComposant(),
			getCurrentComposant()->getNumeroLigne(),
			getCurrentPhase()->getNumPhase());		
}
//--------------------------------------------------------------
void AdxData::SendX3_InterruptionComposant()
{
	X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_INTERRUPTCOMPOSANT,
			IlvTrue,
			"%s%s%d%d",
			getCurrentOrder()->getNumOF(),
			getCurrentComposant()->getComposant(),
			getCurrentComposant()->getNumeroLigne(),
			getCurrentComposant()->getSequenceNomenclature());
}

//--------------------------------------------------------------
void AdxData::SendX3_ChangementOFNonPese(AdxOrder* order)
{
	int peseeParArticle = 0;
	if ( getInterface()->getFonctionEnCours() == 2) 
		peseeParArticle = 2;

	if (order != NULL)
	{
		X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_CHGTOFNONPESE,
			IlvTrue,
			"%s%s%d%d%d%d",
			getCurrentOrder()->getNumOF(),
			getCurrentComposant()->getComposant(),
			getCurrentComposant()->getNumeroLigne(),
			getCurrentComposant()->getSequenceNomenclature(),
			order->getNumOF(),
			peseeParArticle);
	}
	else
	{
		X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_CHGTOFNONPESE,
			IlvTrue,
			"%s%s%d%d%d%d",
			getCurrentOrder()->getNumOF(),
			getCurrentComposant()->getComposant(),
			getCurrentComposant()->getNumeroLigne(),
			getCurrentComposant()->getSequenceNomenclature(),
			"null",
			peseeParArticle);		
	}
}

//--------------------------------------------------------------
// sr 11.02 réactualisation des données incident n° 27
// Si un of est en cours, on le libère d'abord (WGGFLG = 3)
// On extrait le plan de pesée et on rafraichit les données côté poste
void AdxData::SendX3_Refresh()
{
	if (getNbOrders()!=0 && getCurrentOrder()!= NULL )
	{
		X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_REFRESH,
			IlvTrue,
			"%s",
			getCurrentOrder()->getNumOF());
	}
	else
	{
		X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_REFRESH,
			IlvTrue,
			"%s",
			"");
	}
	// On recharge les fichiers concernés
	loadOrders(getSzCheminCsv2());
	loadPhases(getSzCheminCsv3());
	loadFichesISM(getSzCheminCsv7());
	loadComposants(getSzCheminCsv4(),0);
	// On se repositionne comme pour une 1ere arrivée dans la centrale
	// pour savoir si on doit débloquer un OF en sortant
	setPeseeLancee(false);			
}

//--------------------------------------------------------------
// Remise à jour du flag _enPeséeMulti = oui à non
// dûe à l'abandon de la peséee multi-article cause récipient 
// de capacité insuffisante ou balance de portée insuffisante
void AdxData::sendX3_InterruptionPeseeMulti()
{
	X3Ilog_SendX3(getInterface()->getStructX3(),
				X3_ABANDON_PESEEMULTI,
        		IlvTrue,
				"");
}

//--------------------------------------------------------------
void AdxData::SendX3_ChangementComposant()
{
	X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_DESALLOUECOMPOSANT,
			IlvTrue,
			"%s%s%d%d",
			getCurrentOrder()->getNumOF(),
			getCurrentComposant()->getComposant(),
			getCurrentComposant()->getNumeroLigne(),
			getCurrentComposant()->getSequenceNomenclature());
}

//--------------------------------------------------------------
void AdxData::SendX3_InterruptionPhase()
{
	X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_INTERRUPTPHASE,
			IlvTrue,
			"%s%d",
			getCurrentOrder()->getNumOF(),
			getCurrentPhase()->getNumPhase());
}

//--------------------------------------------------------------
void AdxData::SendX3_InterruptionOF()
{
	int peseeParArticle = 0;
	if ( getInterface()->getFonctionEnCours() == 2) 
		peseeParArticle = 2;

	X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_INTERRUPTOF,
			IlvTrue,
			"%s%s%d%d%d",
			getCurrentOrder()->getNumOF(),
			getCurrentComposant()->getComposant(),
			getCurrentComposant()->getNumeroLigne(),
			getCurrentComposant()->getSequenceNomenclature(),
			peseeParArticle);
}

//--------------------------------------------------------------
void AdxData::sendX3_FinPhase()
{
	savePesee(1);
	X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_FINPHASE,
			IlvTrue,
			"%s%s%d%d",
			getCurrentOrder()->getNumOF(),
			getCurrentComposant()->getComposant(),
			getCurrentComposant()->getNumeroLigne(),
			getCurrentComposant()->getSequenceNomenclature());
}

//--------------------------------------------------------------
void AdxData::sendX3_FinOF()
{
	savePesee(2);
	X3Ilog_SendX3(getInterface()->getStructX3(),
			X3_FINOF,
			IlvTrue,
			"%s%s%d%d",
			getCurrentOrder()->getNumOF(),
			getCurrentComposant()->getComposant(),
			getCurrentComposant()->getNumeroLigne(),
			getCurrentComposant()->getSequenceNomenclature());
}

//---------------------------------------------------------------------------
void AdxData::sendX3_SoldeEmballage()
{
	AdxPesee_OF* peseeOF = getInterface()->getPesee_OF();
	// On ne peut pas passer un décimal, donc on multiplie par 1000
	// et on passe un entier long
	// dans X3 on divisera par 1000
	// llc conversion de la muerte de double à long via une chaine
	char szBuffer[100] = "";
	double qteFinContenant;
	qteFinContenant= ((getCurrentLot()->getQuantiteTotale())-(peseeOF->_poidsPese));
    if (qteFinContenant <= 0)
        return;

	//qteFinContenant  *= 1000;
	//sprintf(szBuffer, "%.0f", qteFinContenant);
	//long qteRest = atoi(szBuffer);

	// APCPRD-2753 mm 02.2013 Passer directement la quantité décimalisée via une string
	// l'ancienne méthode posait un problème d'arrondi si nb de décimales > 3
	sprintf(szBuffer, getCurrentComposant()->getFormat(), qteFinContenant);
	
	//109330 mm 09.2015 -  verrue effectuée dans le but de rendre les sous-lot optionnels 
	// (contournement d'un pré-requis pour le client Sothys)
	if ( strcmp( getCurrentLot()->getSlo(),"") == 0 )
		getCurrentLot()->setSlo("ZZZZZ");
		
	X3Ilog_SendX3(getInterface()->getStructX3(),
					X3_SOLDEEMB,
					IlvTrue,					//IlvFalse, modifié pour test 09.11 mm
					"%s%s%s%s%d%s%d%d%d",				
					getCurrentOrder()->getNumOF(),
					getCurrentComposant()->getComposant(),
					getCurrentLot()->getLot(),
					getCurrentLot()->getSlo(),
                    getCurrentLot()->getSequence(),
					szBuffer,
					getInterface()->getFonctionEnCours(),
					getCurrentComposant()->getNumeroLigne(),
					getCurrentComposant()->getSequenceNomenclature());
}

//---------------------------------------------------------------------------
void AdxData::sendX3_MajEmballage(int wsens)
{
    // On ne peut pas passer un décimal, donc on multiplie par 1000
	// et on passe un entier long
	// dans X3 on divisera par 1000
	// llc conversion de la muerte de double à long via une chaine
    // sr 03.04 : on arrive ici si ce qui a été pesée est  <> de ce qui devait être pesé et que :
    //  la pesée est supérieure à la qté disponible : wsens = 1 :
    //       le delta entre poids pesé et qté disponible sera rajouté à la quantité totale de la ligne de stock pour obtenir 
    //       la nouvelle quantité
    //  la pesée inférieure à la pesée prévue : wsens = 2 :
    //       c'est que le disponible n'est en fait pas consommable 
    //       donc le delta sera enlevé de la qté totale de la ligne de stock
    //  Dernière pesée en emballage interne  : wsens = 3 
    //      si réponse non à "solde emballage" ? et emballage vide
    //      on fait un redressement positif de 0,001 Kg
    //  Dernière pesée en emballage fournisseur  : wsens = 4 
    //      si pesée inférieure au prévu
    //      on fait un redressement négatif pour le delta entre poids à peser et poids pesé
    //  pesée à 0 car le stock alloué n'est en fait plus disponible. wsens = 5
    //  on va d'abord désallouer puis faire un redressement négatif pour la qté disponible    

	AdxPesee_OF* peseeOF = getInterface()->getPesee_OF();
    double qteContenant;
    double quantite;   
	char szBuffer[100] = "";

        switch (wsens)
    {
	     case 1 :
         {
	        qteContenant= peseeOF->_poidsPese;
            break;
         }
         case 2 :
         {
            qteContenant= ((getCurrentLot()->getQuantiteDisponible())-(peseeOF->_poidsPese));
		    break;
         }
         case 3 :
         {
            qteContenant= 1;
  		    break;
         }
	     case 4 :
         {
	        qteContenant= ((peseeOF->_poidsAPeser)-(peseeOF->_poidsPese));
            break;
         }
 	     case 5 :
         {
             qteContenant = getCurrentLot()->getQuantiteDisponible();

            // décrémentation de la quantité allouée du composant
			if (getCurrentComposant()->getGestionStock() == 3			// composant a titre
				&& getCurrentComposant()->getTitreTheo() != 0)
				quantite = getCurrentLot()->getQuantiteAllouee() * getCurrentLot()->getTitre() / getCurrentComposant()->getTitreTheo();
			else
				quantite = getCurrentLot()->getQuantiteAllouee();

            getCurrentComposant()->setQuantiteAllouee(getCurrentComposant()->getQuantiteAllouee() - quantite);
            if (getCurrentComposant()->getQuantiteAllouee() < 0)
            {
               getCurrentComposant()->setQuantiteAllouee(0);
            }
            // le lot devient inexploitable
            getCurrentLot()->setQuantiteAllouee(0);
            getCurrentLot()->setQuantiteDisponible(0);
            // Sur le dernier lot uniquement
 //         peseeOF->_stockReelInfInfo = true;
            break;
         }

    }
    if (qteContenant == 0)
        return;

    //qteContenant  *= 1000;
	//sprintf(szBuffer, "%.0f", qteContenant);
	//long qteTot = atoi(szBuffer);

	// APCPRD-2753 mm 02.2013 Passer directement la quantité décimalisée via une string
	// l'ancienne méthode posait un problème d'arrondi si nb de décimales > 3
    sprintf(szBuffer, getCurrentComposant()->getFormat(), qteContenant);

	//109330 mm 09.2015 -  verrue effectuée dans le but de rendre les sous-lot optionnels
	// ( contournement d'un pré-requis pour le client Sothys)
	if ( strcmp( getCurrentLot()->getSlo(),"") == 0 )
		getCurrentLot()->setSlo("ZZZZZ");

    X3Ilog_SendX3(getInterface()->getStructX3(),
					X3_MAJEMB,
					IlvTrue,					//IlvFalse, modifié pour test 09.11 mm
					"%s%s%s%s%s%d%d%d%d",		
					getCurrentOrder()->getNumOF(),
					getCurrentComposant()->getComposant(),
					getCurrentLot()->getLot(),
					getCurrentLot()->getSlo(),					
					szBuffer,
                    getInterface()->getFonctionEnCours(),
					getCurrentComposant()->getNumeroLigne(),
					getCurrentComposant()->getSequenceNomenclature(),
                    wsens);
}

//--------------------------------------------------------------
void AdxData::SendX3_Procedure(int i) // i = 1 ouv de Box; 2 = fin de phase; 3 = fin d'OF; 4 = chgmt matiere
{
	bool X3Cred = false;

	if (getInterface()->getSequenceAppelante() == 0)
	{
		if (i == 1)	//ouverture de box	
		{
			getInterface()->getPanneauAppelant()->setSensitive(false);
			getInterface()->setSequenceAppelante(14);
			X3Ilog_SendX3(getInterface()->getStructX3(),
					X3_VIDEBOX,
//					IlvTrue,
					IlvFalse,
					"%s%s%d%s%d%d",
					getOuvertureBox(),
					"null",
					0,
					"null",
					1,
					getOuvertureBoxOblig());
		}

		if (i == 2 && getOFProcedure() != NULL && getPhaseProcedure() != NULL)	//fin de phase
		{
			if ( _X3Ver = 11 )													//X3-67237
			{																	//X3-67237
				do																//X3-67237
					X3Cred = SendX3_CheckCredentials(true, true);				//X3-67237
				while ( X3Cred = false);										//X3-67237
			}																	//X3-67237

			getInterface()->getPanneauAppelant()->setSensitive(false);
			getInterface()->setSequenceAppelante(14);
			X3Ilog_SendX3(getInterface()->getStructX3(),
					X3_VIDEBOX,
//					IlvTrue,
					IlvFalse,
					"%s%s%d%s%d%d",
					getVideBoxFinPhase(),
					getOFProcedure()->getNumOF(),
					getPhaseProcedure()->getNumPhase(),
					"null",
					3,
					getVideBoxFinPhaseOblig());
		}

		if (i == 3 && getOFProcedure() != NULL)	//fin d'OF
		{
			if ( _X3Ver = 11 )													//X3-67237
			{																	//X3-67237
				do																//X3-67237
					X3Cred = SendX3_CheckCredentials(true, true);				//X3-67237
				while ( X3Cred = false);										//X3-67237
			}																	//X3-67237

			getInterface()->getPanneauAppelant()->setSensitive(false);
			getInterface()->setSequenceAppelante(14);
			X3Ilog_SendX3(getInterface()->getStructX3(),
					X3_VIDEBOX,
//					IlvTrue,
					IlvFalse,
					"%s%s%d%s%d%d",
					getVideBoxFinOF(),
					getOFProcedure()->getNumOF(),
					0,
					"null",
					2,
					getVideBoxFinOFOblig());
		}

		if (i == 4 && getComposantProcedure() != NULL)	// changement de matiere 
		{
			if ( _X3Ver = 11 )													//X3-67237	
			{																	//X3-67237
				do																//X3-67237
					X3Cred = SendX3_CheckCredentials(true, true);				//X3-67237
				while ( X3Cred = false);										//X3-67237
			}																	//X3-67237

			getInterface()->getPanneauAppelant()->setSensitive(false);
			getInterface()->setSequenceAppelante(14);
			X3Ilog_SendX3(getInterface()->getStructX3(),
					X3_VIDEBOX,
					IlvFalse,
					"%s%s%d%s%d%d",
					getVideBoxFinMatiere(),
					"null",
					0,
					getComposantProcedure(),
					4,
					getVideBoxFinMatiereOblig());
		}

		setIndicateurProcedure(0);
	}
	else
	{
		getInterface()->setSequenceAppelante(0);
		getInterface()->getPanneauAppelant()->setSensitive(true);
	}
}

//--------------------------------------------------------------
void AdxData::SendX3_Reconciliation() 
{
	if (getInterface()->getSequenceAppelante() == 0)
	{
		getInterface()->getPanneauAppelant()->setSensitive(false);
		getInterface()->setSequenceAppelante(15);
		X3Ilog_SendX3(getInterface()->getStructX3(),
				X3_RECONCILIATION,
//				IlvTrue,
				IlvFalse,
				"");
	}
	else
	{
		getInterface()->setSequenceAppelante(0);
		getInterface()->getPanneauAppelant()->setSensitive(true);
	}
}


//--------------------------------------------------------------
void AdxData::sendX3_Etalonnage(int sta)
// sta = 1 :etalonnage KO sur une balance à étalonner
// sta = 2 :etalonnage KO sur une balance pas à étalonner
// sta = 3 :etalonnage OK
{	
	saveLigneEtalonnage();
	if (sta==1)
	{
		X3Ilog_SendX3(getInterface()->getStructX3(),
				X3_FINETALONNAGE_KO_KO,
				IlvTrue,
				"");
	}
	if (sta==2)
	{
		X3Ilog_SendX3(getInterface()->getStructX3(),
				X3_FINETALONNAGE_OK_KO,
				IlvTrue,
				"");
	}
	if (sta==3)
	{
		X3Ilog_SendX3(getInterface()->getStructX3(),
				X3_FINETALONNAGE_OK,
				IlvTrue,
				"");
	}

}

//--------------------------------------------------------------
void AdxData::SendX3_Aide()
{
// Neutralisé car l'appel de l'aide fonctionne différemment
//	if (getInterface()->getSequenceAppelante() == 0)
//	{
//		getInterface()->getPanneauAppelant()->setSensitive(false);
//		getInterface()->setSequenceAppelante(16);
		X3Ilog_SendX3(getInterface()->getStructX3(),
				X3_AIDE,
//				IlvTrue,
				IlvFalse,
				"");
//	}
//	else
//	{
//		getInterface()->setSequenceAppelante(0);
//		getInterface()->getPanneauAppelant()->setSensitive(true);
//	}
}
	
//--------------------------------------------------------------
void AdxData::setLanguage(const char* str)
{
	if( _language != 0) {
		delete [] _language;
	}
	_language = new char[ strlen( str) +1];
	strcpy( _language, str);
}

//--------------------------------------------------------------
void AdxData::setUtilisateur(const char* str)
{
	if( _utilisateur != 0) {
		delete [] _utilisateur;
	}
	_utilisateur = new char[ strlen( str) +1];
	strcpy( _utilisateur, str);
}

//--------------------------------------------------------------
void AdxData::setApplication(const char* str)
{
	if( _application != 0) {
		delete [] _application;
	}
	_application = new char[ strlen( str) +1];
	strcpy( _application, str);
}

//--------------------------------------------------------------
void AdxData::setLieu(const char* str)
{
	if( _lieu != 0) {
		delete [] _lieu;
	}
	_lieu = new char[ strlen( str) +1];
	strcpy( _lieu, str);
}

//--------------------------------------------------------------
void AdxData::setBox(const char* str)
{
	if( _box != 0) {
		delete [] _box;
	}
	_box = new char[ strlen( str) +1];
	strcpy( _box, str);
}

//--------------------------------------------------------------
void AdxData::setOuvertureBox(const char* str)
{
	if( _ouvertureBox != 0) {
		delete [] _ouvertureBox;
	}
	_ouvertureBox = new char[ strlen( str) +1];
	strcpy( _ouvertureBox, str);
}

//---------------------------------------------------------------------------
void AdxData::setOuvertureBoxOblig( const int p)
{
	_ouvertureBoxOblig = p;
}

//--------------------------------------------------------------
void AdxData::setVideBoxFinOF(const char* str)
{
	if( _videBoxFinOF != 0) {
		delete [] _videBoxFinOF;
	}
	_videBoxFinOF = new char[ strlen( str) +1];
	strcpy( _videBoxFinOF, str);
}

//---------------------------------------------------------------------------
void AdxData::setVideBoxFinOFOblig( const int p)
{
	_videBoxFinOFOblig = p;
}

//--------------------------------------------------------------
void AdxData::setVideBoxFinPhase(const char* str)
{
	if( _videBoxFinPhase != 0) {
		delete [] _videBoxFinPhase;
	}
	_videBoxFinPhase = new char[ strlen( str) +1];
	strcpy( _videBoxFinPhase, str);
}

//---------------------------------------------------------------------------
void AdxData::setVideBoxFinPhaseOblig( const int p)
{
	_videBoxFinPhaseOblig = p;
}

//--------------------------------------------------------------
void AdxData::setVideBoxFinMatiere(const char* str)
{ // SMO : STD-PR-OO1 : Pesee Matiere
	if( _videBoxFinMatiere != 0)
	{
		delete [] _videBoxFinMatiere;
	}
	_videBoxFinMatiere = new char[ strlen( str) +1];
	strcpy( _videBoxFinMatiere, str);
}

//---------------------------------------------------------------------------
void AdxData::setVideBoxFinMatiereOblig( const int p)
{ // SMO : STD-PR-OO1 : Pesee Matiere
	_videBoxFinMatiereOblig = p;
}

//--------------------------------------------------------------
void AdxData::setPeseePartielle(const char* str)
{
	if( _peseePartielle != 0) {
		delete [] _peseePartielle;
	}
	_peseePartielle = new char[ strlen( str) +1];
	strcpy( _peseePartielle, str);
}

//---------------------------------------------------------------------------
void AdxData::setPeseePartielleCode( const int p)
{
	_peseePartielleCode = p;
}

//--------------------------------------------------------------
void AdxData::setModifLigneStock(const char* str)
{
	if( _modifLigneStock != 0) {
		delete [] _modifLigneStock;
	}
	_modifLigneStock = new char[ strlen( str) +1];
	strcpy( _modifLigneStock, str);
}

//---------------------------------------------------------------------------
void AdxData::setModifLigneStockCode( const int p)
{
	_modifLigneStockCode = p;
}

//--------------------------------------------------------------
void AdxData::setRecontroleArticle(const char* str)
{
	if( _recontroleArticle != 0) {
		delete [] _recontroleArticle;
	}
	_recontroleArticle = new char[ strlen( str) +1];
	strcpy( _recontroleArticle, str);
}

//---------------------------------------------------------------------------
void AdxData::setRecontroleArticleCode( const int p)
{
	_recontroleArticleCode = p;
}

//--------------------------------------------------------------
void AdxData::setRecontroleCuve(const char* str)
{
	if( _recontroleCuve != 0)
	{
		delete [] _recontroleCuve;
	}
	_recontroleCuve = new char[ strlen( str) +1];
	strcpy(_recontroleCuve, str);
}

//---------------------------------------------------------------------------
void AdxData::setRecontroleCuveCode( const int p)
{
	_recontroleCuveCode = p;
}

//---------------------------------------------------------------------------
void AdxData::setPrioriteAllocation(const char* str)
{
	if( _prioriteAllocation != 0)
	{
		delete [] _prioriteAllocation;
	}
	_prioriteAllocation = new char[ strlen( str) +1];
	strcpy(_prioriteAllocation, str);
}
//---------------------------------------------------------------------------
void  AdxData::setPrioriteAllocationCode( const int p)
{
	_prioriteAllocationCode = p;
}
//---------------------------------------------------------------------------
void AdxData::setDepotBox(const char* str)
{
	if( _depotBox != 0)
	{
		delete [] _depotBox;
	}
	_depotBox = new char[ strlen( str) +1];
	strcpy( _depotBox, str);
}
//---------------------------------------------------------------------------
void   AdxData::setEmplacementBox(const char* str)
{
	if( _emplacementBox != 0)
	{
		delete [] _emplacementBox;
	}
	_emplacementBox = new char[ strlen( str) +1];
	strcpy( _emplacementBox, str);
}
//---------------------------------------------------------------------------
void  AdxData::setAllocationAuto(const char* str)
{
	if( _allocationAuto != 0)
	{
		delete [] _allocationAuto;
	}
	_allocationAuto = new char[ strlen( str) +1];
	strcpy(_allocationAuto, str);
}
//---------------------------------------------------------------------------
void  AdxData::setAllocationAutoCode( const int p)
{
	_allocationAutoCode = p;
}

//---------------------------------------------------------------------------
void   AdxData::setChargementListMat( const int p)
{
	_chargementListMat  = p;
}
//--------------------------------------------------------------------------
void   AdxData::setApplicationTolerance( const int p)
{
	 _applicationTolerance  = p;
}
//--------------------------------------------------------------------------
void   AdxData::setExceedingTolerancePos( const int p)
{
	 _exceedingTolerancePos  = p;
}
//--------------------------------------------------------------------------
void   AdxData::setDecoupageCAB(const int p)
{
	_decoupageCAB = p;
}
//--------------------------------------------------------------------------
void AdxData::setLibDecoupageCAB(const char* str)
{
	if( _libDecoupageCAB != 0) {
		delete [] _libDecoupageCAB;
	}
	_libDecoupageCAB =  new char[ strlen( str) +1];
	strcpy( _libDecoupageCAB, str);
}
//--------------------------------------------------------------------------
void  AdxData::setTypeCAB(const int p)
{
	_typeCAB = p;
}
//--------------------------------------------------------------------------
void  AdxData::setSuppBlanc(const int p)
{
	_suppBlanc = p;
}
//--------------------------------------------------------------------------
void  AdxData::setNumZoneArt(const int p)
{
	_numZoneArticle = p;
}
//-------------------------------------------------------------------------
void  AdxData::setSeparateurArt(const char* str)
{
	if( _separateurArt != 0) {
		delete [] _separateurArt;
	}
	_separateurArt =  new char[ strlen( str) +1];
	strcpy( _separateurArt, str);
}
//--------------------------------------------------------------------------
void  AdxData::setNumZoneLot(const int p)
{
	_numZoneLot = p;
}
//--------------------------------------------------------------------------
void  AdxData::setSeparateurLot(const char* str)
{
	if( _separateurLot != 0) {
		delete [] _separateurLot;
	}
	_separateurLot =  new char[ strlen( str) +1];
	strcpy( _separateurLot, str);
}
//--------------------------------------------------------------------------
void  AdxData::setNumZoneSlo(const int p)
{
	_numZoneSlo = p;
}
//--------------------------------------------------------------------------
void  AdxData::setSeparateurSlo(const char* str)
{
	if( _separateurSlo != 0) {
		delete [] _separateurSlo;
	}
	_separateurSlo =  new char[ strlen( str) +1];
	strcpy( _separateurSlo, str);
}
//--------------------------------------------------------------------------
void  AdxData::setLongueurArt(const int p)
{
	_longueurArt = p;
}
//--------------------------------------------------------------------------
void  AdxData::setDebutArt(const int p)
{
	_debutArt = p;
}
//--------------------------------------------------------------------------
void AdxData::setLongueurLot(const int p)
{
	_longueurLot = p;
}
//--------------------------------------------------------------------------
void AdxData::setLongueurLot2(const int p)
{
	_longueurLot2 = p;
}
//--------------------------------------------------------------------------
void AdxData::setDebutLot(const int p)
{
	_debutLot = p;
}
//--------------------------------------------------------------------------
void AdxData::setLongueurSlo(const int p)
{
	_longueurSlo = p;
}
//--------------------------------------------------------------------------
void AdxData::setDebutSlo(const int p)
{
	_debutSlo = p;
}
//---------------------------------------------------------------------------
void AdxData::setRedressementNegatif( const int p)
{
	_redressementNegatif = p;
}

//---------------------------------------------------------------------------
void AdxData:: setCodeOFEnCoursPesee( const int p)
{
	_codeOFEnCoursPesee = p;
}

//---------------------------------------------------------------------------
void AdxData::setLibOFEnCoursPesee(const char* str)
{
	if( _libOFEnCoursPesee != 0) {
		delete [] _libOFEnCoursPesee;
	}
	_libOFEnCoursPesee = new char[ strlen( str) +1];
	strcpy( _libOFEnCoursPesee, str);
}

//---------------------------------------------------------------------------
void AdxData::setCodeOFPeseBox( const int p)
{
	_codeOFPeseBox = p;
}

//---------------------------------------------------------------------------
void AdxData::setLibOFPeseBox(const char* str)
{
	if( _libOFPeseBox != 0) {
		delete [] _libOFPeseBox;
	}
	_libOFPeseBox = new char[ strlen( str) +1];
	strcpy( _libOFPeseBox, str);
}

//---------------------------------------------------------------------------
void AdxData::setCodeMatEnCoursPesee( const int p)
{
	_codeMatEnCoursPesee = p;
}

//---------------------------------------------------------------------------
void AdxData::setLibMatEnCoursPesee(const char* str)
{
	if( _libMatEnCoursPesee != 0) {
		delete [] _libMatEnCoursPesee;
	}
	_libMatEnCoursPesee = new char[ strlen( str) +1];
	strcpy( _libMatEnCoursPesee, str);
}

//---------------------------------------------------------------------------
void AdxData::setCodeMatPese( const int p)
{
	_codeMatPese = p;
}

//---------------------------------------------------------------------------
void AdxData::setLibMatPese(const char* str)
{
	if( _libMatPese != 0) {
		delete [] _libMatPese;
	}
	_libMatPese = new char[ strlen( str) +1];
	strcpy( _libMatPese, str);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv1(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv1, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv2(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv2, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv3(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv3, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv4(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv4, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv5(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv5, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv6(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv6, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv7(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv7, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv8(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv8, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv9(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv9, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv10(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv10, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv11(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv11, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv12(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv12, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setSzCheminCsv13(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv13, deb, fin);
}

//--------------------------------------------------------------
void AdxData::setNbPhasesPesees(const int nb)
{
	_nbPhasesPesees = nb;
}

//--------------------------------------------------------------
void AdxData::setNbLotsPeses(const int nb)
{
	_nbLotsPeses = nb;
}

//--------------------------------------------------------------
//X3-67237: Added below block to set the UsrWei flag
void AdxData::setSzCheminCsv14(const char* deb, const char* fin)
{	
	sprintf (_szCheminCsv14, deb, fin);
}

void AdxData::setUsrWei(const int nb)
{
	_usrwei = nb;
}

void AdxData::setBoxPwd(const int nb)
{
	_boxpwd = nb;
}

void AdxData::setEwoPwd(const int nb)
{
	_ewopwd = nb;
}

void AdxData::setPhaPwd(const int nb)
{
	_phapwd = nb;
}

void AdxData::setMatPwd(const int nb)
{
	_matpwd = nb;
}

void AdxData::setUserID(const char* str)
{
	if( _X3UserID != NULL) 
	{
		delete [] _X3UserID;
	}

	_X3UserID = new char[ strlen( str) +1];
	strcpy( _X3UserID, str);
}

void AdxData::setX3Ver(const int nb)
{
	_X3Ver = nb;
}

//X3-67237: end of added block

//--------------------------------------------------------------
void AdxData::setIndicateurProcedure(int i)
{
	_indicateurProcedure = i;

	if (i == 0 || i == 1)
	{
		_composantProcedure				= NULL;  
		_OFProcedure					= NULL;
		_phaseProcedure					= NULL;
		_attenteProcedureFinComposant	= false; 
		_attenteProcedureFinOF			= false;
		_attenteProcedureFinPhase		= false;
	}

	if (i == 2)
	{
		 _OFProcedure		= _currentOrder;
		 _phaseProcedure	= _currentPhase;
	}

	if (i == 3)
	{
		_OFProcedure		= _currentOrder;
		_phaseProcedure		= NULL;

	}

	// SMO : STD-PR-OO1 : Pesee Matiere : 28/07/2010
	if (i == 4)
	{
		_composantProcedure				= getPseMatCurrentMat();	 
		//_attenteProcedureFinComposant	= true;

	}
}

//--------------------------------------------------------------
void AdxData::PositionneProcedurePhaseAttente()
{
	//if(getInterface()->getFonctionEnCours() == 1|| getInterface()->getFonctionEnCours() == 3)
	//{
		if (strcmp (getVideBoxFinPhase(), "") != 0)
		{
			if (getVideBoxFinPhaseOblig() == 1 
				|| getVideBoxFinPhaseOblig() == 2)
			{
				setIndicateurProcedure(2);
				if (getVideBoxFinPhaseOblig() == 2)
					_attenteProcedureFinPhase = true;
			}
			else 
				setIndicateurProcedure(0);
		}
		else 
			setIndicateurProcedure(0);
	//}
}

//--------------------------------------------------------------
void AdxData::PositionneProcedureOFAttente()
{
	//if(getInterface()->getFonctionEnCours() == 1|| getInterface()->getFonctionEnCours() == 3)
	//{
		// Vide Fin OF prioritaire
		if ( strcmp(getVideBoxFinOF(), "") != 0)
		{
			if (getVideBoxFinOFOblig() == 1
				||getVideBoxFinOFOblig() == 2 )
			{
				setIndicateurProcedure(3);
				if (getVideBoxFinOFOblig() == 2 )
					_attenteProcedureFinOF = true;
			}
			else 
				setIndicateurProcedure(0);
		}
		else
		// s'il n'existe pas on gere le vide fin phase
		{
			PositionneProcedurePhaseAttente(); 
		}
	//}
}

//--------------------------------------------------------------
void AdxData::PositionneProcedureComposantAttente()
{
	if (strcmp (getVideBoxFinMatiere(), "") != 0)
	{
		if (getVideBoxFinMatiereOblig() == 1
			|| getVideBoxFinMatiereOblig() == 2)
		{
			setIndicateurProcedure(4);
			if (getVideBoxFinMatiereOblig() == 2)
				_attenteProcedureFinComposant = true;
		} 
		else
			setIndicateurProcedure(0);
	}
	else 
		setIndicateurProcedure(0);
}

//---------------------------------------------------------------------------
void AdxData::lanceProcedureEnAttente()
{
	if (_attenteProcedureFinOF == true){
		SendX3_Procedure(3);
		return;
	}
	if (_attenteProcedureFinPhase == true){
		SendX3_Procedure(2);
		return; 
	}
	if (_attenteProcedureFinComposant == true){
		SendX3_Procedure(4); 
		return; // SMO : 28/07/2010 
	}
}

//--------------------------------------------------------------
// copie lot par lot la liste de lot passee en parametre dans _lotList de AdxData
//		pour restauration par exemple
void AdxData::setLotList(IlList* lotList)
{
	if (_nbLots > 0)
	{
		for (int i = 0; i < _nbLots; i++)
		{
			delete (AdxLot*)(*_lotList)[i];
		}
	}
	_nbLots = 0;
	_lotList->empty();
	getCurrentComposant()->setQuantiteAllouee(0);
	for (int i = 0; i < lotList->length(); i++)
	{
		AdxLot* lot = (AdxLot*) (*lotList)[i];
		getCurrentComposant()->setQuantiteAllouee(
							getCurrentComposant()->getQuantiteAllouee()
							+ lot->getQuantiteAllouee());
		getLotList()->append(lot->copy());
	}
	_nbLots = lotList->length();
}

//--------------------------------------------------------------
// compare lot par lot la liste de lot passee en parametre avec _lotList de AdxData
//		retourne true si elle sont identique
bool AdxData::compareLotList(IlList* lotList)
{
	if (_nbLots != lotList->length())
		return false;
	AdxLot* lot1;
	AdxLot* lot2;
	if (_nbLots > 0)
	{
		for (int i = 0; i < _nbLots; i++)
		{
			lot1 = (AdxLot*)(*_lotList)[i];
			lot2 = (AdxLot*)(*lotList)[i];
			if (
				strcmp( lot1->getLot(), lot2->getLot()) != 0 ||
				strcmp( lot1->getEmplacement(), lot2->getEmplacement()) != 0 ||
				strcmp( lot1->getStatut(), lot2->getStatut()) != 0 ||
				strcmp( lot1->getLibStatut(), lot2->getLibStatut()) != 0 ||
				lot1->getQuantiteAllouee() != lot2->getQuantiteAllouee() ||
				lot1->getQuantiteDisponible() != lot2->getQuantiteDisponible() ||
				lot1->getTitre() != lot2->getTitre() ||
				lot1->getDatePeremption()->getDay() != lot2->getDatePeremption()->getDay() ||
				lot1->getDatePeremption()->getMonth() != lot2->getDatePeremption()->getMonth() ||
				lot1->getDatePeremption()->getYear() != lot2->getDatePeremption()->getYear() ||
				strcmp( lot1->getUnite(), lot2->getUnite()) != 0 ||
				strcmp( lot1->getCuve(), lot2->getCuve()) != 0 ||
				strcmp( lot1->getVanne(), lot2->getVanne()) != 0 ||
				lot1->getChrono() != lot2->getChrono() ||
				lot1->getSequence() != lot2->getSequence())
				return false;
		}
	}
	return true;
}

//--------------------------------------------------------------
void AdxData::razListeFicheISM(void)
{
if (getNbFichesISM() > 0)
{
	for (int i = 0; i <getNbFichesISM(); i++)
	{
		delete (AdxFicheISM*)(* getFicheISMList())[i];
	}
}
setNbFichesISM(0);
getFicheISMList()->empty();
_currentFicheISM = NULL;

}
//--------------------------------------------------------------
void  AdxData::razListeOF(void)
{
if (getNbOrders() > 0)
{
	for (int i = 0; i <getNbOrders(); i++)
	{
		delete (AdxOrder*)(* getOrderList())[i];
	}
}
setNbOrders(0) ;
getOrderList()->empty();
_currentOrder = NULL;

}
//--------------------------------------------------------------
void AdxData::razListePhase(void)
{
if (getNbPhases() > 0)
{
	for (int i = 0; i <getNbPhases(); i++)
	{
		delete (AdxPhase*)(* getPhaseList())[i];
	}			
}
setNbPhases(0);
getPhaseList()->empty();
_currentPhase = NULL;

}
//--------------------------------------------------------------
void AdxData::razListeComposant(void)
{
if(_composantList_Art != NULL)
{
	_composantList_Art->empty();
	setNbComposants_Art(0);
}
_currentComposant = NULL;
}
//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
void AdxData::init(AdxInterface* m_interface)
{
	_szCheminCsv1					= new char[_MAX_PATH];
	_szCheminCsv2					= new char[_MAX_PATH];
	_szCheminCsv3					= new char[_MAX_PATH];
	_szCheminCsv4					= new char[_MAX_PATH];
	_szCheminCsv5					= new char[_MAX_PATH];
	_szCheminCsv6					= new char[_MAX_PATH];
	_szCheminCsv7					= new char[_MAX_PATH];
	_szCheminCsv8					= new char[_MAX_PATH];
	_szCheminCsv9					= new char[_MAX_PATH];
	_szCheminCsv10					= new char[_MAX_PATH];
	_szCheminCsv11					= new char[_MAX_PATH];
	_szCheminCsv12					= new char[_MAX_PATH];
	_szCheminCsv13					= new char[_MAX_PATH];
	_szCheminCsv14					= new char[_MAX_PATH];		//X3-67237
	_dateJour						= NULL;
	_language						= NULL;
	_utilisateur					= NULL;
	_application					= NULL;
	_lieu							= NULL;
	_box							= NULL;
	_ouvertureBox					= NULL;
	_videBoxFinOF					= NULL;
	_videBoxFinPhase				= NULL;
	_videBoxFinMatiere				= NULL;					// SMO : STD-PR-OO1 : Pesee Matiere
	_peseePartielle					= NULL;
	_modifLigneStock				= NULL;
	_recontroleArticle				= NULL;
	_recontroleCuve					= NULL;
	_prioriteAllocation				= NULL;
	_allocationAuto					= NULL;
	_depotBox						= NULL;
	_emplacementBox					= NULL;
	_redressementNegatif			= NULL;
	_orderList						= new IlList;
	_nbOrders						= 0;
	_balanceList					= new IlList;
	_nbBalances						= 0;
	_ficheISMList					= new IlList;
	_nbFichesISM					= 0;
	_ficheISMRecipientList			= new IlList;
	_nbFichesISMRecipient			= 0;
	_recipientList					= new IlList;
	_nbRecipients					= 0;
	_phaseList						= new IlList;
	_nbPhases						= 0;
	_lotList						= new IlList;
	_nbLots							= 0;
	_unitList						= new IlList;
	_nbUnits						= 0;
	_etalonList						= new IlList;
	_nbEtalons						= 0;
	_currentOrder					= NULL;
	_currentPhase					= NULL;
	_currentComposant				= NULL;
	_currentFicheISM				= NULL;
	_currentLot						= NULL;
	_currentBalance					= NULL;
	_interface						= m_interface;
	_composantProcedure				= NULL;					// SMO : 28/07/2010
	_OFProcedure					= NULL;
	_phaseProcedure					= NULL;
	_attenteProcedureFinComposant	= false;				// SMO : 28/07/2010
	_attenteProcedureFinOF			= false;
	_attenteProcedureFinPhase		= false;
	_libOFEnCoursPesee				= NULL;
	_libOFPeseBox					= NULL;
	_libMatEnCoursPesee				= NULL;
	_libMatPese						= NULL;
	_composantList_Art				= new IlList;
	_nbComposants_Art				= 0;
	_peseeLancee					= false;
	_enCoursDePeseeParArticle		= false;			// mm 05.11
	_libDecoupageCAB			    = NULL;
	_separateurArt					= NULL;
	_separateurLot					= NULL;
	_separateurSlo					= NULL;
	_lockedOrder					= NULL;				//115769 mm 04.2016

	// SMO -------------------------------------
	_pseMat_currentMat				= NULL;
	_pseMat_currentMatLib			= NULL;
	_pseMat_currentIndexComposant	= 0 ;
	_pseMat_matiereBegin		    = false;			// mm 08.10

	_usrwei							= 0;				//X3-67237
	_boxpwd							= 0;				//X3-67237
	_ewopwd							= 0;				//X3-67237
	_phapwd							= 0;				//X3-67237
	_matpwd							= 0;				//X3-67237
	_X3UserID						= NULL;				//X3-67237
	_X3Ver							= 0;				//X3-67237

	// -------- 06.04 Unicode	
	_stringUTF8 = NULL;
	_stringMBS = NULL;
	// --------

	// langage par défaut pour les premiers messages d'erreur
	// avant lecture des paramètres
    setLanguage("ENG");

// lecture du fichier de demarrage X3 => uti,appli,date,lieu,box,...

}

// 06.04 Unicode
const char* AdxData::getStringUnicode(AdxCsvLine* line, long index) 
{

	LPSTR  stringMBSBuffer = NULL;

	setstringUTF8((char*)line->getString(index));

	if (Unicode_Utf8ToMbyte(getstringUTF8(), &stringMBSBuffer, getCodepage(), -1) != 0)
	{
		setstringMBS(stringMBSBuffer);
		free(stringMBSBuffer);
		return (const char*)getstringMBS();
	}
	else
	{
		return line->getString(index);
	}
}

////////////////////////////////////////////////////////

//X3-67237 - Added Below function to check user credentials
bool AdxData::SendX3_CheckCredentials(bool GetCred, bool ShowMsg) 
{
	bool dataOK;

	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "SendX3_CheckCredentials - Start (_X3Ver = " << getX3Ver() << ")" << endl;
	}

	if ( !(getX3Ver() == 11) )
	{
		setUserID(getUtilisateur());
		return true;
	}

	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "SendX3_CheckCredentials - calling X3Ilog_SendX3" << endl;
	}

	if ( GetCred == true )
	{
		X3Ilog_SendX3(getInterface()->getStructX3(),
			          X3_USER_CREDENTIALS,
				      IlvFalse,
					  "");
	}

	dataOK = loadUserID(getSzCheminCsv14());
	if ( ! dataOK )
	{
		if(this->_interface->getTraceMode() == 1)
		{
			this->_interface->_traceFile<< "SendX3_CheckCredentials - Failed to load UserID" << endl;
		}
	
		return false;
	}

	if (strcmp (getUserID(),"xxxxxxxx") == 0)
	{
		if(this->_interface->getTraceMode() == 1)
		{
			this->_interface->_traceFile<< "SendX3_CheckCredentials - X3 Credentials Failed (" << getUserID() << ")" << endl;
		}

		if ( ShowMsg )
		{
			getInterface()->getMessage()->setPanneauAppelant(NULL);
			getInterface()->envoieMessage("&UserPwd",false);
		}
	
		return false;
	}

	if(this->_interface->getTraceMode() == 1)
	{
		this->_interface->_traceFile<< "SendX3_CheckCredentials - Success (UserID = " << getUserID() << ")" << endl;
	}

	return true;
}
//X3-67237 - End of added block for user credentials check
////////////////////////////////////////////////////////

