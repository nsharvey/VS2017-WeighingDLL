// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/stereo.h
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
// Definition of the IlvStereographicProjection class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Stereo_H
#define __Ilv_Maps_Stereo_H

#include <ilviews/maps/projection/project.h>

ILVMAPSMODULEINIT(IlvStereographicProjection);

class ILVMAPSEXPORTED IlvStereographicProjection
: public IlvProjection
{
public:
    IlvStereographicProjection();

    IlDouble getLatitudeOfTrueScale() const { return _latitudeOfTrueScale; }

    void   setLatitudeOfTrueScale(IlDouble latitudeOfTrueScale);

    IlDouble getScaleFactor() const { return _k0; }

    virtual void setScaleFactor(IlDouble k0);

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
    enum {
	SPole,
	NPole,
	Obliq,
	Equit
    }	_mode;
    IlDouble _k0;
    IlDouble _akm1;
    IlDouble _latitudeOfTrueScale;
    IlDouble _cosph0;
    IlDouble _sinph0;
    IlDouble _cosX1;
    IlDouble _sinX1;	
    void computeParameters();
    static IlDouble Ss(IlDouble phit, IlDouble sinphi, IlDouble eccen);

    ILVMAPS_DECLMANDATORYPROJMEMBERS(IlvStereographicProjection);
};

#endif /* __Ilv_Maps_Stereo_H */
