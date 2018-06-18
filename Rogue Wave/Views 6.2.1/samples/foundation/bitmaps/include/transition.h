// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/include/transition.h
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
// Using IlvBitmapTransition classes.
// --------------------------------------------------------------------------

#ifndef __Ilv_Samples_Transition_H
#define __Ilv_Samples_Transition_H

#include <ilviews/bitmaps/jpg.h>
#include <ilviews/bitmaps/bmp.h>
#include <ilviews/bitmaps/transition.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/graphics/inter.h>
#include <ilviews/graphics/icon.h>
#include <ilviews/gadgets/slider.h>
#include <ilviews/gadgets/combo.h>
#include <ilviews/util/transition.h>

#include <app.h>

// --------------------------------------------------------------------------
// Panel class for sample Transition
// --------------------------------------------------------------------------
class Transition : public PageNoteBook 
{
public:
    Transition(IlvAbstractView* view, const char* filename);
    ~Transition();
    
    void		speedChanged();
    void		transitionChanged();
    void		doIt();

protected:
    void		initTransition();

    IlvButton*		_image;
    IlvRGBBitmapData*	_image1;
    IlvRGBBitmapData*	_image2;
    IlvBitmapTransition* _transition;
    IlvTransitionScheduler* _scheduler;
    IlUInt		_duration;
    IlBoolean		_first;
};

#endif /* !__Ilv_Samples_Transition_H*/

