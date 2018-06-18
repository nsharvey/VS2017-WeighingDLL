// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/relfrect.h
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
// Declaration of the IlvReliefRectangle and IlvReliefDiamond classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Relfrect_H
#define __Ilv_Graphics_Relfrect_H

#if !defined(__Ilv_Graphics_Rectangl_H)
#include <ilviews/graphics/rectangl.h>
#endif

#define DeclareAccessors(c) \
friend class c##_Accessors

#define IlvDefaultReliefThickness 2
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvReliefRectangle : public IlvFilledRectangle
{
public:
    IlvReliefRectangle(IlvDisplay*    display,
		       const IlvRect& rect,
		       IlUShort       thickness = IlvDefaultReliefThickness,
		       IlvPalette*    palette   = 0);
    ~IlvReliefRectangle();

    virtual void	invert(IlBoolean = IlFalse);
    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setLineStyle(IlvLineStyle*);
    virtual void	setLineWidth(IlUShort);
    virtual void	setFillStyle(IlvFillStyle);
    virtual void	setPattern(IlvPattern*);
    virtual void	setColorPattern(IlvColorPattern*);
    virtual void	setGradientPattern(IlvGradientPattern*);
    virtual void	setFont(IlvFont*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setArcMode(IlvArcMode);
    virtual void	setFillRule(IlvFillRule);
    virtual void	setPalette(IlvPalette*);
    virtual void	setAlpha(IlvIntensity);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);
    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;
    inline IlUShort	getThickness() const { return _thickness; }
    inline void		setThickness(IlUShort thickness)
			{
			    _thickness = thickness;
			}

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvReliefRectangle);
    DeclareAccessors(IlvReliefRectangle);

protected:
    IlUShort		_thickness;
    IlvPalette*		_invpalette;
    IlvPalette*		_topshadow;
    IlvPalette*		_bottomshadow;
    IlvPalette*		_selpalette;
    // ____________________________________________________________
    void		computePalettes();
    inline void		unLockPalettes()
			{
			    _invpalette->unLock();
			    _topshadow->unLock();
			    _bottomshadow->unLock();
			    _selpalette->unLock();
			}
    IlvReliefRectangle(IlvDisplay*,
		       IlUShort    = IlvDefaultReliefThickness,
		       IlvPalette* = 0);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvReliefDiamond : public IlvReliefRectangle
{
public:
    IlvReliefDiamond(IlvDisplay*    display,
		     const IlvRect& rect,
		     IlUShort       thickness = IlvDefaultReliefThickness,
		     IlvPalette*    palette   = 0)
	: IlvReliefRectangle(display, rect, thickness, palette)
    {}

    void		draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvReliefDiamond);
};

ILVVWSMODULEINIT(g0relfrect);
#endif /* __Ilv_Graphics_Relfrect_H */
