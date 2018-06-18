// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/coordinate.cpp
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
// Definition of the VpfCoordinate class
// --------------------------------------------------------------------------

#include <vpf/coordinate.h>

// --------------------------------------------------------------------------
VpfCoordinate::VpfCoordinate()
: _longitude(0.0),
  _normalizedLongitude(0.0),
  _latitude(0.0)
{
}

// --------------------------------------------------------------------------
VpfCoordinate::VpfCoordinate(double longitude,
                             double latitude)
: _longitude(longitude),
  _normalizedLongitude(normalizeLongitude(longitude)),
  _latitude(latitude)
{
}

// --------------------------------------------------------------------------
VpfCoordinate::VpfCoordinate(const VpfCoordinate& source)
: _longitude(source._longitude),
  _normalizedLongitude(source._normalizedLongitude),
  _latitude(source._latitude)
{
}

// --------------------------------------------------------------------------
VpfCoordinate&
VpfCoordinate::operator=(const VpfCoordinate& source)
{
    _longitude = source._longitude;
    _latitude = source._latitude;
    _normalizedLongitude = source._normalizedLongitude;
    return *this;
}

// --------------------------------------------------------------------------
void
VpfCoordinate::set(double longitude, double latitude)
{
    _longitude = longitude;
    _latitude = latitude;
    _normalizedLongitude = normalizeLongitude(_longitude);
}

// --------------------------------------------------------------------------
void
VpfCoordinate::translate(double longitude, double latitude)
{
    _longitude += longitude;
    _normalizedLongitude = normalizeLongitude(_longitude);

    // Might look weird, but for now we want a new
    // latitude in the ]-180, 180] range
    // A value outside the [-90, 90] range tells us that
    // we have also to change the longitude to reflect passing a pole
    double newLatitude = normalizeLongitude(latitude + _latitude);
    if (newLatitude < -90.0) {
	_latitude = -180 - newLatitude;
	_normalizedLongitude =
	    _longitude = normalizeLongitude(_longitude + 180.0);
    } else
    if (_latitude > 90.0) {
	_latitude = 180 - newLatitude;
	_normalizedLongitude =
	    longitude = normalizeLongitude(_longitude + 180.0);
    } else {
	_latitude = newLatitude;
	_normalizedLongitude = normalizeLongitude(_longitude);
    }
}

// --------------------------------------------------------------------------
double
VpfCoordinate::normalizeLongitude(double l)
{
    if ((l >= -180.0) && (l <= 180.0))
	return l;
    double add = (l > 0.0)
	? (l + 180.0)
	: (l - 180.0);
    double times = (l + add) / 360.0;
    int itimes = (int)times;
    return (times - (double) itimes) * 360.0 - add;
}

// --------------------------------------------------------------------------
void
VpfCoordinate::normalize()
{
    _longitude = _normalizedLongitude;
}

// --------------------------------------------------------------------------
int
VpfCoordinate::operator==(const VpfCoordinate& source) const
{
    return ((_normalizedLongitude == source._normalizedLongitude) &&
	    (_latitude == source._latitude));
}
