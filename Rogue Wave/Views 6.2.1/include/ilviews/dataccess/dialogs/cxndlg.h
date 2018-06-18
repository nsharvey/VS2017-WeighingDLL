// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dialogs/cxndlg.h
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
// Declaration of the IliSQLConnectionDialog class
// Defined in library dbaccess
// --------------------------------------------------------------------------
#ifndef __Ili_Cxndlg_H
#define __Ili_Cxndlg_H

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ilv_Msglabel_H
#  include <ilviews/gadgets/msglabel.h>
#endif

#ifndef __Ilv_Passwded_H
#  include <ilviews/gadgets/passwded.h>
#endif

#ifndef __Ilv_Graphics_Relfline_H
#  include <ilviews/graphics/relfline.h>
#endif

#ifndef __Ilv_Gadgets_Textfd_H
#  include <ilviews/gadgets/textfd.h>
#endif

#ifndef __Ilv_Gadgets_Toggle_H
#  include <ilviews/gadgets/toggle.h>
#endif

#ifndef __Ilv_Gadgets_Scombo_H
#  include <ilviews/gadgets/scombo.h>
#endif

#ifndef __Ilv_Gadgets_Textfd_H
#  include <ilviews/gadgets/textfd.h>
#endif

#ifndef __Ilv_Gadgets_Idialog_H
#  include <ilviews/gadgets/idialog.h>
#endif

#ifndef __Ili_Session_H
#  include <ilviews/dataccess/dbms/session.h>
#endif

class ILV_DBI_EXPORTED IliSQLConnectionDialog
  : public IlvDialog {
public:
  IliSQLConnectionDialog (IlvDisplay* dpy,const char* title,
			  IlvAbstractView* view = 0);

  IlBoolean queryConnect (IliSQLSession*, IlBoolean connectP);

  IlBoolean isShowingName () const;
  void showName (IlBoolean f);

  IlBoolean isLimitedToPassword () const;
  void limitToPassword (IlBoolean);

  virtual void apply ();

  void onDbms ();
  void onName ();

protected:
  IliSQLSession* _session;
  IlBoolean _connectP;
  IlBoolean _limitedToPassword;
  IlBoolean _isCustom;
  IlInt _dbmsCount;
  struct {
    IlvGraphic* label;
    IlvGraphic* textfd;
    IlBoolean shown;
  } _fields[10];
  IlvGraphic* _keepPwd;
  IlvPos _dy;
  IlvPos _xLabel;
  IlvPos _xTextfd;
  IlvPos _yFirst;
  IlvAbstractView* _view;
  IliString _customText;

  void fillNamesCombo (IliSQLSession*);
  void fillDbmsCombo (IliSQLSession*);
  void reformat ();

  IlvTextField* getTextField (const char* name) const;
  void setTextFieldLabel (const char* name, const char* label);
  const char* getTextFieldLabel (const char* name) const;
  IlBoolean getToggle (const char* name) const;
  void setToggle (const char* name, IlBoolean);
  void showGraphic (IlvGraphic*, IlInt y, IlBoolean sensitive);
  void hideGraphic (IlvGraphic*);
};

#endif
