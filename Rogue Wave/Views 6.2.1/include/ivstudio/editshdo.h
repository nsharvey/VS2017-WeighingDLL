// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/editshdo.h
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
// Declaration of the IlvStEditShadowRectangleInteractor class
// --------------------------------------------------------------------------

#ifndef __IlvSt_Editshdo_H
#define __IlvSt_Editshdo_H

#include <ilviews/manager/manager.h>
#include <ilviews/graphics/shadrect.h>
#include <ivstudio/util.h>
#include <ivstudio/stselect.h>

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStEditShadowRectangleInteractor
: public IlvStSubInteractor {
public:
    IlvStEditShadowRectangleInteractor() : IlvStSubInteractor() {}
    // ____________________________________________________________
    virtual void drawGhost();
    virtual void init();

    virtual void doChange();
protected:
    IlvPosition	_selection;

    virtual void handleButtonDown(IlvEvent& event);
    virtual void handleButtonUp(IlvEvent& event);
    virtual void handleButtonDrag(IlvEvent& event);
    void moveShadow(const IlvPoint& p);
    void resizeShadow(const IlvPoint& p);
    IlvPosition whichSelection(const IlvPoint& p);
};

#define DEFAULT_THICKNESS 8

#endif /* !__IlvSt_Editshdo_H */
