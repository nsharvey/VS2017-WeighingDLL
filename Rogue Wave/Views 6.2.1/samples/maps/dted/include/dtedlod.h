// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/dted/include/dtedlod.h
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
// Declaration of DTED Load On Demand reader.
// --------------------------------------------------------------------------
#ifndef __Dtedlod_H
#define __Dtedlod_H

#include <ilviews/manager/paninter.h>
#include <ilviews/manager/magview.h>

#include <ilviews/manager/manager.h>
#include <ilviews/manager/rectangl.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/toolbar.h>
#include <ilviews/gadgets/button.h>

#include <ilviews/maps/format/dted/dtedreader.h>
#include <ilviews/maps/format/dted/dtedlayer.h>

// --------------------------------------------------------------------------
class DtedLod
{
public:
    DtedLod(IlvDisplay* display, const char* dirname);
    ~DtedLod();

    void mainWindow();
    IlvToolBar* createToolBar();
    void dtedLayer();
    void dtedFile();
    void debugView(IlBoolean);
    void interactors();
    void show()
	{ _gadgetContainer->show(); }
    IlvManagerRectangle* getManagerRectangle()
	{ return _managerRectangle; }
    IlvDisplay* getDisplay()
	{ return _display; }
    IlvView* getView()
	{  return _view; }
    IlvManager* getManager()
	{ return _manager; }

    IlvDisplay* _display;
    char* _dirName;
    IlvDTEDLayer* _dtedLayer;
    IlvView* _debug;
    IlvPanZoomInteractor* _panzoom;
    IlvManagerMagViewInteractor* _magvint;

    IlvGadgetContainer* _gadgetContainer;
    IlvManagerRectangle* _managerRectangle;
    IlvManager* _manager;
    IlvView* _view;
    IlBoolean _isDir;
};
#endif
