// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/projimg/include/pcenter.h
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
// Declaration of center interactor class
// --------------------------------------------------------------------------
#ifndef _Pcenter_H
#define _Pcenter_H

#include "centeri.h"
#include "proj.h"

#include <ilviews/graphics/polyline.h>
#include <ilviews/graphics/set.h>

// --------------------------------------------------------------------------
#define LAT_DIV 3
#define LONG_DIV 3

#define NUM_LAT (360/LAT_DIV + 1)
#define NUM_LONG  (180/LONG_DIV + 1)

// --------------------------------------------------------------------------
class PointVector
{
public:
    PointVector(IlUInt np);
    ~PointVector();

    IlUInt getCount() const
	{ return _numPoints; }

    void setValid(IlUInt i, IlBoolean v)
	{ _valid[i] = v; }
    IlBoolean isValid(IlUInt i) const
	{ return _valid[i]; }

    IlvPoint* getPoints() const
	{ return _points; }
    IlvPoint& getPoint(IlUInt i) const
	{ return _points[i]; }

private:
    IlUInt _numPoints;
    IlBoolean* _valid;
    IlvPoint* _points;
};

// --------------------------------------------------------------------------
class ProjCenterInteractor
    : public CenterInteractor
{
public:
    ProjCenterInteractor(ImageProjector* ip);
    virtual ~ProjCenterInteractor();

    virtual IlBoolean canCenter(IlvEvent& event);
    virtual void doIt(IlvEvent& event);
    virtual void mouseMoved(IlvEvent& event);
    virtual void abort();
    void stop();
    void drawLines();

private:
    ImageProjector* _imageProjector;
    PointVector* _lat;
    PointVector* _long;
    IlvPalette* _palette;
    IlBoolean _started;
};

#endif
