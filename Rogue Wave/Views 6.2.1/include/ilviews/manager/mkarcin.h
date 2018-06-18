// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/mkarcin.h
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
// Declaration of the IlvMakeEllipseInteractor class and its subtypes
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Mkarcin_H
#define __Ilv_Manager_Mkarcin_H

#if !defined(__Ilv_Manager_Dragrin_H)
#include <ilviews/manager/dragrin.h>
#endif
#if !defined(__Ilv_Graphics_Arc_H)
#include <ilviews/graphics/arc.h>
#endif
#if !defined(__Ilv_Graphics_Ellipse_H)
#include <ilviews/graphics/ellipse.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeEllipseInteractor
    : public IlvDragRectangleInteractor
{
public:
    IlvMakeEllipseInteractor(IlvManager* manager, IlvView* view)
	: IlvDragRectangleInteractor(manager, view)
    {}
    IlvMakeEllipseInteractor(): IlvDragRectangleInteractor() {};

    virtual void	drawGhost();
    virtual void	doIt(IlvRect& rect);

    IlvMakeEllipseInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeFilledEllipseInteractor
    : public IlvMakeEllipseInteractor
{
public:
    IlvMakeFilledEllipseInteractor(IlvManager* manager, IlvView* view)
	: IlvMakeEllipseInteractor(manager, view)
    {}
    IlvMakeFilledEllipseInteractor(): IlvMakeEllipseInteractor() {};

    virtual void	drawGhost();
    virtual void	doIt(IlvRect& rect);

    IlvMakeFilledEllipseInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();
};


// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeArcInteractor : public IlvManagerViewInteractor
{
public:
    IlvMakeArcInteractor(IlvManager* manager, IlvView* view)
	: IlvManagerViewInteractor(manager, view)
    {
	_rectangledone = IlFalse;
	_xor_rectangle.resize(0, 0);
    }
    IlvMakeArcInteractor()
	: IlvManagerViewInteractor()
    {
	_rectangledone = IlFalse;
	_xor_rectangle.resize(0, 0);
    }

    virtual IlBoolean	handleEvent(IlvEvent& event);
    void		drawGhost();
    virtual void	doIt(IlvRect& rect, IlFloat start, IlFloat range);
    void		abort();
    inline void		getRectangle(IlvRect& rect) { rect = _xor_rectangle; }
    inline IlFloat	firstAngle() { return (IlFloat)_angle1; }
    inline IlFloat	secondAngle() { return (IlFloat)_angle2; }

    IlvMakeArcInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlBoolean		selected(int angle, IlvEvent& event);
    void		newAngle(IlvEvent& event);
    virtual void	drawArc();

    IlvRect		_xor_rectangle;
    IlvPos		_firstx;
    IlvPos		_firsty;
    IlBoolean		_snap;
    IlBoolean		_rectangledone;
    IlFloat		_angle1;
    IlFloat		_angle2;
    int			_selectedpoint;		// 1: first, 2: second
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeFilledArcInteractor : public IlvMakeArcInteractor
{
public:
    IlvMakeFilledArcInteractor(IlvManager* manager, IlvView* view)
	: IlvMakeArcInteractor(manager, view)
    {};
    IlvMakeFilledArcInteractor() : IlvMakeArcInteractor() {};

    virtual void	doIt(IlvRect& rect, IlFloat start, IlFloat range);

    IlvMakeFilledArcInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    void		drawArc();
};

ILVMGRMODULEINIT(m0_mkarcin);

#endif /* !__Ilv_Manager_Mkarcin_H */
