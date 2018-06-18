// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/macros.h
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
// General purpose macro definitions for Rogue Wave Views
// --------------------------------------------------------------------------
#ifndef __Ilv_Macros_H
#define __Ilv_Macros_H

#if !defined(IlvVersion)
#define IlvVersion 621
#endif /* !IlvVersion */

#define IlvVersionString "6.2.1"
#define IlvProductName "Rogue Wave Views"

#define IL_MODPREFIX(module) ilv62##module
#define IL_MODINIT(module) ilv62i_##module
#define IL_MODTERM(module) ilv62t_##module
#define IL_ICDECL(module) CIlv62##module

#if defined(ILVDLL) && !defined(IL_DLL)
#define IL_DLL
#endif /* ILVDLL && !IL_DLL*/

#if defined(ILVBUILDLIBS) && !defined(IL_BUILDLIBS)
#define IL_BUILDLIBS
#endif /* ILVBUILDLIBS && !IL_BUILDLIBS */

// For compatibility with Views 3.1
#if (defined(ILVSTD) || defined(ILVMSVCSTD)) && !defined(IL_STD)
#define IL_STD
#endif /* (ILVSTD || ILVMSVCSTD) && !IL_STD */
#if defined(ILVDEBUG) && !defined(IL_DEBUG)
#define IL_DEBUG
#endif /* ILVDEBUG && !IL_DEBUG */

#if !defined(__Il_Macros_H)
#  include <ilog/macros.h>
#endif

#define ILVCALLBACK     IL_CALLBACK
#define ILVHUGE         IL_HUGE
#define ILVVOLATILE     IL_VOLATILE
#if defined(IL_FATFILENAMES)
#define ILVFATFILENAMES
#endif /* IL_FATFILENAMES */

#if defined(IL_STD) && !defined(ILVSTD)
#define ILVSTD
#endif /* IL_STD && !ILVSTD */

#if defined(IL_DLL) && !defined(ILVDLL)
#define ILVDLL
#endif /* IL_DLL && !ILVDLL */

#define ILVSTDPREF IL_STDPREF
#define ILVSTDUSE  IL_STDUSE

// Compilers specifics

// Pre-Views 2.2 flags compatibility
#if defined(SunCC2_1) && !defined(IL_SUNCC2_1)
#define IL_SUNCC2_1
#endif /* SunCC2_1 && !IL_SUNCC2_1 */

// Windows 16 flags
#if defined(WIN16)
#  if !defined(ILVNOSTATICDATA)
#    define ILVNOSTATICDATA
#  endif /* ILVNOSTATICDATA */
#endif /* _WINDOWS && !_Windows */

#if defined(WINDOWS)
typedef IlAny IlvWindowsHandle;
#  if !defined(main) && !defined(ILVKEEPMAIN) && !defined(_CONSOLE)
#    define main IlvMain
#  endif /* !main && !ILVKEEPMAIN && !_CONSOLE */
// --------------------------- MicroSoft C/C++
#  if defined(_MSC_VER)
extern "C" int IlvMain(int argc, char* argv[]);
#    if !defined(ILVNOSTATICDATA)
#      define ILVNOSTATICDATA
#    endif /* ILVNOSTATICDATA */
#  endif /* _MSC_VER */
#endif /* !WINDOWS */

#define ILVBASEEXPORTED IL_BASEEXPORTED
#define ILVBASEIMPORTED IL_BASEIMPORTED
#define ILVBASEEXPORTEDFUNCTION IL_BASEEXPORTEDFUNCTION
#define ILVBASEIMPORTEDFUNCTION IL_BASEIMPORTEDFUNCTION
#define ILVEXPORTEDDEF IL_EXPORTEDDEF
#define ILVEXPORTED IL_EXPORTED
#define ILVIMPORTED IL_IMPORTED

#if defined(ILVDSPLIB)
#  define ILVDSPEXPORTED IL_BASEEXPORTED
#  define ILVDSPEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVDSPEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVDSPEXPORTED */
#  define ILVDSPEXPORTED IL_BASEIMPORTED
#  define ILVDSPEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVDSPEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVDSPEXPORTED */

#if defined(ILVVWSLIB)
#  define ILVVWSEXPORTED IL_BASEEXPORTED
#  define ILVVWSEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVVWSEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVVWSLIB */
#  define ILVVWSEXPORTED IL_BASEIMPORTED
#  define ILVVWSEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVVWSEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVVWSLIB */

typedef IlInt IlvInt;
typedef IlUInt IlvUInt;
typedef IlAny IlvAny;
typedef IlShort IlvShort;
typedef IlUShort IlvUShort;
typedef IlUChar IlvUChar;
typedef IlBoolean IlvBoolean;
typedef IlFloat IlvFloat;
typedef IlDouble IlvDouble;

#if !defined(IlvNil)
#define IlvNil ((IlvAny)0)
#endif /* !IlvNil */

#define IlvTrue IlTrue
#define IlvFalse IlFalse

#define IlvMin IlMin
#define IlvMax IlMax
#define IlvAbs IlAbs

#if defined(IL_RTTI)
#define ILVRTTI
#endif /* IL_RTTI */
#define ILVCAST IL_CAST
#define ILVUNSAFECAST IL_UNSAFECAST
#define ILVDYNAMICCAST IL_DYNAMICCAST
#define ILVCONSTCAST IL_CONSTCAST
#define ILVEXPLICIT IL_EXPLICIT
#define ILVMUTABLE IL_MUTABLE
#define ILVREINTERPRETCAST IL_REINTERPRETCAST

// --------------------------------------------------------------------------
inline long
IlvRoundFloat(IlvFloat d)
{
    return (((d) >= 0.) ? (long)(0.5+(d)) : -(long)(0.5 - (d)));
}

// --------------------------------------------------------------------------
inline long
IlvRoundDouble(IlvDouble d)
{
    return (((d) >= 0.) ? (long)(0.5+(d)) : -(long)(0.5 - (d)));
}

#define ILVSTRING IL_STRING

// --------------------------------------------------------------------------
//    Memory clean up
// --------------------------------------------------------------------------
#if defined(WINDOWS)
ILVDSPEXPORTEDFUNCTION(void) _IlvRegisterFreeCallback(void (*)());
#endif /* WINDOWS */

// --------------------------------------------------------------------------
//    Debug macros
// --------------------------------------------------------------------------
#define ILVASSERT IL_ASSERT
#define ILVTRACE  IL_TRACE

// --------------------------------------------------------------------------
//    Basic Ilv Classes
// --------------------------------------------------------------------------
#if !defined(__IlvPOS)
#define __IlvPOS
typedef IlInt		IlvPos;
typedef IlUInt		IlvDim;
typedef IlShort		IlvDeltaPos; // Delta between coordinates
#if defined(WIN16)
#define IlvMINPOS      LONG_MIN
#define IlvMAXPOS      LONG_MAX
#define IlvMAXDIM      ULONG_MAX
#else  /* !WIN16 */
#define IlvMINPOS      INT_MIN
#define IlvMAXPOS      INT_MAX
#define IlvMAXDIM      UINT_MAX
#endif	/* !WIN16 */
#define IlvMAXDELTAPOS SHRT_MAX
#endif /* !__IlvPos */

// Static initialization macros
#define ILVDSPMODULEINIT(m) IL_MODULEINIT(m, ILVDSPEXPORTED)
#define ILVDSPMODULETERM(m) IL_MODULETERM(m, ILVDSPEXPORTED)

#define ILVVWSMODULEINIT(m) IL_MODULEINIT(m, ILVVWSEXPORTED)
#define ILVVWSMODULETERM(m) IL_MODULETERM(m, ILVVWSEXPORTED)

#define ILVMODULEINIT(m)    IL_MODULEINIT(m, IL_BASEIMPORTED)
#define ILVMODULETERM(m)    IL_MODULETERM(m, IL_BASEIMPORTED)

// 3.0 compatibility
#define IlvDECLAREINITDSPCLASS(m) IL_MODULEINIT(m, ILVDSPEXPORTED);
#define IlvDECLAREINITVWSCLASS(m) IL_MODULEINIT(m, ILVVWSEXPORTED);
#define IlvDECLAREINITCLASS(m)    IL_MODULEINIT(m, IL_BASEIMPORTED);

#define ILVDEFINEINITCLASS(mod, exp)	\
IL_BEGINMODULEINITDEF(mod)exp IL_ENDMODULEINITDEF(mod)

#if defined(ILV_DONT_USE_LIBPRAGMA) && !defined(IL_DONT_USE_LIBPRAGMA)
#  define IL_DONT_USE_LIBPRAGMA
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "winviews.lib")
#  pragma comment(lib, "wsock32.lib")
#  pragma comment(lib, "imm32.lib")
#endif

// --------------------------------------------------------------------------
// Interface macros
// --------------------------------------------------------------------------
#define IlvRegisterInterface(Name,Cl,Itf)			    \
void Cl::init##Name##Interface() const {			    \
static IlBoolean init = IlFalse;				    \
if (!init) { init = IlTrue; static Itf i;			    \
    AddProperty(Ilv##Name##Interface::GetSymbol(), &i); } }

// Default parameters are for X11:
#if defined(VMS) || !(defined(X11) || defined(WINDOWS) || defined(DPS))
#define X11 1
#endif /* !X11 && !WINDOWS && !DPS */

#endif /* !__Ilv_Macros_H */
