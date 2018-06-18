// X3Centr1.cpp
// ------------
// project : Adonix X3 Centrale de Pesee
// author : EP		28/05/01
//--------------------------------------------------------------
//
// Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include <ilviews/gadgets/gadcont.h>
#include <stdlib.h>
#include "x3centr1.h"
#include "AdxInterface.h"
#include "AdxAccueil.h"
#include "AdxData.h"
#include <ilviews/ilm.h>
#include "Shlwapi.h"
#include <fstream>							// GBE 20/12/12 TRACE

#include <string>							//X3-67237: Used to get the version number of the DLL

using std::endl;							// GBE 20/12/12 TRACE

/*
// à activer pour 4.00
static char *ilm_license_views=\
//"LICENSE adonix-gaillard-demo module ordonnancement\n\
//RUNTIME Views 4.000 NEVER U8PA31D6M1WX 1 pcwinnt pcwin95 ";
"LICENSE adonix-gaillard-demo module ordonnancement\n\
RUNTIME Views 4.000 NEVER  5B7JY0G60135 Y pcwinnt pcwin95 , license: 224700 ";
//static int ilm_license_signature_views=4069483;
static int ilm_license_signature_views=3755763;
//TOKEN Views 4.000 NEVER U8PA31D6M1WX 1 pcwinnt on fc796828 EPARADIS , license: 191700
*/
/*
// à activer pour 4.01
static char *ilm_Views_license=\
"LICENSE adonix-gaillard-application progiciel x3\n\
RUNTIME Views      4.010 NEVER       KP4JS2AJ831N Y pcwinnt , license: 200670 ";
static int ilm_Views_license_signature=65392;
*/

/*
// à activer pour 4.02
static char *ilm_Views_license=\
"LICENSE adonix-gaillard-application progiciel x3\n\
RUNTIME Views      4.020 NEVER       42B472BSSKWU Y pcwinnt , license: 200670 ";
static int ilm_Views_license_signature=1843722;
*/
/*
// à activer pour 4.02
static char *ilm_Views_license=\
"LICENSE adonix-gaillard-application progiciel x3\n\
RUNTIME Views      4.020 NEVER       R1SWE2AWSNBA Y pcwinnt pcwin95 , license: 200670 ";
static int ilm_Views_license_signature=523741;
*/

// à activer pour 5.00
//static char *ilm_Views_license=\
//"LICENSE adonix-gaillard-application progiciel x3\n\
//RUNTIME Views      5.000 NEVER       PB72F2H88MYN Y pcwinnt pcwin95 , license: 200670 ";
//static int ilm_Views_license_signature=6889939;


//static const char* ilm_runtime_license =
//  "LICENSE sage-annecy\n"
//  "RUNTIME Scheduler 6.600 NEVER FP6JM26YSSHN N any , application: Module Ordonnancement  en technologie X3 , license: 13766300-7547\n"
//  "RUNTIME Views 5.300 NEVER 0B20P2P4SD4G N any , application: Modules Ordo et centrale pesee en techX3 , license: 13766300-7549\n"
//  "RUNTIME Solver 6.600 NEVER NNTWX3T6WHKJ N any , application: Module Ordonnancement  en technologie X3 , license: 13766300-7547\n"
//  "RUNTIME Dispatcher 4.600 NEVER CEYEN13PMSU7 N any , application: Module Ordonnancement  en technologie X3 , license: 13766300-7547\n";
//static const int ilm_runtime_license_signature = 2048892;
static const char* ilm_runtime_license =
  "LICENSE - Runtime Replacement Keys 2.2\n"
  "RUNTIME Broker 2.300 NEVER BMRU52ZSSRK5 Y\n"
  "RUNTIME CDE 2.300 NEVER D0WYX2V088DF Y\n"
  "RUNTIME Configurator 2.300 NEVER XZJSN0DS075G Y\n"
  "RUNTIME CP-Optimizer 2.300 NEVER 1CPUS3JYWKZD Y\n"
  "RUNTIME OPLStudio 6.300 NEVER RP6JN17WM2BD Y\n"
  "RUNTIME CPLEX 12.100 NEVER XYUWY1UW4U12 Y any , options: b e m p=MAX q\n"
  "RUNTIME Db-Link 5.300 NEVER U8K830BUG10G Y\n"
  "RUNTIME Dispatcher 4.600 NEVER D5GS61Y04TDS Y\n"
  "RUNTIME InForm 3.000 NEVER EWJ8F2R0SEE0 Y\n"
  "RUNTIME InFormSQL 3.000 NEVER V7HSA32WWH78 Y\n"
  "RUNTIME ODF 2.730 NEVER GPVC12DCSMWA Y\n"
  "RUNTIME OptimizationDecisionManager 3.300 NEVER KF0G31K8MUV8 Y\n"
  "RUNTIME OPLStudio 6.300 NEVER EZMAT33AC14D Y any , options: ide\n"
  "RUNTIME OPLinterpreter 3.000 NEVER H8KSV1KEM8ZS Y\n"
  "RUNTIME P-Solver 6.000 NEVER Z2UWG2CE80HA Y\n"
  "RUNTIME RT-Broker 2.300 NEVER PYK8T11Y488S Y\n"
  "RUNTIME RT-Rules 6.110 NEVER ZHXY806AGGNZ Y\n"
  "RUNTIME RT-Dynamic-Rules 6.110 NEVER EED6J0SUGKMF Y\n"
  "RUNTIME Rules 7.200 NEVER AUUCX19PM6W2 Y\n"
  "RUNTIME Scheduler 6.600 NEVER CKMAJ3WJCHYD Y\n"
  "RUNTIME Schedule 2.210 NEVER PZ20Z0ZJGN40 Y\n"
  "RUNTIME Server 5.300 NEVER ZP1G13HEW2HS Y\n"
  "RUNTIME Solver 6.600 NEVER 7U9M51TPMJHJ Y\n"
  "RUNTIME TGO 1.160 NEVER U2ZE41J043U7 Y\n"
  "RUNTIME Views 5.300 NEVER 4ARAR312WM6D Y\n"
  "RUNTIME ViewsBidi 5.300 NEVER YHA4H2NGS1EU Y\n"
  "RUNTIME ViewsCharts 5.300 NEVER EGE6208M0JUF Y\n"
  "RUNTIME ViewsDataccess 5.300 NEVER 0352R0TYGFY5 Y\n"
  "RUNTIME ViewsDataccessSQL 5.300 NEVER GF10P3PUWXAS Y\n"
  "RUNTIME ViewsLayout 5.300 NEVER 135JD1ZJ4VKD Y\n"
  "RUNTIME ViewsMaps 5.300 NEVER HMHS73Z4W1N8 Y\n";
static const int ilm_runtime_license_signature = 1975328;


/* -------------------------------------------------------
Fonction    : DllMain
Description : Entry point of the DLL

Paramètres  :	conventional
Retour		:	BOOL

Auteur	    : EP
Créé le	    : 01/02/01
------------------------------------------------------- */
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	AdxInterface::DllInstance = (HINSTANCE)hModule;
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}




/* -------------------------------------------------------
Fonction    : X3Centr1_InitAppEx
Description : Initialization function of the weighing units module
			  with the new way to initialize
Paramètres  :	Instance of the calling program
				Table of paths
				Pointer on return function
				Major version
				Minor version
				Patch number

Retour		:	Pointer on an allocated structure

Auteur	    : EP
Créé le	    : 01/02/01
------------------------------------------------------- */
X3CENTR1_API char* X3Centr1_InitAppEx (HINSTANCE m_hInstance,
									 char** m_pszPaths,
									 fn_CallBack pfCallBack,
								     unsigned int nProdMajor,
									 unsigned int nProdMinor,
									 unsigned int nProdPatch)
{
MessageBox(NULL,"Inside InitAppEx","test",MB_OK);		
	if ((m_pszPaths[CstnPathCSV] == NULL) || (m_pszPaths[CstnPathROOTX3] == NULL))
	return NULL;

//	MessageBox(NULL,"Enter X3Centr1_InitAppEx","test",MB_OK);
	X3IlogStruct* pIlog;

// à activer pour 4.00
//	IlvRegisterLicense(ilm_license_views, ilm_license_signature_views);
/*
// à activer pour 4.01
	IlvRegisterLicense(ilm_Views_license, ilm_Views_license_signature);
*/
// à activer pour 4.02
	IlvRegisterLicense(ilm_runtime_license, ilm_runtime_license_signature);

	// on alloue un espace pour la structure
	pIlog = (X3IlogStruct*)malloc (sizeof(X3IlogStruct));
	if (pIlog == NULL)
		return NULL;
	//MessageBox(NULL," 1 Allocation Structure","test",MB_OK);

	ZeroMemory (pIlog, sizeof(X3IlogStruct));


	// Création objet synchronisation (LLC)
/*	pIlog->hMutex = CreateMutex (NULL, FALSE, "IlogSync");	
	// si erreur de création, sortie? que peut on faire de plus ?			
	if (pIlog->hMutex == NULL)								
	{
		return NULL;
	}
*/
//	pIlog->hWaiting = CreateEvent (NULL, TRUE, TRUE, EVENT_WAITING);
//	DebugBreak();
	pIlog->pfCallBack = pfCallBack;
	pIlog->hInstance = m_hInstance;
	pIlog->_interface = new AdxInterface();
	//MessageBox(NULL," 2 Création interface","test",MB_OK);

	// recup des chemins des fichiers
	sprintf (pIlog->szPathX3, "%s", m_pszPaths[CstnPathROOTX3]);
	sprintf (pIlog->szPathCSV, "%s", m_pszPaths[CstnPathCSV]);
	sprintf (pIlog->szPathIni, "%s", m_pszPaths[CstnPathINI]);
	//Si le répertoire de cache est vide on passe par l'ancien emplacement pour rester
	//compatible avec les anciens dossiers X3
	if(PathIsDirectoryEmpty(m_pszPaths[CstnPatchCACHE]))
	{
		sprintf (pIlog->szPathCACHE, "%sIcons\\Risquesecu_jpg", m_pszPaths[CstnPathROOTX3]);
	}
	else
	{
		sprintf (pIlog->szPathCACHE, "%s", m_pszPaths[CstnPatchCACHE]);
	}
	
	// Get the data from the csv files
	if (*(m_pszPaths[CstnPathCSV] + strlen (m_pszPaths[CstnPathCSV]) - 1) == '\\')
	{	// The path ends with an anti-slash
		pIlog->_interface->getDonnees()->setSzCheminCsv1("%sX3ScalesBox.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv2("%sX3ScalesMwg.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv3("%sX3ScalesPha.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv4("%sX3ScalesMat.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv5("%sX3ScalesSto.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv6("%sX3ScalesSle.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv7("%sX3ScalesHsh.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv8("%sX3ScalesCtn.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv9("%sX3ScalesTco.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv10("%sX3ScalesAll.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv11("%sX3ScalesWgg.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv12("%sX3ScalesCgd.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv13("%sX3ScalesCbt.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv14("%sX3ScalesUid.csv", m_pszPaths[CstnPathCSV]);  //NSH

	}
	else
	{
		pIlog->_interface->getDonnees()->setSzCheminCsv1("%s\\X3ScalesBox.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv2("%s\\X3ScalesMwg.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv3("%s\\X3ScalesPha.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv4("%s\\X3ScalesMat.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv5("%s\\X3ScalesSto.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv6("%s\\X3ScalesSle.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv7("%s\\X3ScalesHsh.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv8("%s\\X3ScalesCtn.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv9("%s\\X3ScalesTco.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv10("%s\\X3ScalesAll.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv11("%s\\X3ScalesWgg.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv12("%s\\X3ScalesCgd.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv13("%s\\X3ScalesCbt.csv", m_pszPaths[CstnPathCSV]);
		pIlog->_interface->getDonnees()->setSzCheminCsv14("%s\\X3ScalesUid.csv", m_pszPaths[CstnPathCSV]);  //NSH
	}

// initialise l'interface (première partie)
// 02.04 on passe la chaîne de caractère szPathX3 au lieu du pointeur m_pszPathX3 car ce dernier
// appartient au client qui le nettoie 
	if (!pIlog->_interface->initInterface((IlvAny)m_hInstance,
		"Accueil Centrales", pIlog->_interface->getDonnees()->getLanguage(),
		pIlog->szPathX3, pIlog->szPathIni,pIlog->szPathCSV,pIlog->szPathCACHE ,(char*)pIlog))
	{
		X3Ilog_Reset(pIlog);
		return NULL;
	}
	//MessageBox(NULL," 3 Initialisation interface 1","test",MB_OK);	

// chargement des donnees à partir des fichiers
	if (!pIlog->_interface->getDonnees()->loadData(
							pIlog->_interface->getDonnees()->getSzCheminCsv1(),
							pIlog->_interface->getDonnees()->getSzCheminCsv2(),
							pIlog->_interface->getDonnees()->getSzCheminCsv3(),
							pIlog->_interface->getDonnees()->getSzCheminCsv4(),
							pIlog->_interface->getDonnees()->getSzCheminCsv6(),
							pIlog->_interface->getDonnees()->getSzCheminCsv7(),
							pIlog->_interface->getDonnees()->getSzCheminCsv8(),
							pIlog->_interface->getDonnees()->getSzCheminCsv9(),
							pIlog->_interface->getDonnees()->getSzCheminCsv12(),
							pIlog->_interface->getDonnees()->getSzCheminCsv14()))	//NSH
	{
		X3Ilog_Reset(pIlog);
		return NULL;
	}
	//MessageBox(NULL," 4 Lecture fichiers","test",MB_OK);


// initialise l'interface (deuxième partie)
// 02.04 on passe la chaîne de caractère szPathX3 au lieu du pointeur m_pszPathX3 car ce dernier
// appartient au client qui le nettoie
	if (!pIlog->_interface->completeInitInterface((IlvAny)m_hInstance,
		"Accueil Centrales", pIlog->_interface->getDonnees()->getLanguage(),
		pIlog->szPathX3, (char*)pIlog))
	{
		X3Ilog_Reset(pIlog);
		return NULL;
	}
	//MessageBox(NULL," 5 Initialisation interface 2","test",MB_OK);		

	return (char*)pIlog;
}


/* -------------------------------------------------------
Fonction    : X3Centr1_ShowAccueil
Description : Affiche la page d'accueil dans la fenêtre passée en paramètre

Paramètres  :	Pointeur sur la structure IlogStruct
				Handle de la fenêtre
				Cadre alloué a l'accueil
Retour		:	Rien

Auteur	    : EP
Créé le	    : 20/03/01
------------------------------------------------------- */
X3CENTR1_API void X3Centr1_ShowAccueil (char* pStruct,
										HWND hWnd,
										RECT* pRect)
{
X3IlogStruct* pIlog;

	pIlog = (X3IlogStruct*)pStruct;
	if (pIlog == NULL)
		return;

	pIlog->hClientIlog = hWnd;

	IlvRect rect(pRect->left, pRect->top,
		(pRect->right - pRect->left), (pRect->bottom - pRect->top));

	pIlog->_interface->showWindow((IlvSystemView)(unsigned int)hWnd, &rect);
//	pIlog->_interface->showWindow((IlvSystemView)(unsigned int)hWnd, rect
//		   ,pIlog->_problem->getStartDate(),15 );
	pIlog->_container = pIlog->_interface->getAccueil();
	long a = 0;
}


/* -------------------------------------------------------
Fonction    : X3Ilog_CloseScales
Description : Fermeture de la classe Ilog

Paramètres  :	Pointeur sur la structure IlogStruct
Retour		:	Rien

Auteur	    : MC
Créé le	    : 21/09/01
------------------------------------------------------- */
X3CENTR1_API void X3Centr1_CloseScales (char* pStruct)
{
X3IlogStruct* pIlog;

	pIlog = (X3IlogStruct*)pStruct;
	// GBE 23/05/2013 Nouvelle gestion de la fermetures des fenêtres
	// il faut respecter l'ordre 
	pIlog->_interface->closeAllWindows();


	// GBE 22/04/2013 On déplace la libération de l'OF pour que ce soit fait dans tous les cas.
	//      On va pouvoir désormais fermer la centrale en cliquant sur le bouton de fermeture
	//      ou sur la crois rouge en haut à droite de la fenêtre
    AdxData* m_data = pIlog->_interface->getDonnees();

	if (m_data != NULL)
	{
		if ((m_data->getCurrentOrderIndex() == 0) && (m_data->getPeseeLancee() == false))
		{
			m_data->SendX3_ChangementOFNonPese(NULL);
		}
	}

	if (pIlog)
	{
		delete pIlog->_interface;
		free (pIlog);
	}
}

/* -------------------------------------------------------
Fonction    : X3Ilog_ChangeTitle
Description : Change le titre de la fenetre

Paramètres  :	Pointeur sur structure
				Titre
Retour		:	Rien

Auteur	    : Marc
Créé le	    : 13/12/99
------------------------------------------------------- */
void X3Ilog_ChangeTitle (const char* pStruct, const char* pszTitle)
{
X3IlogStruct* pIlog;

/* NSH - commented out below for now - DEBUG doesn't seem to like it!

	std::string X3_DLLVersion;									//X3-67237: string to hold the DLL version
	std::string newtitle;										//X3-67237: string to hold the window title

	X3_DLLVersion = X3Ilog_GetProductVersion();					//X3-67237: go find the DLL version
	newtitle = std::string(pszTitle) + 
		       std::string(" (ver: ") + 
			   std::string(X3_DLLVersion) + 
			   std::string(")");								//X3-67237: build the new window title to include the DLL version
NSH */

	pIlog = (X3IlogStruct*)pStruct;
	if (pIlog)
	{
		if (pIlog->hClientIlog)
//X3-67237: replaced with below			SetWindowText (GetParent (pIlog->hClientIlog), pszTitle);
	SetWindowText (GetParent (pIlog->hClientIlog), pszTitle);
//NSH - commented out for now				SetWindowText (GetParent (pIlog->hClientIlog), newtitle.c_str());		//X3-67237: Show the new title
	}
}

/* -------------------------------------------------------
Fonction    : X3Ilog_GetWindowHandle
Description : Renvoit le handle de la fenetre supportant le gantt

Paramètres  :	Pointeur sur structure
				Adresse de la zone en réception (_MAX_PATH)
Retour		:	Rien

Auteur	    : Marc
Créé le	    : 13/12/99
------------------------------------------------------- */
HWND X3Ilog_GetWindowHandle (const char* pStruct)
{
X3IlogStruct* pIlog;
HWND hPere;

	pIlog = (X3IlogStruct*)pStruct;
	if (pIlog)
	{
		hPere = GetParent (pIlog->hClientIlog);
		if (hPere == NULL)
			hPere = pIlog->hClientIlog; // Pour testX3
		return hPere;
	}
	return NULL;
}

/* -------------------------------------------------------
Fonction    : X3Ilog_SendX3
Description : Retourne en fonction d'un nombre variable de paramètre, un format de type :
				XnNm (ou n et m représente le nombre de char et num)
				Puis les paramètres cadrés selon le format.

Paramètres  :	char*
Retour		:	Rien

Auteur	    : Marc
Créé le	    : 30/11/99
------------------------------------------------------- */
void X3Ilog_SendX3 (const char* pStruct,
					int nAction,
					int bSynchro,
					const char* pszFormat, ...)
{
X3IlogStruct* pIlog;
va_list argument;
char szData[1024];
short nData;
char szFormat[256];
short nFormat;
int nLong;
char* pszTemp;
char szTemp[256];
long lTemp;
short nbPar;
char* pszPar;
int i;
int j;
//DWORD dwWaitResult;
	pIlog = (X3IlogStruct*)pStruct;
	if (pIlog)
	{
		// GBE 20/12/12 Ajout Trace pour les échanges avec X3
		AdxInterface* Interface = pIlog->_interface;
		// GBE 20/12/12 Ajout Trace pour les échanges avec X3
		if(Interface->getTraceMode() == 1)
		{
			Interface->_traceFile<< "X3Ilog_SendX3 Entree" << endl;
		}
		va_start (argument, pszFormat);	// On démarre au premier paramètre optionnel

		ZeroMemory (szFormat, sizeof(szFormat));
		nFormat = 0;
		ZeroMemory (szData, sizeof(szData));
		nData = 0;
 		ZeroMemory (szTemp, sizeof(szTemp));
		// On traite les paramètres optionnnels
		nbPar = strlen (pszFormat);
		pszPar = (char *)pszFormat;
		// Chargement des parametres
		i = 0;
		if(Interface->getTraceMode() == 1)
		{
			// GBE 20/12/12 Ajout Trace pour les échanges avec X3
			Interface->_traceFile<< "X3Ilog_SendX3 Action ("<<nAction<<") bSynchro("<<bSynchro<<")" << endl;
		}
		while (i < nbPar)
		{
			if (*pszPar == '%')
			{
//				switch (*(pszPar + 1))
				switch (*(pszPar + i + 1))
				{
				case 's':
 					// Paramètre alphanumérique (char*)
					pszTemp = va_arg (argument, char*);
                    // on copie la donnée dans un buffer de travail car on va peut-être la modifier 
                    // pour rajouter les "///"
                    sprintf(szTemp,"%s",pszTemp);
					nLong = strlen(szTemp);
                    if (nLong == 10)
                    {
                        nLong +=3;
                        j  = sprintf(szTemp,"%s///",szTemp);
//                        j += sprintf(szTemp+j,"%s","///");				
                    }
    					// on charge le format
					szFormat[nFormat] = 'X';
					nFormat++;
					szFormat[nFormat] = nLong;
					nFormat++;
					// on charge la donnée
					CopyMemory (&szData[nData], &szTemp[0], nLong);
					nData += nLong;
					if(Interface->getTraceMode() == 1)
					{
						// GBE 20/12/12 Ajout Trace pour les échanges avec X3
						Interface->_traceFile<< "\t String Parameter ("<<szTemp<<")" << endl;
					}
					break;
				case 'd':
					// Paramètre numérique (long)
					lTemp = va_arg (argument, long);
					sprintf (szTemp, "%ld", lTemp);
					nLong = strlen (szTemp);
                    if (nLong == 10)
                    {
                        nLong +=3;
                        j  = sprintf(szTemp,"%s///",szTemp);
//                        j += sprintf(szTemp+j,"%s","///");				
                    }
					// on charge le format
					szFormat[nFormat] = 'N';
					nFormat++;
					szFormat[nFormat] = nLong;
					nFormat++;
					// on charge la donnée
					CopyMemory (&szData[nData], &szTemp[0], nLong);
					nData += nLong;
					if(Interface->getTraceMode() == 1)
					{
						// GBE 20/12/12 Ajout Trace pour les échanges avec X3
						Interface->_traceFile<< "\t Number Parameter ("<<szTemp<<")" << endl;
					}
					break;

				}
			}
			i += 2;
		}	
		va_end (argument);

//		ResetEvent(pIlog->hWaiting);
//		if (pIlog->pfCallBack)
//			(*(pIlog->pfCallBack))((char*)pIlog, nAction, szFormat, szData);
		if (pIlog->pfCallBack)
			(*(pIlog->pfCallBack))((char*)pIlog, nAction, bSynchro, szFormat, szData);
//		(*(pIlog->pfCallBack))((char*)pIlog,pIlog->hWaiting, nAction, szFormat, szData);

		// Création objet synchronisation (LLC)
//		pIlog->hMutex = OpenMutex (MUTEX_ALL_ACCESS, FALSE, "IlogSync");	
		// si erreur de création, sortie? que peut on faire de plus ?			
/*		if (pIlog->hMutex == NULL)								
		{
			return;												
		}
		// on prend la main sur le Mutex
		dwWaitResult = WaitForSingleObject (pIlog->hMutex, INFINITE);
		// test si plantage DLL avant libération
		switch (dwWaitResult)
		{
			case WAIT_ABANDONED:				
				return;	
			case WAIT_OBJECT_0:
				ReleaseMutex(pIlog->hMutex);
		}*/
		// on attend que le thread est "attrapé" la connection
//		WaitForSingleObject (pIlog->hWaiting, 2000);
		// GBE 20/12/12 Ajout Trace pour les échanges avec X3
		if(Interface->getTraceMode() == 1)
		{
			Interface->_traceFile<< "X3Ilog_SendX3 Sortie" << endl;
		}
    }
}

/* -------------------------------------------------------
Fonction    : X3Ilog_Notify
Description : Redonne la main après un SendX3 pour indiquer
			  que le serveur a terminé	

Paramètres  :	Handle de la fenêtre
				Pointeur sur la structure IlogStruct
Retour		:	Rien

Auteur	    : MC
Créé le	    : 18/09/01
------------------------------------------------------- */

void X3Ilog_Notify (HWND hWnd,const char* pStruct)
{
	X3IlogStruct* pIlog;
	pIlog = (X3IlogStruct*)pStruct;
	if (pIlog && pIlog->_interface != NULL)
	{
		// GBE 20/12/12 Ajout Trace pour les échanges avec X3
		AdxInterface* Interface = pIlog->_interface;
		// GBE 20/12/12 Ajout Trace pour les échanges avec X3
		if(Interface->getTraceMode() == 1)
		{
			Interface->_traceFile<< "X3Ilog_SendX3 Entree" << endl;
		}
		pIlog->_interface->notify();
		// GBE 20/12/12 Ajout Trace pour les échanges avec X3
		if(Interface->getTraceMode() == 1)
		{
			Interface->_traceFile<< "X3Ilog_SendX3 Sortie" << endl;
		}
	}
//	MessageBox(NULL,"test après notify","test",MB_OK);
}

/* -------------------------------------------------------
Fonction    : X3Ilog_Reset
Description : Fermeture de la classe Ilog

Paramètres  :	Pointeur sur la structure IlogStruct
Retour		:	Rien

Auteur	    : MC
Créé le	    : 21/09/01
------------------------------------------------------- */
void X3Ilog_Reset (X3IlogStruct* pIlog)
{
	if (pIlog)
	{
		if (pIlog->_interface != NULL)
			delete pIlog->_interface;
		free (pIlog);
	}
}


/*NSH commented out below block for now - DEBUG doesn't seem to like it

//X3-67237: Added below block to get the version number from the resource file which will be shown in the window title
//X3-67237: Below was taken from a couple of examples on the web
static std::string X3Ilog_GetProductVersion()
{
	std::string strResult;
    char szModPath[ MAX_PATH ];
	HMODULE hm = NULL;

	if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
		GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
		(LPCSTR) &X3Ilog_ChangeTitle,
		&hm))
	{
		//Some error
	}

	szModPath[ 0 ] = '\0';
	GetModuleFileNameA(hm, szModPath, sizeof(szModPath));
	DWORD dwHandle;
    DWORD dwSize = GetFileVersionInfoSize( szModPath, &dwHandle );

    if( dwSize > 0 )
    {
        BYTE* pbBuf = static_cast<BYTE*>( alloca( dwSize ) );
        if( GetFileVersionInfo( szModPath, dwHandle, dwSize, pbBuf ) )
        {
            UINT uiSize;
            BYTE* lpb;
            if( VerQueryValue( pbBuf,
                               "\\VarFileInfo\\Translation",
                               (void**)&lpb,
                               &uiSize ) )
            {
                WORD* lpw = (WORD*)lpb;
                CString strQuery;
                strQuery.Format( "\\StringFileInfo\\%04x%04x\\ProductVersion", lpw[ 0 ], lpw[ 1 ] );
                if( VerQueryValue( pbBuf,
                                   const_cast<LPSTR>( (LPCSTR)strQuery ),
                                   (void**)&lpb,
                                   &uiSize ) && uiSize > 0 )
                {
                    strResult = (LPCSTR)lpb;
                }
            }
        }
    }

	return strResult;
}
//X3-67237 - End of added block

*/