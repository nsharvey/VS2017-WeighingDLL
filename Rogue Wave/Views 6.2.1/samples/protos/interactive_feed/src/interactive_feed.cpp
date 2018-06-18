// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/interactive_feed/interactive_feed.cpp
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
// Using the prototypes
// --------------------------------------------------------------------------

#if defined(IL_STD)
#include <cmath>
#else
#include <math.h>
#endif

#include <ilviews/manager/all.h>
#include <ilviews/protos/proto.h>
#include <ilviews/protos/protogr.h>
#include <ilviews/protos/groupholder.h>
#include <ilviews/protos/grouplin.h>

IL_STDUSE

// While not mandatory, it is often convenient to include
// all default graphic objects in the main file: 
// this allows editing the prototype in Studio without
// having to take care that all individual objects
// are individually included.
// To optimize the runtime footprint, one may wish
// to include just the necessary objects, once the prototypes
// have been designed for good and won't need to be modified
// or extended anymore.
#include <ilviews/graphics/all.h>
#include <ilviews/protos/allaccs.h>
#if 0
// if you have the gadgets modules, you can as well include all predefined
// gadgets to include gadgets in your prototypes.
#include <ilviews/gadgets/gadgets.h>
#endif

// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny)
{
  IlvDisplay* display = view->getDisplay();
  delete view;
  delete display;
  IlvExit(0);
}

// -------------------------------------------------------------------------
// create a mediator that will handle exchange between the application
// and the panel, by means of IlvGroup objects.

IlvUInt angleincrement = 4;

class MyGroupWatcher: public IlvGroupMediator 
{
public:
    MyGroupWatcher(IlvGroup* g,
		   IlUInt* a)
    	: IlvGroupMediator(g, a),
	  speed(0)
    {}
    IlBoolean changeValues(const IlvValue*,
			   IlUShort);
    void queryValues(IlvValue*,
		     IlUShort) const;
    IlUInt speed;
};

// --------------------------------------------------------------------------
// method handling user input and updating the application.
IlBoolean 
MyGroupWatcher::changeValues(const IlvValue* v,
			     IlUShort n)
{
    if (locked())
         return IlFalse;
    for (IlUInt i = 0; i < n; i++) {
	 if (v[i].getName() == IlvGetSymbol("increment"))
  	     *(IlUInt*)getObject() = (IlUInt) v[i];
    // here, we do not want the speed value to be editable by the user.
    // if we wanted to, we'd just have to add the following code.
    //	 else if (v[i].getName() == IlvGetSymbol("speed"))
    //	     speed = (IlUInt) v[i];
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
// method that synchronizes the group to the application values.
void
MyGroupWatcher::queryValues(IlvValue* v,
			    IlUShort n) const
{
    for (IlUInt i = 0; i < n; i++) {
	if (v[i].getName() == IlvGetSymbol("speed"))
   	    v[i]=speed;
	else if (v[i].getName() == IlvGetSymbol("increment"))
	    v[i]= *(IlUInt*)getObject();
    }
}

// --------------------------------------------------------------------------
static void
TimerProc(IlvTimer*,
	  IlAny arg)
{
    static IlUInt angle = 0;
    MyGroupWatcher* watcher=(MyGroupWatcher*)arg;
    IlUInt speed = (IlUInt)
	(60 + (40.0 * sin(IlvDegreesToRadians((IlDouble)angle))));
    watcher->speed = speed;
    
#if !defined(OPTIMIZE)
    watcher->update();
#elif !defined(OPTIMIZE_MAX)
    // if we're sure that the application has only changed a few values
    // and we know those, we can pass only those values that have changed.
    watcher->update(& IlvGetSymbol("speed"), 1);
#else
    // an even faster method, but less general, is the following:
    watcher->getPresentation()->changeValue(IlvValue("speed", speed));
#endif
    
    angle = (angle + angleincrement) % 360;
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
  // Connect to the display system ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  IlvDisplay* display = new IlvDisplay("Protos", 0, argc, argv);
  if (!display || display->isBad()) {
    IlvFatalError("Couldn't open display");
    if (display)
        delete display;
    return -1;
  }
  
  // Prepare a window and a manager to display a scene ~~~~~~~~~~~~~~~~~~
  IlvManager* manager = new IlvManager(display);
  IlvView* view = new IlvView(display, "BGO sample 2", "BGO sample 2",
  			      IlvRect(0, 0, 400, 300));
  manager->addView(view);
  // Load a data file into the manager ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Add to the samples'data directory to the display's path
  // to be sure to find the proper file.
  IlString buf(getenv("ILVHOME"));
  buf += "/samples/protos/interactive_feed/data";
  display->appendToPath(buf);
  display->appendToPath(".");
  manager->read("data.ilv");

  // find the group we want to feed with values ~~~~~~~~~~~~~~~~~~~~~~~~~
  IlvGroupHolder* holder=IlvGroupHolder::Get(manager);
  IlvGroup* maingroup = holder->getGroup("MainGroup");  
  if (!maingroup) {
	IlvFatalError("This sample expects to find an IlvGroup "
		      "of name \"MainGroup\" in the file \"data.ilv\"");
	return -1;
  }
  // install a connection between this group and the rest of the application
  MyGroupWatcher watch(maingroup, &angleincrement);
  watch.update();
  
  // start changing the values of the in the application ~~~~~~~~~~~~~~~~
  IlvTimer* timer = new IlvTimer(display, 0, 200, TimerProc, (IlAny)&watch);
  timer->run();
  
  // display the scene and run the application ~~~~~~~~~~~~~~~~~~~~~~~~~~
  view->setDestroyCallback(Quit);
  manager->setDoubleBuffering(view, IlTrue);
  view->show();
  IlvMainLoop();
  return 0;
}
