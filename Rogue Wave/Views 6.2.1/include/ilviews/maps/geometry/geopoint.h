// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geopoint.h
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
// Geometry Class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Geometry_Point_H
#define __Ilv_Maps_Geometry_Point_H

#include <ilviews/maps/geometry.h>

ILVMAPSMODULEINIT(IlvMapPoint);

class ILVMAPSEXPORTED IlvMapPoint: public IlvMapGeometry
{
private:
    IlvCoordinate _point;

public:
    IlvMapPoint();

    IlvMapPoint(const IlvMapPoint& source);

    IlvMapPoint(const IlvCoordinate& point);

    virtual ~IlvMapPoint();

    void setPoint(const IlvCoordinate& point) {
	_point.move(point.x(), point.y());
    }

    const IlvCoordinate& getPoint() const {return _point;}

    // documented in the superclass
    virtual IlBoolean isCollection() const;
    virtual IlUInt getSubElementCount() const;
    virtual const IlvMapGeometry* getSubElement(IlUInt index) const;
    virtual IlvMapGeometry* copy() const;
    virtual IlvClassInfo* getClassInfo() const;

    ILVMAPS_DECL_GEOM_MEMBERS();
private:
	IlvMapsIcFriend(IlvMapPoint, ILVMAPSEXPORTED);
};

#endif /* __Ilv_Maps_Geometry_Point_H */
