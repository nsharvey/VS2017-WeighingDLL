// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/windows/macrosadv.h
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
// Windows advanced look & feel handlers
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Windows_Macrosadv_H
#define __Ilv_Gadgets_Windows_Macrosadv_H

#if !defined(__Ilv_Gadgets_Windows_Macros_H)
#  include <ilviews/gadgets/windows/macros.h>
#endif

#if defined(ILVADVWLOOKLIB)
#  define ILVADVWLOOKEXPORTED IL_BASEEXPORTED
#  define ILVADVWLOOKEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVADVWLOOKEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVADVWLOOKLIB */

#if !defined(ILVADVWLOOKEXPORTED)
#  define ILVADVWLOOKEXPORTED IL_BASEIMPORTED
#  define ILVADVWLOOKEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVADVWLOOKEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILVADVWLOOKEXPORTED */

// Static initialization macros
#define ILVADVWLOOKMODULEINIT(m) IL_MODULEINIT(m, ILVADVWLOOKEXPORTED)
#define ILVADVWLOOKMODULETERM(m) IL_MODULETERM(m, ILVADVWLOOKEXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvawlook.lib")
#endif

#endif /* __Ilv_Gadgets_Windows_Macrosadv_H */
