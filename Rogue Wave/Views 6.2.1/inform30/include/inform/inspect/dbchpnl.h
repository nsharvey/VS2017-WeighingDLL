// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/inspect/dbchpnl.h
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
// Definition of the IliDbChartInspector class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbchpnl_H
#define __Ili_Dbchpnl_H

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ilv_Contain_Contain_H
#  include <ilviews/contain/contain.h>
#endif

#ifndef __Ilv_Gadgets_Frame_H
#  include <ilviews/gadgets/frame.h>
#endif

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Graphics_Holder_H
#  include <ilviews/graphics/holder.h>
#endif

#ifndef __Ilv_Base_Hash_H
#  include <ilviews/base/hash.h>
#endif

#ifndef __Ilv_Manager_Manager_H
#  include <ilviews/manager/manager.h>
#endif

#ifndef __Ilv_Base_Message_H
#  include <ilviews/base/message.h>
#endif

#ifndef __Ilv_Manager_Holder_H
#  include <ilviews/manager/holder.h>
#endif

#ifndef __Ilv_Msglabel_H
#  include <ilviews/gadgets/msglabel.h>
#endif

#ifndef __Ilv_Gadgets_Notebook_H
#  include <ilviews/gadgets/notebook.h>
#endif

#ifndef __Ili_Datatype_H
#  include <ilviews/dataccess/datatype.h>
#endif

#ifndef __Ili_Maptable_H
#  include <ilviews/dataccess/maptable.h>
#endif

#ifndef __Ili_Memtable_H
#  include <ilviews/dataccess/memtable.h>
#endif

#ifndef __Ili_Reposit_H
#  include <ilviews/dataccess/reposit.h>
#endif

#ifndef __Ili_Util_H
#  include <ilviews/dataccess/util.h>
#endif

#ifndef __Ili_Clrcombo_H
#  include <ilviews/dataccess/gadgets/clrcombo.h>
#endif

#ifndef __Ili_Datasrc_H
#  include <ilviews/dataccess/gadgets/datasrc.h>
#endif

#ifndef __Ili_Dbchart_H
#  include <../inform30/include/inform/gadgets/dbchart.h>
#endif

#ifndef __Ili_Dbfield_H
#  include <ilviews/dataccess/gadgets/dbfield.h>
#endif

#ifndef __Ili_Dbtoggle_H
#  include <ilviews/dataccess/gadgets/dbtoggle.h>
#endif

#ifndef __Ili_Entryfld_H
#  include <ilviews/dataccess/gadgets/entryfld.h>
#endif

#ifndef __Ili_Mdatasrc_H
#  include <ilviews/dataccess/gadgets/mdatasrc.h>
#endif

#ifndef __Ili_Tablegad_H
#  include <ilviews/dataccess/gadgets/tablegad.h>
#endif

#ifndef __Ili_Tblcombo_H
#  include <ilviews/dataccess/gadgets/tblcombo.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

enum IliDbChartPage {
    IliDbChartDataPage = 0,
    IliDbChartSeriesPage,
    IliDbChartLookPage,
    IliDbChartDisplayPage,
    IliDbChartPageCount
};

// --------------------------------------------------------------------------
// IliDbChartPanel
// --------------------------------------------------------------------------
class ILV_DBSCHART_EXPORTED IliDbChartPanel : public IliInspectorBook
{
public:
    IliDbChartPanel(IlvDisplay* display, IlvSystemView transientFor = 0);
    ~IliDbChartPanel();
    
    virtual void	pagesDefine();
    virtual void	pageInit(IlInt);
    virtual void	pageInitFrom (IlInt, IlvGraphic*);
    virtual IlBoolean	pageValidate(IlInt);
    virtual void	pageApply (IlInt, IlvGraphic*);
    virtual void	pageCustomGeneralPage(IlInt);
    
    //---- Data ----
    IliDeclInspBookAccess(IliDbToggle, DataCHKDynDs, 0, "CHKDynDs");
    IliDeclInspBookAccess(IliDbToggle, DataCHKNotSerie, 0, "CHKNotSerie");
    IliDeclInspBookAccess(IliDbToggle, DataCHKAutoSelect, 0, "CHKAutoSelect");
    IliDeclInspBookAccess(IlvMessageLabel, DataTXTSerie, 0, "TXTSerie");
    IliDeclInspBookAccess(IliTableComboBox,
			  DataCBNDataSource,
			  0,
			  "CBNDataSource");
    IliDeclInspBookAccess(IliMemoryDataSource, DataCOLUMN, 0, "%COLUMN_MS");
    IliDeclInspBookAccess(IliMemoryDataSource, DataCOMBO, 0, "%COMBO_MS");
    IliDeclInspBookAccess(IliMemoryDataSource, DataAXE, 0, "%AXE_MS");
    IliDeclInspBookAccess(IliDbToggle, DataCHKAxisX, 0, "CHKAxisX");
    IliDeclInspBookAccess(IliTableComboBox,
			  DataCBNDualValue,
			  0,
			  "CBNDualValue");
    IliDeclInspBookAccess(IliTableGadget, DataTBLColumn, 0, "TBLColumn");
    
    //---- Series ----
    IliDeclInspBookAccess(IliMemoryDataSource,
			  SeriesDISPLAY,
			  1,
			  "%DISPLAY_MS");
    IliDeclInspBookAccess(IliMemoryDataSource, SeriesGRAPH, 1, "%GRAPH_MS");
    IliDeclInspBookAccess(IliMemoryDataSource, SeriesMISS, 1, "MISS_MS");
    IliDeclInspBookAccess(IliDbToggle, SeriesCHKAllCharts, 1, "CHKAllCharts");
    IliDeclInspBookAccess(IliTableGadget, SeriesTBLChart, 1, "TBLChart");
    IliDeclInspBookAccess(IliDbField, SeriesCBNDef, 1, "CBNDef");
    
    //---- Look ----
    IliDeclInspBookAccess(IliDbToggle, LookCHKGridVerti, 2, "CHKGridVerti");
    IliDeclInspBookAccess(IliDbToggle, LookCHKGridHoriz, 2, "CHKGridHoriz");
    IliDeclInspBookAccess(IliMemoryDataSource, LookCOLOR, 2, "%COLOR_MS");
    IliDeclInspBookAccess(IliTableGadget, LookTBLColor, 2, "TBLColor");
    IliDeclInspBookAccess(IliTableComboBox, LookCBNScale, 2, "CBNScale");
    IliDeclInspBookAccess(IliTableComboBox, LookCBNSteps, 2, "CBNSteps");
    IliDeclInspBookAccess(IliTableComboBox, LookCBNTypeFrom, 2, "CBNTypeFrom");
    IliDeclInspBookAccess(IliTableComboBox, LookCBNFormat, 2, "CBNFormat");
    IliDeclInspBookAccess(IliDbToggle, LookCHKUseMinY, 2, "CHKUseMinY");
    IliDeclInspBookAccess(IliDbToggle, LookCHKUseMaxY, 2, "CHKUseMaxY");
    IliDeclInspBookAccess(IliEntryField, LookEDTMinY, 2, "EDTMinY");
    IliDeclInspBookAccess(IliEntryField, LookEDTMaxY, 2, "EDTMaxY");
    IliDeclInspBookAccess(IliEntryField, LookEDTNbPoints, 2, "EDTNbPoints");
    
    //---- Display ----
    IliDeclInspBookAccess(IliDbToggle,
			  DispCHKBottomScale,
			  3,
			  "CHKBottomScale");
    IliDeclInspBookAccess(IliDbToggle, DispCHKLegend, 3, "CHKLegend");
    
    //---- Other ----
    inline void		setReturnData(IliDbChartDefinition*);
    inline void		setBeginModifyCharts();
    inline void		setEndModifyCharts();
    inline IlBoolean	isModifyCharts();
    void		setDbChart(IliDbChart*);
    void		comboIsClosed(IlBoolean = IlTrue);
    void		fillComboDataSource();
    
    void		newUserAxisChoice(IlBoolean = IlFalse);
    void		newDataOrganizeChoice(IlBoolean = IlTrue);
    void		buildAllSeries();
    void		buildSeriesFromColumnSeries();
    void		buildSeriesFromColumnValues(IlInt num, IlInt);
    
    void		chartSelected(const char*);
    void		initTableGadget(IliTableGadget*, IlInt);
    
protected:
    void		initBookData();
    void		initBookSeries();
    void		initBookLook();
    void		initBookDisplay();
    
    void		initFromBookData();
    void		initFromBookSeries();
    void		initFromBookLook();
    void		initFromBookDisplay();
    
    IlBoolean		validateBookData();
    IlBoolean		validateBookSeries();
    IlBoolean		validateBookLook();
    IlBoolean		validateBookDisplay();
    
    IlBoolean		isSameDataSource(const char*);
    const char*		getFormattedValue(IlInt, const char*);
    inline const char*	getSeriesColumnName() const;
    inline const char*	getAxisXColumnName() const;
    inline const char*	getValuesColumnName(IlInt index = 0) const;
    IlBoolean		validate(char*);
    
    inline IliTable*	getTable();
    
private:
    IliDataSource*		_ds;
    IliDbChart*			_chart;
    IlStringHashTable*		_hshTable;
    IliDbChartDefinition*	_data;
    IlBoolean			_modifiedCharts;
    
    IliTgFocusControler		_focusCtrl[IliDbChartPageCount];
};

inline void
IliDbChartPanel::setBeginModifyCharts()
{
    _modifiedCharts = IlTrue;
}

inline void
IliDbChartPanel::setEndModifyCharts()
{
    _modifiedCharts = IlFalse;
}

inline IlBoolean
IliDbChartPanel::isModifyCharts()
{
    return _modifiedCharts;
}

inline IliTable*
IliDbChartPanel::getTable()
{
    return (_ds) ? _ds->getTable() : 0;
}

inline const char*
IliDbChartPanel::getSeriesColumnName() const
{
    return _data->getSeriesColumnName();
}

inline const char*
IliDbChartPanel::getAxisXColumnName() const
{
    return _data->getAxisXColumnName();
}

inline const char*
IliDbChartPanel::getValuesColumnName(IlInt index) const
{
    return _data->getValuesColumnName(index);
}

#ifdef ILI_COMPAT_PREFIX
#define IlvSwDbChartPanel IliDbChartPanel
#endif

#endif 









