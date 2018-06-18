// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/shapefile/dbfreader.h
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
#ifndef __ILV_maps_Format_shapefile_IlvShapeDBFReader_H
#define __ILV_maps_Format_shapefile_IlvShapeDBFReader_H

#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/format/mapinput.h>
#include <ilviews/maps/attribute.h>
#include <ilviews/maps/attribute/all.h>
#include <ilviews/maps/attrprop.h>
#include <ilviews/base/iostream.h>


ILVMAPSMODULEINIT(format_IlvShapeDBFReader);

class AttributeReader;
class ILVMAPSEXPORTED IlvShapeDBFReader
{
private:
    IlvMapInput   _input;       /** The map input */
    IlvMapsError  _initStatus;  /** an error code if init was not Ok */

    // dbf description data
    IlInt     _recordCount;
    IlShort   _headerSize;
    IlShort   _recordSize;
    IlInt     _fieldCount;   // attribute count

    IlUChar*                       _attributeSizes;
    char**                          _attributeNames;
    AttributeReader**               _attributeReaders;
    IlvMapClassInfo**               _attributeClasses;
    IlvFeatureAttributeInfo*        _attributeInfo;

    // for reading purpose
    IlUInt _start;
    IlUInt _currentLocation;
    IlUInt _currentObjectIndex;

public:
    IlvShapeDBFReader(const char* filename);

    IlvShapeDBFReader(IL_STDPREF istream& stream);

    virtual ~IlvShapeDBFReader();

    IlvMapsError getInitStatus() { return _initStatus; };

    int getRecordCount() { return _recordCount; };

    const IlvFeatureAttributeInfo* getInfo() { return _attributeInfo; };

    int getCurrentIndex() { return (_currentLocation-_start) / (_recordSize);}

    IlvFeatureAttributeProperty* getNextRecord(IlvMapsError& status);

    IlvFeatureAttributeProperty* readRecord(int index,
					    IlvMapsError& status);

private:
    static void InitStatic();
    void        initialize();

    IlvFeatureAttributeProperty* readCurrentRecord(IlvMapsError& status);

    IlvMapsError readHeader();

    IlvMapsIcFriend(format_IlvShapeDBFReader, ILVMAPSEXPORTED);
}; // class IlvShapeDBFReader

#endif /* __ILV_maps_Format_shapefile_IlvShapeDBFReader_H */
