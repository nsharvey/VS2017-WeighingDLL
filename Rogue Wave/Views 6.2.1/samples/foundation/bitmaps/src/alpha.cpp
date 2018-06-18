// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/src/alpha.cpp
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
// Using alpha compositing. 
// --------------------------------------------------------------------------

#include <alpha.h>

#if defined(IL_STD)
#include <cstdlib>
IL_STDUSE
#else
#include <stdlib.h>
#endif

// --------------------------------------------------------------------------
// Callbacks
// --------------------------------------------------------------------------
static void
Blend(IlvGraphic* g, IlAny arg)
{
    IL_CAST(Alpha*, arg)->blend();
}

// --------------------------------------------------------------------------
static void
SwitchImages(IlvContainer* cont, IlvEvent&, IlAny)
{
    IL_CAST(Alpha*, cont)->switchImages();
    IL_CAST(Alpha*, cont)->blend();
}

// --------------------------------------------------------------------------
// Panel class for sample Alpha
// --------------------------------------------------------------------------
Alpha::Alpha(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename),
      _dstdata(0),
      _bkgdata(0),
      _blddata(0),
      _dsticon(0),
      _bkgicon(0),
      _slider(0),
      _cursrc(1)
{
    initAlpha();
}

// --------------------------------------------------------------------------
Alpha::~Alpha()
{
    _srcdata[0]->unLock();
    _srcdata[1]->unLock();
    _dstdata->unLock();
    _bkgdata->unLock();
    _blddata->unLock();
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Alpha::initAlpha()
{
    const char* BLDNAME = "biplane_shadow.png";
    const char* SRCNAME = "checkers.png";
    const char* SRCNAME2 = "gradient.png";

    IlvDisplay* display = getDisplay();
    IlvIcon* icon;
    _srcdata[0] = (IlvRGBBitmapData*)(display->readBitmapData(SRCNAME));
    _srcdata[0]->lock();
    _srcdata[1] = (IlvRGBBitmapData*)(display->readBitmapData(SRCNAME2));
    _srcdata[1]->lock();
    _blddata = (IlvRGBBitmapData*)(display->readBitmapData(BLDNAME));
    _blddata->lock();
    _bkgdata = new IlvRGBBitmapData(180,_srcdata[1]->getHeight());
    _bkgdata->lock();
    _bkgdata->copy(_srcdata[_cursrc],
		   IlvRect(0, 0, 180, _srcdata[_cursrc]->getHeight()),
		   IlvPoint());    
    
    addObject(icon = new IlvIcon(display, 
				 IlvPoint(10, 15), 
				 new IlvBitmap(display, _blddata))); 
    icon->setNamedProperty(new IlvToolTip("source image"));
    _dstdata = new IlvRGBBitmapData(_srcdata[_cursrc]->getWidth(), 
				    _srcdata[_cursrc]->getHeight());
    _dstdata->lock();
    _dstdata->copy(_srcdata[_cursrc], 
		   IlvRect(0, 0, 
			   _srcdata[_cursrc]->getWidth(), 
			   _srcdata[_cursrc]->getHeight()),
		   IlvPoint());
    addObject(_dsticon = new IlvIcon(display,
				     IlvPoint(395, 25),
				     new IlvBitmap(display, _dstdata)));
    _dsticon->setNamedProperty(new IlvToolTip("composite image"));
    
    addObject(_bkgicon = new IlvIcon(display,
				     IlvPoint(190, 25),
				     new IlvBitmap(display, _bkgdata)));
    _dsticon->setNamedProperty(new IlvToolTip("composite image"));
    
    IlvRGBBitmapData* alphachan =
	new IlvRGBBitmapData(_blddata->getWidth(), _blddata->getHeight());
    alphachan->lock();
    for (IlvUInt h = 0; h < _blddata->getHeight(); ++h) {
	for (IlvUInt w = 0; w < _blddata->getWidth(); ++w) {
	    IlvUChar alpha = 255 - _blddata->getAlpha(w, h);
	    alphachan->setRGBPixel(w, h, alpha, alpha, alpha);
	}
    }
    addObject(icon = new IlvIcon(display, 
				 IlvPoint(10, 150),
				 new IlvBitmap(display, alphachan)));
    icon->setNamedProperty(new IlvToolTip("alpha channel"));
    alphachan->unLock();
    _slider = (IlvSlider*)getObject("slider");
    _slider->setFocusable(IlFalse);
    _slider->setValues(0, 255, 0);
    _slider->setPageIncrement(1);
    _slider->setNamedProperty(new IlvToolTip("blend factor"));
    _slider->setCallback(Blend, this);
    _to.move((_srcdata[_cursrc]->getWidth() - _blddata->getWidth()) / 2,
	     (_srcdata[_cursrc]->getHeight() - _blddata->getHeight()) / 2);
    addAccelerator(SwitchImages, IlvKeyDown, ' ');
}

// --------------------------------------------------------------------------
void 
Alpha::blend()
{
    IlvUChar blend = IL_CAST(IlvUChar, _slider->getValue());
    _dstdata->copy(_srcdata[_cursrc],
		   IlvRect(0,
			   0,
			   _srcdata[_cursrc]->getWidth(), 
			   _srcdata[_cursrc]->getHeight()),
		   IlvPoint());
    _dstdata->alphaCompose(_blddata,
			   IlvRect(0,
				   0, 
				   _blddata->getWidth(),
				   _blddata->getHeight()),
			   _to,
			   blend);
    _dsticon->setBitmap(new IlvBitmap(getDisplay(), _dstdata));
    initReDraw();
    invalidateRegion(_dsticon);
    invalidateRegion(_bkgicon);
    reDrawView(IlFalse, IlTrue);
}

// --------------------------------------------------------------------------
void
Alpha::switchImages()
{
    _cursrc = 1 - _cursrc;
    _bkgdata->copy(_srcdata[_cursrc],
		   IlvRect(0, 0, 180, _srcdata[_cursrc]->getHeight()),
		   IlvPoint());    
    _bkgicon->setBitmap(new IlvBitmap(getDisplay(), _bkgdata));
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageAlpha(Pan* mainPanel)
{
    Alpha* panel = new Alpha(mainPanel, "alpha.ilv");
    mainPanel->addPageNoteBook(panel, "Alpha", "alpha.txt");
}
