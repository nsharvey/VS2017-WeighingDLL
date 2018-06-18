// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/inspect/dbslstpn.h
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
#ifndef __Ili_Compat_Dbslstpn_H
#define __Ili_Compat_Dbslstpn_H

#include <../inform30/include/inform/macros.h>

#include <ilviews/dataccess/inspect/dbslstpn.h>

// --------------------------------------------------------------------------
// IliDbStringListPanel
// --------------------------------------------------------------------------
class ILV_STINFORM30_EXPORTED IliDbOldStringListPanel
  : public IlvStIListPanel {
public:
  IliDbOldStringListPanel(IlvDisplay*,IlvSystemView transientFor = 0);
  ~IliDbOldStringListPanel();

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
};

#ifdef ILI_COMPAT_PREFIX
#define IlvSwDbStringListPanel IliDbOldStringListPanel
#define IlvSwDbStringListPropTag IliDbOldStringListPropTag
#endif

#endif
