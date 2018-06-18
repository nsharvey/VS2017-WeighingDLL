// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geomarea.h
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
#ifndef __ILV_maps_Geometry_IlvMapMultiArea_H
#define __ILV_maps_Geometry_IlvMapMultiArea_H

#include <ilviews/maps/geometry/geoarea.h>
#include <ilviews/maps/geometry/geomcurve.h>

ILVMAPSMODULEINIT(IlvMapMultiArea);

class ILVMAPSEXPORTED IlvMapMultiArea : public IlvMapArea
{
public:
    IlvMapMultiArea();

    IlvMapMultiArea(const IlvMapMultiArea& source);

    virtual ~IlvMapMultiArea();

    inline IlUInt	getCardinal() const { return _areas.length(); }

    inline
    const IlvMapArea*	getArea(IlUInt i) const
			{
			    return (const IlvMapArea*) _areas.getValue(i);
			}

    inline void		addArea(IlvMapArea* area)
			{
			    _areas.append((IlAny) area);
			}

    IlvMapArea*		removeArea(const IlvMapArea* area);

    void		removeAll();

    // documented in the superclass
    virtual
    const IlvMapCurve*	getStroke() const;
    virtual IlBoolean	contains(const IlvCoordinate& coordinate) const;
    virtual IlBoolean	isCollection() const;
    virtual IlUInt	getSubElementCount() const;
    virtual
    const IlvMapGeometry* getSubElement(IlUInt index) const;
    virtual
    IlvMapGeometry*	copy() const;
    virtual
    IlvClassInfo*	getClassInfo() const;

    // not documented
    inline void		resetList() { _areas.empty(); }
    inline 
    const IlvList&	getAreaList() const {return _areas;}

    ILVMAPS_DECL_GEOM_MEMBERS();    

private:
    IlvMapsIcFriend(IlvMapMultiArea, ILVMAPSEXPORTED);

    IlvList		_areas;
    IlvMapMultiCurve*	_volatileStroke;

};


#endif /* __ILV_maps_Geometry_IlvMapMultiArea_H */
