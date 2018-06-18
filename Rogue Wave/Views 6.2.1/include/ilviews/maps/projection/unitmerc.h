// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/unitmerc.h
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
// Definition of the IlvUniversalTransverseMercatorProjection class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Unitmerc_H
#define __Ilv_Maps_Unitmerc_H

#include <ilviews/maps/projection/tranmerc.h>

ILVMAPSMODULEINIT(IlvUniversalTransverseMercatorProjection);

class ILVMAPSEXPORTED IlvUniversalTransverseMercatorProjection
: public IlvTransverseMercatorProjection
{
public:
    IlvUniversalTransverseMercatorProjection(IlUShort zone = 30);
    IlvUniversalTransverseMercatorProjection(IlDouble lon);

    virtual IlBoolean isSouth() const { return _south; }

    void   setSouth(IlBoolean south);

    IlUShort getZone() const { return _zone; }

    IlBoolean setZone(IlUShort zone);

    virtual void setLLCenter(IlDouble lon, IlDouble lat);
    virtual void setScaleFactor(IlDouble k0);

    virtual void write(IlvOutputFile&) const;

protected:
    virtual void printPROJ4Specifics(IL_STDPREF ostream&) const;

private:
    IlBoolean	_south;
    IlUShort   _zone;
    void computeParameters();

    ILVMAPS_DECLMANDATORYPROJMEMBERS(
    IlvUniversalTransverseMercatorProjection);
};

#endif /* __Ilv_Maps_Unitmerc_H */
