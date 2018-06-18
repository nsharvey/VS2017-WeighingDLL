// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/zicon.h
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
// Declaration of the IlvZoomableIcon and IlvZoomableTransparentIcon classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Zicon_H
#define __Ilv_Graphics_Zicon_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Graphics_Icon_H)
#include <ilviews/graphics/icon.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvZoomableIcon : public IlvIcon
{
public:
    IlvZoomableIcon(IlvDisplay*     display,
		    const IlvPoint& position,
		    IlvBitmap*      bitmap,
		    IlvPalette*     palette = 0);
    // ____________________________________________________________
    inline const IlvTransformer&	getTransformer() const { return _t; }
    virtual IlBoolean	zoomable() const;
    virtual void	drawRotatedBitmap(IlvPort*,
					  IlvPalette*,
					  const IlvTransformer& t,
					  const IlvRegion*      clip = 0)const;
    virtual void	drawBitmap(IlvPort*,
				   IlvPalette*,
				   const IlvRect&,
				   const IlvRegion* clip = 0) const;
    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;
    void		applyTransform(const IlvTransformer* t);
    void		boundingBox(IlvRect&              r,
				    const IlvTransformer* t = 0) const;
    IlBoolean		contains(const IlvPoint&       p,
				 const IlvPoint&       tp,
				 const IlvTransformer* t = 0) const;
    IlBoolean		intersects(const IlvRegion&      trect,
				   const IlvTransformer* t = 0) const;
    IlBoolean		inside(const IlvRegion&      trect,
			       const IlvTransformer* t = 0) const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvZoomableIcon);

protected:
    IlvTransformer	_t;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvZoomableTransparentIcon : public IlvZoomableIcon
{
public:
    IlvZoomableTransparentIcon(IlvDisplay*	display,
			       const IlvPoint&	position,
			       IlvBitmap*	bitmap,
			       IlvPalette*	palette = 0);

    // ____________________________________________________________
    virtual void	drawRotatedBitmap(IlvPort*,
					  IlvPalette*,
					  const IlvTransformer& t,
					  const IlvRegion*      clip = 0)const;
    virtual void	drawBitmap(IlvPort*,
				   IlvPalette*,
				   const IlvRect&,
				   const IlvRegion* clip = 0) const;
    virtual void	setBitmap(IlvBitmap* bitmap);

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvZoomableTransparentIcon);
};

ILVVWSMODULEINIT(g0zicon);
#endif /* !__Ilv_Graphics_Zicon_H */
