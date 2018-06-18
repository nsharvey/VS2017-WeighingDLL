// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/mkpyrint.cpp
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
//
// --------------------------------------------------------------------------
#include <ilviews/mkpyrint.h>
#include <ilviews/pyrrect.h>

// --------------------------------------------------------------------------
IlvMakePyrRectangleInteractor::IlvMakePyrRectangleInteractor(IlvManager* manager,
							   IlvView*    mview)
: IlvManagerViewInteractor(manager, mview), _state(Waiting)
{
}

// --------------------------------------------------------------------------
IlvMakePyrRectangleInteractor::IlvMakePyrRectangleInteractor()
: IlvManagerViewInteractor(), _state(Waiting)
{
}

// --------------------------------------------------------------------------
IlvMakePyrRectangleInteractor::~IlvMakePyrRectangleInteractor()
{
}

// --------------------------------------------------------------------------
void
IlvMakePyrRectangleInteractor::abort()
{
    if (_state == DraggingPoint) {
	_state = DraggingRectangle;
	drawGhost();
    }
    _state = Waiting;
}

// --------------------------------------------------------------------------
void
IlvMakePyrRectangleInteractor::doIt()
{
    _state = Waiting;
    IlvGraphic* obj = new IlvPyramidRectangle(manager()->getDisplay(),
					      _rect, _point);
    manager()->deSelect();
    manager()->addObject(obj);
    manager()->makeSelected(obj);
}

// --------------------------------------------------------------------------
void
IlvMakePyrRectangleInteractor::drawGhost()
{
    switch (_state) {
    case DraggingRectangle:
	if (_rect.w()) {
	    IlvRect rect(_rect);
	    if (getTransformer()) getTransformer()->apply(rect);
	    manager()->getDisplay()->fillRectangle(getView(),
						   manager()->getPalette(),
						   rect);
	}
	break;
    case DraggingPoint:
	{
	    IlvDisplay*  d = manager()->getDisplay();
	    IlvPalette*  p = manager()->getPalette();
	    IlvRect rect(_rect);
	    IlvPoint point(_point);
	    if (getTransformer()) {
		getTransformer()->apply(rect);
		getTransformer()->apply(point);
	    }
	    IlvPoint pul(rect.x(),           rect.y()),
	             pll(rect.x(),  (IlvDim)(rect.bottom()-1)),
	             pur((IlvDim)(rect.right()-1), rect.y()),
	             plr((IlvDim)(rect.right()-1),
			 (IlvDim)(rect.bottom()-1));
	    if (point.x() < rect.x()) { // Point at left of rectangle
		if (point.y() < rect.y()) {
		    d->drawLine(getView(), p, point, pur);
		    d->drawLine(getView(), p, point, pul);
		    d->drawLine(getView(), p, point, pll);
		}
		else if (point.y() > rect.bottom()) {
		    d->drawLine(getView(), p, point, pul);
		    d->drawLine(getView(), p, point, pll);
		    d->drawLine(getView(), p, point, plr);
		}
		else {
		    d->drawLine(getView(), p, point, pul);
		    d->drawLine(getView(), p, point, pll);
		}
	    } else  // Point at right of rectangle
		if (point.x() >= rect.right()) {
		    if (point.y() < rect.y()) {
			d->drawLine(getView(), p, point, pul);
			d->drawLine(getView(), p, point, pur);
			d->drawLine(getView(), p, point, plr);
		    }
		    else if (point.y() >= rect.bottom()) {
			d->drawLine(getView(), p, point, pur);
			d->drawLine(getView(), p, point, plr);
			d->drawLine(getView(), p, point, pll);
		    }
		    else {
			d->drawLine(getView(), p, point, pur);
			d->drawLine(getView(), p, point, plr);
		    }
		} else {                  // Point over or under rectangle
		    if (point.y() < rect.y()) {
			d->drawLine(getView(), p, point, pul);
			d->drawLine(getView(), p, point, pur);
		    }
		    else if (point.y() >= rect.bottom()) {
			d->drawLine(getView(), p, point, pll);
			d->drawLine(getView(), p, point, plr);
		    }
		}
        }
    default:
	break;
    }
}

// --------------------------------------------------------------------------
IlBoolean
IlvMakePyrRectangleInteractor::handleEvent(IlvEvent& event)
{
    IlBoolean consumed = IlFalse;

    switch (event.type()) {
    case IlvKeyDown:
    case IlvKeyUp:
	consumed = manager()->shortCut(event, _mgrview);
	break;
    case IlvButtonDown:
	if (event.button() != IlvLeftButton)
	    consumed = manager()->shortCut(event, _mgrview);
	else
	    switch (_state) {
	    case Waiting:
		_rect.move(event.x(), event.y());
		_rect.w(0);
		_state = DraggingRectangle;
		consumed = IlTrue;
		break;
	    }
	break;
    case IlvButtonDragged:
	if (event.modifiers() != IlvLeftButton)
	    consumed = manager()->shortCut(event, _mgrview);
	else {
	    IlvPoint p(event.x(), event.y());
	    if (getTransformer()) getTransformer()->inverse(p);
	    switch (_state) {
	    case DraggingRectangle:
		if (_rect.w()) drawGhost();
		_rect.resize((IlvDim)(IlvMax(_rect.x(), p.x()) - _rect.x()),
		    (IlvDim)(IlvMax(_rect.y(), p.y()) - _rect.y()));
		if (_rect.x() > p.x()) _rect.x(p.x());
		if (_rect.y() > p.y()) _rect.y(p.y());
		ensureVisible(IlvPoint(event.x(), event.y()));
		drawGhost();
		consumed = IlTrue;
		break;
	    case DraggingPoint:
		drawGhost();
		_point = p;
		ensureVisible(IlvPoint(event.x(), event.y()));
		drawGhost();
		consumed = IlTrue;
	    default:
		break;
	    }
	}
	break;
    case IlvButtonUp:
	if (event.button() != IlvLeftButton)
	    consumed = manager()->shortCut(event, _mgrview);
	else
	    switch (_state) {
	    case DraggingRectangle:
	    {
		if (!_rect.w()) {
		    _state = Waiting;
		    return IlTrue;
		}
		// Do not draw ghost !!
		_state = DraggingPoint;
		_point.move(_rect.x(), _rect.y());
		consumed = IlTrue;
	    }
	    break;
	    case DraggingPoint:
	    {
		drawGhost();
		_state = DraggingRectangle;
		drawGhost();
		doIt();
		callPrevious();
		consumed = IlTrue;
	    }
	    break;
	    default:
		break;
	    }
    }
    return consumed;
}
