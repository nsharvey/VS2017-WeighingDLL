// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadmgr/macros.h
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
// Export purpose macro definitions for the gadmgr library.
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadmgr_Macros_H
#define __Ilv_Gadmgr_Macros_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

#if defined(ILVGDTMGRLIB)
#  define ILVGDTMGREXPORTED IL_BASEEXPORTED
#  define ILVGDTMGREXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVGDTMGREXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVGDTMGRLIB */
#  define ILVGDTMGREXPORTED IL_BASEIMPORTED
#  define ILVGDTMGREXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVGDTMGREXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVGDTMGRLIB */

// Static initialization macros
#define ILVGDTMGRMODULEINIT(m) IL_MODULEINIT(m, ILVGDTMGREXPORTED)
#define ILVGDTMGRMODULETERM(m) IL_MODULETERM(m, ILVGDTMGREXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvgadmgr.lib")
#endif

#endif /* __Ilv_Gadmgr_Macros_H */
