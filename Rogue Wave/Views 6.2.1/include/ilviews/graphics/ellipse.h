// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/ellipse.h
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
// Declaration of the IlvEllipse and IlvFilledEllipse classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Ellipse_H
#define __Ilv_Graphics_Ellipse_H

#define IlvTWOPI 360

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvEllipse : public IlvSimpleGraphic
{
public:
    IlvEllipse(IlvDisplay*     display,
	       const IlvPoint& center,
	       IlvDim          radius,
	       IlvPalette*     palette = 0);
    IlvEllipse(IlvDisplay*    display,
	       const IlvRect& drawrect,
	       IlvPalette*    palette = 0);

    virtual IlBoolean	contains(const IlvPoint&       p,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual void	boundingBox(IlvRect&              rect,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);
    void		rotate(const IlvPoint& center, IlFloat angle);

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvEllipse);

protected:
    IlvRect		_drawrect;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvFilledEllipse : public IlvEllipse
{
public:
    IlvFilledEllipse(IlvDisplay*     display,
		     const IlvPoint& center,
		     IlvDim          radius,
		     IlvPalette*     palette = 0)
	: IlvEllipse(display, center, radius, palette)
    {}
    IlvFilledEllipse(IlvDisplay*    display,
		     const IlvRect& drawrect,
		     IlvPalette*    palette = 0)
	: IlvEllipse(display, drawrect, palette)
    {}

    virtual IlBoolean	contains(const IlvPoint& p,
				 const IlvPoint& tp,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvFilledEllipse);
};

ILVVWSMODULEINIT(g0ellipse);
#endif /* !__Ilv_Graphics_Ellipse_H */
