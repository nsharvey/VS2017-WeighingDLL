// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/layout/userman/src/layoutsample1.cpp
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

#include <ilviews/layout/orthlink.h>
#include <ilviews/layout/report.h>
#include <ilviews/base/sstream.h>
#include <ilviews/graphics/relfrect.h>
#include <ilviews/grapher/polylink.h>
#include <ilog/pathname.h>

// --------------------------------------------------------------------------
static const char* fileName = "data/layoutsample1.ilv";

// --------------------------------------------------------------------------
void
Quit(IlvView* view,
     IlAny arg)
{
    IlvDisplay* display = view->getDisplay();
    IlvGrapher* grapher = (IlvGrapher*)arg;
    grapher->removeView(view);
    delete view;
    delete grapher;
    delete display;
    IlvExit(0);
}

extern "C" IlBoolean IlvSetLanguage();

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvSetLanguage();
    // --- Display ---
    IlvDisplay* display = new IlvDisplay("LayoutSample1", "", argc, argv);
    if (display->isBad()) {
        IlvFatalError("Couldn't open display");
        if (display)
	    delete display;
	return 1;
    }

    // Add the sample data directory in the display path
    IlPathName path = display->getHomePath();
    path.addDirectory("samples/layout/userman");
    display->prependToPath(path.getDirectory());

    // Create the grapher instance
    IlvGrapher* grapher = new IlvGrapher(display);
    // Create the view instance
    IlvView* view = new IlvView(display, "Layout Sample", "Layout Sample",
				IlvRect(0, 0, 600, 350));
    // Attach the view to the grapher
    grapher->addView(view);
    // Set the destroy callback on the view
    view->setDestroyCallback(Quit, (IlAny)grapher);

    // Fill the grapher with nodes and links from a Rogue Wave Views ILV file.
    // Alternatively, the nodes and links could be created by code.
    grapher->read(fileName);
    
    // Declare a handle for the layout instance
    IlvOrthogonalLinkLayout* layout = new IlvOrthogonalLinkLayout();

    // Attach the grapher to the layout instance
    layout->attach(grapher);
    
    // Perform the layout and get the layout report
    IlvGraphLayoutReport* layoutReport = layout->performLayout();

#ifdef VERBOSE
    // Print information from the layout report (optional)
    IlvPrint("layout done in %.8g sec., code = %d",
             layoutReport->getLayoutTime(),
             layoutReport->getCode());
#endif
    // Detach the grapher from the layout instance
    layout->detach();

    // Delete the layout instance
    delete layout;

    IlvMainLoop();
    return 0;
}
