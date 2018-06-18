// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/styling/src/pick.cpp
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
// Select and apply a CSS Style Sheet to a Gadget Container
// --------------------------------------------------------------------------
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/graphics/selector.h>
#include <ilviews/css/stylesheet.h>
#include <fstream>

static const char* title = "Rogue Wave Views: Pick Style";

IlvStyleSheet* sheets[3];
static const char* sheetFilenames[3] = {
    0, // None
    "colorful.css",    // Colorful
    "highcontrast.css" // High contrast
};
// At the time of this writing, view backgrounds are not
// under the control of styling.
// We change the background color of the view using this
// color set.
static const char* bgColors[3] = {
    "grey",            // No style
    "orange",          // Colorful
    "black"            // High contrast
};
// --------------------------------------------------------------------------
static void
Quit(IlvView* top, IlAny)
{
    IlvDisplay* display = top->getDisplay();
    delete top;
    // Release all created style sheets
    for (int loop = 0; loop < 3; loop++) {
	if (sheets[loop]) {
	    sheets[loop]->unLock();
	}
    }
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
StyleSheetChanged(IlvGraphic* g, IlAny cArg)
{
    // Which style sheet should now be selected
    IlShort selected = IL_DYNAMICCAST(IlvSelector*, g)->whichSelected();
    IlvStyleSheet* sheet = sheets[selected];
    IlvGadgetContainer* container = IL_CAST(IlvGadgetContainer*, cArg);
    // Remove the last associated style sheet
    container->removeStyleSheet(0);
    container->setBackground(container->getDisplay()
				      ->getColor(bgColors[selected]));
    if (sheet) {
	// Associate the selected one
	container->addStyleSheet(sheet);
    }
    // Force a redraw to retreive new styles
    container->reDraw();
}

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    // Create the display connection
    IlvDisplay* display =  new IlvDisplay("Pick", "", argc, argv);
    if (!display || display->isBad()) {
        if (display)
	    delete display;
	IlvFatalError("Couldn't create display");
	return 1;
    }

    // Pre-load the stylesheets
    sheets[0] = 0; // The 'no-style' stylesheet...
    display->prependToPath("../data");
    for (int loop = 1; loop < 3; loop++) {
	const char* path= display->findInPath(sheetFilenames[loop]);
	IlvStyleSheet* sheet = 0;
	if (path) {
	    // Read the style sheet
	    sheet = new IlvCssStyleSheet(sheetFilenames[loop]);
	    std::ifstream stream(path);
	    sheet->read(stream);
	    // Because style sheets will be attached and detached from
	    // the container, we must lock them so they don't get deleted
	    // on the first removal.
	    sheet->lock();
	}
	sheets[loop] = sheet;
    }

    // Create the container that will hold the gadgets
    IlvGadgetContainer* container =
	new IlvGadgetContainer(display,
			       title,
			       title,
			       IlvRect(0, 0, 300, 150),
			       IlFalse,
			       IlFalse);
    container->setDestroyCallback(Quit);

    // Create the controls
    container->addObject("selectorLabel",
			 new IlvMessageLabel(display, "Select a style:",
					     IlvRect(4,  4, 80, 22)));
    IlvSelector* selector = new IlvSelector();
    IlvToggle* toggle[3];
    toggle[0] = new IlvToggle(display,
			      "None",
			      IlvRect(16, 28, 120, 16));
    selector->addObject(toggle[0]);
    selector->setSelected(toggle[0]);
    toggle[1] = new IlvToggle(display,
			      "Colorful",
			      IlvRect(16, 50, 120, 16));
    selector->addObject(toggle[1]);
    toggle[2] = new IlvToggle(display,
			      "High contrast",
			      IlvRect(16, 72, 120, 16));
    selector->addObject(toggle[2]);
    selector->setInteractor("Selector");
    selector->setCallback(StyleSheetChanged, container);
    container->addObject(selector);
    container->addObject("button1",
			 new IlvButton(display, "Button 1",
				       IlvRect(210,  8, 82, 24)));
    container->addObject("button2",
			 new IlvButton(display, "Button 2",
				       IlvRect(210, 40, 82, 24)));
    container->addObject("textfield",
			 new IlvTextField(display, "Some text entry control",
					  IlvRect(8, 120, 282, 20)));

    container->show();
    IlvMainLoop();
    return 0;
}
