// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/segment.cpp
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
// Definition of the VpfSegment class
// --------------------------------------------------------------------------

#include <vpf/segment.h>
#include <vpf/extent.h>
#include <limits.h>

// --------------------------------------------------------------------------
VpfSegment::VpfSegment(VpfUInt id,
                       VpfUInt nCoordinates,
                       VpfCoordinate* coordinates)
: _ID(id),
  _nCoordinates(nCoordinates),
  _coordinates(coordinates
	       ? coordinates
	       : new VpfCoordinate[nCoordinates]),
  _inverted(0)
{
}

// --------------------------------------------------------------------------
VpfSegment::~VpfSegment()
{
    if (_coordinates)
	delete [] _coordinates;
}

// --------------------------------------------------------------------------
VpfFeatureItem*
VpfSegment::reshape(const VpfExtent& extent)
{
    if (_nCoordinates < 2)
	return 0;

    VpfCoordinate* nc = new VpfCoordinate[_nCoordinates];
    VpfUInt nnc = 0;
    VpfCoordinate previous(*getCoordinate(1));
    VpfCoordinate current;
    int previousWasIn = 0;
    int modified = 0;

    for (VpfUInt i = 0; i < _nCoordinates; i++) {
	current = *getCoordinate(i);

	if (extent.contains(current)) {
	    previousWasIn = 1;
	    nc[nnc++] = current;
	} else {
	    modified = 1;
	    int result = (previous.getNormalizedLongitude() <
			  current.getNormalizedLongitude())
		? extent.reduce(previous, current)
		: extent.reduce(current, previous);
	    if (!result) {
		if (previousWasIn)
		    nc[nnc++] = previous;
		nc[nnc++] = current;
		previousWasIn = 1;
	    } else {
		previousWasIn = 0;
	    }
	}
	previous = current;
    }

    if (modified)
	return new VpfSegment(_ID, nnc, nc);

    delete [] nc;
    return this;
}

// --------------------------------------------------------------------------
VpfCoordinate*
VpfSegment::getCoordinate(VpfUInt i) const
{
    if (isInverted())
	i = _nCoordinates - i - 1;
    return &_coordinates[i];
}

// --------------------------------------------------------------------------
void
VpfSegment::setCoordinate(VpfUInt i, const VpfCoordinate* coordinate)
{
    if (isInverted())
	i = _nCoordinates - i - 1;
    _coordinates[i] = *coordinate;
}
