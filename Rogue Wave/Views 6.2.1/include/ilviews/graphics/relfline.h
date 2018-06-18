// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/relfline.h
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
// Declaration of the IlvReliefLine class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Relfline_H
#define __Ilv_Graphics_Relfline_H

#if !defined(__Ilv_Graphics_Line_H)
#include <ilviews/graphics/line.h>
#endif

#if !defined(__Ilv_Base_Look_H)
#include <ilviews/base/look.h>
#endif

#define IlvDefaultLineShadowThickness 1

class IlvReliefLine;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvReliefLineLFHandler : public IlvObjectLFHandler
{
public:
    IlvReliefLineLFHandler(IlvLookFeelHandler* lf);

    virtual IlvPalette*	getBottomShadow(const IlvReliefLine*)const = 0;
    virtual IlvPalette*	getTopShadow(const IlvReliefLine*) const = 0;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvDefaultReliefLineLFHandler
    : public IlvReliefLineLFHandler
{
public:
    IlvDefaultReliefLineLFHandler(IlvLookFeelHandler* lf)
	: IlvReliefLineLFHandler(lf)
    {}

    virtual IlvPalette*	getBottomShadow(const IlvReliefLine*) const;
    virtual IlvPalette*	getTopShadow(const IlvReliefLine*) const;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvReliefLine : public IlvLine
{
public:
    IlvReliefLine(IlvDisplay*     display,
		  const IlvPoint& from,
		  const IlvPoint& to,
		  IlUShort        thickness = IlvDefaultLineShadowThickness,
		  IlvPalette*     palette   = 0);
    virtual ~IlvReliefLine();

    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* t = 0) const;
    virtual void	setBackground(IlvColor* c);
    virtual void	setForeground(IlvColor* c);
    virtual void	invert(IlBoolean);
    virtual void	setLineStyle(IlvLineStyle* style);
    virtual void	setLineWidth(IlUShort width);
    virtual void	setMode(IlvDrawMode m);
    virtual void	setOverwrite(IlBoolean value);
    virtual void	setPalette(IlvPalette*);
    virtual void	setAlpha(IlvIntensity);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);
    virtual void 	changeLook(const IlvLookFeelHandler*);
    IlUShort		getThickness() const { return _thickness; }
    void		setThickness(IlUShort value) { _thickness = value; }

    DeclareGraphicAccessors();
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvReliefLine);

    static IlSymbol*	_thicknessValue;

protected:
    void		computePalettes();
    void		computePoints(IlvPoint*			top,
				      const IlvTransformer*	t = 0) const;

    IlUShort		_thickness;
    IlvPalette*		_topshadow;
    IlvPalette*		_bottomshadow;
};

ILVVWSMODULEINIT(g0relfline);
#endif /* !__Ilv_Graphics_Relfline_H */
