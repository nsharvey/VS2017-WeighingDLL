// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geoimage.h
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
#ifndef __ILV_maps_Geometry_IlvMapImage_H
#define __ILV_maps_Geometry_IlvMapImage_H

#include <ilviews/maps/geometry/geoarea.h>
#include <ilviews/maps/geometry/geolinestr.h>
#include <ilviews/bitmaps/data.h>

ILVMAPSMODULEINIT(IlvMapImage);

class ILVMAPSEXPORTED IlvMapImage : public IlvMapArea
{
private:
    IlvCoordinate _upperLeftCorner;
    IlvCoordinate _lowerRightCorner;
    IlvBitmapData* _bitmapData;
    IlvMapLineString* _volatileStroke;

public:
    IlvMapImage();

    IlvMapImage(const IlvMapImage& source);
    virtual ~IlvMapImage();

    void setUpperLeftCorner(const IlvCoordinate& ul)
    {_upperLeftCorner=ul;}

    const IlvCoordinate& getUpperLeftCorner() const
    {return _upperLeftCorner;}

    void setLowerRightCorner(const IlvCoordinate& lr)
    {_lowerRightCorner=lr;}

    const IlvCoordinate& getLowerRightCorner() const
    {return _lowerRightCorner;}

    void setBitmapData(IlvBitmapData* bitmapData);
    IlvBitmapData* getBitmapData() const {return _bitmapData;}

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
	IlvMapsIcFriend(IlvMapImage, ILVMAPSEXPORTED);
};

#endif /* __ILV_maps_Geometry_IlvMapImage_H */
