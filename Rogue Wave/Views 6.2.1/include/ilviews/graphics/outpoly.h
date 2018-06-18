// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/outpoly.h
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
// Declaration of the IlvOutlinePolygon class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Outpoly_H
#define __Ilv_Graphics_Outpoly_H

#if !defined(__Ilv_Graphics_Polyline_H)
#include <ilviews/graphics/polyline.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvOutlinePolygon : public IlvPolygon
{
public:
    IlvOutlinePolygon(IlvDisplay* display,
		      IlUInt      count,
		      IlvPoint*   points,
		      IlvPalette* palette = 0)
    : IlvPolygon(display, count, points, palette),
      _invertedPalette(0)
    {
	computePalette();
    }
    virtual ~IlvOutlinePolygon();
    // ____________________________________________________________
    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setLineWidth(IlUShort);
    virtual void	setLineStyle(IlvLineStyle*);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setPalette(IlvPalette*);
    virtual void	setAlpha(IlvIntensity);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);
    virtual void	invert(IlBoolean);
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;
    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvOutlinePolygon);

protected:
    IlvPalette*		_invertedPalette;
    void		computePalette();
};

ILVVWSMODULEINIT(g0outpoly);
#endif /* !__Ilv_Graphics_Outpoly_H */
