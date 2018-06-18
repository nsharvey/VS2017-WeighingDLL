/* ****************************************************
    Win Unicode.cpp
    Module utilitaire pour traitement chaîne Unicode
   **************************************************** */


#include "stdafx.h"

#ifdef __cplusplus
	extern "C" {
#endif




/* -------------------------------------------------------
Fonction    : Unicode_WcharToChar
Description : Trancodage d'une chaîne Unicode en chaîne de char

Paramètres	: LPWSTR pszUnicodeBuff	: pointeur sur chaîne unicode							[in]
			: LPSTR* ppszBuffer		: pointeur de pointeur sur chaîne char transcodé		[out]

 Retour		: int : longueur finale de la chaîne (en nombre de char)

Remarque	: Il faut faire un free sur le pointeur "ppszBuffer" en retour d'appel de cette fct.

Auteur	    : Claude
Créé le	    : 16/01/02
Modifié le  :
------------------------------------------------------- */
int Unicode_WcharToChar(LPWSTR pszUnicodeBuff,LPSTR* ppszBuffer)
{
int nOutBufferSize = 0;

	// Premier appel à "WideCharToMultiByte" pour déterminer la taille du buffer transcodé
	nOutBufferSize = WideCharToMultiByte(CP_ACP,0, pszUnicodeBuff ,wcslen(pszUnicodeBuff)+1,NULL,0,NULL,NULL);

	// Second appel à "WideCharToMultiByte" pour effectuer le transcodage
	nOutBufferSize = WideCharToMultiByte(CP_ACP,0, pszUnicodeBuff ,wcslen(pszUnicodeBuff)+1,*ppszBuffer,nOutBufferSize,NULL,NULL);

	
	return nOutBufferSize;
}

/* -------------------------------------------------------
Fonction    : Unicode_CharToWchar
Description : Trancodage d'une chaîne de char en Unicode

Paramètres	: const char* aBuffer		: pointeur sur chaîne à transcoder								[in]
			  LPWSTR* ppszUnicodeBuff	: pointeur de pointeur sur chaîne transcodé en unicode			[out]

Retour		: int : longueur finale de la chaîne Unicode (en WCHAR).

Remarque	: Il faut faire un free sur le pointeur "ppszUnicodeBuff" en retour d'appel de cette fct.

Auteur	    : Claude
Créé le	    : 16/01/02
Modifié le  :
------------------------------------------------------- */
int Unicode_CharToWchar(const char* szBuffer, LPWSTR* ppszUnicodeBuff)
{
int nOutBufferSize = 0;

	// Premier appel à "MultiByteToWideChar" pour déterminer la taille du buffer transcodé (sans le caractère de fin, car java n'apprécie pas)
	nOutBufferSize = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED, szBuffer ,strlen(szBuffer)+1,NULL,0);

	// Second appel à "MultiByteToWideChar" pour effectuer le transcodage
	nOutBufferSize = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED, szBuffer ,strlen(szBuffer)+1,*ppszUnicodeBuff,nOutBufferSize);

	
	return nOutBufferSize;
}

/* -------------------------------------------------------
Fonction    : Unicode_WcharToUtf8
Description : Trancodage d'un buffer Unicode en buffer UTF-8 
			  **** A ne plus Utiliser - Utiliser à la place Unicode_WcharToMbyte ****

Paramètres	: LPWSTR pszUnicodeBuff	: pointeur sur buffer unicode								[in]
			: LPSTR* ppszBuffer		: pointeur de pointeur sur buffer char transcodé			[out]
			  int nLen				: si <= 0, le buffer en entré est NULL Terminated, autrement, on se base sur nLen pour la longueur du buffer [in]									

 Retour		: int : longueur finale du buffer char (inclu le zero fin de chaîne si nLen <=0).

Remarque	: Il faut faire un free sur le pointeur "ppszBuffer" en retour d'appel de cette fct.

Auteur	    : Claude
Créé le	    : 25/02/02
Modifié le  :
------------------------------------------------------- */
int Unicode_WcharToUtf8(LPWSTR pszUnicodeBuff,LPSTR* ppszBuffer, int nLen)
{
int		nOutBufferSize = 0;
int		nBuffLen = 0;

	// Détermine la longueur de buffer à transcoder
	if (nLen > 0)
		nBuffLen = nLen;
	else
		nBuffLen = wcslen(pszUnicodeBuff) + 1;

	// Premier appel à "WideCharToMultiByte" pour déterminer la taille du buffer transcodé
	nOutBufferSize = WideCharToMultiByte(CP_UTF8,0,pszUnicodeBuff,nBuffLen,NULL,0,NULL,NULL);

	
	// Second appel à "WideCharToMultiByte" pour effectuer le transcodage
	nOutBufferSize = WideCharToMultiByte(CP_UTF8,0,pszUnicodeBuff,nBuffLen,*ppszBuffer,nOutBufferSize,NULL,NULL);

	return nOutBufferSize;
}

/* -------------------------------------------------------
Fonction    : Unicode_Utf8ToWchar
Description : Trancodage d'un buffer UTF-8 en Unicode

Paramètres	: const char* aBuffer		: pointeur sur buffer à transcoder								[in]
			  LPWSTR* ppszUnicodeBuff	: pointeur de pointeur sur buffer transcodé en unicode			[out]
			  int nLen					 : si <= 0, le buffer en entré est NULL Terminated, autrement, on se base sur nLen pour la longueur du buffer [in]

Retour		: int : longueur finale du buffer Unicode (en WCHAR).

Remarque	: Il faut faire un free sur le pointeur "ppszUnicodeBuff" en retour d'appel de cette fct.

Auteur	    : Claude
Créé le	    : 25/02/02
Modifié le  :
------------------------------------------------------- */
int Unicode_Utf8ToWchar(const char* szBuffer, LPWSTR* ppszUnicodeBuff, int nLen)
{
int		nOutBufferSize = 0;
int		nBuffLen = 0;

	// Détermine la longueur de buffer à transcoder
	if (nLen > 0)
		nBuffLen = nLen;
	else
		nBuffLen = strlen(szBuffer) + 1;

	// Premier appel à "MultiByteToWideChar" pour déterminer la taille du buffer transcodé (sans le caractère de fin, car java n'apprécie pas)
	nOutBufferSize = MultiByteToWideChar(CP_UTF8,0, szBuffer,nBuffLen,NULL,0);
	// Allocation de l'espace mémoire nécessaire
	*ppszUnicodeBuff = (LPWSTR)malloc (sizeof(WCHAR)*nOutBufferSize);
	
	if (*ppszUnicodeBuff != NULL)
	{
		ZeroMemory (*ppszUnicodeBuff,sizeof(WCHAR)*nOutBufferSize);

		// Second appel à "MultiByteToWideChar" pour effectuer le transcodage
		nOutBufferSize = MultiByteToWideChar(CP_UTF8,0, szBuffer ,nBuffLen,*ppszUnicodeBuff,nOutBufferSize);
	}
	
	return nOutBufferSize;
}

/* -------------------------------------------------------
Fonction    : Unicode_WcharToMbyte
Description : Trancodage d'un buffer Unicode en buffer MultiByte.. selon le code page passé en argument

Paramètres	: LPWSTR pszUnicodeBuff	: pointeur sur buffer unicode							[in]
			: LPSTR* ppszBuffer		: pointeur de pointeur sur buffer multi-byte transcodé [out]
			  int nCp				: Code page cible [in]									
			  int nLen				: si <= 0, le buffer en entré est NULL Terminated, autrement, on se base sur nLen pour la longueur du buffer [in]									

Retour		: int : longueur finale du buffer char (inclu le zero fin de chaîne si nLen <=0).

Remarque	: Il faut faire un free sur le pointeur "ppszBuffer" en retour d'appel de cette fct.

Auteur	    : Claude
Créé le	    : 24/05/02
Modifié le  :
------------------------------------------------------- */
int Unicode_WcharToMbyte(LPWSTR pszUnicodeBuff,LPSTR* ppszBuffer, int nCp, int nLen)
{
	int		nOutBufferSize = 0;
	int		nBuffLen = 0;

		// Détermine la longueur de buffer à transcoder
		if (nLen > 0)
			nBuffLen = nLen;
		else
			nBuffLen = wcslen(pszUnicodeBuff) + 1;

		// Premier appel à "WideCharToMultiByte" pour déterminer la taille du buffer transcodé
		nOutBufferSize = WideCharToMultiByte(nCp,0,pszUnicodeBuff,nBuffLen,NULL,0,NULL,NULL);

				// Allocation de l'espace mémoire nécessaire
		*ppszBuffer = (LPSTR)malloc (sizeof(char)*nOutBufferSize);
		
		if (*ppszBuffer != NULL)
		{
			ZeroMemory (*ppszBuffer,sizeof(char)*nOutBufferSize);

			// Second appel à "WideCharToMultiByte" pour effectuer le transcodage
			nOutBufferSize = WideCharToMultiByte(nCp,0,pszUnicodeBuff,nBuffLen,*ppszBuffer,nOutBufferSize,NULL,NULL);
		}

		
		return nOutBufferSize;
}

/* -------------------------------------------------------
Fonction    : Unicode_Utf8ToMbyte
Description : Trancodage d'un buffer UTF8 en buffer MultiByte.. selon le code page passé en argument

Paramètres	: LPSTR pszUtf8f		: pointeur sur buffer utf-8								[in]
			: LPSTR* ppszBuffer		: pointeur de pointeur sur buffer multi-byte transcodé [out]
			  int nCp				: Code page cible [in]									
			  int nLen				: si <= 0, le buffer en entré est NULL Terminated, autrement, on se base sur nLen pour la longueur du buffer [in]									

Retour		: int : longueur finale du buffer char (inclu le zero fin de chaîne si nLen <=0).

Remarque	: Il faut faire un free sur le pointeur "ppszBuffer" en retour d'appel de cette fct.

Auteur	    : Claude
Créé le	    : 24/05/02
Modifié le  :
------------------------------------------------------- */
int Unicode_Utf8ToMbyte(LPSTR pszUtf8f, LPSTR* ppszBuffer, int nCp, int nLen)
{
LPWSTR pszUnicodeBuffer   = NULL;
int nRet = 0;
int nLenTrs;
					
	nLenTrs = Unicode_Utf8ToWchar(pszUtf8f, &pszUnicodeBuffer, nLen);
	if(pszUnicodeBuffer)
	{
		nLenTrs = Unicode_WcharToMbyte(pszUnicodeBuffer, ppszBuffer,nCp, nLenTrs);
		if(ppszBuffer)
			nRet = nLenTrs;
		// report correctif ordo 
        free(pszUnicodeBuffer);
	}

	return nRet;
}
#ifdef __cplusplus
	}
#endif