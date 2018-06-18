// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/objectmodel/8iwrite.h
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
// Declaration of the IlvObjectSDOWriter class
// Defined in library ilvdbmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Objectmodel_8iwrite_H
#define __Ilv_Maps_Format_Oracle_Objectmodel_8iwrite_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/geometry/all.h>

class IlvFeatureAttributeInfo;
class IldADTValue;
class _IlvMapsQueryHandler;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvObjectSDOWriter
{
    friend class _IlvMaps8iWriterErrorReporter;
public:
    IlvObjectSDOWriter(IldDbms*    dbms,
		       const char* tableName,
		       const char* geometryColumnName = "GEOMETRY",
		       const char* xDimensionName = "X",
		       const char* yDimensionName = "Y",
		       IlBoolean   createTables = IlFalse,
		       const IlvFeatureAttributeInfo* info = 0,
		       IlvCoordinate* upperLeftCorner = 0,
		       IlvCoordinate* lowerRightCorner = 0);
    virtual ~IlvObjectSDOWriter();

    virtual
    IlvMapsError	getInitStatus() const;

    inline void		setUsingOrderedRings(IlBoolean set)
			{
			    _isUsingOrderedRings = set;
			}
    inline IlBoolean	isUsingOrderedRings() { return _isUsingOrderedRings; }

    inline const char*	getLayerName() const { return _tableName.getValue(); }

    IldDbms*	getDbms() const;

    inline IlBoolean	isCheckingStringAttributes() const
			{
			    return _isCheckingString;
			}
    inline void		setCheckingStringAttributes(IlBoolean check)
			{
			    _isCheckingString = check;
			}

    virtual
    IlvMapsError	writeFeature(const IlvMapFeature* feature,
				     IlBoolean saveAtt = IlFalse);

    virtual
    IlvMapsError	writeFeatureIterator(IlvMapFeatureIterator* reader,
					     IlInt& count,
					     IlBoolean saveAtt = IlFalse);

    virtual IlvMapsError
	updateFeatureAttributes(const IlvFeatureAttributeProperty* attributes,
				IlUInt keyPos);

    virtual IlvMapsError
	updateFeatureAttribute(const char* keyColumnName,
			       const IlvFeatureAttribute* keyAttribute,
			       const char* attributeColumnName,
			       const IlvFeatureAttribute* attributeToUpdate);

    virtual
    IlvMapsError	close(IlDouble tolerance = 0.0,
			      const IlvCoordinate* upperLeft = 0,
			      const IlvCoordinate* lowerRight = 0);

    virtual IlvMapsError
    populateIndexes(IlShort fixedTilingLevel,
		    IlShort sdoNumtiles, // < 0 => not called in the parameters list of CREATE INDEX
		    const char* indexName, // can be ownerName.indexName
		    const char* sdoLayerName, // can be ownerName.layerName
		    const char* sdoGeometryColumnName = "GEOMETRY",
		    IlShort sdoMaxlevel = 32, // 32 is recommended by Oracle
		    IlInt sdoCommitInterval = -1,
		    const char* layerGtype = 0, // set it to "POINT" for layers composed of only points
		    const char* sdoTableSpace = 0,
		    const char* sdoInitialExtent = 0,
		    const char* sdoNextExtent = 0,
		    IlInt sdoMinExtents = -1, // -1 will insert NULL
		    IlInt sdoMaxExtents = -1, // -1 will insert NULL
		    IlInt sdoPCTincrease = -1, // -1 will insert NULL
		    const char* btreeInitialExtent = 0,
		    const char* btreeNextExtent = 0,
		    IlInt btreePCTincrease = -1);

protected:
    void		createTable(IldDbms*, const IlvFeatureAttributeInfo*,
				    IlvMapsError&);
    IlvMapsError	prepareWriteQuery(const IlvFeatureAttributeInfo*);
    IlvMapsError	makeSDOGeometry(const IlvMapFeature*);
    virtual IlvMapsError matchMapGeometry(const IlvMapGeometry*,
					 IlUInt&, IlUInt&);
    IlvMapsError	getCollection(const IlvMapGeometryCollection*,
				      IlUInt&);
    IlvMapsError	getMultiArea(const IlvMapMultiArea*, IlUInt&);
    IlvMapsError	getPolygon(const IlvMapPolygon*, IlUInt&);
    IlvMapsError	getCircle(const IlvMapCircle*, IlUInt&);
    IlvMapsError	getMultiCurve(const IlvMapMultiCurve*, IlUInt&);
    IlvMapsError	getLineString(const IlvMapLineString*, IlUInt&);
    IlvMapsError	getArcString(const IlvMapArcString*, IlUInt&);
    IlvMapsError	getCurveString(const IlvMapCurveString*, IlUInt&);
    IlvMapsError	getMultiPoint(const IlvMapMultiPoint*, IlUInt&);
    IlvMapsError	getPoint(const IlvMapPoint*, IlUInt&);
    IlvMapsError	getLinearSegment(const IlvMapLinearSegment*,
					 IlUInt&);
    IlvMapsError	getArcSegment(const IlvMapArcSegment*, IlUInt&);
private:
    void		addElemInfoArrayValue(IlInt);
    void		addOrdinateArrayValue(IlInt);
    void		addCoordinate(const IlvMapCoordinateVector*,
				      IlBoolean = IlTrue);
    void		addCoordinate(const IlvCoordinate&);
    void		addArcString(const IlvMapArcString*,
				     IlUInt&,
				     IlBoolean = IlTrue);
    IlUInt		addCurveString(const IlvMapCurveString*,
				       IlUInt&);
    void		addSegment(const IlvMapSegment*,
				   IlUInt&,
				   IlBoolean = IlTrue,
				   IlBoolean = IlTrue);
    static IlString	GetOwnerName(IlString*);
    static IlString	GetTableName(IlString*);

    IlvMapsError	_initStatus;
    IlvMapsError	_error;
    _IlvMapsQueryHandler* _qHandler;
    IlString		_tableName;
    IlString		_ownerName;
    IlString		_geometryColName;
    IlString		_xDimName;
    IlString		_yDimName;
    IlDouble		_minX;
    IlDouble		_maxX;
    IlDouble		_minY;
    IlDouble		_maxY;
    IlBoolean		_is816;
    IlBoolean		_isUsingOrderedRings;
    IlBoolean		_isSavingAttributes;
    IlBoolean		_isCheckingString;
    IldRequest*		_writeQuery;
    IldADTValue*	_sdoGeometryADT;
    IldADTValue*	_pointTypeADT;
    IldADTValue*	_elemInfoArrayADT;
    IldADTValue*	_ordinateArrayADT;
    IlUInt		_elemInfoArrayIndex;
    IlUInt		_ordinateArrayIndex;
};

#endif /* __Ilv_Maps_Format_Oracle_Objectmodel_8iwrite_H */
