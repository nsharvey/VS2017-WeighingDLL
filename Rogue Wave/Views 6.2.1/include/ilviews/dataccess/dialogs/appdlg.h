// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dialogs/appdlg.h
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
// Declaration of the IliApplicationPropertiesPanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Appdlg_H
#define __Ili_Appdlg_H

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

#ifndef __Ili_Appprop_H
#  include <ilviews/dataccess/dbstudio/appprop.h>
#endif

// --------------------------------------------------------------------------
// IliApplicationPropertiesPanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliApplicationPropertiesPanel
  : public IlvStDialog {
public:
  IliApplicationPropertiesPanel (IlvStudio*);
  ~IliApplicationPropertiesPanel ();

  virtual void apply ();
  virtual void cancel ();
  virtual void reset ();

  IlBoolean validate (IlBoolean interactive = IlTrue);
  void resetTitle ();

  void onFocusOutCallback ();
  void onPrimaryCallback ();

protected:
  IliApplicationProperties _app;
  IlvNotebook* _notebook;
  IliTable* _formats;
  IliTableGadget* _tgFormats;
  IliTable* _masks;
  IliTableGadget* _tgMasks;
  IlBoolean _titleModified;

  char _decimalPoint;
  char _thousandsSeparator;
  IliString _currencySymbol;
  IlInt _currencyPosition;
  IlBoolean _isMDY;
  char _dateSeparator;
  char _timeSeparator;

  IlvGraphic* getNotebookGraphic (IlInt pageIndex,const char* name) const;
  const char* getTextLabel (IlInt pageIndex,const char* name) const;
  void setTextLabel (IlInt pageIndex,const char* name,const char* value);
  IlInt getOption (IlInt pageIndex,const char* name) const;
  void setOption (IlInt pageIndex,const char* name,IlInt);
  IlInt getSelectorIndex (IlInt pageIndex,const char* name) const;
  void setSelectorIndex (IlInt pageIndex,const char* name,IlInt);
  void setFocusOutCallback (IlInt pageIndex,const char* name,
			    IlvGraphicCallback);
  void setPrimaryCallback (IlInt pageIndex,const char* name,
			   IlvGraphicCallback);

  void readFormats ();
  void writeFormats ();
  void readMasks ();
  void writeMasks ();
  void readNumbers ();
  void writeNumbers ();
  void readDates ();
  void writeDates ();

  IlBoolean isModified () const;
  IlBoolean areNumbersModified () const;
  IlBoolean areDatesModified () const;
};

#endif
