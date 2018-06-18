// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/coordinate.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the VpfCoordinate class
// --------------------------------------------------------------------------
#ifndef VPF_COORDINATE_H
#define VPF_COORDINATE_H

#ifndef __Ilv_Maps_Project_H
# include <ilviews/maps/projection/project.h>
#endif

// --------------------------------------------------------------------------
class VpfCoordinate : public IlvCoordinate
{
public:
    VpfCoordinate();
    VpfCoordinate(double longitude, double latitude);
    VpfCoordinate(const VpfCoordinate& source);
    VpfCoordinate(const IlvCoordinate& source);

    VpfCoordinate& operator=(const VpfCoordinate& source);
    VpfCoordinate& operator=(const IlvCoordinate& source);
    void set(double longitude, double latitude);
    void translate(double longitude, double latitude);

    int operator==(const VpfCoordinate& source) const;
    int operator!=(const VpfCoordinate& source) const
	{ return !(*this == source); }
    double getLongitude() const { return getX(); }
    double getNormalizedLongitude() const
	{ return normalizeLongitude(getX()); }
    double getLatitude() const { return getY(); }

    void normalize();
    int isNormal() const { return getX() == getNormalizedLongitude(); }
protected:
    static inline double normalizeLongitude(double l) {
	if ((l >= -180.0) && (l <= 180.0))
	    return l;
	double add = (l > 0.0)
	    ? (l + 180.0)
	    : (l - 180.0);
	double times = (l + add) / 360.0;
	int itimes = (int)times;
	return (times - (double) itimes) * 360.0 - add;
    }
};

#endif /* VPF_COORDINATE_H */
