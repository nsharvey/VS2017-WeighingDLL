// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/grapher/linkhand/src/linkhand.cpp
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
// Demonstrating the use of IlvLinkHandle.
// --------------------------------------------------------------------------
#include <ilviews/grapher/all.h>
#include <ilviews/graphics/all.h>
#include <ilviews/graphics/set.h>
#include <ilviews/graphics/inter.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/contain/contain.h>
#include <ilviews/contain/rectangl.h>
#include <ilviews/bitmaps/png.h>
#include <ilog/pathname.h>

#if defined(IL_STD)
IL_STDUSE
#  include <cstdio>
#else
#  include <stdio.h>
#endif
IL_NO_UNSECURE_CRT_WARNINGS

static const char* title = "Link Handle Sample";
static const IlUInt NbNodes = 48;

// --------------------------------------------------------------------------
// - Factory to create IlvLinkHandle instances
// - The created instance will reference a copy of the graphic model
// - that is set with the setGraphicModel method
class IlvMakeLinkHandleFactory
: public IlvMakeLinkInteractorFactory 
{
public:
    IlvMakeLinkHandleFactory() : _graphicModel(0) {}
    virtual IlvLinkImage* createLink(IlvDisplay* dpy,
				     IlvGraphic* from,
				     IlvGraphic* to,
				     IlBoolean  oriented) const;
    
    void setGraphicModel(IlvGraphic* model) { _graphicModel = model; }

protected:
    IlvGraphic* _graphicModel;
};

// --------------------------------------------------------------------------
IlvLinkImage*
IlvMakeLinkHandleFactory::createLink(IlvDisplay* dpy,
				     IlvGraphic* from,
				     IlvGraphic* to,
				     IlBoolean) const
{
    if (_graphicModel) {
	IlvRect bbox;
	_graphicModel->boundingBox(bbox);
	IlvDim width = IlvMin(bbox.w(), bbox.h());
	IlvLinkHandle* linkh = 
	    new IlvLinkHandle(dpy, _graphicModel, from, to, width, IlFalse);
	linkh->useLinkPalette(IlFalse);
	return linkh;
    }
    else {
	return 0;
    }
}

// --------------------------------------------------------------------------
// - IlvLinkHandleSample
// --------------------------------------------------------------------------
class IlvLinkHandleSample
{
public:
    IlvLinkHandleSample(IlvDisplay* dpy) 
    : _panel(0),
      _graph(0),
      _graphicModels(),
      _gModel(0),
      _mkLinkInter(0),
      _selInter(0)
    {
	init(dpy);
    }
    ~IlvLinkHandleSample();

    IlvGrapher*	    getGrapher() const { return _graph; }
    IlvContainer*   getPanel() const { return _panel; }

    IlvGraphic* getGraphicModel(const IlvGraphic* orig) const
    { 
	IlvGraphic* res;
	return _graphicModels.find((IlAny)orig, (IlAny*)&res) ? res : 0;
    }
    
    static void ChangeLinkModelCB(IlvGraphic*, IlAny);
    void changeLinkModel(const IlvGraphic* g);
 
    static void ChangeInteractorAcc(IlvManager*,
				    IlvView*,
				    IlvEvent&,
				    IlAny);
    void changeInteractor();
    static void Quit(IlvView*,
		     IlAny);

private:
    IlvContainer*		_panel;		// Main panel.
    IlvGrapher*			_graph;		// The grapher.
    IlAList			_graphicModels; // Graphic models for links.
    IlvTransformedGraphic*	_gModel;	// Visual representation.
    IlvMakeLinkInteractor*	_mkLinkInter; // Interactor to create links.
    IlvGraphSelectInteractor*	_selInter;    // Interactor to manipulate obj

    void init(IlvDisplay* dpy);
    
    // Not implemented
    IlvLinkHandleSample(const IlvLinkHandleSample&);
    IlvLinkHandleSample& operator=(const IlvLinkHandleSample&);

};

// --------------------------------------------------------------------------
void
IlvLinkHandleSample::init(IlvDisplay* dpy)
{
    //== Create the panel
    _panel = new IlvContainer(dpy, "Panel", title,
			      IlvRect(0, 0, 640, 600), IlFalse, IlTrue);
    _panel->setBackground(dpy->getColor("dimgray"));
    
    //== Sets the destroy callback that will invoke the current instance 
    //== destructor
    _panel->setDestroyCallback(Quit, this);

    //== Enable attachment handling
    IlvAttachmentsHandler::Set(_panel, new IlvAttachmentsHandler);

    //== Read the panel description file.
    //== This file contains the view ractangle and the palette of graphic
    //== objects that are used as link model.
    _panel->readFile("linkhand.ilv");

    //=========================================================
    //== Create a grapher and connect the view rectangle's view
    IlvViewRectangle* rectview =
	IL_CAST(IlvViewRectangle*, _panel->getObject("ViewRect"));
    if (!rectview) { // The file was not properly loaded, exit
	IlvFatalError("The panel description file could not be read");
	IlvExit(-1);
    }
    IlvView* view = rectview->getView();
    _graph = new IlvGrapher(dpy, 3);
    _graph->addView(view);
    
    //== Set the layer where the links will be added by the interactor.
    //== This layer is the bottom-most layer, which means that the links
    //== will appear under the nodes
    _graph->setInsertionLayer(0);

    //== Toggle undo mechanism. By hitting the 'u' key, undoable actions
    //== will be reverted.
    _graph->setUndoEnabled(IlTrue);

    //== Enable link manipulation through IlvGraphSelectInteractor
    _graph->setLinksEditable(IlTrue);
    
    //===============================================================
    //== Populate the grapher with nodes arranged in rows and columns
    char buf[32];
    IlvPalette* pal = dpy->getPalette(dpy->getColor("steelBlue"),
				      dpy->getColor("white"),
				      0, 0,
				      dpy->getFont("%arial-10-"));
    IlvGraphic* node;
    IlvRect r;
    IlUInt i;
    for (i = 0; i < NbNodes; ++i) {
	if (!(i % 8)) {
	    r.moveResize(10, 10 + IlvPos((i / 8) * 100), 48, 32);
	}
	else {
	    r.translate(100, 0);
	}
	sprintf(buf, "Node%lu", (unsigned long)i);
	node = new IlvReliefLabel(dpy, buf, r, 1, pal);
	_graph->addNode(node, IlFalse);
	IlvGenericPin* pin = new IlvGenericPin();
	pin->set(node);
	pin->addPin(node, r.center(), 0);
    }
    
    //=============================================================
    //== Create the factory and the interactor used to create links
    IlvMakeLinkHandleFactory* factory = new IlvMakeLinkHandleFactory();
    _mkLinkInter = new IlvMakeLinkInteractor;
    _mkLinkInter->handlePointerMoved(IlTrue);
    _mkLinkInter->setFactory(factory);
    _graph->setInteractor(_mkLinkInter, view);

    //=======================================================================
    //== Create an interactor to manipulate the nodes and links inside the
    //== grapher
    _selInter = new IlvGraphSelectInteractor;
    _selInter->opaqueMove(IlTrue);


    //=======================================================================
    //== Each graphic model has a button interactor that triggers the
    //== "ChangeLinkModelCB"
    //== named callback. We link this name to the C++ function that must be
    //== called when the user clicks on the object.
    _panel->registerCallback("ChangeLinkModelCB", ChangeLinkModelCB);
    
    //=======================================================================
    //== For each graphic model, create a copy and store it in the
    //== _graphicModels data member. This copy will be shared by the created
    //== links and by the visual representation of the model (_gModel)
    IlUInt count;
    IlvGraphic* const* objs = _panel->getObjects(count);
    IlPoolOf(Pointer)::Lock((IlAny*)objs);
    IlvGraphic* copy;
    for (i = 0; i < count; ++i) {
	if (objs[i]->getInteractor()) { // The object is a graphic model.
	    copy = objs[i]->copy();
	    if (!_gModel) {
		// Pick up the first one as initial graphic model
		_gModel = new IlvTransformedGraphic(copy, IlFalse);
		IlvRect r;
		_panel->getObject("LinkModelRect")->boundingBox(r);
		r.expand(-10, -10);
		_gModel->moveResize(r);
		_panel->addObject(_gModel);
		factory->setGraphicModel(copy);
	    }
	    _graphicModels.append(objs[i], copy);
	    objs[i]->setClientData(this);
	}
    }
    IlPoolOf(Pointer)::UnLock((IlAny*)objs);

    //== Add an accelerator that enable to switch between the two interactors
    _graph->addAccelerator(ChangeInteractorAcc, IlvKeyUp, ' ', 0, this);
    
    //== Toggle double buffering on 
    _graph->setDoubleBuffering(view, IlTrue);
}

// --------------------------------------------------------------------------
IlvLinkHandleSample::~IlvLinkHandleSample()
{
    delete _graph;
    delete _selInter;
    delete _mkLinkInter;
    delete IlvAttachmentsHandler::Set(_panel, 0);
    delete _panel;
}

// --------------------------------------------------------------------------
// Destroy callback.
void 
IlvLinkHandleSample::Quit(IlvView* view,
			  IlAny arg)
{
    IlvDisplay* display = view->getDisplay();
    delete IL_CAST(IlvLinkHandleSample*, arg);
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// - Accelerators to toggle between Select and MakeLink interactors
void 
IlvLinkHandleSample::ChangeInteractorAcc(IlvManager*, 
					 IlvView*, 
					 IlvEvent&, 
					 IlAny arg)
{
    IL_CAST(IlvLinkHandleSample*, arg)->changeInteractor();
}

// --------------------------------------------------------------------------
// - Switches between selection and link interactors
void 
IlvLinkHandleSample::changeInteractor()
{
    IlvManagerViewInteractor* inter =
	_graph->getInteractor(_graph->getFirstView());
    IlBoolean gModelVisible;
    if (inter == _mkLinkInter) {
	gModelVisible = IlFalse;
	_graph->setInteractor(_selInter, _graph->getFirstView());
    }
    else {
	gModelVisible = IlTrue;
	_graph->setInteractor(_mkLinkInter, _graph->getFirstView());
    }
    _panel->setVisible(_gModel, gModelVisible, IlTrue);
}

// --------------------------------------------------------------------------
// - Callback to change the graphic model of the link handle created
// - by the factory
void
IlvLinkHandleSample::ChangeLinkModelCB(IlvGraphic* g,
				       IlAny arg)
{
    IlvLinkHandleSample* sample = IL_CAST(IlvLinkHandleSample*, arg);
    sample->changeLinkModel(g);
}

// --------------------------------------------------------------------------
// - Changes the link model following selection
void 
IlvLinkHandleSample::changeLinkModel(const IlvGraphic* g)
{
    IlvGraphic* model = getGraphicModel(g);
    if (!model) {
	return;
    }
    _panel->initReDraw();
    _panel->invalidateRegion(_gModel);
    IlvRect bbox;
    _gModel->boundingBox(bbox);
    _gModel->setObject(model);
    _gModel->moveResize(bbox);
    _panel->invalidateRegion(_gModel);
    _panel->reDrawView();
    IL_CAST(IlvMakeLinkHandleFactory*, _mkLinkInter->getFactory())
	->setGraphicModel(model);
}

// --------------------------------------------------------------------------
// Entry point
// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    // Initialize the display.
    IlvDisplay* dpy = new IlvDisplay("LinkHandle", "", argc, argv);
    if (!dpy || dpy->isBad()) {
	IlvFatalError("Couldn't create display");
	if (dpy) {
	    delete dpy;
	}
	return -1;
    }
    IlPathName localPath(dpy->getHomePath());
    localPath.addDirectory("samples/grapher/linkhand/data");
    dpy->prependToPath(localPath);

    new IlvLinkHandleSample(dpy);

    IlvMainLoop();
    return 1;
}
