// AdxProfile.cpp
// --------------
// projet : Adonix X3 Optimisation
// auteur : MG + MC
//--------------------------------------------------------------
//

#include "stdafx.h"
#include "AdxProfile.h"



DefaultValue sDefault[] =
{
	{SECTION_GENERAL,	CLE_GENERAL_TRACE,		"0"},
	{SECTION_GENERAL,	CLE_GENERAL_MSG,		"0"},
	{SECTION_GENERAL,	CLE_GENERAL_SCAMSG,		"0"},
	{SECTION_GENERAL,	CLE_SHOW_GRADUATION,	"1"},
	{SECTION_GENERAL,	CLE_SHOW_TOLERANCE,		"1"},
	{SECTION_GENERAL,	CLE_WEIGHT_FONT_HEIGHT,	"40"}
};
char*     _pathIni;		// chemin de .ini - mm 05.07

/* -------------------------------------------------------
Fonction	:	AdxProfile_PutValue
Description :	Enregistre une valeur dans une section du .INI

Paramètres	:	Nom de la section générale
				Nom du parametre
				Chaine à enregistrer
Retour		: Bool
Auteur		: Marc
Créé le		: 19/06/98
Modifié le  : 
------------------------------------------------------- */
BOOL AdxProfile_PutValue (char* pszSectionName, char* pszParamName, char* pszValeur)
{
	char szFileIniName[_MAX_PATH];

	AdxProfile_GiveFileIniName (&szFileIniName[0], sizeof(szFileIniName));
	return (WritePrivateProfileString(pszSectionName, pszParamName, pszValeur, szFileIniName));
}

/* -------------------------------------------------------
Fonction	:	AdxProfile_GiveValue
Description :	Renvoit une valeur stockée dans le .INI

Paramètres	:	Nom de la section générale
				Nom du parametre
				Adresse du pointeur recevant la chaine
					L'appelant est responsable de la libération de la chaine
Retour		: Bool
Auteur		: Marc
Créé le		: 27/03/98
Modifié le  : 
------------------------------------------------------- */
BOOL AdxProfile_GiveValue (char* pszSectionName, char* pszParamName, char** ppszRetour)
{
	char szFileIniName[_MAX_PATH];
	char szTemp[255];
	DWORD dwRet;


	*ppszRetour = NULL;
	ZeroMemory (szTemp, sizeof (szTemp));

	AdxProfile_GiveFileIniName (&szFileIniName[0], sizeof(szFileIniName));

	dwRet = GetPrivateProfileString(pszSectionName, pszParamName, "", &szTemp[0], sizeof(szTemp), szFileIniName);
	if (dwRet < 1)
	{
		dwRet = AdxProfile_SetStandardValue (pszSectionName, pszParamName, &szTemp[0], sizeof(szTemp));
	}
	if (dwRet > 0)
	{
		*ppszRetour = (char*)malloc ((dwRet + 1) * sizeof(char));
		if (*ppszRetour == NULL)
			return (FALSE);
		
		sprintf (*ppszRetour, "%s", &szTemp[0]);
	}	
	// S'il y a quelquechose dans dwRet, 
	// c'est qu'il a trouvé la section ou la valeur par défault
	return (dwRet > 0 ? TRUE : FALSE );
}

/* -------------------------------------------------------
Fonction	:	AdxProfile_SetStandardValue
Description :	Renvoit la valeur par défault du parametre

Paramètres	:	Nom de la section
				Nom du parametre
				Zone de stockage de la valeur
				Longueur de la zone de stockage

Retour		: Nombre de caracteres stockés
Auteur		: Marc
Créé le		: 19/06/98
Modifié le  : 
------------------------------------------------------- */
DWORD AdxProfile_SetStandardValue (char* pszSectionName, char* pszParamName, char* pszRetour, DWORD dwLong)
{
	DWORD dwRet;
	int i;
	int j;
	BOOL bOk;

	dwRet = 0;
	i = 0;
	// On recherche d'abord la section
	while (_stricmp (sDefault[i].dvSection, pszSectionName) != 0) 
	{
		if (sDefault[i].dvSection[0] == 0)
			return 0;		// on a parcouru la table mais on n'a rien trouvé
		i++;
	}

	while (_stricmp (sDefault[i].dvSection, pszSectionName) == 0)	//tant que l'on est dans la meme section
	{
		bOk = TRUE;
		// on controle car par car la correspondance de la cle
		for (j=0; j < (int)strlen(sDefault[i].dvCle); j++)
		{
			if (j > (int)strlen(pszParamName))
			{
				bOk = FALSE;	// le nom de la cle en parametre est plus long
				break;
			}
			// On traite les valeurs generiques (avec une étoile à la fin)
			if (sDefault[i].dvCle[j] == '*')
				break;
			// On controle que les car sont identiques
			if (toupper(sDefault[i].dvCle[j]) != toupper(pszParamName[j]))
			{
				bOk = FALSE;	// le nom de la cle en parametre est plus long
				break;
			}
		}
		if (bOk)
		{
			if (strlen(sDefault[i].dvValue) < dwLong)
			{
				sprintf (pszRetour, "%s", sDefault[i].dvValue);
				dwRet = strlen (sDefault[i].dvValue);
			}
			else
			{
				strncpy (pszRetour, sDefault[i].dvValue, dwLong - 1);
				*(pszRetour + dwLong) = '\0';
				dwRet = dwLong - 1;;
			}
			break;	// On sort de la boucle avec dwRet chargé
		}
		i++;
	}
	return (dwRet);
}

/* -------------------------------------------------------
Fonction	:	AdxProfile_GiveFileIniName
Description :	Renvoit le nom complet du fichier.ini de l'application

Paramètres	:	Adresse de la chaine a renseigner
				Longuer de la chaine passée

Retour		: rien
Auteur		: Marc
Créé le		: 03/04/98
Modifié le  : 
------------------------------------------------------- */
void AdxProfile_GiveFileIniName (char* pszRetour, int nLong)
{
	// On construit le nom du fichier avec son repertoire
	AdxProfile_GiveFileDirectory (pszRetour, nLong);
	if ((strlen(pszRetour) + 1 + sizeof(INI_FILENAME)) < (unsigned)nLong)
		sprintf (pszRetour, "%s%c%s", pszRetour, '\\', INI_FILENAME);
}

/* -------------------------------------------------------
Fonction	:	AdxProfile_GiveFileDirectory
Description :	Renvoit le nom de la directory de l'application sans le \ de fin

Paramètres	:	Adresse de la chaine a renseigner
				Longueur de la chaine

Retour		: rien
Auteur		: Marc
Créé le		: 29/06/98
Modifié le  : 11/05/07 
------------------------------------------------------- */
void AdxProfile_GiveFileDirectory (char* pszRetour, int nLong)
{
	sprintf(pszRetour,"%s", _pathIni);
	/*char szDirectory[_MAX_PATH];
	char szDrive[3];
	char szDir[_MAX_PATH];
	char szFileName[_MAX_PATH];
	char szExt[_MAX_PATH];

	// On construit le nom du fichier avec son repertoire
//	GetCurrentDirectory(_MAX_PATH, pszRetour);
	GetModuleFileName (NULL, &szDirectory[0], nLong - 1);
	_splitpath (szDirectory, &szDrive[0], &szDir[0], &szFileName[0], &szExt[0]);
	// on enleve le '\' de fin
	while (szDir[strlen(szDir) - 1] == '\\')
	{
		szDir[strlen(szDir) - 1] = 0;
	}
	if ((strlen(szDirectory) + strlen(szDrive)) < (unsigned)nLong)
		sprintf (pszRetour, "%s%s", szDrive, szDir);*/
}

/* -------------------------------------------------------
Fonction	:	setPathIni
Description :	recupere nouveau chemin (pathIni) pour le fichier .ini.

Paramètres	:	Nouveau chemin du fichier .ini

Retour		: rien
Auteur		: Muriel
Créé le		: 11/05/07 
Modifié le  : 
------------------------------------------------------- */
void  setPathIni(const char* pathIni) 
{
	if( _pathIni != NULL)
		delete [] _pathIni;
	_pathIni = new char[_MAX_PATH];
	strcpy( _pathIni, pathIni);
}