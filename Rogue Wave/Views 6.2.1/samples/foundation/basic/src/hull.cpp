// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/basic/src/hull.cpp
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
// Compute the convex hull of a set of points, using a recursive algorithm
// known as 'Quick Hull'.
// --------------------------------------------------------------------------

#include <ilviews/base/view.h>
#include <ilviews/util/pool.h>
#include <math.h>

static const char* title = "Rogue Wave Views sample: hull";

#define ADD(b, c, p) b = IlPoolOf(IlvPoint)::ReAlloc(b, c + 1); b[c++] = p

// --------------------------------------------------------------------------
class Segment
{
public:
    Segment(const IlvPoint& p1,
	    const IlvPoint& p2)
    : _p1(p1),
      _p2(p2),
      _slope(0.),
      _isVertical(IlTrue)
    {
	if (p1.x() == p2.x())
	    return;
	_isVertical = IlFalse;
	if (p1.y() == p2.y())
	    return;
	_slope = (p2.y() - p1.y()) / (IlDouble)(p2.x() - p1.x());
    }

    IlBoolean isOnLeft(const IlvPoint p)
    {
	if (_isVertical) {
	    if (p.x() < _p1.x())
		return IlTrue;
	    else {
		if (p.x() == _p1.x()) {
		    if (((p.y() > _p1.y()) &&
			 (p.y() < _p2.y())) ||
			((p.y() > _p2.y()) &&
			 (p.y() < _p1.y())))
			return IlTrue;
		    else
			return IlFalse;
		} else
		    return IlFalse;
	    }
	} else {            
	    IlvPos x3 = (IlvPos)
		(((p.x() + _slope * (_slope * _p1.x() - _p1.y() + p.y())) /
		  (1 + _slope * _slope)) * 1000);
	    IlvPos y3 = (IlvPos)
		((_slope * (x3 / 1000 - _p1.x()) + _p1.y()) * 1000);
	    
	    if (_slope == 0.) {
		return ((p.y() * 1000) > y3)
		    ? IlTrue
		    : IlFalse;
	    } else {
		if (_slope > 0.) {
		    return (x3 > (p.x() * 1000))
			? IlTrue
			: IlFalse;
		} else {
		    return ((p.x() * 1000) > x3)
			? IlTrue
			: IlFalse;
		}
	    }
	}
    }

    const IlvPoint&	getP1()            const { return _p1; }
    const IlvPoint&	getP2()            const { return _p2; }
    IlDouble		getSlope()         const { return _slope; }
    IlBoolean		isSlopeUndefined() const { return _isVertical; }

private:
    IlvPoint		_p1;
    IlvPoint		_p2;
    IlDouble		_slope;
    IlBoolean		_isVertical;
};

// --------------------------------------------------------------------------
IlDeclarePoolOf(Segment, Segment);
IlDefinePoolOf(Segment);

static IlUInt    nDots;
static IlvPoint* dots;
static IlUInt    hullCount;
static Segment*  hull;

// --------------------------------------------------------------------------
static IlUInt
FindFurthest(IlUInt count,
	     IlvPoint* P,
	     const IlvPoint& l,
	     const IlvPoint& r)
{
    Segment newLn(l, r);
    IlvPos x, y;
    IlUInt furthest = 0;
    double maxDist = 0;
    for (IlUInt loop = 0; loop < (count - 2); loop++) {
	if (newLn.isSlopeUndefined()) {
            x = l.x();
            y = P[loop].y();
	} else if (r.y() == l.y()) {
	    x = P[loop].x();
	    y = l.y();
	} else {
	    x = (IlvPos)(((P[loop].x() + newLn.getSlope() *
			   (newLn.getSlope() * l.x() - l.y() + P[loop].y()))
			  / (1 + newLn.getSlope() * newLn.getSlope())));
	    y = (int) ((newLn.getSlope() * (x - l.x()) + l.y()));
	}
	IlvPos dx = P[loop].x() - x;
	IlvPos dy = P[loop].y() - y;
	double distance = sqrt((double)(dx * dx + dy * dy));
	if (distance > maxDist) {
            maxDist = distance;
            furthest = loop;
	}
    }
    return furthest;
}

// --------------------------------------------------------------------------
static void
RecurseHull(IlUInt&         hullCount,
	    Segment*&       hull,
	    IlUInt&         count,
	    IlvPoint*       part,
	    const IlvPoint& l,
	    const IlvPoint& r,
	    int             lower)
{
    if (count == 2) {
	hull = IlPoolOf(Segment)::ReAlloc(hull, hullCount + 1);
	hull[hullCount++] = Segment(part[0], part[1]);
	return;
    }
    IlUInt hAt = FindFurthest(count, part, l, r);
    Segment lh(l, part[hAt]);
    Segment hr(part[hAt], r);
    IlUInt count1 = 0;
    IlvPoint* P1 = IlPoolOf(IlvPoint)::Alloc(16, IlTrue);
    IlUInt count2 = 0;
    IlvPoint* P2 = IlPoolOf(IlvPoint)::Alloc(16, IlTrue);
	
    for (IlUInt i = 0; i < (count - 2); i++) {
	if (i != hAt) {
	    if (!lower) {
		if (lh.isOnLeft(part[i])) {
		    ADD(P1, count1, part[i]);
		}
		if (hr.isOnLeft(part[i])) {
		    ADD(P2, count2, part[i]);
		}
	    } else {
		if (!lh.isOnLeft(part[i])) {
		    ADD(P1, count1, part[i]);
		}
		if (!hr.isOnLeft(part[i])) {
		    ADD(P2, count2, part[i]);
		}
	    }
	}
    }
    IlvPoint& h = part[hAt];
    ADD(P1, count1, l);
    ADD(P1, count1, h);
    ADD(P2, count2, h);
    ADD(P2, count2, r);
    if (!lower) {
	RecurseHull(hullCount, hull, count1, P1, l, h, 0);
	RecurseHull(hullCount, hull, count2, P2, h, r, 0);
    } else {
	RecurseHull(hullCount, hull, count1, P1, l, h, 1);
	RecurseHull(hullCount, hull, count2, P2, h, r, 1);
    }
    IlPoolOf(IlvPoint)::UnLock(P1);
    IlPoolOf(IlvPoint)::UnLock(P2);
}

// --------------------------------------------------------------------------
static void
ComputeHull()
{
    // Find the left and right extrema points, that define the initial
    // segment that splits the point set into the 'upper' and 'lower'
    // sets.
    IlvPos minX = dots[0].x();
    IlvPos maxX = dots[0].x();
    IlUInt iLeft = 0;
    IlUInt iRight = 0;
    IlUInt loop;
    for (loop = 1; loop < nDots; loop++) {
	IlvPos x = dots[loop].x();
	if (x < minX) {
	    minX = x;
	    iLeft = loop;
	}
	if (x > maxX) {
	    maxX = x;
	    iRight = loop;
	}
    }
    IlvPoint& left  = dots[iLeft];
    IlvPoint& right = dots[iRight];
    // Store all points in the defined sets.
    IlvPoint* lower = IlPoolOf(IlvPoint)::Alloc(64, IlTrue);
    IlUInt lowerCount = 0;
    IlvPoint* upper = IlPoolOf(IlvPoint)::Alloc(64, IlTrue);
    IlUInt upperCount = 0;
    Segment lr(left, right);
    for (loop = 0; loop < nDots; loop++) {
	if ((loop != iLeft) && (loop != iRight)) {
            IlvPoint& p = dots[loop];
            if (lr.isOnLeft(p)) {
		ADD(upper, upperCount, p);
	    } else {
		ADD(lower, lowerCount, p);
	    }
	}
    }
    ADD(upper, upperCount, left);
    ADD(upper, upperCount, right);
    ADD(lower, lowerCount, left);
    ADD(lower, lowerCount, right);

    // Run the actual recursive algorithm on each sets.
    hull = IlPoolOf(Segment)::Alloc(32, IlTrue);
    hullCount = 0;
    RecurseHull(hullCount, hull, upperCount, upper, left, right, 0);
    RecurseHull(hullCount, hull, lowerCount, lower, left, right, 1);
    IlPoolOf(Segment)::UnLock(hull);
}

// --------------------------------------------------------------------------
static void
Destroy(IlvView* view,
	IlAny)
{
    IlPoolOf(IlvPoint)::UnLock(dots);
    delete view->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
Expose(IlvView* view,
       IlvEvent&,
       IlAny palette)
{
    view->erase(IlFalse);
    if (!nDots)
	view->drawString(view->getDisplay()->defaultPalette(),
			 IlvPoint(10, 20),
			 "Please click here to add points", -1);
    IlUInt loop;
    for (loop = 0; loop < nDots; loop++)
	view->drawMarker(view->getDisplay()->defaultPalette(), dots[loop]);
    for (loop = 0; loop < hullCount; loop++)
	view->drawLine((IlvPalette*)palette,
		       hull[loop].getP1(),
		       hull[loop].getP2());
}

// --------------------------------------------------------------------------
static void
Input(IlvView* view,
      IlvEvent& event,
      IlAny)
{
    if ((event.getType() == IlvButtonUp) &&
	(event.getButton() == IlvLeftButton)) {
	dots = IlPoolOf(IlvPoint)::ReAlloc(dots, nDots + 1);
	dots[nDots++].move(event.x(), event.y());
	if (nDots >= 3)
	    ComputeHull();
	view->erase(IlTrue);
    }
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay("Hull", "", argc, argv);
    if (!display || display->isBad()) {
	delete display;
	IlvFatalError("Couldn't open display");
	IlvExit(-1);
    }
    IlvView* view = new IlvView(display,
				title,
				title,
				IlvRect(0, 0, 500, 500),
				IlFalse);
    view->setInputCallback(Input);
    view->setExposeCallback(Expose,
			    display->getPalette(0, display->getColor("red")));
    view->setDestroyCallback(Destroy);
			    
    nDots = 0;
    IlPoolOf(IlvPoint)::Lock(dots = IlPoolOf(IlvPoint)::Alloc(64));
    view->show();
    IlvMainLoop();
    return 0;
}

