// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vsclint.h
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
// Declaration of the IlvViewScrolledStringListInteractor class
// Defined in library ilv31gadgt
// --------------------------------------------------------------------------

#ifndef __Ilv31_Vsclint_H
#define __Ilv31_Vsclint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Vslinter_H)
#include <ilviews/vslinter.h>
#endif
#if !defined(__Ilv31_Sclist_H)
#include <ilviews/sclist.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvViewScrolledStringListInteractor
: public IlvViewStringListInteractor {
public:
    IlvViewScrolledStringListInteractor();
    // ____________________________________________________________
    virtual void scrollBarChanged(IlvContainer*, IlvScrollBar*, IlvDirection);
    virtual const char* className() const;
    virtual IlBoolean accept(const IlvGraphic*) const;
};

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvHScrolledStringListInteractor
: public IlvHStringListInteractor {
public:
    virtual void scrollBarChanged(IlvScrolledStringList*,
				  IlvScrollBar*, IlvDirection) = 0;
};

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvVHScrolledStringListInteractor
: public IlvHScrolledStringListInteractor {
public:
    IlvVHScrolledStringListInteractor(IlvViewScrolledStringListInteractor*
				      inter)
    : IlvHScrolledStringListInteractor(),
      _scrolledStringListInteractor(inter)
    {}
    // ____________________________________________________________
    virtual void select(IlvStringList*, IlUShort);
    virtual void unSelect(IlvStringList*, IlUShort);
    virtual void doIt(IlvStringList*);
    virtual void scrollBarChanged(IlvScrolledStringList*, IlvScrollBar*,
				  IlvDirection);
protected:
    IlvViewScrolledStringListInteractor* _scrolledStringListInteractor;
};

// --------------------------------------------------------------------------
ILV31GDTMODULEINIT(vsclint);

#endif /* !__Ilv31_Vsclint_H */
