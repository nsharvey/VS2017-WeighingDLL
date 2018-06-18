// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vpopint.h
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
// Declaration of the IlvViewPopupMenuInteractor class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------

#ifndef __Ilv31_Vpopint_H
#define __Ilv31_Vpopint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Gadgets_Menu_H)
#include <ilviews/gadgets/menu.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Contain_Holder_H)
#include <ilviews/contain/holder.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvViewPopupMenuInteractor
: public IlvViewGadgetInteractor {
public:
    IlvViewPopupMenuInteractor();
    // ____________________________________________________________
    virtual void select(IlvContainer*, IlvPopupMenu*, IlUShort);
    virtual void unSelect(IlvContainer*, IlvPopupMenu*, IlUShort);
    virtual void doIt(IlvContainer*, IlvPopupMenu*);
    virtual IlBoolean isSelectable(IlvMenuItem*) const;
    virtual IlShort selectNext(IlvPopupMenu*);
    virtual IlShort selectPrevious(IlvPopupMenu*);
    IlBoolean isDraggingTearOff() const { return _draggingTearOff; }
    void       dragTearOff(IlBoolean drag) { _draggingTearOff = drag; }
    virtual const char* className() const;
    virtual IlBoolean accept(const IlvGraphic*) const;
private:
    IlBoolean _draggingTearOff;
};

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvVHPopupMenuInteractor
: public IlvHPopupMenuInteractor {
public:
    IlvVHPopupMenuInteractor(IlvViewPopupMenuInteractor* inter)
    : IlvHPopupMenuInteractor(),
      _popupMenuInteractor(inter)
    {}
    // ____________________________________________________________
    virtual void select(IlvPopupMenu*, IlUShort);
    virtual void unSelect(IlvPopupMenu*, IlUShort);
    virtual void doIt(IlvPopupMenu*);
    virtual IlBoolean isSelectable(IlvPopupMenu*, IlvMenuItem*) const;
    virtual IlShort selectNext(IlvPopupMenu*);
    virtual IlShort selectPrevious(IlvPopupMenu*);
protected:
    IlvViewPopupMenuInteractor* _popupMenuInteractor;
};

ILV31GDTMODULEINIT(vpopint);

#endif /* !__Ilv31_Vpopint_H */
