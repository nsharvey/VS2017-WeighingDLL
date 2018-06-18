// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/arc.h
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
// Declaration of the IlvArc and IlvFilledArc classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Arc_H
#define __Ilv_Graphics_Arc_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvArc : public IlvSimpleGraphic
{
public:
    IlvArc(IlvDisplay*		display,
	   const IlvRect&	rect,
	   IlFloat		startAngle =  0,
	   IlFloat		angleRange = 90,
	   IlvPalette*		palette	   =  0);

    virtual void	draw(IlvPort*,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	boundingBox(IlvRect&		  rect,
				    const IlvTransformer* t = 0) const;
    virtual IlBoolean	contains(const IlvPoint&	p,
				 const IlvPoint&,
				 const IlvTransformer*	t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	rotate(const IlvPoint&, IlFloat angle);
    virtual void	symmetry(IlvDirection);
    inline IlFloat	getStartAngle() const { return _angle1; }
    inline void		setStartAngle(IlFloat startAngle)
			{
			    _angle1 = clampAngle(startAngle);
			}
    inline IlFloat	getDeltaAngle() const { return _angle2; }
    void		setDeltaAngle(IlFloat angleRange);
    virtual void	print(ILVSTDPREF ostream&, int level = 0) const;

    DeclareGraphicAccessors();

    static IlSymbol*	_startAngleValue;
    static IlSymbol*	_deltaAngleValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvArc);

    inline
    const IlvRect&	getBBox() const { return _bbox; }

protected:
    IlFloat		clampAngle(double);

    IlvRect		_bbox;
    IlFloat		_angle1, _angle2;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvFilledArc : public IlvArc
{
public:
    IlvFilledArc(IlvDisplay*	display,
		 const IlvRect&	rect,
		 IlFloat	startAngle	=  0,
		 IlFloat	angleRange	= 90,
		 IlvPalette*	palette		=  0)
	: IlvArc(display, rect, startAngle, angleRange, palette)
    {}

    virtual void	draw(IlvPort*,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	boundingBox(IlvRect&		  rect,
				    const IlvTransformer* t = 0) const;
    virtual IlBoolean	contains(const IlvPoint&	p,
				 const IlvPoint&,
				 const IlvTransformer*	t = 0) const;
    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvFilledArc);
};

ILVVWSMODULEINIT(g0arc);
#endif /* !__Ilv_Graphics_Arc_H */
