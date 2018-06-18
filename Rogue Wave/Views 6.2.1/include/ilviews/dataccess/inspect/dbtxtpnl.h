// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/dbtxtpnl.h
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
// Declaration of the IliDbTextPanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbtxtpnl_H
#define __Ili_Dbtxtpnl_H

#ifndef __IlvSt_Txtpanel_H
#  include <ivstudio/gadgets/txtpanel.h>
#endif

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Gadmgr_Gadmgr_H
#  include <ilviews/gadmgr/gadmgr.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

class ILV_DBS_EXPORTED IliDbTextPanel:
  public IlvStITextPanel {
public:
  IliDbTextPanel (IlvDisplay*, IlvSystemView transientFor = 0);
  ~IliDbTextPanel();

  virtual void initializeEditors();
  virtual void initFrom(IlvGraphic*);
  virtual void applyChange(IlvGraphic*);

  virtual void defineProps ();
  virtual void doApplyChange (IlvGraphic*);
  virtual void doInitFrom (IlvGraphic*);

  void setModified();
private:
  IliNotebookUsage* _nt;
  IliDbGadgetPanel* _insp;
};

#endif
