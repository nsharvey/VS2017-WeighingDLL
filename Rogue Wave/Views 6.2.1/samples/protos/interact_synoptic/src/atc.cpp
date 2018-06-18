// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/interact_synoptic/src/atc.cpp
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

// the 'mini' application kernel: this implements a simple
// simulator that will move planes from airport to airport
// in straight line and according to their schedule.

#include <ilviews/base/string.h>

#if defined(IL_STD)
#include <cstdlib> // for srand() and rand()
#include <ctime>  // for time()
#include <cmath>
#include <iostream>
#if defined(WINDOWS)
#include <fstream>
#endif /* WINDOWS */
IL_STDUSE;
#else  /* !IL_STD */
#include <stdlib.h> // for srand() and rand() and getenv()
#include <time.h> // for time()
#include <math.h>
#include <iostream.h>
#if defined(WINDOWS)
#include <fstream.h>
#endif /* WINDOWS */
#endif /* !IL_STD */

#ifndef M_PI
#define M_PI 3.141592653589793238462643384279
#endif

#include <atc.h>

// ------------------------------------------------------------------------
void
Observer::update_obs(Observable*,
		     IlAny)
{
    // DBG("non-overloaded Observer::update_obs()\n");
}

// ------------------------------------------------------------------------
void
Observable::notify (IlAny msg)
{
    if (locked)
	return;
    locked = IlTrue;
    Observer* o;
    IlvMapList(&observers, Observer*, o, o->update_obs(this, msg); );
    locked = IlFalse;
}

// ------------------------------------------------------------------------
Flight::Flight(Airport* f,
	       Airport* t,
	       IlFloat time,
	       const IlvSymbol* n)
    : from(f),
      to(t),
      departure(time),
      label(n),
      position(f->position),
      altitude(0),
      direction(0),
      speed(0)
{
}

// ------------------------------------------------------------------------
Flight::~Flight()
{
}

// ------------------------------------------------------------------------
void
Flight::update_obs (Observable*,
		    IlAny msg)
{
    IlFloat time = *(IlFloat*) msg;
    IlBoolean do_notify = IlFalse;
    if (time == 0) {
	position = from->position;
	altitude = 1;
	speed = 1;
	direction = (IlFloat)atan2(to->position.y() - from->position.y(),
				   to->position.x() - from->position.x());
	if (direction < 0)
	    direction += (IlFloat)(2 * M_PI);
	do_notify = IlTrue;
    }
    if (time >= departure &&
#if defined(WINDOWS) && defined(_MSC_VER) && (_MSC_VER >= 1400) /* x86_.net2005_8.0 or higher */
	_hypot(position.x() - to->position.x(),		
#else /* x86_.net2003_7.1 or lower for windows, or Unix/Linux ports */
	hypot(position.x() - to->position.x(),
#endif
	      position.y() - to->position.y()) >= 1) {
	position.translate((IlFloat)(speed * cos(direction)),
			   (IlFloat)(speed * sin(direction)));
	do_notify = IlTrue;
    }
    if (do_notify)
	notify(msg);
}

// ------------------------------------------------------------------------
void
ATC::load (istream& in)
{
    unsigned int alen = 0;
    unsigned int flen = 0;
    unsigned int i;
    in >> alen;
    in >> flen;
    for (i = 0 ; i < alen; ++i) {
	IlvFloatPoint pos;
	IlString str;
	in >> str;
	in >> pos._x;
	in >> pos._y;
	Airport* a = new Airport(IlvGetSymbol(str), pos);
	airports.append((IlAny)IlvGetSymbol(str), a);
    }
    for (i = 0 ; i < flen; ++i) {
	IlString from, to, str;
	float dep = 0;
	in >> from;
	in >> to;
	in >> dep;
	in >> str;
	Flight* f = new Flight(find(IlvGetSymbol(from)),
			       find(IlvGetSymbol(to)),
			       dep,
			       IlvGetSymbol(str));
	add_observer(f);
	flights.append((IlAny)f);
    }
}

// ------------------------------------------------------------------------
void
ATC::timer_tick ()
{
    time += 1.0;
    notify((IlAny)&time);
}
