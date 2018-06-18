// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/lconfcon.h
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
// Definition of the IlvLambertConformalConicProjection class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Lconfcon_H
#define __Ilv_Maps_Lconfcon_H

#include <ilviews/maps/projection/conic.h>

ILVMAPSMODULEINIT(IlvLambertConformalConicProjection);

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvLambertConformalConicProjection
: public IlvConicProjection
{
public:
    IlvLambertConformalConicProjection(
			     IlDouble l1=IlvMaps::DegreeToRadian(33.),
			     IlDouble l2=IlvMaps::DegreeToRadian(45.));

    virtual IlvMapsError setEllipsoid(const IlvEllipsoid& ellipsoid);
    virtual void setLLCenter(IlDouble lon, IlDouble lat);
    virtual IlvMapsError setSecantLatitudes(const IlvCoordinate& secant);
    IlDouble getScaleFactor() const { return _k0; }
    void setScaleFactor(IlDouble k0) { _k0 = k0; }

    virtual void write(IlvOutputFile &) const;

protected:
    virtual IlvMapsError sForward(IlvCoordinate& ll) const;
    virtual IlvMapsError eForward(IlvCoordinate& ll) const;
    virtual IlvMapsError sInverse(IlvCoordinate& xy) const;
    virtual IlvMapsError eInverse(IlvCoordinate& xy) const;
    virtual void printPROJ4Specifics(IL_STDPREF ostream&) const;
private:
    IlDouble _n;
    IlDouble _c;
    IlDouble _rho0;
    IlDouble _k0;
    void initParameters();

    ILVMAPS_DECLMANDATORYPROJMEMBERS(IlvLambertConformalConicProjection);
};

#endif /* __Ilv_Maps_Lconfcon_H */
