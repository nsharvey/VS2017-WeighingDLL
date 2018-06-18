// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/segment.h
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
// Declaration of the VpfSegment class
// --------------------------------------------------------------------------
#ifndef VPF_SEGMENT_H
#define VPF_SEGMENT_H

#include <vpf/basictypes.h>
#include <vpf/coordinate.h>
#include <vpf/featureitem.h>

class VpfExtent;

// --------------------------------------------------------------------------
class VpfSegment : public VpfFeatureItem
{
public:
    VpfSegment(VpfUInt, VpfUInt, VpfCoordinate* = 0);
    virtual ~VpfSegment();
    // ____________________________________________________________
    virtual VpfFeatureItem*	reshape(const VpfExtent&);
    inline VpfUInt		getId() const { return _ID; }
    inline VpfUInt		getNCoordinates() const
				{
				    return _nCoordinates;
				}
    VpfCoordinate*		getCoordinate(VpfUInt) const;
    void			setCoordinate(VpfUInt, const VpfCoordinate*);
    inline void			setInverted(int inverted)
				{
				    _inverted = inverted;
				}
    inline int			isInverted() const { return _inverted; }

protected:
    VpfUInt			_ID;
    VpfUInt			_nCoordinates;
    VpfCoordinate*		_coordinates;
    int				_inverted;
};


#endif /* VPF_SEGMENT_H */
