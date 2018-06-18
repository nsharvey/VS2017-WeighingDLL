// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/src/createbm.cpp
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

#include <createbm.h>

#if defined(IL_STD)
#include <fstream>
#include <cmath>
IL_STDUSE
#else
#include <fstream.h>
#include <math.h>
#endif

static IlFloat const FloatPi = 3.141592653F;

// --------------------------------------------------------------------------
// Callback
// --------------------------------------------------------------------------
static void
SaveCB(IlvGraphic* g, IlAny arg)
{
    IL_CAST(Createbm*, arg)->save();
}

// --------------------------------------------------------------------------
// Panel class for sample Createbm
// --------------------------------------------------------------------------
Createbm::Createbm(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename),
      _text(0)
{
    initCreatebm();
}

// --------------------------------------------------------------------------
Createbm::~Createbm()
{
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Createbm::initCreatebm()
{
    IlvRect dims(0, 0, 284, 284);
    IlvUInt x, y;
    IlvDisplay* display = getDisplay();

    /*
    IlvRGBBitmapData* backdata = new IlvRGBBitmapData(1, dims.h());
    backdata->lock();
    for (y = 0; y < dims.h(); ++y) {
	IlvUChar value = 255 - (IlvUChar)(255.0 * y / dims.h());
	backdata->setRGBPixel(0, 
			      y, 
			      value,
			      value,
			      value);
    }
    setBackgroundBitmap(new IlvBitmap(display, backdata));
    backdata->unLock();
    */
    IlvUInt width = (IlvUInt)dims.w() - 20;
    IlFloat centerx = width / 2.F;
    IlFloat centerx2 = centerx * centerx;
    IlvRGBBitmapData* bdata = new IlvRGBBitmapData(width, width);
    IlvBWBitmapData* mask = new IlvBWBitmapData(width, width);
    bdata->lock();
    mask->lock();
    for (y = 0; y < width; ++y) {
	for (x = 0; x < width; ++x) {
	    IlvInt dx = (IlvInt)(centerx - x);
	    IlvInt dy = (IlvInt)(centerx - y);
	    IlvInt dx2 = dx * dx;
	    IlvInt dy2 = dy * dy;
	    IlFloat hue;
	    if ((dx != 0) || (dy != 0)) {
		hue = IL_CAST(IlFloat, atan2((double)dy, (double)dx));
		if (hue  < 0.F)
		    hue += 2.F * FloatPi;
		hue *= 180.F / FloatPi;
	    }
	    else {
		hue = 0;
	    }
	    if ((dx2 + dy2) >= centerx2) {
		bdata->setRGBPixel(x, y, 0, 0, 0);
		mask->setPixel(x, y, 0);
	    }
	    else {
		IlFloat sat =
		    IL_CAST(IlFloat, sqrt((double) (dx2 + dy2)) / centerx);
		IlvIntensity r;
		IlvIntensity g;
		IlvIntensity b;
		IlvHSVToRGB(hue, sat, 1.F, r, g, b);
		bdata->setRGBPixel(x, y, r / 256, g / 256, b / 256);
		mask->setPixel(x, y, 255);
	    }
	}
    }
    bdata->setMask(mask);
    mask->unLock();
    addObject(new IlvTransparentIcon(display, 
				     IlvPoint(310, 20), 
				     new IlvBitmap(display,bdata)));
    bdata->unLock();
    IlvButton* btn = (IlvButton*)getObject("Save");
    btn->setCallback(SaveCB,this);
    
    _text = (IlvText*)getObject("Msg");
    if (_text) {
      _text->setText("");
    }
}

// --------------------------------------------------------------------------
void
Createbm::save()
{
    ofstream output("createbm.jpg"
#if defined(_WIN32)
		    , ios::binary
#endif
		    );
    IlvBitmapData* bdata = IlvSystemPort::GetBitmapData(this);
    IlvBitmapStreamer::Get("IlvJPGStreamer")->write(bdata, output);
    delete bdata;
    if (_text) {
        _text->addLine("The file createbm.jpg");
	_text->addLine("has been created...");
        reDrawObj(_text);
    }
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
DefinePageCreatebm(Pan* mainPanel)
{
    Createbm* panel = new Createbm(mainPanel, "createbm.ilv");
    mainPanel->addPageNoteBook(panel, "Create", "createbm.txt");
}
