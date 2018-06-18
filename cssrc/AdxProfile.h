// AdxProfile.h
// ------------
// projet : Adonix X3 Optimisation
// auteur : MG + MC
//--------------------------------------------------------------
//    header pour gestion du profil utilisateur
//
#ifndef __ADXPROFILE_H
	#define __ADXPROFILE_H


//--------------------------
// constantes 
#define INI_FILENAME	"x3Scales.ini"

#define SECTION_GENERAL			"General"
#define CLE_GENERAL_TRACE		"Trace"
#define CLE_GENERAL_MSG	    	"Message"
#define CLE_GENERAL_SCAMSG   	"NoScaleMess" // sr 01.12 APCPRD-511

// gbe 26/03/12 Gestion de la visibilité des éléments de l'écran AdxPesee_OF
#define SECTION_ADXPESEE_OF		"PeseeOF"
#define CLE_SHOW_GRADUATION     "ShowGraduation"
#define CLE_SHOW_TOLERANCE		"ShowTolerance"
#define CLE_WEIGHT_FONT_HEIGHT	"WeightFontHeight"

// GBE 04/10/2013 Gestion de la purge du buffer lors du test de connexion
#define SECTION_COMMUNICATION	"Communication"
#define CLE_CLEAR_BUFFER		"ClearBufferAtConnectTest"


typedef struct _DefaultValue
{
	char dvSection[32];
	char dvCle[32];
	char dvValue[32];

} DefaultValue;

//--------------------------
// variables

//--------------------------
// définition des fonctions
BOOL AdxProfile_PutValue (	char* pszSectionName,	// Enregistre une valeur dans une section du .INI
						char* pszParamName, 
						char* pszValeur);

BOOL AdxProfile_GiveValue (char* pszSectionName,	// renvoit une valeur stockée dans le .INI
						char* pszParamName, 
						char** ppszRetour);

DWORD AdxProfile_SetStandardValue (					// Renvoit la valeur par défaut d'un parametre
						char* pszSectionName, 
						char* pszParamName, 
						char* pszRetour, 
						DWORD dwLong);

void AdxProfile_GiveFileIniName (					// Renvoit le nom complet du fichier.ini de l'application
						char* pszRetour,
						int nLong);

void AdxProfile_GiveFileDirectory (					// Renvoit le nom de la directory de l'application
						char* pszRetour,
						int nLong);

void  setPathIni(const char* pathIni) ;				// recupere nouveau chemin (pathIni) pour le fichier .ini.

#endif
// fin du header
