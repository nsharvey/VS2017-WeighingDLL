// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/dted/src/dtedlod.cpp
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
// Implementation of DTED Load On Demand viewer.
// --------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include <ilviews/manager/manager.h>
#include <ilviews/manager/selinter.h>
#include <ilviews/manager/paninter.h>
#include <ilviews/maps/mapinfo.h>
#include <ilviews/maps/renderer.h>
#include <ilviews/maps/projection/geogproj.h>
#include <ilviews/maps/projection/unknownp.h>

#include <dtedlod.h>

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
// Static and callback functions
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Exit from destroy callback
// --------------------------------------------------------------------------
static void
Exit(IlvView*, IlvAny a)
{
    DtedLod* dtl = (DtedLod*)a;
    delete dtl->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Exit callback, called from the exit button of the tool bar.
// --------------------------------------------------------------------------
static void
Exit(IlvGraphic*, IlvAny a)
{
    DtedLod* dtl = (DtedLod*)a;
    delete dtl->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Zoomin toolbar callback
// --------------------------------------------------------------------------
static void
Zoom(IlvGraphic* , IlvAny a)
{
    DtedLod* dtl = (DtedLod*)a;
    IlvRect visibleRect;
    IlvManager* manager = dtl->getManager();
    IlvView* view = dtl->getView();

    manager->zoomView(view,
		      IlvPoint(visibleRect.centerx(),
			       visibleRect.centery()),
		      1.5,
		      1.5,
                      IlTrue);
}

// --------------------------------------------------------------------------
// Zoom out toolbar callback
// --------------------------------------------------------------------------
static void
UnZoom(IlvGraphic* , IlvAny a)
{
    DtedLod* dtl = (DtedLod*)a;

    IlvManagerRectangle* mgrRect = dtl->getManagerRectangle();
    IlvRect visibleRect;

    IlvManager* manager = mgrRect->getManager();

    manager->zoomView(mgrRect->getView(),
		      IlvPoint(visibleRect.centerx(),
			       visibleRect.centery()),
		      (float) (1./1.5),
		      (float) (1./1.5),
                      IlTrue);
}

// --------------------------------------------------------------------------
static void
ShowAll(IlvGraphic* , IlvAny a)
{
    DtedLod* dtl = (DtedLod*)a;
    IlvManagerRectangle* mgrRect = dtl->getManagerRectangle();
    IlvManager* manager = mgrRect->getManager();
    IlvView* view = mgrRect->getView();
    manager->fitTransformerToContents(view, IlvTrue, IlvTrue);
}


// --------------------------------------------------------------------------
// Debug view toolbar callback, toggles the debug view visibility
// --------------------------------------------------------------------------
static void
Debug(IlvGraphic* k, IlvAny a)
{
    IlvToolBar* tb = (IlvToolBar*)k;
    IlUInt pos = tb->whichSelected();
    IlvMenuItem* t = tb->getItem((IlUShort)pos);
    DtedLod* dtl = (DtedLod*)a;
    dtl->debugView(t->isSelected());
}

// --------------------------------------------------------------------------
// DTED loader
// --------------------------------------------------------------------------
DtedLod::DtedLod(IlvDisplay* display, const char* dirname)
    : _display(display),
      _dirName(dirname ? strcpy(new char[strlen(dirname)+1], dirname) : 0),
      _dtedLayer(0),
      _debug(0),
      _panzoom(0),
      _magvint(0)
{
    IlPathName p(_dirName);

    _isDir = p.isSystemDirectory() | IlIUrlStream::IsAnURL(_dirName);

    mainWindow();

    if (_isDir) {
	dtedLayer();
    }
    else { // simply loads a dted file
	dtedFile();
    }
    interactors();
}

// --------------------------------------------------------------------------
DtedLod::~DtedLod()
{
    if (_gadgetContainer) {
	delete _gadgetContainer;
    }
    if (_dtedLayer) {
	delete _dtedLayer;
    }
    if (_panzoom) {
	delete _panzoom;
    }
    if (_magvint) {
	delete _magvint;
    }
    if (_debug) {
	delete _debug;
    }
}

// --------------------------------------------------------------------------
// Creates the main window
// --------------------------------------------------------------------------
void
DtedLod::mainWindow()
{
    IlvDim width = 640;
    IlvDim height = 480;

    IlvRect r(50, 50, width, height);

    _gadgetContainer = new IlvGadgetContainer(_display,
					      "DtedLod",
					      "Dted lod demo",
					      r,
					      IlFalse,
					      IlFalse);

    _gadgetContainer->setDestroyCallback(Exit, (IlvAny)this);

    IlvToolBar* tb = createToolBar();
    IlvDim tbh = tb->h();
    IlvColor* col = _display->getColor((IlvIntensity)30,
				       (IlvIntensity)235 * 256,
				       (IlvIntensity)245 * 256);

    IlvGraphicHolder* gh = _gadgetContainer->getHolder();
    r.move(0,tbh);
    _managerRectangle = new IlvManagerRectangle(_display, r);
    _managerRectangle->setBackground(col);
    _gadgetContainer->addObject(_managerRectangle, IlFalse);
    gh->attach(_managerRectangle, IlvHorizontal, 0, 1, 0);
    gh->attach(_managerRectangle, IlvVertical, 0, 1, 0);

    _manager = _managerRectangle->getManager();
    _view = _managerRectangle->getView();
    _manager->setKeepingAspectRatio(_view, IlTrue);
}

// --------------------------------------------------------------------------
// Toolbar creation with an exit, zoomin and zoomout items.
// --------------------------------------------------------------------------
IlvToolBar*
DtedLod::createToolBar()
{
    IlvRect cbb;
    _gadgetContainer->boundingBox(cbb);

    IlvToolBar* toolBar= new IlvToolBar(_display, IlvRect(0, 0, cbb.w(), 0));
    toolBar->setName("ToolBar");

    IlvMenuItem* zoomItem = new IlvMenuItem();
    zoomItem->setBitmap(_display->readBitmap("data/maps/zoom.png"));
    zoomItem->setToolTip("Zoom");
    zoomItem->setClientData(this);
    zoomItem->setCallback(Zoom);
    toolBar->insertItem(zoomItem);

    IlvMenuItem* unZoomItem = new IlvMenuItem();
    unZoomItem->setBitmap(_display->readBitmap("data/maps/unzoom.png"));
    unZoomItem->setToolTip("Unzoom");
    unZoomItem->setClientData(this);
    unZoomItem->setCallback(UnZoom);
    toolBar->insertItem(unZoomItem);

    IlvMenuItem* showAllItem = new IlvMenuItem();
    showAllItem->setBitmap(_display->readBitmap("data/maps/fit.png"));
    showAllItem->setToolTip("Show all");
    showAllItem->setClientData(this);
    showAllItem->setCallback(ShowAll);
    toolBar->insertItem(showAllItem);

    if (_isDir) { // need a debug view only on load on demand mode
	IlvMenuItem* debugItem = new IlvMenuItem();
	debugItem->setBitmap(_display->readBitmap("data/maps/debug.png"));
	debugItem->setToolTip("Debug");
	debugItem->setToggle(IlTrue);
	debugItem->setClientData(this);
	debugItem->setCallback(Debug);
	toolBar->insertItem(debugItem);
    }

    toolBar->setConstraintMode(IlTrue);

    _gadgetContainer->addObject(toolBar);

    _gadgetContainer->getHolder()->attach(toolBar, IlvHorizontal, 0, 1, 0);

    return toolBar;
}

// --------------------------------------------------------------------------
// Creates a DTED tiled layer and starts it
// --------------------------------------------------------------------------
void
DtedLod::dtedLayer()
{
    IlvMapAdapter adapter(0.005);
    _dtedLayer = new IlvDTEDLayer(_dirName,
				  0,
				  &adapter);
    IlvMapsError status;
    status = _dtedLayer->getInitStatus();
    if (status != IlvMaps::NoError()) {
	IlvPrint("IlvDTEDLayer -> %s",
		 IlvMaps::GetErrorMessage(status, _display));
    }
    else {
	_manager->addLayer(_dtedLayer);
	if (_isDir)
	    _dtedLayer->fitTransformerToTile(_view, -46, 23);
	_dtedLayer->start();
    }
}

// --------------------------------------------------------------------------
// Loads s file
// --------------------------------------------------------------------------
void
DtedLod::dtedFile()
{
    IlvDTEDReader dte(_dirName);

    IlvMapsError status = IlvMaps::NoError();
    // checks if the reader is ok
    // i.e _dirName is a valid dted file
    status = dte.getInitStatus();
    if (status != IlvMaps::NoError()) {
	IlvPrint("getInitStatus -> %s",
	       IlvMaps::GetErrorMessage(status, _display));
	IlvExit(1);
    }

    // get the unique map feature
    const IlvMapFeature* f = dte.getNextFeature(status);
    if (status != IlvMaps::NoError()) {
	IlvPrint("getNextFeature -> %s",
	       IlvMaps::GetErrorMessage(status, _display));
	IlvExit(1);
    }

    //adapter, mapInfo and renderer to make the IlvGraphic
    IlvMapAdapter adapter(0.005);
    IlvMapInfo mapInfo(dte.getProjection(), &adapter);
    IlvFeatureRenderer* renderer = dte.getDefaultFeatureRenderer(_display);
    IlvGraphic* graphic = renderer->makeGraphic(*f, mapInfo, status);
    if (status != IlvMaps::NoError()) {
	IlvPrint("makeGraphic -> %s",
	       IlvMaps::GetErrorMessage(status, _display));
	IlvExit(1);
    }

    if (graphic) {
	_manager->addObject(graphic, IlFalse);
	_manager->fitTransformerToContents(_view);
    }

    delete renderer;
}

// --------------------------------------------------------------------------
// Creates a debug view and its magview interactor
// --------------------------------------------------------------------------
void
DtedLod::debugView(IlBoolean show)
{
    if (!_debug) {
	_debug = new IlvView(_display,
			     "DebugView",
			     "DebugView",
			     IlvRect(0, 0, 100, 100),
			     IlFalse, IlFalse);
	_manager->addView(_debug);
	//	_manager->setDoubleBuffering(_debug, IlTrue);
	_dtedLayer->setDebugView(_debug);

	_magvint = new IlvManagerMagViewInteractor(_manager, _debug, _view);

	_magvint->setAutoZooming(IlTrue);
	_magvint->setAutoTranslating(IlTrue);
	_magvint->setResizingAllowed(IlFalse);

	_manager->setInteractor(_magvint, _debug);
    }
    if (show) {
	IlvRect size;
	_gadgetContainer->frameBBox(size);
	size.moveResize(size.x() + size.w() + 10,
			size.y(), 200, 200);
	_debug->moveResize(size);
	_debug->show();
    }
    else {
	_debug->hide();
    }
}

// --------------------------------------------------------------------------
// Create a pan zoom interactor for the main window
// --------------------------------------------------------------------------
void
DtedLod:: interactors()
{
    _panzoom = new IlvPanZoomInteractor(_manager, _view);
    _panzoom->setOpaqueMove(IlFalse);
    _manager->setInteractor(_panzoom, _view);
}
