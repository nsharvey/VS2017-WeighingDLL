// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/include/app.h
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
// File: samples/dataccess/nodb/include/app.h
// IlogViews 2.21 generated application header file
// File generated: Tue Oct  1 15:43:29 1996
// --------------------------------------------------------------------------

#ifndef __app__header__
#define __app__header__

#include <ilviews/gadgets/appli.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/notebook.h>
#include <ilviews/gadgets/text.h>

#include <ilviews/dataccess/string.h>

// --------------------------------------------------------------------------
// Application class
// --------------------------------------------------------------------------
class NoDbApp: public IlvApplication 
{
public:
  NoDbApp(const char* app,const char* display=0,int argc=0,char** argv=0);
  NoDbApp(IlvDisplay*,const char*,IlvBoolean owner = IlvFalse);
  ~NoDbApp();

  virtual void makePanels();
  virtual void beforeRunning();
};

// --------------------------------------------------------------------------
// Page for notebook
// --------------------------------------------------------------------------
class PageNoteBook
  : public IlvGadgetContainer
{
public:
  PageNoteBook(IlvAbstractView* view,const char* filename);

  virtual void initialize(const char* filename);

  void setLegendFileName(const char* filename);
  const char* getLegendFileName() const;
protected:
  IliString _legendFileName;
};

// --------------------------------------------------------------------------
// Main panel class
// --------------------------------------------------------------------------
class Pan
: public IlvGadgetContainer 
{
public:
  Pan(IlvDisplay*, const char*, const char*, const IlvRect&);

  void initializeSamples();
  void addPageNoteBook(PageNoteBook*,const char*,const char*);
  void newPageSelected();

protected:
  IlvNotebook* _notebook;
  IlvText* _legend;
  IlvInt _pagesCount;
};

#endif /* !__folioapp__header__*/


