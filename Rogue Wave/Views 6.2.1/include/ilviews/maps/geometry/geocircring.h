// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geocircring.h
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
// Defines a ring containing any type of segment
// --------------------------------------------------------------------------

#ifndef _Ilv_Maps_IlvCircularRing_H
#define _Ilv_Maps_IlvCircularRing_H

#include <ilviews/maps/geometry/georing.h>
#include <ilviews/maps/geometry/geocircle.h>

ILVMAPSMODULEINIT(IlvMapCircularRing);

class ILVMAPSEXPORTED IlvMapCircularRing
    :public IlvMapRing
{
private:
    IlvMapCircle* _stroke;
public:
    IlvMapCircularRing(IlvMapCircle* stroke);

    IlvMapCircularRing(const IlvMapCircularRing& source);

    virtual ~IlvMapCircularRing();

    const IlvMapCircle* getCircularStroke() const
	{return _stroke;}

    IlvMapCircle* setStroke(IlvMapCircle* stroke);

    // documented in the superclass
    virtual const IlvMapCurve* getStroke() const;
    virtual IlBoolean contains(const IlvCoordinate& coordinate) const;
    virtual IlBoolean isCollection() const;
    virtual IlUInt getSubElementCount() const;
    virtual const IlvMapGeometry* getSubElement(IlUInt index) const;
    virtual IlvMapGeometry* copy() const;
    virtual IlvClassInfo* getClassInfo() const;


    ILVMAPS_DECL_GEOM_MEMBERS();
private:
	IlvMapsIcFriend(IlvMapCircularRing, ILVMAPSEXPORTED);
};

#endif /* _Ilv_Maps_IlvCircularRing_H */
