// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/marker.h
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
// Declaration of the IlvMarker class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Marker_H
#define __Ilv_Graphics_Marker_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvMarker : public IlvSimpleGraphic
{
public:
    IlvMarker(IlvDisplay*     display,
	      const IlvPoint& point,
	      IlvMarkerType   type    = IlvMarkerSquare,
	      IlUShort        size    = IlvDefaultMarkerSize,
	      IlvPalette*     palette = 0)
    : IlvSimpleGraphic(display, palette),
      _point(point),
      _type(type),
      _size(size)
    {}
    // ____________________________________________________________
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer*) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;
    virtual void	applyTransform(const IlvTransformer*);
    inline const IlvPoint&	getPoint() const {  return _point; }
    inline void		setPoint(const IlvPoint& p) { _point = p; }
    inline void		setType(IlvMarkerType t) { _type = t; }
    inline IlvMarkerType	getType() const { return _type; }
    inline void		setSize(IlUShort size) { _size = size; }
    inline IlUShort	getSize() const { return _size; }

    virtual IlBoolean	zoomable() const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvMarker);

protected:
    IlvPoint		_point;
    IlvMarkerType	_type;
    IlUShort		_size;
};

class ILVVWSEXPORTED IlvZoomableMarker : public IlvMarker
 {
public:
    IlvZoomableMarker(IlvDisplay*     display,
		      const IlvPoint& point,
		      IlvMarkerType   type    = IlvMarkerSquare,
		      IlUShort        size    = IlvDefaultMarkerSize,
		      IlvPalette*     palette = 0)
    : IlvMarker(display, point, type, size, palette)
    {}
    // ____________________________________________________________
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer*) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;

    virtual IlBoolean	zoomable() const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvZoomableMarker);
};

ILVVWSMODULEINIT(g0marker);
#endif /* !__Ilv_Graphics_Marker_H */
