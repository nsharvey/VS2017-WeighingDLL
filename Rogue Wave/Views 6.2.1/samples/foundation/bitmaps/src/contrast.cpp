// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/src/contrast.cpp
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
// Using IlvIndexedBitmapData. 
// --------------------------------------------------------------------------

#include <contrast.h>

#if defined(IL_STD)
#include <cstdlib>
IL_STDUSE
#else
#include <stdlib.h>
#endif

// --------------------------------------------------------------------------
// Callback
// --------------------------------------------------------------------------
static void
ContrastCB(IlvGraphic* g, IlAny arg)
{
    IL_CAST(Contrast*, arg)->contrastChanged();
}

// --------------------------------------------------------------------------
// Panel class for sample Contrast
// --------------------------------------------------------------------------
Contrast::Contrast(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename),
      _srcdata(0),
      _dsticon(0),
      _slider(0)
{
    initContrast();
}

// --------------------------------------------------------------------------
Contrast::~Contrast()
{
    _srcdata->unLock();
    _cmap->unLock();
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Contrast::initContrast()
{
    const char* CONTRASTBITMAPNAME = "cat.png";

    IlvDisplay* display = getDisplay();
    IlvBitmapData* data = display->readBitmapData(CONTRASTBITMAPNAME);
    if (data->getDepth() == 8) {
	_srcdata = (IlvIndexedBitmapData*)data;
    }
    else {
	IlvWUQuantizer wuquant;
	_srcdata = wuquant.quantize(data, 240);
	delete data;
    }
    _srcdata->lock();
    _cmap = _srcdata->getColorMap();
    _cmap->lock();

    IlUInt width = _srcdata->getWidth();
    IlUInt height = _srcdata->getHeight();
    
    addObject(new IlvIcon(display, 
			  IlvPoint(10, 25), 
			  new IlvBitmap(display, _srcdata)));
    addObject(_dsticon = new IlvIcon(display, 
				     IlvPoint(width + 45, 25), 
				     new IlvBitmap(display, _srcdata)));
    _slider = (IlvSlider*)getObject("slider");
    _slider->setFocusable(IlFalse);
    _slider->setValues(-255, 255, 0);
    _slider->setPageIncrement(1);
    _slider->setCallback(ContrastCB, this);
    // resize(width * 2 + 60, height + 20);
}

// --------------------------------------------------------------------------
// Called when contrast changed
// --------------------------------------------------------------------------
void 
Contrast::contrastChanged()
{
    IlvInt contrast = _slider->getValue();
    IlUInt ncols = _cmap->getColorNum();
    IlvColorMap* newcmap = new IlvColorMap(ncols);
    for (IlUInt idx = 0; idx < ncols; ++idx) {
	IlUChar r, g, b;
	_cmap->getEntry(idx, r, g, b);
	if (contrast > 0) {
	    newcmap->setEntry(idx, 
			      (IlUChar)(r >= (255 - contrast)
					? 255
					: r + (IlUChar)contrast),
			      (IlUChar)(g >= (255 - contrast)
					? 255
					: g + (IlUChar)contrast),
			      (IlUChar)(b >= (255 - contrast)
					? 255
					: b + (IlUChar)contrast));
	}
	else {
	    newcmap->setEntry(idx, 
			      (IlUChar)(r <= IlAbs(contrast)
					? 0
					: r + contrast),
			      (IlUChar)(g <= IlAbs(contrast)
					? 0
					: g + contrast),
			      (IlUChar)(b <= IlAbs(contrast)
					? 0
					: b + contrast));
	}
    }
    _srcdata->setColorMap(newcmap);
    _dsticon->setBitmap(new IlvBitmap(getDisplay(), _srcdata));
    initReDraw();
    invalidateRegion(_dsticon);
    reDrawView(IlFalse, IlTrue);
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
DefinePageContrast(Pan* mainPanel)
{
    Contrast* panel = new Contrast(mainPanel, "contrast.ilv");
    mainPanel->addPageNoteBook(panel, "Contrast", "contrast.txt");
}
