// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/dbslstpn.h
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
// Declaration of the IliDbStringListInspector class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Dbslstpn_H
#define __Ili_Dbslstpn_H

#ifndef __IlvSt_Lispanel_H
#  include <ivstudio/gadgets/lispanel.h>
#endif

#ifndef __Ili_Dbstrlst_H
#  include <ilviews/dataccess/gadgets/dbstrlst.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

// --------------------------------------------------------------------------
// IliDbStringListPanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliDbStringListPanel
  : public IlvStIListPanel {
public:
  IliDbStringListPanel(IlvDisplay*,IlvSystemView transientFor = 0);
  ~IliDbStringListPanel();

  enum IliStringlistPropTag {
    strFlag_ColumnBitmap = fld_TagsCount,
    strFlag_TagsCount
  };

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
