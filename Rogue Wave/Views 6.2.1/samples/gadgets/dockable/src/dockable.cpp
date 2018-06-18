// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/dockable/src/dockable.cpp
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
// Sample showing how to use the dockable features of Rogue Wave Views
//
// It uses the classes defined in the dockapp.h and dockapp.cpp files
//
// It defines several classes:
//
// MyMainWindow          : This user class is a subclass of
//                         IlvDockableMainWindow that filters docking
//                         operations. Its purpose is to forbid docking
//                         operations below the status bar of the main window
//
// MyApplication         : This user class is a subclass of the
//                         DockableApplication class. It overrides the
//                         createPanes() virtual method of DockableApplication
//                         to instantiates several panes. It also manages a
//                         control view that deal with panes visibility.
//
// MyMainMenuBarPane     : This class is a subclass of the IlvAbstractBarPane
//                         class. It displays vertical labels when the menu
//                         bar is docked in a vertical direction.
// --------------------------------------------------------------------------

#include <ilviews/gadgets/toolbar.h>
#include <ilviews/gadgets/tree.h>
#include <ilviews/gadgets/text.h>
#include <ilviews/gadgets/menu.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/graphics/io.h>
#include <ilog/pathname.h>

#include <dockapp.h>

#define PANESFILE "panes.ilv"

// ------------------------------------------------------------------------
// This class is a subclass of IlvDockableMainWindow that filters docking
// operations.
// ------------------------------------------------------------------------
class MyApplication;
class MyMainWindow
    : public IlvDockableMainWindow
{
public:
    MyMainWindow(const MyApplication*   application,
		 const char*            name,
		 const char*            title,
		 const IlvRect&         dims,
		 IlUInt                 prop = 0,
		 IlBoolean              vis = IlTrue,
		 IlvSystemView          trFor = 0);
    // ______________________________________________________________________
    virtual IlBoolean acceptDocking(const IlvPane*,
				     IlUInt) const;

protected:
    const MyApplication* _application;
};

// ------------------------------------------------------------------------
// This class is a subclass of the IlvAbstractBarPane class.
// It's used for the main menu bar to display vertical labels when the bar
// is docked in a vertical direction.
// --------------------------------------------------------------------------
class MyMainMenuBarPane
    : public IlvAbstractBarPane
{
public:
    MyMainMenuBarPane(const char* name,
		      IlvAbstractBar* bar)
        : IlvAbstractBarPane(name, bar)
    {}
    virtual void setContainer(IlvPanedContainer* container)
    {
	IlvAbstractBarPane::setContainer(container);
	if (container)
	    checkLabelOrientation();
    }
    virtual void orientationChanged()
    {
	checkLabelOrientation();
	IlvAbstractBarPane::orientationChanged();
    }
    void checkLabelOrientation()
    {
	IlvDockable* dockable = IlvDockable::GetDockable(this);
	getBar()->setLabelOrientation(dockable && dockable->isDocked()
				      ? getBar()->getOrientation()
				      : IlvHorizontal,
				      IlFalse,
				      IlFalse);
    }
};

// ------------------------------------------------------------------------
// This class is a subclass of DockableApplication that creates a few panes
// in the main window: A main menu bar, a tool bar, a project tree, ...
// ------------------------------------------------------------------------
class MyApplication
    : public DockableApplication
{
public:
    MyApplication(const char* name,
		  const char* displayName,
		  int argc,
		  char** argv)
	: DockableApplication(name, displayName, argc, argv)
    {
	IlPathName localPath(getDisplay()->getHomePath());
	localPath.addDirectory("samples/gadgets/dockable/data");
	getDisplay()->prependToPath(localPath);
    }
    // ______________________________________________________________________

    // This method creates the main window
    virtual IlvDockableMainWindow* createMainWindow(const IlvRect& rect) const
    {
	return new MyMainWindow(this,
				GetMainWindowName(),
				getName(),
				rect,
				0,
				IlFalse);
    }

    // This method adds a small control window to handle the panes visibility
    virtual void makePanels()
    {
	DockableApplication::makePanels();
	IlvGadgetContainer* controlView = createControlView();
	addPanel(controlView);
	updateControlView();
	controlView->show();
    }

    // This method creates the panes
    // Each docking pane is given a default IlvDockingPaneLocation object that
    // represents its default location in the application.
    virtual void createPanes()
    {
	IlvDockingPaneLocation* location;
	IlvPane* pane;
	IlvRect rect;

	// Main Menu Bar
	pane = createMainMenuBarPane(GetMainMenuBarName());
	location =
	    new IlvDockingPaneLocation(pane->getName(),
				       IlvDockableMainWindow:: // Relative to
				       GetMainWorkspaceName(), // the main work
				                               // space pane
				       IlvTop);                // on top of it
	addPane(pane, location);

	// Standard Tool Bar
	pane = createStandardToolBarPane(GetStandardToolBarName());
	location =
	    new IlvDockingPaneLocation(pane->getName(),
				       GetMainMenuBarName(), // Relative to
				                             // the menu bar
				       IlvBottom);           // below it
	addPane(pane, location);

	// Project Pane
	pane = createProjectPane(GetProjectName());
	rect.resize(150, 150);
	location =
	    new IlvDockingPaneLocation(pane->getName(),
				       IlvDockableMainWindow:: // Relative to
				       GetMainWorkspaceName(), // the main work
				                               // space pane
				       IlvLeft,                // on the left
				       IlvDockingPaneLocation::// docked
				       DockedVertically,       // vertically
				       IlTrue,                 // visible
				       0,                      // no size for
				                               // horizontal
				                               // docking
				       &rect);                 // size for
	                                                       // vertical
	                                                       // docking
	addPane(pane, location);

	// Output Pane
	pane = createOutputPane(GetOutputName());
	rect.resize(300, 100);
	location =
	    new IlvDockingPaneLocation(pane->getName(),
				       IlvDockableMainWindow:: // Relative to
				       GetMainWorkspaceName(), // the main work
				                               // space pane
				       IlvBottom,              // below it
				       IlvDockingPaneLocation::// docked
				       DockedHorizontally,     // horizontally
				       IlTrue,                 // visible
				       &rect);                 // size for
	                                                       // horizontal
	                                                       // docking
	addPane(pane, location);

	// Debug Pane
	pane = createDebugPane(GetDebugName());
	rect.resize(300, 100);
	location =
	    new IlvDockingPaneLocation(pane->getName(),
				       GetOutputName(),        // Relative to
				                               // the output
				                               // pane
				       IlvRight,               // on the right
				       IlvDockingPaneLocation::// docked
				       DockedHorizontally,     // horizontally
				       IlTrue,                 // visible
				       &rect);                 // size for
	                                                       // horizontal
	                                                       // docking
	addPane(pane, location);

	// Now fixed panes are created directly in the main window

	// Add a separator
	pane = createSeparatorPane(GetStatusBarSeparatorName(), IlvHorizontal);
	addPane(pane);
	getMainWindow()->addPane(pane);

	// Then add a status pane below the separator
	pane = createStatusBarPane(GetStatusBarName());
	addPane(pane);
	getMainWindow()->addPane(pane);

	// The view of the main workspace area can be changed here.
	// We could have transform it into an MDI area.
	// In the sample, we just change the color of the view to white
	getMainWindow()->getMainWorkspaceViewPane()->getView()->
	    setBackground(getDisplay()->getColor("white"));
    }

    // Creates and returns the main menu bar pane
    IlvPane* createMainMenuBarPane(const char* name) const
    {
	IlvGraphic* graphic =
	    IlvViewInputFile::ReadObject(getDisplay(), PANESFILE, name);
	if (!graphic || !graphic->isSubtypeOf(IlvAbstractBar::ClassInfo())) {
	    IlvFatalError("Unable to load %s object");
	    return 0;
	}
	return new MyMainMenuBarPane(name, (IlvAbstractBar*)graphic);
    }

    // Creates and returns the standard toolbar pane
    IlvPane* createStandardToolBarPane(const char* name) const
    {
	IlvGraphic* graphic =
	    IlvViewInputFile::ReadObject(getDisplay(), PANESFILE, name);
	if (!graphic || !graphic->isSubtypeOf(IlvAbstractBar::ClassInfo())) {
	    IlvFatalError("Unable to load %s object");
	    return 0;
	}
	return new IlvAbstractBarPane(name, (IlvAbstractBar*)graphic);
    }

    // Creates and returns the debug pane(graphic pane containing an IlvText)
    IlvPane* createDebugPane(const char* name) const
    {
	IlvGraphic* graphic =
	    IlvViewInputFile::ReadObject(getDisplay(), PANESFILE, name);
	if (!graphic) {
	    IlvFatalError("Unable to load %s object");
	    return 0;
	}
	IlvPane* pane = new IlvGraphicPane(name, graphic);
	pane->setResizeMode(IlvPane::Resizable);
	pane->setMinimumSize(IlvHorizontal, 200);
	return pane;
    }

    // Creates and returns the output pane(graphic pane containing an IlvText)
    IlvPane* createOutputPane(const char* name) const
    {
	IlvGraphic* graphic =
	    IlvViewInputFile::ReadObject(getDisplay(), PANESFILE, name);
	if (!graphic) {
	    IlvFatalError("Unable to load %s object");
	    return 0;
	}
	IlvPane* pane = new IlvGraphicPane(name, graphic);
	pane->setResizeMode(IlvPane::Resizable);
	pane->setMinimumSize(IlvVertical, 90);
	// Force horizontal docking by setting our own dockable instance on
	// the pane
	IlvDockable* dockable = new IlvDockable(pane);
	dockable->setDockingDirection(IlvHorizontal);
	return pane;
    }

    // Creates and returns the project pane (graphic pane containing
    // an IlvTreeGadget)
    IlvPane* createProjectPane(const char* name) const
    {
	IlvGraphic* graphic =
	    IlvViewInputFile::ReadObject(getDisplay(), PANESFILE, name);
	if (!graphic) {
	    IlvFatalError("Unable to load %s object");
	    return 0;
	}
	IlvPane* pane = new IlvGraphicPane(name, graphic);
	pane->setResizeMode(IlvPane::Resizable);
	return pane;
    }

    // Creates and returns a pane containing a separator pane
    virtual IlvPane* createSeparatorPane(const char* name,
					 IlvDirection dir) const
    {
	return new IlvSeparatorPane(name, getDisplay(), dir);
    }

    // Creates and returns the pane containing the status bar
    virtual IlvPane* createStatusBarPane(const char* name) const
    {
	IlvGraphic* graphic =
	    IlvViewInputFile::ReadObject(getDisplay(), PANESFILE, name);
	if (!graphic) {
	    IlvFatalError("Unable to load %s object");
	    return 0;
	}
	return new IlvGraphicPane(name, graphic);
    }

    // This method creates a small window to handle the pane visibility
    // A toggle button will be created for each pane to change its visibility
    IlvGadgetContainer* createControlView() const
    {
	IlvGadgetContainer* controlView =
	    new IlvGadgetContainer(getDisplay(),
				   "ControlView",
				   "Pane Visibility",
				   IlvRect(400, 200, 10, 10),
				   0,
				   IlFalse,
				   IlFalse,
				   getMainWindow()->getSystemView());
	controlView->setProperty(IlvGetSymbol("Application"), (IlAny)this);

	// Add the toggles to handle the pane visibility
	IlvPos y = 2;
	IlvDim h = getDisplay()->defaultFont()->height() + 2;
	for (IlUInt i = 0; i < getPanesCount(); i++, y += h) {
	    const char* name = getPane(i)->getName();
	    IlvToggle* toggle = new IlvToggle(getDisplay(),
					      IlvPoint(5, y),
					      name);
	    toggle->setCallback(ChangePaneVisibility, (IlAny)name);
	    controlView->addObject(toggle, IlFalse);
	}

	controlView->fitToContents();
	controlView->resize(controlView->width() + 5,
			    controlView->height() + 5);
	controlView->addAccelerator(RestoreConfig, IlvKeyDown, 'R', 0,
				    (IlAny)this);
	controlView->addAccelerator(SaveConfig, IlvKeyDown, 'S', 0,
				    (IlAny)this);
	return controlView;
    }

    void saveConfig() {
	_configurationHandler->
	    getCurrentDockingConfiguration(_savedConfiguration);
    }

    static void SaveConfig(IlvContainer* cont,
			   IlvEvent& event,
			   IlAny arg)
    {
	MyApplication* appli = (MyApplication*)arg;
	appli->saveConfig();
    }

    void restoreConfig() {
	if (_savedConfiguration.getCardinal())
	    _configurationHandler->
		setCurrentDockingConfiguration(_savedConfiguration,
					       IlTrue);
    }

    static void RestoreConfig(IlvContainer* cont,
			      IlvEvent& event,
			      IlAny arg)
    {
	MyApplication* appli = (MyApplication*)arg;
	appli->restoreConfig();
    }

    // This method updates the control view
    void updateControlView()
    {
	// Must update the control view
	IlvContainer* controlView = getPanel("ControlView");
	if (controlView) {
	    IlvToggle* toggle;
	    for (IlUInt i = 0; i < controlView->getCardinal(); i++) {
		toggle = (IlvToggle*)controlView->getObject(i);
		IlvPane* pane = getPane(toggle->getLabel());
		if (pane)
		    paneVisibilityChanged(pane);
	    }
	}
    }

    // This method is called when the visibility of the pane 'pane' has changed
    virtual void paneVisibilityChanged(IlvPane* pane)
    {
	// Must update the control view
	IlvContainer* controlView = getPanel("ControlView");
	if (controlView) {
	    IlvToggle* toggle;
	    for (IlUInt i = 0; i < controlView->getCardinal(); i++) {
		toggle = (IlvToggle*)controlView->getObject(i);
		if (!strcmp(toggle->getLabel(), pane->getName())) {
		    toggle->setState(pane->isVisible());
		    toggle->reDraw();
		}
	    }
	}
    }

    // Callback called when the visibility of a pane changes
    static void ChangePaneVisibility(IlvGraphic* g,
				     IlAny arg)
    {
	const char* name = (const char*)arg;
	IlvToggle* toggle = (IlvToggle*)g;
	IlvContainer* container = IlvContainer::GetContainer(toggle);
	DockableApplication* appli = (DockableApplication*)
	    container->getProperty(IlvGetSymbol("Application"));
	if (!appli || !name)
	    return;
	if (toggle->getState())
	    appli->showPane(name);
	else
	    appli->hidePane(name);
    }

    // Returns the name of the main menu bar pane
    static const char* GetMainMenuBarName() {
	return "MainMenuBar";
    }

    // Returns the name of the main menu bar pane
    static const char* GetStandardToolBarName() {
	return "StandardToolBar";
    }

    // Returns the name of the project pane
    static const char* GetProjectName() {
	return "Project";
    }

    // Returns the name of the project pane
    static const char* GetOutputName() {
	return "Output";
    }

    // Returns the name of the debug pane
    static const char* GetDebugName() {
	return "Debug";
    }

    // Returns the name of the status pane
    static const char* GetStatusBarSeparatorName() {
	return "StatusBarSeparator";
    }

    // Returns the name of the status pane
    static const char* GetStatusBarName() {
	return "StatusBar";
    }

protected:
    IlvDockingConfiguration _savedConfiguration;
};

// ------------------------------------------------------------------------
MyMainWindow::MyMainWindow(const MyApplication*   application,
			   const char*      name,
			   const char*      title,
			   const IlvRect&   dims,
			   IlUInt           prop,
			   IlBoolean        vis,
			   IlvSystemView    trFor)
    : IlvDockableMainWindow(application->getDisplay(),
			    name,
			    title,
			    dims,
			    prop,
			    vis,
			    trFor),
      _application(application)
{
}

// ------------------------------------------------------------------------
// Forbid docking operations below the separator of the status bar
// ------------------------------------------------------------------------
IlBoolean
MyMainWindow::acceptDocking(const IlvPane* pane,
			    IlUInt index) const
{
    IlvPane* separatorPane =
	_application->getPane(MyApplication::GetStatusBarSeparatorName());
    if (!separatorPane ||
	separatorPane->getContainer() != (IlvPanedContainer*)this)
	return IlvDockableMainWindow::acceptDocking(pane, index);
    IlvUInt sepIndex = getIndex(separatorPane);
    return (index > sepIndex)
	? IlFalse
	: IlvDockableMainWindow::acceptDocking(pane, index);
}

// ------------------------------------------------------
// Entry point
// ------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvSetLocale();
    MyApplication* appli = new MyApplication("Dockable Sample", 0, argc, argv);
    if (!appli->getDisplay())
        return -1;
    appli->run();
    return 0;
}
