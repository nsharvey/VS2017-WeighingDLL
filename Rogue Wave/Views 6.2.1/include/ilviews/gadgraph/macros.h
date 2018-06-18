// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgraph/macros.h
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
// Export purpose macro definitions for the gadgraph library.
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgraph_Macros_H
#define __Ilv_Gadgraph_Macros_H

#if !defined(__Ilv_Grapher_Macros_H)
#include <ilviews/grapher/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

#if defined(ILVGDTGRAPHLIB)
#  define ILVGDTGRAPHEXPORTED IL_BASEEXPORTED
#  define ILVGDTGRAPHEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVGDTGRAPHEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVGDTGRAPHLIB */
#  define ILVGDTGRAPHEXPORTED IL_BASEIMPORTED
#  define ILVGDTGRAPHEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVGDTGRAPHEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVGDTGRAPHLIB */

// Static initialization macros
#define ILVGDTGRAPHMODULEINIT(m) IL_MODULEINIT(m, ILVGDTGRAPHEXPORTED)
#define ILVGDTGRAPHMODULETERM(m) IL_MODULETERM(m, ILVGDTGRAPHEXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvgadgraph.lib")
#endif

#endif /* __Ilv_Gadgraph_Macros_H */
