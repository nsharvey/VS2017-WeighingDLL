// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geomcurve.h
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
// Geometry Package
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Geometry_IlvMapMultiCurve_H
#define __ILV_maps_Geometry_IlvMapMultiCurve_H

#include <ilviews/maps/geometry/geocurve.h>
#include <ilviews/base/link.h>

ILVMAPSMODULEINIT(IlvMapMultiCurve);


class ILVMAPSEXPORTED IlvMapMultiCurve : public IlvMapCurve
{
public:
    IlvMapMultiCurve();

    IlvMapMultiCurve(const IlvMapMultiCurve& source);

    virtual ~IlvMapMultiCurve();

    inline IlUInt	getCardinal() const { return _curves.length(); }

    inline 
    const IlvMapCurve*	getCurve(IlUInt i) const
			{
			    return (const IlvMapCurve*) _curves.getValue(i);
			}

    inline void		addCurve(IlvMapCurve* curve)
			{
			    _curves.append((IlAny) curve);
			}

    IlvMapCurve*	removeCurve(const IlvMapCurve* curve);

    void		removeAll();

    // documented in the superclass
    virtual IlBoolean	isCollection() const;
    virtual IlUInt	getSubElementCount() const;
    virtual
    const IlvMapGeometry* getSubElement(IlUInt index) const;
    virtual
    IlvMapGeometry*	copy() const;
    virtual
    IlvClassInfo*	getClassInfo() const;

    // not documented
    inline void		resetList() { _curves.empty(); }
    inline
    const IlvList&	getCurveList() const { return _curves; }

    ILVMAPS_DECL_GEOM_MEMBERS();

private:
    IlvMapsIcFriend(IlvMapMultiCurve, ILVMAPSEXPORTED);

    IlvList _curves;
};

#endif /* __ILV_maps_Geometry_IlvMapMultiCurve_H */
