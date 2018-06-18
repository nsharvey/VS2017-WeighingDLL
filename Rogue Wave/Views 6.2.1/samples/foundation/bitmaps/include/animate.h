// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/include/animate.h
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
// Using IlvBitmapAnimationHandler.
// This sample creates a bitmap animation handler that manages several
// bitmaps. An IlvTransparentIcon is used to display the animated bitmap.
// --------------------------------------------------------------------------

#ifndef __Ilv_Samples_Animate_H
#define __Ilv_Samples_Animate_H

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/graphics/icon.h>
#include <ilviews/bitmaps/data.h>
#include <ilviews/bitmaps/png.h>

#include <app.h>

class MyBitmapAnimationHandler;

// --------------------------------------------------------------------------
// Panel class for sample Animate
// --------------------------------------------------------------------------
class Animate : public PageNoteBook 
{
 public:
    Animate(IlvAbstractView* view, const char* filename);
    ~Animate();

 protected:

    void			initAnimate();

    MyBitmapAnimationHandler*	_animHandler;
    IlvRGBBitmapData*		_firstData;
    IlvRGBBitmapData*		_lastData;
};

#endif /* !__Ilv_Samples_Animate_H*/
