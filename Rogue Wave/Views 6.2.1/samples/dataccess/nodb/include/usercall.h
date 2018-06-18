// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/include/usercall.h
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
// Define global user callback in IlvGadgetContainer and load/save a table
// --------------------------------------------------------------------------

#ifndef __Sample_Usercall_H__
#define __Sample_Usercall_H__

#include <ilviews/dataccess/gadgets/dbfield.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/dataccess/gadgets/dbnavig.h>
#include <ilviews/dataccess/gadgets/entryfld.h>
#include <ilviews/dataccess/gadgets/mdatasrc.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/filesel.h>
#include <ilviews/gadgets/gadcont.h>

#include <app.h>

enum DialogId
{
  DlgSave = 0,
  DlgLoad,
  NbDialog
};

// --------------------------------------------------------------------------
// Panel class for sample UserCall
// --------------------------------------------------------------------------
class UserCall 
  : public PageNoteBook
{
public:
  UserCall(IlvAbstractView* view, const char* filename);
  ~UserCall();
  void initUserCall();
  
  inline IlvIFileSelector* getFileDialog(DialogId);
protected:
  IlvIFileSelector* _pFileDialog[NbDialog];
};

inline IlvIFileSelector*
UserCall::getFileDialog (DialogId id) {
  return _pFileDialog[id];
}

#endif /* !__Sample_Usercall_H__*/
