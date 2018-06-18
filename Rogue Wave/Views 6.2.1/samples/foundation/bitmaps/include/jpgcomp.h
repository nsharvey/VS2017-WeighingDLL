// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/include/jpgcomp.h
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
// Using the JPEG streamer. 
// --------------------------------------------------------------------------

#ifndef __Ilv_Samples_Jpgcomp_H
#define __Ilv_Samples_Jpgcomp_H

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/slider.h>
#include <ilviews/graphics/icon.h>
#include <ilviews/bitmaps/data.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/graphics/tooltip.h>
#include <ilviews/bitmaps/jpg.h>

#include <app.h>

// --------------------------------------------------------------------------
// Panel class for sample Jpgcomp
// --------------------------------------------------------------------------
class JpgComp : public PageNoteBook 
{
public:
    JpgComp(IlvAbstractView* view, const char* filename);
    ~JpgComp();
    
    void		qualityChanged();

 protected:

    void		initJpgComp();

    IlvRGBBitmapData*	_srcdata;
    IlvIcon*		_dsticon;
    IlvSlider*		_slider;
};

#endif /* !__Ilv_Samples_Jpgcomp_H*/
