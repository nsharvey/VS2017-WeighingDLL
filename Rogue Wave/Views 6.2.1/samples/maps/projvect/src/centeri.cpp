// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/projvect/src/centeri.cpp
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Implementation of center interactor.
//
// --------------------------------------------------------------------------
#include <centeri.h>
#include <cursors.h>

// --------------------------------------------------------------------------
// CenterInteractor
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Center interactor prototype. Used to define a new center of projection
// --------------------------------------------------------------------------
CenterInteractor::CenterInteractor(IlvManager* manager,
				   IlvView*    view)
    : IlvManagerViewInteractor(manager, view),
      _button(IlvLeftButton),
      _centerCursor(0),
      _forbidCursor(0),
      _oldCursor(0),
      _currentCursor(0)
{
    IlvDisplay* display = manager->getDisplay();
    _oldCursor = getView()->getCursor();
    IlvBitmap* bm;
    IlvBitmap* mask;

    // some cursors and associated masks

    // center cursor
    bm = new IlvBitmap(display,
		       center_width,
		       center_height,
		       1,
		       center_bits,
		       IlTrue,
		       8);
    mask = new IlvBitmap(display,
			 center_mask_width,
			 center_mask_height,
			 1,
			 center_mask_bits,
			 IlTrue,
			 8);
    if (bm && mask) {
	_centerCursor = new IlvCursor(display,
				      16,
				      16,
				      "centerCursor",
				      bm,
				      mask);
    }
    if (_centerCursor) {
	_centerCursor->lock();
    }

    // forbiden cursor
    bm = new IlvBitmap(display,
		       forbid_width,
		       forbid_height,
		       1,
		       forbid_bits,
		       IlTrue,
		       8);
    mask = new IlvBitmap(display,
			 forbid_mask_width,
			 forbid_mask_height,
			 1,
			 forbid_mask_bits,
			 IlTrue,
			 8);
    if (bm && mask) {
	_forbidCursor = new IlvCursor(display,
				      17,
				      17,
				      "forbidCursor",
				      bm,
				      mask);
    }
    if (_forbidCursor) {
	_forbidCursor->lock();
    }
}

// --------------------------------------------------------------------------
CenterInteractor::~CenterInteractor() {
    if (_forbidCursor) {
	_forbidCursor->unLock();
	_forbidCursor = 0;
    }
    if (_centerCursor) {
	_centerCursor->unLock();
	_centerCursor = 0;
    }
}

// --------------------------------------------------------------------------
void
CenterInteractor::abort() {
     IlvManagerViewInteractor::abort();
     IlvView* view = getView();
     if (view) {
	 view->setCursor(_oldCursor);
	 view->getDisplay()->sync();
     }
     _currentCursor = 0;
}

// --------------------------------------------------------------------------
// Set the correct cursor
// --------------------------------------------------------------------------
void
CenterInteractor::cursor(IlvEvent& event) {
    if (canCenter(event)) {
	if (_currentCursor != _centerCursor) {
	    getView()->setCursor(_centerCursor);
	    _currentCursor = _centerCursor;
	}
    }
    else {
	if (_currentCursor != _forbidCursor) {
	    getView()->setCursor(_forbidCursor);
	    _currentCursor = _forbidCursor;
	}
    }
}

// --------------------------------------------------------------------------
// Virtuals to be defined in the application
// --------------------------------------------------------------------------
IlvBoolean
CenterInteractor::canCenter(IlvEvent& event)
{
    return IlFalse;
}

// --------------------------------------------------------------------------
void
CenterInteractor::mouseMoved(IlvEvent&)
{
}

// --------------------------------------------------------------------------
void
CenterInteractor::drawGhost()
{
}

// --------------------------------------------------------------------------
void CenterInteractor::doIt(IlvEvent& event)
{
}

// --------------------------------------------------------------------------
// handleEvent
// IlvButtonDragged : affect correct cursor
// IlvButtonUp : Do the job
// IlvLeaveWindow : disable interactor
// IlvEnterWindow : enable interactor
// --------------------------------------------------------------------------
IlBoolean
CenterInteractor::handleEvent(IlvEvent& event)
{
    switch (event.type()) {
    case IlvButtonDragged:
	cursor(event);
	return IlTrue;
    case IlvButtonUp:
	doIt(event);
	return IlTrue;
    case IlvPointerMoved:
	cursor(event);
	mouseMoved(event);
	return IlTrue;
    case IlvLeaveWindow:
	abort();
	return IlTrue;
    case IlvEnterWindow:
	attach(getManager(), getView());
	return IlTrue;
    default:
	break;
    }
    return getManager()->shortCut(event, getView());
}

// --------------------------------------------------------------------------
IlBoolean
CenterInteractor::inRange(IlvPoint& p)
{
    IlvView* view = getView();
    IlvRect rect;
    view->sizeVisible(rect);
    return rect.contains(p);
}
