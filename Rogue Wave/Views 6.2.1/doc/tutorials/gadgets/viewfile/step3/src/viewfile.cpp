// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/gadgets/viewfile/step3/src/viewfile.cpp
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
// Implements the FileViewerApplication class
// This class uses the FileViewerWindow and FileViewer classes to display
// the file hierarchy of a hard drive.
// --------------------------------------------------------------------------

#include <viewfile.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/gadgets/menu.h>

#define upBm "../../data/up.png"

// --------------------------------------------------------------------------
FileViewerApplication::FileViewerApplication(const char* name,
					     const char* displayName,
					     int argc,
					     char** argv)
: IlvApplication(name, displayName, argc, argv)
{
    // Do not use the default exit panel
    setUsingExitPanel(IlvFalse);
}

// --------------------------------------------------------------------------
FileViewerApplication::~FileViewerApplication()
{
    // Delete the FileViewer
    FileViewerWindow* window = (FileViewerWindow*)
	getMainWindow()->getMainWorkspaceViewPane()->getView();
    FileViewer* viewer = FileViewerApplication::GetFileViewer(window);
    FileViewerApplication::SetFileViewer(window, 0);
    delete viewer;
}

// ------------------------------------------------------------------------
void
FileViewerApplication::makePanels()
{
    // Initialize the main window
    initMainWindow();
    
    // Initialize the panes
    initPanes();
    
    // Initialize the application
    configureApplication();

    // Update the main window layout
    getMainWindow()->updatePanes(IlvTrue);

    // Show it
    getMainWindow()->show();
}

// ------------------------------------------------------------------------
void
FileViewerApplication::initMainWindow() 
{
    // Create the main window
    IlvRect rect(0, 0, 500, 300);
    IlvContainer* mainWindow = createMainWindow(rect);
    // Name it to be able to retrieve it
    mainWindow->setName(getName());
    // Quit the application when user asks for termination
    mainWindow->setDestroyCallback(IlvAppExit, this);
    // Add the panel to the application
    addPanel(mainWindow);
}

// ------------------------------------------------------------------------
IlvDockableMainWindow*
FileViewerApplication::getMainWindow() const
{
    return (IlvDockableMainWindow*)getPanel(getName());
}

// ------------------------------------------------------------------------
IlvContainer* 
FileViewerApplication::createMainWindow(const IlvRect& rect) const
{
    return new IlvDockableMainWindow(getDisplay(),
				     getName(),
				     getName(),
				     rect,
				     0,
				     IlvFalse);
}

// ------------------------------------------------------------------------
void
FileViewerApplication::initPanes()
{
    // Initialize the menu bar
    initMenuBar();

    // Initialize the tool bar
    initToolBar();
}

// ------------------------------------------------------------------------
static void
ExitApplication(IlvGraphic* g, IlvAny arg)
{
    FileViewerApplication* application = (FileViewerApplication*)arg;
    application->quit();
}

// ------------------------------------------------------------------------
static void 
ShowAboutPanel(IlvGraphic* g, IlvAny arg)
{
    FileViewerApplication* application = (FileViewerApplication*)arg;
    application->showVersion();
}

// ------------------------------------------------------------------------
// This class is a subclass of the IlvAbstractBarPane class.
// It's used for the main menu bar to display vertical labels when the bar
// is docked in a vertical direction.
// --------------------------------------------------------------------------
class ApplicationMenuBarPane
: public IlvAbstractBarPane
{
public:
    ApplicationMenuBarPane(const char* name, IlvAbstractBar* bar)
	: IlvAbstractBarPane(name, bar) {}
    
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
	// Retrieve the dockable instance connected with this pane
        IlvDockable* dockable = IlvDockable::GetDockable(this);
	// Change the orientation of the label of the encapsulated
	// bar
        getBar()->setLabelOrientation(dockable && dockable->isDocked()
                                      ? getBar()->getOrientation()
                                      : IlvHorizontal,
                                      IlvFalse,
                                      IlvFalse);
    }
};

// ------------------------------------------------------------------------
void
FileViewerApplication::initMenuBar()
{
    // The menu bar is in fact an IlvToolBar
    IlvToolBar* menubar = new IlvToolBar(getDisplay(), IlvPoint(0, 0));
    // Add two items
    menubar->addLabel("File");
    menubar->addLabel("Help");
    // Change the mode of the menu bar to make it show it items on several
    // rows if needed
    menubar->setConstraintMode(IlvTrue);
    // Create the pane that will encapsulates the menu bar
    IlvGraphicPane* menubarPane = new ApplicationMenuBarPane("Menu Bar",
							     menubar);
    // Add the pane to the application on top of the main workspace
    getMainWindow()->addRelativeDockingPane(menubarPane,
					    IlvDockableMainWindow::
					    GetMainWorkspaceName(),
					    IlvTop);
    // Now fill the menus with popup menus
    IlvPopupMenu* menu;
    // Menu File : New / Separator / Exit
    menu = new IlvPopupMenu(getDisplay());
    menu->addLabel("Exit");
    menu->getItem(0)->setCallback(ExitApplication);
    menu->getItem(0)->setClientData(this);
    menubar->getItem(0)->setMenu(menu, IlvFalse);
    // Menu Help : About
    menu = new IlvPopupMenu(getDisplay());
    menu->addLabel("About");
    menubar->getItem(1)->setMenu(menu, IlvFalse);
    menu->getItem(0)->setCallback(ShowAboutPanel);
    menu->getItem(0)->setClientData(this);
}

// ------------------------------------------------------------------------
static void
UpOneLevel(IlvGraphic* g, IlvAny arg)
{
    // Retrieve a pointer on the application
    FileViewerApplication* application = (FileViewerApplication*)arg;
    // Retrieve a pointer on the main window
    FileViewerWindow* window = (FileViewerWindow*)
	application->getMainWindow()->getMainWorkspaceViewPane()->getView();
    // Retrieve  pointer on the file viewer
    FileViewer* viewer = FileViewerApplication::GetFileViewer(window);
    if (viewer) {
	// Find the last selected item of the tree
	IlvTreeGadgetItem* item =
	    viewer->getTreeGadget()->getLastSelectedItem();
	// And select its parent
	if (item && item->getParent() && item->getParent()->getParent())
	    viewer->getTreeGadget()->selectItem(item->getParent(),
						IlvTrue,
						IlvTrue,
						IlvTrue);
    }
}

// ------------------------------------------------------------------------
void
FileViewerApplication::initToolBar()
{
    IlvToolBar* toolbar = new IlvToolBar(getDisplay(), IlvPoint(0, 0));
    // Item Up One Level
    toolbar->insertBitmap(getBitmap(upBm));
    toolbar->getItem(0)->setCallback(UpOneLevel);
    toolbar->getItem(0)->setClientData(this);
    toolbar->getItem(0)->setToolTip("Up One Level");
    // Encapsulates the tool bar into a graphic pane
    IlvGraphicPane* toolbarPane = new IlvAbstractBarPane("Tool Bar", toolbar);
    // Add the pane to the application on top of the main workspace
    getMainWindow()->addRelativeDockingPane(toolbarPane,
					    IlvDockableMainWindow::
					    GetMainWorkspaceName(),
					    IlvTop);
}

// ------------------------------------------------------------------------
void
FileViewerApplication::SetFileViewer(FileViewerWindow* window,
				     FileViewer* viewer)
{
    window->setProperty(IlvGetSymbol("Viewer"), (IlvAny)viewer);
}

// ------------------------------------------------------------------------
FileViewer*
FileViewerApplication::GetFileViewer(const FileViewerWindow* window)
{
    return (FileViewer*)window->getProperty(IlvGetSymbol("Viewer"));
}

// ------------------------------------------------------------------------
void
FileViewerApplication::configureApplication()
{
    // Create the file viewer window
    FileViewerWindow* window = createFileViewerWindow(getMainWindow(),
						      IlvRect(0, 0, 400, 200));
    // Replace the view of the main workspace pane with the file viewer window
    getMainWindow()->getMainWorkspaceViewPane()->setView(window);
    // Create the file viewer using the file viewer window
    FileViewer* viewer = createFileViewer(window);
    // Link the file viewer with its window
    // This is used in the UpOneLevel callback
    SetFileViewer(window, viewer);
    // Initialize the file viewer
    IlvPathName path("/");
    viewer->init(path);
}

// --------------------------------------------------------------------------
FileViewer*
FileViewerApplication::createFileViewer(FileViewerWindow* window) const
{
    return new FileViewer(window->getDirectoryHierarchy(),
			  window->getFileList());
}

// ------------------------------------------------------------------------
FileViewerWindow*
FileViewerApplication::createFileViewerWindow(IlvView* parent,
					      const IlvRect& rect) const
{
    return new FileViewerWindow(parent, rect);
}

// ------------------------------------------------------------------------
void
FileViewerApplication::showVersion()
{
    IlvIInformationDialog dialog(getDisplay(), "VIEWFILE Tutorial");
    dialog.moveToMouse();
    dialog.showModal();
}

// ------------------------------------------------------
// Entry point
// ------------------------------------------------------
int main(int argc, char* argv[])
{
    IlvSetLocale();
    FileViewerApplication* appli =
	new FileViewerApplication("VIEWFILE Sample", 0, argc, argv);
    if (!appli->getDisplay())
        return -1;
    appli->run();
    return 0;
}
