// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/proj_step3.cpp
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

#include "proj_step3.h"

#ifdef ILVSTD
#include <iostream>
#else
#include <iostream.h>
#endif

#include <ilog/sstream.h>


// --------------------------------------------------------------------------
IlvMapsDefineProjectionIO(Mercator,
			  IlvProjection,
			  "My Mercator Implementation",
			  new Mercator(),
			  Mercator::InitClass());


IlvMapsError Mercator::_polarZoneError;

// --------------------------------------------------------------------------
// the getter for the latitudeOfTrueScale accessor
static void
_getter(const IlvProjection* p, IlvValue& v)
{
    Mercator* mercator = (Mercator*) p;
    char buffer[12];
    v = IlvMaps::RadianToDMS(buffer,                                 
			     mercator->getLatitudeOfTrueScale(),            
			     IlTrue);
}

// --------------------------------------------------------------------------
// the setter for the latitudeOfTrueScale accessor
static IlBoolean
_setter(IlvProjection* p, const IlvValue& v)
{
    Mercator* mercator = (Mercator*) p;
    IlDouble value;                                                      
    IlvMapsError error = IlvMaps::DMSToRadian(v, value);             
    if (error != IlvMaps::NoError())                                  
	return IlFalse;                                                 
    mercator->setLatitudeOfTrueScale(value);                                
    return IlTrue;           
}

// --------------------------------------------------------------------------
void
Mercator::InitClass()
{
    _polarZoneError = IlvMaps::CreateError("&MercatorPolarZoneError");
    ClassInfo()->addAccessor(IlvGetSymbol("latitudeOfTrueScale"),
			     IlvValueStringType,
			     _getter,
			     _setter);
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
// Testing the projection accessor

#include <ilviews/maps/projection/projitf.h>
int
main(int , char**)
{
    Mercator merc;

    IlvProjectionInterface* interface = merc.getInterface();
    IlvValue v("latitudeOfTrueScale");

    const char* result = interface->queryValue(v);
    IlvPrint("Default latitude of True Scale is %s", result);

    v = "45";
    interface->changeValue(v);

    result = interface->queryValue(v);
    IlvPrint("Current latitude of True Scale is %s", result);

    if (fabs(merc.getLatitudeOfTrueScale() - IlvMaps::Pi() / 4) > 0.0000001)
	IlvPrint("The latitude of true scale was not set correctly");
    
    return 0;
}
