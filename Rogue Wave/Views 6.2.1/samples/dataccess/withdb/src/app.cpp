// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/withdb/src/app.cpp
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
// File: samples/dataccess/withdb/src/app.cpp
// IlogViews 2.21 generated application source file
// File generated: Tue Oct  1 15:43:29 1996
// --------------------------------------------------------------------------
#include <app.h>

#ifdef IL_STD
#include <cstring>
#else
#include <string.h>
#endif

#include <ilviews/dataccess/home.h>
#include <ilviews/dataccess/format.h>
#include <ilviews/dataccess/error.h>
#include <ilviews/dataccess/gadgets/dbtimer.h>
#include <ilviews/dataccess/dbms/session.h>

IL_STDUSE

// --------------------------------------------------------------------------
// Declares the pages of samples
// --------------------------------------------------------------------------
extern void DefinePageDynamicSelect(Pan*);
extern void DefinePageGauge(Pan*);
extern void DefinePageGettingStarted1(Pan*);
extern void DefinePageGettingStarted2(Pan*);
extern void DefinePageGettingStarted3(Pan*);
extern void DefinePageQuery(Pan*);
extern void DefinePageSession(Pan*);

// --------------------------------------------------------------------------
// callback functions
// --------------------------------------------------------------------------
static void ILVCALLBACK
NoteBookSelectPage(IlvGraphic*, IlvAny any) {
  Pan* panel = (Pan*)any;
  if (panel)
    panel->newPageSelected();
}

// --------------------------------------------------------------------------
static void
Quit(IlvView* view,IlAny) {
    IlvDisplay* display = view->getDisplay();
    delete view;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Application class
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
DbApp::DbApp(const char* appName,const char* displayName,
		 int argc,char** argv)
  : IlvApplication(appName, displayName, argc, argv) {
}

DbApp::DbApp(IlvDisplay* display,const char* name,IlvBoolean owner)
: IlvApplication(display, name, owner) {
}

// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
DbApp::~DbApp() {
}

// --------------------------------------------------------------------------
void
DbApp::beforeRunning() {
  IlvJvScriptLanguage::InitAuxiliaryLib (getDisplay());

  IliAppendDataAccessPath(getDisplay());
  IliFormat::ReadMessageDatabase(getDisplay(), "dataccess/dataccess.dbm");
  IliFormat::ReadMessageDatabase(getDisplay(), "dataccess/date.dbm");
  IliFormat::ConnectToMessageDatabase(getDisplay());
  IliErrorMessage::ConnectToMessageDatabase(getDisplay());

  IliFormat::ReadMessageDatabase(getDisplay(), "dataccess/dblink.dbm");
  IliSQLSession::ConnectToMessageDatabase(getDisplay());
}

// --------------------------------------------------------------------------
// Creates the panel
// --------------------------------------------------------------------------
void
DbApp::makePanels() {
  Pan* panel = new Pan(getDisplay(), "Pan", "Pan", IlvRect(0,0,500,500));
  addPanel(panel);
  panel->initializeSamples();
  panel->setDestroyCallback(Quit);
  panel->show();
  // --- The Exit panel is not wanted ---
  setUsingExitPanel(IlvFalse);
}

// --------------------------------------------------------------------------
// Main panel class
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
Pan::Pan(IlvDisplay* display,const char* name,
	 const char* title,const IlvRect& size)
  : IlvGadgetContainer(display,name,title,size,0,IlvFalse,IlvFalse,0)
{ 
  _notebook = 0;
  _legend = 0;
  _pagesCount = 0;
}
 
// --------------------------------------------------------------------------
// Initializes the pages of samples
// --------------------------------------------------------------------------
void 
Pan::initializeSamples() {
  readFile("pan.ilv");
  _notebook = (IlvNotebook*)getObject("NoteBook");
  _legend = (IlvText*)getObject("Legend");
  if (_notebook && _legend) {
    _notebook->addCallback(IlvNotebook::PageSelectedCallbackType(),
			   NoteBookSelectPage,this);
  }
  else
    return;
  //---- the pages of samples ----
  DefinePageGauge(this);
  DefinePageGettingStarted1(this);
  DefinePageGettingStarted2(this);
  DefinePageGettingStarted3(this);
  DefinePageQuery(this);
  DefinePageSession(this);
  PageNoteBook* qpage = new PageNoteBook(this,"querymod.ilv");
  this->addPageNoteBook(qpage, "Query Mode", "querymod.txt");
  PageNoteBook* tpage = new PageNoteBook(this,"transman.ilv");
  this->addPageNoteBook(tpage, "Transaction Manager", "transman.txt");
  PageNoteBook* cpage = new PageNoteBook(this,"collect.ilv");
  this->addPageNoteBook(cpage, "Informix 9", "collect.txt");
  PageNoteBook* npage = new PageNoteBook(this,"nest.ilv");
  this->addPageNoteBook(npage, "Oracle 9i", "nest.txt");

  newPageSelected();
}

// --------------------------------------------------------------------------
// Add a page of notebook
// --------------------------------------------------------------------------
void 
Pan::addPageNoteBook(PageNoteBook* panel,const char* name,
		     const char* legendFileName) {

  panel->setLegendFileName(getDisplay()->findInPath(legendFileName));
  if (panel && name && *name) {
    panel->hide();
    panel->allowFocus(IlvTrue);
    if (_pagesCount)
      _notebook->addPage(name);
    else
      _notebook->getPages()[0]->setLabel(name);
    _notebook->getPages()[_pagesCount]->setView(panel);
    _pagesCount++;
  }
}

// --------------------------------------------------------------------------
// New page has been selected
// --------------------------------------------------------------------------
void
Pan::newPageSelected() {
  IlvNotebookPage* ntpg = _notebook->getSelectedPage();
  if (ntpg) {
    PageNoteBook *page = (PageNoteBook*)(ntpg->getView());
    if (page) {
      const char* filename = page->getLegendFileName();
      if (filename && *filename) {
	if (!_legend->readText(filename))
	  _legend->setText("No file");
	reDrawObj(_legend);
      }
    }
  }
    
}

// --------------------------------------------------------------------------
// Page for notebook
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
PageNoteBook::PageNoteBook(IlvAbstractView* view, const char* filename)
  : IlvGadgetContainer(view, IlvRect(0,0,500,300)) {
    initialize(filename);
}

// --------------------------------------------------------------------------
// Initializes the page
// --------------------------------------------------------------------------
void 
PageNoteBook::initialize(const char* filename) {
  readFile(filename);
}

// --------------------------------------------------------------------------
// Sets the legend file name
// --------------------------------------------------------------------------
void 
PageNoteBook::setLegendFileName(const char* filename) {
  _legendFileName = filename;
}

// --------------------------------------------------------------------------
// Returns the legend file name
// --------------------------------------------------------------------------
const char* 
PageNoteBook::getLegendFileName() const {
  return (const char*)_legendFileName;
}


