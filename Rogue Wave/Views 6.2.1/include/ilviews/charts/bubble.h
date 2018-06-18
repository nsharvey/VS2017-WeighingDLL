// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/bubble.h
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
// Declaration of classes allowing to define a bubble displayer.
// Contains:
//  - IlvBubbleChartDisplayer: a subclass of IlvSingleChartDisplayer which
//    represents data with bubbles.
//  - IlvBubbleDSLst: a subclass of IlvChartDataSetListener defining a
//    listener to be set on the data set represented by the bubble displayer.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Bubble_H
#define __Ilv_Charts_Bubble_H

#if !defined(__Ilv_Charts_Display_H)
#include <ilviews/charts/display.h>
#endif

#if !defined(__Ilv_Charts_Data_H)
#include <ilviews/charts/data.h>
#endif

// --------------------------------------------------------------------------
// Class IlvBubbleChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvBubbleChartDisplayer : public IlvSingleChartDisplayer
{
public:
    enum BubbleSizeMode {
	MinMax = 0x0001,
	Scaling = 0x0002
    };

    IlvBubbleChartDisplayer(IlvGraphic* graphic,
			    IlvDim maxSize = 40,
			    IlvDim minSize = 0,
			    IlvPalette* palette = 0);

    IlvBubbleChartDisplayer(IlvGraphic* graphic,
			    IlDouble scaling,
			    IlvPalette* palette = 0);

    virtual ~IlvBubbleChartDisplayer();

    // Accessors
    inline
    BubbleSizeMode	getBubbleSizeMode() const { return _bubbleSizeMode; }
    inline void		setBubbleSizeMode(BubbleSizeMode mode)
			{
			    _bubbleSizeMode = mode;
			}

    inline IlvDim	getMaxSize() const { return _maxSize; }

    inline void		setMaxSize(IlvDim maxSize) { _maxSize = maxSize; }

    inline IlvDim	getMinSize() const { return _minSize; }

    inline void		setMinSize(IlvDim minSize) { _minSize = minSize; }

    inline IlDouble	getScaling() const { return _scaling; }

    inline void		setScaling(IlDouble scaling) { _scaling = scaling; }

    inline IlvGraphic*	getGraphicModel() const { return _graphicModel; }

    IlvGraphic*		setGraphicModel(IlvGraphic* graphic);

    inline
    IlvChartDataSet*	getSizeDataSet() const { return getDataSet(1); }

    IlvDim		getGraphicSize(IlUInt pointIndex) const;

    // Displayer properties
    virtual IlvDim	getSizeAlongBase() const;

    virtual IlBoolean	isViewable() const;

    virtual void	getClipArea(IlvRect& area,
				    const IlvTransformer* t) const;

    virtual void	drawPoints(IlvChartDisplayerPoints* displayerPoints,
				   IlvPort* dst,
				   const IlvTransformer* t = 0,
				   const IlvRegion* clip = 0) const;

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    DeclareChartDisplayerTypeInfo(IlvBubbleChartDisplayer);

protected:
    BubbleSizeMode	_bubbleSizeMode;
    IlvDim		_maxSize;
    IlvDim		_minSize;
    IlDouble		_scaling;
    IlvGraphic*		_graphicModel;

    virtual void	update();

    virtual void	boundingBoxOfPoints(IlvChartDisplayerPoints* displayerPoints,
					    IlvRect& bbox,
					    IlBoolean takeInfoIntoAccount,
					    const IlvTransformer* t = 0) const;

    virtual void	computeItem(const IlvChartDisplayerPoints* displayerPoints,
				    IlUInt pointIndex,
				    IlUInt& usedPointsCount,
				    IlvPoint* points,
				    const IlvTransformer* t = 0) const;

    virtual IlUInt 
    getItemPointsCount(const IlvChartDisplayerPoints* displayerPoints) const;

    virtual void	drawItem(const IlvChartDisplayerPoints* displayerPoints,
				 IlUInt pointIndex,
				 IlUInt pointCount,
				 IlvPoint* points,
				 IlvPalette* itemPalette,
				 IlvPort* dst,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;

    virtual void	boundingBoxOfItem(const IlvChartDisplayerPoints* displayerPoints,
					  IlUInt pointIndex,
					  IlUInt pointCount,
					  IlvPoint* points,
					  IlvRect& bbox,
					  IlBoolean takeInfoIntoAccount = IlTrue,
					  const IlvTransformer* t = 0)
 const;

};

// --------------------------------------------------------------------------
// Class IlvBubbleDSLst
// --------------------------------------------------------------------------
class IlvBubbleDSLst : public IlvChartDataSetListener
{
public:
    IlvBubbleDSLst(IlvBubbleChartDisplayer* bubbleDisp,
		   const IlvCoordInterval& range);

    virtual void	dataPointRemoved(const IlvChartDataSet* dataSet,
					 IlUInt pointIndex);


    virtual void	dataPointChanged(const IlvChartDataSet* dataSet,
					 IlUInt pointIndex,
					 IlBoolean beforeChange);

    
    virtual void	dataPointAdded(const IlvChartDataSet* dataSet,
				       IlUInt position);

    virtual void	endBatch(const IlvChartDataSet* dataSet);

protected:
    IlvCoordInterval		_range;
    IlvBubbleChartDisplayer*	_bubbleDisp;

    void		checkRange(const IlvCoordInterval& range);
};


ILVCHTMODULEINIT(bubble);

#endif /* !__Ilv_Charts_Bubble_H */
