// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/editline.h
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
// Declaration of the IlvStEditLineInteractor class
// --------------------------------------------------------------------------

#ifndef __IlvSt_Editline_H
#define __IlvSt_Editline_H

#include <ilviews/graphics/line.h>
#include <ilviews/manager/manager.h>
#include <ivstudio/util.h>
#include <ivstudio/stselect.h>

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStEditLineInteractor
: public IlvStSubInteractor {
public:
    IlvStEditLineInteractor() : IlvStSubInteractor() {}
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvEvent& event);
    virtual void drawGhost();
    virtual void init();

    virtual void doChange();

protected:
    IlInt   _selectedPoint;	// 0: from; 1: to; 2: arrow

    virtual void handleButtonDown(IlvEvent& event);
    virtual void handleButtonUp(IlvEvent& event);
    virtual void handleButtonDrag(IlvEvent& event);

    virtual IlInt whichSelection(IlvEvent& event);
};


// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStEditArrowLineInteractor
: public IlvStEditLineInteractor {
public:
    IlvStEditArrowLineInteractor() : IlvStEditLineInteractor() {}
    // ____________________________________________________________
    virtual void doChange();
protected:
    virtual void handleButtonDown(IlvEvent& event);
    virtual void handleButtonDrag(IlvEvent& event);
    virtual IlInt whichSelection(IlvEvent& event);
};
#endif /* !__IlvSt_Editline_H */
