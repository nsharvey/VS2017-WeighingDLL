// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/movresh.h
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
// Declaration of the IlvMoveReshapeInteractor class
// Not part of any Rogue Wave Views library
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Movresh_H
#define __Ilv_Manager_Movresh_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Graphics_Select_H)
#include <ilviews/graphics/select.h>
#endif
#if !defined(__Ilv_Manager_Movinter_H)
#include <ilviews/manager/movinter.h>
#endif
#if !defined(__Ilv_Manager_Reshint_H)
#include <ilviews/manager/reshint.h>
#endif

// --------------------------------------------------------------------------
class IlvMoveReshapeInteractor : public IlvManagerViewInteractor
{
public:
    IlvMoveReshapeInteractor(IlvManager* manager, IlvView* view)
    : IlvManagerViewInteractor(manager, view),
      _first(),
      _xor_rectangle(0, 0, 0, 0),
      _move(),
      _reshape(),
      _current(0) {}
    IlvMoveReshapeInteractor()
    : IlvManagerViewInteractor(),
      _first(),
      _xor_rectangle(0, 0, 0, 0),
      _move(),
      _reshape(),
      _current(0) {}

    virtual void	attach(IlvManager* manager, IlvView* view);
    virtual void	handleExpose(IlvRegion* clip = 0);
    virtual void	handleEvent(IlvEvent& event);
    virtual void	drawGhost();

    virtual void	drawGhost(const IlvRect&, IlvRegion* clip = 0);
    inline const IlvRect&	getRectangle() { return _xor_rectangle; }
    virtual void	doIt(const IlvRect&);

    IlvMoveReshapeInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlvPoint			_first;
    IlvRect			_xor_rectangle;
    IlvMoveInteractor		_move;
    IlvReshapeInteractor	_reshape;
    IlvManagerViewInteractor*	_current;
};


ILVMGRMODULEINIT(m0_movresh);

#endif /* ! __Ilv_Manager_Movresh_H */
