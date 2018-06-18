// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/geointer.h
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
// Declaration of predefined geometric interactor classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Geointer_H
#define __Ilv_Manager_Geointer_H

#if !defined(__Ilv_Manager_Dragrin_H)
#include <ilviews/manager/dragrin.h>
#endif

#if !defined(__Ilv_Manager_Transition_H)
#include <ilviews/manager/transition.h>
#endif

#define IlvMgrInteractorDefaultSchedulingDuration 1000
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeZoomInteractor : public IlvDragRectangleInteractor
{
public:
    IlvMakeZoomInteractor(IlvManager* manager, IlvView* view)
	: IlvDragRectangleInteractor(manager, view),
	  _transitionScheduler(0)
    {}
    IlvMakeZoomInteractor()
	: IlvDragRectangleInteractor(),
	  _transitionScheduler(0)
    {}
    virtual ~IlvMakeZoomInteractor();

    virtual void	doIt(IlvRect& rect);
    void useDefaultTransitionScheduler(IlBoolean value = IlTrue,
				       IlUInt duration = IlvMgrInteractorDefaultSchedulingDuration);

    IlvManagerTransitionScheduler* getTransitionScheduler() const
			{
			    return _transitionScheduler;
			}
    void setTransitionScheduler(IlvManagerTransitionScheduler* scheduler)
			{
			    delete _transitionScheduler;
			    _transitionScheduler = scheduler;
			}

    IlvMakeZoomInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlvManagerTransitionScheduler* _transitionScheduler;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeUnZoomInteractor
    : public IlvDragRectangleInteractor
{
public:
    IlvMakeUnZoomInteractor(IlvManager* manager, IlvView* view)
	: IlvDragRectangleInteractor(manager, view),
	  _transitionScheduler(0)
    {}
    IlvMakeUnZoomInteractor()
	: IlvDragRectangleInteractor(),
	  _transitionScheduler(0)
    {}
    virtual ~IlvMakeUnZoomInteractor();

    virtual void	doIt(IlvRect& rect);
    void useDefaultTransitionScheduler(IlBoolean value = IlTrue,
				       IlUInt duration = IlvMgrInteractorDefaultSchedulingDuration);

    IlvManagerTransitionScheduler* getTransitionScheduler() const
			{
			    return _transitionScheduler;
			}
    void setTransitionScheduler(IlvManagerTransitionScheduler* scheduler)
			{
			    delete _transitionScheduler;
			    _transitionScheduler = scheduler;
			}

    IlvMakeUnZoomInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlvManagerTransitionScheduler* _transitionScheduler;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeMoveInteractor : public IlvManagerViewInteractor
{
public:
    IlvMakeMoveInteractor(IlvManager*    manager,
			  IlvView*       view,
			  unsigned short button = IlvLeftButton)
	: IlvManagerViewInteractor(manager, view),
	  _button(button),
	  _transitionScheduler(0)
	{}
    IlvMakeMoveInteractor(unsigned short button = IlvLeftButton)
	: IlvManagerViewInteractor(),
	 _button(button),
	  _transitionScheduler(0)
	{}
    virtual ~IlvMakeMoveInteractor();

    inline void		setButton(IlUShort b) { _button = b; }
    inline IlUShort	getButton() const { return _button; }
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	drawGhost();
    virtual void	doIt(IlvPos dx, IlvPos dy);
    void useDefaultTransitionScheduler(IlBoolean value = IlTrue,
				       IlUInt duration = IlvMgrInteractorDefaultSchedulingDuration);

    IlvManagerTransitionScheduler* getTransitionScheduler() const
			{
			    return _transitionScheduler;
			}
    void setTransitionScheduler(IlvManagerTransitionScheduler* scheduler)
			{
			    delete _transitionScheduler;
			    _transitionScheduler = scheduler;
			}

    IlvMakeMoveInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlvPos		_prevx;
    IlvPos		_prevy;
    IlvPos		_dx;
    IlvPos		_dy;
    IlUShort		_button;
    IlvManagerTransitionScheduler* _transitionScheduler;
};

ILVMGRMODULEINIT(m0_geointer);

#endif /* !__Ilv_Manager_Geointer_H */
