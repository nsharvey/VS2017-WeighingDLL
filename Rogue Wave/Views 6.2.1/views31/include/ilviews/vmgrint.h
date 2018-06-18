// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/vmgrint.h
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
// Declaration of predefined IlvVariableManagerObjectInteractor classes
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Vmgrint_H
#define __Ilv31_Vmgrint_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Objinter_H)
#include <ilviews/objinter.h>
#endif
#if !defined(__Ilv31_Mgrinter_H)
#include <ilviews/mgrinter.h>
#endif

// --------------------------------------------------------------------------
#define IlvVariableManagerMoveInteractor IlvManagerMoveInteractor

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableManagerReshapeInteractor
: public IlvManagerReshapeInteractor {
public:
    virtual void doIt(IlvManager* view, IlvGraphic* ghost,
		      IlvRect& rect, IlvTransformer* t = 0);
    virtual const char* className() const;
};

#define IlvVariableManagerGaugeInteractor IlvManagerGaugeInteractor

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableManagerChartInteractorDragYPoint
: public IlvManagerChartInteractorDragYPoint {
public:
    IlvVariableManagerChartInteractorDragYPoint(IlUInt b = IlvLeftButton)
    : IlvManagerChartInteractorDragYPoint(b) {}
    // ____________________________________________________________
    virtual void doIt(IlvManager*, IlvChart* chart,
		      IlUInt, IlvPoint& point);
    virtual const char* className() const;
};

ILV31VARMODULEINIT(vmgrint);
#endif /* !__Ilv31_Vmgrint_H */
