// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/synoptic/include/synoptic.h
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

// the 'mini' application kernel
// this implements a small production system in a generic way.

#include <ilviews/base/string.h>
#include <ilviews/base/iostream.h>
#include <ilviews/base/hash.h>
#include <ilviews/base/geometry.h>
#include <ilviews/base/link.h>

// --------------------------------------------------------------------------
// utility classes : implementation of a classic Observer/Observable
// design pattern
// -------------------------------------------------------------------------

struct Observable;

// --------------------------------------------------------------------------
struct Observer {
    virtual void update_obs(Observable*,
			    IlAny msg = 0);
};

// --------------------------------------------------------------------------
struct Observable {
    IlBoolean locked;
    IlList observers;

    Observable()
        : locked(IlFalse)
    {}
    // ____________________________________________________________
    void add_observer(Observer* o)
    {
        observers.append(o);
    }
    void notify(IlAny msg = 0);
};

// --------------------------------------------------------------------------
// application classes: Machine types and factory.
// -------------------------------------------------------------------------

struct Factory;

#define REPAIR_PRICE 30

// --------------------------------------------------------------------------
struct Machine
    : Observable
{
    Factory* factory;
    char* name;
    char* cname;
    IlBoolean broken;
    IlBoolean running;

    Machine(Factory* f,
	    const char* n = 0,
	    const char* cn = 0);
    virtual ~Machine() {}
    // ____________________________________________________________
    virtual void repair();
    virtual void do_break();
    void run(IlBoolean);
    void setName(const char*);
    virtual void action();
};

// --------------------------------------------------------------------------
struct Container
    : Machine
{
    IlFloat capacity;
    IlFloat level;

    Container(Factory* f,
	      const char* n,
	      const char* cn = 0,
	      IlFloat c = 0,
	      IlFloat l = 0)
        : Machine(f, n, cn ? cn : "Container"),
	  capacity(c),
	  level(l)
    {}
    // ____________________________________________________________
    IlvBoolean add(IlFloat);
    IlvFloat remove(IlFloat, IlBoolean = IlTrue);
};

// --------------------------------------------------------------------------
struct Producer
    : Container
{
    IlFloat rate;
    IlFloat cost;
    Container* output;

    Producer(Factory* f,
	     const char* n,
	     IlFloat c = 0,
	     IlFloat co = 0,
	     Container* o = 0)
        : Container(f, n, "Producer", c, c),
	  rate(0),
	  cost(co),
	  output(o)
    {}

    void refill();
    void set_rate(IlFloat);
    void action();
};

// --------------------------------------------------------------------------
struct Mixer
    : Container
{
#define MAX_MIX 10
    Container* inputs[MAX_MIX]; // List of machines
    IlFloat rates[MAX_MIX]; // List of Floats
    IlFloat production;
    IlFloat rate;
    IlFloat spill;

    Mixer(Factory* f,
	  const char* n,
	  const char* cn = 0,
	  IlFloat c = 0,
	  IlFloat p = 0)
        : Container(f, n, cn ? cn : "Mixer", c, 0),
	  production(p),
	  rate(0),
	  spill(0)
    { inputs[0] = 0; }

    void add_input(Container*,
		   IlFloat);
    void set_rate(IlFloat);
    void action();
};

// --------------------------------------------------------------------------
struct Factory
    : Mixer
{
    IlList machines;
    IlFloat rand_break;

    Factory();
    Machine* find(const char* n);
    void action();
};
