// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/motif/src/dragdrop.cpp
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
// Demonstrating the Motif drag/drop
// --------------------------------------------------------------------------

#include <include/ddmotif.h>
#include <include/ddinter.h>
#include <include/ddpanels.h>
#include <ilviews/contain/contain.h>
#include <ilviews/graphics/all.h>
#include <ilviews/bitmaps/ppm.h>

static const char* DefaultFileName = "demo2d.ilv";

// --------------------------------------------------------------------------
static void
Quit(IlvView* top,
     IlAny)
{
    delete top->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// This function associates the Motif D&D interactor with each of the objects
// stored in this container.
// --------------------------------------------------------------------------
void
InstallMotifDrag(IlvContainer* source)
{
    MotifDragInteractor* mdd =
	new MotifDragInteractor(source->getSystemView());
    IlUInt count;
    IlvGraphic* const* objects = source->getObjects(count);
    for (IlUInt loop = 0; loop < count; loop++)
	objects[loop]->setInteractor(mdd);
}

// **************************************************************************
// Entry point
// **************************************************************************
int
main(int argc,
     char* argv[])
{
    const char* filename = (argc > 1) ? argv[1] : DefaultFileName;
    IlvDisplay* display = new IlvDisplay("MotifDD", "", argc, argv);
    if (!display || display->isBad()) {
	if (display) delete display;
	IlvFatalError("Couldn't open display...");
	return 1;
    }
    if (!display->topShell()) {
    	delete display;
	IlvFatalError("This Views application hasn't been linked with mviews...");
	return 1;
    }

    // Create a container to drag IlogViews objects from
    const char* title = "SourceContainer";
    IlvContainer* sourceContainer = new IlvContainer(display, title, title,
						     IlvRect(0, 0, 400, 400),
						     IlTrue, IlFalse);
    sourceContainer->setDestroyCallback(Quit);
    sourceContainer->readFile(filename);
    // Set the interactors to the objects
    InstallMotifDrag(sourceContainer);
    // Show this container
    sourceContainer->show();

    // Create a container to drop objects (Views or Compound Text) in
    // This must NOT be a Top Window!!
    title = "DestContainer";
    IlvContainer* destContainer = new IlvContainer(display, title, title,
						   IlvRect(420, 0, 400, 400),
						   IlTrue, IlTrue);
    destContainer->setDestroyCallback(Quit);
    // Register as a drop site
    ContainerMotifDropSite drop(destContainer);

    // Create another possible DropSite, pure Motif
    MotifTextDropSite motifDrop(CreateMotifPanels(display));

    IlvMainLoop();
    return 0;
}
