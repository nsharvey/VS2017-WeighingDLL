// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/layout/orthlink/orthoitf.h
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
// Declaration of the IlvOrthogonalLayoutInterface class
// Defined in library ilvstorthlink
// --------------------------------------------------------------------------
#ifndef __IlvSt_Layout_Orthlink_Orthoitf_H
#define __IlvSt_Layout_Orthlink_Orthoitf_H

#if !defined(__IlvSt_Layout_Macros_H)
#include <ivstudio/layout/macros.h>
#endif /* __IlvSt_Layout_Macros_H */

#if !defined(__IlvSt_Layout_Inspitf_H)
#include <ivstudio/layout/inspitf.h>
#endif /* __IlvSt_Layout_Inspitf_H */

#if defined(ILVSTORTHLIB)
#define ILVSTORTHEXPORTED ILVBASEEXPORTED
#define ILVSTORTHEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVSTORTHEXPORTEDVAR(type)		ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVSTORTHLIB */
#define ILVSTORTHEXPORTED ILVBASEIMPORTED
#define ILVSTORTHEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVSTORTHEXPORTEDVAR(type)		ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVSTORTHLIB */

#define IlvDECLAREINITSTORTHCLASS(m) IL_MODULEINIT(m, ILVSTORTHEXPORTED);
#define ILVSTORTHMODULEINIT(m)	IL_MODULEINIT(m, ILVSTORTHEXPORTED);

class ILVSTORTHEXPORTED IlvOrthogonalLayoutInterface
    : public IlvLayoutInspectorInterface
{
public:
    IlvOrthogonalLayoutInterface(IlvGraphLayout*, const char* = 0);
    virtual ~IlvOrthogonalLayoutInterface();

    virtual IlBoolean	buildPage(IlvLayoutInspectorPanel*);
    virtual IlBoolean	createAccessors(IlvLayoutInspectorPanel*);

    virtual IlBoolean	selectLayout(IlvLayoutInspectorPanel*);

    void	specRoot();
    void	showRoot();

protected:

private:
};

// --------------------------------------------------------------------------
#endif /* !__IlvSt_Layout_Orthlink_Orthoitf_H */
