// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/transition.h
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
// Declaration of the IlvTransitionHandler classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Transition_H
#define __Ilv_Util_Transition_H

#include <ilviews/ilv.h>

class IlvTimer;
class IlvTransitionScheduler;
class IlvBitmapTransition;
class IlvRGBBitmapData;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTransitionHandler
{
public:
    IlvTransitionHandler() {}
    virtual ~IlvTransitionHandler();
    //____________________________________________________________
    virtual void	startTransition(IlvTransitionScheduler& scheduler);
    virtual void	doTransition(IlvTransitionScheduler& scheduler,
				     IlDouble oldRate,
				     IlDouble newRate) = 0;
    virtual void	stopTransition(IlvTransitionScheduler& scheduler);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTransitionScheduler
{
public:
    IlvTransitionScheduler(IlvDisplay* display,
			   IlvTransitionHandler& handler,
			   IlUInt duration,
			   IlBoolean isSteps = IlFalse,
			   IlUInt delay = 0,
			   IlBoolean owner = IlTrue);
    virtual ~IlvTransitionScheduler();

    inline IlBoolean	isRunning() const { return _running; }
    inline IlUInt	getDuration() const { return _duration; }
    void		setDuration(IlUInt duration) { _duration = duration; }
    inline IlUInt	getSteps() const { return _steps; }
    void		setSteps(IlUInt steps) { _steps = steps; }
    inline
    IlvTransitionHandler& getTransitionHandler() { return _handler; }
    inline
    const IlvTransitionHandler& getTransitionHandler() const
			{
			    return _handler;
			}
    inline
    IlvDisplay*		getDisplay() const { return _display; }
    virtual IlDouble	computeNextStep(IlDouble current) const;
    virtual IlDouble	computeNextTransition(IlDouble start,
					      IlDouble current) const;
    inline IlDouble	getLastTransition() const { return 100.; }
    IlBoolean		isLastTransition(IlDouble current) const;
    inline IlBoolean	finishBeforeStopping() const { return _finish; }
    void		finishBeforeStopping(IlBoolean finish = IlTrue)
			{
			    _finish = finish;
			}
    virtual void	doTransition(IlDouble old, IlDouble current);
    virtual void	nextTransition();
    virtual void	start();
    virtual void	stop();

protected:
    IlvDisplay*		_display;
    IlvTransitionHandler& _handler;
    IlBoolean		_owner;
    IlDouble		_currentTransition;
    IlBoolean		_running;
    IlUInt		_delay;
    IlvTimer*		_timer;
    IlAny		_idleProcId;
    IlUInt		_steps;
    IlUInt		_duration;
    IlDouble		_startTime;
    IlBoolean		_finish;

    void		abort();
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvBitmapTransitionHandler : public IlvTransitionHandler
{
public:
    IlvBitmapTransitionHandler(IlvBitmapTransition& transition,
			       IlvRGBBitmapData& image1,
			       IlvRGBBitmapData& image2,
			       IlvPort& dst);
    ~IlvBitmapTransitionHandler();
    virtual void	startTransition(IlvTransitionScheduler& scheduler);
    virtual void	doTransition(IlvTransitionScheduler& scheduler,
				     IlDouble previous,
				     IlDouble current);

protected:
    IlvBitmapTransition& _transition;
    IlvRGBBitmapData&	_image1;
    IlvRGBBitmapData&	_image2;
    IlvRGBBitmapData*	_buffer;
    IlvPort& _dst;
};

#endif
