// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/manager/hook/src/scalemgr.cpp
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

#if defined(IL_STD)
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <ilviews/graphics/all.h>
#include <ilviews/manager/manager.h>
#include <ilviews/graphics/marker.h>

#include "scalehk.h"

// --------------------------------------------------------------------------
static char title[] = "Manager hooks and scales";

// --------------------------------------------------------------------------
static void
Quit(IlvView* top,
     IlAny mgr)
{
    delete (IlvManager*)mgr;
    delete top->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display =
	new IlvDisplay("ManagerHooksAndScales", "", argc, argv);
    if (!display || display->isBad()) {
        if (display) 
	    delete display;
	IlvFatalError("Couldn't create display");
	exit(-1);
    }

    IlvView* topView = new IlvElasticView(display,
					  title,
					  title,
					  IlvRect(0, 0, 500, 500),
					  IlFalse);
    topView->setDestroyCallback(Quit);

    // Create a sub window and a new manager;
    IlvView* subView = new IlvView(topView,
				   IlvRect(100, 100, 300, 300),
				   IlTrue);
    IlvColor* bgColor = display->getColor("lightblue");
    if (bgColor)
 	subView->setBackground(bgColor);
    IlvManager* subMgr = new IlvManager(display);
    subMgr->removeAccelerator(IlvKeyDown, 'R'); // remove rotate accelerator

    subMgr->addView(subView);
    subMgr->read("africa.ilv");

    // Create a scale view hook to trap the transformer changes in subView
    // and manage the scales;
    Ilv4ScaleHook* scaleHook = new Ilv4ScaleHook(subMgr, subView, topView);
    subMgr->installViewHook(scaleHook);
    scaleHook->getSManager()->addObject(new IlvMarker(display,
					              IlvPoint(0, 0)));
    subMgr->addObject(new IlvMarker(display, IlvPoint(0, 0)));
    scaleHook->getSManager()->addObject(new IlvMarker(display,
						      IlvPoint(0, 200)));
    scaleHook->getSManager()->addObject(new IlvMarker(display,
						      IlvPoint(200, 0)));
    subMgr->addObject(new IlvMarker(display, IlvPoint(200, 200)));

    // The map is large. With transformer = identity, the only visible thing
    // is an empty piece of the Atlantic Ocean... Unzoom a little bit.
    IlvTransformer t((IlFloat)0.4, (IlFloat)0, (IlFloat)0, (IlFloat)0.4,
		     (IlFloat)0, (IlFloat)0);
    subMgr->setTransformer(subView, &t);

    subMgr->setDoubleBuffering(subView, IlTrue);
    subView->setFocus(); // Otherwise, click on the map to get the focus.

    topView->show();
    IlvMainLoop();
    return 0;
}
