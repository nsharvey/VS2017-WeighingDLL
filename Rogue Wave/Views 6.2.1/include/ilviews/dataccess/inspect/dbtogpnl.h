// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/dbtogpnl.h
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
// Declaration of the IliDbTogglePanel class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbtogpnl_H
#define __Ili_Dbtogpnl_H

#ifndef __IlvSt_Butpnl_H
#  include <ivstudio/gadgets/butpnl.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

#ifndef __Ili_Dbtoggle_H
#  include <ilviews/dataccess/gadgets/dbtoggle.h>
#endif

// --------------------------------------------------------------------------
// IliDbTogglePanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliDbTogglePanel:
  public IlvStITogglePanel {
public:
  IliDbTogglePanel (IlvDisplay*, IlvSystemView transientFor = 0);
  ~IliDbTogglePanel ();

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
