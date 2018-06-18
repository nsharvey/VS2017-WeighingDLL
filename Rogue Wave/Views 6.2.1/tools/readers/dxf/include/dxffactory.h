// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/dxf/include/dxffactory.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the DXF Graphic Factory class
// This class translates DXF entities into IlvGraphics
// --------------------------------------------------------------------------

#ifndef DXFGraphicFactory_H
#define DXFGraphicFactory_H

#include <ilviews/base/graphic.h>
#include <ilviews/maps/projection/project.h>
#include <ilviews/maps/mapinfo.h>

// The abstract factory class
class DXFGraphicFactory
{
  public:
    DXFGraphicFactory(IlvMapInfo* targetMapInfo = 0,
		      IlvProjection* sourceProjection = 0);
    virtual ~DXFGraphicFactory();

    virtual IlvGraphic* createArc(const IlvTransformer* t,
				  const IlvCoordinate& ur,
				  const IlvCoordinate& lr,
				  IlDouble startAngle,
				  IlDouble angleRange,
				  IlvPalette* palette) = 0;
    virtual IlvGraphic* createCircle(const IlvTransformer* t,
				     const IlvCoordinate& center,
				     IlDouble radius,
				     IlvPalette* palette) = 0;
    virtual IlvGraphic* createLine(const IlvTransformer* t,
				   const IlvCoordinate& from,
				   const IlvCoordinate& to,
				   IlvPalette* palette) = 0;
    virtual IlvGraphic* createPoint(const IlvTransformer* t,
				    const IlvCoordinate& p,
				    IlvPalette* palette) = 0;
    virtual IlvGraphic* createPolygon(const IlvTransformer* t,
				       IlInt size,
				       const IlvCoordinate* coordinates,
				       IlvPalette* palette) = 0;
    virtual IlvGraphic* createPolyline(const IlvTransformer* t,
				       IlInt size,
				       const IlvCoordinate* coordinates,
				       IlvPalette* palette) = 0;
  
    virtual IlvGraphic* createText(const IlvTransformer* t,
				   const char* string,
				   const IlvCoordinate& location,
				   IlvPosition position,
				   IlDouble height,
				   IlvPalette* palette) = 0;



    // Coordinate transformations
    IlvPoint* toViews(IlInt size,
		      const IlvCoordinate* coordinates,
		      const IlvTransformer* t);
    IlvPoint toViews(const IlvCoordinate& c, const IlvTransformer* t);
    void toViews(const IlvCoordinate& c,
		 IlvPoint& p,
		 const IlvTransformer* t);
    const IlvMapInfo* getMapInfo() const {return _mapInfo;}


    // called by the dxf reader if extmin and extmax are found in the file.
    void updateMapInfo(const IlvCoordinate& ll,
		       const IlvCoordinate& ur);

    
  private:
    IlvMapInfo* _mapInfo;
    IlBoolean _mapInfoOwner;
    IlvProjection* _sourceProjection;
    IlBoolean _project;
    IlvPoint* _points;
    IlInt _maxSize;
};

// The default implementation
class DXFDefaultGraphicFactory : public DXFGraphicFactory
{
  public:
    DXFDefaultGraphicFactory(IlvDisplay* display,
			     IlvMapInfo* targetMapInfo = 0,
			     IlvProjection* sourceProjection = 0);
    virtual IlvGraphic* createArc(const IlvTransformer* t,
				  const IlvCoordinate& ul,
				  const IlvCoordinate& lr,
				  IlDouble startAngle,
				  IlDouble angleRange,
				  IlvPalette* palette);
    virtual IlvGraphic* createCircle(const IlvTransformer* t,
				     const IlvCoordinate& center,
				     IlDouble radius,
				     IlvPalette* palette);
    virtual IlvGraphic* createLine(const IlvTransformer* t,
				   const IlvCoordinate& from,
				   const IlvCoordinate& to,
				   IlvPalette* palette);
    virtual IlvGraphic* createPoint(const IlvTransformer* t,
				    const IlvCoordinate& p,
				    IlvPalette* palette);
    virtual IlvGraphic* createPolygon(const IlvTransformer* t,
				       IlInt size,
				       const IlvCoordinate* coordinates,
				       IlvPalette* palette);
    virtual IlvGraphic* createPolyline(const IlvTransformer* t,
				       IlInt size,
				       const IlvCoordinate* coordinates,
				       IlvPalette* palette);
    virtual IlvGraphic* createText(const IlvTransformer* t,
				   const char* string,
				   const IlvCoordinate& location,
				   IlvPosition position,
				   IlDouble height,
				   IlvPalette* palette);

    
  private:
    IlvDisplay* _display;
};

#endif
