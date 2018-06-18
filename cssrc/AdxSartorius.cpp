// AdxSartorius.cpp
// ------------
// project : Adonix	X3 Scales
// author :	MC
// V130	: MC 2001.05.28
//--------------------------------------------------------------
//

/******************************************************
*													  *
*	 PILOTE	DE PERIPHERIQUE	SARTORIUS				  *
*													  *
*******************************************************
*													  *
*  REALISATION CONCEPTUELLE	: MC					  *
*			   MATERIELLE	: SARTORIUS				  *
*			   LOGICIELLE	: MC					  *
*													  *
*-----------------------------------------------------*
*													  *
*  LANGAGE	   C++		  compilation MSV6			  *
*													  *
*-----------------------------------------------------*
*													  *
*  OBJECTIF	   Le driver assurera l'�mission et	la	  *
*			   r�ception de	caract�res sur un des 8	  *
*			   ports suivant le	protocole SBI. 		  *
*			   Il pilotera une balance avec	le jeu	  *
*			   d'instruction disponible.Il filtrera	  *
*			   les manipulations clavier de			  *	
*			   l'op�rateur							  *
*													  *
*-----------------------------------------------------*
*													  *
*  CONTRAINTES Les flux	� g�rer	sont faibles et	quasi *
*			   exclusifs.							  *
*													  *
*******************************************************/

/***************************************************************************
*																		   *
* Fonctionnement du	pilote			 :									   *
*	Le pilote connait le jeu d'instruction de la balance.				   *
*	Il fonctionne en mode transactionnel question r�ponse.				   *
*	Sur	une	requete	standard venant	d'amont,le pilote g�n�re le	message	au *
*	format de la balance et	appelle	le driver MULTICOM.	La balance r�pond �*
*	la question. Cette r�ponse est lue par le pilote qui transforme	cette  *
*	r�ponse	en une requete + statut	+ data standard	pour l'appelant.	   *
*																		   *
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
#include "AdxSartorius.h"
#include "AdxBalance.h"

#include <fstream>							// 06.04 TRACE

using std::endl;							// 06.04 TRACE


static char	ptl[DOWN_BUF_SIZ];
static char	inmsg[MAXC+1];			   //contient le message traite	recu de	l'aval
static unsigned	char Icar;			   //contient le caractere courant traite
static char	ioptr_d[DOWN_BUF_SIZ];	   //contient le message � envoyer
static DriverStatus	istatus;		   //statut	acquis en entree(par l'aval)
static DriverStatus	ostatus;		   //statut	renseigne en sortie(pour l'amont)
static WeighingOperation ope;		   //operation a traiter
static WeighingOperation rep;		   //reponse sur l'operation lue que l'on retourne
									   //	a l'appelant
static int pornum;					   //indice	du port	courant	a traiter
static 	char prevUnit[4]="";		// dernier bon


/*************************************************
*	 traitement	de l'ordre de pes�e				 *
*************************************************/
void AdxSartorius::weighingTreatment(AdxWeighingInterface* wi,
										WeighingOperation& opi,
										int& numPort,
										WeighingOperation& opo,
										DriverStatus& sto,
										bool bCheckPlate)
{
		setWeighingInterface(wi);
		ope	= opi;
		pornum = numPort;
		rep	= opo;
		ostatus	= sto;

        WeighingOrder order;
		int	i;
		long j;
		char Chaine[64]="";				   //Chaine	pour manipulations diverses
		char* unit = new char[4];
		char* runit = new char[4];
		char Orgmess[30]="";			   //Message original
		char Opmess[9]="";				   //Message operateur

		char	ChBufferSave[MAXC+1];
		DriverStatus	istatusSav;
		bool bBuffSaved = false;

        //double nTar;					   12.07 Pas d'affichage sur Sartorius
		strset(ptl,0);
		strset(ioptr_d,0);
		memset(ChBufferSave,0,MAXC+1);
		//if(ope != WAIT_MSG)
		//{
		//	// on vide le buffer au cas o� quelqu'un aurait appuyer sur un bouton sans qu'on s'y attende
		//	receptionMsgLight();
		//	if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
		//	{
		//		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Clear Buffer" << endl;
  //  			getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< inmsg  <<" -> ignored"<< endl;
		//	}
		//}
	// Avant toute chose on teste le plateau si on est sur une balance 
	// multi-plateaux et que bCheckPlate = true
	if(bCheckPlate && getWeighingInterface()->getBalance()->IsMultiPlate())
	{
		// Contr�le de l'index du plateau
		short plateIndex = getWeighingInterface()->getBalance()->getPlateIndex();
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
			bBuffSaved = true; // on indique qu'on a enregistr� le buffer
		}
		istatusSav = istatus;
		// on vide le buffer
		memset(inmsg,0,MAXC+1);

		sprintf(ioptr_d,"%c%s",ESC,"i_");
		// Envoie de lordre
		emissionMsg();
		delay(200);

		if (istatus == OK)
		{
			//getWeighingInterface()->editionMessage(); inutile lors du check plate
			receptionMsg();
		}

		if (istatus == OK)
		{
			// la r�ponse va �tre par exemple : "CA1/016302/1"
			// CA1 le type d'indicateur
			// 016302 la version du logiciel
			// 1 le plateau s�lectionn�
			if(strlen(inmsg) != 0)
			{
				// extraction du num�ro de plateau
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
				// R�ponse inconnue
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
	// Le contr�le du plateau dans le cas d'un multi-plateau s'est bien pass�
	// on continue
		
		switch (ope)
		{
				case E_KBD:					   //blocage clavier
						sprintf(ioptr_d,"%c%c",ESC,'O');
                   		emissionMsg();
						break;
				case D_KBD:					   //deblocage
						sprintf(ioptr_d,"%c%c",ESC,'R');
                   		emissionMsg();
						break;
				case RAZ:					   //remise	a zero de la balance
						sprintf(ioptr_d,"%c%s",ESC,"kZE_");			   //"ESCkZE_"
                		emissionMsg();
                        delay(500);
						sprintf(ioptr_d,"%c%c",ESC,'P');		// on imprime
						transaction();
						break;
				case CHG_U:					   //changement	d'unite	de mesure
                		strset(unit,0);
						strcpy(unit,getWeighingInterface()->getWeightUnit());
						if (controleUnite(unit))
						{
							if (strcmp(unit,"G") == 0)
							{
    	    					sprintf(ioptr_d,"%c%s",ESC,"kZE_");		   //"ESCkZE_"
                        		emissionMsg();
                                delay(500);
                                sprintf(ioptr_d,"%c%c",ESC,'P');	    	// on imprime
                        		emissionMsg();                          
                                delay(500);
								receptionMsg();
                                strncpy(runit,inmsg+17,3);
    							if (strcmp(runit,"kg ") == 0)
                                {
    	    					    sprintf(ioptr_d,"%c%s",ESC,"kEN_");		   //"ESCkEN_"
                               		emissionMsg();
                                }
                           }	
							if (strcmp(unit,"KG") == 0)
							{
   	    					sprintf(ioptr_d,"%c%s",ESC,"kZE_");		   //"ESCkZE_"
                        		emissionMsg();
                                delay(500);
                                sprintf(ioptr_d,"%c%c",ESC,'P');	    	// on imprime
                        		emissionMsg();                          
                                delay(500);
								receptionMsg();
                                strncpy(runit,inmsg+17,3);
    							if (strcmp(runit,"g  ") == 0)
                                {
    	    					    sprintf(ioptr_d,"%c%s",ESC,"kEN_");		   //"ESCkEN_"
                               		emissionMsg();
                                }
							}	
						}
						else
							ostatus	= UNIT_ERROR;
						break;
				case TAR:					   //consigne de tare a	envoyer
                                               // si elle est zero, faire RAZ
					    if (getWeighingInterface()->getTare() == 0)
                        {
					    	sprintf(ioptr_d,"%c%s",ESC,"kZE_");			   //"ESCkZE_"
                	    	emissionMsg();
                        }
                        else
                        { /* 12.07 Pas d'affichage sur Sartorius
                            // sr pour consigne de tare 11.04
                            nTar = getWeighingInterface()->getTare();
			                strncpy(unit,"   ",3);
                   			strncpy(runit,"   ",3);
                            strcpy(unit,getWeighingInterface()->getWeightUnit());
                            strcpy(runit,getWeighingInterface()->getResWeightUnit());
                            if(strcmp(unit,runit)!=0)
                            {
                                nTar = getWeighingInterface()->getInterface()->getDonnees()->
                                convertir(nTar,unit,runit);
                            }
                           sprintf(ioptr_d,"%c%c %.3f%c",
								ESC,'t',
								nTar,
								'_');									//"ESCt <consigne>	_"                            sprintf(ioptr_d,"%c%c %.3f%c",
						    emissionMsg();
                            delay(300);
						    sprintf(ioptr_d,"%c%s",ESC,"kPT_");				//"ESCkPT_"
						    emissionMsg();
                        */ }
                        delay(1000);
						sprintf(ioptr_d,"%c%c",ESC,'P');		// on imprime
					    emissionMsg();
                        getWeighingInterface()->editionMessage();
                        delay(300);                       
                        receptionMsg();
                		strset(prevUnit,0);
                        strncpy(prevUnit,inmsg+17,3);
                        inmsg[0] = 'T';
                        decodeResponse();
                        // fin sr 11.04
						break;
				case RAZ_TAR:				   //effacement	de la valeur de	tare
				case DETAR:	    			   //effacement	de la valeur de	tare
						sprintf(ioptr_d,"%c%s",ESC,"t0.0_");
						emissionMsg();
                        delay(500);
						sprintf(ioptr_d,"%c%s",ESC,"kPT_");				//"ESCkPT_"
						emissionMsg();
                        delay(500);
						sprintf(ioptr_d,"%c%c",ESC,'P');		// on imprime
						transaction();
						break;
				case BIP:					   //message sonore
						sprintf(ioptr_d,"%c%c",ESC,'Q');			   //"ESCQ"
						emissionMsg();
						break;
				case DSPL:					   //affichage d'un	message

						// 12.07 Pas d'affichage sur Sartorius
						break;
                        strcpy(Orgmess,getWeighingInterface()->getWeighingMessage());
                   		strset(Opmess,0);
                        strncpy(Opmess,Orgmess,8);
 						sprintf(ioptr_d,"%c%c%s%c",
								ESC,'t', Opmess,'_');
						emissionMsg();
                        if (Orgmess[8] != 0)
                        {
                            strncpy(Opmess,Orgmess+8,8);
						    sprintf(ioptr_d,"%c%c%s%c",
								ESC,'t', Opmess,'_');
						    emissionMsg();
                        }                 
                        getWeighingInterface()->editionMessage();
                        delay(2000);         // temps d'affichage du message
						sprintf(ioptr_d,"%c%s",ESC,"kCF_");	 //on efface le message
						emissionMsg();
						break;
				case RAZ_DSPL:					   //effacement du message
						sprintf(ioptr_d,"%c%s",ESC,"kCF_");				//"ESCkCF_"
						emissionMsg();
						break;
				case PDS_S:					   //acquisition d'un poids	stable
						sprintf(ioptr_d,"%c%c",ESC,'P');	   // print
						emissionMsg();
                        getWeighingInterface()->editionMessage();
                        receptionMsg();
                        inmsg[0]='S';
                        decodeResponse();
						break;
				case PDS_I:					   //acquisition d'un poids	immediat
                        order = getWeighingInterface()->getWeighingOrder();
						sprintf(ioptr_d,"%c%c",ESC,'P');	   // print
						emissionMsg();
                        getWeighingInterface()->editionMessage(); 
						delay(200);
                        receptionMsg();
						if(inmsg[0] != 'N' && inmsg[0] != '\0' && inmsg[0] != 'C' && inmsg[0] != 'S')
						{
	if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
    {
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Bad data !!!" << endl;
    	getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< inmsg  << endl;
    }
							break;
						}
						if (strncmp(inmsg,"Stat       OFF",14)==0)
						{
							memset(inmsg,0,MAXC+1);
						}
						if (order == POIDS_IMDT)
						  inmsg[0]='C';      // test connection
						else
						  inmsg[0]='I';
                        decodeResponse();
						break;
				case WAIT_MSG:				   //lecture du	message	le + vieux
						i =	getWeighingInterface()->getMsgWaitingTime();
						j=1;
						do
						{
							// gbe : si on a sauvegard� une trame il ne faut pas l'�craser lors de la premi�re boucle
							// on remet ensuite le bool � false pour repartir
							if (bBuffSaved == false)
							{
								receptionMsg();			 //pour filtrage des operations manuelles
												  		 // et les messages doubles
						}
							else
							{
								bBuffSaved = false;
							}
						}
						while ((istatus	!= OK) && (++j <= i));
  						if (istatus	== OK)
                        {
                        order = getWeighingInterface()->getWeighingOrder();
                         switch (order)
                            {
                             case RAZ_M:
                             case RAZ_A:
                                //receptionMsg();
                                delay(300);
							   // 12/08/08 Sartorius modifi�
	if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
    {
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Send WAIT RAZ " << endl;
    }
							   if(_typeSartorius == 3)
							   {
  	    							sprintf(ioptr_d,"%c%s",ESC,"kZE_");		   //bouton >0<
 					    			emissionMsg();
							   }
                                rep = RAZ;
                                break;
                             case DETAR:
                             case TAR_M:
                             case TAR_A:
 	if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
    {
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Send WAIT TAR " << endl;
    }
                              if (*(inmsg+17) == ' ' && _typeSartorius == 3)
                               {
                                   do
                                   {
 					            	sprintf(ioptr_d,"%c%c",ESC,'P');	   // print
					            	emissionMsg();
                                    delay(200);
                                   receptionMsg();
                                   }
                                   while (*(inmsg+17) == ' ');
                               }
                               delay(300);
							   // 12/08/08 Sartorius modifi�
							   if(_typeSartorius == 3)
							   {
									sprintf(ioptr_d,"%c%s",ESC,"kT_");		   //bouton >T1<
 					    			emissionMsg();
							   }
                               inmsg[0]='T';
                               decodeResponse();
                               break;
                            }
                        }
                        else
						{
								ostatus	= istatus;
								rep	= ope;
						}
						break;
				case SERIAL_NUM: // demande du num�ro de s�rie
						sprintf(ioptr_d,"%c%s",ESC,"x9_");				//"x9_"
						emissionMsg();
						delay(200);
						receptionMsg();
                        decodeResponse();
						break;

				case CHG_P:						//changement de plateau
				{
					// Le cas Sartorius est un peu particulier, on doit utiliser la commande i_
					// pour r�cup�rer le plateau s�lectionner et envoyer ensuite la commande kNW_
					// pour passer au plateau suivant
					IlvUShort plateIndex = getWeighingInterface()->getBalance()->getPlateIndex();
					// on interroge le concentrateur pour connaitre le plateau s�lectionn�
					// la r�ponse va �tre par exemple : "CA1/016302/1"
					// CA1 le type d'indicateur
					// 016302 la version du logiciel
					// 1 le plateau s�lectionn�
					sprintf(ioptr_d,"%c%s",ESC,"i_");
					// Envoie de lordre
					emissionMsg();
					delay(200);
					// r�ception de la r�ponse
					receptionMsg();
					if (istatus	!= OK)
					{
						ostatus	= UNAVAILABLE;
						rep	= ope;
						break;
					}
					// r�cup�ration du num�ro de plateau
					char cIndex = inmsg[strlen(inmsg)-1];
					short nIndex = cIndex - (short)'0';
					if( nIndex < 1 || nIndex > 9)
					{
						ostatus	= SYNTAX_ERROR;
						rep	= ope;
						break;
					}
					if (plateIndex == nIndex)
					{
						// si on est d�j� sur le bon plateau rien � faire
						ostatus	= OK;
						rep	= ope;
						break;
					}
					// on va envoyer la commande de chengement de plateau jusqu'au bon
					IlvUShort wnProtection = 0; // Protection contre une boucle infinie
					do
					{
						wnProtection++;
	if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
    {
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Send to scaleSAR : "<< getWeighingInterface()->getBalance()->getBalance() << endl;
    	getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t CHG_P wnProtection="<< wnProtection  << endl;
    }
						if (wnProtection >= 10)
						{
							// on a pas pu trouver le bon plateau erreur on sort
							ostatus	= UNAVAILABLE;
							rep	= ope;
							break;
						}
						// envoie de l'ordre de changement de plateau
						sprintf(ioptr_d,"%c%s",ESC,"kNW_");
						emissionMsg();
						delay(200);
						//// r�ception de la r�ponse
						//receptionMsg();
						//if (istatus	!= OK)
						//{
						//	ostatus	= UNAVAILABLE;
						//	rep	= ope;
						//	break;
						//}
						// interrogation de l'afficheur
						sprintf(ioptr_d,"%c%s",ESC,"i_");
						// Envoie de l'ordre
						emissionMsg();
						delay(200);
						// r�ception de la r�ponse
						receptionMsg();
						if (istatus	!= OK)
						{
							ostatus	= UNAVAILABLE;
							rep	= ope;
							break;
						}
						// r�cup�ration du num�ro de plateau
						char cIndex = inmsg[strlen(inmsg)-1];
						short nIndex = cIndex - (short)'0';
						if( nIndex < 1 || nIndex > 9)
						{
							ostatus	= SYNTAX_ERROR;
							rep	= ope;
							break;
						}
						if (plateIndex == nIndex)
						{
							// si on est d�j� sur le bon plateau rien � faire
							ostatus	= OK;
							rep	= ope;
							break;
						}
					}while(nIndex != plateIndex && wnProtection < 10);
				}
		break;
				default:
						ostatus	= UNKNOWN2;
						rep	= ope;
						break;
		}

		delete [] unit;
		opo	= rep;
		sto	= ostatus;
	// gbe 10/05/12 d�placement en fin de fonction pour �viter d'int�rompre un ordre en cours
	// On redispatch les �vennements de l'interface pour �viter les freeze
	if (getWeighingInterface()->getInterface()->getDisplay()->hasEvents())
	{
		getWeighingInterface()->getInterface()->getDisplay()->readAndDispatchEvents();
	}
}
		

/*************************************************
* appel	du multi com							 *
*************************************************/
void AdxSartorius::callMultiCom(int	pornum,	ComOperation comOp,	char* iodata)
{
		DriverStatus sta;
		int	nbcMax = 256;

		getWeighingInterface()->getMultiCom()->comOperationTreatment(pornum,
																	 comOp,
																	 iodata,
																	 sta,
																	 nbcMax);

		istatus	= sta;
}


/*************************************************
*	 �mission de la	trame selon	protocole		 *
*************************************************/
void AdxSartorius::emissionMsg(void)
{
		char trailer[3]	= {"\r\n"};
		strcat(ioptr_d,trailer);
	// 06.04 TRACE
	if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
    {
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Send to scaleSAR : "<< getWeighingInterface()->getBalance()->getBalance() << endl;
    	getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< ioptr_d  << endl;
    }

        callMultiCom(pornum,SEND,ioptr_d);
}

/*************************************************
*  r�ception d'un message selon	protocole		 *
*************************************************/
void AdxSartorius::receptionMsg(void)
{
//	for (int i =0; i<MAXC; i++)
//	{
////		inmsg[i] = ' ';
//		inmsg[i] = '\0';
//	}
	// On utilise memset 
	memset(inmsg,0,MAXC+1);

	callMultiCom(pornum,READ,inmsg);
	if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
    {
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "Recieve from scaleSAR : "<< getWeighingInterface()->getBalance()->getBalance() << endl;
    	getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< inmsg  << endl;
    }
}
void AdxSartorius::receptionMsgLight(void)
{
	// On utilise memset 
	memset(inmsg,0,MAXC+1);
	// on ne lit que le port 
	callMultiCom(pornum,READ,inmsg);
}

/*************************************************
* transaction d'�mission-r�ception				 *
*************************************************/
void AdxSartorius::transaction(void)
{
		emissionMsg();

		if (istatus	== OK)
		{
				getWeighingInterface()->editionMessage();
				receptionMsg();
		}

		if (istatus	== OK)
				decodeResponse();
		else
				ostatus	= istatus;
}
/*************************************************
* decodage de la reponse:						 *
* -mise	en forme de	la partie applicative,		 *
* -mise	a jour de l'operation,					 *
* -mise	a jour du statut de	retour				 *
*************************************************/
void AdxSartorius::decodeResponse(void)
{
	ostatus	= OK;					//le statut	est	d'office mis a OK
	rep	= ope;						//la reponse est d'office positionn�e
	char resUnit[4]	= "";			// avec	l'operation	a efectuer
	char resWeight[10] = "";
	char resScale[2] = "";
//	int	scaleNumber;
	double weight;
	char* pszTmp = NULL;
	char balUnit[4]	= "";
	
	char scaleID[7]	= "";
																					 
   	// 06.04 TRACE
    if (getWeighingInterface()->getInterface()->getTraceMode() == 1)
    {
		getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< "decodeResponse" << endl;
    	getWeighingInterface()->getInterface()->_traceFile << "\t\t\t\t"<< inmsg  << endl;
    }
	if (ope == SERIAL_NUM)
	{
		AdxWeighingInterface* wi = NULL;
		AdxBalance* balance = NULL;
		wi = getWeighingInterface();
		balance=wi->getBalance(); // R�cup�ration de la balance courante
		// on est dans le cas du num�ro de s�rie, la balance ne r�pond
		// pas autre chose. C'est ici que le test entre le num�ro retourn�
		// et le num�ro stock� dans la classe balance doit �tre effectu�
		if (wi->getInterface()->getTraceMode() == 1)
		{
			// trace du num�ro de s�rie
			wi->getInterface()->_traceFile << "\t\t\t\t"<< "decodeResponse" << endl;
    		wi->getInterface()->_traceFile << "\t\t\t\t"<< "SCALE SERIAL NUMBER=" <<inmsg  << endl;
		}
			wi->afChRTrim(inmsg);
			wi->afChLTrim(inmsg);

		if (balance->getSerialNumber()!=NULL && balance->getSerialNumber()[0] !='\0' && strcmp(balance->getSerialNumber(),inmsg) != 0)
		{
			// la balance connect� NE CORRESPOND PAS � la blance attendu
			if (wi->getInterface()->getTraceMode() == 1)
			{
				// trace du num�ro de s�rie
				wi->getInterface()->_traceFile << "\t\t\t\t"<< "ERROR" << endl;
				wi->getInterface()->_traceFile << "\t\t\t\t"<< "SCALE SERIAL NUMBER EXPECTED="<< balance->getSerialNumber() << endl;
    			wi->getInterface()->_traceFile << "\t\t\t\t"<< "SCALE SERIAL NUMBER RETURNED=" <<inmsg  << endl;
			}
			ostatus = NO_RESPONSE;
			return;
		}
	}
										   
	strncpy(scaleID,inmsg,6); 
	if (strcmp(scaleID,"Stat  ") == 0)
	{
		if (*(inmsg+9) != 'E')
		{
			switch(*(inmsg+12))
			{
				case 'H':
					ostatus	= SURCHARGE_ERROR;
					break;
				case 'L':
					ostatus	= SOUSCHARGE_ERROR;
					break;
				case 'C':	
					ostatus	= LOGISTIC_ERROR;
					break;
				default:
					break;	
			}
		}
		else
		{
			ostatus	= LOGISTIC_ERROR;
		}
	}
	else
	{
	    switch (*inmsg)
        {
        case 'C':                      // test connection
 			if (strlen(inmsg) < 14)
				ostatus = NO_RESPONSE;
            else
				ostatus = OK;
            break;
        case 'I':                       // poids immediat
  			if (strlen(inmsg) < 14)
			{
				ostatus = NO_RESPONSE;
				break;
			}
            strncpy(resUnit,inmsg+17,3);
  			if (strcmp(resUnit,"   ") == 0)
            {
                ostatus	= DYNAMIQUE;					// pas encore stable
                strcpy(resUnit,prevUnit);
            }
            else
            {
                strcpy(prevUnit,resUnit);
                ostatus	= OK;
               rep=PDS_S;
           }
 			strncpy(resWeight,inmsg+8,8);		  
			weight = atof(resWeight);  
            if (*(inmsg+6) == '-')
               weight *= -1 ;
			getWeighingInterface()->setResWeight(weight);
            transcodeUnite(resUnit);
            getWeighingInterface()->setResWeightUnit(resUnit);
            break;
        case 'S':
            strncpy(resUnit,inmsg+17,3);
			if (strcmp(resUnit,"   ") == 0)
            {	ostatus	= UNAVAILABLE;					// pas encore stable
                break;
            }
			strncpy(resWeight,inmsg+8,8);		  
			weight = atof(resWeight);  
            if (*(inmsg+6) == '-')
              weight *= -1 ;
			getWeighingInterface()->setResWeight(weight);
            transcodeUnite(resUnit);
            getWeighingInterface()->setResWeightUnit(resUnit);
			break;
        case 'T':
            rep=TAR;

            strncpy(resWeight,inmsg+8,8);		  
			weight = atof(resWeight);
/*            if (*(inmsg+6) == '-')
             weight *= -1 ;
*/
			getWeighingInterface()->setResTare(weight);

            strncpy(resUnit,inmsg+17,3);
            transcodeUnite(resUnit);
            getWeighingInterface()->setResWeightUnit(resUnit);
             break;
        default:
            break;
    	}
    }
 }
 		 

/*************************************************
* Transcodage unit�								 *
*************************************************/
void AdxSartorius::transcodeUnite(char*	unit)
{
/*		if (strcmp(unit,"g")   == 0) strcpy(unit,"G");
		if (strcmp(unit,"g ")  == 0) strcpy(unit,"G");
		if (strcmp(unit,"g  ") == 0) strcpy(unit,"G");
		if (strcmp(unit,"kg ") == 0) strcpy(unit,"KG");
		if (strcmp(unit,"kg")  == 0) strcpy(unit,"KG");
		if (strcmp(unit,"lb	") == 0) strcpy(unit,"LB");
		if (strcmp(unit,"oz	") == 0) strcpy(unit,"OZ");
		if (strcmp(unit,"ozt") == 0) strcpy(unit,"OZT");
		if (strcmp(unit,"dwt") == 0) strcpy(unit,"DWT");
*/

	// 61152 mm 01.10
	// Mise en majuscules + suppression des espaces
	getWeighingInterface()->afChUpper(unit);
	getWeighingInterface()->afChRTrim(unit);
	getWeighingInterface()->afChLTrim(unit);
}

/*************************************************
* Contr�le unit�								 *
*************************************************/
bool AdxSartorius::controleUnite(char* unit)
{
		if (strcmp(unit,"KG") == 0
				|| strcmp(unit,"G")	 == 0
				|| strcmp(unit,"LB") ==	0
				|| strcmp(unit,"OZ") ==	0
				|| strcmp(unit,"OZT") == 0
				|| strcmp(unit,"DWT") == 0)
				return true;
		else
				return false;
}

/*************************************************
* Temporisation	en milli secondes				 *
*************************************************/
void AdxSartorius::delay(int milliSec)
{
		clock_t	start, end;
		start =	clock();
		do
		{
				end	= clock();
		}
		while ((end- start)	< milliSec);
}


				
