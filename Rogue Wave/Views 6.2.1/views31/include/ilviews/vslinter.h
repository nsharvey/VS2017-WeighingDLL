// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vslinter.h
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
// Declaration of the IlvViewStringListInteractor class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Vslinter_H
#define __Ilv31_Vslinter_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Contain_Holder)
#include <ilviews/contain/holder.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvViewStringListInteractor
: public IlvViewGadgetInteractor {
public:
    IlvViewStringListInteractor();
    // ____________________________________________________________
    virtual void select(IlvContainer*, IlvTransformer*,
			IlvStringList*, IlUShort);
    virtual void unSelect(IlvContainer*, IlvTransformer*,
			  IlvStringList*, IlUShort);
    virtual void doIt(IlvContainer*, IlvStringList*);
    virtual const char* className() const;
    virtual IlBoolean accept(const IlvGraphic*) const;
};

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvVHStringListInteractor
: public IlvHStringListInteractor {
public:
    IlvVHStringListInteractor(IlvViewStringListInteractor* inter)
    : IlvHStringListInteractor(),
      _stringListInteractor(inter)
    {}
    // ____________________________________________________________
    virtual void select(IlvStringList*, IlUShort);
    virtual void unSelect(IlvStringList*, IlUShort);
    virtual void doIt(IlvStringList*);
protected:
    IlvViewStringListInteractor* _stringListInteractor;
};

// --------------------------------------------------------------------------
ILV31GDTMODULEINIT(vslinter);

#endif /* !__Ilv31_Vslinter_H */