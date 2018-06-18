// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/dockapp.cpp
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
// The implementation of DockableApplication methods.
// --------------------------------------------------------------------------
#include "dockapp.h"

#if defined(IL_STD)
#  include <fstream>
#  include <iostream>
#  include <cstring>
#  include <cstdlib>
IL_STDUSE
#else  /* !IL_STD */
#  include <fstream.h>
#  include <iostream.h>
#  include <string.h>
#  include <stdlib.h>
#  include <stdio.h>
#endif /* !IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
// This class is a subclass of the IlvPaneListener class. It used by the
// DockableApplication class to be informed of changes on its panes.
// --------------------------------------------------------------------------
class ApplicationPaneListener
: public IlvPaneListener
{
public:
    ApplicationPaneListener(DockableApplication* application)
    : _application(application) {}
    // ______________________________________________________________________
    virtual void paneVisibilityChanged()
    {
	if (_application)
	    _application->paneVisibilityChanged(getPane());
    }
protected:
    DockableApplication* _application;
};

// --------------------------------------------------------------------------
ApplicationOptions::~ApplicationOptions()
{
    delete [] _optionFile;
    delete _mainWindowRect;
    delete _configuration;
}

// --------------------------------------------------------------------------
void
ApplicationOptions::setOptionFile(const char* optionFile)
{
    if (optionFile == _optionFile) {
	return;
    }
    if (_optionFile) {
	delete [] _optionFile;
    }
    _optionFile = IlCopyString(optionFile);
}

// --------------------------------------------------------------------------
void
ApplicationOptions::setMainWindowRect(const IlvRect& rect)
{
    if (!_mainWindowRect) {
	_mainWindowRect = new IlvRect(rect);
    }
    else {
	*_mainWindowRect = rect;
    }
}

// --------------------------------------------------------------------------
void
ApplicationOptions::
setDockingConfiguration(const IlvDockingConfiguration& configuration)
{
    if (_configuration) {
	delete _configuration;
    }
    _configuration = new IlvDockingConfiguration(configuration);
}

// --------------------------------------------------------------------------
void
ApplicationOptions::loadOptions()
{
    const char* filename = getOptionFile();
    if (filename) {
	ifstream file(filename, IlInputStreamMode);
	if (!(!file)) {
	    loadMainWindowInfo(file);
	    loadDockingConfiguration(file);
	    file.close();
	}
    }
}

// --------------------------------------------------------------------------
void
ApplicationOptions::loadMainWindowInfo(istream& i)
{
    IlvRect rect;
    i >> rect;
    if (!i) {
	delete _mainWindowRect;
	_mainWindowRect = 0;
    }
    else {
	setMainWindowRect(rect);
    }
}

#define BEGIN_PANE_CHAR     '{'
#define END_PANE_CHAR       '}'

// --------------------------------------------------------------------------
void
ApplicationOptions::loadDockingConfiguration(istream& i)
{
    // Create the configuration
    IlvDockingConfiguration configuration;

    // Find the begin tag
    while (!i.eof() && i.get() != BEGIN_PANE_CHAR);
    if (i.eof()) {
	return;
    }

    // Read the number of panes
    IlUInt nbPanes;
    i >> nbPanes;

    // Read the panes
    IlUInt loop = nbPanes;
    while (loop--) {
	// Find the begin tag
	while (!i.eof() && (i.get() != BEGIN_PANE_CHAR));
	if (!i || i.eof()) {
	    return;
	}
	char* buffer;
	// Read the pane name
	buffer = IlvReadString(i);
	if (!buffer) {
	    return;
	}
	char* paneName = IlCopyString(buffer, IlFalse);

	// Read the visible state : visible or not
	int vis;
	i >> vis;
	IlBoolean visible = vis == 0 ? IlFalse : IlTrue;

	// Read the pane state : Docked or undocked ?
	int docked;
	i >> docked;

	// Read the docked rect in horizontal
	IlvRect horizontalDockedRect;
	i >> horizontalDockedRect;

	// Read the docked rect in vertical
	IlvRect verticalDockedRect;
	i >> verticalDockedRect;

	// Read the undocked rect
	IlvRect unDockedRect;
	i >> unDockedRect;

	// Read the relative Pane name
	buffer = IlvReadString(i);
	if (!buffer) {
	    return;
	}
	char* relativePaneName = IlCopyString(buffer, IlFalse);

	// Read the relative position
	long relativePosition;
	i >> relativePosition;

	// Find the end tag
	while (!i.eof() && i.get() != END_PANE_CHAR);
	if (!i || i.eof()) {
	    return;
	}

	IlvDockingPaneLocation* location =
	    new IlvDockingPaneLocation(paneName,
				       relativePaneName,
				       (IlvPosition)relativePosition,
				       docked,
				       visible,
				       &horizontalDockedRect,
				       &verticalDockedRect,
				       &unDockedRect);
	configuration.addLocation(location);

	// Delete the temporary buffers
	delete [] paneName;
	delete [] relativePaneName;
    }

    // Find the end tag
    while (!i.eof() && i.get() != END_PANE_CHAR);
    if (i.eof()) {
	return;
    }
    setDockingConfiguration(configuration);
}

// --------------------------------------------------------------------------
void
ApplicationOptions::saveOptions()
{
    const char* filename = getOptionFile();
    if (filename) {
	ofstream file(filename, IlOutputStreamMode);
	if (!(!file)) {
	    if (getMainWindowRect()) {
		writeMainWindowInfo(file);
	    }
	    if (getDockingConfiguration()) {
		writeDockingConfiguration(file);
	    }
	    file.close();
	}
    }
}

// --------------------------------------------------------------------------
void
ApplicationOptions::writeMainWindowInfo(ostream& o)
{
    o << *getMainWindowRect() << endl;
}

// --------------------------------------------------------------------------
void
ApplicationOptions::writeDockingConfiguration(ostream& o)
{
    o << BEGIN_PANE_CHAR << IlvSpc()
      << _configuration->getCardinal() << endl;
    for (IlUInt loop = 0; loop < _configuration->getCardinal(); loop++) {
	const IlvDockingPaneLocation* location =
	    _configuration->getLocation(loop);
	o << BEGIN_PANE_CHAR << endl;
	IlvWriteString(o, (const char*)(location->getPaneName()
					? location->getPaneName()
					: "NoName"));
	o << IlvSpc() << (int)location->isVisible() << IlvSpc();
	o << location->getDockedState() << endl;
	o << location->getPaneGeometry(IlvDockingPaneLocation::
				       DockedHorizontally) << endl
	  << location->getPaneGeometry(IlvDockingPaneLocation::
				       DockedVertically) << endl
	  << location->getPaneGeometry(IlvDockingPaneLocation::
				       UnDocked) << endl;
	IlvWriteString(o, location->getRelativePaneName());
	o << IlvSpc()
	  << (int)location->getRelativePosition() << IlvSpc() << endl
	  << END_PANE_CHAR << endl;
    }
    o << END_PANE_CHAR << endl;
}

// --------------------------------------------------------------------------
DockableApplication::DockableApplication(const char* name,
					 const char* displayName,
					 int argc,
					 char** argv)
: IlvApplication(name, displayName, argc, argv),
  _nbPanes(0),
  _panes(0),
  _options(0),
  _configurationHandler(0)
{
#if !defined(WINDOWS)
    getDisplay()->setCurrentLook(IlvWindows95Look); // Win95 look on X Window
#endif
    setUsingExitPanel(IlFalse);
    // Use the option file 'mapbuilder.opt' by default.
    _options = new ApplicationOptions("mapbuilder.opt");
    // Create the configuration handler
    _configurationHandler = new ApplicationConfigurationHandler(this);
}

// --------------------------------------------------------------------------
DockableApplication::~DockableApplication()
{
    delete [] _panes;
    delete _options;
    delete _configurationHandler;
    removePanel(getMainWindow(), IlTrue);
}

// --------------------------------------------------------------------------
IlvBitmap*
DockableApplication::getBitmap(const char* name) const
{
    IlvBitmap* bitmap = getDisplay()->getBitmap(name);

    if (bitmap) { // The bitmap has already been loaded. Return it
	return bitmap;
    }

    // try to load the bitmap using its full name
    bitmap = getDisplay()->readBitmap(name);
    if (bitmap) { 
	return bitmap;
    }

    // try to load ILVMAPSHOME/bitmap...
    char path[2048];
    const char* home = getDisplay()->getEnvOrResource("ILVMAPSHOME");
    if (home) {
	sprintf(path,"%s/%s",home,name);
	bitmap = getDisplay()->readBitmap(path);
    }
    if (bitmap) { 
	return bitmap;
    }
    
    // try to load ILVHOME/bitmap...
    home = getDisplay()->getEnvOrResource("ILVHOME");
    if (home) {
	sprintf(path,"%s/%s",home,name);
	bitmap = getDisplay()->readBitmap(path);
    }
    return bitmap; 
}

// --------------------------------------------------------------------------
void
DockableApplication::makePanels()
{
    // Load the options
    loadOptions();
    // Create the main window
    initMainWindow();
    // Fill it with panes
    initPanes();
    // Updates and show the main window
    getMainWindow()->updatePanes(IlTrue);
    getMainWindow()->show();
}

// --------------------------------------------------------------------------
void
DockableApplication::updateOptions()
{
    // Main window info
    IlvRect bbox;
    getMainWindow()->globalBBox(bbox);
    _options->setMainWindowRect(bbox);
    // Docking configuration
    IlvDockingConfiguration configuration;
    _configurationHandler->getCurrentDockingConfiguration(configuration);
    _options->setDockingConfiguration(configuration);
}

// --------------------------------------------------------------------------
static void
QuitApplication(IlvView* view, IlvAny arg)
{
    DockableApplication* application = (DockableApplication*)arg;
    application->updateOptions();
    application->saveOptions();
    application->quit();
}

// --------------------------------------------------------------------------
void
DockableApplication::initMainWindow()
{
    IlvRect rect(10, 10, 600, 600);
    if (_options->getMainWindowRect()) {
	rect = *_options->getMainWindowRect();
    }
    IlvDockableMainWindow* mainWindow = createMainWindow(rect);
    mainWindow->setDestroyCallback(QuitApplication, this);
    addPanel(mainWindow);
}

// --------------------------------------------------------------------------
IlvDockableMainWindow*
DockableApplication::createMainWindow(const IlvRect& rect) const
{
    return new IlvDockableMainWindow(getDisplay(),
				     GetMainWindowName(),
				     getName(),
				     rect,
				     0,
				     IlFalse);
}

// --------------------------------------------------------------------------
void
DockableApplication::initPanes()
{
    // First, create the panes
    createPanes();
    // Then set the right configuration
    // If a configuration has been found in the options, use it
    // else use the default configuration
    const IlvDockingConfiguration& configuration =
				_options->getDockingConfiguration()
			      ? *_options->getDockingConfiguration()
			      : getDefaultDockingConfiguration();
    _configurationHandler->setCurrentDockingConfiguration(configuration);
}

// --------------------------------------------------------------------------
void
DockableApplication::addPane(IlvPane* pane,
			     IlvDockingPaneLocation* location)
{
    if (!_panes) {
	_panes = new IlvPane*[100]; // 100 is an arbitrary value
    }
    _panes[_nbPanes++] = pane;
    if (pane) {
	// Attach a listener to the pane
	IlvPaneListener* listener = new ApplicationPaneListener(this);
	pane->addListener(listener);
    }
    // If a location is provided, then it's the default location of
    // the pane. This default location will be used only if no docking pane
    // configuration has been found in the options
    if (location) {
	_defaultDockingConfiguration.addLocation(location);
    }
}

// --------------------------------------------------------------------------
IlvPane*
DockableApplication::getPane(const char* name) const
{
    // First look into _panes
    for (IlUInt i = 0; i < _nbPanes; i++) {
	if (_panes[i] && !strcmp(_panes[i]->getName(), name)) {
	    return _panes[i];
	}
    }
    // If not found try a recursive call on the main window
    return getMainWindow()
	? getMainWindow()->getPane(name, IlTrue)
	: 0;
}

// --------------------------------------------------------------------------
void
DockableApplication::paneVisibilityChanged(IlvPane* /* pane */ )
{
}

// --------------------------------------------------------------------------
void
DockableApplication::createPanes()
{
    // To do in a subclass : Add your panes using the addPane method
}

// --------------------------------------------------------------------------
void
DockableApplication::showPane(const char* name, IlBoolean update)
{
    IlvPane* pane = getPane(name);
    if (pane && !pane->isVisible()) {
	pane->show();
	if (update && pane->getContainer()) {
	    pane->getContainer()->updatePanes();
	}
    }
}

// --------------------------------------------------------------------------
void
DockableApplication::hidePane(const char* name, IlBoolean update)
{
    IlvPane* pane = getPane(name);
    if (pane && pane->isVisible()) {
	pane->hide();
	if (update && pane->getContainer()) {
	    pane->getContainer()->updatePanes();
	}
    }
}

// --------------------------------------------------------------------------
IlUInt
ApplicationConfigurationHandler::getDockingPanesCount() const
{
    return _appli->getDefaultDockingConfiguration().getCardinal();
}

// --------------------------------------------------------------------------
IlvPane*
ApplicationConfigurationHandler::getDockingPane(IlUInt index) const
{
    const IlvDockingPaneLocation* location =
	_appli->getDefaultDockingConfiguration().getLocation(index);
    return _appli->getPane(location->getPaneName());
}

// --------------------------------------------------------------------------
IlvDockableMainWindow*
ApplicationConfigurationHandler::getMainWindow() const
{
    return _appli->getMainWindow();
}
