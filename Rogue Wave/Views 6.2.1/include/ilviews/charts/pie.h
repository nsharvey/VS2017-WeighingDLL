// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/pie.h
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
// Declaration of the classes needed to draw a pie chart.
// Contains:
//  - IlvPieSliceInfo.
//  - IlvPieChartDisplayer: a subclass of IlvSingleChartDisplayer which 
//    represents data with a pie.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Pie_H
#define __Ilv_Charts_Pie_H

#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif

#if !defined(__Ilv_Charts_Display_H)
#include <ilviews/charts/display.h>
#endif

#if !defined(__Ilv_Charts_Data_H)
#include <ilviews/charts/data.h>
#endif

#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif

// --------------------------------------------------------------------------
// Class IlvPieSliceInfo
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPieSliceInfo : public IlvChartDataGraphicInfo
{
public:
    IlvPieSliceInfo(IlBoolean tornOff,
		    IlvPalette* palette = 0,
		    IlvGraphic* graphic = 0);

    virtual ~IlvPieSliceInfo();

    //== Accessors ============
    inline IlBoolean	isTornOff() const { return _tornOff; }

    inline void		setTornOff(IlBoolean flag) { _tornOff = flag; }

    inline const char*	getLegendText() const 
			{
			    return _legendText.isEmpty()
				? (const char*)0
				: (const char*)_legendText;
			}

    inline void		setLegendText(const char* legendText)
			{
			    _legendText = legendText;
			}

    DeclareChartDataPointInfoTypeInfo(IlvPieSliceInfo);

protected:
    IlBoolean		_tornOff;
    IlString		_legendText;
};

// --------------------------------------------------------------------------
// Class IlvPieChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvPieChartDisplayer : public IlvSingleChartDisplayer
{
public:
    IlvPieChartDisplayer(IlDouble radius,
			 IlDouble startingAngle = 0.0,
			 IlDouble range = 360.0,
			 IlvDim tearOffDelta = 20,		
			 IlvPalette* palette = 0);

    virtual ~IlvPieChartDisplayer();

    virtual IlBoolean	useVirtualDataSets() const;

    virtual IlBoolean	isContinuous() const;

    //== Accessors ============
    void		setRadius(IlDouble radius);

    inline IlDouble	getRadius() const { return _radius; }

    void		setStartingAngle(IlDouble angle);

    inline IlDouble	getStartingAngle() const { return _startingAngle; }

    void		setRange(IlDouble range);

    inline IlDouble	getRange() const { return _range; }

    inline void		setTearOffDelta(IlvDim delta)
			{
			    _tearOffDelta = delta;
			}

    inline IlvDim	getTearOffDelta() const { return _tearOffDelta; }

    virtual void	setChartGraphic(IlvChartGraphic* chart);

    //== Slice infos handling ============

    IlUInt		getSliceInfoCount() const;

    IlvPieSliceInfo*	getSliceInfo(IlUInt sliceIndex) const;

    void		setSliceInfo(IlUInt sliceIndex,
				     IlvPieSliceInfo* sliceInfo);

    void		removeSliceInfo(IlUInt sliceIndex);

    void		removeAllSliceInfo();

    inline
    IlvPointInfoCollection* getSliceInfoCollection() const
			{
			    return _sliceInfos;
			}

    //== Slices methods ============
    IlvPalette*		getSlicePalette(IlUInt sliceIndex) const;

    void		setSlicePalette(IlUInt sliceIndex,
					IlvPalette* palette);

    IlBoolean		isSliceTornOff(IlUInt sliceIndex) const;

    void		tearOffSlice(IlUInt sliceIndex,
				     IlBoolean flag = IlTrue);

    IlvGraphic*		getSliceGraphic(IlUInt sliceIndex) const;

    void		setSliceGraphic(IlUInt sliceIndex,
					IlvGraphic* graphic);

    const char*		getSliceLegendText(IlUInt sliceIndex) const;

    virtual void	setSliceLegendText(IlUInt sliceIndex,
					   const char* legendText); 

    const IlvDoublePoint& getOffset() const { return _offset; }

    inline void		getOffset(IlDouble& theta, IlvPos& rho) const 
			{
			    theta = _offset.x();
			    rho = (IlvPos)_offset.y();
			}
    inline void		getOffset(IlvDoublePoint& offset) const
			{
			    offset = _offset;
			}

    inline void		setOffset(IlDouble theta, IlvPos rho) 
			{
			    setOffset(IlvDoublePoint(theta, rho));
			}

    inline void		setOffset(const IlvDoublePoint& offset)
			{
			    _offset = offset;
			}

    inline
    IlvPieChartDataSet* getPieDataSet() const 
			{
			    return (IlvPieChartDataSet*) getDataSet();
			}

    virtual IlBoolean	getSliceGeometry(IlUInt sliceIndex,
					 IlvRect& sliceRect,
					 IlDouble& startAngle,
					 IlDouble& range,
					 const IlvTransformer* t = 0) const;

    virtual void	getSliceGraphicPosition(IlUInt sliceIndex,
						const IlvRect& sliceRect,
						IlDouble startAngle,
						IlDouble range,
						IlvPoint& position,
						const IlvTransformer* t
						= 0) const;

    virtual IlBoolean	sliceBBox(IlUInt sliceIndex,
				  IlvRect& bbox,
				  const IlvTransformer* t = 0) const;

    virtual IlBoolean	sliceContains(IlUInt sliceIndex,
				      const IlvPoint& viewPoint,
				      const IlvTransformer* t = 0) const;

    IlUInt		whichSlice(const IlvPoint& viewPoint,
				   const IlvTransformer* t = 0) const;

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    virtual void	setLegendItems(IlvChartLegend* legend) const;

    virtual void	setOverwrite(IlBoolean o);
    virtual void	setMode(IlvDrawMode mode);

    virtual void	getClipArea(IlvRect& area,
				    const IlvTransformer* t) const;

    DeclareChartDisplayerTypeInfo(IlvPieChartDisplayer);

protected:
    IlDouble		_radius;
    IlDouble		_startingAngle;
    IlDouble		_range;
    IlvDim		_tearOffDelta;
    IlvPointInfoCollection* _sliceInfos;
    IlvDoublePoint	_offset;

    // Internal methods

    virtual void	updateVirtualDataSets();

    virtual
    IlvPieSliceInfo*	createSliceInfo() const;

    virtual void	drawPoints(IlvChartDisplayerPoints* displayerPoints, 
				   IlvPort* dst,
				   const IlvTransformer* t = 0,
				   const IlvRegion* clip = 0) const;

    virtual void	boundingBoxOfPoints(IlvChartDisplayerPoints* displayerPoints,
					    IlvRect& bbox,
					    IlBoolean takeInfoIntoAccount
					    = IlTrue,
					    const IlvTransformer* t = 0) const;

    virtual
    IlvDoublePoint* selectDataPointsForPoint(IlUInt dataPointIndex,
					     IlUInt& count,
					     IlUInt*& dataPointIndexes) const;

    virtual 
    IlvDoublePoint* selectDataPointsForRange(const IlvCoordInterval& abscissaRange,
					     IlUInt& pointCount,
					     IlUInt*& dataPointIndexes,
					     const IlvTransformer* t = 0,
					     const IlvRect* clip = 0) const;

    virtual void computeItem(const IlvChartDisplayerPoints* displayerPoints,
			     IlUInt pointIndex,
			     IlUInt& usedPointsCount,
			     IlvPoint* points,
			     const IlvTransformer* t = 0) const;

    virtual
    IlUInt getItemPointsCount(const IlvChartDisplayerPoints* displayerPoints) const;

    virtual void drawItem(const IlvChartDisplayerPoints* displayerPoints,
			  IlUInt pointIndex,
			  IlUInt pointCount,
			  IlvPoint* points,
			  IlvPalette* itemPalette,
			  IlvPort* dst,
			  const IlvTransformer* t = 0,
			  const IlvRegion* clip = 0) const;

    virtual
    void boundingBoxOfItem(const IlvChartDisplayerPoints* displayerPoints,
			   IlUInt pointIndex,
			   IlUInt pointCount,
			   IlvPoint* points,
			   IlvRect& bbox,
			   IlBoolean takeInfoIntoAccount = IlTrue,
			   const IlvTransformer* t = 0) const;

    // Not documented.
    void		getPieRect(IlvRect& pieRect,
				   const IlvTransformer* t = 0) const;

    void		updatePolarProjector();

private:
    void		getSliceGeometryFromPts(IlUInt sliceIndex,
						IlvPoint* points,
						IlvRect& sliceRect,
						IlDouble& startAngle,
						IlDouble& range,
						const IlvTransformer* t
						= 0) const;
};

ILVCHTMODULEINIT(pie);

#endif /* !__Ilv_Charts_Pie_H */
