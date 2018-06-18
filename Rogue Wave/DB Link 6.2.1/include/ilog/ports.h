// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/ports.h
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
// Define, based on the current compiler and platform, plateform-independant
// symbols that libraries may rely on.
// --------------------------------------------------------------------------
#ifndef __Il_Ports_H
#define __Il_Ports_H

#if defined(__sun)
#  define IL_SOLARIS_PORT
#  define IL_HAS_WEAK_REFERENCE
#endif /* Solaris */

#if defined(SYSV) && !defined(__SVR4)
#  define __SVR4
#endif /* SYSV && !__SVR4 */

#if defined(_MSC_VER)
#  define IL_MSVC_PORT
#  if (_MSC_VER >= 1200) && !defined(IL_STD)
#    define IL_STD
#  endif /* VC >= 6 */
#endif /* Microsoft Visual C++ */

#if defined(__hpux)
#  define IL_HPUX_PORT
#  if  defined(__HP_aCC) && defined(_HP_NAMESPACE_STD) && !defined(IL_STD)
#    define IL_STD
#  endif /* aC++ && HP_NAMESPACE_STD */
#endif /* HP-UX */

#if defined(linux)
#  define IL_LINUX_PORT
#  if (__GNUC__ >= 3) && !defined(IL_STD)
#    define IL_STD
#  endif /* gcc >= 3 */
#  define IL_HAS_WEAK_REFERENCE
#endif /* Linux */

#if defined(__GNUC__) && \
           ((__GNUC__ >= 3) || ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 96)))
#  define GCC_2_96_OR_MORE
#endif

#if defined(_AIX)
#define IL_AIX_PORT
#  if !defined(IL_STD)
#    define IL_STD
#  endif /* !IL_STD */
#  if !defined(ILJSTDH)
#    define ILJSTDH
#  endif /* !ILJSTDH */
#endif /* AIX */

#if defined(sgi)
#  define IL_SGI_PORT
#  if defined(_STANDARD_C_PLUS_PLUS) && !defined(IL_STD)
#    define IL_STD
#  endif /* CC73 -LANG:std */
#endif /* Sgi */

#if defined(__MINGW32__) || defined(__MINGW64__)
#  define IL_MINGW_PORT
#  if defined(__MINGW64__)
#    define IL_MINGW64_PORT
#  else /* !__MINGW64__ */
#    define IL_MINGW32_PORT
#  endif /* !__MINGW64__ */
#  if !defined(IL_STD)
#    define IL_STD
#  endif /* !IL_STD */
#  if !defined(ILJSTDH)
#    define ILJSTDH
#  endif /* !ILJSTDH */
#endif /* MinGW */

/* Windows 32 flags */
#if defined(_WIN32) || defined(__FLAT__)
/* MS/Windows 32 bits */
#  if !defined(WIN32)
#    define WIN32
#  endif /* !WIN32 */
#  if !defined(WINDOWS)
#    define WINDOWS
#  endif /* !WINDOWS */
#  if !defined(IL_FATFILENAMES)
#    define IL_FATFILENAMES
#  endif /* IL_FATFILENAMES */
#endif /* _WIN32 || __FLAT__*/

#if defined(_WIN64)
/* MS/Windows 64 bits */
#  if !defined(WIN64)
#    define WIN64
#  endif /* !WIN64 */
#  if !defined(WINDOWS)
#    define WINDOWS
#  endif /* !WINDOWS */
#  if !defined(IL_FATFILENAMES)
#    define IL_FATFILENAMES
#  endif /* IL_FATFILENAMES */
#endif /* _WIN64 */

// std::get_new_handler() is a C++11 feature
#define IL_HAS_GET_NEW_HANDLER 
#if defined(IL_LINUX_PORT) || defined(IL_SOLARIS_PORT) \
    || defined(IL_HPUX_PORT) || defined(IL_AIX_PORT) \
    || (defined(IL_MSVC_PORT) && (_MSC_VER < 1700))
#  undef IL_HAS_GET_NEW_HANDLER
#endif /* (All Unix ports) || (MSVC < 2012) */

#endif /* !__Il_Ports_H */
