// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/layout/macros.h
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
// Definition of macros
// --------------------------------------------------------------------------
#ifndef __IlvSt_Layout_Macros_H
#define __IlvSt_Layout_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif /* __Ilv_Macros_H */

#if defined(ILVSTLAYLIB)
#define ILVSTLAYEXPORTED ILVBASEEXPORTED
#define ILVSTLAYEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVSTLAYEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVSTLAYLIB */
#define ILVSTLAYEXPORTED ILVBASEIMPORTED
#define ILVSTLAYEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVSTLAYEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVSTLAYLIB */

#define IlvDECLAREINITSTLAYCLASS(m) IL_MODULEINIT(m, ILVSTLAYEXPORTED);
#define ILVSTLAYMODULEINIT(m)	IL_MODULEINIT(m, ILVSTLAYEXPORTED);

#endif /* __IlvSt_Layout_Macros_H */
