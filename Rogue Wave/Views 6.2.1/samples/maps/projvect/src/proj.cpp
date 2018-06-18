// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/projvect/src/proj.cpp
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
// Implementation of vector projector.
// --------------------------------------------------------------------------
#include <proj.h>
#include <pcenter.h>

#include <stdio.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/graphics/set.h>
#include <ilog/pathname.h>

#if defined(IL_STD)
#  include <iostream>
#  include <fstream>
using namespace std;
#else
#  include <iostream.h>
#  include <fstream.h>
#  include <stdlib.h>
#endif

// --------------------------------------------------------------------------
// Defines
// --------------------------------------------------------------------------
#define LAT_DIV_GRID 3
#define LONG_DIV_GRID 6

#define LARGE

#ifdef LARGE
#define LAT_DIV_GRID_SUP 33
#define LONG_DIV_GRID_SUP 30
#else
#define LAT_DIV_GRID_SUP 0
#define LONG_DIV_GRID_SUP 0
#endif

// --------------------------------------------------------------------------
// Static and callback functions
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Distance between two IlvCoordinate.
// Used to eliminate grid points that are too far.
// --------------------------------------------------------------------------
static IlDouble
dist(IlvCoordinate& p1, IlvCoordinate& p2)
{
    IlDouble x1;
    IlDouble y1;
    IlDouble dx;
    IlDouble dy;

    x1 = p1.x();
    y1 = p1.y();
    dx = x1 - p2.x();
    dy = y1 - p2.y();

    return sqrt((IlDouble)(dx * dx) + (IlDouble)(dy * dy));
}

// --------------------------------------------------------------------------
// Creates a grid of constant lat and constant long
// --------------------------------------------------------------------------
static void
MakeGrid(IlvManager* manager,IlvView* view,
	 IlvMapInfo* mapInfo,IlBoolean redraw)
{
    IlDouble lat;
    IlDouble lon;
    IlvCoordinate c;
    IlvCoordinate last;
    IlvPoint x[360/LAT_DIV_GRID + 1];
    IlvPoint y[180/LONG_DIV_GRID + 1];
    const IlvProjection* projection = mapInfo->getProjection();
    const IlvMapAdapter* adapter = mapInfo->getAdapter();
    IlvDisplay* display = manager->getDisplay();

    double a = projection->getEllipsoid()->getA();
    IlvPalette* plt = display->getPalette(view->getBackground(),
					  display->getColor("blue"));

    int i;
    int j;
    int k;

    IlvGraphicSet* set = new IlvGraphicSet();

    for (i = -180; i <= 180; i += (LAT_DIV_GRID + LAT_DIV_GRID_SUP)) {
	lon = IlvMaps::DegreeToRadian(i);
	for (j = -90, k = 0; j <= 90; j += LONG_DIV_GRID) {
	    lat = IlvMaps::DegreeToRadian(j);
	    c.move(lon, lat);
	    if (projection->forward(c, c) == IlvMaps::NoError()) {
		if (k > 0) {
		    if (dist(c, last) < a) {
			adapter->toViews(c, y[k++]);
			last = c;
		    }
		    else {
			if (k > 1) {
			    IlvPolyline* pl = new IlvPolyline(display,
							      k, y, plt);
			    set->addObject(pl);
			}
			k = 0;
		    }
		}
		else {
		    adapter->toViews(c, y[k++]);
		    last = c;
		}
	    }
	}
	if (k) {
	    IlvPolyline* pl = new IlvPolyline(display, k, y, plt);
	    set->addObject(pl);
	}
    }

    for (i = -90; i <= 90; i += (LONG_DIV_GRID + LONG_DIV_GRID_SUP)) {
	lat = IlvMaps::DegreeToRadian(i);
	for (j = -180, k = 0; j <= 180; j += LAT_DIV_GRID) {
	    lon = IlvMaps::DegreeToRadian(j);
	      c.move(lon, lat);
	    if (projection->forward(c, c) == IlvMaps::NoError()) {
		if (k > 0) {
		    if (dist(c, last) < a) {
			adapter->toViews(c, x[k++]);
			last = c;
		    }
		    else {
			if (k > 1) {
			    IlvPolyline* pl = new IlvPolyline(display,
							      k, x, plt);
			    set->addObject(pl);
			}
			k = 0;
		    }
		}
		else {
		    adapter->toViews(c, x[k++]);
		    last = c;
		}
	    }
	}
	if (k) {
	    IlvPolyline* pl = new IlvPolyline(display, k, x, plt);
	    set->addObject(pl);
	}
    }
    IlvGraphic* o = manager->getObject("Grid");
    if (o) {
	manager->removeObject(o, IlFalse);
    }
    manager->addObject(set, IlFalse);
    manager->setObjectName(set, "Grid");
    if (redraw) {
	manager->draw(view, IlFalse);
    }
}

// --------------------------------------------------------------------------
// Initializes the vectors projector
// --------------------------------------------------------------------------
VectorProjector::VectorProjector(IlvDisplay* display)
    : Gui(),
      _mapInfo(0)
{
}

// --------------------------------------------------------------------------
VectorProjector::~VectorProjector()
{
    if (_mapInfo) {
	_mapInfo->detach();
	delete _mapInfo;
    }
}

// --------------------------------------------------------------------------
// Load a .ilv file
// --------------------------------------------------------------------------
void
VectorProjector::loadSourceData(IlvDisplay* display,int argc, char** argv)
{
    _sourceManager = new IlvManager(display,
				    0,
				    IlFalse,
				    30000 /* no quadtree needed */,
				    30000 /* no quadtree needed */);
    char* file;
    if (argc > 1) {
	file = argv[1];
    }
    else {
	file = (char*)"world.ilv";
    }

    ifstream stream(display->findInPath(file));
    _sourceManager->read(stream);
}

// --------------------------------------------------------------------------
static void
ProjectObject(IlvGraphic* g, IlvAny a)
{
    VectorProjector* projector = (VectorProjector*) a;
    projector->project(g);
}

// --------------------------------------------------------------------------
// Project a polyline.
// - inverse the projection in which the object is found.
// - reproject using the selected projection.
// --------------------------------------------------------------------------
void
VectorProjector::project(IlvGraphic* g)
{
    IlvMapInfo* sourceMapInfo = IlvMapInfo::Get(_sourceManager);
    if (!sourceMapInfo) {
	IlvPrint("Source is not georeferenced");
	return;
    }
    const IlvProjection* p = _mapInfo->getProjection();
    const IlvMapAdapter* a = _mapInfo->getAdapter();

    if (g->isSubtypeOf(IlvPolyline::ClassInfo())) {
	IlvPolyline* source = (IlvPolyline*) g;
	IlUInt count = source->numberOfPoints();
	IlvPoint* points = new IlvPoint[count];
	source->getPoints(points);
	IlBoolean noError = IlTrue;
	IlvMapsError noMapError = IlvMaps::NoError();
	IlvCoordinate c;
	IlDouble distance;
	for (IlUInt i = 0; i < count; i++) {
	    sourceMapInfo->inverse(points[i], c);
	    if (p->forward(c, c) != noMapError) {
		noError = IlFalse;
		break;
	    }
	    if (!a->isInRange(c)) {
		noError = IlFalse;
		break;
	    }
	    a->toViews(c, points[i]);
	    if (i > 0) {
		IlDouble dx;
		IlDouble dy;

		dx = (IlDouble)(points[i].x() - points[i - 1].x());
		dy = (IlDouble)(points[i].y() - points[i - 1].y());

		distance = sqrt(dx * dx + dy * dy);
		distance = a->fromViews(distance);
		distance = p->getUnitConverter()->toMeters(distance);
		if (distance > p->getEllipsoid()->getA()) {
		    // disc assumed
		    noError = IlFalse;
		    break;
		}
	    }
	}
	if (noError) {
	    IlvPolyline* projected =
		new IlvPolyline(getDisplay(),
				count,
				points,
				source->getPalette());
	    projected->setForeground(getForeground());
	    getManager()->addObject(projected, IlFalse);
	}
	delete[] points;
    }
}

// --------------------------------------------------------------------------
// Shows the grid
// --------------------------------------------------------------------------
void
VectorProjector::showGrid(IlBoolean s)
{
    if (isShowingGrid() == s) {
	return;
    }
    Gui::showGrid(s);
    IlvManager* manager = getManager();
    IlvView* view = getView();
    if (isShowingGrid()) {
	MakeGrid(manager, view, _mapInfo, IlTrue);
    }
    else {
	IlvGraphic* set = manager->getObject("Grid");
	if (set) {
	    manager->removeObject(set);
	}
    }
}

// --------------------------------------------------------------------------
// Get the center of view in projection coordinates
// Used by the keep long/lat feature
// --------------------------------------------------------------------------
IlBoolean
VectorProjector::getViewCenter(IlvCoordinate& ll)
{
    IlvRect rect;
    IlvFloatPoint fp;
    IlBoolean ret;

    IlvManager* manager = getManager();
    IlvView* view = getView();
    view->sizeVisible(rect);
    fp.move((IlFloat)rect.x() + (IlFloat)rect.w()/(IlFloat)2.,
	    (IlFloat)rect.y() + (IlFloat)rect.h()/(IlFloat)2.);
    IlvTransformer* tr = manager->getTransformer(view);
    if (tr) {
	tr->inverse(fp);
    }

    const IlvMapAdapter* adapter = _mapInfo->getAdapter();
    ll.x(adapter->fromViews(fp.x()));
    ll.y(adapter->fromViews(-fp.y()));
    const IlvProjection* pr = _mapInfo->getProjection();

    ret = IlFalse;
    if (pr->inverse(ll) == IlvMaps::NoError()) {
	ret = IlTrue;
    }
    return ret;
}

// --------------------------------------------------------------------------
// Set the center of view in projection coordinates
// Used by the keep long/lat feature
// --------------------------------------------------------------------------
void
VectorProjector::setViewCenter(IlvCoordinate& ll)
{
    IlvManager* manager = getManager();
    IlvView* view = getView();
    const IlvMapAdapter* adapter = _mapInfo->getAdapter();
    const IlvProjection* projection = _mapInfo->getProjection();
    projection->forward(ll);

    IlvFloatPoint fp;
    fp.x((IlFloat)adapter->toViews(ll.x()));
    fp.y((IlFloat)adapter->toViews(-ll.y()));

    IlvTransformer* tr = manager->getTransformer(view);
    if (tr) {
	tr->apply(fp);
    }

    IlvRect rect;
    view->sizeVisible(rect);
    IlvTransfoParam tx = fp.x() -
	((IlvTransfoParam)rect.x() + (IlvTransfoParam)rect.w()/2.);
    IlvTransfoParam ty = fp.y() -
	((IlvTransfoParam)rect.y() + (IlvTransfoParam)rect.h()/2.);

    IlvTransformer t(1., 0., 0., 1., -tx, -ty);
    manager->addTransformer(view, &t);
}

// --------------------------------------------------------------------------
// Project using selected projection
// --------------------------------------------------------------------------
void
VectorProjector::showProjection(IlvProjection* projection)
{
    IlvCoordinate ll;
    IlBoolean doCenter;

    CenterInteractor* ci = getCenterInteractor();
    if (ci) {
	ci -> abort();
    }

    wait(IlTrue);

    IlvManager* manager = getManager();
    IlvView* view = getView();
    doCenter = IlFalse;


    if (_mapInfo) {
	if (getKeepll()) {
	    if (getViewCenter(ll)) {
		doCenter = IlTrue;
	    }
	}
	_mapInfo->detach();
	delete _mapInfo;
    }

    _mapInfo = new IlvMapInfo(projection, 0, IlFalse);
    _mapInfo->attach(manager);

    manager->deleteAll(IlTrue, IlFalse);
    for (int i = 0; i < _sourceManager->getNumLayers(); i++) {
	_sourceManager->applyToObjects(i, ProjectObject, this, IlTrue);
    }

    if (isShowingGrid()) {
	MakeGrid(manager, view, _mapInfo, IlFalse);
    }

    if (doCenter) {
	setViewCenter(ll);
	manager->draw(view, IlTrue);
    }
    else {
	showAll();
    }

    wait(IlFalse);
}

// --------------------------------------------------------------------------
void
VectorProjector::showAll()
{
    IlvManager* manager = getManager();
    IlvView* view = getView();
    IlBoolean keepRatio = manager->isKeepingAspectRatio(view);

    IlvGraphic* o = manager->getObject("Grid");
    if (o) {
	manager->removeObject(o, IlFalse, IlFalse);
    }
    manager->fitTransformerToContents(view, IlFalse, keepRatio);
    if (o) {
	manager->addObject(o, IlFalse);
	manager->setObjectName(o, "Grid");
    }
    manager->draw(view, IlTrue);
}

// --------------------------------------------------------------------------
const char**
VectorProjector::getLabels(IlUShort& rcount)
{
    _dictionary.unregisterProjection(IlvFrenchLambertProjection::
   				     ClassInfo());
    IlUInt count;
    const char** projectionNames = _dictionary.getProjectionNames(count);
    rcount = (IlUShort)count;
    return projectionNames;
}

// --------------------------------------------------------------------------
void
VectorProjector::comboItemSelected(const char* projectionName)
{
    if (projectionName) {
	IlvProjection* projection =
	    _dictionary.createProjection(projectionName);
	if (projection) {
	    projection->setShared();
	    projection->lock();
	    projection->setEllipsoid(*IlvEllipsoid::SPHERE());
	    showProjection(projection);
	    projection->unLock();
	}
    }
}

// --------------------------------------------------------------------------
void
VectorProjector::centerProjection(IlvView* view, IlvEvent& event)
{
    IlvCoordinate ll;
    IlvMapInfo* mapInfo = getMapInfo();

    if (mapInfo &&
	(mapInfo->inverse(event, view, ll) == IlvMaps::NoError())) {
	IlvProjection* p = mapInfo->getProjection()->copy();
	p->setShared();
	p->lock();
	p->setLLCenter(ll.x(), ll.y());
	showProjection(p);
	p->unLock();
    }
}

// --------------------------------------------------------------------------
static
void ShowMousePosition(IlvView* view, IlvEvent& event, IlvAny arg)
{
    VectorProjector* viewer = (VectorProjector*) arg;
    IlvMapInfo* mapInfo = viewer->getMapInfo();

    if (event.type() != IlvPointerMoved) {
	return;
    }

    char buf1[12];
    char buf2[12];
    char label[50];

    IlvCoordinate ll;

    if (mapInfo) {
	if (mapInfo->inverse(event, view, ll) == IlvMaps::NoError()) {
	    sprintf(label, "%s %s",
		    IlvMaps::RadianToDMS(buf1, ll.x(), IlFalse),
		    IlvMaps::RadianToDMS(buf2, ll.y(), IlTrue));
	}
	else {
	    sprintf(label, "Can't compute latitude and longitude");
	}
    }
    else {
	sprintf(label, "No georeferencment information available");
    }

    IlvTextField* statusBar = viewer->getStatusBar();

    statusBar->setLabel(label);
    statusBar->reDraw();
}

// --------------------------------------------------------------------------
// Main
// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay("Gui", 0, argc, argv);
    if (display->isBad()) {
	IlvPrint("Couldn't open display");
	return 1;
    }
    IlPathName localPath(display->getHomePath());
    display->prependToPath(localPath);
    localPath.addDirectory("samples/maps/projvect/data");
    display->prependToPath(localPath);

    VectorProjector* viewer = new VectorProjector(display);

    viewer->createGui(display);
    viewer->setCenterInteractor(new ProjCenterInteractor(viewer));
    viewer->loadSourceData(display, argc, argv);
    IlvProjection* p = new IlvAlbersEqualAreaProjection();
    p->setShared();
    p->lock();
    viewer->showProjection(p);
    p->unLock();
    viewer->getView()->setInputCallback(ShowMousePosition, viewer);

    viewer->show();
    IlvMainLoop();

    return 0;
}
