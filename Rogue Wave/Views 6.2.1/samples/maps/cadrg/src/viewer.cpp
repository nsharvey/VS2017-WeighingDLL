// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/cadrg/src/viewer.cpp
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
// Implementation of CADRG viewer class
// --------------------------------------------------------------------------
#include <ilviews/maps/tiling/tilecache.h>
#include <ilviews/maps/scalefilter.h>
#include <ilviews/maps/projection/geogproj.h>

#include <ilviews/bitmaps/png.h>
#include <ilviews/manager/rectangl.h>

#include <viewer.h>

// --------------------------------------------------------------------------
// Note: This define is used to indicate the maximum of pixels (in millions)
// which can display before apply of the transformation. It is necessary to
// set a limitation because the CADRG are very big and can contains several
// billions of pixels which can't be set in memory.
// --------------------------------------------------------------------------
#define MAX_PIXELS_SHOW 400

// --------------------------------------------------------------------------
// Callbacks
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Exit callback called from an accelerator.
// --------------------------------------------------------------------------
static void
ExitCB(IlvView*, IlvAny a)
{
    Viewer* viewer = (Viewer*)a;
    delete viewer->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Called when the user clicks the Exit button of toolbar
// --------------------------------------------------------------------------
static void
ExitButtonCB(IlvGraphic*, IlvAny a)
{
    Viewer* viewer = (Viewer*)a;
    delete viewer->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Called when the user clicks the Zoom button of toolbar
// --------------------------------------------------------------------------
static void
ZoomCB(IlvGraphic* , IlvAny a)
{
    Viewer* viewer = (Viewer*)a;
    viewer->zoom();
}

// --------------------------------------------------------------------------
// Called when the user clicks the unzoom button of toolbar
// --------------------------------------------------------------------------
static void
UnZoomCB(IlvGraphic* , IlvAny a)
{
    Viewer* viewer = (Viewer*)a;
    viewer->unZoom();
}

// --------------------------------------------------------------------------
// Called when the user clicks the show all button of toolbar
// --------------------------------------------------------------------------
static void
ShowAllCB(IlvGraphic* , IlvAny a)
{
    Viewer* viewer = (Viewer*)a;
    viewer->showAll();
}

// --------------------------------------------------------------------------
// Viewer
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
Viewer::Viewer(IlvDisplay* display, const char* tocname)
    : _display(display)
{
    _limitWidth = 0;
    _layers[0] = 0;
    _layers[1] = 0;
    _layers[2] = 0;
    _tocReader =  new IlvCADRGTocReader(tocname);

    mainWindow();

    _chooser = new CovChoose(display, this);
    _chooser->selectDefault();
}

// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
Viewer::~Viewer()
{
    delete _tocReader;
    delete _chooser;
}

// --------------------------------------------------------------------------
// Builds the main window.
// --------------------------------------------------------------------------
void
Viewer::mainWindow()
{
    IlvRect r(0, 0, 500, 300);
    _gadgetContainer = new IlvGadgetContainer(_display,
					      "Gui",
					      "Cadrg loader",
					      r,
					      IlFalse,
					      IlFalse);
    _gadgetContainer->setDestroyCallback(ExitCB, (IlvAny)this);
    IlvToolBar* tb = createToolBar();
    IlvRect tbr;
    tb->boundingBox(tbr);
    r.moveResize(0, tbr.h(), r.w(), r.h() - tbr.h());
    _managerRectangle = new IlvManagerRectangle(_display, r);
    _manager = _managerRectangle->getManager();

    _managerRectangle->makeView(_gadgetContainer);
    _view = _managerRectangle->getView();
    _manager->setDoubleBuffering(_view, IlTrue);
    _manager->setKeepingAspectRatio(_view, IlTrue);
    _gadgetContainer->addObject(_managerRectangle);

    IlvBitmap *background = _display->readBitmap("empty.png");

    if (background) {
	_view->setBackgroundBitmap(background);
    }

    _panzoom = new IlvPanZoomInteractor(_manager, _view);
    _panzoom->setOpaqueMove(IlFalse);
    _manager->setInteractor(_panzoom, _view);

    IlvGraphicHolder* ho = _gadgetContainer->getHolder();
    ho->attach(_managerRectangle, IlvHorizontal, 0, 1, 0);
    ho->attach(_managerRectangle, IlvVertical, 0, 1, 0);

    IlvGeographicProjection* proj = new IlvGeographicProjection();
    proj->setShared();
    _mapinfo = new IlvMapInfo(proj,
    			      new IlvMapAdapter(1e-5),
    			      IlFalse);
    _mapinfo->attach(_manager);
}

// --------------------------------------------------------------------------
// Create the toolbar
// --------------------------------------------------------------------------
IlvToolBar*
Viewer::createToolBar()
{
    IlvRect cbb;
    _gadgetContainer->boundingBox(cbb);

    IlvToolBar* toolBar= new IlvToolBar(_display, IlvRect(0, 0, cbb.w(), 0));
    toolBar->setName("ToolBar");

    IlvMenuItem* zoomItem = new IlvMenuItem();
    zoomItem->setBitmap(_display->readBitmap("data/maps/zoom.png"));
    zoomItem->setToolTip("Zoom");
    zoomItem->setClientData(this);
    zoomItem->setCallback(ZoomCB);
    toolBar->insertItem(zoomItem);

    IlvMenuItem* unZoomItem = new IlvMenuItem();
    unZoomItem->setBitmap(_display->readBitmap("data/maps/unzoom.png"));
    unZoomItem->setToolTip("Unzoom");
    unZoomItem->setClientData(this);
    unZoomItem->setCallback(UnZoomCB);
    toolBar->insertItem(unZoomItem);

    IlvMenuItem* showAllItem = new IlvMenuItem();
    showAllItem->setBitmap(_display->readBitmap("data/maps/fit.png"));
    showAllItem->setToolTip("Show All");
    showAllItem->setClientData(this);
    showAllItem->setCallback(ShowAllCB);
    toolBar->insertItem(showAllItem);

   toolBar->setConstraintMode(IlTrue);

    _gadgetContainer->addObject(toolBar);
    _gadgetContainer->getHolder()->attach(toolBar, IlvHorizontal, 0, 1, 0);

    return toolBar;
}

// --------------------------------------------------------------------------
// Execute a zoom
// --------------------------------------------------------------------------
void
Viewer::zoom()
{
    IlvRect visibleRect;
    _view->sizeVisible(visibleRect);
    _manager->initReDraws();
    _manager->zoomView(_view,
		      IlvPoint(visibleRect.centerx(),visibleRect.centery()),
		      1.5,
		      1.5,
		      IlFalse);
    _manager->invalidateRegion(_view, visibleRect);
    _manager->reDrawViews();
}

// --------------------------------------------------------------------------
// Execute an unzoom when it is possible
// --------------------------------------------------------------------------
void
Viewer::unZoom()
{
    IlvRect bbox;
    IlvRect visibleRect;

    _manager->computeBBox(bbox, _view);
    _view->sizeVisible(visibleRect);
    // The window size has been increase, we can't unzoom
    // before call to fitToContent to compute new limit width of bbox
    if ((visibleRect.w() > _viewSize.w()) ||
	(visibleRect.h() > _viewSize.h())) {
	return;
    }
    // We check that the unzoom is not to strong
    IlInt est = (IlInt)((IlFloat)(bbox.w()) * ((IlFloat)(1./1.5)));
    if (est < _limitWidth) {
	showAll();
	return;
    }
    _manager->initReDraws();
    _manager->zoomView(_view,
		      IlvPoint(visibleRect.centerx(),visibleRect.centery()),
		      (float) (1./1.5),
		      (float) (1./1.5),
		      IlFalse);

    _manager->invalidateRegion(_view, visibleRect);
    _manager->reDrawViews();
}

// --------------------------------------------------------------------------
// Execute to show a maximum of the map
// --------------------------------------------------------------------------
void
Viewer::showAll()
{
    IlvRect newrect;
    _view->sizeVisible(newrect);
    if ((newrect.w() != _viewSize.w()) || (newrect.h() != _viewSize.h())) {
	IlFloat x0, y0;
	IlFloat sx, sy;
	IlvDim viewW = newrect.w()-1;
	IlvDim viewH = newrect.h()-1;
	IlvRect rect;
	rect.resize(0, 0);
	_manager->computeBBox(rect, _view);
	if (!rect.w()) {
	    return;
	}

	// Save initial values to compute the transformer to fit
	if (_limitWidth == 0) {
	    _manager->computeBBox(rect, _view);
	    _initialBbox = rect;
	    IlvTransformer* mt = _manager->getTransformer(_view);
	    if (mt) {
		_initialTrans = *mt;
	    }
	}
	rect = _initialBbox;

	// See the comment about memory limitation at the top of this file
	IlvDouble coef = (((IlDouble)rect.w())/1000.0);
	coef *= (((IlDouble)rect.h())/1000.0);
	coef /= ((IlDouble)MAX_PIXELS_SHOW);
	coef  = sqrt(coef);

	if (coef > 1.0) {
	    sx = ((IlFloat)viewW / (IlFloat)rect.w()) * ((IlFloat)coef);
	    sy = ((IlFloat)viewH / (IlFloat)rect.h()) * ((IlFloat)coef);
	}
	else {
	    sx = ((IlFloat)viewW / (IlFloat)rect.w());
	    sy = ((IlFloat)viewH / (IlFloat)rect.h());
	}
	if (sx < sy) {
	    sy = sx;
	}
	else {
	    sx = sy;
	}
	x0 = (newrect.centerx() - sx*rect.centerx());
	y0 = (newrect.centery() - sy*rect.centery());
	// Compute new transformer before to store for next showAll calls
	IlvTransformer t(sx, (IlFloat)0, (IlFloat)0, sy, x0, y0);
	_transToFit = _initialTrans;
	_transToFit.compose(t);
	_manager->setTransformer(_view, &_transToFit);
	// Store control and optimize information
	_viewSize = newrect;
	_manager->computeBBox(rect, _view);
	_limitWidth = rect.w();
    }
    else {
	_manager->setTransformer(_view,&_transToFit);
    }
    _manager->draw((IlvView*)_view, IlTrue);
}

// --------------------------------------------------------------------------
// Perform the loading of specified coverages.
// --------------------------------------------------------------------------
void
Viewer::loadCoverages(const IlvCADRGCoverage* smallScaleCoverage,
		      const IlvCADRGCoverage* mediumScaleCoverage,
		      const IlvCADRGCoverage* largeScaleCoverage)
{
    _manager->deleteAll(IlTrue, IlTrue);
    while (_manager->getNumLayers() > 2) {
	_manager->removeLayer();
    }

    IlvCADRGLayer* l;
    IlvMapsError status;
    _layers[0] = 0;
    _layers[1] = 0;
    _layers[2] = 0;

    if (smallScaleCoverage) {
	l = new IlvCADRGLayer(*smallScaleCoverage);
	status = l->getInitStatus();
	if (status == IlvMaps::NoError()) {
	    _manager->addLayer(l);
	    _layers[0] = l;
	}
	else {
	    IlvPrint(IlvMaps::GetErrorMessageId(status));
	}
	l->fitToPreferredZoomFactor(_view);
    }
    if (mediumScaleCoverage) {
	l = new IlvCADRGLayer(*mediumScaleCoverage);
	status = l->getInitStatus();
	if (status == IlvMaps::NoError()) {
	    _manager->addLayer(l);
	    _layers[1] = l;
	}
	else {
	    IlvPrint(IlvMaps::GetErrorMessageId(status));
	}
	l->fitToPreferredZoomFactor(_view);
    }
    if (largeScaleCoverage) {
	l = new IlvCADRGLayer(*largeScaleCoverage);
	status = l->getInitStatus();
	if (status == IlvMaps::NoError()) {
	    _manager->addLayer(l);
	    _layers[2] = l;
	}
	else {
	    IlvPrint(IlvMaps::GetErrorMessageId(status));
	}
	l->fitToPreferredZoomFactor(_view);
    }

    installVisibilityFilters();
    IlvTiledLayer::StartAll(_manager);

    showAll();
}

// --------------------------------------------------------------------------
// Install the scale visibility filters.
// --------------------------------------------------------------------------
void
Viewer::installVisibilityFilters()
{
    IlDouble smallScale = 1.;
    if (_layers[0]) {
	smallScale = _layers[0]->getPreferredScale();
    }

    IlDouble middleScale = 1.;
    if (_layers[1]) {
	middleScale = _layers[1]->getPreferredScale();
    }

    IlDouble largeScale = 1;
    if (_layers[2]) {
	largeScale = _layers[2]->getPreferredScale();
    }

    IlvScaleVisibilityFilter* f;

    _filters[0] = 0;
    _filters[1] = 0;
    _filters[2] = 0;

    if (_layers[0]) {
	f = new IlvScaleVisibilityFilter(0.,
					 sqrt(smallScale * middleScale));
	_layers[0]->addVisibilityFilter(f);
	_filters[0] = f;
    }

    if (_layers[1]) {
	f = new IlvScaleVisibilityFilter(sqrt(smallScale * middleScale),
					 sqrt(middleScale * largeScale));
	_layers[1]->addVisibilityFilter(f);
	_filters[1] = f;
    }

    if (_layers[2]) {
	f = new IlvScaleVisibilityFilter(sqrt(middleScale * largeScale),
					 1.);
	_layers[2]->addVisibilityFilter(f);
	_filters[2] = f;
    }
}

// --------------------------------------------------------------------------
void
Viewer::show()
{
    _gadgetContainer->show();
}
