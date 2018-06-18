// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/dockapp.h
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
// Declaration of the DockableApplication class
// -------------------------------------------------------------------------
#ifndef _DockApp_h_
#define _DockApp_h_

#include <ilviews/util/util.h>
#include <ilviews/gadgets/dockutil.h>
#include <ilviews/gadgets/appli.h>
#include <ilviews/maps/util.h>

// ------------------------------------------------------------------------
class ApplicationOptions
{
public:
    ApplicationOptions(const char* file)
        : _optionFile(0), _mainWindowRect(0), _configuration(0)
    {
	setOptionFile(file);
    }
    virtual ~ApplicationOptions();
    // ______________________________________________________________________
    const char*              getOptionFile() const { return _optionFile; }
    void                     setOptionFile(const char* optionFile);
    IlvRect*                 getMainWindowRect() const
	{ return _mainWindowRect; }
    void                     setMainWindowRect(const IlvRect& rect);
    IlvDockingConfiguration* getDockingConfiguration() const
	{ return _configuration; }
    void setDockingConfiguration(const IlvDockingConfiguration&);
    void                     loadOptions();
    void                     saveOptions();

protected:
    char*                    _optionFile;
    IlvRect*                 _mainWindowRect;
    IlvDockingConfiguration* _configuration;

    void                     loadMainWindowInfo(istream& i);
    void                     loadDockingConfiguration(istream& i);
    void                     writeMainWindowInfo(ostream& o);
    void                     writeDockingConfiguration(ostream& o);
};

class ApplicationConfigurationHandler;

// ------------------------------------------------------------------------
class DockableApplication
    : public IlvApplication
{
public:
    DockableApplication(const char* name,
			const char* displayName,
			int argc,
			char** argv);
    ~DockableApplication();
    // ______________________________________________________________________
    IlvBitmap*               getBitmap(const char* name) const;
    virtual void             makePanels();
    void                     updateOptions();
    void                     loadOptions() { _options->loadOptions(); }
    void                     saveOptions() { _options->saveOptions(); }
    void                     initMainWindow();
    virtual IlvDockableMainWindow* createMainWindow(const IlvRect&) const;
    void                     initPanes();
    IlUInt                   getPanesCount() const { return _nbPanes; }
    void                     addPane(IlvPane* pane,
				     IlvDockingPaneLocation* location = 0);
    IlvPane*                 getPane(IlUInt index) const
	{ return (IlvPane*)_panes[index]; }
    IlvPane*                 getPane(const char* name) const;
    virtual void             paneVisibilityChanged(IlvPane*);
    virtual void             createPanes();
    void                     showPane(const char* name,
				      IlBoolean update = IlTrue);
    void                     hidePane(const char* name,
				      IlBoolean update = IlTrue);
    IlvDockableMainWindow* getMainWindow() const
	{ return (IlvDockableMainWindow*)getPanel(GetMainWindowName()); }

    // Returns the name of the main window
    static const char* GetMainWindowName()
	{ return "Map Builder"; }

    const IlvDockingConfiguration&
    getDefaultDockingConfiguration() const
	{ return _defaultDockingConfiguration; }

protected:
    IlUInt                          _nbPanes;
    IlvPane**                       _panes;
    ApplicationOptions*             _options;
    IlvDockingConfigurationHandler* _configurationHandler;
    IlvDockingConfiguration         _defaultDockingConfiguration;
};

// ------------------------------------------------------------------------
// This class deals with docking pane configuration
// ------------------------------------------------------------------------
class ApplicationConfigurationHandler
    : public IlvDockingConfigurationHandler
{
public:
    ApplicationConfigurationHandler(DockableApplication* appli)
    : _appli(appli)
    {
    }
    // ______________________________________________________________________
    virtual IlUInt getDockingPanesCount() const;
    virtual IlvPane* getDockingPane(IlUInt index) const;
    virtual IlvDockableMainWindow* getMainWindow() const;
protected:
    DockableApplication* _appli;
};


#endif /* DockApp */
