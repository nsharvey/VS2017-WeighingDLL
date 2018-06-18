// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/georaster.h
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
// Geometry Package
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Geometry_IlvMapRaster_H
#define __ILV_maps_Geometry_IlvMapRaster_H

#include <ilviews/maps/geometry/geoarea.h>
#include <ilviews/maps/geometry/geolinestr.h>
#include <ilviews/maps/maps.h>

ILVMAPSMODULEINIT(IlvMapRaster);

class ILVMAPSEXPORTED IlvMapRaster
    : public IlvMapArea
{
private:
    IlBoolean _useUnknownValue;
    IlShort _unknownValue;
    IlvCoordinate _upperLeftCorner;
    IlvCoordinate _lowerRightCorner;
    IlInt _columns;
    IlInt _rows;
    IlShort* _values;
    IlvMapLineString* _volatileStroke;
    static IlvMapsError _unknownValueStatus;
    static IlvMapsError _outOfBoundStatus;
public:
    IlvMapRaster(const IlvCoordinate& upperLeftCorner,
		 const IlvCoordinate& lowerRightCorner,
		 IlInt columns,
		 IlInt rows,
		 IlShort* values,
		 IlBoolean copy,
		 IlBoolean useUnknownValue = IlFalse,
		 IlShort unknownValue = -1);

    IlvMapRaster(const IlvMapRaster& source);

    virtual ~IlvMapRaster();

    const IlShort* getValues() const
    { return _values;}

    IlInt getRows() const
    { return _rows;}

    IlInt getColumns() const
    {return _columns;}

    const IlvCoordinate& getUpperLeftCorner() const
    {return _upperLeftCorner;}

    const IlvCoordinate& getLowerRightCorner()
    {return _lowerRightCorner;}

    IlShort getValue(IlInt column, IlInt row, IlvMapsError& status) const;

    IlShort getValue(const IlvCoordinate& point, IlvMapsError& status) const;

    static IlvMapsError UnknownValueStatus();

    static IlvMapsError OutOfBoundStatus();

    // documented in the superclass
    virtual IlvMapGeometry* copy() const;
    virtual const IlvMapCurve* getStroke() const;
    virtual IlBoolean contains(const IlvCoordinate& coordinate) const;
    virtual IlBoolean isCollection() const;
    virtual IlUInt getSubElementCount() const;
    virtual const IlvMapGeometry* getSubElement(IlUInt index) const;
    virtual IlvClassInfo* getClassInfo() const;

    ILVMAPS_DECL_GEOM_MEMBERS();
private:
	IlvMapsIcFriend(IlvMapRaster, ILVMAPSEXPORTED);
};


#endif /* __ILV_maps_Geometry_IlvMapRaster_H */
