// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/synedit/include/TreeView.h
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
// Declaration of the TreeView class
// --------------------------------------------------------------------------
#if !defined(TreeView__header__)
#define TreeView__header__

#if !defined(__Ilv_Appframe_Viewgadg_H)
#include <ilviews/appframe/viewgadg.h>
#endif /* !__Ilv_Appframe_Viewgadg_H */

class TreeDocument;
class SynNode;

// --------------------------------------------------------------------------
// TreeView class
// --------------------------------------------------------------------------

class TreeView
: public IlvDvTreeView
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    TreeView(IlvDisplay*);
    virtual ~TreeView();

    // --------------------------------------------------------------------------
    // Overridables
    virtual void initializeView();

    // ----------------------------------------------------------------------
    // Basic properties
    TreeDocument* getSyneditDocument() const;

    // ----------------------------------------------------------------------
    // Export TreeView fields and methods
    IlvDvDeclareInterface();

protected:
    IlvTreeGadgetItem* createNodeItem(SynNode*) const;
    virtual void activate(IlvTreeGadgetItem* item);
    void selectClass(IlAny node);
    IlvTreeGadgetItem* findNodeItem(IlAny node) const;
};

// --------------------------------------------------------------------------
IL_MODULEINIT(TreeView, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !TreeView__header__ */
