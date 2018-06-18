// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/interact_synoptic/src/plane.cpp
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

// The User interface of the ATC application: for each object
// of the domain (airports and flights), we create a prototype
// instance that implements the UI for that given object.

#include <ilviews/base/string.h>
#include <ilviews/base/view.h>
#include <ilviews/graphics/inter.h>
#include <ilviews/graphics/all.h>
#include <ilviews/gadgets/slider.h>
#include <ilviews/manager/manager.h>
#include <ilviews/manager/objinter.h>
#include <ilog/pathname.h>

#include <ilviews/protos/allaccs.h>
#include <ilviews/protos/group.h>
#include <ilviews/protos/groupholder.h>
#include <ilviews/protos/protogr.h>
#include <ilviews/protos/grouplin.h>

#if defined(IL_STD)
IL_STDUSE;
#include <cstdlib> // for srand() and rand() and getenv()
#include <ctime>  // for time()
#include <cmath>
#include <iostream>
#include <fstream>
#else  /* !IL_STD */
#include <stdlib.h> // for srand() and rand() and getenv()
#include <time.h> // for time()
#include <math.h>
#include <iostream.h>
#include <fstream.h>
#endif /* !IL_STD */

#include <atc.h>

#define FLIGHTFILE "easy_atc.txt"
#define AIRPORT_PROTO "atc.airport"
#define FLIGHT_PROTO "atc.plane"

// ------------------------------------------------------------------------
// the link between the application and the UI: an IlvProtoMediator
// instanciates a Prototype and links it to a given application
// object: here an airport...
struct AirportUI : public IlvProtoMediator
{
    AirportUI(IlvManager* m,
	      Airport* a)
        : IlvProtoMediator(m->getDisplay(), AIRPORT_PROTO, a)
    {
	IlvGroup* pres = getPresentation();
	if (!pres)
	    return;
	update(); // update the UI from application's data.
	install(m); // place the object in the manager
    }

    inline Airport* airport() const {
        return (Airport*)getObject();
    }

    IlBoolean changeValues(const IlvValue*,
			   IlUShort)
    { return IlTrue; }

    void queryValues(IlvValue* values,
		     IlUShort n) const
    {
	Airport* a = airport();
	for (IlUInt i = 0; i < n ; i++) {
#define DO_VALUE(N,V) \
    if (!strcmp(values[i].getName()->name(), N)) values[i] = a->V;
	    DO_VALUE("Name", name->name());
	    DO_VALUE("PosX", position.x());
	    DO_VALUE("PosY", position.y());
	}
    }
};

// ------------------------------------------------------------------------
// ...and here a flight. The changeValues and queryValues members
// are in charge of transfering changed values from the UI
// to the application object and vice-versa.
struct FlightUI : public IlvProtoMediator, public Observer
{
    FlightUI(IlvManager* m,
	     Flight* f)
        : IlvProtoMediator(m->getDisplay(), FLIGHT_PROTO, f),
	  Observer()
    {
	f->add_observer(this);
	IlvGroup* pres = getPresentation();
	if (!pres)
	    return;
	update();
	install(m);
    }

    inline Flight* flight() const
    { return (Flight*)getObject(); }

    IlBoolean changeValues(const IlvValue* values,
			   IlUShort n)
    {
	if (locked())
	    return IlTrue;
	Flight* f = flight();
	for (IlUInt i = 0; i < n ; i++) {
#define PUT_VALUE(N,A)\
     if (!strcmp(values[i].getName()->name(), N)) f->A = (IlFloat)values[i];
	    PUT_VALUE("PosX", position._x);
	    PUT_VALUE("PosY", position._y);
	    PUT_VALUE("Altitude", altitude);
	    PUT_VALUE("Speed", speed);
	    PUT_VALUE("Direction", direction);
	    PUT_VALUE("Departure", departure);
	}
	lock();
	f->notify();
	unlock();
	return IlTrue;
    }

    void queryValues(IlvValue* values,
		     IlUShort n) const
    {
	Flight* f = flight();
	for (IlUInt i = 0; i < n ; i++) {
#define SET_VALUE(N, V)    \
	if (!strcmp(values[i].getName()->name(), N)) values[i] = f->V;
	    SET_VALUE("Name", label->name());
	    SET_VALUE("PosX", position.x());
	    SET_VALUE("PosY", position.y());
	    SET_VALUE("Altitude", altitude);
	    SET_VALUE("Speed", speed);
	    SET_VALUE("Direction", direction);
	    SET_VALUE("Departure", departure);
	}
    }

    void update_obs (Observable* o,
		     IlAny)
    {
	if (o == flight()) {
	    // we could optimize update, as we know that
	    // only those attributes are actually modified by the application:
	    // const IlvSymbol** symblist = {IlvGetSymbol("PosY"), IlvGetSymbol("PosX") }
	    //	     update(symblist, 2);
	    update();
       }
    }
};

// ------------------------------------------------------------------------
// the ATC_UI structures is in charge of handling the UI for a whole
// scene of flights and airports: given an 'ATC' object, it will
// create a manager for it and create as many 'ProtoMediator' as
// needed to represent the ATC structure.

struct ATC_UI : public IlvManager
{
    ATC app; // in a real application, this would be a pointer
             // to the application context...
    IlvTimer* timer;
    IlUInt period;

    ATC_UI (IlvDisplay* d,
	    const char* flight_plans,
	    IlUInt p = 100)
        : IlvManager(d),
	  app(),
	  timer(0),
	  period(p)
    {
	ifstream in (d->findInPath(flight_plans));
	if (!in.bad())
	    app.load(in);
	else {
	    IlvFatalError("Usage: plane [filename]\n where filename "
			  "defaults to "
			  FLIGHTFILE);
	}
	Airport* a;
	Flight* f;
	IlvMapAListValue(&(app.airports),
			 Airport*,
			 a,
			 new AirportUI(this, a););
	IlvMapList(&(app.flights), Flight*, f, new FlightUI(this, f););
    }

    static void ticks(IlvTimer*,
		      IlAny me)
    {
	((ATC_UI*)me)->app.timer_tick();
    }

    void start()
    {
	if (timer)
	    delete timer;
	timer = new IlvTimer(getDisplay(),
			     (int)(IlInt)(period / 1000),
			     (int)(IlInt)(period % 1000),
			     ticks,
			     this);
	app.start();
	timer->run();
    }

    void stop()
    {
        delete timer;
	timer = 0;
    }
};

// ------------------------------------------------------------------------
// main program. Reduced to a strict minimum for demo purposes.
// ------------------------------------------------------------------------
static void
DestroyView(IlvView* view,
	    IlAny)
{
    delete view->getDisplay();
    IlvExit(0);
}

// ------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay("PrototypeSample", "", argc, argv);
    if (!display || display->isBad()) {
    	IlvFatalError("Couldn't open display");
	if (display)
	    delete display;
    	return 1;
    }
    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/protos/interact_synoptic/data");
    display->prependToPath(localPath);
    
    // Create the prototype manager.
    ATC_UI ui(display,
	      (argc > 1) ? argv[1] : FLIGHTFILE);

    // Create a toplevel view and add it to the manager.
    IlvView* view = new IlvView(display,
				"PrototypeSample",
				"Prototypes Sample (ATC)",
				IlvRect(20, 100, 580, 600),
				IlTrue, IlFalse);
    view->setDestroyCallback(DestroyView);
    view->setBackground(display->getColor((IlFloat)0.,
					  (IlFloat)0.,
					  (IlFloat).3));
    ui.addView(view);
    // Show panel and run event loop.
    view->show();
    ui.setDoubleBuffering(view, IlTrue);
    ui.start();
    IlvMainLoop();
    return 0;
}
