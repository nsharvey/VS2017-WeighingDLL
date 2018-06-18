// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/chartgraphic.h
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
// Declaration of the IliChartGraphic class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Chartgraphic_H
#define __Ili_Chartgraphic_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifdef IL_STD
#  include <fstream>
#else
#  include <fstream.h>
#endif

#ifndef __Ilv_Base_View_H
#  include <ilviews/base/view.h>
#endif
#ifndef __Ilv_Charts_Chartinc_H
#  include <ilviews/charts/chartinc.h>
#endif
#ifndef __Ili_Chartmodel_H
#  include <ilviews/dataccess/gadgets/chartmodel.h>
#endif

enum IliChartModelType {
    IliChartDataModelType = 0,
    IliChartSeriesModelType,
    IliChartModelTypeCount
};

// --------------------------------------------------------------------------
// IliChartMapper
// --------------------------------------------------------------------------
class ILV_DACHART_EXPORTED IliChartMapper
{
public:
    inline
    IliChartMapper(IlInt r = 0, IlDouble d = 0.0) 
	: _rowno(r), _x(d), _previous(0), _next(0) {}
    IliChartMapper(const IliChartMapper& o)
	: _rowno(o._rowno), _x(o._x), _previous(0), _next(0) {}

    inline void		setPrevious(IliChartMapper* n) { _previous = n; }
    inline
    IliChartMapper*	getPrevious() const { return _previous; }

    inline void		setNext(IliChartMapper* n) { _next = n; }
    inline
    IliChartMapper*	getNext() const { return _next; }

    inline void		setRow(IlInt r) { _rowno = r; }
    inline IlInt	getRow() const { return _rowno; }

    inline void		setXValue(IlDouble x) { _x = x; }
    inline IlDouble	getXValue() const { return _x; }

    inline IlInt operator>(const IliChartMapper& m) const
			{
			    return (_x > m._x) ? 1 : 0;
			}

protected:
    //---- Information ----
    IlInt		_rowno;
    IlDouble		_x;

    //---- Link ----
    IliChartMapper*	_previous;
    IliChartMapper*	_next;
};

// --------------------------------------------------------------------------
// IliDataSetIdentifier
// --------------------------------------------------------------------------
class ILV_DACHART_EXPORTED IliDataSetIdentifier
{
public:
    IliDataSetIdentifier();

    //---- Operators ----
    const IliDataSetIdentifier& operator=(const IliDataSetIdentifier&);
    IlInt operator==(const IliDataSetIdentifier&) const;

    //---- Properties ----
    void		setSeriesName(const IliString&);
    const IliString&	getSeriesName() const;
    IlBoolean		isThisSeries(const IliString&) const;

    void		setDataSourceIndex(IlInt dsi);
    IlInt		getDataSourceIndex() const;

    void		setPredeclared(IlBoolean);
    IlBoolean		isPredeclared() const;

protected:
    //---- Data Model ----
    IlInt		_dsi;
    IliString		_seriesName;
    IlBoolean		_predeclared;
};

// --------------------------------------------------------------------------
// IliDataSet
// --------------------------------------------------------------------------
class ILV_DACHART_EXPORTED IliDataSet : public IlvChartDataSet
{
public:
    IliDataSet(const IliDataSetIdentifier& id,
	       const char* name = 0,
	       IlvPointInfoCollection* ptInfoCollection = 0);
    virtual ~IliDataSet();

    //---- Data Model ----
    void		setDataModel(IliChartDataModel*);
    IliChartDataModel*	getDataModel() const;

    //---- Properties ----
    void		setIdentifier(const IliDataSetIdentifier&);
    const IliDataSetIdentifier& getIdentifier() const;

    void		setSeriesName(const char*);
    void		setDataSourceIndex(IlInt);

    //---- Points ----
    virtual IlBoolean	isIncreasingOnX() const;
    virtual IlUInt	getDataCount() const;

    virtual void	getPoint(IlUInt i,IlvDoublePoint& point) const;
    virtual IlBoolean	setPoint(IlUInt pointIndex,
				 const IlvDoublePoint& point);
    virtual IlBoolean	insertPoint(const IlvDoublePoint& point,
				    IlUInt pointIndex,
				    IlvChartDataPointInfo* pointInfo = 0,
				    IlBoolean copyPointInfo = IlFalse);
    virtual IlBoolean	removePointAndInfo(IlUInt pointIndex);
    virtual void	removePointsAndInfo();

    DeclareChartDataSetTypeInfo(IliDataSet);

    //---- Value ----
    void		beginEditValue();
    void		endEditValue();
    void		resetValues();
    IlInt		addValue(IlDouble x,IlInt rowno);
    void		replaceValue(IlInt rold,IlInt rnew);
    void		moveValue(IlInt from,IlInt to);
    void		insertValue(IlDouble x,IlInt rowno);
    IlInt		removeValue(IlInt rowno);
    IlInt		getValueIndex(IlInt rowno) const;

    //---- Other ----
    void		updateBoundingBoxValues();
    IlInt		getRow(IlInt) const;

protected:
    //---- Value ----
    IliChartMapper*	_mappers;
    IlInt		_mappingCount;

    //---- Data Model ----
    IliDataSetIdentifier _dataSetId;
    IliChartDataModel*	_dataModel;
};

// --------------------------------------------------------------------------
// IliChartGraphic
// --------------------------------------------------------------------------
class ILV_DACHART_EXPORTED IliChartGraphic
: public IlvChartGraphic
{
public:
    IliChartGraphic(IlvDisplay* display,
		    const IlvRect& bbox,
		    IlvPalette* palette = 0);
    virtual ~IliChartGraphic();

    void		init();

    DeclareTypeInfo();
    DeclareIOConstructors(IliChartGraphic);

    //---- Data Source ----
    void		setDataSourceCount(IlInt count);

    IlInt		getDataSourceCount() const;

    void		setDataSourceName(const char* name,IlInt index = 0);

    const char*		getDataSourceName(IlInt index = 0) const;

    void		setDataSource(IliDataSource* ds,IlInt index = 0);

    IliDataSource*	getDataSource(IlInt index = 0);

    void		addColumnName(const char* name,IlInt dsi = 0);
    void		setColumnName(const char* name,
				      IlInt pos,
				      IlInt dsi = 0);
    const char*		getColumnName(IlInt pos, IlInt dsi = 0) const;
    IlInt		getColumnIndex(IlInt pos, IlInt dsi = 0) const;

    void		setColumnCount(IlInt count, IlInt dsi = 0) const;
    IlInt		getColumnCount(IlInt dsi = 0) const;

    IliTableBuffer*	getBufferInfo(IlInt dsi) const;

    IliDsUsageDeclareFctConnectDirect();

    //---- Refresh ----
    void		refreshAll();
    void		startOfBatch();
    void		endOfBatch();
    IlInt		getBatchCount() const;
    IlBoolean		isBatchMode() const;

    //---- Data Model ----
    void		setDataModelName(const char* name);
    const char*		getDataModelName() const;

    IliChartDataModel*	getDataModel() const;

    //---- Properties ----

    IlInt		getModelPropertyCount(IliChartModelType type) const;
    IlInt		getModelPropertyIndex(IliChartModelType type,
					      const char* name) const;
    const char*		getModelPropertyName(IliChartModelType type,
					     IlInt index) const;
    const IliValue&	getModelPropertyValue(IliChartModelType type,
					      const char* name) const;
    const IliValue&	getModelPropertyValue(IliChartModelType type,
					      IlInt index) const;
    void		setModelPropertyValue(IliChartModelType type,
					      const char* name,
					      const IliValue& val);
    void		setModelPropertyValue(IliChartModelType type,
					      IlInt index,
					      const IliValue& val);
    void		copyModelProperties(IliChartModelType type,
					    IliPropertiesManager&) const;

    //---- Series Model ----
    void		setSeriesModelName(const char* name);
    const char*		getSeriesModelName() const;

    IliChartSeriesModel* getSeriesModel() const;

    //---- Default displayer ----
    void		setDefaultDisplayer(IlvAbstractChartDisplayer* disp);
    IlvAbstractChartDisplayer* getDefaultDisplayer() const;

    //---- Holder ----
    virtual void	setHolder (IlvGraphicHolder*);

    //---- Error reporting ----
    void		addErrorSink(IliErrorSink* sink);
    void		removeErrorSink(IliErrorSink* sink);
    void		setErrorReporter(IliErrorReporter* reporter);
    IliErrorReporter*	getErrorReporter() const;
    void		reportErrors(const IliErrorList& errList) const;

    //---- Accessors ----
    virtual IlvValue&	queryValue(IlvValue& value) const;
    virtual IlBoolean	applyValue(const IlvValue& value);
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    static  void	GetAccessors(const IlvSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count);
protected:
    //---- Properties ----
    IliPropertiesManager _props[IliChartModelTypeCount];

    //---- Data Model ----
    IliChartDataModel* _dataModel;

    //---- Series Model ----
    IliChartSeriesModel* _seriesModel;

    //---- Data source and columns ----
    IliListDataSourceUsage* _ds;

    //---- Default Displayer ----
    IlvAbstractChartDisplayer* _defDisplayer;

    //---- Refresh ----
    IlBoolean		_inEndOfBatch;
    IlBoolean		_needRefresh;
    IlInt		_batchCount;

    void		initScales(IlBoolean useGrid, IlvPalette* gridPalette);
};

IliModuleDECL_exp(ILV_DACHART_EXPORTED,IliChartGraphic);

#endif



