// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geopolygon.h
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
// Defines a polygon whose elements are segment rings.
// --------------------------------------------------------------------------

#ifndef __ILV_maps_Geometry_IlvMapPolygon_H
#define __ILV_maps_Geometry_IlvMapPolygon_H

#include <ilviews/macros.h>
#include <ilviews/base/link.h>
#include <ilviews/maps/geometry/georing.h>
#include <ilviews/maps/geometry/geomcurve.h>

ILVMAPSMODULEINIT(IlvMapPolygon);

class ILVMAPSEXPORTED IlvMapPolygon
    : public IlvMapArea
{
private:
    IlvMapRing* _exteriorRing;
    IlvList   _interiorRings;
    IlvMapMultiCurve* _volatileMultiCurve;
    IlBoolean _isTrokeValid;
public:
    IlvMapPolygon(IlvMapRing* exteriorRing);

    IlvMapPolygon(const IlvMapPolygon& source);

    virtual ~IlvMapPolygon();

    IlvMapRing* getExteriorRing() const {return _exteriorRing;}

    IlvMapRing* setExteriorRing(IlvMapRing* exteriorRing);

    virtual IlUInt getInteriorRingCount() const {
	return _interiorRings.length();
    }

    void removeInteriorRings();

    IlvMapRing* removeInteriorRing(const IlvMapRing* ring);


    void addInteriorRing(IlvMapRing* ring) {
	_interiorRings.append((IlAny) ring);
    }

    const IlvMapRing* getInteriorRing(IlUInt index) const;

    // documented in the superclass
    const virtual IlvMapCurve* getStroke() const;
    virtual IlBoolean contains(const IlvCoordinate& coordinate) const;
    virtual IlBoolean isCollection() const;
    virtual IlUInt getSubElementCount() const;
    virtual const IlvMapGeometry* getSubElement(IlUInt index) const;
    virtual IlvMapGeometry* copy() const;
    virtual IlvClassInfo* getClassInfo() const;

    ILVMAPS_DECL_GEOM_MEMBERS();
private:
	IlvMapsIcFriend(IlvMapPolygon, ILVMAPSEXPORTED);
};

#endif /* __ILV_maps_Geometry_IlvMapPolygon_H */
