/* ****************************************************
    Win Unicode.cpp
    Module utilitaire pour traitement cha�ne Unicode
   **************************************************** */


#include "stdafx.h"

#ifdef __cplusplus
	extern "C" {
#endif




/* -------------------------------------------------------
Fonction    : Unicode_WcharToChar
Description : Trancodage d'une cha�ne Unicode en cha�ne de char

Param�tres	: LPWSTR pszUnicodeBuff	: pointeur sur cha�ne unicode							[in]
			: LPSTR* ppszBuffer		: pointeur de pointeur sur cha�ne char transcod�		[out]

 Retour		: int : longueur finale de la cha�ne (en nombre de char)

Remarque	: Il faut faire un free sur le pointeur "ppszBuffer" en retour d'appel de cette fct.

Auteur	    : Claude
Cr�� le	    : 16/01/02
Modifi� le  :
------------------------------------------------------- */
int Unicode_WcharToChar(LPWSTR pszUnicodeBuff,LPSTR* ppszBuffer)
{
int nOutBufferSize = 0;

	// Premier appel � "WideCharToMultiByte" pour d�terminer la taille du buffer transcod�
	nOutBufferSize = WideCharToMultiByte(CP_ACP,0, pszUnicodeBuff ,wcslen(pszUnicodeBuff)+1,NULL,0,NULL,NULL);

	// Second appel � "WideCharToMultiByte" pour effectuer le transcodage
	nOutBufferSize = WideCharToMultiByte(CP_ACP,0, pszUnicodeBuff ,wcslen(pszUnicodeBuff)+1,*ppszBuffer,nOutBufferSize,NULL,NULL);

	
	return nOutBufferSize;
}

/* -------------------------------------------------------
Fonction    : Unicode_CharToWchar
Description : Trancodage d'une cha�ne de char en Unicode

Param�tres	: const char* aBuffer		: pointeur sur cha�ne � transcoder								[in]
			  LPWSTR* ppszUnicodeBuff	: pointeur de pointeur sur cha�ne transcod� en unicode			[out]

Retour		: int : longueur finale de la cha�ne Unicode (en WCHAR).

Remarque	: Il faut faire un free sur le pointeur "ppszUnicodeBuff" en retour d'appel de cette fct.

Auteur	    : Claude
Cr�� le	    : 16/01/02
Modifi� le  :
------------------------------------------------------- */
int Unicode_CharToWchar(const char* szBuffer, LPWSTR* ppszUnicodeBuff)
{
int nOutBufferSize = 0;

	// Premier appel � "MultiByteToWideChar" pour d�terminer la taille du buffer transcod� (sans le caract�re de fin, car java n'appr�cie pas)
	nOutBufferSize = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED, szBuffer ,strlen(szBuffer)+1,NULL,0);

	// Second appel � "MultiByteToWideChar" pour effectuer le transcodage
	nOutBufferSize = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED, szBuffer ,strlen(szBuffer)+1,*ppszUnicodeBuff,nOutBufferSize);

	
	return nOutBufferSize;
}

/* -------------------------------------------------------
Fonction    : Unicode_WcharToUtf8
Description : Trancodage d'un buffer Unicode en buffer UTF-8 
			  **** A ne plus Utiliser - Utiliser � la place Unicode_WcharToMbyte ****

Param�tres	: LPWSTR pszUnicodeBuff	: pointeur sur buffer unicode								[in]
			: LPSTR* ppszBuffer		: pointeur de pointeur sur buffer char transcod�			[out]
			  int nLen				: si <= 0, le buffer en entr� est NULL Terminated, autrement, on se base sur nLen pour la longueur du buffer [in]									

 Retour		: int : longueur finale du buffer char (inclu le zero fin de cha�ne si nLen <=0).

Remarque	: Il faut faire un free sur le pointeur "ppszBuffer" en retour d'appel de cette fct.

Auteur	    : Claude
Cr�� le	    : 25/02/02
Modifi� le  :
------------------------------------------------------- */
int Unicode_WcharToUtf8(LPWSTR pszUnicodeBuff,LPSTR* ppszBuffer, int nLen)
{
int		nOutBufferSize = 0;
int		nBuffLen = 0;

	// D�termine la longueur de buffer � transcoder
	if (nLen > 0)
		nBuffLen = nLen;
	else
		nBuffLen = wcslen(pszUnicodeBuff) + 1;

	// Premier appel � "WideCharToMultiByte" pour d�terminer la taille du buffer transcod�
	nOutBufferSize = WideCharToMultiByte(CP_UTF8,0,pszUnicodeBuff,nBuffLen,NULL,0,NULL,NULL);

	
	// Second appel � "WideCharToMultiByte" pour effectuer le transcodage
	nOutBufferSize = WideCharToMultiByte(CP_UTF8,0,pszUnicodeBuff,nBuffLen,*ppszBuffer,nOutBufferSize,NULL,NULL);

	return nOutBufferSize;
}

/* -------------------------------------------------------
Fonction    : Unicode_Utf8ToWchar
Description : Trancodage d'un buffer UTF-8 en Unicode

Param�tres	: const char* aBuffer		: pointeur sur buffer � transcoder								[in]
			  LPWSTR* ppszUnicodeBuff	: pointeur de pointeur sur buffer transcod� en unicode			[out]
			  int nLen					 : si <= 0, le buffer en entr� est NULL Terminated, autrement, on se base sur nLen pour la longueur du buffer [in]

Retour		: int : longueur finale du buffer Unicode (en WCHAR).

Remarque	: Il faut faire un free sur le pointeur "ppszUnicodeBuff" en retour d'appel de cette fct.

Auteur	    : Claude
Cr�� le	    : 25/02/02
Modifi� le  :
------------------------------------------------------- */
int Unicode_Utf8ToWchar(const char* szBuffer, LPWSTR* ppszUnicodeBuff, int nLen)
{
int		nOutBufferSize = 0;
int		nBuffLen = 0;

	// D�termine la longueur de buffer � transcoder
	if (nLen > 0)
		nBuffLen = nLen;
	else
		nBuffLen = strlen(szBuffer) + 1;

	// Premier appel � "MultiByteToWideChar" pour d�terminer la taille du buffer transcod� (sans le caract�re de fin, car java n'appr�cie pas)
	nOutBufferSize = MultiByteToWideChar(CP_UTF8,0, szBuffer,nBuffLen,NULL,0);
	// Allocation de l'espace m�moire n�cessaire
	*ppszUnicodeBuff = (LPWSTR)malloc (sizeof(WCHAR)*nOutBufferSize);
	
	if (*ppszUnicodeBuff != NULL)
	{
		ZeroMemory (*ppszUnicodeBuff,sizeof(WCHAR)*nOutBufferSize);

		// Second appel � "MultiByteToWideChar" pour effectuer le transcodage
		nOutBufferSize = MultiByteToWideChar(CP_UTF8,0, szBuffer ,nBuffLen,*ppszUnicodeBuff,nOutBufferSize);
	}
	
	return nOutBufferSize;
}

/* -------------------------------------------------------
Fonction    : Unicode_WcharToMbyte
Description : Trancodage d'un buffer Unicode en buffer MultiByte.. selon le code page pass� en argument

Param�tres	: LPWSTR pszUnicodeBuff	: pointeur sur buffer unicode							[in]
			: LPSTR* ppszBuffer		: pointeur de pointeur sur buffer multi-byte transcod� [out]
			  int nCp				: Code page cible [in]									
			  int nLen				: si <= 0, le buffer en entr� est NULL Terminated, autrement, on se base sur nLen pour la longueur du buffer [in]									

Retour		: int : longueur finale du buffer char (inclu le zero fin de cha�ne si nLen <=0).

Remarque	: Il faut faire un free sur le pointeur "ppszBuffer" en retour d'appel de cette fct.

Auteur	    : Claude
Cr�� le	    : 24/05/02
Modifi� le  :
------------------------------------------------------- */
int Unicode_WcharToMbyte(LPWSTR pszUnicodeBuff,LPSTR* ppszBuffer, int nCp, int nLen)
{
	int		nOutBufferSize = 0;
	int		nBuffLen = 0;

		// D�termine la longueur de buffer � transcoder
		if (nLen > 0)
			nBuffLen = nLen;
		else
			nBuffLen = wcslen(pszUnicodeBuff) + 1;

		// Premier appel � "WideCharToMultiByte" pour d�terminer la taille du buffer transcod�
		nOutBufferSize = WideCharToMultiByte(nCp,0,pszUnicodeBuff,nBuffLen,NULL,0,NULL,NULL);

				// Allocation de l'espace m�moire n�cessaire
		*ppszBuffer = (LPSTR)malloc (sizeof(char)*nOutBufferSize);
		
		if (*ppszBuffer != NULL)
		{
			ZeroMemory (*ppszBuffer,sizeof(char)*nOutBufferSize);

			// Second appel � "WideCharToMultiByte" pour effectuer le transcodage
			nOutBufferSize = WideCharToMultiByte(nCp,0,pszUnicodeBuff,nBuffLen,*ppszBuffer,nOutBufferSize,NULL,NULL);
		}

		
		return nOutBufferSize;
}

/* -------------------------------------------------------
Fonction    : Unicode_Utf8ToMbyte
Description : Trancodage d'un buffer UTF8 en buffer MultiByte.. selon le code page pass� en argument

Param�tres	: LPSTR pszUtf8f		: pointeur sur buffer utf-8								[in]
			: LPSTR* ppszBuffer		: pointeur de pointeur sur buffer multi-byte transcod� [out]
			  int nCp				: Code page cible [in]									
			  int nLen				: si <= 0, le buffer en entr� est NULL Terminated, autrement, on se base sur nLen pour la longueur du buffer [in]									

Retour		: int : longueur finale du buffer char (inclu le zero fin de cha�ne si nLen <=0).

Remarque	: Il faut faire un free sur le pointeur "ppszBuffer" en retour d'appel de cette fct.

Auteur	    : Claude
Cr�� le	    : 24/05/02
Modifi� le  :
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