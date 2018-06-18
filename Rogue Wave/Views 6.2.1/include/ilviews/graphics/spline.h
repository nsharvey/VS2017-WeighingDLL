// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/spline.h
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
// Declaration of the IlvSpline class and its subtypes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Spline_H
#define __Ilv_Graphics_Spline_H

#if !defined(__Ilv_Graphics_Polypts_H)
#include <ilviews/graphics/polypts.h>
#endif
#if !defined(__Ilv_Graphics_Polyptsel_H)
#include <ilviews/graphics/polyptsel.h>
#endif
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvSpline : public IlvPolyPoints
{
public:
    IlvSpline(IlvDisplay* display,
	      IlUInt      count,
	      IlvPoint*   points,
	      IlvPalette* palette     = 0,
	      IlBoolean   computeBBox = IlTrue);
    IlvSpline(IlvDisplay*    display,
	      const IlvRect& arcRect,
	      IlFloat        startAngle,
              IlFloat        angleRange,
	      IlvPalette*    palette = 0,
	      IlBoolean      computeBBox = IlTrue);
    IlvSpline(IlvInputFile& is, IlvPalette*, IlBoolean = IlTrue);
    IlvSpline(const IlvSpline& source);

    virtual void	computeBBox(IlvRect& bbox);
    virtual IlBoolean	contains(const IlvPoint&       p,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

    DeclareInterface(Selection);
    DeclareLazyTypeInfoRO();
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvClosedSpline : public IlvSpline
{
public:
    IlvClosedSpline(IlvDisplay* display,
		    IlUInt      count,
		    IlvPoint*   points,
		    IlvPalette* palette = 0);
    IlvClosedSpline(IlvDisplay*    display,
		    const IlvRect& box,
		    IlvPalette*    palette     = 0);

    virtual void	computeBBox(IlvRect& bbox);
    virtual IlBoolean	contains(const IlvPoint&     p,
				 const IlvPoint&     tp,
			       const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    IlvClosedSpline(IlvInputFile& is, IlvPalette*, IlBoolean = IlTrue);
    IlvClosedSpline(const IlvClosedSpline&);

    DeclareLazyTypeInfoRO();
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvFilledSpline : public IlvClosedSpline
{
public:
    IlvFilledSpline(IlvDisplay* display,
		    IlUInt      count,
		    IlvPoint*   points,
		    IlvPalette* palette = 0);
    IlvFilledSpline(IlvDisplay*    display,
		    const IlvRect& box,
		    IlvPalette*    palette = 0);
    IlvFilledSpline(IlvInputFile&, IlvPalette*, IlBoolean = IlTrue);
    IlvFilledSpline(const IlvFilledSpline&);

    virtual IlBoolean	contains(const IlvPoint&       p,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;

    DeclareLazyTypeInfoRO();
};

ILVVWSMODULEINIT(g0spline);
#endif /* !_Ilv_Graphics_Spline_H */
