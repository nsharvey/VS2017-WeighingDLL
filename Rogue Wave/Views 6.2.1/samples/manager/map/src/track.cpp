// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/manager/map/src/track.cpp
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
// Definition of the Track object
// --------------------------------------------------------------------------

#include "track.h"

#if defined(IL_STD)
IL_STDUSE
#include <cstdlib>
#include <cstdio>
#else
#include <stdlib.h>
#include <stdio.h>
#endif

// --------------------------------------------------------------------------
Track::~Track()
{
    _highlightPalette->unLock();
    _alternatePalette->unLock();
    delete [] _label;
}

// --------------------------------------------------------------------------
Track::Track(IlvDisplay*     display,
	     const IlvPoint& position,
	     const IlvPoint& destination,
	     const char*     data,
	     IlvPalette*     palette,
	     IlvPalette*     highlightPalette,
	     IlvPalette*     alternatePalette)

    : IlvSimpleGraphic(display, palette),
      _showLastPositions(IlTrue),
      _showSpeed(IlTrue),
      _showLabel(IlTrue),
      _showRoute(IlTrue),
      _speed(0),
      _height(0),
      _warningDistance(0),
      _width2(0),
      _width3(0)
{
    _highlightPalette = highlightPalette ? highlightPalette : getPalette();
    _highlightPalette->lock();
    _alternatePalette = alternatePalette ? alternatePalette : getPalette();
    _alternatePalette->lock();

    init(position, destination);
    size_t l  = strlen(data);
    _label = strcpy(new char[l + 1], data);
    _width1 = getPalette()->getFont()->stringWidth(_label);
}

// --------------------------------------------------------------------------
void
Track::init(const IlvPoint& position,
	    const IlvPoint& destination)
{
    _position    = position;
    for (IlUInt i = 0; i < TRACKMAXLASTPOSITION; ++i)
	_lastPositions[i] = _position;
    _speedPosition = _position;
    _destination = destination;
}

// --------------------------------------------------------------------------
void
Track::setSpeed(IlUInt val)
{
    _speed = val;
    sprintf(_speedStr, "%3lu Kt", (unsigned long int) _speed);
    _width2 = getPalette()->getFont()->stringWidth(_speedStr);
}

// --------------------------------------------------------------------------
void
Track::setHeight(IlUInt val)
{
    _height = val;
    sprintf(_heightStr, "%5lu Ft", (unsigned long int) _height);
    _width3 = getPalette()->getFont()->stringWidth(_heightStr);
}

// --------------------------------------------------------------------------
#define DELTA 5
#define DELTAX 10
#define DELTAY 2
// --------------------------------------------------------------------------
static inline IlBoolean
CloseTo(const IlvPoint& pos,
	const IlvPoint& dest,
	IlvDim limit)
{
    double X  = dest.x() - pos.x();
    double Y  = dest.y() - pos.y();
    return ((X * X + Y * Y) <= (double)(limit * limit));
}

// --------------------------------------------------------------------------
IlBoolean
Track::zoomable() const
{
    return IlFalse;
}

// --------------------------------------------------------------------------
void
Track::draw(IlvPort* dst,
	    const IlvTransformer* t,
	    const IlvRegion* clip) const
{
    IlvPalette* palette = _palette;
    if (_lastPositions[0] == _lastPositions[1])                  // Taking off
	palette = _highlightPalette;
    else if (CloseTo(_position, _destination, _warningDistance)) // Landing
	palette = _alternatePalette; 

    IlvPoint point, p;
    {
	IlvPushClip pushClip(*palette, clip);
	// Draw position
	point = _position;
	if (t)
	    t->apply(point);
	IlvRect rect(point.x() - DELTA, point.y() - DELTA,
		     2 * DELTA, 2 * DELTA);
	dst->drawArc(palette, rect, (IlFloat)0, (IlFloat)360);
	// Draw last positions
	IlvPos d = 2;
	if (_showLastPositions) {
	    for (IlUInt i = 0; i < TRACKMAXLASTPOSITION; ++i, ++d) {
		p = _lastPositions[i];
		if (t)
		    t->apply(p);
		rect.move(p.x() - d, p.y() - d);
		rect.resize((IlvDim)(2 * d),(IlvDim)(2 * d));
		dst->drawRectangle(palette, rect);
	    }
	}
	// Draw Speed
	if (_showSpeed) {
	    p = _speedPosition;
	    if (t)
		t->apply(p);
	    dst->drawLine(palette, point, p);
	}
	// Draw Labels
	if (_showLabel) {
	    IlvDim h = palette->getFont()->height();
	    p = point;
	    p.translate(DELTAX, 0);
	    dst->drawString(palette, p, _label, -1);
	    p.translate(0, DELTAY + h);
	    dst->drawString(palette, p, _speedStr, -1);
	    p.translate(0, DELTAY + h);
	    dst->drawString(palette, p, _heightStr, -1);
	}
    }
    // Draw the rest of the route
    if (_showRoute && !hasLanded()) {
	IlvPushClip pushClip(*_alternatePalette, clip);
	IlvPoint destination(_destination);
	if (t)
	    t->apply(destination);
	dst->drawLine(_alternatePalette, point, destination);
    }
}

// --------------------------------------------------------------------------
void
Track::boundingBox(IlvRect& bbox,
		   const IlvTransformer* t) const
{
    IlvPoint point, p;
    // Add Position
    point = _position;
    if (t)
	t->apply(point);
    IlvRect rect(point.x() - DELTA, point.y() - DELTA, 2 * DELTA, 2 * DELTA);
    bbox = rect;
    // Add Last Positions
    IlvPos d = 2;
    IlvDim dd = (IlvDim)(2 * d);
    if (_showLastPositions) {
	// Faster than code below.
	p = _lastPositions[0];
	if (t)
	    t->apply(p);
	bbox.add(IlvRect(p.x() - d, p.y() - d, dd, dd));
	p = _lastPositions[TRACKMAXLASTPOSITION - 1];
	if (t)
	    t->apply(p);
	bbox.add(IlvRect(p.x() - d, p.y() - d, dd, dd));
    }
    // Add Speed
    if (_showSpeed) {
	p = _speedPosition;
	if (t)
	    t->apply(p);
	bbox.add(p);
    }
    // Add Labels
    if (_showLabel) {
	IlvDim h = _palette->getFont()->height();
	p = point;
	p.translate(DELTAX, 0);
	rect.move(p.x(), p.y() - h + d);
	rect.resize((IlvDim)_width1, h);
	bbox.add(rect);
	p.translate(0, DELTAY + h);
	rect.move(p.x(), p.y()- h + d);
	rect.resize((IlvDim)_width2, h);
	bbox.add(rect);
	p.translate(0, DELTAY + h);
	rect.move(p.x(), p.y() - h + d);
	rect.resize((IlvDim)_width3, h);
	bbox.add(rect);
	bbox.expand(5);
    }
    // Add destination
    if (_showRoute) {
	IlvPoint dest = _destination;
	if (t)
	    t->apply(dest);
	bbox.add(dest);
    }
}

// --------------------------------------------------------------------------
void
Track::applyTransform(const IlvTransformer* t)
{
    t->apply(_position);
    for (IlUInt i = 0; i < TRACKMAXLASTPOSITION; ++i)
	t->apply(_lastPositions[i]);
    t->apply(_speedPosition);
    t->apply(_destination);
}

// --------------------------------------------------------------------------
IlBoolean
Track::contains(const IlvPoint&       p,
		const IlvPoint&       tp,
		const IlvTransformer* t) const
{
    return IlvGraphic::contains(p, tp, t);
}

// --------------------------------------------------------------------------
void
Track::newPosition(const IlvPoint& p)
{
    // Shift last positions
    IlUInt i;
    for (i = 0; i < TRACKMAXLASTPOSITION - 1; ++i)
	_lastPositions[i] = _lastPositions[i + 1];
    _lastPositions[i] = _position;
    _position = p;
    _speedPosition = _position;
    _speedPosition.translate(_position.x() -
			     _lastPositions[TRACKMAXLASTPOSITION - 1].x(),
			     _position.y() -
			     _lastPositions[TRACKMAXLASTPOSITION - 1].y());
}

// --------------------------------------------------------------------------
void
Track::translatePosition(const IlvPoint& p)
{
    IlvPoint point = _position;
    point.translate(p.x(), p.y());
    newPosition(point);
}

// --------------------------------------------------------------------------
void
Track::setFont(IlvFont* font)
{
    IlvSimpleGraphic::setFont(font);
    _width1 = getPalette()->getFont()->stringWidth(_label);
    _width2 = getPalette()->getFont()->stringWidth(_speedStr);
    _width3 = getPalette()->getFont()->stringWidth(_heightStr);
}

// --------------------------------------------------------------------------
IlvGraphic*
Track::copy() const
{
    Track* track = new Track(_palette->getDisplay(),
			     _position,
			     _destination,
			     _label,
			     _palette,
			     _highlightPalette,
			     _alternatePalette);
    if (_speed)
	track->setSpeed(_speed);
    if (_height)
	track->setHeight(_height);
    return track;
}

// --------------------------------------------------------------------------
IlvGraphic*
Track::read(IlvInputFile&,
	    IlvPalette*)
{
    // No IO required
    return 0;
}

// --------------------------------------------------------------------------
void
Track::write(IlvOutputFile&) const
{
    // No IO required
}

IlvRegisterClass(Track, IlvSimpleGraphic);
