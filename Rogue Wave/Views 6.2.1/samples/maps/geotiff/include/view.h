// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/geotiff/include/view.h
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
#ifndef _View_H
#define _View_H

#include <ilviews/manager/paninter.h>
#include <ilviews/manager/magview.h>

#include <ilviews/ilv.h>
#include <ilviews/manager/manager.h>
#include <ilviews/manager/rectangl.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/toolbar.h>
#include <ilviews/gadgets/button.h>

#include <ilviews/maps/tiling/tiledlayer.h>

#include "filesel.h"
#include "tiler.h"
#include "alert.h"

// --------------------------------------------------------------------------
class View
{
public:
    View(IlvDisplay* display, const char* file);
    virtual ~View();
    
    IlvToolBar* createToolBar();
    void mainWindow();
    void show();
    void openFile(const char* file);
    void tileFile();
    void debugView(IlBoolean);
    void alert(const char* message);
    
    IlvDisplay* getDisplay()
	{ return _display; }
    IlvView* getTopView()
	{ return _gadgetContainer; }
    IlvManager* getManager()
	{ return _manager; }
    IlvView* getView()
	{ return _view; }
    IlvPanZoomInteractor* getPanZoom()
	{ return _panzoom; }
    void setPanZoom(IlvPanZoomInteractor* pzi)
	{ _panzoom = pzi; }

private:
    IlvDisplay* _display;
    IlvGadgetContainer* _gadgetContainer;
    IlvManagerRectangle* _managerRectangle;
    IlvManager* _manager;
    IlvView* _view;
    FileSelector* _fileSel;
    Tiler* _tiler;
    IlvTiledLayer* _layer;    
    IlvPanZoomInteractor* _panzoom;
    IlvView* _debug;
    IlvManagerMagViewInteractor* _magvint;
    Alert* _alert;
};

#endif