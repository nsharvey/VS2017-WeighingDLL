// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/grid.h
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
// Declaration of the IlvManagerGrid class
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Grid_H
#define __Ilv_Manager_Grid_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Observer_H)
#include <ilviews/base/observer.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerGrid : public IlvObservable
{
public:
    IlvManagerGrid(IlvPalette*     palette,
		   const IlvPoint& origin,
		   IlvDim          spacingx,
		   IlvDim          spacingy,
		   IlBoolean       visible = IlTrue,
		   IlBoolean       active  = IlTrue,
		   IlvDim          shownx  = 1,
		   IlvDim          showny  = 1);
    virtual ~IlvManagerGrid();
    // ____________________________________________________________
    virtual void	snap(IlvPoint& p);
    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t,
			     const IlvRegion&      clip);
    void		setForeground(IlvColor* foreground);
    inline IlvColor*	getForeground() const
			{
			    return _palette ? _palette->getForeground() : 0;
			}
    inline IlvPalette*  getPalette() const { return _palette; }
    inline void		getOrigin(IlvPoint& origin) const
			{
			    origin.move(_origx, _origy);
			}
    inline void		setOrigin(const IlvPoint& origin)
			{
			    _origx = origin.x();
			    _origy = origin.y();
			    notify();
			}
    inline void		getSpacings(IlvDim& sx, IlvDim& sy) const
			{
			    sx = _spacingx;
			    sy = _spacingy;
			}
    inline void		setSpacings(IlvDim sx, IlvDim sy)
			{
			    _spacingx = sx;
			    _spacingy = sy;
			    notify();
			}
    inline IlBoolean	isVisible() const { return _visible;}
    inline void		setVisible(IlBoolean v) { _visible = v; notify(); }
    inline IlBoolean	isActive() const { return _active; }
    inline void		setActive(IlBoolean active)
			{
			    _active = active;
			    notify();
			}
    inline IlBoolean	drawOnTop() const { return _top; }
    inline void		setDrawOnTop(IlBoolean b) { _top = b; notify(); }
    inline void		getShown(IlvDim& sx, IlvDim& sy) const
			{
			    sx = _shownx;
			    sy = _showny;
			}
    inline void		setShown(IlvDim sx, IlvDim sy)
			{
			    _shownx = sx;
			    _showny = sy;
			    notify();
			}

protected:
    IlvPalette*		_palette;
    IlvPos		_origx;
    IlvPos		_origy;
    IlvDim		_spacingx;
    IlvDim		_spacingy;
    IlvDim		_shownx;
    IlvDim		_showny;
    IlBoolean		_visible;
    IlBoolean		_active;
    IlBoolean		_top;
};

#endif /* !__Ilv_Manager_Grid_H */
