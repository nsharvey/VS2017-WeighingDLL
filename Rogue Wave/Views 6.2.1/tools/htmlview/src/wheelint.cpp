// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/htmlview/src/wheelint.cpp
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
// Demonstrating the use of IlvMouseWheel event through an interactor
// ----------------------------------------------------------------------------

#include "../src/wheelint.h"

#include <ilviews/graphics/holder.h>
#include <ilviews/contain/inter.h>
#include <ilviews/gadgets/scgadget.h>

#define TIMER_PERIOD 30
#define DRAGDELTA 10

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
IlvScrollableInterfaceTimer::
IlvScrollableInterfaceTimer(IlvScrollableInterface* scrollable,
			    IlvView* view,
			    const IlvPoint& ref,
			    IlvDim speed)
    : IlvTimer(view->getDisplay()),
      _inDoIt(IlFalse),
      _destroyAsked(IlFalse),
      _ref(ref),
      _mouse(ref),
      _scrollable(scrollable),
      _scrView(view),
      _oldCursor(0),
      _bitmap(0),
      _savedBitmap(0),
      _speed(speed)
{
    IlvDisplay* display = view->getDisplay();
    runOnce();
  
    // Loads bitmap
    _bitmap = display->getBitmap("../data/pix/wheel.xpm");
    if (!_bitmap)
	_bitmap = display->readBitmap("../data/pix/wheel.xpm");
    if (!_bitmap)
	_bitmap = display->getDefaultBitmap();
    _bitmap->computeMask();
    _bitmap->lock();

    // Create the bitmap used to save the background
    _savedBitmap = new IlvBitmap(display,
				 _bitmap->width(),
				 _bitmap->height(),
				 view->depth());
    _savedBitmap->lock();

    // Keeps old cursor
    _oldCursor = _scrView->getCursor();
    if (_oldCursor)
	_oldCursor->lock();

    showReference(IlTrue);
    updateCursor(ref, ref);
}

// --------------------------------------------------------------------------
IlvScrollableInterfaceTimer::~IlvScrollableInterfaceTimer()
{
    _inDoIt = IlTrue;
    showReference(IlFalse);
    // Changes the cursor
    _scrView->setCursor(_oldCursor);
    if (_oldCursor)
	_oldCursor->unLock();
    _bitmap->unLock();
    _savedBitmap->unLock();
}

// --------------------------------------------------------------------------
void
IlvScrollableInterfaceTimer::destroy()
{
  if (_inDoIt)
    _destroyAsked = IlTrue;
  else
    delete this;
}

// --------------------------------------------------------------------------
void
IlvScrollableInterfaceTimer::doIt()
{
    if (!_inDoIt) {
	_inDoIt = IlTrue;
    
	// Change the sb values
	IlvPos xoff = (getXOffset() / (IlvPos)getSpeed());
	IlvPos yoff = (getYOffset() / (IlvPos)getSpeed());
	IlvScrollBar* vsb = _scrollable->getFirstScrollBar(IlvVertical);
	IlvScrollBar* hsb = _scrollable->getFirstScrollBar(IlvHorizontal);
	if (vsb && yoff) {
	    IlInt value = vsb->getValue();
	    vsb->setValue(vsb->getValue() + (yoff > 0 ? yoff * yoff : - yoff * yoff));
	    if (value != vsb->getValue()) {
		showReference(IlFalse);
		vsb->valueChanged();
		showReference(IlTrue);
		vsb->reDraw();
	    }
	}
	if (hsb && xoff) {
	    IlInt value = hsb->getValue();
	    hsb->setValue(hsb->getValue() + (xoff > 0 ? xoff * xoff : - xoff * xoff));
	    if (value != hsb->getValue()) {
		showReference(IlFalse);
		hsb->valueChanged();
		showReference(IlTrue);
		hsb->reDraw();
	    }
	}

	// Re-starts the timer or destroy it
	if (_destroyAsked)
	    delete this;
	else {
	    run(0, TIMER_PERIOD);
	    _inDoIt = IlFalse;
	}
    }
}

// --------------------------------------------------------------------------
void
IlvScrollableInterfaceTimer::showReference(IlBoolean show)
{
    IlvRect rect(_ref.x() - _bitmap->width()/2,
		 _ref.y() - _bitmap->height()/2,
		 _bitmap->width(),
		 _bitmap->height());
    if (!show) {
	// Removes the ref to allow scrolling
	_scrView->drawBitmap(getDisplay()->defaultPalette(),
			     _savedBitmap,
			     IlvRect(0, 0, rect.w(), rect.h()),
			     rect.upperLeft());
    } else {
	// First save the area that will be erased by the bitmap
	_savedBitmap->drawBitmap(getDisplay()->defaultPalette(),
				 _scrView,
				 rect,
				 IlvPoint(0, 0));
	// Then draw the bitmap
	_scrView->drawBitmap(getDisplay()->defaultPalette(),
			     _bitmap,
			     rect,
			     0,
			     IlvCenter,
			     IlTrue);
    }
}

// --------------------------------------------------------------------------
void
IlvScrollableInterfaceTimer::updateCursor(const IlvPoint&,
					  const IlvPoint&)
{
    IlvCursor* cursor = getDisplay()->getCursor("sizing");
    if (cursor) {
	cursor->lock();
	_scrView->setCursor(cursor);
	cursor->unLock();
    }
}

// --------------------------------------------------------------------------
void
IlvScrollableInterfaceTimer::mouseMoved(const IlvPoint& point)
{
    _mouse = point;
    IlvPos xoff = getXOffset();
    IlvPos yoff = getYOffset();
    if (IlAbs(xoff) > DRAGDELTA || IlAbs(yoff) > DRAGDELTA) {
	if (!isRunning())
	    run(0, TIMER_PERIOD);
    } else {
	suspend();
    }
    updateCursor(_ref, _mouse);
}

// --------------------------------------------------------------------------
IlBoolean
IlvScrolledGadgetPanInteractor::handleEvent(IlvGraphic*,
					    IlvEvent& event,
					    const IlvTransformer*)
{
    if (!isMoving()) {
	if (event.type() == IlvButtonDown &&
	    event.button() == IlvMiddleButton) {
	    startMoving(IlvPoint(event.x(), event.y()));
	    return IlTrue;
	} else
	    return _gadget->handleEvent(event);
    } else {
	if (event.type() == IlvPointerMoved ||
	    event.type() == IlvButtonDragged) {
	    mouseMoved(IlvPoint(event.x(), event.y()));
	    return IlTrue;
	} else
	    if ((event.type() == IlvButtonUp && _dragged) ||
		(event.type() == IlvButtonDown) ||
		(event.type() == IlvDoubleClick) ||
		(event.type() == IlvMultiClick) ||
		(event.type() == IlvKeyboardFocusOut)) {
		endMoving();
		return IlTrue;
	    } else
		return IlFalse;
    }
}

// --------------------------------------------------------------------------
IlvScrolledGadgetPanInteractor::~IlvScrolledGadgetPanInteractor()
{
    if (_timer) {
	_timer->destroy();
	_timer = 0;
    }
}

// --------------------------------------------------------------------------
void
IlvScrolledGadgetPanInteractor::startMoving(const IlvPoint& point)
{
    // Starts the timer
    if (_timer)
	_timer->destroy();
    _timer = new IlvScrollableInterfaceTimer(_gadget, _gadget->getView(),
					     point);
    _moving = IlTrue;
    _dragged = IlFalse;
}

// --------------------------------------------------------------------------
void
IlvScrolledGadgetPanInteractor::mouseMoved(const IlvPoint& point)
{
    _dragged = IlTrue;
    _timer->mouseMoved(point);
}

// --------------------------------------------------------------------------
void
IlvScrolledGadgetPanInteractor::endMoving()
{
    _moving = IlFalse;
    // Deletes the timer
    if (_timer) {
	_timer->destroy();
	_timer = 0;
    }
    _gadget->adjustScrollBars(IlTrue);
}
