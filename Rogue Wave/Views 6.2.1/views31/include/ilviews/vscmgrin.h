// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vscmgrin.h
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
// Declaration of the IlvViewSCManagerInteractor class
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Vscmgrin_H
#define __Ilv31_Vscmgrin_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Gadmgr_Rectscmg_H)
#include <ilviews/gadmgr/rectscmg.h>
#endif
#if !defined(__Ilv_Contain_Inter_H)
#include <ilviews/contain/inter.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvViewSCManagerInteractor
: public IlvViewObjectInteractor {
public:
    virtual IlBoolean handleEvent(IlvGraphic* obj, IlvEvent&, IlvContainer*,
				  IlvTransformer* t);
    virtual IlBoolean accept(const IlvGraphic*) const;
    virtual const char* className() const;
};

ILV31GDTMODULEINIT(vscmgrin);

#endif /* ! __Ilv31_Vscmgrin_H */
