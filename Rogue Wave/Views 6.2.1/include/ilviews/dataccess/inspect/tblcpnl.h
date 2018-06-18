// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/tblcpnl.h
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
// Declaration of the IliTableComboBoxPanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Tblcpnl_H
#define __Ili_Tblcpnl_H

#ifndef __IlvSt_Fieldpnl_H
#  include <ivstudio/gadgets/fieldpnl.h>
#endif

#ifndef __IlvSt_Combopnl_H
#  include <ivstudio/gadgets/combopnl.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

#ifndef __Ili_Mdatasrc_H
#  include <ilviews/dataccess/gadgets/mdatasrc.h>
#endif

#ifndef __Ili_Dbsimtog_H
#  include <ilviews/dataccess/gadgets/dbsimtog.h>
#endif

class IliTableComboBoxPanel;

enum PaletteUsageSimpleToggle {
  FillColorSimpleToggle = 0,
  TextColorSimpleToggle,
  PaletteUsageSimpleToggleCount
};

// --------------------------------------------------------------------------
// IliTableColumnsDialog
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliTableColumnsDialog
  : public IlvDialog {
public:
    IliTableColumnsDialog (IlvDisplay* dpy,const char* title,
			   IlvSystemView view = 0);
    ~IliTableColumnsDialog();

    void setTableMapping(IliTable*);
    void select(IliString*);

    virtual void apply ();

protected:
    IliTable* _tableMapping;
    IliString* _listCols;
    IliMemoryDataSource* _ds;
    IliTableGadget* _tg;

    IlInt getDisplayColumnsCount();
    IlInt getDisplayColumns(IliString*);
};

// --------------------------------------------------------------------------
// IliTableColumnsComboBox
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliTableColumnsComboBox
  : public IliDialogComboBox {
public:
  IliTableColumnsComboBox(IlvDisplay* display,const IlvRect& rect,
			  IlUShort thickness = IlvDefaultGadgetThickness,
			  IlvPalette* palette = 0);
  ~IliTableColumnsComboBox ();

  void setPanelComboBox(IliTableComboBoxPanel* pnl,const char* list);

  const char* getTableColumns();

  virtual void onOpen();
  virtual void onApply ();

protected:
  IliString _listCols;
  IliTable* _tableMapping;
  IliTableComboBoxPanel* _panel;

  virtual void onInitDialog ();
  virtual void showDialog (IlBoolean grab);
};

// --------------------------------------------------------------------------
// IliTableComboBoxPanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliTableComboBoxPanel:
  public IlvStITextFieldPanel {
public:
  IliTableComboBoxPanel (IlvDisplay*,IlvSystemView transientFor = 0);
  ~IliTableComboBoxPanel();

  enum IliTblComboPropTag {
    tblc_TblCols = fld_TagsCount,
    tblc_TagsCount
  };

  virtual void initializeEditors();
  virtual void initFrom(IlvGraphic*);
  virtual void applyChange(IlvGraphic*);

  virtual void defineProps();
  virtual void doApplyChange(IlvGraphic*);
  virtual void doInitFrom(IlvGraphic*);
  virtual void beforeInitFrom(IlvGraphic*);

  const char* getTableColumns();
  IliTable* getForeignTable();

  void setModified();
protected:
  IliNotebookUsage* _nt;
  IliDbGadgetPanel* _insp;
  IliDbGadgetPanel* _map;

  IliTableColumnsComboBox* _cbn;
};

// --------------------------------------------------------------------------
// IliScrolledComboBoxPanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliScrolledComboBoxPanel
  : public IlvStIScrolledComboPanel {
public:
  IliScrolledComboBoxPanel(IlvDisplay* display,IlvSystemView transientFor = 0);
  ~IliScrolledComboBoxPanel();

  virtual void initializeEditors();
  virtual void initFrom(IlvGraphic*);
  virtual void applyChange(IlvGraphic*);

  virtual void defineProps ();
  virtual void doApplyChange (IlvGraphic*);
  virtual void doInitFrom (IlvGraphic*);

  void setModified();
protected:
  IliNotebookUsage* _nt;
  IliDbGadgetPanel* _insp;
  IliDbGadgetPanel* _map;
};

#endif
