// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/i18n/src/controlinput.cpp
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
// Sample to show how to control localized input.
// --------------------------------------------------------------------------

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/button.h>

// -------------------------------------------------------------------------
static void 
QuitCB(IlvGraphic* g,
       IlAny)
{
    IlvDisplay* display = g->getHolder()->getDisplay();
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
DestroyView(IlvView* top,
	    IlAny)
{
    IlvDisplay* display = top->getDisplay();
    delete top;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
int
main (int argc,
      char* argv[])
{
    if (!IlvSetLocale())
	IlvPrint("Falling back to the C locale.");
    
    IlvDisplay* display = new IlvDisplay("Control Input", 0, argc, argv);

    if (display->isBad()) {
	delete display;
	IlvFatalError("Couldn't create display");
	IlvExit(-1);
    }

    IlvRect rect(50,50,420,250);
    
    IlvGadgetContainer* cont = 
	new IlvGadgetContainer(display, "Control Input",
			       "Control Input", rect, IlFalse);
    // set the destroy callback to quit the window from the window manager.
    cont->setDestroyCallback(DestroyView);
    
    IlvRect rect1(10, 10, 400, 50);
    IlvColor* color = display->getColor("yellow");
    IlvPalette* pal1 = new IlvPalette(display);
    pal1->setBackground(color);
    
    IlvTextField* tf1 = 
	new IlvTextField(display, 
			 "This text field should accept localized input.", 
			 rect1, 2, pal1);
    tf1->setAlignment(IlvCenter);
    
    rect1.y(80);
    color = display->getColor("red");
    IlvPalette* pal2 = new IlvPalette(display);
    pal2->setBackground(color);

    IlvTextField* tf2 = 
	new IlvTextField(display,
			 "This text field should NOT accept localized input.", 
			 rect1, 0, pal2);
    tf2->setAlignment(IlvCenter);
    // set this object so that it does not connect to an Input Method.
    tf2->setNeedsInputContext(IlvFalse);

    IlvButton* but = new IlvButton(display, IlvPoint(170, 170), "Quit");
    but->setCallback(QuitCB, (IlAny)0);
    
    cont->addObject(tf1);
    cont->addObject(tf2);
    cont->addObject(but);

    IlvMainLoop();
    return 0;
}
