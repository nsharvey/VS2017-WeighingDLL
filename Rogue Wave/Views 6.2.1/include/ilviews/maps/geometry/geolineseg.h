// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geolineseg.h
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
// Defines a linear segment
// --------------------------------------------------------------------------

#ifndef _Ilv_Maps_Geometry_IlvMapLinearSegment_H
#define _Ilv_Maps_Geometry_IlvMapLinearSegment_H

#include <ilviews/maps/geometry/geosegment.h>

ILVMAPSMODULEINIT(IlvMapLinearSegment);

class ILVMAPSEXPORTED IlvMapLinearSegment : public IlvMapSegment
{
private:
    IlvCoordinate _start;
    IlvCoordinate _end;
public:
    IlvMapLinearSegment();

    IlvMapLinearSegment(const IlvMapLinearSegment& source);

    IlvMapLinearSegment(const IlvCoordinate& start, const IlvCoordinate& end);

    virtual ~IlvMapLinearSegment();

    // documented in the superclass
    virtual void setStartPoint(const IlvCoordinate& start) ;
    virtual void setEndPoint(const IlvCoordinate& end) ;
    virtual const IlvCoordinate& getStartPoint() const;
    virtual const IlvCoordinate& getEndPoint() const;
    virtual IlBoolean isCollection() const;
    virtual IlUInt getSubElementCount() const;
    virtual const IlvMapGeometry* getSubElement(IlUInt index) const;
    virtual IlvClassInfo* getClassInfo() const;
    virtual IlvMapGeometry* copy() const;
    virtual IlUInt getHorizontalIntersectionCount(
				     const IlvCoordinate& point) const;

    ILVMAPS_DECL_GEOM_MEMBERS();

private:
	IlvMapsIcFriend(IlvMapLinearSegment, ILVMAPSEXPORTED);
};

#endif /* _Ilv_Maps_Geometry_IlvMapLinearSegment_H */
