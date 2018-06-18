// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/base_feed/base_feed.cpp
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

/* 
 * While not mandatory, it is often convenient to include
 * all default graphic objects in the main file: 
 * this allows editing the prototype in Studio without
 * having to take care that all individual objects
 * are individually included.
 * To optimize the runtime footprint, one may wish
 * to include just the necessary objects, once the prototypes
 * have been designed for good and won't need to be modified
 * or extended anymore.
 */
#include <ilviews/graphics/all.h>
#include <ilviews/protos/allaccs.h>

#if 0
// if you have the gadgets modules, you can as well include all predefined
// gadgets to include gadgets in your prototypes.
#include <ilviews/gadgets/gadgets.h>
#endif

static void
Quit(IlvView* view,
     IlAny)
{
    IlvDisplay* display = view->getDisplay();
    delete view;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Change speed value at each timer tick
// --------------------------------------------------------------------------
const IlUInt angleincrement = 4;

static void
TimerProc(IlvTimer*,
	  IlAny arg)
{
    static IlUInt angle = 0;
    IlvGroup* maingroup=(IlvGroup*) arg;
    IlUInt speed = (IlUInt)
	(60 + (40.0 * sin(IlvDegreesToRadians((IlvDouble)angle))));
    // We feed in feed values. Because the main group is connected
    // to other prototypes or group, this will turn adjust all
    // values the main group is connected to.
    maingroup->changeValue(IlvValue("speed", speed));
    angle = (angle + angleincrement) % 360;
}

// -------------------------------------------------------------------------
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
  IlvView* view = new IlvView(display, "BGO sample 1", "BGO sample 1",
  			      IlvRect(0, 0, 400, 300));
  manager->addView(view);
  // Load a data file into the manager ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Add to the samples'data directory to the display's path
  // to be sure to find the proper file.
  IlString buf (getenv("ILVHOME"));
  buf+="/samples/protos/base_feed/data";
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
  // start changing the values of the target group ~~~~~~~~~~~~~~~~~~~~~~
  IlvTimer* timer = new IlvTimer(display, 0, 200, TimerProc, (IlAny)maingroup);
  timer->run();

  // display the scene and run the application ~~~~~~~~~~~~~~~~~~~~~~~~~~
  view->setDestroyCallback(Quit);
  manager->setDoubleBuffering(view, IlTrue);
  view->show();
  IlvMainLoop();
  return 0;
}
