// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/attitem.h
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
// Declaration of the IlvMatrixItemAttribute classes
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Attitem_H
#define __Ilv31_Attitem_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Gadgets_Matrix_H)
#include <ilviews/gadgets/matrix.h>
#endif
#if !defined(__Ilv31_Attribut_H)
#include <ilviews/attribut.h>
#endif

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvMatrixItemAttribute
    : public IlvGraphicAttribute
{
 public:
    IlvMatrixItemAttribute(IlvContainer* container,
			   IlvGraphic* obj = 0,
			   const char* name = 0,
			   IlUShort col = 0,
			   IlUShort row = 0)
	: IlvGraphicAttribute(container, obj, name),
	_column(col),
	_row(row)
	{}
    IlvMatrixItemAttribute(IlvManager* manager,
			   IlvGraphic* obj = 0,
			   const char* name = 0,
			   IlUShort col = 0,
			   IlUShort row = 0)
	: IlvGraphicAttribute(manager, obj, name),
	_column(col),
	_row(row)
	{}
    // ____________________________________________________________
    void setItem(IlUShort col,
		 IlUShort row)
    {
	_column = col;
	_row = row;
    }
    void getItem(IlUShort& col,
		 IlUShort& row) const
    {
	col = _column;
	row = _row;
    }
    virtual void apply(const IlvAttributeValue&);
    virtual void set(const IlvAttributeValue&,
		     IlBoolean redraw = IlTrue);
    virtual const IlvAttributeValue& get() const;
    virtual IlBoolean accept(IlvGraphic*);
    // check attribute application.
    // checkData should be a pointer to an array of two UShorts: c&r
    virtual IlBoolean check(const IlvGraphic*,
			    IlAny checkData) const;

    virtual void read(IL_STDPREF istream&);
    virtual void write(IL_STDPREF ostream&) const;
    IlvGraphicAttribute* copy();

    IlvDeclareAttribute();
 protected:
    IlUShort	_column;
    IlUShort	_row;
};

ILV31VARMODULEINIT(attitem);
#endif /* __Ilv31_Attitem_H */
