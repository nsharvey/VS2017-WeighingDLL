// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/layout/inspector/src/panel.cpp
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
// Create the main panel and the inspector panel
// --------------------------------------------------------------------------

#include <panel.h>

#include <ilviews/bitmaps/io.h>
#include <ilviews/layout/gphadapt.h>
#include <ilviews/layout/report.h>
#include <ilviews/layout/linkconnect.h>
#include <ilviews/layout/random.h>
#include <ivstudio/layout/random/randomitf.h>
#include <ilviews/layout/tree.h>
#include <ivstudio/layout/tree/treeitf.h>
#include <ilviews/layout/bus.h>
#include <ivstudio/layout/bus/busitf.h>
#include <ilviews/layout/hierarchical.h>
#include <ivstudio/layout/hierarchical/hieritf.h>
#include <ilviews/layout/orthlink.h>
#include <ivstudio/layout/orthlink/orthoitf.h>

#include <ilviews/gadgraph/rectscgr.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/grapher/alllinks.h>
#include <ilviews/graphics/selector.h>
#include <ivstudio/stlibini.h>
#include <ivstudio/inspect.h>
#include <ilviews/gadgets/fbrowser.h>
#include <ilviews/gadgets/colorch.h>
#include <ilviews/grapher/inters.h>
#include <ilviews/manager/selhook.h>

#if defined(IL_STD)
#  include <fstream>
#  include <cstdio>
IL_STDUSE
#else
#  include <fstream.h>
#  include <stdio.h>
#endif

static const char MainPanelFileName[] = "data/mainpan.ilv";
#define NBINTER 5
// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny)
{
    IlvDisplay* display = view->getDisplay();
    delete view;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
#define X 10
#define Y 50
#define W 800
#define H 900
#define RECTW 40

// --------------------------------------------------------------------------
class MakeNode
    : public IlvManagerViewInteractor
{
public:
    MakeNode(IlvManager* manager,
	     IlvView* view)
        : IlvManagerViewInteractor(manager, view),
	  _button(0)
	{}
    virtual IlBoolean handleEvent(IlvEvent& event);
    virtual void doIt(const IlvPoint& point);
    virtual void init();
    virtual void abort();
private:
    IlUShort		_button;
};

// --------------------------------------------------------------------------
class SelectionHook
    : public IlvManagerSelectionHook
{
public:
    SelectionHook(MainPanel* p)
	{ _panel = p; }
    virtual void selectionChanged(IlvGraphic*,
				  IlBoolean);
private:
    MainPanel*	_panel;
};

// --------------------------------------------------------------------------
void
SelectionHook::selectionChanged(IlvGraphic* g,
				IlBoolean selected)
{
    if (_panel) {
	IlvStringList* list = _panel->getInspectorPanel()->getStringList();
	IlShort lastSelect = list->getLastSelectedItem();
	if (lastSelect >= 0) {
	    IlvLayoutInspectorInterface* itf = (IlvLayoutInspectorInterface*)
		list->getItem(lastSelect)->getClientData();
	    if (itf) {
		itf->objectSelected(selected ? g : 0);
	    }
	}
	_panel->getInspectorPanel()->reinitialize();
    }
}

// --------------------------------------------------------------------------
void
MakeNode::init()
{
    _button = 0;
}

// --------------------------------------------------------------------------
void
MakeNode::abort()
{
    _button = 0;
}

// --------------------------------------------------------------------------
IlBoolean
MakeNode::handleEvent(IlvEvent& event)
{
    switch(event.type()) {
    case IlvButtonDown: {
	_button = event.button();
	return IlTrue;
    }
    case IlvButtonUp: {
	if (event.button() != _button) {
	    return getManager()->shortCut(event, _mgrview);
	}
	else {
	    doIt(IlvPoint(event.x(), event.y()));
	    return IlTrue;
	}
	break;
    }
    default:
	;
    }
    return getManager()->shortCut(event, _mgrview);
}

// --------------------------------------------------------------------------
void
MakeNode::doIt(const IlvPoint& point)
{
    getManager()->deSelect();
    IlvGrapher* mgr = ILVDYNAMICCAST(IlvGrapher*, getManager());
    if (mgr) {
	static int count = 0;
	static char buffer[16];
	sprintf(buffer, "%d", count++);
	IlvMessageLabel* node =
	    new IlvMessageLabel(getManager()->getDisplay(),
				buffer,
				IlvRect(point.x(), point.y(), 30, 20));
	node->setAlignment(IlvCenter);
	node->setOpaque(IlTrue);
	node->setThickness(2);
	mgr->addNode(node, IlTrue, getManager()->getInsertionLayer());
	getManager()->makeSelected(node);
	getManager()->setObjectName(node, buffer);
    }
}

// --------------------------------------------------------------------------
void
MakeNodeCB(IlvGraphic* g,
	   IlAny p)
{
    MainPanel* panel = ILVREINTERPRETCAST(MainPanel*, p);
    IlvToolBar* toolbar = ILVDYNAMICCAST(IlvToolBar*, g);
    toolbar->deSelectAll();
    panel->setInteractor(0);
}

// --------------------------------------------------------------------------
void
MakeLinkImageCB(IlvGraphic* g,
		IlAny p)
{
    MainPanel* panel = ILVREINTERPRETCAST(MainPanel*, p);
    IlvToolBar* toolbar = ILVDYNAMICCAST(IlvToolBar*, g);
    toolbar->deSelectAll();
    panel->setInteractor(4);
}

// --------------------------------------------------------------------------
void
MakeSquareLinkCB(IlvGraphic* g,
		 IlAny p)
{
    MainPanel* panel = ILVREINTERPRETCAST(MainPanel*, p);
    IlvToolBar* toolbar = ILVDYNAMICCAST(IlvToolBar*, g);
    toolbar->deSelectAll();
    panel->setInteractor(1);
}

// --------------------------------------------------------------------------
void
MakeCurvedLinkCB(IlvGraphic* g,
		 IlAny p)
{
    MainPanel* panel = ILVREINTERPRETCAST(MainPanel*, p);
    IlvToolBar* toolbar = ILVDYNAMICCAST(IlvToolBar*, g);
    toolbar->deSelectAll();
    panel->setInteractor(2);
}

// --------------------------------------------------------------------------
void
SelectCB(IlvGraphic* g,
	 IlAny p)
{
    MainPanel* panel = ILVREINTERPRETCAST(MainPanel*, p);
    IlvToolBar* toolbar = ILVDYNAMICCAST(IlvToolBar*, g);
    toolbar->deSelectAll();
    panel->setInteractor(3);
}

// --------------------------------------------------------------------------
void
NewCB(IlvGraphic*,
      IlAny p)
{
    MainPanel* panel = ILVREINTERPRETCAST(MainPanel*, p);
    panel->getGrapher()->deleteAll(IlTrue, IlTrue);
}

// --------------------------------------------------------------------------
void
OpenCB(IlvGraphic*,
       IlAny p)
{
    MainPanel* panel = ILVREINTERPRETCAST(MainPanel*, p);
    panel->getFBrowser()->setType(IlvFileSelectorLoad);
    const char* fileName = panel->getFBrowser()->get();
    if (fileName) {
	panel->getGrapher()->read(fileName);
	panel->getGrapher()->reDraw();
    }
}

// --------------------------------------------------------------------------
void
SaveCB(IlvGraphic*,
       IlAny p)
{
    MainPanel* panel = ILVREINTERPRETCAST(MainPanel*, p);
    panel->getFBrowser()->setType(IlvFileSelectorSave);
    const char* fileName = panel->getFBrowser()->get();
    if (fileName) {
	ofstream of(fileName);
	panel->getGrapher()->save(of);
    }
}

// --------------------------------------------------------------------------
void
InspectCB(IlvGraphic*,
	  IlAny p)
{
    MainPanel* panel = ILVREINTERPRETCAST(MainPanel*, p);
    panel->inspect();
}

// --------------------------------------------------------------------------
void
ChangeColor(IlvGraphic* obj,
	    IlAny arg)
{
    obj->setForeground(ILVREINTERPRETCAST(IlvColor*, arg));
}

// --------------------------------------------------------------------------
void
ColorCB(IlvGraphic*,
	IlAny p)
{
    MainPanel* panel = ILVREINTERPRETCAST(MainPanel*, p);
    if (!panel->getGrapher()->numberOfSelections()) {
	return;
    }
    IlvColor* color = panel->getColCh()->get();
    if (color) {
	panel->getGrapher()->applyToSelections(ChangeColor, color);
    }
}

// --------------------------------------------------------------------------
void
SetMoveable(IlvGraphic* obj,
	    IlAny arg)
{
    IlvManager* manager = obj->getHolder()->getManager();
    manager->setMoveable(obj, arg ? IlTrue : IlFalse);
}

// --------------------------------------------------------------------------
MainPanel::MainPanel(IlvDisplay* display,
		     const char* name,
		     const char* title,
		     const IlvRect& dims)
    : IlvDockableContainer(display, name, title, dims, IlvVertical),
      _inspPanel(0),
      _grapher(0),
      _grapherView(0),
      _fbrowser(0),
      _colSel(0),
      _interactorArray(IlArray(NBINTER)),
      _selected(-1)
{
    init();
}

// --------------------------------------------------------------------------
MainPanel::~MainPanel()
{
    if (_inspPanel) {
	delete _inspPanel;
    }
    if (_fbrowser) {
	delete _fbrowser;
    }
    if (_colSel) {
	delete _colSel;
    }
    if (_grapherView) {
	_grapher->setInteractor(0, _grapherView);
	delete _grapherView;
    }
    for (IlUInt loop = 0; loop < _interactorArray.getLength(); ++loop) {
	IlvManagerViewInteractor* inter =
	    (IlvManagerViewInteractor*)_interactorArray[loop];
	if (inter) {
	    delete inter;
	}
    }
    _interactorArray.empty();
    if (_grapher) {
	delete _grapher;
    }
}

// --------------------------------------------------------------------------
void
MainPanel::init()
{
    IlvDisplay* display = getDisplay();
    display->prependToPath("../data");
    setDestroyCallback(Quit);
    createOrthogonalDockableContainer(IlTrue);
    IlvPane* pane;

    IlvContainer* dummy = new IlvContainer(display,
					   "Hidden",
					   "Hidden",
					   IlvRect(0, 0, 600, 600),
					   IlFalse,
					   IlFalse);
    dummy->registerCallback("MakeNodeCB", MakeNodeCB);
    dummy->registerCallback("MakeLinkImageCB", MakeLinkImageCB);
    dummy->registerCallback("MakeSquareLinkCB", MakeSquareLinkCB);
    dummy->registerCallback("MakeCurvedLinkCB", MakeCurvedLinkCB);
    dummy->registerCallback("SelectCB", SelectCB);
    dummy->registerCallback("NewCB", NewCB);
    dummy->registerCallback("OpenCB", OpenCB);
    dummy->registerCallback("SaveCB", SaveCB);
    dummy->registerCallback("InspectCB", InspectCB);
    dummy->readFile(MainPanelFileName);

    // Adds the main toolbar pane.
    IlvToolBar* toolbar =
	ILVDYNAMICCAST(IlvToolBar*, dummy->getObject("MainToolBar"));
    IlUShort itemNb = toolbar->getCardinal();
    IlvMenuItem* item;
    IlUShort loop;
    for (loop = 0; loop < itemNb; ++loop) {
	item = toolbar->getItem(loop);
	item->setCallback(dummy->getCallback(item->getCallbackName()));
	item->setCallbackName(0);
	item->setClientData(ILVREINTERPRETCAST(IlAny, this));
    }
    dummy->removeObject(toolbar);
    pane = new IlvAbstractBarPane("MainToolBar", toolbar);
    addDockingPane(pane);

    // Adds an horizontal paned Container.
    IlvDockableContainer* horContainer =
	new IlvDockableContainer(this,
				 IlvRect(0, 0, 600, 400),
				 IlvHorizontal);
    horContainer->createOrthogonalDockableContainer(IlTrue);
    pane = new IlvViewPane("Main Area", horContainer);
    pane->setResizeMode(IlvPane::Elastic);
    addPane(pane);

    // Adds the interactor toolbar pane.
    toolbar =
	ILVDYNAMICCAST(IlvToolBar*, dummy->getObject("InteractorToolBar"));
    itemNb = toolbar->getCardinal();
    for (loop = 0; loop < itemNb; ++loop) {
	item = toolbar->getItem(loop);
	item->setCallback(dummy->getCallback(item->getCallbackName()));
	item->setCallbackName(0);
	item->setClientData(ILVREINTERPRETCAST(IlAny, this));
    }
    dummy->removeObject(toolbar);
    pane = new IlvAbstractBarPane("InteractorToolBar", toolbar);
    horContainer->addDockingPane(pane);

    _grapher = new IlvGrapher(display, 1, IlTrue, 1000, 1000);
    _grapherView = new IlvView(this, IlvRect(0, 0, 400, 400));
    getGrapherView()->setBackground(display->getColor("White"));
    getGrapher()->addView(getGrapherView());
    pane = new IlvViewPane("Main View", getGrapherView());
    pane->setResizeMode(IlvPane::Elastic);
    horContainer->addPane(pane);

    updatePanes(IlTrue);

    _fbrowser = new IlvFileBrowser(display, getSystemView());
    _colSel =   new IlvColorSelector(display, getSystemView());

    initializeLayout();
    delete dummy;

    // Initialize interactors
    IlvView* view = getGrapherView();
    IlvManagerViewInteractor* inter = new MakeNode(getGrapher(), view);
    _interactorArray.add(inter);
    _interactorArray.add(new IlvMakeDoubleLinkImageInteractor(getGrapher(),
							      view,
							      IlFalse));
    _interactorArray.add(new
			 IlvMakeOneSplineLinkImageInteractor(getGrapher(),
							     view,
							     IlFalse));
    _interactorArray.add(new IlvGraphSelectInteractor(getGrapher(),
						      view));
    _interactorArray.add(new IlvMakeLinkImageInteractor(getGrapher(),
							view,
							IlFalse));
}

// --------------------------------------------------------------------------
void
MainPanel::initializeLayout()
{
    _inspPanel = new IlvLayoutInspectorPanel(getDisplay(),
					     "Inspector",
					     0,
					     getSystemView());
    _inspPanel->initializeEditors();

    IlvLayoutInspectorInterface* itf;
    IlvGraphLayout* layout = new IlvRandomLayout();
    layout->attach(getGrapher());
    itf = new IlvRandomLayoutInterface(layout);
    _inspPanel->registerLayout("Random Layout", itf);

    layout = new IlvTreeLayout();
    layout->attach(getGrapher());
    itf = new IlvTreeLayoutInterface(layout);
    _inspPanel->registerLayout("Tree Layout", itf);

    layout = new IlvBusLayout();
    layout->attach(getGrapher());
    itf = new IlvBusLayoutInterface(layout);
    _inspPanel->registerLayout("Bus Layout", itf);

    layout = new IlvHierarchicalLayout();
    layout->attach(getGrapher());
    itf = new IlvHierarchicalLayoutInterface(layout);
    _inspPanel->registerLayout("Hierarchical Layout", itf);

    layout = new IlvOrthogonalLinkLayout();
    layout->attach(getGrapher());
    itf = new IlvOrthogonalLayoutInterface(layout);
    _inspPanel->registerLayout("Orthogonal Layout", itf);

    _inspPanel->initializeLayout();
}

// --------------------------------------------------------------------------
IlvGrapher*
MainPanel::getGrapher() const
{
    return _grapher;
}

// --------------------------------------------------------------------------
IlvView*
MainPanel::getGrapherView() const
{
    return _grapherView;
}

// --------------------------------------------------------------------------
void
MainPanel::setInteractor(IlUInt index)
{
    if (_selected == (IlInt)index) {
	getGrapher()->setInteractor(0, getGrapherView());
	_selected = -1;
    }
    else {
	IlvManagerViewInteractor* interactor =
	    (IlvManagerViewInteractor*)_interactorArray[index];
	getGrapher()->setInteractor(interactor,
				    getGrapherView());
	_selected = index;
    }
    return;
}

// --------------------------------------------------------------------------
IlvFileBrowser*
MainPanel::getFBrowser() const
{
    return _fbrowser;
}

// --------------------------------------------------------------------------
IlvColorSelector*
MainPanel::getColCh() const
{
    return _colSel;
}

// --------------------------------------------------------------------------
void
MainPanel::inspect() const
{
    _inspPanel->show();
}

// --------------------------------------------------------------------------
IlvLayoutInspectorPanel*
MainPanel::getInspectorPanel() const
{
    return _inspPanel;
}

// --------------------------------------------------------------------------
void
MainPanel::show()
{
    IlvDockableContainer::show();
    _inspPanel->show();
}
