// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/sclinter.h
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
// Declaration of the IlvManagerScrolledStringListInteractor class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Sclinter_H
#define __Ilv31_Sclinter_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Slinter_H)
#include <ilviews/slinter.h>
#endif
#if !defined(__Ilv31_Vsclint_H)
#include <ilviews/vsclint.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvManagerScrolledStringListInteractor
: public IlvManagerStringListInteractor
{
 public:
    IlvManagerScrolledStringListInteractor();
    // ____________________________________________________________
    virtual void scrollBarChanged(IlvManager*,
				  IlvView*,
				  IlvScrollBar*,
				  IlvDirection);
    virtual const char* className() const;
    virtual IlBoolean accept(const IlvGraphic*) const;
};

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvMHScrolledStringListInteractor
    : public IlvHScrolledStringListInteractor
{
 public:
    IlvMHScrolledStringListInteractor(IlvManagerScrolledStringListInteractor*
				      inter)
	: IlvHScrolledStringListInteractor(),
	_scrolledStringListInteractor(inter)
	{}
    // ____________________________________________________________
    virtual void select(IlvStringList*, IlUShort);
    virtual void unSelect(IlvStringList*, IlUShort);
    virtual void doIt(IlvStringList*);
    virtual void scrollBarChanged(IlvScrolledStringList*,
				  IlvScrollBar*,
				  IlvDirection);

 protected:
    IlvManagerScrolledStringListInteractor* _scrolledStringListInteractor;
};
// --------------------------------------------------------------------------

ILV31GDTMODULEINIT(sclinter);

#endif /* !__Ilv31_Sclinter_H */
