// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/cadrg/cadrglayer.h
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
// Definition of the IlvCADRGLayer class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Cadrg_Cadrglayer_H
#define __Ilv_Maps_Format_Cadrg_Cadrglayer_H

#if !defined(__Ilv_Maps_Tiling_Tiledlayer_H)
#  include <ilviews/maps/tiling/tiledlayer.h>
#endif
#if !defined(__Ilv_Maps_Format_Cadrg_Cadrgutil_H)
#  include <ilviews/maps/format/cadrg/cadrgutil.h>
#endif
#if !defined(__Ilv_Maps_Renderer_H)
#  include <ilviews/maps/renderer.h>
#endif

ILVMAPSMODULETERM(IlvCADRGLayer);

class IlvCADRGTocReader;

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvCADRGLayer
: public IlvTiledLayer
{
public:
    IlvCADRGLayer(const IlvCADRGCoverage& coverage,
		  const IlvMapAdapter* adapter = 0,
		  IlvTileCache* cache = 0);
    virtual ~IlvCADRGLayer();

    inline void setImageRenderer(const IlvFeatureRenderer& renderer)
	{ _imageRenderer = renderer.copy(); }
    IlvFeatureRenderer* getImageRenderer() const;
    IlFloat getPreferredZoomFactor() const;
    void fitToPreferredZoomFactor(IlvView* view,
				  IlBoolean redraw = IlTrue) const;
    IlDouble getPreferredScale();

    inline const IlvCADRGCoverage* getCoverage() const {return _coverage;}
    inline const IlvMapInfo& getMapInfo() const {return *_mapInfo;}
    static void UnlockToc(const char*);
    static void Finalize();

    IlvTilingDeclareLayerIO(IlvCADRGLayer);
private:
    static IlvMapAdapter* GetAdapter(const IlvMapAdapter*);
    static IlvRect GetTileOrigin(const IlvCADRGCoverage&,
				 const IlvMapAdapter*);
    static IlvCADRGTocReader* GetTocReader(const char*, IlvMapsError&);

    void setSize(const IlvCADRGCoverage&);
private:
    char*		_tocPathName;
    IlInt		_coverageIndex;
    IlvCADRGCoverage*	_coverage;
    IlvMapInfo*		_mapInfo;
    IlvFeatureRenderer*	_imageRenderer;
    IlvMapsIcFriend(IlvCADRGLayer, ILVMAPSEXPORTED);
};

#endif /* !__Ilv_Maps_Format_Cadrg_Cadrglayer_H */
