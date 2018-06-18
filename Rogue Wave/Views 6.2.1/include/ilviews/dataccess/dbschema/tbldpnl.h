// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbschema/tbldpnl.h
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
// Declaration of the IliSQLTableDefPanel class
// Declaration of the IliSQLTableEditPanel class
// Defined in library dbschema
// --------------------------------------------------------------------------
#ifndef __Ili_Tbldpnl_H
#define __Ili_Tbldpnl_H

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Gadgets_Idialog_H
#  include <ilviews/gadgets/idialog.h>
#endif

#ifndef __Ilv_Msglabel_H
#  include <ilviews/gadgets/msglabel.h>
#endif

#ifndef __Ilv_Gadgets_Notebook_H
#  include <ilviews/gadgets/notebook.h>
#endif

#ifndef __Ilv_Gadgets_Textfd_H
#  include <ilviews/gadgets/textfd.h>
#endif

#ifndef __Ili_Tbldef_H
#  include <ilviews/dataccess/tbldef.h>
#endif

#ifndef __Ili_Tblref_H
#  include <ilviews/dataccess/tblref.h>
#endif

#ifndef __Ili_Typetag_H
#  include <ilviews/dataccess/typetag.h>
#endif

#ifndef __Ili_Session_H
#  include <ilviews/dataccess/dbms/session.h>
#endif

#ifndef __Ili_Mdatasrc_H
#  include <ilviews/dataccess/gadgets/mdatasrc.h>
#endif

#ifndef __Ili_Sqldtsrc_H
#  include <ilviews/dataccess/gadgets/sqldtsrc.h>
#endif

#ifndef __Ili_Tablegad_H
#  include <ilviews/dataccess/gadgets/tablegad.h>
#endif

// --------------------------------------------------------------------------
// IliSQLTableDefPanel
// --------------------------------------------------------------------------
class IliSQLTableDefPanel : public IlvDialog {
public:
  IliSQLTableDefPanel (IlvDisplay*, IlvView*);

  virtual void apply ();

  IlBoolean inspect (IliSQLTableDef*);

protected:
  IlvView* _view;
  IliSQLTableDef* _tblDef;

  const char* getStr (const char* fld) const;
  void setStr (const char* fld, const char* str);
};

// --------------------------------------------------------------------------
// IliSQLTableEditPanel
// --------------------------------------------------------------------------
class IliSQLTableEditPanel : public IlvDialog {
public:
  IliSQLTableEditPanel (IlvDisplay*, IlvView*);
  ~IliSQLTableEditPanel();

  IlBoolean editTable (IliSQLTableRef&,IliSQLSession*);

  void comboChanged();
  void initialize();

protected:
  IlvView* _view;
  IliTableGadget* _tblGadget;
  IliScrolledComboBox* _combo;
};

#endif
