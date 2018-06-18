// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dialogs/strdlg.h
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
// Declaration of the IliStringsDialog class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Strdlg_H
#define __Ili_Strdlg_H

#ifndef __Ilv_Gadgets_Idialog_H
#  include <ilviews/gadgets/idialog.h>
#endif

#ifndef __Ili_Strtable_H
#  include <ilviews/dataccess/strtable.h>
#endif

class ILV_DBG_EXPORTED IliStringsDialog
  : public IlvDialog {
public:
  IliStringsDialog (IlvDisplay* dpy,const char* title,
		    IliStringsTable* strings,IlBoolean owner = IlFalse,
		    IlvSystemView transientFor = 0);

  virtual void apply ();

  const IliStringsTable* getStringsTable () const { return _strings; }
  IliStringsTable* getStringsTable () { return _strings; }

protected:
  IliStringsTable* _strings;
};

#endif
