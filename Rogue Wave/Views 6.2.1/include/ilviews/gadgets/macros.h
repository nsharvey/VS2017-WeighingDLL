// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/macros.h
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
// Defined in library ilvgadgt
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Macros_H
#define __Ilv_Gadgets_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if defined(ILVGDTLIB)
#  define ILVGDTEXPORTED IL_BASEEXPORTED
#  define ILVGDTEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVGDTEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVGDTLIB */

#if !defined(ILVGDTEXPORTED)
#  define ILVGDTEXPORTED IL_BASEIMPORTED
#  define ILVGDTEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVGDTEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILVGDTEXPORTED */

// Static initialization macros
#define ILVGDTMODULEINIT(m) IL_MODULEINIT(m, ILVGDTEXPORTED)
#define ILVGDTMODULETERM(m) IL_MODULETERM(m, ILVGDTEXPORTED)

// 3.0 compatibility
#define IlvDECLAREINITGDTCLASS(m) IL_MODULEINIT(m, ILVGDTEXPORTED);

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvgadgt.lib")
#endif

#endif /* __Ilv_Gadgets_Macros_H */
