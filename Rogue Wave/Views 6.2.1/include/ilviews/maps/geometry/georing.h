// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/georing.h
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

#ifndef _Ilv_Maps_IlvMapRing_H
#define _Ilv_Maps_IlvMapRing_H

#include <ilviews/maps/macros.h>
#include <ilviews/maps/coord.h>
#include <ilviews/maps/geometry/geoarea.h>

ILVMAPSMODULEINIT(IlvMapRing);


class ILVMAPSEXPORTED IlvMapRing
    :public IlvMapArea
{
protected:
    IlvMapRing();
public:
    virtual ~IlvMapRing();

    // documented in the superclass
    virtual const IlvMapCurve* getStroke() const = 0;
    virtual IlBoolean contains(const IlvCoordinate& coordinate) const = 0;
    virtual IlvMapGeometry* copy() const = 0;
    virtual IlvClassInfo* getClassInfo() const = 0;

    // other ClassInfo functions
    static IlvClassInfo* ClassInfo();
    static IlvClassInfo** ClassInfoRef();
private:
    static IlvClassInfo* _classinfo;

private:
	IlvMapsIcFriend(IlvMapRing, ILVMAPSEXPORTED);
};

#endif /* _Ilv_Maps_IlvMapRing_H */
