// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/shapeLOD.cpp
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
#include <stdlib.h>

#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/format/shapefile/shpreader.h>
#include <ilviews/maps/format/shapefile/spindex.h>
#include <ilviews/maps/format/shapefile/shpreader.h>
#include <ilviews/maps/format/shapefile/shpfile.h>
#include <ilviews/maps/format/shapefile/shptiler.h>
#include <ilviews/maps/format/shapefile/shptloader.h>
#include <ilviews/maps/format/shapefile/shplayer.h>
#include <ilviews/maps/projection/allprojs.h>

// --------------------------------------------------------------------------
IlInt getColumnCount()
{
    return 100;
}

// --------------------------------------------------------------------------
IlInt getRowCount()
{
    return 100;
}

// --------------------------------------------------------------------------
IlvCoordinate* getOrigin()
{
    return new IlvCoordinate();
}

// --------------------------------------------------------------------------
IlDouble getTileWidth()
{
    return 2.;
}

// --------------------------------------------------------------------------
IlDouble getTileHeight()
{
    return 2.;
}

// --------------------------------------------------------------------------
IlInt getRow(IlvMapFeature* f)
{
    return rand() % 100;
}

// --------------------------------------------------------------------------
IlInt getColumn(IlvMapFeature* f)
{
    return rand() % 100;
}

// --------------------------------------------------------------------------
IlvMapsError SpatialIndex(const char* shpFileName,
			  const char* shxFileName,
			  const char* idxFileName)
{
    // Chapter Readers/The IlvShapeFileIndex Class

    IlvMapsError status;
    // Open The index file.
    IlvShapeFileIndex* index =
	new IlvShapeFileIndex(shxFileName);
    status = index->getInitStatus();
    if(status != IlvMaps::NoError())
	return status;

    // Open the corresponding Shapefile.
    IlvShapeSHPReader* shape =
	new IlvShapeSHPReader(shpFileName);
    status = shape->getInitStatus();    
    if(status != IlvMaps::NoError())
	return status;

    // Construct a reader from the Shapefile reader and the Shapefile index.
    IlvShapeFileReader* reader =
	new IlvShapeFileReader(shape, 0, index);
    status = reader->getInitStatus();    
    if(status != IlvMaps::NoError())
	return status;
    
    // Retrieve the feature for each index.
    IlInt count = index->getRecordCount();
    for(IlInt i = 0; i < count; i++) {
	const IlvMapFeature* feature = reader->getFeatureAt(i, status);
	if(status != IlvMaps::NoError())
	    return status;
    }

    // Chapter Readers/The IlvShapeSpatialIndex Class
    
    // Open the spatial index
    IlvShapeSpatialIndex* spindex =
	new IlvShapeSpatialIndex(idxFileName);
    status = spindex->getInitStatus();
    if(status != IlvMaps::NoError())
	return status;

    // Loop on all columns and rows.
    for(int c = 0; c < spindex->getColumnCount(); c++) {
	for(int r = 0; r < spindex->getRowCount(); r++) {
	    IlInt *ret;
	    IlUInt size;
	    // Retrieve the IDs of objects belonging to the tile
	    // at column 'c' and row 'w'.
	    status = spindex->getIdArray(c, r, ret, size);
	    if(status != IlvMaps::NoError())
		return status;
	    // Loop on these IDs and retrieve the correspnding map feature.
	    for(IlUInt i = 0; i < size; i++) {
		const IlvMapFeature* feature = reader->getFeatureAt(ret[i], status);
		if(status != IlvMaps::NoError())
		    return status;
	    }
	    // Free allocated array.
	    if(ret)
		delete[] ret;
	}
    }

    // This class can also be used to generate your own tiling information for a given Shapefile
    IlvShapeSpatialIndex* tilerIndex = new IlvShapeSpatialIndex(getColumnCount(),
								getRowCount(),
								getOrigin(),
								getTileWidth(),
								getTileHeight());
    status = tilerIndex->getInitStatus();
    if(status != IlvMaps::NoError())
	return status;
    IlvMapFeature* feature = (IlvMapFeature*)reader->getNextFeature(status);
    if(status != IlvMaps::NoError())
	return status;
    int id = 0;
    while(feature) {
	// Determine to which tile(s) the object must belong.
	int row = getRow(feature);
	int col = getColumn(feature);
	// Add it to the spatial index.
	tilerIndex->add(row, col, id);
	feature = (IlvMapFeature*)reader->getNextFeature(status);
	if(status != IlvMaps::NoError())
	    return status;
	id++;
    }
    // write the spatial index.
    tilerIndex->save("spatialIndex.idx");
    
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
void
Tiler(const char* shpFileName)
{
    //Chapter Readers / The ShapeFileTiler class.
    IlvShapeFileTiler::CreateShapeSpatialIndex(shpFileName, 
					       "spatialIndex.idx", 
					       (IlDouble)5, (IlDouble)10);
    IlvShapeFileTiler::CreateShapeSpatialIndex(shpFileName, 
					       "spatialIndex.idx", 
					       (IlInt)20, (IlInt)30);
}

// --------------------------------------------------------------------------
IlvRect getTileOrigin()
{
    return IlvRect(0, 0, 10, 10);
}

// --------------------------------------------------------------------------
IlvMapsError
TileLoader(const char* shpFileName,
	   const char* dbfFileName,
	   const char* shxFileName,
	   const char* idxFileName)
{
    IlvMapsError status;
    IlvMapAdapter a(0.001);
    IlvShapeFileTileLoader* tileLoader = 
	new IlvShapeFileTileLoader(shpFileName,
				   dbfFileName, // or null if attributes loading 
				                // is not wanted.
				   shxFileName,
				   idxFileName,
				   &a);
    status = tileLoader->getInitStatus();
    if(status != IlvMaps::NoError())
	return status;
    IlvTiledLayer* tiledLayer = new IlvTiledLayer(getTileOrigin());
    status = tiledLayer->getInitStatus();
    if(status != IlvMaps::NoError())
	return status;
    tiledLayer->setTileLoader(tileLoader);    
    
    IlvShapeFileLayer* shapeLayer = new IlvShapeFileLayer(tileLoader);
    status = shapeLayer->getInitStatus();
    if(status != IlvMaps::NoError())
	return status;
    IlvDisplay* display = new IlvDisplay("");
    if(display->isBad())
	return IlvMaps::IllegalArgument();
    IlvManager* manager = new IlvManager(display);
    manager->addLayer(shapeLayer);
    ofstream stream("out.ilv");
    manager->save(stream);
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
int
main(int argc, char**argv)
{
    if (argc < 2) {
	IlvPrint("Failed : Usage %s filename", argv[0]);
        return -1;
    }
    IlString a(argv[1]);
    IlString shp = a + IlString(".shp");
    IlString shx = a + IlString(".shx");
    IlString idx = a + IlString(".idx");

    IlvMapsError status = SpatialIndex(shp.getValue(),
                                       shx.getValue(),
                                       idx.getValue());
    if (status != IlvMaps::NoError()) {
        IlvPrint("Failed : %s", IlvMaps::GetErrorMessageId(status));
	return -1;
    }
    Tiler(shp.getValue());
    IlString dbf = a + IlString(".dbf");
    status = TileLoader(shp.getValue(),
                        dbf.getValue(),
                        shx.getValue(),
                        idx.getValue());
    if (status != IlvMaps::NoError()) {
        IlvPrint("Failed : %s", IlvMaps::GetErrorMessageId(status));
	return -1;
    }
    return 0;
}
