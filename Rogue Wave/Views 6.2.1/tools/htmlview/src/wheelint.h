// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/htmlview/src/wheelint.h
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

#include <ilviews/base/inter.h>
#include <ilviews/gadgets/scgadget.h>
#include <ilviews/base/timer.h>

#define IlvDefaultSpeedIncrement 20

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
class IlvScrollableInterfaceTimer
    : public IlvTimer
{
public:
    IlvScrollableInterfaceTimer(IlvScrollableInterface* scrollable,
				IlvView* view,
				const IlvPoint& ref,
				IlvDim speed = IlvDefaultSpeedIncrement);
    ~IlvScrollableInterfaceTimer();
    // ____________________________________________________________
    IlvDim getSpeed() const { return _speed; }
    IlvPos getXOffset() const { return _mouse.x() - _ref.x(); }
    IlvPos getYOffset() const {	return _mouse.y() - _ref.y(); }
    virtual void doIt();
    virtual void mouseMoved(const IlvPoint& point);
    virtual void destroy();

protected:
    IlBoolean               _inDoIt;
    IlBoolean               _destroyAsked;
    IlvPoint                _ref;
    IlvPoint                _mouse;
    IlvScrollableInterface* _scrollable;
    IlvView*                _scrView;
    IlvCursor*              _oldCursor;
    IlvBitmap*              _bitmap;
    IlvBitmap*              _savedBitmap;
    IlvDim                  _speed;

    void showReference(IlBoolean show = IlTrue);
    void updateCursor(const IlvPoint& ref, const IlvPoint& point);
};

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
class IlvScrolledGadgetPanInteractor
    : public IlvGadgetInteractor
{
public:
    IlvScrolledGadgetPanInteractor(IlvScrolledGadget* gadget)
	: _gadget(gadget),
	  _moving(IlFalse),
	  _dragged(IlFalse),
	  _timer(0)
    {}
    ~IlvScrolledGadgetPanInteractor();
    // ____________________________________________________________
    IlBoolean isMoving() { return _moving; }
    virtual IlBoolean handleEvent(IlvGraphic* obj,
				  IlvEvent& event,
				  const IlvTransformer* t);

protected:
    IlvScrolledGadget*            _gadget;
    IlBoolean                     _moving;
    IlBoolean                     _dragged;
    IlvScrollableInterfaceTimer*  _timer;

    void startMoving(const IlvPoint& point);
    void mouseMoved(const IlvPoint& point);
    void endMoving();
};
