// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/flatprojection.h
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
// Declaration of the FlatProjection class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_FLATPROJECTION_H
#define VPF_GUI_FLATPROJECTION_H

#include <vpf/gui/projection.h>
#include <vpf/coordinate.h>

// --------------------------------------------------------------------------
class FlatProjection
: public Projection
{
public:
    FlatProjection(const IlvPoint& center,
		   double xMagnify, double yMagnify)
    : Projection("Plate-carree", center, xMagnify, yMagnify)
    {}
    // ____________________________________________________________
    virtual int forward(const VpfCoordinate& c, IlvPoint& p) const
	{
	    p = _center;
	    p.translate((IlvPos)(c.getNormalizedLongitude() * _xMagnify +
				 ((c.getNormalizedLongitude() < 0) ? -0.5 : 0.5)),
			(IlvPos)(c.getLatitude() * _yMagnify +
				 ((c.getLatitude() < 0) ? 0.5 : -0.5)));
	    return 0;
	}
    virtual int inverse(const IlvPoint& p, VpfCoordinate& c) const
	{
	    c.set((double) (p.x() - _center.x()) / _xMagnify,
		  (double) (p.y() - _center.y()) / _yMagnify);
	    return 0;
	}
};

#endif /* VPF_GUI_FLATPROJECTION_H */
