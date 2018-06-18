// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/macros.h
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
// Declaration of filters macros 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Macros_H
#define __Ilv_Bitmaps_Filters_Macros_H

#ifndef __Ilv_Macros_H
#include <ilviews/macros.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvbmpflt.lib")
#endif

#if defined(ILVFLTLIB)
#  define ILVFLTEXPORTED IL_BASEEXPORTED
#  define ILVFLTEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVFLTEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVFLTLIB */
#  define ILVFLTEXPORTED IL_BASEIMPORTED
#  define ILVFLTEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVFLTEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVFLTLIB */

// Static initialization macros
#define ILVFLTMODULEINIT(m) IL_MODULEINIT(m, ILVFLTEXPORTED)
#define ILVFLTMODULETERM(m) IL_MODULETERM(m, ILVFLTEXPORTED)

#endif /* __Ilv_Bitmaps_Filters_Macros_H */
