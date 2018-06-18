// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vmbinter.h
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
// Declaration of the IlvViewMenuBarInteractor class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------

#ifndef __Ilv31_Vmbinter_H
#define __Ilv31_Vmbinter_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Gadgets_Menubar_H)
#include <ilviews/gadgets/menubar.h>
#endif
#if !defined(__Ilv_Contain_Holder_H)
#include <ilviews/contain/holder.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvViewMenuBarInteractor
    : public IlvViewGadgetInteractor
{
 public:
    IlvViewMenuBarInteractor();
    // ____________________________________________________________
    virtual void select(IlvContainer*,
			IlvMenuBar*,
			IlUShort);
    virtual void unSelect(IlvContainer*,
			  IlvMenuBar*,
			  IlUShort);
    virtual const char* className() const;
    virtual IlBoolean accept(const IlvGraphic*) const;
};

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvVHMenuBarInteractor
    : public IlvHMenuBarInteractor
{
 public:
    IlvVHMenuBarInteractor(IlvViewMenuBarInteractor* inter)
	: IlvHMenuBarInteractor(),
	_menubarInteractor(inter)
	{}
    // ____________________________________________________________
    virtual void select(IlvMenuBar*,
			IlUShort);
    virtual void unSelect(IlvMenuBar*,
			  IlUShort);
 protected:
    IlvViewMenuBarInteractor* _menubarInteractor;
};

// --------------------------------------------------------------------------
ILV31GDTMODULEINIT(vmbinter);

#endif /* !__Ilv31_Vmbinter_H */
