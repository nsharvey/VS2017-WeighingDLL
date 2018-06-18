// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/dragrin.h
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
// Declaration of the IlvDragRectangleInteractor class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Dragrin_H
#define __Ilv_Manager_Dragrin_H

#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvDragRectangleInteractor
: public IlvManagerViewInteractor
{
public:
    IlvDragRectangleInteractor(IlvManager* manager,
			       IlvView*    view,
			       IlUShort    button = IlvLeftButton,
			       IlBoolean   snap   = IlTrue)
	: IlvManagerViewInteractor(manager, view),
	  _snap(snap),
	  _button(button),
	  _forcedpoint(IlFalse) { _xor_rectangle.w(0); }
    IlvDragRectangleInteractor(IlUShort  button = IlvLeftButton,
			       IlBoolean snap   = IlTrue)
	: IlvManagerViewInteractor(),
	  _snap(snap),
	  _button(button),
	  _forcedpoint(IlFalse) { _xor_rectangle.w(0); }
    // ____________________________________________________________
    inline void		setButton(IlUShort b) { _button = b;    }
    inline IlUShort	getButton()     const { return _button; }
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	drawGhost();
    virtual void	doIt(IlvRect& rect);
    virtual void	doPoint(const IlvPoint& p);
    virtual void	init();
    virtual void	abort();
    virtual void	computeForcedPoint(IlvPoint&,
					   IlvDeltaPoint& Point,
					   IlvRect&);
    inline void		setForcedPoint(IlBoolean v) { _forcedpoint = v;      }
    inline IlBoolean	getForcedPoint()      const { return _forcedpoint;   }
    inline IlvRect&	getRectangle()              { return _xor_rectangle; }

    IlvDragRectangleInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlvRect		_xor_rectangle;
    IlBoolean		_started;
    IlvPoint		_origin;
    IlBoolean		_snap;
    IlUShort		_button;
    IlBoolean		_forcedpoint;
};

ILVMGRMODULEINIT(m0_dragrin);

#endif /* !__Ilv_Manager_Dragrin_H */
