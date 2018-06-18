// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/manager/macros.h
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
// Declaration of macros used for exporting appmrg symbols
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Manager_Macros_H)
#define __Ilv_Appframe_Manager_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvappmgr.lib")
#endif

// --------------------------------------------------------------------------
#if defined(ILVDVMGRLIB)
#  define ILVDVMGREXPORTED IL_BASEEXPORTED
#  define ILVDVMGREXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVDVMGREXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVDVMGRLIB */

#if !defined(ILVDVMGREXPORTED)
#  define ILVDVMGREXPORTED IL_BASEIMPORTED
#  define ILVDVMGREXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVDVMGREXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILVDVMGREXPORTED */

// Static initialization macros
#define ILVDVMGRMODULEINIT(m) IL_MODULEINIT(dvmgr_##m, ILVDVMGREXPORTED)
#define ILVDVMGRMODULETERM(m) IL_MODULETERM(dvmgr_##m, ILVDVMGREXPORTED)

// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Manager_Macros_H */
