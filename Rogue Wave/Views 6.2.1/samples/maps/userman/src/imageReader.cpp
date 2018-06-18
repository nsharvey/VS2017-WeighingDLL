// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/imageReader.cpp
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

#include <ilviews/base/graphic.h>
#include <ilviews/manager/manager.h>

#include <ilviews/maps/tiling/tiledlayer.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/format/image/imgreader.h>
#include <ilviews/maps/format/image/imgtloader.h>
#include <ilviews/maps/format/image/imglayer.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/renderer.h>
#include <ilviews/maps/projection/allprojs.h>

// --------------------------------------------------------------------------
IlvRect getTileOrigin() {
    return IlvRect(0, 0, 10, 10);
}

// --------------------------------------------------------------------------
IlvMapsError
readImage(IlvDisplay* display,
	  const char* fileName)
{
    IlvMapsError status;
    // The image is known to be at 77 degrees 30 seconds east
    // and 10 degrees north for the upper left corner. 
    // Lower right corner is at 82 degrees 30 seconds east
    // and 5 degrees north.    
    IlvCoordinate ul(77.5, 10);
    IlvCoordinate lr(82.5, 5);
    IlvImageReader* reader = new IlvImageReader(display, fileName, ul, lr);
    status = reader->getInitStatus();
    if(status != IlvMaps::NoError())
	return status;
    IlvMapFeature* feature = (IlvMapFeature*)reader->getNextFeature(status);
    if(status != IlvMaps::NoError())
	return status;
    IlvFeatureRenderer* renderer = reader->getDefaultFeatureRenderer(display);
    // image is known to be in the geographic projection
    IlvGeographicProjection* projection = new IlvGeographicProjection();
    IlvMapInfo* mapInfo = new IlvMapInfo(projection);
    feature->setProjection(projection);
    IlvGraphic* g = renderer->makeGraphic(*feature, *mapInfo, status);
    if(status != IlvMaps::NoError())
	return status;    
    IlvManager* manager = new IlvManager(display);
    manager->addObject(g, IlFalse);
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
IlvMapsError
tileLoader(IlvDisplay* display)
{
    IlvMapsError status;
    IlvMapAdapter* adapter = new IlvMapAdapter(0.001);
    IlvImageTileLoader* loader =
	new IlvImageTileLoader(display,
			       "tiles/tile_%c_%r.jpg",
			       "%03d",
			       "%02d",
			       adapter);
    status = loader->getInitStatus();
    if(status != IlvMaps::NoError())
	return status;
    IlvRect tileOrigin = getTileOrigin();

    IlvTiledLayer* tiledLayer = new IlvTiledLayer(tileOrigin);
    tiledLayer->setTileLoader(loader);

    IlvImageLayer* layer = new IlvImageLayer(loader, tileOrigin);
    IlvManager* manager = new IlvManager(display);
    manager->addLayer(layer);
    ofstream stream("out.ilv");
    manager->save(stream);
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay("");
    if(display->isBad())
	return -1;

    if(argc > 1) {
	IlvMapsError status = readImage(display, argv[1]);
	if(status != IlvMaps::NoError())
	    IlvPrint("Failed : %s", IlvMaps::GetErrorMessageId(status));
    } else {
	IlvPrint("Failed : Usage %s filename", argv[0]);
	return -1;
    }
    tileLoader(display);
    return 0;
}
