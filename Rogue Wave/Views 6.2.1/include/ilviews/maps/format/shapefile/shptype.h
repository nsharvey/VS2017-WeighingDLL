// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/shapefile/shptype.h
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
// ilog.views.maps.format.shapefile
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Format_shapefile_IlvShapeType_H
#define __ILV_maps_Format_shapefile_IlvShapeType_H

enum IlvShapeType {
    IlvShapeTypeNull        = 0,
    IlvShapeTypePoint       = 1,
    IlvShapeTypePolyline    = 3,
    IlvShapeTypePolygon     = 5,
    IlvShapeTypeMultipoint  = 8,
    IlvShapeTypePointZ      = 11,
    IlvShapeTypePolylineZ   = 13,
    IlvShapeTypePolygonZ    = 15,
    IlvShapeTypeMultipointZ = 18,
    IlvShapeTypePointM      = 21,
    IlvShapeTypePolylineM   = 23,
    IlvShapeTypePolygonM    = 25,
    IlvShapeTypeMultipointM = 28,
    IlvShapeTypeMultipatch  = 31
};

#endif /*__ILV_maps_Format_shapefile_IlvShapeType_H*/
