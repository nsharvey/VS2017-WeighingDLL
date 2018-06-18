// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/multishape.cpp
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
#include <multishape.h>

#include <ilviews/maps/rendering/curverdr.h>

// --------------------------------------------------------------------------
ShapeLayerFactory::ShapeLayerFactory(IlPathName& dirname)
: _numLayers(9),
  _renderer(0),
  _minScale(1./1000000),
  _dirName(dirname),
  _basename(GetFileBaseName(dirname))
{
}

// --------------------------------------------------------------------------
ShapeLayerFactory::~ShapeLayerFactory()
{
    if (_renderer) {
	delete _renderer;
	_renderer = 0;
    }
}

// --------------------------------------------------------------------------
IlvShapeFileLayer*
ShapeLayerFactory::makeLayer(IlvDisplay* display,
			     const IlvMapAdapter* adapter,
			     int layer)
{
    IlPathName p;
    p.setDirectory(_dirName);
    p += _basename;
    IlString base = p.getString();
    IlString shp(base);
    shp += IlString(layer) + IlString(".shp");
    const char* shpFileName = shp.getValue();
    IlString shx(base);
    shx += IlString(layer) + IlString(".shx");
    const char* shxFileName = shx.getValue();
    const char* dbfFileName = 0;
    IlString idx(base);
    idx += IlString(layer) + IlString(".idx");
    const char* idxFileName = idx.getValue();
    IlvShapeFileTileLoader* tileLoader =
	new IlvShapeFileTileLoader(shpFileName,
				   dbfFileName,
				   shxFileName,
				   idxFileName,
				   adapter);
    tileLoader->setFeatureRenderer(getRenderer(display));
    tileLoader->setAttachingAttributes(IlFalse);
    IlvShapeFileLayer* tl = new IlvShapeFileLayer(tileLoader);
    tl->setNamedProperty(new IlvStringProperty(IlvGetSymbol("_MULTIRES_"),
					       "MULTIRES"));
    tl->setTileLoader(tileLoader);
    IlvRect size;
    getSize(adapter, size);
    tl->setSize(size);
    IlvScaleVisibilityFilter* filter = getFilter(layer);
    tl->addVisibilityFilter(filter);
    return tl;
}

// --------------------------------------------------------------------------
void
ShapeLayerFactory::getSize(const IlvMapAdapter* adapter,
			   IlvRect& rect)
{
    IlDouble x = -180.;
    IlDouble y = 90;	
    IlDouble width = 360;
    IlDouble height = -180;
    rect = adapter->toViews(IlvCoordinate(x, y),
			    IlvCoordinate(x + width, y + height));
}

// --------------------------------------------------------------------------
IlInt
ShapeLayerFactory::Pow2(IlInt i)
{
    if (i == 0) {
	return 1;
    }
    return 2 << (i - 1);
}    

// --------------------------------------------------------------------------
IlvFeatureRenderer*
ShapeLayerFactory::getRenderer(IlvDisplay* display)
{
    if (!_renderer) {
	_renderer = new IlvDefaultCurveRenderer(display);
    }
    return _renderer;
}

// --------------------------------------------------------------------------
IlvScaleVisibilityFilter*
ShapeLayerFactory::getFilter(int layer)
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
	if(layer == 0) {
	    minScale = IlvScaleVisibilityFilter::NoLimit();
	}
	else {
	    minScale = _minScale / (IlDouble)Pow2(nl - layer);
	}
    }
    return new IlvScaleVisibilityFilter(minScale, maxScale);
}

// --------------------------------------------------------------------------
IlBoolean
ShapeLayerFactory::IsMultiShapeDirectory(IlPathName& p)
{
    if (!p.isDirectory()) {
	return IlFalse;
    }
    
    if (!p.openDir()) {
	return IlFalse;
    }
    
    IlPathName result;
    IlBoolean r = IlTrue; // be optimistic 
    // look for a pattern like '*[0-9].???'
    while(p.readDir(result)) {
	IlString s = result.getString(IlPathName::IlUnixPathType);
	if ((s == IlString("./")) || (s == IlString("../"))) {
	    continue;
	}
	size_t len = s.getLength();
	if (len <= 5) { 
	    {
		r = IlFalse;
	    }
	    break;
	}
	IlString end = s.getSubString((int)len - 5);
	if (end.startsWith("0") ||
	    end.startsWith("1") ||
	    end.startsWith("2") ||
	    end.startsWith("3") ||
	    end.startsWith("4") ||
	    end.startsWith("5") ||
	    end.startsWith("6") ||
	    end.startsWith("7") ||
	    end.startsWith("8") ||
	    end.startsWith("9")) {
	    if (end.endsWith(".shp") ||
		end.endsWith(".shx") ||
		end.endsWith(".idx") ||
		end.endsWith(".dbf")) {
		continue;
	    }
	    else {
		r = IlFalse;
		break;
	    }
	}
	else {
	    r = IlFalse;
	    break;
	}
    }
    p.closeDir();
    return r;
}

// --------------------------------------------------------------------------
IlString
ShapeLayerFactory::GetFileBaseName(IlPathName& p)
{
    if (!p.isDirectory()) {
	return IlString();
    }
    if (!p.openDir()) {
	return IlString();
    }
    IlPathName result;
    IlString shp("*.shp");
    IlString ret;
    while (p.readDir(result)) {
	if (result.match(shp)) {
	    IlString s = result.getString();
	    ret = s.getSubString(0, (int)s.getLength() - 5);
	    break;
	}
    }
    p.closeDir();
    if (!ret) {
	return IlString();
    }
    return ret;
}
