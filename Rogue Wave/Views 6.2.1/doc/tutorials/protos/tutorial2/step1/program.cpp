// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/protos/tutorial2/step1/program.cpp
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

#include <ilviews/manager/all.h>
#include <ilviews/protos/proto.h>
#include <ilviews/protos/protogr.h>
#include <ilviews/protos/groupholder.h>
#include <ilviews/graphics/all.h>

#include <ilviews/gadgets/msglabel.h>

#include <ilviews/protos/allaccs.h>

static void Quit(IlvView* view, IlvAny)
{
    IlvDisplay* display = view->getDisplay();
    delete view;
    delete display;
    IlvExit(0);
}

int main(int argc, char* argv[])
{
  // Connect to the display system ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  IlvDisplay* display = new IlvDisplay("ViewsBGO", 0, argc, argv);
  if (!display || display->isBad()) {
    IlvFatalError("Couldn't open display");
    return -1;
  }
  // Prepare a window and a manager to display a scene ~~~~~~~~~~~~~~~~~~
  IlvManager* manager = new IlvManager(display);
  IlvView* view = new IlvView(display, "BGO tutorial 1", "BGO tutorial 1",
  			      IlvRect(0, 0, 400, 300));
  manager->addView(view);
  // Load a data file into the manager ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Add to the samples'data directory to the display's path
  // to be sure to find the proper file.
  IlString buf (getenv("ILVHOME"));
  buf+="/doc/tutorials/protos/tutorial2/step1";
  display->appendToPath(buf);
  display->appendToPath("..");
  manager->read("myPanel.ilv");

  // display the scene and run the application ~~~~~~~~~~~~~~~~~~~~~~~~~~
  view->setDestroyCallback(Quit);
  manager->setDoubleBuffering(view, IlvTrue);
  view->show();
  IlvMainLoop();
  return 0;
}
