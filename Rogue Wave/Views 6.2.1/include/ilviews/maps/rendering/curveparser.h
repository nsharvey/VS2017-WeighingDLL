// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/rendering/curveparser.h
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
// Rendering class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Rendering_IlvCurveParser_H
#define __ILV_maps_Rendering_IlvCurveParser_H

#include <ilviews/maps/mapinfo.h>
#include <ilviews/maps/graphics/mapgenpath.h>
#include <ilviews/maps/geometry/geolinestr.h>
#include <ilviews/maps/geometry/geoarcstr.h>
#include <ilviews/maps/geometry/geocurvstr.h>
#include <ilviews/maps/geometry/geocircle.h>
#include <ilviews/maps/geometry/geomcurve.h>

// not documented
class ILVMAPSEXPORTED _IlvCurveParser
{
private:
    const IlvProjection* _sourceProjection;
    const IlvMapInfo* _targetMapInfo;
    IlvPoint _pointBuffer[2];
public:
    _IlvCurveParser(const IlvProjection* sourceProjection,
		    const IlvMapInfo* targetMapInfo):
	_sourceProjection(sourceProjection),
	_targetMapInfo(targetMapInfo) {}
    void setSourceProjection(const IlvProjection* sourceProjection)
	{_sourceProjection = sourceProjection;}
    void setTargetMapInfo(const IlvMapInfo* targetMapInfo)
	{_targetMapInfo = targetMapInfo;}

    // parsing methods: the classInfo  argument is systematically passed
    // to dispatching methods
    // in order to avoid multiple class to the virtual getClassInfo

    // segment methods
    virtual IlvMapsError moveToStart(IlvMapGeneralPath* currentGraphic,
				     const IlvMapSegment* segment) const;

    virtual IlvMapsError joinSegment(IlvMapGeneralPath* currentGraphic,
				     const IlvMapSegment* segment,
				     IlvClassInfo* segmentClassInfo) const;

    virtual IlvMapsError joinLinearSegment(IlvMapGeneralPath* currentGraphic,
					   const IlvMapLinearSegment*
					   linearSegment) const;

    virtual IlvMapsError joinArcSegment(IlvMapGeneralPath* currentGraphic,
					const IlvMapArcSegment*
					arcSegment) const;

    virtual IlvMapsError joinLineString(IlvMapGeneralPath* currentGraphic,
					const IlvMapLineString* lineString)
	const;

    virtual IlvMapsError joinArcString(IlvMapGeneralPath* currentGraphic,
				       const IlvMapArcString* arcString)
	const;

    virtual IlvMapsError joinCurveString(IlvMapGeneralPath* currentGraphic,
					 const IlvMapCurveString* curveString)
	const;

    virtual IlvMapsError addCircle(IlvMapGeneralPath* currentGraphic,
				   const IlvMapCircle* circle) const;

    virtual IlvMapsError addCurve(IlvMapGeneralPath* currentGraphic,
				  const IlvMapCurve* curve,
				  IlvClassInfo* classInfo) const;

    virtual IlvMapsError addMultiCurve(IlvMapGeneralPath* currentGraphic,
				       const IlvMapMultiCurve* curve) const;
};

#endif
