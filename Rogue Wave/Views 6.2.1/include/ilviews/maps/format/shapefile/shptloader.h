// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/shapefile/shptloader.h
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
// ilog.views.maps.format.shapefile
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Shapefile_Shptloader_H
#define __Ilv_Maps_Format_Shapefile_Shptloader_H

#if !defined(__Ilv_Maps_Maps_H)
#  include <ilviews/maps/maps.h>
#endif
#if !defined(__Ilv_Maps_Projection_Project_H)
#  include <ilviews/maps/projection/project.h>
#endif
#if !defined(__Ilv_Maps_Format_Maptloader_H)
#  include <ilviews/maps/format/maptloader.h>
#endif
#if !defined(__Ilv_Maps_Format_Shapefile_Spindex_H)
#  include <ilviews/maps/format/shapefile/spindex.h>
#endif
#if !defined(__Ilv_Maps_Format_Shapefile_Shpfile_H)
#  include <ilviews/maps/format/shapefile/shpfile.h>
#endif
#if !defined(__Ilv_Maps_Mapfeature_H)
#  include <ilviews/maps/mapfeature.h>
#endif
#if !defined(__Ilv_Maps_Laiterator_H)
#  include <ilviews/maps/laiterator.h>
#endif
#if !defined(__Ilv_Maps_Tiling_Tile_H)
#  include <ilviews/maps/tiling/tile.h>
#endif
#if !defined(__Ilv_Maps_Tiling_Tileloader_H)
#  include <ilviews/maps/tiling/tileloader.h>
#endif

ILVMAPSMODULEINIT(IlvShapeFileTileLoader);

class ILVMAPSEXPORTED IlvShapeFileTileLoader : public IlvMapTileLoader
{
public:
    IlvShapeFileTileLoader(const char* shpFilename,
			   const char* dbfFilename,
			   const char* shxFilename,
			   const char* indexFilename,
			   const IlvMapAdapter* adapter);    

    virtual ~IlvShapeFileTileLoader();

    virtual IlvRect&	getTileOrigin();

    virtual IlBoolean	getUpperLeftCorner(IlvCoordinate& c) const;

    virtual IlBoolean	getLowerRightCorner(IlvCoordinate& c) const;

    virtual
    IlvMapFeatureIterator* getFeatureIterator(IlvTile* tile);

    virtual
    IlvFeatureRenderer* getDefaultFeatureRenderer(IlvDisplay *display);

    const char*		getSHPFilename() const { return _shpFilename; }

    const char*		getSHXFilename() const { return _shxFilename; }

    const char*		getDBFFilename() const { return _dbfFilename; }

    const char*		getSpatialIndexFilename() const
			{
			    return _indexFilename;
			}

    virtual IlBoolean	isPersistent() const;

    virtual IlvMapInfo*	getMapInfo();

protected:
    virtual
    IlvShapeFileReader*	getReader(const char* shpFilename,
				  const char* dbfFilename,
				  const char* shxFilename);

    IlvTilingDeclareIO(IlvShapeFileTileLoader);

private:
    void		initIndex();
    static void		InitStatic();

    IlvMapsIcFriend(IlvShapeFileTileLoader, ILVMAPSEXPORTED);

private:
    char*		_shpFilename;
    char*		_shxFilename;
    char*		_dbfFilename;
    char*		_indexFilename;
    IlvProjection*	_projection;
    IlvCoordinate*	_UL;
    IlvCoordinate*	_LR;
    IlvShapeSpatialIndex* _spatialIndex;
    IlvMapInfo*		_mapinfo;
    IlvRect		_tileOrigin;
    IlvShapeFileReader*	_iterator;
};

#endif /* !__Ilv_Maps_Format_Shapefile_Shptloader_H */
