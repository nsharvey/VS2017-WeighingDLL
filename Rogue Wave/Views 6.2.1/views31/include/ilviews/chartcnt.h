// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/chartcnt.h
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
// Definition of the ChartContainer class
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Chartcnt_H
#define __Ilv31_Chartcnt_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Graphics_Scale_H)
#include <ilviews/graphics/scale.h>
#endif
#if !defined(__Ilv_Graphics_Set_H)
#include <ilviews/graphics/set.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Graphics_Attach_H)
#include <ilviews/graphics/attach.h>
#endif

class IlvAbstractChart;
class IlvChart;
class IlvChartData;

#define IlvChartContainerClipToChartsRectFlag 1

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvChartsHandle
: public IlvSimpleGraphic
{
public:
    IlvChartsHandle(IlvDisplay* display, const IlvRect& handleRect)
    : IlvSimpleGraphic(display, 0),
      _handleRect(handleRect)
    {}
    // ____________________________________________________________
    virtual void draw(IlvPort*, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    virtual void boundingBox(IlvRect&,
			     const IlvTransformer* t = 0) const;
    virtual void applyTransform(const IlvTransformer*);
    DeclareTypeInfo();
protected:
    IlvRect _handleRect;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvChartContainer
: public IlvContainer
{
public:
    IlvChartContainer(IlvAbstractView* parent,
		      const IlvRect&   size,
		      const IlvRect&   chartsRect,
		      const IlvPoint&  legendPosition,
		      IlvPosition      legendAlignment = IlvVertical,
		      IlvPosition      scalesMask = IlvBottomLeft,
		      IlBoolean        useacc  = IlTrue,
		      IlBoolean        visible = IlTrue);
    IlvChartContainer(IlvDisplay*     d,
		      IlvSystemView   parent,
		      const IlvRect&  size,
		      const IlvRect&  chartsRect,
		      const IlvPoint& legendPosition,
		      IlvPosition     legendAlignment = IlvVertical,
		      IlvPosition     scalesMask = IlvBottomLeft,
		      IlBoolean       useacc  = IlTrue,
		      IlBoolean       visible = IlTrue);
    IlvChartContainer(IlvDisplay* d,  IlvSystemView,
		      const IlvRect&  chartsRect,
		      const IlvPoint& legendPosition,
		      IlvPosition     legendAlignment = IlvVertical,
		      IlvPosition     scalesMask = IlvBottomLeft,
		      IlBoolean       useacc = IlTrue);
    IlvChartContainer(IlvDisplay*     d,
		      const char*     name,
		      const char*     title,
		      const IlvRect&  dims,
		      const IlvRect&  chartsRect,
		      const IlvPoint& legendPosition,
		      IlvPosition     legendAlignment = IlvVertical,
		      IlvPosition     scalesMask = IlvBottomLeft,
		      IlBoolean       useacc  = IlTrue,
		      IlBoolean       visible = IlTrue);
    IlvChartContainer(IlvDisplay*     d,
		      const char*     name,
		      const char*     title,
		      const IlvRect&  dims,
		      IlUInt          properties,
		      const IlvRect&  chartsRect,
		      const IlvPoint& legendPosition,
		      IlvPosition     legendAlignment = IlvVertical,
		      IlvPosition     scalesMask = IlvBottomLeft,
		      IlBoolean       useacc  = IlTrue,
		      IlBoolean       visible = IlTrue,
		      IlvSystemView   transientFor = 0);
    virtual ~IlvChartContainer();
    // _______________________________________________
    static IlSymbol* _chartProperty;
    static IlSymbol* _legendProperty;
    IlSymbol* chartProperty() const { return _chartProperty; }
    IlSymbol* legendProperty() const { return _legendProperty; }
    virtual void handleResize(IlvRect& rect);
    virtual void applyResize(IlFloat sx, IlFloat sy,
			     IlBoolean redraw = IlTrue);
    IlvRectangularScale* getScale(IlvPosition pos) const {
	int i = positionToIndex(pos);
	return (i == -1) ? 0 : _scale[i];
    }
    void setScale(IlvPosition pos, IlvRectangularScale* scale);
    void setScaleFormat(IlvPosition mask, const char* format);
    const char* const* getScaleFormat() const {
	return (const char* const*)_format;
    }
    int positionToIndex(IlvPosition pos) const;
    IlvPosition indexToPosition(int index) const;
    virtual void updateScaleLabels(IlvPosition mask) const;
    virtual void updateScale(IlvPosition mask);
    virtual void drawGhost(const IlvRect&) const;
    virtual void draw (const IlvRegion* clip = 0);
    virtual void draw(IlvPort* dst,
		      const IlvTransformer* t = 0,
                      const IlvRegion* clip = 0);
    void reDrawCharts();
    IlvGraphic* getChartsHandle() const { return _handle; }
    virtual void addChart(IlvAbstractChart*, IlBoolean redraw = IlFalse);
    virtual void insertChart(IlvAbstractChart*, IlBoolean redraw = IlFalse);
    virtual IlBoolean removeChart(IlvAbstractChart*,
				  IlBoolean redraw = IlFalse);
    void setChartData(IlvChart*, IlvChartData*,
		      IlBoolean redraw = IlTrue);
    void manageChart(IlvAbstractChart*, IlInt position = 0);
    void popChart(IlvAbstractChart*, IlBoolean redraw = IlFalse);
    void pushChart(IlvAbstractChart*, IlBoolean redraw = IlFalse);
    virtual void swap(IlvGraphic*,IlvGraphic*);
    IlUInt getNumCharts()  const { return _charts.getLength();}
    IlvAbstractChart* getChart(IlUInt index) const;
    IlvAbstractChart* const* getCharts(IlUInt& count) const;
    IlInt getChartIndex(IlvAbstractChart*) const;
    virtual void updateChart(IlvAbstractChart*);
    virtual void adjustChart(IlvAbstractChart*) const;
    void adjustCharts() const;
    virtual void moveCharts(IlvPos x, IlvPos y, IlBoolean redraw = IlTrue);
    virtual void reshapeCharts(const IlvRect& size, IlBoolean redraw = IlTrue);
    virtual void zoomCharts(IlvDirection, IlFloat fromX, IlFloat toX,
			    IlFloat fromY, IlFloat toY, IlBoolean r = IlTrue);
    void fitChartsToContents(IlvDirection d=(IlvDirection)
			     (IlvHorizontal|IlvVertical), IlBoolean r = IlTrue);
    virtual void translateCharts(IlvDirection, IlFloat dx,
				 IlFloat dy, IlBoolean redraw = IlTrue);
    void chartsBBox(IlvRect& bbox, const IlvTransformer* t = 0);
    void fixOrigin(IlvPosition mask, IlvPos o, IlBoolean adjust = IlTrue);
    void attachOrigin(IlvPosition mask, IlFloat o);
    void getOrigins(IlFloat* mo, IlvPos* fo) const;
    void getOriginAttachments(IlvGraphicAttachment* oAttach) const;
    IlvGraphic* getLegend() const { return _legend; }
    void setLegend(IlvGraphic* legend);
    void getLegendPosition(IlvPoint& p) const { p = _legendPosition; }
    IlvPosition getLegendAlignment() const { return _legendAlignment; }
    IlvDeltaPos getLegendSpacing() const { return _legendSpacing; }
    void setLegendSpacing(IlvDeltaPos spacing) { _legendSpacing = spacing; }
    virtual IlAny getLegendItem(const IlvAbstractChart*) const;
    virtual void addToLegend(IlvAbstractChart*, const char* label,
			     IlvDeltaPos labelspacing = IlvDefaultSetSpacing,
			     IlvDim indicatorW=10, IlvDim indicatorH=10,
			     IlvGraphic* indctr=0, IlBoolean redraw = IlFalse);
    virtual void addToLegend(IlvAbstractChart*, IlAny item,
			     IlBoolean redraw = IlFalse);
    virtual IlBoolean removeFromLegend(IlvAbstractChart*,
				       IlBoolean redraw = IlFalse);
    virtual void computePoints(const IlvRect&, IlFloat& xmin, IlFloat& xmax,
			       IlFloat& ymin, IlFloat& ymax,
			       IlBoolean operateByStep = IlTrue) const;
    virtual void contentsChanged(IlBoolean redraw = IlTrue);
    virtual void validate(IlFloat& xmin , IlFloat&  xmax ,
			  IlFloat& ymin , IlFloat&  ymax );
    IlFloat getXMin() const { return _min[0]; }
    IlFloat getXMax() const { return _max[0]; }
    IlFloat getYMin() const { return _min[positionToIndex(_currentAxis)]; }
    IlFloat getYMax() const { return _max[positionToIndex(_currentAxis)]; }
    void getValues(IlFloat& xmin, IlFloat& xmax,
		   IlFloat& ymin, IlFloat& ymax) const
	 {
	     xmin = _min[0];
	     xmax = _max[0];
	     getYValues(_currentAxis, ymin, ymax);
	 }
    void getYValues(IlvPosition pos, IlFloat& min, IlFloat& max) const
	 {
	     min = _min[positionToIndex(pos)];
	     max = _max[positionToIndex(pos)];
	 }
    IlFloat getDefaultExtrema() const { return _defaultExtrema; }
    void     setDefaultExtrema(IlFloat value,
			       IlvPosition = (IlvPosition)(IlvRight|IlvLeft));
    void     unSetDefaultExtrema()   { _extremaMustBeUsed = IlFalse; }
    IlFloat getShownXMin() const { return _shownMin[0]; }
    IlFloat getShownXMax() const { return _shownMax[0]; }
    IlFloat getShownYMin() const
	 { return _shownMin[positionToIndex(_currentAxis)]; }
    IlFloat getShownYMax() const
	{ return _shownMax[positionToIndex(_currentAxis)]; }
    void getShownValues(IlFloat& xmin, IlFloat& xmax,
			IlFloat& ymin, IlFloat& ymax) const
	{ xmin = _shownMin[0];
	  xmax = _shownMax[0];
	  getShownYValues(_currentAxis, ymin, ymax);
	}
    void getShownYValues(IlvPosition pos, IlFloat& min, IlFloat& max) const
	{ min = _shownMin[positionToIndex(pos)];
	  max = _shownMax[positionToIndex(pos)];
	}
    void currentAxis(IlvPosition pos) { _currentAxis = pos; }
    IlvPosition currentAxis() const { return _currentAxis; }
    void computeAxisLimits();

    IlBoolean inZoom() const { return _inZoom; }
    void setInZoom(IlBoolean value) { _inZoom = value; }

    static IlSymbol* _AxisProperty;
    static IlSymbol* AxisProperty() { return _AxisProperty; }

    IlUShort getChartFlags() const { return _chartFlags; }
    void      clipToChartsRect(IlBoolean flag);
    IlBoolean isClippingToChartsRect() const;
protected:
    IlvRect              _chartsRect;
    IlvPoint             _legendPosition;
    IlvPosition          _legendAlignment;
    IlvDeltaPos          _legendSpacing;
    IlvPosition          _currentAxis;
    IlFloat              _defaultExtrema;
    IlBoolean            _extremaMustBeUsed;
    IlvPosition          _defaultExtremaAxis;
    IlBoolean		 _inZoom;
    IlFloat              _min[3];
    IlFloat              _max[3];
    IlFloat              _shownMin[3];
    IlFloat              _shownMax[3];
    IlvRectangularScale* _scale[3];
    IlvGraphicAttachment _origAttach[3];
    IlFloat              _moveOrigin[3];
    IlvPos               _fixOrigin[3];
    char*                _format[3];
    IlvGraphic*          _legend;
    IlList               _charts;
    void insertObj(IlvGraphic*, IlInt pos, IlBoolean redraw = IlFalse);
    virtual void drawAll(IlvPort* dst, const IlvRegion& region,
			 const IlvRegion* clip=0);
    void init(IlvPosition scalesMask);
    void installAccelerators();
private:
    IlvChartsHandle*	_handle;
    IlUShort		_chartFlags;
};

ILV31VWSMODULEINIT(chartcnt);
#endif /* !__Ilv31_Chartcnt_H */
