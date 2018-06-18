// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/bar.h
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
// Declaration of the classes that display bars.
// Contains:
//  - IlvBarChartDisplayer: a subclass of IlvSingleChartDisplayer which
//    represents data with bars.
//  - Ilv3dBarChartDisplayer: a subclass of IlvBarChartDisplayer which
//    represents data with 3D bars.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Bar_H
#define __Ilv_Charts_Bar_H

#if !defined(__Ilv_Charts_Display_H)
#include <ilviews/charts/display.h>
#endif

// --------------------------------------------------------------------------
// Class IlvBarChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvBarChartDisplayer : public IlvSingleChartDisplayer
{
public:

    IlvBarChartDisplayer(IlvDim width = IlvChartDisplayerWidth,
			 IlvPalette* palette = 0);

    //== Accessors ===============

    virtual IlvDim	getWidth() const;

    virtual void	setWidth(IlvDim width);

    inline IlvDim	getSize() const { return _size; }

    void		setWidthPercent(IlUInt width);

    IlUInt		getWidthPercent() const;

    void		setStrokeThreshold(IlUInt threshold);

    IlUInt		getStrokeThreshold() const;


    //== Displayer properties ===============

    virtual IlBoolean	isFilled() const;

    virtual IlvDim	getSizeAlongBase() const;

    virtual void	getClipArea(IlvRect& area,
				    const IlvTransformer* t) const;

    DeclareChartDisplayerTypeInfo(IlvBarChartDisplayer);

protected:
    IlvDim		_size;
    IlUInt		_widthPercent;
    IlBoolean		_zoomableBars;
    IlUInt		_strokeThreshold;

    virtual void	boundingBoxOfPoints(IlvChartDisplayerPoints* dspPts,
					    IlvRect& bbox,
					    IlBoolean takeInfoIntoAccount,
					    const IlvTransformer* t = 0) const;

    virtual void	computeItem(const IlvChartDisplayerPoints* dspPts,
				    IlUInt pointIndex,
				    IlUInt& usedPointsCount,
				    IlvPoint* points,
				    const IlvTransformer* t = 0) const;

    virtual IlUInt
	getItemPointsCount(const IlvChartDisplayerPoints* dspPts) const;

    virtual void	drawItem(const IlvChartDisplayerPoints* dspPts,
				 IlUInt pointIndex,
				 IlUInt pointCount,
				 IlvPoint* points,
				 IlvPalette* itemPalette,
				 IlvPort* dst,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;

    virtual IlBoolean	isDrawingStroke(const IlvChartDisplayerPoints*) const;
};

// --------------------------------------------------------------------------
// Class Ilv3dBarChartDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED Ilv3dBarChartDisplayer : public IlvBarChartDisplayer
{
public:

    Ilv3dBarChartDisplayer(IlvDim width = IlvChartDisplayerWidth,
			   IlvDim depth = IlvChartDisplayerDepth,
			   IlvPalette* palette = 0);

    virtual ~Ilv3dBarChartDisplayer();

    //== Accessors ===============

    virtual IlvDim	getWidth() const;

    virtual void	setWidth(IlvDim width);

    inline IlvDim	getDepth() const { return _depth; }

    inline void		setDepth(IlvDim depth) { _depth = depth; }

    virtual void	setPalette(IlvPalette* palette, IlUInt index = 0);

    // Not documented at that level of the class hierarchy.
    // See the IlvAbstractChartDisplayer class for the documentation.
    virtual void	setOverwrite(IlBoolean o);

    // Not documented at that level of the class hierarchy.
    // See the IlvAbstractChartDisplayer class for the documentation.
    virtual void	setMode(IlvDrawMode mode);

    inline IlBoolean	isDrawingTopFace() const { return _drawTopFace; }

    inline void		drawTopFace(IlBoolean b) {_drawTopFace = b;}

    virtual void	getClipArea(IlvRect& area,
				    const IlvTransformer* t) const;

    DeclareChartDisplayerTypeInfo(Ilv3dBarChartDisplayer);

protected:
    IlvDim		_depth;
    IlvPalette*		_topShadow;
    IlvPalette*		_bottomShadow;
    IlBoolean		_drawTopFace;

    // Internal methods

    // See IlvSingleChartDisplayer for the documentation.
    virtual void	drawPoints(IlvChartDisplayerPoints* dspPts,
				   IlvPort* dst,
				   const IlvTransformer* t = 0,
				   const IlvRegion* clip = 0) const;

    virtual void	boundingBoxOfPoints(IlvChartDisplayerPoints* dspPts,
					    IlvRect& bbox,
					    IlBoolean takeInfoIntoAccount,
					    const IlvTransformer* t = 0) const;

    virtual void	computePalettes();

    virtual void	computeTopBottomShadows(IlvPalette* currentPalette,
						IlvPalette*& topShadow,
						IlvPalette*& bottomShadow) const;

    virtual void	computeItem(const IlvChartDisplayerPoints* dspPts,
				    IlUInt pointIndex,
				    IlUInt& usedPointsCount,
				    IlvPoint* points,
				    const IlvTransformer* t = 0) const;

    virtual IlUInt
	getItemPointsCount(const IlvChartDisplayerPoints* dspPts) const;

    virtual void	drawItem(const IlvChartDisplayerPoints* dspPts,
				 IlUInt pointIndex,
				 IlUInt pointCount,
				 IlvPoint* points,
				 IlvPalette* itemPalette,
				 IlvPort* dst,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;
};

ILVCHTMODULEINIT(bar);

#endif /* !__Ilv_Charts_Bar_H */
