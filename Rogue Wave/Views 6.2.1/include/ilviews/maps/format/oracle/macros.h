// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/macros.h
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
// Rogue Wave Views - Maps add-on.
// Defines the useful macros for SDO
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Macros_H
#define __Ilv_Maps_Format_Oracle_Macros_H

#define SDOLIBRARYMODULE

#include <ilviews/macros.h>
#include <ilviews/base/gcontext.h>

// Export / import macros for DB Maps library
#if defined(ILVDBMAPSLIB)
#  define ILVDBMAPSEXPORTED ILVBASEEXPORTED
#  define ILVDBMAPSEXPORTEDFUNCTION(type) ILVBASEEXPORTEDFUNCTION(type)
#  define ILVDBMAPSEXPORTEDVAR(type) ILVBASEEXPORTEDFUNCTION(type)
#else /* !ILVDBMAPSLIB */
#  define ILVDBMAPSEXPORTED ILVBASEIMPORTED
#  define ILVDBMAPSEXPORTEDFUNCTION(type) ILVBASEIMPORTEDFUNCTION(type)
#  define ILVDBMAPSEXPORTEDVAR(type) ILVBASEIMPORTEDFUNCTION(type)
#endif /* !IVLDBMAPSLIB */
extern ILVDBMAPSEXPORTEDFUNCTION(IlBoolean) _IlvMapsInitializeSDOPackage();
//static IlBoolean InitializeIt = _IlvMapsInitializeSDOPackage();

#define ILVDBMAPSMODULEINIT(m) IL_MODULEINIT(maps##m, ILVDBMAPSEXPORTED)
#define ILVDBMAPSMODULETERM(m) IL_MODULETERM(maps##m, ILVDBMAPSEXPORTED)

#endif /* __Ilv_Maps_Format_Oracle_Macros_H */
