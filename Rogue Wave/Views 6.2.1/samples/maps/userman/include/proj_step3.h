// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/include/proj_step3.h
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
// This file shows how to subclass IlvProjection to define a new projection
// that has specific parameters.
// It shows how to define a new accessor
// --------------------------------------------------------------------------


#ifndef __Newproj_H
#define __Newproj_H

#include <ilviews/maps/projection/project.h>


class Mercator : public IlvProjection
{
public:
    Mercator();

    void setLatitudeOfTrueScale(IlDouble latitudeOfTrueScale)
    {_latitudeOfTrueScale = latitudeOfTrueScale;}
    IlDouble getLatitudeOfTrueScale() const {return _latitudeOfTrueScale;}

    static IlvMapsError PolarZoneError() {return _polarZoneError;}

    virtual void write(IlvOutputFile&) const;
    
protected:
    virtual IlvMapsError sForward(IlvCoordinate &) const;
    virtual IlvMapsError sInverse(IlvCoordinate &) const;
    virtual IlvMapsError eForward(IlvCoordinate &) const;
    virtual IlvMapsError eInverse(IlvCoordinate &) const;
    
private:
    static void InitClass();
    
private:
    IlDouble _latitudeOfTrueScale;
    static IlvMapsError _polarZoneError;
    
    IlvMapsDeclareProjectionIO(Mercator);
};

// Enable IO initialization
IlvMapsInitProjectionIO(Mercator);

#endif
