// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/src/animate.cpp
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

#include <animate.h>

#if defined(IL_STD)
#include <cstdlib>
IL_STDUSE
#else
#include <stdlib.h>
#endif

// --------------------------------------------------------------------------
// Subclass of IlvBitmapAnimationHandler that handles one IlvBitmap object
// per frame
class MyBitmapAnimationHandler : public IlvBitmapAnimationHandler
{
public:
    MyBitmapAnimationHandler(IlUInt speed = 50)
	: _frames(5),
	  _speed(speed)
    {
    }
    ~MyBitmapAnimationHandler()
    {
	for (IlUInt i = 0; i < getFramesCount(); i++)
	    getFrame(i)->unLock();
    }

    IlvBitmap*		getFrame(IlUInt index) const 
    {
	return IL_CAST(IlvBitmap*, _frames[index]);
    }
    void		addFrame(IlvBitmap* bitmap)
    {
	bitmap->lock();
	_frames.add(bitmap);
    }
    
    // -------------------------------------------------------------------
    // Overridables
    // -------------------------------------------------------------------
    virtual IlUInt getFrameDelay(IlUInt /* frame */) const
    {
	return _speed;
    }
    virtual IlUInt	getFramesCount() const
    {
	return _frames.getLength();
    }
    virtual void	drawFrame(IlvPort*		dst,
				  IlvPalette*		palette,
				  const IlvRect&	rect,
				  IlUInt		index,
				  const IlvRegion*	clip,
				  IlvPosition		alignment,
				  IlBoolean		transparent) const
    {
	IlvBitmap* frame = getFrame(index);
	if (transparent && !frame->getMask()) {
            frame->computeMask();
	}
        dst->drawBitmap(palette,
                        frame,
                        IlvRect(0, 0, frame->width(), frame->height()),
                        rect,
                        clip,
                        alignment,
                        transparent);
    }

protected:
    IlArray		_frames;
    IlUInt		_speed;
};

// --------------------------------------------------------------------------
// Panel class for sample Animate
// --------------------------------------------------------------------------
Animate::Animate(IlvAbstractView* view, const char* filename)
    : PageNoteBook(view, filename),
      _animHandler(0),
      _lastData(0),
      _firstData(0)
{
    initAnimate();
}

// --------------------------------------------------------------------------
Animate::~Animate()
{
    _firstData->unLock();
    _lastData->unLock();
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Animate::initAnimate()
{
    const char* ANIMATEPNG1NAME = "logo1.png";
    const char* ANIMATEPNG2NAME = "logo2.png";
    const char* ANIMATEPNG3NAME = "logo3.png";
    const char* ANIMATEPNG4NAME = "logo4.png";
    const char* ANIMATEPNG5NAME = "logo5.png";

    IlvDisplay* display = getDisplay();
    // How to read and display a bitmap
    _firstData = (IlvRGBBitmapData*)display->readBitmapData(ANIMATEPNG1NAME);
    _firstData->lock();
    IlUInt width = _firstData->getWidth();
    IlUInt height = _firstData->getHeight();
    IlvTransparentIcon* firsticon = 
	new IlvTransparentIcon(display,
			       IlvPoint(80, 20), 
			       new IlvBitmap(display, _firstData));
    addObject(firsticon);
    // End of how to

    _lastData = (IlvRGBBitmapData*)display->readBitmapData(ANIMATEPNG5NAME);
    _lastData->lock();
    IlvTransparentIcon* lasticon = 
	new IlvTransparentIcon(display,
			       IlvPoint(80, 105), 
			       new IlvBitmap(display, _lastData));
    addObject(lasticon);

    // How to animate several pictures
    _animHandler = new MyBitmapAnimationHandler(200);
    // Add the frames
    IlvBitmap* frame1 = display->readBitmap(ANIMATEPNG1NAME);
    IlvBitmap* frame2 = display->readBitmap(ANIMATEPNG2NAME);
    IlvBitmap* frame3 = display->readBitmap(ANIMATEPNG3NAME);
    IlvBitmap* frame4 = display->readBitmap(ANIMATEPNG4NAME);
    IlvBitmap* frame5 = display->readBitmap(ANIMATEPNG5NAME);
    if (!frame1 || !frame2 || !frame3 || !frame4 || !frame5) {
	IlvFatalError("Unable to load the bitmaps !");
	IlvExit(1);
    }
    _animHandler->addFrame(frame1);
    _animHandler->addFrame(frame2);
    _animHandler->addFrame(frame3);
    _animHandler->addFrame(frame4);
    _animHandler->addFrame(frame5);
    _animHandler->addFrame(frame4);
    _animHandler->addFrame(frame3);
    _animHandler->addFrame(frame2);

    // Create a bitmap from the first frame of the animation.
    // This bitmap is only used by objects that do not support animation,
    // otherwise the frames added to the animation handler are used to
    // draw the bitmap.
    IlvBitmap* bitmap = new IlvBitmap(display,
				      _animHandler->getFrame(0)->width(),
				      _animHandler->getFrame(0)->width(),
				      display->screenDepth());
    bitmap->drawBitmap(display->defaultPalette(),
		       _animHandler->getFrame(0),
		       IlvRect(0, 0, bitmap->width(), bitmap->height()),
		       IlvPoint(0, 0));
    bitmap->setMask(_animHandler->getFrame(0)->getMask());

    // Set the animation handler to the created bitmap
    bitmap->setAnimationHandler(_animHandler);
    // Create a transparent icon
    IlvTransparentIcon* icon =
	new IlvTransparentIcon(display, IlvPoint(10, 170), bitmap);
    IlvRect bbox;
    icon->boundingBox(bbox);
    icon->move(80, 225 - (bbox.h() / 2));

    // Add it to the container
    addObject(icon);

    // Set the double buffering
    //setDoubleBuffering(IlTrue);
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageAnimate(Pan* mainPanel)
{
    Animate* panel = new Animate(mainPanel, "animate.ilv");
    mainPanel->addPageNoteBook(panel, "Animate", "animate.txt");
}
