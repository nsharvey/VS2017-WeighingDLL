// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/projection.h
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
// Declaration of the Projection class
// --------------------------------------------------------------------------
#ifndef VPF_GUI_PROJECTION_H
#define VPF_GUI_PROJECTION_H

#include <vpf/string.h>
#include <ilviews/base/geometry.h>

class VpfCoordinate;

// --------------------------------------------------------------------------
class Projection
{
public:
    Projection(const char* name,
	       const IlvPoint& center,
	       double xMagnify, double yMagnify)
    : _name(VpfStrDup(name)),
      _center(center),
      _xMagnify(xMagnify),
      _yMagnify(-yMagnify)
    {}
    virtual ~Projection()
	{
	    if (_name)
		delete [] _name;
	}
    // ____________________________________________________________
    const char* getName() const { return _name; }
    const IlvPoint& getCenter() const { return _center; }
    virtual int forward(const VpfCoordinate& c, IlvPoint& p) const = 0;
    virtual int inverse(const IlvPoint& p, VpfCoordinate& c) const = 0;
protected:
    char*	_name;
    IlvPoint	_center;
    double	_xMagnify;
    double	_yMagnify;
};


#endif /* VPF_GUI_PROJECTION_H */
