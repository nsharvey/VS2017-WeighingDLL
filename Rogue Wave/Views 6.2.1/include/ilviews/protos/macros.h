// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/macros.h
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

#ifndef __Ilv_Protos_Macros_H
#define __Ilv_Protos_Macros_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if defined(ILVPROLIB)
#define ILVPROEXPORTED ILVBASEEXPORTED
#define ILVPROEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVPROEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVPROLIB */
#define ILVPROEXPORTED ILVBASEIMPORTED
#define ILVPROEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVPROEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVPROLIB */
#if defined(ILVGDPLIB)
#define ILVGDPEXPORTED ILVBASEEXPORTED
#define ILVGDPEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVGDPEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVGDPLIB */
#define ILVGDPEXPORTED ILVBASEIMPORTED
#define ILVGDPEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVGDPEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVGDPLIB */
#if defined(ILVVRPLIB)
#define ILVVRPEXPORTED ILVBASEEXPORTED
#define ILVVRPEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVVRPEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVVRPLIB */
#define ILVVRPEXPORTED ILVBASEIMPORTED
#define ILVVRPEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVVRPEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVVRPLIB */

#define IlvDECLAREINITPROCLASS(m) IL_MODULEINIT(m, ILVPROEXPORTED);
#define IlvDECLAREINITGDPCLASS(m) IL_MODULEINIT(m, ILVGDPEXPORTED);
#define IlvDECLAREINITVRPCLASS(m) IL_MODULEINIT(m, ILVVRPEXPORTED);

// Message database
//
#ifdef ILVDEFLTMSGS
#define ILVPROMSG(id,msg) _IlvGetProtoMessage(0,id,msg)
#else
#define ILVPROMSG(id,msg) _IlvGetProtoMessage(0,id,0)
#endif

#endif /* __Ilv_Protos_Macros_H */
