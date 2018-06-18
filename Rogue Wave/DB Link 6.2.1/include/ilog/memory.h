// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/memory.h
// --------------------------------------------------------------------------
//
// Licensed Materials - Property of Rogue Wave Software, Inc.
// (c) Copyright Rogue Wave Software, Inc. 2012, 2018
// (c) Copyright IBM Corp. 2009, 2011
// (c) Copyright ILOG 1992, 2009
// All Rights Reserved.
//
// Note to U.S. Government Users Restricted Rights:
// The Software and Documentation were developed at private expense and
// are "Commercial Items" as that term is defined at 48 CFR 2.101,
// consisting of "Commercial Computer Software" and
// "Commercial Computer Software Documentation", as such terms are
// used in 48 CFR 12.212 or 48 CFR 227.7202-1 through 227.7202-4,
// as applicable.
//
// --------------------------------------------------------------------------
// Declaration of memory management functions
// --------------------------------------------------------------------------
#ifndef __Il_Memory_H
#define __Il_Memory_H

#if !defined(__Il_Macros_H)
#  include <ilog/macros.h>
#endif

#if defined(IL_STD)
#  include <cstddef>
#  include <cstring>
#else  /* ! IL_STD */
#  include <stddef.h>
#  include <string.h>
#endif /* ! IL_STD */

#if (defined(IL_MSVC_PORT) && (_MSC_VER < 1300)) || /* msvc6. */ \
    (defined(IL_SGI_PORT) && defined(_STANDARD_C_PLUS_PLUS)) /* sgi */
// <cstddef> does not define size_t in the std namespace
ILOG_EXPORTEDFUNCTION(void*) IlMalloc(size_t nBytes);
ILOG_EXPORTEDFUNCTION(void*) IlRealloc(void* block, size_t);
ILOG_EXPORTEDFUNCTION(void*) IlMemMove(void*, const void*, size_t);
#else  /* !msvc6 && !sgi */
ILOG_EXPORTEDFUNCTION(void*) IlMalloc(IL_STDPREF size_t nBytes);
ILOG_EXPORTEDFUNCTION(void*) IlRealloc(void* block, IL_STDPREF size_t);
ILOG_EXPORTEDFUNCTION(void*) IlMemMove(void*,const void*, IL_STDPREF size_t);
#endif /* !msvc6 && !sgi */
ILOG_EXPORTEDFUNCTION(void)  IlFree(void* block);
#define IL_MALLOC(type, n)    ((type*)IlMalloc((n)*sizeof(type)))
#define IL_REALLOC(type, array, n) \
((type*)IlRealloc((IlAny)(array), (n)*sizeof(type)))

#if defined(WINDOWS)
#  if defined(IL_MSVC_PORT) && (_MSC_VER >= 1400)
#    define IL_STRCASECMP(s1, s2) _stricmp(s1, s2)
#    define IL_STRNCASECMP(s1, s2, n) _strnicmp(s1, s2, n)
#  else /* MSVC < 2003 */
#    define IL_STRCASECMP(s1, s2) stricmp(s1, s2)
#    define IL_STRNCASECMP(s1, s2, n) strnicmp(s1, s2, n)
#  endif  /* x86_.net2003_7.1 and lower */
#else  /* !WINDOWS */
#  if defined(sun) && !defined(__SVR4)
#    if defined(IL_SUNCC2_1)
#       define IL_STRCASECMP(s1, s2) strcasecmp((char*)(s1), (char*)(s2))
#       define IL_STRNCASECMP(s1,s2,n) strncasecmp((char*)(s1),(char*)(s2),n)
#    else
#       define IL_STRCASECMP(s1, s2) strcasecmp((char*)(s1), s2)
#       define IL_STRNCASECMP(s1, s2, n) strncasecmp((char*)(s1), s2, n)
#    endif /* !IL_SUNCC2_1 */
#  else
#    define IL_STRCASECMP(s1, s2) strcasecmp(s1, s2)
#    define IL_STRNCASECMP(s1, s2, n) strncasecmp(s1, s2, n)
#  endif /* ! (sun && !__SVR4) */
#endif /* !WINDOWS */
#if defined(IL_AIX_PORT) || defined(sinix)
#  include <sys/types.h>
extern "C" {
    int strcasecmp(const char *, const char *);
    int strncasecmp(const char *, const char *, size_t);
}
#endif /* _AIX || sinix */

inline char*
IlCopyString(const char* string, IlBoolean zeroIfEmpty = IlTrue)
{
    if (string) {        	// Not NULL
	if (string[0]) { 	// Not empty
#if defined(IL_SOLARIS_PORT)
	    return std::strcpy(new char[std::strlen(string)+1], string);
#else  /* !IL_SOLARIS_PORT */
#  if defined(IL_MSVC_PORT) && !defined(_CRT_SECURE_NO_WARNINGS)
     // Temporary remove unsecure CRT call warning 
#    pragma warning(push)
#    pragma warning(disable: 4996)
#  endif
	    return strcpy(new char[strlen(string)+1], string);
#  if defined(IL_MSVC_PORT) && !defined(_CRT_SECURE_NO_WARNINGS)
#    pragma warning(pop)
#  endif
#endif /* !IL_SOLARIS_PORT */
	} else if (zeroIfEmpty) {
	    return 0;
	} else {	// Return an empty string
	    char* empty = new char[1];
	    *empty = 0;
	    return empty;
	}
    } else {		// Input is NULL
	return 0;
    }
}

#endif /* !__Il_Memory_H */
