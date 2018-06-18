// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/desktop.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the MapDesktopManager class
// --------------------------------------------------------------------------
#ifndef _MapDesktop_h_
#define _MapDesktop_h_

#include <ilviews/ilv.h>
#include <ilviews/gadgets/desktop.h>
#include <ilviews/gadgets/vframe.h>

// --------------------------------------------------------------------------
class MapDesktopManagerListener
{
public:
    virtual void frameSelectionChanged(IlvViewFrame*,
				       IlvViewFrame*) { };
    virtual void frameMinimized(IlvViewFrame*,
				int) { };
    virtual void frameMaximized(IlvViewFrame*,
				int) { };
    virtual void frameRestored(IlvViewFrame*,
			       int) { };
    // when calling frameRemoved, the frame is in its destructor,
    // so beware of what you do with it....
    virtual void frameRemoved(IlvViewFrame*) { };
    virtual void frameAdded(IlvViewFrame*) { };
};


IlDefineListOf(MapDesktopManagerListener,MapDesktopManagerListener*);

class MapBuilder;

// --------------------------------------------------------------------------
class MapDesktopManager
    : public IlvDesktopManager
{
public:
    MapDesktopManager(IlvView*, MapBuilder*);

    inline MapBuilder* getBuilder() const
	{ return builder; };

    // callback management
    inline void addListener(MapDesktopManagerListener* listener)
	{ listenerList.append(listener); }
    inline IlBoolean removeListener(MapDesktopManagerListener* listener)
	{ return listenerList.remove(listener); }

    // overrides some methods to be notified of some changes
    virtual void frameSelectionChanged(IlvViewFrame*,
				       IlvViewFrame*);
    virtual void frameMinimized(IlvViewFrame*, int);
    virtual void frameMaximized(IlvViewFrame*, int);
    virtual void frameRestored(IlvViewFrame*, int);
    virtual void removeFrame(IlvViewFrame*);
    virtual void addFrame(IlvViewFrame*);
private:
    MapBuilder* builder;

    IlListOf(MapDesktopManagerListener) listenerList;
};

#endif /* !_MapDesktop_h_ */
