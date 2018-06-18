// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/gadgets/custgad/step2/include/ctxminter.h
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
// Declaration of the ContextualMenuInteractor class
// --------------------------------------------------------------------------

#ifndef __ContextualMenuInteractor
#define __ContextualMenuInteractor

#include <ilviews/base/gadget.h>
#include <ilviews/gadgets/menu.h>

// --------------------------------------------------------------------------
class ContextualMenuInteractor
: public IlvGadgetInteractor 
{
public:
    ContextualMenuInteractor() {};
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvGraphic* obj,
				  IlvEvent&,
				  const IlvTransformer* t);
    virtual IlBoolean shouldShowMenu(IlvGraphic*,
				     IlvEvent&,
				     const IlvTransformer*) const;
    virtual IlvPopupMenu* getMenu(IlvGraphic*,
				  IlvEvent&,
				  const IlvTransformer*) const = 0;
};

#include <coltree.h>

// --------------------------------------------------------------------------
class ColoredTreeGadgetInteractor
: public ContextualMenuInteractor
{
public:
    ColoredTreeGadgetInteractor() {};
    // ____________________________________________________________
    virtual IlvPopupMenu* getMenu(IlvGraphic*,
				  IlvEvent&,
				  const IlvTransformer*) const;
    static void SetSelectedItem(IlvPopupMenu*,
				 ColoredTreeGadget*,
				 IlvTreeGadgetItem*);
    static IlvTreeGadgetItem* GetSelectedItem(const IlvPopupMenu*);
};

#endif
