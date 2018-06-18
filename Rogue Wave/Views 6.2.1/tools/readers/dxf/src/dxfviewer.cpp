// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/dxf/src/dxfviewer.cpp
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
// Definition of the DXF File Viewer
//
// This class shows how to read and display DXF Files
// with Rogue Wave Views.
// --------------------------------------------------------------------------

// Some objects used for the GUI
#include <ilviews/gadgets/menubar.h>
#include <ilviews/gadgets/menu.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/gadgets/toolbar.h>
#include <ilviews/graphics/label.h>

#include <ilviews/bitmaps/io.h>

#include <ilviews/maps/projection/allprojs.h>

// conditional includes supporting the new C++ norm
#ifdef ILVSTD
#include <iostream>
#include <fstream>
using namespace std;
#else
#include <iostream.h>
#include <fstream.h>
#include <stdio.h>
#ifndef WINDOWS
#include <unistd.h>
#endif
#include <stdlib.h>
#endif

    
#include "dxfviewer.h"
#include "dxffactory.h"
#include "dxfreader.h"

// --------------------------------------------------------------------------
// Static and callback functions
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Static method to read bitmaps
// --------------------------------------------------------------------------
static IlvBitmap*
GetBitmap(IlvDisplay* display,const char* name)
{
    IlvBitmap* bitmap = display->getBitmap(name);

    if (bitmap) { // The bitmap has already been loaded. Return it
	return bitmap;
    }

    // try to load the bitmap using its full name
    bitmap = display->readBitmap(name);
    if (bitmap) { 
	return bitmap;
    }

    // try to load ILVMAPSHOME/bitmap...
    char path[2048];
    const char* home=display->getEnvOrResource("ILVMAPSHOME");
    if (home)
	sprintf(path,"%s/%s",home,name);
    else
	sprintf(path,"%s",name);
    bitmap = display->readBitmap(path);
    if (bitmap) { 
	return bitmap;
    }
    
    // try to load ILVHOME/bitmap...
    home=display->getEnvOrResource("ILVHOME");
    if (home) {
	sprintf(path,"%s/%s",home,name);
	bitmap = display->readBitmap(path);
    }
    return bitmap; 
}

// --------------------------------------------------------------------------
static void
ExitCB(IlvView*, IlvAny a)
{
    DXFViewer* viewer = (DXFViewer*) a;
    IlvDisplay* display = viewer->getDisplay();
    delete viewer;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
ExitCB(IlvGraphic*, IlvAny)
{
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
LoadCB(IlvGraphic*, IlvAny a)
{
    DXFViewer* viewer = (DXFViewer*) a;
    viewer->load();
}

// --------------------------------------------------------------------------
static void
SaveCB(IlvGraphic*, IlvAny a)
{
    DXFViewer* viewer = (DXFViewer*) a;
    viewer->save(IlFalse);
}

// --------------------------------------------------------------------------
static void
SaveWithMapInfoCB(IlvGraphic*, IlvAny a)
{
    DXFViewer* viewer = (DXFViewer*) a;
    viewer->save(IlTrue);
}

// --------------------------------------------------------------------------
static void
ZoomCB(IlvGraphic* , IlvAny a)
{
    DXFViewer* viewer = (DXFViewer*) a;
    IlvSCManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvRect visibleRect;
    mgrRect->getView()->sizeVisible(visibleRect);
    mgrRect->getManager()->zoomView(mgrRect->getView(),
				    IlvPoint(visibleRect.centerx(),
					     visibleRect.centery()),
				    1.5,
				    1.5);
}

// --------------------------------------------------------------------------
static void
UnZoomCB(IlvGraphic* , IlvAny a)
{
    DXFViewer* viewer = (DXFViewer*) a;
    IlvSCManagerRectangle* mgrRect = viewer->getManagerRectangle();
    IlvRect visibleRect;
    mgrRect->getView()->sizeVisible(visibleRect);
    mgrRect->getManager()->zoomView(mgrRect->getView(),
				    IlvPoint(visibleRect.centerx(),
					     visibleRect.centery()),
				    (float) (1./1.5),
				    (float) (1./1.5));
}

// --------------------------------------------------------------------------
static void
ShowAllCB(IlvGraphic* , IlvAny a)
{
    DXFViewer* viewer = (DXFViewer*) a;
    viewer->showAll();
}

// --------------------------------------------------------------------------
// DXFViewerFileDialog: Class to be used as a file selector
// --------------------------------------------------------------------------
#ifndef USE_ADVGDT
class DXFViewerFileDialog : public IlvDialog
{
public:

    IlvTextField* _filename;
    IlBoolean _ok;
    DXFViewerFileDialog(IlvDisplay*display,IlvSystemView transientFor);

    // gets the filename
    const char* get();
};

// --------------------------------------------------------------------------
static void 
DXFViewerFileDialogOkCB(IlvGraphic* graphic,IlvAny arg)
{
    DXFViewerFileDialog* d = (DXFViewerFileDialog*)arg;
    d->_ok = IlTrue;
    d->hide();
}

// --------------------------------------------------------------------------
static void 
DXFViewerFileDialogCancelCB(IlvGraphic* graphic,IlvAny arg)
{
    DXFViewerFileDialog* d = (DXFViewerFileDialog*)arg;
    d->hide();
}

// --------------------------------------------------------------------------
DXFViewerFileDialog::DXFViewerFileDialog(IlvDisplay*display,
					 IlvSystemView transientFor)
    : IlvDialog(display,"FileDialog","SourceFile",
		IlvRect(0,0,300,150),0,transientFor)
{
    _filename = new IlvTextField(display,IlvPoint(100,10),
				 "");
    _filename->w(190);
    IlvLabel* label = new IlvLabel(display,
				   IlvPoint(10,
					    _filename->y() + _filename->h()-2),
				   "Filename");
    this->addObject(_filename);
    this->addObject(label);
    IlvButton* okButton = new IlvButton(display,
					"Ok",
					IlvRect(30,100,80,24));
    
    this->addObject(okButton);
    okButton->setClientData(this);
    okButton->setCallback(DXFViewerFileDialogOkCB);
    IlvButton* cancelButton = new IlvButton(display,
					"Cancel",
					IlvRect(180,100,80,24));
    
    this->addObject(cancelButton);
    cancelButton->setClientData(this);
    cancelButton->setCallback(DXFViewerFileDialogCancelCB);

}

// --------------------------------------------------------------------------
const char* DXFViewerFileDialog::get()
{
    _ok = IlFalse;
    this->showModal();
    if (_ok) {
	return _filename->getLabel();
    } 
    return (const char*)0;
}
#endif /* USE_ADVGDT */

// --------------------------------------------------------------------------
// DXFViewer
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Creates an new instance of the DXF Viewer. FileName is the name of a DXF 
// Frame file.
// --------------------------------------------------------------------------
DXFViewer::DXFViewer(IlvDisplay* display,
		     IlvMapInfo* mapInfo,
		     IlvProjection* sourceProjection,
		     const char* fileName)
:_mapInfo(mapInfo),
 _sourceProjection(sourceProjection)
{
  createGUI(display);

  if (_mapInfo)
      _mapInfo->attach(_managerRectangle->getManager());
  
  if (fileName)
      loadFile(fileName);
}

// --------------------------------------------------------------------------
void
_showMousePosition(IlvView* view, IlvEvent& event, IlvAny arg)
{
    DXFViewer* viewer = (DXFViewer*) arg;
    viewer->showMousePosition(view, event);
}

// --------------------------------------------------------------------------
DXFViewer::~DXFViewer()
{
    // displaying the mouse position
    IlvView* view = _managerRectangle->getView();
    view->removeInputCallback(_showMousePosition, this);
    if (_fileSelector) {
	delete _fileSelector;
	_fileSelector = 0;
    }
    if (_sourceProjection) {
	if (_sourceProjection != _mapInfo->getProjection()) {
	    delete _sourceProjection;
	    _sourceProjection = 0;
	}
    }
    if (_container) {
	delete _container;
	_container = 0;
    }
}

// --------------------------------------------------------------------------
// This function creates the Graphic User Interface by code. It would also 
// have been possible to use Rogue Wave Views Studio for that.
// --------------------------------------------------------------------------
void
DXFViewer::createGUI(IlvDisplay* display)
{
    _container = new IlvGadgetContainer(display,
					"DXFViewer",
					"Rogue Wave Views DXF Viewer",
					IlvRect(50, 50, 450, 450),
					IlFalse);
    _container->setDestroyCallback(ExitCB, this);
    createMenuBar(_container);
    createToolBar(_container);
    createManagerRectangle(_container);
    createStatusBar(_container);
    
    // Georeferencing the manager
    IlvManager* manager = _managerRectangle->getManager();
    
    // displaying the mouse position
    IlvView* view = _managerRectangle->getView();
    view->setInputCallback(_showMousePosition, this);
    
    manager->setDoubleBuffering(view, IlTrue);
    manager->setKeepingAspectRatio(view, IlTrue);
    
#ifdef USE_ADVGDT    
    _fileSelector = new IlvFileBrowser(display,
				       _container->getSystemView());
#else
    _fileSelector = new DXFViewerFileDialog(display,
					    _container->getSystemView());
#endif
    _fileSelector->setTitle("Load a DXF Frame File");
}

// --------------------------------------------------------------------------
void
DXFViewer::createMenuBar(IlvGadgetContainer* container)
{
    IlvMenuBar* menuBar= new IlvMenuBar(container->getDisplay(),
				       IlvRect(0, 0, 450, 26));
    menuBar->setFlushingRight(IlFalse);
    container->addObject(menuBar);
    
    // horizontal attachment
    container->getHolder()->attach(menuBar, IlvHorizontal);

    // subMenu creation
    IlvMenuItem fileItem("File");
    IlvPopupMenu* fileMenu = new IlvPopupMenu(container->getDisplay());

    IlvMenuItem loadItem("Load");
    loadItem.setClientData(this);
    loadItem.setCallback(LoadCB);
    fileMenu->addItem(loadItem);
    
    IlvMenuItem saveItem("Save");
    saveItem.setClientData(this);
    saveItem.setCallback(SaveCB);
    fileMenu->addItem(saveItem);
    
    IlvMenuItem saveWithMapInfoItem("Save with Map Info");
    saveWithMapInfoItem.setClientData(this);
    saveWithMapInfoItem.setCallback(SaveWithMapInfoCB);
    fileMenu->addItem(saveWithMapInfoItem);
    
    IlvMenuItem quitItem("Quit");
    quitItem.setCallback(ExitCB);
    quitItem.setClientData(this);
    fileMenu->addItem(quitItem);
    
    fileItem.setMenu(fileMenu, IlFalse);
    menuBar->addItem(fileItem);

}

// --------------------------------------------------------------------------
void
DXFViewer::createToolBar(IlvGadgetContainer* container)
{
    // Registering first the gif bitmap reader
    // IlvRegisterBitmapReader(IlvReadGIFBitmap, "gif");
    
    IlvDisplay* display = container->getDisplay();
    IlvToolBar* toolBar = new IlvToolBar(display,
					 IlvRect(0, 27, 450, 27));
    container->addObject(toolBar);
    container->getHolder()->attach(toolBar, IlvHorizontal);

    IlvMenuItem zoomItem;
    zoomItem.setBitmap(GetBitmap(display,"data/maps/zoom.png"));
    zoomItem.setToolTip("Zoom");
    zoomItem.setClientData(this);
    zoomItem.setCallback(ZoomCB);
    toolBar->addItem(zoomItem);

    IlvMenuItem unZoomItem;
    unZoomItem.setBitmap(GetBitmap(display,"data/maps/unzoom.png"));
    unZoomItem.setToolTip("Unzoom");
    unZoomItem.setClientData(this);
    unZoomItem.setCallback(UnZoomCB);
    toolBar->addItem(unZoomItem);
    
    IlvMenuItem showAllItem;
    showAllItem.setBitmap(GetBitmap(display,"data/maps/fit.png"));
    showAllItem.setToolTip("Show All");
    showAllItem.setClientData(this);
    showAllItem.setCallback(ShowAllCB);
    toolBar->addItem(showAllItem);
}

// --------------------------------------------------------------------------
void
DXFViewer::createManagerRectangle(IlvGadgetContainer* container)
{
    _managerRectangle = new IlvSCManagerRectangle(container->getDisplay(),
						  IlvRect(0, 54, 450, 381));
    container->addObject(_managerRectangle);


    // attachments
    container->getHolder()->attach(_managerRectangle, IlvHorizontal);
    container->getHolder()->attach(_managerRectangle, IlvVertical);

    // remove the default accelerators of the manager
    _managerRectangle->getManager()->removeAccelerators();
}

// --------------------------------------------------------------------------
void
DXFViewer::createStatusBar(IlvGadgetContainer* container)
{
    _statusBar = new IlvTextField(container->getDisplay(),
				  "",
				  IlvRect(0, 435, 450, 15));
    container->addObject(_statusBar, IlTrue);

    _statusBar->setEditable(IlFalse);

    // attachments
    container->getHolder()->attach(_statusBar, IlvHorizontal);
    container->getHolder()->attach(_statusBar, IlvVertical, 1, 0, 0);
}

// --------------------------------------------------------------------------
void
DXFViewer::load()
{
#ifdef USE_ADVGDT
    _fileSelector->setType(IlvFileSelectorLoad);
#endif
    const char* fileName = _fileSelector->get();
    if (fileName)
	loadFile(fileName);
}

// --------------------------------------------------------------------------
void
DXFViewer::save(IlBoolean saveMapInfo)
{
    IlvMapInfo* mapInfo = IlvMapInfo::Get(_managerRectangle->getManager());
#ifdef USE_ADVGDT
    _fileSelector->setType(IlvFileSelectorSave);
#endif
    const char* fileName = _fileSelector->get();
    if (fileName) {
	if (!saveMapInfo)
	    if (mapInfo)
		mapInfo->detach();
	ofstream os(fileName);
	_managerRectangle->getManager()->save(os);
	if (!saveMapInfo && mapInfo)
	    mapInfo->attach(_managerRectangle->getManager());
    }
}

// --------------------------------------------------------------------------
void
DXFViewer::loadFile(const char* fileName)
{
    char buffer[100];
    _statusBar->setLabel("Loading...");
    _statusBar->reDraw();


    DXFDefaultGraphicFactory factory(getDisplay(),
				     _mapInfo,
				     _sourceProjection);

    _managerRectangle->getManager()->deleteAll(IlTrue, IlTrue);
    
    DXFReader reader(fileName,
		     _managerRectangle->getManager(),
		     &factory);
    if (reader.isBad()) {
	IlvIErrorDialog dialog(_managerRectangle->getManager()->getDisplay(),
			       reader.getErrorMessage());
	dialog.setTitle("DXF Error");
	dialog.get();
    }

    if (reader.getMapInfo() && !_mapInfo) {
	const IlvMapInfo* source = reader.getMapInfo();
	IlvMapInfo* copy = new IlvMapInfo(source->getProjection(),
					  source->getAdapter());
	IlvMapInfo* old = copy->attach(_managerRectangle->getManager());
	if (old)
	    delete old;
    }
    
    sprintf(buffer, "Done");


    showAll();

    _statusBar->setLabel(buffer);
    _statusBar->reDraw();

}

// --------------------------------------------------------------------------
void
DXFViewer::showMousePosition(IlvView* view, IlvEvent& event)
{
    char buf1[12];
    char buf2[12];
    char label[50];
    
    IlvCoordinate ll;

    if (_mapInfo) {
	if (_mapInfo->inverse(event, view, ll) == IlvMaps::NoError())
	    sprintf(label, "%s %s", 
		    IlvMaps::RadianToDMS(buf1, ll.x(), IlFalse),
		    IlvMaps::RadianToDMS(buf2, ll.y(), IlTrue));
	else
	    sprintf(label, "Can't compute latitude and longitude");
    }
    else
	sprintf(label, "No georeferencement information available");
    
    _statusBar->setLabel(label);
    _statusBar->reDraw();
}

// --------------------------------------------------------------------------
void
DXFViewer::showAll()
{
    IlvManager* manager = _managerRectangle->getManager();
    IlvView* view = _managerRectangle->getView();
    manager->fitTransformerToContents(view, IlTrue, IlTrue);
}

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
int 
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay("DXFViewer", 0, argc, argv);
    if (display->isBad()) {
      cout << "Couldn't open display" << endl;
      return 1;
    }

    DXFViewer* viewer = new DXFViewer(display);
    
    if (argc > 1)
	viewer->loadFile(argv[1]);
    
    IlvMainLoop();

    return 0;    
}



