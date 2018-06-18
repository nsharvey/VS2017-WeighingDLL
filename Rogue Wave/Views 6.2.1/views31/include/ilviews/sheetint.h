// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/sheetint.h
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
// Declaration of the IlvManagerSheetInteractor class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Sheetint_H
#define __Ilv31_Sheetint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Matinter_H)
#include <ilviews/matinter.h>
#endif
#if !defined(__Ilv_Gadgets_Sheet_H)
#include <ilviews/gadgets/sheet.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvManagerSheetInteractor
: public IlvManagerMatrixInteractor
{
public:
    IlvManagerSheetInteractor();
    // ____________________________________________________________
    virtual const char* className() const;
    virtual IlBoolean   accept(const IlvGraphic*) const;
    virtual IlBoolean   handleResizeColumn(IlvManager*,
					   IlvGraphic*,
					   IlvEvent&,
					   IlvView*,
					   IlvTransformer*);
    virtual IlBoolean   handleResizeRow(IlvManager*,
					IlvGraphic*,
					IlvEvent&,
					IlvView*,
					IlvTransformer*);
    virtual IlBoolean   handleMatrix(IlvManager*,
				     IlvGraphic*,
				     IlvEvent&,
				     IlvView*,
				     IlvTransformer*);
};

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvMHSheetInteractor
: public IlvHSheetInteractor
{
public:
    IlvMHSheetInteractor(IlvManagerSheetInteractor* inter)
    : IlvHSheetInteractor(),
      _sheetInteractor(inter)
    {}
    // ____________________________________________________________
    IlBoolean  handleResizeColumn(IlvSheet*, IlvEvent&);
    IlBoolean  handleResizeRow(IlvSheet*, IlvEvent&);
    IlBoolean  handleMatrix(IlvSheet*, IlvEvent&);
    void       validate(IlvMatrix*);
    void       editItem(IlvMatrix*, IlUShort, IlUShort);

protected:
    IlvManagerSheetInteractor* _sheetInteractor;
};

ILV31GDTMODULEINIT(sheetint);

#endif /* !__Ilv31_Sheetint_H */