// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/cirscale.h
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
// Declaration of the IlvCircularScale class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Cirscale_H
#define __Ilv_Graphics_Cirscale_H

#if !defined(__Ilv_Graphics_Scale_H)
#include <ilviews/graphics/scale.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvCircularScale : public IlvScale
{
public:
    IlvCircularScale(IlvDisplay*	display,
		     const IlvRect&	drawrect,
		     const char*	format, // May be 0
		     IlFloat		min,
		     IlFloat		max,
		     IlFloat		start		=   0.,
		     IlFloat		range		= 180.,
		     IlUShort		steps		=   0,
		     IlUShort		substeps	=   0,
		     IlBoolean		in		= IlFalse,
		     IlUShort		stepsize	=  10,
		     IlUShort		substepsize	=   5,
		     IlvPalette*	palette		=   0)
	: IlvScale(display,
		   drawrect,
		   format,
		   min,
		   max,
		   steps,
		   substeps,
		   stepsize,
		   substepsize,
		   palette),
	  _in(in),
	  _start(start),
	  _range(range)
    {}
    IlvCircularScale(IlvDisplay*	display,
		     const IlvRect&	drawrect,
		     char*		labels[],
		     IlFloat		start		=   0.,
		     IlFloat		range		= 180.,
		     IlUShort		steps		=   0,
		     IlUShort		substeps	=   0,
		     IlBoolean		in		= IlFalse,
		     IlUShort		stepsize	=  10,
		     IlUShort		substepsize	=   5,
		     IlvPalette*	palette		=   0)
	: IlvScale(display,
		   drawrect,
		   labels,
		   steps,
		   substeps,
		   stepsize,
		   substepsize,
		   palette),
	  _in(in),
	  _start(start),
	  _range(range)
    {}

    inline IlFloat	getStart() const { return _start;  }
    inline void		setStart(IlFloat start) { _start = start; }
    inline IlFloat	getRange() const { return _range;  }
    inline void		setRange(IlFloat range) { _range = range; }
    inline IlBoolean	getDirection() const { return _in; }
    inline void		setDirection(IlBoolean in) { _in = in; }

    virtual void	draw(IlvPort*,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;
    virtual IlBoolean	contains(const IlvPoint&	p,
				 const IlvPoint&	tp,
				 const IlvTransformer*	t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);

    DeclareGraphicAccessors();

    static IlSymbol*	_startValue;
    static IlSymbol*	_rangeValue;
    static IlSymbol*	_directionValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvCircularScale);

protected:
    IlBoolean	_in; // (in/out)
    IlFloat	_start, _range;
};

ILVVWSMODULEINIT(g0cirscale);
#endif /* !__Ilv_Graphics_Cirscale_H */
