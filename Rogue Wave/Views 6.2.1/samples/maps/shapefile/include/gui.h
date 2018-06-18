// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/shapefile/include/gui.h
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
// Declaration of the shapefile viewer gui.
// --------------------------------------------------------------------------
#ifndef _Gui_h
#define _Gui_h

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/manager/rectangl.h>
#include <ilviews/gadgets/toolbar.h>
#include <ilviews/gadgets/combo.h>
#include <ilviews/manager/paninter.h>
#include <ilviews/manager/zoomint.h>
#include <ilviews/manager/selinter.h>
#include <ilviews/graphics/lablist.h>
#include <ilviews/graphics/rectangl.h>

class Gui;

// --------------------------------------------------------------------------
class PopupInteractor
    : public IlvManagerViewInteractor
{
public:
    PopupInteractor(Gui* viewer);

    virtual IlBoolean handleEvent(IlvEvent&);
    virtual void drawGhost();

private:
    Gui* _viewer;
};

// --------------------------------------------------------------------------
class PopupShapefileInfo
    : public IlvView
{
public:
    PopupShapefileInfo(IlvView*);
    virtual ~PopupShapefileInfo();

    void addLabel(const char* label)
	{ _list->addLabel(label); }
    void fitToContents()
	{ _manager->fitToContents(this); }

    void clear();
    virtual void show();
    void adjust();

    IlvListLabel* _list;
    IlvRectangle* _rect;
    IlvManager* _manager;
};

// --------------------------------------------------------------------------
class Gui
{
public:
    Gui();
    virtual ~Gui();

    IlvManagerRectangle* getManagerRectangle() const
	{ return _managerRectangle; }
    IlvView* getView() const
	{ return _managerRectangle ? _managerRectangle->getView() : 0; }
    IlvManager* getManager() const
	{ return _managerRectangle ? _managerRectangle->getManager() : 0; }

    virtual void showAll();

    IlvDisplay* getDisplay() const
	{ return _container->getDisplay(); }
    IlvGadgetContainer* getContainer() const
	{ return _container; }

    PopupShapefileInfo* getPopupInfo();

    void createGui(IlvDisplay*);
    IlvToolBar* createToolBar(IlvGadgetContainer* container);
    void createManagerRectangle(IlvGadgetContainer* container);
    void createStatusBar(IlvGadgetContainer* container);
    virtual void buttonDown(IlvGraphic*);

    IlvColor* getForeground() const
	{ return _foreground; }
    void wait(IlvBoolean);

    IlvTextField* getStatusBar() const
	{ return _statusBar; }

    IlvPanZoomInteractor* getPanZoomInteractor() const
	{ return _panZoomInteractor; }
    void setPanZoomInteractor(IlvPanZoomInteractor* p)
	{ _panZoomInteractor = p; }

    IlvZoomInteractor* getZoomInteractor() const
	{ return _zoomInteractor; }
    void setZoomInteractor(IlvZoomInteractor* p)
	{ _zoomInteractor = p; }

    PopupInteractor* getPopupInteractor() const
	{ return _popupInteractor; }
    void setPopupInteractor(PopupInteractor* p)
	{ _popupInteractor = p; }

    IlvGadgetContainer* getIndexPanel() const
	{ return _indexPanel; }
    void setFileOk(IlBoolean ok)
	{ _okFile = ok; }
    IlBoolean isFileOk() const
	{ return _okFile; }

    const IlString& getFileName() const
	{ return _fileName; }
    void setFileName(const IlString& fileName)
	{ _fileName = fileName; }

private:
    IlvPanZoomInteractor* _panZoomInteractor;
    IlvZoomInteractor* _zoomInteractor;
    PopupInteractor* _popupInteractor;
    IlvCursor* _waitCursor;
    IlvCursor* _oldCursor;
    PopupShapefileInfo* _popupInfo;

    IlvGadgetContainer* _container;
    IlvManagerRectangle* _managerRectangle;
    IlvTextField* _statusBar;
    IlvColor* _foreground;
    IlvGadgetContainer* _indexPanel;
    IlBoolean _okFile;
    IlString  _fileName;
};

#endif
