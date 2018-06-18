// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/geotiff/src/view.cpp
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
#include <view.h>

#include <ilviews/maps/adapter.h>
#include <ilviews/maps/format/geotiff/gtifftloader.h>
#include <ilviews/maps/format/geotiff/gtifflayer.h>
#include <ilviews/maps/format/geotiff/gtifftiler.h>

// --------------------------------------------------------------------------
// Exit callback, called from the exit button of the tool bar.
// --------------------------------------------------------------------------
static void
Exit(IlvGraphic*, IlvAny a)
{
    View* v = (View*)a;
    delete v->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Exit callback called from the window close button.
// --------------------------------------------------------------------------
static void
Exit(IlvView*, IlvAny a)
{
    View* v = (View*) a;
    delete v->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Open a file callback.
// --------------------------------------------------------------------------
static void
Open(IlvGraphic*, IlvAny a)
{
    View* v = (View*)a;
    v->openFile(0);
}

// --------------------------------------------------------------------------
// Tile a tiff file callback.
// --------------------------------------------------------------------------
static void
Tile(IlvGraphic*, IlvAny a)
{
    View* v = (View*)a;
    v->tileFile();
}

// --------------------------------------------------------------------------
// Detach an interactor from the manager.
// --------------------------------------------------------------------------
static void
ResetInteractor(View* v)
{
    IlvManager* manager = v->getManager();
    IlvView* view = v->getView();
    IlvManagerViewInteractor* mvi = manager->getInteractor(view);
    if (mvi) {
	mvi->abort();
	mvi->attach(manager, view);
    }
}

// --------------------------------------------------------------------------
// Zoom callback, zoom the view by a factor of 1.5
// --------------------------------------------------------------------------
static void
Zoom(IlvGraphic*, IlvAny a)
{
    View* v = (View*)a;
    ResetInteractor(v);
    IlvRect visibleRect;
    v->getView()->sizeVisible(visibleRect);
    v->getManager()->zoomView(v->getView(),
			      IlvPoint(visibleRect.centerx(),
				       visibleRect.centery()),
			      1.5, 1.5);
}

// --------------------------------------------------------------------------
// Unzzom callback, unzoom by a factor of 0.5
// --------------------------------------------------------------------------
static void
UnZoom(IlvGraphic*, IlvAny a)
{
    View* v = (View*)a;
    ResetInteractor(v);
    IlvRect visibleRect;
    v->getView()->sizeVisible(visibleRect);
    v->getManager()->zoomView(v->getView(),
			      IlvPoint(visibleRect.centerx(),
				       visibleRect.centery()),
			      0.5, 0.5);
}

// --------------------------------------------------------------------------
// Pan callback. Installs a pan zoom interactor.
// --------------------------------------------------------------------------
static void
Pan(IlvGraphic*, IlvAny a)
{
    View* v = (View*)a;
    ResetInteractor(v);
    IlvManager* manager = v->getManager();
    IlvView* view = v->getView();
    if(!v->getPanZoom()) {
	IlvPanZoomInteractor* pan = new IlvPanZoomInteractor(manager, view);
	pan->setOpaqueMove(IlFalse);
	pan->setDrawingBitmap(IlFalse);
	v->setPanZoom(pan);
    }
    manager->setInteractor(v->getPanZoom(), view);
}

// --------------------------------------------------------------------------
// Debug callback. Shows the debug view.
// --------------------------------------------------------------------------
static void
Debug(IlvGraphic* k, IlvAny a)
{
    IlvToolBar* tb = (IlvToolBar*)k;
    IlUInt pos = tb->whichSelected();
    IlvMenuItem* t = tb->getItem((IlUShort)pos);
    View* v = (View*)a;
    v->debugView(t->isSelected());
}

// --------------------------------------------------------------------------
// View constructor. Constructs the application main window.
// --------------------------------------------------------------------------
View::View(IlvDisplay* display, const char* file)
    : _display(display),
      _fileSel(0),
      _tiler(0),
      _layer(0),
      _panzoom(0),
      _debug(0),
      _alert(0)
{
    mainWindow();
    openFile(file);
}

// --------------------------------------------------------------------------
// Destructor. Clean stuff.
// --------------------------------------------------------------------------
View::~View()
{
    if (_fileSel) {
	delete _fileSel;
    }
    if (_tiler) {
	delete _tiler;
    }
    if (_panzoom) {
	delete _panzoom;
    }
    if (_magvint) {
	delete _magvint;
    }
}

// --------------------------------------------------------------------------
// Opens a file to load.
// --------------------------------------------------------------------------
void
View::openFile(const char* file)
{
    const char* filename;
    if (!file) {
	if (!_fileSel)
	    _fileSel = new FileSelector(getTopView());
	_fileSel->show();
	filename = _fileSel->getString();
	if (!filename) {
	    return;
	}
    }
    else {
	filename = _display->findInPath(file);
    }
    if (_layer) {
	_manager->removeLayer(_layer->getIndex());
	_layer = 0;
    }
    IlvMapAdapter a(0.5);
    IlvGeoTIFFTileLoader* tl = new IlvGeoTIFFTileLoader(filename, &a);
    if (tl->getInitStatus() != IlvMaps::NoError()) {
	IlString s(filename);
	s += ": Not a TIFF File";
	alert(s.getValue());
	delete tl;
	return;
    }
    _layer = new IlvGeoTIFFLayer(tl);
    _layer->setDebugView(_debug);
    _layer->setDebugDrawingOnTop(IlFalse);
    _manager->addLayer(_layer);

    IlvGeoTIFFReader reader (filename);
    if(reader.getInitStatus() != IlvMaps::NoError()) {
	IlString s(filename);
	s += ": Not a TIFF File";
	alert(s.getValue());
	return;
    }
    int c = reader.getColumnCount();
    int r = reader.getRowCount();
    _layer->fitTransformerToTile(getView(), r/2, c/2);

    _layer->start();
    _manager->reDraw();
}

// --------------------------------------------------------------------------
// Do the tiling job : Constructs a IlvGeoTIFFTiler with the source file name
// and target file name and calls the performTiling method to do the job.
// --------------------------------------------------------------------------
void
View::tileFile()
{
    if (!_tiler) {
	_tiler = new Tiler(getTopView());
    }
    _tiler->show();
    if (_tiler->wasCanceled()) {
	return;
    }
    const char* source = _tiler->getSourceFile();
    const char* target = _tiler->getTargetFile();
    if (!IlvFileExists(source)) {
	IlString tmp("The file ");
	tmp += IlString(source) + IlString(" does not exist.");
	alert(tmp.getValue());
	tileFile();
    }
    IlPathName p1(source);
    IlPathName p2(target);
    if (p1 == p2) {
	alert("Source and destination must be different files");
	tileFile();
    }
    IlInt tileWidth = _tiler->getTileWidth();
    IlInt tileHeight = _tiler->getTileHeight();

    IlvGeoTIFFTiler tiler(source, target, tileWidth, tileHeight);
    if (tiler.getInitStatus() != IlvMaps::NoError()) {
	alert("Bad tiling parameters");
	tileFile();
    }
    IlvCursor* c = getDisplay()->getCursor("wait");
    getView()->setCursor(c);
    getDisplay()->readAndDispatchEvents();
    IlvTIFFStreamer str;
    tiler.performTiling(str);
    c = getDisplay()->getCursor("default");
    getView()->setCursor(c);
}

// --------------------------------------------------------------------------
// Creates the toolbar
// --------------------------------------------------------------------------
IlvToolBar*
View::createToolBar()
{
    IlvMenuItem* sep;
    IlvRect cbb;
    _gadgetContainer->boundingBox(cbb);
    IlvToolBar* toolBar= new IlvToolBar(_display, IlvRect(0, 0, cbb.w(), 0));
    toolBar->setName("ToolBar");

    IlvMenuItem* openItem = new IlvMenuItem();
    openItem->setBitmap(_display->readBitmap(
			    _display->findInPath("data/maps/open.png")));
    openItem->setToolTip("Open");
    openItem->setClientData(this);
    openItem->setCallback(Open);
    toolBar->insertItem(openItem);

    IlvMenuItem* tileItem = new IlvMenuItem();
    tileItem->setBitmap(_display->readBitmap(
			    _display->findInPath("data/maps/tiling.png")));
    tileItem->setToolTip("Tile a TIFF File");
    tileItem->setClientData(this);
    tileItem->setCallback(Tile);
    toolBar->insertItem(tileItem);

    sep = new IlvMenuItem();
    toolBar->insertItem(sep);

    IlvMenuItem* zoomItem = new IlvMenuItem();
    zoomItem->setBitmap(_display->readBitmap(
			    _display->findInPath("data/maps/zoom.png")));
    zoomItem->setToolTip("Zoom");
    zoomItem->setClientData(this);
    zoomItem->setCallback(Zoom);
    toolBar->insertItem(zoomItem);

    IlvMenuItem* unZoomItem = new IlvMenuItem();
    unZoomItem->setBitmap(_display->readBitmap(
			      _display->findInPath("data/maps/unzoom.png")));
    unZoomItem->setToolTip("Unzoom");
    unZoomItem->setClientData(this);
    unZoomItem->setCallback(UnZoom);
    toolBar->insertItem(unZoomItem);

    IlvMenuItem* panItem = new IlvMenuItem();
    panItem->setBitmap(_display->readBitmap(
			   _display->findInPath("data/maps/move.png")));
    panItem->setToolTip("Pan");
    panItem->setClientData(this);
    panItem->setCallback(Pan);
    toolBar->insertItem(panItem);

    IlvMenuItem* debugItem = new IlvMenuItem();
    debugItem->setBitmap(_display->readBitmap(
			     _display->findInPath("data/maps/debug.png")));
    debugItem->setToolTip("Debug");
    debugItem->setToggle(IlTrue);
    debugItem->setClientData(this);
    debugItem->setCallback(Debug);
    toolBar->insertItem(debugItem);

    toolBar->setConstraintMode(IlTrue);
    _gadgetContainer->addObject(toolBar);
    _gadgetContainer->getHolder()->attach(toolBar, IlvHorizontal, 0, 1, 0);
    return toolBar;
}

// --------------------------------------------------------------------------
// Creates the main window
// --------------------------------------------------------------------------
void
View::mainWindow()
{
    IlvDim width = 640;
    IlvDim height = 480;

    IlvRect r(50, 50, width, height);

    _gadgetContainer = new IlvGadgetContainer(_display,
					      "GeoTIFF",
					      "GeoTIFF Demo",
					      r,
					      IlFalse,
					      IlFalse);
    _gadgetContainer->setDestroyCallback(Exit, (IlvAny)this);

    IlvToolBar* tb = createToolBar();
    IlvDim tbh = tb->h();

    r.moveResize(0, tbh, width, height - tbh);
    _managerRectangle = new IlvManagerRectangle(_display, r);
    _gadgetContainer->addObject(_managerRectangle, IlFalse);

    IlvGraphicHolder* gh = _gadgetContainer->getHolder();
    gh->attach(_managerRectangle, IlvHorizontal, 0, 1, 0);
    gh->attach(_managerRectangle, IlvVertical, 0, 1, 0);

    _manager = _managerRectangle->getManager();
    _view = _managerRectangle->getView();
    _manager->setKeepingAspectRatio(_view, IlTrue);
}

// --------------------------------------------------------------------------
// Shows the main window.
// --------------------------------------------------------------------------
void
View::show()
{
    _gadgetContainer->show();
}

// --------------------------------------------------------------------------
// Creates a debug view.
// --------------------------------------------------------------------------
void
View::debugView(IlBoolean show)
{
    if (!_debug) {
	IlvManager* manager = getManager();
	_debug = new IlvView(_display,
			     "DebugView",
			     "DebugView",
			     IlvRect(0, 0, 100, 100),
			     IlFalse, IlFalse);
	manager->addView(_debug);
	manager->setDoubleBuffering(_debug, IlTrue);
	if (_layer) {
	    _layer->setDebugView(_debug);
	}

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
	if (_layer) {
	    _layer->setDebugView(_debug);
	}
	_debug->show();
    }
    else {
	_debug->hide();
    }
}

// --------------------------------------------------------------------------
// Creates the alert box.
// --------------------------------------------------------------------------
void
View::alert(const char* m)
{
    if (!_alert) {
	_alert = new Alert(getTopView());
    }
    _alert->setMessage(m);
    _alert->show();
}
