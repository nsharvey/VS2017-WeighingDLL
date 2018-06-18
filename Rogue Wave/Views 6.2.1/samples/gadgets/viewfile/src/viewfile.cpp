// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/viewfile/src/viewfile.cpp
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

#define upBm "up.png"
#define newBm "new.png"

// --------------------------------------------------------------------------
FileViewerApplication::FileViewerApplication(const char* name,
					     const char* displayName,
					     int argc,
					     char** argv)
    : IlvApplication(name, displayName, argc, argv)
{
    // Do not use the default exit panel
    setUsingExitPanel(IlFalse);
}

// --------------------------------------------------------------------------
FileViewerApplication::~FileViewerApplication()
{
    // Delete all the FileViewers
    for (IlUInt i = 0; i < getDesktopManager()->getCardinal(); i++) {
	FileViewerWindow* window = (FileViewerWindow*)
	    getDesktopManager()->getFrame(i)->getClient();
	// Retrieve  pointer on the file viewer
	FileViewer* viewer = FileViewerApplication::GetFileViewer(window);
	FileViewerApplication::SetFileViewer(window, 0);
	delete viewer;
    }
    // Delete the desktop manager
    delete getDesktopManager();
}

// ------------------------------------------------------------------------
void
FileViewerApplication::makePanels()
{
    // Initialize the main window
    initMainWindow();
    
    // Initialize the desktop manager
    initDesktopManager();

    // Initialize the panes
    initPanes();
    
    // Initialize the application
    configureApplication();

    // Update the main window layout
    getMainWindow()->updatePanes(IlTrue);

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
				     IlFalse);
}

// ------------------------------------------------------------------------
void
FileViewerApplication::initDesktopManager()
{
    createDesktopManager(getMainWindow()->
			 getMainWorkspaceViewPane()->getView());
}
    
// ------------------------------------------------------------------------
IlvDesktopManager*
FileViewerApplication::createDesktopManager(IlvView* view) const
{
    return new IlvDesktopManager(view);
}

// ------------------------------------------------------------------------
IlvDesktopManager*
FileViewerApplication::getDesktopManager() const
{
    return IlvDesktopManager::Get(getMainWindow()->
				  getMainWorkspaceViewPane()->getView());
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
AddNewFrame(IlvGraphic* g,
	    IlAny arg)
{
    FileViewerApplication* application = (FileViewerApplication*)arg;
    IlvViewFrame* vframe =
	application->createNewFrame(IlvRect(0, 0, 400, 200), "/");
    application->getDesktopManager()->setCurrentFrame(vframe);
}

// ------------------------------------------------------------------------
static void
ExitApplication(IlvGraphic* g,
		IlAny arg)
{
    FileViewerApplication* application = (FileViewerApplication*)arg;
    application->quit();
}

// ------------------------------------------------------------------------
static void
CascadeFrames(IlvGraphic* g,
	      IlAny arg)
{
    FileViewerApplication* application = (FileViewerApplication*)arg;
    application->getDesktopManager()->cascadeFrames();
}

// ------------------------------------------------------------------------
static void 
TileHorizontallyFrames(IlvGraphic* g,
		       IlAny arg)
{
    FileViewerApplication* application = (FileViewerApplication*)arg;
    application->getDesktopManager()->tileFrames(IlvHorizontal);
}

// ------------------------------------------------------------------------
static void 
TileVerticallyFrames(IlvGraphic* g,
		     IlAny arg)
{
    FileViewerApplication* application = (FileViewerApplication*)arg;
    application->getDesktopManager()->tileFrames(IlvVertical);
}

// ------------------------------------------------------------------------
static void 
ShowAboutPanel(IlvGraphic* g,
	       IlAny arg)
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
    ApplicationMenuBarPane(const char* name,
			   IlvAbstractBar* bar)
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
                                      IlFalse,
                                      IlFalse);
    }
};

// ------------------------------------------------------------------------
void
FileViewerApplication::initMenuBar()
{
    // The menu bar is in fact an IlvToolBar
    IlvToolBar* menubar = new IlvToolBar(getDisplay(), IlvPoint(0, 0));
    // Add three items
    menubar->addLabel("File");
    menubar->addLabel("Windows");
    menubar->addLabel("Help");
    // Change the mode of the menu bar to make it show it items on several
    // rows if needed
    menubar->setConstraintMode(IlTrue);
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
    menu->addLabel("New (Ctrl+N)");
    menu->getItem(0)->setBitmap(getBitmap(newBm));
    menu->getItem(0)->setCallback(AddNewFrame);
    menu->getItem(0)->setClientData(this);
    menu->getItem(0)->setAcceleratorText("Ctrl+N");
    menu->getItem(0)->setAcceleratorKey(IlvCtrlChar('N'));
    menu->addItem(IlvMenuItem());
    menu->addLabel("Exit");
    menu->getItem(2)->setCallback(ExitApplication);
    menu->getItem(2)->setClientData(this);
    menubar->getItem(0)->setMenu(menu, IlFalse);
    // Menu Windows : Cascase / Tile Horizontally / Tile Vertically
    menu = new IlvPopupMenu(getDisplay());
    menu->addLabel("Cascade");
    menu->getItem(0)->setCallback(CascadeFrames);
    menu->getItem(0)->setClientData(this);
    menu->addLabel("Tile Horizontally");
    menu->getItem(1)->setCallback(TileHorizontallyFrames);
    menu->getItem(1)->setClientData(this);
    menu->addLabel("Tile Vertically");
    menu->getItem(2)->setCallback(TileVerticallyFrames);
    menu->getItem(2)->setClientData(this);
    menubar->getItem(1)->setMenu(menu, IlFalse);
    // Menu Help : About
    menu = new IlvPopupMenu(getDisplay());
    menu->addLabel("About");
    menubar->getItem(2)->setMenu(menu, IlFalse);
    menu->getItem(0)->setCallback(ShowAboutPanel);
    menu->getItem(0)->setClientData(this);
}

// ------------------------------------------------------------------------
static void
UpOneLevel(IlvGraphic* g,
	   IlAny arg)
{
    // Retrieve a pointer on the application
    FileViewerApplication* application = (FileViewerApplication*)arg;
    // Retrieve a pointer on the main window
    FileViewerWindow* window = (FileViewerWindow*)
	application->getDesktopManager()->getCurrentFrame()->getClient();
    // Retrieve  pointer on the file viewer
    FileViewer* viewer = FileViewerApplication::GetFileViewer(window);
    if (viewer) {
	// Find the last selected item of the tree
	IlvTreeGadgetItem* item =
	    viewer->getTreeGadget()->getLastSelectedItem();
	// And select its parent
	if (item && item->getParent() && item->getParent()->getParent())
	    viewer->getTreeGadget()->selectItem(item->getParent(),
						IlTrue,
						IlTrue,
						IlTrue);
    }
}

// ------------------------------------------------------------------------
void
FileViewerApplication::initToolBar()
{
    IlvToolBar* toolbar = new IlvToolBar(getDisplay(), IlvPoint(0, 0));
    // Item New
    toolbar->insertBitmap(getBitmap(newBm));
    toolbar->getItem(0)->setCallback(AddNewFrame);
    toolbar->getItem(0)->setClientData(this);
    toolbar->getItem(0)->setToolTip("New");
    // Separator
    toolbar->addItem(IlvMenuItem());
    // Item Up One Level
    toolbar->insertBitmap(getBitmap(upBm));
    toolbar->getItem(2)->setCallback(UpOneLevel);
    toolbar->getItem(2)->setClientData(this);
    toolbar->getItem(2)->setToolTip("Up One Level");
    // Encapsulates the tool bar into a graphic pane
    IlvGraphicPane* toolbarPane = new IlvAbstractBarPane("Tool Bar", toolbar);
    // Add the pane to the application on top of the main workspace
    getMainWindow()->addRelativeDockingPane(toolbarPane,
					    IlvDockableMainWindow::
					    GetMainWorkspaceName(),
					    IlvTop);
}

// ------------------------------------------------------------------------
static void
DestroyFrame(IlvView* view,
	     IlAny)
{
    delete view;
}

// ------------------------------------------------------------------------
IlvViewFrame*
FileViewerApplication::createNewFrame(const IlvRect& rect,
				      const char* path) const
{
    // Create a view frame in the desktop manager view
    IlvViewFrame* vframe = new IlvViewFrame(getDesktopManager()->getView(),
					    path,
					    rect,
					    IlFalse);
    vframe->setDestroyCallback(DestroyFrame);
    // Create a file viewer window inside the view frame
    FileViewerWindow* viewerWindow = createFileViewerWindow(vframe, rect);
    // Create the file viewer in the file viewer window
    FileViewer* viewer = createFileViewer(viewerWindow);
    // Associates the viewer window with the viewer
    SetFileViewer(viewerWindow, viewer);
    // Intialize the file viewer
    IlvPathName pathname("/");
    viewer->init(pathname);
    return vframe;
}

// ------------------------------------------------------------------------
void
FileViewerApplication::SetFileViewer(FileViewerWindow* window,
				     FileViewer* viewer)
{
    window->setProperty(IlvGetSymbol("Viewer"), (IlAny)viewer);
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
    // The desktop manager is maximized by default
    getDesktopManager()->
	makeMaximizedStateButtons((IlvToolBar*)
				  ((IlvGraphicPane*)getMainWindow()->
				   getPane("Menu Bar", IlTrue))->getObject());
    getDesktopManager()->maximize(0);
    
    // Create a frame initialized at "/"
    getDesktopManager()->setCurrentFrame(createNewFrame(IlvRect(0,
								0,
								400,
								200), "/"));
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
int main(int argc,
	 char* argv[])
{
    IlvSetLocale();
    FileViewerApplication* appli =
	new FileViewerApplication("VIEWFILE Sample", 0, argc, argv);
    if (!appli->getDisplay())
        return -1;
    // Add the directory path to access the sample data
    const char* home = appli->getDisplay()->getEnvOrResource("ILVHOME", 0);
    if (home && *home) {
        IlString strHome = home;
        strHome+= "/";
        IlPathName dataPath = strHome;
        dataPath.addDirectory("samples/gadgets/viewfile/data/");
        appli->getDisplay()->prependToPath((const char*)dataPath);
    }
    appli->run();
    return 0;
}
