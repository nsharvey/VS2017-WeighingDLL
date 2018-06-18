// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/synoptic/src/synoptic.cpp
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

// the 'mini' application kernel
// this implements a small production system in a generic way.

#include <ilviews/base/string.h>
#include <ilviews/base/error.h>
#include <ilviews/base/iostream.h>
#include <ilviews/base/hash.h>
#include <ilviews/base/geometry.h>
#include <ilviews/base/link.h>

#if defined(IL_STD)
#include <cstdlib> // for srand() and rand()
#include <cstring>
#include <cmath>
#include <iostream>
#if defined(WINDOWS)
#include <fstream>
#endif /* WINDOWS */
IL_STDUSE;
#else  /* !IL_STD */
#include <stdlib.h> // for srand() and rand() and getenv()
#include <math.h>
#include <string.h>
#include <iostream.h>
#if defined(WINDOWS)
#include <fstream.h>
#endif /* WINDOWS */
#endif /* !IL_STD */

#include <synoptic.h>

// --------------------------------------------------------------------------
// utility classes : implementation of a classic Observer/Observable
// design pattern
// --------------------------------------------------------------------------
void
Observer::update_obs(Observable*,
		     IlAny)
{
    IlvCErr << "non-overloaded Observer::update_obs()\n";
}

// --------------------------------------------------------------------------
void
Observable::notify(IlAny msg)
{
    if (locked)
	return;
    locked = IlTrue;
    Observer* o;
    IlvMapList(&observers, Observer*, o,
	       o->update_obs(this, msg);
	       );
    locked = IlFalse;
}

// --------------------------------------------------------------------------
// application classes: Machine types and factory.
Machine::Machine (Factory* f,
		  const char* n,
		  const char* cn)
    : factory(f),
      name(new char [strlen(n) + 1]),
      cname(new char [cn ? (strlen(cn) + 1) : 8]),
      broken(IlFalse),
      running(IlFalse)
{
    strcpy(name, n);
    strcpy(cname, cn ? cn : "Machine");
}

// --------------------------------------------------------------------------
void
Machine::setName(const char* n)
{
    if (!n)
	return;
    if (name)
	delete [] name;
    name = strcpy(new char [strlen(n) + 1], n);
}

// --------------------------------------------------------------------------
void
Machine::repair()
{
    if (!broken)
	return;
    IlvFloat f = factory->remove(REPAIR_PRICE, IlvFalse);
    if (f > 0)
	broken = IlvFalse;
    else
	factory->add(f);
    notify((IlAny)"Broken");
}

// --------------------------------------------------------------------------
void
Machine::do_break()
{
  if (broken) // If it ain't broken, don't fix it ! ;-)
	return;
    broken = IlTrue;
    notify((IlAny)"Broken");
}

// --------------------------------------------------------------------------
void
Machine::run (IlBoolean r)
{
    if (running == r)
	return;
    running = r;
    notify((IlAny)"Running");
}

// --------------------------------------------------------------------------
void
Machine::action()
{
    if (running && !broken)
	notify((IlAny)"Action");
}

// --------------------------------------------------------------------------
IlBoolean
Container::add(IlFloat f)
{
    if ((f + level) <= capacity) {
	level += f;
	notify((IlAny)"Level");
	return IlTrue;
    } else
	do_break();
    return IlFalse;
}

// --------------------------------------------------------------------------
IlFloat
Container::remove(IlFloat f,
		  IlBoolean b)
{
    if (broken)
	return 0;
    if (level >= f) {
	level -= f;
	notify((IlAny)"Level");
    } else {
	if (b) {
	    do_break();
	    f = 0;
	} else {
	    f = level;
	    level = 0;
	    notify((IlAny)"Level");
	}
    }
    return f;
}

// --------------------------------------------------------------------------
void
Producer::refill()
{
    IlFloat f = factory->remove((capacity-level)*cost, IlFalse);
    add(f / cost);
}

// --------------------------------------------------------------------------
void
Producer::set_rate(IlFloat f)
{
    rate = f;
    notify((IlAny)"Rate");
}

// --------------------------------------------------------------------------
void
Producer::action()
{
    if (!broken && running && output) {
	IlFloat f = remove(rate, IlFalse);
	if (f > 0)
	    output->add(f);
    }
}

// --------------------------------------------------------------------------
void
Mixer::set_rate(IlFloat f)
{
    rate = f;
    notify((IlAny)"Rate");
}

// --------------------------------------------------------------------------
void
Mixer::add_input(Container* c,
		 IlFloat r)
{
    int i = 0;
    while (inputs[i])
	i++;
    inputs[i]   = c;
    rates[i]    = r;
    inputs[i + 1] = 0;
}

// --------------------------------------------------------------------------
void
Mixer::action()
{
    if (!running || broken || (rate == 0))
	return;
    int i = 0;
    IlFloat minrate = rate;
    for (; inputs[i]; i++) {
	IlFloat f = inputs[i]->remove(rates[i] * rate, IlFalse);
	if ((f < rates[i] * rate) &&
	    (f / rates[i]) < minrate)
	    minrate = f / rates[i];
    }
    if (minrate > 0)
	add(production * minrate);
    if (spill != (1 - minrate / rate)) {
	spill = 1 - minrate / rate;
	notify((IlAny)"Spill");
    }
}

// --------------------------------------------------------------------------
void
Factory::action()
{
    Machine* m;
    IlvMapList(&machines, Machine*, m,
	       if (m != this)
	           m->action()
	       );
    Mixer::action();
    if (rand_break > 0) {
	 if ((rand() % 300) < rand_break) {
	     IlvInt it = machines.length() - 1;
	     m = 0;
	     if (it >= 0)
		 m = (Machine*) machines[rand() % it];
	     if (m && strcmp(m->cname, "Factory"))
		 m->do_break();
	 }
    }
}

// --------------------------------------------------------------------------
Machine*
Factory::find(const char* n)
{
    Machine* m = 0;
    IlvMapList(&machines, Machine*, m,
	       if (!strcmp(n, m->name))
	       return m;);
    return (Machine*)0;
}

// --------------------------------------------------------------------------
Factory::Factory()
    : Mixer(0, "Arkola Inc.", "Factory", 1000000, 100),
      rand_break(1)
{
    factory = this;
    // here, we could build the plant, for instance from
    // a file. But we have chosen to build it from within
    // the UI to allow using Studio as a plant design tool.
}
