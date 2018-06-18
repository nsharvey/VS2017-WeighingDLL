// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/mkrelfin.h
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
// Declaration of the IlvMakeReliefRectangleInteractor class and its subtypes
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Mkrelfin_H
#define __Ilv_Manager_Mkrelfin_H

#if !defined(__Ilv_Manager_Dragrin_H)
#include <ilviews/manager/dragrin.h>
#endif
#if !defined(__Ilv_Graphics_Relfrect_H)
#include <ilviews/graphics/relfrect.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeReliefRectangleInteractor
: public IlvDragRectangleInteractor
{
public:
    IlvMakeReliefRectangleInteractor(IlvManager* manager,
				     IlvView*    view,
				     IlUShort    button = IlvLeftButton,
				     IlBoolean   snap   = IlTrue)
	: IlvDragRectangleInteractor(manager, view, button, snap),
          _thickness(IlvDefaultReliefThickness) {}
    IlvMakeReliefRectangleInteractor(IlUShort  button = IlvLeftButton,
				     IlBoolean snap   = IlTrue)
	: IlvDragRectangleInteractor(button, snap),
          _thickness(IlvDefaultReliefThickness) {}
    // ____________________________________________________________
    virtual void	drawGhost();
    virtual void	doIt(IlvRect& rect);
    inline IlUShort	getThickness() const { return _thickness; }
    inline void		setThickness(IlUShort t) { _thickness = t; }

    IlvMakeReliefRectangleInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlUShort		_thickness;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMakeReliefDiamondInteractor
: public IlvDragRectangleInteractor
{
public:
    IlvMakeReliefDiamondInteractor(IlvManager* manager,
				   IlvView*    view,
				   IlUShort    button = IlvLeftButton,
				   IlBoolean   snap   = IlTrue)
	: IlvDragRectangleInteractor(manager, view, button, snap),
          _thickness(IlvDefaultReliefThickness) {}
    IlvMakeReliefDiamondInteractor(IlUShort  button = IlvLeftButton,
				   IlBoolean snap   = IlTrue)
	: IlvDragRectangleInteractor(button, snap),
          _thickness(IlvDefaultReliefThickness) {}
    // ____________________________________________________________
    virtual void	doIt(IlvRect& rect);
    inline IlUShort	getThickness() const { return _thickness; }
    inline void		setThickness(IlUShort t) { _thickness = t; }

    IlvMakeReliefDiamondInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlUShort		_thickness;
};

ILVMGRMODULEINIT(m0_mkrelfin);

#endif /* !__Ilv_Manager_Mkrelfin_H */
