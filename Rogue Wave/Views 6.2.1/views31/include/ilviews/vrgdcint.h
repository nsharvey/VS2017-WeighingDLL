// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vrgdcint.h
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
// Declaration of predefined VariableGadgetContainer interactor classes
// Provided only for compatibility with V2.1.
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Vrgdcint_H
#define __Ilv31_Vrgdcint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Vsbinter_H)
#include <ilviews/vsbinter.h>
#endif
#define IlvViewVarSBInteractor IlvViewSBInteractor

#if !defined(__Ilv31_Vslidint_H)
#include <ilviews/vslidint.h>
#endif
#define IlvViewVarSliderInteractor IlvViewSliderInteractor

#if !defined(__Ilv31_Vtfinter_H)
#include <ilviews/vtfinter.h>
#endif
#define IlvViewVarTextFieldInteractor IlvViewTextFieldInteractor

#if !defined(__Ilv31_Vsheetin_H)
#include <ilviews/vsheetin.h>
#endif
#define IlvViewVarSheetInteractor IlvViewSheetInteractor

#if !defined(__Ilv31_Contint_H)
#include <ilviews/contint.h>
#endif
// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvViewVarToggleInteractor
: public IlvViewToggleInteractor {
public:
    virtual void doIt(IlvGraphic* obj, IlvContainer* view);
    virtual const char* className() const;
};

ILV31VARMODULEINIT(vrgdcint);
#endif /* !__Ilv31_Vrgdcint_H */
