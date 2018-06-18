// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/multires/include/viewer.h
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
#ifndef _Viewer_H
#define _Viewer_H

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/manager/rectangl.h>
#include <ilviews/manager/paninter.h>
#include <ilviews/manager/zoomint.h>
#include <ilviews/gadgets/toolbar.h>

#include <multiraster.h>
#include <multishape.h>
#include <filesel.h>
#include <alert.h>

// --------------------------------------------------------------------------
class Viewer
{
public:
    Viewer(IlvDisplay* display,
	   IlPathName& raster,
	   IlPathName& shape);
    virtual ~Viewer();

    IlvToolBar* createToolBar();
    void mainWindow();
    void makeLayers();
    void show();
    void openFile();
    static IlBoolean IsDataCDRoot(IlString& root,
				  IlPathName& raster,
				  IlPathName& shape);

    IlvDisplay* getDisplay()
	{ return _display; }
    IlvManager* getManager()
	{ return _manager; }
    IlvView* getView()
	{ return _view; }
    IlvPanZoomInteractor* getPanZoom()
	{ return _panzoom; }
    void setPanZoom(IlvPanZoomInteractor* pzi)
	{ _panzoom = pzi; }
    IlvZoomInteractor* getZoomTnt()
	{ return _zoomint; }
    void setZoomInt(IlvZoomInteractor* pzi)
	{ _zoomint = pzi; }
    void alert(const char* msg);

private:
    IlvDisplay* _display;
    IlvGadgetContainer* _gadgetContainer;
    IlvManagerRectangle* _managerRectangle;
    IlvManager* _manager;
    IlvView* _view;
    FileSelector* _fileSel;
    Alert* _alert;
    IlvPanZoomInteractor* _panzoom;
    IlvZoomInteractor* _zoomint;
    RasterLayerFactory* _rasterFactory;
    ShapeLayerFactory* _shapeFactory;
    IlvMapInfo* _info;
};
#endif
