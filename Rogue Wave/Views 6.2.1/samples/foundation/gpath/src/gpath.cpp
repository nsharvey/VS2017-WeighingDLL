// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/gpath/src/gpath.cpp
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
// Demonstrating the IlvGraphicPath object
// --------------------------------------------------------------------------

#if defined(IL_STD)
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <ilviews/contain/contain.h>
#include <ilviews/graphics/path.h>
#include <ilviews/base/ptarray.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/graphics/set.h>
#include <ilviews/graphics/handle.h>
#include <ilviews/base/timer.h>
#include <ilviews/base/pathname.h>

static IlvTimer*              timer      = 0;
static IlvGraphicPath*        trajectory = 0;
static IlvTransformedGraphic* stringPath = 0;
static IlvTransformedGraphic* mobile     = 0;

// --------------------------------------------------------------------------
static void
SetTransform(IlvGraphic* obj, IlAny t)
{
    ((IlvTransformedGraphic*)obj)->setTransformer(*(IlvTransformer*)t);
}

// --------------------------------------------------------------------------
static IlvTransformer rotation;
static void
SetRotation(const IlvPoint& center, IlFloat angle)
{
    rotation.setValues((IlFloat)1, (IlFloat)0,
		       (IlFloat)0, (IlFloat)1,
		       (IlFloat)0, (IlFloat)0);
    rotation.rotate((IlFloat)center.x(), (IlFloat)center.y(), angle);
}

// --------------------------------------------------------------------------
static void
PredefinedRotation(IlvGraphic* obj, IlAny)
{
    obj->applyTransform(&rotation);
}

// --------------------------------------------------------------------------
static void
MoveMobile(IlvContainer*          container,
	   IlvGraphicPath*        gpath,
	   IlvTransformedGraphic* tobj)
{
#define INCREMENT 10
    static IlDouble length = 1.; // not 0.;
    IlvPoint  pos;
    IlDouble angle;
    IlDouble gpathLength = gpath->getLocation(gpath->getNumPaths(),
					      gpath->getPaths(), length,
					      &pos, &angle);
    if (gpathLength > 0.) {
	// failure : length is longer than the total length of
	// the path (returned by getLocation).
	if (length > gpathLength)
	    length = ((IlInt)length) % (IlInt)gpathLength;
	if (length == 0.)
	    length = gpathLength;
	gpathLength = gpath->getLocation(gpath->getNumPaths(),
					 gpath->getPaths(), length,
					 &pos, &angle);
	// should not fail this time
	if (gpathLength > 0.) {
	    IlvWarning("MoveMobile: cannot get point location");
	    length += INCREMENT;
	    return;
	}
    }

    IlvTransformer t;
    if (angle)
	t.rotate((IlFloat)0, (IlFloat)0, (IlFloat)angle);
    t.translate((IlFloat)pos.x(), (IlFloat)pos.y());
    container->applyToObject(tobj, SetTransform, &t, IlTrue);
    length += INCREMENT;
}

// --------------------------------------------------------------------------
// Timer callback
// --------------------------------------------------------------------------
static void
TimerProc(IlvTimer*, IlAny userArg)
{
    IlvContainer* container = IL_CAST(IlvContainer*, userArg);
    MoveMobile(container, trajectory, mobile);
    container->applyToObject(stringPath, PredefinedRotation, 0, IlTrue);
}

// --------------------------------------------------------------------------
// Accelerators and callbacks
// --------------------------------------------------------------------------
static void
StartStop(IlvContainer* container, IlvEvent&, IlAny)
{
    if (timer) {
	timer->suspend();
	delete timer;
	timer = 0;
    } else {
	// Initialize the rotation transformer
	IlvRect bbox;
	stringPath->boundingBox(bbox);
	SetRotation(bbox.center(), (IlFloat)6);
	if (!timer)
	    timer = new IlvTimer(container->getDisplay(),
				 0, 20,
				 TimerProc, (IlAny)container);
	timer->run();
    }
}

// --------------------------------------------------------------------------
static void
Quit(IlvView* view, IlAny)
{
   if (timer)
       timer->suspend();
   delete timer;
   delete view->getDisplay();
   IlvExit(0);
}

// --------------------------------------------------------------------------
static const char title[] = "Rogue Wave Views sample: gpath";
int
main(int argc, char* argv[])
{
    IlvDisplay* display = new IlvDisplay("GPath", "", argc, argv);
    if (display->isBad()) {
	delete display;
	IlvFatalError("Couldn't create display");
	exit(-1);
    }
    // Add the sample directory to the display path
    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/foundation/gpath");
    display->prependToPath(localPath);
    IlvContainer* container = new IlvContainer(display,
					       title,
					       title,
					       IlvRect(0, 0, 800, 800),
					       IlTrue, IlFalse);
    container->setDestroyCallback(Quit);
    container->readFile("data/gpath.ilv");

    trajectory = (IlvGraphicPath*)container->getObject("path");
    stringPath = (IlvTransformedGraphic*)container->getObject("VIEWS");
    mobile     = (IlvTransformedGraphic*)container->getObject("mobile");
    if (! (trajectory && stringPath && mobile)) {
	IlvWarning("Object %s not found",
		   trajectory ? (stringPath ? "mobile" : "VIEWS") : "path");
	Quit(container, 0); // exit;
    }

    container->addAccelerator(StartStop,  IlvKeyUp, ' ', 0, 0);
    container->setDoubleBuffering(IlTrue);
    container->show();

    IlvMainLoop();
    return 0;
}
