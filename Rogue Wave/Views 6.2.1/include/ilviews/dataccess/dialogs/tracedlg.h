// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dialogs/tracedlg.h
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
// Declaration of the IliSQLTraceDialog class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Tracedlg_H
#define __Ili_Tracedlg_H

#ifndef __Ilv_Gadgets_Idialog_H
#  include <ilviews/gadgets/idialog.h>
#endif

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ilv_Gadgets_Frame_H
#  include <ilviews/gadgets/frame.h>
#endif

#ifndef __Ilv_Ctoggle_H
#  include <ilviews/gadgets/ctoggle.h>
#endif

#ifndef __Ili_Macros_H
#  include <ilviews/dataccess/macros.h>
#endif

class ILV_DBSQLG_EXPORTED IliSQLTraceDialog
  : public IlvDialog {
public:
  IliSQLTraceDialog (IlvDisplay*, IlvAbstractView*);

  virtual void apply ();

  IlBoolean activate ();

  void onEnable ();

protected:
  IlvAbstractView* _view;

  IlvColoredToggle* getEnableToggle ();
  IlvColoredToggle* getConnectToggle ();
  IlvColoredToggle* getCursorsToggle ();
  IlvColoredToggle* getSQLToggle ();

  void enable (IlvGadget*, IlBoolean);
  void check (IlvToggle*, IlBoolean);
  IlBoolean getCheck (IlvToggle*) const;
};

#endif
