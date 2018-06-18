// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/gadgets/dbchart.h
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
// Definition of the IliDbChart class
// Defined in library dbchart
// --------------------------------------------------------------------------
#ifndef __Ili_Dbchart_H
#define __Ili_Dbchart_H

#ifndef __Ilv_Graphics_Rectview_H
#include <ilviews/graphics/rectview.h>
#endif

#ifndef __Ili_Table_H
#  include <ilviews/dataccess/table.h>
#endif

#ifndef __Ili_Ivalitf_H
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif

#ifndef __Ili_Fielditf_H
#  include <ilviews/dataccess/fielditf.h>
#endif

#ifndef __Ili_Palspec_H
#  include <ilviews/dataccess/palspec.h>
#endif

#ifndef __Ili_Dbchartc_H
#include <../inform30/include/inform/gadgets/dbchartc.h>
#endif

#ifndef __Ili_Dsusage_H
#include <ilviews/dataccess/gadgets/dsusage.h>
#endif

enum IliDbChartMappingColumn {
  IliDbChartValueColumn = 0,
  IliDbChartDisplayColumn,
  IliDbChartColumnCount
};

// --------------------------------------------------------------------------
// IliDbChart
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliDbChart
  : public IlvViewRectangle,
    public IliFieldItf
{
public:
  IliDbChart(IlvDisplay* display, const IlvRect& rect);
  ~IliDbChart();

  DeclareTypeInfo();
  DeclareIOConstructors(IliDbChart);

  // ---- API ----
  void setChartHook(IliDbChartHook* obj);
  IliDbChartHook* getChartHook() const;

  virtual IliDbChartDefinition* getNewChartDefinition();
  virtual IliDbChartContainer* getNewChartContainer(IlvAbstractView*,
						    const IlvRect&  size,
						    IliDbChartDefinition*);
  virtual IliDbChartContainer* getNewChartContainerForEditMode(IlvDisplay*,
							       const char*,
							       const IlvRect&);

  //---- Series ----
  IlInt getSeriesCount() const;
  void setSeriesCount(IlInt count);

  void defineSeries(IlInt index,const char* name, const char* label,
		    const char* chart, IlvColor* color,
		    IliChartMissingValue miss);

  IlBoolean addSeries(const char*,IlInt& num);
  IlInt getSeriesIndex(const char*) const; // OLD
  IlInt getSeriesPosition(const char* name) const;

  const char* getSeriesName(IlInt index) const;

  const char* getSeriesLabel(IlInt index) const;

  const char* getSeriesChart(IlInt index) const;

  IlvColor* getSeriesColor(IlInt index) const;

  void setSeriesColor(IlInt,IlvColor*);

  IliChartMissingValue getSeriesMissingValue(IlInt index) const;

  //---- Data ----
  void extractDataByColumn(IlBoolean byColumn);

  IlBoolean isDataExtractedByColumn() const;

  void setAutoSelect(IlBoolean autoSelect);

  IlBoolean isAutoSelect() const;

  void reset(IlBoolean columns = IlTrue);

  void resetX();

  void resetValues();

  IlInt getXValueCount() const;

  IlInt getXValuePosition(const char* name) const;

  const char* getXValue(IlInt index) const;

  const char* getXValueLabel(IlInt index) const;

  void addXValue(const char* value);

  //---- Obsolete Functions -----
  void defineSeries(IlInt, const char*, const char*, IlvColor*);
  IlInt getValuesCount() const;
  IlFloat* getValues(IlInt, IlInt = 0);
  const char* getX(IlInt) const; // OLD
  void addX(const char*); // OLD
  void computeFilterValue();

  void allocValues();

  void setValue(const char* series, const char* x, IlFloat value);

  void computeFromDataSource();

  void enableWriteData(IlBoolean);
  IlBoolean isWriteDataEnabled() const;

  //---- Properties ----
  void setChartColor(IliChartColor index, IlvColor* color);

  IlvColor* getChartColor(IliChartColor index) const;

  void setInteraction(IliDbChartInteraction typ, IlBoolean active);

  IlBoolean getInteraction(IliDbChartInteraction typ) const;

  void setFilterValue(IliFilterValue filter);

  IliFilterValue getFilterValue() const;

  void setDefaultChart(const char* cl);

  const char* getDefaultChart() const;

  //---- Scales ----
  void setScaleType(IliScaleType typ);

  IliScaleType getScaleType() const;

  void setVerticalStepsCount(IlInt count);

  IlInt getVerticalStepsCount() const;

  void showGrid(IlvDirection dir, IlBoolean show);

  IlBoolean isShowingGrid(IlvDirection dir) const ;

  void setScaleY(IliMinMaxScale typ, IlBoolean fix, IlDouble val = 0.0);

  IlDouble getScaleY(IliMinMaxScale typ) const;

  IlBoolean isScaleYFixed(IliMinMaxScale typ) const;

  void setFormatY(const IliFormat& fmt);

  const IliFormat& getFormatY() const;

  void formatValue(IliString& dest, IlFloat value) const;

  void showBottomScaleLabels(IlBoolean show);

  IlBoolean isShowingBottomScaleLabels() const;

  void showLegend(IlBoolean flag);

  IlBoolean isShowingLegend() const;

  void sortXAxis(IlBoolean sorted, IlBoolean numeric);

  IlBoolean isXAxisSorted() const;

  IlBoolean isXAxisNumeric() const;

  //---- Zoom ----
  void setZoomSize(IlInt size);

  IlInt getZoomSize() const;
  IlInt getZoomRealSize() const;

  void setZoomPosition(IlInt from);
  IlInt getZoomPosition() const;
  IlInt getZoomRealPosition() const;

  void setZoomType(IliZoomType type);

  IliZoomType getZoomType() const;

  //---- Refresh ----
  void refreshAll(IlInt col = -1, IlBoolean compute = IlTrue);
  void refreshFromScript();

  //---- Columns ----
  IlBoolean setSeriesColumnName(const char* name);

  IlBoolean setAxisXColumnName(const char* name);

  IlBoolean addValuesColumnName(const char* name);

  const char* getSeriesColumnName() const;

  const char* getAxisXColumnName() const;

  const char* getValuesColumnName(IlInt index = 0) const;

  IlInt getValuesColumnsCount() const;

  void removeAllValuesColumns();

  //---- Data source ----
  void setDataSource(const IliDataSource* ds);

  IliDataSource* getDataSource() const;

  //---- Mapping ----
  IliSingleDsUsageDeclareDSAccess(Series);
  IliSingleDsUsageDeclareDSAccess(XValue);

  IliDsUsageDeclareFctConnect(series);
  IliDsUsageDeclareFctConnect(xvalue);

  IliDsUsageDeclareBatch(series);
  IliDsUsageDeclareBatch(xvalue);

  //---- Information ----
  IliDbChartDefinition* getChartDefinition() const;
  void setChartDefinition(IliDbChartDefinition*);

  //---- overloads IlvChartContainer ----
  void setAttachment();

  //---- overloads IlvViewRectangle ----
  virtual void drawContents(IlvPort*, const IlvRect&,const IlvRegion*) const;
  virtual IlvView* createView(IlvAbstractView*,const IlvRect&);

  //---- implements IliFieldItf ----
  virtual void f_refresh ();
  virtual IlBoolean f_isReadOnly () const;
  virtual void f_setReadOnly (IlBoolean);

  //---- overloads IlvGraphic ----
  virtual void setHolder (IlvGraphicHolder*);

  //---- Rogue Wave Script ----
  virtual IlBoolean getValueDescriptor(IlvValue& value) const;
  virtual IlvValue&  queryValue(IlvValue& value) const;
  virtual IlBoolean applyValue(const IlvValue& value);
  static  void GetAccessors(const IlvSymbol* const** accessors,
			    const IlvValueTypeClass* const** types,
			    IlUInt& count);
  virtual IlBoolean f_supportsAccessor(IliFieldAccessorTag) const;
  static  IlBoolean F_supportsAccessor(IliFieldAccessorTag);

  //---- Inspector ----
  void applyFromInspector(IliDbChartDefinition*);

  //---- Register chart ----
  static IlBoolean RegisterDynChart(const char* name, const char* cl,
				     IliCreateChartCallback cb,
				     IliChartMissingValue miss = IliChartMissingRepeat);
  static IlBoolean RegisterDynMultiChart(const char* name, const char* cl,
					  IliCreateMultiCallback cb,
					  IliComputeSizeCallback scb= 0,
					  IliChartMissingValue miss = IliChartMissingRepeat);
protected:
  IlvGraphicHolder*       _holderChart;
  IliDbChartDefinition* _chartDef;
  IlBoolean              _readOnly;
  IlBoolean              _writeData;
  IlUInt                 _batchCount;
  IlBoolean              _refreshRequested;
  IlBoolean              _initFromConstructor;
  IliDbChartContainer*  _chartSelection;

  //---- Mapping ----
  IliSingleDataSourceUsage* _dsSeries;
  IliSingleDataSourceUsage* _dsXValue;
  IlInt _batchCountSeries;
  IlInt _batchCountXValue;

  void init ();
  void startOfBatch ();
  void endOfBatch ();
  void refreshValues ();
  void createChartSelection(const IlvRect&);
  virtual IlBoolean f_doConnect ();
  virtual void f_doDisconnect ();
};

IliSingleDsUsageCodeDSAccess(IliDbChart,Series,_dsSeries)
IliSingleDsUsageCodeDSAccess(IliDbChart,XValue,_dsXValue)

IlvDeclareEnumTypeClass(ILV_DBCHART_EXPORTED,ChartFilterValue);
IlvDeclareEnumTypeClass(ILV_DBCHART_EXPORTED,ScaleType);
IlvDeclareEnumTypeClass(ILV_DBCHART_EXPORTED,ZoomType);

IliModuleDECL_exp(ILV_DBCHART_EXPORTED,ChartFilterValue);
IliModuleDECL_exp(ILV_DBCHART_EXPORTED,ScaleType);
IliModuleDECL_exp(ILV_DBCHART_EXPORTED,ZoomType);
IliModuleDECL_exp(ILV_DBCHART_EXPORTED,IliDbChart);

#ifdef ILI_COMPAT_PREFIX
#define IlvSwDbChart IliDbChart
#endif

#endif 






