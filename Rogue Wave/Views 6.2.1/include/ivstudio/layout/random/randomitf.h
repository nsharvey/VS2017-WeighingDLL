// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/layout/random/randomitf.h
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
// Declaration of the IlvRandomLayoutInterface class
// Defined in library ilvstrandom
// --------------------------------------------------------------------------
#ifndef __IlvSt_Layout_Random_Randomitf_H
#define __IlvSt_Layout_Random_Randomitf_H

#if !defined(__IlvSt_Layout_Macros_H)
#include <ivstudio/layout/macros.h>
#endif /* __IlvSt_Layout_Macros_H */

#if !defined(__IlvSt_Layout_Inspitf_H)
#include <ivstudio/layout/inspitf.h>
#endif /* __IlvSt_Layout_Inspitf_H */

#if defined(ILVSTRANDLIB)
#define ILVSTRANDOMLAYEXPORTED ILVBASEEXPORTED
#define ILVSTRANDOMLAYEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVSTRANDOMLAYEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVSTRANDLIB */
#define ILVSTRANDOMLAYEXPORTED ILVBASEIMPORTED
#define ILVSTRANDOMLAYEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVSTRANDOMLAYEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVSTRANDLIB */

#define IlvDECLAREINITSTRANDOMLAYCLASS(m)	IL_MODULEINIT(m, ILVSTRANDOMLAYEXPORTED);
#define ILVSTRANDOMLAYMODULEINIT(m)	IL_MODULEINIT(m, ILVSTRANDOMLAYEXPORTED);

class ILVSTRANDOMLAYEXPORTED IlvRandomLayoutInterface
    : public IlvLayoutInspectorInterface
{
public:
    IlvRandomLayoutInterface(IlvGraphLayout*, const char* = 0);
    virtual ~IlvRandomLayoutInterface();

    virtual IlBoolean	buildPage(IlvLayoutInspectorPanel*);
    virtual IlBoolean	createAccessors(IlvLayoutInspectorPanel*);

    virtual IlBoolean	selectLayout(IlvLayoutInspectorPanel*);

protected:

private:
};

// --------------------------------------------------------------------------
#endif /* !__IlvSt_Layout_Random_Randomitf_H */
