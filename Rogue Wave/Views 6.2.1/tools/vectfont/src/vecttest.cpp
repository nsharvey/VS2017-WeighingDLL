// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/src/vecttest.cpp
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
// Testing the Rogue Wave Views vectorial fonts
// --------------------------------------------------------------------------

#include <vfincl/vect.h>
#include <vfincl/vectlab.h>

#include <ilviews/contain/contain.h>
#include <ilviews/contain/inter.h>
#include <ilviews/graphics/rectangl.h>
extern "C"  IlvVirtualVectFont* IlvVirtualVectFont_romans();

// --------------------------------------------------------------------------
static void
Quit(IlvView* v, IlvAny)
{
    delete v->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
Quit(IlvContainer* container, IlvEvent&, IlvAny arg)
{
    Quit(container, arg);
    IlvExit(0);
}

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvDisplay* display = new IlvDisplay("Demo", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Can't open display \n");
	if (display)
	    delete display;
	return 1;
    }
    IlvVirtualVectFont* vfont = IlvVirtualVectFont_romans();
    if (!vfont) {
	IlvFatalError("Virtual vectorial font \"romans\" not loaded\n");
	delete display;
	return 1;
    }
    IlvRect size(0, 0, 200, 200);
    IlvContainer* container =
	new IlvContainer(display, "VectTest", "VectTest", size);
    container->addAccelerator(Quit, IlvKeyUp, 'Q');
    container->setDestroyCallback(Quit);

    IlvRectangle* rect = new IlvRectangle(display, IlvRect(10, 110, 40, 40));
    container->addObject(rect);

    IlvVectFont* f1 = new IlvVectFont(vfont, 40, 40, IlvFloat(0), IlvFloat(0));
    IlvVectFont* f2 = new IlvVectFont(vfont, 30, 30, IlvFloat(30), IlvFloat(0));
    IlvVectLabel* obj1 = new IlvVectLabel(display, f1, IlvPoint(10, 150),
					  "ABCD 01234 qwerty");
    IlvVectLabel* obj2 = new IlvVectLabel(display, f2, IlvPoint(100, 250),
					  "ABCD 01234 qwerty");

    container->addObject(obj1);
    container->addObject(obj2);
    IlvViewReshapeInteractor* reshapedecoder= new IlvViewReshapeInteractor();
    container->setObjectInteractor(obj1, reshapedecoder);
    container->setObjectInteractor(obj2, reshapedecoder);

    IlvMainLoop();

    return 0;
}
