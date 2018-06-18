// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/evplayer.h
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
// Definition of the IlvEventPlayer class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Evplayer_H
#define __Ilv_Util_Evplayer_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

class IlvView;
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvEventStruct
{
public:
    IlvEventStruct(IlvView*, IlvEvent& event);
    IlvEventStruct(const char*, IlvEvent& event);
    IlvEventStruct(const char*, IlvEvent& event, char*, int);

    inline IlvEvent*	getEvent()		{ return &_event; }
    inline const char*	getName() const		{ return _name; }
    inline void		setName(const char* n)	{ _name = n; }
    virtual const char*	getObjectName() const	{ return 0; }

    inline char*	getImBuffer() const	{ return _buffer; }
    inline int		getNbBytes() const	{ return _nbytes; }

    const char*		_name;
    IlvEvent		_event;

private:
    char*		_buffer;
    int			_nbytes;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvEventPlayer
{
public:
    IlvEventPlayer();
    virtual ~IlvEventPlayer();

    virtual void	start();
    void		stop();
    virtual void	play(IlvDisplay* display,
			     IlUInt period = 1000,
			     IlBoolean movePointer = IlFalse);
    virtual void	playOneEvent(IlvAbstractView* view, IlvEvent& event);
    void		destroyList();
    char*		buildName(const char*);
    inline IlList*	events() { return _eventlist; }
    virtual IlBoolean	save(const char* filename) const;
    virtual void	saveEvent(IlvEventStruct* s,
				  IL_STDPREF ostream& stream) const;
    virtual IlBoolean	load(IlvDisplay*, const char* filename);
    virtual IlBoolean	loadEvent(IL_STDPREF istream& stream);
    void		removeLast();
    void		init(IlvDisplay*, IlUInt speed = 1000) ;
    void		playOnce(IlvDisplay* display);
    virtual void	recordOneEvent(IlvView* view, IlvEvent& event);
    virtual void	recordOneEvent(IlvView* view,
				       IlvEvent& event,
				       char*,
				       int);
    void		recordImBuffer(IlvAbstractView*,
				       IlvEvent&,
				       char*,
				       int);
    int			getImBuffer(IlvAbstractView*,
				    IlvEvent&,
				    char*,
				    int,
				    int*);

    inline 
    IlList::Cell*	getCurrent() const { return _current; }
    inline IlList*	getNames() const	{ return _names;   }
    virtual void	addEventObject(const char*, IlvEvent*, const IlvRect&);
    virtual const IlvEventStruct* getCurrentGadgetEvent();

    static
    IlvEventPlayer*	getPlayer();
    static
    IlvEventPlayer*	getRecorder();

protected:
    void		destroyNames(IlList* list);
    char*		getCopyName(const char*, IlList* list);
    void		updateNames(IlList*);

    IlList*		_eventlist;
    IlList::Cell*	_current;
    IlList*		_names;
    IlvEventPlayer*	_oldPlayer;
    IlUInt		_previousDate;
    IlUInt		_speed;
    IlBoolean		_movePointer;

private:
    IlvEventStruct*	_evPlayed;
};

ILVDSPEXPORTEDFUNCTION(IL_STDPREF ostream&)
operator<<(IL_STDPREF ostream&, IlvEvent&);
ILVDSPEXPORTEDFUNCTION(IL_STDPREF istream&)
operator>>(IL_STDPREF istream&, IlvEvent&);

ILVDSPEXPORTEDFUNCTION(IlvEventPlayer*)
IlvCurrentEventPlayer(IlvEventPlayer* evplayer);
ILVDSPEXPORTEDFUNCTION(IlvEventPlayer*)
IlvCurrentEventPlayer();
ILVDSPEXPORTEDFUNCTION(IlvEventPlayer*)
IlvGetWorkingEventPlayer();
ILVDSPEXPORTEDFUNCTION(IlBoolean)
IlvRecordingEvents();
ILVDSPEXPORTEDFUNCTION(void)
IlvAddEventRecord(IlvView*, IlvEvent&);

#endif /* !__Ilv_Util_Evplayer_H */
