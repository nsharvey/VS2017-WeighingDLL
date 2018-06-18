// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadmgr/mviselect.h
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
// Declaration of the IlvManagerViewHook subclasses
// Defined in library ilvgadmgr
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadmgr_Mviselect_H
#define __Ilv_Gadmgr_Mviselect_H

#if !defined(__Ilv_Gadmgr_Macros_H)
#include <ilviews/gadmgr/macros.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Gadgets_Amenu_H)
#include <ilviews/gadgets/amenu.h>
#endif

// --------------------------------------------------------------------------
class ILVGDTMGREXPORTED IlvManagerViewInteractorSelector
: public IlvManagerViewHook
{
public:
    IlvManagerViewInteractorSelector(IlvManager*          manager,
				     IlvView*             view,
				     IlvMenuItemSelector* selector);
    // ____________________________________________________________
    IlvMenuItemSelector* getMenuItemSelector() const { return _selector; }
    void setMenuItemSelector(IlvMenuItemSelector* selector);
    virtual void         interactorChanged(IlvManagerViewInteractor* current,
					   IlvManagerViewInteractor* previous);
    virtual void         pushInteractor(const IlSymbol* name);
    void link(const IlSymbol* name, IlvManagerViewInteractor* interactor);
    void unLink(const IlSymbol* name) { link(name, 0); }
    IlvManagerViewInteractor* getInteractor(const IlSymbol* name) const;
    const IlSymbol* getName(IlvManagerViewInteractor* interactor) const;

protected:
    IlvMenuItemSelector*   _selector;
    IlAList                _interactors;
    IlBoolean              _pushingInteractor;
};

#endif /* !__Ilv_Gadmgr_Mviselect_H */
