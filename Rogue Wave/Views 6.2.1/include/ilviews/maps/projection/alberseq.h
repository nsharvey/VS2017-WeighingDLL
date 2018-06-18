// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/alberseq.h
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
// Definition of the IlvAlbersEqualAreaProjection class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_AlbersEqualArea_H
#define __Ilv_Maps_AlbersEqualArea_H

#include <ilviews/maps/projection/project.h>
#include <ilviews/maps/projection/conic.h>

ILVMAPSMODULEINIT(IlvAlbersEqualAreaProjection);

class ILVMAPSEXPORTED IlvAlbersEqualAreaProjection
: public IlvConicProjection
{
public:
    IlvAlbersEqualAreaProjection(IlDouble lat1=IlvMaps::DegreeToRadian(29.5),
				 IlDouble lat2=IlvMaps::DegreeToRadian(45.5));

    virtual IlvMapsError setSecantLatitudes(const IlvCoordinate& s);

    virtual IlvMapsError setEllipsoid(const IlvEllipsoid& ellipsoid);
    virtual void setLLCenter(IlDouble lon, IlDouble lat);

    virtual void write(IlvOutputFile&) const;

protected:
    virtual IlvMapsError sForward(IlvCoordinate& ll) const;
    virtual IlvMapsError eForward(IlvCoordinate& ll) const;
    virtual IlvMapsError sInverse(IlvCoordinate& xy) const;
    virtual IlvMapsError eInverse(IlvCoordinate& xy) const;

    virtual void printPROJ4Specifics(IL_STDPREF ostream&) const;

private:
    IlDouble _n;
    IlDouble _ec;
    IlDouble _c;
    IlDouble _dd;
    IlDouble _rho0;
    IlDouble _n2;

    void initParameters();

    ILVMAPS_DECLMANDATORYPROJMEMBERS(IlvAlbersEqualAreaProjection);
};

#endif /* __Ilv_Maps_AlbersEqualArea_H */
