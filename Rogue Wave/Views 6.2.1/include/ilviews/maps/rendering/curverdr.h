// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/rendering/curverdr.h
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
// Rendering class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Rendering_IlvDefaultCurveRenderer_H
#define __ILV_maps_Rendering_IlvDefaultCurveRenderer_H

#include <ilviews/maps/renderer.h>
#include <ilviews/maps/rendering/curveparser.h>
#include <ilviews/maps/rendering/linerdrstyle.h>

ILVMAPSMODULEINIT(curverdr);

class ILVMAPSEXPORTED IlvDefaultCurveRenderer
    :public IlvFeatureRenderer
{
private:
    _IlvCurveParser* _curveParser;
    IlvMapLineRenderingStyle* _lineRenderingStyle;
public:
    IlvDefaultCurveRenderer(IlvDisplay* display);

    IlvDefaultCurveRenderer(const IlvDefaultCurveRenderer& source);

    void setLineRenderingStyle(IlvMapLineRenderingStyle* lineRenderingStyle);

    IlvMapLineRenderingStyle* getLineRenderingStyle() const;

    virtual ~IlvDefaultCurveRenderer();

    virtual IlvGraphic* makeGraphic(const IlvMapFeature& feature,
				    const IlvMapInfo& targetMapInfo,
				    IlvMapsError& status) const;

protected:
    virtual IlvGraphic*
    makeGraphicFromMultiCurve(const IlvMapFeature& feature,
			      const IlvMapInfo& targetMapInfo,
			      IlvMapsError& status) const;
    virtual IlvGraphic*
    makeGraphicFromCurve(const IlvMapFeature& feature,
			 const IlvMapInfo& targetMapInfo,
			 IlvMapsError& status) const;
    static void Init();
    IlvMapsIcFriend(curverdr,ILVMAPSEXPORTED);
private:
    _IlvCurveParser* getCurveParser(const IlvMapFeature& feature,
				    const IlvMapInfo& targetMapInfo) const;

public:
    ILVMAPS_DECLMANDATORYRENDERERMEMBERS(IlvDefaultCurveRenderer);

};


#endif /* __ILV_maps_Rendering_IlvDefaultCurveRenderer_H */
