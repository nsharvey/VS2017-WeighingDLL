// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/dxf/src/dxffactory.cpp
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
// Definition of the DXF Graphic Factory class
// This class translates DXF entities into IlvGraphics
// --------------------------------------------------------------------------

#include <ilviews/graphics/line.h>
#include <ilviews/graphics/arc.h>
#include <ilviews/graphics/marker.h>
#include <ilviews/graphics/ellipse.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/maps/projection/unknownp.h>
#include <ilviews/maps/graphics/maplabel.h>

#include "dxffactory.h"

DXFGraphicFactory::DXFGraphicFactory(IlvMapInfo* targetMapInfo,
				     IlvProjection* sourceProjection)
:_mapInfo(targetMapInfo),
 _mapInfoOwner(IlFalse),
 _sourceProjection(sourceProjection),
 _points(new IlvPoint[30]),
 _maxSize(30)
{
    // If No Map Info is provided, the data will of course not be
    // projected. An adapter will be computed if the dxf file contains
    // its minimal and maximal extensions.
    if (!_mapInfo) {
	_project = IlFalse;
	_mapInfoOwner = IlTrue;
    }
    else
	// If a Map Info is provided, the created object will use the
	// map info. If the source projection (the projection of the
	// objects contained in the dxf files) is also provided,
	// the dxf data will be reprojected.
	_project = ((_mapInfo->getProjection()->getClassInfo() !=
		     IlvUnknownProjection::ClassInfo()) &&
		    _sourceProjection &&
		    (_sourceProjection->getClassInfo() !=
		     IlvUnknownProjection::ClassInfo()) &&
		    (_sourceProjection != _mapInfo->getProjection()));
}

DXFGraphicFactory::~DXFGraphicFactory()
{
    delete [] _points;
    if (_mapInfoOwner && _mapInfo)
	delete _mapInfo;
}

IlvPoint*
DXFGraphicFactory::toViews(IlInt size,
			   const IlvCoordinate* coordinates,
			   const IlvTransformer* t)
{
    if (size > _maxSize) {
	delete [] _points;
	if (_maxSize * 2 > size) {
	    _points = new IlvPoint[_maxSize * 2];
	    _maxSize *= 2;
	}
	else {
	    _points = new IlvPoint[size];
	    _maxSize = size;
	}
    }
    for (IlInt i = 0; i < size; i++)
	toViews(coordinates[i], _points[i], t);
    return _points;
}

IlvPoint
DXFGraphicFactory::toViews(const IlvCoordinate& orig,
			   const IlvTransformer* t)
{
    IlvPoint result;
    toViews(orig, result, t);
    return result;
}
void
DXFGraphicFactory::toViews(const IlvCoordinate& orig,
			   IlvPoint& result,
			   const IlvTransformer* t)
{
    static IlvCoordinate c;
    c.move(orig.x(), orig.y());
    
    if (t) {
	IlDouble x = orig.x();
	IlDouble y = orig.y();
	IlDouble x11, x12, x21, x22, x0, y0;
	t->getValues(x11, x12, x21, x22, x0, y0);
	c.move(x11 * x + x12 * y + x0, x21 * x + x22 * y + y0);
    }
    
    if (_project) {
	_sourceProjection->inverse(c, c);
	_mapInfo->forward(c, result);
    }
    else {
	if (!_mapInfo) {
	    // If no map info was provided, and if
	    // extmin and extmax were not found in the header
	    // then create a default map info....
	    IlvUnknownProjection p;
	    IlvMapAdapter a(1);
	    _mapInfo = new IlvMapInfo(&p, &a);
	}
	_mapInfo->getAdapter()->toViews(c, result);
    }
}

void
DXFGraphicFactory::updateMapInfo(const IlvCoordinate& ll,
				 const IlvCoordinate& ur)
{
    IlvMapAdapter adapter(IlvCoordinate(ll.x(), ur.y()),
			  IlvCoordinate(ur.x(), ll.y()),
			  IlvRect(- (1 << 15),
				  - ( 1 << 15),
				  1 << 16,
				  1 << 16));
    IlvUnknownProjection p;
    _mapInfo = new IlvMapInfo(&p, &adapter);
}


DXFDefaultGraphicFactory::DXFDefaultGraphicFactory(IlvDisplay* display,
						   IlvMapInfo* targetMapInfo,
						   IlvProjection* sourceProjection)
:DXFGraphicFactory(targetMapInfo, sourceProjection),
 _display(display)
{
}

IlvGraphic*
DXFDefaultGraphicFactory::createLine(const IlvTransformer* t,
				     const IlvCoordinate& from,
				     const IlvCoordinate& to,
				     IlvPalette* palette)
{
    return new IlvLine(_display,
		       toViews(from, t),
		       toViews(to, t),
		       palette);
}
IlvGraphic*
DXFDefaultGraphicFactory::createArc(const IlvTransformer* t,
				    const IlvCoordinate& ul,
				    const IlvCoordinate& lr,
				    IlDouble startAngle,
				    IlDouble angleRange,
				    IlvPalette* palette)
{
    IlvPoint ulPoint = toViews(ul, t);
    IlvPoint lrPoint = toViews(lr, t);
    IlvPos minX = ulPoint.x();
    if (lrPoint.x() < ulPoint.x())
	minX = lrPoint.x();
    IlvPos minY = ulPoint.y();
    if (lrPoint.y() < ulPoint.y())
	minY = lrPoint.y();
	
    return new IlvArc(_display,
		      IlvRect(minX,
			      minY,
			      (IlvDim) fabs((IlDouble) ulPoint.x() -
					    (IlDouble) lrPoint.x()),
			      (IlvDim) fabs((IlDouble) ulPoint.y() -
					    (IlDouble) lrPoint.y())),
		      (IlvFloat) startAngle,
		      (IlvFloat) angleRange,
		      palette);
}

IlvGraphic*
DXFDefaultGraphicFactory::createPoint(const IlvTransformer* t,
				      const IlvCoordinate& p,
				      IlvPalette* palette)
{
      return new IlvMarker(_display,
			   toViews(p, t),
			   IlvMarkerPlus,
			   4,
			   palette);
}
IlvGraphic*
DXFDefaultGraphicFactory::createCircle(const IlvTransformer* t,
				       const IlvCoordinate& center,
				       IlDouble radius,
				       IlvPalette* palette)
{
    IlvPoint cPoint = toViews(center, t);
    IlvPoint dxPoint = toViews(IlvCoordinate(center.x()+radius,
					     center.y()),
			       t);
    IlDouble r = sqrt((IlDouble) (cPoint.x() - dxPoint.x()) *
		       (IlDouble) (cPoint.x() - dxPoint.x()) +
		       (IlDouble) (cPoint.y() - dxPoint.y()) *
		       (IlDouble) (cPoint.y() - dxPoint.y()));
    if (r < 1)
	r = 1;

    return new IlvEllipse(_display,
			  cPoint,
			  (IlvDim) r,
			  palette);
}

IlvGraphic*
DXFDefaultGraphicFactory::createPolygon(const IlvTransformer* t,
					IlInt size,
					const IlvCoordinate* coordinates,
					IlvPalette* palette)
{
    IlvPoint* points = toViews(size, coordinates, t);
    IlvGraphic* result = new IlvPolygon(_display,
					size,
					points,
					palette);
    return result;
}

IlvGraphic*
DXFDefaultGraphicFactory::createPolyline(const IlvTransformer* t,
					 IlInt size,
					 const IlvCoordinate* coordinates,
					 IlvPalette* palette)
{
    IlvPoint* points = toViews(size, coordinates, t);
    IlvGraphic* result = new IlvPolyline(_display,
					 size,
					 points,
					 palette);
    return result;
}

IlvGraphic*
DXFDefaultGraphicFactory::createText(const IlvTransformer* t,
				     const char* string,
				     const IlvCoordinate& location,
				     IlvPosition position,
				     IlDouble height,
				     IlvPalette* palette)
{
  IlvPoint origin = toViews(location, t);
  IlvCoordinate c2(location.x(), location.y() + height);
  IlvPoint p2 = toViews(c2, t);
  height = fabs((IlDouble)(p2.y() - origin.y()));
  if (height < 1)
    return 0;
  IlDouble size = IlvMapLabel::GetLength(_display,
					  (IlvDim) height,
					  string,
					  palette);
  return new IlvMapLabel(_display,
			 origin,
			 IlvPoint(0, 0),
			 position,
			 size > height ? (IlvDim) (size * 1.5 ):
			                 (IlvDim) (height * 1.5),
			 string,
			 palette);
}
