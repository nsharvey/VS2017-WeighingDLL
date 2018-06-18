// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/hshiftdatum.h
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
// Defined in library ilvmaps
// --------------------------------------------------------------------------


#ifndef __Ilv_Maps_HorizontalShiftDatum_H
#define __Ilv_Maps_HorizontalShiftDatum_H

#include <ilviews/maps/macros.h>
#include <ilviews/maps/projection/ellips.h>
#include <ilviews/maps/projection/hdatum.h>

ILVMAPSMODULETERM(hshiftdatum);

class ILVMAPSEXPORTED IlvHorizontalShiftDatum : public IlvHorizontalDatum
{
public:
    IlvHorizontalShiftDatum(const char* name,
			    const char* regionOfUse,
			    const IlvEllipsoid& ellipsoid,
			    IlDouble dx,
			    IlDouble dy,
			    IlDouble dz);
    IlvHorizontalShiftDatum(const IlvHorizontalShiftDatum &source);

    ~IlvHorizontalShiftDatum();
    const char*		getName() const { return _name; }
    const char*		getRegionOfUse() const { return _regionOfUse; }
    IlDouble		getDX() const { return _dx; };
    IlDouble		getDY() const { return _dy; };
    IlDouble		getDZ() const { return _dz; };
    IlBoolean		equivalent(const IlvHorizontalDatum* datum) const;

    virtual
    IlvHorizontalDatum*	copy() const;

    static const IlvHorizontalShiftDatum* WGS84();

    IlvMapsDeclareIO(IlvHorizontalShiftDatum);
    IlvMapsIcFriend(hshiftdatum, ILVMAPSEXPORTED);

private:
    static void		Init();
    static void		Finalize();

    char*		_name;
    char*		_regionOfUse;
    IlDouble		_dx;
    IlDouble		_dy;
    IlDouble		_dz;
}; // IlvHorizontalShiftDatum


#endif /* __Ilv_Maps_HorizontalShiftDatum_H */
