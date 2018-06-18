// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/exclint.h
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
// Declaration of the IlvManagerSelectorInteractor class
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Exclint_H
#define __Ilv31_Exclint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Graphics_Selector_H)
#include <ilviews/graphics/selector.h>
#endif

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvManagerSelectorInteractor
: public IlvManagerObjectInteractor
{
public:
    virtual IlBoolean  handleEvent(IlvManager*,
				   IlvGraphic*     obj,
				   IlvEvent&,
				   IlvView*        view,
				   IlvTransformer* t);
    virtual void       doIt(IlvSelector* selector);
    virtual IlBoolean  accept(const IlvGraphic*) const;
    virtual const char* className() const;
};

ILV31VWSMODULEINIT(exclint);

#endif /* !__Ilv31_Exclint_H */
