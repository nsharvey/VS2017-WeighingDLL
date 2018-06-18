// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/cadrg/cadrgread.h
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
// Definition of the IlvCADRGFrameReader class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Cadrg_Cadrgread_H
#define __Ilv_Maps_Format_Cadrg_Cadrgread_H

#if !defined(__Ilv_Maps_Mapfeature_H)
#  include <ilviews/maps/mapfeature.h>
#endif
#if !defined(__Ilv_Maps_Format_Mapinput_H)
#  include <ilviews/maps/format/mapinput.h>
#endif

ILVMAPSMODULEINIT(format_IlvCADRGFrameReader);

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvCADRGFrameReader
: public IlvMapFeatureIterator
{
public:
    IlvCADRGFrameReader(const char* fileName);
    IlvCADRGFrameReader(IL_STDPREF istream& input);
    virtual ~IlvCADRGFrameReader();

    virtual IlvMapsError	getInitStatus() const;
    virtual IlBoolean	getLowerRightCorner(IlvCoordinate& lr) const;
    virtual IlBoolean	getUpperLeftCorner(IlvCoordinate& ul) const;
    virtual const IlvProjection* getProjection() const;
    static IlvMapsError	FormatError();
    static IlvMapsError	InitError();
    virtual const IlvMapFeature* getNextFeature(IlvMapsError& status);
    virtual IlvFeatureRenderer*
    getDefaultFeatureRenderer(IlvDisplay* display);
    IlBoolean		isGeoreferenced() const;
    IlInt getCurrentSubFrame() const
	{ return _currentSubFrame; }

private:
    IlvMapsError	read();
    IlvMapsError	readHeader();
    IlvMapsError	readLocationSection();
    IlBoolean		readNextSection(IlBoolean* doneSections,
					IlvMapsError& status);
    IlvMapsError	readCoverageSection();
    IlvMapsError	readCompressionSection();
    IlvMapsError	readCompressionSubSection();
    IlvMapsError	readColorGraySection();
    IlvMapsError	readColorMapSubSection();
    IlvMapsError	readMaskSubsection();
    void		prepareFeatureReading();
    void		initProjection();
    void		initCoordinates();

    IlvMapInput		_input;
    IlvMapsError	_initStatus;
    IlUShort		_numberOfSections;
    struct CADRGLocationStruct {IlUShort id; IlUInt location;};
    CADRGLocationStruct* _locations;
    IlvProjection*	_projection;

    IlDouble		_upperLeftLat;
    IlDouble		_upperLeftLong;
    IlDouble		_lowerLeftLat;
    IlDouble		_lowerLeftLong;
    IlDouble		_upperRightLat;
    IlDouble		_upperRightLong;
    IlDouble		_lowerRightLat;
    IlDouble		_lowerRightLong;
    IlDouble		_verticalInterval;
    IlDouble		_horizontalInterval;
    IlInt		_cLookup[4][4096];
    IlUChar		_red[217];
    IlUChar		_green[217];
    IlUChar		_blue[217];
    IlUInt		_maskTable[36];

    IlvCoordinate	_upperLeftCorner;
    IlvCoordinate	_lowerRightCorner;
    IlDouble		_frameWidth;
    IlDouble		_frameHeight;
    IlInt		_currentSubFrame;
    IlvMapFeature*	_feature;

    IlvMapFeatureIteratorDeclareClassInfo();

    IlvMapsIcFriend(format_IlvCADRGFrameReader, ILVMAPSEXPORTED);
};

#endif /* !__Ilv_Maps_Format_Cadrg_Cadrgread_H */
