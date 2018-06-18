// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/mkshadin.h
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
// Declaration of the IlvMakeShadowRectangleInteractor class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Mkshadin_H
#define __Ilv_Manager_Mkshadin_H

#if !defined(__Ilv_Manager_Dragrin_H)
#include <ilviews/manager/dragrin.h>
#endif
#if !defined(__Ilv_Graphics_Shadrect_H)
#include <ilviews/graphics/shadrect.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeShadowRectangleInteractor
: public IlvDragRectangleInteractor
{
public:
    IlvMakeShadowRectangleInteractor(IlvManager* manager, IlvView* view,
			       IlUShort    button = IlvLeftButton,
			       IlBoolean   snap   = IlTrue)
	: IlvDragRectangleInteractor(manager, view, button, snap),
          _state(initState), _pos((IlvPosition)0) {}
    IlvMakeShadowRectangleInteractor(IlUShort  button = IlvLeftButton,
			       IlBoolean snap   = IlTrue)
	: IlvDragRectangleInteractor(button, snap), 
          _state(initState), _pos((IlvPosition)0) {}
    // ____________________________________________________________
    virtual IlBoolean handleEvent(IlvEvent& event);
    void         drawGhost();
    void         doIt(IlvRect&);
    void         abort();

    IlvMakeShadowRectangleInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    enum {
	initState,
	rectDone
    }            _state;
    IlvPosition  _pos;
    IlvDim       _delta;
};

ILVMGRMODULEINIT(m0_mkshadin);

#endif /* !__Ilv_Manager_Mkshadin_H */
