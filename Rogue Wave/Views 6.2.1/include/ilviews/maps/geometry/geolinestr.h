// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geolinestr.h
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
// Defines the IlvMapLineString class
// --------------------------------------------------------------------------

#ifndef __ILV_maps_Geometry_IlvMapLineString_H
#define __ILV_maps_Geometry_IlvMapLineString_H

#include <ilviews/maps/geometry/geosegstr.h>
#include <ilviews/maps/geometry/coorvect.h>
#include <ilviews/maps/geometry/geolineseg.h>

ILVMAPSMODULEINIT(IlvMapLineString);

class ILVMAPSEXPORTED IlvMapLineString : public IlvMapSegmentString
{
public:
    IlvMapLineString();

    IlvMapLineString(const IlvCoordinate& startPoint);

    IlvMapLineString(const IlvMapLineString& source);

    virtual ~IlvMapLineString();

    void		lineTo(const IlvCoordinate& end)
			{
			    _points.addPoint(end);
			}

    // documented in the superclass
    virtual void	removeAll();
    virtual
    const IlvMapSegment* getSegment(IlUInt index) const;
    virtual void	setStartPoint(const IlvCoordinate& start);
    virtual
    const IlvCoordinate& getStartPoint() const;
    virtual void	setEndPoint(const IlvCoordinate& end);
    virtual
    const IlvCoordinate& getEndPoint() const;
    virtual
    IlUInt		getHorizontalIntersectionCount(const IlvCoordinate&) const;
    virtual IlUInt	getSegmentCount() const;


    const IlvMapLinearSegment* getLinearSegment(IlUInt index) const;

    IlUInt		getPointCount() const
			{
			    return _points.getPointCount();
			}

    const IlvCoordinate& getPoint(IlUInt index) const
			{
			    return _points.getPoint(index);
			}

    // Documented in the superclass
    virtual
    IlvMapGeometry*	copy() const;
    virtual
    IlvClassInfo*	getClassInfo() const;

    // Not documented
    IlvMapCoordinateVector* getPoints() const
			{
			    return (IlvMapCoordinateVector*) &_points;
			}

    ILVMAPS_DECL_GEOM_MEMBERS();

private:
    IlvMapsIcFriend(IlvMapLineString, ILVMAPSEXPORTED);

    IlvMapCoordinateVector	_points;
    IlvMapLinearSegment*	_volatileSegment;

};

#endif /* __ILV_maps_Geometry_IlvMapLineString_H */
