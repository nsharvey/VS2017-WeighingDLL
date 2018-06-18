// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/shapefile/src/gui.cpp
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
// Implementation of shapeviewer GUI.
// --------------------------------------------------------------------------

#include <gui.h>
#include <shapeviewer.h>

#include <ilog/locale.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/gadgets/menubar.h>
#include <ilviews/graphics/selector.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/base/memory.h>
#include <ilviews/maps/format/shapefile/shptiler.h>
#include <ilviews/gadgets/fbrowser.h>

#if defined(IL_STD)
#  include <iostream>
#  include <fstream>
IL_STDUSE;
#else
# include <iostream.h>
#  include <fstream.h>
#  include <stdio.h>
#  if defined(WINDOWS)
#    include <unistd.h>
#  endif
#  include <stdlib.h>
#endif

// --------------------------------------------------------------------------
// Callbacks
// --------------------------------------------------------------------------
static void
Exit(IlvView*, IlvAny a)
{
    Gui* viewer = (Gui*) a;
    IlvDisplay* display = viewer->getDisplay();
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
IndexFileCB(IlvGraphic* g, IlvAny a)
{
    Gui* gui = (Gui*)a;
    gui->getIndexPanel()->hide();
    gui->setFileOk(IlTrue);
}

// --------------------------------------------------------------------------
static void
CancelFileCB(IlvGraphic* g, IlvAny a)
{
    Gui* gui = (Gui*)a;
    gui->setFileOk(IlFalse);
    gui->getIndexPanel()->hide();
}

// --------------------------------------------------------------------------
static void
SelectorCB(IlvGraphic* g, IlvAny a)
{
    IlvSelector* selector = (IlvSelector*)g;
    IlUShort sel = selector->whichSelected();
    IlvGadgetContainer* indexPanel = (IlvGadgetContainer*)a;
    IlvTextField* tf1 = (IlvTextField*)indexPanel->getObject("tcol");
    IlvTextField* tf2 = (IlvTextField*)indexPanel->getObject("trow");
    IlvTextField* tf3 = (IlvTextField*)indexPanel->getObject("twidth");
    IlvTextField* tf4 = (IlvTextField*)indexPanel->getObject("theight");
    if (sel == 0) {
	tf1->setEditable(IlTrue);
	tf2->setEditable(IlTrue);
	tf3->setEditable(IlFalse);
	tf4->setEditable(IlFalse);
    }
    else {
	tf1->setEditable(IlFalse);
	tf2->setEditable(IlFalse);
	tf3->setEditable(IlTrue);
	tf4->setEditable(IlTrue);
    }
}

// --------------------------------------------------------------------------
static void
Exit(IlvGraphic*, IlvAny a)
{
    Gui* viewer = (Gui*)a;
    IlvManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvView* view = mgrRect->getView();
    Exit(view, a);
}

// --------------------------------------------------------------------------
static void
ResetInteractor(Gui* viewer)
{
    IlvManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvManager* manager = mgrRect->getManager();
    IlvView* view = mgrRect->getView();
    IlvManagerViewInteractor* mvi = manager->getInteractor(view);
    if (mvi) {
	mvi->abort();
	mvi->attach(manager, view);
    }
}

// --------------------------------------------------------------------------
static void
Zoom(IlvGraphic* , IlvAny a)
{
    Gui* viewer = (Gui*) a;
    ResetInteractor(viewer);
    IlvManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvRect visibleRect;
    mgrRect->getView()->sizeVisible(visibleRect);
    mgrRect->getManager()->zoomView(mgrRect->getView(),
				    IlvPoint(visibleRect.centerx(),
					     visibleRect.centery()),
				    1.5, 1.5);
}

// --------------------------------------------------------------------------
static void
Select(IlvGraphic* , IlvAny a)
{
    Gui* viewer = (Gui*)a;
    IlvManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvManager* manager = mgrRect->getManager();
    IlvView* view = mgrRect->getView();
    PopupInteractor* pzi;
    pzi = viewer->getPopupInteractor();
    if (!pzi) {
	Gui* viewer = (Gui*) a;
	pzi = new PopupInteractor(viewer);
	viewer->setPopupInteractor(pzi);
    }
    IlvManagerViewInteractor* mvi = manager->getInteractor(view);
    if (mvi != pzi) {
	manager->removeInteractor(view);
	manager->setInteractor(pzi, view);
    }
}

// --------------------------------------------------------------------------
static void
UnZoom(IlvGraphic* , IlvAny a)
{
    Gui* viewer = (Gui*)a;
    ResetInteractor(viewer);
    IlvManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvRect visibleRect;
    mgrRect->getView()->sizeVisible(visibleRect);
    mgrRect->getManager()->zoomView(mgrRect->getView(),
				    IlvPoint(visibleRect.centerx(),
					     visibleRect.centery()),
				    (float)(1./1.5),
				    (float)(1./1.5));
}

// --------------------------------------------------------------------------
static void
ShowAll(IlvGraphic* , IlvAny a)
{
    Gui* viewer = (Gui*) a;
    ResetInteractor(viewer);
    viewer->showAll();
}

// --------------------------------------------------------------------------
static void
PanZoom(IlvGraphic* , IlvAny a)
{
    Gui* viewer = (Gui*) a;
    IlvManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvManager* manager = mgrRect->getManager();
    IlvView* view = mgrRect->getView();
    IlvPanZoomInteractor* pzi;
    pzi = viewer->getPanZoomInteractor();
    if (!pzi) {
	pzi = new IlvPanZoomInteractor(manager, view);
	viewer->setPanZoomInteractor(pzi);
    }

    IlvManagerViewInteractor* mvi = manager->getInteractor(view);
    if (mvi != pzi) {
	manager->removeInteractor(view);
	manager->setInteractor(pzi, view);
    }
}

// --------------------------------------------------------------------------
static void
ZoomInt(IlvGraphic* , IlvAny a)
{
    Gui* viewer = (Gui*) a;
    IlvManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvManager* manager = mgrRect->getManager();
    IlvView* view = mgrRect->getView();
    IlvZoomInteractor* zi;
    zi = viewer->getZoomInteractor();
    if (!zi) {
	zi = new IlvZoomInteractor(manager, view);
	viewer->setZoomInteractor(zi);
    }
    IlvManagerViewInteractor* mvi = manager->getInteractor(view);
    if (mvi != zi) {
	manager->removeInteractor(view);
	manager->setInteractor(zi, view);
    }
}

// --------------------------------------------------------------------------
static void
LoadCB(IlvGraphic* g, IlvAny a)
{
    ShapeViewer* viewer = (ShapeViewer*)a;
    const char* const filters[1] = { "*.shp" };
    const char* const messages[1] = { "*.shp, Shapefile" };

    IlvFileBrowser fb(viewer->getDisplay(),
		      viewer->getContainer()->getSystemView(),
		      "./", 1, filters, messages);
    viewer->setFileName(fb.get());
    if (viewer->getFileName().getLength() > 4) {
	viewer->loadFile(viewer->getFileName().getValue());
	ResetInteractor(viewer);
	viewer->showAll();
    }
}

// --------------------------------------------------------------------------
static void
LodCB(IlvGraphic* g, IlvAny a)
{
    ShapeViewer* viewer = (ShapeViewer*)a;
    const char* const filters[1] = { "*.shp" };
    const char* const messages[1] = { "*.shp, Shapefile" };

    IlvFileBrowser fb(viewer->getDisplay(),
		      viewer->getContainer()->getSystemView(),
		      "./", 1, filters, messages);
    viewer->setFileName(fb.get());
    if (viewer->getFileName().getLength() > 4) {
	viewer->loadFile(viewer->getFileName().getValue(), IlTrue);
	ResetInteractor(viewer);
	viewer->showAll();
    }
}

// --------------------------------------------------------------------------
static void
IndexCB(IlvGraphic* g, IlvAny a)
{
    ShapeViewer* viewer = (ShapeViewer*)a;
    const char* const filters[1] = { "*.shp" };
    const char* const messages[1] = { "*.shp, Shapefile" };

    IlvFileBrowser fb(viewer->getDisplay(),
		      viewer->getContainer()->getSystemView(),
		      "./", 1, filters, messages);
    viewer->setFileName(fb.get());
    if (viewer->getFileName().getLength() < 4) {
	return;
    }

    IlString shapeFileName = IlString(viewer->getFileName());
    IlString* idxFileName = ShapeViewer::GetIDXFileName(shapeFileName);

    // Dialog for index file parameter
    IlvGadgetContainer* indexPanel = viewer->getIndexPanel();
    indexPanel->moveToView(viewer->getContainer());
    indexPanel->setTitle("Choose index options");
    // set the upper left and lower right corner fields
    IlvMessageLabel* ulx = (IlvMessageLabel*)indexPanel->getObject("ulx");
    IlvMessageLabel* uly = (IlvMessageLabel*)indexPanel->getObject("uly");
    IlvMessageLabel* lrx = (IlvMessageLabel*)indexPanel->getObject("lrx");
    IlvMessageLabel* lry = (IlvMessageLabel*)indexPanel->getObject("lry");
    IlString* shxFileName = ShapeViewer::GetSHXFileName(shapeFileName);
    if (shxFileName) {
	IlvShapeFileIndex* index = new IlvShapeFileIndex(*shxFileName);
	IlvCoordinate ul,lr;
	IlBoolean ulOk = index->getUpperLeftCorner(ul);
	IlBoolean lrOk = index->getLowerRightCorner(lr);
	if (ulOk && lrOk) {
	    IlString ulxString("X = ");
	    IlString ulyString("Y = ");
	    IlString lrxString("X = ");
	    IlString lryString("Y = ");
	    char buf[512];
	    IlDoubleToString(buf, ul.x());
	    ulxString += IlString(buf);
	    IlDoubleToString(buf, ul.y());
	    ulyString += IlString(buf);
	    IlDoubleToString(buf, lr.x());
	    lrxString += IlString(buf);
	    IlDoubleToString(buf, lr.y());
	    lryString += IlString(buf);
	    ulx->setLabel(ulxString.getValue());
	    uly->setLabel(ulyString.getValue());
	    lrx->setLabel(lrxString.getValue());
	    lry->setLabel(lryString.getValue());
	}
	delete shxFileName;
	delete index;
    }
    indexPanel->showModal();
    if (viewer->isFileOk()) {
	IlvSelector* selector = (IlvSelector*)indexPanel->getObject("selector");
	if (selector->whichSelected() == 0) { // tile numbers
	    IlvNumberField* tf1 = (IlvNumberField*)indexPanel->getObject("tcol");
	    IlvNumberField* tf2 = (IlvNumberField*)indexPanel->getObject("trow");
	    IlBoolean error;
	    IlInt row = tf1->getIntValue(error);
	    if (!error) {
		IlInt col = tf2->getIntValue(error);
		if (!error) {
		    IlvMapsError error =
			IlvShapeFileTiler::CreateShapeSpatialIndex(shapeFileName.getValue(),
								   idxFileName->getValue(),
								   row,
								   col);
		    viewer->checkError(error, IlTrue);
		    indexPanel->hide();
		}
	    }
	}
	else { // tile width and height
	    IlvNumberField* tf3 = (IlvNumberField*)indexPanel->getObject("twidth");
	    IlvNumberField* tf4 = (IlvNumberField*)indexPanel->getObject("theight");
	    IlBoolean error;
	    IlDouble width = (IlDouble)tf3->getFloatValue(error);
	    if (!error) {
		IlDouble height = (IlDouble)tf4->getFloatValue(error);
		if (!error) {
		    IlvMapsError error =
			IlvShapeFileTiler::CreateShapeSpatialIndex(shapeFileName.getValue(),
								   idxFileName->getValue(),
								   width,
								   height);
		    viewer->checkError(error, IlTrue);
		    indexPanel->hide();
		}
	    }
	}
    }
    if (idxFileName) {
	delete idxFileName;
    }
}

// --------------------------------------------------------------------------
static void
EraseCB(IlvGraphic* g, IlvAny a)
{
    Gui* viewer = (Gui*)a;
    viewer->getManager()->deleteAll(IlTrue, IlTrue);
}

// --------------------------------------------------------------------------
// PopupInteractor
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
PopupInteractor::PopupInteractor( Gui* viewer)
   : IlvManagerViewInteractor(viewer->getManager(), viewer->getView()),
     _viewer(viewer) {
}

// --------------------------------------------------------------------------
void
PopupInteractor::drawGhost()
{
}

// --------------------------------------------------------------------------
IlBoolean
PopupInteractor::handleEvent(IlvEvent& e)
{
    IlvGraphic* g;
    switch (e.type()) {
    case IlvButtonUp:
	_viewer->getPopupInfo()->hide();
	return IlTrue;
    case IlvButtonDown:
	g = getManager()->lastContains(IlvPoint(e.x(), e.y()), getView());
	if (g) {
	    _viewer->buttonDown(g);
	    return IlTrue;
	}
	break;
    default:
	break;
    }
    return IlFalse;
}

// --------------------------------------------------------------------------
// PopupShapefileInfo
// --------------------------------------------------------------------------
PopupShapefileInfo::PopupShapefileInfo(IlvView* v)
    : IlvView(v->getDisplay(), "", "", IlvRect(),
	      IlvNoBorder, IlvFalse, v->getSystemView())
{
    IlvColor* bg = v->getBackground();
    IlvDisplay* display = v->getDisplay();
    if (bg) {
	IlvFloat v = bg->getValue();
	IlvFloat h = bg->getHue();
	IlvFloat s = bg->getSaturation();
	v *= 2.;
	IlvColor* b = display->getColor(h, s, v);
	setBackground(b);
    }
    _list = new IlvListLabel(display, IlvPoint(), 0, 0, 0);
    _rect = new IlvRectangle(display, IlvRect(0, 0, 10, 10));
    _manager = new IlvManager(display, 1, IlvFalse);
    _manager->addObject(_list);
    _manager->addObject(_rect);
    _manager->addView(this);
}

// --------------------------------------------------------------------------
PopupShapefileInfo::~PopupShapefileInfo()
{
    if (_manager) {
	_manager->removeObject(_list);
	delete _manager;
	_manager = 0;
    }
}

// --------------------------------------------------------------------------
void
PopupShapefileInfo::adjust()
{
    if (_manager) {
	IlvRect r;
	boundingBox(r);
	r.w(r.w() + 4);
	r.h(r.h() + 4);
	resize(r.w(), r.h());
	_manager->setTransformer(this);
	_manager->translateView(this, 2, 2, IlvFalse);
	r.move(-2, -2);
	_rect->moveResize(r);
    }
}

// --------------------------------------------------------------------------
void
PopupShapefileInfo::clear()
{
    _list->setLabels(0, 0);
}

// --------------------------------------------------------------------------
void
PopupShapefileInfo::show()
{
    fitToContents();
    adjust();
    moveToMouse(IlvTopLeft);
    raise();
    IlvView::show();
}

// --------------------------------------------------------------------------
// Gui
// --------------------------------------------------------------------------
Gui::Gui()
    : _panZoomInteractor(0),
      _zoomInteractor(0),
      _popupInteractor(0),
      _waitCursor(0),
      _oldCursor(0),
      _popupInfo(0),
      _indexPanel(0),
      _okFile(IlFalse),
      _fileName()
{
}

// --------------------------------------------------------------------------
Gui::~Gui()
{
    IlvView* view = _managerRectangle->getView();
    IlvManager* manager = _managerRectangle->getManager();
    manager->removeInteractor(view);
    if (_waitCursor) {
	_waitCursor->unLock();
    }
    if (_foreground) {
	_foreground->unLock();
    }
    if (_panZoomInteractor) {
	delete _panZoomInteractor;
    }
    if (_zoomInteractor) {
	delete _zoomInteractor;
    }
    if (_container) {
	delete _container;
    }
    if (_indexPanel) {
	delete _indexPanel;
    }
}

// --------------------------------------------------------------------------
void
Gui::buttonDown(IlvGraphic*)
{
}

// --------------------------------------------------------------------------
PopupShapefileInfo*
Gui::getPopupInfo()
{
    if (!_popupInfo) {
	_popupInfo = new PopupShapefileInfo(getView());
    }
    return _popupInfo;
}

// --------------------------------------------------------------------------
// This function creates the Graphic User Interface
// by code. It would also have been possible
// to use Rogue Wave Views Studio for that.
// --------------------------------------------------------------------------
void
Gui::createGui(IlvDisplay* display)
{
    _container = new IlvGadgetContainer(display,
					"Gui",
					"Shape viewer",
					IlvRect(50, 50, 640, 480),
					IlvFalse,
					IlvFalse);
    _foreground = getDisplay()->getColor("green");
    if (_foreground) {
	_foreground->lock();
    }
    _container->setDestroyCallback(Exit, this);
    createToolBar(_container);
    createStatusBar(_container);
    createManagerRectangle(_container);
    IlvManager* manager = _managerRectangle->getManager();
    IlvView* view = _managerRectangle->getView();
    manager->setDoubleBuffering(view, IlvTrue);
    manager->setKeepingAspectRatio(view, IlvTrue);
    Select(0, this);
    // The index panel allowing to create the Rogue Wave Views Maps .idx file
    _indexPanel = new IlvGadgetContainer(getDisplay(), "-", "-",
					 IlvRect(0, 0, 10, 10), 0,
					 IlFalse, IlFalse,
					 _container->getSystemView());
    _indexPanel->readFile("index.ilv");
    IlvButton* ok = (IlvButton*)_indexPanel->getObject("ok");
    IlvButton* cancel = (IlvButton*)_indexPanel->getObject("cancel");
    ok->setCallback(IndexFileCB, this);
    cancel->setCallback(CancelFileCB, this);
    IlvSelector* selector = (IlvSelector*)_indexPanel->getObject("selector");
    selector->setCallback(SelectorCB, _indexPanel);
}

// --------------------------------------------------------------------------
IlvToolBar*
Gui::createToolBar(IlvGadgetContainer* container)
{
    IlvDisplay* display = container->getDisplay();
    IlvRect cbb;
    container->boundingBox(cbb);

    IlvToolBar* toolBar= new IlvToolBar(display, IlvRect(0, 0, cbb.w(), 0));
    toolBar->setName("ToolBar");

    IlvMenuItem* selectItem = new IlvMenuItem();
    selectItem->setBitmap(display->readBitmap("data/maps/select.png"));
    selectItem->setToolTip("Select");
    selectItem->setClientData(this);
    selectItem->setCallback(Select);
    toolBar->insertItem(selectItem);

    IlvMenuItem* zoomItem = new IlvMenuItem();
    zoomItem->setBitmap(display->readBitmap("data/maps/zoom.png"));
    zoomItem->setToolTip("Zoom");
    zoomItem->setClientData(this);
    zoomItem->setCallback(Zoom);
    toolBar->insertItem(zoomItem);

    IlvMenuItem* unZoomItem = new IlvMenuItem();
    unZoomItem->setBitmap(display->readBitmap("data/maps/unzoom.png"));
    unZoomItem->setToolTip("Unzoom");
    unZoomItem->setClientData(this);
    unZoomItem->setCallback(UnZoom);
    toolBar->insertItem(unZoomItem);

    IlvMenuItem* showAllItem = new IlvMenuItem();
    showAllItem->setBitmap(display->readBitmap("data/maps/fit.png"));
    showAllItem->setToolTip("Show All");
    showAllItem->setClientData(this);
    showAllItem->setCallback(ShowAll);
    toolBar->insertItem(showAllItem);

    IlvMenuItem* panZoom = new IlvMenuItem();
    panZoom->setToolTip("Pan Zoom");
    panZoom->setClientData(this);
    panZoom->setCallback(PanZoom);
    panZoom->setBitmap(display->readBitmap("data/maps/move.png"));
    toolBar->insertItem(panZoom);

    IlvMenuItem* zoomInt = new IlvMenuItem();
    zoomInt->setToolTip("Zoom an area");
    zoomInt->setClientData(this);
    zoomInt->setCallback(ZoomInt);
    zoomInt->setBitmap(display->readBitmap("data/maps/zoomin.png"));
    toolBar->insertItem(zoomInt);

    IlvMenuItem* sep = new IlvMenuItem();
    toolBar->insertItem(sep);

    IlvMenuItem* loadInt = new IlvMenuItem();
    loadInt->setToolTip("Load a shapefile");
    loadInt->setClientData(this);
    loadInt->setCallback(LoadCB);
    loadInt->setBitmap(display->readBitmap("data/maps/open.png"));
    toolBar->insertItem(loadInt);

    IlvMenuItem* lodInt = new IlvMenuItem();
    lodInt->setToolTip("Load On Demand a shapefile");
    lodInt->setClientData(this);
    lodInt->setCallback(LodCB);
    lodInt->setBitmap(display->readBitmap("data/maps/tiling.png"));
    toolBar->insertItem(lodInt);

    IlvMenuItem* indexInt = new IlvMenuItem();
    indexInt->setToolTip("Create the Rogue Wave Views Maps "
			 "index file for shapefile");
    indexInt->setClientData(this);
    indexInt->setCallback(IndexCB);
    indexInt->setBitmap(display->readBitmap("data/maps/generate.png"));
    toolBar->insertItem(indexInt);

    IlvMenuItem* delInt = new IlvMenuItem();
    delInt->setToolTip("Erase all");
    delInt->setClientData(this);
    delInt->setCallback(EraseCB);
    delInt->setBitmap(display->readBitmap("data/maps/del.png"));
    toolBar->insertItem(delInt);

    toolBar->setConstraintMode(IlvTrue);

    container->addObject(toolBar);
    container->getHolder()->attach(toolBar, IlvHorizontal, 0, 1, 0);
    return toolBar;
}

// --------------------------------------------------------------------------
void
Gui::createManagerRectangle(IlvGadgetContainer* container)
{
    IlvGraphic* tb = container->getObject("ToolBar");
    IlvGraphic* sb = container->getObject("StatusBar");
    IlvRect tbbx;
    tb->boundingBox(tbbx);
    IlvRect cbbx;
    container->boundingBox(cbbx);
    IlvRect sbbx;
    sb->boundingBox(sbbx);
    IlvPos y = tbbx.y() + tbbx.h();
    IlvDim h = sbbx.y() - y;
    _managerRectangle = new IlvManagerRectangle(container->getDisplay(),
						IlvRect(0, y, cbbx.w(), h));
    container->addObject(_managerRectangle);
    container->getHolder()->attach(_managerRectangle, IlvHorizontal,
				   0, 1, 0);
    container->getHolder()->attach(_managerRectangle, IlvVertical,
				   0, 1, 0);
}

// --------------------------------------------------------------------------
void
Gui::wait(IlvBoolean w)
{
    IlvView* view = getView();
    if (!view) {
	return;
    }
    IlvDisplay* display = getDisplay();
    if (w) {
	_oldCursor = view->getCursor();
	if (!_waitCursor) {
	    _waitCursor = display->getCursor("wait");
	    if (_waitCursor) {
		_waitCursor->lock();
	    }
	}
	view->setCursor(_waitCursor);
    }
    else {
	view->setCursor(_oldCursor);
    }
    display->sync();
    while (display->hasEvents()) {
	display->waitAndDispatchEvents();
    }
}

// --------------------------------------------------------------------------
void
Gui::createStatusBar(IlvGadgetContainer* container)
{
    IlvRect cbbx;
    container->boundingBox(cbbx);
    _statusBar = new IlvTextField(container->getDisplay(), "StatusBar",
				  IlvRect());
    _statusBar->fitToLabel();
    IlvRect tbbx;
    _statusBar->boundingBox(tbbx);
    IlvDim height = tbbx.h() + 2;
    _statusBar->moveResize(IlvRect(0, cbbx.h() - height, cbbx.w(), height));
    _statusBar->setEditable(IlvFalse);
    _statusBar->setName("StatusBar");
    _statusBar->setLabel("");

    // Attachments
    container->getHolder()->attach(_statusBar, IlvHorizontal);
    container->getHolder()->attach(_statusBar, IlvVertical, 1, 0, 0);
    container->addObject(_statusBar, IlvTrue);
}

// --------------------------------------------------------------------------
void
Gui::showAll()
{
    IlvManager* manager = _managerRectangle->getManager();
    IlvView* view = _managerRectangle->getView();
    manager->fitTransformerToContents(view, IlvTrue, IlvTrue);
}
