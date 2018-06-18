// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/macros.h
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
// Defined in library ilvstates
// --------------------------------------------------------------------------
#ifndef __Ilv_States_Macros_H
#define __Ilv_States_Macros_H

#include <ilviews/macros.h>

#if defined(ILVSTATESLIB)
#  define ILVSTATESEXPORTED IL_BASEEXPORTED
#  define ILVSTATESEXPORTEDFUNCTION(type) IL_BASEEXPORTEDFUNCTION(type)
#  define ILVSTATESEXPORTEDVAR(type) IL_BASEEXPORTEDFUNCTION(type)
#endif /* !ILVSTATESLIB */

#if !defined(ILVSTATESEXPORTED)
#  define ILVSTATESEXPORTED IL_BASEIMPORTED
#  define ILVSTATESEXPORTEDFUNCTION(type) IL_BASEIMPORTEDFUNCTION(type)
#  define ILVSTATESEXPORTEDVAR(type) IL_BASEIMPORTEDFUNCTION(type)
#endif /* ILVSTATESEXPORTED */

// Static initialization macros
#define ILVSTATESMODULEINIT(m) IL_MODULEINIT(m, ILVSTATESEXPORTED)
#define ILVSTATESMODULETERM(m) IL_MODULETERM(m, ILVSTATESEXPORTED)

// 3.0 compatibility
#define IlvDECLAREINITSTATESCLASS(m) IL_MODULEINIT(m, ILVSTATESEXPORTED);

#endif /* !__Ilv_States_Macros_H */
