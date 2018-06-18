// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/synoptic/src/ui.cpp
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
// The factory sample:  a synoptic builder and simulator.
//
// Files: arkola.ipl (library), arkola.ilv (panel used by default)
//        synoptic.h, synoptic.cpp: the simulator code
//        ui.cpp : the main loop and UI/Application link
// See ../index.html for synopsis and guide.
// --------------------------------------------------------------------------

#include <ilviews/base/string.h>
#include <ilviews/base/error.h>
#include <ilviews/base/view.h>
#include <ilviews/graphics/inter.h>
#include <ilviews/graphics/all.h>

#include <ilviews/gadgets/toggle.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/slider.h>

#include <ilviews/protos/allaccs.h>
#include <ilviews/protos/group.h>
#include <ilviews/protos/grouplin.h>
#include <ilviews/protos/groupholder.h>
#include <ilviews/protos/protogr.h>
#include <ilviews/protos/valuesrc.h> // for the clock protos.

#if defined(IL_STD)
#include <cstdlib> // for srand() and rand()
#include <cmath>
#include <iostream>
#if defined(WINDOWS)
#include <fstream>
#endif /* WINDOWS */
IL_STDUSE;
#else  /* !IL_STD */
#include <stdlib.h> // for srand() and rand() and getenv()
#include <math.h>
#include <iostream.h>
#if defined(WINDOWS)
#include <fstream.h>
#endif /* WINDOWS */
#endif /* !IL_STD */

#include <synoptic.h>

#define DATAFILE "arkola.ilv"

// The Machine UI class makes the link between a presentation object
// (an IlvGroup) and its internal representation in the application
// (a Machine).

struct MachineUI
  : public IlvGroupMediator, Observer
{
    MachineUI(Machine* f,
	      IlvGroup* g);
    // ____________________________________________________________
    void make_links();
    inline Machine* machine() const
    { return (Machine*)getObject(); }
    // overloaded members:
    void update_obs (Observable*,
		     IlAny = 0);
    IlBoolean changeValues(const IlvValue*,
			   IlUShort);
    void queryValues(IlvValue*,
		     IlUShort) const;
};

// --------------------------------------------------------------------------
MachineUI::MachineUI(Machine* f,
		     IlvGroup* g)
    : IlvGroupMediator(g, f),
      Observer()
{
    f->add_observer(this);

    // Move all instance values to object values...
    // in a real application, when the interface is build
    // from the application data and not vice-versa, calling update()
    // is sufficient.
    IlvUInt cnt;
    const IlvSymbol** symbs;
    const IlvValueTypeClass** types;

    // Get all the public value names of our presentation
    g->getAccessorList(symbs, types, cnt, IlFalse, IlFalse);
    IlvValue* vals = new IlvValue [cnt];
    for (IlUInt i = 0; i < cnt; i++)
	vals[i]=IlvValue(symbs[i]->name());
    // Get exported values from instance
    g->queryValues(vals, (IlUShort)cnt);
    // Load them in the machine
    changeValues(vals, (IlUShort)cnt);
    delete [] vals;
}

// --------------------------------------------------------------------------
void
MachineUI::make_links()
{
    // find from the connections between prototypes where
    // goes the production of each machine.
    IlvAccessible** sources = 0;
    IlvSymbol** sv   = 0,
	     ** subV = 0;
    IlvValueTypeClass** types = 0;
    IlvValueSubscriptionMode* modes = 0;
    IlUInt cnt = getPresentation()->getSubscriptions(0, sv, subV, types,
						     modes, &sources);
    Machine* from = machine();
    for (IlUInt i = 0; i < cnt; i++) {
	// for each link that looks like one of ours we
	// link the machines together.
        if ((sv[i] != IlvGetSymbol("Output")) ||
	    (subV[i] != IlvGetSymbol("Input")))
	    continue;
	Machine* to = from->factory->find(sources[i]->getName());
	if (to) {
	    if (!strcmp(from->cname, "Producer")) {
		// Producers have an output connection toward a container
		Producer* p = (Producer*)from;
		p->output = (Container*)to;
	    } else
	    if (!strcmp(to->cname, "Mixer") ||
		!strcmp(to->cname, "Factory")) {
		// Mixers have several input connections from containers
		Mixer* to2 = (Mixer*)to;
		IlvValue rate ("Output", (IlFloat)0);
		getPresentation()->queryValue(rate);
		to2->add_input((Container*)from, (IlFloat)rate);
	    }
	}
    }
    if (sv)
	delete [] sv;
    if (subV)
	delete [] subV;
    if (types)
	delete [] types;
    if (modes)
	delete [] modes;
    if (sources)
	delete [] sources;
}

// --------------------------------------------------------------------------
IlBoolean
MachineUI::changeValues(const IlvValue* values,
			IlUShort n)
{
#define DO_VALUE(N, A) if (!strcmp(values[i].getName()->name(), N)){ A;}
#define PUT_VALUE(N, A) DO_VALUE(N, f->A = values[i])

    if (locked())
	return IlTrue;
    Container* f = (Container*)machine();
    for (IlUInt i = 0; i < n ; i++) {
	// machine fields
	DO_VALUE("Name", f->setName((const char*)values[i]));
	PUT_VALUE("Broken", broken);
	DO_VALUE("Running", f->run((IlvBoolean)values[i]));
	DO_VALUE("Repair", f->repair());
	// container fields
	PUT_VALUE("Capacity", capacity);
	PUT_VALUE("Level", level);
	//  DO_VALUE("Output", {}); // nothing for now.
	// should change the Mixer to which the container points...
	if (!strcmp(f->cname, "Producer")) {
	    // producer fields
	    DO_VALUE("Rate",
		     ((Producer*)f)->set_rate(ILVCAST(IlFloat, values[i])/
					      ILVCAST(IlFloat, 4.0)));
	    DO_VALUE("Cost",((Producer*)f)->cost = values[i]);
	    DO_VALUE("Refill",((Producer*)f)->refill());
	} else
	if (!strcmp(f->cname, "Mixer") || !strcmp(f->cname, "Factory")) {
	    // mixer fields
	    DO_VALUE("Rate", ((Mixer*)f)->set_rate(values[i]));
	    DO_VALUE("Production", ((Mixer*)f)->production = values[i]);
	    // DO_VALUE("Spill"); nothing to change: this is to notify UI
	    if (!strcmp(f->cname, "Factory")) {
		// factory fields
		DO_VALUE("Action", ((Factory*)f)->action());
		DO_VALUE("RandBreak", ((Factory*)f)->rand_break = values[i]);
	    }
	}
    }
    lock();
    f->notify();
    unlock();
    return IlTrue;
}

// --------------------------------------------------------------------------
void
MachineUI::queryValues(IlvValue* values,
		       IlUShort n) const
{
    Container* f = (Container*)machine();
    for (IlUInt i = 0; i < n ; i++) {
#define SET_VALUE(N, F, V) \
        if (!strcmp(values[i].getName()->name(), N)) { values[i] = F->V;}
	// machine fields
	SET_VALUE("Name", f, name);
	SET_VALUE("Broken", f, broken);
	SET_VALUE("Running", f, running);
	// container fields
	SET_VALUE("Capacity", f, capacity);
	SET_VALUE("Level", f, level);
	// producer fields
	if (!strcmp(f->cname, "Producer")) {
	    SET_VALUE("Rate", ((Producer*)f), rate * 4.0);
	    SET_VALUE("Cost", ((Producer*)f), cost);
	} else
	if (!strcmp(f->cname, "Mixer") ||
	    !strcmp(f->cname, "Factory")) {
	    // mixer fields
	    SET_VALUE("Rate", ((Mixer*)f), rate);
	    SET_VALUE("Production", ((Mixer*)f), production);
	    SET_VALUE("Spill", ((Mixer*)f), spill);
	    if (!strcmp(f->cname, "Factory")) {
		// factory fields
		// Action field is used to trigger the action, not
		// get a value
		SET_VALUE("RandBreak", ((Factory*)f), rand_break);
	    }
	}
    }
}

// --------------------------------------------------------------------------
void
MachineUI::update_obs (Observable*,
		       IlAny arg)
{
    const IlvSymbol* s = arg ? IlvGetSymbol((const char*)arg) : 0;
    if (s)
	update(&s, 1);
    else
	update();
}

// --------------------------------------------------------------------------
struct FactoryUI
    : public IlvManager
{
    Factory factory;

    FactoryUI(IlvDisplay* d,
	      const char* file)
        : IlvManager(d), factory()
    {
	read(file);
	// Note: we have chosen to build the Factory
	// from the UI instead of the opposite: this
	// allows using PrStudio as an Application builder.
	// while this is convenient for demo purposes,
	// it is a bit unrealistic from a software engineering perspective.
	IlUInt cnt=0;
	IlvGroupHolder* holder=IlvGroupHolder::Get(this);
	IlvGroup** groups = holder->getGroups(cnt);
	if (groups) {
	    IlList machines;
	    // make a machine for each proto instance.
	    for (IlUInt i = 0; i < cnt; i++) {
		if (!groups[i]->isSubtypeOf(IlvProtoInstance::ClassInfo()))
		    continue;
		IlvProtoInstance* p = (IlvProtoInstance*)groups[i];
		if (!p)
		    continue;
		const char* cname = p->getPrototype()->getName();
		Machine* m = 0;
		if (!strcmp(cname, "Container"))
		    m = new Container(&factory, p->getName());
		else
		if (!strcmp(cname, "Producer"))
		    m = new Producer(&factory, p->getName());
		else
		if (!strcmp(cname, "Mixer"))
		    m = new Mixer(&factory, p->getName());
		else
		if (!strcmp(cname, "Factory"))
		    m = &factory;
		if (m) {
		    factory.machines.append(m);
		    machines.append(new MachineUI(m, p));
		}
	    }
	    // now, for each machineUI, we build the links from the connections
	    // note that connections are not used here to transmit actual
	    // values, as these will be done by the application kernel.
	    MachineUI* m;
	    IlvMapList(&machines, MachineUI*, m, m->make_links());
	    delete groups;
	}
    }
};

// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny)
{
    delete view->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Entry Point
int
main(int argc,
     char* argv[])
{
    IlvDisplay*  display = new IlvDisplay("PrototypeSample", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Couldn't open display");
	if (display)
	    delete display;
	return -1;
    }
    // The prototype and panel data files are located in the
    // parent directory, so add it to the display's path.
    IlString buf(getenv("ILVHOME"));
    buf += "/samples/protos/synoptic/data";
    display->prependToPath(buf);
    
    // Create the application
    FactoryUI app(display, (argc > 1) ? argv[1] : DATAFILE);

    // Create a toplevel view and add it to the manager.
    IlvView* view = new IlvView(display,
				"PrototypeSample",
				"Prototypes Sample (Arkola Inc.)",
				IlvRect(20, 100, 580, 400),
				IlTrue, IlFalse);
    view->setDestroyCallback(Quit);
    app.addView(view);
    app.fitToContents(view);
    app.fitTransformerToContents(view);
    app.setDoubleBuffering(view, IlTrue);

    // Show panel and run event loop.
    view->show();
    IlvMainLoop();
    return 0;
}
