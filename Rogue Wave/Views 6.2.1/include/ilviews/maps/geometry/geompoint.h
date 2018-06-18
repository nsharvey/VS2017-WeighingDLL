// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geompoint.h
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
#ifndef __ILV_maps_Geometry_IlvMapMultiPoint_H
#define __ILV_maps_Geometry_IlvMapMultiPoint_H

#include <ilviews/maps/geometry/geopoint.h>
#include <ilviews/maps/geometry/coorvect.h>

ILVMAPSMODULEINIT(IlvMapMultiPoint);

class ILVMAPSEXPORTED IlvMapMultiPoint
    : public IlvMapGeometry
{
private:
    IlvMapCoordinateVector _points;
    IlvMapPoint* _volatilePoint;
public:
    IlvMapMultiPoint();

    IlvMapMultiPoint(const IlvMapMultiPoint& source);

    virtual ~IlvMapMultiPoint();

    void removeAll() {
	_points.reset();
    }

    IlUInt getPointCount() const {
	return _points.getPointCount();
    }

    const IlvCoordinate& getPoint(IlUInt index) const {
	return _points.getPoint(index);
    }

    void addPoint(const IlvCoordinate& c) {
	_points.addPoint(c);
    }

    // documented in the superclass
    virtual IlBoolean isCollection() const;
    virtual IlUInt getSubElementCount() const;
    virtual const IlvMapGeometry* getSubElement(IlUInt index) const;
    virtual IlvMapGeometry* copy() const;
    virtual IlvClassInfo* getClassInfo() const;

    // not documented
    IlvMapCoordinateVector* getPoints() const 
	{return (IlvMapCoordinateVector*) &_points;}

    ILVMAPS_DECL_GEOM_MEMBERS();
private:
	IlvMapsIcFriend(IlvMapMultiPoint, ILVMAPSEXPORTED);
};

#endif /* __ILV_maps_Geometry_IlvMapMultiPoint_H */
