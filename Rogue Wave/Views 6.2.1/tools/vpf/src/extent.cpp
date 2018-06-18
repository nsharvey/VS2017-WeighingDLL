// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/extent.cpp
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
// Definition of the VpfExtent class
// --------------------------------------------------------------------------

#include <vpf/extent.h>
#include <vpf/coordinate.h>

// --------------------------------------------------------------------------
VpfExtent::VpfExtent()
{
}

// --------------------------------------------------------------------------
VpfExtent::VpfExtent(const VpfCoordinate& c1, const VpfCoordinate& c2)
{
    set(c1, c2);
}

// --------------------------------------------------------------------------
VpfExtent::VpfExtent(const VpfExtent& source)
: _c1(source._c1),
  _c2(source._c2)
{
}

// --------------------------------------------------------------------------
VpfExtent&
VpfExtent::operator=(const VpfExtent& source)
{
    _c1 = source._c1;
    _c2 = source._c2;
    return *this;
}

// --------------------------------------------------------------------------
void
VpfExtent::set(const VpfCoordinate& arg1, const VpfCoordinate& arg2)
{
    _c1 = arg1;
    _c1.normalize();
    _c2 = arg2;
    _c2.normalize();

    if ((_c1.getLongitude() == _c2.getLongitude()) &&
	(arg1.getLongitude() != arg2.getLongitude())) {
	_c1.set(-180.0, _c1.getLatitude());
	_c2.set(180.0, _c2.getLatitude());
    } else
    if (_c2.getLongitude() < _c1.getLongitude())
	_c2.translate(360.0, 0.0);
}

// --------------------------------------------------------------------------
int
VpfExtent::contains(const VpfCoordinate& c) const
{
    double lon = c.getNormalizedLongitude();
    double lat = c.getLatitude();

    if (lon < _c1.getLongitude())
	lon += 360.0;

    return ((lon >= _c1.getLongitude()) &&
	    (lon <= _c2.getLongitude()) &&
	    (lat >= _c1.getLatitude()) &&
	    (lat <= _c2.getLatitude()));
}

// --------------------------------------------------------------------------
int
VpfExtent::contains(const VpfExtent& e) const
{
    return contains(e._c1) && contains(e._c2);
}

// --------------------------------------------------------------------------
int
VpfExtent::intersects(const VpfExtent& e) const
{
    return ((e.getMaxLatitude() > getMinLatitude()) &&
	    (e.getMinLatitude() < getMaxLatitude()) &&
	    ((e.getMaxLongitude() > getMinLongitude())  &&
	     (e.getMinLongitude() < getMaxLongitude())) ||
	    // Case where 'this' is normalized, but not 'e'
	    ((getMaxLongitude() > 180) &&
	     (e.getMaxLongitude()+360. > getMinLongitude()) &&
	     (e.getMinLongitude()+360. < getMaxLongitude())));
}

// --------------------------------------------------------------------------
int
VpfExtent::reduce(VpfCoordinate& a, VpfCoordinate& b) const
{
    // Requirement a.getNormalizedLongitude() < b.getNormalizedLongitude()
    // Reduces the "ab" vector so it fits into the extent
    // Returns a non-zero value in the vector can't be reduced
    // (i.e. the vector does not intersect the extent)

    double deltax = b.getNormalizedLongitude() - a.getNormalizedLongitude();
    double deltay = b.getLatitude() - a.getLatitude();
    double ratio = deltax ? deltay / deltax : (double) 999999.0;
    double invratio = deltay ? deltax / deltay : (double) 999999.0;

    double ax = a.getNormalizedLongitude();
    double bx = b.getNormalizedLongitude();
    double ay = a.getLatitude();
    double by = b.getLatitude();

    double gMlo = getMaxLongitude();
    double gmlo = getMinLongitude();
    double gMla = getMaxLatitude();
    double gmla = getMinLatitude();

    // both points are out of extent
    if ((ax > gMlo) || (bx < gmlo))
	return 1;

    // the first point is out of extent (west)
    if (ax < gmlo) {
	// we approximate the position of a so that
	// ab has the same direction vector but a is
	// in the longitude extent
	ay += ratio * (gmlo - ax);
	ax = gmlo;
    }

    // the second point is out of extent (east)
    if (bx > gMlo) {
	// we approximate the position of b so that
	// ab has the same direction vector but b is
	// the longitude extent
	by -= ratio * (bx - gMlo);
	bx = gMlo;
    }

    // the first point is out of extent (south)
    if (ay < gmla) {
	if (by < gmla)
	    // the second point is ooe too.
	    return 1;

	// approximation so that a is in the
	// latitude extent
	ax += invratio * (gmla - ay);
	ay = gmla;
    } else
    if (ay > gMla) {
	// the first point is out of extent (north)
	if (by > gMla)
	    // and the second too
	    return 1;

	// approximation so that a is in the
	// latitude extent
	ax -= invratio * (ay - gMla);
	ay = gMla;
    }

    // the second point is out of extent (south)
    // but we know the first is not
    if (by < gmla) {
	bx += invratio * (gmla - by);
	by = gmla;
    } else
    if (by > gMla) {
	// the second point is out of extent (north)
	// but the second isn't
	bx -= invratio * (by - gMla);
	by = gMla;
    }
    a.set(ax, ay);
    b.set(bx, by);
    // reduction successful
    return 0;
}
