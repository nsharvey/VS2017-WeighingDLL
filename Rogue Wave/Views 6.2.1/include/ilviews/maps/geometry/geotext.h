// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry/geotext.h
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
#ifndef __ILV_maps_Geometry_IlvMapText_H
#define __ILV_maps_Geometry_IlvMapText_H

#include <ilviews/maps/geometry.h>

ILVMAPSMODULEINIT(IlvMapText);

class ILVMAPSEXPORTED IlvMapText : public IlvMapGeometry
{
public:
    virtual ~IlvMapText();
    IlvMapText();

    IlvMapText(const IlvCoordinate& p, const char* text);

    IlvMapText(const IlvMapText& source);

    inline
    const IlvCoordinate& getPoint() const { return _point; }

    inline void		setPoint(const IlvCoordinate& point)
			{
			    _point.move(point.x(), point.y());
			}

    inline const char*	getText() const {return _text;}

    void		setText(const char* text);

    // documented in the setText
    virtual IlBoolean	isCollection() const;
    virtual IlUInt	getSubElementCount() const;
    virtual
    const IlvMapGeometry* getSubElement(IlUInt index) const;
    virtual
    IlvMapGeometry*	copy() const;
    virtual
    IlvClassInfo*	getClassInfo() const;

    ILVMAPS_DECL_GEOM_MEMBERS();

private:
    IlvMapsIcFriend(IlvMapText, ILVMAPSEXPORTED);

    char*		_text;
    IlvCoordinate	_point;

    
};

#endif /* __ILV_maps_Geometry_IlvMapText_H */
