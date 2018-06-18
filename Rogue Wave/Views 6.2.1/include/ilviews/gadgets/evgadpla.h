// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/evgadpla.h
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
// Declaration of the IlvEventGadgetPlayer class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Evgadpla_H
#define __Ilv_Evgadpla_H

#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif
#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Util_Evplayer_H)
#include <ilviews/util/evplayer.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

class IlvView;
// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvEventGadgetStruct
    : public IlvEventStruct {
 public:
    IlvEventGadgetStruct(const char* viewName,
			 IlvEvent& event,
			 IlFloat eventFromObjectX,
			 IlFloat eventFromObjectY,
			 const char* objectName);
    // ____________________________________________________________
    virtual const char* getObjectName() const {return _objectName;}
    void setObjectName(const char* name) {_objectName = name;}
    IlFloat getEventFromObjectX() const {return _eventFromObjectX;}
    IlFloat getEventFromObjectY() const {return _eventFromObjectY;}
    void setEventFromObjectX(IlFloat eventFromObjectX)
    {_eventFromObjectX = eventFromObjectX;}
    void setEventFromObjectY(IlFloat eventFromObjectY)
    {_eventFromObjectY = eventFromObjectY;}
protected:
    const char*   _objectName;
    IlFloat      _eventFromObjectX;
    IlFloat      _eventFromObjectY;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvEventGadgetPlayer
    : public IlvEventPlayer {
 public:
    IlvEventGadgetPlayer();
    ~IlvEventGadgetPlayer();
    // ____________________________________________________________
    virtual void start();
    virtual void addEventObject(const char*, IlvEvent*, const IlvRect&);
    virtual const IlvEventStruct* getCurrentGadgetEvent();
    void setCurrentGadgetStruct(IlvEventGadgetStruct* gadgetStruct)
    {_gadgetStruct = gadgetStruct;}
    virtual void playOneEvent(IlvAbstractView* view, IlvEvent& event);
    virtual void saveEvent(IlvEventStruct* s, ILVSTDPREF ostream& stream) const;
    virtual IlBoolean loadEvent(ILVSTDPREF istream& stream);
    void purgeFromView(const char*);
    void purgeFromObject(const char*);
    void purgeFromEventType(IlvEventType);
protected:
    IlvList*              _objectNames;
    IlvEventGadgetStruct* _gadgetStruct;
};

#endif /* !__Ilv_Evgadpla_H */
