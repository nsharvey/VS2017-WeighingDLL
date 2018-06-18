// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/projvect/src/gui.cpp
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
// Implementation of vector projector GUI.
// --------------------------------------------------------------------------
#include <gui.h>
#include <centeri.h>

// Some objects used for the GUI
#include <ilviews/gadgets/menubar.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/base/memory.h>
#include <ilviews/bitmaps/streamer.h>

#if defined(IL_STD)
#  include <iostream>
#  include <fstream>
using namespace std;
#else
#  include <iostream.h>
#  include <fstream.h>
#  include <stdio.h>
#  include <stdlib.h>
#endif

// --------------------------------------------------------------------------
// Static and callback functions
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Callback that handles the mouse position
// --------------------------------------------------------------------------
static void
ShowMousePositionCB(IlvView* view, IlvEvent& event, IlvAny arg)
{
    Gui* viewer = (Gui*)arg;
    viewer->showMousePosition(view, event);
}

// --------------------------------------------------------------------------
// Exit callback called from an accelerator.
// Do some cleanup.
// --------------------------------------------------------------------------
static void
ExitCB(IlvView*, IlvAny a)
{
    Gui* viewer = (Gui*)a;
    IlvDisplay* display = viewer->getDisplay();
    delete viewer;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Exit callback, called from the exit button of the tool bar.
// --------------------------------------------------------------------------
static void
ExitCB(IlvGraphic*, IlvAny a)
{
    Gui* viewer = (Gui*)a;
    IlvManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvView* view = mgrRect->getView();
    ExitCB(view, a);
}

// --------------------------------------------------------------------------
// Called when changing interactor.
// --------------------------------------------------------------------------
static void
RemoveInteractorCB(Gui* viewer)
{
    IlvManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvManager* manager = mgrRect->getManager();
    IlvView* view = mgrRect->getView();
    manager->removeInteractor(view);
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
	mvi->detach();
	mvi->attach(manager, view);
    }
}

// --------------------------------------------------------------------------
// Zoom in toolbar callback
// --------------------------------------------------------------------------
static void
ZoomCB(IlvGraphic* , IlvAny a)
{
    Gui* viewer = (Gui*)a;
    ResetInteractor(viewer);
    IlvManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvRect visibleRect;
    mgrRect->getView()->sizeVisible(visibleRect);
    mgrRect->getManager()->zoomView(mgrRect->getView(),
				    IlvPoint(visibleRect.centerx(),
					     visibleRect.centery()),
				    1.5,
				    1.5);
}

// --------------------------------------------------------------------------
// Zoom out toolbar callback
// --------------------------------------------------------------------------
static void
UnZoomCB(IlvGraphic* , IlvAny a)
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
// Fit to contents toolbar callback
// --------------------------------------------------------------------------
static void
ShowAllCB(IlvGraphic*, IlvAny a)
{
    Gui* viewer = (Gui*)a;
    ResetInteractor(viewer);
    viewer->showAll();
}

// --------------------------------------------------------------------------
// Center interactor toolbar callback
// --------------------------------------------------------------------------
static void
CenterCB(IlvGraphic* , IlvAny a)
{
    Gui* viewer = (Gui*)a;
    IlvManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvManager* manager = mgrRect->getManager();
    IlvView* view = mgrRect->getView();

    CenterInteractor* ci = viewer->getCenterInteractor();
    if (!ci) {
	ci = new CenterInteractor(manager, view);
	viewer->setCenterInteractor(ci);
    }
    IlvManagerViewInteractor* mvi = manager->getInteractor(view);
    if (mvi != ci) {
	manager->removeInteractor(view);
	manager->setInteractor(ci, view);
    }
}

// --------------------------------------------------------------------------
// Pan zoom interactor toolbar callback
// --------------------------------------------------------------------------
static void
PanZoomCB(IlvGraphic* , IlvAny a)
{
    Gui* viewer = (Gui*)a;
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
// Zoom interactor toolbar callback
// --------------------------------------------------------------------------
static void
ZoomIntCB(IlvGraphic* , IlvAny a)
{
    Gui* viewer = (Gui*)a;
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
// Keep log/lat toolbar callback
// --------------------------------------------------------------------------
static void
KeepllCB(IlvGraphic* k, IlvAny v)
{
    IlvToolBar* tb = (IlvToolBar*)k;
    IlUInt pos = tb->whichSelected();
    IlvMenuItem* t = tb->getItem((IlUShort)pos);

    Gui* viewer = (Gui*)v;
    viewer->setKeepll(t->isSelected());
}

// --------------------------------------------------------------------------
// Show grid toolbar callback
// --------------------------------------------------------------------------
static void
GridCB(IlvGraphic* k, IlvAny v)
{
    IlvToolBar* tb = (IlvToolBar*)k;
    IlUInt pos = tb->whichSelected();
    IlvMenuItem* t = tb->getItem((IlUShort)pos);

    Gui* viewer = (Gui*)v;
    viewer->showGrid(t->isSelected());
}

// --------------------------------------------------------------------------
// Combo box item selection callback
// --------------------------------------------------------------------------
static void
ComboItemSelectedCB(IlvGraphic* g, IlvAny)
{
    Gui* gui = (Gui*)g->getClientData();
    IlvComboBox* cb = gui->getComboBox();
    gui->comboItemSelected(cb->getSelection());
}

// --------------------------------------------------------------------------
// Gui: User interface
// --------------------------------------------------------------------------
Gui::Gui()
    : _panZoomInteractor(0),
      _centerInteractor(0),
      _zoomInteractor(0),
      _waitCursor(0),
      _oldCursor(0),
      _keepll(0),
      _showGrid(0)
{
}

// --------------------------------------------------------------------------
Gui::~Gui()
{
    IlvView* view = _managerRectangle->getView();
    view->removeInputCallback(ShowMousePositionCB, this);
    IlvManager* manager = _managerRectangle->getManager();
    manager->removeInteractor(view);

    if (_waitCursor) {
	_waitCursor->unLock();
    }
    if (_foreground) {
	_foreground->unLock();
    }
    if (_centerInteractor) {
	delete _centerInteractor;
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
}

// --------------------------------------------------------------------------
// This function creates the Graphic User Interface by code. It would also
// have been possible to use Rogue Wave Views Studio for that.
// --------------------------------------------------------------------------
void
Gui::createGui(IlvDisplay* display)
{
    _container = new IlvGadgetContainer(display,
					"Gui",
					"Projecting Vectors",
					IlvRect(50, 50, 640, 480),
					IlFalse,
					IlFalse);

    _foreground = getDisplay()->getColor("green");
    if (_foreground) {
	_foreground->lock();
    }
    _container->setDestroyCallback(ExitCB, this);
    createToolBar(_container);
    createStatusBar(_container);
    createManagerRectangle(_container);
    _container->applyResize();

    IlvManager* manager = _managerRectangle->getManager();

    // Displaying the mouse position
    IlvView* view = _managerRectangle->getView();
    view->setInputCallback(ShowMousePositionCB, this);

    manager->setDoubleBuffering(view, IlTrue);
    manager->setKeepingAspectRatio(view, IlTrue);
}

// --------------------------------------------------------------------------
// Toolbar creation
// --------------------------------------------------------------------------
IlvToolBar*
Gui::createToolBar(IlvGadgetContainer* container)
{
    IlvDisplay* display = container->getDisplay();

    IlvRect cbb;
    container->boundingBox(cbb);

    IlvToolBar* toolBar= new IlvToolBar(display, IlvRect(0, 0, cbb.w(), 0));
    toolBar->setName("ToolBar");

    IlvMenuItem* sep = new IlvMenuItem();

    IlvMenuItem* zoomItem = new IlvMenuItem();
    zoomItem->setBitmap(display->readBitmap("data/maps/zoom.png"));
    zoomItem->setToolTip("Zoom");
    zoomItem->setClientData(this);
    zoomItem->setCallback(ZoomCB);
    toolBar->insertItem(zoomItem);

    IlvMenuItem* unZoomItem = new IlvMenuItem();
    unZoomItem->setBitmap(display->readBitmap("data/maps/unzoom.png"));
    unZoomItem->setToolTip("Unzoom");
    unZoomItem->setClientData(this);
    unZoomItem->setCallback(UnZoomCB);
    toolBar->insertItem(unZoomItem);

    IlvMenuItem* showAllItem = new IlvMenuItem();
    showAllItem->setBitmap(display->readBitmap("data/maps/fit.png"));
    showAllItem->setToolTip("Show all");
    showAllItem->setClientData(this);
    showAllItem->setCallback(ShowAllCB);
    toolBar->insertItem(showAllItem);

    IlvMenuItem* panZoom = new IlvMenuItem();
    panZoom->setToolTip("Pan Zoom");
    panZoom->setClientData(this);
    panZoom->setCallback(PanZoomCB);
    panZoom->setBitmap(display->readBitmap("data/maps/move.png"));
    toolBar->insertItem(panZoom);

    IlvMenuItem* zoomInt = new IlvMenuItem();
    zoomInt->setToolTip("Zoom an area");
    zoomInt->setClientData(this);
    zoomInt->setCallback(ZoomIntCB);
    zoomInt->setBitmap(display->readBitmap("data/maps/zoomin.png"));
    toolBar->insertItem(zoomInt);

    IlvMenuItem* center = new IlvMenuItem();
    center->setToolTip("Projection center");
    center->setClientData(this);
    center->setCallback(CenterCB);
    center->setBitmap(display->readBitmap("data/maps/pointer.png"));
    toolBar->insertItem(center);

    toolBar->insertItem(sep);

    IlvMenuItem* keepll = new IlvMenuItem();
    keepll->setToolTip("Keep Long and Lat");
    keepll->setToggle(IlTrue);
    keepll->setClientData(this);
    keepll->setCallback(KeepllCB);
    keepll->setBitmap(display->readBitmap("data/maps/punaise.png"));
    toolBar->insertItem(keepll);

    IlvMenuItem* grid = new IlvMenuItem();
    grid->setToolTip("Grid");
    grid->setToggle(IlTrue);
    grid->setClientData(this);
    grid->setCallback(GridCB);
    grid->setBitmap(display->readBitmap("data/maps/grid.png"));
    toolBar->insertItem(grid);

    IlUShort count;
    const char** labels = getLabels(count);
    _comboBox = new IlvComboBox(container->getDisplay(),
				IlvPoint(),
				"Items",
				labels,
				count);
    if (labels) {
	delete [] labels;
    }
    if (_comboBox->getCardinal()) {
	_comboBox->setSelected(0);
    }
    _comboBox->setCallback(ComboItemSelectedCB);
    _comboBox->setClientData(this);
    IlvRect labelRect;
    IlvRect arrowRect;
    IlvRect menuRect;
    _comboBox->itemsBBox(labelRect, arrowRect);
    IlvPopupMenu* sm = _comboBox->getSubMenu();
    sm->boundingBox(menuRect);
    _comboBox->resize(arrowRect.w() + menuRect.w(),
		      _comboBox->h() + 2);

    _comboBox->setEditable(IlFalse);
    toolBar->insertGraphic(_comboBox);

    toolBar->setFlushingRight(IlTrue);
    toolBar->setConstraintMode(IlTrue);

    container->addObject(toolBar);

    container->getHolder()->attach(toolBar, IlvHorizontal, 0, 1, 0);

    return toolBar;
}

// --------------------------------------------------------------------------
// Default implementation
const char**
Gui::getLabels(IlUShort& count)
{
    count = 0;
    return 0;
}

// --------------------------------------------------------------------------
void
Gui::createManagerRectangle(IlvGadgetContainer* container)
{
    IlvDisplay* display = container->getDisplay();
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
    _managerRectangle->setBackground(display->getColor((IlvIntensity)47,
						       (IlvIntensity)79,
						       (IlvIntensity)79));
    container->addObject(_managerRectangle);

    // Attachments
    container->getHolder()->attach(_managerRectangle, IlvHorizontal,
				   0, 1, 0);
    container->getHolder()->attach(_managerRectangle, IlvVertical,
				   0, 1, 0);
}

// --------------------------------------------------------------------------
// Sets or removes the wait cursor
// --------------------------------------------------------------------------
void
Gui::wait(IlBoolean w)
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
// The status created as an IlvTextField
// --------------------------------------------------------------------------
void
Gui::createStatusBar(IlvGadgetContainer* container)
{
    IlvRect cbbx;
    container->boundingBox(cbbx);

    _statusBar = new IlvTextField(container->getDisplay(),
				  "StatusBar",
				  IlvRect());
    _statusBar->fitToLabel();


    IlvRect tbbx;
    _statusBar->boundingBox(tbbx);
    IlvDim height = tbbx.h() + 2;
    _statusBar->moveResize(IlvRect(0, cbbx.h() - height, cbbx.w(), height));
    _statusBar->setEditable(IlFalse);
    _statusBar->setName("StatusBar");
    _statusBar->setLabel("");

    // Attachments
    container->getHolder()->attach(_statusBar, IlvHorizontal);
    container->getHolder()->attach(_statusBar, IlvVertical, 1, 0, 0);

    container->addObject(_statusBar, IlTrue);
}

// --------------------------------------------------------------------------
void
Gui::showMousePosition(IlvView*, IlvEvent&)
{
}

// --------------------------------------------------------------------------
void
Gui::comboItemSelected(const char*)
{
}

// --------------------------------------------------------------------------
void
Gui::centerCallback(IlvManager*, IlvView*)
{
}

// --------------------------------------------------------------------------
void
Gui::showGrid(IlBoolean s)
{
    _showGrid = s;
}

// --------------------------------------------------------------------------
void
Gui::showAll()
{
    IlvManager* manager = _managerRectangle->getManager();
    IlvView* view = _managerRectangle->getView();
    manager->fitTransformerToContents(view, IlTrue, IlTrue);
}
