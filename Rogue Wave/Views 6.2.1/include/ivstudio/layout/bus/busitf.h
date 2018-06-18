// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/layout/bus/busitf.h
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
// Declaration of the IlvBusLayoutInterface class
// Defined in library ilvstbus
// --------------------------------------------------------------------------
#ifndef __IlvSt_Layout_Bus_Busitf_H
#define __IlvSt_Layout_Bus_Busitf_H

#if !defined(__IlvSt_Layout_Macros_H)
#include <ivstudio/layout/macros.h>
#endif /* __IlvSt_Layout_Macros_H */

#if !defined(__IlvSt_Layout_Inspitf_H)
#include <ivstudio/layout/inspitf.h>
#endif /* __IlvSt_Layout_Inspitf_H */

#if defined(ILVSTBUSLIB)
#define ILVSTBUSLAYEXPORTED ILVBASEEXPORTED
#define ILVSTBUSLAYEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVSTBUSLAYEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVSTBUSLIB */
#define ILVSTBUSLAYEXPORTED ILVBASEIMPORTED
#define ILVSTBUSLAYEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVSTBUSLAYEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVSTBUSLIB */

#define IlvDECLAREINITSTBUSLAYCLASS(m)	IL_MODULEINIT(m, ILVSTBUSLAYEXPORTED);
#define ILVSTBUSLAYMODULEINIT(m)	IL_MODULEINIT(m, ILVSTBUSLAYEXPORTED);

class ILVSTBUSLAYEXPORTED IlvBusLayoutInterface
    : public IlvLayoutInspectorInterface
{
public:
    IlvBusLayoutInterface(IlvGraphLayout*, const char* = 0);
    virtual ~IlvBusLayoutInterface();

    virtual IlBoolean	buildPage(IlvLayoutInspectorPanel*);
    virtual IlBoolean	createAccessors(IlvLayoutInspectorPanel*);

    virtual IlBoolean	selectLayout(IlvLayoutInspectorPanel*);

    void		makeBusNode();
    void		specBusNode();

protected:

private:
};

// --------------------------------------------------------------------------
#endif /* !__IlvSt_Layout_Bus_Busitf_H */
