// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/mdilv/src/mdilv.cpp
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
// Small ilv viewer using the classes IlvToolBar, IlvViewFrame,
// and IlvDesktopManager
// --------------------------------------------------------------------------

#include <ilviews/gadgets/vframe.h>
#include <ilviews/gadgets/desktop.h>
#include <ilviews/gadgets/fbrowser.h>
#include <ilviews/gadgets/rectscgc.h>
#include <ilviews/gadgets/gadgets.h>
#include <ilviews/gadgets/appli.h>
#include <ilviews/graphics/all.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/gadgets/scview.h>
#include <ilviews/bitmaps/png.h>
#include <ilog/pathname.h>

#if defined(IL_STD)
#include <fstream>
#include <cstdio>
IL_STDUSE
#else
#include <fstream.h>
#include <stdio.h>
#endif

// --------------------------------------------------------------------------
// This subclass of IlvViewFrame creates an IlvGadgetContainer as client view
// of the frame.
// --------------------------------------------------------------------------
class ContainerViewFrame : public IlvViewFrame
{
public:
    ContainerViewFrame(IlvView* parent,
		       const char* title,
		       const IlvRect& size,
		       IlBoolean visible = IlTrue)
        : IlvViewFrame(parent, title, size, visible),
	  _container(0)
    {
	// Create the client view of the frame
	IlvScrolledView* client = new IlvScrolledView(this, size);
	// Create the container that will be scrolled
	_container = new IlvGadgetContainer(client->getClipView(),
					    IlvRect(0, 0, size.w(), size.h()),
					    IlFalse);
	// Minimum size
	setMinHeight(100);
	// Register the view to allow focus and keyboard event
	registerClientView(_container);
	registerClientView(client->getClipView());
	// Set a destroy callback to handle destruction
	setDestroyCallback(DestroyFrame);
    }
    ~ContainerViewFrame()
    {
	if (getClient() && ((IlvScrolledView*)getClient())->getClipView())
	    unRegisterClientView(((IlvScrolledView*)getClient())->
				 getClipView());
	unRegisterClientView(_container);
    }
    // ______________________________________________________________________
    void loadFile(const char* filename)
    {
	// Read the file
	getContainer()->readFile(filename);
	// Resize the container to fit its contents
	getContainer()->fitToContents();
	getContainer()->reDraw();
    }
    IlvContainer* getContainer() const
    {
	return _container;
    }
    void destroy()
    {
	IlvIQuestionDialog dlg(getDisplay(), "Are you sure ?");
	dlg.moveToMouse();
	if (dlg.get())
	    delete this;
    }
    static void DestroyFrame(IlvView* view,
			     IlAny)
    {
	((ContainerViewFrame*)view)->destroy();
    }
protected:
    IlvContainer* _container;
};

// --------------------------------------------------------------------------
// This subclass of IlvDesktopManager handles the creation of
// ContainerViewFrame instances.
// --------------------------------------------------------------------------
class FileViewerDesktop
    : public IlvDesktopManager
{
public:
    FileViewerDesktop(IlvView* view)
        : IlvDesktopManager(view), _newFrameLocation(0, 0)
    {
    }
    // ______________________________________________________________________
    void frameSelectionChanged(IlvViewFrame* newFrame,
			       IlvViewFrame* oldFrame)
    {
	// Just call the super class method
	IlvDesktopManager::frameSelectionChanged(newFrame, oldFrame);
	// You can add additional code here if you want to do something special
	// each time the current frame changes.
    }
    ContainerViewFrame* getCurrentContainerFrame() const
    {
	return (ContainerViewFrame*)getCurrentFrame();
    }
    ContainerViewFrame* buildNewFrame(const char* title,
				      const IlvRect& rect)
    {
	// Build a new name for this frame
	char tmpTitle[255];
	if (!title) {
	    sprintf(tmpTitle, "Frame %lu", (unsigned long int) getCardinal());
	    title = tmpTitle;
	}
	// Create the frame
	ContainerViewFrame* frame =
	    new ContainerViewFrame(getView(),
				   title,
				   IlvRect(_newFrameLocation.x(),
					   _newFrameLocation.y(),
					   rect.w(),
					   rect.h()),
				   IlFalse);
	_newFrameLocation.translate(IlvPoint(20, 20));
	return frame;
    }
protected:
    IlvPoint _newFrameLocation;
};

// --------------------------------------------------------------------------
// This subclass of IlvGadgetContainer is the main panel of the application.
// It contains a menu bar, a tool bar, a desktop manager, and a status bar.
// --------------------------------------------------------------------------
class FileViewerMainWindow
    : public IlvGadgetContainer
{
public:
    FileViewerMainWindow(IlvDisplay*    d,
			 const char*    name,
			 const char*    title,
			 const IlvRect& dims,
			 IlBoolean      visible = IlTrue)
        : IlvGadgetContainer(d, name, title, dims, IlFalse, visible)
    {
	// Read the description file
	readFile("mdilv.ilv");
	fitToContents();

	// Register the callbacks
	registerCallback("NewCB", NewCB);
	registerCallback("OpenCB", OpenCB);
	registerCallback("QuitCB", QuitCB);
	registerCallback("HighlightCB", HighlightCB);
	registerCallback("CascadeCB", CascadeCB);
	registerCallback("TileVerticalCB", TileVerticalCB);
	registerCallback("TileHorizontalCB", TileHorizontalCB);
	registerCallback("CloseCB", CloseCB);
	registerCallback("NextCB", NextCB);
	registerCallback("PreviousCB", PreviousCB);
	registerCallback("CloseAllCB", CloseAllCB);
	registerCallback("UpdateWindowsCB", UpdateWindowsCB);
	registerCallback("BufferingCB", BufferingCB);

	// Highligh callbacks
	getMenuBar()->addHighlightCallback(IlvGetSymbol("HighlightCB"));
	getToolBar()->addHighlightCallback(IlvGetSymbol("HighlightCB"));

	// Open menu callback
	IlvMenuItem* item =
	    (IlvMenuItem*)getMenuBar()->getItemByName("BUFFERS");
	if (item && item->getMenu())
	    item->getMenu()->
		setOpenMenuCallbackName(IlvGetSymbol("UpdateWindowsCB"));

	// Buffering Callback
	item = (IlvMenuItem*)getToolBar()->getItemByName("BUFFERING");
	if (item && item->getGraphic()) {
	    IlvOptionMenu* optmenu = (IlvOptionMenu*)item->getGraphic();
	    optmenu->setCallback(IlvGetSymbol("BufferingCB"));
	}

	// Initialize the desktop
	IlvDesktopManager* desktop =
	    new FileViewerDesktop(getDesktopRectangle()->getView());

	// Create the maximized buttons in the menu bar
	desktop->makeMaximizedStateButtons(getMenuBar());
    }
    ~FileViewerMainWindow()
    {
	// Delete the desktop manager
	delete getDesktopManager();
    }
    // ______________________________________________________________________
    IlvToolBar* getToolBar() const
    {
	return (IlvToolBar*)getObject("ToolBar");
    }
    IlvToolBar* getMenuBar() const
    {
	return (IlvToolBar*)getObject("MenuBar");
    }
    IlvToolBar* getStatusBar() const
    {
	return (IlvToolBar*)getObject("StatusBar");
    }
    IlvGadgetContainerRectangle* getDesktopRectangle() const
    {
	return (IlvGadgetContainerRectangle*)getObject("Desktop");
    }
    FileViewerDesktop* getDesktopManager() const
    {
	return (FileViewerDesktop*)
	    IlvDesktopManager::Get(getDesktopRectangle()->getView());
    }
    static void QuitCB(IlvGraphic* /* g */,
		       IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->quit();
    }
    void quit()
    {
	IlvApplication* appli = IlvApplication::GetApplication(this);
	if (appli)
	    appli->quit();
    }
    static void NewCB(IlvGraphic* /* g */,
		      IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->newFrame();
    }
    void newFrame() {
	ContainerViewFrame* frame =
	    getDesktopManager()->buildNewFrame(0, IlvRect(0, 0, 300, 400));
	getDesktopManager()->setCurrentFrame(frame);
    }
    static void OpenCB(IlvGraphic* g,
		       IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->open();
    }
    void open()
    {
	const char* const filters[1] = { "*.ilv" };
	const char* const messages[1] = { "Rogue Wave Views files" };
	const char* home = getDisplay()->getEnvOrResource("ILVHOME", 0);
	IlPathName dataPath;
	if (home && *home) {
	    IlString strHome = home;
	    strHome+= "/";
	    dataPath= strHome;
	    dataPath.addDirectory("data/");
	}
	IlvFileBrowser fb(getDisplay(),
			  getSystemView(),
			  dataPath,
			  1,
			  filters,
			  messages);
	const char* result = fb.get();
	if (result) {
	    ContainerViewFrame* frame =
		getDesktopManager()->buildNewFrame(result,
						   IlvRect(0, 0, 300, 400));
	    frame->loadFile(result);
	    getDesktopManager()->setCurrentFrame(frame);
	}
    }
    static void CascadeCB(IlvGraphic* /* g */,
			  IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->cascade();
    }
    void cascade()
    {
	getDesktopManager()->cascadeFrames();
    }
    static void TileHorizontalCB(IlvGraphic* /* g */,
				 IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->tileHorizontal();
    }
    void tileHorizontal()
    {
	getDesktopManager()->tileFrames(IlvHorizontal);
    }
    static void TileVerticalCB(IlvGraphic* /* g */,
			       IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->tileVertical();
    }
    void tileVertical()
    {
	getDesktopManager()->tileFrames(IlvVertical);
    }
    static void NextCB(IlvGraphic* /* g */,
		       IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->next();
    }
    void next()
    {
	FileViewerDesktop* desktop = getDesktopManager();
	ContainerViewFrame* frame = desktop->getCurrentContainerFrame();
	if (frame)
	    desktop->setCurrentFrame(desktop->getNextFrame());
    }
    static void PreviousCB(IlvGraphic* /* g */,
			   IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->previous();
    }
    void previous()
    {
	FileViewerDesktop* desktop = getDesktopManager();
	ContainerViewFrame* frame = desktop->getCurrentContainerFrame();
	if (frame)
	    desktop->setCurrentFrame(desktop->getPreviousFrame());
    }
    static void CloseCB(IlvGraphic* /* g */,
			IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->close();
    }
    void close()
    {
	ContainerViewFrame* frame =
	    getDesktopManager()->getCurrentContainerFrame();
	if (frame)
	    frame->closeFrame();
    }
    static void CloseAllCB(IlvGraphic* /* g */,
			   IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->closeAll();
    }
    void closeAll() {
	for (IlUInt i = getDesktopManager()->getCardinal(); i; i--)
	    getDesktopManager()->getFrame(i - 1)->closeFrame();
    }
    static void ChangeCurrentFrameCB(IlvGraphic* g,
				     IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder) {
	    IlvPopupMenu* menu = (IlvPopupMenu*)g;
	    const char* title =
		menu->getItem(menu->whichSelected())->getLabel();
	    holder->changeCurrentFrame(title);
	}
    }
    void changeCurrentFrame(const char* title)
    {
	FileViewerDesktop* desktop = getDesktopManager();
	for (IlUInt i = 0; i < desktop->getCardinal(); i++) {
	    if (!strcmp(title, desktop->getFrame(i)->getTitle())) {
		desktop->setCurrentFrame(desktop->getFrame(i));
		return;
	    }
	}
    }
    static void UpdateWindowsCB(IlvGraphic* g,
				IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->updateWindowsMenu((IlvPopupMenu*)g);
    }
    void updateWindowsMenu(IlvPopupMenu* menu)
    {
	menu->autoLabelAlignment(IlFalse, IlFalse);
	// The item is named ==> Retrieve it using getItemByName
	IlvGadgetItem* separator = menu->getItemByName("START_BUFFERS");
	if (!separator)
	    return;
	IlvUShort index = (IlvUShort)(menu->getIndex(separator) + 1);
	// First remove all the items after separator
	while (menu->getCardinal() != index)
	    menu->removeItem((IlvUShort)(menu->getCardinal() - 1));
	// Then add the new buffers
	for (IlUInt i = 0; i < getDesktopManager()->getCardinal(); i++) {
	    menu->insertLabel(index,
			      getDesktopManager()->getFrame(i)->getTitle());
	    menu->getItem(index++)->setCallback(ChangeCurrentFrameCB);
	}
	menu->autoLabelAlignment(IlvTrue, IlvFalse);
    }
    static void HighlightCB(IlvGraphic* g,
			    IlAny arg)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder) {
	    IlvAbstractMenu* menu = (IlvAbstractMenu*)g;
	    IlShort pos = *(IlShort*)arg;
	    IlvMenuItem* item = (pos != -1)? menu->getItem(pos) : 0;
	    holder->highlight(item);
	}
    }
    void highlight(const IlvMenuItem* item)
    {
	if (item) {
	    const char* label = item->getLabel()
		? item->getLabel()
		: (item->getToolTip()
		   ? item->getToolTip()
		   : "");
	    getStatusBar()->getItem(0)->setLabel(label);
	} else
	    getStatusBar()->getItem(0)->setLabel("Ready");
    }
    static void BufferingCB(IlvGraphic* g,
			    IlAny /* arg */)
    {
	FileViewerMainWindow* holder = (FileViewerMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder) {
	    IlvOptionMenu* menu = (IlvOptionMenu*)g;
	    holder->setBuffering(menu->whichSelected() ? IlTrue : IlFalse);
	}
    }
    void setBuffering(IlvBoolean set)
    {
	ContainerViewFrame* frame =
	    getDesktopManager()->getCurrentContainerFrame();
	if (!frame)
	    return;
	frame->getContainer()->setDoubleBuffering(set);
	frame->getContainer()->reDraw();
    }
};

// --------------------------------------------------------------------------
// This subclass of the IlvApplication class just creates an instance of
// the FileViewerMainWindow class.
// --------------------------------------------------------------------------
class FileViewerApplication
    : public IlvApplication
{
public:
    FileViewerApplication(const char* name,
			  const char* displayName,
			  int argc,
			  char** argv)
        : IlvApplication(name, displayName, argc, argv)
    {
	setUsingExitPanel(IlFalse);
    }
    ~FileViewerApplication()
    {
    }
    // ______________________________________________________________________
    virtual void makePanels()
    {
	IlvContainer* mainWindow =
	    new FileViewerMainWindow(getDisplay(),
				     getName(),
				     getName(),
				     IlvRect(0, 0, 400, 500));
	mainWindow->setDestroyCallback(IlvAppExit, this);
	addPanel(mainWindow);
    }
};

// ------------------------------------------------------
// Entry point
// ------------------------------------------------------
int main(int argc,
	 char* argv[])
{
    IlvSetLocale();
    FileViewerApplication* appli =
	new FileViewerApplication("MDI Sample", 0, argc, argv);
    if (!appli->getDisplay())
        return -1;
    IlPathName localPath(appli->getDisplay()->getHomePath());
    localPath.addDirectory("samples/gadgets/mdilv/data");
    appli->getDisplay()->prependToPath(localPath);
    
    appli->run();
    return 0;
}
