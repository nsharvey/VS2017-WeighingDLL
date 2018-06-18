// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/animator.h
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
// Declaration of the IlvAnimator class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Animator_H
#define __Ilv_Util_Animator_H

#if !defined(__Ilv_Ilv_h)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Util_Proplist_h)
#include <ilviews/util/proplist.h>
#endif
#if !defined(__Ilv_Base_Timer_h)
#include <ilviews/base/timer.h>
#endif

#define IlvDefaultAnimationPeriod 100

class IlvBitmap;
class IlvTimer;
class IlvDisplay;
class IlvGraphic;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvAnimator : public IlvNamedProperty
{
public:

    enum IlvAnimationMode {
	IlvAnimationNone     = 0,
	IlvAnimationForward  = 1,
	IlvAnimationBackward = 2,
	IlvAnimationForwardOnce  = 3,
	IlvAnimationBackwardOnce = 4
    };

    IlvAnimator(IlSymbol* name,
		IlvAnimationMode mode = IlvAnimationForward,
		IlUInt period = IlvDefaultAnimationPeriod);
    virtual ~IlvAnimator();
    //____________________________________________________________
    inline IlUInt	getPeriod() const { return _period; }
    inline
    IlvAnimationMode	getAnimationMode() const { return _mode; }
    inline void		setAnimationMode(IlvAnimationMode mode)
			{
			    setAnimationMode(mode, _period);
			}
    void		setAnimationMode(IlvAnimationMode mode,
					 IlUInt period);
    inline IlUInt	getState() const { return _state; }
    inline void		setState(IlUInt state) { _state = state; }
    void		reset();
    void		changeState(IlUInt state, IlBoolean redraw = IlTrue);
    virtual void	animate();
    virtual void	stateChanged(IlUInt newState, IlUInt oldState);
    virtual IlUInt	nextState(IlUInt state) const;
    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();
    virtual
    const IlSymbol*	getValueName() const;
    // Redraw mechanism
    virtual void	reDraw() const;
    virtual void	initReDraws() const = 0;
    virtual void	invalidateRegion()  const = 0;
    virtual void	reDrawViews() const = 0;
    // Need to be redefined in subclasses
    virtual IlUInt	getStatesCount() const = 0;
    virtual IlBoolean	isLastState(IlUInt state) const;

    DeclareValueAccessors();
    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvAnimator);

protected:
    IlUInt		_state;
    IlUInt		_period;
    IlvAnimationMode	_mode;

private:
    IlvTimer*		_timer;
    IlvTimerListener*	_listener;
    void		startTimer();
    void		stopTimer();
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvBitmapAnimator : public IlvAnimator
{
public:

    IlvBitmapAnimator(IlSymbol* name,
		      IlvAnimationMode mode = IlvAnimationForward,
		      IlUInt period = IlvDefaultAnimationPeriod);
    virtual ~IlvBitmapAnimator();
    //____________________________________________________________

    virtual IlvBitmap*	getBitmap() const = 0;
    virtual IlBoolean	isLastState(IlUInt state) const;
    virtual IlUInt	getStatesCount() const;
    virtual void	stateChanged(IlUInt newState, IlUInt oldState);

    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvBitmapAnimator);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGraphicAnimator : public IlvAnimator
{
public:

    IlvGraphicAnimator(IlSymbol* name,
		       IlvAnimationMode mode = IlvAnimationForward,
		       IlUInt period = IlvDefaultAnimationPeriod,
		       IlBoolean useApply = IlTrue);
    //____________________________________________________________
    virtual void	animate();
    virtual void	initReDraws() const;
    virtual void	invalidateRegion() const;
    virtual void	reDrawViews() const;
    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();
    virtual void	stateChanged(IlUInt newState, IlUInt oldState);
    inline IlvGraphic*	getGraphic() const { return _graphic; }
    inline IlBoolean	usesApply() const { return _useApply; }
    inline void		useApply(IlBoolean value) { _useApply = value; }
    static
    IlvGraphicAnimator* Get(const IlvGraphic* graphic, const IlSymbol* name);
    void		addTo(IlvGraphic* graphic);
    void		removeFrom(IlvGraphic* graphic);
    inline static
    IlvGraphicAnimator*	RemoveFrom(IlvGraphic* graphic, const IlSymbol* name)
			{
			    IlvGraphicAnimator* animator = Get(graphic, name);
			    if (animator)
				animator->removeFrom(graphic);
			    return animator;
			}

    DeclareValueAccessors();
    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvGraphicAnimator);

protected:
    IlvGraphic*		_graphic;
    IlBoolean		_useApply;

    inline void		setGraphic(IlvGraphic* g) { _graphic = g; }
};

ILVVWSMODULEINIT(animator);

#endif /* !__Ilv_Util_Animator_H */
