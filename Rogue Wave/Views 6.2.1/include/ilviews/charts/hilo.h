// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/hilo.h
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
// Declaration of classes to draw high-low charts
// Contains:
//  - IlvHiLoChartDisplayer.
//  - IlvHiLoBarChartDisplayer.
//  - IlvHiLoOpenCloseChartDisplayer.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Hilo_H
#define __Ilv_Charts_Hilo_H

#if !defined(__Ilv_Charts_Display_H)
#include <ilviews/charts/display.h>
#endif

// --------------------------------------------------------------------------
// Class IlvHiLoChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvHiLoChartDisplayer : public IlvSingleChartDisplayer
{
public:
    IlvHiLoChartDisplayer(IlvDim	width = IlvChartDisplayerWidth,
			  IlvPalette*	risePalette = 0,
			  IlvPalette*	fallPalette = 0);

    virtual ~IlvHiLoChartDisplayer();

    //== Displayer properties =======================
    virtual IlBoolean	isFilled() const;

    virtual IlBoolean	isContinuous() const;

    virtual IlvDim	getSizeAlongBase() const;

    virtual IlBoolean	useVirtualDataSets() const;

    virtual IlBoolean	isViewable() const;

    inline IlvDim	getWidth() const { return 2*_size; }

    void		setWidth(IlvDim width);

    void		setWidthPercent(IlUInt width);

    IlUInt		getWidthPercent() const;

    inline IlvDim	getSize() const { return _size; }

    // Not documented at that level of the class hierarchy.
    // See the IlvAbstractChartDisplayer class for the documentation.
    virtual void	setOverwrite(IlBoolean o);

    // Not documented at that level of the class hierarchy.
    // See the IlvAbstractChartDisplayer class for the documentation.
    virtual void	setMode(IlvDrawMode mode);

    inline IlvPalette*	getRisePalette() const { return _palette; }

    inline void		setRisePalette(IlvPalette* pal) { setPalette(pal); }

    IlvPalette*		getFallPalette() const;

    void		setFallPalette(IlvPalette* pal);

    virtual
    IlvChartDataPointInfo* getPointInfo(IlUInt dataPointIndex,
					const IlvChartDataSet* dataSet
					= 0) const;

    //== Legend =======================
    virtual
    const char*		getLegendText(IlUInt index = 0) const;

    virtual void	getClipArea(IlvRect& area,
				    const IlvTransformer* t) const;


    DeclareChartDisplayerTypeInfo(IlvHiLoChartDisplayer);

protected:
    IlvDim		_size;
    IlvPalette*		_fallPalette;
    IlUInt		_widthPercent;
    IlBoolean		_zoomableBars;

    virtual void	updateVirtualDataSets();

    // Internal methods
    virtual void	drawPoints(IlvChartDisplayerPoints* displayerPoints,
				   IlvPort* dst,
				   const IlvTransformer* t = 0,
				   const IlvRegion* clip = 0) const;

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    virtual
    IlvDoublePoint*	selectDataPointsForPoint(IlUInt dataPointIndex,
						 IlUInt& count,
						 IlUInt*& dataPointIndexes) const;

    virtual void	boundingBoxOfPoints(IlvChartDisplayerPoints*
					    displayerPoints,
					    IlvRect& bbox,
					    IlBoolean takeInfoIntoAccount,
					    const IlvTransformer* t = 0) const;

    virtual void	computeItem(const IlvChartDisplayerPoints*
				    displayerPoints,
				    IlUInt pointIndex,
				    IlUInt& usedPointsCount,
				    IlvPoint* points,
				    const IlvTransformer* t = 0) const;

    virtual IlUInt	getItemPointsCount(const IlvChartDisplayerPoints*
					   displayerPoints) const;

    virtual void	drawItem(const IlvChartDisplayerPoints*
				 displayerPoints,
				 IlUInt pointIndex,
				 IlUInt pointCount,
				 IlvPoint* points,
				 IlvPalette* itemPalette,
				 IlvPort* dst,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;
};


// --------------------------------------------------------------------------
// Class IlvHiLoBarChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvHiLoBarChartDisplayer : public IlvHiLoChartDisplayer
{
public:
    IlvHiLoBarChartDisplayer(IlvDim width = IlvChartDisplayerWidth,
			     IlvPalette* risePalette = 0,
			     IlvPalette* fallPalette = 0);

    DeclareChartDisplayerTypeInfo(IlvHiLoBarChartDisplayer);

protected:

    virtual void	computeItem(const IlvChartDisplayerPoints*
				    displayerPoints,
				    IlUInt pointIndex,
				    IlUInt& usedPointsCount,
				    IlvPoint* points,
				    const IlvTransformer* t = 0) const;

    virtual IlUInt	getItemPointsCount(const IlvChartDisplayerPoints*
					   displayerPoints) const;


    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    virtual void	drawItem(const IlvChartDisplayerPoints*
				 displayerPoints,
				 IlUInt pointIndex,
				 IlUInt pointCount,
				 IlvPoint* points,
				 IlvPalette* itemPalette,
				 IlvPort* dst,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;
};

// --------------------------------------------------------------------------
// Class IlvHiLoOpenCloseChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvHiLoOpenCloseChartDisplayer
    : public IlvCompositeChartDisplayer
{
public:

    // Constructors
    IlvHiLoOpenCloseChartDisplayer(IlvDim width = IlvChartDisplayerWidth,
				   IlvPalette* hiLoRisePal = 0,
				   IlvPalette* openCloseRisePal = 0,
				   IlvPalette* hiLoFallPal = 0,
				   IlvPalette* openCloseFallPal = 0,
				   IlvChartDisplayerFactory* factory = 0);


    inline
    IlvHiLoChartDisplayer*	getHiLoDisplayer() const
    {
	return ILVDYNAMICCAST(IlvHiLoChartDisplayer*,getDisplayer(0));
    }

    inline
    IlvHiLoChartDisplayer*	getOpenCloseDisplayer() const
    {
	return ILVDYNAMICCAST(IlvHiLoChartDisplayer*,getDisplayer(1));
    }

    inline void		setHiLoRisePalette(IlvPalette* pal)
			{
			    setPalette(pal, 0);
			}

    inline void		setOpenCloseRisePalette(IlvPalette* pal)
			{
			    setPalette(pal,1);
			}

    inline void		setHiLoFallPalette(IlvPalette* pal)
			{
			    getHiLoDisplayer()->setFallPalette(pal);
			}

    inline void		setOpenCloseFallPalette(IlvPalette* pal)
			{
			    getOpenCloseDisplayer()->setFallPalette(pal);
			}

    void		setWidthPercent(IlUInt width);

    IlUInt		getWidthPercent() const;

    virtual IlBoolean	useVirtualDataSets() const;

    DeclareChartDisplayerTypeInfoRO(IlvHiLoOpenCloseChartDisplayer);

protected:

    // API

    virtual
    IlvAbstractChartDisplayer* createDisplayer(IlUInt index,
					       IlvPalette* palette = 0);

    virtual void	updateDisplayers();

};

ILVCHTMODULEINIT(hilo);

#endif /* !__Ilv_Charts_Hilo_H */
