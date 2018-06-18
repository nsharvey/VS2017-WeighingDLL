// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/grapher/macros.h
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
// Declaration of macros used for exporting appgrapher symbols
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Grapher_Macros_H)
#define __Ilv_Appframe_Grapher_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvappgrapher.lib")
#endif

// --------------------------------------------------------------------------
#if defined(ILVDVGRAPHERLIB)
#  define ILVDVGRAPHEREXPORTED IL_BASEEXPORTED
#  define ILVDVGRAPHEREXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVDVGRAPHEREXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVDVGRAPHERLIB */

#if !defined(ILVDVGRAPHEREXPORTED)
#  define ILVDVGRAPHEREXPORTED IL_BASEIMPORTED
#  define ILVDVGRAPHEREXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVDVGRAPHEREXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILVDVGRAPHEREXPORTED */

// Static initialization macros
#define ILVDVGRAPHERMODULEINIT(m) IL_MODULEINIT(dvgrp_##m, ILVDVGRAPHEREXPORTED)
#define ILVDVGRAPHERMODULETERM(m) IL_MODULETERM(dvgrp_##m, ILVDVGRAPHEREXPORTED)

// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Grapher_Macros_H */
