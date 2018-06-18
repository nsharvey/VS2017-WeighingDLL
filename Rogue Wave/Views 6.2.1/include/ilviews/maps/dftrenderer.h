// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/dftrenderer.h
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
// Definitino of the IlvDefaultFeatureRenderer class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Dftrenderer_H
#define __Ilv_Maps_Dftrenderer_H

#if !defined(__Ilv_Maps_Renderer_H)
#  include <ilviews/maps/renderer.h>
#endif

ILVMAPSMODULEINIT(dftrenderer);

class ILVMAPSEXPORTED IlvDefaultFeatureRenderer
: public IlvFeatureRenderer
{
public:
    IlvDefaultFeatureRenderer(IlvDisplay* display);
    IlvDefaultFeatureRenderer(const IlvDefaultFeatureRenderer& source);
    virtual ~IlvDefaultFeatureRenderer();

    virtual IlvGraphic* makeGraphic(const IlvMapFeature& mapFeature,
				    const IlvMapInfo& targetMapInfo,
				    IlvMapsError& status) const;

    void		setPointRenderer(const IlvFeatureRenderer* pointRndr);
    IlvFeatureRenderer* getPointRenderer() const;

    void		setCurveRenderer(const IlvFeatureRenderer* curveRndr);
    IlvFeatureRenderer* getCurveRenderer() const;

    void		setAreaRenderer(const IlvFeatureRenderer* areaRndr);
    IlvFeatureRenderer* getAreaRenderer() const;

    void		setTextRenderer(const IlvFeatureRenderer* textRndr);
    IlvFeatureRenderer* getTextRenderer() const;

    void		setImageRenderer(const IlvFeatureRenderer* imageRndr);
    IlvFeatureRenderer* getImageRenderer() const;

    void		setRasterRenderer(const IlvFeatureRenderer* rasterRndr);
    IlvFeatureRenderer* getRasterRenderer() const;

    ILVMAPS_DECLMANDATORYRENDERERMEMBERS(IlvDefaultFeatureRenderer);
protected:
    virtual IlvGraphic* dispatch(const IlvMapFeature& mapFeature,
                                 const IlvMapInfo& targetMapInfo,
				 IlvMapsError& status) const;
    virtual IlvGraphic*
    makeGraphicFromGeometryCollection(const IlvMapFeature& mapFeature,
				      const IlvMapInfo& targetMapInfo,
				      IlvMapsError& status) const;
private:
    static void		Init();
    IlvMapsIcFriend(dftrenderer,ILVMAPSEXPORTED);

    IlvFeatureRenderer* _pointRenderer;
    IlvFeatureRenderer* _curveRenderer;
    IlvFeatureRenderer* _areaRenderer;
    IlvFeatureRenderer* _textRenderer;
    IlvFeatureRenderer* _imageRenderer;
    IlvFeatureRenderer* _rasterRenderer;
    IlvClassInfo*	_lastClassInfo;
    IlvFeatureRenderer* _lastRenderer;
};

#endif /* !__Ilv_Maps_Dftrenderer_H */
