// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geoarea.h
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
// General Class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Geometry_IlvMapArea_H
#define __Ilv_Maps_Geometry_IlvMapArea_H

#if defined(IL_STD)
#include <cmath>
#else  /* !IL_STD */
#include <math.h>
#endif /* IL_STD */

#include <ilviews/maps/geometry/geocurve.h>

ILVMAPSMODULEINIT(IlvMapArea);

class ILVMAPSEXPORTED IlvMapArea : public IlvMapGeometry
{
private:
    static IlvClassInfo* _classinfo;
protected:
    IlvMapArea();

public:
    virtual ~IlvMapArea();

    virtual const IlvMapCurve* getStroke() const = 0;

    virtual IlBoolean contains(const IlvCoordinate& coordinate) const = 0;

    // documented in the superclass
    virtual IlvMapGeometry* copy() const = 0;
    virtual IlvClassInfo* getClassInfo() const = 0;

    // other ClassInfo functions
    static IlvClassInfo* ClassInfo();
    static IlvClassInfo** ClassInfoRef();
private:
	IlvMapsIcFriend(IlvMapArea, ILVMAPSEXPORTED);
};

#endif /* __Ilv_Maps_Geometry_IlvMapArea_H */
