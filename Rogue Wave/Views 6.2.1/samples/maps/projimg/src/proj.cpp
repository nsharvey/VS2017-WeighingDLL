// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/projimg/src/proj.cpp
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
// Implementation of image projector
// --------------------------------------------------------------------------
#include <proj.h>
#include <pcenter.h>

#include <stdio.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/graphics/set.h>
#include <ilviews/graphics/zicon.h>
#include <ilviews/bitmaps/io.h>
#include <ilviews/bitmaps/jpg.h>
#include <ilog/pathname.h>

#if defined(IL_STD)
#  include <fstream>
ILVSTDUSE
#else  /* !ILVSTD */
#  include <fstream.h>
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

const IlInt TARGET_SIZE = 512;

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

    double a = projection->getEllipsoid()->getA() * 2.;
    IlvPalette* plt = display->getPalette(view->getBackground(),
#ifdef LARGE
					  display->getColor("black"));
#else
                                          display->getColor("blue"));
#endif

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
// Show mouse position as DMS
// --------------------------------------------------------------------------
static
void ShowMousePosition(IlvView* view, IlvEvent& event, IlvAny arg)
{
    ImageProjector* viewer = (ImageProjector*) arg;
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
	sprintf(label, "No geo-referencing information available");
    }

    IlvTextField* statusBar = viewer->getStatusBar();

    statusBar->setLabel(label);
    statusBar->reDraw();
}

// --------------------------------------------------------------------------
// Initializes the image projector
// --------------------------------------------------------------------------
ImageProjector::ImageProjector(IlvDisplay* display)
    : Gui(),
      _mapInfo(0)
{
    ifstream is(display->findInPath("earth.jpg")
#if (defined(WINDOWS) || defined(PM)) && !defined(MAINWIN)
		       , ios::in|ios::binary
#endif /* (WINDOWS || PM) && !MAINWIN */
		       );

    IlvJPGStreamer jpgstr;
    _sourceBitmapData = jpgstr.read(is);

    if (_sourceBitmapData) {
	_sourceWidth = _sourceBitmapData->getWidth();
	_sourceHeight = _sourceBitmapData->getHeight();
	_sourceData = _sourceBitmapData->getData();
    }
}

// --------------------------------------------------------------------------
// Deletes The image projector
// --------------------------------------------------------------------------
ImageProjector::~ImageProjector()
{
    if (_sourceBitmapData) {
	delete _sourceBitmapData;
	_sourceBitmapData = 0;
    }
    if (_mapInfo) {
	_mapInfo->detach();
	delete _mapInfo;
	_mapInfo = 0;
    }
}

// --------------------------------------------------------------------------
// Called from gui : Fills the combo that lists all the avaiable projections
// --------------------------------------------------------------------------
const char**
ImageProjector::getLabels(IlUShort& rcount)
{
    _dictionary.unregisterProjection(IlvFrenchLambertProjection::
    				     ClassInfo());
    IlUInt count;
    const char** projectionNames = _dictionary.getProjectionNames(count);
    rcount = (IlUShort)count;
    return projectionNames;
}

// --------------------------------------------------------------------------
// Get the center of view in projection coordinates used by the keep
// long/lat feature
// --------------------------------------------------------------------------
IlBoolean
ImageProjector::getViewCenter(IlvCoordinate& ll) const
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
// Set the center of view in projection coordinates used by the keep
// long/lat feature
// --------------------------------------------------------------------------
void
ImageProjector::setViewCenter(IlvCoordinate& ll)
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
// Creates the bitmap of TARGET_SIZE x TARGET_SIZE
// --------------------------------------------------------------------------
void
ImageProjector::makeBitmap()
{
    IlvManager* manager = getManager();
    manager->deleteAll(IlTrue, IlFalse);

    // creating the target bitmap : TARGET_SIZE * TARGET_SIZE
    // using 0 as transparent color
    IlvDisplay* display = getDisplay();
    IlShort depth = (display->screenDepth() <= 8) ? 1 : 4;
    IlvUChar* data = new IlvUChar[TARGET_SIZE * TARGET_SIZE * depth];

    IlvCoordinate xy;
    const IlvProjection* projection = _mapInfo->getProjection();
    IlDouble dist =  projection->getEllipsoid()->getA() * IlvMaps::Pi() * 2;
    dist = _mapInfo->getUnitConverter()->fromMeters(dist);
    IlDouble f = dist / (IlDouble) TARGET_SIZE;
    // get the coordinate of the center of the projection
    IlvCoordinate center = projection->getLLCenter();
    projection->forward(center, center);
    IlvMapsError mapNoError = IlvMaps::NoError();
    IlInt inverseX;
    IlInt inverseY;
    for (int x = 0; x < TARGET_SIZE; x++)
	for (int y = 0; y < TARGET_SIZE; y++) {
	    // get the coordinate in the projection's
	    // Cartesian coordinate system
	    IlDouble X = (IlDouble)(x - TARGET_SIZE / 2) * f + center.x();
	    IlDouble Y = (IlDouble) (TARGET_SIZE / 2 - y) * f + center.y();
	    xy.move(X, Y);

	    if (projection->inverse(xy, xy) == mapNoError) {
		inverseX = (IlInt)((IlvMaps::RadianToDegree(xy.x()) + 180.)
				   / 360. * (IlDouble) _sourceWidth);
		inverseY = (IlInt)((- IlvMaps::RadianToDegree(xy.y()) + 90.)
				   / 180. * (IlDouble) _sourceHeight);
		if (inverseX == (IlInt) _sourceWidth) {
		    inverseX = 0;
		}
		if (inverseY == (IlInt) _sourceHeight) {
		    inverseY = 0;
		}
		if ((inverseX >= 0) &&
		    (inverseX < (IlInt) _sourceWidth) &&
		    (inverseY >= 0) &&
		    (inverseY < (IlInt) _sourceHeight)) {
		    setColor(x, y, inverseX, inverseY,
			     _sourceWidth, depth, data);
		}
		else {
		    setUnknown(x, y, depth, data);
		}
	    }
	    else {
		setUnknown(x, y, depth, data);
	    }
	}

    IlvRGBBitmapData* dst = new IlvRGBBitmapData(TARGET_SIZE, TARGET_SIZE);
    dst->setRGBPixels(data, TARGET_SIZE * depth,
		      IlvRect(0, 0, TARGET_SIZE, TARGET_SIZE),
		      IlvPoint(0, 0));
    IlvBitmap* bitmap = new IlvBitmap(display, dst);
    delete [] data;
    delete dst;
    IlvZoomableIcon* icon = new IlvZoomableIcon(display, IlvPoint(0, 0),
						bitmap);
    IlvRect newSize =
	_mapInfo->getAdapter()->toViews(IlvCoordinate(center.x() - dist/2,
						      center.y() + dist/2),
					IlvCoordinate(center.x() + dist/2,
						      center.y() - dist/2));
    icon->moveResize(newSize);
    getManager()->addObject(icon, IlFalse);
}

// --------------------------------------------------------------------------
void
ImageProjector::showProjection(IlvProjection* projection)
{
    IlvCoordinate ll;
    IlBoolean doCenter;

    CenterInteractor* ci = getCenterInteractor();
    if (ci) {
	ci->abort();
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
    _mapInfo->attach(getManager());
    makeBitmap();
    if (isShowingGrid())	   {
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
ImageProjector::setUnknown(IlInt x,
			   IlInt y,
			   IlShort depth,
			   IlvUChar* data)
{
    if (depth != 1) {
	for (int i = 0; i < depth; i++) {
	    data[x * depth + y * depth * TARGET_SIZE + i] = 0;
	}
    }
    else {
	data[x + y * TARGET_SIZE] = 0;
    }
}

// --------------------------------------------------------------------------
void
ImageProjector::setColor(IlInt x,
			 IlInt y,
			 IlInt inverseX,
			 IlInt inverseY,
			 IlvDim width,
			 IlShort depth,
			 IlvUChar* data)
{
    IlInt target = x * depth + y * depth * TARGET_SIZE;
    IlInt source = inverseX * depth + inverseY * depth * width;
    if (depth != 1) {
	for (int i = 0; i < depth; i++)  {
	    data[target + i] = _sourceData[source + i];
	}
    }
    else {
	data[target] = _sourceData[source];
    }
}

// --------------------------------------------------------------------------
// Shows the grid
// --------------------------------------------------------------------------
void
ImageProjector::showGrid(IlBoolean s)
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
// combo callback -> a new projection is selected
// --------------------------------------------------------------------------
void
ImageProjector::comboItemSelected(const char* projectionName)
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
// Set a new projection center
// --------------------------------------------------------------------------
void
ImageProjector::centerProjection(IlvView* view, IlvEvent& event)
{
    IlvCoordinate ll;
    IlvMapInfo* mapInfo = getMapInfo();

    if (mapInfo) {
	if (mapInfo->inverse(event, view, ll) == IlvMaps::NoError()) {
	    IlvProjection* p = mapInfo->getProjection()->copy();
	    p->setShared();
	    p->lock();
	    p->setLLCenter(ll.x(), ll.y());
	    showProjection(p);
	    p->unLock();
	}
    }
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
    localPath.addDirectory("samples/maps/projimg/data");
    display->prependToPath(localPath);

    ImageProjector* viewer = new ImageProjector(display);

    viewer->createGui(display);
    viewer->setCenterInteractor(new ProjCenterInteractor(viewer));
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
