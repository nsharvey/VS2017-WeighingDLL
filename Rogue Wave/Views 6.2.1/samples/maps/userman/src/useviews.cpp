// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/useviews.cpp
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
// Using Rogue Wave Views Maps modules
// --------------------------------------------------------------------------

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadmgr/rectscmg.h>
#include <ilviews/graphics/all.h>
#include <ilviews/gadgets/textfd.h>

#include <ilviews/manager/manager.h>
#include <ilviews/maps/projection/lamazeqa.h>
#include <ilviews/maps/mapinfo.h>

#include <ilog/pathname.h>

#ifndef ILVSTD
#include <string.h>
#include <stdio.h>
#else
#include <string>
#include <cstdio>
#endif

class SimpleMapViewer
{
  public:
    SimpleMapViewer(IlvDisplay * display,
		    const char* fileName);
    ~SimpleMapViewer();


    void showMousePosition(IlvView* view,
			   IlvEvent& event);
  private:
    void createGUI(IlvDisplay* display);
    void createManagerRectangle(IlvGadgetContainer*);
    void createStatusBar(IlvGadgetContainer*);
    void loadMap(const char* fileName);
    void addCities();
    void addCity(const char*, const char*, const char*);

  private:
    IlvGadgetContainer* _container;
    IlvSCManagerRectangle* _managerRectangle;
    IlvMapInfo* _mapInfo;
    IlvTextField* _statusBar;
};

// --------------------------------------------------------------------------
void
_showMousePosition(IlvView* view, IlvEvent& event, IlvAny arg)
{
    SimpleMapViewer* mapViewer = (SimpleMapViewer*) arg;
    mapViewer->showMousePosition(view, event);
}

// --------------------------------------------------------------------------
SimpleMapViewer::SimpleMapViewer(IlvDisplay* display,
				 const char* fileName)
    :_container(0),
     _managerRectangle(0),
     _mapInfo(0),
     _statusBar(0)

   
{
    createGUI(display);
    loadMap(fileName);
}

// --------------------------------------------------------------------------
void
SimpleMapViewer::loadMap(const char* fileName)
{
    IlvManager* manager = _managerRectangle->getManager();
    IlvView* view = _managerRectangle->getView();
    manager->read(fileName);
    _mapInfo = IlvMapInfo::Get(manager);
    if (_mapInfo) {
	view->setInputCallback(_showMousePosition, this);
	addCities();
    }
    manager->fitTransformerToContents(view, IlTrue);
}

// --------------------------------------------------------------------------
SimpleMapViewer::~SimpleMapViewer()
{
    if(_mapInfo) {
	IlvView* view = _managerRectangle->getView();
	view->removeInputCallback(_showMousePosition, this);
    }
    
    delete _container;
}

// --------------------------------------------------------------------------
// the exit callback
void
_exit(IlvView* view, IlvAny arg)
{
    SimpleMapViewer* viewer = (SimpleMapViewer*) arg;
    IlvDisplay* display = view->getDisplay();
    delete viewer;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
void
SimpleMapViewer::createGUI(IlvDisplay* display)
{
    _container = new IlvGadgetContainer(display,
					"SimpleMapViewer",
					"Integrating projections and"
					" graphics",
					IlvRect(50, 50, 450, 450),
					IlFalse);
    _container->setDestroyCallback(_exit, this);
    createManagerRectangle(_container);
    createStatusBar(_container);
}
  
// --------------------------------------------------------------------------
void
SimpleMapViewer::createManagerRectangle(IlvGadgetContainer* container)
{
    _managerRectangle = new IlvSCManagerRectangle(container->getDisplay(),
						  IlvRect(0, 0, 450, 435));
    container->addObject(_managerRectangle);
    
    
    // attachments
    container->getHolder()->attach(_managerRectangle, IlvHorizontal);
    container->getHolder()->attach(_managerRectangle, IlvVertical);

    IlvManager* manager = _managerRectangle->getManager();
    IlvView* view = _managerRectangle->getView();

    manager->setKeepingAspectRatio(view, IlTrue);
    manager->setDoubleBuffering(view, IlTrue);
}

// --------------------------------------------------------------------------
void
SimpleMapViewer::createStatusBar(IlvGadgetContainer* container)
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
SimpleMapViewer::showMousePosition(IlvView* view, IlvEvent& event)
{
    char buf1[12];
    char buf2[12];
    char label[50];
    
    IlvManager* manager = _mapInfo->getManager();

    const char* name = "";
    IlvPoint p(event.x(), event.y());
    IlvGraphic* g = manager->lastContains(p, view);
    if (g && g->getName())
	name = g->getName();

    IlvCoordinate ll;
    if (_mapInfo->inverse(event, view, ll) == IlvMaps::NoError())
	sprintf(label, "%s %s %s", 
		IlvMaps::RadianToDMS(buf1, ll.x(), IlFalse),
		IlvMaps::RadianToDMS(buf2, ll.y(), IlTrue),
		name);
    else
	sprintf(label, "Unable to invert mouse position");

    
    _statusBar->setLabel(label);
    _statusBar->reDraw();
}

// --------------------------------------------------------------------------
void
SimpleMapViewer::addCities()
{
    addCity("Washington", "39D11'N", "76D51W");
    addCity("New York", "40D59'N", "73D39'W");
    addCity("Miami", "25D58'N", "80D02'W");
    addCity("San Francisco", "37D44'N", "122D20'W");
    addCity("Seattle", "47D51'N", "122D01'W");
    addCity("Denvers", "39D50'N", "104D53'W");
}

// --------------------------------------------------------------------------
void
SimpleMapViewer::addCity(const char* cityName,
			 const char* latString,
			 const char* longString)
{
    double latitude;
    IlvMaps::DMSToRadian(latString, latitude);
    
    double longitude;
    IlvMaps::DMSToRadian(longString, longitude);
    
    IlvCoordinate c(longitude, latitude);
    
    IlvMapsError status = IlvMaps::NoError();
    IlvPoint p;
    status = _mapInfo->forward(c, p);
    
    if (status == IlvMaps::NoError()) {
	IlvMarker* marker = new IlvMarker(_container->getDisplay(),
					  p,
					  IlvMarkerFilledDiamond);
	marker->setSize(4);
	marker->setForeground(_container->getDisplay()->getColor("red"));
	IlvManager* manager = _managerRectangle->getManager();
	manager->addObject(marker, 1, IlFalse);
	marker->setName(cityName);
    }
}

// --------------------------------------------------------------------------
int
main(int, char**)
{
    IlvDisplay* display = new IlvDisplay("Map Viewer");        
    if (display->isBad()) {
	IlvPrint("Cannot create the display");
	return 1;
    }
    IlPathName localPath(display->getHomePath());
    display->prependToPath(localPath);
    localPath.addDirectory("samples/maps/userman/data");
    display->prependToPath(localPath);


    SimpleMapViewer*  viewer = new SimpleMapViewer(display,
						   "world.ilv");
    IlvMainLoop();

    return 0;
}
