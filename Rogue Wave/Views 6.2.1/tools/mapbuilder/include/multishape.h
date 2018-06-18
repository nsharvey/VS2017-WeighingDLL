// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/multishape.h
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

#include <ilviews/maps/renderer.h>
#include <ilviews/maps/scalefilter.h>
#include <ilviews/maps/format/shapefile/shplayer.h>

// --------------------------------------------------------------------------
class ShapeLayerFactory
{
private :
public:
    ShapeLayerFactory(IlPathName& dirname);
    virtual ~ShapeLayerFactory();

    IlInt getNumLayers() const
	{ return _numLayers; }

    IlvShapeFileLayer* makeLayer(IlvDisplay* display,
				 const IlvMapAdapter* adapter,
				 int layer);

    void getSize(const IlvMapAdapter* adapter, IlvRect& rect);

    IlvFeatureRenderer* getRenderer(IlvDisplay* display);

    IlvScaleVisibilityFilter* getFilter(int layer);

    static IlString GetFileBaseName(IlPathName& p);

    static IlBoolean IsMultiShapeDirectory(IlPathName& p);

    static IlInt Pow2(IlInt i);

private:
    int _numLayers;
    IlvFeatureRenderer* _renderer;
    IlDouble _minScale;
    IlPathName _dirName;
    IlString _basename;

};
