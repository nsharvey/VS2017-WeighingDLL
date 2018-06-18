// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/polyline.h
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
// Declaration of the IlvPolyline, IlvPolygon and IlvArrowPolyline classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Polyline_H
#define __Ilv_Graphics_Polyline_H

#if !defined(__Ilv_Graphics_Polypts_H)
#include <ilviews/graphics/polypts.h>
#endif

#define IlvExtPolyline IlvPolyline
#define IlvExtPolygon  IlvPolygon

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvPolyline : public IlvPolyPoints
{
public:
    IlvPolyline(IlvDisplay* display,
		IlUInt      count,
		IlvPoint*   points,
		IlvPalette* palette = 0)
    : IlvPolyPoints(display, count, points,palette, IlTrue)
    {}
    IlvPolyline(IlvDisplay*     display,
		const IlvPoint& p1,
		const IlvPoint& p2,
		const IlvPoint& p3,
		const IlvPoint& p4,
		IlvPalette*     palette = 0);
    IlvPolyline(IlvDisplay*    display,
		const IlvRect& rect,
		IlvPalette*    palette = 0);
    IlvPolyline(IlvDisplay*     display,
		const IlvPoint& center,
		IlUInt          count,
		IlvDim          outerRadius,
		IlvDim          innerRadius = 0,
		IlBoolean       crossed = IlFalse,
		IlvPalette*     palette = 0);
    // ____________________________________________________________
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t = 0,
			     const IlvRegion*      clip = 0) const;
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvPolyline);

protected:
    IlvPolyline(IlvDisplay* display, IlvPalette* palette = 0)
	: IlvPolyPoints(display, palette)
    {}
    void		extendBBox(IlUInt count, const IlvPoint* points);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvPolygon : public IlvPolyline
{
public:
    IlvPolygon(IlvDisplay* display,
	       IlUInt      count,
	       IlvPoint*   points,
	       IlvPalette* palette = 0)
	: IlvPolyline(display, count, points, palette)
    {}
    IlvPolygon(IlvDisplay*     display,
	       const IlvPoint& p1,
	       const IlvPoint& p2,
	       const IlvPoint& p3,
	       const IlvPoint& p4,
	       IlvPalette*     palette = 0);
    IlvPolygon(IlvDisplay*    display,
	       const IlvRect& rect,
	       IlvPalette*    palette = 0);
    IlvPolygon(IlvDisplay*     display,
	       const IlvPoint& center,
	       IlUInt          count,
	       IlvDim          outerRadius,
	       IlvDim          innerRadius = 0,
	       IlBoolean       crossed = IlFalse,
	       IlvPalette*     palette = 0);

    virtual void	draw(IlvPort*,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvPolygon);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvArrowPolyline : public IlvPolyline
{
public:
    IlvArrowPolyline(IlvDisplay* display,
		     IlBoolean   allLines,
		     IlFloat     atpos,
		     IlUInt      count,
		     IlvPoint*   points,
		     IlvPalette* palette = 0)
	: IlvPolyline(display, count, points, palette),
	  _alllines(allLines),
	  _atpos(atpos)
      {}
    IlvArrowPolyline(IlvDisplay*     display,
		     IlBoolean       allLines,
		     IlFloat         atpos,
		     const IlvPoint& p1,
		     const IlvPoint& p2,
		     const IlvPoint& p3,
		     const IlvPoint& p4,
		     IlvPalette*     palette = 0)
	: IlvPolyline(display, p1, p2, p3, p4, palette),
	  _alllines(allLines),
	  _atpos(atpos)
    {}
    // ____________________________________________________________
    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;
    void		boundingBox(IlvRect&, const IlvTransformer* = 0) const;
    inline void		setArrowPosition(IlFloat p) { _atpos = p; }
    inline IlFloat	getArrowPosition() const { return _atpos;}
    void		useAllLines(IlBoolean value) { _alllines = value;}

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvArrowPolyline);

protected:
    IlBoolean		_alllines;
    IlFloat		_atpos;
};

ILVVWSMODULEINIT(g0polyline);
#endif /* !__Ilv_Graphics_Polyline_H */
