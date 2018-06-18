// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/maptileloader.cpp
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

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/manager/rectangl.h>
#include <ilviews/manager/paninter.h>
#include <ilviews/manager/zoomint.h>
#include <ilviews/gadgets/toolbar.h>

#include <ilviews/maps/format/maptloader.h>
#include <ilviews/maps/dftrenderer.h>
#include <ilviews/maps/projection/geogproj.h>
#include <ilviews/maps/format/image/imgreader.h>
#include <ilviews/maps/tiling/tiledlayer.h>
#include <ilviews/maps/format/pathmgr.h>

#include <ilog/pathname.h>

// --------------------------------------------------------------------------
// MyTileLoader
// --------------------------------------------------------------------------
class MyTileLoader : public IlvMapTileLoader
{
    IlvDisplay* _display;
    const char* _filename;
    IlvProjection* _projection;
    IlvMapInfo* _info;
    IlvDim _imageWidth;
    IlvDim _imageHeight;
public:
    MyTileLoader(IlvDisplay* display,
		 const char* filename)
	: _display(display),
	  _filename(IlvMapDataPathManager::ResolvePath(filename)),
	  _projection(new IlvGeographicProjection()),
	  _info(0),
	  _imageWidth(0),
	  _imageHeight(0)
    {
	IlvBitmap* bitmap = display->readBitmap(IlvMapDataPathManager::ResolvePath(filename));	
	if (bitmap) {
	    bitmap->lock();
	    _imageWidth = bitmap->width();
	    _imageHeight = bitmap->height();
	    bitmap->unLock();
	}
    }

    ~MyTileLoader()
    {
	if(_info)
	    delete _info;
    }
    
    IlBoolean isPersistent() const {
	return IlFalse;
    }

    IlvMapFeatureIterator* getFeatureIterator(IlvTile* tile)
    {
	IlvRect rect;
	tile->boundingBox(rect);
		 
	IlvMapInfo* info = getMapInfo();

	IlvCoordinate ul;
	IlvCoordinate lr;
	IlvPoint p1(rect.x(), rect.y());
	IlvPoint p2(rect.x() + rect.w(), rect.y() - rect.h());
	ul = info->getAdapter()->fromViews(p1);
	lr = info->getAdapter()->fromViews(p2);
	
	return new IlvImageReader(_display,
				  _filename,
				  ul, lr);
    }
    
    IlvFeatureRenderer* getDefaultFeatureRenderer(IlvDisplay* display)
    {
	return new IlvDefaultFeatureRenderer(display);
    }

    IlvMapInfo* getMapInfo()
    {
	if(_info == 0)
	    _info = new IlvMapInfo(_projection);
	return _info;
    }

    IlvRect getTileOrigin() {
	return IlvRect(0, 0, _imageWidth, _imageHeight);
    }
};

// --------------------------------------------------------------------------
// Viewer
// --------------------------------------------------------------------------
class Viewer;

static void ResetInteractor(Viewer* v);
static void UnZoom(IlvGraphic*, IlvAny a);
static void Pan(IlvGraphic*, IlvAny a);
static void ZoomInt(IlvGraphic*, IlvAny a);
static void Exit(IlvGraphic* g, IlvAny a);
static void Exit(IlvView*, IlvAny a);

class Viewer
{
private:
    IlvDisplay* _display;
    const char* _filename;
    IlvGadgetContainer* _gadgetContainer;
    IlvManagerRectangle* _managerRectangle;
    IlvManager* _manager;
    IlvView* _view;
    IlvPanZoomInteractor* _panzoom;
    IlvZoomInteractor* _zoomint;
    IlvMapInfo* _info;
public:
    Viewer(IlvDisplay* display,
	   const char* filename)
	   :_display(display),
	    _filename(filename),
	    _gadgetContainer(0),
	    _managerRectangle(0),
	    _manager(0),
	    _view(0),	    
	    _panzoom(0),
	    _zoomint(0),
	    _info(0)
    {
	mainWindow();
    }

    virtual ~Viewer()
    {
    }

    IlvManager* getManager() {
	return _manager;
    }

    IlvView* getView() {
	return _view;
    }

    IlvPanZoomInteractor* getPanZoom() {
	return _panzoom;
    }

    void setZoomInt(IlvZoomInteractor* pzi) {
	_zoomint = pzi;
    }
    
    void setPanZoom(IlvPanZoomInteractor* pzi) {
	_panzoom = pzi;
    }
    
    IlvZoomInteractor* getZoomTnt() {
	return _zoomint;
    }

    IlvDisplay* getDisplay() {
	return _display;
    }
    
    IlvToolBar*
    createToolBar()
    {
	IlvRect cbb;
	_gadgetContainer->boundingBox(cbb);

	IlvToolBar* toolBar= new IlvToolBar(_display, IlvRect(0, 0, cbb.w(), 0));
	toolBar->setName("ToolBar");
	toolBar->setFlushingRight(IlTrue);
    
	IlvMenuItem* zoomItem = new IlvMenuItem();
	zoomItem->setBitmap(_display->readBitmap("data/maps/zoom.png"));
	zoomItem->setToolTip("Zoom");
	zoomItem->setClientData(this);
	zoomItem->setCallback(ZoomInt);
	toolBar->insertItem(zoomItem);

	IlvMenuItem* unZoomItem = new IlvMenuItem();
	unZoomItem->setBitmap(_display->readBitmap("data/maps/unzoom.png"));
	unZoomItem->setToolTip("Unzoom");
	unZoomItem->setClientData(this);
	unZoomItem->setCallback(UnZoom);
	toolBar->insertItem(unZoomItem);

	IlvMenuItem* panItem = new IlvMenuItem();
	panItem->setBitmap(_display->readBitmap("data/maps/move.png"));
	panItem->setToolTip("Pan");
	panItem->setClientData(this);
	panItem->setCallback(Pan);
	toolBar->insertItem(panItem);
    
	IlvMenuItem* quitItem = new IlvMenuItem();
	quitItem->setBitmap(_display->readBitmap("data/maps/exit.png"));
	quitItem->setToolTip("Exit");
	quitItem->setClientData(this);
	quitItem->setCallback(Exit);
	toolBar->insertItem(quitItem);
    
	toolBar->setConstraintMode(IlTrue);
    
	_gadgetContainer->addObject(toolBar);
    
	_gadgetContainer->getHolder()->attach(toolBar, IlvHorizontal, 0, 1, 0);

	return toolBar;
    }

    void
    mainWindow()
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

    void
    show()
    {
	MyTileLoader* mtl = new MyTileLoader(_display, _filename);
	IlvTiledLayer* tt = new IlvTiledLayer(mtl->getTileOrigin());
	tt->setTileLoader(mtl);
	_manager->addLayer(tt);
	_gadgetContainer->show();
	//	_manager->fitTransformerToContents(_view);
	IlvTiledLayer::StartAll(_manager);    
	IlvMainLoop();     
    }
};

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
			      IlvPoint(visibleRect.centerx(), visibleRect.centery()),
			      0.5, 0.5);
}

// --------------------------------------------------------------------------
// Pan callback. Installs a pan zoom interactor.
// --------------------------------------------------------------------------
static void
Pan(IlvGraphic*, IlvAny a)
{    
    Viewer* v = (Viewer*) a;
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
static void
ZoomInt(IlvGraphic*, IlvAny a)
{    
    Viewer* v = (Viewer*) a;
    ResetInteractor(v);
    IlvManager* manager = v->getManager();
    IlvView* view = v->getView();
    if(!v->getZoomTnt()) {
	IlvZoomInteractor* pan = new IlvZoomInteractor(manager, view);
	v->setZoomInt(pan);
    }
    manager->setInteractor(v->getZoomTnt(), view);
}

// --------------------------------------------------------------------------
static void
Exit(IlvGraphic* g, IlvAny a)
{
    Viewer* v = (Viewer*)a;
    IlvDisplay* d = v->getDisplay();
    delete d;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
Exit(IlvView*, IlvAny a)
{
    Viewer* v = (Viewer*) a;
    IlvDisplay* d = v->getDisplay();
    delete d;
    IlvExit(0);
}

// --------------------------------------------------------------------------
int 
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay("");
    if(display->isBad()) {
	IlvPrint("Can't open display");
	return -1;
    }
    IlPathName localPath(display->getHomePath());
    display->prependToPath(localPath);
    localPath.addDirectory("samples/maps/userman/data");
    display->prependToPath(localPath);

    if(argc <= 1) {
	IlvPrint("Usage %s filename", argv[0]);
	return -1;
    }
    Viewer v(display, argv[1]);
    v.show();
	return 0;
}
