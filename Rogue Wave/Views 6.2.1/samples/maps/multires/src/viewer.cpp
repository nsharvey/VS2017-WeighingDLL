// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/multires/src/viewer.cpp
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
#include <ilviews/maps/projection/geogproj.h>

#include <viewer.h>

// --------------------------------------------------------------------------
// Static and callback functions
// --------------------------------------------------------------------------
static void
Exit(IlvGraphic* g, IlvAny a)
{
    Viewer* v = (Viewer*)a;
    delete v->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
Exit(IlvView*, IlvAny a)
{
    Viewer* v = (Viewer*)a;
    delete v->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Open a file callback.
// --------------------------------------------------------------------------
static void
Open(IlvGraphic*, IlvAny a)
{
    Viewer* v = (Viewer*)a;
    v->openFile();
}

// --------------------------------------------------------------------------
// Detach an interactor from the manager.
// --------------------------------------------------------------------------
static void
ResetInteractor(Viewer* v)
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
static void
Fit(IlvGraphic* g, IlvAny a)
{
   Viewer* v = (Viewer*)a;
   ResetInteractor(v);
   v->getManager()->fitTransformerToContents(v->getView());
}

// --------------------------------------------------------------------------
// Zoom callback, zoom by a factor of 2
// --------------------------------------------------------------------------
static void
Zoom(IlvGraphic*, IlvAny a)
{
    Viewer* v = (Viewer*)a;
    ResetInteractor(v);
    IlvRect visibleRect;
    v->getView()->sizeVisible(visibleRect);
    v->getManager()->zoomView(v->getView(),
			      IlvPoint(visibleRect.centerx(),
				       visibleRect.centery()),
			      2., 2.);
}

// --------------------------------------------------------------------------
// Unzzom callback, unzoom by a factor of 0.5
// --------------------------------------------------------------------------
static void
UnZoom(IlvGraphic*, IlvAny a)
{
    Viewer* v = (Viewer*) a;
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
    Viewer* v = (Viewer*)a;
    ResetInteractor(v);
    IlvManager* manager = v->getManager();
    IlvView* view = v->getView();
    if (!v->getPanZoom()) {
	IlvPanZoomInteractor* pan = new IlvPanZoomInteractor(manager, view);
	pan->setOpaqueMove(IlFalse);
	pan->setDrawingBitmap(IlFalse);
	v->setPanZoom(pan);
    }
    manager->setInteractor(v->getPanZoom(), view);
}

// --------------------------------------------------------------------------
static void
ZoomInt(IlvGraphic*, IlvAny a)
{
    Viewer* v = (Viewer*)a;
    ResetInteractor(v);
    IlvManager* manager = v->getManager();
    IlvView* view = v->getView();
    if (!v->getZoomTnt()) {
	IlvZoomInteractor* pan = new IlvZoomInteractor(manager, view);
	v->setZoomInt(pan);
    }
    manager->setInteractor(v->getZoomTnt(), view);
}

// --------------------------------------------------------------------------
// Viewer
// --------------------------------------------------------------------------
Viewer::Viewer(IlvDisplay* display,IlPathName& raster,IlPathName& shape)
    : _display(display),
      _gadgetContainer(0),
      _managerRectangle(0),
      _manager(0),
      _view(0),
      _fileSel(0),
      _alert(0),
      _panzoom(0),
      _zoomint(0),
      _rasterFactory(new RasterLayerFactory(raster)),
     _shapeFactory(new ShapeLayerFactory(shape)),
     _info(0)
{
    mainWindow();
    makeLayers();
}

// --------------------------------------------------------------------------
Viewer::~Viewer()
{
    if (_rasterFactory) {
	delete _rasterFactory;
    }
    if (_shapeFactory) {
	delete _shapeFactory;
    }
    if (_fileSel) {
	delete _fileSel;
    }
    if (_alert) {
	delete _alert;
    }
}

// --------------------------------------------------------------------------
IlvToolBar*
Viewer::createToolBar()
{
    IlvMenuItem* sep;
    IlvRect cbb;
    _gadgetContainer->boundingBox(cbb);

    IlvToolBar* toolBar= new IlvToolBar(_display, IlvRect(0, 0, cbb.w(), 0));
    toolBar->setName("ToolBar");

    IlvMenuItem* openItem = new IlvMenuItem();
    openItem->setBitmap(_display->readBitmap("data/maps/open.png"));
    openItem->setToolTip("Open");
    openItem->setClientData(this);
    openItem->setCallback(Open);
    toolBar->insertItem(openItem);

    sep = new IlvMenuItem();
    toolBar->insertItem(sep);


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

    IlvMenuItem* fitItem = new IlvMenuItem();
    fitItem->setBitmap(_display->readBitmap("data/maps/fit.png"));
    fitItem->setToolTip("Fit");
    fitItem->setClientData(this);
    fitItem->setCallback(Fit);
    toolBar->insertItem(fitItem);

    IlvMenuItem* panItem = new IlvMenuItem();
    panItem->setBitmap(_display->readBitmap("data/maps/move.png"));
    panItem->setToolTip("Pan");
    panItem->setClientData(this);
    panItem->setCallback(Pan);
    toolBar->insertItem(panItem);

    IlvMenuItem* zoomIntItem = new IlvMenuItem();
    zoomIntItem->setBitmap(_display->readBitmap("data/maps/zoomin.png"));
    zoomIntItem->setToolTip("Zoom interactor");
    zoomIntItem->setClientData(this);
    zoomIntItem->setCallback(ZoomInt);
    toolBar->insertItem(zoomIntItem);

    toolBar->setConstraintMode(IlTrue);

    _gadgetContainer->addObject(toolBar);

    _gadgetContainer->getHolder()->attach(toolBar, IlvHorizontal, 0, 1, 0);

    return toolBar;
}

// --------------------------------------------------------------------------
void
Viewer::mainWindow()
{
    IlvDim width = 800;
    IlvDim height = 400;

    IlvRect r(50, 50, width, height);

    _gadgetContainer = new IlvGadgetContainer(_display,
					      "MultiResolution",
					      "MultiResolution Demo",
					      r,
					      IlFalse,
					      IlFalse);
    _gadgetContainer->setDestroyCallback(Exit, (IlvAny)this);

    IlvToolBar* tb = createToolBar();
    IlvDim tbh = tb->h();
    _gadgetContainer->resize(width, height + tbh);
    r.moveResize(0, tbh, width, height);
    _managerRectangle = new IlvManagerRectangle(_display, r);
    _gadgetContainer->addObject(_managerRectangle, IlFalse);

    IlvGraphicHolder* gh = _gadgetContainer->getHolder();
    gh->attach(_managerRectangle, IlvHorizontal, 0, 1, 0);
    gh->attach(_managerRectangle, IlvVertical, 0, 1, 0);

    _manager = _managerRectangle->getManager();
    _view = _managerRectangle->getView();
    _manager->setKeepingAspectRatio(_view, IlTrue);
    IlvColor* bg = _display->getColor((IlvIntensity)0,
				     (IlvIntensity)(255 << 8),
				     (IlvIntensity)(255 << 8));
    _view->setBackground(bg);
}

// --------------------------------------------------------------------------
void
Viewer::makeLayers()
{
    IlvGeographicProjection p;
    const IlvMapAdapter adapter(&p);
    _info = new IlvMapInfo(&p, &adapter, IlTrue);
    _info->attach(_manager);
    IlInt i;
    if (_rasterFactory) {
	IlvImageLayer* l = 0;
	for (i = 0; i < _rasterFactory->getNumLayers(); i++) {
	    l = _rasterFactory->makeLayer(_display, &adapter, i);
	    _manager->addLayer(l);
	}
    }
    if (_shapeFactory) {
	IlvShapeFileLayer* l = 0;
	for (i = 0; i < _shapeFactory->getNumLayers(); i++) {
	    l = _shapeFactory->makeLayer(_display, &adapter, i);
	    _manager->addLayer(l);
	}
    }
}

// --------------------------------------------------------------------------
void
Viewer::show()
{
    _gadgetContainer->show();
    _manager->fitTransformerToContents(_view);
    IlvTiledLayer::StartAll(_manager);
    IlvMainLoop();
}

// --------------------------------------------------------------------------
IlBoolean
Viewer::IsDataCDRoot(IlString& root,IlPathName& raster,IlPathName& shape)
{
    IlPathName p(root);
    p.forceDirectory();

    IlPathName data(p);
    data += IlString("data");
    data.forceDirectory();
    if (!data.doesExist()) {
	return IlFalse;
    }

    IlPathName multires(data);
    multires.forceDirectory();
    multires += IlString("multires");
    if (!multires.doesExist()) {
	return IlFalse;
    }

    multires.forceDirectory();

    IlPathName r(multires);
    r += IlString("raster");
    if (!r.doesExist()) {
	return IlFalse;
    }

    IlPathName s(multires);
    s += IlString("poline");
    if (!s.doesExist()) {
	return IlFalse;
    }

    raster = r;
    shape = s;
    return IlTrue;
}

// --------------------------------------------------------------------------
void
Viewer::openFile()
{
    if (!_fileSel) {
	_fileSel = new FileSelector(_gadgetContainer);
    }
    _fileSel->show();
    const char* filename = _fileSel->getString();
    if (!filename) {
	return;
    }
    IlString root(filename);
    IlPathName raster;
    IlPathName shape;
    IlBoolean isRoot = IsDataCDRoot(root, raster, shape);
    if (isRoot) {
	raster.forceDirectory();
	shape.forceDirectory();
	if (!RasterLayerFactory::IsMultiRasterDirectory(raster, 9)) {
	    IlString s(raster.getString().getValue());
	    s += " is not a multiraster directory";
	    alert(s.getValue());
	    return;
	}
	if (!ShapeLayerFactory::IsMultiShapeDirectory(shape)) {
	    IlString s(shape.getString().getValue());
	    s += " is not a multishape directory";
	    alert(s.getValue());
	    return;
	}
	delete _rasterFactory;
	delete _shapeFactory;
	_rasterFactory = new RasterLayerFactory(raster);
	_shapeFactory = new ShapeLayerFactory(shape);
    }
    else {
	raster = IlPathName(filename);
	raster.forceDirectory();
	if (!RasterLayerFactory::IsMultiRasterDirectory(raster, 9)) {
	    shape = IlPathName(filename);
	    shape.forceDirectory();
	    IlBoolean isShape =
	        ShapeLayerFactory::IsMultiShapeDirectory(shape);
	    if (isShape) {
		delete _rasterFactory;
		delete _shapeFactory;
		_shapeFactory = new ShapeLayerFactory(shape);
		_rasterFactory = 0;
	    }
	    else {
		IlString s(shape.getString().getValue());
		s += " is not a multires directory";
		alert(s.getValue());
		return;
	    }
	} else {
	    delete _rasterFactory;
	    delete _shapeFactory;
	    _rasterFactory = new RasterLayerFactory(raster);
	    _shapeFactory = 0;
	}
    }
    IlInt num = _manager->getNumLayers();
    for (IlInt i = 0; i < num - 2; i++) {
	_manager->removeLayer();
    }
    makeLayers();
    _manager->fitTransformerToContents(_view);
    IlvTiledLayer::StartAll(_manager);
    _manager->reDraw();
}

// --------------------------------------------------------------------------
void
Viewer::alert(const char* msg)
{
    if (!_alert) {
	_alert = new Alert(_gadgetContainer);
    }
    _alert->setMessage(msg);
    _alert->show();
}
