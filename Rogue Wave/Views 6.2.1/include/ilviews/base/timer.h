// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/timer.h
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
// Declaration of the IlvTimer class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Timer_H
#define __Ilv_Base_Timer_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif

class IlvTimerListener;
class IlList;

// --------------------------------------------------------------------------
// IlvTimerListener
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvTimerListener
{
    friend class IlvTimer;

public:
    IlvTimerListener();
    virtual ~IlvTimerListener();
    // ____________________________________________________________
    inline IlvTimer*	getTimer() const { return _timer; }
    // Virtuals
    virtual void	timerStarted();
    virtual void	timerStopped();
    virtual void	beforeDoIt();
    virtual void	afterDoIt();

protected:
    inline void		setTimer(IlvTimer* timer) { _timer = timer; }
    IlvTimer*		_timer;
};

// --------------------------------------------------------------------------
typedef void (* IlvTimerProc)(IlvTimer* timer, IlAny userArg);
typedef void (IlvTimerListener::*IlvTimerListenerNotificationMethod)();

// --------------------------------------------------------------------------
// IlvTimer
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvTimer
{
public:
    IlvTimer(IlvDisplay* display,
	     int secs = 1,
	     int millis = 0,
	     IlvTimerProc proc = 0,
	     IlAny arg = 0);
    virtual ~IlvTimer();
    // ____________________________________________________________
    inline IlvDisplay*	getDisplay() const { return _display;   }
    inline IlUInt	getPeriod()  const { return _millisecs; }
    inline const char*	getName() const { return _name; }
    void		setName(const char*);
    inline IlBoolean   runOnce() const { return _runOnce; }
    inline void		runOnce(IlBoolean runOnce) { _runOnce = runOnce; }
    void		startCheckingDeletion(IlBoolean&);
    void		stopCheckingDeletion(IlBoolean&);
    inline IlBoolean	isInDoIt() const { return _inDoIt; }
    inline void		setProc(IlvTimerProc proc, IlAny arg = 0)
			{
			    _timerproc = proc; _procarg = arg;
			}
    virtual void	trigger();
    virtual void	run();
    virtual void	run(int secs, int millis = 0);
    virtual void	suspend();
    virtual void	doIt();
    virtual IlBoolean	isRunning() const;

    // Listeners
    void		addListener(IlvTimerListener*);
    void		removeListener(IlvTimerListener*);
    void		callListeners(IlvTimerListenerNotificationMethod);
    void		removeListeners();

protected:
    IlvDisplay*		_display;
    IlUInt		_millisecs;
    IlBoolean		_runOnce;
    char*		_name;
    IlAny		_inputid;
    IlAny		_procarg;
    IlvTimerProc	_timerproc;
    IlBoolean		_inDoIt;
    IlList*		_listeners;
    IlList*		_alive;

private:
    void		destroy();
};

// --------------------------------------------------------------------------
// IlvSharedTimer & IlvSmartTimer
// --------------------------------------------------------------------------
class IlvSmartTimer;
class ILVDSPEXPORTED IlvSharedTimer : public IlvTimer
{
    friend class IlvSmartTimer;
public:
    IlvSharedTimer(IlvDisplay* display,
		   int secs = 1,
		   int millis = 0);
    // ____________________________________________________________
    inline IlUInt	getCurrentTime() const { return _currentTime; }
    virtual void	trigger();
    virtual void	doIt();
    static IlUInt	_MinPeriod;

protected:
    IlList		_smartTimers;
    IlUInt		_currentTime;
    IlBoolean		_destroyAsked;

    void		addSmartTimer(IlvSmartTimer* smartTimer);
    void		removeSmartTimer(IlvSmartTimer* smartTimer);
    void		deleteTimer();
    IlBoolean		isEmpty() const;
    IlBoolean		hasRunningTimers() const;

    static IlList	_SharedTimers;

    static
    IlvSharedTimer*	AllocTimer(IlvSmartTimer* smartTimer);
    static void		FreeTimer(IlvSmartTimer* smartTimer);
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvSmartTimer : public IlvTimer
{
public:
    IlvSmartTimer(IlvDisplay* display,
		  int secs = 1,
		  int millis = 0,
		  IlvTimerProc proc = 0,
		  IlAny arg = 0);
    virtual ~IlvSmartTimer();
    // ____________________________________________________________
    virtual void	run(int secs, int millis = 0);
    virtual void	run();
    virtual void	suspend();
    virtual void	doIt();
    virtual IlBoolean	isRunning() const;
    inline
    IlvSharedTimer*	getSharedTimer() const { return _sharedTimer; }

protected:
    IlBoolean		_running;
    IlvSharedTimer*	_sharedTimer;
};

#endif /* ! __Ilv_Base_Timer_H */
