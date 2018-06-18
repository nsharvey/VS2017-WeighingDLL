// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/chartmodel.h
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
// Declaration of the IliChartDataModel class
// Defined in library dbchart
// --------------------------------------------------------------------------
#ifndef __Ili_Chartmodel_H
#define __Ili_Chartmodel_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifdef IL_STD
#include <fstream>
#else
#include <fstream.h>
#endif

#ifndef __Ilv_Base_View_H
#  include <ilviews/base/view.h>
#endif

#ifndef __Ilv_Charts_Display_H
#  include<ilviews/charts/display.h>
#endif

#ifndef __Ili_Reposit_H
#  include <ilviews/dataccess/reposit.h>
#endif

#ifndef __Ili_Dsusage_H
#  include <ilviews/dataccess/gadgets/dsusage.h>
#endif

#ifndef __Ili_Gdtmodel_H
#  include <ilviews/dataccess/gadgets/gdtmodel.h>
#endif

#ifndef __Ili_Ivalitf_H
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif

class IliChartGraphic;
class IliDataSetIdentifier;

// --------------------------------------------------------------------------
// IliChartDataModel
// --------------------------------------------------------------------------
class ILV_DACHART_EXPORTED IliChartDataModel : public IliGadgetModel
{
public:
    IliChartDataModel();
    virtual ~IliChartDataModel();

    //---- Basic methods ----
    IliDeclareModel();

    //---- Chart ----
    void		setChartGraphic(IliChartGraphic*);
    IliChartGraphic*	getChartGraphic() const;

    //---- Events ----
    virtual IlBoolean	refreshAll();

    //---- Request ----
    virtual IlDouble	readXValue(const IliDataSetIdentifier& id,
				   IlInt rowno) const;
    virtual IlDouble	readYValue(const IliDataSetIdentifier& id,
				   IlInt rowno) const;
    virtual void	deleteXYValue(const IliDataSetIdentifier& id,
				      IlInt rowno) const;
    virtual void	deleteAllXYValues(const IliDataSetIdentifier& id)const;
    virtual void	writeXYValue(const IliDataSetIdentifier& id,
				     IlInt rowno,
				     IlDouble x,
				     IlDouble y) const;
    virtual void	addXYValue(const IliDataSetIdentifier& id,
				   IlDouble x,
				   IlDouble y) const;

    //---- Data Parsing ----
    virtual IlBoolean	isPointsDataSource(IlInt dsi) const;
    virtual IlInt	computeSeriesCount(IlInt dsi,
					   IlInt row,
					   IliTableBuffer* buff) const;
    virtual void	computeSeriesName(IlInt dsi,
					  IlInt row,
					  IlInt index,
					  IliTableBuffer* buff,
					  IliString& series) const;
    virtual IlDouble	computeXValue(IlInt dsi,
				      IlInt row,
				      const IliString& series,
				      IliTableBuffer* buff) const;

    //---- Model ----
    IliDeclareAccessorForModel(IliChartDataModel);

    //---- Mapper ----
    void		startEditSeries(IlInt = -1);
    void		endEditSeries(IlInt = -1);

    void		resetSeries();
    IlInt		getSeriesIndex(const IliDataSetIdentifier&) const;
    IlInt		declareSeries(const IliDataSetIdentifier&);

    void		resetValues(IlInt);
    IlInt		declareValue(IlInt series, IlDouble x, IlInt rowno);

    //---- Data set ----
    void		connectToDataSets();
    void		disconnectToDataSets();

    //---- Other ----
    static void		AtInit();
    static void		AtExit();

    //---- Events Not documented ----
    virtual void	tableDeleted (const IliModelHookInfo& info);
    virtual void	tableChanged (const IliModelHookInfo& info);

    virtual void	columnInserted (const IliModelHookInfo& info);
    virtual void	columnChanged (const IliModelHookInfo& info);
    virtual void	columnToBeDeleted (const IliModelHookInfo& info);
    virtual void	columnDeleted (const IliModelHookInfo& info);
    virtual void	columnMoved (const IliModelHookInfo& info);

    virtual void	allRowsDeleted(const IliModelHookInfo& info);
    virtual void	rowsInserted(const IliModelHookInfo& info);
    virtual void	rowInserted (const IliModelHookInfo& info);
    virtual void	rowToBeChanged (const IliModelHookInfo& info);
    virtual void	rowChanged (const IliModelHookInfo& info);
    virtual void	rowToBeDeleted (const IliModelHookInfo& info);
    virtual void	rowDeleted (const IliModelHookInfo& info);
    virtual void	rowMoved (const IliModelHookInfo& info);
    virtual void	rowsExchanged (const IliModelHookInfo& info);
    virtual void	rowsFetched(const IliModelHookInfo& info);
    virtual void	rowFetched (const IliModelHookInfo& info);
    virtual void	currentRowChanged(const IliModelHookInfo& info);

    virtual void	columnCellsChanged (const IliModelHookInfo& info);
    virtual void	cellChanged (const IliModelHookInfo& info);

protected:
    IliChartGraphic*	_charts;
};

// --------------------------------------------------------------------------
// Macro for IliChartDataModel
// --------------------------------------------------------------------------
#ifdef DOXYGEN_GENERATION
IliRegisterChartDataModel(cl);
#else
#define IliRegisterChartDataModel(cl) \
  IliChartDataModel::RegisterModel(new cl)
#endif

// --------------------------------------------------------------------------
// IliChartSeriesModel
// --------------------------------------------------------------------------
class ILV_DACHART_EXPORTED IliChartSeriesModel : public IliModel
{
public:
    IliChartSeriesModel();
    virtual ~IliChartSeriesModel();

    //---- Basic methods ----
    IliDeclareModel();

    //---- Chart ----
    void		setChartGraphic(IliChartGraphic*);
    IliChartGraphic*	getChartGraphic() const;

    //---- series ----
    virtual const char*
	computeSeriesColor(const IliDataSetIdentifier& id) const;
    virtual IlvAbstractChartDisplayer*
	computeSeriesDisplayer(const IliDataSetIdentifier& id) const;

    //---- Model ----
    IliDeclareAccessorForModel(IliChartSeriesModel);

    //---- Other ----
    static void		AtInit();
    static void		AtExit();

protected:
    //---- Chart ----
    IliChartGraphic*	_charts;
};

// --------------------------------------------------------------------------
// Macro for IliChartSeriesModel
// --------------------------------------------------------------------------
#ifdef DOXYGEN_GENERATION
IliRegisterChartSeriesModel(cl);
#else
#define IliRegisterChartSeriesModel(cl) \
    IliChartSeriesModel::RegisterModel(new cl)
#endif

IliModuleDECL_exp(ILV_DACHART_EXPORTED,IliChartDataModel);

#endif
