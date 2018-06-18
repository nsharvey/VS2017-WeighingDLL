// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/line.h
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
// Declaration of the IlvLine class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Line_H
#define __Ilv_Graphics_Line_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvLine : public IlvSimpleGraphic
{
public:
    IlvLine(IlvDisplay*		display,
	    const IlvPoint&	from,
	    const IlvPoint&	to,
	    IlvPalette*		palette = 0)
	: IlvSimpleGraphic(display, palette),
	  _from(from),
	  _to(to)
    {}

    virtual IlBoolean	contains(const IlvPoint&	p,
				 const IlvPoint&	tp,
				 const IlvTransformer*	t) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	boundingBox(IlvRect&		  rect,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	symmetry(IlvDirection);
    inline
    const IlvPoint&	getFrom() const { return _from; }
    inline void		setFrom(const IlvPoint& p) { _from = p; }
    inline
    const IlvPoint&	getTo() const { return _to; }
    inline void		setTo(const IlvPoint& to) { _to = to; }
    virtual void	print(ILVSTDPREF ostream&, int detail = 0) const;

    DeclareInterface(Selection);
    DeclareInterface(Shape);
    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvLine);
    DeclareGraphicAccessors();

    static IlSymbol*	_fromValue;
    static IlSymbol*	_toValue;

protected:
    IlvPoint		_from;
    IlvPoint		_to;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvArrowLine : public IlvLine
{
public:
    IlvArrowLine(IlvDisplay*		display,
		 IlFloat		atPos,
		 const IlvPoint&	from,
		 const IlvPoint&	to,
		 IlvPalette*		palette = 0)
	: IlvLine(display, from, to, palette),
	  _atpos(atPos)
    {}

    virtual void	boundingBox(IlvRect&		  rect,
				    const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t    = 0,
			     const IlvRegion*		clip = 0) const;
    inline void		setArrowPosition(IlFloat atPos) { _atpos = atPos; }
    inline IlFloat	getArrowPosition() const { return _atpos; }

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvArrowLine);
    DeclareGraphicAccessors();

    static IlSymbol*	_atposValue;

protected:
    IlFloat		_atpos;
};

ILVVWSMODULEINIT(g0line);
#endif /* !__Ilv_Graphics_Line_H */
