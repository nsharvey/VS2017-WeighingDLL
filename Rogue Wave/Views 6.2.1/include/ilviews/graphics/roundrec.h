// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/roundrec.h
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
// Declaration of the IlvRoundRectangle class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Roundrec_H
#define __Ilv_Graphics_Roundrec_H

#if !defined(__Ilv_Graphics_Rectangl_H)
#include <ilviews/graphics/rectangl.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvRoundRectangle : public IlvRectangle
{
public:
    IlvRoundRectangle(IlvDisplay*	display,
		      const IlvRect&	rect,
		      IlUShort		radius  = 0,
		      IlvPalette*	palette = 0)
	: IlvRectangle(display, rect, palette)
    {
	_radius = (radius > 0)
	    ? radius
	    : (IlUShort)(IlMin(rect.w(), rect.h())>>3);
    }

    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    inline IlUShort	getRadius() const { return _radius;  }
    inline void		setRadius(IlUShort radius) { _radius = radius;}

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvRoundRectangle);

    DeclareGraphicAccessors();
    static IlSymbol*	_RadiusValue;

protected:
    IlUShort		_radius;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvFilledRoundRectangle : public IlvFilledRectangle
{
public:
    IlvFilledRoundRectangle(IlvDisplay*		display,
			    const IlvRect&	rect,
			    IlUShort		radius  = 0,
			    IlvPalette*		palette = 0)
	: IlvFilledRectangle(display, rect, palette)
    {
	    _radius = (radius > 0)
		? radius
		: (IlUShort)(IlMin(rect.w(), rect.h())>>3);
    }

    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    inline IlUShort	getRadius() const { return _radius; }
    inline void		setRadius(IlUShort radius) { _radius = radius;}

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvFilledRoundRectangle);

    DeclareGraphicAccessors();
    static IlSymbol*	_RadiusValue;

protected:
    IlUShort		_radius;
};

ILVVWSMODULEINIT(g0roundrec);
#endif /* __Ilv_Graphics_Roundrec_H */

