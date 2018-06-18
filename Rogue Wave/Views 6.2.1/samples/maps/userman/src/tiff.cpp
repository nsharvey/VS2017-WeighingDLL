// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/tiff.cpp
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
#include <ilviews/maps/maps.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/renderer.h>
#include <ilviews/maps/projection/allprojs.h>

#include <ilviews/maps/format/geotiff/gtiffreader.h>
#include <ilviews/maps/format/geotiff/gtifflayer.h>
#include <ilviews/maps/format/geotiff/gtifftloader.h>
#include <ilviews/maps/format/geotiff/gtifftiler.h>
#include <ilviews/maps/tiling/tiledlayer.h>

// --------------------------------------------------------------------------
IlvRect getTileOrigin() {
    return IlvRect(0, 0, 10, 10);
}

// --------------------------------------------------------------------------
IlInt getTileWidth() {
    return 64;
}

// --------------------------------------------------------------------------
IlInt getTileHeight() {
    return 64;
}

// --------------------------------------------------------------------------
IlvMapsError
reader(IlvDisplay* display,
       const char* filename)
{
    IlvMapsError status;
    IlvGeoTIFFReader* reader =
	new IlvGeoTIFFReader(filename);
    status = reader->getInitStatus();
    if(status != IlvMaps::NoError())
	return status;
    const IlvMapFeature* feature =
	reader->getNextFeature(status);    
    if(status != IlvMaps::NoError())
	return status;
    IlvFeatureRenderer* renderer = reader->getDefaultFeatureRenderer(display);
    // image is known to be in the geographic projection
    IlvGeographicProjection* projection = new IlvGeographicProjection();
    IlvMapInfo info(projection);
    IlvGraphic* graphic = renderer->makeGraphic(*feature,
					      info,
					      status);
    IlvManager* manager = new IlvManager(display);
    manager->addObject(graphic, IlFalse);
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
IlvMapsError
tileLoader(IlvDisplay* display,
	   const char* fileName)
{
    IlvMapAdapter adapter(0.001);
    IlvGeoTIFFTileLoader* loader =
	new IlvGeoTIFFTileLoader(fileName,
				 &adapter);
    IlvMapsError status = loader->getInitStatus();
    if(status != IlvMaps::NoError())
	return status;
    IlvTiledLayer* tiledLayer = new IlvTiledLayer(getTileOrigin());
    tiledLayer->setTileLoader(loader);

    IlvGeoTIFFLayer* layer = new IlvGeoTIFFLayer(loader);
    IlvManager* manager = new IlvManager(display);
    manager->addLayer(layer);
    ofstream stream("out.ilv");
    manager->save(stream);
    
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
class MyStreamer : public IlvTIFFStreamer
{
public:
    IlAny openStream(ILVSTDPREF istream& stream) {
	IlvPrint("openStream");
	return IlvTIFFStreamer::openStream(stream);
    }

    void closeStream(IlAny identifier) {
	IlvPrint("closeStream");
	IlvTIFFStreamer::closeStream(identifier);
    }
};

// --------------------------------------------------------------------------
IlvMapsError
tiler(const char* filename)
{
    IlvGeoTIFFTiler* tiler =
	new IlvGeoTIFFTiler(filename,
			    "out.tif",
			    getTileWidth(),
			    getTileHeight());
    IlvMapsError status = tiler->getInitStatus();
    if(status != IlvMaps::NoError())
	return status;
    IlvTIFFStreamer streamer;
    /*
    IlAny id = streamer.openStream(ifstream(filename));
    IlUInt width;
    IlBoolean b = streamer.getTagValue(id, 256, width);
    streamer.closeStream(id);
    IlvPrint("value found %d %x", b, width);
    */
    status = tiler->performTiling(streamer);
    return status;
}

// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay("");
    if(display->isBad())
	return -1;
    IlvMapsError status;
    
    if(argc > 1) {
	status = reader(display, argv[1]);
	if(status != IlvMaps::NoError())
	    IlvPrint("Failed : %s", IlvMaps::GetErrorMessageId(status));
    } else {
	IlvPrint("Failed : Usage %s filename", argv[0]);
	return -1;
    }
    status = tileLoader(display, argv[1]);    
    if(status != IlvMaps::NoError())
	IlvPrint("Failed : %s", IlvMaps::GetErrorMessageId(status));
    tiler(argv[1]);
    return 0;
}
