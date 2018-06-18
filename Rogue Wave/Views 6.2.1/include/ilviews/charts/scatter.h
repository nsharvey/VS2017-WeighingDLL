// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/scatter.h
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
// Declaration of the IlvScatterChartDisplayer class which represents data
//   with markers.
// Declaration of the IlvMarkedPolylineChartDisplayer class which
//   represents data with markers and/or lines.
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Scatter_H
#define __Ilv_Charts_Scatter_H

#if !defined(__Ilv_Charts_Display_H)
#include <ilviews/charts/display.h>
#endif

#if !defined(__Ilv_Charts_Polyline_H)
#include <ilviews/charts/polyline.h>
#endif

// --------------------------------------------------------------------------
// Class IlvScatterChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvScatterChartDisplayer
    : public IlvSingleChartDisplayer
{
public:
    IlvScatterChartDisplayer(IlvMarkerType marker = IlvMarkerFilledSquare,
			     IlvDim markerSize = IlvDefaultMarkerSize,
			     IlvPalette* palette = 0);

    //== Accessors ====================
    inline IlvDim	getMarkerSize() const { return _markerSize; }

    inline void		setMarkerSize(IlvDim size) { _markerSize = size; }

    inline
    IlvMarkerType	getMarker() const { return _marker; }

    inline void		setMarker(IlvMarkerType marker) { _marker = marker; }

    virtual IlvDim	getSizeAlongBase() const;

    virtual void	drawLegendItem(IlvPort* dst,
				       const IlvRect& legendArea,
				       IlvPalette* itemPal,
				       const IlvRegion* clip,
				       IlAny clientData = 0) const;

    virtual void	getClipArea(IlvRect& area,
				    const IlvTransformer* t) const;

    DeclareChartDisplayerTypeInfo(IlvScatterChartDisplayer);

protected:
    IlvMarkerType	_marker;
    IlvDim		_markerSize;

    //== Internal methods ====================
    virtual void boundingBoxOfPoints(IlvChartDisplayerPoints* displayerPoints,
				     IlvRect& bbox,
				     IlBoolean takeInfoIntoAccount = IlTrue,
				     const IlvTransformer* t = 0) const;

    virtual void computeItem(const IlvChartDisplayerPoints* displayerPoints,
			     IlUInt pointIndex,
			     IlUInt& usedPoints,
			     IlvPoint* points,
			     const IlvTransformer* t = 0) const;

    virtual IlUInt getItemPointsCount(const IlvChartDisplayerPoints* displayerPoints) const;

    virtual void drawItem(const IlvChartDisplayerPoints* displayerPoints,
			  IlUInt pointIndex,
			  IlUInt pointCount,
			  IlvPoint* points,
			  IlvPalette* itemPalette,
			  IlvPort* dst,
			  const IlvTransformer* t,
			  const IlvRegion* clip = 0) const;

    virtual void boundingBoxOfItem(const IlvChartDisplayerPoints* displayerPoints,
				   IlUInt pointIndex,
				   IlUInt pointCount,
				   IlvPoint* points,
				   IlvRect& bbox,
				   IlBoolean takeInfoIntoAccount = IlTrue,
				   const IlvTransformer* t = 0) const;

};

// --------------------------------------------------------------------------
// Class IlvMarkedPolylineChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvMarkedPolylineChartDisplayer
    : public IlvCompositeChartDisplayer
{
public:

    IlvMarkedPolylineChartDisplayer(IlvMarkerType marker = IlvMarkerFilledSquare,
				    IlvDim markerSize = IlvDefaultMarkerSize,
				    IlvPalette* markerPalette = 0,
				    IlvPalette* linePalette = 0);

    virtual ~IlvMarkedPolylineChartDisplayer();

    //== Markers and line accessors ================

    inline
    IlvPolylineChartDisplayer* getLineDisplayer() const
			{
			    return ILVDYNAMICCAST(IlvPolylineChartDisplayer*,
						  getDisplayer(0));
			}

    inline
    IlvScatterChartDisplayer* getMarkerDisplayer() const
			{
			    return ILVDYNAMICCAST(IlvScatterChartDisplayer*,
						  getDisplayer(1));
			}

    inline IlBoolean	isMarkerVisible() const { return _markerVisible; }

    inline void		setMarkerVisible(IlBoolean visible)
			{
			    _markerVisible = visible;
			    getDisplayer(1)->setVisible(visible);
			}

    inline IlvPalette*	getMarkerPalette() const { return getPalette(1); }

    inline void		setMarkerPalette(IlvPalette* pal)
			{
			    setPalette(pal, 1);
			}

    inline IlvColor*	getMarkerForeground() const
			{
			    return getForeground(1);
			}

    inline void		setMarkerForeground(IlvColor* color)
			{
			    setForeground(color, 1);
			}

    inline IlvColor*	getMarkerBackground() const
			{
			    return getBackground(1);
			}

    inline void		setMarkerBackground(IlvColor* color)
			{
			    setBackground(color, 1);
			}

    inline IlBoolean	isLineVisible() const { return _lineVisible; }

    inline void		setLineVisible(IlBoolean visible)
			{
			    _lineVisible = visible;
			    getDisplayer(0)->setVisible(visible);
			}

    inline IlvPalette*	getLinePalette() const { return getPalette(0); }

    inline void		setLinePalette(IlvPalette* pal)
			{
			    setPalette(pal, 0);
			}

    inline IlvColor*	getLineForeground() const { return getForeground(0); }

    inline void		setLineForeground(IlvColor* color)
			{
			    setForeground(color, 0);
			}

    inline IlvColor*	getLineBackground() const { return getBackground(0); }

    inline void		setLineBackground(IlvColor* color)
			{
			    setBackground(color, 0);
			}

    virtual void	setLegendItems(IlvChartLegend* legend) const;

    DeclareChartDisplayerTypeInfo(IlvMarkedPolylineChartDisplayer);

protected:
    IlBoolean		_markerVisible;
    IlBoolean		_lineVisible;

    virtual
    IlvAbstractChartDisplayer* createDisplayer(IlUInt index,
					       IlvPalette* palette = 0);

    virtual void	updateDisplayers();
};

ILVCHTMODULEINIT(scatter);

#endif /* !__Ilv_Charts_Scatter_H */
