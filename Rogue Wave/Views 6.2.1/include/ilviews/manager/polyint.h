// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/polyint.h
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
// Declaration of the IlvPolySelectInteractor class
// Defined in library ilvmgr
// ------------------------------------------------------------------------
#ifndef __Ilv_Manager_Polyint_H
#define __Ilv_Manager_Polyint_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Graphics_Polysel_H)
#include <ilviews/graphics/polysel.h>
#endif
#if !defined(__Ilv_Graphics_Polyptsel_H)
#include <ilviews/graphics/polyptsel.h>
#endif
#if !defined(__Ilv_Base_Command_H)
#include <ilviews/base/command.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvPolySelectInteractor : public IlvManagerViewInteractor
{
public:
    IlvPolySelectInteractor(IlvManager* manager, IlvView* view)
	: IlvManagerViewInteractor(manager, view),
	  _selectedpoint(),
	  _firstpoint(),
	  _pointindex(-1),
	  _polyselect(0),
	  _polypoints(0),
	  _ghostpoints(0),
	  _dragging(IlFalse),
	  _rotating(IlFalse),
	  _angle((IlFloat)0),
	  _command(0)
    {}
    IlvPolySelectInteractor()
	: IlvManagerViewInteractor(),
	  _selectedpoint(),
	  _firstpoint(),
	  _pointindex(-1),
	  _polyselect(0),
	  _polypoints(0),
	  _ghostpoints(0),
	  _dragging(IlFalse),
	  _rotating(IlFalse),
	  _angle((IlFloat)0),
	  _command(0)
    {}
    // ____________________________________________________________
    IlBoolean	handleEvent(IlvEvent& event);
    void		init();
    void		drawGhost();
    void		abort() ;
    void		handleExpose(IlvRegion* rect = 0);

    inline
    IlvPolySelection*	getPolySelection() const { return _polyselect; }
    virtual
    IlvPolySelection*	createPolySelection(IlvPolyPoints* polypt);
    virtual
    IlvPolyPoints*	selectPolyPoints(IlvPoint& point);
    virtual IlBoolean	acceptPoint(IlvPolyPoints* polypt, IlUInt index);
    virtual IlBoolean	acceptRotate(IlvPolyPoints* polypt);
    virtual void	doChangePoint(IlvPolyPoints* polypt,
				      IlUInt         index,
				      IlvPoint&      value);
    virtual void	doRotate(IlvPolyPoints* polypt, IlFloat angle);

    IlvPolySelectInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    void		handleButtonDown(IlvEvent& event);
    void		handleButtonDragged(IlvEvent& event);
    void		handleButtonUp(IlvEvent& event);

    IlvPoint			_selectedpoint;
    IlvPoint			_firstpoint;
    IlInt			_pointindex;
    IlvPolySelection*		_polyselect;  // temporary
    IlvPolyPoints*		_polypoints;  // Selected polypoints
    IlvPolyPoints*		_ghostpoints; // Copy of polypoints
    IlBoolean			_dragging;
    IlBoolean			_rotating;    // to be implemented
    IlFloat			_angle;
    IlvChangeValueCommand*	_command;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvEditPointsInteractor : public IlvManagerViewInteractor
{
public:
    IlvEditPointsInteractor(IlvManager* manager, IlvView* view)
	: IlvManagerViewInteractor(manager, view),
	  _target(0),
	  _selection(0),
	  _ghost(0),
	  _command(0) {}
    IlvEditPointsInteractor()
	: IlvManagerViewInteractor(),
	  _target(0),
	  _selection(0),     
	  _ghost(0),
	  _command(0) {}
    // ____________________________________________________________
    IlBoolean	handleEvent(IlvEvent& event);
    void		init();
    void		drawGhost();
    void		abort() ;
    void		handleExpose(IlvRegion* rect = 0);
    virtual
    IlvPolyPointsSelection* createSelection(IlvGraphic* polypt);
    virtual
    IlvPolyPoints*	selectObject(IlvPoint& point);

    virtual void	insertPoint(IlvEvent& event, 
				    IlInt segment, 
				    const IlvPoint& p, 
				    IlDouble param);
    virtual void	removePoint(IlvEvent& event, IlUInt index);

    IlvEditPointsInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    void		handleButtonDown(IlvEvent& event);
    void		handleButtonDragged(IlvEvent& event);
    void		handleButtonUp(IlvEvent& event);

    IlvPolyPoints* 		_target;
    IlvPolyPointsSelection* 	_selection;
    IlvPolyPoints*		_ghost;
    IlvChangeValueCommand*	_command;
};

ILVMGRMODULEINIT(m0_polyint);

#endif /* !__Ilv_Manager_Polyint_H */
