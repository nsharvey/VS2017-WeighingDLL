// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/cirgauge.h
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
// Declaration of the IlvCircularGauge class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Cirgauge_H
#define __Ilv_Graphics_Cirgauge_H

#if !defined(__Ilv_Graphics_Gauge_H)
#include <ilviews/graphics/gauge.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvCircularGauge : public IlvGauge
{
public:
    IlvCircularGauge(IlvDisplay*	display,
		     const IlvRect&	drawrect,
		     IlFloat		min	=   0,
		     IlFloat		max	= 100,
		     IlFloat		value	=  50,
		     IlFloat		start	=   0,
		     IlFloat		range	= 180,
		     IlvPalette*	palette	=   0)
	: IlvGauge(display, drawrect, min, max, value, palette),
	  _start(start),
	  _range(range)
    {}

    virtual IlUInt	computeNeedlePoints(IlvPoint* points,
					    const IlvTransformer* t = 0) const;
    inline IlFloat	getStart() const { return _start;  }
    inline void		setStart(IlFloat start) { _start = start; }
    inline IlFloat	getRange() const { return _range;  }
    inline void		setRange(IlFloat range) { _range = range; }
    virtual void	drawValue(IlvPort*,
				  const IlvTransformer*	t = 0,
				  const IlvRegion*	clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;
    virtual IlBoolean	contains(const IlvPoint&	p,
				 const IlvPoint&	tp,
				 const IlvTransformer*	t = 0) const;
    virtual IlFloat	requestValue(const IlvPoint&,
				     const IlvTransformer*,
				     IlBoolean&) const;
    virtual void	bboxRange(IlFloat		v1,
				  IlFloat		v2,
				  IlvRect&		rect,
				  const IlvTransformer*	t = 0) const;

    DeclareGraphicAccessors();

    static IlSymbol*	_startValue;
    static IlSymbol*	_rangeValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvCircularGauge);

protected:
    IlFloat		_start;
    IlFloat		_range;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvFilledCircularGauge : public IlvCircularGauge
{
public:
    IlvFilledCircularGauge(IlvDisplay*		display,
			   const IlvRect&	drawrect,
			   IlFloat		min	=   0,
			   IlFloat		max	= 100,
			   IlFloat		value	=  50,
			   IlFloat		start	=   0,
			   IlFloat		range	= 180,
			   IlvPalette*		palette	= 0)
	: IlvCircularGauge(display,
			   drawrect,
			   min,
			   max,
			   value,
			   start,
			   range,
			   palette)
    {}

    virtual void	drawValue(IlvPort*,
				  const IlvTransformer*	t    = 0,
				  const IlvRegion*	clip = 0) const;
    virtual IlFloat	requestValue(const IlvPoint&,
				     const IlvTransformer*,
				     IlBoolean&) const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvFilledCircularGauge);
};

ILVVWSMODULEINIT(g0cirgauge);
#endif /* !__Ilv_Graphics_Cirgauge_H */
