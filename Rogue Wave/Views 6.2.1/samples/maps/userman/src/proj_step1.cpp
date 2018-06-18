// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/proj_step1.cpp
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
// --------------------------------------------------------------------------

#include "proj_step1.h"

IlvMapsDefineBasicProjectionIO(Mercator,
			       IlvProjection,
			       "My Mercator Implementation",
			       new Mercator(),
			       IlvMapsEmptyStatement());



// --------------------------------------------------------------------------
Mercator::Mercator()
:IlvProjection(IlTrue, IlTrue, IlvConformalProjectionGeometricProperty)
{
}

// --------------------------------------------------------------------------
Mercator::Mercator(const Mercator& source)
:IlvProjection(source)
{
}

// --------------------------------------------------------------------------
IlvMapsError
Mercator::sForward(IlvCoordinate& ll) const
{
    // return an error if the point is close to a pole
    if (fabs(fabs(ll.y()) - IlvMaps::Pi() / 2.) <= 1e-10)
	return ToleranceConditionError();
    
    ll.setY(log(tan(IlvMaps::Pi() / 4. + 0.5 * ll.y())));
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
IlvMapsError
Mercator::sInverse(IlvCoordinate& xy) const
{
    xy.setY(IlvMaps::Pi() / 2. - 2. * atan(exp(-xy.y())));
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
IlvMapsError
Mercator::eForward(IlvCoordinate& ll) const
{
    // return an error if the point is close to a pole
    if (fabs(fabs(ll.y()) - IlvMaps::Pi() / 2.) <= 1e-10)
	return ToleranceConditionError();
    
    IlDouble	e = sqrt(getEllipsoid()->getES());
    IlDouble    sinphi = e * sin(ll.y());
    
    ll.setY(tan(.5 * (IlvMaps::Pi() / 2. - ll.y()))/pow((1. - sinphi) /
							(1. +  sinphi),
							0.5 * e));
    ll.setY(-log(ll.y()));
    
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
IlvMapsError
Mercator::eInverse(IlvCoordinate& xy) const
{
    IlDouble	ts = exp(-xy.y());
    IlDouble	e = sqrt(getEllipsoid()->getES());
    IlDouble	eccnth = 0.5 * e;
    IlDouble	Phi = IlvMaps::Pi() / 2. -2. * atan(ts);

    int		i = 15;
    IlDouble	dphi;
    
    do {
	IlDouble	con = e * sin(Phi);
	dphi = IlvMaps::Pi()/2.
	    - 2. * atan(ts * pow((1 - con)/(1 + con), eccnth)) - Phi;
	Phi += dphi;
    } while(fabs(dphi) > 1.e-10 && --i != 0);
    if(i <= 0)
	return ToleranceConditionError();

    xy.setY(Phi);

    return IlvMaps::NoError();
}


// --------------------------------------------------------------------------
// Testing the projection and comparing with the IlvMercatorProjection

#include <ilviews/maps/projection/mercator.h>
int
main(int , char**)
{
    Mercator merc;
    IlvMercatorProjection orig;

    IlvCoordinate ll(IlvMaps::Pi() / 4, IlvMaps::Pi() / 4);
    IlvCoordinate r1;
    IlvCoordinate r2;

    merc.forward(ll, r1);
    orig.forward(ll, r2);

    if (!r1.isCloseTo(r2, 0.000001))
	IlvPrint("Error in sforward");

    merc.inverse(r1, r1);
    orig.inverse(r2, r2);
    
    if (!r1.isCloseTo(r2, 0.000001))
	IlvPrint("Error in sInverse");

    merc.setEllipsoid(*IlvEllipsoid::WGS84());
    orig.setEllipsoid(*IlvEllipsoid::WGS84());
    
    merc.forward(ll, r1);
    orig.forward(ll, r2);

    if (!r1.isCloseTo(r2, 0.000001))
	IlvPrint("Error in eforward");

    merc.inverse(r1, r1);
    orig.inverse(r2, r2);
    
    if (!r1.isCloseTo(r2, 0.000001))
	IlvPrint("Error in eInverse");

    return 0;
	
}
