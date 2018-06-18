// X3Centr1.h
// ----------
// project : Adonix X3 Centrale de Pesee
// author : EP		28/05/01
//--------------------------------------------------------------
//
#ifndef __X3CENTR1__H
	#define __X3CENTR1__H

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the X3CENTR1_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// X3CENTR1_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

//#include <windows.h>
#include <ilviews/gadgets/stdialog.h>

class AdxInterface;
class AdxData;

// Fonction de callback pour les effets tunnels et les retours sur erreur
//typedef BOOL (*fn_CallBack)(char*,HANDLE, int, char*, char*);
//typedef BOOL (*fn_CallBack)(char*, int, char*, char*);
typedef BOOL (*fn_CallBack)(char*, int, int, char*, char*);

// Les constantes
#define X3_TUNNEL				11
#define X3_ERREUR				12
/*#define X3_MESSAGE			13
#define X3_QUITTER				14
#define X3_AIDEOBJET			15*/
#define	X3_PESEEPARMAT			19
#define X3_CHANGEOF				20
#define X3_ALLOCLOT				21
#define X3_DESALLOUECOMPOSANT	22
#define X3_INTERRUPTCOMPOSANT	23
#define X3_INTERRUPTOF			24
#define X3_INTERRUPTPHASE		25
#define X3_MODIFALLOC			26
#define X3_PESEEPARTIELLE		27
#define X3_FINLOT				28
#define X3_FINCOMPOSANT			29
#define X3_FINPHASE				30
#define X3_FINOF				31
#define X3_AIDE					32
#define X3_RECONCILIATION		33
#define X3_IMPRIMEETALLOUELOTS	34
#define X3_VIDEBOX				35
#define X3_SOLDEEMB				36
#define X3_CHGTOFNONPESE		37
#define X3_IMPRIMELOTS			38
#define X3_MAJEMB   			39
#define X3_FINETALONNAGE_OK		40
#define X3_FINETALONNAGE_KO_KO	41
#define X3_FINETALONNAGE_OK_KO	42
#define X3_SOLDEMATIERE			43
#define X3_FINPHASEBIS			44
#define X3_FINOFBIS				45
#define X3_REFRESH				46    // sr 11.02 reactualisation des donnees
#define X3_RELOADALL    		47    // sr 03.04 diminution des allocs suite à une pesée > prévu
                                    
#define X3_CONSULTATIONSTOCK	48	  // mm 04.10 consultation stock détaillé

#define X3_PSEMAT_MAT			49	  // SMO : STD-PR-OO1 : Pesee Matiere : recuperation liste des composants
#define X3_PSEMAT_OF			50	  // SMO : STD-PR-OO1 : Pesee Matiere : recuperation liste des OFs par matiere
#define X3_FINCOMPOSANT_ART		51	  // mm 10.10 : Pesee Matiere : pesée complète article	
#define	X3_ABANDON_PESEEMULTI	52	  // mm 09.12 : abandon pesée multi-article (récipient ou balance pas adaptés)

#define X3_USER_CREDENTIALS		100		//X3-67237: Callback number to inform X3 to ask for user id/password

// gbe 18/01/11 mise en place du nouvel appel de la centrale de pesée
//Ordre des chemins dans le tableau
#define CstnPathCSV				0	//Chemin des csv
#define CstnPathROOTX3			1	//Root du client X3
#define CstnPathINI				2	//Chemin du fichier ini
#define CstnPatchCACHE			3	//Chemin du cache des images


#define EVENT_WAITING			"X3_WAITING_EVENT"

typedef struct _X3IlogStruct
{
	HINSTANCE hInstance;
// Classe pour resoudre le probleme d optimisation
	AdxInterface* _interface;
	IlvGadgetContainer* _container;
	fn_CallBack pfCallBack;
	HWND hClientIlog;
	char szPathX3[_MAX_PATH];
//	HANDLE hWaiting;
	char szPathIni[_MAX_PATH];		// chemin du .ini - mm 05.07
	char szPathCSV[_MAX_PATH];
	char szPathCACHE[_MAX_PATH];		// Chemin ver le cache - gbe 18/01/11
//	HANDLE hMutex;					// pointeur sur Mutex (LLC)
} X3IlogStruct;
//HANDLE hWaiting;

// Nous n'avons besoin que de dllexport en declaration sinon declaration fonction invalide
//#ifdef X3CENTR1_EXPORTS
#define X3CENTR1_API __declspec(dllexport)
//#else
//#define X3CENTR1_API __declspec(dllimport)
//#endif

X3CENTR1_API char* X3Centr1_InitAppEx (HINSTANCE m_hInstance,
									 char** m_pszPaths,
									 fn_CallBack pfCallBack,
								     unsigned int nProdMajor,
									 unsigned int nProdMinor,
									 unsigned int nProdPatch);

X3CENTR1_API void X3Centr1_ShowAccueil (char* pStruct, HWND hWnd, RECT* pRect);


// This class is exported from the x3centr1.dll
//class X3CENTR1_API CX3centr1 {
//public:
//	CX3centr1(void);
	// TODO: add your methods here.
//};

//extern X3CENTR1_API int nX3centr1;

//X3CENTR1_API int fnX3centr1(void);

// les fonctions internes avec l'accueil

void X3Ilog_ChangeTitle (const char* pStruct, const char* pszTitle);

void X3Ilog_SendX3 (const char* pStruct, int nAction,
					int bSynchro, const char* pszFormat, ...);
std::string X3Ilog_GetProductVersion ();					//X3-67237: Used to get the version number of the DLL

HWND X3Ilog_GetWindowHandle (const char* pStruct);

void X3Ilog_Reset (X3IlogStruct* pIlog);
#endif //__X3CENTR1__H

