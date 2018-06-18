// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/dxf/src/readdxf.cpp
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
// Reading DXF files using an IlvDXFInput
// --------------------------------------------------------------------------
#include <dxfincl/dxread.h>
#include <ilviews/base/iostream.h>
#include <ilviews/manager/manager.h>
#include <ilviews/manager/selinter.h>

#if defined(ILVSTD)
#include <fstream>
#include <cstring>
#include <cstdlib>
ILVSTDUSE
#else
#include <fstream.h>
#include <string.h>
#include <stdlib.h>
#endif

// #define INTERACTIVE

#if defined(INTERACTIVE)
#include <ilviews/gadgets/filesel.h>
#define DXFFILEDIR "."
#endif /* INTERACTIVE */

// --------------------------------------------------------------------------
static void ILVCALLBACK
ShowTransformer(IlvManager* mgr, IlvView* view, IlvEvent&, IlAny)
{
    IlvTransformer* t = mgr->getTransformer(view);
    if (t) {
	IlvTransfoParam x11, x12, x21, x22, dx, dy;
	t->getValues(x11, x12, x21, x22, dx, dy);
	IlvPrint("  transfo: %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",
		 x11, x12, x21, x22, dx, dy);
    }
    else IlvPrint("  transfo: identity");
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
Quit(IlvManager* mgr, IlvView*, IlvEvent&, IlAny)
{
    IlvDisplay* display = mgr->getDisplay();
    delete mgr;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
Quit(IlvView* top, IlAny mgr)
{
    IlvDisplay* display = top->getDisplay();
    delete (IlvManager*)mgr;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvDisplay* display = new IlvDisplay("DXF", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Couldn't initialise IlvDisplay.");
	delete display;
	return 1;
    }
    const char* filename = 0;
    double scale = 0.0;
    double translatex = 0.0, translatey = 0.0;
    for (int argloop = 1; argloop < argc; argloop++) {
	if (!strcmp(argv[argloop], "-scale")) {
	    if (argloop+2 > argc) {
		IlvFatalError("-scale needs a scaling parameter");
		delete display;
		return 1;
	    }
	    argloop++;
	    scale = atof(argv[argloop]);
	    if (scale <= 0.0) {
		IlvFatalError("Invalid parameter to -scale option");
		delete display;
		return 1;
	    }
	}
	else if (!strcmp(argv[argloop], "-translate")) {
	    if (argloop+3 > argc) {
		IlvFatalError("-translate needs two tarnslation parameters");
		delete display;
		return 1;
	    }
	    argloop++;
	    translatex = atof(argv[argloop]);
	    argloop++;
	    translatey = atof(argv[argloop]);
	}
	else filename = argv[argloop];
    }
    if (!filename) {
#if defined(INTERACTIVE)
	IlvIFileSelector* selector =
	    new IlvIFileSelector(display, DXFFILEDIR, "*.dxf");
	filename = selector->get();
	if (!filename) {
	    IlvFatalError("No file selected.");
	    delete display;
	    return 1;
	}
#else /* !INTERACTIVE */
	IlvFatalError("Usage %s <in.dxf> [-scale scale]", argv[0]);
	delete display;
	return 1;
#endif /* INTERACTIVE */
    }
    ifstream stream(filename, IlBinaryInputStreamMode);
    if (!stream) {
	IlvFatalError("Couldn't open %s", filename);
	delete display;
	return 1;
    }
    IlvDXFInput dxfinput(stream);
    IlvRect viewSize(0, 0, 800, 600);
    dxfinput.setViewsExtents(viewSize);
    if (scale != 0.0)
	dxfinput.scale(dxfinput.getExtmin().x(),
		       dxfinput.getExtmin().y(),
		       (IlFloat)scale, (IlFloat)scale);
    if ((translatex != 0.0) || (translatey != 0.0))
	dxfinput.translate((IlFloat)translatex, (IlFloat)translatey);

    IlUInt count = 0;
    IlvGraphic** graphics = dxfinput.readObjects(count, *display);
    IlvPrint("%ld objects loaded.\n", count);
    // Create the Manager and its View
    IlvView* view = new IlvView(display, "readDXF", "readDXF",
				viewSize, IlFalse);
    IlvManager* manager=  new IlvManager(display);
    view->setDestroyCallback(Quit, manager);
    manager->addView(view);

    // Store the objects
    for (IlUInt i = 0; i < count; i++)
	manager->addObject(graphics[i], IlFalse);
    IlvRect bbox;
    manager->computeBBox(bbox);
    manager->addAccelerator(Quit, IlvKeyUp, 'Q');
    manager->addAccelerator(ShowTransformer, IlvKeyUp, '?');
    manager->setInteractor(new IlvSelectInteractor(manager, view), view);
    IlvPrint("Views Bounding Box (%ld,%ld %ldx%ld)",
	     bbox.x(), bbox.y(), bbox.w(), bbox.h());
    view->show();
    IlvMainLoop();
    return 0;
}
