// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/include/TextView.h
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
// IlogViews 4 generated header file
// File generated Thu Aug 26 15:58:41 1999
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Declaration of the TextView class
// --------------------------------------------------------------------------
#if !defined(TextView__header__)
#define TextView__header__

#if !defined(__Ilv_Appframe_Viewgadg_H)
#include <ilviews/appframe/viewgadg.h>
#endif /* !__Ilv_Appframe_Viewgadg_H */

class TreeDocument;

// --------------------------------------------------------------------------
// TextView class
// --------------------------------------------------------------------------

class TextView
: public IlvDvTextView
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    TextView(IlvDisplay*);
    virtual ~TextView();

    // --------------------------------------------------------------------------
    // Overridables
    virtual void initializeView();

    // ----------------------------------------------------------------------
    // Basic properties
    TreeDocument* getSyneditDocument() const;

    // ----------------------------------------------------------------------
    // Export TextView fields and methods
    IlvDvDeclareInterface();

protected:
    void selectClass(IlAny node);
    virtual void selectionChanged();
    virtual IlBoolean handleControl(IlUShort c);
    void cursorMoved();
};

// --------------------------------------------------------------------------
IL_MODULEINIT(TextView, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !TextView__header__ */
