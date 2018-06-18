// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/geogproj.h
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
// Rogue Wave Views - Maps add-on.
// Definition of the IlvGeographicProjection class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Geographic_H
#define __Ilv_Maps_Geographic_H

#include <ilviews/maps/projection/project.h>

ILVMAPSMODULEINIT(IlvGeographicProjection);

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvGeographicProjection
: public IlvProjection
{

public:
    IlvGeographicProjection();
    virtual IlvMapsError setEllipsoid(const IlvEllipsoid& ellipsoid);

protected:
    virtual IlvMapsError sForward(IlvCoordinate& ll) const;
    virtual IlvMapsError sInverse(IlvCoordinate& xy) const;

    virtual IL_STDPREF ostream& printPROJ4Descriptor(IL_STDPREF ostream&,
						     IlvMapsError* status = 0)
	const;
private:
    void initParameters();

    ILVMAPS_DECLMANDATORYPROJMEMBERS(IlvGeographicProjection);
};

#endif /* __Ilv_Maps_Eqdiscyl_H */
