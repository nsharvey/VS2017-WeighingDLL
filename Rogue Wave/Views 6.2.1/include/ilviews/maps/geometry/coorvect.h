// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/coorvect.h
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
#ifndef __ILV_maps_Geometry_IlvMapCoordinateVector_H
#define __ILV_maps_Geometry_IlvMapCoordinateVector_H

#include <ilviews/maps/coord.h>

// Undocumented Class
class ILVMAPSEXPORTED IlvMapCoordinateVector {
private:
    IlvCoordinate* _points;
    int _size;
    int _pointCount;
public:
    IlvMapCoordinateVector();
    IlvMapCoordinateVector(const IlvMapCoordinateVector&);
    ~IlvMapCoordinateVector();

    void addPoint(const IlvCoordinate& point);
    const IlvCoordinate& getPoint(int i) const {return _points[i];}
    IlInt getPointCount() const {return _pointCount;}
    IlvMapCoordinateVector* copy() const;
    void shrink();
    void reset() {_pointCount = 0;}

    void set(const IlvMapCoordinateVector& source);

private:
    void grow();
};

#endif
