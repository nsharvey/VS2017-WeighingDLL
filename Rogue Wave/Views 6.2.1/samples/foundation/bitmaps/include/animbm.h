// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/include/animbm.h
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
// Using IlvBitmapData. 
// --------------------------------------------------------------------------

#ifndef __Ilv_Samples_Animbm_H
#define __Ilv_Samples_Animbm_H

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/gadgets/text.h>
#include <ilviews/graphics/icon.h>
#include <ilviews/bitmaps/data.h>
#include <ilviews/bitmaps/png.h>

#include <app.h>

// --------------------------------------------------------------------------
// Panel class for sample Rotation
// --------------------------------------------------------------------------
class Rotation : public PageNoteBook 
{
public:
    Rotation(IlvAbstractView* view, const char* filename);
    ~Rotation();
    
    void		update();

    void		setMotionBlur(IlBoolean blur);
    IlBoolean		getMotionBlur() const { return _blur; }

 protected:

    void		initRotation();

    IlvFrame*		_previewFrame;
    IlvIcon*		_icon;
    IlvRGBBitmapData*	_srcData;
    IlvRGBBitmapData*	_dstData;
    IlvRGBBitmapData*	_mtnData;
    IlInt		_angle;
    IlFloat		_sint[360];
    IlFloat		_cost[360];
    IlFloat		_zoom;
    IlFloat		_zoomFactor;
    IlUInt		_srcWidth;
    IlUInt		_srcHeight;
    IlInt		_dstHalfWidth;
    IlInt		_dstHalfHeight;
    IlBoolean		_blur;
};

#endif /* !__Ilv_Samples_Animbm_H*/
