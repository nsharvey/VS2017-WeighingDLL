// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/src/quantize.cpp
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
// Using quantizers and streamers. 
// --------------------------------------------------------------------------

#include <quantize.h>

#if defined(IL_STD)
#include <strstream>
IL_STDUSE
#else /* !IL_STD */
#include <strstream.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
// Callback
// --------------------------------------------------------------------------
static void
QuantizeCB(IlvGraphic* g, IlAny arg)
{
    IL_CAST(Quantize*, arg)->quantize();
}

// --------------------------------------------------------------------------
// Panel class for sample Quantize
// --------------------------------------------------------------------------
static const char* BITMAPNAME = "colors.png";
#define CMAP_ICON_W 10

// --------------------------------------------------------------------------
Quantize::Quantize(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename),
      _srcdata(0),
      _dsticon(0),
      _slider(0),
      _ctoggle(0)
{
    initQuantize();
}

// --------------------------------------------------------------------------
Quantize::~Quantize()
{
    _srcdata->unLock();
}

// --------------------------------------------------------------------------
void
Quantize::initQuantize()
{
    IlvDisplay* display = getDisplay();
    _srcdata = display->readBitmapData(BITMAPNAME);
    _srcdata->lock();
    IlUInt width = _srcdata->getWidth();
    IlUInt height = _srcdata->getHeight();
    IlUInt numcols = _srcdata->getUsedColorNum();
    IlvIcon* srcicon = new IlvIcon(display, 
				   IlvPoint(10, 25), 
				   new IlvBitmap(display, _srcdata));
    ostrstream tooltipstr;
    tooltipstr << "Original Image : "
	       << (int)numcols 
	       << " colors" << ends;
    delete srcicon->setNamedProperty(new IlvToolTip(tooltipstr.str()));
    tooltipstr.rdbuf()->freeze(0);
    addObject(srcicon);
    addObject(_dsticon = new IlvIcon(display, 
				     IlvPoint(335, 25), 
				     new IlvBitmap(display, 
						   _srcdata->getWidth(), 
						   _srcdata->getHeight(), 
						   display->screenDepth())));
    _slider = (IlvSlider*)getObject("slider");
    _slider->setFocusable(IlFalse);
    _slider->setValues(256, 2, 256);
    _slider->setPageIncrement(1);
    _slider->setNamedProperty(new IlvToolTip("colors"));
    _slider->setCallback(QuantizeCB, this);
    _ctoggle =  (IlvColoredToggle*)getObject("toggle");
    _ctoggle->setFocusable(IlFalse);
    _ctoggle->setCheckColor(display->getColor("red"));
    _ctoggle->setState(IlvTrue);
    delete _ctoggle->setNamedProperty(new IlvToolTip("dithering"));
    _ctoggle->setCallback(QuantizeCB, this);
    
    IlvRect sliderBox;
    _slider->boundingBox(sliderBox);
    addObject(_cmapicon = new IlvIcon(display,
				      IlvPoint(sliderBox.right() + 2, 25),
				      new IlvBitmap(display,
						    CMAP_ICON_W,
						    height,
						    display->screenDepth())));
    //    resize(width * 2 + 90, height + 20);
    quantize();
}

// --------------------------------------------------------------------------
// Applies effect
// --------------------------------------------------------------------------
void 
Quantize::quantize()
{
    IlvDisplay* display = getDisplay();
    _wuquant.setDithering(_ctoggle->getState());
    IlvUInt numColors = IL_CAST(IlvUInt, _slider->getValue());
    IlvIndexedBitmapData* dstdata = _wuquant.quantize(_srcdata, numColors);
    ostrstream tooltipstr;
    tooltipstr << "Quantized Image : "
	       << (int)dstdata->getUsedColorNum()
	       << " colors" << ends;
    delete _dsticon->setNamedProperty(new IlvToolTip(tooltipstr.str()));
    tooltipstr.rdbuf()->freeze(0);
    _dsticon->setBitmap(new IlvBitmap(display, dstdata));
    IlvColorMap* cmap = dstdata->getColorMap();
    IlUInt height = dstdata->getHeight();
    IlUInt numcolors = cmap->getColorNum();
    IlvIndexedBitmapData* cmapdata =
	new IlvIndexedBitmapData(1, numcolors, cmap);
    for (IlUInt idx = 0; idx < numcolors; ++idx) {
	cmapdata->setPixel(0, idx, (IlUChar)idx);
    }
    IlvIndexedBitmapData* newcmapdata =
	new IlvIndexedBitmapData(CMAP_ICON_W, height, cmap);
    newcmapdata->stretch(cmapdata,
			 IlvRect(0, 0, 1, numcolors),
			 IlvRect(0, 0, CMAP_ICON_W, height));
    delete cmapdata;
    _cmapicon->setBitmap(new IlvBitmap(display, newcmapdata));
    delete newcmapdata;
    delete dstdata;
    initReDraw();
    invalidateRegion(_dsticon);
    invalidateRegion(_cmapicon);
    reDrawView(IlFalse,IlTrue);
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
DefinePageQuantize(Pan* mainPanel)
{
    Quantize* panel = new Quantize(mainPanel, "quantize.ilv");
    mainPanel->addPageNoteBook(panel, "Quantize", "quantize.txt");
}
