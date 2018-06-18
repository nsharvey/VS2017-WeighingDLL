// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/relfpoly.h
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
// Declaration of the IlvReliefPolyline and IlvReliefPolygon classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Relfpoly_H
#define __Ilv_Graphics_Relfpoly_H

#if !defined(__Ilv_Graphics_Polyline_H)
#include <ilviews/graphics/polyline.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvReliefPolyline
: public IlvPolyline
{
public:
    IlvReliefPolyline(IlvDisplay* display,
		      IlUInt     count,
		      IlvPoint*   points,
		      IlUShort   thickness,
		      IlvPalette* palette = 0)
	: IlvPolyline(display, count, points, palette),
          _thickness(thickness),
	  _invPalette(0), _topshadow(0), _bottomshadow(0)
	    { lockPalettes(); }
    ~IlvReliefPolyline();
    // ____________________________________________________________
    IlUShort		getThickness() const { return _thickness; }
    inline void		setThickness(IlUShort thickness) 
			{
			    _thickness = thickness;
			}
    virtual void	boundingBox(IlvRect& bbox,
				    const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;
    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setPalette(IlvPalette*);
    virtual void	setAlpha(IlvIntensity);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvReliefPolyline);

protected:
    IlUShort		_thickness;
    IlvPalette*		_invPalette;
    IlvPalette*		_topshadow;
    IlvPalette*		_bottomshadow;

    void		lockPalettes();
    void		unLockPalettes();

    IlvReliefPolyline(IlvDisplay* display, IlvPalette* palette = 0)
	: IlvPolyline(display, palette),
	  _invPalette(0), _topshadow(0), _bottomshadow(0)
	{
	    lockPalettes();
	}
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvReliefPolygon : public IlvReliefPolyline
{
public:
    IlvReliefPolygon(IlvDisplay* display,
		     IlUInt      count,
		     IlvPoint*   points,
		     IlUShort    thickness,
		     IlvPalette* palette = 0)
	: IlvReliefPolyline(display, count, points, thickness, palette) {}
    // ____________________________________________________________
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;
    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvReliefPolygon);
};

ILVVWSMODULEINIT(relfpoly);
#endif /* __Ilv_Graphics_Relfpoly_H */
