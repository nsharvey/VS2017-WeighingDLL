// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/useproj.cpp
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
// Using a projection of the library.
//
// This example shows how to use the projections of this map library.
// It creates a projection instance and use it to project geographic
// coordinates (latitude and longitude) onto a plane coordinate system,
// and get the inverse projection, that is, project Cartesian coordinates
// onto an ellipsoid. 
// --------------------------------------------------------------------------


// including the projection declaration
#include <ilviews/maps/projection/mercator.h>

// --------------------------------------------------------------------------
void
showProjection(const IlvProjection& projection)
{
    double lambda = IlvMaps::DegreeToRadian(-45.);
    double phi = IlvMaps::DegreeToRadian(30.);

    IlvCoordinate ll(lambda, phi);
    IlvCoordinate xy;

    // forward projection (from long/lat to x/y)
    IlvMapsError status = projection.forward(ll, xy);

    if (status != IlvMaps::NoError())
        IlvPrint("Projection exception for this data : %s", 
		 IlvMaps::GetErrorMessageId(status));

    // printing the result
    IlvPrint("The projection of 45W 30N is \n"
	     " x = %d m\n"
	     " y = %d m",
	     (int) xy.x(),
	     (int) xy.y());

    // resetting ll
    ll.move(0., 0.);

    // inverse projection (from x/y to long/lat)
    status = projection.inverse(xy, ll);
    if (status != IlvMaps::NoError())
        IlvPrint("Projection exception for this data : %s", 
		 IlvMaps::GetErrorMessageId(status));


    // printing the result
    char buffer1[12];
    char buffer2[12];
    IlvPrint("The inverse projection is \n"
	     " %s %s",
	     IlvMaps::RadianToDMS(buffer1, ll.x(), IlFalse),
	     IlvMaps::RadianToDMS(buffer2, ll.y(), IlTrue));
}

// --------------------------------------------------------------------------
int
main(int , char**)
{
    IlvMercatorProjection projection;
    showProjection(projection);
    return 0;
}
