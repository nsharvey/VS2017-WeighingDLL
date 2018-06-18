// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/projimg/include/centeri.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of center interactor class
// --------------------------------------------------------------------------
#ifndef _CenterInteractor_H
#define _CenterInteractor_H

#include <ilviews/manager/manager.h>

// --------------------------------------------------------------------------
class CenterInteractor
    : public IlvManagerViewInteractor
{
public:
    CenterInteractor(IlvManager* manager,
		     IlvView*    view);
    ~CenterInteractor();
    virtual IlBoolean handleEvent(IlvEvent&);
    virtual void doIt(IlvEvent&);
    virtual void drawGhost();
    virtual IlBoolean canCenter(IlvEvent&);
    virtual void mouseMoved(IlvEvent&);
    IlBoolean inRange(IlvPoint&);
    void cursor(IlvEvent&);
    virtual void abort();

private:
    IlUShort _button;
    IlvCursor* _centerCursor;
    IlvCursor* _forbidCursor;
    IlvCursor* _oldCursor;
    IlvCursor* _currentCursor;
};

#endif
