// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/chartpnl.h
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
// Declaration of the IliChartGraphicPanel class
// Defined in library dbstchart
// --------------------------------------------------------------------------
#ifndef __Ili_Chartpnl_H
#define __Ili_Chartpnl_H

#ifndef __IlvSt_Charts_Chartpnl_H
#  include <ivstudio/charts/chartpnl.h>
#endif

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Gadmgr_Gadmgr_H
#  include <ilviews/gadmgr/gadmgr.h>
#endif

#ifndef __Ili_Mdatasrc_H
#  include <ilviews/dataccess/gadgets/mdatasrc.h>
#endif

#ifndef __Ili_Dbtoggle_H
#  include <ilviews/dataccess/gadgets/dbtoggle.h>
#endif

#ifndef __Ili_Dssheet_H
#  include <ilviews/dataccess/gadgets/dssheet.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

class IliChartGraphic;
class IliChartDataModel;

// --------------------------------------------------------------------------
// IliChartGraphicPanel
// --------------------------------------------------------------------------
class ILV_DBSTCHART_EXPORTED IliChartGraphicPanel
  : public IlvStIChartPanel {
public:
  IliChartGraphicPanel(IlvDisplay*,IlvSystemView transientFor = 0);
  ~IliChartGraphicPanel();

  //---- Common ----
  virtual void initializeEditors();
  virtual void initFrom(IlvGraphic* g);
  virtual void applyChange(IlvGraphic* g);

  void initData();

  //---- Specific ----
  void initBookSpecific(IliDbGadgetPanel*);
  void initFromBookSpecific(IliDbGadgetPanel*);
  IlBoolean validateBookSpecific(IliDbGadgetPanel*);

  //---- Data Sources ----
  void initBookDataSources();
  void initDataBookDataSources();
  IlBoolean applyBookDataSources();

  //---- Data model properties ----
  void initBookDataModelProp(IliDbGadgetPanel*);
  void initFromBookDataModelProp(IliDbGadgetPanel*);
  IlBoolean validateBookDataModelProp(IliDbGadgetPanel*);

  //---- Series model properties ----
  void initBookSeriesModelProp(IliDbGadgetPanel*);
  void initFromBookSeriesModelProp(IliDbGadgetPanel*);
  IlBoolean validateBookSeriesModelProp(IliDbGadgetPanel*);

  //---- Default chart ----
  void initBookDefaultChart();
  void initDataBookDefaultChart();
  IlBoolean applyBookDefaultChart();

  //---- event ----
  void setModified();
  void newModel(IlBoolean fromCombo = IlTrue);

  //---- Tools ----
  IliChartGraphic* getChartGraphicGadget() const { return _chart; }
  IliDeclNotebookAccess(_nt,IliDataSourceSheet,DsSheet,1,"DsSheet"); 
  void initializePropertiesModel(const IliModel* mod,IliPropertiesManager& mgr,
				 IlInt page);
  void modelHasChanged(IliInspectorGadget* insp);

protected:
  //---- Common ----
  IliNotebookUsage* _nt;
  IliChartGraphic* _chart;

  //---- Specific ----
  IliDbGadgetPanel* _inspSpecific;
  IlInt _dataModel;
  IlInt _seriesModel;

  //---- Data Sources ----

  //---- Data model properties ----
  IliDbGadgetPanel* _inspPropData;
  IliPropertiesManager _propsData;

  //---- Series model properties ----
  IliDbGadgetPanel* _inspPropSeries;
  IliPropertiesManager _propsSeries;

  //---- Default chart ----
};

#endif
