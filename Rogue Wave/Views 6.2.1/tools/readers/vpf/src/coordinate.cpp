// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/coordinate.cpp
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
// Definition of the VpfCoordinate class
// --------------------------------------------------------------------------

#include <vpf/coordinate.h>

// --------------------------------------------------------------------------
VpfCoordinate::VpfCoordinate()
: IlvCoordinate(0,0)
{
}

// --------------------------------------------------------------------------
VpfCoordinate::VpfCoordinate(double longitude,
                             double latitude)
: IlvCoordinate(longitude, latitude)
{
}

VpfCoordinate::VpfCoordinate(const IlvCoordinate& coord)
: IlvCoordinate(coord)
{
}

// --------------------------------------------------------------------------
VpfCoordinate::VpfCoordinate(const VpfCoordinate& source)
: IlvCoordinate(source.getX(), source.getY())
{
}

// --------------------------------------------------------------------------
VpfCoordinate&
VpfCoordinate::operator=(const VpfCoordinate& source)
{
    move(source.getX(), source.getY());
    return *this;
}

//-----------------------------------------------------------------------------
VpfCoordinate&
VpfCoordinate::operator=(const IlvCoordinate& source)
{
    move(source.getX(), source.getY());
    return *this;
}

// --------------------------------------------------------------------------
void
VpfCoordinate::set(double longitude, double latitude)
{
    move(longitude, latitude);
}

// --------------------------------------------------------------------------
void
VpfCoordinate::translate(double longitude, double latitude)
{
    setX(getX()+longitude);

    // Might look weird, but for now we want a new
    // latitude in the ]-180, 180] range
    // A value outside the [-90, 90] range tells us that
    // we have also to change the longitude to reflect passing a pole
    double newLatitude = normalizeLongitude(latitude + getY());
    if (newLatitude < -90.0) {
	setY(-180 - newLatitude);
	setX(normalizeLongitude(getX() + 180.0));	
    } else if (getY() > 90.0) 
	setY(180 - newLatitude);
     else 
	setY(newLatitude);
}

// --------------------------------------------------------------------------
void
VpfCoordinate::normalize()
{
    setX(getNormalizedLongitude());
}

// --------------------------------------------------------------------------
int
VpfCoordinate::operator==(const VpfCoordinate& source) const
{
    return ((getNormalizedLongitude() == source.getNormalizedLongitude()) &&
	    (getY() == source.getY()));
}
