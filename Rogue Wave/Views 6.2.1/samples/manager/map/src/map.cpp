// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/manager/map/src/map.cpp
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
// Was formerly a benchmark for animation in managers.
// --------------------------------------------------------------------------

#include <ilviews/manager/manager.h>
#include <ilviews/manager/layer.h>
#include <ilviews/manager/paninter.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/graphics/line.h>
#include <ilviews/graphics/spline.h>
#include <ilviews/graphics/set.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/base/timer.h>
#include "track.h"
#include "hook.h"

#if defined(IL_STD)
IL_STDUSE
#include <cstdlib>
#include <cstdio>
#include <cmath>
#else
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#endif

#define MAXTRACKS 50
#if defined(ILVFATFILENAMES)
#define FILENAME "europe.ilv"
#else  /* !ILVFATFILENAMES */
#define FILENAME "europe.ilv"
#endif /* !ILVFATFILENAMES */

// --------------------------------------------------------------------------
static int		_TrackLayer     = 0;
static double		_Delta          = 0;
static IlBoolean	_ShowMap        = IlTrue;
static IlBoolean	_DrawRoutes     = IlTrue;
static int		_TimerSec       = 0;
static int		_TimerMilliSec  = 100;
static IlSymbol*	_TrackTag       = 0;
static IlvRect		_MapBox;
static const int        _NbCompanies    = 13;
static const char*	_Companies[]    = {
   "AF", "AL", "AN", "BA", "FI", "IT", "KL", "LU", "PA", "SA", "TW", "UN", "US"
};

// --------------------------------------------------------------------------
// Accelerator to toggle double buffering
// --------------------------------------------------------------------------
static void
SetDBL(IlvManager* manager, IlvView* view, IlvEvent&, IlAny)
{
    if (manager->isDoubleBuffering(view)) {
	manager->setDoubleBuffering(view, IlFalse);
    }
    else {
	manager->setDoubleBuffering(view, IlTrue);
	manager->draw(view, IlTrue);
    }
}

// --------------------------------------------------------------------------
// Accelerator to hide/show the map
// --------------------------------------------------------------------------
static void
ShowMap(IlvManager* manager, IlvView*, IlvEvent&, IlAny arg)
{
    IlvMapHook* hook = (IlvMapHook*)arg;
    _ShowMap = !_ShowMap;
    if (_ShowMap) {
	hook->adjust();
	manager->installViewHook(hook);
	manager->draw(hook->getView(), IlTrue);
    }
    else {
	manager->removeViewHook(hook);
	manager->draw(hook->getView(), IlTrue);
    }
}

// --------------------------------------------------------------------------
// Accelerator to hide/show routes (a route is represented by a line
// between a moving object and its destination)
// --------------------------------------------------------------------------
static void
DrawRoute(IlvGraphic* obj, IlAny arg)
{
    Track* track = IL_CAST(Track*, obj);
    track->showRoute(arg ? IlTrue : IlFalse);
}

// --------------------------------------------------------------------------
//
static void
ToggleDrawRoutes(IlvManager* manager, IlvView*, IlvEvent&, IlAny arg)
{
    _DrawRoutes = !_DrawRoutes;
    manager->applyToTaggedObjects(_TrackTag, DrawRoute, (IlAny)_DrawRoutes);
    IlvTimer* timer = IL_CAST(IlvTimer*, arg);
    if (!timer->isRunning()) {
	manager->reDraw();
    }
}
    
// --------------------------------------------------------------------------
// Accelerator to stop/restart the animation
// --------------------------------------------------------------------------
static void
ToggleAnimation(IlvManager*, IlvView*, IlvEvent&, IlAny arg)
{
    IlvTimer* timer = IL_CAST(IlvTimer*, arg);
    if (timer->isRunning()) {
	timer->suspend();
    }
    else {
        timer->run(_TimerSec, _TimerMilliSec);
    }
}

// --------------------------------------------------------------------------
// Accelerator to change the speed of the animation
// --------------------------------------------------------------------------
static void
ChangePeriod(IlvManager*, IlvView*, IlvEvent&, IlAny arg)
{
    if (arg) { // Faster
	if ((_TimerSec > 0) || ((_TimerSec == 0) && (_TimerMilliSec > 50))) {
	    if (_TimerMilliSec > 50) {
		_TimerMilliSec -= 50;
	    }
	    else {
		--_TimerSec;
		_TimerMilliSec = 950;
	    }
	}
    }
    else {   // Slower
	if (_TimerSec < 3) {
	    if (_TimerMilliSec >= 950) {
		++_TimerSec;
		_TimerMilliSec = 0;
	    }
	    else {
		_TimerMilliSec += 50;
	    }
	}
    }
}

// --------------------------------------------------------------------------
// Utility function. Returns a random point on the map.
// --------------------------------------------------------------------------
static IlvPoint
RandomPoint()
{
    IlvPoint randomPt(_MapBox.x() + (rand() % (_MapBox.w() / 3)) * 3,
		      _MapBox.y() + (rand() % (_MapBox.h() / 3)) * 3);
    // rand() % / 3 * 3 is to work around a bug in rand().
    return randomPt;
}

// --------------------------------------------------------------------------
// Timer callback for the animation. Moves the track objects and redraws.
// --------------------------------------------------------------------------
static void
UpdateTrack(IlvGraphic* g, IlAny)
{
    Track* track = (Track*)g;
    if (track->hasLanded()) {
	track->init(RandomPoint(), RandomPoint());
    }
    else {
	double delta = (_Delta * (double)track->getSpeed()) / (double)800;
	double X  = track->getDestination().x() - track->getPosition().x();
	double Y  = track->getDestination().y() - track->getPosition().y();
	double R2 = X * X + Y * Y;
	if (R2 <= delta * delta) {
	    track->land();
	}
	else {
	    double R = sqrt(R2);
	    double dx = (delta * X) / R;
	    double dy = (delta * Y) / R;
	    track->translatePosition(IlvPoint((IlvPos)dx, (IlvPos)dy));
	}
    }
}

// --------------------------------------------------------------------------
//
static void
UpdateTracks(IlvTimer* timer, IlAny arg)
{
    IlvManager* manager = (IlvManager*)arg;
    manager->applyToObjects(_TrackLayer,
			    UpdateTrack,
			    manager,
			    !_DrawRoutes);
    if (_DrawRoutes) {
	IlvView* view = manager->getFirstView();
	manager->initReDraws();
	manager->invalidateRegion(view, IlvRect(0,
						0,
						view->width(),
						view->height()));
	manager->reDrawViews();
    }
    timer->run(_TimerSec, _TimerMilliSec);
}

// --------------------------------------------------------------------------
// Returns a track object with some random characteristics.
// --------------------------------------------------------------------------
static Track*
NewRandomTrack(IlvDisplay* display,
	       IlvPalette* palette,
	       IlvPalette* hilit,
	       IlvPalette* alt)
{
    char buf[128];
    sprintf(buf, "%s 0%u",
	    _Companies[rand() % _NbCompanies], // Random company
	    100 + (rand() % 900));             // Random flight number
    Track* track = new Track(display,
			     RandomPoint(),
			     RandomPoint(),
			     buf,
			     palette,
			     hilit,
			     alt);
    // Random speed [250 - 1000] mph
    track->setSpeed(250 + (rand() % 750));
    // Random height [5000-55000] ft
    track->setHeight(100 * (50 + (rand() % 500)));
    track->setWarningDistance((IlvDim)(_Delta * 2));
    return track;
}

// --------------------------------------------------------------------------
// Destroy callback of the main view. Quit the application.
// --------------------------------------------------------------------------
static void
Quit(IlvView* top, IlAny arg)
{
    IlAny* args = (IlAny*)arg;
    delete (IlvTimer*)args[1];
    delete (IlvManager*)args[0];
    delete top->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Resize callback of the main view. Call fitTransformerToContents
// --------------------------------------------------------------------------
static void
Resize(IlvView* top, IlvRect& rect, IlAny arg)
{
    static IlvDim oldWidth, oldHeight;
    if (oldWidth != rect.w() || oldHeight != rect.h()) {
	IlvManager* manager = (IlvManager*)arg;
	manager->fitTransformerToContents(top, IlTrue, IlTrue);
    }
    oldWidth = rect.w();
    oldHeight = rect.h();
}

// --------------------------------------------------------------------------
// Utility function.
// Returns the resource value set in the user environment or the default
// value if there is none.
// --------------------------------------------------------------------------
static inline const char*
GetResourceOrDefault(IlvDisplay* display,
		     const char* resourceName,
		     const char* defaultValue)
{
    const char* resourceValue = display->getResource(resourceName);
    return resourceValue ? resourceValue : defaultValue;
}

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    int maxTracks = MAXTRACKS;
    if (argc > 1) {
        maxTracks = atoi(argv[1]);
    }
    if (maxTracks < 1) {
	maxTracks = 1;
    }
    if (maxTracks > 1000) {
	maxTracks = 1000;
    }

    // Connect with display system
    IlvDisplay* display = new IlvDisplay("MapSample", "", argc, argv);
    if (display->isBad()) {
	IlvFatalError("Cannot create display");
	delete display;
	return -1;
    }

    // Use the lazy redraw mode...
    IlvEventLoop::getEventLoop()->setLazyRedraw(3);

    // Create top view (work area)
    IlvRect viewRect(0, 0, 801, 401);
    IlvView* managerview = new IlvView(display,
				       "Map sample",
				       "Map sample",
				       viewRect,
				       IlFalse);

    // Create manager
    IlvManager* manager = new IlvManager(display);

    // Read Map
    manager->read(FILENAME);
    manager->computeBBox(_MapBox);
    _Delta = _MapBox.w() / 1000;

    // Set the background of the view to the background of the oceans...
    IlvManagerLayer* oceans = manager->getManagerLayer("Oceans");
    if (oceans && oceans->getCardinal()) {
	IlUInt count;
	IlvGraphic* const* objects = oceans->getObjects(count);
	if (objects[0]->isSubtypeOf(IlvSimpleGraphic::ClassInfo())) {
	    IlvSimpleGraphic* obj = (IlvSimpleGraphic*)objects[0];
	    managerview->setBackground(obj->getForeground());
	}
    }

    // Add a layer for the track
    IlvManagerLayer* layer = new IlvManagerLayer(30);
    // Do not use the quadtree because objects in this layer are
    // always moving.
    layer->allowSubdivision(IlFalse); 
    manager->addLayer(layer);
    _TrackLayer = manager->getLayerIndex(layer);

    // Set all layers invisible (this is needed for IlvMapHook)
    // And set antialiasing for all layers
    IlUInt i;
    for (i = 0; i < (IlUInt)_TrackLayer; i++) {
	IlvManagerLayer* layer = manager->getManagerLayer(i);
	layer->setVisible(IlFalse);
	layer->setAntialiasingMode(IlvUseAntialiasingMode);
    }
    
    // Initialize a symbol to tag the track objects
    _TrackTag = IlvGetSymbol("TrackSymbol", IlTrue);

    // Creates palettes for tracks
    const char* trackColor     = GetResourceOrDefault(display,
						      "trackColor",
						      "white");
    const char* highlightColor = GetResourceOrDefault(display,
						      "highlightColor",
						      "red");
    const char* alternateColor = GetResourceOrDefault(display,
						      "alternateColor",
						      "black");
    IlvPalette* palette = 
	display->getPalette(0, display->getColor(trackColor));
    IlvPalette* highlightPalette =
	display->getPalette(0,
			    display->getColor(highlightColor),
			    0,
			    0,
			    palette->getFont());
    IlvPalette* alternatePalette =
	display->getPalette(0,
			    display->getColor(alternateColor),
			    0,
			    0,
			    palette->getFont());
    palette->lock();
    highlightPalette->lock();
    alternatePalette->lock();

    // Creates tracks
    Track* track;
    for (i = 0; i < (IlUInt)maxTracks; i++) {
	track = NewRandomTrack(display,
			       palette,
			       highlightPalette,
			       alternatePalette);
	track->addTag(_TrackTag);
	manager->addObject(track, IlFalse, _TrackLayer);
    }
    palette->unLock();
    highlightPalette->unLock();
    alternatePalette->unLock();

    // Attach view to manager
    manager->addView(managerview);
    manager->setKeepingAspectRatio(managerview, IlTrue);

    // Create the hook
    IlvMapHook hook(manager, managerview, 0, (IlUShort)(_TrackLayer - 1));
    manager->installViewHook(&hook);

    // Set double buffering on
    manager->setDoubleBuffering(managerview, IlTrue);

    // Set a transformer to see most of the map
    IlFloat scale = (IlFloat)viewRect.w() / (IlFloat)_MapBox.w();
    IlvTransformer t(scale, 0, 0, scale,
		     -_MapBox.x() * scale, -_MapBox.y() * scale);
    manager->setTransformer(managerview, &t);

    manager->reDraw();

    // Create the timer
    IlvTimer* timer = new IlvTimer(display,
				   _TimerSec,
				   _TimerMilliSec,
				   UpdateTracks,
				   manager);
    timer->runOnce(IlTrue);

    // Add accelerators
    manager->addAccelerator(SetDBL,           IlvKeyUp,   'b');
    manager->addAccelerator(ShowMap,          IlvKeyUp,   'm', 0, &hook);
    manager->addAccelerator(ToggleAnimation,  IlvKeyUp,   's', 0, timer);
    manager->addAccelerator(ToggleDrawRoutes, IlvKeyUp,   't', 0, timer);
    manager->addAccelerator(ChangePeriod,     IlvKeyDown, '+', 0, (IlAny)1);
    manager->addAccelerator(ChangePeriod,     IlvKeyDown, '-', 0, (IlAny)0);

    // Set a destroy callback
    IlAny args[2];
    args[0] = (IlAny)manager;
    args[1] = (IlAny)timer;
    managerview->setDestroyCallback(Quit, (IlAny*)args);

    // Set a resize callback
    managerview->setResizeCallback(Resize, (IlAny)manager);

    // Install a pan/zoom interactor
    IlvPanZoomInteractor* paninter =
	new IlvPanZoomInteractor(manager, managerview);
    manager->setInteractor(paninter, managerview);
    
    // Show the view, run the timer and wait for events.
    managerview->show();
    timer->run();
    IlvMainLoop();
    return 0;
}
