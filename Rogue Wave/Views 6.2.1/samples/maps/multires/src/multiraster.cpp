// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/multires/src/multiraster.cpp
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
#include <multiraster.h>

#include <ilviews/maps/rendering/imagerdr.h>

// --------------------------------------------------------------------------
// RasterLayerFactory
// --------------------------------------------------------------------------
RasterLayerFactory::RasterLayerFactory(IlPathName& dirname)
    : _numLayers(9),
      _renderer(0),
      _minScale(1./4000000),
      _dirName(dirname)
{
}

// --------------------------------------------------------------------------
RasterLayerFactory::~RasterLayerFactory()
{
    if(_renderer) {
	delete _renderer;
    }
}

// --------------------------------------------------------------------------
IlInt
RasterLayerFactory::Pow2(int i)
{
    if (i == 0) {
	return 1;
    }
    return 2 << (i - 1);
}

// --------------------------------------------------------------------------
IlBoolean
RasterLayerFactory::IsMultiRasterDirectory(IlPathName& p, IlInt numLayers)
{
    if (!p.isDirectory()) {
	return IlFalse;
    }
    for (int i = 0; i < numLayers; i++) {
	IlPathName pp(p);
	IlString s(25 * Pow2(i), "%04d");
	pp += s;
	if (!pp.doesExist()) {
	    return IlFalse;
	}
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
IlvImageLayer*
RasterLayerFactory::makeLayer(IlvDisplay* display,
			      const IlvMapAdapter* adapter,
			      int layer)
{
    char* s = getString(layer);
    IlvImageTileLoader* loader = new IlvImageTileLoader(display,
							s,
							"%03d",
							"%03d",
							adapter);
    delete [] s;
    IlvRect o;
    getTileOrigin(layer,
		  adapter,
		  o);
    IlvImageLayer* tl = new IlvImageLayer(loader, o);
    IlvFeatureRenderer* renderer = getRenderer(display);
    loader->setFeatureRenderer(renderer);
    IlvRect size;
    getSize(adapter, size);
    tl->setSize(size);
    IlvScaleVisibilityFilter* filter = getFilter(layer);
    tl->addVisibilityFilter(filter);
    return tl;
}

// --------------------------------------------------------------------------
void
RasterLayerFactory::getSize(const IlvMapAdapter* adapter,IlvRect& rect)
{
    IlDouble x = -180.;
    IlDouble y = 90;
    IlDouble width = 360;
    IlDouble height = -180;
    rect= adapter->toViews(IlvCoordinate(x, y),
			   IlvCoordinate(x + width, y + height));
}

// --------------------------------------------------------------------------
void
RasterLayerFactory::getTileOrigin(int layer,
				  const IlvMapAdapter* adapter,
				  IlvRect& rect)
{
    IlDouble f = Pow2(_numLayers - layer - 1);
    IlDouble x = -180.;
    IlDouble y = -90.;
    IlDouble width = 2.5f * f;
    IlDouble height = 2.5f * f;
    rect = adapter->toViews(IlvCoordinate(x, -y),
			    IlvCoordinate(x + width, -y - height));
}

// --------------------------------------------------------------------------
char*
RasterLayerFactory::getString(int layer)
{
    IlInt ld = 25 * Pow2(_numLayers - layer - 1);
    IlPathName p(_dirName);
    IlString s(ld, "%04d");
    p.addDirectory(s);
    p.setFileName("%c%r.jpg");
    return p.getString().copyValue();
}

// --------------------------------------------------------------------------
IlvFeatureRenderer*
RasterLayerFactory::getRenderer(IlvDisplay* display)
{
    if (!_renderer) {
	_renderer = new IlvDefaultImageRenderer(display);
    }
    return _renderer;
}

// --------------------------------------------------------------------------
IlvScaleVisibilityFilter*
RasterLayerFactory::getFilter(int layer)
{
    IlDouble maxScale;
    IlDouble minScale;
    int nl = _numLayers - 1;
    if (layer == nl) {
	minScale = _minScale;
	maxScale = IlvScaleVisibilityFilter::NoLimit();
    }
    else {
	maxScale = _minScale / (IlDouble)Pow2(nl - layer - 1);
	if (layer == 0) {
	    minScale = IlvScaleVisibilityFilter::NoLimit();
	}
	else {
	    minScale = _minScale / (IlDouble)Pow2(nl - layer);
	}
    }
    return new IlvScaleVisibilityFilter(minScale, maxScale);
}
