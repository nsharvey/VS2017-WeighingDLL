// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/util.h
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
// Declaration of global utility functions
// --------------------------------------------------------------------------
#ifndef __IlvSt_Util_H
#define __IlvSt_Util_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_Memory_H)
#  include <ilviews/base/memory.h>
#endif

#ifdef _WINDOWS
#include <assert.h>
#endif

#if defined(ILVSTD)
#include <cstdlib>
#include <cstring>
#else  /* !ILVSTD */
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#endif /* !ILVSTD */

class IlvDisplay;
class IlString;
class IlPathName;

// --------------------------------------------------------------------------
#if defined(ILVSTLIB)
#define ILVSTEXPORTEDDEF ILVBASEEXPORTED
#define ILVSTEXPORTEDFUNC(type) ILVBASEEXPORTEDFUNCTION(type)
#else
#define ILVSTEXPORTEDDEF ILVBASEIMPORTED
#define ILVSTEXPORTEDFUNC(type) ILVBASEIMPORTEDFUNCTION(type)
#endif
#define ILVSTUDIOCLASS ILVSTEXPORTEDDEF
#define ILVSTEXPORTEDVAR(type) ILVSTEXPORTEDDEF type
#define IlvDECLAREINITSTUDIOCLASS(m) IL_MODULEINIT(m ,ILVSTUDIOCLASS);

#if defined(ILVSTGRAPHERLIB)
#define ILVSTGRAPHEREXPORTEDDEF ILVBASEEXPORTED
#define ILVSTGRAPHEREXPORTEDFUNC(type) ILVBASEEXPORTEDFUNCTION(type)
#else
#define ILVSTGRAPHEREXPORTEDDEF ILVBASEIMPORTED
#define ILVSTGRAPHEREXPORTEDFUNC(type) ILVBASEIMPORTEDFUNCTION(type)
#endif
#define ILVSTGRAPHERCLASS ILVSTGRAPHEREXPORTEDDEF
#define ILVSTGRAPHEREXPORTEDVAR(type) ILVSTGRAPHEREXPORTEDDEF type
#define IlvDECLAREINITSTGRAPHERCLASS(m) IL_MODULEINIT(m, ILVSTGRAPHERCLASS);

#if defined(ILVSTGADGETLIB)
#define ILVSTGADGETEXPORTEDDEF ILVBASEEXPORTED
#define ILVSTGADGETEXPORTEDFUNC(type) ILVBASEEXPORTEDFUNCTION(type)
#else
#define ILVSTGADGETEXPORTEDDEF ILVBASEIMPORTED
#define ILVSTGADGETEXPORTEDFUNC(type) ILVBASEIMPORTEDFUNCTION(type)
#endif
#define ILVSTGADGETCLASS ILVSTGADGETEXPORTEDDEF
#define ILVSTGADGETEXPORTEDVAR(type) ILVSTGADGETEXPORTEDDEF type
#define IlvDECLAREINITSTGADGETCLASS(m) IL_MODULEINIT(m, ILVSTGADGETCLASS);

#if defined(ILVSTAPPLILIB)
#define ILVSTAPPLIEXPORTEDDEF ILVBASEEXPORTED
#define ILVSTAPPLIEXPORTEDFUNC(type) ILVBASEEXPORTEDFUNCTION(type)
#else
#define ILVSTAPPLIEXPORTEDDEF ILVBASEIMPORTED
#define ILVSTAPPLIEXPORTEDFUNC(type) ILVBASEIMPORTEDFUNCTION(type)
#endif
#define ILVSTAPPLICLASS ILVSTAPPLIEXPORTEDDEF
#define ILVSTAPPLIEXPORTEDVAR(type) ILVSTAPPLIEXPORTEDDEF type
#define IlvDECLAREINITSTAPPLICLASS(m) IL_MODULEINIT(m, ILVSTAPPLICLASS);

#if defined(ILVSTGENEXLIB)
#define ILVSTGENEXEXPORTEDDEF ILVBASEEXPORTED
#define ILVSTGENEXEXPORTEDFUNC(type) ILVBASEEXPORTEDFUNCTION(type)
#else
#define ILVSTGENEXEXPORTEDDEF ILVBASEIMPORTED
#define ILVSTGENEXEXPORTEDFUNC(type) ILVBASEIMPORTEDFUNCTION(type)
#endif
#define ILVSTGENEXCLASS ILVSTGENEXEXPORTEDDEF
#define ILVSTGENEXEXPORTEDVAR(type) ILVSTGENEXEXPORTEDDEF type
#define IlvDECLAREINITSTGENEXCLASS(m) IL_MODULEINIT(m, ILVSTGENEXCLASS);

#if defined(ILVSTVARLIB)
#define ILVSTVAREXPORTEDDEF ILVBASEEXPORTED
#define ILVSTVAREXPORTEDFUNC(type) ILVBASEEXPORTEDFUNCTION(type)
#else
#define ILVSTVAREXPORTEDDEF ILVBASEIMPORTED
#define ILVSTVAREXPORTEDFUNC(type) ILVBASEIMPORTEDFUNCTION(type)
#endif
#define ILVSTVARCLASS ILVSTVAREXPORTEDDEF
#define ILVSTVAREXPORTEDVAR(type) ILVSTVAREXPORTEDDEF type
#define IlvDECLAREINITSTVARCLASS(m) IL_MODULEINIT(m, ILVSTVARCLASS);

#if defined(ILVSTJSLIB)
#define ILVSTJSEXPORTEDDEF ILVBASEEXPORTED
#define ILVSTJSEXPORTEDFUNC(type) ILVBASEEXPORTEDFUNCTION(type)
#else
#define ILVSTJSEXPORTEDDEF ILVBASEIMPORTED
#define ILVSTJSEXPORTEDFUNC(type) ILVBASEIMPORTEDFUNCTION(type)
#endif
#define ILVSTJSCLASS ILVSTJSEXPORTEDDEF
#define ILVSTJSEXPORTEDVAR(type) ILVSTJSEXPORTEDDEF type
#define IlvDECLAREINITSTJSCLASS(m) IL_MODULEINIT(m, ILVSTJSCLASS);

#define ILVSTBF
#if defined(ILVSTDEBUG) && defined(_WINDOWS)
    #define IlvStAssert(exp) assert(exp)
#else
    #define IlvStAssert(exp)
#endif

class IlvView;
class IlvStStringArray;
class IlvStString;
// --------------------------------------------------------------------------
extern ILVSTEXPORTEDFUNC(IlInt) IlvStGetVersion();
extern ILVSTEXPORTEDFUNC(IlInt) IlvStGetInternalReference();
extern ILVSTEXPORTEDFUNC(IlInt) IlvStSetInternalReference(IlInt);
extern ILVSTEXPORTEDFUNC(const char*) IlvStDate();
extern ILVSTEXPORTEDFUNC(char*) IlvStSetString(char*&, const char*);
extern ILVSTEXPORTEDFUNC(IlBoolean) IlvStEqual(const char*, const char*);
extern ILVSTEXPORTEDFUNC(IlBoolean) IlvStIsBlank(const char*);
extern ILVSTEXPORTEDFUNC(IlBoolean) IlvStIsAnIdentifier(const char*);
extern ILVSTEXPORTEDFUNC(char*) IlvStAppend(const char*, const char*, const char*);
extern ILVSTEXPORTEDFUNC(const char*) IlvStStrNoMnemonic(char* dst, const char*);
extern ILVSTEXPORTEDFUNC(void) IlvStSortStrings(const char**, int);
extern ILVSTEXPORTEDFUNC(void) IlvStTokenize(const char* str,
			  const char* seps,
			  IlvStStringArray& result);
extern ILVSTEXPORTEDFUNC(IlString) IlvStMakeFilePath(const char* dir,
						     const char* name,
						     const char* ext);
extern ILVSTEXPORTEDFUNC(IlBoolean) IlvStIsCIdentifier(const char*);
extern ILVSTEXPORTEDFUNC(IlBoolean) IlvStIsCPPIdentifier(const char*);
extern ILVSTEXPORTEDFUNC(void) IlvStMoveToMouse(IlvView* cont);
extern ILVSTEXPORTEDFUNC(void) IlvStCenterScreen(IlvView* cont);
extern ILVSTEXPORTEDFUNC(void) IlvStCheckScreenBorders(IlvView* cont);
extern ILVSTEXPORTEDFUNC(void) IlvStFormatString(IlvDisplay*,
						 IlvStString&,
						 const char* msg, ...);

extern ILVSTEXPORTEDFUNC(IlBoolean) IlvStCheckOutputFile(const char* fname);
extern ILVSTEXPORTEDFUNC(IlBoolean) IlvStCheckOutputFile(const IlPathName&);

// --------------------------------------------------------------------------
inline IlAny IlvStMalloc(
#if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530)
			  std::
#endif /* Borland C++ Builder 3.0 */
			  size_t size)
{ return
#if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530)
      std::
#endif /* Borland C++ Builder 3.0 */
    malloc(size); }

// --------------------------------------------------------------------------
inline IlAny IlvStRealloc(IlAny ptr,
#if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530)
			   std::
#endif /* Borland C++ Builder 3.0 */
			   size_t size)
{ return
#if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530)
      std::
#endif /* Borland C++ Builder 3.0 */
    realloc((char*)ptr, size); }

// --------------------------------------------------------------------------
inline void IlvStFree(IlAny pointer)
{
#if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530)
    std::
#endif /* Borland C++ Builder 3.0 */
	free((char*) pointer); }

// --------------------------------------------------------------------------
inline void* IlvStMemMove(void* dst,
			  const void* src,
#if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530)
			  std::
#endif /* Borland C++ Builder 3.0 */
			  size_t sz)
{
    return IlvMemMove(dst, (void*)src, (IlUInt)sz);
}

#endif /* !__IlvSt_Util_H */
