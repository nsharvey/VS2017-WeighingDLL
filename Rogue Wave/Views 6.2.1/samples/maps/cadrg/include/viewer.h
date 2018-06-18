// -------------------------------------------------------------- -*- C++ -*-
//					  Rogue Wave Views sample source file
// File: samples/maps/cadrg/include/viewer.h
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
// Declaration of cadrg viewer class
//
// This class shows how to load cadrg data with Rogue Wave Views Maps.
// --------------------------------------------------------------------------
#ifndef _Viewer_H
#define _Viewer_H

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/manager/rectangl.h>
#include <ilviews/manager/paninter.h>
#include <ilviews/manager/magview.h>
#include <ilviews/gadgets/toolbar.h>

#include <ilviews/maps/scalefilter.h>

#include <ilviews/maps/format/cadrg/cadrgtoc.h>
#include <ilviews/maps/format/cadrg/cadrgread.h>
#include <ilviews/maps/format/cadrg/cadrglayer.h>

#include <covchoose.h>

class MyHook;

// --------------------------------------------------------------------------
class Viewer
{
public:
    Viewer(IlvDisplay* display, const char* tocname);
    virtual ~Viewer();

    inline IlvDisplay* getDisplay()
	{ return _display; }
    inline IlvCADRGTocReader* getTocReader()
	{ return _tocReader; }
    IlvManagerRectangle* getManagerRectangle()
	{ return _managerRectangle; }

    void loadCoverages(const IlvCADRGCoverage* smallScaleCoverage,
		       const IlvCADRGCoverage* mediumScaleCoverage,
		       const IlvCADRGCoverage* largeScaleCoverage);

    void installVisibilityFilters();
    void mainWindow();
    IlvToolBar* createToolBar();

    void showAll();
    void zoom();
    void unZoom();
    void show();

private:
    IlvDisplay* _display;
    class CovChoose* _chooser;
    IlvCADRGTocReader* _tocReader;
    IlvGadgetContainer* _gadgetContainer;
    IlvManagerRectangle* _managerRectangle;
    IlvManager* _manager;
    IlvView* _view;
    IlvCADRGLayer* _layers[3];
    IlvScaleVisibilityFilter* _filters[3];
    IlvPanZoomInteractor* _panzoom;
    IlvMapInfo* _mapinfo;

    // Data to control and optimize the fit, zoom and unzoom actions
    IlvRect _viewSize;
    IlvTransformer _transToFit;
    IlvTransformer _initialTrans;
    IlvRect _initialBbox;
    IlInt _limitWidth;
};

#endif /* _Viewer_H */
