// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/protos/tutorial2/step3/program.cpp
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
// Using the prototypes
// --------------------------------------------------------------------------

#include <ilviews/manager/all.h>
#include <ilviews/protos/proto.h>
#include <ilviews/protos/protogr.h>
#include <ilviews/protos/groupholder.h>
#include <ilviews/protos/grouplin.h>

#include <ilviews/graphics/all.h>
#include <ilviews/protos/allaccs.h>
#include <ilviews/gadgets/msglabel.h>

// The application object for which we want to create a user interface.

#if defined(ILVSTD)
#include <cmath>
ILVSTDUSE
#else
#include <math.h>
#endif

// --------------------------------------------------------------------------
struct Thermometer {
    IlFloat temperature;
    IlUInt acceleration;
    IlUInt curval;
    IlvTimer timer;
    // the display argument is here just to allow using a Views timer.
    Thermometer(IlvDisplay*);
    ~Thermometer() {}
    void adjust_temp();   
    static void TimerProc(IlvTimer*, IlAny);
};

// --------------------------------------------------------------------------
Thermometer::Thermometer(IlvDisplay* dpy)
    :temperature(20), acceleration(4), curval(0), 
     timer(dpy, 0, 200, TimerProc, this)
{
    timer.run();
}

// --------------------------------------------------------------------------
void
Thermometer::adjust_temp()
{
    temperature =
	(IlFloat)(50.0 + (40.0 * sin(IlvDegreesToRadians((IlDouble)curval))));
    curval = (curval + acceleration) % 360;
}

// --------------------------------------------------------------------------
void
Thermometer::TimerProc(IlvTimer*, IlAny arg)
{
    ((Thermometer*)arg)->adjust_temp();
}

// --------------------------------------------------------------------------
// create a mediator that will handle exchange between the application
// object and the panel, by means of IlvGroup objects.

struct TemperatureWatcher: public IlvGroupMediator 
{
    TemperatureWatcher(IlvGroup* g, Thermometer* a)
    	: IlvGroupMediator(g, a) 
    {
	if (!tempSymbol) tempSymbol=IlGetSymbol("temperature");
	if (!accSymbol) accSymbol=IlGetSymbol("acceleration");
    }
    IlBoolean changeValues(const IlvValue*, IlUShort);
    void queryValues(IlvValue*, IlUShort) const;
    inline Thermometer* getThermometer() const { 
	return (Thermometer*) getObject(); }
    static IlSymbol* tempSymbol;
    static IlSymbol* accSymbol;
};

// --------------------------------------------------------------------------
IlSymbol* TemperatureWatcher::tempSymbol;
IlSymbol* TemperatureWatcher::accSymbol;

// --------------------------------------------------------------------------
// method handling with user input and updating the application.
IlBoolean 
TemperatureWatcher::changeValues(const IlvValue* v, IlUShort n)
{
    if(locked()) return IlFalse;
    for (IlUInt i=0;i<n;i++) {
	if (v[i].getName() == accSymbol)
	    getThermometer()->acceleration = (IlUInt) v[i];
	// here, we do not want the temperature value to be
	// editable by the user.
	// if we wanted to, we'd just have to add the following code.
	//	 else if (v[i].getName() == tempSymbol)
	//	     getThermometer()->temperature = (IlFloat) v[i];
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
// method that synchronizes the group to the application values.
void
TemperatureWatcher::queryValues(IlvValue* v, IlUShort n) const
{
    for (IlUInt i=0;i<n;i++) {
	if (v[i].getName() == tempSymbol)
   	    v[i]= getThermometer()->temperature;
	else if (v[i].getName() == accSymbol)
	    v[i]= getThermometer()->acceleration;
    }
}

// --------------------------------------------------------------------------
static void
TimerProc(IlvTimer*, IlAny arg)
{
    TemperatureWatcher* watcher=(TemperatureWatcher*) arg;
    // synchronize the display to the new application values
#if !defined(OPTIMIZE)
    watcher->update();
#else
    // if we're sure that the application has only changed a few values
    // and we know those, we can pass only those values that have changed.
    watcher->update(& TemperatureWatcher::tempSymbol, 1);
    // we might also extend the Thermometer object to notify
    // or set some flags when its values are changed so that
    // it uses an observer/observable mechanism instead of periodic updates.
    // finally, another optimization might consist in storing the current 
    // value of the temperature, and calling update() only if this
    // value is different from the stored one.
#endif
}

// --------------------------------------------------------------------------
static void
Quit(IlvView* view, IlAny)
{
    IlvDisplay* display = view->getDisplay();
    delete view;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    // Connect to the display system ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    IlvDisplay* display = new IlvDisplay("Protos", 0, argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Couldn't open display");
	return -1;
    }  
    // create and initialize an application object.
    Thermometer appObject(display);
    
    // Prepare a window and a manager to display a scene ~~~~~~~~~~~~~~~~~~
    IlvManager* manager = new IlvManager(display);
    IlvView* view = new IlvView(display, "BGO tutorial 3", "BGO tutorial 3",
				IlvRect(0, 0, 400, 300));
    manager->addView(view);
    // Load a data file into the manager ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    IlString buf (getenv("ILVHOME"));
    buf +="/doc/tutorials/protos/tutorial2/step3";
    display->appendToPath(buf);
    display->appendToPath("..");
    manager->read("myPanel.ilv");
    
    // find the group we want to feed with values ~~~~~~~~~~~~~~~~~~~~~~~~~
    IlvGroupHolder* holder=IlvGroupHolder::Get(manager);
    IlvGroup* tempRep = holder->getGroup("myThermometer");  
    if (!tempRep) {
	IlvFatalError("This sample expects to find an IlvGroup "
		      "of name \"myThermometer\" in the file \"myPanel.ilv\"");
	return -1;
    }
    // install a connection between this group and the rest of the application
    TemperatureWatcher watch(tempRep, &appObject);
    watch.update();
    // start observing the application ~~~~~~~~~~~~~~~~
    IlvTimer timer(display, 0, 200, TimerProc, (IlAny)&watch);
    timer.run();
    // display the scene and run the application ~~~~~~~~~~~~~~~~~~~~~~~~~~
    view->setDestroyCallback(Quit);
    manager->setDoubleBuffering(view, IlTrue);
    view->show();
    IlvMainLoop();
    return 0;
}
