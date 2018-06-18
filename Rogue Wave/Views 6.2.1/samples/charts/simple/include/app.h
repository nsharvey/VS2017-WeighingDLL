// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/charts/simple/include/app.h
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

#ifndef __Ilv_Samples_App_H
#define __Ilv_Samples_App_H

#include <ilviews/gadgets/appli.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/notebook.h>
#include <ilviews/gadgets/text.h>

// --------------------------------------------------------------------------
// Page for notebook
// --------------------------------------------------------------------------
class PageNoteBook : public IlvGadgetContainer
{
public:
    PageNoteBook(IlvAbstractView* view, const char* filename);

    virtual void	initialize(const char* filename);
    void		setLegendFileName(const char* filename);
    const char*		getLegendFileName() const;
    void		setGraphicAttachments(IlvGraphic* g);
    
protected:
    IlString		_legendFileName;
};

// --------------------------------------------------------------------------
// Main panel class
// --------------------------------------------------------------------------
class Pan : public IlvGadgetContainer
{
public:
    Pan(IlvDisplay*, const char*, const char*, const IlvRect&);

    void		initializeSamples();
    void		addPageNoteBook(PageNoteBook*,
					const char*,
					const char*);
    void		newPageSelected();
    
protected:
    IlvNotebook*	_notebook;
    IlvText*		_legend;
    IlInt		_pagesCount;
};

#endif /* !__Ilv_Samples_App_H*/


