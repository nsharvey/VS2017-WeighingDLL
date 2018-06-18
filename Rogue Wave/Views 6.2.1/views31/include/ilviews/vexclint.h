// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vexclint.h
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
// Declaration of the IlvViewSelectorInteractor
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Vexclint_H
#define __Ilv31_Vexclint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Graphics_Selector_H)
#include <ilviews/graphics/selector.h>
#endif

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvViewSelectorInteractor
    : public IlvViewObjectInteractor 
{
 public:
    virtual IlBoolean handleEvent(IlvGraphic* obj, IlvEvent&,
				  IlvContainer* view,
				  IlvTransformer* t);
    virtual void doIt(IlvSelector* obj);
    virtual IlBoolean accept(const IlvGraphic*) const;
    virtual const char* className() const;
};

ILV31VWSMODULEINIT(vexclint);

#endif /* !__Ilv31_Vexclint_H */
