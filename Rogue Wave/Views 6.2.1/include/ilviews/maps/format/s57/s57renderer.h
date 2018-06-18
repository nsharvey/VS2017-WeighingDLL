// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/s57renderer.h
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
// Rogue Wave Views - Maps add-on.
// --------------------------------------------------------------------------
#ifndef __Ilv_S57renderer_H
#define __Ilv_S57renderer_H

#include <ilviews/maps/dftrenderer.h>
#include <ilviews/maps/rendering/linerdrstyle.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57ObjectStyle
{
public:
    IlvS57ObjectStyle(IlvDisplay* display, const char* init);
    ~IlvS57ObjectStyle();

    void		initialize(IlvDisplay*, const char*);

    IlInt		getCode() const;
    IlInt		getStrokeStyle() const;
    const char*		getName() const;
    const char*		getBitmapName() const;
    IlvBitmap*		getBitmap() const;
    IlvColor*		getBackgroundColor(IlvDisplay*) const;
    IlvColor*		getForegroundColor(IlvDisplay*) const;
    IlBoolean		isFill() const;
    IlBoolean		isStroke() const;
    IlBoolean		isVisible() const;
    IlBoolean		hasBitmap() const;

protected:
    IlInt		_code;
    IlInt		_strokeStyle;
    IlString		_name;
    IlString		_background;
    IlString		_foreground;
    IlString		_bitmapName;
    IlBoolean		_fill;
    IlBoolean		_stroke;
    IlBoolean		_visible;
    IlvBitmap*		_bitmap;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57Renderer : public IlvDefaultFeatureRenderer
{
public:
    IlvS57Renderer(IlvDisplay* display);

    virtual ~IlvS57Renderer();

    IlvS57ObjectStyle*	findStyle(IlInt code) const;

protected:
    virtual IlvGraphic*	dispatch(const IlvMapFeature& mapFeature, 
				 const IlvMapInfo& targetMapInfo, 
				 IlvMapsError& status) const;

    void		addStyle(const char*);

    void		setupAreaRenderer(IlvS57ObjectStyle*) const;
    void		setupCurveRenderer(IlvS57ObjectStyle*) const;
    void		setupPointRenderer(IlvS57ObjectStyle*) const;

    void		setupStrokeStyle(IlvMapLineRenderingStyle* line,
					 IlInt style) const;

    IlvS57ObjectStyle**	_styles;
    IlInt		_styleCount;
    IlInt		_styleSize;
    IlString		_pathStyle;
};

#endif /* !__Ilv_S57renderer_H */
