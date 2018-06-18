// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/windows/src/ilvmdi.cpp
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
// Demonstrationg the MDI support in Rogue Wave Views
// --------------------------------------------------------------------------

#include <windows.h>
#include <ilviews/contain/contain.h>
#include <ilviews/graphics/all.h>

// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny)
{
    delete view->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay("IlvMDI", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Couldn't create display");
	if (display)
	    delete display;
	return 1;
    }
    IlvView* view = new IlvView(display,
				"MDI Parent",
				"MDI Parent",
				IlvRect(0, 0, 600, 480),
				IlFalse);
    IlvContainer* cont1 = new IlvContainer(display,
					   "Child 1",
					   "Child 1",
					   IlvRect(0, 0, 300, 150),
					   IlvMDIChild,
					   IlTrue,
					   IlTrue,
					   view->getSystemView());
    cont1->readFile("tiger2.ilv");
    IlvContainer* cont2 = new IlvContainer(display,
					   "Child 2",
					   "Child 2",
					   IlvRect(100, 100, 300, 150),
					   IlvMDIChild,
					   IlTrue,
					   IlTrue,
					   view->getSystemView());
    cont2->readFile("elefante.ilv");
    view->setDestroyCallback(Quit);
    view->show();
    IlvMainLoop();
    return 0;
}
