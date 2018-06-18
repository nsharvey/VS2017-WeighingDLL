// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/dxf/include/dxfviewer.h
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
// Declaration of the dxf Viewer
//
// This class shows how to read and display DXF files
// with Rogue Wave Views.
// --------------------------------------------------------------------------

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadmgr/rectscmg.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/maps/mapinfo.h>

#ifdef USE_ADVGDT
#include <ilviews/gadgets/fbrowser.h>
#endif

class DXFViewerFileDialog;
class DXFViewer
{

    public:
    DXFViewer(IlvDisplay* display,
		IlvMapInfo* mapInfo = 0,
		IlvProjection* sourceProjection = 0,
		const char* fileName = 0);
    ~DXFViewer();

    // prompts a file chooser and loads the selected file
    void load();

    void save(IlBoolean saveMapInfo);

    void loadFile(const char*);

    IlvSCManagerRectangle* getManagerRectangle() const
                                     {return _managerRectangle;}


    // callbacks
    void showAll();
    void showMousePosition(IlvView* view,
			   IlvEvent& event);

    IlvDisplay* getDisplay() const {return _container->getDisplay();}
    
    private:
    void createGUI(IlvDisplay*);
    void createMenuBar(IlvGadgetContainer* container);
    void createToolBar(IlvGadgetContainer* container);
    void createManagerRectangle(IlvGadgetContainer* container);
    void createStatusBar(IlvGadgetContainer* container);

    private:
    IlvGadgetContainer* _container;
    IlvSCManagerRectangle* _managerRectangle;

#ifdef USE_ADVGDT
    IlvFileBrowser* _fileSelector;
#else
    DXFViewerFileDialog* _fileSelector;
#endif

    IlvTextField* _statusBar;

    IlvMapInfo* _mapInfo;
    IlvProjection* _sourceProjection;
};
