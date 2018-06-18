// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/macrosadv.h
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
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Macrosadv_H
#define __Ilv_Gadgets_Macrosadv_H

#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

#if defined(ILVADVGDTLIB)
#  define ILVADVGDTEXPORTED IL_BASEEXPORTED
#  define ILVADVGDTEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVADVGDTEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVADVGDTLIB */

#if !defined(ILVADVGDTEXPORTED)
#  define ILVADVGDTEXPORTED IL_BASEIMPORTED
#  define ILVADVGDTEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVADVGDTEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILVADVGDTEXPORTED */

// Static initialization macros
#define ILVADVGDTMODULEINIT(m) IL_MODULEINIT(m, ILVADVGDTEXPORTED)
#define ILVADVGDTMODULETERM(m) IL_MODULETERM(m, ILVADVGDTEXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvadvgdt.lib")
#endif

#endif /* __Ilv_Gadgets_Macrosadv_H */
