// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/extent.h
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
// Declaration of the VpfExtent class
// --------------------------------------------------------------------------
#ifndef VPF_EXTENT_H
#define VPF_EXTENT_H

#include <vpf/coordinate.h>

// --------------------------------------------------------------------------
class VpfExtent
{
public:
    VpfExtent();
    VpfExtent(const VpfCoordinate& c1, const VpfCoordinate& c2);
    VpfExtent(const VpfExtent& source);
    // ____________________________________________________________
    VpfExtent& operator=(const VpfExtent& source);
    void		set(const VpfCoordinate& c1, const VpfCoordinate& c2);

    inline double	getMinLongitude() const { return _c1.getLongitude(); }
    inline double	getMaxLongitude() const { return _c2.getLongitude(); }
    inline double	getMinLatitude()  const { return _c1.getLatitude(); }
    inline double	getMaxLatitude()  const { return _c2.getLatitude(); }

    int			contains(const VpfCoordinate& c1) const;
    int			contains(const VpfExtent& e) const;
    int			intersects(const VpfExtent& e) const;

    int			reduce(VpfCoordinate&, VpfCoordinate&) const;

protected:
    VpfCoordinate	_c1;
    VpfCoordinate	_c2;
};

#endif /* VPF_EXTENT_H */

