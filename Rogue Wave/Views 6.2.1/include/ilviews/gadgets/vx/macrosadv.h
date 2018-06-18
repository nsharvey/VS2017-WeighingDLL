// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/vx/macrosadv.h
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
// VX advanced look & feel handlers
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Vx_Macrosadv_H
#define __Ilv_Gadgets_Vx_Macrosadv_H

#if !defined(__Ilv_Gadgets_Vx_Macros_H)
#  include <ilviews/gadgets/vx/macros.h>
#endif

#if defined(ILVADVVXLOOKLIB)
#  define ILVADVVXLOOKEXPORTED IL_BASEEXPORTED
#  define ILVADVVXLOOKEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVADVVXLOOKEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVADVVXLOOKLIB */

#if !defined(ILVADVVXLOOKEXPORTED)
#  define ILVADVVXLOOKEXPORTED IL_BASEIMPORTED
#  define ILVADVVXLOOKEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVADVVXLOOKEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILVADVVXLOOKEXPORTED */

// Static initialization macros
#define ILVADVVXLOOKMODULEINIT(m) IL_MODULEINIT(m, ILVADVVXLOOKEXPORTED)
#define ILVADVVXLOOKMODULETERM(m) IL_MODULETERM(m, ILVADVVXLOOKEXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvavxlook.lib")
#endif

#endif /* __Ilv_Gadgets_Vx_Macrosadv_H */
