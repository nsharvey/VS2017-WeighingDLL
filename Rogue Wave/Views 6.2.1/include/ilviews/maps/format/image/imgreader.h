// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/image/imgreader.h
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
// ilog.views.maps.format.image
// Defined in library ilvmaps
// --------------------------------------------------------------------------

#ifndef __ILV_maps_Format_image_IlvImageReader_H
#define __ILV_maps_Format_image_IlvImageReader_H

#include <ilviews/ilv.h>
#include <ilviews/maps/macros.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/format/mapinput.h>
#include <ilviews/bitmaps/streamer.h>
#include <ilviews/maps/geometry/geoimage.h>
#include <ilog/iurlstr.h>

#ifdef IL_STD
#include <iostream>
#include <fstream>
IL_STDUSE;
#else
#include <iostream.h>
#include <fstream.h>
#endif

ILVMAPSMODULEINIT(IlvImageReader);

class ILVMAPSEXPORTED IlvImageReader : public IlvMapFeatureIterator
{
public:
    IlvImageReader(IlvDisplay* display,
		   const char* filename,
		   IlvCoordinate& ul,
		   IlvCoordinate& lr);    
    IlvImageReader(IlvDisplay* display,
		   IL_STDPREF istream& input,
		   IlvCoordinate& ul,
		   IlvCoordinate& lr);
    IlvImageReader(IlvDisplay* display,
		   IlIUrlStream& input,
		   IlvCoordinate& ul,
		   IlvCoordinate& lr);

    virtual ~IlvImageReader();

    virtual
    IlvMapsError	getInitStatus() const;

    virtual
    const IlvMapFeature* getNextFeature(IlvMapsError& status);    
    virtual IlBoolean	getLowerRightCorner(IlvCoordinate& coordinate) const;
    virtual IlBoolean	getUpperLeftCorner(IlvCoordinate& coordinate) const;

    const IlvProjection* getProjection() const { return _projection; }

    void		setSourceProjection(IlvProjection* projection) 
			{
			    _projection = projection;
			}

    IlvFeatureRenderer*	getDefaultFeatureRenderer(IlvDisplay *display);

    virtual
    IlvMapImage*	getGeometry();

    IlvMapsError	getInitStatus();

protected:
    virtual void	setInitStatus(IlvMapsError status);

private:

    IlvMapFeatureIteratorDeclareClassInfo();
    IlvMapsIcFriend(IlvImageReader, ILVMAPSEXPORTED);

    char*		_filename;
    IlvDisplay*		_display;    
    IlvMapsError	_status;
    IlvMapFeature*	_feature;
    IlBoolean		_alreadyDone;    
    IlvMapGeometry*	_geometry;    
    IlvProjection*	_projection;
    IlBoolean		_isUrl;
    IlvMapImage*	_imageGeometry;    
    IlvCoordinate*	_upperLeft;
    IlvCoordinate*	_lowerRight;    
    istream&		_stream;
    IlBoolean		_ownStream;
};

#endif /* __ILV_maps_Format_image_IlvImageReader_H */
