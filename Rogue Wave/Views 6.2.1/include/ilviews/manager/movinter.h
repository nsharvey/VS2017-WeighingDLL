// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/movinter.h
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
// Declaration of the IlvMoveInteractor class
// Not part of any Rogue Wave Views library
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Movinter_H
#define __Ilv_Manager_Movinter_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif

// --------------------------------------------------------------------------
class IlvMoveInteractor : public IlvManagerViewInteractor
{
public:
    IlvMoveInteractor(IlvManager* manager, IlvView* view)
    : IlvManagerViewInteractor(manager, view),
      _deltax(0),
      _deltay(0),
      _bbox(),
      _move(0),
      _xor_rectangle(0, 0, 0, 0),
      _wasSelected(IlFalse) {}
    IlvMoveInteractor()
    : IlvManagerViewInteractor(),
      _deltax(0),
      _deltay(0),
      _bbox(),
      _move(0),
      _xor_rectangle(0, 0, 0, 0),
      _wasSelected(IlFalse) {}

    virtual void		handleEvent(IlvEvent& event);
    virtual void		handleExpose(IlvRegion* clip = 0);
    virtual void		drawGhost();
    virtual void		doIt(const IlvPoint&);
    inline const IlvRect&	getRectangle() const { return _xor_rectangle; }
    void			drawGhost(const IlvRect&, IlvRegion* clip = 0);
    void			drawGhost(IlvGraphic*, IlvRegion* clip = 0);

    IlvMoveInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    void			handleButtonDown(const IlvPoint&);
    void			handleButtonDragged(const IlvPoint&);
    void			handleButtonUp(const IlvPoint&);

    IlvPos			_deltax;
    IlvPos			_deltay;
    IlvRect			_bbox;
    IlvGraphic*			_move;
    IlvRect			_xor_rectangle;
    IlBoolean			_wasSelected;
};


ILVMGRMODULEINIT(m0_movinter);

#endif /* !__Ilv_Manager_Movinter_H */
