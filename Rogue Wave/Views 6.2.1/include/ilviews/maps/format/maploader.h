// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/maploader.h
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
// ilog.views.maps.format
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Format_IlvMapLoader_H
#define __ILV_maps_Format_IlvMapLoader_H

#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/base/iostream.h>

class IlvManager;
class IlvManagerLayer;
class IlvProjection;
class IlvMapFeatureIterator;
class IlvFeatureRenderer;
class ILVMAPSEXPORTED IlvMapLoader
{
public:
    IlvMapLoader(IlvManager* manager);
    virtual ~IlvMapLoader();

    virtual IlUInt load(const char* fileName, IlvMapsError& status);

    virtual IlUInt load(IlvMapFeatureIterator* iterator,
			 IlvMapsError& status);

    virtual IlUInt load(IlvMapFeatureIterator* iterator,
			 IlvFeatureRenderer* renderer,
			 IlvMapsError& status);

    virtual IlvMapFeatureIterator* makeFeatureIterator(const char* filename);

    void		setDefaultSourceProjection(IlvProjection* projection);

protected:
    IlvManager*		_manager;
    IlvManagerLayer*	_insertionLayer;
    IlBoolean		_attachAttributes;
    IlvProjection*	_defaultSourceProjection;

};

#endif /* __ILV_maps_Format_IlvMapLoader_H */
