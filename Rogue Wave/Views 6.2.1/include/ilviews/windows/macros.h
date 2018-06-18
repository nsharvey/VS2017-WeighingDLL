// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/windows/macros.h
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
// Definitions of the com library macros.
// --------------------------------------------------------------------------

#if !defined(__ILV_Windows_Macros_H)
#define __ILV_Windows_Macros_H

#if !defined(__ILV_MACROS_H)
#include <ilviews/macros.h>
#endif /* !__ILV_MACROS_H */

#if defined(ILVCOMLIB)
#  define ILVCOMEXPORTED		IL_BASEEXPORTED
#  define ILVCOMEXPORTEDFUNCTION(type)	IL_BASEEXPORTEDFUNCTION(type)
#  define ILVCOMEXPORTEDVAR(type)	IL_BASEEXPORTEDFUNCTION(type)
#else   /* !ILVCOMLIB */
#  define ILVCOMEXPORTED		IL_BASEIMPORTED
#  define ILVCOMEXPORTEDFUNCTION(type)	IL_BASEIMPORTEDFUNCTION(type)
#  define ILVCOMEXPORTEDVAR(type)	IL_BASEEXPORTEDFUNCTION(type)
#endif  /* !ILVCOMLIB */

#define ILVCOMMODULEINIT(m) IL_MODULEINIT(m, ILVCOMEXPORTED)
#define ILVCOMMODULETERM(m) IL_MODULETERM(m, ILVCOMEXPORTED)

#endif /* !__ILV_Windows_Macros_H */
