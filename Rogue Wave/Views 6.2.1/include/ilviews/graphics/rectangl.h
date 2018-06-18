// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/rectangl.h
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
// Declaration of the IlvRectangle class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Rectangl_H
#define __Ilv_Graphics_Rectangl_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvRectangle : public IlvSimpleGraphic
{
public:
    IlvRectangle(IlvDisplay*    display,
		 const IlvRect& drawrect,
		 IlvPalette*    palette = 0)
	: IlvSimpleGraphic(display, palette),
	  _drawrect(drawrect)
    {}

    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;
    virtual void	boundingBox(IlvRect&              rect,
				    const IlvTransformer* t = 0) const;
    virtual IlBoolean	contains(const IlvPoint& p, const IlvPoint& tp,
				 const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvRectangle);

protected:
    IlvRect		_drawrect;

    IlvRectangle(IlvDisplay* display, IlvPalette* palette = 0)
	: IlvSimpleGraphic(display, palette)
    {}
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvFilledRectangle : public IlvRectangle
{
public:
    IlvFilledRectangle(IlvDisplay*    display,
		       const IlvRect& drawrect,
		       IlvPalette*    palette = 0)
	: IlvRectangle(display, drawrect, palette)
    {}

    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual IlBoolean	contains(const IlvPoint&       p,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvFilledRectangle);

protected:
    IlvFilledRectangle(IlvDisplay* display, IlvPalette* palette = 0)
	: IlvRectangle(display, palette)
    {}
};

ILVVWSMODULEINIT(g0rectangl);
#endif /* !__Ilv_Graphics_Rectangl_H */
