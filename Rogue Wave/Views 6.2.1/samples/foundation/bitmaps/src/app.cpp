// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/bitmaps/src/app.cpp
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
// Application and Notebook panel classes
// --------------------------------------------------------------------------

#include <app.h>

// --------------------------------------------------------------------------
// Declares the pages of samples
// --------------------------------------------------------------------------
extern void DefinePageContrast(Pan*);
extern void DefinePageJpgComp(Pan*);
extern void DefinePageQuantize(Pan*);
extern void DefinePageTransition(Pan*);
extern void DefinePageAnimate(Pan*);
extern void DefinePageAlpha(Pan*);
extern void DefinePageCreatebm(Pan*);
extern void DefinePageRotation(Pan*);

// --------------------------------------------------------------------------
// Callback
// --------------------------------------------------------------------------
static void
NoteBookSelectPage(IlvGraphic*, IlAny any)
{
    Pan* panel = (Pan*)any;
    if (panel) {
        panel->newPageSelected();
    }
}

// --------------------------------------------------------------------------
// Exit the application
// --------------------------------------------------------------------------
void
Quit(IlvView* view, IlAny arg)
{
    delete view->getDisplay();
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Main panel class
// --------------------------------------------------------------------------
Pan::Pan(IlvDisplay*	display,
	 const char*	name,
	 const char*	title,
	 const IlvRect&	size)
    : IlvGadgetContainer(display, name, title, size, 0, IlFalse, IlFalse, 0)
{ 
    _notebook = 0;
    _legend = 0;
    _pagesCount = 0;
}
 
// --------------------------------------------------------------------------
// Initializes the pages of samples
// --------------------------------------------------------------------------
void 
Pan::initializeSamples()
{
    readFile("pan.ilv");
    setDestroyCallback(Quit);
    _notebook = (IlvNotebook*)getObject("NoteBook");
    _legend = (IlvText*)getObject("Legend");
    if (_notebook && _legend) {
        _notebook->addCallback(IlvNotebook::PageSelectedCallbackType(),
			       NoteBookSelectPage,
			       this);
    }
    else {
        return;
    }
    
    // Notebook pages
    DefinePageAlpha(this);
    DefinePageAnimate(this);
    DefinePageContrast(this);
    DefinePageCreatebm(this);
    DefinePageJpgComp(this);
    DefinePageQuantize(this);
    DefinePageRotation(this);
    DefinePageTransition(this);
    newPageSelected();
}

// --------------------------------------------------------------------------
// Add a notebook page
// --------------------------------------------------------------------------
void 
Pan::addPageNoteBook(PageNoteBook*	panel,
		     const char*	name,
		     const char*	legendFileName)
{
    panel->setLegendFileName(getDisplay()->findInPath(legendFileName));
    if (panel && name && *name) {
        panel->hide();
        panel->allowFocus(IlvTrue);
        if (_pagesCount) {
            _notebook->addPage(name);
	}
        else {
            _notebook->getPages()[0]->setLabel(name);
	}
        _notebook->getPages()[_pagesCount]->setView(panel);
        _pagesCount++;
    }
}

// --------------------------------------------------------------------------
// New page has been selected
// --------------------------------------------------------------------------
void
Pan::newPageSelected()
{
    IlvNotebookPage* ntpg = _notebook->getSelectedPage();
    if (ntpg) {
        PageNoteBook *page = (PageNoteBook*)(ntpg->getView());
        if (page) {
            const char* filename = page->getLegendFileName();
            if (filename && *filename) {
	        if (!_legend->readText(filename)) {
		    _legend->setText("No file");
		}
		reDrawObj(_legend);
	    }
	}
    }
}

// --------------------------------------------------------------------------
// Notebook page
// --------------------------------------------------------------------------
PageNoteBook::PageNoteBook(IlvAbstractView*	view,
			   const char*		filename)
    : IlvGadgetContainer(view, IlvRect(0, 0, 500, 300))
{
    initialize(filename);
}

// --------------------------------------------------------------------------
void 
PageNoteBook::initialize(const char* filename)
{
    readFile(filename);
}

// --------------------------------------------------------------------------
void 
PageNoteBook::setLegendFileName(const char* filename)
{
    _legendFileName = filename;
}

// --------------------------------------------------------------------------
const char* 
PageNoteBook::getLegendFileName() const
{
    return (const char*)_legendFileName;
}
