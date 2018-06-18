// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/grapher/design/src/design.cpp
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
// Using the grapher to demonstrate GrapherPins
// --------------------------------------------------------------------------

#include <ilviews/grapher/all.h>
#include <ilviews/gadgraph/rectscgr.h>
#include <ilviews/gadmgr/mviselect.h>
#include <ilviews/graphics/icon.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/toolbar.h>
#include <ilog/pathname.h>

#include <fixedpin.h>

#if defined(IL_STD)
IL_STDUSE
#  include <fstream>
#  include <cstdio>
#else
#  include <fstream.h>
#  include <stdio.h>
#endif
IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
// - Static vars
static const char* title = "ElecDesign";

// --------------------------------------------------------------------------
// Definition of icons
#define vcc_width 20
#define vcc_height 12
static unsigned char vcc_bits[] = {
   0x07, 0x44, 0x00, 0x47, 0x44, 0x00, 0x47, 0x44, 0x00, 0xf2, 0x29, 0x09,
   0x42, 0xa8, 0x04, 0x42, 0x10, 0x09, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00,
   0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x05, 0x00, 0x00, 0x02, 0x00, 0x00};

#define ground_width 13
#define ground_height 12
static unsigned char ground_bits[] = {
   0x40, 0x00, 0xa0, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00,
   0xff, 0x1f, 0x92, 0x04, 0x49, 0x12, 0x24, 0x09, 0x92, 0x04, 0x49, 0x12};

#define hresistr_width 28
#define hresistr_height 9
static unsigned char hresistr_bits[] = {
   0x80, 0x88, 0x88, 0x00, 0x80, 0x88, 0x88, 0x00, 0x80, 0x88, 0x88, 0x00,
   0x42, 0x55, 0x55, 0x05, 0x5d, 0x55, 0x55, 0x0b, 0x52, 0x55, 0x55, 0x04,
   0x20, 0x22, 0x22, 0x00, 0x20, 0x22, 0x22, 0x00, 0x20, 0x22, 0x22, 0x00};

#define vresistr_width 9
#define vresistr_height 28
static unsigned char vresistr_bits[] = {
   0x10, 0x00, 0x28, 0x00, 0x10, 0x00, 0x10, 0x00, 0x18, 0x00, 0x07, 0x00,
   0x38, 0x00, 0xc0, 0x01, 0x38, 0x00, 0x07, 0x00, 0x38, 0x00, 0xc0, 0x01,
   0x38, 0x00, 0x07, 0x00, 0x38, 0x00, 0xc0, 0x01, 0x38, 0x00, 0x07, 0x00,
   0x38, 0x00, 0xc0, 0x01, 0x38, 0x00, 0x07, 0x00, 0x38, 0x00, 0xc0, 0x01,
   0x30, 0x00, 0x10, 0x00, 0x28, 0x00, 0x10, 0x00};

#define npn_width 15
#define npn_height 14
static unsigned char npn_bits[] = {
   0x00, 0x20, 0x80, 0x50, 0x80, 0x30, 0x80, 0x08, 0x80, 0x04, 0x82, 0x02,
   0xfd, 0x01, 0x82, 0x02, 0x80, 0x24, 0x80, 0x28, 0x80, 0x30, 0x80, 0x3c,
   0x00, 0x50, 0x00, 0x20};

#define iclinkc_width 16
#define iclinkc_height 16
static unsigned char iclinkc_bits[] = {
   0x00, 0x78, 0x00, 0x48, 0xfc, 0x4f, 0x04, 0x78, 0x04, 0x00, 0x04, 0x00,
   0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00,
   0x0f, 0x00, 0x09, 0x00, 0x09, 0x00, 0x0f, 0x00};

#define select_width 16
#define select_height 16
static unsigned char select_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0xfc, 0x01, 0xfc, 0x00, 0x7c, 0x00, 0x7c, 0x00,
   0xfc, 0x00, 0xcc, 0x01, 0x84, 0x03, 0x00, 0x07, 0x00, 0x0e, 0x00, 0x1c,
   0x00, 0x38, 0x00, 0x30, 0x00, 0x40, 0x00, 0x00};

// --------------------------------------------------------------------------
static IlvDrawSelection*
MakeNodeSelection(IlvManager* mgr,
		  IlvGraphic* g)
{
    IlvDisplay* dpy = mgr->getDisplay();
    IlvPalette* pal =
	dpy->getPalette(dpy->getColor("white"), dpy->getColor("red"));
    IlvGraphNodeSelection* sel = new IlvGraphNodeSelection(dpy, g, 3, pal);
    sel->drawFrame(IlFalse);
    return sel;
}

// --------------------------------------------------------------------------
static inline IlvBitmap*
MakeBitmap(IlvDisplay* dpy,
	   IlvDim width,
	   IlvDim height,
	   unsigned char* bits)
{
    return new IlvBitmap(dpy, width, height, 1, bits, IlTrue, 8);
}
// --------------------------------------------------------------------------
// Definition of the class Element
// --------------------------------------------------------------------------
class Element
{
public:
    Element(IlvBitmap*  bitmap,
	    const char* name,
	    FixedPin* pin)
        : _bitmap(bitmap),
	  _pin(pin)
    {
	bitmap->setName(name);
	bitmap->lock();
    }
    ~Element()
    {
	_bitmap->unLock();
	delete _pin;
    }
    // ____________________________________________________________
    IlvBitmap* getBitmap() const { return _bitmap; }
    FixedPin*  getPin()    const { return _pin; }
private:
    IlvBitmap* _bitmap;
    FixedPin*       _pin;
};
Element* elements[5];

// --------------------------------------------------------------------------
class CopyObjectInteractor
    : public IlvManagerViewInteractor
{
public:
    CopyObjectInteractor(IlvManager*    manager,
			 IlvView*       view,
			 int idx)
        : IlvManagerViewInteractor(manager, view),
	  _element(elements[idx]),
	  _ghost(0),
	  _location()
	{}
    // ____________________________________________________________
    virtual void init();
    virtual void abort() ;
    virtual IlBoolean handleEvent(IlvEvent& event);
    virtual void drawGhost();
private:
    Element*   _element;
    IlvBitmap* _ghost;
    IlvPoint   _location;
};

// --------------------------------------------------------------------------
// Quit from the Window Manager
// --------------------------------------------------------------------------
static void
Quit(IlvView* top, IlAny display)
{
    delete top;
    for (int loop = 0; loop < 5; ++loop) {
	delete elements[loop];
    }
    delete (IlvDisplay*)display;
    IlvExit(0);
}


// --------------------------------------------------------------------------
void
CreateInteractors(IlvToolBar* toolbar,
		  IlvGrapher* graph,
		  IlvView* view)
{
    IlvDisplay* dpy = view->getDisplay();
    //== Create an interactor selector to switch between editing modes.
    IlvMenuItemSelector* itemSelector =
	new IlvMenuItemSelector(IlSymbol::Get("EditingModes", IlFalse));
    IlvManagerViewInteractorSelector* interSelector =
	new IlvManagerViewInteractorSelector(graph, view, itemSelector);
    graph->installViewHook(interSelector);

    //== Helper macro to add items connected to editing modes.
#define EDITMODE(name, item, inter)				\
    item->setName(name);                                        \
    itemSelector->addItem(item);                                \
    interSelector->link(IlSymbol::Get(name, IlFalse), inter);

    //== Create interactor to manipulate nodes
    IlvGraphSelectInteractor* select =
        new IlvGraphSelectInteractor(graph, view);
    select->opaqueMove(IlTrue);

    //== Interactor to create links
    IlvMakeLinkInteractor* mkLinkInter =
	new IlvMakeOneLinkImageInteractor(graph, view, IlFalse);
    mkLinkInter->setMakeNodeSelection(MakeNodeSelection);
    mkLinkInter->handlePointerMoved(IlTrue);

    const IlUShort nbItems = 8;
    IlvMenuItem* items[nbItems];

    items[0] = new IlvMenuItem(MakeBitmap(dpy, select_width, select_height,
					  select_bits));
    EDITMODE("Select", items[0], select);

    items[1] = new IlvMenuItem(MakeBitmap(dpy, iclinkc_width,
					  iclinkc_height, iclinkc_bits));
    EDITMODE("MakeLink", items[1], mkLinkInter);

    items[2] = new IlvMenuItem(); // Separator

    char name[16];
    for (IlUShort i = 3; i < nbItems; ++i) {
	items[i] = new IlvMenuItem(elements[i - 3]->getBitmap());
	sprintf(name, "Element%d", i - 2);
	EDITMODE(name, items[i],
		 new CopyObjectInteractor(graph, view, i - 3));
    }
    toolbar->setItems(items, nbItems);
    // Connect the selector to the toolbar.
    itemSelector->addTo(toolbar);
    graph->setInteractor(select);
}

// --------------------------------------------------------------------------
static void
Save(IlvManager* mgr,
     IlvView*,
     IlvEvent&,
     IlAny arg)
{
    const char* filename = "output.ilv";
    ofstream stream(filename,IlOutputStreamMode);
    if (!stream) {
	IlvFatalError("Couldn't open %s for writing", filename);
	return;
    }
    mgr->save(stream);
}

// --------------------------------------------------------------------------
static void
Load(IlvManager* mgr,
     IlvView*,
     IlvEvent&,
     IlAny arg)
{
    const char* filename = "output.ilv";
    if (filename) {
	mgr->read(filename);
	mgr->reDraw();
    }
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* dpy = new IlvDisplay("Design", "", argc, argv);
    if (!dpy || dpy->isBad()) {
	IlvFatalError("Couldn't create display");
	if (dpy)
	    delete dpy;
	return 1;
    }
    IlPathName localPath(dpy->getHomePath());
    localPath.addDirectory("samples/grapher/design/data");
    dpy->prependToPath(localPath);

    // Initialize array of elements
    elements[0] = new Element(MakeBitmap(dpy,
					 vcc_width, vcc_height, vcc_bits),
			      "vcc",
			      new FixedPin(1, 1, 10));
    elements[1] = new Element(MakeBitmap(dpy, ground_width,
					 ground_height, ground_bits),
			      "ground",
			      new FixedPin(1, 6, 1));
    elements[2] = new Element(MakeBitmap(dpy,
					 hresistr_width, hresistr_height,
					 hresistr_bits),
			      "hresistor",
			      new FixedPin(2, 1, 4, 26, 4));
    elements[3] = new Element(MakeBitmap(dpy, vresistr_width,
					 vresistr_height, vresistr_bits),
			      "vresistor",
			      new FixedPin(2, 4, 1, 4, 26));
    elements[4] = new Element(MakeBitmap(dpy, npn_width,
					 npn_height, npn_bits),
			      "npn",
			      new FixedPin(3, 1, 6, 13, 1, 13, 12));
    IlvGadgetContainer* panel = new IlvGadgetContainer(dpy, title, title,
						       IlvRect(0, 0,
							       640, 480),
						       IlFalse, IlFalse);
    panel->setDestroyCallback(Quit, dpy);
    panel->allowFocus(IlFalse);

    panel->readFile("design.ilv");
    IlvSCGrapherRectangle* grapherRect =
	IL_CAST(IlvSCGrapherRectangle*, panel->getObject("GraphRect"));
    IlvToolBar* toolbar = IL_CAST(IlvToolBar*, panel->getObject("Toolbar"));

    IlvGrapher* graph = grapherRect->getGrapher();
    IlvView* graphView = grapherRect->getView();
    graph->setLinksEditable(IlTrue);

    CreateInteractors(toolbar, graph, graphView);
    graph->addAccelerator(Save, IlvKeyUp, IlvCtrlChar('S'));
    graph->addAccelerator(Load, IlvKeyUp, IlvCtrlChar('L'));

    graph->setBackground(graphView, dpy->getColor("white"));
    graph->setDoubleBuffering(graphView, IlTrue);
    graph->setInsertionLayer(0);

    panel->show();
    IlvMainLoop();
    return 0;
}

// --------------------------------------------------------------------------
void
CopyObjectInteractor::init()
{
    _ghost = 0;
}

// --------------------------------------------------------------------------
void
CopyObjectInteractor::abort()
{
    _ghost = 0;
}

// --------------------------------------------------------------------------
IlBoolean
CopyObjectInteractor::handleEvent(IlvEvent& event)
{
    switch (event.type()) {
    case IlvButtonDown:
	_ghost = _element->getBitmap();
	_location.move(event.x(), event.y());
	drawGhost();
	return IlTrue;
    case IlvButtonDragged:
	drawGhost();
	_location.move(event.x(), event.y());
	drawGhost();
	return IlTrue;
    case IlvButtonUp:
	drawGhost();
	if (_ghost) {
	    _ghost = 0;
	    IlvBitmap* bmp = _element->getBitmap();
	    IlvTransformer* t = getManager()->getTransformer(getView());
	    IlvPoint p(event.x(), event.y());
	    IlvPos dx = IL_CAST(IlvPos,bmp->width()/2);
	    IlvPos dy = IL_CAST(IlvPos,bmp->height()/2);
	    p.translate(dx,dy);
	    if (t)
		t->inverse(p);
	    p.translate(-dx,-dy);
	    IlvPalette* pal =
	        getDisplay()->getPalette(0, getDisplay()->getColor("blue"));
	    IlvIcon* element =
		new IlvTransparentIcon(getDisplay(), p,
				       _element->getBitmap(), pal);
	    element->setNamedProperty(new FixedPin(*(_element->getPin())));
	    ((IlvGrapher*)getManager())->addNode(element);
	    callPrevious();
	}
	return IlTrue;
    default:
	;
    }
    return getManager()->shortCut(event,getView());
}

// --------------------------------------------------------------------------
void
CopyObjectInteractor::drawGhost()
{
    if (_ghost) {
	getView()->drawBitmap(getManager()->getPalette(),
			      _ghost,
			      IlvRect(0, 0,
				      _ghost->width(), _ghost->height()),
			      _location);
    }
}
