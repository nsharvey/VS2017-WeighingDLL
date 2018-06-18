// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/macros.h
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
// Common macros and type definitions for Rogue Wave Views C++ products.
// --------------------------------------------------------------------------
#ifndef __Il_Macros_H
#define __Il_Macros_H

/* Version is 6.2.1 */
#if !defined(IlogLibVersion)
#  define IlogLibVersion 621
#endif /* !IlogLibVersion */

#if !defined(__Il_Ports_H)
#  include <ilog/ports.h>
#endif /* !__Il_Ports_H */

#if defined(WINDOWS)
#  if defined(__BORLANDC__)
#    if defined(IL_DLL)
#      if !defined(IL_BASEIMPORTED)
#        define IL_BASEIMPORTED _import
#      endif /* !IL_BASEIMPORTED */
#      if !defined(IL_BASEEXPORTED)
#        define IL_BASEEXPORTED _export
#      endif /* !IL_BASEEXPORTED */
#      if !defined(IL_BASEIMPORTEDFUNCTION)
#        define IL_BASEIMPORTEDFUNCTION(type) type IL_BASEIMPORTED
#      endif /* !IL_BASEIMPORTEDFUNCTION */
#      if !defined(IL_BASEEXPORTEDFUNCTION)
#        define IL_BASEEXPORTEDFUNCTION(type) type IL_BASEEXPORTED
#      endif /* !IL_BASEEXPORTEDFUNCTION */
#    endif /* IL_DLL */
#    if !defined(IL_EXPORTEDDEF)
#      define IL_EXPORTEDDEF(type) type IL_BASEEXPORTED
#    endif /* !IL_EXPORTEDDEF */
#    if !defined(IL_EXPORTFUNCTION)
#      define IL_EXPORTFUNCTION(type, e) type e
#    endif
#  endif /* __BORLANDC__ */
/* --------------------------- MicroSoft C/C++ */
#  if defined(IL_MSVC_PORT)
#    if !defined(_CRT_SECURE_NO_WARNINGS)
#      define IL_NO_UNSECURE_CRT_WARNINGS __pragma(warning(disable:4996))
#    endif
#    if (_MSC_VER >= 1300)
#      define IL_DECLSPEC __declspec
#    else  /* _MSC_VER < 1300 */
#      define IL_DECLSPEC _declspec
#    endif /* _MSC_VER < 1300 */
#    if defined(IL_DLL)
#	if !defined(IL_BASEIMPORTED)
#	  define IL_BASEIMPORTED IL_DECLSPEC(dllimport)
#       endif /* IL_BASEIMPORTED */
#       if !defined(IL_BASEEXPORTED)
#	  define IL_BASEEXPORTED IL_DECLSPEC(dllexport)
#	endif /* !IL_BASEEXPORTED */
#       if !defined(IL_BASEEXPORTEDFUNCTION)
#	  define IL_BASEEXPORTEDFUNCTION(type) IL_BASEEXPORTED type
#	  define IL_BASEIMPORTEDFUNCTION(type) IL_BASEIMPORTED type
#       endif /* !IL_BASEEXPORTEDFUNCTION */
#     if !defined(IL_EXPORTEDDEF)
#	define IL_EXPORTEDDEF(type) IL_BASEEXPORTED type
#     endif /* !IL_EXPORTEDDEF */
#    else  /* !IL_DLL */
#	 if !defined(IL_BASEIMPORTED)
#	   define IL_BASEIMPORTED IL_DECLSPEC()
#        endif /* IL_BASEIMPORTED */
#        if !defined(IL_BASEEXPORTED)
#	   define IL_BASEEXPORTED IL_DECLSPEC()
#	 endif /* !IL_BASEEXPORTED */
#        if !defined(IL_BASEEXPORTEDFUNCTION)
#	   define IL_BASEEXPORTEDFUNCTION(type) IL_BASEEXPORTED type
#	   define IL_BASEIMPORTEDFUNCTION(type) IL_BASEIMPORTED type
#        endif /* !IL_BASEEXPORTEDFUNCTION */
#    endif /* !IL_DLL */
#    if !defined(IL_EXPORTFUNCTION)
#      define IL_EXPORTFUNCTION(type, e) e type
#    endif
#  endif /* _MSC_VER */
#  if !defined(IL_FATFILENAMES)
#    define IL_FATFILENAMES
#  endif /* IL_FATFILENAMES */
#endif /* !WINDOWS */

#if defined(IL_MAINWIN) && defined(IL_FATFILENAMES)
#undef IL_FATFILENAMES
#endif /* IL_MAINWIN && IL_FATFILENAMES */

#if !defined(IL_NO_UNSECURE_CRT_WARNINGS)
#  define IL_NO_UNSECURE_CRT_WARNINGS
#endif /* !IL_NO_UNSECURE_CRT_WARNINGS */
#if !defined(IL_BASEEXPORTED)
#  define IL_BASEEXPORTED
#endif /* !IL_BASEEXPORTED */
#if !defined(IL_BASEIMPORTED)
#  define IL_BASEIMPORTED
#endif /* !IL_BASEIMPORTED */
#if !defined(IL_BASEEXPORTEDFUNCTION)
#  define IL_BASEEXPORTEDFUNCTION(type) type
#endif /* !IL_BASEEXPORTEDFUNCTION */
#if !defined(IL_BASEIMPORTEDFUNCTION)
#  define IL_BASEIMPORTEDFUNCTION(type) type
#endif /* !IL_BASEIMPORTEDFUNCTION */
#if !defined(IL_EXPORTEDDEF)
#  define IL_EXPORTEDDEF(type) type
#endif /* !IL_EXPORTEDDEF */

#if !defined(IL_EXPORTED)
#  define IL_EXPORTED IL_BASEIMPORTED
#endif /* !IL_EXPORTED */
#if !defined(IL_IMPORTED)
#  define IL_IMPORTED IL_BASEIMPORTED
#endif /* !IL_IMPORTED */

#if !defined(IL_CALLBACK)
#  define IL_CALLBACK
#endif /* !IL_CALLBACK */
#if !defined(IL_HUGE)
#  define IL_HUGE
#endif /* !IL_HUGE */

#if !defined(IL_EXPORTFUNCTION)
#  define IL_EXPORTFUNCTION(type, e) type
#endif

// --------------------------------------------------------------------------
// Debug macros
// --------------------------------------------------------------------------
#if defined(IL_DEBUG)
#  define IL_ASSERT(cond, expr) { if (!(cond)) { expr; } }
#  define IL_TRACE(expr) { expr; }
#else  /* !IL_DEBUG */
#  if !defined(NDEBUG)
#    define NDEBUG
#  endif
#  define IL_ASSERT(cond, expr)
#  define IL_TRACE(expr)
#endif /* !IL_DEBUG */

#if (defined(__alpha) && !defined(WIN32)) || \
    (defined(__hpux) && defined(__LP64__)) || \
    (defined(IL_SOLARIS_PORT) && defined(__sparcv9)) || \
    (defined(IL_SOLARIS_PORT) && defined(__x86_64__)) || \
    (defined(linux) && defined(__x86_64__)) || \
    (defined(linux) && defined(__ia64__)) || \
    (defined(_AIX) && defined(__64BIT__))
typedef int IlInt;
typedef unsigned int IlUInt;
#else  /* !(alphaosf||hp64||usparc64||solarisx64||ia64/amd64 linux||aix64) */
typedef long IlInt;
typedef unsigned long IlUInt;
#endif /* !(alphaosf||hp64||usparc64||solarisx64||ia64/amd64 linux||aix64) */

typedef void* IlAny;
typedef short IlShort;
typedef unsigned short IlUShort;
typedef unsigned char IlUChar;

#if !defined(__IlBOOLEAN)
#  define __IlBOOLEAN
#  if defined(__GNUC__) || defined(WINDOWS)
typedef bool IlBoolean;
#    define IlFalse false
#    define IlTrue	true
#  else  /* !__GNUC__ && !WIN32 */
#    if (defined(__alpha) && !defined(WINDOWS)) || \
        (defined(__hpux) && defined(__LP64__)) || \
        (defined(IL_SOLARIS_PORT) && defined(__sparcv9)) || \
        (defined(IL_SOLARIS_PORT) && defined(__x86_64__)) || \
        (defined(_AIX) && defined(__64BIT__))
typedef short IlBoolean;
#    else  /* !(alphaosf || hp64 || ultrasparc64 || aix64) */
typedef int IlBoolean;
#    endif /* !(alphaosf || hp64 || ultrasparc64 || aix64) */
#  define IlFalse ((IlBoolean)0)
#  define IlTrue  ((IlBoolean)1)
#  endif /* !__GNUC__ && !WINDOWS */
#endif /* !__IlBOOLEAN */
#if !defined(__IlFloat)
#  define __IlFloat
typedef float IlFloat;
typedef double IlDouble;
#endif /* __IlFloat */

#if !defined(__IlMIN)
#  define __IlMIN
#  define IlDEFMinMax(T) inline T IlMin(T x, T y) { return (x >= y)?y:x; }\
inline T IlMax(T x, T y) { return (x >= y) ? x : y; }
#define IlDEFAbs(T)	inline T IlAbs(T x) { return (x >= 0)?x:(T)(-x); }

IlDEFMinMax(int)
IlDEFAbs(int)
IlDEFMinMax(unsigned int)
IlDEFMinMax(long)
IlDEFAbs(long)
IlDEFMinMax(unsigned long)
IlDEFMinMax(short)
IlDEFAbs(short)
IlDEFMinMax(unsigned short)
IlDEFMinMax(IlFloat)
IlDEFAbs(IlFloat)
IlDEFMinMax(IlDouble)
IlDEFAbs(IlDouble)
#endif /* !__IlMIN */

#if defined(IL_SOLARIS_PORT) && defined(IL_SUNCC2_1)
#  define IL_VOLATILE
#endif /* Sun C++ 2.1 */
#if !defined(IL_VOLATILE)
#  define IL_VOLATILE volatile
#endif /* !IL_VOLATILE */

/* IL_STRING */
#if defined(__BORLANDC__) || defined(__GNUC__) || defined(_MSC_VER)
#  define IL_STRING(name) ""#name""
#elif defined(IL_SOLARIS_PORT) && defined(IL_SUNCC2_1) /* !BorlandC && !GnuC && !VS */
#  define IL_STRING(name) "name"
#else  /* !sparc_4_2.1 */
#  define IL_STRING(name) #name
#endif  /* !BorlandC && !GnuC && !VS && !sparc_4_2.1*/

// --------------------------------------------------------------------------
// Handling casts
// --------------------------------------------------------------------------
#if (defined(__hpux) && (__cplusplus >= 199707L)) || defined(_CPPRTTI)
#  define IL_RTTI
#endif /* HP aC++ || _CPPRTTI */
#if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530) && !defined(IL_STD)
#  define IL_STD
#endif /* Borland C++ >= 3.0 */
#if defined(__SUNPRO_CC_COMPAT)&&(__SUNPRO_CC_COMPAT >= 5)&&!defined(IL_STD)
#  define IL_STD
#endif /* Sun C++ >= 5.0 */
#if defined(IL_STD) || defined(__LP64__) /* HP 64 bits */
#  define IL_CAST(type, expr) static_cast<type>(expr)
#  if defined(_MSC_VER) && (_MSC_VER >= 1200) && !defined(_CPPRTTI)
#    define IL_DYNAMICCAST(type, expr) IL_CAST(type, expr)
#  else  /* !VisualC++ 6 */
#    define IL_DYNAMICCAST(type, expr) dynamic_cast<type>(expr)
#  endif /* !VisualC++ 6 */
#  define IL_CONSTCAST(type, expr) const_cast<type>(expr)
#  define IL_REINTERPRETCAST(type, expr) reinterpret_cast<type>(expr)
#elif defined(IL_RTTI) /* !IL_STD */
#  define IL_CAST(type, expr) ((type)(expr))
#  define IL_DYNAMICCAST(type, expr) dynamic_cast<type>(expr)
#  define IL_CONSTCAST(type, expr) ((type)(expr))
#  define IL_REINTERPRETCAST(type, expr) IL_CAST(type, expr)
#else  /* !IL_STD && !IL_RTTI */
#  define IL_CAST(type, expr) ((type)(expr))
#  define IL_DYNAMICCAST(type, expr) ((type)(expr))
#  define IL_CONSTCAST(type, expr) ((type)(expr))
#  define IL_REINTERPRETCAST(type, expr) IL_CAST(type, expr)
#endif /* !IL_STD && !IL_RTTI */

#  if (defined(_MSC_VER) && (_MSC_VER >= 1100)) || \
      (defined(__hpux) && (__cplusplus >= 199707L)) || \
      defined(_AIX) || \
      defined(IL_SOLARIS_PORT) || \
      defined(__GNUC__) || \
      defined(__BORLANDC__)
#    define IL_EXPLICIT explicit
#    define IL_MUTABLE  mutable
#    define IL_ACCESSMUTABLE(class, field) field
#  else  /* ! (_MSC_VER||__hpux||_AIX||SOLARIS||__GNUC__||__BORLANDC__) */
#    define IL_EXPLICIT
#    define IL_MUTABLE
#    define IL_ACCESSMUTABLE(class, field) IL_CONSTCAST(class*, this)->field
#  endif /* ! (_MSC_VER||__hpux||_AIX||SOLARIS||__GNUC__||__BORLANDC__) */

#if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530)
#  define __USELOCALES__
#endif

/* For new C++ standard (3.0). */
#if defined(IL_STD)
#  define IL_STDPREF std::
#  define IL_STDUSE using namespace std;
#else
#  if defined(__SUNPRO_CC_COMPAT) && (__SUNPRO_CC_COMPAT >= 5)
#    define IL_STDPREF
#  else
#    define IL_STDPREF ::
#  endif
#  define IL_STDUSE
#endif

#define IL_EMPTYMACRO

#if defined(__SUNPRO_CC_COMPAT) && (__SUNPRO_CC_COMPAT >= 5)
#  define IL_DEFINEFPTRTOANYCAST(FUNCTYPE) \
struct FUNCTYPE##Cast {				\
  FUNCTYPE##Cast(IlAny a)    { v.a = a; }	\
  FUNCTYPE##Cast(FUNCTYPE f) { v.f = f; }	\
  union { FUNCTYPE f; IlAny a; } v;		\
  operator IlAny()    const { return v.a; }	\
  operator FUNCTYPE() const { return v.f; } }
#else
#  define IL_DEFINEFPTRTOANYCAST(FUNCTYPE) \
typedef FUNCTYPE FUNCTYPE##Cast
#endif
#define IL_FPTRTOANYCAST(FUNCTYPE) FUNCTYPE##Cast

// --------------------------------------------------------------------------
// Macros for static initializations
// --------------------------------------------------------------------------
#if defined(IL_BUILDLIBS)
#  define IL_MODULEINIT(m, e) class e IL_ICDECL(m)\
{ public: IL_ICDECL(m)(); static int c; }; \
extern "C" IL_EXPORTFUNCTION(void, IL_EMPTYMACRO e) IL_MODINIT(m)()
#  define IL_MODULETERM(m, e) extern "C" {\
    IL_EXPORTFUNCTION(void, IL_EMPTYMACRO e) IL_MODINIT(m)();\
    IL_EXPORTFUNCTION(void, IL_EMPTYMACRO e) IL_MODTERM(m)();\
}\
class e IL_ICDECL(m){\
public: IL_ICDECL(m)(); ~IL_ICDECL(m)(); static int c;}
#else  /* !IL_BUILDLIBS */
#  define IL_MODULEINIT(m, e) \
extern "C" IL_EXPORTFUNCTION(void, IL_EMPTYMACRO e) IL_MODINIT(m)();\
static class e IL_ICDECL(m)\
{\
  public:\
    IL_ICDECL(m)();\
    static int c;\
} IL_MODPREFIX(m)
#  define IL_MODULETERM(m, e) extern "C" {\
    IL_EXPORTFUNCTION(void, IL_EMPTYMACRO e) IL_MODINIT(m)();\
    IL_EXPORTFUNCTION(void, IL_EMPTYMACRO e) IL_MODTERM(m)();\
};\
static class e IL_ICDECL(m)\
{\
  public:\
    IL_ICDECL(m)();\
    ~IL_ICDECL(m)();\
    static int c;\
} IL_MODPREFIX(m)
#endif /* !IL_BUILDLIBS */

#define IL_BEGINMODULEINITDEF(mod)	\
void IL_MODINIT(mod)(){if(!IL_ICDECL(mod)::c++){
#define IL_ENDMODULEINITDEF(mod)	\
}}int IL_ICDECL(mod)::c=0;IL_ICDECL(mod)::IL_ICDECL(mod)(){IL_MODINIT(mod)();}

#define IL_BEGINMODULETERMDEF(mod)	\
void IL_MODTERM(mod)(){if(!--IL_ICDECL(mod)::c){
#define IL_ENDMODULETERMDEF(mod)	\
}}IL_ICDECL(mod)::~IL_ICDECL(mod)(){IL_MODTERM(mod)();}

#if defined(ILOGLIB)
#  define ILOG_EXPORTED IL_BASEEXPORTED
#  define ILOG_EXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILOG_EXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILOGLIB */
#  define ILOG_EXPORTED IL_BASEIMPORTED
#  define ILOG_EXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILOG_EXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILOGLIB */

/* Static initialization macros */
#define ILOGMODULEINIT(m) IL_MODULEINIT(m, ILOG_EXPORTED)
#define ILOGMODULETERM(m) IL_MODULETERM(m, ILOG_EXPORTED)

#if !defined(IL_BUILDLIBS) && defined(_MSC_VER) && \
    !defined(IL_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilog.lib")
#endif /* Use Lib pragma */

#if !defined(IL_PTRCASTS) && defined(__cplusplus)
#  define IL_PTRCASTS
#  if defined(WIN64)||(defined(_MSC_VER)&&(_MSC_VER >= 1300)) /* intptr_t */
#    if defined(IL_STD)
#      include <cstddef>
#    else  /* !IL_STD */
#      include <stddef.h>
#    endif /* !IL_STD */
typedef intptr_t	IlIntPtr;
typedef uintptr_t	IlUIntPtr;
#  else /* !intptr_t */
typedef long		IlIntPtr;
typedef unsigned long	IlUIntPtr;
#  endif /* !intptr_t */

inline IlIntPtr
IlCastIlAnyToIlIntPtr(IlAny v)
{
    return IL_REINTERPRETCAST(IlIntPtr, v);
}
inline IlUIntPtr
IlCastIlAnyToIlUIntPtr(IlAny v)
{
    return IL_REINTERPRETCAST(IlUIntPtr, v);
}
inline IlAny
IlCastIlIntPtrToIlAny(IlIntPtr v)
{
    return IL_REINTERPRETCAST(IlAny, v);
}
inline IlAny
IlCastIlUIntPtrToIlAny(IlUIntPtr v)
{
    return IL_REINTERPRETCAST(IlAny, v);
}
inline char
IlCastIlAnyToChar(IlAny v)
{
    return IL_CAST(char, IlCastIlAnyToIlIntPtr(v));
}
inline IlUChar
IlCastIlAnyToIlUChar(IlAny v)
{
    return IL_CAST(IlUChar, IlCastIlAnyToIlUIntPtr(v));
}
inline IlShort
IlCastIlAnyToIlShort(IlAny v)
{
    return IL_CAST(IlShort, IlCastIlAnyToIlIntPtr(v));
}
inline IlUShort
IlCastIlAnyToIlUShort(IlAny v)
{
    return IL_CAST(IlUShort, IlCastIlAnyToIlUIntPtr(v));
}
inline int
IlCastIlAnyToInt(IlAny v)
{
    return IL_CAST(int, IlCastIlAnyToIlIntPtr(v));
}
inline IlInt
IlCastIlAnyToIlInt(IlAny v)
{
    return IL_CAST(IlInt, IlCastIlAnyToIlIntPtr(v));
}
inline IlUInt
IlCastIlAnyToIlUInt(IlAny v)
{
    return IL_CAST(IlUInt, IlCastIlAnyToIlUIntPtr(v));
}
inline IlAny
IlCastCharToIlAny(char v)
{
    return IlCastIlIntPtrToIlAny(IL_CAST(IlIntPtr, v));
}
inline IlAny
IlCastIlUCharToIlAny(IlUChar v)
{
    return IlCastIlUIntPtrToIlAny(IL_CAST(IlUIntPtr, v));
}
inline IlAny
IlCastIlShortToIlAny(IlShort v)
{
    return IlCastIlIntPtrToIlAny(IL_CAST(IlIntPtr, v));
}
inline IlAny
IlCastIlUShortToIlAny(IlUShort v)
{
    return IlCastIlUIntPtrToIlAny(IL_CAST(IlUIntPtr, v));
}
inline IlAny
IlCastIlIntToIlAny(IlInt v)
{
    return IlCastIlIntPtrToIlAny(IL_CAST(IlIntPtr, v));
}
inline IlAny
IlCastIntToIlAny(int v)
{
    return IlCastIlIntPtrToIlAny(IL_CAST(IlIntPtr, v));
}
inline IlAny
IlCastIlUIntToIlAny(IlUInt v)
{
    return IlCastIlUIntPtrToIlAny(IL_CAST(IlUIntPtr, v));
}

inline IlBoolean
IlIsNear0(IlDouble v, IlDouble precision) { return (IlAbs(v) < precision); }
#  define IlEpsilon 0.000000000001
#  define IL_NEAR0(v) (IlAbs(v) < IlEpsilon)
#  define IL_NEAR1(v) (IlAbs((v) - 1.) < IlEpsilon)
#endif /* IL_PTRCASTS && __cplusplus */

#endif  /* __Il_Macros_H */
