// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/macrosadv.h
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
// Defined in library ilvamlook
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Motif_Macrosadv_H
#define __Ilv_Gadgets_Motif_Macrosadv_H

#if !defined(__Ilv_Gadgets_Motif_Macros_H)
#include <ilviews/gadgets/motif/macros.h>
#endif

#if defined(ILVADVMLOOKLIB)
#  define ILVADVMLOOKEXPORTED IL_BASEEXPORTED
#  define ILVADVMLOOKEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVADVMLOOKEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVADVMLOOKLIB */

#if !defined(ILVADVMLOOKEXPORTED)
#  define ILVADVMLOOKEXPORTED IL_BASEIMPORTED
#  define ILVADVMLOOKEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVADVMLOOKEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILVADVMLOOKEXPORTED */

// Static initialization macros
#define ILVADVMLOOKMODULEINIT(m) IL_MODULEINIT(m, ILVADVMLOOKEXPORTED)
#define ILVADVMLOOKMODULETERM(m) IL_MODULETERM(m, ILVADVMLOOKEXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvamlook.lib")
#endif

#endif /* __Ilv_Gadgets_Motif_Macrosadv_H */
