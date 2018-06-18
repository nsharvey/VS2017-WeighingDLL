// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/build/macros.h
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
// Export purpose macro definitions for the build library.
// --------------------------------------------------------------------------
#ifndef __Ilv_Build_Macros_H
#define __Ilv_Build_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvbuild.lib")
#endif

#if defined(ILVBLDLIB)
#  define ILVBLDEXPORTED IL_BASEEXPORTED
#  define ILVBLDEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVBLDEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVBLDLIB */
#  define ILVBLDEXPORTED IL_BASEIMPORTED
#  define ILVBLDEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVBLDEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVBLDLIB */

// Static initialization macros
#define ILVBLDMODULEINIT(m) IL_MODULEINIT(m, ILVBLDEXPORTED)
#define ILVBLDMODULETERM(m) IL_MODULETERM(m, ILVBLDEXPORTED)

// 3.0 compatibility
#define IlvDECLAREINITVARCLASS(m) IL_MODULEINIT(m, ILVBLDEXPORTED);

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvbuild.lib")
#endif

#endif /* __Ilv_Build_Macros_H */
