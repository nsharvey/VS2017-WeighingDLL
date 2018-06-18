// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/macros.h
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
// Export purpose macro definitions for the printing library.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_Macros_H
#define __Ilv_Printing_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvprint.lib")
#endif

#if defined(ILVPRINTINGLIB)
#  define ILVPRINTINGEXPORTED IL_BASEEXPORTED
#  define ILVPRINTINGEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVPRINTINGEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVPRINTINGLIB */
#  define ILVPRINTINGEXPORTED IL_BASEIMPORTED
#  define ILVPRINTINGEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVPRINTINGEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVPRINTINGLIB */

// Static initialization macros
#define ILVPRINTINGMODULEINIT(m) IL_MODULEINIT(m, ILVPRINTINGEXPORTED)
#define ILVPRINTINGMODULETERM(m) IL_MODULETERM(m, ILVPRINTINGEXPORTED)

#endif /* __Ilv_Printing_Macros_H */
