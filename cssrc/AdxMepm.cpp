// AdxMepm.cpp
// -----------
// project : Adonix X3 Scales
// author : MC
// V130 : MC 2001.05.28
//--------------------------------------------------------------
//

/******************************************************
*                                                     *
*    PILOTE DE PERIPHERIQUE METTLER PM 3000           *
*                                                     *
*******************************************************
*                                                     *
*  REALISATION CONCEPTUELLE : MC                      *
*              MATERIELLE   : METTLER PM 3000         *
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
#include "AdxWeighingInterface.h"
#include "AdxMultiCom.h"
#include "AdxMepm.h"
#include "AdxInterface.h"

static char ptl[DOWN_BUF_SIZ];
static char inmsg[MAXC+1];             //contient le message traite recu de l'aval
static unsigned char Icar;             //contient le caractere courant traite
//static char io_dd[2];
static char ioptr_d[DOWN_BUF_SIZ];     //contient le message à envoyer
//char *ioptr_u;                       //pointeur absolu sur le message recu
static DriverStatus istatus;           //statut acquis en entree(par l'aval)
static DriverStatus ostatus;           //statut renseigne en sortie(pour l'amont)
static WeighingOperation ope;          //operation a traiter
static WeighingOperation rep;          //reponse sur l'operation lue que l'on retourne
									   // a l'appelant
static int  pornum;                    //indice du port courant a traiter

/*************************************************
*    traitement de l'ordre de pesée              *
*************************************************/
void AdxMepm::weighingTreatment(AdxWeighingInterface* wi,
								 WeighingOperation& opi,
								 int& porid,
								 WeighingOperation& opo,
								 DriverStatus& sto)
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
//			sprintf(ioptr_d,"%c%c",KBD,
//				(ope == E_KBD)? ENABLE :DISABLE);
//			transaction();
//			break;
		case RAZ:                      //remise a zero de la balance
//			sprintf(ioptr_d,"%c",
//			    REMISEAZERO);              //"Z"
//			transaction();
			ostatus = UNKNOWN2;
			rep = ope;
			break;
		case TAR:                      //consigne de tare a envoyer
			sprintf(ioptr_d,"%c %.3f",
			    BASE,
				getWeighingInterface()->getTareUnitBal());	  //"B <consigne>"
			transaction();
			break;
		case RAZ_TAR:                  //effacement de la valeur de tare
			sprintf(ioptr_d,"%c 0",BASE);   //"B 0"
			transaction();
			break;
		case DETAR:                    //le poids sur le plateau est considéré
			                           // comme le poids de tare si==0 msg double
			sprintf(ioptr_d,"%c",TARE);    //"T"
			transaction();
			break;
		case CHG_U:                    //changement d'unite de mesure
			strncpy(unit,"   ",3);
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
		case CHG_P:                    //changement de plateau

			/*   sprintf(ioptr_d,"%c %d",
				CHANGE,i);*/               //"S <nø plateau>"

//			sprintf(ioptr_d,"%c%c%s %d",
//				APPLICATION,WRITE,"010",
//				getWeighingInterface()->getScaleNumber());//"AW010 <info>"
//			transaction();
			ostatus = UNKNOWN2;
			rep = ope;
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
		case ART_I:                    //acquisition d'un article immediat
									   //utilisé pour demande de poids, non prévu
									   // pour cette balance : retour valeur donnée
//			getWeighingInterface()->setResWeightUnit(getWeighingInterface()->getWeightUnit());
//			sprintf(ioptr_d,"%c%c%c",
//				NET,ARTICLE,IMMEDIAT);     //"SXI"
//			transaction();
			ostatus = OK;
			rep = ope;
			break;
		case ART_S:                    //acquisition d'un article stable (net,brut,tare)
//			sprintf(ioptr_d,"%c%c",
//				NET,ARTICLE);              //"SX"
//			transaction();
//			break;
		case APL_R:                    //lecture d'un bloc d'application
//			strncpy(ioptr_u,ptl,3);        // bizarre semble à l'envers        
//			sprintf(ioptr_d,"%c%c%s",
//				APPLICATION,LECTURE,ptl);  //"AR<nø bloc>"
//			transaction();
//			break;
		case APL_W:                    //écriture d'un bloc d'application
//			strncpy(ioptr_u,ptl,
//				DOWN_BUF_SIZ);             //la taille demandee est exageree 
//										   // ceci pour copier toute la zone data
//			sprintf(ioptr_d,"%c%c%s",
//				APPLICATION,WRITE,ptl);    //"AW<nø bloc> <info>"
//			transaction();
//			break;
		case APL_C:                    //effacement du contenu d'un bloc d'application
//			strncpy(ioptr_u,ptl,3);        //un nø de bloc est sur 3 digits
//			sprintf(ioptr_d,"%c%c%s ",
//				APPLICATION,WRITE,ptl);    //"AW <nø bloc> "
//			transaction();
			ostatus = UNKNOWN2;
			rep = ope;
			break;
		case DSPL:                     //affichage d'un message
			sprintf(ioptr_d,"%c %s",
				DISPLAY,
				getWeighingInterface()->getWeighingShortMessage());   //"D <texte>"
			transaction();
//			delay(2000);                   //pause pour laisser le temps de lire le
//										   // message
//			sprintf(ioptr_d,"%c",
//				DISPLAY);                  //annule le message courant.
//										   // Cela évite un blocage caractérisé par l'* 
//										   // affiché sur la METTLER
//			emissionMsg();
			break;
		case RAZ_DSPL:                 //"D "
			sprintf(ioptr_d,"%c ",DISPLAY);
			transaction();
			break;
		case BIP:                      //message sonore
//			sprintf(ioptr_d,"%c%c",
//				DISPLAY,SOUND);            //"DS"
//			transaction();
//			break;
		case PRT:                      //envoi d'information à imprimer
			ostatus = UNKNOWN2;
			rep = ope;
			break;
		case WAIT_MSG:                 //lecture du message le + vieux
			i = getWeighingInterface()->getMsgWaitingTime();
			j=1;
			do
				receptionMsg();           //pour filtrage des operations manuelles
		                                   // et les messages doubles

			while ((istatus != OK) && (++j <= i));

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
}
/*************************************************
* appel du multi com                             *
*************************************************/
void AdxMepm::callMultiCom(int pornum, ComOperation comOp, char* iodata)
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
void AdxMepm::emissionMsg(void)
{
	char trailer[3] = {"\r\n"};
	strcat(ioptr_d,trailer);
	callMultiCom(pornum,SEND,ioptr_d);
}

/*************************************************
*  réception d'un message selon protocole        *
*************************************************/
void AdxMepm::receptionMsg(void)
{
	// gbe 11/08
	// On redispatch les évennements de l'interface pour éviter les freeze
	if (getWeighingInterface()->getInterface()->getDisplay()->hasEvents())
	{
		getWeighingInterface()->getInterface()->getDisplay()->readAndDispatchEvents();
	}
	callMultiCom(pornum,READ,inmsg);
}

/*************************************************
* transaction d'émission-réception               *
*************************************************/
void AdxMepm::transaction(void)
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
void AdxMepm::decodeResponse(void)
{
	ostatus = OK;                      //le statut est d'office mis a OK
	rep = ope;
	char resUnit[4] = "aaa";
	char resWeight[20] = "";
	char resScale[2] = "";
//	int scaleNumber;
	double weight;
	char* pszTmp = NULL;
									   //la reponse est d'office positionnée
	                                   // avec l'operation a efectuer
	switch (*inmsg)
	{
//		case APPLICATION:
//			if (ope == APL_R)          //acquittement d'une lecture dans 
				                       // un bloc d'application
//			strcpy(ioptr_u,inmsg+3);
//			break;
//		case UNIT_POIDS:               //changement d'unite de poids
//			rep = CHG_U;
//			if (*(inmsg+1) == OP_ACTION || *(inmsg+1) != PC_ACTION)
//				strcpy(ioptr_u,inmsg+2);
//			{
//				strncpy(resUnit,inmsg+2,3);
//				getWeighingInterface()->setResWeightUnit(resUnit);
//			}
//			else
//				ostatus = UNKNOWN_ANSWER;
//			break;
//		case DISPLAY:
//		case KBD:
//			if (*(inmsg+1) != AUTO)    //acquittement a un ordre blocage/deblocage
//				                       // clavier ou demande d'affichage
//				ostatus = UNKNOWN_ANSWER;
//			break;
//		case NET | CHANGE:
		case NET:
			switch(*(inmsg+1))
			{
//				case PLATEAU:          //changement de plateau operateur
//				case PC_ACTION:        //changement de plateau depuis PC
//					rep = CHG_P;
//					strncpy(resScale,inmsg+4,1);
//					scaleNumber = atoi(resScale);
//					getWeighingInterface()->setScaleNumber(scaleNumber);
//					*ioptr_u = *(inmsg+4); //contient le nø de plateau
//					*(ioptr_u+1) = 0;
//					break;
//				case ART_M:            //operateur a envoye l'article une fois stable
//					rep = ART_S;
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
//					break;
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
					ostatus = DYNAMIQUE;
					strncpy(resWeight,
						inmsg+2,10);          //inmsg+2 on saute l'espace
					weight = atof(resWeight);
					getWeighingInterface()->setResWeight(weight);
//					strncpy(resUnit,inmsg+14,3);
//					getWeighingInterface()->setResWeightUnit(resUnit);
					break;
//				case ARTICLE:          //article complet
//					switch(*(inmsg+2))
//					{
//						case DYNAMIC:
//							ostatus = DYNAMIQUE;
//						default:
//							strncpy(resWeight,
//								inmsg+9,10);         
//							weight = atof(resWeight);
//							getWeighingInterface()->setResGrossWeight(weight);
//							strncpy(resUnit,inmsg+14,3);
//							getWeighingInterface()->setResWeightUnit(resUnit);
//							strncpy(resWeight,
//								inmsg+30,10);          
//							weight = atof(resWeight);
//							getWeighingInterface()->setResWeight(weight);
//							strncpy(resWeight,
//								inmsg+51,10);          
//							weight = atof(resWeight);
//							getWeighingInterface()->setResTare(weight);
//							break;
//					}
//					break;
				default:               //reception du net affiche
					rep = PDS_S;
					strncpy(resWeight,
						inmsg+3,10);          //inmsg+3 on saute l'espace
					weight = atof(resWeight);
					getWeighingInterface()->setResWeight(weight);
//					strncpy(resUnit,inmsg+14,3);
//					getWeighingInterface()->setResWeightUnit(resUnit);
					break;
			}
			break;
		case TARE:
			rep = TAR;
//			switch (*(inmsg+1))
//			{
//				case SURCHARGE:
//					ostatus = SURCHARGE_ERROR;
//					break;
//				case SOUSCHARGE:
//					ostatus = SOUSCHARGE_ERROR;
//					break;
//				case AUTO:
//				case MANUEL:
//					switch(*(inmsg+2))
//					{
//						case 'H':              //acquittement d'un envoi d'une
//											   // consigne de tare
//							strncpy(resWeight,
//								inmsg+4,10);
//							weight = atof(resWeight);
//							getWeighingInterface()->setResTare(weight);
//							strncpy(resUnit,inmsg+15,3);
//							getWeighingInterface()->setResWeightUnit(resUnit);
//							break;
//						case 0:                //mal explique dans la doc
//							break;
//						default:
//							strncpy(resWeight,
//								inmsg+4,10);
//							weight = atof(resWeight);
//							getWeighingInterface()->setResTare(weight);
//							strncpy(resUnit,inmsg+15,3);
//							getWeighingInterface()->setResWeightUnit(resUnit);
//							break;
//					}
//					break;
//			}
			break;
//		case REMISEAZERO:
//			rep = RAZ;
//			switch (*(inmsg+1))
//			{
//				case SURCHARGE:
//					ostatus = SURCHARGE_ERROR;
//					break;
//				case SOUSCHARGE:
//					ostatus = SOUSCHARGE_ERROR;
//					break;
//				case AUTO:
//				case MANUEL:
//				default:
//					break;
//			}
//			break;
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
//		case KEY_PAC:                  //une information en provenance du PAC
//			                           // est validee par l'operateur
//			switch(*(inmsg+1))
//			{
//				case KEYP_A:
//					rep = ID_A;
//					strcpy(ioptr_u,inmsg+3);
//					break;
//				case KEYP_B:
//					rep = ID_B;
//					strcpy(ioptr_u,inmsg+3);
//					break;
//				case KEYP_C:
//					rep = ID_C;
//					strcpy(ioptr_u,inmsg+3);
//					break;
//				case KEYP_D:
//					rep = ID_D;
//					strcpy(ioptr_u,inmsg+3);
//					break;
//				default:
//					break;
//			}
//			break;
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
void AdxMepm::transcodeUnite(char* unit)
{
/*	if (strcmp(unit,"LB ") == 0) unit = "lb ";
	if (strcmp(unit,"Lb ") == 0) unit = "lb ";
	if (strcmp(unit,"OZ ") == 0) unit = "oz ";
	if (strcmp(unit,"Oz ") == 0) unit = "oz ";
	if (strcmp(unit,"OZT") == 0) unit = "ozt";
	if (strcmp(unit,"Ozt") == 0) unit = "ozt";
	if (strcmp(unit,"DWT") == 0) unit = "dwt";
	if (strcmp(unit,"Dwt") == 0) unit = "dwt";
	if (strcmp(unit,"CT ") == 0) unit = "ct ";
	if (strcmp(unit,"Ct ") == 0) unit = "ct ";
	if (strcmp(unit,"TL ") == 0) unit = "tl ";
	if (strcmp(unit,"Tl ") == 0) unit = "tl ";
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
bool AdxMepm::controleUnite(char* unit)
{
	if (strcmp(unit,"g  ") == 0
		|| strcmp(unit,"lb ") == 0
		|| strcmp(unit,"oz ") == 0
		|| strcmp(unit,"ozt") == 0
		|| strcmp(unit,"dwt") == 0
		|| strcmp(unit,"ct ") == 0
		|| strcmp(unit,"tl ") == 0)
		return true;
	else
		return false;
}

/*************************************************
* Temporisation en milli secondes                *
*************************************************/
void AdxMepm::delay(int milliSec)
{
	clock_t start, end;
	start = clock();
	do
	{
		end = clock();
	}
	while ((end- start) < milliSec);
}




