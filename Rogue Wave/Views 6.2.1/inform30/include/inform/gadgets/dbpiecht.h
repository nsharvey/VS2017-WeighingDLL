// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/gadgets/dbpiecht.h
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
// Declaration of the IliDbPieChart class
// Defined in library dbchart
// --------------------------------------------------------------------------
#ifndef __Ili_Dbpiecht_H
#define __Ili_Dbpiecht_H

#ifndef __Ilv_Base_Error_H
#  include <ilviews/base/error.h>
#endif

#ifndef __Ilv_Graphics_Tooltip_H
#  include <ilviews/graphics/tooltip.h>
#endif

#ifndef __Ilv_Oldchart_Piechart_H
#  include <ilviews/piechart.h>
#endif

#ifndef __Ili_Error_H
#  include <ilviews/dataccess/error.h>
#endif

#ifndef __Ili_Errorrep_H
#  include <ilviews/dataccess/errorrep.h>
#endif

#ifndef __Ilv_Base_Gadget_H
#  include <ilviews/base/gadget.h>
#endif

#ifndef __Ili_Ivalitf_H
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif

#ifndef __Ili_Fielditf_H
#  include <ilviews/dataccess/fielditf.h>
#endif

#ifndef __Ili_Datasrc_H
#  include <ilviews/dataccess/gadgets/datasrc.h>
#endif

#ifndef __Ili_Chartool_H
#  include <../inform30/include/inform/gadgets/chartool.h>
#endif

#ifndef __Ili_Memtable_H
#  include <ilviews/dataccess/memtable.h>
#endif

#ifndef __Ili_Palspec_H
#  include <ilviews/dataccess/palspec.h>
#endif

enum IliDbPieLabelType {
  IliDbPieLabelNothing = 0,
  IliDbPieLabelSeriesName,
  IliDbPieLabelSeriesPercentage,
  IliDbPieLabelSeriesValue,
  IliDbPieLabelValue,
  IliDbPieLabelTypeCount
};

// --------------------------------------------------------------------------
// IliDbPieChartToolTip
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliDbPieChartToolTip : public IlvToolTip
{
public:
  IliDbPieChartToolTip();

  DeclarePropertyInfoRO();
  DeclarePropertyIOConstructors(IliDbPieChartToolTip);

  virtual void init(const IlvView*, const IlvGraphic*, const IlvPoint&);
  virtual void reInit(const IlvView*, const IlvGraphic*, const IlvPoint&);
  virtual void show(IlvView*, IlvRect& rect);
};

// --------------------------------------------------------------------------
// IliDbPieColor
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliDbPieColor
{
public:
  IliDbPieColor() { _name.nullify(); _color = 0; }
  ~IliDbPieColor() {}

  void setName(const char* name) { _name = name; }
  const char* getName() const { return (const char*)_name; }
  IlInt isThisName(const char* name) const { return (_name == name); }

  void setColor(IlvColor* color) { _color = color; }
  IlvColor* getColor() const { return _color; }

  IliDbPieColor& operator=(const IliDbPieColor& o) { return copy(o); }
protected:
  IliString _name;
  IlvColor* _color;

  IliDbPieColor& copy(const IliDbPieColor& o)
  { _name = o._name; _color = o._color; return *this; }
};

// --------------------------------------------------------------------------
// IliDbPieSeries
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliDbPieSeries : public IliDbPieColor
{
public:
  IliDbPieSeries():IliDbPieColor() { init(); }

  void setValue(IlFloat value,IliFilterValueModel*);
  inline void setPercentage(IlInt);
  inline IlFloat getValue() const;
  inline IlInt getValuesCount() const;
  inline IlInt getPercentage() const;
  inline IlInt computePercentage(IlFloat);
  inline void resetCounter();
  inline void setDeclared(IlBoolean dec);
  inline IlBoolean isDeclared() const;

  inline void initFrom(const IliDbPieColor& o);
  inline void operator=(const IliDbPieSeries& o);
protected:
  IlFloat _value;
  IlInt _percentage;
  IlInt _count;
  IlBoolean _declared;

  inline void init();
};

// --------------------------------------------------------------------------
// IliDbPieDefinition
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliDbPieDefinition
{
public:
  IliDbPieDefinition();
  ~IliDbPieDefinition();
  IliDbPieDefinition& operator=(const IliDbPieDefinition&);

  //---- Look ----
  IlBoolean setStart(IlFloat);
  IlFloat getStart() const;
  IlBoolean setRange(IlFloat);
  IlFloat getRange() const;
  IlBoolean setTearOff(const char*);
  const char* getTearOff() const;
  IlBoolean setTearOffDelta(IlvDim);
  IlvDim getTearOffDelta() const;
  IlBoolean setLabelType(IliDbPieLabelType);
  IliDbPieLabelType getLabelType() const;

  //---- Filter ----
  IlBoolean setFilterValues(IliFilterValue);  // OLD
  IliFilterValue getFilterValues() const;      // OLD
  IlBoolean setFilterValueModelName(const char*);
  const char* getFilterValueModelName() const;

  //---- Series ----
  void resetSeries();
  IlInt getSeriesCount() const;
  IlInt getSeriesIndex(const char*) const;
  const char* getSeriesName(IlInt) const;
  IlBoolean setSeriesColor(IlInt,IlvColor*);
  IlvColor* getSeriesColor(IlInt) const;
  IlInt addSeries(IlInt,const char*);
  IlBoolean computeFilterValue();
  void makeDefaultSeries();
  IlBoolean isDeclaredSeries(IlInt) const;
  IlBoolean isTearOff(IlInt) const;
  IlBoolean isDefaultSeries() const;
  IlBoolean isActiveSeries(const char*) const;
  void compressSeries();

  //---- Declared series ----
  IlBoolean declareSeries(const char* name,IlvColor *color);
  const char* getDeclaredSeriesName(IlInt index) const;
  IlvColor* getDeclaredSeriesColor(IlInt index) const;
  IlInt getDeclaredSeriesCount() const;
  void resetDeclaredSeries();
  void installDeclaredSeries();

  //---- Values ----
  void resetCounter();
  void setValue(IlInt,IlFloat);
  IlFloat getValue(IlInt) const;
  IlInt getPercentage(IlInt) const;
  IlInt getValueCount(IlInt) const;
protected:

  //---- Look ----
  IlFloat _start;
  IlFloat _range;
  IliString _tearOff;
  IlvDim _tearOffDelta;
  IliDbPieLabelType _labelType;

  //---- Series ----
  IliDbPieSeries* _series;
  IlInt _seriesCount;
  IlBoolean _defaultSeries;

  //---- declared series ----
  IliDbPieColor* _declaredSeries;
  IlInt _declaredCount;

  //---- Filter ----
  IliFilterValueModel* _filter;
};

// --------------------------------------------------------------------------
// IliDbPieChart
// --------------------------------------------------------------------------
class ILV_DBCHART_EXPORTED IliDbPieChart
  : public IlvGadget, public IliFieldItf
{
public:
  IliDbPieChart (IlvDisplay* display,const IlvRect& rect,
		   IlUShort thickness = IlvDefaultGadgetThickness,
		   IlvPalette* palette = 0);
  virtual ~IliDbPieChart ();
  DeclareTypeInfo();
  DeclareIOConstructors(IliDbPieChart);

  IlvPieChart* getPieChart() const;
  virtual IlvPieChart* getNewPieChart(IlvRect& r, IlvChartDataYPoints* data,
				      IlFloat start,IlFloat range,
				      IlvDim delta) const;
  //---- Table ----
  const IliTable* getTable () const;
  IliTable* getTable ();
  virtual void setTable (IliTable* tbl, IlBoolean owner = IlTrue);
  IlBoolean isTableOwner () const;

  //---- Properties ----
  IlBoolean isReadOnly () const;

  //---- Columns ----
  void setSeriesColumnName(const char* name);
  const char* getSeriesColumnName() const;
  IlInt getSeriesColumnIndex() const;
  void setValuesColumnName(const char* name);
  const char* getValuesColumnName() const;
  IlInt getValuesColumnIndex() const;

  IlBoolean isReallyBoundToDataSource () const;
  IlBoolean isBoundToDataSource () const;
  void bindToDataSource (IlBoolean f);

  //---- refresh ----
  void refreshAll();
  void needRefreshData();
  void needRefreshLook();
  void refreshData();
  void refreshLook();

  void startOfBatch();
  void endOfBatch();

  IlInt getBatchCount() const;

  //---- tooltips ----
  virtual void getToolTipText(const IlvPoint& pt, IliString& s);
  void enableToolTip(IlBoolean flag);
  void enablePaletteToolTip();
  IlBoolean isToolTipEnabled() const;

  inline void setValueFormat(const IliFormat& fmt);
  inline const IliFormat& getValueFormat() const;

  //---- error reporting ----
  void addErrorMessage (const IliErrorMessage& msg);
  void addErrorMessage (const char* msg);
  void addErrorSink (IliErrorSink* sink);
  void removeErrorSink (IliErrorSink* sink);
  IliErrorReporter* getErrorReporter () const;
  void setErrorReporter (IliErrorReporter* reporter);
  void reportErrors (const IliErrorList& errorList) const;

  //---- implements IliFieldItf ----
  virtual IlBoolean f_isConsistent () const;
  virtual void f_internalToExternal ();
  virtual IlBoolean f_externalToInternal ();
  virtual IlBoolean f_complete ();
  virtual IlBoolean f_isReadOnly () const;
  virtual void f_setReadOnly (IlBoolean f);
  virtual const IliValue& f_getValue (IlBoolean internalP = IlFalse) const;
  virtual IlBoolean f_setValue(const IliValue&,IlBoolean internalP = IlFalse);
  virtual IlBoolean f_isInputModified () const;
  virtual void f_setInputModified (IlBoolean f);
  virtual void f_enableAutoReDraw (IlBoolean);
  virtual void f_refresh ();
  virtual IlBoolean f_doConnect ();
  virtual void f_doDisconnect ();
  virtual void f_dataSourceToField (IlInt colno);
  virtual void f_fieldToDataSource (IlInt colno);
  virtual IlBoolean f_isColumnModified (IlInt colno) const;

  //---- filter ----
  void setFilterValues(IliFilterValue filter);   // OLD
  IliFilterValue getFilterValues() const; // OLD
  void setFilterValueModelName(const char* filter);
  const char* getFilterValueModelName() const;

  //---- overrides ----

  virtual void draw(IlvPort* dst, const IlvTransformer* t=0,
		    const IlvRegion* clip = 0) const;
  virtual void computeFocusRegion (IlvRegion&, const IlvTransformer*) const;
  virtual void drawFocus(IlvPort*, const IlvPalette*, const IlvTransformer*,
			 const IlvRegion*) const;

  virtual IlBoolean zoomable() const;
  void apply (IlvApplyObject, IlAny);
  void applyReferences (IlvApplyObject, IlAny);

  virtual void setHolder (IlvGadgetHolder* holder);

  void fetchMoreRows ();

  virtual void tableChanged ();
  virtual void tableDeleted ();
  virtual void columnInserted (IlInt colno);
  virtual void columnChanged (IlInt colno);
  virtual void columnToBeDeleted (IlInt colno);
  virtual void columnDeleted (IlInt colno);
  virtual void columnMoved (IlInt src, IlInt dest);

  virtual void rowInserted (IlInt rowno);
  virtual void rowToBeChanged (IlInt rowno);
  virtual void rowChanged (IlInt rowno);
  virtual void rowToBeDeleted (IlInt rowno);
  virtual void rowDeleted (IlInt rowno);
  virtual void rowMoved (IlInt src, IlInt dest);
  virtual void rowFetched (IlInt rowno);
  virtual void rowsExchanged (IlInt row1, IlInt row2);
  virtual void rowsInserted(IlInt row1, IlInt row2);
  virtual void rowsFetched(IlInt row1, IlInt row2);

  virtual void columnCellsChanged (IlInt colno);
  virtual void cellChanged (IlInt rowno, IlInt colno);

  //---- draw ----
  virtual void setBackground (IlvColor*);
  virtual void setForeground (IlvColor*);
  virtual void setFont (IlvFont*);
  virtual void setMode (IlvDrawMode);
  virtual void setOverwrite (IlBoolean);
  virtual void setPalette (IlvPalette*);

  void adjustTableBuffer ();

  //---- Declared series ----
  void declareSeries(const char* name,IlvColor *color);
  const char* getDeclaredSeriesName(IlInt index) const;
  IlvColor* getDeclaredSeriesColor(IlInt index) const;
  IlInt getDeclaredSeriesCount() const;
  void resetDeclaredSeries();

  //---- series ----
  IlInt getSeriesIndex(const char* name) const;
  void invalidateSeries();

  virtual void resetSeries();
  virtual IlBoolean makeSeries();
  virtual IlInt indexForNewSeries(const char*);
  virtual IlInt addSeries(const char*,IlInt = -1);

  void setSeriesValue(IlInt, IlFloat);
  IlFloat getSeriesValue(IlInt) const;

  virtual IlInt getSeriesCount() const;
  virtual IlvGraphic* getSeriesLabel(IlInt index) const;
  virtual IlvColor* computeNextColor(IlInt index);
  void setSeriesColor(IlInt index,IlvColor*);
  IlvColor* getSeriesColor(IlInt index) const;

  //---- other ----
  void setAutoSelect(IlBoolean autoSelect);
  IlBoolean isAutoSelect() const;

  //---- Look ----
  void setStart(IlFloat start);
  IlFloat getStart() const;
  void setRange(IlFloat range);
  IlFloat getRange() const;
  void setTearOff(const char* name);
  const char* getTearOff() const;
  void setTearOffDelta(IlvDim dim);
  IlvDim getTearOffDelta() const;
  void setLabelType(IliDbPieLabelType type);
  IliDbPieLabelType getLabelType() const;

  //---- accessors ----

  virtual IlBoolean getValueDescriptor(IlvValue& value) const;
  virtual IlvValue&  queryValue(IlvValue& value) const;
  virtual IlBoolean applyValue(const IlvValue& value);
  static  void GetAccessors(const IlvSymbol* const** accessors,
                            const IlvValueTypeClass* const** types,
                            IlUInt& count);
  virtual IlBoolean f_supportsAccessor(IliFieldAccessorTag) const;
  static  IlBoolean F_supportsAccessor(IliFieldAccessorTag);

protected:
  IliDbPieDefinition _pieDef;
  IlvPieChart* _pieChart;

  //---- Refresh ----
  IlInt _batchCount;
  IlBoolean _inEndOfBatch;
  IlBoolean _needRefreshData;
  IlBoolean _needRefreshLook;

  //---- datasource
  IlBoolean _autoSelect;
  IlBoolean _isBoundToDataSource;
  IlBoolean _tableOwner;

  IliTable* _table;
  IliTableBuffer* _tableBuffer;
  IliTableBuffer* _tableBuffInfo;
  IliTableHook* _tableHook;

  IliString _seriesColumnName;
  IliString _valuesColumnName;

  IliDbPieChartToolTip* _pieToolTip;
  IlBoolean _toolTipEnabled;
  IlBoolean _paletteToolTip;
  IliFormat  _valueFormat;

  IlvList _errorSinks;
  IliErrorReporter* _errorReporter;
  IliErrorSink* _dsErrorSink;

  void initPieChart(IliTable* table, IlBoolean initTable = IlTrue);

  //---- tools ----
  IlBoolean isColumnUsed(IlInt) const;

  void installToolTip(IlBoolean);
  IlBoolean isToolTipInstalled() const;
private:
  IlvColor* _firstColor;
  IlvColor* _previousColor;
  IlInt _refColor;

  void columnHasBeenChanged(IlInt);
};

inline void
IliDbPieSeries::initFrom(const IliDbPieColor& o) {
  copy(o);
  init();
}

inline void
IliDbPieSeries::operator=(const IliDbPieSeries& o) {
  copy(o);
  _value = o._value;
  _percentage = o._percentage;
  _count = o._count;
  _declared = o._declared;
}

inline void
IliDbPieSeries::init() {
  _value = (IlFloat)0.0;
  _percentage = 0;
  _count = 0;
  _declared = IlFalse;
}

inline IlFloat
IliDbPieSeries::getValue() const {
  return _value;
}

inline IlInt
IliDbPieSeries::getValuesCount() const {
  return _count;
}

inline IlInt
IliDbPieSeries::getPercentage() const {
  return _percentage;
}

inline void
IliDbPieSeries::setPercentage(IlInt p) {
  _percentage = p;
}

inline IlInt
IliDbPieSeries::computePercentage(IlFloat total) {
  IlFloat v = (total && _count)? _value / total : (IlFloat)(0.0);
  _percentage = (IlInt)(v * 1000.0);
  return _percentage;
}

inline void
IliDbPieSeries::resetCounter() {
  _value = (IlFloat)0.0;
  _percentage = 0;
  _count = 0;
}

inline void
IliDbPieSeries::setDeclared(IlBoolean dec) {
  _declared = dec;
}

inline IlBoolean
IliDbPieSeries::isDeclared() const {
  return _declared;
}

inline void
IliDbPieChart::setValueFormat(const IliFormat& form) {
  _valueFormat = form;
}

inline const IliFormat&
IliDbPieChart::getValueFormat() const {
  return _valueFormat;
}

IlvDeclareEnumTypeClass(ILV_DBCHART_EXPORTED,FilterValue);
IlvDeclareEnumTypeClass(ILV_DBCHART_EXPORTED,DbPieLabelType);

IliModuleDECL_exp(ILV_DBCHART_EXPORTED,FilterValue);
IliModuleDECL_exp(ILV_DBCHART_EXPORTED,DbPieLabelType);
IliModuleDECL_exp(ILV_DBCHART_EXPORTED,IliDbPieChart);

#ifdef ILI_COMPAT_PREFIX
#define IlvSwDbPieLabelType IliDbPieLabelType
#define IlvSwDbPieColor IliDbPieColor
#define IlvSwDbPieSeries IliDbPieSeries
#define IlvSwDbPieDefinition IliDbPieDefinition
#define IlvSwDbPieChartToolTip IliDbPieChartToolTip
#define IlvSwDbPieChart IliDbPieChart
#endif

#endif 












