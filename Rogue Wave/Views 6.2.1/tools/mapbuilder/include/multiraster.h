// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/multiraster.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
#include <ilog/pathname.h>
#include <ilog/string.h>

#include <ilviews/ilv.h>

#include <ilviews/bitmaps/jpg.h>

#include <ilviews/maps/renderer.h>
#include <ilviews/maps/scalefilter.h>
#include <ilviews/maps/format/image/imglayer.h>

// --------------------------------------------------------------------------
class RasterLayerFactory
{
public:
    RasterLayerFactory(IlPathName& dirname);
    virtual ~RasterLayerFactory();

    IlvImageLayer* makeLayer(IlvDisplay* display,
			     const IlvMapAdapter* adapter,
			     int layer);

    void getSize(const IlvMapAdapter* adapter, IlvRect& rect);

    void getTileOrigin(int layer,
		       const IlvMapAdapter* adapter,
		       IlvRect& rect);

    char* getString(int layer);

    IlvFeatureRenderer* getRenderer(IlvDisplay* display);

    IlvScaleVisibilityFilter* getFilter(int layer);

    IlInt getNumLayers() {
	return _numLayers;
    }

    static IlBoolean IsMultiRasterDirectory(IlPathName& p, IlInt numLayers);

    static IlInt Pow2(int i);

private:
    int _numLayers;
    IlvFeatureRenderer* _renderer;
    IlDouble _minScale;
    IlPathName _dirName;
};
