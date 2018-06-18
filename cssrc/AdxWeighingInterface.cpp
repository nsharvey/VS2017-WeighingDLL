// AdxWeighingInterface.cpp
// ------------------------
// project : Adonix X3 Scales
// author : MC
// V130 : MC 2001.05.28
//--------------------------------------------------------------
//

// sr 11.02
#include "stdafx.h"
#include <cmath>

#include "AdxWeighingInterface.h"
#include "AdxMeid5.h"
#include "AdxMeid7.h"
#include "AdxMepm.h"
#include "AdxSartorius.h"
#include "AdxMSICS.h"
#include "AdxMultiCom.h"
#include "AdxInterface.h"
#include "AdxPesee_OF.h"
#include "AdxPesee_Etalon.h"
#include "AdxBalance.h"
#include "AdxLot.h"
#include "AdxFicheISM.h"
#include "AdxData.h"
#include "AdxComposant.h"
#include "AdxMessage.h"
#include "AdxGadgetContainer.h"
#include "AdxRecipient.h"					// mm 11.08
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>							// 06.04 TRACE

using std::endl;							// 06.04 TRACE

/*
//--------------------------------------------------------------
// Traitement de pes�e
//
static DWORD weighingProc(AdxWeighingInterface* weighingInterface)
{

//	SetEvent(port->_hEventThread);

	while (weighingInterface->_bActive)
	{
		DWORD dwWaitResult;				
		dwWaitResult = WaitForSingleObject(weighingInterface->_hEventWeighing,INFINITE);
		switch (dwWaitResult)
		{
		case WAIT_OBJECT_0:
			{
				weighingInterface->manualMode();
				break;
			}
		default:
			{
			// some other error occurred
			}
		}//Switch

		ResetEvent(weighingInterface->_hEventWeighing);
//		SetEvent(port->_hEventIO);
	}
	return TRUE;
}
*/
//--------------------------------------------------------------
AdxWeighingInterface::~AdxWeighingInterface() {
	if( _weighingShortMessage != NULL)
		delete [] _weighingShortMessage;
	if( _weighingMessage != NULL)
		delete [] _weighingMessage;
	if( _resWeighingMessage != NULL)
		delete [] _resWeighingMessage;
	if( _weightUnit != NULL)
		delete [] _weightUnit;
	if( _resWeightUnit != NULL)
		delete [] _resWeightUnit;
//	if( _balance != NULL)
//		delete [] _balance;
	if( _meid5 != NULL)
		delete [] _meid5;
	if( _meid7 != NULL)
		delete [] _meid7;
	if( _mepm != NULL)
		delete [] _mepm;
	if( _sartorius != NULL)
		delete [] _sartorius;
	if( _multiCom != NULL)
		delete [] _multiCom;
	// On ferme le mutex
	CloseHandle(_hMutexStopPesee);
	CloseHandle(_hMutexCancel);
	CloseHandle(_hMutexValid);
	CloseHandle(_hMutexComm);
/*
	_bActive = FALSE;
		
	// Release the worker threads
	if(_hThread != NULL)
	{
		TerminateThread(_hThread,0);
		WaitForSingleObject(_hThread,10000);
		_dwThreadID = 0;
		_hThread = NULL;
//		delete _hThread;
	}

	if(_hEventWeighing != NULL)
	{
		CloseHandle(_hEventWeighing);
		_hEventWeighing = NULL;
//		delete _hEventWeighing;
	}
*/
}

//--------------------------------------------------------------
AdxWeighingInterface::AdxWeighingInterface(AdxInterface* interf) :
	_weighingOperation					(RAZ),
	_weighingReturnOp					(RAZ),
	_weighingOrder						(DISPL),
	_weighingStatus						(OK_STA),
	_driverStatus						(OK),
	_weight								(0.0),
	_resNetWeight						(0.0),
	_resGrossWeight						(0.0),
	_tare								(0.0),
	_tareUnitBal						(0.0),
	_resTare							(0.0),
	_weighingShortMessage				(NULL),
	_weighingMessage					(NULL),
	_resWeighingMessage					(NULL),
	_weightUnit							(NULL),
	_resWeightUnit						(NULL),
	_balance							(NULL),
	_scaleNumber						(0),
	_meid5								(NULL),
	_meid7								(NULL),
	_mepm								(NULL),
	_sartorius							(NULL),
	_multiCom							(NULL),
	_msgWaitingTime						(0),
	_weighingFlag						(0),
    _matiere1Pesee						(false)
//	_hThread							(NULL),
//	_dwThreadID							(0),
//	_hEventWeighing                     (NULL),
//	_bActive							(FALSE)
{
	setInterface(interf);
	// Cr�ation du mutex pour la fin de pes�e
	_hMutexStopPesee = CreateMutex( NULL,               // pas d'attributs de s�curit�
									TRUE,               // appartient au thread
									"MutexEndWeighing");// nom du mutex
	_hMutexCancel = CreateMutex( NULL,					// pas d'attributs de s�curit�
								TRUE,					// appartient au thread
								"MutexCancel");			// nom du mutex
	_hMutexValid = CreateMutex( NULL,					// pas d'attributs de s�curit�
								TRUE,					// appartient au thread
								"MutexValid");			// nom du mutex
	_hMutexComm = CreateMutex( NULL,					// pas d'attributs de s�curit�
								TRUE,					// appartient au thread
								"MutexComm");			// nom du mutex
	// Initialisation de l'indicateur de fin de pes�e
	this->setStopPesee(false);
	this->setCancel(false);
	this->setValid(false);
}
//--------------------------------------------------------------
// Traitement de l'ordre de pes�e
//
void AdxWeighingInterface::weighingOrderTreatment(bool bCheckPlate)
{

//	if (!SetEvent(_hEventWeighing))
//	{
//		return;
//	}
// V�rification validit� ordre

// V�rification pr�sence balance

// V�rification port de communication

// Pr�paration de l'ordre d'appel au driver
	manualMode(bCheckPlate);
}

//--------------------------------------------------------------
// Traitement de l'ordre de pes�e en mode manuel
//
void AdxWeighingInterface::manualMode(bool bCheckPlate)
{
    AdxBalance* balance = getBalance();

	WeighingOrder order = getWeighingOrder();
	if (getInterface()->getTraceMode() == 1)
    {
		getInterface()->_traceFile << "AdxWeighingInterface::manualMode Entree" << endl;
		getInterface()->_traceFile << "\t Ordre = "<<order<<" bCheckPlate = "<<bCheckPlate << endl;
		if(balance != NULL)
		{
			getInterface()->_traceFile << "\t Scale Name = "<<balance->getBalance() <<" IsMultiPlate = "<<balance->IsMultiPlate()  << endl;
		}
    }

	// 06.04 TRACE
	if (getInterface()->getTraceMode() == 1)
		getInterface()->_traceFile << "\t\t\t"<< msg_ord[order] << endl;

	setDriverStatus(OK);		//statut driver OK par d�faut
	setWeighingStatus(OK_STA);  //statut pes�e OK par d�faut
	WeighingStatus sta_err = OK_STA;
	double tareUnitBal = 0;
	double resTare = 0;
	double poidsPese = 0;
	double dernierPoidsPese   = 0;
	double dernierPoidsPeseOk = 0;
	int nb = 0;
	int nbEgal   = 0;
	int nbEgalOk = 0;
	bool bLocalCheckPlate = bCheckPlate;
	// le tarage normal correspond � une pes�� pour mepm

	bool orderModif = false;
	if (order == TAR_M && balance->getNoDriver() == 3)
	{
		order = POIDS_STAB_M;
		orderModif = true;
	}

	switch(order) 
	{
		case RAZ_M:  //mise a zero manuelle
		case RAZ_A:  //mise a zero automatique
			if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile << "------>manualMode RAZ_A : Begin" << endl;
			}
			EmissionReception(D_KBD,balance,false);	 // d�verrouillage clavier
			if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile << "------>manualMode RAZ_A : After D_KBD" << endl;
			}
			setWeighingMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
													"&RemiseAZero"));
			setWeighingShortMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
														 "&Zero"));
			sendMsgScales();
			if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile << "------>manualMode RAZ_A : After sendMsgScales" << endl;
			}
			
			while(1)
			{
				if(getCancel() == true)
				{
					// on annule la pes�e donc on sort de la boucle
					if (getInterface()->getTraceMode() == 1)
						getInterface()->_traceFile << "------>manualMode RAZ_A : Cancel=TRUE Exit Loop 1" << endl;
					break;
				}
				getResponseScales(1,bLocalCheckPlate);
				// On ne doit faire le cont�le qu'une seule fois car ensuite on 
				// trapera le changement de plateau dans les trames
				// On ne fait �a que pour les Mettler car les sartorius n'envoient pas
				// de trames lors de l'appui sur le bouton de changement de balance
				if(getBalance()->getNoDriver() != 5)
				{
					bLocalCheckPlate = false;
				}
				if (getWeighingReturnOp() == TAR) //d�tection bonne reponse et
												  // �limination du msg double ?
				{
					getResponseScales(1,bLocalCheckPlate);
					if((getDriverStatus() == OK) && (getWeighingReturnOp() == RAZ))
					{
						break;
					}
					break;						  //cas o� RAZ �quivalent � TAR z�ro	
				}
				if ((getDriverStatus() == OK) && (getWeighingReturnOp() == RAZ))
				{
					break;    //bonne reponse
				}
				if ((sta_err = statusEvents()) != OK_STA)
				{
					break;
				}
				if ((sta_err = opeEvents()) != OK_STA)
				{
					break;
				}
			}
			if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile << "------>manualMode RAZ_A : After While" << endl;
			}
			break;

		//case DETAR:						//le poids sur le plateau est consid�r�
		//								// comme le poids de tare
		case TAR_M:						//tarage manuel
		case TAR_A:						//tarage automatique
/*
			// changement d'unit� de poids ? propose la modification
			if (strcmp(getWeightUnit(),getResWeightUnit()) != 0)
			{
				EmissionReception(CHG_U,balance);
				if (getDriverStatus() == NO_RESPONSE)//possible sur anomalie sur/souscharge
					getResponseScales(1);//si pas de r�ponse envoie au driver
										 // l'ordre d'attendre un message
				setResWeightUnit(getWeightUnit());
//				balance->setUnite(getResWeightUnit());
			}
*/
			if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile << "------>manualMode TAR_A : Begin" << endl;
			}
			setWeighingMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
													"&Tarage"));
			setWeighingShortMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
														 "&Tare"));
			sendMsgScales();
			if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile << "------>manualMode TAR_A : After sendMsgScales" << endl;
			}
//			EmissionReception(DETAR,balance);
			while(1)
			{
				if(getCancel() == true)
				{
					// on annule la pes�e donc on sort de la boucle
					if (getInterface()->getTraceMode() == 1)
						getInterface()->_traceFile << "------>manualMode TAR_A : Cancel=TRUE Exit Loop 2" << endl;
					break;
				}
				getResponseScales(1,bLocalCheckPlate);
				if(getBalance()->getNoDriver() != 5)
				{
					bLocalCheckPlate = false;
				}
				if (getWeighingReturnOp() == TAR)
				{
					if (strcmp(getWeightUnit(),getResWeightUnit()) != 0)
					{
						// reconvertit la tare pes�e
						resTare = getInterface()->getDonnees()->convertir(
							getResTare(),
							getResWeightUnit(),
							getWeightUnit());
						setResTare(resTare);
//						sta_err = CHG_PDS_UNIT;
					}
					break;
				}
				if ((sta_err = statusEvents()) != OK_STA)
					break;
				if ((sta_err = opeEvents()) != OK_STA)
					break;
			}
			if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile << "------>manualMode TAR_A : After While" << endl;
			}

			break;						//fin du case TAR

		case CONS_TAR_M:				//tarage manuel (net+tare)
		case CONS_TAR_A:				//tarage automatique (net+tare)
/*
			// changement d'unit� de poids ? propose la modification
			if (strcmp(getWeightUnit(),getResWeightUnit()) != 0)
			{
				EmissionReception(CHG_U,balance);
				if (getDriverStatus() == NO_RESPONSE)//possible sur anomalie sur/souscharge
					getResponseScales(1);//si pas de r�ponse envoie au driver
										 // l'ordre d'attendre un message
//				balance->setUnite(getResWeightUnit());
			}
*/
			setWeighingMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
													"&ConsigneTare"));
			setWeighingShortMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
														 "&Cons"));
			// convertit la tare en unit� poids balance
			if (getTare() != 0)
				tareUnitBal = getInterface()->getDonnees()->convertir(
					getTare(),
					getWeightUnit(),
					getResWeightUnit());
			setTareUnitBal(tareUnitBal);

//			sendMsgScales();

			EmissionReception(TAR,balance,bLocalCheckPlate);

			if (getDriverStatus() == NO_RESPONSE) //possible sur anomalie sur/souscharge
				getResponseScales(2,bLocalCheckPlate);
			if (getDriverStatus() == NO_RESPONSE) //si le silence persiste ->anomalie
				sta_err = NO_RESP;
			else
				sta_err = statusEvents();

			break;

		case POIDS_IMDT:				//acquisition d'un poids instantane automatique
										// d�tourn� pour test balance connect�e
			setDriverStatus(NO_RESPONSE);		//statut driver ERREUR
						// sr 03.12 APCPRd-511 Envoyer ou non un message selon param�tre de X3scales.ini
			if(getInterface()->getScaMsgMode() ==0)
			{
				sendMsgScales();
			}
			for (nb=0; nb <2; nb++)
			{
	  			EmissionReception(PDS_I,balance,bLocalCheckPlate);
				if (((getWeighingReturnOp() == PDS_I) && (getDriverStatus() == OK))
					|| ((getWeighingReturnOp() == PDS_I)
						&& (getDriverStatus() == DYNAMIQUE))
					|| (getWeighingReturnOp() == PDS_S))
				{
					break;
				}
			}

			if (getDriverStatus() == NO_RESPONSE) setDriverStatus(TRANSMIT_ERROR);
			sta_err = statusEvents();
			break;

		case POIDS_STAB_M:				//acquisition d'un poids stable manuel
		case POIDS_STAB_A:				//acquisition d'un poids stable automatique

			EmissionReception(E_KBD,balance,false);  //pendant la pes�e, verrouille
											   // par pr�caution	
/*
			// changement d'unit� de poids ? propose la modification
			if (strcmp(getWeightUnit(),getResWeightUnit()) != 0)
			{
				EmissionReception(CHG_U,balance);
				if (getDriverStatus() == NO_RESPONSE)//possible sur anomalie sur/souscharge
					getResponseScales(1);//si pas de r�ponse envoie au driver
										 // l'ordre d'attendre un message
//				balance->setUnite(getResWeightUnit());
			}
*/
			if (orderModif)
			{
				setWeighingMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
														"&Tarage"));
				setWeighingShortMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
															 "&Tare"));
			}
			else
			{
				char* message = new char[20];
				sprintf(message,"%s %.3f %s",
						IlvGetMessage(getInterface()->getDisplay(),	"&Peser"),
						getWeight(), 
						getWeightUnit()); 
				setWeighingMessage(message);
				delete [] message;
	
				setWeighingShortMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
														"&Pesee"));
			}
			// sr 03.12 APCPRd-511 Envoyer ou non un message selon param�tre de X3scales.ini
			if(getInterface()->getScaMsgMode() ==0)
			{
				sendMsgScales();
			}
			setDriverStatus(NO_RESPONSE); //force � NO_RESPONSE
			if (getInterface()->getTraceMode() == 1)
				getInterface()->_traceFile << "------>manualMode befor while POIDS_STAB_M" << endl;

			while(1)
			{
				// On redispatch les �vennements de l'interface pour �viter les freeze
				//if (getInterface()->getDisplay()->hasEvents())
				//{
				//	getInterface()->getDisplay()->readAndDispatchEvents();
				//}
				if(getCancel() == true)
				{
					// on annule la pes�e donc on sort de la boucle
					if (getInterface()->getTraceMode() == 1)
						getInterface()->_traceFile << "------>manualMode Cancel=TRUE Exit Loop 3" << endl;
					break;
				}
				if(getValid() == true && balance->IsMultiPlate() == true)
				{
					// La pes�e a �t� valid�e
					if (getInterface()->getTraceMode() == 1)
						getInterface()->_traceFile << "------>manualMode Valid=TRUE Exit Loop 3bis" << endl;
					break;
				}
				else if(getValid() == true)
				{						
					// La pes�e a �t� valid�e
					if (getInterface()->getTraceMode() == 1)
						getInterface()->_traceFile << "------>manualMode Valid=TRUE Exit Loop 3ter" << endl;
					break;
				}
				if (getDriverStatus() == NO_RESPONSE)
				{
		  			EmissionReception(PDS_I,balance,bLocalCheckPlate);
					if (((getWeighingReturnOp() == PDS_I) && (getDriverStatus() == OK))
						|| ((getWeighingReturnOp() == PDS_I)
							&& (getDriverStatus() == DYNAMIQUE))
						|| (getWeighingReturnOp() == PDS_S))
					{
						if (_weighingFlag == 0)
							setDriverStatus(NO_RESPONSE); //car DYNAMIQUE est important
														  // pour la suite
						// reconvertit le poids pes�
						poidsPese = getInterface()->getDonnees()->convertir(
							getResWeight(),
							getResWeightUnit(),
							getWeightUnit());
						setResNetWeight(poidsPese);
						
						// d�clenche la mise � jour de la jauge et de l'affichage poids
                        // plus de mise � jour du poids pour le tarage
						if ((_panneauAppelant == getInterface()->getPesee_OF()) & !orderModif)
							getInterface()->getPesee_OF()
								->evolutionPoids();
						if (_panneauAppelant == getInterface()->getPesee_Etalon())
							getInterface()->getPesee_Etalon()
								->evolutionPoids();
						// sr 04.02
						// propose d'arr�ter la pes�e si poids stabilis� et inf�rieur au maxi
						// depuis X essais
						// sr 02.03 la temporisation est maintenant g�r�e par l'utilisateur
						// via le param�tre tempo de la balance
                        // orderModif = oui veut dire tarage avec une MP3000
						if ((_panneauAppelant == getInterface()->getPesee_Etalon())
                            ||(controlePoidsInf()) 
                            ||(getInterface()->getDonnees()->getCurrentComposant()->getCodeAServir() >= 8))
                        {
                            if((!orderModif) & (getWeighingReturnOp() == PDS_S))
						    {
							    if (poidsPese == dernierPoidsPeseOk)
    							{
	    							nbEgalOk += 1;
		    					}
			    				else
				    			{
					    			dernierPoidsPeseOk = poidsPese;
						    		nbEgalOk = 0;
							    }
							    //if (nbEgalOk >= balance->getTempo() )
							    if(
									((balance->getTempo() != 0)&&(nbEgalOk >= balance->getTempo()))
								  )
							    {
								    finPesee();
									this->setStopPesee(true);
								    break;
							    }
								if( getBalance()->getTempo() == 0 && (_panneauAppelant == getInterface()->getPesee_OF()))
								{
								   getInterface()->getPesee_OF()->getvalider()->setSensitive(true);
								   // mm 09.11 - la premi�re mati�re doit �tre totalement  pes�e pour que le Bt V+ soit actif 
								   // (la 1ere matiere ne peut pas �tre partiellement pes�e puis �tre cumul�e � la seconde)
								   //  APCPRD-727 : il faudrait faire la m�me chose quelque soit la mati�re 
								   // sr 01.12 APCPRD-723 Controler ici la fiche ISM
									
								   if ((getInterface()->getDonnees()->getCurrentFicheISM()->getPeseeMultiArticle() == 2 )
								   && (getInterface()->getDonnees()->getCurrentFicheISM()->getModePeseeCode() == 2)	
								   && (getInterface()->getDonnees()->getCurrentFicheISM()->getCodeEmballage() == 3 ||	 //emb mixte
								   getInterface()->getDonnees()->getCurrentFicheISM()->getCodeEmballage() == 1 ))		 //emb interne
								   {	
									    if (controlePoidsSup())
											// Ya t il une mati�re � peser en cumul� apr�s ?
											getInterface()->getPesee_OF()->getvaliderPlus()->setSensitive(true);
										else
											getInterface()->getPesee_OF()->getvaliderPlus()->setSensitive(false);
								   }
								   else
										getInterface()->getPesee_OF()->getvaliderPlus()->setSensitive(false);
								}
								if(getCancel() == true || getValid() == true)
								{	
									// on a d�j� fait le fin pes�e
									// on r�initialise juste les flags
									if (getInterface()->getTraceMode() == 1)
										getInterface()->_traceFile << "------>manualMode Cancel="<<getCancel()<<" Valid="<<getValid()<<" Exit Loop 4" << endl;
									break;
								}
                            }
						}
						else
						{
							if (getBalance()->getTempo() == 0  && (_panneauAppelant == getInterface()->getPesee_OF()))
							{
								getInterface()->getPesee_OF()->getvalider()->setSensitive(false);
								getInterface()->getPesee_OF()->getvaliderPlus()->setSensitive(false);
							}
						}
					}
				}
				if((getDriverStatus() == OK) 
					&& ((getWeighingReturnOp() == TAR)))
//						|| (getWeighingReturnOp() == ART_S)					
//						|| (getWeighingReturnOp() == PDS_S)))	//reponse tant attendue
				{
//					if (getWeighingReturnOp() == TAR)
					setWeighingReturnOp(PDS_S);
					if (strcmp(getWeightUnit(),getResWeightUnit()) != 0)
					{
//						sta_err = CHG_PDS_UNIT;
					}

					// reconvertit le poids pes�
					poidsPese = getInterface()->getDonnees()->convertir(
						getResWeight(),
						getResWeightUnit(),
						getWeightUnit());
					setResNetWeight(poidsPese);
					if (orderModif)
					{
						setResTare(poidsPese);
					}

					// d�clenche la mise � jour de la jauge et de l'affichage poids
					if ((_panneauAppelant == getInterface()->getPesee_OF()) & !orderModif)
						getInterface()->getPesee_OF()
							->evolutionPoids();
					if (_panneauAppelant == getInterface()->getPesee_Etalon())
						getInterface()->getPesee_Etalon()
							->evolutionPoids();
					if (getInterface()->getTraceMode() == 1)
						getInterface()->_traceFile << "------>manualMode Cancel="<<getCancel()<<" Valid="<<getValid()<<" Exit Loop 5" << endl;
					break;
				}	
				if ((sta_err = statusEvents()) != OK_STA)
				{
					if (getInterface()->getTraceMode() == 1)
						getInterface()->_traceFile << "------>manualMode Cancel="<<getCancel()<<" Valid="<<getValid()<<" Exit Loop 6 statusEvents("<<statusEvents()<<")" << endl;
					break;
				}
				if ((sta_err = opeEvents()) != OK_STA)
				{
					if (getInterface()->getTraceMode() == 1)
						getInterface()->_traceFile << "------>manualMode Cancel="<<getCancel()<<" Valid="<<getValid()<<" Exit Loop 7 opeEvents("<<opeEvents()<<")" << endl;
					break;
				}
			}// fin du while(1)
			break;

		case MSG1:						//envoi d'un message sur afficheur
		case DISPL:
			sendMsgScales();
			break;

		case BIPP:						//envoi d'un bip
			EmissionReception(BIP,balance,false);
			break;

		case CHGT_UP_M:					//changement d'unite de poids manuel
		case CHGT_UP_A:					//changement d'unite de poids automatique
			sendMsgScales();
			EmissionReception(CHG_U,balance,bLocalCheckPlate);
			if (getDriverStatus() == NO_RESPONSE)//possible sur anomalie sur/souscharge
				getResponseScales(3,bLocalCheckPlate);//si pas de r�ponse envoie au driver
									 // l'ordre d'attendre un message
			if (getDriverStatus() == NO_RESPONSE)//si le silence persiste ->anomalie
				sta_err = NO_RESP;
			else
				sta_err = statusEvents();

			break;

		case UNT_PDS:					//acquisition de l'unite de poids de la balance
			EmissionReception(ART_I,balance,bLocalCheckPlate);
			if (getDriverStatus() == NO_RESPONSE)//possible sur anomalie sur/souscharge
				getResponseScales(3,bLocalCheckPlate);
			if (getDriverStatus() == NO_RESPONSE)//si le silence persiste ->anomalie
				sta_err = NO_RESP;

			break;
		case CTRL_BAL_PRA:			 	//test de balance
		case CLAV_BAL:				    //activation/desactivation clavier balance
		case CLAV_BAL_LOCK:				// sr 01.12 APCPRD-729 : Verrouillage clavier
			EmissionReception(E_KBD,balance,false); 
			break;
		case CLAV_BAL_UNLOCK:			// sr 01.12 APCPRD-729 : deverrouillage clavier
			EmissionReception(D_KBD,balance,false);
			break;
		case SERIAL_NUMBER: // demande du num�ro de s�rie de la balance
			EmissionReception(SERIAL_NUM,balance,false);
			if (getDriverStatus() == NO_RESPONSE)//possible sur anomalie sur/souscharge
				getResponseScales(3,false);
			if (getDriverStatus() == NO_RESPONSE)//si le silence persiste ->anomalie
				sta_err = NO_RESP;

			break;
		case CHGT_P: // Changement de plateau
			EmissionReception(CHG_P,balance,false);
			if (getDriverStatus() != OK)// Probl�me lors du changement de plateau
			{
				sta_err = CHG_PLATE;
				char wChMessage[255];
				wChMessage[0] = '\0';

				sprintf(wChMessage,"%s : %s",
					IlvGetMessage(getInterface()->getDisplay(),"&Error"),
					IlvGetMessage(getInterface()->getDisplay(),msg_status [sta_err]));
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				getInterface()->envoieMessage(wChMessage,false);
				balance->setMultiPlateOK(false);
				balance->setConnecte(0);
			}
			else
			{
				balance->setMultiPlateOK(true);
			}
			break;
		default:						//ordre inconnu
			break;
	}
	setWeighingStatus(sta_err);
	setResWeighingMessage(msg_status [sta_err]);
	if (getInterface()->getTraceMode() == 1)
    {
		getInterface()->_traceFile << "AdxWeighingInterface::manualMode Sortie" << endl;
		getInterface()->_traceFile << "\t getWeighingStatus()="<<getWeighingStatus() << " getResWeighingMessage()="<<getResWeighingMessage()<< endl;
    }
	/*if (getInterface()->getTraceMode() == 1)
    {
		getInterface()->_traceFile << "AdxWeighingInterface::manualMode exit" << endl;
    }*/
	return;
}

/*
//--------------------------------------------------------------
// Traitement de l'ordre de pes�e en mode automatique
//
// S�quence �bauch�e, � finaliser, pour un fonctionnement l�g�rement diff�rent
// o� aucune confirmation n'est demand�e � la balance
// A mettre eventuellement en activit� avec les balances qui le permettent
//
void AdxWeighingInterface::automaticMode(void)
{
    AdxBalance* balance = getBalance();
  
	WeighingOrder order = getWeighingOrder();
	setDriverStatus(OK);		//statut driver OK par d�faut
	setWeighingStatus(OK_STA);  //statut pes�e OK par d�faut
	WeighingStatus sta_err = OK_STA;

	switch(order) 
	{
		case RAZ_M:  //mise a zero manuelle
		case RAZ_A:  //mise a zero automatique
			sendMsgScales();
			while(1)
			{
				getResponseScales(1);
				if (getWeighingReturnOp() == TAR) //d�tection bonne reponse et
												  // �limination du msg double
				{
					getResponseScales(1);
					if((getDriverStatus() == OK) && (getWeighingReturnOp() == RAZ))
					{
						break;
					}
					break;
				}
				if ((getDriverStatus() == OK) && (getWeighingReturnOp() == RAZ))
				{
					break;    //bonne reponse
				}
				if ((sta_err = statusEvents()) != OK_STA)
				{
					break;
				}
				if ((sta_err = opeEvents()) != OK_STA)
				{
					break;
				}
			}
			break;

		case DETAR:						//le poids sur le plateau est consid�r�
										// comme le poids de tare
		case TAR_M:						//tarage manuel
		case TAR_A:						//tarage automatique
			sendMsgScales();
			while(1)
			{
				getResponseScales(1);
				if (getWeighingReturnOp() == TAR)
				{
					if (strcmp(getWeightUnit(),getResWeightUnit()) != 0)
					{
						sta_err = CHG_PDS_UNIT;
					}
					break;
				}
				if ((sta_err = statusEvents()) != OK_STA)
					break;
				if ((sta_err = opeEvents()) != OK_STA)
					break;
			}

			break;						//fin du case TAR

		case CONS_TAR_M:				//tarage manuel (net+tare)
		case CONS_TAR_A:				//tarage automatique (net+tare)

//			// changement d'unit� de poids ? propose la modification
//			if (strcmp(getWeightUnit(),getResWeightUnit()) != 0)
//			{
//				EmissionReception(CHG_U,balance);
//				if (getDriverStatus() == NO_RESPONSE)//possible sur anomalie sur/souscharge
//					getResponseScales(1);//si pas de r�ponse envoie au driver
//										 // l'ordre d'attendre un message
//				balance->setUnite(getResWeightUnit());
//			}

			setWeighingMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
													"&ConsigneTare"));
			setWeighingShortMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
														 "&Cons"));
			// convertit la tare en unit� poids balance
			if (getTare() != 0)
				tareUnitBal = getInterface()->getDonnees()->convertir(
					getTare(),
					getWeightUnit(),
					getResWeightUnit());

			setTareUnitBal(tareUnitBal);

			EmissionReception(TAR,balance);

			if (getDriverStatus() == NO_RESPONSE) //possible sur anomalie sur/souscharge
				getResponseScales(2);
			if (getDriverStatus() == NO_RESPONSE) //si le silence persiste ->anomalie
				sta_err = NO_RESP;
			else
				sta_err = statusEvents();

			break;

		case POIDS_IMDT:				//acquisition d'un poids instantane automatique
										// d�tourn� pour test balance connect�e
			setDriverStatus(NO_RESPONSE);		//statut driver ERREUR
			sendMsgScales();
			for (nb=0; nb <2; nb++)
			{
	  			EmissionReception(PDS_I,balance);
				if (((getWeighingReturnOp() == PDS_I) && (getDriverStatus() == OK))
					|| ((getWeighingReturnOp() == PDS_I)
						&& (getDriverStatus() == DYNAMIQUE))
					|| (getWeighingReturnOp() == PDS_S))
				{
					break;
				}
			}

			if (getDriverStatus() == NO_RESPONSE) setDriverStatus(TRANSMIT_ERROR);
			sta_err = statusEvents();
			break;

		case POIDS_STAB_M:				//acquisition d'un poids stable manuel
		case POIDS_STAB_A:				//acquisition d'un poids stable automatique
//--------  Sans doute faire jouer ici un bouton OK actionn� par l'utilisateur
//          lorsqu'il estime avoir le poids voulu
//          Ce bouton doit activer un "�v�nement" que l'on r�cup�re ici
//          pour interrompre la boucle de demande de poids imm�diat
//          Peut �tre faire comme dans Prodstar un dernier appel
//          de type PDS_S ou mieux ART_S pour r�cup�rer et v�rifier 
//          l'unit� de poids

			EmissionReception(E_KBD,balance);  //pendant la pes�e, verrouille
											   // par pr�caution	
// 
//			// changement d'unit� de poids ? propose la modification
//			if (strcmp(getWeightUnit(),getResWeightUnit()) != 0)
//			{
//				EmissionReception(CHG_U,balance);
//				if (getDriverStatus() == NO_RESPONSE)//possible sur anomalie sur/souscharge
//					getResponseScales(1);//si pas de r�ponse envoie au driver
//										 // l'ordre d'attendre un message
////				balance->setUnite(getResWeightUnit());
//			}
// 
			if (orderModif)
			{
				setWeighingMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
														"&Tarage"));
				setWeighingShortMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
															 "&Tare"));
			}
			else
			{
				char* message = new char[20];
				sprintf(message,"%s %.3f %s",
						IlvGetMessage(getInterface()->getDisplay(),	"&Peser"),
						getWeight(), 
						getWeightUnit()); 
				setWeighingMessage(message);
				delete [] message;
				setWeighingShortMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
														"&Pesee"));
			}

			sendMsgScales();

			setDriverStatus(NO_RESPONSE); //force � NO_RESPONSE
			while(1)
			{
				if (getDriverStatus() == NO_RESPONSE)
				{
		  			EmissionReception(PDS_I,balance);
					if (((getWeighingReturnOp() == PDS_I) && (getDriverStatus() == OK))
						|| ((getWeighingReturnOp() == PDS_I)
							&& (getDriverStatus() == DYNAMIQUE))
						|| (getWeighingReturnOp() == PDS_S))
					{
						if (_weighingFlag == 0)
							setDriverStatus(NO_RESPONSE); //car DYNAMIQUE est important
														  // pour la suite
						// reconvertit le poids pes�
						poidsPese = getInterface()->getDonnees()->convertir(
							getResWeight(),
							getResWeightUnit(),
							getWeightUnit());
						setResNetWeight(poidsPese);

						// d�clenche la mise � jour de la jauge et de l'affichage poids
						if (_panneauAppelant == getInterface()->getPesee_OF())
							getInterface()->getPesee_OF()
								->evolutionPoids();
						if (_panneauAppelant == getInterface()->getPesee_Etalon())
							getInterface()->getPesee_Etalon()
								->evolutionPoids();
						// propose d'arr�ter la pes�ee si poids atteint et stabilis�
						if (controlePoids(poidsPese) && !orderModif
							&& getWeighingReturnOp() == PDS_S)
						{
							finPeseeAuto();
						}
						// propose d'arr�ter la pes�ee si poids n'est pas atteint
						// mais stabilis� depuis 5 essais
						if (poidsPese == dernierPoidsPese
							&& getWeighingReturnOp() == PDS_S)
						{
							nbEgal += 1;
						}
						else
						{
							dernierPoidsPese = poidsPese;
							nbEgal = 0;
						}
						if (nbEgal >= 50)
						{
							if (finPeseePartielleAuto())
								break;
						}
					}
				}

				if ((sta_err = statusEvents()) != OK_STA)
					break;
				if ((sta_err = opeEvents()) != OK_STA)
					break;
			}							// fin du while(1)
			break;

		case MSG1:						//envoi d'un message sur afficheur
		case DISPL:
			sendMsgScales();
			break;

		case BIPP:						//envoi d'un bip
			EmissionReception(BIP,balance);
			break;

		case CHGT_UP_M:					//changement d'unite de poids manuel
		case CHGT_UP_A:					//changement d'unite de poids automatique
			sendMsgScales();
			EmissionReception(CHG_U,balance);
			if (getDriverStatus() == NO_RESPONSE)//possible sur anomalie sur/souscharge
				getResponseScales(3);//si pas de r�ponse envoi au driver
									 // l'ordre d'attendre un message
			if (getDriverStatus() == NO_RESPONSE)//si le silence persiste ->anomalie
				sta_err = NO_RESP;
			else
				sta_err = statusEvents();

			break;

		case UNT_PDS:					//acquisition de l'unite de poids de la balance
			EmissionReception(ART_I,balance);
			if (getDriverStatus() == NO_RESPONSE)//possible sur anomalie sur/souscharge
				getResponseScales(3);
			if (getDriverStatus() == NO_RESPONSE)//si le silence persiste ->anomalie
				sta_err = NO_RESP;

			break;

		case CTRL_BAL_PRA:				//test de balance
		case CLAV_BAL:					//activation/desactivation clavier balance
		default:						//ordre inconnu
			break;
	}
	setWeighingStatus(sta_err);
	setResWeighingMessage(msg_status [sta_err]);
	return;
}
*/

//--------------------------------------------------------------
// Envoi d'un message sur l'afficheur de la balance
//
void AdxWeighingInterface::sendMsgScales()
{
    AdxBalance* balance = getBalance();

	EmissionReception(DSPL,balance,false);
}

//--------------------------------------------------------------
// Attente du message de retour de la balance
//
void AdxWeighingInterface::getResponseScales(int nbWait,bool bCheckPlate)
{
    AdxBalance* balance = getBalance();

	setMsgWaitingTime(nbWait);
	EmissionReception(WAIT_MSG,balance,bCheckPlate);
}

//--------------------------------------------------------------
// Communication avec la balance
//
void AdxWeighingInterface::EmissionReception(WeighingOperation ope,
											 AdxBalance* balance,
											 bool bCheckPlate)
{
	int numDrv = 0; 
	int numPort = 0; 
	DWORD dwWaitResult;

	// mm 02.2013 - all�gement de la trace car devient illisible
	/*if (getInterface()->getTraceMode() == 1)
    {
		getInterface()->_traceFile << "AdxWeighingInterface::EmissionReception Entree Wait Mutex" << endl;
    }*/

	
	dwWaitResult = WaitForSingleObject(_hMutexComm,INFINITE);
	if(dwWaitResult == WAIT_OBJECT_0)
	{
		numDrv = balance->getNoDriver(); 
		numPort = balance->getPort(); 
		// mm 02.2013 - all�gement de la trace car devient illisible
		/*if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxWeighingInterface::EmissionReception Mutex UP port="<< numPort << endl;
		}*/

		// Positionnement par d�faut

		WeighingOperation rep = ope;
		DriverStatus sta = OK;

		// Oriente vers le bon driver
		switch (numDrv)
		{
		case 1:
			getMeid5()->weighingTreatment(this,ope,numPort,rep,sta,bCheckPlate);	//appel du pilote
			setWeighingReturnOp(rep);
			setDriverStatus(sta);
			break;
		case 2:
			getMeid7()->weighingTreatment(this,ope,numPort,rep,sta,bCheckPlate);	//appel du pilote
			setWeighingReturnOp(rep);
			setDriverStatus(sta);
			break;
		case 3:
			getMepm()->weighingTreatment(this,ope,numPort,rep,sta);		//appel du pilote
			setWeighingReturnOp(rep);
			setDriverStatus(sta);
			break;
		case 4:
			getSartorius()->weighingTreatment(this,ope,numPort,rep,sta,bCheckPlate);		//appel du pilote
			setWeighingReturnOp(rep);
			setDriverStatus(sta);
			break;
		// 12/08/08 Sartorius modifi�
		case 5:
			getSartoriusMod()->weighingTreatment(this,ope,numPort,rep,sta,bCheckPlate);		//appel du pilote
			setWeighingReturnOp(rep);
			setDriverStatus(sta);
			break;
		case 6:
			getMSICS()->weighingTreatment(this,ope,numPort,rep,sta,bCheckPlate);		//appel du pilote
			setWeighingReturnOp(rep);
			setDriverStatus(sta);
			break;
		default:
			break;
		}
	}
	ReleaseMutex(_hMutexComm);
	// mm 02.2013 - all�gement de la trace car devient illisible
	/*if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "E-R:release Mutex port="<< numPort << endl;
	}*/
}

//--------------------------------------------------------------
// Elabore le statut pes�e de retour en fonction du statut driver retourn�
//
WeighingStatus AdxWeighingInterface::statusEvents(void)
{
	switch (getDriverStatus())
	{
		case PORT:
			return(PORT_NOT_CORRECT);
		case PCLOSE:
			return(PORT_NOT_OPENED);
		case LOGISTIC_ERROR:
			return(ERR_LOGISTIC);
		case TRANSMIT_ERROR:
			return(ERR_TRANSMIT);
		case SYNTAX_ERROR:
			return(ERR_SYNTAX);
		case UNAVAILABLE:
			return(DATA_UNAVAILABLE);
		case SURCHARGE_ERROR:
			return(SUR_CHARGE);
		case SOUSCHARGE_ERROR:
			return(SOUS_CHARGE);
		case UNKNOWN_ANSWER:
			return(UNKNOWN_MSG);
		case DYNAMIQUE:
			return(DYNAMIC_PDS);
		case TRONCATED_RESPONSE:
			return(SHORT_MSG);
		case UNIT_ERROR:
			return(UNIT_BAL_NOT_CORRECT);
		case BAD_PLATE:
			return(BAD_PLATE_MSG);

		default:
			return(OK_STA);
	}
}
//--------------------------------------------------------------
// Tranforme le statut pes�e de retour en fonction de l'op�ration retourn�e
//
WeighingStatus AdxWeighingInterface::opeEvents(void)
{
	switch (getWeighingReturnOp())
	{
		case CHG_P:
			return(CHG_PLATE);
		case CHG_U:
			return(CHG_PDS_UNIT);
		case RAZ:
			return(RAZ_OP);
		case TAR:
			return(TAR_OP);
		case RAZ_TAR:
			return(RAZ_TAR_OP);
		default:
			return(OK_STA);
	}
}

//---------------------------------------------------------------------------
void AdxWeighingInterface::editionMessage()
{
//	if (getInterface()->getPesee_OF() == NULL) return;
	if (getPanneauAppelant() == NULL) return;
	WeighingOrder order = getWeighingOrder();
	if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "AdxWeighingInterface::editionMessage : Enter Order :"<<order<< endl;
	}

	if (order == POIDS_IMDT)
	{
		// Edition d'un message test pour patienter
		char* szTemp = new char[80];
		sprintf(szTemp,"%s",
//			(char*)IlvGetMessage(getInterface()->getPesee_OF()->getDisplay(),
			(char*)IlvGetMessage(getPanneauAppelant()->getDisplay(),
			"&TestEnCours"));
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxWeighingInterface::editionMessage : Message 1:"<< szTemp << endl;
		}

		if (_panneauAppelant == getInterface()->getPesee_OF())
		{
			getInterface()->getPesee_OF()->getmessage()
				->setLabel(getInterface()->getPesee_OF()->formatMessage(szTemp));
			getInterface()->getPesee_OF()
				->bufferedDraw(getInterface()->getPesee_OF()->getmessage());
		}
		if (_panneauAppelant == getInterface()->getPesee_Etalon())
		{
			getInterface()->getPesee_Etalon()->getMessage()
				->setLabel(szTemp);
			getInterface()->getPesee_Etalon()
				->bufferedDraw(getInterface()->getPesee_Etalon()->getMessage());
		}

		delete [] szTemp;
	}

	if (order == RAZ_M || order == TAR_M)
	{
		// Edition d'un message d'attente r�ponse de la balance
		char* szTemp = new char[80];
		sprintf(szTemp,"%s : %s",getWeighingShortMessage(),
//			(char*)IlvGetMessage(getInterface()->getPesee_OF()->getDisplay(),
			(char*)IlvGetMessage(getPanneauAppelant()->getDisplay(),
			"&Attente"));
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxWeighingInterface::editionMessage : Message 2:"<< szTemp << endl;
		}

		if (_panneauAppelant == getInterface()->getPesee_OF())
		{
			getInterface()->getPesee_OF()->getmessage()
				->setLabel(getInterface()->getPesee_OF()->formatMessage(szTemp));
			getInterface()->getPesee_OF()
				->bufferedDraw(getInterface()->getPesee_OF()->getmessage());
		}
		if (_panneauAppelant == getInterface()->getPesee_Etalon())
		{
			getInterface()->getPesee_Etalon()->getMessage()
				->setLabel(szTemp);
			getInterface()->getPesee_Etalon()
				->bufferedDraw(getInterface()->getPesee_Etalon()->getMessage());
		}
		delete [] szTemp;
	}

	if (order == CONS_TAR_M)
	{
		// Edition d'un message pour patienter
		char* szTemp = new char[80];
		sprintf(szTemp,"%s",getWeighingMessage());
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxWeighingInterface::editionMessage : Message 3:"<< szTemp << endl;
		}

		if (_panneauAppelant == getInterface()->getPesee_OF())
		{
			getInterface()->getPesee_OF()->getmessage()
				->setLabel(getInterface()->getPesee_OF()->formatMessage(szTemp));
			getInterface()->getPesee_OF()
				->bufferedDraw(getInterface()->getPesee_OF()->getmessage());
		}
		if (_panneauAppelant == getInterface()->getPesee_Etalon())
		{
			getInterface()->getPesee_Etalon()->getMessage()
				->setLabel(szTemp);
			getInterface()->getPesee_Etalon()
				->bufferedDraw(getInterface()->getPesee_Etalon()->getMessage());
		}
		delete [] szTemp;
	}

	if (order == POIDS_STAB_M)
	{
		// Edition d'un message pes�e en cours pour patienter
		char* szTemp = new char[80];
		sprintf(szTemp,"%s",
//			(char*)IlvGetMessage(getInterface()->getPesee_OF()->getDisplay(),
			(char*)IlvGetMessage(getPanneauAppelant()->getDisplay(),
			"&PeseeEnCours"));
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxWeighingInterface::editionMessage : Message 4:"<< szTemp << endl;
		}

		if (_panneauAppelant == getInterface()->getPesee_OF())
		{
			getInterface()->getPesee_OF()->getmessage()
				->setLabel(getInterface()->getPesee_OF()->formatMessage(szTemp));
			getInterface()->getPesee_OF()
				->bufferedDraw(getInterface()->getPesee_OF()->getmessage());
		}
		if (_panneauAppelant == getInterface()->getPesee_Etalon())
		{
			getInterface()->getPesee_Etalon()->getMessage()
				->setLabel(szTemp);
			getInterface()->getPesee_Etalon()
				->bufferedDraw(getInterface()->getPesee_Etalon()->getMessage());
		}
		delete [] szTemp;
	}
}

//--------------------------------------------------------------
// Fin de pes�e 
//               
void AdxWeighingInterface::finPesee()
{
    AdxBalance* balance = getBalance();

	if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "AdxWeighingInterface::finPesee Enter" << endl;
	}

	EmissionReception(PDS_I,balance,true);
	// envoi d'un message pour arr�ter ou non la pes�e
	char* message = new char[80];
	sprintf(message,"%s",
			IlvGetMessage(getInterface()->getDisplay(),
							"&PeseeContinuer2"));
	if (_panneauAppelant == getInterface()->getPesee_OF())
	{
		getInterface()->getMessage()
			->setPanneauAppelant(getInterface()->getPesee_OF());
	}
	if (_panneauAppelant == getInterface()->getPesee_Etalon())
	{
		getInterface()->getMessage()
			->setPanneauAppelant(getInterface()->getPesee_Etalon());
	}
	if ((getStopPesee() == false && getInterface()->envoieMessage(message,true) == true)||getStopPesee() == true)
	{
		// on arr�te la pes�e
		EmissionReception(D_KBD,balance,false);  //d�verrouille le clavier

		// envoi d'un message sur �cran de la balance
		setWeighingMessage((char*)IlvGetMessage(getInterface()
							->getDisplay(),"&PeseeOK"));
		setWeighingShortMessage((char*)IlvGetMessage(getInterface()
							->getDisplay(),"&PesOK"));
		sendMsgScales();

		// GBE 10/09/08 On supprime le message de validation de la pes�e
		// depuis la balance pour le cas sartorius modifi� car cela nous 
		// oblige � appuyer sur le bouton de remise � z�ro ou de tare
		if(balance->getNoDriver() != 5) // sis Sartorius modifi�
		{
			// envoi d'un message sur �cran de pes�e
			char* szTemp = new char[80];
			sprintf(szTemp,"%s",
	//		(char*)IlvGetMessage(getInterface()->getPesee_OF()->getDisplay(),
				(char*)IlvGetMessage(getPanneauAppelant()->getDisplay(),
				"&PeseeTerminee"));

			if (_panneauAppelant == getInterface()->getPesee_OF())
			{
				getInterface()->getPesee_OF()->getmessage()
					->setLabel(getInterface()->getPesee_OF()->formatMessage(szTemp));
				getInterface()->getPesee_OF()
					->bufferedDraw(getInterface()->getPesee_OF()->getmessage());
			}
			if (_panneauAppelant == getInterface()->getPesee_Etalon())
			{
				getInterface()->getPesee_Etalon()->getMessage()
					->setLabel(szTemp);
				getInterface()->getPesee_Etalon()
					->bufferedDraw(getInterface()->getPesee_Etalon()->getMessage());
			}
			delete [] szTemp;

			// attente r�ponse balance
			getResponseScales(1000,true);
		}
	}
	else
	{
		// continuer la pes�e
		manualMode(true);
		return;
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxWeighingInterface::finPesee exit 1" << endl;
		}
	}
	// mm 02.2013 - all�gement de la trace car devient illisible
	/*if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "AdxWeighingInterface::finPesee exit 2" << endl;
	}*/
	
}	

//--------------------------------------------------------------
// Fin de pes�e partielle 
//               
// sr 11.02 Que l'on continue ou pas on retourne toujours "true"
// sinon on part en boucle !!!
bool AdxWeighingInterface::finPeseePartielle()
{
    AdxBalance* balance = getBalance();

	if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "AdxWeighingInterface::finPeseePartielle Enter" << endl;
	}
	EmissionReception(PDS_I,balance,true);

	// envoi d'un message sur �cran de pes�e
	setWeighingMessage((char*)IlvGetMessage(getInterface()
						->getDisplay(),"&PeseeInterrompue"));
	setWeighingShortMessage((char*)IlvGetMessage(getInterface()
						->getDisplay(),"&PesInt"));
	sendMsgScales();

	// envoi d'un message pour continuer ou non la pes�e
	char* message = new char[80];
	sprintf(message,"%s",
			IlvGetMessage(getInterface()->getDisplay(),
							"&PeseeContinuer"));
	if (_panneauAppelant == getInterface()->getPesee_OF())
	{
		getInterface()->getMessage()
			->setPanneauAppelant(getInterface()->getPesee_OF());
	}
	if (_panneauAppelant == getInterface()->getPesee_Etalon())
	{
		getInterface()->getMessage()
			->setPanneauAppelant(getInterface()->getPesee_Etalon());
	}
	if (getInterface()->envoieMessage(message,true) == true)
	{
		// continuer la pes�e
		manualMode(true);
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxWeighingInterface::finPeseePartielle exit 1" << endl;
		}
		return true;
	}
	else
	{
		// pes�e partielle
		EmissionReception(D_KBD,balance,false);  //d�verrouille le clavier

		// envoi d'un message sur �cran de la balance
		setWeighingMessage((char*)IlvGetMessage(getInterface()
							->getDisplay(),"&Confirmer"));
		setWeighingShortMessage((char*)IlvGetMessage(getInterface()
							->getDisplay(),"&Conf"));
		sendMsgScales();

		// envoi d'un message sur �cran de pes�e
		char* szTemp = new char[80];
		sprintf(szTemp,"%s",
//			(char*)IlvGetMessage(getInterface()->getPesee_OF()->getDisplay(),
			(char*)IlvGetMessage(getPanneauAppelant()->getDisplay(),
			"&PeseePartielleTerminee"));

		if (_panneauAppelant == getInterface()->getPesee_OF())
		{
			getInterface()->getPesee_OF()->getmessage()
				->setLabel(getInterface()->getPesee_OF()->formatMessage(szTemp));
			getInterface()->getPesee_OF()
				->bufferedDraw(getInterface()->getPesee_OF()->getmessage());
		}
		if (_panneauAppelant == getInterface()->getPesee_Etalon())
		{
			getInterface()->getPesee_Etalon()->getMessage()
				->setLabel(szTemp);
			getInterface()->getPesee_Etalon()
				->bufferedDraw(getInterface()->getPesee_Etalon()->getMessage());
		}
		delete [] szTemp;

		// attente r�ponse balance
		getResponseScales(1000,true);
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxWeighingInterface::finPeseePartielle exit 2" << endl;
		}
		return true;
	}
	// mm 02.2013 - all�gement de la trace car devient illisible
	/*if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "AdxWeighingInterface::finPeseePartielle exit 3" << endl;
	}*/
}

//--------------------------------------------------------------
// Temporisation en milli secondes 
//               
void AdxWeighingInterface::delay(int milliSec)
{
	clock_t start, end;
	start = clock();
	do
	{
		end = clock();
	}
	while ((end- start) < milliSec);
}


//--------------------------------------------------------------
// Controle poids inf�rieur au poids max tol�r�
bool AdxWeighingInterface::controlePoidsInf()
{
	AdxPesee_OF* m_pesee_OF  =  getInterface()->getPesee_OF();
	AdxData* m_data = getInterface()->getDonnees();

	// On a d�j� tout calcul� dans la fonction evolutionPoids
	// on contr�le juste que le poids total ne d�passe pas la tol�rance Max
    if(m_pesee_OF->getPoidsDejaPese() <= m_pesee_OF->getWeightMax())
    {
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxWeighingInterface::controlePoidsInf TRUE getPoidsDejaPese=("<<m_pesee_OF->getPoidsDejaPese()<<") getWeightMax=("<<m_pesee_OF->getWeightMax()<<")"<< endl;
		}
        return true;
    }
    else
    {
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxWeighingInterface::controlePoidsInf FALSE getPoidsDejaPese=("<<m_pesee_OF->getPoidsDejaPese()<<") getWeightMax=("<<m_pesee_OF->getWeightMax()<<")"<< endl;
		}
		//116324  mm 08.2016 - authorization to exceed tolerance+
		if  ( m_data->getExceedingTolerancePos()==2 )
		{
			return true;
		}
        return false;
    }
}

//--------------------------------------------------------------
/*bool AdxWeighingInterface::controlePoidsSup()
{
    AdxBalance* balance = getBalance();
    double _wpoidsEnPesee;
    double _wpoidsDejaPese;
	double _tolerance = 0.0;
	double _weightMin;
	AdxData* m_data = getInterface()->getDonnees();

	// tol�rance prise sur la nomenclature, ou par d�faut sur la balance - mm 05.10
	if (m_data->getCurrentComposant() != NULL)
		_tolerance = m_data->getCurrentComposant()->getToleranceArticleNegative();
	if (_tolerance == 0)
		_tolerance = balance->getTolerance();


	if (m_data->getCurrentComposant()->getGestionStock() != 3) 
  	{
    	_wpoidsEnPesee  = getResNetWeight();
    }
    else
    {
		    _wpoidsEnPesee  = getResNetWeight() * m_data->getCurrentLot()->getTitre()
    			/ m_data->getCurrentComposant()->getTitreTheo();
    }
     _wpoidsDejaPese  = getTotResNetWeight()+ _wpoidsEnPesee;

	double origine ;
	if (balance->getConsigne() != 0)
		origine = 0;
	else
    {
  		origine	= getTotWeight();
    }

    _weightMin = origine - getTotWeight() * _tolerance/100;
    if(_wpoidsDejaPese >= _weightMin)
    {
       return true;
    }
    else
    {
       return false;
    }

}*/

//--------------------------------------------------------------
// Controle poids sup�rieur au poids min tol�r�
bool AdxWeighingInterface::controlePoidsSup()
{
	AdxPesee_OF* m_pesee_OF  =  getInterface()->getPesee_OF();

	// On a d�j� tout calcul� dans la fonction evolutionPoids
	// on contr�le juste que le poids total est sup�rieur au poids min tol�r� 
    if(m_pesee_OF->getPoidsDejaPese() >= m_pesee_OF->getWeightMin())
    {
       return true;
    }
    else
    {
       return false;
    }
}
//--------------------------------------------------------------
// V�rification connexion balance 
//               
void AdxWeighingInterface::connectionTest(AdxBalance* balance,
										  bool bAppel)
{

	int numPort = balance->getPort();
	int noDrv = balance->getNoDriver();
	long connecte = 0;

	// Gestion multi plateaux
	// si le flag MultiPlateOK est � faux c'est qu'il y a eu un probl�me
	// lors du changement du plateau ! la balance est donc comme d�connect�
	// il faudra red�marrer la centrale pour tout remettre en ordre

	if (balance->getMultiPlateOK() == false)
	{
		balance->setConnecte(connecte);
		return;
	}
	if (numPort > 0 && numPort < 9 && noDrv > 0)
	{
		if (getMultiCom()->_portCom[numPort-1] != NULL)
		{
			// GBE 03/10/13 On vide le buffer pour �liminer les trames parasites
			if (this->getInterface()->getClearBuffer())
			{
				DriverStatus wSta;			// Status de retour du port com
				ComOperation wComOp;		// Op�ration du port com
				int wnMax = MAXC;
				int wnProtect = 0;			// protection de la boucle pour �viter une boucle infinie
				static char wInmsg[MAXC+1];
				wInmsg[0] = '\0';
				wSta = OK;
				wComOp = READ;
				while(wSta == OK && wnProtect <= 10)
				{
					this->getMultiCom()->comOperationTreatment(numPort,
															 wComOp,
															 wInmsg,
															 wSta,
															 wnMax);
					wnProtect++;
				}
			}

			WeighingOrder order;
			order = POIDS_IMDT;  
			setWeighingMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
												"&TestConnexion"));
			setWeighingShortMessage((char*)IlvGetMessage(getInterface()->getDisplay(),
													 "&Test"));
			setWeighingOrder(order);
			setBalance(balance);
			weighingOrderTreatment(false); // pas de check du plateau pour les test de connexion
			// si OK : connecte
			if (getWeighingStatus() == OK_STA
			 || getWeighingStatus() == DYNAMIC_PDS
			 || getWeighingStatus() == SOUS_CHARGE)	// BCH le 03/01/2008
			{
				connecte = 1;
			}
			else
			{
				// propose de r�essayer une fois
				if (bAppel)
				{
					char* message = new char[80];
					sprintf(message,"%s   %s  %s = %d",
						IlvGetMessage(getInterface()->getDisplay(),"&BalanceDeconnectee"),
						balance->getBalance(), 
						IlvGetMessage(getInterface()->getDisplay(),"&NoPort"),
						numPort); 
					getInterface()->getMessage()->setPanneauAppelant(NULL);
					if (getInterface()->envoieMessage(message,true) == true)
					{
						delete [] message;
						// v�rifie une deuxi�me et derni�re fois
						connectionTest(balance, false);
					}
					else
					{
						delete [] message;
					}
				}
			}
		}
	}
	// On test le nim�ro de s�rie s'il est renseign� dans la struture balance
//	if(balance->getSerialNumber() != NULL && connecte == 1)
	if(connecte == 1)
	{
		// lu num�ro de serie est renseign� on int�roge la balance pour savoir
		// si la balance connect�e est bien celle attendue
		WeighingOrder order;
		order = SERIAL_NUMBER;  
		setWeighingOrder(order);
		setBalance(balance);
		weighingOrderTreatment(false); // pas de check du plateau pour le num�ro de s�rie
		if (getWeighingStatus() != OK_STA)
		{
			// La balance connect� ne correspond pas � celle qui 
			// a �t� param�tr�e (pas de correspondance de N� de s�rie)
			connecte = 0; // on concid�re la balance comme non connect�e
			// affichage du message
			char* message = new char[80];
			sprintf(message,"%s %s %s %d %s",
				IlvGetMessage(getInterface()->getDisplay(),"&MessSerial1"),
				balance->getBalance(), 
				IlvGetMessage(getInterface()->getDisplay(),"&MessSerial2"),
				numPort,
				IlvGetMessage(getInterface()->getDisplay(),"&MessSerial3")); 
			getInterface()->getMessage()->setPanneauAppelant(NULL);
			getInterface()->envoieMessage(message,false);
		}
	}
	balance->setConnecte(connecte);
}


//--------------------------------------------------------------
// Initialisation �cran � z�ro 
//               
void AdxWeighingInterface::initEcranBalance(AdxBalance* balance)
{
	WeighingOrder order;
	if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "AdxWeighingInterface::initEcranBalance Entree" << endl;
	}

	if(balance->getConnecte() == 1 && balance->IsMultiPlate() == true)
	{
		order = CHGT_P;
		setWeighingOrder(order);
		weighingOrderTreatment(false);
		if (getWeighingStatus() != OK_STA)
		{
			// le changement de plateau a �chou�
			return;
		}
	}

	// On doit positionner le bon plateau

	// envoie une consigne de tare nulle pour remettre l'afficheur
	// � z�ro
	order = CONS_TAR_M;  
	setWeighingOrder(order);
	setTare(0);
	setWeightUnit(balance->getUnite());
	setResWeightUnit(balance->getUnite());
	weighingOrderTreatment();
	if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "AdxWeighingInterface::initEcranBalance Sortie" << endl;
	}
}

//--------------------------------------------------------------
// Mettre une cha�ne de caract�res en minuscules.
// 
void AdxWeighingInterface::afChLower(char *plChValueES/* Cha�ne � traiter en entr�e/sortie  */)
{
	long wni = 0;
	if(plChValueES != NULL)
	{
		while(plChValueES[wni] != '\0')
		{
			plChValueES[wni] =(char) tolower(plChValueES[wni]) ;
			wni++;
		}
	}
}
//--------------------------------------------------------------
// Mettre une cha�ne de caract�res en majuscules.
// 
void AdxWeighingInterface::afChUpper(char *plChValueES/* Cha�ne � traiter en entr�e/sortie  */)
{
	long wni = 0;
	if(plChValueES != NULL)
	{
		while(plChValueES[wni] != '\0')
		{
			plChValueES[wni] =(char) toupper(plChValueES[wni]) ;
			wni++;
		}
	}
}

//--------------------------------------------------------------
// Elimination des blancs a droite
//
void AdxWeighingInterface::afChRTrim (char * lChValeurES/* Cha�ne � traiter en entr�e/sortie  */)
{
	long     i=strlen( lChValeurES);

	for (i=strlen(lChValeurES)-1; i>=0 ;i--)
	{
		if (lChValeurES[i]!=' ')
			break;
	}
	lChValeurES[i+1]='\0';

}

//--------------------------------------------------------------
// Elimination des blancs a gauche
// 
void AdxWeighingInterface::afChLTrim (char * lChValeurES/* Cha�ne � traiter en entr�e/sortie  */)
{
	long     i=0,j,lgn;
	char  *pwChInter=NULL;

	lgn = strlen(lChValeurES);
	// Allocation de la m�moire pour la cha�ne temporaire
	pwChInter =(char *) calloc (lgn+1 , sizeof(char));

		lgn = strlen(lChValeurES);

	for(;;)
	{
		if ((lChValeurES[i]!=' ' && lChValeurES[i]!='\0') || i==lgn)
			break;
		i++;
	}

	for (j=i;j<lgn;j++)
		pwChInter[j-i]=lChValeurES[j];

	pwChInter[j-i]='\0';

	strcpy  ( lChValeurES,  pwChInter);
	// Lib�ration de la m�moire
	free(pwChInter);
}

//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
// Initialisation Interface
//
bool AdxWeighingInterface::initWeighingInterface()
{	
	setPanneauAppelant(getInterface()->getPesee_OF());

	long nbDrv = 6;	// 26/08/08 MT SICS 
	// Tableau dans lequel on va compter les ouverture de port de communication
	// on a 8 ports de communication et le premier port est le COM1
	short tabPort[8] ={0,0,0,0,0,0,0,0};
	WeighingStatus sta_err = OK_STA;

	// Controle des balances
	// 06.04 TRACE
	if (getInterface()->getTraceMode() == 1)
		getInterface()->_traceFile << "\t"<< "Scales control" << endl;


	IlList* balanceList = getInterface()->getDonnees()->getBalanceList();
	long nbBalances = getInterface()->getDonnees()->getNbBalances();
	for( long i = 0 ; i < nbBalances ; i++) 
	{
		AdxBalance* balance = (AdxBalance*)(*balanceList)[ i];


  		// V�rifie pr�sence des drivers
		// 06.04 TRACE 
		if (getInterface()->getTraceMode() == 1)
			getInterface()->_traceFile << "\t\t"<< balance->getBalance() 
												<< " "
												<< balance->getLibBalance()
												<< endl;

		int kdrv = 0;
		for( long j = 0 ; j < nbDrv ; j++)
		{
			if (strcmp(balance->getPilote(), driverNames[j]) == 0)
			{
				kdrv = 1;
				driverFlag[j] = 1;
				balance->setNoDriver(j+1);
				break;
			}
		}

		if (kdrv == 0)					// driver balance inconnu
		{
			// force le no driver � z�ro : la balance ne sera pas connect�e
			balance->setNoDriver(0);
			sta_err = PILOT_NOT_PRESENT;
			setWeighingStatus(sta_err);
			char* message = new char[80];
			sprintf(message,"%s  %s : %s",
					IlvGetMessage(getInterface()->getDisplay(),	msg_status [sta_err]),
					balance->getPilote(), 
					balance->getBalance()); 
			setResWeighingMessage(message);
			getInterface()->getMessage()->setPanneauAppelant(NULL);
			getInterface()->envoieMessage(message,false);
			delete [] message;
//			return false;

		}

 		// 06.04 TRACE 
		if (getInterface()->getTraceMode() == 1)
			getInterface()->_traceFile << "\t\t\t"<< "Driver checked" << endl;

		// V�rifie les ports

		int numPort = balance->getPort();

		if (numPort <= 0 || numPort > 8)	// num�ro de port erron�
		{
			// la balance ne sera pas connect�e
			sta_err = PORT_NOT_CORRECT;
			setWeighingStatus(sta_err);
			char* message = new char[80];
			sprintf(message,"%s  %d : %s",
					IlvGetMessage(getInterface()->getDisplay(),	msg_status [sta_err]),
					numPort, 
					balance->getBalance()); 
			setResWeighingMessage(message);
			getInterface()->getMessage()->setPanneauAppelant(NULL);
			getInterface()->envoieMessage(message,false);
			delete [] message;
//			return false;
		}
		else
		{
			portFlag[numPort-1] = 1;
			baudRate[numPort-1] = balance->getVitesse();
			parity[numPort-1] = balance->getParite();
			stopBits[numPort-1] = balance->getStopBit();
			byteSize[numPort-1] = balance->getFormat();

			// Gestion multi plateaux
			tabPort[numPort-1] +=1; // incr�ment du compteur
		}
		// 06.04 TRACE 
		if (getInterface()->getTraceMode() == 1)
		getInterface()->_traceFile << "\t\t\t"<< "Port checked" << endl;
	}


	// Initialise les drivers

	for (long i = 0; i <= nbDrv; i++)
	{
		if (driverFlag[i] > 0)
		{
			switch (i)
			{
			case 0:
				setMeid5(new AdxMeid5());
				break;
			case 1:
				setMeid7(new AdxMeid7());
				break;
			case 2:
				setMepm(new AdxMepm());
				break;
			case 3:
				setSartorius(new AdxSartorius((short)i));
				break;
			// 12/08/08 Sartorius modifi�
			case 4:
				setSartoriusMod(new AdxSartorius((short)i));
				break;
			// 26/08/08 MT SICS 
			case 5:
				setMSICS(new AdxMSICS());
				break;
			}
		}
	}
	// 06.04 TRACE 
	if (getInterface()->getTraceMode() == 1)
		getInterface()->_traceFile << "\t"<< "Driver(s) initialized" << endl;

	// Initialise le multi com

	setMultiCom(new AdxMultiCom());
	getMultiCom()->initMultiCom(this, portFlag, baudRate, parity, stopBits, byteSize);

	sta_err = getWeighingStatus();
	if (sta_err != OK_STA)  // en principe impossible
	{
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		getInterface()->envoieMessage(getResWeighingMessage(),false);
		return false;
	}
 	// 06.04 TRACE 
	if (getInterface()->getTraceMode() == 1)
		getInterface()->_traceFile << "\t"<< "Multicom initialized" << endl;

	// connecte les balances
  	// 06.04 TRACE
	if (getInterface()->getTraceMode() == 1)
		getInterface()->_traceFile << "\t" << "Scale test" << endl;

	for(long i = 0 ; i < nbBalances ; i++) 
	{
		AdxBalance* balance = (AdxBalance*)(*balanceList)[ i];
		int numPort = balance->getPort();
		// Gestion multi plateaux
		// si le port est ouvert plusieurs fois c'est qu'on est en pr�sence d'un
		// concentrateur connect� � plusieurs plateaux
		if(tabPort[numPort-1] > 1)
		{
			// On est en mode multi plateaux
			balance->setMultiPlate(true);
			// On r�cup�re les dernier caract�re du nom de la balance qui doit 
			// �tre compris entre 1 et 9 
			char cIndex = balance->getBalance()[strlen(balance->getBalance())-1];
			// On retranche le code ASCII de 0 pour obtenir la valeur enti�re du caract�re
			// en fin de cha�ne
			short nIndex = cIndex - (short)'0';
			if( nIndex < 1 || nIndex > 9)
			{
				// Erreur !!!
			}
			else
			{
				balance->setPlateIndex(nIndex);
			}
		}

		int noDrv = balance->getNoDriver();
 		// v�rification connexion balance
		// 06.04 TRACE 
		if (getInterface()->getTraceMode() == 1)
			getInterface()->_traceFile << "\t\t"<< balance->getBalance() 
												<< " "
												<< balance->getLibBalance()
												<< endl;

		connectionTest(balance,true);
		long connecte = balance->getConnecte();
		if (connecte)
		{
			initEcranBalance(balance);
			// 06.04 TRACE
			if (getInterface()->getTraceMode() == 1)
				getInterface()->_traceFile << "\t\t\t"<< "online" << endl;
        }
		else
		{
			// 06.04 TRACE
			if (getInterface()->getTraceMode() == 1)
				getInterface()->_traceFile << "\t\t\t"<< "offline" << endl;
			char* message = new char[80];
			sprintf(message,"%s : %s  %s = %d",
					IlvGetMessage(getInterface()->getDisplay(),"&BalanceNonConnectee"),
					balance->getBalance(), 
					IlvGetMessage(getInterface()->getDisplay(),"&NoPort"),
					numPort); 
			getInterface()->getMessage()->setPanneauAppelant(NULL);
			getInterface()->envoieMessage(message,false);
			delete [] message;
		}
	}

	return true;
}

void AdxWeighingInterface::setValid(bool value)
{
	DWORD dwWaitResult;
	AdxBalance* balance = getBalance();
	dwWaitResult = WaitForSingleObject(_hMutexValid,INFINITE);
	if(dwWaitResult == WAIT_OBJECT_0)
	{
		if (getInterface()->getTraceMode() == 1 && value == true)
			getInterface()->_traceFile << "!!!!!!!"<< "Valid Raise" << endl;
		_bValid = value;
		if(value == true)
		{
			// On d�v�rouille le clavier si la balance est connect�e
			if(balance != NULL && balance->getConnecte() == 1)
			{
				if (getInterface()->getTraceMode() == 1)
					getInterface()->_traceFile << "\t\t\t"<< "Before Send D_KBD" << endl;
				EmissionReception(D_KBD,balance,false);  //d�verrouille le clavier
				if (getInterface()->getTraceMode() == 1)
					getInterface()->_traceFile << "\t\t\t"<< "After Send D_KBD" << endl;			
			}
		}
	}
	ReleaseMutex(_hMutexValid);
}

void AdxWeighingInterface::setCancel(bool value)
{
	DWORD dwWaitResult;
	AdxBalance* balance = getBalance();
	dwWaitResult = WaitForSingleObject(_hMutexCancel,INFINITE);
	if(dwWaitResult == WAIT_OBJECT_0)
	{
		if (getInterface()->getTraceMode() == 1 && value == true)
			getInterface()->_traceFile << "!!!!!!!"<< "Cancel Raise" << endl;
		_bCancel = value;
		if(value == true)
		{
			// On d�v�rouille le clavier si la balance est connect�e
			if(balance != NULL && balance->getConnecte() == 1)
			{
				if (getInterface()->getTraceMode() == 1)
					getInterface()->_traceFile << "\t\t\t"<< "Before Send D_KBD" << endl;
				EmissionReception(D_KBD,balance,false);  //d�verrouille le clavier
				if (getInterface()->getTraceMode() == 1)
					getInterface()->_traceFile << "\t\t\t"<< "After Send D_KBD" << endl;
			}
		}
	}
	ReleaseMutex(_hMutexCancel);
}

