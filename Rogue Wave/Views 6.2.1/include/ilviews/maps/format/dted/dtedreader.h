// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/dted/dtedreader.h
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
// The DTED reader class header file
// --------------------------------------------------------------------------

#ifndef _Ilv_map_Format_DTEDReader_H
#define _Ilv_map_Format_DTEDReader_H

#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/format/mapinput.h>
#include <ilviews/maps/rendering/cmodel.h>
#include <ilog/iurlstr.h>

ILVMAPSMODULEINIT(format_IlvDTEDReader);


class ILVMAPSEXPORTED IlvDTEDReader
    : public IlvMapFeatureIterator
{
public:
    IlvDTEDReader(const char* filename);

    IlvDTEDReader(IL_STDPREF istream& input);

    IlvDTEDReader(IlIUrlStream& input);

    virtual ~IlvDTEDReader();

    virtual IlvMapsError getInitStatus() const;

    virtual const IlvMapFeature* getNextFeature(IlvMapsError& status);

    virtual IlBoolean getLowerRightCorner(IlvCoordinate& coordinate) const;

    virtual IlBoolean getUpperLeftCorner(IlvCoordinate&) const;

    const IlvProjection* getProjection() const {
	return _projection;
    }

    IlvFeatureRenderer* getDefaultFeatureRenderer(IlvDisplay *);

    IlvMapFeatureIteratorDeclareClassInfo();

private:
    IlvMapsError readLowerLeftOrigin();
    IlvMapsError readElevations();    
    IlvMapsError readHeader();
    IlvMapsError readIntervals();
    IlvMapsError readSize();

    IlvMapsError init();
    IlvMapsError _status;
    IlvMapFeature* _feature;
    IlBoolean _oneFeatureRead;
    IlvMapGeometry* _geometry;
    IlUInt _cols;
    IlUInt _rows;
    IlShort *_values;
    IlvMapInput _input;
    IlInt _maxValue;
    IlInt _minValue;
    IlDouble _lowerLeftLat;
    IlDouble _lowerLeftLong;
    IlDouble _longitudeInterval;
    IlDouble _latitudeInterval;
    IlvProjection* _projection;
    IlvMapColorModel* _colorModel;
    IlBoolean _isUrl;
    static IlvMapsError _noError;
    static IlvMapsError _formatError;
    static IlvMapsError FormatError();
    static void Init();

    IlvMapsIcFriend(format_IlvDTEDReader, ILVMAPSEXPORTED);
};

#endif /* _Ilv_map_Format_DTEDReader_H */
