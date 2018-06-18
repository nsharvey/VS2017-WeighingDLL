// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vcontint.h
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
// Declaration of predefined IlvVariableViewObjectInteractor classes
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Vcontint_H
#define __Ilv31_Vcontint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Contint_H)
#include <ilviews/contint.h>
#endif

// --------------------------------------------------------------------------
#define IlvViewVarMoveInteractor IlvViewMoveInteractor

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvViewVarReshapeInteractor
: public IlvViewReshapeInteractor {
public:
    virtual void doIt(IlvContainer* container, IlvGraphic* ghost,
		      IlvRect& rect);
    virtual const char* className() const;
};

// --------------------------------------------------------------------------
#if !defined(__Ilv31_Gaugeint_H)
#include <ilviews/gaugeint.h>
#endif
#define IlvViewVarGaugeInteractor IlvViewGaugeInteractor

// --------------------------------------------------------------------------
#if !defined(__Ilv31_Chartint_H)
#include <ilviews/chartint.h>
#endif
class ILV31VAREXPORTED IlvViewVarChartInteractorDragYPoint
: public IlvViewChartInteractorDragYPoint {
public:
    IlvViewVarChartInteractorDragYPoint(IlUInt whichButton = IlvLeftButton)
    : IlvViewChartInteractorDragYPoint(whichButton) {}
    // ____________________________________________________________
    virtual void doIt(IlvContainer*, IlvChart*, IlUInt, IlvPoint&);
    virtual const char* className() const;
};

ILV31VARMODULEINIT(vcontint);
#endif /* !__Ilv31_Vcontint_H */
