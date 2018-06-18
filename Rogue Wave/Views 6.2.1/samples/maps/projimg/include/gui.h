// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/projimg/include/gui.h
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
// Declaration of image projector gui.
// --------------------------------------------------------------------------
#ifndef _Gui_h
#define _Gui_h

#include "centeri.h"

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/manager/rectangl.h>
#include <ilviews/gadgets/toolbar.h>
#include <ilviews/gadgets/combo.h>
#include <ilviews/manager/paninter.h>
#include <ilviews/manager/zoomint.h>

// --------------------------------------------------------------------------
class Gui
{
public:
    Gui();
    virtual ~Gui();

    virtual const char** getLabels(IlUShort& count);

    IlvManagerRectangle* getManagerRectangle() const
	{ return _managerRectangle; }
    IlvView* getView() const
	{ return _managerRectangle ? _managerRectangle->getView() : 0; }
    IlvManager* getManager() const
	{ return _managerRectangle ? _managerRectangle->getManager() : 0; }

    virtual void showAll();
    virtual void showMousePosition(IlvView* view, IlvEvent& event);

    virtual void centerCallback(IlvManager* manager, IlvView* view);

    virtual void comboItemSelected(const char* selection);

    IlvDisplay* getDisplay() const
	{ return _container->getDisplay(); }

    void createGui(IlvDisplay*);
    IlvToolBar* createToolBar(IlvGadgetContainer* container);

    void createManagerRectangle(IlvGadgetContainer* container);
    void createStatusBar(IlvGadgetContainer* container);

    IlvColor* getForeground() const
	{ return _foreground; }

    void setKeepll(IlBoolean s)
	{ _keepll = s; }
    IlBoolean getKeepll() const
	{ return _keepll; }

    virtual void showGrid(IlBoolean s);
    IlBoolean isShowingGrid() const
	{ return _showGrid; }

    void wait(IlBoolean);

    IlvComboBox* getComboBox() const
	{ return _comboBox; }

    IlvTextField* getStatusBar() const
	{ return _statusBar; }

    IlvPanZoomInteractor* getPanZoomInteractor() const
	{ return _panZoomInteractor; }
    void setPanZoomInteractor(IlvPanZoomInteractor* p)
	{ _panZoomInteractor = p; }

    CenterInteractor* getCenterInteractor() const
	{ return _centerInteractor; }
    void setCenterInteractor(CenterInteractor* p)
	{ _centerInteractor = p; }

    IlvZoomInteractor* getZoomInteractor() const
	{ return _zoomInteractor; }
    void setZoomInteractor(IlvZoomInteractor* p)
	{ _zoomInteractor = p; }
    void show()
	{ _container->show(); }

private:
    IlvPanZoomInteractor* _panZoomInteractor;
    CenterInteractor* _centerInteractor;
    IlvZoomInteractor* _zoomInteractor;
    IlvCursor* _waitCursor;
    IlvCursor* _oldCursor;
    IlBoolean _keepll;
    IlBoolean _showGrid;

    IlvGadgetContainer* _container;
    IlvManagerRectangle* _managerRectangle;
    IlvTextField* _statusBar;
    IlvComboBox* _comboBox;
    IlvColor *_foreground;
};

#endif
