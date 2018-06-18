// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/coordinate.h
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
// Declaration of the VpfCoordinate class
// --------------------------------------------------------------------------
#ifndef VPF_COORDINATE_H
#define VPF_COORDINATE_H

// --------------------------------------------------------------------------
class VpfCoordinate
{
public:
    VpfCoordinate();
    VpfCoordinate(double longitude, double latitude);
    VpfCoordinate(const VpfCoordinate& source);

    VpfCoordinate& operator=(const VpfCoordinate& source);
    void		set(double longitude, double latitude);
    void		translate(double longitude, double latitude);

    int operator==(const VpfCoordinate& source) const;
    int operator!=(const VpfCoordinate& source) const { return !(*this == source); }

    double		getLongitude() const { return _longitude; }
    inline double	getNormalizedLongitude() const
			{
			    return _normalizedLongitude;
			}
    inline double	getLatitude() const { return _latitude; }

    void		normalize();
    inline int		isNormal() const
			{
			    return (_longitude == _normalizedLongitude);
			}

protected:
    double		_longitude;
    double		_normalizedLongitude;
    double		_latitude;

    static double	normalizeLongitude(double l);
};

#endif /* VPF_COORDINATE_H */
