// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/popinter.h
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
// Declaration of the IlvManagerPopupMenuInteractor class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------

#ifndef __Ilv31_Popinter_H
#define __Ilv31_Popinter_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Gadgets_Menu_H)
#include <ilviews/gadgets/menu.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Manager_Holder_H)
#include <ilviews/manager/holder.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvManagerPopupMenuInteractor
    : public IlvManagerGadgetInteractor
{
 public:
    IlvManagerPopupMenuInteractor();
    // ____________________________________________________________
    virtual const char* className() const;
    virtual IlBoolean   accept(const IlvGraphic*) const;
    virtual void        select(IlvManager*,
			       IlvView*,
			       IlvPopupMenu*,
			       IlUShort);
    virtual void        unSelect(IlvManager*,
				 IlvView*,
				 IlvPopupMenu*,
				 IlUShort);
    virtual void        doIt(IlvManager*,
			     IlvPopupMenu*);
    virtual IlBoolean   isSelectable(IlvMenuItem*) const;
    virtual IlShort     selectNext(IlvPopupMenu*);
    virtual IlShort     selectPrevious(IlvPopupMenu*);
};

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvMHPopupMenuInteractor
    : public IlvHPopupMenuInteractor
{
 public:
    IlvMHPopupMenuInteractor(IlvManagerPopupMenuInteractor* inter)
	: IlvHPopupMenuInteractor(),
	_popupMenuInteractor(inter)
	{}
    // ____________________________________________________________
    virtual void       select(IlvPopupMenu*,
			      IlUShort);
    virtual void       unSelect(IlvPopupMenu*,
				IlUShort);
    virtual void       doIt(IlvPopupMenu*);
    virtual IlBoolean  isSelectable(IlvPopupMenu*,
				    IlvMenuItem*) const;
    virtual IlShort   selectNext(IlvPopupMenu*);
    virtual IlShort   selectPrevious(IlvPopupMenu*);
    
 protected:
    IlvManagerPopupMenuInteractor* _popupMenuInteractor;
};

// --------------------------------------------------------------------------
ILV31GDTMODULEINIT(popinter);

#endif /* !__Ilv31_Popinter_H */
