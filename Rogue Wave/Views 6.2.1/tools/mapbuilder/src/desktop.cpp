// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/desktop.cpp
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
// The implementation of MapDesktopManager methods.
// --------------------------------------------------------------------------
#include "desktop.h"
#include "builder.h"

#if defined(IL_STD)
#  include <cstring>
IL_STDUSE
#else  /* !IL_STD */
#  if !defined(WINDOWS)
#    include <strings.h>
#  endif
#  include <stdlib.h>
#endif /* !IL_STD */

// --------------------------------------------------------------------------
MapDesktopManager::MapDesktopManager(IlvView* view,MapBuilder* b)
: IlvDesktopManager(view),
  builder(b)
{
}

// --------------------------------------------------------------------------
void
MapDesktopManager::frameSelectionChanged(IlvViewFrame* newFrame,
					      IlvViewFrame* oldFrame)
{  
    // Copy the list before calling callbacks
    IlListOf(MapDesktopManagerListener) tmp;
    for (IlUInt i=0; i < listenerList.length(); i++) {
	tmp.append(listenerList.getValue(i));
    }
    for (IlUInt j=0; j < tmp.length(); j++) {
	tmp.getValue(j)->frameSelectionChanged(newFrame,oldFrame);
    }
}

// --------------------------------------------------------------------------
void
MapDesktopManager::frameMinimized(IlvViewFrame* frame,int previousState)
{
    // copy the list before calling callbacks
    IlListOf(MapDesktopManagerListener) tmp;
    for (IlUInt i=0; i < listenerList.length(); i++) {
	tmp.append(listenerList.getValue(i));
    }
    for (IlUInt j=0; j < tmp.length(); j++) {
	tmp.getValue(j)->frameMinimized(frame,previousState);
    }
}

// --------------------------------------------------------------------------
void
MapDesktopManager::frameMaximized(IlvViewFrame* frame,int previousState)
{
    // copy the list before calling callbacks
    IlListOf(MapDesktopManagerListener) tmp;
    for (IlUInt i=0; i < listenerList.length(); i++) {
	tmp.append(listenerList.getValue(i));
    }
    for (IlUInt j=0; j < tmp.length(); j++) {
	tmp.getValue(j)->frameMaximized(frame,previousState);
    }
}

// --------------------------------------------------------------------------
void
MapDesktopManager::frameRestored(IlvViewFrame* frame,int previousState)
{
    // copy the list before calling callbacks
    IlListOf(MapDesktopManagerListener) tmp;
    for (IlUInt i=0; i < listenerList.length(); i++) {
	tmp.append(listenerList.getValue(i));
    }
    for (IlUInt j=0; j < tmp.length(); j++) {
	tmp.getValue(j)->frameRestored(frame,previousState);
    }
}

// --------------------------------------------------------------------------
void
MapDesktopManager::removeFrame(IlvViewFrame* frame)
{
    // copy the list before calling callbacks
    IlListOf(MapDesktopManagerListener) tmp;
    for (IlUInt i=0; i < listenerList.length(); i++) {
	tmp.append(listenerList.getValue(i));
    }
    for (IlUInt j=0; j < tmp.length(); j++) {
	tmp.getValue(j)->frameRemoved(frame);
    }
    IlvDesktopManager::removeFrame(frame);
}

// --------------------------------------------------------------------------
void
MapDesktopManager::addFrame(IlvViewFrame* frame)
{
    // copy the list before calling callbacks
    IlListOf(MapDesktopManagerListener) tmp;
    for (IlUInt i=0; i < listenerList.length(); i++) {
	tmp.append(listenerList.getValue(i));
    }
    for (IlUInt j=0; j < tmp.length(); j++) {
	tmp.getValue(j)->frameAdded(frame);
    }
    IlvDesktopManager::addFrame(frame);
}
