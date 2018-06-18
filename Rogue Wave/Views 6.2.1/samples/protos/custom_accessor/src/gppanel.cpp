// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/custom_accessor/src/gppanel.cpp
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

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// 		Main module for prototype sample application.
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

#include <ilviews/protos/proto.h>
#include <ilviews/protos/allaccs.h>
#include <ilviews/protos/protogr.h>
#include <ilviews/graphics/all.h>
#include <ilviews/gadgets/slider.h>


#define DATAFILE "bunnypan.ilv"

// --------------------------------------------------------------------------
// Quit from the Window Manager
// --------------------------------------------------------------------------
static void
DestroyView(IlvView* top,
	    IlAny)
{
    IlvDisplay* d = top->getDisplay();
    delete top;
    delete d;
    IlvExit(0);
}

// **************************************************************************
// C++ entry point
// **************************************************************************
int
main(int argc,
     char* argv[])
{
    // Connect to the display system ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    IlvDisplay* display = new IlvDisplay("PrototypeSample", "", argc, argv);
    // Check its validity ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (!display || display->isBad()) {
        if (display)
	    delete display;
	IlvFatalError("Couldn't open display");
	return -1;
    }

    // The prototype and panel data files are located in the
    // parent directory, so add it to the display's path.
    IlString buf (getenv("ILVHOME"));
    buf += "/samples/protos/custom_accessor/data";
    display->prependToPath(buf);
    
    // Create the manager.
    //
    IlvManager* manager = new IlvManager(display);

    // Create a toplevel view and add it to the manager.
    //
    IlvView* view = new IlvView(display,
				"PrototypeSample",
				"Prototypes Sample",
				IlvRect(100, 100, 480, 400),
				IlTrue,
				IlFalse);
    view->setDestroyCallback(DestroyView);
    manager->addView(view);

    // Read the panel file: the prototypes used in the panel
    // are automatically loaded.
    //
    manager->read(DATAFILE);

    // Show panel and run event loop.
    //
    view->show();
    manager->setDoubleBuffering(view, IlTrue);
    IlvMainLoop();
    return 0;
}
