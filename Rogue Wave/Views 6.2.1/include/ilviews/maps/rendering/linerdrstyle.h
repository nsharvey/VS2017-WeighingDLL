// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/rendering/linerdrstyle.h
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
// Definition of the IlvMapLineRenderingStyle class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Rendering_IlvMapLineRenderingStyle_H
#define __ILV_maps_Rendering_IlvMapLineRenderingStyle_H

#include <ilviews/maps/rendering/rdrstyle.h>
#include <ilviews/maps/rendering/incrpalette.h>

ILVMAPSMODULEINIT(linerdrstyle);

class ILVMAPSEXPORTED IlvMapLineRenderingStyle : public IlvMapRenderingStyle
{
public:
    IlvMapLineRenderingStyle(IlvDisplay* display);

    IlvMapLineRenderingStyle(const IlvMapLineRenderingStyle& source);

    void		setStyleAndWidthAllowed(IlBoolean allow)
			{
			    _styleAndWidthAllowed = allow;
			}

    IlBoolean		isStyleAndWidthAllowed() const
			{
			    return _styleAndWidthAllowed;
			}

    void		setPalette(IlvPalette* palette);

    IlvPalette*		getPalette() const
			{
			    return _styleAndWidthAllowed
				? _internalPalette.getPalette()
				: _palette.getPalette();
			}

    IlvPalette*		getInternalPalette() const
			{
			    return _internalPalette.getPalette();
			}

    void		setForeground(IlvColor* color);

    IlvMapsError	setForeground(const char* colorName);

    IlvColor*		getForeground() const
			{
			    return _internalPalette.getForeground();
			}

    void		setLineWidth(IlUShort lineWidth);

    IlUShort		getLineWidth() const
			{
			    return _internalPalette.getLineWidth();
			}

    void		setLineStyle(IlvLineStyle* lineStyle);

    IlvMapsError	setLineStyle(const char* lineStyleName);

    IlvLineStyle*	getLineStyle() const
			{
			    return _internalPalette.getLineStyle();
			}

protected:
    virtual ~IlvMapLineRenderingStyle();

private:
    static void		Init();

    IlvMapsIcFriend(linerdrstyle, ILVMAPSEXPORTED);
    ILVMAPS_DECLMANDATORYRDRSTYLEMEMBERS(IlvMapLineRenderingStyle);

    IlvMapIncrementalPalette	_palette;
    IlvMapIncrementalPalette	_internalPalette;
    IlBoolean			_styleAndWidthAllowed;
};

#endif /* __ILV_maps_Rendering_IlvMapLineRenderingStyle_H */
