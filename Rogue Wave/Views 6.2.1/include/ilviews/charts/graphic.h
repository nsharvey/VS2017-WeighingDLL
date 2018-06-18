// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/graphic.h
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
// Declaration of the IlvChartgraphic class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Graphic_H
#define __Ilv_Charts_Graphic_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_List_H)
#include <ilviews/base/list.h>
#endif

#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif
#if !defined(__Ilv_Charts_Chart_H)
#include <ilviews/charts/chart.h>
#endif
#if !defined(__Ilv_Charts_Data_H)
#include <ilviews/charts/data.h>
#endif
#if !defined(__Ilv_Charts_Scaledis_H)
#include <ilviews/charts/scaledis.h>
#endif
#if !defined(__Ilv_Charts_Layout_H)
#include <ilviews/charts/layout.h>
#endif
#if !defined(__Ilv_Charts_Grid_H)
#include <ilviews/charts/grid.h> // needed by Borland
#endif

class IlvAbstractProjector;
class IlvChartLayout;
class IlvAbstractChartDisplayer;
class IlvSingleChartDisplayer;
class IlvCompositeChartDisplayer;
class IlvAbstractGridDisplayer;
class IlvAbstractChartCursor;
class IlvChartLegend;
class IlvChartUpdater;
class IlvAxisCrossing;

// -------------------------------------------------------------------------
// --- Chart Accessors allow user-definition and implementation
// of accessors for subclasses of ChartGraphic and other
// subclasses of the chart package

class IlvChartAccessorArray;

class IlvChartAccessor
{
    friend class IlvChartGraphic;
public:
    IlvChartAccessor(const char*, IlvValueTypeClass*&);
    virtual ~IlvChartAccessor();
    void declareAccessor(const IlSymbol* const**,
			 const IlvValueTypeClass* const**, IlUInt&);
    virtual void queryValue(const IlvChartGraphic*, IlvValue&);
    virtual IlBoolean applyValue(IlvChartGraphic*, const IlvValue&);
    static IlvChartAccessor* Find (const IlSymbol*);
protected:
    const char* _name;
    const IlSymbol* _symbol;
    IlvValueTypeClass*& _type;
    static IlvChartAccessorArray* _instances;
};

class IlvChartAccessorParam : public IlvChartAccessor
{
public:
    IlvChartAccessorParam(const char*, IlvValueTypeClass*&);
    ~IlvChartAccessorParam();
    // ____________________________________________________________
    void queryValue(const IlvChartGraphic*, IlvValue&);
    IlBoolean applyValue(IlvChartGraphic*, const IlvValue&);
};

class ILVCHTEXPORTED
IlDeclareArrayWithoutEquality(IlvValue, IlvChartParamArray);

// --------------------------------------------------------------------------
class IlvChartGraphic;
class ILVCHTEXPORTED IlvChartDrawHook : public IlvNamedProperty
{
public:
    virtual ~IlvChartDrawHook();
    static IlSymbol* GetSymbol();

    static IlvChartDrawHook* Set(IlvChartGraphic*   scale,
				 IlvChartDrawHook*  hook);
    static IlvChartDrawHook* Get(const IlvChartGraphic* scale);
    static IlvChartDrawHook* Remove(IlvChartGraphic* scale);

    inline IlvChartGraphic* getChart() const { return _chart; }

    virtual void beforeDraw(IlvPort* dst,
			    const IlvTransformer* t = 0,
			    const IlvRegion*	  clip = 0) const;
    virtual void  afterDraw(IlvPort* dst,
			    const IlvTransformer* t = 0,
			    const IlvRegion*	  clip = 0) const;

    virtual void propertyAdded(IlAny);
    virtual void propertyRemoved();

    DeclareLazyPropertyInfoRO();
    DeclarePropertyIOConstructors(IlvChartDrawHook);

protected:
    IlvChartGraphic*	_chart;

    IlvChartDrawHook();
};

// --------------------------------------------------------------------------
// Class IlvAxisElement
// --------------------------------------------------------------------------
class IlvScaleCoordListener;

class ILVCHTEXPORTED IlvAxisElement
{
public:
    IlvAxisElement(IlvChartGraphic* parent,
                   IlvCoordinateInfo* info, IlvAxisCrossing* crossing);

    virtual ~IlvAxisElement();

    virtual void setScale(IlvAbstractScaleDisplayer* scaledisp);

    void setAxisCrossing(IlvAxisCrossing* crossing);

    void setGrid(IlvAbstractGridDisplayer* griddisplayer);

    // Format value ?
    // void setFormat(...)

    inline IlvAbstractScaleDisplayer* getScale() const { return _scale; }

    IlvCoordinateInfo*                getCoordinateInfo() const;

    inline IlvAbstractGridDisplayer*  getGrid() const { return _grid; }

    inline IlvChartGraphic*           getChart() const { return _parentChart; }

    inline IlvAxisCrossing* getAxisCrossing() const { return _axisCrossing; }

protected:
    void setCoordinateInfo(IlvCoordinateInfo*);

    IlvChartGraphic*           _parentChart;

    IlvCoordinateInfo*         _coordinateInfo; // IlvAxis in JCharts
//     IlvScaleCoordListener*     _coordLst;
    IlvAbstractScaleDisplayer* _scale;          // IlvScale
    IlvAbstractGridDisplayer*  _grid;           // IlvGrid
    IlvAxisCrossing*           _axisCrossing;   // IlvCoordinateSystem

};

// --------------------------------------------------------------------------
// Class IlvAbscissaAxisElement
// --------------------------------------------------------------------------

class ILVCHTEXPORTED IlvAbscissaAxisElement : public IlvAxisElement
{
public:
    IlvAbscissaAxisElement(IlvChartGraphic* parent,
                           IlvCoordinateInfo* info, IlvAxisCrossing* crossing);

    virtual void setScale(IlvAbstractScaleDisplayer*);

};


// --------------------------------------------------------------------------
// Class IlvChartGraphic
// --------------------------------------------------------------------------
//- FLAGS
#define IlvCHTChartFullRedrawRequest 0x00000001
#define IlvCHTChart40FileFormat	     0x00000002
#define IlvCHTChartDispBBox	     0x00000004
#define IlvCHTChart50FileFormat	     0x00000008

#define IlvChartProjectHorizontally 1
#define IlvChartProjectVertically   2


// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartGraphic : public IlvSimpleGraphic
{
    friend class IlvAxisElement;
    friend class IlvAbscissaAxisElement;

public:

    enum FillMode {
	FillNone = 0x0000,
	FillDataArea = 0x0001,
	FillGraphArea = 0x0002,
	FillDataAndGraphArea = FillDataArea | FillGraphArea
    };

    enum ScrollMode {
	IlvScrollModeStop,
	IlvScrollModeShift,
	IlvScrollModeCycle
    };

    IlvChartGraphic(IlvDisplay* display,
		    const IlvRect& bbox,
		    IlvPalette* palette = 0);

    virtual ~IlvChartGraphic();

    //== Virtuals from IlvSimpleGraphic ====================
    virtual void draw(IlvPort* dst,
		      const IlvTransformer* t = 0,
		      const IlvRegion* givenClip = 0) const;

    virtual void applyTransform(const IlvTransformer* t);
    virtual void boundingBox(IlvRect& r,
			     const IlvTransformer* t = 0) const;
    virtual void setOverwrite(IlBoolean);
    virtual void setMode(IlvDrawMode);
    virtual void setPalette(IlvPalette* palette);
    virtual void setBackground(IlvColor* background);
    virtual void setFillStyle(IlvFillStyle);
    virtual void setPattern(IlvPattern*);
    virtual void setColorPattern(IlvColorPattern*);
    virtual void setGradientPattern(IlvGradientPattern*);

    //== Colors ====================
    void setDataAreaBackground(IlvColor* color);
    void setDataAreaBackgroundPalette(IlvPalette* palette);
    inline IlvColor* getDataAreaBackground() const {
	return _dataAreaFillPalette->getForeground();
    }
    inline IlvPalette* getDataAreaBackgroundPalette() const{
	return _dataAreaFillPalette;
    }

    //IlvPalette* getDataAreaFillPalette() const;

    void setFillMode(FillMode mode) { _fillMode = mode; }
    FillMode getFillMode() const { return _fillMode; }

    // No focus drawing
    virtual void drawFocus(IlvPort*,
			   const IlvPalette* ,
                           const IlvTransformer* t = 0,
                           const IlvRegion*      clip = 0) const;
    virtual void computeFocusRegion(IlvRegion&,
                                    const IlvTransformer* t = 0) const;

    virtual void apply(IlvApplyObject, IlAny);
    virtual void applyReferences(IlvApplyObject, IlAny);

    virtual void setHolder(IlvGraphicHolder* holder);

    virtual IlBoolean beforeChangeValues(const IlvValue* =0, IlUShort = 0);
    virtual void      afterChangeValues(const IlvValue* =0, IlUShort = 0);

    virtual IlUInt getCallbackTypes(const char* const**     names,
				    const IlSymbol* const** types) const;

    //== Data ====================
    IlvAbstractChartData* getData() const { return _chartData; }

    virtual void setData(IlvAbstractChartData* data);

    //== Chart displayers ====================
    IlUInt getDisplayersCount() const;

    IlvAbstractChartDisplayer* getDisplayer(IlUInt displayerIndex) const;

    IlvAbstractChartDisplayer* getDisplayerByName(const char* name) const;

    IlBoolean addDisplayer(IlvAbstractChartDisplayer* displayer,
			   IlvChartDataSet* dataSet = 0,
			   IlvCoordinateInfo* ordinateInfo=0,
			   IlUInt  position = IlvLastPositionIndex);

    virtual IlBoolean addDisplayer(IlvAbstractChartDisplayer* displayer,
				   IlUInt count,
				   IlvChartDataSet* const* dataSets,
				   IlvCoordinateInfo* ordinateInfo = 0,
				   IlUInt position = IlvLastPositionIndex);

    virtual IlBoolean replaceDisplayer(IlvAbstractChartDisplayer* oldDisplayer,
				       IlvAbstractChartDisplayer* newDisplayer,
				       IlBoolean copyPalettes = IlFalse);

    virtual void moveDisplayer(IlUInt displayerIndex, IlUInt  newIndex);

    virtual IlBoolean removeDisplayer(IlUInt displayerIndex);

    virtual void removeDisplayers();

    IlUInt getDisplayerIndex(const IlvAbstractChartDisplayer* displayer) const;

    //== Chart layout ====================
    IlvChartLayout* getLayout() const {return _chartLayout;}

    virtual void setLayout(IlvChartLayout* layout);

    //== Projector =========================
    IlvAbstractProjector* getProjector() const { return _projector; }

    virtual IlBoolean setProjector(IlvAbstractProjector* projector);

    //== Scale displayers =========================
    IlvSingleScaleDisplayer* getAbscissaScale() const
	{
	    return IL_CAST(IlvSingleScaleDisplayer*,
			   _abscissaAxisElement.getScale());
	}

    virtual void setAbscissaScale(IlvSingleScaleDisplayer* scale);

    inline IlUInt getOrdinateScalesCount() const
    { return _ordinateAxisElements.getLength(); }

    IlvAbstractScaleDisplayer* getOrdinateScale(IlUInt index = 0) const;

    IlvSingleScaleDisplayer* getOrdinateSingleScale(IlUInt index = 0) const;

    void addOrdinateScale(IlvAbstractScaleDisplayer* scale)
	{ insertOrdinateScale(scale,IlvLastPositionIndex); }

    virtual void insertOrdinateScale(IlvAbstractScaleDisplayer* scale,
				     IlUInt index = 0);
    virtual void setOrdinateScale(IlUInt index,
				  IlvAbstractScaleDisplayer* scale);
    IlUInt getOrdinateScaleIndex(const IlvAbstractScaleDisplayer* scale) const;

    virtual void removeAbscissaScale();

    virtual void removeOrdinateScale(IlUInt index);

    virtual void removeOrdinateScales();

    //== Chart coordinate info ====================
    IlvCoordinateInfo* getAbscissaInfo() const;

    inline IlUInt getOrdinateInfoCount() const {
	return _ordinateAxisElements.getLength();
    }

    IlvCoordinateInfo* getOrdinateInfo(IlUInt index = 0) const;

    IlUInt getOrdinateInfoIndex(const IlvCoordinateInfo* info) const;

    //== Legend ====================
    inline IlvChartLegend* getLegend() const { return _legend; }

    void setLegend(IlvChartLegend* legend);

    inline void iSetLegend(IlvChartLegend* legend) { _legend = legend; }

    // Not documented
    // This method is used inside the update() method when legendToUpdate()
    // returns IlTrue.
    void updateLegend();

    //== Scales & Grids positioning ========

    void setDrawOrder(IlvDrawOrder drawOrder);

    //== Scroll mode ====================
    inline ScrollMode getScrollMode() const { return _scrollMode;  }

    void setScrollMode(ScrollMode mode, IlBoolean createCursor = IlFalse);

    IlvAbstractChartCursor* getCycleCursor() const;

    inline IlvAbstractChartCursor* getScrollCursor() const {
	return _scrollCursor;
    }

    inline IlDouble getScrollRatio() const { return _scrollRatio; }

    inline void setScrollRatio(IlDouble ratio) { _scrollRatio = ratio; }

    // Only works for ShiftScrollMode
    void enableFastScroll(IlBoolean enable);

    inline IlBoolean isFastScrollEnabled() const { return _fastScroll; }

    // Methods for automatic update
    virtual void drawPoints(const IlvChartDataSet* ds,
			    IlUInt iMin,
			    IlUInt iMax);

    virtual void dataPointsAdded(const IlvChartDataSet* ds,
				 IlUInt iMin,
				 IlUInt iMax,
				 IlBoolean reDraw = IlTrue);

    virtual void dataPointsRemoved(const IlvChartDataSet* ds,
				   IlUInt iMin,
				   IlUInt iMax,
				   IlBoolean reDraw = IlTrue);

    virtual void dataAllPointsRemoved(const IlvChartDataSet* ds,
				   IlBoolean reDraw = IlTrue);


    //== Specific for cyclic mode ====================

#if DOCUMENTED_LATER
#endif
    inline IlDouble getMinimumCycle() const { return _minimumCycle; }

#if DOCUMENTED_LATER
#endif
    inline IlDouble getMaximumCycle() const { return _maximumCycle; }

#if DOCUMENTED_LATER
#endif
    inline IlDouble getOriginCycle() const { return _originCycle; }

    inline IlBoolean projectHorizontally() const
	{
	    return (_projectFlags & IlvChartProjectHorizontally)
		? IlTrue
		: IlFalse;
	}

    inline void setProjectHorizontally(IlBoolean projectHorizontally)
    {
	if (projectHorizontally)
	    _projectFlags |= IlvChartProjectHorizontally;
	else
	    _projectFlags &= ~IlvChartProjectHorizontally;
    }
    inline IlBoolean projectVertically() const
    { return (_projectFlags & IlvChartProjectVertically) ? IlTrue : IlFalse; }

    inline void setProjectVertically(IlBoolean projectVertically)
    {
	if (projectVertically)
	    _projectFlags |= IlvChartProjectVertically;
	else
	    _projectFlags &= ~IlvChartProjectVertically;
    }

    inline IlvPalette* getProjectedPointsPalette() const
        { return _projectedPointsPalette; }

    void setProjectedPointsPalette(IlvPalette* palette);

    // How to use color for drawing

#if DOCUMENTED_LATER
#endif
    inline IlBoolean  applyPaletteAfterPoint() const
	{ return _applyPaletteAfterPoint; }

#if DOCUMENTED_LATER
#endif
    inline void setApplyPaletteAfterPoint(IlBoolean b)
        { _applyPaletteAfterPoint = b; }

    //== Shortcuts to dataset accessors ==================
    inline IlUInt getDataSetsCount() const
	{
	    return getData()->getDataSetsCount();
	}

    inline IlvChartDataSet* const* getDataSets(IlUInt& dataSetCount) const
	{
	    return getData()->getDataSets(dataSetCount);
	}

    inline IlvChartDataSet* getDataSet(IlUInt dataSetIndex) const
	{
	    return getData()->getDataSet(dataSetIndex);
	}

    inline IlUInt getDataSetIndex(const IlvChartDataSet* dataSet) const
	{ return getData()->getDataSetIndex(dataSet); }

    //== Cursors ================
    IlvAbstractChartCursor* addAbscissaCursor(IlDouble value,
					      IlvPalette* palette = 0,
					      IlBoolean reDraw = IlTrue);

    IlvAbstractChartCursor* removeAbscissaCursor(IlvAbstractChartCursor* cursor,
						 IlBoolean reDraw = IlTrue);

    IlvAbstractChartCursor* addOrdinateCursor(IlDouble value,
					      IlvPalette* palette = 0,
					      IlUInt index = 0,
					      IlBoolean reDraw = IlTrue);

    IlvAbstractChartCursor* removeOrdinateCursor(IlvAbstractChartCursor* cursor,
						 IlUInt index = 0,
						 IlBoolean reDraw = IlTrue);

    IlvSingleScaleDisplayer* getScaleForCursor(const IlvAbstractChartCursor* cursor) const;

    void moveCursor(IlvAbstractChartCursor* cursor,
		    IlDouble newValue,
		    IlBoolean reDraw = IlTrue);

    void setCursorVisible(IlvAbstractChartCursor* cursor,
			  IlBoolean visible);

    void invalidateCursor(IlvAbstractChartCursor* cursor);


    //== Grid displayers ====================
    inline IlvAbstractGridDisplayer* getAbscissaGrid() const
	{
	    return IL_CAST(IlvAbstractGridDisplayer*,
			   _abscissaAxisElement.getGrid());
	}

    virtual void setAbscissaGrid(IlvAbstractGridDisplayer* grid);

    IlvAbstractGridDisplayer* getOrdinateGrid(IlUInt index = 0) const;

    virtual void setOrdinateGrid(IlUInt index,
				  IlvAbstractGridDisplayer* grid);
    IlUInt getOrdinateGridIndex(const IlvAbstractGridDisplayer* grid) const;

    virtual void removeOrdinateGrids();

    IlvAbstractGridDisplayer* addAbscissaGrid(IlvPalette* majorPalette = 0,
					      IlvPalette* minorPalette = 0,
					      IlBoolean reDraw = IlTrue);

    void removeAbscissaGrid(IlBoolean reDraw = IlTrue);

    IlvAbstractGridDisplayer* addOrdinateGrid(IlvPalette* majorPalette = 0,
					      IlvPalette* minorPalette = 0,
					      IlUInt index = 0,
					      IlBoolean reDraw = IlTrue);

    void removeOrdinateGrid(IlUInt index = 0,
			    IlBoolean reDraw = IlTrue);

    //== API ================

    IlBoolean isReDrawnWhenNotified() const { return _reDrawWhenNotified; }

    inline void reDrawWhenNotified(IlBoolean reDraw)
	{
	    _reDrawWhenNotified = reDraw;
	}

    //== Methods concerning geometry ============
    inline void getGraphArea(IlvRect& graphArea,
			     const IlvTransformer* t = 0) const
	{
	    getLayout()->getGraphArea(graphArea, t);
	}

    inline void getDataDisplayArea(IlvRect& dataDisplayArea,
				   const IlvTransformer* t = 0) const
	{
	    getLayout()->getDataDisplayArea(dataDisplayArea, t);
	}

    inline void getDataDisplayArea(const IlvCoordinateInfo* coordInfo,
				   IlvRect& dataDisplayArea,
				   const IlvTransformer* t = 0) const
	{
	    IlvProjectorArea projArea;
	    getProjectorArea(coordInfo, projArea, t);
	    getProjector()->getDataDisplayArea(projArea, dataDisplayArea);
	}

    void getProjectorArea(const IlvCoordinateInfo* coordInfo,
			  IlvProjectorArea& projArea,
			  const IlvTransformer* t) const;

    inline void getProjectorArea(const IlvAbstractScaleDisplayer* scale,
				 IlvProjectorArea& projArea,
				 const IlvTransformer* t = 0) const
	{
	    getProjectorArea(scale->getCoordinateInfo(), projArea, t);
	}

    IlvCoordinateGroup*
	getCoordinateGroup(const IlvCoordinateInfo* coord) const;

    void stackScales(IlUInt count,
		     const IlvSingleScaleDisplayer* const* scales,
		     IlDouble offsetRatio);

    void stackCoordinates(IlUInt count,
			  const IlvCoordinateInfo* const* coords,
			  IlDouble offsetRatio);

    IlvCoordinateGroup* removeCoordinateGroup(IlvCoordinateGroup* group);

    IlBoolean getDrawingArea(IlvRect& drawingArea,
			     const IlvTransformer* t = 0) const;

    // This method is used inside the update() method when layoutToUpdate()
    // returns IlTrue.
#if DOCUMENTED_LATER
#endif
    virtual void updateLayout();

    virtual void update();

    void updateAndReDraw();

    void dataPointChanged(const IlvChartDataSet* dataSet,
			  IlUInt pointIndex,
			  IlBoolean beforeChange);

    inline IlBoolean invalidatePoint(const IlvChartDataSet* dataSet,
				     IlUInt idx,
				     IlBoolean ptInfo = IlTrue)
	{
	    return invalidatePoints(dataSet, idx, idx, ptInfo);
	}

    IlBoolean invalidatePoints(const IlvChartDataSet* dataSet,
			       IlUInt iMin,
			       IlUInt iMax,
			       IlBoolean ptInfo = IlTrue);


    IlBoolean dataPointsToDisplay(IlUInt count,
				  const IlvDoublePoint* dataPoints,
				  IlvPoint* points,
				  const IlvCoordinateInfo* ordinateInfo,
				  IlBoolean shiftOfCycleLength,
				  const IlvTransformer* t = 0) const;

    IlBoolean displayToDataPoints(IlUInt count,
				  const IlvPoint* points,
				  IlvDoublePoint* dataPoints,
				  const IlvCoordinateInfo* ordinateInfo,
				  IlBoolean shiftOfCycleLength,
				  const IlvTransformer* t = 0) const;

    IlBoolean resetCycleValues();

#if DOCUMENTED_LATER
#endif
    IlBoolean isInCyclicMode() const;

#if DOCUMENTED_LATER
#endif
    IlBoolean hasToShiftOfCycleLength(const IlvDoublePoint& dataPoint) const;

#if DOCUMENTED_LATER
#endif
    IlBoolean isShiftedOfCycleLength(const IlvPoint& point) const;

    IlUInt getNearestPoint(IlvAbstractChartDisplayer*& displayer,
			   IlvChartDataSet*& dataSet,
			   const IlvPoint& viewPoint,
			   IlvDim distance,
			   IlvPoint& point,
			   const IlvTransformer* t) const;

    IlUInt getDisplayItem(IlvAbstractChartDisplayer*& displayer,
                          IlvChartDataSet*& dataSet,
                          const IlvPoint& viewPoint,
                          const IlvTransformer* t) const;

#if DOCUMENTED_LATER
#endif
    void getCrossingPoint(IlUInt ordinateAxisIndex,
			  IlvPoint& point,
			  const IlvTransformer* t = 0) const;



    void setAxisCrossing(IlInt index, IlvAxisCrossing*);

    void setAxisCrossing(IlInt index, IlDouble val);

    const IlvAxisCrossing* getAxisCrossing(IlInt index) const;

    ///// AxisElement stuff
    // protected:
    IlvAxisElement* getOrdinateAxisElt(IlUInt idx) const;
    IlvAxisElement* addOrdinateAxisElt();


#if DOCUMENTED_LATER
#endif
    IlvPoint* getCrossingPoints(IlUInt& crossingCount,
				const IlvTransformer* t = 0) const;

    void getPointOnAbscissaScaleAxis(IlDouble valueOnAxis,
				     IlvPoint& pointOnAxis,
				     const IlvTransformer* t = 0) const;

    void drawScales(IlvDrawOrder drawOrder,
		    IlvPort* dst,
		    const IlvTransformer* t = 0,
		    const IlvRegion* clip = 0) const;

    void drawScale(IlvAbstractScaleDisplayer* scale,
		   IlvDrawOrder drawOrder,
		   IlvPort* dst,
		   const IlvTransformer* t = 0,
		   const IlvRegion* clip = 0) const;

    void drawCursor(const IlvAbstractChartCursor* cursor,
		    IlvPort* dst = 0,
		    const IlvTransformer* t = 0,
		    const IlvRegion* clip = 0) const;

    IlBoolean boundingBoxOfScale(IlvAbstractScaleDisplayer* scale,
				 IlvRect& bbox,
				 const IlvTransformer* t = 0) const;

    IlBoolean boundingBoxOfCursor(IlvSingleScaleDisplayer* scale,
				  IlvAbstractChartCursor* cursor,
				  IlvRect&         bbox,
				  const IlvTransformer* t = 0) const;

    void computeGraphicalElementsBBox(IlvRect& bbox,
				      const IlvTransformer* t = 0) const;

    // Methods zoom, translate
    virtual void translateCharts(IlDouble deltaAbscissa,
				 IlDouble deltaOrdinate,
				 IlUInt ordinateAxisIndex = 0,
				 IlBoolean redraw = IlTrue,
				 IlBoolean clipToAutoRange = IlTrue);

    virtual IlBoolean zoomCharts(const IlvCoordInterval& abscissaRange,
				 IlBoolean redraw = IlTrue,
				 IlBoolean clipToAutoRange = IlTrue);

    virtual IlBoolean zoomCharts(const IlvCoordInterval& ordinateRange,
				 IlUInt ordinateAxisIndex,
				 IlBoolean redraw = IlTrue,
				 IlBoolean clipToAutoRange = IlTrue);

    IlBoolean zoomCharts(const IlvCoordInterval& abscissaRange,
			 const IlvCoordInterval& ordinateRange,
			 IlUInt ordinateAxisIndex = 0,
			 IlBoolean redraw = IlTrue,
			 IlBoolean clipToAutoRange = IlTrue);
    // Persistence
    DeclareTypeInfo();
    DeclareGraphicAccessors();
    DeclareIOConstructors(IlvChartGraphic);

    // Get the current accessor parameters
    const IlvValue* getAccessorParam(const IlSymbol*) const;
    void setAccessorParam(const IlvValue&);
    inline const IlvValue* getAccessorParam(const char* n) const
	{ return getAccessorParam(IlGetSymbol(n)); }
    inline const IlvValue* getAccessorParam(IlvValue& v) const
	{
	  const IlvValue* v2 = getAccessorParam(v.getName());
	  if (v2) v=*v2;
	  return &v;
	}

    //== Accessors for updating ====================
    IlBoolean layoutToUpdate() const;
    void invalidateLayout();

    inline IlBoolean legendToUpdate() const
	{
	    return _legend && _legendToUpdate;
	}
    inline void invalidateLegend() { _legendToUpdate = IlTrue; }

    inline IlBoolean autoMinMaxToUpdate() const
	{
	    return _autoMinMaxToUpdate;
	}
    inline void setAutoMinMaxToUpdate(IlBoolean flag)
	{
	    _autoMinMaxToUpdate = flag;
	}

    //== Flags
    inline IlUInt getFlags() const { return _flags; }
    inline void setFlags(IlUInt flags) { _flags = flags; }

protected:
    IlUInt			_flags;
    IlvRect			_bbox;
    IlvAbstractChartData*	_chartData;
    IlArray			_chartDisplayers;
    IlvChartLayout*		_chartLayout;
    IlvAbstractProjector*	_projector;

    IlvAbscissaAxisElement      _abscissaAxisElement;
    IlArray                     _ordinateAxisElements;

    IlvChartLegend*		_legend;
    IlBoolean			_legendToUpdate;

    ScrollMode			_scrollMode;
    IlDouble			_scrollRatio;
    IlBoolean			_fastScroll;
    IlDouble			_minimumCycle;
    IlDouble			_maximumCycle;
    IlDouble			_originCycle;
    IlvAbstractChartCursor*	_scrollCursor;
    IlUShort			_projectFlags;
    IlBoolean			_applyPaletteAfterPoint;
    IlvPalette*			_projectedPointsPalette;

    IlBoolean			_autoMinMaxToUpdate;

    IlvChartDataListener*	_dataListener;
    IlBoolean			_reDrawWhenNotified;
    IlvChartUpdater*		_updater;

    IlvCoordInfoLstMap		*_coordLstMap;
    FillMode			_fillMode;
    IlvPalette*			_dataAreaFillPalette;
    IlvPalette*			_graphAreaFillPalette;

    IlList*			_coordinateGroups;

    IlvChartParamArray 		_accessorParams;

    // Accessors
    // Specific accessors for cyclic mode
    inline void setMinimumCycle(IlDouble min) { _minimumCycle = min; }
    inline void setMaximumCycle(IlDouble max) { _maximumCycle = max; }
    inline void setOriginCycle(IlDouble origin) { _originCycle = origin; }

    // Internal methods
    IlBoolean updateAutoDataRange() const;
    virtual void validateAutoDataRange(const IlvCoordinateInfo* ci,
				       IlvCoordInterval& range) const;

    virtual IlBoolean modifyScales(const IlvAbstractProjector* oldProjector,
				   const IlvAbstractProjector* newProjector);

    virtual IlBoolean modifyScalesFromPolarToCartesian();
    virtual IlBoolean modifyScalesFromCartesianToPolar();
    virtual IlBoolean isProjectorValidForScale(const IlvAbstractScaleDisplayer* scale) const;


    void updateDisplayers(IlvAbstractScaleDisplayer* oldScale,
			  IlvAbstractScaleDisplayer* newScale);

    void coordInfoReplaced(IlvCoordinateInfo* oldCoord,
			   IlvCoordinateInfo* newCoord);

    //== Computes the palette used to fill the graph area
    void computeFillPalette();

    //== Factory method to create the listener that is attached to
    //== the chart data.
    virtual IlvChartDataListener* createDataListener();

    virtual IlvAbstractChartCursor* addScrollCursor();
    virtual IlvAbstractChartCursor* addCycleCursor();

    //== Factory method to create the updater used to compute
    //== invalidated regions on the chart.
    virtual IlvChartUpdater* createUpdater();
    inline  IlvChartUpdater* getUpdater() {
	if (!_updater)
	    _updater = createUpdater();
	return _updater;
    }

    static IlSymbol* GetCycleCursorProperty();
    void setCycleCursor(IlvAbstractChartCursor*);

    void fillArea(IlvPort*		dst,
		  const IlvTransformer* t = 0,
		  const IlvRegion*	clip = 0) const;
};


// --------------------------------------------------------------------------
// Class IlvChartGraphicDataListener
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartGraphicDataListener
: public IlvChartDataListener
{
public:

    IlvChartGraphicDataListener(IlvChartGraphic* chart) :
      IlvChartDataListener(), _chartGraphic(chart) {}

    IlvChartGraphic* getChartGraphic() const { return _chartGraphic; }

    virtual void dataSetRemoved(const IlvAbstractChartData* chartData,
				IlvChartDataSet* dataSet);

    virtual void dataSetAdded(const IlvAbstractChartData* chartData,
			      IlvChartDataSet* dataSet,
			      IlUInt position);

    virtual void dataSetChanged(const IlvAbstractChartData* chartData,
				IlvChartDataSet* oldSet,
				IlvChartDataSet* newSet);

    virtual void dataPointRemoved(const IlvAbstractChartData* chartData,
				  const IlvChartDataSet* dataSet,
				  IlUInt pointIndex);

    virtual void dataAllPointsRemoved(const IlvAbstractChartData* chartData,
				  const IlvChartDataSet* dataSet);

    virtual void dataPointChanged(const IlvAbstractChartData* chartData,
				  const IlvChartDataSet* dataSet,
				  IlUInt pointIndex,
				  IlBoolean beforeChange);

    virtual void dataPointAdded(const IlvAbstractChartData* chartData,
				const IlvChartDataSet* dataSet,
				IlUInt position);

    virtual void startBatch(const IlvAbstractChartData* chartData,
			    const IlvChartDataSet* dataSet);

    virtual void endBatch(const IlvAbstractChartData* chartData,
			  const IlvChartDataSet* dataSet);

protected:
    IlvChartGraphic* _chartGraphic;
};

// --------------------------------------------------------------------------
// Class IlvChartUpdater
// --------------------------------------------------------------------------
class IlvChartUpdater : public IlvRegionUpdater
{
public:
    IlvChartUpdater(IlvChartGraphic* chart);

    inline void setDataToUpdate(const IlvChartDataSet* dataSet,
			        IlUInt iMin,
			        IlUInt iMax)
    { _dataSet = dataSet; _iMin = iMin; _iMax = iMax; }

    virtual IlBoolean update(IlvRegion& region,
			     const IlvRect& clip,
			     const IlvTransformer* t = 0) const;

    inline IlUShort getMaxRectangles() const { return _maxRectangles; }
    inline void setMaxRectangles(IlUShort max) {_maxRectangles=max; }
private:
    IlvChartGraphic*	    _chart;
    const IlvChartDataSet*  _dataSet;
    IlUInt		    _iMin;
    IlUInt		    _iMax;
    IlUShort		    _maxRectangles;
};


// --------------------------------------------------------------------------
// Class IlvAxisCrossing
// --------------------------------------------------------------------------

class ILVCHTEXPORTED IlvAxisCrossing
{
public:
    virtual ~IlvAxisCrossing();

    virtual IlDouble getCrossingValue(IlvCoordinateInfo* info) const = 0;

    static IlvAxisCrossing* minValueCrossing();
    static IlvAxisCrossing* maxValueCrossing();
};

class ILVCHTEXPORTED IlvMinAxisCrossing : public IlvAxisCrossing
{
public:
    virtual IlDouble getCrossingValue(IlvCoordinateInfo*) const;
};

class ILVCHTEXPORTED IlvMaxAxisCrossing : public IlvAxisCrossing
{
public:
    virtual IlDouble getCrossingValue(IlvCoordinateInfo*) const;
};

class ILVCHTEXPORTED IlvAxisAnchoredCrossing : public IlvAxisCrossing
{
public:
    IlvAxisAnchoredCrossing(IlDouble val);

    virtual IlDouble getCrossingValue(IlvCoordinateInfo*) const;

protected:
    IlDouble _val;
};

ILVCHTMODULEINIT(graphic);

#endif /* !__Ilv_Charts_Graphic_H */
