// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/area.cpp
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
// Definition of the VpfRing and VpfArea classes
// --------------------------------------------------------------------------

#include <vpf/area.h>
#include <vpf/segment.h>
#include <string.h>

// --------------------------------------------------------------------------
VpfRing::VpfRing(VpfUInt id, VpfUInt nSegments)
: _id(id),
  _nSegments(nSegments),
  _segments(new VpfSegment*[nSegments])
{
    for (VpfUInt i = 0; i < _nSegments; i++)
	_segments[i] = 0;
}

// --------------------------------------------------------------------------
VpfRing::~VpfRing()
{
    if (_segments) {
	for (VpfUInt i = 0; i < _nSegments; i++)
	    if (_segments[i]) delete _segments[i];
	delete [] _segments;
    }
}

// --------------------------------------------------------------------------
void
VpfRing::resize(VpfUInt nSegments)
{
    VpfSegment** copy = new VpfSegment*[nSegments];
    memcpy(copy, _segments, nSegments * sizeof(VpfSegment*));
    delete [] _segments;
    _segments = copy;
    _nSegments = nSegments;
}

// --------------------------------------------------------------------------
VpfRing*
VpfRing::reshape(const VpfExtent& extent)
{
    VpfUInt j = 0;
    VpfSegment* result
#if defined(__GNUC__)
		       = 0
#endif /* Gnu */
    ;

    for (VpfUInt i = 0; i < _nSegments; i++) {
	if ((result = (VpfSegment*) _segments[i]->reshape(extent)) != 0) {
	    if (result != _segments[i])
		delete _segments[i];
	    if (i != j)
		_segments[j++] = result;
	}
    }
    _nSegments = j;
    return j
	? this
	: 0;
}

// --------------------------------------------------------------------------
VpfArea::VpfArea(VpfUInt id, VpfUInt nRings)
: _id(id),
  _nRings(nRings),
  _rings(new VpfRing*[nRings])
{
    for (VpfUInt i = 0; i < _nRings; i++)
	_rings[i] = 0;
}

// --------------------------------------------------------------------------
VpfArea::~VpfArea()
{
    if (_rings) {
	for (VpfUInt i = 0; i < _nRings; i++)
	    if (_rings[i])
		delete _rings[i];
	delete [] _rings;
    }
}

// --------------------------------------------------------------------------
void
VpfArea::resize(VpfUInt nRings)
{
    VpfRing** copy = new VpfRing*[nRings];
    memcpy(copy, _rings, nRings * sizeof(VpfRing*));
    delete [] _rings;
    _rings = copy;
    _nRings = nRings;
}

// --------------------------------------------------------------------------
VpfFeatureItem*
VpfArea::reshape(const VpfExtent& extent)
{
    VpfUInt j = 0;
    VpfRing* result
#if defined(__GNUC__)
		    = 0
#endif /* Gnu */
	;

    for (VpfUInt i = 0; i < _nRings; i++) {
	if ((result = _rings[i]->reshape(extent)) != 0) {
	    if (result != _rings[i])
		delete _rings[i];
	    if (i != j)
		_rings[j++] = result;
	}
    }
    _nRings = j;
    return j
	? this
	: 0;
}
