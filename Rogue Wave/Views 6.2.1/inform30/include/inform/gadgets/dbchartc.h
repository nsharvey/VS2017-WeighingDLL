// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/gadgets/dbchartc.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Definition of the IliDbChartContainer class
// Defined in library dbchart
// --------------------------------------------------------------------------
#ifndef __Ili_Dbchartc_H
#define __Ili_Dbchartc_H

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ilv_Oldchart_Chart_H
#  include <ilviews/chart.h>
#endif

#ifndef __Ilv_Oldchart_Chartcnt_H
#  include <ilviews/chartcnt.h>
#endif

#ifndef __Ilv_Contain_Chartint_H
#  include <ilviews/chartint.h>
#endif

#ifndef __Ilv_Gadgets_Frame_H
#  include <ilviews/gadgets/frame.h>
#endif

#ifndef __Ilv_Msglabel_H
#  include <ilviews/gadgets/msglabel.h>
#endif

#ifndef __Ilv_Gadgets_Scrollb_H
#  include <ilviews/gadgets/scrollb.h>
#endif

#ifndef __Ili_Datatype_H
#  include <ilviews/dataccess/datatype.h>
#endif

#ifndef __Ili_Format_H
#  include <ilviews/dataccess/format.h>
#endif

#ifndef __Ili_Memtable_H
#  include <ilviews/dataccess/memtable.h>
#endif

#ifndef __Ili_Module_H
#  include <ilviews/dataccess/module.h>
#endif

#ifndef __Ili_Reposit_H
#  include <ilviews/dataccess/reposit.h>
#endif

#ifndef __Ili_Chartool_H
#  include <../inform30/include/inform/gadgets/chartool.h>
#endif

#ifndef __Ili_Datasrc_H
#  include <ilviews/dataccess/gadgets/datasrc.h>
#endif

#ifndef __Ili_Entryfld_H
#  include <ilviews/dataccess/gadgets/entryfld.h>
#endif

#ifndef __Ili_Tablegad_H
#  include <ilviews/dataccess/gadgets/tablegad.h>
#endif

#ifndef __Ili_Tblcombo_H
#  include <ilviews/dataccess/gadgets/tblcombo.h>
#endif

#ifndef __Ili_FilterValue_
#define __Ili_FilterValue_

enum IliChartMissingValue {
    IliChartMissingRepeat = 0,
    IliChartMissingPutZero,
    IliChartMissingIgnore,
    IliChartMissingNbTag
};

#endif

enum IliChartColor {
    IliChartBackground = 0,
    IliChartColorScale,
    IliChartColorGrid,
    IliChartColorNbTag
};

enum IliZoomType {
    IliZoomAllPoints = 0,
    IliZoomLastPoints,
    IliZoomCursor,
    IliZoomNbTag
};

enum IliScaleType {
    IliScaleTypeNormal = 0,
    IliScaleTypeAdjusted,
    IliScaleTypeExpansed,
    IliScaleTypeNbTag
};

enum IliDbChartInteraction {
    IliDataSourceToDbChart = 1,
    IliDbChartToDataSource
};

enum IliMinMaxScale {
    IliMinScale = 0,
    IliMaxScale,
    IliMinMaxScaleNbTag
};

class ILV_DBCHART_EXPORTED IliDbChartContainer;
class ILV_DBCHART_EXPORTED IliDbChartDefinition;
class ILV_DBCHART_EXPORTED IliDbChartSeries;

typedef IlvChart* (*IliCreateChartCallback)(IlvDisplay* disp, IlvChartData* d);

typedef IlvMultiChart* (*IliCreateMultiCallback)(IlvDisplay* disp);

typedef void (*IliComputeSizeCallback)(IlvMultiChart* chart, IlInt spacing );

// --------------------------------------------------------------------------
// IliChartData
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliChartData : public IlvChartDataPoints
{
public:
    IliChartData(IlUInt count, IlvFloatPoint* values, IlBoolean repeat);
    virtual void	getPoint(IlUInt num, IlvFloatPoint& p) const;

protected:
    IlBoolean		_repeatLastPoint;
};

// --------------------------------------------------------------------------
// IliChartHook
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliChartTableHook : public IliTableHook
{
public:
    IliChartTableHook(IliDbChartContainer *chart);
    virtual void		startOfBatch();
    virtual void		endOfBatch();
    virtual void		tableDeleted();
    virtual void		tableChanged();
    virtual void		columnChanged(IlInt);
    virtual void		rowInserted(IlInt);
    virtual void		rowToBeChanged(IlInt);
    virtual void		rowChanged(IlInt);
    virtual void		rowToBeDeleted(IlInt);
    virtual void		rowDeleted(IlInt);
    virtual void		rowMoved(IlInt, IlInt);
    virtual void		rowsExchanged(IlInt, IlInt);
    virtual void		rowsInserted(IlInt, IlInt);
    virtual void		rowsFetched(IlInt, IlInt);
    virtual void		cellChanged(IlInt, IlInt);

protected:
    IliDbChartContainer*	_chart;
};

// --------------------------------------------------------------------------
// IliDbChartSeries
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliDbChartSeries
{
public:
    IliDbChartSeries();
    virtual ~IliDbChartSeries();
    
    void		setName(const char* name);
    const char*		getName() const;
    IlInt		isThis(const char* name) const;
    
    void		setLabel(const char* name);
    const char*		getLabel() const;
    
    void		setChart(const char* chart);
    const char*		getChart() const;
    
    void		setColor(const char* name);
    const char*		getColor() const;
    IlvColor*		getColor(IlvDisplay*) const;
    
    void		setMissingValue(IliChartMissingValue);
    IliChartMissingValue getMissingValue() const;
    
    void		predefinedSeries(IlBoolean = IlTrue);
    IlBoolean		isSeriesPredefined() const;
    
    void		setChartData(IlvChartData*);
    IlvChartData*	getChartData() const;
    
    void		setMultiChart(IlBoolean);
    IlBoolean		isMultiChart() const;
    
    void		setDisplayer(IlvChart*, IlBoolean del = IlTrue);
    IlvChart*		getDisplayer() const;
    
    void		resetValues();
    void		allocValues(IlInt count);
    void		allocForInsertValue(IlInt);
    
    void		setValue(IlInt pos, IlFloat value);
    IlBoolean		setValue(IlInt pos, IlFloat value, IliFilterValue);
    IlFloat		getValue(IlInt pos) const;
    
    IlUShort		getCounter(IlInt pos) const;
    void		setCounter(IlInt pos, IlUShort val);
    
    void		copyDefinition(IliDbChartSeries& series);
    void		copy(IliDbChartSeries& series);
    
protected:
    //---- Properties ----
    IliString		_name;
    IliString		_label;
    IliString		_chart;
    IliString		_color;
    IliChartMissingValue _missing;
    IlBoolean		_predefine;
    
    //---- values ----
    IlInt		_count;
    IlFloat*		_values;
    IlUShort*		_counters;
    
    //---- Display ----
    IlvChartData*	_chartData;
    IlvChart*		_displayer;
    IlBoolean		_multiChart;
};

// --------------------------------------------------------------------------
// IliDbChartHook
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliDbChartHook
{
    friend class IliDbChartDefinition;

public:
    IliDbChartHook();
    virtual ~IliDbChartHook();
    
    void			lock();
    void			unLock();
    
    virtual IliDbChartHook*	clone() const;
    
    IliDbChartDefinition*	getChart() const;
    
    //---- Events series ----
    virtual const char*		computeSeriesLabel(const char* series);
    virtual const char*		computeSeriesChart(const char* series);
    virtual const char*		computeSeriesColor(const char* series);
    virtual IlInt		computeSeriesInsertionPosition(const char* s,
							       const char* l);
    virtual IliChartMissingValue computeSeriesMissingValue(const char* series,
							   const char* chart);
    virtual IlvFloatPoint*	computeSeriesValues(IlInt index,
						    IlInt from,
						    IlInt size,
						    IlInt& count);
    
    //---- Events x value ----
    virtual const char*		computeXValueLabel(const char* name);
    virtual IlInt		computeXValueInsertionPosition(const char* n,
							       const char* l);
    
    //---- Information series ----
    IlInt			getSeriesCount() const;
    const char*			getSeriesName(IlInt pos) const;
    const char*			getSeriesLabel(IlInt pos) const;
    const char*			getSeriesChart(IlInt pos) const;
    const char*			getSeriesColor(IlInt pos) const;
    IlvColor*			getSeriesColor(IlInt pos,
					       IlvDisplay* display) const;
    IliChartMissingValue	getSeriesMissingValue(IlInt pos) const;
    IlFloat			getSeriesValue(IlInt pos, IlInt xpos) const;
    IlUShort			getSeriesCounter(IlInt pos, IlInt xpos) const;
    
    //---- Information x value ----
    IlInt			getXValueCount() const;
    const char*			getXValue(IlInt) const;
    const char*			getXValueLabel(IlInt) const;
    
    //---- Tools ----
    const char*			getMappedValue(IliTable*,
					       IlInt,
					       const char*,
					       IlvGraphicHolder* holder = 0,
					       IliTable* = 0) const;
    IliTable*			getTable() const;
    
protected:
    IliDbChartDefinition*	_chartDef;
    IlInt			_refCount;
    
    void			connect(IliDbChartDefinition*);
};

// --------------------------------------------------------------------------
// IliDbChartDefinition
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliDbChartDefinition
{
public:
    IliDbChartDefinition(IlvDisplay* disp) { init (disp); }
    virtual ~IliDbChartDefinition();
    IlvDisplay*		getDisplay() const;
    void		lock();
    void		unLock();
    
    //---- Data ----
    void		init(IlvDisplay*);
    void		reset(IlBoolean columns = IlTrue);
    void		resetX();
    void		resetValues();
    void		computeFromDataSource();
    void		computeX();
    void		computeValues();
    void		computeValuesByRow(IliTableBuffer*,
					   IlInt,
					   IlInt,
					   IlInt);
    void		computeValuesByColumn(IliTableBuffer*, IlInt);
    void		computeSeriesChartData(IlInt series, IlBoolean repeat);
    
    void		extractDataByColumn(IlBoolean);
    IlBoolean		isDataExtractedByColumn() const;
    
    //---- Load & Save ----
    virtual void	save(IlvOutputFile&, IlBoolean = IlFalse);
    virtual void	load(IlvInputFile&, IlBoolean = IlFalse);
    
    //---- Series ----
    IliDbChartSeries*	getSeries(IlInt) const;
    IlInt		getSeriesCount() const;
    void		setSeriesCount(IlInt);
    void		defineSeries(IlInt,
				     const char*,
				     const char*,
				     const char*,
				     const char*,
				     IliChartMissingValue);
    IlInt		addSeries(const char*);
    IlInt		getSeriesPosition(const char*) const;
    void		compressSeries();
    void		predefinedAllSeries();
    
    //---- X value ----
    const char*		getXValueLabel(IlInt) const;
    const char*		getXValue(IlInt) const;
    IlInt		getXValueCount() const;
    IlInt		getXValuePosition(const char*) const;
    IlInt		addXValue(const char*, IlBoolean = IlFalse);
    void		sortXAxis(IlBoolean, IlBoolean);
    IlBoolean		isXAxisSorted() const;
    IlBoolean		isXAxisNumeric() const;
    void		allocValues();
    
    void		setAutoSelect(IlBoolean);
    IlBoolean		isAutoSelect() const;
    
    //---- Properties ----
    void		setChartColor(IliChartColor, IlvColor*);
    IlvColor*		getChartColor(IliChartColor) const;
    
    void		setChartColorName(IliChartColor, const char*);
    const char*		getChartColorName(IliChartColor) const;
    
    void		setDefaultChart(const char*);
    const char*		getDefaultChart() const;
    
    void		setInteraction(IliDbChartInteraction, IlBoolean);
    IlBoolean		getInteraction(IliDbChartInteraction) const;
    
    void		setFilterValue(IliFilterValue);
    IliFilterValue	getFilterValue() const;
    
    //---- Scales -----
    void		setScaleType(IliScaleType);
    IliScaleType	getScaleType() const;
    
    void		setVerticalStepsCount(IlInt);
    IlInt		getVerticalStepsCount() const;
    
    void		showGrid(IlvDirection, IlBoolean);
    IlBoolean		isShowingGrid(IlvDirection) const;
    
    void		setScaleY(IliMinMaxScale, IlBoolean, IlDouble = 0.0);
    IlDouble		getScaleY(IliMinMaxScale) const;
    IlBoolean		isScaleYFixed(IliMinMaxScale) const;
    
    void		setFormatY(const IliFormat&);
    const IliFormat&	getFormatY() const;
    void		formatValue(IliString&, IlFloat) const;
    
    void		showBottomScaleLabels(IlBoolean);
    IlBoolean		isShowingBottomScaleLabels() const;
    void		showLegend(IlBoolean);
    IlBoolean		isShowingLegend() const;
    
    //---- Zoom ----
    void		setZoomSize(IlInt size);
    IlInt		getZoomSize() const;
    IlInt		getZoomRealSize() const;
    
    void		setZoomPosition(IlInt from);
    IlInt		getZoomPosition() const;
    IlInt		getZoomRealPosition() const;
    
    void		setZoomType(IliZoomType);
    IliZoomType		getZoomType() const;
    
    //---- Columns ----
    IlBoolean		setSeriesColumnName(const char*);
    IlBoolean		setAxisXColumnName(const char*);
    IlBoolean		addValuesColumnName(const char*);
    
    IlBoolean		isSeriesColumnName(const char*) const;
    IlBoolean		isAxisXColumnName(const char*) const;
    IlBoolean		isValuesColumnName(const char*) const;
    
    const char*		getSeriesColumnName() const;
    const char*		getAxisXColumnName() const;
    const char*		getValuesColumnName(IlInt index = 0) const;
    
    IlInt		getSeriesColumnIndex() const;
    IlInt		getAxisXColumnIndex() const;
    IlInt		getValuesColumnIndex(IlInt index = 0) const;
    
    IlInt		getValuesColumnsCount() const;
    void		removeAllValuesColumns();
    
    void		computeColumnsIndex();
    
    //---- Data source ----
    void		setDataSource(const IliDataSource*);
    IliDataSource*	getDataSource() const;
    void		setDataSourceName(const char*);
    const char*		getDataSourceName() const;
    IliTable*		getTable() const;
    
    //---- Mapping ----
    void		setMappingSeriesDsName(const char*);
    void		setMappingSeriesDs(const IliDataSource*);
    IlBoolean		hasMappingSeries() const;
    IlBoolean		isValidMappingSeries() const;
    IliTable*		getMappingSeriesTable() const;
    
    void		setMappingXValueDsName(const char*);
    void		setMappingXValueDs(const IliDataSource*);
    IlBoolean		hasMappingXValue() const;
    IlBoolean		isValidMappingXValue() const;
    IliTable*		getMappingXValueTable() const;
    
    //---- Other ----
    IlBoolean		isLoadWithData() const;
    
    void		thereIsNewSeries();
    void		thereIsNotNewSeries();
    IlBoolean		isThereNewSeries() const;
    
    virtual void	makeCopyFrom(IliDbChartDefinition*, IlBoolean);
    
    void		setChartHook(IliDbChartHook*);
    IliDbChartHook*	getChartHook() const;
    
protected:
    IliDbChartHook*	_chartHook;
    
    //---- Data sources ----
    IliDataSource*	_dataSource;
    IliString		_dataSourceName;
    
    //---- Mapping ----
    IliDataSource*	_dsSeries;
    IliString		_dsNameSeries;
    IliDataSource*	_dsXValue;
    IliString		_dsNameXValue;
    
    //---- Columns ----
    IliString		_seriesColumnName;
    IliString		_axisXColumnName;
    IliString*		_valuesColumnsName;
    IlInt		_seriesColumn;
    IlInt		_axisXColumn;
    IlInt*		_valuesColumns;
    IlInt		_valuesColumnsCount;
    
    //---- X values ----
    IlInt		_xCount;
    IliString**		_xValues;
    IliString**		_xLabels;
    IlBoolean		_sortedX;
    IlBoolean		_numericX;
    
    //---- Series ----
    IlBoolean		_hasNewSeries;
    IlInt		_seriesCount;
    IliDbChartSeries**	_series;
    
    
    IlBoolean		_writeData;
    
    IlBoolean		_showLegend;
    IlBoolean		_showBottomScale;
    IliFilterValue	_filterValues;
    
    IlBoolean		_autoSelect;
    
    IliFormat		_formatAxisY;
    
    IlBoolean		_extractDataByColumn;
    IliString		_defaultChart;
    
    IlDouble		_scaleMinMaxY[IliMinMaxScaleNbTag];
    IlBoolean		_useMinMaxScaleY[IliMinMaxScaleNbTag];
    IliScaleType	_scaleType;
    
    IlvDisplay*		_display;
    
    IlInt		_useGrid;
    IlInt		_nbVerticalSteps;
    
    IlInt		_useDynamic;
    
    IliString		_colorsChart[IliChartColorNbTag];
    
    IlInt		_refCount;
    
    //---- Zoom ----
    IlInt		_zoomSize;
    IlInt		_zoomPosition;
    IliZoomType		_zoomType;
};

// --------------------------------------------------------------------------
// IliDbChartContainer
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliDbChartContainer : public IlvChartContainer
{
public:
    IliDbChartContainer(IlvCompositeAbstractView*, const IlvRect&);
    IliDbChartContainer(IlvCompositeAbstractView*,
			const IlvRect&,
			IliDbChartDefinition*);
    IliDbChartContainer(IlvDisplay*, const char*, const IlvRect&);
    ~IliDbChartContainer();
    void		init();
    
    //---- Definition ----
    void		setChartDefinition(IliDbChartDefinition*);
    IliDbChartDefinition* getChartDefinition() const;
    
    //---- Scales -----
    virtual void	validate(IlFloat&, IlFloat&, IlFloat&, IlFloat&);
    virtual void	updateScaleLabels(IlvPosition) const;
    virtual void	beforeDraw(IlvPort*,
				   const IlvTransformer*,
				   const IlvRegion*);
    IlUShort		computeLeftScaleLabels(char**) const;
    IlUShort		computeBottomScaleLabels(char**) const;
    
    //---- Refresh ----
    void		waitRefresh();
    void		dontWaitRefresh();
    IlBoolean		isRefreshWaited() const;
    void		refreshAll(IlInt = -1,
				   IlBoolean = IlTrue,
				   IlBoolean = IlFalse);
    void		onlyDataModified(IlInt col = -1);
    void		refreshDisplay(IlInt);
    void		deleteAllCharts();
    void		compressSeries();
    
    //---- Scroll bar ----
    virtual void	setAttachment();
    void		computeBBox(IlvRect& h, const IlvTransformer* t);
    IlvScrollBar*	getScrollBar() { return _scroll; }
    void		scrollValueChanged();
    void		adjustScrollBar();
    
    IlBoolean		isAdjustScroll() const;
    void		adjustScroll();
    void		dontAdjustScroll();
    
    //---- Displayer ----
    IlvChart*		createNewChart(IlInt, IliDbChartSeries*);
    void		createMultiChart(IliDbChartSeries*);
    void		removeDisplayerForSeries(IliDbChartSeries*);
    void		computeSpacingMultiChart();
    
    //---- Events ----
    void		setChartHook(IliDbChartHook*);
    
    virtual void	setHook();
    virtual void	removeHook();
    
    virtual void	startOfBatch();
    virtual void	endOfBatch();
    virtual void	tableDeleted();
    virtual void	tableChanged();
    virtual void	columnChanged(IlInt);
    virtual void	rowInserted(IlInt);
    virtual void	rowToBeChanged(IlInt);
    virtual void	rowChanged(IlInt);
    virtual void	rowToBeDeleted(IlInt);
    virtual void	rowDeleted(IlInt);
    virtual void	rowMoved(IlInt, IlInt);
    virtual void	rowsExchanged(IlInt, IlInt);
    virtual void	rowsInserted(IlInt, IlInt);
    virtual void	rowsFetched(IlInt, IlInt);
    virtual void	cellChanged(IlInt, IlInt);
    
    // ---- Data source ----
    void		setDataSource(const IliDataSource*);
    IliDataSource*	getDataSource();
    
    //---- Chart type ----
    static IlInt	GetNbDynCharts();
    static const char*	GetClassDynChartByIndex(IlInt);
    static const char*	GetLabelDynChartByIndex(IlInt);
    static IlBoolean	IsMultiChartRegister(const char*);
    static IliChartMissingValue GetChartMissingValueType(const char*);
    static IlInt	GetChartIndexOfClassName(const char*);
    static IlBoolean	RegisterDynChart(const char*,
					 const char*,
					 IliCreateChartCallback,
					 IliChartMissingValue = IliChartMissingRepeat);
    static IlBoolean	RegisterDynMultiChart(const char*,
					      const char*,
					      IliCreateMultiCallback,
					      IliComputeSizeCallback = 0,
					      IliChartMissingValue = IliChartMissingRepeat);
    
    //---- Other ----
    void		makeCopyFrom(IliDbChartDefinition*, IlBoolean);
    
    static void		AtInit();
    static void		AtExit();
protected:
    IliChartTableHook*		_chartTableHook;
    IliDbChartDefinition*	_chartDef;
    IlvMultiChart*		_multiChart;
    IlvScrollBar*		_scroll;
    IlBoolean			_adjustScroll;
    
    //---- Refresh ----
    IlBoolean			_waitRefresh;
    IlBoolean			_refreshVScale;
    IlBoolean			_refreshHScale;
    IlBoolean			_refreshLegend;
    
    //---- protected functions ----
    IlBoolean		isValidColumn(IlInt col);
    
    friend class IliModuleCLASS(IliDbChartContainer);
    IlInt		getSpacingX();
    
    void		buildScroll();
};

//----

IliModuleDECL_exp(ILV_DBCHART_EXPORTED, IliDbChartContainer);

#ifdef ILI_COMPAT_PREFIX
#define IlvSwChartMissingValue		IliChartMissingValue
#define IlvSwChartMissingRepeat		IliChartMissingRepeat
#define IlvSwChartMissingPutZero	IliChartMissingPutZero
#define IlvSwChartMissingNbTag		IliChartMissingNbTag
#define IlvSwChartColor			IliChartColor
#define IlvSwChartBackground		IliChartBackground
#define IlvSwChartColorScale		IliChartColorScale
#define IlvSwChartColorGrid		IliChartColorGrid
#define IlvSwChartColorNbTag		IliChartColorNbTag
#define IlvSwZoomType			IliZoomType
#define IlvSwZoomAllPoints		IliZoomAllPoints
#define IlvSwZoomLastPoints		IliZoomLastPoints
#define IlvSwZoomCursor			IliZoomCursor
#define IlvSwZoomNbTag			IliZoomNbTag
#define IlvSwScaleType			IliScaleType
#define IlvSwScaleTypeNormal		IliScaleTypeNormal
#define IlvSwScaleTypeAdjusted		IliScaleTypeAdjusted
#define IlvSwScaleTypeExpansed		IliScaleTypeExpansed
#define IlvSwScaleTypeNbTag		IliScaleTypeNbTag
#define IlvSwSeriesInfo			IliSeriesInfo
#define IlvSwSeriesInfoName		IliSeriesInfoName
#define IlvSwSeriesInfoChart		IliSeriesInfoChart
#define IlvSwSeriesInfoColor		IliSeriesInfoColor
#define IlvSwSeriesInfoNbTag		IliSeriesInfoNbTag
#define IlvSwFilterValue		IliFilterValue
#define IlvSwFilterValueFirst		IliFilterValueFirst
#define IlvSwFilterValueLast		IliFilterValueLast
#define IlvSwFilterValueBiggest		IliFilterValueBiggest
#define IlvSwFilterValueSmallest	IliFilterValueSmallest
#define IlvSwFilterValueSum		IliFilterValueSum
#define IlvSwFilterValueAverage		IliFilterValueAverage
#define IlvSwFilterValueNbTag		IliFilterValueNbTag
#define IlvSwDbChartInteraction		IliDbChartInteraction
#define IlvSwDataSourceToDbChart	IliDataSourceToDbChart
#define IlvSwDbChartToDataSource	IliDbChartToDataSource
#define IlvSwMinMaxScale		IliMinMaxScale
#define IlvSwMinScale			IliMinScale
#define IlvSwMaxScale			IliMaxScale
#define IlvSwMinMaxScaleNbTag		IliMinMaxScaleNbTag
#define IlvSwDbChartDefinition		IliDbChartDefinition
#define IlvSwDbChartSeries		IliDbChartSeries
#define IlvSwCreateChartCallback	IliCreateChartCallback
#define IlvSwCreateMultiCallback	IliCreateMultiCallback
#define IlvSwComputeSizeCallback	IliComputeSizeCallback
#define IlvSwChartDataBar		IliChartData
#define IlvSwChartDataLine		IliChartDataLine
#define IlvSwChartHook			IliChartTableHook
#define IlvSwDbChartSeries		IliDbChartSeries
#define IlvSwDbChartDefinition		IliDbChartDefinition
#define IlvSwDbChartContainer		IliDbChartContainer
#endif

#endif 






