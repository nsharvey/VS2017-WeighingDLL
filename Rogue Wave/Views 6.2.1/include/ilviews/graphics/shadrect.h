// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/shadrect.h
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
// Declaration of the IlvShadowRectangle class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Shadrect_H
#define __Ilv_Graphics_Shadrect_H

#if !defined(__Ilv_Graphics_Rectangl_H)
#include <ilviews/graphics/rectangl.h>
#endif

#define IlvDefaultShadowThickness 4
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvShadowRectangle : public IlvFilledRectangle
{
public:
    IlvShadowRectangle(IlvDisplay*	display,
		       const IlvRect&	rect,
		       IlUShort		shadowThickness
						= IlvDefaultShadowThickness,
		       IlvPosition	shadowPosition  = IlvBottomRight,
		       IlvPalette*	palette         = 0);
    virtual ~IlvShadowRectangle();

    void		draw(IlvPort*			dst,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    void		setBackground(IlvColor* c);
    void		setForeground(IlvColor* c);
    void		setLineStyle(IlvLineStyle* style);
    void		setLineWidth(IlUShort style);
    void		setMode(IlvDrawMode m);
    void		setPalette(IlvPalette* palette);
    void		setOverwrite(IlBoolean);
    void		setAlpha(IlvIntensity);
    void		setAntialiasingMode(IlvAntialiasingMode);
    inline IlUShort	getThickness() const { return _thickness; }
    inline void		setThickness(IlUShort thickness)
			{
			    _thickness = thickness;
			}
    inline IlvPosition	getShadowPosition() const { return _shadowPosition; }
    inline void		setShadowPosition(IlvPosition shadowPosition)
			{
			    _shadowPosition = shadowPosition;
			}

    DeclareGraphicAccessors();

    static IlSymbol*	_thicknessValue;
    static IlSymbol*	_shadowPositionValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvShadowRectangle);

protected:
    IlvPalette*		_invertedPalette;
    IlUShort		_thickness;
    IlvPosition		_shadowPosition;
    IlvShadowRectangle(IlvDisplay* display,
		       IlUShort    shadowThickness = IlvDefaultShadowThickness,
		       IlvPosition shadowPosition  = IlvBottomRight,
		       IlvPalette* palette         = 0);
};

ILVVWSMODULEINIT(g0shadrect);
#endif /* !__Ilv_Graphics_Shadrect_H */
