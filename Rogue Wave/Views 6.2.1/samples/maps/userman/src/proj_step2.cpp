// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/proj_step2.cpp
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
// that has specific parameters and specific error messages.
// It shows how to handle Input/Output of additional parameters
//          how to allocate new error messages
// --------------------------------------------------------------------------

#include "proj_step2.h"

#ifdef ILVSTD
#include <iostream>
ILVSTDUSE
#else
#include <iostream.h>
#endif

#include <ilog/sstream.h>


// --------------------------------------------------------------------------
// Using the definition macro that doesn't define
// the read constructor
// The private function Mercator::InitClass is passed
// as initialisation statement. This function initializes
// the Mercator specific error code.
IlvMapsDefineProjectionIO(Mercator,
			  IlvProjection,
			  "My Mercator Implementation",
			  new Mercator(),
			  Mercator::InitClass());


// The specific error code for the Mercator Projection
IlvMapsError Mercator::_polarZoneError;

// --------------------------------------------------------------------------
// This private function is called during the C++ static initialisation
// phase.
void
Mercator::InitClass()
{
    _polarZoneError = IlvMaps::CreateError("&MercatorPolarZoneError");
}

// --------------------------------------------------------------------------
Mercator::Mercator()
:IlvProjection(IlTrue, IlTrue, IlvConformalProjectionGeometricProperty),
 _latitudeOfTrueScale(0)
{
}

// --------------------------------------------------------------------------
// Copy constructor, called by the copy member function
Mercator::Mercator(const Mercator& source)
:IlvProjection(source),
 _latitudeOfTrueScale(source._latitudeOfTrueScale)
{
}

// --------------------------------------------------------------------------
// This constructor is called when a Mercator projection
// is read from an ilv file
Mercator::Mercator(IlvInputFile& file)
:IlvProjection(file)
{
    file.getStream() >> _latitudeOfTrueScale;
}

// --------------------------------------------------------------------------
// Thie function is called when a Mercator projection is
// saved into an ilv file.
void Mercator::write(IlvOutputFile &file) const
{
    IlvProjection::write(file);
    file.getStream() << _latitudeOfTrueScale << IlvSpc();
}

// --------------------------------------------------------------------------
IlvMapsError
Mercator::sForward(IlvCoordinate& ll) const
{
    // return an error if the point is close to a pole
    if (fabs(fabs(ll.y()) - IlvMaps::Pi() / 2.) <= 1e-10)
	// Returning the specific error code
	return PolarZoneError();

    IlDouble k = cos(_latitudeOfTrueScale);
    ll.setY(k * log(tan(IlvMaps::Pi() / 4. + 0.5 * ll.y())));
    ll.setX(k * ll.x());
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
IlvMapsError
Mercator::sInverse(IlvCoordinate& xy) const
{
    IlDouble k = cos(_latitudeOfTrueScale);
    xy.setX(xy.x() / k);
    xy.setY(IlvMaps::Pi() / 2. - 2. * atan(exp(-xy.y() / k)));
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
IlvMapsError
Mercator::eForward(IlvCoordinate& ll) const
{
    // return an error if the point is close to a pole
    if (fabs(fabs(ll.y()) - IlvMaps::Pi() / 2.) <= 1e-10)
	return PolarZoneError();

    IlDouble cosphi = cos(_latitudeOfTrueScale);
    IlDouble sinphi = sin(_latitudeOfTrueScale);
    IlDouble es = getEllipsoid()->getES();
    IlDouble k = cosphi / sqrt(1. - es * sinphi * sinphi);

    
    IlDouble	e = sqrt(getEllipsoid()->getES());
    sinphi = e * sin(ll.y());

    ll.setX(ll.x() * k);
    
    ll.setY(tan(.5 * (IlvMaps::Pi() / 2. - ll.y()))/pow((1. - sinphi) /
							(1. +  sinphi),
							0.5 * e));
    ll.setY(-log(ll.y()) * k);
    
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
IlvMapsError
Mercator::eInverse(IlvCoordinate& xy) const
{
    IlDouble cosphi = cos(_latitudeOfTrueScale);
    IlDouble sinphi = sin(_latitudeOfTrueScale);
    IlDouble es = getEllipsoid()->getES();
    IlDouble k = cosphi / sqrt(1. - es * sinphi * sinphi);
    
    
    IlDouble	ts = exp(-xy.y() / k);
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

    xy.setX(xy.x() / k);
    xy.setY(Phi);

    return IlvMaps::NoError();
}


// --------------------------------------------------------------------------
// Testing the projection

#include <ilviews/maps/projection/mercator.h>
int
main(int , char**)
{
    Mercator merc1;
    IlvMercatorProjection orig;

    IlvCoordinate ll(IlvMaps::Pi() / 4, IlvMaps::Pi() / 4);
    IlvCoordinate r1;
    IlvCoordinate r2;


    merc1.setLatitudeOfTrueScale(IlvMaps::Pi() / 4.);
    orig.setLatitudeOfTrueScale(IlvMaps::Pi() / 4.);


    // This code tests that the Mercator projection
    // is correctly saved and read.
    strstream s;
    IlvOutputFile f(s);
    merc1.save(f);
    s << ends;
    IlvInputFile in(s);
    Mercator* mercP = (Mercator*) IlvProjection::Load(in);
    Mercator& merc = *mercP;

    
    merc.forward(ll, r1);
    orig.forward(ll, r2);

    if (!r1.isCloseTo(r2, 0.0000001))
	IlvPrint("Error in sforward");

    merc.inverse(r1, r1);
    orig.inverse(r2, r2);
    
    if (!r1.isCloseTo(r2, 0.0000001))
	IlvPrint("Error in sInverse");

    merc.setEllipsoid(*IlvEllipsoid::WGS84());
    orig.setEllipsoid(*IlvEllipsoid::WGS84());
    
    merc.forward(ll, r1);
    orig.forward(ll, r2);

    if (!r1.isCloseTo(r2, 0.0000001))
	IlvPrint("Error in eforward");

    merc.inverse(r1, r1);
    orig.inverse(r2, r2);
    
    if (!r1.isCloseTo(r2, 0.0000001))
	IlvPrint("Error in eInverse");

    delete mercP;
    
    return 0;
	
}
