// AdxMSICS.cpp
// ------------
// project : Sage X3 Scales
// author : gbe
//--------------------------------------------------------------
//

/******************************************************
*                                                     *
*    PILOTE DE PERIPHERIQUE METTLER COMPATIBLE AVEC   *
*    LE PROTOCOLE SICS LEVEL 0 ET LEVEL 1             *
*                                                     *
*******************************************************
*                                                     *
*  LANGAGE     C++        compilation MSV6            *
*                                                     *
*-----------------------------------------------------*
*                                                     *
*  OBJECTIF    Le driver assurera l'émission et la    *
*              réception de caractères sur un des 8   *
*              ports suivant le protocole METTLER     *
*              SICS Level 0 ET 1                      *
*              Il pilotera une balance avec le jeu    *
*              d'instruction disponible.Il filtrera   *
*              les manipulations clavier de           *
*              l'opérateur                            *
*                                                     *
*-----------------------------------------------------*
*                                                     *
*  CONTRAINTES Les flux à gérer sont faibles et quasi *
*              exclusifs.                             *
*                                                     *
*******************************************************/

/***************************************************************************
*                                                                          *
* Fonctionnement du pilote           :                                     *
*	Le pilote connait le jeu d'instruction de la balance.                  *
*   Il fonctionne en mode transactionnel question réponse.                 *
*   Sur une requete standard venant d'amont,le pilote génère le message au *
*   format de la balance et appelle le driver MULTICOM. La balance répond à*
*   la question. Cette réponse est lue par le pilote qui transforme cette  *
*   réponse en une requete + statut + data standard pour l'appelant.       *
*                                                                          *
***************************************************************************/

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "AdxInterface.h"
#include "AdxData.h"
#include "AdxWeighingInterface.h"
#include "AdxMultiCom.h"
#include "AdxMSICS.h"
#include "AdxBalance.h"

#include <fstream>

using std::endl;



static char ptl[DOWN_BUF_SIZ];
static char inmsg[MAXC+1];             //contient le message traite recu de l'aval
static unsigned char Icar;             //contient le caractere courant traite
static char ioptr_d[DOWN_BUF_SIZ];     //contient le message à envoyer
static DriverStatus istatus;           //statut acquis en entree(par l'aval)
static DriverStatus ostatus;           //statut renseigne en sortie(pour l'amont)
static WeighingOperation ope;          //operation a traiter
static WeighingOperation rep;          //reponse sur l'operation lue que l'on retourne
// a l'appelant
static int  pornum;                    //indice du port courant a traiter



/*************************************************
*    traitement de l'ordre de pesée              *
*************************************************/
void AdxMSICS::weighingTreatment(AdxWeighingInterface* wi,
								 WeighingOperation& opi,
								 int& porid,
								 WeighingOperation& opo,
								 DriverStatus& sto,
								 bool bCheckPlate)
{
	WeighingOperation saveOpe;
	setWeighingInterface(wi);
	ope = opi;
	pornum = porid;
	rep = opo;
	ostatus = sto;

	int i;
	long j;
	char Chaine[64]="";				//Chaine pour manipulations diverses
	char* unit = new char[4];
	strset(ptl,0);
	strset(ioptr_d,0);

	// Variables pour la sauvegarde du buffer
	char	ChBufferSave[MAXC+1];
	DriverStatus	istatusSav;
	bool bBuffSaved = false;

	memset(ChBufferSave,0,MAXC+1);

	// Avant toute chose on teste le plateau si on est sur une balance 
	// multi-plateaux et que bCheckPlate = true
	if(bCheckPlate && getWeighingInterface()->getBalance()->IsMultiPlate())
	{
		// Contrôle de l'index du plateau
		short plateIndex = getWeighingInterface()->getBalance()->getPlateIndex();
		////////////////////////////////////////////////////////////////////////
		// On sauvegarde le buffer 
		receptionMsg();
		if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
		{
			getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Save Buffer" << endl;
			getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< inmsg  <<" -> Saved"<< endl;
		}
		strcpy(ChBufferSave,inmsg);
		if (ChBufferSave[0] != '\0')
		{
			bBuffSaved = true; // on indique qu'on a enregistré le buffer
		}
		istatusSav = istatus;
		// on vide le buffer
		memset(inmsg,0,MAXC+1);
		////////////////////////////////////////////////////////////////////////
		sprintf(ioptr_d,"%c%c %s",
			APPLICATION,'R',"010");//"AR 010"
		emissionMsg();

		if (istatus == OK)
		{
			getWeighingInterface()->editionMessage();
			receptionMsg();
		}

		if (istatus == OK)
		{
			// la réponse est "AR A n" avec n = numéro du plateau
			if(strncpy(inmsg,"AR A",4) == 0)
			{
				// extraction du numéro de plateau
				char cIndex = inmsg[strlen(inmsg)-1];
				short nIndex = cIndex - (short)'0';
				if (plateIndex != nIndex)
				{
					// On ne se trouve pas sur le bon plateau
					ostatus = BAD_PLATE;
					rep = ope;
					delete [] unit;
					opo = rep;
					sto = ostatus;
					return;
				}
			}
			else
			{
				// Réponse inconnue
					ostatus = UNKNOWN_ANSWER;
					rep = ope;
					delete [] unit;
					opo = rep;
					sto = ostatus;
					return;
			}
		}
		else
		{
			ostatus = istatus;
		}
		// On restaure la valeur du buffer
		if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
		{
			getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Retore Buffer" << endl;
			getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< ChBufferSave  <<" -> Restored"<< endl;
		}
		strcpy(inmsg,ChBufferSave);
		istatus = istatusSav;
	}
	// Le contrôle du plateau dans le cas d'un multi-plateau s'est bien passé
	// on continue
	switch (ope)
	{
	case E_KBD:						//blocage clavier
		sprintf(ioptr_d,"%s",LOCKK);
		_keyState = false; 
		transaction();
		break;
	case D_KBD:						//déblocage clavier
		sprintf(ioptr_d,"%s",UNLOCKK);
		_keyState = true; 
		transaction();
		break;
	case RAZ:						//remise a zero de la balance
		sprintf(ioptr_d,"%c",
			REMISEAZERO);			//"Z"
		transaction();
		break;
	case TAR:						//consigne de tare a envoyer
		strncpy(unit,"   ",3);
		strcpy(unit,getWeighingInterface()->getWeightUnit());
		transcodeUnite(unit);
		if (controleUnite(unit))
		{
			sprintf(ioptr_d,"%s %.3f %s",
				SETTARE,
				getWeighingInterface()->getTare(),
				unit);				//"TA <consigne> <unite>"
		}
		else
		{
			strcpy(unit,getWeighingInterface()->getResWeightUnit());
			transcodeUnite(unit);
			sprintf(ioptr_d,"%s %.3f %s",
				SETTARE,
				getWeighingInterface()->getTareUnitBal(),
				unit);				//"TA <consigne> <unite>"
		}
		transaction();
		break;
	case RAZ_TAR:					//effacement de la valeur de tare
		sprintf(ioptr_d,"%s ",RAZTARE);   //"TAC"
		transaction();
		break;
	case DETAR:						//le poids sur le plateau est considéré
									// comme le poids de tare si==0 msg double
		sprintf(ioptr_d,"%c",TARE); //"T"
		transaction();
		break;
	case CHG_U:						//changement d'unite de mesure
		strncpy(unit,"   ",4);
		strcpy(unit,getWeighingInterface()->getWeightUnit());
		transcodeUnite(unit);
		if (controleUnite(unit))
		{
			sprintf(ioptr_d,"%c %s",
				UNIT_POIDS,
				unit);				//"U <unite poids>"
			transaction();
		}
		else
			ostatus = UNIT_ERROR;
		break;
	case CHG_P:						//changement de plateau à travers ID5
		//sprintf(ioptr_d,"%c%c %s %d",
		//	APPLICATION,WRITE,"010",
		//	getWeighingInterface()->getScaleNumber());//"AW 010 <info>"
		sprintf(ioptr_d,"%c%c %s %d",
			APPLICATION,WRITE,"010",
			getWeighingInterface()->getBalance()->getPlateIndex());//"AW 010 <info>"
		transaction();
		break;
	case PDS_S:						//acquisition d'un poids stable
		sprintf(ioptr_d,"%c",NET);	//"S"
		transaction();
		break;
	case PDS_I:						//acquisition d'un poids immediat
		sprintf(ioptr_d,"%c%c",
			NET,IMMEDIAT);			//"SI"
		transaction();
		break;
	case PDS_IR:					//boucle d'acquisition d'un poids immediat
		sprintf(ioptr_d,"%c%c%c",
			NET,IMMEDIAT,REPEAT);	//"SIR"
		transaction();
		break;
	case ART_S:						//acquisition d'un article stable (net,brut,tare)
		sprintf(ioptr_d,"%c%c",
			NET,ARTICLE);			//"SX"
		transaction();
		break;
	case ART_I:						//acquisition d'un article immediat
		sprintf(ioptr_d,"%c%c%c",
			NET,ARTICLE,IMMEDIAT);	//"SXI"
		transaction();
		break;
	case DSPL:						//affichage d'un message
		break;
		sprintf(ioptr_d,"%c \"%s\"",
			DISPLAY,
			getWeighingInterface()->getWeighingMessage());   //"D <texte>"
		transaction();
		break;
	case RAZ_DSPL:					//"DW"
		sprintf(ioptr_d,"%s",RAZDISPLAY);
		transaction();
		break;
	case BIP:						//pas de message sonore
		break;
	case PRT:						//pas envoi d'information à imprimer
		break;
	case WAIT_MSG:					//lecture du message le + vieux
		if(_keyOnly == false)
		{
			sprintf(ioptr_d,"%s",KEYONLY);
			_keyState = true; 
			_keyOnly = true;
			transaction();
		}
		i = getWeighingInterface()->getMsgWaitingTime();
		j=1;
		do
		{
		////////////////////////////////////////////////////////////////////////
			// gbe : si on a sauvegardé une trame il ne faut pas l'écraser lors de la première boucle
			// on remet ensuite le bool à false pour repartir
			if (bBuffSaved == false)
			{
				receptionMsg();			 //pour filtrage des operations manuelles
								  		 // et les messages doubles
			}
			else
			{
				bBuffSaved = false;
			}
		////////////////////////////////////////////////////////////////////////
			if(strlen(inmsg)>1 && strncmp(inmsg,"SA",2) == 0)
			{
				// On a appuyé sur la touche de changement de plateau lors de 
				// l'attente de la MAZ ou de la Tare !!!
				istatus = BAD_PLATE;
				// on sort de la boucle
				break;
			}
		}
		while ((istatus != OK) && (++j <= i));

		if (istatus == OK)
		{
			decodeResponse();
			// Si on est dans le cas de la tare, il faut intéroger la tare
			if(rep==TAR)
			{
				sprintf(ioptr_d,"%c",
					TARE);				//"T"
				transaction();
			}
			if(rep==RAZ)
			{
				sprintf(ioptr_d,"%c",
					REMISEAZERO);				//"Z"
				transaction();
			}
			sprintf(ioptr_d,"%s",UNLOCKK);
			_keyState = true;
			_keyOnly = false;
			saveOpe = rep;
			transaction();
			rep = saveOpe;
		}
		else
		{
			ostatus = istatus;
			rep = ope;
		}
		break;
	case UNITE_P:					//acquisition de l'unite de poids de
									// la balance
		break;
	case SERIAL_NUM: // demande du numéro de série
		sprintf(ioptr_d,"%s","I4");				//"I4"
		transaction();
		break;

	default:
		ostatus = UNKNOWN2;
		rep = ope;
		break;
	}

	delete [] unit;
	opo = rep;
	sto = ostatus;
}
/*************************************************
* appel du multi com                             *
*************************************************/
void AdxMSICS::callMultiCom(int pornum, ComOperation comOp, char* iodata)
{
	DriverStatus sta;
	int nbcMax = 256;

	getWeighingInterface()->getMultiCom()->comOperationTreatment(pornum,
		comOp,
		iodata,
		sta,
		nbcMax);

	istatus = sta;
}


/*************************************************
*    émission de la trame selon protocole        *
*************************************************/
void AdxMSICS::emissionMsg(void)
{
	char trailer[3] = {"\r\n"};
	strcat(ioptr_d,trailer);
	// 06.04 TRACE
	if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
	{
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Send to scaleMT-SICS" << endl;
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< ioptr_d  << endl;
	}

	callMultiCom(pornum,SEND,ioptr_d);
}

/*************************************************
*  réception d'un message selon protocole        *
*************************************************/
void AdxMSICS::receptionMsg(void)
{
	// gbe 11/08
	// On redispatch les évennements de l'interface pour éviter les freeze
	if (getWeighingInterface()->getInterface()->getDisplay()->hasEvents())
	{
		getWeighingInterface()->getInterface()->getDisplay()->readAndDispatchEvents();
	}
	for (int i =0; i<MAXC; i++)
	{
//		inmsg[i] = ' ';
		inmsg[i] = '\0';
	}
	callMultiCom(pornum,READ,inmsg);
	// 06.04 TRACE
	if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
	{
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Receive from scaleMT-SICS" << endl;
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< inmsg  << endl;
	}
}

/*************************************************
* transaction d'émission-réception               *
*************************************************/
void AdxMSICS::transaction(void)
{
	emissionMsg();

	if (istatus == OK)
	{
		getWeighingInterface()->editionMessage();
		receptionMsg();
	}

	if (istatus == OK)
		decodeResponse();
	else
		ostatus = istatus;
}
/*************************************************
* decodage de la reponse:                        *
* -mise en forme de la partie applicative,       *
* -mise a jour de l'operation,                   *
* -mise a jour du statut de retour               *
*************************************************/
void AdxMSICS::decodeResponse(void)
{
	ostatus = OK;					//le statut est d'office mis a OK
	rep = ope;
	char resUnit[4] = "";
	char resWeight[20] = "";
	char resScale[2] = "";
	double weight;
	char* pszTmp = NULL;
	char balUnit[4] = "";
	char wChTrame[MAXC+1];			// Caine contenant le message reçu sans CR LF
	short wni = 0;
	short wnLgTrame = 0;
	bool wbRetour = true;
	//la reponse est d'office positionnée

	// Suppression de CR et LF en fin de trame
//	strncpy(wChTrame,inmsg,strlen(inmsg)-2);
//	wChTrame[strlen(inmsg)-2] = '\0';

	// lignes déplacées	
	AdxWeighingInterface* wi = NULL;
	AdxBalance* balance = NULL;
	wi = getWeighingInterface();
	balance=wi->getBalance(); // Récupération de la balance courante
	if (ope == SERIAL_NUM)
	{
		/*AdxWeighingInterface* wi = NULL;
		AdxBalance* balance = NULL;
		wi = getWeighingInterface();
		balance=wi->getBalance(); // Récupération de la balance courante */
		// on est dans le cas du numéro de série, la balance ne répond
		// pas autre chose. C'est ici que le test entre le numéro retourné
		// et le numéro stocké dans la classe balance doit être effectué
		if (wi->getInterface()->getTraceMode() == 1)
		{
			// trace du numéro de série
			wi->getInterface()->_traceFile << "\t\t\t\t"<< "decodeResponse" << endl;
    		wi->getInterface()->_traceFile << "\t\t\t\t"<< "SCALE SERIAL NUMBER=" <<inmsg  << endl;
		}
			wi->afChRTrim(inmsg);
			wi->afChLTrim(inmsg);
			strncpy(wChTrame,inmsg+6,strlen(inmsg)-7);
			wChTrame[(strlen(inmsg)-7)] = '\0';
		if (wi->getInterface()->getTraceMode() == 1)
		{
			// trace du numéro de série
    		wi->getInterface()->_traceFile << "\t\t\t\t"<< "SCALE SERIAL NUMBER(extract)=" <<wChTrame  << endl;
		}

		if (balance->getSerialNumber()!=NULL && balance->getSerialNumber()[0] !='\0' && strcmp(balance->getSerialNumber(),wChTrame) != 0)
		{
			// la balance connecté NE CORRESPOND PAS à la blance attendu
			if (wi->getInterface()->getTraceMode() == 1)
			{
				// trace du numéro de série
				wi->getInterface()->_traceFile << "\t\t\t\t"<< "ERROR" << endl;
				wi->getInterface()->_traceFile << "\t\t\t\t"<< "SCALE SERIAL NUMBER EXPECTED="<< balance->getSerialNumber() << endl;
    			wi->getInterface()->_traceFile << "\t\t\t\t"<< "SCALE SERIAL NUMBER RETURNED=" <<wChTrame  << endl;
			}
			ostatus = NO_RESPONSE;
			return;
		}
	}

	strcpy(wChTrame,inmsg);
	wbRetour = IsCorrect(wChTrame);

	// On à une trame valide, il faut savoir quel est l'ordre dont on a la réponse
	wnLgTrame = strlen(wChTrame);
	// Recherche du 1er espace de la trame délimitant la commande exécutée
	for(wni=0;wni<wnLgTrame;wni++)
	{
		if(wChTrame[wni] == ' ')
			break;
	}
////////////////////////////////////////////////////////////////////////////
// ATTENTION !!! En cas d'erreur on ne sort pas de la fonction sans avoir //
//               renseigné la variable rep                                //
////////////////////////////////////////////////////////////////////////////
	if(wni == 1)
	{
		// réponse des ordres sur 1 caractère:
		// D Display message
		// K Key control
		// S Poids stable
		// Z RAZ
		// T Tare
		switch(wChTrame[0])
		{
		case DISPLAY:		// Retour de la commande de display
			if(wbRetour == false)
			{
				return;
			}
			break;
		case KEY_PAC:		// Retour de la commande de gestion du clavier
							// mais aussi gestion des touches enfoncées
			if(strlen(wChTrame) > 3)
			{
				// On a pressé une touche
				// on attend un peu et on receptionne à nouveau une commande car l'appui
				// sur une touche génère deux messages
				if(wChTrame[2] == 'B')
				{
					delay(500);
					receptionMsg();
				}
				//114545 mm 10.2016 - key code 's value depends of model of scale
				/*if (wChTrame[4] == KEYTAR)
				{
					rep = TAR;
				}
				else if (wChTrame[4] == KEYRAZ)
				{
					rep = RAZ;
				}*/ 
				if (strlen (balance->getKeyRazSca()) == 1)
				{
					if (wChTrame[4] == *(balance->getKeyTarSca()))
					 {
	   					rep = TAR;
					 }
					 else if (wChTrame[4] == *(balance->getKeyRazSca()))
					 {
	   					rep = RAZ;
					 }
				}
				else
				{
					if  ((wChTrame[4] == *(balance->getKeyTarSca())) && (wChTrame[5] ==  *(balance->getKeyTarSca()+1)))
					{
	   					rep = TAR;
					}
					else if ((wChTrame[4]== *(balance->getKeyRazSca()))  && (wChTrame[5] ==  *(balance->getKeyRazSca()+1))) 
					{
	   					rep = RAZ;
					}
				}
			}
			else
			{
				if(_keyState=true)
				{
					rep = D_KBD;
				}
				else
				{
					rep = E_KBD;
				}
			}
			
			if(wbRetour == false)
			{
				return;
			}
			break;
		case NET:
			switch(wChTrame[2])
			{
			case DYNAMIC:
				rep = PDS_I;
				break;
			case STABLE:
				rep = PDS_S;
				break;
			}
				
			if(wbRetour == false)
			{
				return;
			}
			// Extraire le poids reçu de la pesée
			wbRetour = extractWheight(wChTrame,
									  wni,
									  &weight,
									  resUnit);
			getWeighingInterface()->setResWeight(weight);
			break;
		case REMISEAZERO:	// Remise à zero
			rep = RAZ;
			if(wbRetour == false)
			{
				return;
			}
			break;
		case TARE:
			rep = TAR;
			if(wbRetour == false)
			{
				return;
			}
			// Extraire le poids reçu de la tare
			wbRetour = extractWheight(wChTrame,
									  wni,
									  &weight,
									  resUnit);
			getWeighingInterface()->setResTare(weight);
			strcpy(balUnit,getWeighingInterface()->getResWeightUnit());
			if (strcmp(strupr(resUnit),strupr(balUnit)) != 0)
			{
				weight = getWeighingInterface()->getInterface()->getDonnees()->
					convertir2(getWeighingInterface()->getResTare(),
					resUnit,
					balUnit);
				getWeighingInterface()->setResTare(weight);
			}
			break;
		default:
			ostatus = UNKNOWN_ANSWER;
		}
	}
	if(wni == 2)
	{
		// réponse des ordres sur 2 caractère:
		// TA Inquiry of tare value
		if(strncmp(wChTrame,ASKTARE,wni) != 0 && strncmp(wChTrame,WRITEPROG,wni) != 0)
		{
			// Ordre inconnu
			ostatus = UNKNOWN_ANSWER;
		}
		else
		{
			if (strncmp(wChTrame,ASKTARE,wni) == 0)
			{
			rep = TAR;
			if(wbRetour == false)
			{
				return;
			}
			// Extraire le poids reçu de la tare
			wbRetour = extractWheight(wChTrame,
									  wni,
									  &weight,
									  resUnit);
			getWeighingInterface()->setResTare(weight);
			strcpy(balUnit,getWeighingInterface()->getResWeightUnit());
			if (strcmp(strupr(resUnit),strupr(balUnit)) != 0)
			{
				weight = getWeighingInterface()->getInterface()->getDonnees()->
					convertir2(getWeighingInterface()->getResTare(),
					resUnit,
					balUnit);
				getWeighingInterface()->setResTare(weight);
				}
			}
			else
			{
				// réponse suite à un changement de plateau
				// AW A Bloc d'application écrit
				// AW I Bloc d'application non présent
				// AW L Le bloc d'application ne peut pas être écrit
				switch (wChTrame[wni+1])
				{
				case 'I':
				case 'L':
					// Erreur
					ostatus = UNKNOWN_ANSWER;
					break;
				case 'A':
				default:
					break;
				}
			}
		}
	}
	if(wni == 3)
	{
		// réponse des ordres sur 3 caractère:
		//
		// réponse des ordres sur 2 caractère:
		// TA Inquiry of tare value
		if(strncmp(wChTrame,RAZTARE,wni)!=0)
		{
			// Ordre inconnu
			ostatus = UNKNOWN_ANSWER;
		}
		else
		{
			rep = TAR;
			if(wbRetour == false)
			{
				return;
			}
		}
	}
}

/*************************************************
* Transcodage unité                              *
*************************************************/
void AdxMSICS::transcodeUnite(char* unit)
{
	// 61152 mm 01.10
	// Mise en minuscule + suppression des espaces
	getWeighingInterface()->afChLower(unit);
	getWeighingInterface()->afChRTrim(unit);
	getWeighingInterface()->afChLTrim(unit);
}


/*************************************************
* Contrôle unité                                 *
*************************************************/
bool AdxMSICS::controleUnite(char* unit)
{
	if (strcmp(unit,"kg") == 0
		|| strcmp(unit,"g") == 0
		|| strcmp(unit,"lb") == 0
		|| strcmp(unit,"oz") == 0
		|| strcmp(unit,"ozt") == 0
		|| strcmp(unit,"dwt") == 0)
		return true;
	else
		return false;
}

/*************************************************
* Temporisation en milli secondes                *
*************************************************/
void AdxMSICS::delay(int milliSec)
{
	clock_t start, end;
	start = clock();
	do
	{
		end = clock();
	}
	while ((end- start) < milliSec);
}

/*
* --------------------------------------------------------------------------
* Fonction    : OrderReply
* But         : Contrôle la réponse à l'ordre donné.
* Explication : La chîne contenant la trame ne doit pas contenir les
*               caractères CR et LF
*               La variable locale ostatus est affecté par cette fonction
* Retour      : Bool à TRUE si OK, FALSE si Problème
* --------------------------------------------------------------------------
*/
bool AdxMSICS::IsCorrect(char* Data)		// Trame à contôler
{
	bool  wbRetour = true;
	short wni = 0;
	short wnLgData = 0;

	// En premier lieu on contrôle les erreurs possibles 
	if(strcmp(Data,SYNTAXERROR)==0)
	{
		ostatus = SYNTAX_ERROR;
		wbRetour = false;
	}
	if(strcmp(Data,TRANSMISSION_ERROR)==0)
	{
		ostatus = TRANSMIT_ERROR;
		wbRetour = false;
	}
	if(strcmp(Data,LOGICAL_ERROR)==0)
	{
		ostatus = LOGISTIC_ERROR;
		wbRetour = false;
	}
	if(wbRetour == false)
	{
		return false;
	}

	wnLgData = strlen(Data);
	// Recherche du 1er espace de la trame délimitant la commande exécutée
	for(wni=0;wni<wnLgData;wni++)
	{
		if(Data[wni] == ' ')
			break;
	}

	switch(Data[wni+1])
	{
	case NOTEXECUTE:
	case LOGISTIC:					// 'L' Commande comprise, mais mauvais paramètres
		ostatus = UNAVAILABLE;
		wbRetour = false;
		break;
	case SURCHARGE:
		ostatus = SURCHARGE_ERROR;
		wbRetour = false;
		break;
	case SOUSCHARGE:
		ostatus = SOUSCHARGE_ERROR;
		wbRetour = false;
		break;
	}

	return wbRetour;
}

/*
* --------------------------------------------------------------------------
* Fonction    : extractWheight
* But         : Extrait le poids ainsi que son unité
* Explication : La chîne contenant la trame ne doit pas contenir les
*               caractères CR et LF
*               
* Retour      : Bool à TRUE si OK, FALSE si Problème
* --------------------------------------------------------------------------
*/
bool AdxMSICS::extractWheight(char*  Data,		   // Trame à contôler
							  short  CommandLength,// Longueur de la commande
							  double* Weight,      // Poids
							  char*  Unit)         // Unité
{
	char  wChWeight[MAXC+1];
	char  wChUnit[MAXC+1];
	short wnEspace = 0;
	short wnPosUnit = 0;
	short wnUnitLenght = 0;
	short wnDataLenght = 0;

	wChWeight[0] = '\0';
	wChUnit[0] = '\0';
	
// format de la trame "S S    -100.00 Kg");
// format de la trame "TA S    -100.00 g"); en théorie 
// format de la trame "TA S   -100.00 g"); en pratique !!!
// Il y a un bug dans le protocole mettler qui oublie de mettre un espace
// entre le status de la commande et les 10 caractères du poids
// 114545 mm 10.2016 : modification of the way of recovery of weight and unit 
// -> trame différente en fonction du modèle de balance
// -> different pattern according to model of scale
	wnDataLenght = strlen(Data);
	wnPosUnit = wnDataLenght-1;
// Recherche de la position de l'unit en partant de la fin de la trame
	for (;;)
	{
		if (wnPosUnit>=0 && Data[wnPosUnit]==' ')
		{
			//wnPosUnit++;
			//wnUnitLenght = wnDataLenght-wnPosUnit;
			wnUnitLenght = wnDataLenght-3;	//114545 mm 09.2016
			break;
		}
		wnPosUnit--;
	}
	//Récupération du poids
	//strncpy(wChWeight,Data+(CommandLength+2),wnDataLenght-(wnUnitLenght+CommandLength+2));
	//wChWeight[wnDataLenght-(wnUnitLenght+CommandLength+2)] = '\0';
	strncpy(wChWeight,Data+(CommandLength+2),wnDataLenght-(CommandLength+2));	//114545 mm 09.2016
	wChWeight[wnDataLenght-(CommandLength+2)] = '\0';							//114545 mm 09.2016

	//strncpy(wChUnit,Data+(wnPosUnit),wnDataLenght-wnPosUnit);
	//wChUnit[wnUnitLenght] = '\0';
	strncpy(wChUnit,Data+wnUnitLenght,wnDataLenght-wnUnitLenght);	//114545 mm 09.2016
	wChUnit[wnDataLenght-wnUnitLenght]= '\0';		//114545 mm 09.2016

	// Mise en forme de l'unité
	transcodeUnite(wChUnit);

	strcpy(Unit,wChUnit);

	*Weight = atof(wChWeight);

	return true;
}