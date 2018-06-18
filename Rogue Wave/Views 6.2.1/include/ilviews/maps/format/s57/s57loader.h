// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/s57loader.h
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
// --------------------------------------------------------------------------
#ifndef __Ilv_S57loader_H
#define __Ilv_S57loader_H

#include <ilviews/base/iostream.h>

#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/format/mapinput.h>
#include <ilviews/maps/rendering/curverdr.h>
#include <ilviews/maps/projection/geogproj.h>
#include <ilviews/maps/geometry/geompoint.h>
#include <ilviews/maps/geometry/geopolygon.h>
#include <ilviews/maps/geometry/geosegring.h>

#include <ilviews/maps/format/s57/s57reader.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

// --------------------------------------------------------------------------
// IlvS57Loader
// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57Loader
: public IlvS57Reader, public IlvMapFeatureIterator
{
public:
    IlvS57Loader(IlvDisplay* display);

    IlvS57Loader(IlvDisplay* display,const IlString& fileName);

    virtual		~IlvS57Loader();

    IlvI8211Rectangle&	getLatLonBounds();
    void		computeBounds();
    void		setRegionOfInterest(IlDouble,
					    IlDouble,
					    IlDouble,
					    IlDouble);

    void		readIt();

    void		restart();

    virtual IlvMapsError		getInitStatus() const;

    virtual const IlvMapFeature*	getNextFeature(IlvMapsError& error);

    void		addrefs(IlvMapGeometry*    geometry,
				IlvDSPMRecord*     dspmRecord, 
				IlvVRIDRecord*     vr,
				IlvS57Enumeration* orientation, 
				IlvS57Enumeration* usag);

    virtual IlvMapLineString* createMapLineString(IlvFRIDRecord* fr,
						  IlvS57EnumerationArray& ori,
						  IlvS57EnumerationArray& usags);

    virtual IlvMapMultiPoint* createMapMultiPoint(IlvFRIDRecord* fr,
						  IlvS57EnumerationArray& ori,
						  IlvS57EnumerationArray& usags);

    virtual IlvMapPolygon* createMapPolygon(IlvFRIDRecord* fr,
					    IlvS57EnumerationArray& ori,
					    IlvS57EnumerationArray& usags);

    virtual IlBoolean		isGeoreferenced();

    const IlvProjection*	getProjection() const;

    virtual IlBoolean		getUpperLeftCorner(IlvCoordinate&) const;
    virtual IlBoolean		getLowerRightCorner(IlvCoordinate&) const;

    virtual IlvFeatureRenderer*	getDefaultFeatureRenderer(IlvDisplay*);

    void			setFilename(const char* filename);

    const char*			getFilename() const;

    IlvMapFeatureIteratorDeclareClassInfo();

private:
    IlvI8211Rectangle		_bounds;
    IlvI8211Rectangle		_aoiDegrees;
    IlString			_filename;
    IlvDisplay*			_display;
    IlvMapsError		_formatError;
    IlvMapsError		_status;

    IlInt			_iFeature;
    IlvProjection*		_projection;
};
#endif /* !__Ilv_S57loader_H */
