// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/shadellp.h
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
// Declaration of the IlvShadowEllipse class
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Shadellp_H
#define __Ilv_Graphics_Shadellp_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

//$doc:Shell
#define DefaulShadowEllipseThickness 4
#define USE_2_PALETTES

// --------------------------------------------------------------------------
class  IlvShadowEllipse : public IlvSimpleGraphic
{
public:
    IlvShadowEllipse(IlvDisplay*    display,
                     const IlvRect& rect,
                     IlUShort       thickness = DefaulShadowEllipseThickness,
                     IlvPalette*    palette   = 0)
    : IlvSimpleGraphic(display, palette),
      _rect(rect),
      _thickness(thickness)
    {
#if defined(USE_2_PALETTES)
        _invertedPalette = 0;
        computeInvertedPalette();
#endif /* USE_2_PALETTES */
    }
#if defined(USE_2_PALETTES)
    ~IlvShadowEllipse();
#endif // USE_2_PALETTES
    // ____________________________________________________________
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual IlBoolean	contains(const IlvPoint&       p,
				 const IlvPoint&       tp,
				 const IlvTransformer* t) const;
    virtual void	boundingBox(IlvRect&              rect,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);
    inline IlUShort	getThickness() const { return  _thickness; }
    inline void		setThickness(IlUShort thickness) 
			{
			    _thickness = thickness;
			}
    DeclareTypeInfo();
    DeclareIOConstructors(IlvShadowEllipse);

#if defined(USE_2_PALETTES)
    virtual void	setBackground(IlvColor* c);
    virtual void	setForeground(IlvColor* c);
    virtual void	setMode(IlvDrawMode m);
    virtual void	setPalette(IlvPalette*);
    void		setAlpha(IlvIntensity);
    void		setAntialiasingMode(IlvAntialiasingMode);
#endif /* USE_2_PALETTES */

protected:
    IlvRect		_rect;
    IlvDim		_thickness;
#if defined(USE_2_PALETTES)
    IlvPalette*		_invertedPalette;

    void		computeInvertedPalette();
#endif /* USE_2_PALETTES */
};

//end:Shell
#endif /* __Ilv_Graphics_Shadellp_H */
