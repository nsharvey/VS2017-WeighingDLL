// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadmgr/scrlhook.h
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
// Declaration of the IlvGadgetScrollViewHook class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Scrlhook_H
#define __Ilv_Manager_Scrlhook_H

#if !defined(__Ilv_Gadmgr_Macros_H)
#include <ilviews/gadmgr/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Scrollb_H)
#include <ilviews/gadgets/scrollb.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif

// --------------------------------------------------------------------------
// IlvGadgetScrollViewHook to attach scrollbars to an IlvView
// --------------------------------------------------------------------------
class ILVGDTMGREXPORTED IlvGadgetScrollViewHook
: public IlvManagerViewHook
{
public:
    IlvGadgetScrollViewHook(IlvManager*   mgr,
			    IlvView*      view,
			    IlvContainer* container,
			    IlvScrollBar* vscroll,
			    IlvScrollBar* hscroll);
    ~IlvGadgetScrollViewHook();
    // ____________________________________________________________
    virtual void transformerChanged(const IlvTransformer*,
				    const IlvTransformer*);
    virtual void viewResized();
    virtual void contentsChanged();
    void         adjustView();
    void         adjustScrollBars();

protected:
    void compute() { getManager()->computeBBox(_bbox,getView()); }
    void init();

    IlvPos        _previousx;
    IlvPos        _previousy;
    IlvScrollBar* _verticalSB;
    IlvScrollBar* _horizontalSB;
    IlvContainer* _container;
    IlvRect       _bbox;

};

#endif /* !__Ilv_Manager_Scrlhook_H */
