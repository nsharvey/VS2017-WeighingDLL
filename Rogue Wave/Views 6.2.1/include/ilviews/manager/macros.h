// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/macros.h
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
// Export purpose macro definitions for the manager library.
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Macros_H
#define __Ilv_Manager_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvmgr.lib")
#endif

#if defined(ILVMGRLIB)
#  define ILVMGREXPORTED IL_BASEEXPORTED
#  define ILVMGREXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVMGREXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVMGRLIB */
#  define ILVMGREXPORTED IL_BASEIMPORTED
#  define ILVMGREXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVMGREXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVMGRLIB */

// Static initialization macros
#define ILVMGRMODULEINIT(m) IL_MODULEINIT(m, ILVMGREXPORTED)
#define ILVMGRMODULETERM(m) IL_MODULETERM(m, ILVMGREXPORTED)

#endif /* __Ilv_Manager_Macros_H */
