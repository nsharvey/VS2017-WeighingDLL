// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/macros.h
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
// Export purpose macro definitions for the edit library.
// --------------------------------------------------------------------------
#ifndef __Ilv_Edit_Macros_H
#define __Ilv_Edit_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if defined(ILVEDTLIB)
#  define ILVEDTEXPORTED IL_BASEEXPORTED
#  define ILVEDTEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVEDTEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#else  /* !ILVEDTLIB */
#  define ILVEDTEXPORTED IL_BASEIMPORTED
#  define ILVEDTEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVEDTEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* !ILVEDTLIB */

// Static initialization macros
#define ILVEDTMODULEINIT(m) IL_MODULEINIT(m, ILVEDTEXPORTED)
#define ILVEDTMODULETERM(m) IL_MODULETERM(m, ILVEDTEXPORTED)

// 3.0 compatibility
#define IlvDECLAREINITEDTCLASS(m) IL_MODULEINIT(m, ILVEDTEXPORTED);

#endif /* __Ilv_Edit_Macros_H */
