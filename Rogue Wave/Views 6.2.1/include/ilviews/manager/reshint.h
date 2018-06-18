// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/reshint.h
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
// Declaration of the IlvReshapeInteractor class
// Not part of any Rogue Wave Views library
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Reshint_H
#define __Ilv_Manager_Reshint_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Graphics_Select_H)
#include <ilviews/graphics/select.h>
#endif

// --------------------------------------------------------------------------
class IlvReshapeInteractor : public IlvManagerViewInteractor
{
public:
    IlvReshapeInteractor(IlvManager* manager, IlvView* view)
    : IlvManagerViewInteractor(manager, view),
      _oppositex(),
      _oppositey(),
      _bbox(),
      _direction(IlvBadPosition),
      _reshape(0),
      _xor_rectangle(0, 0, 0, 0) {}
    IlvReshapeInteractor()
    : IlvManagerViewInteractor(),
      _oppositex(),
      _oppositey(),
      _bbox(),
      _direction(IlvBadPosition),
      _reshape(0),
      _xor_rectangle(0, 0, 0, 0) {}

    virtual void		handleEvent(IlvEvent& event);
    virtual void		handleExpose(IlvRegion* rect = 0);
    virtual void		drawGhost();
    virtual void		drawGhost(IlvGraphic* obj,IlvRegion* clip = 0);
    virtual void		doIt(IlvGraphic*, const IlvRect&);
    inline const IlvRect&	getRectangle() { return _xor_rectangle; }

    IlvReshapeInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlvPos			_oppositex, _oppositey;
    IlvRect			_bbox;
    IlvDirection		_direction;
    IlvDrawSelection*		_reshape;
    IlvRect			_xor_rectangle;

    void			storeOpposite(IlvGraphic* obj);
    void			handleButtonDown(const IlvPoint& point);
    void			handleButtonDragged(const IlvPoint& point);
    void			handleButtonUp(const IlvPoint& point);
};

ILVMGRMODULEINIT(m0_reshint);

#endif /* !__Ilv_Manager_Reshint_H */
