// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/polyline.h
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
// Declaration of classes allowing to define data displayers using lines.
// Contains:
//  - IlvPolylineChartDisplayer: a subclass of IlvSingleChartDisplayer which
//    represents data with a polyline.
//  - IlvPolygonChartDisplayer: a subclass of IlvPolylineChartDisplayer which
//    represents data with a polygon.
//  - IlvStepChartDisplayer: a subclass of IlvSingleChartDisplayer which
//    represents data with steps.
//  - IlvStairChartDisplayer: a subclass of IlvStepChartDisplayer which
//    represents data with stairs.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Polyline_H
#define __Ilv_Charts_Polyline_H

#if !defined(__Ilv_Charts_Display_H)
#include <ilviews/charts/display.h>
#endif

// --------------------------------------------------------------------------
// Class IlvPolylineChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPolylineChartDisplayer
    : public IlvSingleChartDisplayer
{
public:

    IlvPolylineChartDisplayer(IlvPalette* palette = 0);

    virtual ~IlvPolylineChartDisplayer();

    //== Displayer properties ====================

    virtual IlBoolean	isContinuous() const;

    virtual IlBoolean	canBeProjectedIfOutOfBounds() const;

    virtual IlvPalette*	getProjectedPointsPalette() const;

    void		setProjectedPointsPalette(IlvPalette* palette);

    virtual IlBoolean	graphicalRepresentationByDataPoint() const;

    virtual void
    treatPointsOutOfAbscissaLimits(const IlvRect& dataDisplayArea,
				   IlvChartDisplayerPoints* dispPts,
				   const IlvCoordInterval& abscissaRange,
				   const IlvPoint& minLimit,
				   const IlvPoint& maxLimit) const;

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    virtual IlBoolean	closePoints(IlvChartDisplayerPoints* dispPts,
				    const IlvTransformer*    t = 0) const;

    DeclareChartDisplayerTypeInfo(IlvPolylineChartDisplayer);

protected:
    IlvPalette*		_projectedPointsPalette;

    //== Internal methods ====================

    virtual void	drawPoints(IlvChartDisplayerPoints* dispPts,
				   IlvPort* dst,
				   const IlvTransformer* t = 0,
				   const IlvRegion* clip = 0) const;

    virtual
    IlvDoublePoint* selectDataPointsForPoint(IlUInt dataPointIndex,
					     IlUInt& count,
					     IlUInt*& dataPointIndexes) const;

    virtual void	computeItem(const IlvChartDisplayerPoints* dispPts,
				    IlUInt pointIndex,
				    IlUInt& usedPointsCount,
				    IlvPoint* points,
				    const IlvTransformer* t = 0) const;

    virtual
    IlUInt getItemPointsCount(const IlvChartDisplayerPoints* dispPts) const;

    virtual void	drawItem(const IlvChartDisplayerPoints*,
				 IlUInt pointIndex,
				 IlUInt pointCount,
				 IlvPoint* points,
				 IlvPalette* itemPalette,
				 IlvPort* dst,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;
};

// --------------------------------------------------------------------------
// Class IlvPolygonChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPolygonChartDisplayer
    : public IlvPolylineChartDisplayer
{
public:
    IlvPolygonChartDisplayer(IlvPalette* palette = 0);

    virtual IlBoolean	isFilled() const;

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    DeclareChartDisplayerTypeInfoRO(IlvPolygonChartDisplayer);

protected:
    virtual void	drawPoints(IlvChartDisplayerPoints* dispPts,
				   IlvPort* dst,
				   const IlvTransformer* t = 0,
				   const IlvRegion* clip = 0) const;

    virtual void	boundingBoxOfPoints(IlvChartDisplayerPoints* dispPts,
					    IlvRect& bbox,
					    IlBoolean takeInfoIntoAccount =
					    IlTrue,
					    const IlvTransformer* t = 0) const;

    virtual void	drawItem(const IlvChartDisplayerPoints* dispPts,
				 IlUInt pointIndex,
				 IlUInt pointCount,
				 IlvPoint* points,
				 IlvPalette* itemPalette,
				 IlvPort* dst,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;

    void		closePolygon(IlvChartDisplayerPoints* dispPts,
				     const IlvTransformer* t = 0) const;

    virtual
    IlvDoublePoint* selectDataPointsForPoint(IlUInt dataPointIndex,
					     IlUInt& count,
					     IlUInt*& dataPointIndexes) const;

};

// --------------------------------------------------------------------------
// Class IlvStepChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvStepChartDisplayer : public IlvSingleChartDisplayer
{
public:

    IlvStepChartDisplayer(IlvPalette* palette = 0);

    //== Displayer properties ====================

    virtual IlBoolean	isContinuous() const;

    virtual IlBoolean	graphicalRepresentationByDataPoint() const;

    virtual void
    treatPointsOutOfAbscissaLimits(const IlvRect& dataDisplayArea,
				   IlvChartDisplayerPoints* dispPts,
				   const IlvCoordInterval& abscissaRange,
				   const IlvPoint& minLimit,
				   const IlvPoint& maxLimit) const;

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    DeclareChartDisplayerTypeInfoRO(IlvStepChartDisplayer);

protected:

    //== Internal methods ====================

    virtual void	boundingBoxOfPoints(IlvChartDisplayerPoints* dispPts,
					    IlvRect& bbox,
					    IlBoolean takeInfoIntoAccount =
					    IlTrue,
					    const IlvTransformer* t = 0) const;

    virtual
    IlvDoublePoint* selectDataPointsForPoint(IlUInt dataPointIndex,
					     IlUInt& count,
					     IlUInt*& dataPointIndexes) const;

    virtual void	computeItem(const IlvChartDisplayerPoints* dispPts,
				    IlUInt pointIndex,
				    IlUInt& usedPointsCount,
				    IlvPoint* points,
				    const IlvTransformer* t = 0) const;

    virtual
    IlUInt getItemPointsCount(const IlvChartDisplayerPoints* dispPts) const;

    virtual void	drawItem(const IlvChartDisplayerPoints*,
				 IlUInt pointIndex,
				 IlUInt pointCount,
				 IlvPoint* points,
				 IlvPalette* itemPalette,
				 IlvPort* dst,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;
};

// --------------------------------------------------------------------------
// Class IlvFixedStepChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvFixedStepChartDisplayer
    : public IlvSingleChartDisplayer
{
public:

    IlvFixedStepChartDisplayer(IlvDim width = IlvChartDisplayerWidth, 
			       IlvPalette* palette = 0);

    virtual void	getClipArea(IlvRect& area,
				    const IlvTransformer* t) const;

    virtual IlvDim	getSizeAlongBase() const;

    inline IlvDim	getWidth() const { return 2*_size; }

    inline void		setWidth(IlvDim width) { _size = width/2; }

    inline IlvDim	getSize() const { return _size; }

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    DeclareChartDisplayerTypeInfo(IlvFixedStepChartDisplayer);

protected:
    IlvDim		_size;
    //== Internal methods ====================
    virtual void	boundingBoxOfPoints(IlvChartDisplayerPoints* dispPts,
					    IlvRect& bbox,
					    IlBoolean takeInfoIntoAccount =
					    IlTrue,
					    const IlvTransformer* t = 0) const;

    virtual void	computeItem(const IlvChartDisplayerPoints* dispPts,
				    IlUInt pointIndex,
				    IlUInt& usedPointsCount,
				    IlvPoint* points,
				    const IlvTransformer* t = 0) const;

    virtual
    IlUInt getItemPointsCount(const IlvChartDisplayerPoints* dispPts) const;

    virtual void	drawItem(const IlvChartDisplayerPoints*,
				 IlUInt pointIndex,
				 IlUInt pointCount,
				 IlvPoint* points,
				 IlvPalette* itemPalette,
				 IlvPort* dst,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;
};

// --------------------------------------------------------------------------
// Class IlvStairChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvStairChartDisplayer
    : public IlvStepChartDisplayer
{
public:

    IlvStairChartDisplayer(IlvPalette* palette = 0);

    virtual IlBoolean	isFilled() const;

    // API

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    DeclareChartDisplayerTypeInfoRO(IlvStairChartDisplayer);

protected:

    //== Internal methods ====================

    virtual void	drawPoints(IlvChartDisplayerPoints* dispPts,
				   IlvPort* dst,
				   const IlvTransformer* t = 0,
				   const IlvRegion* clip = 0) const;

    virtual void	boundingBoxOfPoints(IlvChartDisplayerPoints* dispPts,
					    IlvRect& bbox,
					    IlBoolean takeInfoIntoAccount =
					    IlTrue,
					    const IlvTransformer* t = 0) const;

    virtual void	computeItem(const IlvChartDisplayerPoints* dispPts,
				    IlUInt pointIndex,
				    IlUInt& usedPointsCount,
				    IlvPoint* points,
				    const IlvTransformer* t = 0) const;

    virtual
    IlUInt getItemPointsCount(const IlvChartDisplayerPoints* dispPts) const;

    virtual void	drawItem(const IlvChartDisplayerPoints* dispPts,
				 IlUInt pointIndex,
				 IlUInt pointCount,
				 IlvPoint* points,
				 IlvPalette* itemPalette,
				 IlvPort* dst,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;
};

ILVCHTMODULEINIT(polyline);

#endif /* !__Ilv_Charts_Polyline_H */
