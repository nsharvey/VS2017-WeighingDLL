// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/grapher/simple/src/simple.cpp
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
// Basic grapher sample. 
// --------------------------------------------------------------------------

#include <ilviews/grapher/all.h>
#include <ilviews/graphics/shadlab.h>
#include <ilviews/graphics/relflab.h>

#if defined(IL_STD)
IL_STDUSE
#  include <cmath>
#  include <cstdlib>
#else
#  include <stdlib.h>
#  include <math.h>
#endif

static const char* title = "Simple Grapher Sample";

// --------------------------------------------------------------------------
// - Make the graph 'complete': add links so that each node is 
// - connected to each of the others. 
static void 
MakeGraphComplete(IlvGrapher* graph)
{

    IlUInt count;
    IlvGraphic* const* nodes = graph->getNodes(count);
    IlPoolOf(Pointer)::Lock((IlAny*)nodes);
    IlUInt i, j;
    IlvGraphic *node1, *node2;
    IlvDisplay* dpy = graph->getDisplay();
    for (i = 0 ; i < count; ++i) {
	node1 = nodes[i];
	for (j = i + 1 ; j < count; ++j) {
	    node2 = nodes[j];
	    if (!graph->isLinkBetween(node1, node2)) {
		graph->addLink(new IlvLinkImage(dpy, IlFalse, node1, node2),
			       IlFalse);
	    }
	}
    }
    IlPoolOf(Pointer)::UnLock((IlAny*)nodes);
    //== Full redraw
    graph->reDraw();
}

// --------------------------------------------------------------------------
// - Replaces all links with a copy pf [linkModel]
static void 
ChangeLinks(IlvGrapher* graph,
	    IlvGrapher* node,
	    IlvLinkImage* linkModel)
{
    if (!linkModel) {
      return;
    }
    if (node) {
    }
    else {
	IlUInt count;
	IlvLinkImage* const* links = graph->getLinks(count);
	//=! We must lock the array to ensure that its contents is not
	//=!  overwritten by another method
	IlPoolOf(Pointer)::Lock((IlAny*)links);
	IlvLinkImage* link;
	IlvLinkImage* newLink;
	for (IlUInt i = 0 ; i < count; ++i) {
	    link = links[i];
	    if (graph->isNode(links[i])) {
		continue;
	    }
	    newLink = IL_CAST(IlvLinkImage*, linkModel->copy());
	    newLink->setPalette(link->getPalette());
	    newLink->setOriented(link->isOriented());
	    graph->changeLink(link, newLink, IlFalse);
	    //=! IlvGrapher::changeLink does not delete the replaced link
	    delete link;
	}
    	//=! A locked array must always be unlocked when we are done with it.
	//=! Otherwise, the memory is never recycled.
	IlPoolOf(Pointer)::UnLock((IlAny*)links);
    }
    graph->reDraw();
}

// --------------------------------------------------------------------------
// - Accelerators
static void 
MakeCompleteAcc(IlvManager* manager,
		IlvView*,
		IlvEvent&,
		IlAny)
{
    MakeGraphComplete((IlvGrapher*)manager);
}

// --------------------------------------------------------------------------
static void 
ChangeLinkToDoubleAcc(IlvManager* mgr,
		      IlvView*,
		      IlvEvent&,
		      IlAny)
{
    IlvLinkImage* linkModel = 
	new IlvDoubleLinkImage(mgr->getDisplay(), IlFalse, 0, 0);
    ChangeLinks((IlvGrapher*)mgr, 0, linkModel);
    delete linkModel;
}

// --------------------------------------------------------------------------
static void 
SelectLink(IlvGraphic* g,
	   IlAny arg)
{
   IlvGrapher* graph = (IlvGrapher*)arg;
   graph->setSelected(g, IlTrue);
}

// --------------------------------------------------------------------------
static void 
DoubleClickAcc(IlvManager* manager,
	       IlvView* view,
	       IlvEvent& evt,
	       IlAny)
{
    IlvGrapher* graph = (IlvGrapher*)manager;
    IlvPoint p(evt.x(), evt.y());
    IlvGraphic* obj = graph->lastContains(p, view);
    if (obj) {
	if (graph->isNode(obj)) {
	    IlvPrint("Click on a NODE");
	    graph->mapLinks(obj, SelectLink, graph, IlvLinkAny);
	}
	else if (graph->isLink(obj)) {
	    IlvPrint("Click on a LINK");
	}
	else {
	    IlvPrint("Click on a REGULAR GRAPHIC");
	}
    }
}

// --------------------------------------------------------------------------
// - Destroy callback.
static void ILVCALLBACK
Quit(IlvView* top,
     IlAny graph)
{
    delete (IlvGrapher*)graph;
    IlvDisplay* d = top->getDisplay();
    delete d;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// - Main.
int
main(int argc, char* argv[])
{

    //== Initialize the display.
    IlvDisplay* dpy = new IlvDisplay("GraphLayout", "", argc, argv);
    if (!dpy || dpy->isBad()) {
	IlvFatalError("Couldn't create display");
	if (dpy) {
	    delete dpy;
	}
	return -1;
    }
    
    //== Create a view.
    IlvView* view = new IlvView(dpy, "GraphView",
				title, IlvRect(0, 0, 640, 480),
				IlTrue, IlFalse);

    //== Create a grapher.
    IlvGrapher* graph = new IlvGrapher(dpy, 2, IlTrue);
    graph->setLinksEditable(IlTrue);

    //== Attach the view to the grapher
    graph->addView(view);
    view->setDestroyCallback(Quit, graph);
    
    //== Create 4 graphic objects and add them as node in the grapher
    IlvPalette* pal = dpy->getPalette(dpy->getColor("lightsteelblue"));
    IlvGraphic* node1 = 
	new IlvShadowLabel(dpy, "Node1", IlvRect(100, 100, 50, 40),
			   1, IlvCenter, pal);
    IlvGraphic* node2 = 
	new IlvShadowLabel(dpy, "Node2", IlvRect(300, 250, 50, 40),
			   1, IlvCenter, pal);
    IlvGraphic* node3 = 
	new IlvShadowLabel(dpy, "Node3", IlvRect(200, 400, 50, 40),
			   1, IlvCenter, pal);
    IlvGraphic* node4 = 
	new IlvReliefLabel(dpy, "Node4", IlvRect(20, 400, 50, 40), 2, pal);
    graph->addNode(node1);
    graph->addNode(node2);
    graph->addNode(node3);
    graph->addNode(node4);

    //== Create and add an ordinary graphic object
    pal = dpy->getPalette(dpy->getColor("steelblue"));
    IlvGraphic* g = 
	new IlvReliefLabel(dpy, "Regular Graphic", IlvRect(400, 150,
							   150, 40),
			   2, pal);
    graph->addObject(g);

    
    //== Create 3 links and add them to the grapher
    pal = dpy->getPalette(0, dpy->getColor("black"), 0, 0, 0, 0, 2);
    graph->addLink(new IlvLinkImage(dpy, IlTrue, node1, node2));
    pal = dpy->getPalette(0,dpy->getColor("blue"));
    graph->addLink(new IlvOneLinkImage(dpy, IlvVerticalLink, IlTrue,
				       node1, node3, pal));
    graph->addLink(new IlvOneLinkImage(dpy, IlvHorizontalLink, IlTrue,
				       node3, node2, pal));

    //== Add some accelerators
    graph->addAccelerator(DoubleClickAcc, IlvDoubleClick, IlvLeftButton, 0);
    graph->addAccelerator(MakeCompleteAcc, IlvKeyUp, ' ', 0);
    graph->addAccelerator(ChangeLinkToDoubleAcc, IlvKeyUp, 'd', 0);
    
    //== Set a select interactor on the grapher view.
    IlvGraphSelectInteractor* selinter =
        new IlvGraphSelectInteractor(graph, view);
    selinter->opaqueMove(IlTrue);
    selinter->opaqueReshape(IlTrue);
    graph->setInteractor(selinter);
    graph->setBackground(view, dpy->getColor("lightgray"));
    graph->setDoubleBuffering(view, IlTrue);

    view->show();
    IlvMainLoop();
    return 1;
}
