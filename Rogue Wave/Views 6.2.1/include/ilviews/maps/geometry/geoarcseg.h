// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geoarcseg.h
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
// Defines an arc segment
// --------------------------------------------------------------------------

#ifndef _Ilv_Maps_IlvMapArcSegment_H
#define _Ilv_Maps_IlvMapArcSegment_H

#include <ilviews/maps/geometry/geosegment.h>

ILVMAPSMODULEINIT(IlvMapArcSegment);


class ILVMAPSEXPORTED IlvMapArcSegment
    :public IlvMapSegment
{
private:
    IlvCoordinate _start;
    IlvCoordinate _intermediate;
    IlvCoordinate _end;
public:
    IlvMapArcSegment();

    IlvMapArcSegment(const IlvMapArcSegment& source);

    IlvMapArcSegment(const IlvCoordinate& start,
		     const IlvCoordinate& intermediate,
		     const IlvCoordinate& end);

    virtual ~IlvMapArcSegment();


    void setIntermediatePoint(const IlvCoordinate& intermediate)
	{_intermediate = intermediate;}
    const IlvCoordinate& getIntermediatePoint() const {return _intermediate;}

    // documented in the superclass
    virtual void setStartPoint(const IlvCoordinate& start);
    virtual void setEndPoint(const IlvCoordinate& end);
    virtual const IlvCoordinate& getStartPoint() const;
    virtual const IlvCoordinate& getEndPoint() const;
    virtual IlUInt
    getHorizontalIntersectionCount(const IlvCoordinate& point) const;
    virtual IlBoolean isCollection() const;
    virtual IlUInt getSubElementCount() const;
    virtual const IlvMapGeometry* getSubElement(IlUInt index) const;
    virtual IlvMapGeometry* copy() const;
    virtual IlvClassInfo* getClassInfo() const;

    // not documented
    static IlUInt GetHorizontalIntersectionCount(IlDouble x, IlDouble y,
				       IlDouble ax, IlDouble ay,
				       IlDouble bx, IlDouble by,
				       IlDouble cx, IlDouble cy);

    ILVMAPS_DECL_GEOM_MEMBERS();
private:
	IlvMapsIcFriend(IlvMapArcSegment, ILVMAPSEXPORTED);
};

#endif /* _Ilv_Maps_IlvMapArcSegment_H */
