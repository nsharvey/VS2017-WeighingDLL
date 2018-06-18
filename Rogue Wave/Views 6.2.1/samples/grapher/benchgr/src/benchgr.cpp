// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/grapher/benchgr/src/benchgr.cpp
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
// Using the grapher
// --------------------------------------------------------------------------

#include <ilviews/grapher/grapher.h>
#include <ilviews/grapher/inters.h>
#include <ilviews/graphics/zoomlab.h>
#include <ilviews/graphics/relflab.h>
#include <ilviews/graphics/ellipse.h>
#include <ilviews/manager/quadtree.h>
#include <ilviews/util/runtime.h>
#include <ilviews/util/util.h>

#if defined(IL_STD)
#include <cstdlib>
#include <cmath>
#include <cstdio>
#else
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#endif

static const char* title = "Grapher Bench Sample";
static IlvRect size(0, 0, 800, 600);


//== Tree
static IlUInt NbChilds = 10;
static const IlUInt Level = 3;
static const IlUInt NbColors = 15;
static const char* ColorNames[] = {
    "red",
    "lightsteelblue",
    "cadetblue",
    "pink",
    "gold",
    "wheat",
    "cornflowerblue",
    "yellow",
    "green",
    "salmon",
    "magenta",
    "blue",
    "white",
    "maroon",
    "violet"
};

//== Circle
static IlUInt CircleLevel = 10;
static const IlUInt FirstCircleCount = 5;
static const IlvPos CircleRadius = 200;

// --------------------------------------------------------------------------
class CenterLink
    : public IlvLinkImage
{
public:
    CenterLink(IlvDisplay* display,
	       IlBoolean  oriented,
	       IlvGraphic* from,
	       IlvGraphic* to,
	       IlvPalette* palette = 0)
    : IlvLinkImage(display, oriented, from, to, palette) 
    {}
  
protected:  
  void      computePoints(IlvPoint& src,
			  IlvPoint& dst,
			  const IlvTransformer* t = 0) const;
};

void      
CenterLink::computePoints(IlvPoint& src,
			  IlvPoint& dst,
			  const IlvTransformer* t) const
{
    IlvRect bbox;
    IlvGrapherPin* pin = IlvGrapherPin::Get(getFrom());
    if (!pin || !pin->getLinkLocation(getFrom(), this, t, src)) {
	getFrom()->boundingBox(bbox, t);
	src.move(bbox.centerx(), bbox.centery());
    }
    pin = IlvGrapherPin::Get(getTo());
    if (!pin || !pin->getLinkLocation(getTo(), this, t, dst)) {
	getTo()->boundingBox(bbox, t);
	dst.move(bbox.centerx(), bbox.centery());
    }
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
Quit(IlvView* top,
     IlAny g)
{
    IlvGrapher* grapher = (IlvGrapher*)g;
    IlvDisplay* display = grapher->getDisplay();
    delete grapher;
    delete top;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
static void
MakeCircleGraph(IlvGrapher*	    graph,
		IlUInt		    level = 1,
		IlUInt		    innerCount = 0,
		IlvGraphic* const*  circle  = 0)
{
    IlvDisplay* dpy = graph->getDisplay();
    IlvGraphic** nodes;
    IlvPoint p;
    IlvLinkImage* link;
    IlUInt i;
    IlUInt count = (level == 1) ? FirstCircleCount : innerCount * 2;
    IlDouble radius = CircleRadius * level * sqrt((double)level);
    IlDouble stepAngle = 2 * IlvPi / count;
    nodes = new IlvGraphic*[count];
    IlvIntensity intensityStep =
	IL_CAST(IlvIntensity, (level * 65535) / CircleLevel);
    IlvColor* color = 
	dpy->getColor((IlvIntensity)(65535 - intensityStep / 2),
		      (IlvIntensity)(65535 - intensityStep),
		      (IlvIntensity)(65535 - intensityStep));
    IlvPalette* pal = dpy->getPalette(0, color);
    IlvDim nodeRadius = IL_CAST(IlvDim, (IlvPi * radius) / (2 * count));
    if (!nodeRadius)
	nodeRadius = 1;
    for (i = 0; i < count; ++i) {
	p.move(IlvRoundDouble(cos(stepAngle * i) * radius),
	       IlvRoundDouble(sin(stepAngle * i) * radius));
	nodes[i] = new IlvFilledEllipse(dpy, p, nodeRadius, pal);
    }
    color = dpy->getColor((IlvIntensity)(65535 - intensityStep),
			  (IlvIntensity)(65535 - intensityStep),
			  (IlvIntensity)(65535 - intensityStep / 2));
    pal = dpy->getPalette(0, color);
    for (i = 0; i < count; ++i) {
	graph->addNode(nodes[i], IlFalse, 1);
	if (i > 0) {
	    link = new CenterLink(dpy, IlFalse, nodes[i - 1], nodes[i], pal);
	    graph->addLink(link, IlFalse, 0);
	}
    }
    graph->addLink(new CenterLink(dpy, IlFalse, nodes[i - 1], nodes[0], pal),  
		   IlFalse, 0);

    if (circle) {
	for (i = 0; i < innerCount; ++i) {
	    link = new CenterLink(dpy, IlFalse, circle[i], nodes[2 * i], pal);
	    graph->addLink(link, IlFalse, 0);
	    link = new CenterLink(dpy, IlFalse, circle[i], nodes[2 * i + 1],
				  pal);
	    graph->addLink(link, IlFalse, 0);
	}
    }
    circle = nodes;
   
    if (++level <= CircleLevel) {
	MakeCircleGraph(graph, level, count, circle);
    }
    delete [] nodes;
}

// --------------------------------------------------------------------------
static void
MakeTreeGraph(IlvGrapher*   grapher,
	      IlUInt	    level = 0,
	      IlvGraphic*   root  = 0)
{
    IlvDisplay* dpy = grapher->getDisplay();
    if (!root) {
	root = new IlvReliefLabel(dpy, IlvPoint(1000, 1000), "Root", 1);
	root->setBackground(dpy->getColor("red"));
	grapher->addNode(root, IlFalse, 1);
    }
    if (++level > Level)
	return;
    char buf[80];
    IlvGraphic* son;
    IlvPalette* pal =
      dpy->getPalette(0, dpy->getColor(ColorNames[level % NbColors]),
		      0, 0, dpy->getFont("%arial-10-"));
    for(IlUInt i = 0; i < NbChilds; i++) {
	sprintf(buf, "Leaf%lu-%lu", (unsigned long)level, (unsigned long)i);
	son = new IlvZoomableLabel(dpy, IlvPoint(rand() % 1000,
						 rand() % 1000), buf, pal);
	grapher->addNode(son, IlFalse, 1);
	grapher->addLink(new IlvDoubleLinkImage(dpy, IlvHorizontalLink, 
						IlFalse, root, son, pal),
			 IlFalse, 0);
	MakeTreeGraph(grapher, level, son);	   
    }
    if (level == 1)
        grapher->nodeXPretty(root, 100, 6, IlFalse);
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    if (argc > 1)
        CircleLevel = atoi(argv[--argc]);
    
    IlvDisplay* dpy = new IlvDisplay("Grapher Bench", "", argc, argv);
    if (!dpy || dpy->isBad()) {
	IlvFatalError("Couldn't create display");
	if (dpy)
	    delete dpy;
	return 1;
    }
    IlvEventLoop::getEventLoop()->setLazyRedraw(0);
    //== Toggle quadtree optimization ON
    IlvSetOptimizeMode(IlTrue);

    IlvGrapher* graph = new IlvGrapher(dpy, 3);
    IlvView* view = new IlvView(dpy, "GraphView" ,title, size, IlTrue, IlFalse);

    view->setDestroyCallback(Quit, graph);
    graph->addView(view);
    IlvGraphSelectInteractor* select =
        new IlvGraphSelectInteractor(graph, view);
    //select->opaqueMove(IlTrue);
    graph->setInteractor(select);
    IlvRunTimeType startTime = IlvRunTime();
    MakeCircleGraph(graph);
    IlvRunTimeType endTime = IlvRunTime();
    IlvPrint("Grapher has stored %d objects in %.3f seconds", 
	     graph->getCardinal(), endTime - startTime);
    graph->fitTransformerToContents(view, IlFalse, IlTrue);
    graph->setBackground(view, dpy->getColor("black"));
    graph->setDoubleBuffering(view, IlTrue);
    view->show();
    IlvMainLoop();
    return 0;
}
