// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/src/app.cpp
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
// File: samples/dataccess/nodb/src/app.cpp
// IlogViews 2.21 generated application source file
// File generated: Tue Oct  1 15:43:29 1996
// --------------------------------------------------------------------------

#include <app.h>
#include <string.h>
#include <ilviews/dataccess/home.h>
#include <ilviews/dataccess/format.h>
#include <ilviews/dataccess/error.h>

// --------------------------------------------------------------------------
// Declares the pages of samples
// --------------------------------------------------------------------------
extern void DefinePageFolio(Pan*);
extern void DefinePageForm(Pan*);
extern void DefinePageHtml(Pan*);
extern void DefinePageSingleToggle(Pan*);
extern void DefinePageUserCall(Pan*);

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
NoDbApp::NoDbApp(const char* appName,const char* displayName,
		 int argc,char** argv)
  : IlvApplication(appName, displayName, argc, argv) {
}

NoDbApp::NoDbApp(IlvDisplay* display,const char* name,IlvBoolean owner)
: IlvApplication(display, name, owner) {
}

// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
NoDbApp::~NoDbApp() {
}

// --------------------------------------------------------------------------
void
NoDbApp::beforeRunning() {
  IliAppendDataAccessPath(getDisplay());
  IliFormat::ReadMessageDatabase(getDisplay(), "dataccess/dataccess.dbm");
  IliFormat::ReadMessageDatabase(getDisplay(), "dataccess/date.dbm");
  IliFormat::ConnectToMessageDatabase(getDisplay());
  IliErrorMessage::ConnectToMessageDatabase(getDisplay());
}

// --------------------------------------------------------------------------
// Creates the panel
// --------------------------------------------------------------------------
void
NoDbApp::makePanels() {
  Pan* panel = new Pan(getDisplay(), "Pan", "NoDb", IlvRect(0,0,500,500));
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
  DefinePageFolio(this);
  DefinePageForm(this);
  DefinePageHtml(this);
  DefinePageSingleToggle(this);
  DefinePageUserCall(this);
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


