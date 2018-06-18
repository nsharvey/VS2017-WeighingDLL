// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/azeqdist.h
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
// Definition of the IlvAzimuthalEquidistantProjection class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Azeqdist_H
#define __Ilv_Maps_Azeqdist_H

#include <ilviews/maps/projection/project.h>

ILVMAPSMODULEINIT(IlvAzimuthalEquidistantProjection);

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvAzimuthalEquidistantProjection
: public IlvProjection
{
public:
    IlvAzimuthalEquidistantProjection();

    // Projection specific parameters
    IlBoolean getGuam() const { return _guam; }

    IlBoolean isGuam() const { return getGuam(); }

    void setGuam(IlBoolean guam);

    // IO
public:
    virtual void write(IlvOutputFile&) const;

    // overloaded to update the internal parameters
public:
    virtual IlvMapsError setEllipsoid(const IlvEllipsoid& ellipsoid);
    virtual void setLLCenter(IlDouble lon, IlDouble lat);

    // Not documented, for library usage
    virtual void printPROJ4Specifics(IL_STDPREF ostream&) const;

    protected:
    virtual IlvMapsError sForward(IlvCoordinate& ll) const;
    virtual IlvMapsError eForward(IlvCoordinate& ll) const;
    virtual IlvMapsError sInverse(IlvCoordinate& xy) const;
    virtual IlvMapsError eInverse(IlvCoordinate& xy) const;
private:
    enum {
	SPole, NPole, Obliq, Equit
    }		_mode;
    IlDouble	_sinph0;
    IlDouble	_cosph0;
    IlDouble	_Mp;
    IlDouble	_N1;
    IlDouble	_GG;
    IlDouble	_He;
    IlBoolean	_guam;
    IlDouble	_M1;
    void computeParameters();
    virtual IlvMapsError gForward(IlvCoordinate& ll) const;
    virtual IlvMapsError gInverse(IlvCoordinate& ll) const;

    ILVMAPS_DECLMANDATORYPROJMEMBERS(IlvAzimuthalEquidistantProjection);    
};


#endif /* __Ilv_Maps_Azeqdist_H */
