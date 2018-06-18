// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/area.h
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
// Declaration of the Area feature related classes (ring)
// --------------------------------------------------------------------------
#ifndef VPF_AREA_H
#define VPF_AREA_H

#include <vpf/featureitem.h>
#include <vpf/segment.h>

#define VPFMAXRINGS  20000
#define VPFMAXSEGS   20000

// --------------------------------------------------------------------------
class VpfRing
{
public:
    VpfRing(VpfUInt, VpfUInt);
    ~VpfRing();
    // ____________________________________________________________
    VpfRing* reshape(const VpfExtent&);

    VpfUInt getID() const { return _id; }

    VpfUInt getNSegments() const { return _nSegments; }
    VpfSegment* getSegment(VpfUInt i) const { return _segments[i]; }
    void setSegment(VpfUInt i, VpfSegment* segment)
    {
	if (_segments[i] && (_segments[i] != segment))
	    delete _segments[i];
	_segments[i] = segment;
    }
    void resize(VpfUInt);
protected:
    VpfUInt		_id;
    VpfUInt		_nSegments;
    VpfSegment**	_segments;
};

// --------------------------------------------------------------------------
class VpfArea
: public VpfFeatureItem
{
public:
    VpfArea(VpfUInt id, VpfUInt nbRings);
    virtual ~VpfArea();
    // ____________________________________________________________
    virtual VpfFeatureItem* reshape(const VpfExtent&);
    
    VpfUInt getId() const { return _id; }

    VpfUInt getNRings() const { return _nRings; }
    VpfRing* getRing(VpfUInt i) const { return _rings[i]; }
    void setRing(VpfUInt i, VpfRing* ring)
    {
	if (_rings[i] && (ring != _rings[i]))
	    delete _rings[i];
	_rings[i] = ring;
    }
    void resize(VpfUInt nbRings);
private:
    VpfUInt	_id;
    VpfUInt	_nRings;
    VpfRing**	_rings;
};

#endif /* VPF_AREA_H */
