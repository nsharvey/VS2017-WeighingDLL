// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/mkpyrint.h
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
// Declaration of the IlvMakePyrRectangleInteractor class
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Mkpyrint_H
#define __Ilv1X_Mkpyrint_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif

typedef enum IlvMakePyrRectInteractorState {
    Waiting,
    DraggingRectangle,
    DraggingPoint
    } _IlvMakePyrRectInteractorState;

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvMakePyrRectangleInteractor
: public IlvManagerViewInteractor {
public:
    IlvMakePyrRectangleInteractor(IlvManager* ed, IlvView* ev);
    IlvMakePyrRectangleInteractor();
    ~IlvMakePyrRectangleInteractor();
    // ____________________________________________________________
    IlBoolean handleEvent(IlvEvent &event);
    virtual void doIt();
    virtual void abort();
    virtual void drawGhost();
private:
    IlvMakePyrRectInteractorState _state;
    IlvRect  _rect;
    IlvPoint _point;
};

#endif /* !__Ilv1X_Mkpyrint_H */
