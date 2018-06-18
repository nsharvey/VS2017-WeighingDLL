// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/grapher/graphed/src/graphed.cpp
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
#include <ilviews/grapher/all.h>
#include <ilviews/graphics/all.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/gadgraph/rectscgr.h>
#include <ilviews/gadgets/toolbar.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/combo.h>

#include <ilviews/bitmaps/png.h>
#include <ilog/pathname.h>

#if defined(IL_STD)
IL_STDUSE
#  include <cstdio>
#else
#  include <stdio.h>
#endif

static const char* title = "Simple Graph Editor";
static const char* PanelFileName = "graphed.ilv";
static const char* GrapherFileName = "graphex.ilv";

// ----------------------------------------------------------------
// - Factory to create link instances
// - The created instance is a copy of the link model
// - that is set with the setLinkModel method
class MakeLinkFactory
    : public IlvMakeLinkInteractorFactory 
{
public:
    MakeLinkFactory() : _linkModel(0) {}
    virtual IlvLinkImage* createLink(IlvDisplay* dpy,
				     IlvGraphic* from,
				     IlvGraphic* to,
				     IlBoolean   oriented) const;
    
    inline void setLinkModel(IlvLinkImage* model) { _linkModel = model; }

protected:
    IlvLinkImage* _linkModel;
};

// --------------------------------------------------------------------------
IlvLinkImage*
MakeLinkFactory::createLink(IlvDisplay* dpy,
			    IlvGraphic* from,
			    IlvGraphic* to,
			    IlBoolean	oriented) const
{
    if (_linkModel) {
	IlvLinkImage* link = IL_CAST(IlvLinkImage*, _linkModel->copy()); 
	link->setFrom(from);
	link->setTo(to);
	link->setOriented(oriented);
	return link;
    } else 
	return 0;
}

// ----------------------------------------------------------------
class IlvGraphEditorSample
{
public:
    enum LinkType {
	DirectLink = 0,
	OneLink,
	OneSplineLink,
	DoubleLink,
	DoubleSplineLink,
	ArcLink
    };

    enum EditMode {
	SelectMode = 0,
	MakeLinkMode,
	PinEditMode
    };

    IlvGraphEditorSample(IlvGrapher* graph, IlvView* view) 
	: _graph(0),
	  _linkModels(),
	  _mkLinkInter(0),
	  _selInter(0),
	  _pinEdtInter(0)
    {init(graph, view);}

    ~IlvGraphEditorSample();

    IlvGrapher*	    getGrapher() const { return _graph; }
    
    void setLinkType(LinkType type);
    void setLinkOriented(IlBoolean b) {_mkLinkInter->setOriented(b);}
    void setEditMode(EditMode mode);

private:
    IlvGrapher*			_graph;		// The grapher.
    IlArray			_linkModels;	// Graphic models for links.
    IlvMakeLinkInteractor*	_mkLinkInter;   // Interactor to create links.
    IlvGraphSelectInteractor*	_selInter;	// Interactor to manipulate
    						// nodes and links.
    IlvPinEditorInteractor*	_pinEdtInter;	// Interactor to edit
    						// connection pins.

    void init(IlvGrapher* graph, IlvView* view);
    
    // Not implemented
    IlvGraphEditorSample(const IlvGraphEditorSample&);
    IlvGraphEditorSample& operator=(const IlvGraphEditorSample&);
};

// --------------------------------------------------------------------------
IlvGraphEditorSample::~IlvGraphEditorSample()
{
    for (IlUInt i = 0; i < _linkModels.getLength(); ++i) {
	delete IL_CAST(IlvLinkImage*, _linkModels[i]);
    }
    _graph->setInteractor(0, _graph->getFirstView());
    delete _mkLinkInter;
    delete _selInter;
    delete _pinEdtInter;
}

// --------------------------------------------------------------------------
void
IlvGraphEditorSample::init(IlvGrapher* graph,
			   IlvView* view)
{
    IlvDisplay* dpy = graph->getDisplay();
    _graph = graph;
    //=========================================================
    //== Set the layer where the links will be added by the interactor.
    _graph->setInsertionLayer(0);

    //== Toggle undo mechanism. By hitting the 'u' key, undoable actions
    //== will be reverted.
    _graph->setUndoEnabled(IlTrue);

    //== Enable link manipulation through IlvGraphSelectInteractor
    _graph->setLinksEditable(IlTrue);
    
    _linkModels.add((IlAny) new IlvLinkImage(dpy, IlFalse, 0, 0));
    _linkModels.add((IlAny) new IlvOneLinkImage(dpy, IlvHorizontalLink, 
					        IlFalse, 0, 0));
    _linkModels.add((IlAny) new IlvOneSplineLinkImage(dpy, IlvHorizontalLink, 
						      IlFalse, 0, 0));
    _linkModels.add((IlAny) new IlvDoubleLinkImage(dpy, IlFalse, 0, 0));
    _linkModels.add((IlAny) new IlvDoubleSplineLinkImage(dpy, IlFalse, 0, 0));
    _linkModels.add((IlAny) new IlvArcLinkImage(dpy, IlFalse, 0, 0));

    //====================================================================
    //== Create sn interactor to manipulate the nodes and links inside the
    //== grapher
    _selInter = new IlvGraphSelectInteractor(_graph, view);
    _selInter->opaqueMove(IlTrue);
    _graph->setInteractor(_selInter);
    
    //=============================================================
    //== Create the factory and the interactor used to create links
    MakeLinkFactory* factory = new MakeLinkFactory();
    factory->setLinkModel(IL_CAST(IlvLinkImage*, _linkModels[0]));
    _mkLinkInter = new IlvMakeLinkInteractor(graph, view, IlFalse);
    _mkLinkInter->handlePointerMoved(IlTrue);
    _mkLinkInter->setFactory(factory);
    
    _pinEdtInter = new IlvPinEditorInteractor(_graph, view);
}

// --------------------------------------------------------------------------
// - Changes the link type that is created by the interactor
void 
IlvGraphEditorSample::setLinkType(LinkType type)
{
    IlUInt idx = (IlUInt)type;
    if (idx < _linkModels.getLength()) {
	IlvLinkImage* link = IL_CAST(IlvLinkImage*, _linkModels[idx]);
	IL_CAST(MakeLinkFactory*, _mkLinkInter->getFactory())
	    ->setLinkModel(link);
    }
}

// --------------------------------------------------------------------------
// - Changes the editing mode
void 
IlvGraphEditorSample::setEditMode(EditMode mode)
{
    IlvView* view = getGrapher()->getFirstView();
    switch(mode) {
    case SelectMode:
        getGrapher()->setInteractor(_selInter, view);
	break;
    case MakeLinkMode:
        getGrapher()->setInteractor(_mkLinkInter, view);
	break;
    case PinEditMode:
        getGrapher()->setInteractor(_pinEdtInter, view);
	break;
    default:
        break;
    }
}

// --------------------------------------------------------------------------
// - Quit the application
static void ILVCALLBACK
Quit(IlvView* top,
     IlAny arg)
{
    IlvDisplay* dpy = top->getDisplay();
    delete IL_CAST(IlvGraphEditorSample*, arg);
    delete top;
    delete dpy;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// - Callbacks on toolbar items
static void
ChangeLinkModelCB(IlvGraphic* g,
		  IlAny arg)
{
    IlvComboBox* combo = IL_CAST(IlvComboBox*, g);
    IlvGraphEditorSample* graphEd = IL_CAST(IlvGraphEditorSample*, arg);
    graphEd->setLinkType(IL_CAST(IlvGraphEditorSample::LinkType,
				 combo->whichSelected()));
}

// --------------------------------------------------------------------------
static void 
SetEditModeCB(IlvGraphic* g,
	      IlAny arg)
{
    IlvGraphEditorSample* graphEd =
	IL_CAST(IlvGraphEditorSample*, g->getClientData());
    IlvToolBar* toolbar = IL_CAST(IlvToolBar*, g);
    IlvGadgetItem* item = toolbar->getCallbackItem();
    IlUShort count;
    IlvMenuItem* const* items = toolbar->getItems(count);
    for (IlUShort i = 0; i < count; ++i) {
	if (items[i]->getCallback() == SetEditModeCB)
	    items[i]->deSelect();
    }
    item->select();
    graphEd->setEditMode(IL_CAST(IlvGraphEditorSample::EditMode,
				 IlCastIlAnyToIlUInt(item->getClientData())));
}

// --------------------------------------------------------------------------
static void 
ToggleOrientedCB(IlvGraphic* g,
		 IlAny arg)
{
    IlvGraphEditorSample* graphEd =
	IL_CAST(IlvGraphEditorSample*, g->getClientData());
    IlvToolBar* toolbar = IL_CAST(IlvToolBar*, g);
    IlvGadgetItem* item = toolbar->getCallbackItem();
    graphEd->setLinkOriented(item->isSelected());

}

// --------------------------------------------------------------------------
// - Adds callbacks to the toolbar items and create a combo box to choose
// - the link type used by the editor.
static void 
UpdateToolBar(IlvToolBar* toolBar,
	      IlvGraphEditorSample* graphEd)
{
    IlvDisplay* dpy = toolBar->getDisplay();
    toolBar->setClientData(graphEd);
    
    //== Select 
    IlvMenuItem* item = toolBar->getItem(0);
    item->setCallback(SetEditModeCB);
    item->setClientData((IlAny)IlvGraphEditorSample::SelectMode);
    item->select();

    //== Make Link
    item = toolBar->getItem(2);
    item->setCallback(SetEditModeCB);
    item->setClientData((IlAny)IlvGraphEditorSample::MakeLinkMode);
    item = toolBar->getItem(3);
    item->setCallback(ToggleOrientedCB);

    //== Pin editing
    item = toolBar->getItem(5);
    item->setCallback(SetEditModeCB);
    item->setClientData((IlAny)IlvGraphEditorSample::PinEditMode);
   
    
    IlvComboBox* combo = new IlvComboBox(dpy, IlvRect(0, 0, 160, 24), "");
    const IlUShort nbItems = 6;
    IlvGadgetItem* items[nbItems];
    items[0] = new IlvMenuItem("DirectLink");
    items[0]->setBitmap(dpy->readBitmap("link.png"));
    items[1] = new IlvMenuItem("OneLink");
    items[1]->setBitmap(dpy->readBitmap("olink.png"));
    items[2] = new IlvMenuItem("OneSplineLink");
    items[2]->setBitmap(dpy->readBitmap("oslink.png"));
    items[3] = new IlvMenuItem("DoubleLink");
    items[3]->setBitmap(dpy->readBitmap("dlink.png"));
    items[4] = new IlvMenuItem("DoubleSplineLink");
    items[4]->setBitmap(dpy->readBitmap("dslink.png"));
    items[5] = new IlvMenuItem("ArcLink");
    items[5]->setBitmap(dpy->readBitmap("alink.png"));
    combo->setItems(items, nbItems);
    combo->setEditable(IlFalse);
    combo->setFocusable(IlFalse);
    combo->setCallback(ChangeLinkModelCB, graphEd);
    combo->setSelected(0);
    toolBar->insertGraphic(combo, 4);    
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* dpy = new IlvDisplay("Graphed", "", argc, argv);
    if (!dpy || dpy->isBad()) {
	IlvFatalError("Couldn't create display");
	if (dpy)
	    delete dpy;
	return 1;
    }
    IlPathName localPath(dpy->getHomePath());
    localPath.addDirectory("samples/grapher/graphed/data");
    dpy->prependToPath(localPath);

    IlvGadgetContainer* panel = new IlvGadgetContainer(dpy, title, title,
						       IlvRect(0, 0,
							       640, 480),
						       IlFalse, IlFalse);    
    panel->allowFocus(IlFalse);

    IlvToolBar* toolBar = 0;
    IlvSCGrapherRectangle* grapherRect = 0;
    IlBoolean ok = panel->readFile(PanelFileName);
    if (ok) {
	grapherRect =
	    IL_CAST(IlvSCGrapherRectangle*, panel->getObject("GraphRect"));
	toolBar = IL_CAST(IlvToolBar*, panel->getObject("Toolbar"));
    }
    if (!grapherRect || !toolBar) {
	IlvFatalError("Bad data file %s", PanelFileName);
	delete dpy;
	return 1;
    }

    IlvGrapher* graph = grapherRect->getGrapher();
    graph->setLinksEditable(IlTrue);
    IlvView* graphView = grapherRect->getView();
    graph->setBackground(graphView, dpy->getColor("lightgrey"));
    graph->read(GrapherFileName);
    graph->setDoubleBuffering(graphView, IlTrue);

    IlvGraphEditorSample* graphEd = 
	new IlvGraphEditorSample(graph, grapherRect->getView());
    UpdateToolBar(toolBar, graphEd);

    panel->setDestroyCallback(Quit, graphEd);
    panel->show();
    IlvMainLoop();
    return 0;
}
