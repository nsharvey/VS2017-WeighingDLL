// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadmgr/macrosadv.h
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
#ifndef __Ilv_Gadmgr_Macrosadv_H
#define __Ilv_Gadmgr_Macrosadv_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

#if defined(ILVADVGDTMGRLIB)
#  define ILVADVGDTMGREXPORTED IL_BASEEXPORTED
#  define ILVADVGDTMGREXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVADVGDTMGREXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVADVGDTMGRLIB */
#  define ILVADVGDTMGREXPORTED IL_BASEIMPORTED
#  define ILVADVGDTMGREXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVADVGDTMGREXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVADVGDTMGRLIB */

// Static initialization macros
#define ILVADVGDTMGRMODULEINIT(m) IL_MODULEINIT(m, ILVADVGDTMGREXPORTED)
#define ILVADVGDTMGRMODULETERM(m) IL_MODULETERM(m, ILVADVGDTMGREXPORTED)

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvadvgadmgr.lib")
#endif

#endif /* __Ilv_Gadmgr_Macrosadv_H */
