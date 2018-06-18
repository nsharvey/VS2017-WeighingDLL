// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/legend.h
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
// Declaration of the classes that define a legend for a chart.
// Contains:
//  - IlvChartLegend: the class that allows you to define a legend that can be
//    added to a given chart.
//  - IlvChartLegendItem: the class that allows you to define an item of the
//    chart legend.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Legend_H
#define __Ilv_Charts_Legend_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if !defined(__Ilv_Graphics_Rectangl_H)
#include <ilviews/graphics/rectangl.h>
#endif

#if !defined(__Ilv_Graphics_Label_H)
#include <ilviews/graphics/label.h>
#endif

#if !defined(__Ilv_Graphics_Shadrect_H)
#include <ilviews/graphics/shadrect.h>
#endif

#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif

#if !defined(__Ilv_Charts_Common_H)
#include <ilviews/charts/common.h>
#endif

class ILVCHTEXPORTED IlvChartGraphic;
class ILVCHTEXPORTED IlvAbstractChartDisplayer;
class ILVCHTEXPORTED IlvChartLegendItem;

// --------------------------------------------------------------------------
// Class IlvChartLegend
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartLegend : public IlvShadowRectangle
{
public:

    IlvChartLegend(IlvDisplay*    display,
		   const IlvRect& bbox,
		   IlUShort       boxWidth     = 20,
		   IlUShort       boxHeight    = 10,
		   IlvPalette*    itemPalette  = 0,
		   IlBoolean      showFrame    = IlTrue,
		   IlUShort       labelSpacing = 4,
		   IlUShort       itemSpacing  = 4);

    ~IlvChartLegend();

    //== Accessors ====================

    inline IlBoolean	isShowingFrame() const { return _showFrame;}

    inline void		showFrame(IlBoolean showFrame)
			{
			    _showFrame = showFrame;
			}

    inline IlBoolean	isTransparent() const { return _transparent;}

    inline void		setTransparent(IlBoolean transparent)
			{
			    _transparent = transparent;
			}

    inline IlBoolean	isAutoRecomputing() const { return _autoRecompute; }

    inline void		setAutoRecompute(IlBoolean autoRecompute)
			{
			    _autoRecompute = autoRecompute;
			}

    inline IlBoolean	isAutoFitting() const {return _autoFitToContents;}

    inline void		setAutoFit(IlBoolean autoFitToContents)
			{
			    _autoFitToContents=autoFitToContents;
			}

    inline IlvPalette*	getItemPalette() const { return _itemPalette; }

    void		setItemPalette(IlvPalette* pal);

    inline IlUShort	getLabelSpacing() const { return _labelSpacing; }

    void		setLabelSpacing(IlUShort spacing);

    inline IlUShort	getItemSpacing() const {return _itemSpacing;}

    void		setItemSpacing(IlUShort spacing);

    IlUInt		getNumberOfItems() const;

    IlvChartLegendItem*	getLegendItem(IlUInt rank) const;

    IlvChartLegendItem*	getLegendItem(const char* label) const;

    inline IlUShort	getBoxWidth() const
			{
			    return _boxWidth;
			}

    void		setBoxWidth(IlUShort w);

    inline IlUShort	getBoxHeight() const { return _boxHeight; }

    void		setBoxHeight(IlUShort h);


    //== Item management ====================

    IlvChartLegendItem*	addLegendItem(const char* label,
				      const IlvAbstractChartDisplayer* dsp,
				      IlAny clientData = 0,
				      IlUInt rank = IlvLastPositionIndex);

    virtual
    IlvChartLegendItem* createLegendItem(const char* label,
					 const IlvAbstractChartDisplayer* dsp,
					 IlAny clientData = 0) const;

    void		removeLegendItems(const IlvAbstractChartDisplayer* dsp);

    IlBoolean		getLegendItemPosition(IlvChartLegendItem* item,
					      IlUInt& col,
					      IlUInt& row) const;

    void		clearLegendItems(IlBoolean reDraw = IlFalse);


    //== Drawing methods ============

    virtual void	drawFrame(IlvPort*              dst,
				  const IlvTransformer* t    = 0,
				  const IlvRegion*      clip = 0) const;

    virtual void	drawGhost(IlvPort*              dst,
				  const IlvTransformer* t    = 0,
				  const IlvRegion*      clip = 0) const;

    //== IlvShadowRectangle virtual methods ============

    // Not documented at that level of the class hierarchy.
    // See the IlvGraphic class for the documentation.
    virtual void	applyTransform(const IlvTransformer* t);

    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;

    virtual IlBoolean	zoomable() const;

    //== Item modification/organisation methods ============

    virtual void	organizeLegendItems(const IlvTransformer* t=0);

    virtual void	fitToContents(IlvDirection dir = IlvBadPosition);

    //== Value accessors ============
    DeclareGraphicAccessors();

    static IlSymbol*	_autoRecomputeValue;
    static IlSymbol*	_autoFitValue;
    static IlSymbol*	_boxWidthValue;
    static IlSymbol*	_boxHeightValue;
    static IlSymbol*	_labelSpacingValue;
    static IlSymbol*	_itemSpacingValue;
    static IlSymbol*	_showFrameValue;
    static IlSymbol*	_transparentValue;

    inline const IlvChartGraphic*	getChartGraphic() const
					{
					    return _chart;
					}

    // Should be not used directly

    void		setChartGraphic(IlvChartGraphic* chart);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvChartLegend);

protected:

    IlBoolean		_autoRecompute; // autorecompute organisation of items
    IlBoolean		_autoFitToContents;  // Auto fit to the items
    IlUShort		_boxWidth;	     // size of the ite boxes
    IlUShort		_boxHeight;
    IlUShort		_labelSpacing; // spacing between label and legend box
    IlUShort		_itemSpacing;  // spacing between item
    IlvPalette*		_itemPalette;  // label palette

    IlBoolean		_showFrame;
    IlBoolean		_transparent;

    IlUInt		_cols;
    IlUInt		_rows;
    IlList		_items;

    IlvChartGraphic*	_chart;

    void		initIt();
    void		computeItemSizes(IlvDim& maxW,
					 IlvDim& maxH,
					 IlvDim& sumW,
					 IlvDim& sumH,
					 const IlvTransformer* t = 0) const;
};


// --------------------------------------------------------------------------
// Class IlvChartLegendItem
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartLegendItem : public IlvSimpleGraphic
{
public:

    IlvChartLegendItem(const IlvChartLegend*            chartLegend,
		       const char*                      label,
		       const IlvAbstractChartDisplayer* dsp,
		       IlvPalette*                      pal= 0);

    ~IlvChartLegendItem();

    //== Accessors ====================

    const IlvAbstractChartDisplayer*	getDisplayer(IlUInt rank = 0) const;

    IlUInt		getDisplayersCount() const;

    void		setLabelPalette(IlvPalette* pal);

    void		setLabelForeground(IlvColor* color);

    IlvPalette*		getLabelPalette() const;

    const char*		getLabel() const;

    inline IlUShort	getBoxWidth() const
			{
			    return _chartLegend->getBoxWidth();
			}

    inline IlUShort	getBoxHeight() const
			{
			    return _chartLegend->getBoxHeight();
			}

    inline IlvDim	getLabelSpacing() const
			{
			    return _chartLegend->getLabelSpacing();
			}

    //== IlvSimpleGraphic virtual methods ================

    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t    = 0,
			     const IlvRegion*      clip = 0) const;

    // Not documented at that level of the class hierarchy.
    // See the IlvGraphic class for the documentation.
    virtual void	boundingBox(IlvRect&              rect,
				    const IlvTransformer* t = 0) const;

    // Not documented at that level of the class hierarchy.
    // See the IlvGraphic class for the documentation.
    virtual void	applyTransform(const IlvTransformer* t);

    // Not documented at that level of the class hierarchy.
    // See the IlvGraphic class for the documentation.
    virtual void	setOverwrite(IlBoolean flag);

    // Not documented at that level of the class hierarchy.
    // See the IlvGraphic class for the documentation.
    virtual void	setMode(IlvDrawMode mode);

    // Not documented at that level of the class hierarchy.
    // See the IlvGraphic class for the documentation.
    virtual void	apply(IlvApplyObject, IlAny);

    // Not documented at that level of the class hierarchy.
    // See the IlvGraphic class for the documentation.
    virtual void	applyReferences(IlvApplyObject, IlAny);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvChartLegendItem);

protected:
    const IlvChartLegend*		_chartLegend;
    IlvPoint				_position;
    IlvLabel*				_label;
    const IlvAbstractChartDisplayer*	_displayer;

    void		getLabelPosition(IlvPoint&             p,
					 const IlvTransformer* t = 0) const;
};


ILVCHTMODULEINIT(legend);


#endif /* !__Ilv_Charts_Legend_H */

