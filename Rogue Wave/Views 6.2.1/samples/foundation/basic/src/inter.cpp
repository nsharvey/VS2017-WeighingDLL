// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/basic/src/inter.cpp
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
// Interacting with graphic objects in a container
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>
#include <ilviews/util/ps.h>
#include <ilviews/graphics/inter.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/relflab.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/graphics/line.h>
#include <ilviews/graphics/arc.h>
#include <ilviews/graphics/spline.h>
#include <ilviews/graphics/set.h>
#include <ilviews/graphics/roundrec.h>
#include <ilviews/graphics/shadrect.h>
#include <ilviews/graphics/lablist.h>
#include <ilviews/graphics/shadlab.h>
#include <ilviews/graphics/icon.h>
#include <ilviews/graphics/marker.h>
#include <ilviews/graphics/gridrect.h>
#include <ilviews/graphics/ellipse.h>

static const char* title = "Rogue Wave Views sample: inter";

#define DATAFILE "demo2d.ilv"
#define BITMAPNAME "escher.ic"
#define DUMPFILE "dump.ps"

static void MakeDump(IlvGraphic*, IlAny);

// --------------------------------------------------------------------------
// Quit
// --------------------------------------------------------------------------
static void
DestroyView(IlvView* top, IlAny)
{
    delete top->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    // Connect to the display system
    IlvDisplay* display = new IlvDisplay("Inter", "", argc, argv);
    // Check its validity
    if (!display || display->isBad()) {
	delete display;
	IlvFatalError("Could not open display");
	return -1;
    }
    // Create a container as a top window
    IlvContainer* container = new IlvContainer(display,
					       title,
					       title,
					       IlvRect(0, 0, 759, 739),
					       IlTrue,
					       IlFalse);
    container->setDestroyCallback(DestroyView);
    // Load a bitmap
    IlvBitmap* bitmap = display->readBitmap(BITMAPNAME);
    if (bitmap) {
	bitmap->setName(BITMAPNAME);
    }
    // Load a data file into the container
    if (!container->readFile(DATAFILE)){
	IlvFatalError("Data file \'%s\' not found", DATAFILE);
	delete container;
	delete display;
	return -2;
    }
    // Get the objects by their names
    IlvGraphic* button  = container->getObject("button");
    if (!button) {
	button = new IlvReliefLabel(display, IlvPoint(40, 40), "PS Dump");
    }

    IlvInteractor* moveReshapeInteractor = IlvInteractor::Get("MoveReshape");
    for (IlUInt i = 0; i < container->getCardinal(); i++) {
	container->getObject(i)->setInteractor(moveReshapeInteractor);
    }
    // Associate an interactor with the button 'Dump'
    IlvButtonInteractor* buttonInteractor =
	new IlvButtonInteractor(IlvLeftButton, MakeDump, container);
    button->setInteractor(buttonInteractor);
    // Show the container
    container->setDoubleBuffering(IlTrue);
    container->show();
    // Wait for user events
    IlvMainLoop();
    return 0;
}

// --------------------------------------------------------------------------
// Implementation of the Dump button action.
// We create a PostScript dump of the visible area of the container
// --------------------------------------------------------------------------
static void
MakeDump(IlvGraphic* graphic, IlAny containerArg)
{
    IlvContainer* container = (IlvContainer*)containerArg;
    // Hide the button itself
    container->setVisible(graphic, IlFalse);
    // Get IlvDisplay instance
    IlvDisplay* display = container->getDisplay();
    // Create a PostScript dump device
    IlvPSColorDevice psdevice(display);
    // Get the visible part of this container
    IlvRect rect;
    container->sizeVisible(rect);
    // Initialize the dump device and check its validity
    if (psdevice.init(DUMPFILE, &rect)) {
	// Prepare IlvDisplay instance to dump
	display->initDump(&psdevice);
	// Redraw the container. It is done in the dump device
	container->draw();
	// Stop the dump process (close the dump file)
	display->endDump();
	// Notify that everything went fine
	IlvWarning("* Dump file ready in \'%s\'.", DUMPFILE);
    }
    else {
	// A problem occured. Let them know about it
	IlvFatalError("Couldn't open \'%s\' to store PostScript dump.",
		      DUMPFILE);
    }
    // Restore the visibility of the button
    container->setVisible(graphic, IlTrue);
}
