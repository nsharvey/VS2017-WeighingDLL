// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/mklinein.h
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
// Declaration of the IlvMakeLineInteractor class and its subtypes
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Mklinein_H
#define __Ilv_Manager_Mklinein_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Graphics_Line_H)
#include <ilviews/graphics/line.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeLineInteractor
: public IlvManagerViewInteractor
{
public:
    IlvMakeLineInteractor(IlvManager* manager, IlvView* view)
	: IlvManagerViewInteractor(manager, view), _prev(0, 0), _first(0, 0) {}
    IlvMakeLineInteractor()
	: IlvManagerViewInteractor(), _prev(0, 0), _first(0, 0) {}
    // ____________________________________________________________
    IlBoolean		handleEvent(IlvEvent& event);
    virtual void	drawGhost();
    virtual void	doIt(IlvPoint& from, IlvPoint& to);
    virtual void	abort() ;
    inline void		getLine(IlvPoint& from, IlvPoint& to)
			{
			    from  = _first;
			    to    = _prev;
			}

    IlvMakeLineInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlvPoint		_prev;
    IlvPoint		_first;
    IlBoolean		_begin_line;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeArrowLineInteractor
: public IlvMakeLineInteractor
{
public:
    IlvMakeArrowLineInteractor(IlvManager* manager, IlvView* view)
	: IlvMakeLineInteractor(manager, view) {}
    IlvMakeArrowLineInteractor()
	: IlvMakeLineInteractor() {}
    // ____________________________________________________________
    virtual void	drawGhost();
    virtual void	doIt(IlvPoint& from, IlvPoint& to);

    IlvMakeArrowLineInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

// --------------------------------------------------------------------------
#if !defined(__Ilv_Graphics_Relfline_H)
#include <ilviews/graphics/relfline.h>
#endif
class ILVMGREXPORTED IlvMakeReliefLineInteractor
: public IlvMakeLineInteractor
{
public:
    IlvMakeReliefLineInteractor(IlvManager* manager, IlvView* view)
	: IlvMakeLineInteractor(manager, view),
          _thickness(IlvDefaultLineShadowThickness) {}
    IlvMakeReliefLineInteractor()
	: IlvMakeLineInteractor(),
          _thickness(IlvDefaultLineShadowThickness) {}
    // ____________________________________________________________
    virtual void	doIt(IlvPoint& from, IlvPoint& to);
    inline IlUShort	getThickness()     const { return _thickness; }
    inline void		setThickness(IlUShort t) { _thickness = t;    }

    IlvMakeReliefLineInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlUShort		_thickness;
};

ILVMGRMODULEINIT(m0_mklinein);

#endif /* !__Ilv_Manager_MklineinH */
