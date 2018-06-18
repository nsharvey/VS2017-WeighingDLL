// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/zoomlab.h
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
// Declaration of the IlvZoomableLabel class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Zoomlab_H
#define __Ilv_Graphics_Zoomlab_H

#if !defined(__Ilv_Graphics_Label_H)
#include <ilviews/graphics/label.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvZoomableLabel : public IlvLabel
{
public:
    IlvZoomableLabel(IlvDisplay*     display,
		     const IlvPoint& position,
		     const char*     label,
		     IlvPalette*     palette = 0);
    // ____________________________________________________________
    virtual void	boundingBox(IlvRect&, const IlvTransformer* = 0) const;
    virtual IlBoolean	zoomable() const;
    virtual void	applyTransform(const IlvTransformer*);
    IlBoolean		contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* = 0) const;
    IlBoolean		intersects(const IlvRegion&,
				   const IlvTransformer* = 0) const;
    IlBoolean		inside(const IlvRegion&,
			       const IlvTransformer* = 0) const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;
    virtual void	setCenter(const IlvPoint&);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvZoomableLabel);

protected:
    IlvTransformer	_t;

    void		drawMinimized(IlvPort*,
				      const IlvTransformer* = 0,
				      const IlvRegion* = 0) const;
};

ILVVWSMODULEINIT(zoomlab);
#endif /* !__Ilv_Graphics_Zoomlab_H */
