// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/multitouch/src/multitouch.cpp
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
// Demonstrates the Multi-touch feature in Rogue Wave Views
// --------------------------------------------------------------------------

#include <ilviews/manager/manager.h>
#include <ilviews/graphics/all.h>

#if defined(ILVSTD)
#  include <cstdio>
#  include <climits>
#else  /* !ILVSTD */
#  include <stdio.h>
#  include <limits.h>
#endif /* ILVSTD */

// --------------------------------------------------------------------------
// Quit callback
// --------------------------------------------------------------------------
static void
Quit(IlvView* top, IlvAny)
{
    delete top->getDisplay();;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Utility function.
// Compute the distance between two points.
// --------------------------------------------------------------------------
static IlvTransfoParam
ComputeDistance(const IlvPoint& p1, const IlvPoint& p2)
{
    IlvPos dx = p2._x - p1._x;
    IlvPos dy = p2._y - p1._y;
    return sqrt(IlDouble(dx*dx + dy*dy));
}

// --------------------------------------------------------------------------
// Utility function.
// Compute the center between two points.
// --------------------------------------------------------------------------
static IlvPoint
CenterPoint(IlvPoint const& p1, IlvPoint const& p2)
{
    return IlvPoint((p1._x + p2._x) / 2, (p1._y + p2._y) / 2);
}

// --------------------------------------------------------------------------
// TouchZoomInteractor class
//
// This interactor handles multitouch events
// It allows zoom with two fingers and pan with one finger.
// --------------------------------------------------------------------------
class TouchZoomInteractor
    : public IlvManagerViewInteractor
{
public:
    TouchZoomInteractor(IlvManager* mgr, IlvView* v);
    virtual ~TouchZoomInteractor();

    IlBoolean		handleEvent(IlvEvent& event);
    void		addTransformer(IlvTransformer& t);

    inline void		registerFirstPoint(IlUShort id, IlvPoint p)
	{
	    firstID = id;
	    setOrgFirst(p);
	    first = p;
	}
    inline void		registerSecondPoint(IlUShort id, IlvPoint p)
	{
	    secondID = id;
	    setOrgSecond(p);
	    second = p;
	}
    inline void		storeTransformer()
	{
	    IlvTransformer* t =
	    getManager()->getTransformer(getView());
	    startTransform = t ? *t : IlvTransformer();
	}
    void		inertiaTranslate();
    inline IlvPoint	getOrgCenterPoint() const
	{
	    if (orgModified) {
		orgCenter = CenterPoint(orgFirst, orgSecond);
		orgModified = IlFalse;
	    }
	    return orgCenter;
	}
    inline void		setOrgFirst(IlvPoint& p)
	{
	    orgFirst = p;
	    orgModified = true;
	}
    inline void		setOrgSecond(IlvPoint& p)
	{
	    orgSecond = p;
	    orgModified = true;
	}
    inline void		setInertiaRatio(IlFloat ratio)
	{
	    if (ratio < 0.0) {
		ratio = -ratio;
	    }
	    if (ratio < 0.001) {
		ratio = IlFloat(0.001);
	    }
	    inertiaRatio = IlFloat(1.0) + ratio;
	}

private:
    IlvPoint		first;
    IlvPoint		second;
    IlvPoint		orgFirst;
    IlvPoint		orgSecond;
    IlUShort		firstID;
    IlUShort		secondID;
    IlvTransformer	startTransform;
    IlvTimer*		inertiaTimer;
    IlvTransfoParam	inertiadx;
    IlvTransfoParam	inertiady;
    IlUInt		inertiaTime;
    IlFloat		inertiaRatio;

    // Caching variables
    mutable IlvPoint	orgCenter;
    mutable IlBoolean	orgModified;
};

// --------------------------------------------------------------------------
// 30ms between inertia animations
static const int InertiaTimerInterval = 30;
// Considered as invalid touch point
static const IlUShort NullTouchPoint = USHRT_MAX;

// --------------------------------------------------------------------------
static void
InertiaTimerProc(IlvTimer* timer, IlAny arg)
{
    TouchZoomInteractor* inter = static_cast<TouchZoomInteractor*>(arg);
    inter->inertiaTranslate();
}

// --------------------------------------------------------------------------
TouchZoomInteractor::TouchZoomInteractor(IlvManager* mgr, IlvView* v)
    : IlvManagerViewInteractor(mgr, v),
      firstID(NullTouchPoint),
      secondID(NullTouchPoint),
      inertiaTimer(0),
      inertiaRatio(IlFloat(1.1))
{
    // Timer to handle inertia when removing the finger after pan
    inertiaTimer = new IlvTimer(getDisplay(),
				0,
				InertiaTimerInterval,
				&InertiaTimerProc,
				this);
    inertiaTimer->runOnce(true);
}

// --------------------------------------------------------------------------
TouchZoomInteractor::~TouchZoomInteractor()
{
    // Stop the timer if the interactor no longer exists
    inertiaTimer->suspend();
    delete inertiaTimer;
}

// --------------------------------------------------------------------------
IlBoolean
TouchZoomInteractor::handleEvent(IlvEvent& event)
{
    switch(event.type()) {
    case IlvTouchDown:
	if (firstID == NullTouchPoint) {
	    // There is no first touch point.
	    // Suspend and reset inertia
	    inertiaTimer->suspend();
	    inertiadx = inertiady = 0;
	    // First touch point =>
	    //   - initiate a translation motion
	    //   - store the initial position
	    registerFirstPoint(event.getTouchPoint(), event.getLocation());
	    //   - store the view transformer.
	    storeTransformer();

	    // All future motions will have this position and transformer
	    // as base state of the view.
	    return IlTrue;
	}
	else if (secondID == NullTouchPoint) {
	    // Second touch point =>
	    //   - initiate a zooming motion
	    //   - store the initial position
	    registerSecondPoint(event.getTouchPoint(),
				event.getLocation());
	    //   - store the new position of the first point as initial
	    //     position for zooming motion
	    //setOrgFirst(getPointLocation(firstID));
	    setOrgFirst(first);
	    //   - store the view transformer as initial transformer.
	    storeTransformer();

	    return IlTrue;
	}
	break;

    case IlvTouchUp:
	if (event.getTouchPoint() == firstID) {
	    if (secondID == NullTouchPoint) {
		// Inertia
		IlvPoint lastLocation = event.getLocation();
		inertiaTimer->run();
	    }
	    else {
		inertiadx = inertiady = 0;
	    }
	    // The first touch point disappears =>
	    //   - close the zooming motion
	    //   - open a translation motion
	    //   - the 2nd touch point becomes the 1st touch point...
	    firstID = secondID;
	    //   - reset the 2nd touch point ID
	    secondID = NullTouchPoint;
	    //   - store the initial position of the (new) 1st touch point
	    //setOrgFirst(getPointLocation(secondID));
	    setOrgFirst(second);
	    //   - store the new initial transformer.
	    storeTransformer();

	    return IlTrue;
	}
	else if (event.getTouchPoint() == secondID) {
	    // The second touch point disappears =>
	    //   - close the zooming motion
	    //   - open a translation motion.
	    //   - reset the 2nd touch point ID
	    secondID = NullTouchPoint;
	    //   - store the new initial position for the 1st touch point
	    //setOrgFirst(getPointLocation(firstID));
	    setOrgFirst(first);
	    //   - store the new initial transformer.
	    storeTransformer();

	    return IlTrue;
	}
	break;

    case IlvTouchMoved:
	if ((firstID != NullTouchPoint) && (secondID != NullTouchPoint)) {
	    // Zoom
	    bool modified = false;
	    IlvRect newRect;
	    if (event.getTouchPoint() == firstID) {
		first = event.getLocation();
		modified = true;
	    }
	    else if (event.getTouchPoint() == secondID) {
		second = event.getLocation();
		modified = true;
	    }
	    if (modified) {
		// Zooming policy:
		// 1- the center of the original two first touch points
		//    must remain the center of the current two touch points.
		// 2- the zoom factor is the ratio between the distance of
		//    the new touch points positions and the distance of the
		//    original touch points positions.
		IlvTransformer t;
		IlvPoint center = getOrgCenterPoint();
		IlvPoint newCenter = CenterPoint(first,second);
		IlvTransfoParam dist = ComputeDistance(orgFirst, orgSecond);
		IlvTransfoParam newDist = ComputeDistance(first, second);
		IlvTransfoParam mag = newDist/dist;
		t.scale(center._x, center._y, mag, mag);
		t.translate(newCenter._x - center._x,
			    newCenter._y - center._y);
		IlvTransformer newT = startTransform;
		newT.compose(t);
		addTransformer(t);

		return IlTrue;
	    }
	}
	else if (firstID != NullTouchPoint) {
	    // Move
	    if (event.getTouchPoint() == firstID) {
		// Just follow the finger.
		IlvPoint newLocation = event.getLocation();
		inertiadx = newLocation._x - first._x;
		inertiady = newLocation._y - first._y;

		first = newLocation;
		IlvTransformer t;
		t.translate(first._x - orgFirst._x, first._y - orgFirst._y);
		addTransformer(t);

		return IlTrue;
	    }
	}
    }
    return manager()->shortCut(event, view());
}

// ------------------------------------------------------------------------
void
TouchZoomInteractor::addTransformer(IlvTransformer& t)
{
    // Compose the transformation due to gestures with
    // the initial transformer and redraw the view
    IlvManager* manager = getManager();
    IlvView* view = getView();
    IlvTransformer newT = startTransform;
    newT.compose(t);
    manager->initReDraws();
    IlvRect bbox;
    manager->setTransformer(view, &newT);
    getView()->sizeVisible(bbox);
    manager->invalidateRegion(view, bbox);
    manager->reDrawViews();
}

// ------------------------------------------------------------------------
void
TouchZoomInteractor::inertiaTranslate()
{
    IlvTransformer t;
    t.translate(inertiadx, inertiady);
    addTransformer(t);
    storeTransformer();
    inertiadx /= inertiaRatio;
    inertiady /= inertiaRatio;
    if ((std::abs(inertiadx) > 1.0) || (std::abs(inertiady) > 1.0)) {
	inertiaTimer->run();
    }
}

// ------------------------------------------------------------------------
// TouchPointsViewHook class
// ------------------------------------------------------------------------
class TouchPointsViewHook
    : public IlvManagerViewHook
{
public:
    TouchPointsViewHook(IlvManager* mgr, IlvView* view)
        : IlvManagerViewHook(mgr, view) {}

    virtual void afterDraw(IlvPort* dst,
			   const IlvTransformer* t = 0,
			   const IlvRegion* region = 0,
			   const IlvRegion* clip = 0);
};

// ------------------------------------------------------------------------
void
TouchPointsViewHook::afterDraw(IlvPort* dst,
			       const IlvTransformer* t,
			       const IlvRegion* region,
			       const IlvRegion* clip)
{
    IlvDisplay* display = getView()->getDisplay();

    IlUShort count = display->getTouchPointCount();
    const IlvPoint** relative = new const IlvPoint*[count];
    IlUShort validNb = display->getTouchPoints(relative);
    for (IlUShort i = 0, valid = 0; (i < count) && (valid < validNb); ++i) {
	if (relative[i]) {
	    IlvRect rect(relative[i]->getX() - 25,
			 relative[i]->getY() - 25,
			 50,
			 50);
	    dst->drawArc(display->defaultPalette(), rect, 0, 360);
	    char s[3];
	    sprintf(s, "%d", i);
	    dst->drawString(display->defaultPalette(),
			    *(relative[i]),
			    s,
			    (int)strlen(s));
	    valid++;
	}
    }
    delete [] relative;
}

// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    const char title[] = "Multitouch";

    IlvSetLocale();
    IlvDisplay* display = new IlvDisplay(title, "", argc, argv);
    if (!display || display->isBad()) {
	if (display) {
	    delete display;
	}
	IlvFatalError("Could not create display");
	return 1;
    }

    IlvView* view = new IlvView(display,
				title,
				title,
				IlvRect(120, 0, 800, 600),
				IlvNoTouchScreenNavigation,
				IlvFalse, IlvFalse);
    view->setDestroyCallback(Quit);
    IlvManager* manager = new IlvManager(display);
    manager->addView(view);
    manager->setInteractor(new TouchZoomInteractor(manager, view), view);
    if (view->enableMultitouch(IlTrue)) {
	view->setTitle("Multitouch sample - multitouch enabled");
    }
    else {
	view->setTitle("Multitouch sample - cannot enable multitouch");
    }
    manager->installViewHook(new TouchPointsViewHook(manager, view));
    manager->read("DCW/world.ilv");
    manager->fitTransformerToContents(view, IlTrue, IlTrue);
    manager->setDoubleBuffering(view, IlTrue);

    view->show();

    IlvMainLoop();
    return 0;
}
