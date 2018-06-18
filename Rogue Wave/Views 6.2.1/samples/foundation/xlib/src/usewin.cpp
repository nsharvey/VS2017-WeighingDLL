// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/xlib/src/usewin.cpp
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
// Drawing in a pure XWindow (Xlib version of IlogViews)
// Use xwininfo to get a WindowId
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>
#include <ilviews/graphics/inter.h>
#include <ilviews/graphics/gridrect.h>
#include <ilviews/graphics/set.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/lablist.h>
#include <ilviews/graphics/relfrect.h>
#include <ilviews/graphics/arc.h>
#include <ilviews/graphics/relflab.h>
#include <stdio.h>
#include <stdlib.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <ilviews/X11/config.h>

static const char* labels[] = {
    "label1",
    "*** big label***",
    "label3",
    "label4"
};

// --------------------------------------------------------------------------
static void
Quit(IlvContainer* cont,
     IlvEvent&,
     IlAny)
{
    delete cont->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    IlvDisplay* display = new IlvDisplay("UseWin", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Can't open Display \n");
	IlvExit(1);
    }
    unsigned long win = 0;
    if (argc > 1)
	win = strtol(argv[1], 0, 16);;
    if (!win) {
	IlvXDisplayConfig* config = display->getXConfig();
	win =  XRootWindow(config->getXDisplay(), config->getScreen());
    }
    IlvContainer* container = new IlvContainer(display,
					       (IlvSystemView)win);
    extern void IlvViewSelectEvents(IlvView*);
    IlvViewSelectEvents(container);
    //Creating objects
    IlvGraphic* obj1 = new IlvRectangle(display, IlvRect(0, 0, 100, 100));
    IlvGraphic* obj2 = new IlvFilledRectangle(display, IlvRect(10, 10, 80, 80));
    IlvGraphic* obj3 = new IlvFilledArc(display,
					IlvRect(100, 0, 100, 100), 30, 90);
    IlvGraphic* obj4 = new IlvLabel(display,
				    IlvPoint(10, 150), "This is a Label");
    IlvGraphic* obj5 = new IlvListLabel(display, IlvPoint(110, 100),
					4, (const char**)labels);
    IlvGraphic* button=new IlvReliefLabel(display, "Push Me",
					  IlvRect(110, 10, 100, 40), 0);
    IlvColor* gold=display->getColor("gold");
    if (!gold) gold=display->defaultBackground();
    button->setBackground(gold);
    IlvGraphic* gridrect = new IlvGridRectangle(display,
						IlvRect(200, 100, 100, 100),
						10, 10);
    container->addObject(gridrect);
    container->addObject(button);
    container->addObject(obj1);
    container->addObject(obj2);
    container->addObject(obj3);
    container->addObject(obj4);
    container->addObject(obj5);

    //Associates Interactors to objects
    IlvReshapeInteractor*     reshape     = new IlvReshapeInteractor();
    IlvMoveInteractor*        move        = new IlvMoveInteractor();
    IlvMoveReshapeInteractor* movereshape = new IlvMoveReshapeInteractor();

    gridrect->setInteractor(movereshape);
    obj2->setInteractor(move);
    obj3->setInteractor(movereshape);
    obj4->setInteractor(move);
    obj5->setInteractor(move);
    obj1->setInteractor(reshape);
    button->setInteractor(new IlvButtonInteractor());

    container->addAccelerator(Quit, IlvKeyUp, 'Q', 0);
    container->reDraw();
    IlvMainLoop();
    return 0;
}

