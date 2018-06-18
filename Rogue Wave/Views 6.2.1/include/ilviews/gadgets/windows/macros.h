// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/windows/macros.h
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
// Windows look & feel handlers
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Windows_Macros_H
#define __Ilv_Gadgets_Windows_Macros_H

#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif

#if defined(ILVWLOOKLIB)
#  define ILVWLOOKEXPORTED IL_BASEEXPORTED
#  define ILVWLOOKEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVWLOOKEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVWLOOKLIB */

#if !defined(ILVWLOOKEXPORTED)
#  define ILVWLOOKEXPORTED IL_BASEIMPORTED
#  define ILVWLOOKEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVWLOOKEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILVWLOOKEXPORTED */

// Static initialization macros
#define ILVWLOOKMODULEINIT(m) IL_MODULEINIT(m, ILVWLOOKEXPORTED)
#define ILVWLOOKMODULETERM(m) IL_MODULETERM(m, ILVWLOOKEXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvwlook.lib")
#endif

#endif /* __Ilv_Gadgets_Windows_Macros_H */
