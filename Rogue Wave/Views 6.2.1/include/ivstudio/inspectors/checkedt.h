// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/checkedt.h
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
// Declaration of generic editor classes
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Checkedt_H)
#define __IlvSt_Inspectors_Checkedt_H

// --------------------------------------------------------------------------
// Includes
#if !defined(__IlvSt_Inspectors_Genedt_H)
#include <ivstudio/inspectors/genedt.h>
#endif

// --------------------------------------------------------------------------
// IlvStICheckedEditor class
// --------------------------------------------------------------------------

class ILVINSPCLASS IlvStICheckedEditor
: public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructors / destructor
    IlvStICheckedEditor(IlvStIPropertyAccessor* accessor = 0,
		        const char* checkGadgetName = 0,
		        const char* name = 0,
		        IlAny defaultValue = 0,
		        NotificationMode = AsOwner);

    IlvStICheckedEditor(IlvStIPropertyAccessor* accessor,
		        const IlSymbol* propertyName,
		        const char* checkGadgetName,
		        const char* name,
		        IlAny defaultValue = 0,
		        NotificationMode = AsOwner);

    ~IlvStICheckedEditor();

    // ----------------------------------------------------------------------
protected:
    IlString _checkGadgetName;

    void initializeCheckedEditor(IlAny defaultValue);
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_checkedt)
#endif /* !__IlvSt_Inspectors_Checkedt_H */
