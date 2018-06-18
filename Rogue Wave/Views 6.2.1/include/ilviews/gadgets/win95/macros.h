// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/win95/macros.h
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
// Windows 95 look & feel handlers
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Win95_Macros_H
#define __Ilv_Gadgets_Win95_Macros_H

#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif

#if defined(ILVW95LOOKLIB)
#  define ILVW95LOOKEXPORTED IL_BASEEXPORTED
#  define ILVW95LOOKEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVW95LOOKEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVW95LOOKLIB */

#if !defined(ILVW95LOOKEXPORTED)
#  define ILVW95LOOKEXPORTED IL_BASEIMPORTED
#  define ILVW95LOOKEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVW95LOOKEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILVW95LOOKEXPORTED */

// Static initialization macros
#define ILVW95LOOKMODULEINIT(m) IL_MODULEINIT(m, ILVW95LOOKEXPORTED)
#define ILVW95LOOKMODULETERM(m) IL_MODULETERM(m, ILVW95LOOKEXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvw95look.lib")
#endif

#endif /* __Ilv_Gadgets_Win95_Macros_H */
