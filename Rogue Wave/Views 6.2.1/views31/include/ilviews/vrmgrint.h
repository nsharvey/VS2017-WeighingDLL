// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vrmgrint.h
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
// Declaration of predefined object interactors classes designed for the
// VariableGadgetManager class.
// Provided only for compatibility with V2.1
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Vrmgrint_H
#define __Ilv31_Vrmgrint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Sbinter_H)
#include <ilviews/sbinter.h>
#endif
#define IlvManagerVarSBInteractor IlvManagerSBInteractor

#if !defined(__Ilv31_Slidint_H)
#include <ilviews/slidint.h>
#endif
#define IlvManagerVarSliderInteractor IlvManagerSliderInteractor

#if !defined(__Ilv31_Tfdinter_H)
#include <ilviews/tfdinter.h>
#endif
#define IlvManagerVarTextFieldInteractor IlvManagerTextFieldInteractor

#if !defined(__Ilv31_Objinter_H)
#include <ilviews/objinter.h>
#endif
// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvManagerVarToggleInteractor
: public IlvManagerToggleInteractor {
public:
    virtual void doIt(IlvGraphic* obj);
    virtual const char* className() const;
};

#if !defined(__Ilv31_Sheetint_H)
#include <ilviews/sheetint.h>
#endif
#define IlvManagerVarSheetInteractor IlvManagerSheetInteractor

ILV31VARMODULEINIT(vrmgrint);
#endif /* ! __Ilv31_Vrmgrint_H */
