// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dialogs/sqlappdg.h
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
// Declaration of the IliSQLApplicationPropertiesPanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Sqlappdg_H
#define __Ili_Sqlappdg_H

#ifndef __Ilv_Gadgets_Idialog_H
#  include <ilviews/gadgets/idialog.h>
#endif

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Gadgets_Notebook_H
#  include <ilviews/gadgets/notebook.h>
#endif

#ifndef __Ilv_Graphics_Relfline_H
#  include <ilviews/graphics/relfline.h>
#endif

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ilv_Gadgets_Textfd_H
#  include <ilviews/gadgets/textfd.h>
#endif

#ifndef __Ilv_Optmenu_H
#  include <ilviews/gadgets/optmenu.h>
#endif

#ifndef __Ilv_Gadgets_Frame_H
#  include <ilviews/gadgets/frame.h>
#endif

#ifndef __Ilv_Msglabel_H
#  include <ilviews/gadgets/msglabel.h>
#endif

#ifndef __Ilv_Graphics_Selector_H
#  include <ilviews/graphics/selector.h>
#endif

#ifndef __Ilv_Gadgets_Toggle_H
#  include <ilviews/gadgets/toggle.h>
#endif

#ifndef __IlvSt_Studio_H
#  include <ivstudio/studio.h>
#endif

#ifndef __IlvSt_Panel_H
#  include <ivstudio/panel.h>
#endif

#ifndef __Ili_Tablegad_H
#  include <ilviews/dataccess/gadgets/tablegad.h>
#endif

#ifndef __Ili_Strtable_H
#  include <ilviews/dataccess/strtable.h>
#endif

#ifndef __Ili_Inspgad_H
#  include <ilviews/dataccess/inspect/inspgad.h>
#endif

#ifndef __Ili_Sqlprop_H
#  include <ilviews/dataccess/dbstudio/sqlprop.h>
#endif

// --------------------------------------------------------------------------
// IliSQLApplicationPropertiesPanel
// --------------------------------------------------------------------------
class ILV_DBSSQL_EXPORTED IliSQLApplicationPropertiesPanel
  : public IlvStDialog {
public:
  IliSQLApplicationPropertiesPanel (IlvStudio*);
  ~IliSQLApplicationPropertiesPanel ();

  virtual void show();
  virtual void apply ();
  virtual void cancel ();
  virtual void reset ();

  IlBoolean validate (IlBoolean interactive = IlTrue);
  void resetTitle ();

  static void ReadDbmsOptionsTable (IlvStudio* studio,IliStringsTable* tbl,
				    IlBoolean normalized);
  static void SetDefaultDbmsOptions (IlvStudio* studio);

  IlBoolean isSQLEnabled() const;
  void enableSQL();

protected:
  IliSQLApplicationProperties _app;
  IlvNotebook* _notebook;
  IliTable* _sessions;
  IliTableGadget* _tgSessions;
  IliInspectorGadget* _tgDbmsOptions;
  IlBoolean _titleModified;

  IliString _sessionsPageTitle;
  IliString _sessionsPageFileName;
  IliString _dbmsPageTitle;
  IliString _dbmsPageFileName;

  void initSessionsPart();
  void initDbmsPart();

  IlvGraphic* getNotebookGraphic (IlInt pageIndex,const char* name) const;

  void readSessions ();
  void writeSessions ();
  void readDbmsOptions ();
  void writeDbmsOptions ();

  IlBoolean isModified () const;
};

#endif
