// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/builder.h
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
// Declaration of the MapBuilder class
// --------------------------------------------------------------------------
#ifndef _MapBuilder_h_
#define _MapBuilder_h_

#include <ilviews/base/list.h>
#include <ilviews/gadgets/dockutil.h>
#include <ilviews/gadgets/appli.h>
#include <ilviews/gadgets/text.h>

#include <dockapp.h>
#include <buffer.h>
#include <defdbmsfact.h>
#include <readctrl.h>
#include <sdoreadctrl.h>

IlDefineListOf(MapBuffer, MapBuffer*);

class MapDesktopManager;

// --------------------------------------------------------------------------
class MapBuilder
    : public DockableApplication
{
public:
#if HAS_SDO_SUPPORT
    SdoReaderController* _requestController;
#endif

    MapBuilder(const char* name,
	       const char* displayName,
	       int argc,
	       char** argv);
    ~MapBuilder();

    // Implementation of IlvApplication
    virtual void makePanels();
    virtual void createPanes();
    virtual void quit();
    virtual void loadFile(const char*);

    // implementation
    MapDesktopManager* getDesktopManager() const { return desktopManager; }
    IlvDockableMainWindow* createMainWindow(const IlvRect& rect) const;
    IlvPane* createMainMenuBarPane(const char* name, IlvPopupMenu** menu);
    IlvPane* createStandardToolBarPane(const char* name);
    IlvPane* createOverviewPane(const char* name);
    IlvPane* createScalePane(const char* name);
    IlvPane* createCoordPane(const char* name);
    IlvPane* createLegendPane(const char* name);
    IlvPane* createStatusPane(const char* name);

    void addInteractor(int interactor);

    // Buffer management
    MapBuffer* makeNewBuffer(IlBoolean visible = IlTrue,
			     IlBoolean destroy = IlTrue);
    MapBuffer* getCurrentBuffer();
    MapBuffer* getBuffer(IlvViewFrame* frame);

    // Destroys the buffer associated with specified view
    // return true if the buffer has been destroyed.
    IlBoolean destroyBuffer(IlvView* view, IlBoolean destroyFrame = IlTrue);
    // Object names
    static char* GetMainMenuBarName() { return (char*)"MainMenuBar"; }
    static char* GetOverviewName()    { return  (char*)"Overview"; }
    static char* GetToolBarName()     { return  (char*)"ToolBar"; }
    static char* GetScaleName()       { return  (char*)"Scale"; }
    static char* GetCoordName()       { return  (char*)"Coordinates"; }
    static char* GetLegendName()      { return  (char*)"Legend"; }
    static char* GetStatusPaneName()  { return  (char*)"Info"; }

    // File browsers
    IlvIFileSelector* getLoadFileBrowser() const
	{ return _loadFileSelector; }
    IlvIFileSelector* getSaveFileBrowser() const
	{ return _saveFileSelector; }

    // Interactor id
    static int PanInteractor() { return 1; }
    static int SelectInteractor() { return 2; }
    static int ZoomIntInteractor() { return 3; }

#if HAS_SDO_SUPPORT
    // DB management
    IldDbms* getDbms() const { return _dbms; };
    void setDbms(IldDbms* dbms);
#endif

    // error reporting
    void reportInfo(const char* message);
    void reportError(const char* message);

    // file browser managements
    const char* requestForInputMapFile();

    // updates the UI components that depends of current buffer
    void updateBufferDependentUI();

private:
    MapDesktopManager* desktopManager;
    IlListOf(MapBuffer) bufferList;
    int _currentInteractor;
    IlBoolean _sdoAvailable;
#if HAS_SDO_SUPPORT
    IldDbms*   _dbms;
    IlvDefaultSDODbmsFactory* _dbmsFactory;
#endif
    IlvText* _statusText;
    IlvIFileSelector* _loadFileSelector;
    IlvIFileSelector* _saveFileSelector;

};

extern MapBuilder* GetBuilder();

#endif /* _MapBuilder_h_ */
