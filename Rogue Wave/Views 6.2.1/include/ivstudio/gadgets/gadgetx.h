// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/gadgetx.h
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
// Declaration of IlvStGraphicExtension
// --------------------------------------------------------------------------
#ifndef __IlvSt_Gadgetx_H
#define __IlvSt_Gadgetx_H

#if !defined(__IlvSt_Studext_H)
#include <ivstudio/studext.h>
#endif

// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStGadgetExtension : public IlvStExtension
{
public:
    IlvStGadgetExtension(IlvStudio*);
    ~IlvStGadgetExtension();

    virtual IlBoolean			initializeCommandDescriptors();
    virtual IlBoolean			initializePanels();
    virtual IlBoolean			initializeInspectors();
    virtual IlBoolean			initializeModes();
    virtual IlBoolean			postInitialize();

    static IlvStGadgetExtension*	Make(IlvStudio*);
}; // class IlvStGadgetExtension

// --------------------------------------------------------------------------

#endif /* __IlvSt_Gadgetx_H */
