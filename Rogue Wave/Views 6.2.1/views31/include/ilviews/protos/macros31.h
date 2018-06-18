// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/protos/macros31.h
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
// Definition of the prototype library macros
// Defined in library ilvproto
// --------------------------------------------------------------------------

#ifndef __Ilv_Protos_Macros31_H
#define __Ilv_Protos_Macros31_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if defined(ILV31PROLIB)
#define ILV31PROEXPORTED ILVBASEEXPORTED
#define ILV31PROEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILV31PROEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILV31PROLIB */
#define ILV31PROEXPORTED ILVBASEIMPORTED
#define ILV31PROEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILV31PROEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILV31PROLIB */

#define IlvDECLAREINIT31PROCLASS(m) IL_MODULEINIT(m, ILV31PROEXPORTED);

#if defined(ILV31VRPLIB)
#define ILV31VRPEXPORTED ILVBASEEXPORTED
#define ILV31VRPEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILV31VRPEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILV31PROLIB */
#define ILV31VRPEXPORTED ILVBASEIMPORTED
#define ILV31VRPEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILV31VRPEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILV31PROLIB */

#define IlvDECLAREINIT31VRPCLASS(m) IL_MODULEINIT(m, ILV31VRPEXPORTED);

#endif /* __Ilv_Protos_Macros31_H */
