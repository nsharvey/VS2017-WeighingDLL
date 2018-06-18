// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geocircle.h
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
#ifndef __ILV_maps_Geometry_IlvMapCircle_H
#define __ILV_maps_Geometry_IlvMapCircle_H

#include <ilviews/maps/geometry.h>

ILVMAPSMODULEINIT(IlvMapCircle);

class ILVMAPSEXPORTED IlvMapCircle : public IlvMapCurve
{
public:
    IlvMapCircle(const IlvCoordinate& center, IlDouble radius);

    IlvMapCircle(const IlvCoordinate& control1,
		 const IlvCoordinate& control2,
		 const IlvCoordinate& control3);

    ~IlvMapCircle();

    const IlvCoordinate& getCenter() const { return _center; }
    IlDouble		getRadius() const { return _radius; }

    void		setCenter(const IlvCoordinate& c) { _center = c; }

    void		setRadius(IlDouble rad) { _radius = rad; }


    // documented in the superclass
    virtual IlBoolean	isCollection() const;
    virtual IlUInt	getSubElementCount() const;
    virtual
    const IlvMapGeometry* getSubElement(IlUInt index) const;
    virtual
    IlvMapGeometry*	copy() const;
    virtual
    IlvClassInfo*	getClassInfo() const;

    ILVMAPS_DECL_GEOM_MEMBERS();

private:
	IlvMapsIcFriend(IlvMapCircle, ILVMAPSEXPORTED);

    IlvCoordinate	_center;
    IlDouble		_radius;
};


#endif /* __ILV_maps_Geometry_IlvMapCircle_H */

