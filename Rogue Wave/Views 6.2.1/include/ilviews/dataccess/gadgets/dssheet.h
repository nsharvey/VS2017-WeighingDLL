// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dssheet.h
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
// Declaration of the IliDataSourceSheet class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dssheet_H
#define __Ili_Dssheet_H

#ifndef __Ilv_Gadgets_Hsheet_H
#  include <ilviews/gadgets/hsheet.h>
#endif

#ifndef __Ilv_Gadgets_Scombo_H
#  include <ilviews/gadgets/scombo.h>
#endif

#ifndef __Ilv_Gadgets_Menu_H
#  include <ilviews/gadgets/menu.h>
#endif

#ifndef __Ili_Dsusage_H
#  include <ilviews/dataccess/gadgets/dsusage.h>
#endif

#ifndef __Ili_Gdtmodel_H
#  include <ilviews/dataccess/gadgets/gdtmodel.h>
#endif

#ifndef __Ili_Memtable_H
#  include <ilviews/dataccess/memtable.h>
#endif

#ifndef __Ili_Strtable_H
#  include <ilviews/dataccess/strtable.h>
#endif

class IliSheetItem;

// --------------------------------------------------------------------------
// IliDataSourceSheet
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDataSourceSheet : public IlvHierarchicalSheet
{
public:
    IliDataSourceSheet(IlvDisplay* d, const IlvRect& rect,
		       IlvDim thickness = IlvDefaultGadgetThickness,
		       IlvPalette* palette = 0);
    virtual ~IliDataSourceSheet();

    void		initSheet();

    DeclareTypeInfo();
    DeclareIOConstructors(IliDataSourceSheet);

    //---- Data model ----
    void		setDataModelName(const char* name);
    const char*		getDataModelName() const;
    IliMappingInspectorModel* getDataModel() const;

    //---- Refresh ----
    void		refreshAll();
    void		refreshDataSources();
    void		refreshColumns(IlInt dsi, IlvTreeGadgetItem* parent);
    void		refreshAddDataSource(IlInt dsi, IlInt at = -1);
    void		refreshAddColumn(IlInt dsi,
					 IlInt col,
					 IlvTreeGadgetItem* parent,
					 IlInt at = -1);
    void		refreshDeleteColumn(IlInt dsi,
					    IlInt col,
					    IlvTreeGadgetItem* item);
    void		refreshDeleteDataSource(IlInt dsi,
						IlvTreeGadgetItem* item);

    //---- Holders -----
    virtual void	setHolder(IlvGraphicHolder*);

    //---- Data sources holder ----
    void		setDataSourcesHolder(IlvGraphicHolder*);
    IlvGraphicHolder*	getDataSourcesHolder() const;

    //---- Event ----
    void		handleAddItem(IliSheetItem*);
    void		handleDeleteItem(IliSheetItem*);
    void		handleRightButton(const IlvPoint&, IliSheetItem*);

    //---- From IlvMatrix ----
    virtual void	validate();
    virtual IlBoolean	handleMatrixEvent(IlvEvent&);
    virtual
    IlvTextField*	createEditionField(IlUShort c, IlUShort r);

    //---- Popup Menu ----
    IliSheetItem*	getPopupSheetItem() const;

protected:
    //---- Data Model ----
    IliMappingInspectorModel* _dataModel;

    //---- Data sources holder ----
    IlvGraphicHolder*	_dsHolder;

    //---- Popup Menu ----
    IliSheetItem*	_popupSheetItem;

    //---- Computing ----
    void		computeDataSourceList(IliStringsTable*);
    void		computeColumnList(IliStringsTable*, IliSheetItem*);

    //---- Popup Menu ----
    void		addPopupItem(IlvPopupMenu*,
				     const char* label,
				     IlvGraphicCallback cb);
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliDataSourceSheet);

#endif
