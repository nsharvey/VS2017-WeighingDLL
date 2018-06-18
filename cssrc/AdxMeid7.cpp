// AdxMeid7.cpp
// ------------
// project : Adonix X3 Scales
// author : MC
// V130 : MC 2001.05.28
//--------------------------------------------------------------
//

/******************************************************
*                                                     *
*    PILOTE DE PERIPHERIQUE METTLER ID7 MULTIRANGE    *
*                                                     *
*******************************************************
*                                                     *
*  REALISATION CONCEPTUELLE : MC                      *
*              MATERIELLE   : METTLER ID7 MULTIRANGE  *
*              LOGICIELLE   : MC                      *
*                                                     *
*-----------------------------------------------------*
*                                                     *
*  LANGAGE     C++        compilation MSV6            *
*                                                     *
*-----------------------------------------------------*
*                                                     *
*  OBJECTIF    Le driver assurera l'émission et la    *
*              réception de caractères sur un des 8   *
*              ports suivant le protocole METTLER.    *
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

#include "stdafx.h"
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
#include "AdxMeid7.h"
#include "AdxBalance.h"

#include <fstream>							// 06.04 TRACE

using std::endl;							// 06.04 TRACE



static char ptl[DOWN_BUF_SIZ];
static char inmsg[MAXC+1];             //contient le message traite recu de l'aval
static unsigned char Icar;             //contient le caractere courant traite
//static char io_dd[2];
static char ioptr_d[DOWN_BUF_SIZ];     //contient le message à envoyer
//char *ioptr_u;                         //pointeur absolu sur le message recu
static DriverStatus istatus;           //statut acquis en entree(par l'aval)
static DriverStatus ostatus;           //statut renseigne en sortie(pour l'amont)
static WeighingOperation ope;          //operation a traiter
static WeighingOperation rep;          //reponse sur l'operation lue que l'on retourne
									   // a l'appelant
static int  pornum;                    //indice du port courant a traiter

/*************************************************
*    traitement de l'ordre de pesée              *
*************************************************/
void AdxMeid7::weighingTreatment(AdxWeighingInterface* wi,
								 WeighingOperation& opi,
								 int& porid,
								 WeighingOperation& opo,
								 DriverStatus& sto,
								 bool bCheckPlate)
{
	setWeighingInterface(wi);
	ope = opi;
	pornum = porid;
	rep = opo;
	ostatus = sto;

	int i;
	long j;
	char Chaine[64]="";                //Chaine pour manipulations diverses
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
		sprintf(ioptr_d,"%c%c%s",
			APPLICATION,'R',"010");//"AR010"
		emissionMsg();

		if (istatus == OK)
		{
			getWeighingInterface()->editionMessage();
			receptionMsg();
		}

		if (istatus == OK)
		{
			// la réponse est "AB n" avec n = numéro du plateau
			if(strncmp(inmsg,"AB",2) == 0)
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
		case CONTROLE_QUITTANCE:
			rep=ope;
			ostatus=OK;
//			itoa(ModeManuel,Chaine,10);	   //balance où l'opérateur
									       // valide au clavier du PC
//			strcpy(ioptr_u,Chaine);        //copie chaine dans ioptr_u qui 
			                               // est un pointeur long
			break;


		case E_KBD:                    //blocage/deblocage clavier
		case D_KBD:                    //"R0" ou "R1"
			sprintf(ioptr_d,"%c%c",KBD,
				(ope == E_KBD)? ENABLE :DISABLE);
			transaction();
			break;
		case RAZ:                      //remise a zero de la balance
			sprintf(ioptr_d,"%c",
			    REMISEAZERO);              //"Z"
			transaction();
			break;
		case TAR:                      //consigne de tare a envoyer
			strncpy(unit,"   ",3);
			strcpy(unit,getWeighingInterface()->getWeightUnit());
			transcodeUnite(unit);
			if (controleUnite(unit))
			{
				sprintf(ioptr_d,"%c %.3f %s",
				    TARE,
					getWeighingInterface()->getTare(),
					unit);					//"T <consigne> <unite>"
			}
			else
			{
				strcpy(unit,getWeighingInterface()->getResWeightUnit());
				transcodeUnite(unit);
				sprintf(ioptr_d,"%c %.3f %s",
				    TARE,
					getWeighingInterface()->getTareUnitBal(),
					unit);					//"T <consigne> <unite>"
			}
			transaction();
			break;
		case RAZ_TAR:                  //effacement de la valeur de tare
			sprintf(ioptr_d,"%c ",TARE);   //"T "
			transaction();
			break;
		case DETAR:                    //le poids sur le plateau est considéré
			                           // comme le poids de tare si==0 msg double
			sprintf(ioptr_d,"%c",TARE);    //"T"
			transaction();
			break;
		case CHG_U:                    //changement d'unite de mesure
			strncpy(unit,"   ",4);
			strcpy(unit,getWeighingInterface()->getWeightUnit());
			transcodeUnite(unit);
			if (controleUnite(unit))
			{
				sprintf(ioptr_d,"%c %s",
					UNIT_POIDS,
					unit);				   //"U <unite poids>"
				transaction();
			}
			else
				ostatus = UNIT_ERROR;
			break;
		case CHG_P:                    //changement de plateau à travers ID5

			/*   sprintf(ioptr_d,"%c %d",
				CHANGE,i);*/               //"S <nø plateau>"

			//sprintf(ioptr_d,"%c%c%s %d",
			//	APPLICATION,WRITE,"010",
			//	getWeighingInterface()->getScaleNumber());//"AW010 <info>"
			sprintf(ioptr_d,"%c%c%s %d",
				APPLICATION,WRITE,"010",
				getWeighingInterface()->getBalance()->getPlateIndex());//"AW010 <info>"
			transaction();
			break;
		case PDS_S:                    //acquisition d'un poids stable
			sprintf(ioptr_d,"%c",NET);     //"S"
			transaction();
			break;
		case PDS_I:                    //acquisition d'un poids immediat
			sprintf(ioptr_d,"%c%c",
				NET,IMMEDIAT);             //"SI"
			transaction();
			break;
		case PDS_IR:                   //boucle d'acquisition d'un poids immediat
			sprintf(ioptr_d,"%c%c%c",
				NET,IMMEDIAT,REPEAT);             //"SIR"
			transaction();
			break;
		case ART_S:                    //acquisition d'un article stable (net,brut,tare)
			sprintf(ioptr_d,"%c%c",
				NET,ARTICLE);              //"SX"
			transaction();
			break;
		case ART_I:                    //acquisition d'un article immediat
			sprintf(ioptr_d,"%c%c%c",
				NET,ARTICLE,IMMEDIAT);     //"SXI"
			transaction();
			break;
		case APL_R:                    //lecture d'un bloc d'application
//			strncpy(ioptr_u,ptl,3);        // bizarre semble à l'envers        
//			sprintf(ioptr_d,"%c%c%s",
//				APPLICATION,LECTURE,ptl);  //"AR<nø bloc>"
//			transaction();
			break;
		case APL_W:                    //écriture d'un bloc d'application
//			strncpy(ioptr_u,ptl,
//				DOWN_BUF_SIZ);             //la taille demandee est exageree 
//										   // ceci pour copier toute la zone data
//			sprintf(ioptr_d,"%c%c%s",
//				APPLICATION,WRITE,ptl);    //"AW<nø bloc> <info>"
//			transaction();
			break;
		case APL_C:                    //effacement du contenu d'un bloc d'application
//			strncpy(ioptr_u,ptl,3);        //un nø de bloc est sur 3 digits
//			sprintf(ioptr_d,"%c%c%s ",
//				APPLICATION,WRITE,ptl);    //"AW <nø bloc> "
//			transaction();
			break;
		case DSPL:                     //affichage d'un message
			sprintf(ioptr_d,"%c %s",
				DISPLAY,
				getWeighingInterface()->getWeighingMessage());   //"D <texte>"
			transaction();
//			delay(2000);                   //pause pour laisser le temps de lire le
										   // message
//			sprintf(ioptr_d,"%c",
//				DISPLAY);                  //annule le message courant.
										   // Cela évite un blocage caractérisé par l'* 
										   // affiché sur la METTLER
//			emissionMsg();
			break;
		case RAZ_DSPL:                 //"D"
			sprintf(ioptr_d,"%c",DISPLAY);
			transaction();
			break;
		case BIP:                      //message sonore
			sprintf(ioptr_d,"%c%c",
				DISPLAY,SOUND);            //"DS"
			transaction();
			break;
		case PRT:                      //envoi d'information à imprimer
			break;
		case WAIT_MSG:                 //lecture du message le + vieux
			i = getWeighingInterface()->getMsgWaitingTime();
			if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
			{
				getWeighingInterface()->getInterface()->_traceFile << "AdxMeid7::weighingTreatment debut WAIT MSG i="<<i << endl;
			}
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
			if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
			{
				getWeighingInterface()->getInterface()->_traceFile << "AdxMeid7::weighingTreatment Fin boucle status="<<istatus<< endl;
			}

			if (istatus == OK)
				decodeResponse();
			else
			{
				ostatus = istatus;
				rep = ope;
			}
			break;
		case UNITE_P:                    //acquisition de l'unite de poids de
										 // la balance
			break;
		case SERIAL_NUM: // demande du numéro de série
			// pas supporté
			break;
		default:
			ostatus = UNKNOWN2;
			rep = ope;
			break;
	}

	delete [] unit;
	opo = rep;
	sto = ostatus;
	// gbe 10/05/12 déplacement en fin de fonction pour éviter d'intérompre un ordre en cours
	// On redispatch les évennements de l'interface pour éviter les freeze
	if (getWeighingInterface()->getInterface()->getDisplay()->hasEvents())
	{
		getWeighingInterface()->getInterface()->getDisplay()->readAndDispatchEvents();
	}

}
/*************************************************
* appel du multi com                             *
*************************************************/
void AdxMeid7::callMultiCom(int pornum, ComOperation comOp, char* iodata)
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
* fonction lecture d'un element recu depuis      *
* un port COM à travers une carte multivoies     *
*************************************************/
/*
void AdxMeid7::readchar(void)
{
	char one[5] = "001 ";
	callMultiCom(pornum,READ,one);    //lecture d'un cacaractere recu
//	disable();
	double time1 = ((double) clock()) / CLOCKS_PER_SEC;
//	enable();
	while (istatus == EMPTY)           //teste si rien n'a ete recu
	{
//		disable();
		double timediff = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
		if (timediff > ATTENTE_UNITAIRE)    //teste time-out
		{
//			enable();
			istatus = NO_RESPONSE;     //cas pas de reponse en temps voulu
			Icar = NUL;
			return;
		}
		else                           //cas time-out non ecoule
		{
//			enable();
			*(one+2) = '1';            //nb d'elements a lire maj en cas
			                           //ou aucun element du buffer n'est disponible
			callMultiCom(pornum,READ,
						  one);        //on reitere la lecture d'un caractere recu
		}
	}
	Icar = *(one+3);
}
*/
/*************************************************
*    émission de la trame selon protocole        *
*************************************************/
void AdxMeid7::emissionMsg(void)
{
//---------------------------------------
//	double time1;
//	double timediff;
//	char* mess;
//		time1 = ((double) clock()) / CLOCKS_PER_SEC;
//---------------------------------------
	char trailer[3] = {"\r\n"};
	strcat(ioptr_d,trailer);
	// 06.04 TRACE
	if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
    {
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Send to scaleID7" << endl;
    	getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< ioptr_d  << endl;
    }

	callMultiCom(pornum,SEND,ioptr_d);
//-----------------------------------------------------
//		timediff = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
//		mess = new char[60];
//		sprintf(mess,"SEND %.3f",
//			timediff); 
//		MessageBox(NULL,mess,"Erreur",MB_OK);
//		delete [] mess;
//-----------------------------------------------------
}

/*************************************************
*  réception d'un message selon protocole        *
*************************************************/
void AdxMeid7::receptionMsg(void)
{
//---------------------------------------
//	double time1;
//	double timediff;
//	char* mess;
//		time1 = ((double) clock()) / CLOCKS_PER_SEC;
//---------------------------------------
	for (int i =0; i<MAXC; i++)
	{
//		inmsg[i] = ' ';
		inmsg[i] = '\0';
	}
	callMultiCom(pornum,READ,inmsg);
    	// 06.04 TRACE
    if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
    {
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Receive from scaleID7" << endl;
    	getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< inmsg  << endl;
    }

//-----------------------------------------------------
//		timediff = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
//		mess = new char[60];
//		sprintf(mess,"READ %.3f",
//			timediff); 
//		MessageBox(NULL,mess,"Erreur",MB_OK);
//		delete [] mess;
//-----------------------------------------------------

/*
	int cpt=0,                         //compteur d'éléments reçus
	nb_retry=0;
	char *ptr;
	ptr = inmsg;
	bool reception_en_cours = true;
	bool overflow = false;
	ptr = inmsg;
//	disable();
//	clk=0;
//	enable();
	readchar();
	if ((istatus == CCLOSE) || (istatus == PCLOSE))
	return;
	while (reception_en_cours)
	{
		switch(Icar)
		{
			case NUL:
				if (istatus == NO_RESPONSE)
				{					   //cas d'erreur de ligne ou de timeout
					if (nb_retry++ <= NB_MAX_RETRY)
						readchar();    //cas appareil bien present
					else
					{
						reception_en_cours = false;
						if (ptr != inmsg)  //cas fil coupe ou overflow de niveau 1
							istatus = TRONCATED_RESPONSE;
					}
				}
				else                   //cas connexion a froid un nul est emis
				{
					readchar();
				}
				break;
			case LF:
				reception_en_cours = false;
//				*(ptr-1) = 0; ?
				istatus = (overflow) ? OVERFLOW2:OK;
				break;
			case SYN:
			case ACK:                  //cas 1ere ou reconnexion on saute
				                       // les caracteres du protocole
			case DEL:
				readchar();
				break;
			default:                   //cas de la réception d'un msg
				if (cpt < MAXC)        //teste le dépassement de capacité
				{
					cpt++;
					*ptr++ = Icar;
				}
				else
					overflow = true;
				readchar();
				break;
		}
	}
*/

}
  
/*************************************************
* transaction d'émission-réception               *
*************************************************/
void AdxMeid7::transaction(void)
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
void AdxMeid7::decodeResponse(void)
{
	ostatus = OK;                      //le statut est d'office mis a OK
	rep = ope;
	char resUnit[4] = "";
	char resWeight[20] = "";
	char resScale[2] = "";
	int scaleNumber;
	double weight;
	char* pszTmp = NULL;
   	char balUnit[4] = "";
									   //la reponse est d'office positionnée

    
/*
//-----------------------------------------------------
		char* mess = new char[60];
		sprintf(mess,"inmsg %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
				*inmsg,
				*(inmsg+1),
				*(inmsg+2),
				*(inmsg+3),
				*(inmsg+4),
				*(inmsg+5),
				*(inmsg+6),
				*(inmsg+7),
				*(inmsg+8),
				*(inmsg+9),
				*(inmsg+10),
				*(inmsg+11),
				*(inmsg+12),
				*(inmsg+13),
				*(inmsg+14),
				*(inmsg+15));
		MessageBox(NULL,mess,"Erreur",MB_OK);
		delete [] mess;
//-----------------------------------------------------
*/
	                                   // avec l'operation a efectuer
	switch (*inmsg)
	{
		case APPLICATION:
//			strcpy(ioptr_u,inmsg+3);
			break;
		case UNIT_POIDS:               //changement d'unite de poids
			rep = CHG_U;
			if (*(inmsg+1) == PC_ACTION || *(inmsg+1) != OP_ACTION)
//				strcpy(ioptr_u,inmsg+2);
			{
//				strncpy(resUnit,inmsg+2,3);
				getWeighingInterface()
					->setResWeightUnit(getWeighingInterface()->getWeightUnit());
			}
			else
				ostatus = UNKNOWN_ANSWER;
			break;
		case DISPLAY:
		case KBD:
			if (*(inmsg+1) != AUTO)    //acquittement a un ordre blocage/deblocage
				                       // clavier ou demande d'affichage
				ostatus = UNKNOWN_ANSWER;
			break;
		case NET | CHANGE:
			switch(*(inmsg+1))
			{
				case PLATEAU:          //changement de plateau operateur
				case PC_ACTION:        //changement de plateau depuis PC
					rep = CHG_P;
					strncpy(resScale,inmsg+4,1);
					scaleNumber = atoi(resScale);
					getWeighingInterface()->setScaleNumber(scaleNumber);
//					*ioptr_u = *(inmsg+4); //contient le nø de plateau
//					*(ioptr_u+1) = 0;
					break;
				case ART_M:            //operateur a envoye l'article une fois stable
					rep = ART_S;
/*
					if (*(inmsg+3) == 'G') //Si a l'emplacement il y a bien le G,
						                   // c'est une interface 082 bien configurée
						strcpy(ioptr_u,
						inmsg+3);          //inmsg+3 pointe sur la 1ere lettre
					                       // pertinente le 'G' de GROSS
					else               //si ce n'est pas le G Aïe !
					{
						pszTmp = strstr(inmsg,
							"A012");       //on recherche le mot A012 
						                   // emplacement du net
						                   //on l'a trouvé/
						if (pszTmp != NULL)
						{
							*(pszTmp+3) = 'N'; //on remplace le 2 par N pour tromper
											   // la station; On est des malins !
						}
					}
*/
					break;
				case INCORRECT:
					switch(*(inmsg+2))
					{
						case 0:            //cas valeur non valable
							ostatus = UNAVAILABLE;
							break;
						case SURCHARGE:    //balance en surcharge
							ostatus = SURCHARGE_ERROR;
							break;
						case SOUSCHARGE:   //balance en souscharge
							ostatus = SOUSCHARGE_ERROR;
							break;
					}
					break;
				case DYNAMIC:          //cas ou la valeur est dynamique
					rep = PDS_I;
					ostatus = DYNAMIQUE;
					strncpy(resWeight,
						inmsg+3,10);          //inmsg+3 on saute l'espace
					weight = atof(resWeight);
					getWeighingInterface()->setResWeight(weight);
					strncpy(resUnit,inmsg+14,3);
//					transcodeUnite(resUnit);
//					getWeighingInterface()->setResWeightUnit(resUnit);
					break;
				case ARTICLE:          //article complet
					switch(*(inmsg+2))
					{
						case INCORRECT:
							switch(*(inmsg+3))
							{
								case 0:            //cas valeur non valable
									ostatus = UNAVAILABLE;
									break;
								case SURCHARGE:    //balance en surcharge
									ostatus = SURCHARGE_ERROR;
									break;
								case SOUSCHARGE:   //balance en souscharge
									ostatus = SOUSCHARGE_ERROR;
									break;
							}
							break;
						case DYNAMIC:
							ostatus = DYNAMIQUE;
						default:
							strncpy(resWeight,
								inmsg+9,10);         
							weight = atof(resWeight);
							getWeighingInterface()->setResGrossWeight(weight);
							strncpy(resUnit,inmsg+14,3);
//							transcodeUnite(resUnit);
//							getWeighingInterface()->setResWeightUnit(resUnit);
							strncpy(resWeight,
								inmsg+30,10);          
							weight = atof(resWeight);
							getWeighingInterface()->setResWeight(weight);
							strncpy(resWeight,
								inmsg+51,10);          
							weight = atof(resWeight);
							getWeighingInterface()->setResTare(weight);
							break;
					}
					break;
				default:               //reception du net affiche
					rep = PDS_S;
					strncpy(resWeight,
						inmsg+3,10);          //inmsg+3 on saute l'espace
					weight = atof(resWeight);
					getWeighingInterface()->setResWeight(weight);
					strncpy(resUnit,inmsg+14,3);
//					transcodeUnite(resUnit);
//					getWeighingInterface()->setResWeightUnit(resUnit);

					break;
			}
			break;
		case TARE:
			rep = TAR;
			switch (*(inmsg+1))
			{
				case SURCHARGE:
					ostatus = SURCHARGE_ERROR;
					break;
				case SOUSCHARGE:
					ostatus = SOUSCHARGE_ERROR;
					break;
				case AUTO:
				case MANUEL:
					// BCH le 03/01/2008 -> Suppression du switch
					strncpy(resWeight,
						inmsg+4,10);
					weight = atof(resWeight);
					getWeighingInterface()->setResTare(weight);

                    // sr 10.03 test pour balance en gramme
        			switch(*(inmsg+17))
		        	{
                        case ' ' :
                            strncpy(resUnit,inmsg+15,2);
                            break;
                        default :
                            strncpy(resUnit,inmsg+15,3);
                            break;
                    }
                    strcpy(balUnit,getWeighingInterface()->getResWeightUnit());
                    // si l'unité rendue n'est pas celle passée
					transcodeUnite(resUnit);
                    if (strcmp(strupr(resUnit),strupr(balUnit)) != 0)
                    {
						weight = getWeighingInterface()->getInterface()->getDonnees()->
                            convertir2(getWeighingInterface()->getResTare(),
							resUnit,
							balUnit);
                        getWeighingInterface()->setResTare(weight);
                    }
                    // fin sr 10.03
					break;
					// BCH : fin de la modification du 03/01/2008
			}
			break;
		case REMISEAZERO:
			rep = RAZ;
			switch (*(inmsg+1))
			{
				case SURCHARGE:
					ostatus = SURCHARGE_ERROR;
					break;
				case SOUSCHARGE:
					ostatus = SOUSCHARGE_ERROR;
					break;
				case AUTO:
				case MANUEL:
				default:
					break;
			}
			break;
		case ERROR2:
			switch (*(inmsg+1))
			{
				case LOGISTIC:
					ostatus = LOGISTIC_ERROR;
					break;
				case SYNTAX:
					ostatus = SYNTAX_ERROR;
					break;
				case TRANSMIT:
					ostatus = TRANSMIT_ERROR;
					break;
			}
			break;
		case KEY_PAC:                  //une information en provenance du PAC
			                           // est validee par l'operateur
			switch(*(inmsg+1))
			{
				case KEYP_A:
					rep = ID_A;
//					strcpy(ioptr_u,inmsg+3);
					break;
				case KEYP_B:
					rep = ID_B;
//					strcpy(ioptr_u,inmsg+3);
					break;
				case KEYP_C:
					rep = ID_C;
//					strcpy(ioptr_u,inmsg+3);
					break;
				case KEYP_D:
					rep = ID_D;
//					strcpy(ioptr_u,inmsg+3);
					break;
				default:
					break;
			}
			break;
		default:
//			strcpy(ioptr_u,
//				inmsg);                //on recopie integralement le message
									   // incongru
			ostatus = UNKNOWN2;
			break;
	}
}

/*************************************************
* Transcodage unité                              *
*************************************************/
void AdxMeid7::transcodeUnite(char* unit)
{
/*	if (strcmp(unit,"G") == 0) strcpy(unit,"g");
//	if (strcmp(unit,"g") == 0) strcpy(unit,"g");
	if (strcmp(unit,"KG") == 0) strcpy(unit,"kg");
	if (strcmp(unit,"Kg") == 0) strcpy(unit,"kg");
//	if (strcmp(unit,"kg") == 0) strcpy(unit,"kg");
	if (strcmp(unit,"LB") == 0) strcpy(unit,"lb");
	if (strcmp(unit,"Lb") == 0) strcpy(unit,"lb");
	if (strcmp(unit,"OZ") == 0) strcpy(unit,"oz");
	if (strcmp(unit,"Oz") == 0) strcpy(unit,"oz");
	if (strcmp(unit,"OZT") == 0) strcpy(unit,"ozt");
	if (strcmp(unit,"Ozt") == 0) strcpy(unit,"ozt");
	if (strcmp(unit,"DWT") == 0) strcpy(unit,"dwt");
	if (strcmp(unit,"Dwt") == 0) strcpy(unit,"dwt");

	if (strcmp(unit,"g  ") == 0) strcpy(unit,"g");
	if (strcmp(unit,"kg ") == 0) strcpy(unit,"kg");

	// BCH le 23/01/2008
	if (strcmp(unit,"g ") == 0) strcpy(unit,"g");
*/
	
	// 61152 mm 01.10
	// Mise en minuscule + suppression des espaces
	getWeighingInterface()->afChLower(unit);
	getWeighingInterface()->afChRTrim(unit);
	getWeighingInterface()->afChLTrim(unit);
}


/*************************************************
* Contrôle unité                                 *
*************************************************/
bool AdxMeid7::controleUnite(char* unit)
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
void AdxMeid7::delay(int milliSec)
{
	clock_t start, end;
	start = clock();
	do
	{
		end = clock();
	}
	while ((end- start) < milliSec);
}
