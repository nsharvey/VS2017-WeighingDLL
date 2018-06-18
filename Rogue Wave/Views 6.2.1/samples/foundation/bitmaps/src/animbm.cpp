// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/src/animbm.cpp
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

#include <animbm.h>

#if defined(IL_STD)
#include <cstdlib>
#include <cmath>
IL_STDUSE
#else
#include <stdlib.h>
#include <math.h>
#endif

#if !defined(M_PI)
#define M_PI 3.141592653
#endif

// --------------------------------------------------------------------------
// Callbacks
// --------------------------------------------------------------------------
static IlBoolean 
UpdateProc(IlAny arg)
{
    IL_CAST(Rotation*, arg)->update();
    return IlFalse;
}

// --------------------------------------------------------------------------
static void
Blur(IlvContainer* cont, IlvEvent&, IlAny) 
{
    Rotation* container = IL_CAST(Rotation*, cont);
    container->setMotionBlur(!container->getMotionBlur());
}

// --------------------------------------------------------------------------
// Panel class for sample Rotation
// --------------------------------------------------------------------------

const IlUInt tilewidth = 100;
const IlUInt tileheight = 100;

// --------------------------------------------------------------------------
Rotation::Rotation(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename),
      _previewFrame(0),
      _srcData(0),
      _dstData(0),
      _mtnData(0),
      _angle(0),
      _zoom((IlvFloat)1.5),
      _zoomFactor((IlvFloat)0.025),
      _blur(IlFalse)
{
    initRotation();
}

// --------------------------------------------------------------------------
Rotation::~Rotation()
{
    _srcData->unLock();
    _dstData->unLock();
    _mtnData->unLock();
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Rotation::initRotation()
{
    const char* FILENAME = "rwlogo.png";

    IlvDisplay* display = getDisplay();
    _srcData = (IlvRGBBitmapData*)(display->readBitmapData(FILENAME));
    _srcData->lock();
    _dstData = new IlvRGBBitmapData(tilewidth, tileheight);
    _dstData->lock();
    _mtnData = new IlvRGBBitmapData(tilewidth, tileheight);
    _mtnData->lock();
    _icon = new IlvIcon(display, 
			IlvPoint(10, 25),
			new IlvBitmap(display, _srcData));
    addObject(_icon);
    for (IlUInt idx = 0; idx < 360; ++idx) {
	_cost[idx] = (IlFloat)cos(idx / 180.0 * M_PI);
	_sint[idx] = (IlFloat)sin(idx / 180.0 * M_PI);	
    }
    _srcWidth = _srcData->getWidth();
    _srcHeight = _srcData->getHeight();
    _dstHalfWidth = (IlInt)(tilewidth / 2);
    _dstHalfHeight = (IlInt)(tileheight / 2);

    addAccelerator(Blur, IlvButtonDown, IlvLeftButton);
    addAccelerator(Blur, IlvKeyDown, ' ');
    IlvEventLoop::getEventLoop()->addIdleProc(UpdateProc, (IlAny)this);
    _previewFrame = (IlvFrame*)getObject("Frame");
}

// --------------------------------------------------------------------------
void 
Rotation::setMotionBlur(IlBoolean blur)
{ 
    _blur = blur;
    if (_blur) {
	_mtnData->fill(IlvRect(0, 0, tilewidth, tileheight), 255, 0, 0);
	if (_previewFrame) {
	    _previewFrame->setLabel("Preview with Blur effect");
	}
    }
    else if (_previewFrame) {
	_previewFrame->setLabel("Preview");
    }
}

// --------------------------------------------------------------------------
void
Rotation::update()
{
    IlInt i, j;
    for (i = -_dstHalfHeight; i < _dstHalfHeight; ++i) {
	for (j = -_dstHalfWidth; j < _dstHalfWidth; ++j) {
	    IlInt x, y;
	    x = (IlInt)((j * _cost[_angle] + i * _sint[_angle]) * _zoom); 
	    y = (IlInt)((j * _sint[_angle] - i * _cost[_angle]) * _zoom);
	    _dstData->fastCopyPixel(_dstHalfWidth + i,
				    _dstHalfHeight + j,
				    _srcData, 
				    abs((int)(x % _srcHeight)), 
				    abs((int)(y % _srcWidth)));
	}
    }
    if (_blur) {
	IlvRect rect(0, 0, _dstHalfWidth * 2, _dstHalfHeight * 2);
	IlvPoint point;
	_dstData->blend(_mtnData, rect, point, 140);
	_mtnData->copy(_dstData, rect, point);
    }	
    _angle += 2;
    if (_angle >= 360) {
	_angle = 0;
    }
    _zoom += _zoomFactor;
    if (_zoom >= 1.5) {
	_zoomFactor = (IlFloat)-0.025;
    }
    else if (_zoom <= 0.5) {
	_zoomFactor = (IlFloat)0.025;
    }
    IlvRect bbox;
    boundingBox(bbox);
    IlvRGBBitmapData* realdata =
	new IlvRGBBitmapData(bbox.w() - 20, bbox.h() - 35);
    realdata->tile(_dstData, IlvPoint(0, 0));
    _icon->setBitmap(new IlvBitmap(getDisplay(), realdata));
    delete realdata;
    initReDraw();
    invalidateRegion(_icon);
    invalidateRegion(_previewFrame);
    reDrawView(IlFalse, IlTrue);
}

// --------------------------------------------------------------------------
// Defines the notebook page
// --------------------------------------------------------------------------
void 
DefinePageRotation(Pan* mainPanel)
{
    Rotation* panel = new Rotation(mainPanel, "rotation.ilv");
    mainPanel->addPageNoteBook(panel, "Rotate", "rotation.txt");
}
