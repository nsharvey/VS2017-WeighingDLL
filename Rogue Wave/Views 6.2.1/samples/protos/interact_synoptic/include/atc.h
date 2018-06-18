// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/interact_synoptic/include/atc.h
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

// the 'mini' application kernel
// this implements a small air traffic system

#include <ilviews/base/string.h>
#include <ilviews/base/iostream.h>
#include <ilviews/base/hash.h>
#include <ilviews/base/geometry.h>
#include <ilviews/base/link.h>

// --------------------------------------------------------------------------
// utility classes: implementation of an Observer/Observable design pattern
// --------------------------------------------------------------------------
// Forward declaration
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

    Observable():locked(IlFalse) {}
    void add_observer(Observer* o) { observers.append(o); }
    void notify (IlAny msg = 0);
};

// --------------------------------------------------------------------------
// application classes: Airport, Flight and ATC
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
struct Airport
{
    IlvFloatPoint position;
    const IlvSymbol* name;
  
    Airport(const IlvSymbol* n,
	    IlvFloatPoint p)
       : position(p),
	 name(n)
    {}
};

// --------------------------------------------------------------------------
struct Flight : Observable, Observer
{
    Airport* from;
    Airport* to;
    IlFloat departure;
    const IlvSymbol* label;

    IlvFloatPoint position;
    IlFloat altitude;
    IlFloat direction;
    IlFloat speed;

    Flight(Airport* from,
	   Airport* to,
	   IlFloat time,
	   const IlvSymbol* n);
    virtual ~Flight();
    void update_obs(Observable*,
		    IlAny);
};

// --------------------------------------------------------------------------
struct ATC : Observable
{
    IlList flights;
    IlAList airports;
    IlFloat time;

    ATC()
        : Observable(),
	  flights(),
	  airports(),
	  time(0)
    {}

    void load(istream&);
    Airport* find(const IlvSymbol* n) {
	Airport* res = 0;
	airports.find((IlAny)n, (IlAny*)&res);
	return res;
    }
    void timer_tick();
    void start() {
        time = 0;
	notify((IlAny)&time);
    }
};
