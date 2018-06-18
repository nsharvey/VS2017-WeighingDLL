// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/gridint.h
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
// Declaration of the IlvViewGridInteractor class
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Gridint_H
#define __Ilv1X_Gridint_H

#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Grid_H)
#include <ilviews/grid.h>
#endif

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvViewGridInteractor
    : public IlvViewObjectInteractor
{
public:
    virtual IlvBoolean handleEvent(IlvGraphic*     obj,
				   IlvEvent&, IlvContainer*   view,
				   IlvTransformer* t);
    virtual void selectObject(IlvGraphic*);
    virtual void unSelectObject(IlvGraphic*);
    virtual void callCallback(IlvContainer*,IlvGridObj*,
			      IlvGraphic*);
    const char* className() const;
};

ILV1XVWSMODULEINIT(gridint);

#endif /* !__Ilv1X_Gridint_H */
