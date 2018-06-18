// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geocurvstr.h
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
// Defines the IlvMapCurveString class
// --------------------------------------------------------------------------

#ifndef _Ilv_Maps_CurveStr_H
#define _Ilv_Maps_CurveStr_H

#include <ilviews/maps/geometry/geosegstr.h>

ILVMAPSMODULEINIT(IlvMapCurveString);

class ILVMAPSEXPORTED IlvMapCurveString
    :public IlvMapSegmentString
{
private:
    IlvList _segments;
public:

    IlvMapCurveString();

    IlvMapCurveString(const IlvMapCurveString& source);

    virtual ~IlvMapCurveString();

    // documented in the superclass
    virtual void removeAll();
    virtual const IlvMapSegment* getSegment(IlUInt index) const;
    virtual void setStartPoint(const IlvCoordinate& start);
    virtual const IlvCoordinate& getStartPoint() const;
    virtual void setEndPoint(const IlvCoordinate& end);
    virtual const IlvCoordinate& getEndPoint() const;
    virtual IlUInt
    getHorizontalIntersectionCount(const IlvCoordinate& point) const;
    virtual IlUInt getSegmentCount() const;


    void joinSegment(IlvMapSegment* segment);

    // documented insuperclass
    virtual IlvMapGeometry* copy() const;
    virtual IlvClassInfo* getClassInfo() const;

    // not documented (an iterator would be preferred)
    const IlvList& getSegmentList() const {return _segments;}

    ILVMAPS_DECL_GEOM_MEMBERS();
private:
	IlvMapsIcFriend(IlvMapCurveString, ILVMAPSEXPORTED);
};

#endif /* _Ilv_Maps_CurveStr_H */
