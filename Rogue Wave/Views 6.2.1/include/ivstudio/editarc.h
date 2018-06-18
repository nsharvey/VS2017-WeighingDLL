// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/editarc.h
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
// Declaration of the IlvEditArcInteractor classe
// --------------------------------------------------------------------------

#ifndef __IlvSt_Editarc_H
#define __IlvSt_Editarc_H

#include <ilviews/graphics/arc.h>
#include <ivstudio/util.h>
#include <ivstudio/stselect.h>

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStEditArcInteractor
: public IlvStSubInteractor {
public:
    IlvStEditArcInteractor() : IlvStSubInteractor() {};
    // ____________________________________________________________
    virtual void drawGhost();
    virtual void init();

    virtual void doChange();
protected:
    IlInt 	_selection; 	// enum IlvEditArcSelection

    void handleButtonDown(IlvEvent& event);
    void handleButtonDrag(IlvEvent& event);
    void handleButtonUp(IlvEvent& event);

    IlInt whichSelection(IlvEvent& event);
};

enum IlvEditArcSelection
{
    IlvEditArcNothing = 0,
    IlvEditArcStartPoint,
    IlvEditArcEndPoint,
    IlvEditArcInArc
};

#endif /* !__IlvSt_Editarc_H */
