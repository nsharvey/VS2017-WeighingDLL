// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/scmatsel.h
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
// Declaration of the IlvManagerScrolledMatrixSelectorInteractor class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Scmatsel_H
#define __Ilv31_Scmatsel_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Matsel_H)
#include <ilviews/matsel.h>
#endif
#if !defined(__Ilv31_Scmatrix_H)
#include <ilviews/scmatrix.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvManagerScrolledMatrixSelectorInteractor
    : public IlvManagerMatrixSelectorInteractor
{
 public:
    virtual IlBoolean  handleEvent(IlvManager*,
				   IlvGraphic*,
				   IlvEvent&,
				   IlvView*,
				   IlvTransformer*);
    virtual const char* className() const;
    virtual IlBoolean  accept(const IlvGraphic*) const;
};

ILV31GDTMODULEINIT(scmatsel);

#endif /* !__Ilv31_Scmatsel_H */