// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/projimg/src/pcenter.cpp
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
// Implementation of center interactor
// --------------------------------------------------------------------------
#include <pcenter.h>

// --------------------------------------------------------------------------
// Static and callback functions
// --------------------------------------------------------------------------
static IlDouble
dist(IlvTransformer* tr,IlvPoint& p1,IlvPoint& p2)
{
    IlDouble x1;
    IlDouble y1;
    IlDouble dx;
    IlDouble dy;

    if (tr) {
	IlvFloatPoint fp1((IlFloat)p1.x(), (IlFloat)p1.y());
	IlvFloatPoint fp2((IlFloat)p2.x(), (IlFloat)p2.y());
	tr->inverse(fp1);
	tr->inverse(fp2);
	x1 = fp1.x();
	y1 = fp1.y();
	dx = x1 - fp2.x();
	dy = y1 - fp2.y();
    }
    else {
	x1 = p1.x();
	y1 = p1.y();
	dx = x1 - p2.x();
	dy = y1 - p2.y();
    }
    return sqrt((IlDouble)(dx * dx) + (IlDouble)(dy * dy));
}

// --------------------------------------------------------------------------
// PointVector
// --------------------------------------------------------------------------
PointVector::PointVector(IlUInt np)
    : _numPoints(np)
{
    if (np) {
	_valid = new IlBoolean[np];
	memset(_valid, IlFalse, np * sizeof(IlBoolean));
	_points = new IlvPoint[np];
	memset(_points, 0, np * sizeof(IlvPoint));
    }
    else {
	_valid = 0;
	_points = 0;
    }
}

// --------------------------------------------------------------------------
PointVector::~PointVector()
{
    if (_valid) {
	delete [] _valid;
    }
    if (_points) {
	delete [] _points;
    }
}


// --------------------------------------------------------------------------
// ProjCenterInteractor
// --------------------------------------------------------------------------
ProjCenterInteractor::ProjCenterInteractor(ImageProjector* ip)
    : CenterInteractor(ip->getManager(), ip->getView()),
      _imageProjector(ip),
      _palette(0),
      _started(IlFalse)
{
    _lat = new PointVector(NUM_LAT);
    _long = new PointVector(NUM_LONG);
}

// --------------------------------------------------------------------------
ProjCenterInteractor::~ProjCenterInteractor()
{
    if (_lat) {
	delete _lat;
	_lat = 0;
    }
    if (_long) {
	delete _long;
	_long = 0;
    }
    if (_palette) {
	_palette->unLock();
	_palette = 0;
    }
}

// --------------------------------------------------------------------------
void
ProjCenterInteractor::stop()
{
    if (_started) {
	drawLines();
    }
    _started = IlFalse;
}

// --------------------------------------------------------------------------
void
ProjCenterInteractor::abort()
{
    CenterInteractor::abort();
    stop();
}

// --------------------------------------------------------------------------
void
ProjCenterInteractor::drawLines()
{
    IlvView* view = getView();
    IlvDisplay* display = getDisplay();

    if (!_palette) {
	IlvColor* bg = view->getBackground();
	IlvColor* fg = display->getColor("red");

	_palette = display->getPalette(bg, fg);
	_palette->setMode(IlvModeXor);
	_palette->lock();
    }

    IlUInt i;
    IlUInt n = _lat->getCount();
    for (i = 0 ; i < n - 1; i++) {
	if (_lat->isValid(i) && _lat->isValid(i + 1)) {
	    if (inRange(_lat->getPoint(i))
		|| inRange(_lat->getPoint(i + 1))) {
		view->drawLine(_palette,
			       _lat->getPoint(i),
			       _lat->getPoint(i + 1));
	    }
	}
    }

    n = _long->getCount();
    for (i = 0 ; i < n - 1; i++) {
	if (_long->isValid(i) && _long->isValid(i + 1)) {
	    if (inRange(_long->getPoint(i))
		|| inRange(_long->getPoint(i + 1))) {
		view->drawLine(_palette,
			       _long->getPoint(i),
			       _long->getPoint(i + 1));
	    }
	}
    }
}

// --------------------------------------------------------------------------
IlBoolean
ProjCenterInteractor::canCenter(IlvEvent& event)
{
    IlvCoordinate ll;
    IlvMapInfo* mapInfo = _imageProjector->getMapInfo();

    if (mapInfo) {
	if (mapInfo->inverse(event, getView(), ll) == IlvMaps::NoError()) {
	    return IlTrue;
	}
    }
    return IlFalse;
}

// --------------------------------------------------------------------------
void
ProjCenterInteractor::doIt(IlvEvent& event)
{
    if (canCenter(event)) {
	_imageProjector->centerProjection(getView(), event);
    }
}

// --------------------------------------------------------------------------
void
ProjCenterInteractor::mouseMoved(IlvEvent& event)
{
    IlvMapInfo* mapInfo = _imageProjector->getMapInfo();
    const IlvProjection* proj = mapInfo->getProjection();
    const IlvMapAdapter* adapter = mapInfo->getAdapter();
    IlvManager* manager = _imageProjector->getManager();
    IlvView* view = getView();

    if (!mapInfo) {
	return;
    }

    if (!canCenter(event)) {
	stop();
	return;
    }

    IlvCoordinate ll;
    if (mapInfo->inverse(event, getView(), ll) != IlvMaps::NoError()) {
	return;
    }

    if (_started) {
	drawLines();
    }
    else {
	_started = IlTrue;
    }

    IlDouble lon;
    IlDouble lat;
    IlDouble distance;
    IlvCoordinate c;
    IlvTransformer* tr = manager->getTransformer(view);
    IlInt l;
    IlUInt k;
    double a = proj->getEllipsoid()->getA();

    lat = ll.y();
    k = 0;
    for (l = -180 ; l <= 180; l += LAT_DIV) {
	lon = IlvMaps::DegreeToRadian(l);
	c.move(lon, lat);
	if (proj->forward(c, c) == IlvMaps::NoError()) {
	    _lat->setValid(k, IlTrue);
	    adapter->toViews(c, _lat->getPoint(k));
	    if (tr) {
		tr->apply(_lat->getPoint(k));
	    }
	    if (k > 0) {
		distance = dist(tr,
				_lat->getPoint(k - 1),
				_lat->getPoint(k));
		if (distance < 3) {
		    _lat->setValid(k, IlFalse);
		}
		else {
		    distance = adapter->fromViews(distance);
		    distance = proj->getUnitConverter()->toMeters(distance);
		    if (distance > a) {
			_lat->setValid(k, IlFalse);
		    }
		}
	    }
	}
	else {
	    _lat->setValid(k, IlFalse);
	}
	k++;
    }

    lon = ll.x();
    k = 0;
    for (l = -90 ; l <= 90; l += LONG_DIV) {
	lat = IlvMaps::DegreeToRadian(l);
	c.move(lon, lat);
	if (proj->forward(c, c) == IlvMaps::NoError()) {
	    _long->setValid(k, IlTrue);
	    adapter->toViews(c, _long->getPoint(k));
	    if (tr) {
		tr->apply(_long->getPoint(k));
	    }
	    if (k > 0) {
		distance = dist(tr,
				_long->getPoint(k - 1),
				_long->getPoint(k));
		if (distance < 3) {
		    _long->setValid(k, IlFalse);
		}
		else {
		    distance = adapter->fromViews(distance);
		    distance = proj->getUnitConverter()->toMeters(distance);
		    if (distance > a) {
			_long->setValid(k, IlFalse);
		    }
		}
	    }
	}
	else {
	    _long->setValid(k, IlFalse);
	}
	k++;
    }
    drawLines();
}
