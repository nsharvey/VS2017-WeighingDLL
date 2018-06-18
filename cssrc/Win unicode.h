/*	Header pour la gestion du mapping générique pour versions Standard/Unicode	*/
#ifndef _WIN_UNICODE_H
	#define _WIN_UNICODE_H

#ifdef _X3
	#include "adxdef.h"
#endif

#ifdef __cplusplus
	extern "C" {
#endif


#define HTML_CHARSET_UTF8		TEXT("utf-8")
#define HTML_CHARSET_ISO88591	TEXT("iso-8859-1")

#ifdef X3_UNICODE
/* ++++++++++++++++++++ UNICODE ++++++++++++++++++++ */
#define LSTRX					LSTRU					// Type chaîne de caractères dans structure res_u
#define T_STX					t_stu					// Champ chaîne de la structure res_u
#define USER_ENDFILENAMEX		TEXT(".Ux3i")			// Extension du fichier de config utilisateur
#define	LOCALISATION_FILENAMEX	TEXT("X3Connex.Ux3c")	// Nom du fichier contenant la description des localisations de fichiers APPLI
#define APPLICATION_FILENAMEX   TEXT("X3APPLI.Ux3a")	// Nom du fichier serveur contenant la desc des appli
#define OPEN_FILE_R				TEXT("rb")				// Mode d'ouverture en lecture du fichier de config utilisateur
#define OPEN_FILE_W				TEXT("wb")				// Mode d'ouverture en écriture du fichier de config utilisateur
#define OPEN_FILE_A				TEXT("ab")				// Mode d'ouverture en "append" du fichier de config utilisateur
#define FLAG_UNICODE			TRUE
#define HTML_CHARSETX			HTML_CHARSET_UTF8		// Définition du Charset des pages HTMLs générées pour le menu
#define	SPLASH_PROGIDX			SPLASH_PROGID_UNICODE	// ProgId de l'OCX Splash
#define	FORMULA_PROGIDX			FORMULA_PROGID_UNICODE	// ProgId de l'OCX Formula
#define Socket_StockeBufferX	Socket_StockeBufferW	// Redirection de la fonction de stockage des buffers sur lecture directe socket	
#define ImpCrystal_ChangeParameterX	ImpCrystal_ChangeParameterW	// Redirection de la fonction de chargement des paramètres Crystal
#define ImpCrystal_ChangePropertyX	ImpCrystal_ChangePropertyW	// Redirection de la fonction de mise à jour des paramètres Crystal
#define ImpCrystal_DefineServerX	ImpCrystal_DefineServerW	// Redirection de la fonction de mise à jour de la liaison ODBC pour Crystal
/* ++++++++++++++++++ FIN UNICODE ++++++++++++++++++ */

#else

/* +++++++++++++++++++++ ANSI ++++++++++++++++++++++ */
#define LSTRX					LSTRG					// Type chaîne de caractères dans structure res_u
#define T_STX					t_str					// Champ chaîne de la structure res_u
#define USER_ENDFILENAMEX		USER_ENDFILENAME		// Extension du fichier de config utilisateur
#define	LOCALISATION_FILENAMEX	LOCALISATION_FILENAME	// Nom du fichier contenant la description des localisations de fichiers APPLI
#define APPLICATION_FILENAMEX   APPLICATION_FILENAME	// Nom du fichier serveur contenant la desc des appli
#define OPEN_FILE_R				TEXT("r")				// Mode d'ouverture en lecture du fichier de config utilisateur
#define OPEN_FILE_W				TEXT("w")				// Mode d'ouverture en écriture du fichier de config utilisateur
#define OPEN_FILE_A				TEXT("a")				// Mode d'ouverture en "append" du fichier de config utilisateur
#define FLAG_UNICODE			FALSE
#define HTML_CHARSETX			HTML_CHARSET_ISO88591	// Définition du Charset des pages HTMLs générées pour le menu
#define	SPLASH_PROGIDX			SPLASH_PROGID_ANSI		// ProgId de l'OCX Splash
#define	FORMULA_PROGIDX			FORMULA_PROGID_ANSI		// ProgId de l'OCX Formula
#define Socket_StockeBufferX	Socket_StockeBuffer		// Redirection de la fonction de stockage des buffers sur lecture directe socket
#define ImpCrystal_ChangeParameterX	ImpCrystal_ChangeParameter	// Redirection de la fonction de chargement des paramètres Crystal
#define ImpCrystal_ChangePropertyX	ImpCrystal_ChangeProperty	// Redirection de la fonction de mise à jour des paramètres Crystal
#define ImpCrystal_DefineServerX	ImpCrystal_DefineServer		// Redirection de la fonction de mise à jour de la liaison ODBC pour Crystal
/* +++++++++++++++++++ FIN ANSI +++++++++++++++++++ */

#endif

#define TCHARSize      (sizeof(TCHAR))

#ifdef _X3
// Structure s_chf pour besoins unicode
typedef struct
{
    TCHAR	*ch_pth_x ;			/*  Nom de la Machine			*/
    TCHAR	*ch_ptv_x ;			/*  Lettre du Volume			*/
    TCHAR	*ch_pta_x ;			/*  Application					*/
    TCHAR	*ch_ptd_x ;			/*  Liste des Sous-Repertoire	*/
    TCHAR	*ch_ptn_x ;			/*  Nom du Fichier				*/
    TCHAR	*ch_pte_x ;			/*  Extension					*/
    nchar	ch_pos ;			/*  Position dans le Buffer		*/
    TCHAR	ch_buf_x[LGP+1] ;	/*  Buffer Canonique			*/
    TCHAR	ch_can_x[LGP+1] ;	/*  Forme Canonique				*/
} s_chf_x ;
#endif

// Prototypes
int Unicode_WcharToChar(LPWSTR pszUnicodeBuff,LPSTR* ppszBuffer);
int Unicode_CharToWchar(const char* szBuffer, LPWSTR* ppszUnicodeBuff);
int Unicode_WcharToUtf8(LPWSTR pszUnicodeBuff,LPSTR* ppszBuffer,int nLen);
int Unicode_Utf8ToWchar(const char* szBuffer, LPWSTR* ppszUnicodeBuff,int nLen);
int Unicode_WcharToMbyte(LPWSTR pszUnicodeBuff,LPSTR* ppszBuffer, int nCp, int nLen);
int Unicode_Utf8ToMbyte(LPSTR pszUtf8f, LPSTR* ppszBuffer, int nCp, int nLen);

#ifdef __cplusplus
	}
#endif

#endif