// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/css/macros.h
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
// Defined in library ilvcss
// --------------------------------------------------------------------------
#ifndef __Ilv_Css_Macros_H
#define __Ilv_Css_Macros_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif

#if defined(ILVCSSLIB)
#  define ILVCSSEXPORTED IL_BASEEXPORTED
#  define ILVCSSEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVCSSEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVCSSLIB */

#if !defined(ILVCSSEXPORTED)
#  define ILVCSSEXPORTED IL_BASEIMPORTED
#  define ILVCSSEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVCSSEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVCSSEXPORTED */

// Static initialization macros
#define ILVCSSMODULEINIT(m) IL_MODULEINIT(m, ILVCSSEXPORTED)
#define ILVCSSMODULETERM(m) IL_MODULETERM(m, ILVCSSEXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvcss.lib")
#endif

#endif /* !__Ilv_Css_Macros_H */
