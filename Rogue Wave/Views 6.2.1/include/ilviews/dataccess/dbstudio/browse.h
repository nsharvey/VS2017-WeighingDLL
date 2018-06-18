// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbstudio/browse.h
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
// Declaration of the IliBrowse class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Browse_H
#define __Ili_Browse_H

#ifndef __Ilv_Base_View_H
#  include <ilviews/base/view.h>
#endif

#ifndef __Ilv_Manager_Manager_H
#  include <ilviews/manager/manager.h>
#endif

#include <ilviews/gadgets/gadcont.h>

#ifndef __IlvSt_Studio_H
#  include <ivstudio/studio.h>
#endif

#ifndef __IlvSt_Panel_H
#  include <ivstudio/panel.h>
#endif

#ifndef __Ilv_Gadgets_Notebook_H
#  include <ilviews/gadgets/notebook.h>
#endif

#ifndef __Ilv_Gadgets_Colorch_H
#  include <ilviews/gadgets/colorch.h>
#endif

#ifndef __Ilv_Gadgets_Fontsel_H
#  include <ilviews/gadgets/fontsel.h>
#endif

#ifndef __Ili_Repview_H
#  include <ilviews/dataccess/gadgets/repview.h>
#endif

// --------------------------------------------------------------------------
// IliDlgBrowsePage
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliDlgBrowsePage : public IlvGadgetContainer
{
public:
  IliDlgBrowsePage(IlvAbstractView* parent,const char* file);

  virtual void refresh();
  virtual void filterOn(IliRepositFilterOn);
  virtual IlvGraphicHolder* getSelectedHolder() const;
};

// --------------------------------------------------------------------------
// IliBrowserPanel
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliBrowserPanel : public IlvStDialog 
{
public:
  IliBrowserPanel (IlvStudio*);
  ~IliBrowserPanel ();

  void initData();
  void refreshAll();
  void addPage(IliDlgBrowsePage*,const char*,IlBoolean hide = IlFalse);
  void bnBuffer();

  IlvNotebook* getNTBook() const
    { return (IlvNotebook*)getObject("NTBook"); }
protected:
  IliDlgBrowsePage** _pages;
  IlInt _pageCount;
  IliString _sqlPageTitle;
};

#endif
