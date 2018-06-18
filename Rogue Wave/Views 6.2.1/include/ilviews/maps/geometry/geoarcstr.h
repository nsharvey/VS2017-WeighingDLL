// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geoarcstr.h
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
// Defines a string composed by arcs segments
// --------------------------------------------------------------------------

#ifndef _Ilv_Maps_IlvMapArcString_H
#define _Ilv_Maps_IlvMapArcString_H

#include <ilviews/maps/geometry/coorvect.h>
#include <ilviews/maps/geometry/geosegstr.h>
#include <ilviews/maps/geometry/geoarcseg.h>

ILVMAPSMODULEINIT(IlvMapArcString);


class ILVMAPSEXPORTED IlvMapArcString
    :public IlvMapSegmentString
{
private:
    IlvMapCoordinateVector _points;
    IlvMapArcSegment* _volatileSegment;

public:
    IlvMapArcString(const IlvCoordinate& start);

    IlvMapArcString();

    IlvMapArcString(const IlvMapArcString& source);

    virtual ~IlvMapArcString();

    // documented in the superclass
    virtual void removeAll();
    virtual void setStartPoint(const IlvCoordinate& start);
    virtual const IlvCoordinate& getStartPoint() const;
    virtual void setEndPoint(const IlvCoordinate& end);
    virtual const IlvCoordinate& getEndPoint() const;
    virtual IlUInt
    getHorizontalIntersectionCount(const IlvCoordinate& point) const;
    virtual IlUInt getSegmentCount() const;

    void arcTo(const IlvCoordinate& intermediate,
	       const IlvCoordinate& end);

    // documented in the superclass
    virtual const IlvMapSegment* getSegment(IlUInt index) const ;

    const IlvMapArcSegment* getArcSegment(IlUInt index) const;

    // documented in the superclass
    virtual IlvMapGeometry* copy() const;
    virtual IlvClassInfo* getClassInfo() const;

    // not documented
    IlvMapCoordinateVector* getPoints() const {
	return (IlvMapCoordinateVector *)&_points;
    }

    ILVMAPS_DECL_GEOM_MEMBERS();
private:
	IlvMapsIcFriend(IlvMapArcString, ILVMAPSEXPORTED);
};

#endif /* _Ilv_Maps_IlvMapArcString_H */
