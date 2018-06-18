// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/layout/inspector/include/panel.h
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
// Declare the main panel class: MainPanel
// --------------------------------------------------------------------------

#include <ilviews/grapher/grapher.h>
#include <ivstudio/layout/insppnl.h>
#include <ilviews/gadgets/dockpane.h>

// --------------------------------------------------------------------------
class IlvFileBrowser;
class IlvColorSelector;

// --------------------------------------------------------------------------
class MainPanel
    : public IlvDockableContainer
{
public:
    MainPanel(IlvDisplay*,
	      const char*,
	      const char*,
	      const IlvRect&);
    virtual ~MainPanel();

    void	show();

    IlvGrapher*	getGrapher() const;
    IlvView*	getGrapherView() const;
    void	setInteractor(IlUInt);

    IlvFileBrowser* getFBrowser() const;
    IlvColorSelector* getColCh()  const;

    void	inspect() const;
    IlvLayoutInspectorPanel*	getInspectorPanel() const;
protected:
    void init();
    void initializeLayout();

    IlvLayoutInspectorPanel* _inspPanel;
    IlvGrapher*		_grapher;
    IlvView*		_grapherView;
    IlvFileBrowser*	_fbrowser;
    IlvColorSelector*	_colSel;
    IlArray		_interactorArray;
    IlInt		_selected;
};
