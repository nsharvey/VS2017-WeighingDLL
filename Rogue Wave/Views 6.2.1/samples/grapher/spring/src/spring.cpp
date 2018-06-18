// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/grapher/spring/src/spring.cpp
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
// Animated layout of a spring-embedder
// --------------------------------------------------------------------------
#include <ilviews/grapher/all.h>
#include <ilviews/graphics/all.h>
#include <ilviews/manager/quadtree.h>
#include <ilviews/base/evloop.h>
#include <ilviews/util/runtime.h>
#include <ilog/pathname.h>

#include <ilviews/bitmaps/png.h>
#include <centerpin.h>

#if defined(IL_STD)
IL_STDUSE
#  include <cmath>
#  include <cstdlib>
#else
#  include <stdlib.h>
#  include <math.h>
#endif

// --------------------------------------------------------------------------
// - Static vars
static IlvRunTimeType StartTime;
static IlvRunTimeType EndTime;
static const IlUInt NbUpdatesPerRedraw = 2;
static const IlDouble MaxNodeTranslation = 10;
static const int LinkLayer = 0;
static const int NodeLayer = 1;
static const char* title = "Spring embedder sample";

// --------------------------------------------------------------------------
// - LayoutHandler class
// - Performs the layout by computing the force vectors for all nodes
// - of the grapher
// --------------------------------------------------------------------------
class LayoutHandler {
public:
    LayoutHandler(IlvGrapher* grapher);
    ~LayoutHandler();
    
    IlvGrapher* getGrapher() const { return _grapher;}
    IlBoolean isRunning() const { return _running; }

    void animate(IlBoolean b);
    inline IlBoolean isAnimating() const { return _animate;}
    void run();
    void stop();
    IlBoolean relax();
    void setFixed(IlvGraphic* node,
		  IlBoolean fixed);
    
    //== Returns the layout handler associated to a grapher
    static inline LayoutHandler* Get(IlvGrapher* grapher)
    { 
	return grapher 
	    ? IL_CAST(LayoutHandler*, grapher->getProperty(GetSymbol())) 
	    : 0; 
    }

    static IlBoolean UpdateProc(IlAny arg);

private:
    IlvGrapher*		_grapher;
    IlBoolean		_running;
    IlBoolean		_animate;
    IlBoolean		_isInvalidating;
    IlArray		_nodes;
    IlArray		_links;
    IlvArrayOfPoints	_nodesCenter;
    IlAny		_procId;
    
    void _stop();
    void init();

    struct NodeInfo {
	NodeInfo() { 
	    _delta = new IlDouble[2];
	    _delta[0] = 0;
	    _delta[1] = 0; 
	    _center = 0;
	}
	~NodeInfo() { delete [] _delta; }
	IlDouble*   _delta;
	IlvPoint*   _center;
    };

    static inline NodeInfo* GetNodeInfo(const IlvGraphic* node)
    {
	return IL_CAST(NodeInfo*, node->getProperty(_nodeInfoSymbol));
    }

    static inline IlDouble* GetDelta(const IlvGraphic* node)
    {
	return GetNodeInfo(node)->_delta;
    }

    static inline IlvPoint* GetCenter(const IlvGraphic* node)
    {
	return GetNodeInfo(node)->_center;
    }
    
    static inline IlUInt GetLength(const IlvLinkImage* link)
    {
	return 50;
    }

    static IlSymbol* _linkLengthSymbol;
    static IlSymbol* _nodeInfoSymbol;
    static IlSymbol* GetSymbol();

};

// --------------------------------------------------------------------------
LayoutHandler::LayoutHandler(IlvGrapher* grapher)
    : _grapher(grapher),
      _running(IlFalse),
      _animate(IlTrue),
      _isInvalidating(IlFalse),
      _nodes(),
      _links(),
      _nodesCenter(),
      _procId(0)
  
{
    if (grapher) {
	grapher->addProperty(GetSymbol(), (IlAny)this);
    }
    init();
}

// --------------------------------------------------------------------------
LayoutHandler::~LayoutHandler()
{
    stop();
    getGrapher()->removeProperty(GetSymbol());
}

// --------------------------------------------------------------------------
void 
LayoutHandler::setFixed(IlvGraphic* node,
			IlBoolean fixed)
{
    NodeInfo* nodeInfo = GetNodeInfo(node);
    if (fixed) {	
	if (nodeInfo->_delta) {
	    delete [] nodeInfo->_delta;
	    nodeInfo->_delta = 0;
	}
    } else if (!nodeInfo->_delta) {
	nodeInfo->_delta = new IlDouble[2];
	nodeInfo->_delta[0] = 0.;
	nodeInfo->_delta[1] = 0.;
    }
}

// --------------------------------------------------------------------------
void 
LayoutHandler::animate(IlBoolean b) 
{ 
    if (_animate == b) return;
    _animate = b;
    if (b && isRunning()) {
	getGrapher()->reDraw();
    } else if (!b && _isInvalidating) {
	getGrapher()->reDrawViews();
	_isInvalidating = IlFalse;
    }
}

// --------------------------------------------------------------------------
void 
LayoutHandler::run()
{
    if (!isRunning()) {	
	_procId = IlvEventLoop::getEventLoop()->addIdleProc(UpdateProc, this);
	_running = IlTrue;
	StartTime = IlvRunTime();
    }
}

// --------------------------------------------------------------------------
void 
LayoutHandler::stop()
{
    if (isRunning()) {	
	IlvEventLoop::getEventLoop()->removeIdleProc(_procId);
	_stop();
    }
}
// --------------------------------------------------------------------------
void 
LayoutHandler::_stop()
{
    _running = IlFalse;
    if (_isInvalidating)
	getGrapher()->reDrawViews();
    else if (!isAnimating())
	getGrapher()->reDraw();
    EndTime = IlvRunTime();
    IlvPrint("Time: %.3f s", EndTime - StartTime);
}

// --------------------------------------------------------------------------
static void 
ConnectToCenterF(IlvGraphic* link,
		 IlAny arg)
{
    IL_CAST(IlvCenterPin*, arg)->setPinIndex(link, 0, IlTrue);
}

// --------------------------------------------------------------------------
static void 
ConnectToCenterT(IlvGraphic* link,
		 IlAny arg)
{
    IL_CAST(IlvCenterPin*, arg)->setPinIndex(link, 0, IlFalse);
}

// --------------------------------------------------------------------------
void
LayoutHandler::init()
{
    if (isRunning()) 
	stop();
    _nodes.empty();
    _links.empty();
    _nodesCenter.empty();
    
    IlvGrapher* graph = getGrapher();    
    IlUInt count;

    IlvGraphic* const* objs = graph->getObjects(count);
    IlPoolOf(Pointer)::Lock((void**)objs);
    IlvGrapherPin* pin;
    IlvGraphic* obj;
    IlUInt i;
    for (i = 0 ; i < count; ++i) {
	obj = objs[i];
	if (graph->isLink(obj)) {
	    _links.add((IlAny)obj);
	    graph->setLayer(obj, LinkLayer, IlFalse);
	} else if (graph->isNode(obj)) {	    
	    graph->setLayer(obj, NodeLayer, IlFalse);
	    _nodes.add((IlAny)obj); 
	    if (graph->isMoveable(obj)) {		
		//== Adds the property that holds the translation vector of
		//== a node during the layout
		obj->addProperty(_nodeInfoSymbol, (IlAny)new NodeInfo());
		
		//== Connects all links of the node to its center using 
		//== an IlvCenterPin instance. Since this operation can modify
		//== the geometry of the links, we use the 
		//== IlvGrapher::applyLinks methos
		pin = new IlvCenterPin();
		pin->set(obj);
		graph->applyLinks(obj, ConnectToCenterF,
				  pin, IlvLinkFrom, IlFalse);
		graph->applyLinks(obj, ConnectToCenterT,
				  pin, IlvLinkTo, IlFalse);
	    }
	}
    }
    _nodesCenter.setMaxLength(_nodes.getLength());
    IlvPoint* centerArray = _nodesCenter.getArray();
    for (i = 0; i < _nodes.getLength(); ++i) {
	GetNodeInfo(IL_CAST(IlvGraphic*, _nodes[i]))->_center = centerArray + i;
    }
    IlPoolOf(Pointer)::UnLock((void**)objs);
}

// --------------------------------------------------------------------------
// - Static init
IlSymbol* LayoutHandler::_linkLengthSymbol = IlSymbol::Get("LinkLength");
IlSymbol* LayoutHandler::_nodeInfoSymbol = IlSymbol::Get("NodeInfo");

// --------------------------------------------------------------------------
// - Performs one iteration of the algorithm by summing the force vectors 
// - applied on each node and translate them accordingly
IlBoolean 
LayoutHandler::relax() 
{
    static IlUInt cpt = 0;
    IlvGrapher* graph = getGrapher();

    if (isAnimating()) {
	if ((++cpt % NbUpdatesPerRedraw) == 1) {
	    _isInvalidating = IlTrue;
	    graph->initReDraws();
	}
	graph->initReDraws();
    }

    IlUInt nbLinks = _links.getLength();
    IlUInt nbNodes = _nodes.getLength();

    IlvLinkImage* link;
    IlUInt i,j, count;
    IlDouble* delta;
    IlDouble dx, dy, vx, vy, len;
    IlvRect bbox;
    IlvGraphic *node1, *node2;
    IlvPoint *center1, *center2;
    NodeInfo *nodeInfo1, *nodeInfo2;

    for (i = 0 ; i < nbNodes; ++i) {	
	node1 = IL_CAST(IlvGraphic*, _nodes[i]);
	node1->boundingBox(bbox);
	_nodesCenter[i].move(bbox.centerx(), bbox.centery());	
    }

    //== Adds the delta due to the stress on the links    
    for (i = 0 ; i < nbLinks; ++i) {
	link = IL_CAST(IlvLinkImage*, _links[i]);
	nodeInfo1 = GetNodeInfo(link->getFrom());
	nodeInfo2 = GetNodeInfo(link->getTo());
	center1 = nodeInfo1->_center;
	center2 = nodeInfo2->_center;
	vx = IL_CAST(IlDouble, center1->x() - center2->x());
	vy = IL_CAST(IlDouble, center1->y() - center2->y());	
	len = sqrt(vx * vx + vy * vy);
	len = (len == 0) ? .0001 : len;
	IlDouble f = (((IlDouble)GetLength(link))- len) / (len * 3);
	dx = f * vx;
	dy = f * vy;
	delta = nodeInfo2->_delta;
	if (delta) {
	    delta[0] -= dx;
	    delta[1] -= dy;
	}
	delta = nodeInfo1->_delta;
	if (delta) {
	    delta[0] += dx;
	    delta[1] += dy;
	}
    }

    for (i = 0 ; i < nbNodes; ++i) {
	node1 = IL_CAST(IlvGraphic*, _nodes[i]);
	nodeInfo1 = GetNodeInfo(node1);
	delta = nodeInfo1->_delta;
	
	if (!delta)
	  continue; // Fixed node
	dx = 0;
	dy = 0;	
	
	node1->boundingBox(bbox);
	bbox.expand(400);

	IlvGraphic* const* objs = 
	    graph->allIntersects(NodeLayer, count, bbox, 0);

	center1 = nodeInfo1->_center;
	for (j = 0 ; j < count; ++j) {
	    node2 = objs[j];
	    if (node2 == node1 || !graph->isNode(node2)) {
		continue;
	    }
	    center2 = GetCenter(node2);
	    vx = center1->x() - center2->x();
	    vy = center1->y() - center2->y();
	    len = vx * vx + vy * vy;
	    if (len == 0) {
		dx += rand() % 2;
		dy += rand() % 2;
	    } else { 
		dx += vx / len;
		dy += vy / len;
	    }
	}
	len = dx * dx + dy * dy;
	if (len > 0) {
	    len = sqrt(len) / 3;
	    delta[0] += dx / len;
	    delta[1] += dy / len;
	}
    }

    //== Apply the translation vector to all nodes.
    IlUInt sumDelta = 0;
    IlvPos deltaX, deltaY;
    IlUInt nbMovedNodes = 0;
    for (i = 0 ; i < nbNodes; ++i) {
	node1 = IL_CAST(IlvGraphic*, _nodes[i]);
	delta = GetDelta(node1);	
	if (delta) {
	    deltaX = IlvRoundDouble(IlvMax(-MaxNodeTranslation, 
					   IlvMin(MaxNodeTranslation,
						  delta[0])));
	    deltaY = IlvRoundDouble(IlvMax(-MaxNodeTranslation, 
					   IlvMin(MaxNodeTranslation,
						  delta[1])));
	    if (deltaX || deltaY) {
		sumDelta += IlvAbs(deltaX) + IlvAbs(deltaY);
		graph->translateObject(node1, deltaX, deltaY, isAnimating());
		nbMovedNodes++;
		delta[0] /= 2;
		delta[1] /= 2;
	    } else {
		delta[0] = 0;
		delta[1] = 0;
	    }
	}
    }

    if (isAnimating()) {
	graph->reDrawViews();
	if (!(cpt % NbUpdatesPerRedraw)) {
	    _isInvalidating = IlFalse;
	    graph->reDrawViews();
	} else
	    graph->disableRedrawTask();
    }

   if (sumDelta < 3 && nbMovedNodes < 3) {
	_stop();
       return IlFalse;
   } else
       return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean 
LayoutHandler::UpdateProc (IlAny arg)
{
    return !IL_CAST(LayoutHandler*, arg)->relax();
}

// --------------------------------------------------------------------------
IlSymbol* 
LayoutHandler::GetSymbol()
{
    static IlSymbol* symbol = IlSymbol::Get("__LayoutHandler");
    return symbol;
}


// --------------------------------------------------------------------------
// - SpringSelectInteractor
// - Subclass of IlvGraphSelectInteractor that is used to:
//	- Launch the layout when a node is moved.
//	- Set the selected nodes as "fixed" (i.e. not moved by the layout)
class SpringSelectInteractor
  : public IlvGraphSelectInteractor {
public:
    SpringSelectInteractor(IlvManager* mgr, IlvView* v) 
      : IlvGraphSelectInteractor(mgr, v) {
	opaqueMove(IlTrue);
    }

    virtual void   addedToSelection(IlvGraphic*);
    virtual void   removedFromSelection(IlvGraphic*);
    virtual void   doTranslate(const IlvPoint&);
};

// --------------------------------------------------------------------------
void   
SpringSelectInteractor::addedToSelection(IlvGraphic* node)
{
    IlvGraphSelectInteractor::addedToSelection(node);
    IlvGrapher* graph = IL_CAST(IlvGrapher*, getManager());
    if (!graph->isNode(node))
	return;
    LayoutHandler* handler = LayoutHandler::Get(graph);
    if (handler) 
	handler->setFixed(node, IlTrue);
}

// --------------------------------------------------------------------------
void   
SpringSelectInteractor::removedFromSelection(IlvGraphic* node)
{
    IlvGraphSelectInteractor::removedFromSelection(node);
    IlvGrapher* graph = IL_CAST(IlvGrapher*, getManager());
    if (!graph->isNode(node))
	return;
    LayoutHandler* handler = LayoutHandler::Get(graph);
    if (handler) 
	handler->setFixed(node, IlFalse);
}

// --------------------------------------------------------------------------
void   
SpringSelectInteractor::doTranslate(const IlvPoint& p)
{
    IlvGraphSelectInteractor::doTranslate(p);
    LayoutHandler* handler = LayoutHandler::Get((IlvGrapher*)getManager());	
    if (handler) {
	handler->animate(IlTrue);
	handler->run();
    }
    
}

// ----------------------------------------------------------------
// Destroy callback.
static void ILVCALLBACK
Quit(IlvView* top,
     IlAny arg)
{
    IlvGrapher* graph = IL_CAST(IlvGrapher*, arg);
    delete LayoutHandler::Get(graph);
    delete graph;
    IlvDisplay* d = top->getDisplay();
    delete d;
    IlvExit(0);
}

// ----------------------------------------------------------------
// Accelerator ('r') : Runs the layout
static void 
RunLayoutAcc(IlvManager* manager,
	     IlvView*,
	     IlvEvent&,
	     IlAny)
{
    LayoutHandler* handler = LayoutHandler::Get((IlvGrapher*)manager);
    if (handler)
	handler->run();
}

// ----------------------------------------------------------------
// Accelerator ('s') : Stops the layout
static void 
StopLayoutAcc(IlvManager* mgr,
	      IlvView*,
	      IlvEvent&,
	      IlAny)
{
    LayoutHandler* handler = LayoutHandler::Get((IlvGrapher*)mgr);
    if (handler)
	handler->stop();
}

// ----------------------------------------------------------------
// Accelerator ('a') : Toggles the animation mode of the layout
static void 
ToggleAnimateLayoutAcc(IlvManager* mgr,
		       IlvView* view,
		       IlvEvent&,
		       IlAny)
{
    LayoutHandler* handler = LayoutHandler::Get((IlvGrapher*)mgr);
    if (handler) {
	IlBoolean anim = !handler->isAnimating();
	handler->animate(anim);
	IlvManagerViewInteractor* inter = mgr->getInteractor(view);
	if (inter && !anim) {
	    mgr->removeInteractor(view);
	    delete inter;
	} else if (!inter && anim) {
	    inter = new SpringSelectInteractor(mgr, view);
	    mgr->setInteractor(inter);
	}
    }
}

// ----------------------------------------------------------------
// Accelerator (spaceBar) : Applies a random translation to all the 
// nodes and launch the layout.
static void 
ScrambleAcc(IlvManager* manager,
	    IlvView* view,
	    IlvEvent&,
	    IlAny)
{
    IlvGrapher* graph = (IlvGrapher*)manager;
    IlUInt count;
    IlvGraphic* const* nodes = graph->getNodes(count);
    IlPoolOf(Pointer)::Lock((IlAny*)nodes);
    for (IlUInt i = 0 ; i < count; ++i) {
	graph->translateObject(nodes[i],
			      (rand() % 100) - 50, (rand() % 100) - 50,
			      IlFalse);
    }
    IlPoolOf(Pointer)::UnLock((IlAny*)nodes);
    graph->reDraw();
    LayoutHandler* handler = LayoutHandler::Get((IlvGrapher*)manager);
    if (handler)
	handler->run();
    
}

// ----------------------------------------------------------------
// Accelerator ('w') : Moves all nodes within the visible 
// area of the main view.
static void 
ShrinkAcc(IlvManager* mgr,
	  IlvView* view,
	  IlvEvent&,
	  IlAny)
{
    IlvGrapher* graph = (IlvGrapher*)mgr;
    IlvRect rect;
    view->sizeVisible(rect);
    IlvPoint p(rect.center());
    if (mgr->getTransformer(view))
	mgr->getTransformer(view)->inverse(p);
    IlUInt count;
    IlvGraphic* const* nodes = graph->getNodes(count);
    IlPoolOf(Pointer)::Lock((IlAny*)nodes);
    for (IlUInt i = 0 ; i < count; ++i) {
	graph->moveObject(nodes[i],
			  p.x() + (rand() % rect.w()) - rect.w() / 2,
			  p.y() + (rand() % rect.h()) - rect.h() / 2,
			  IlFalse);
    }
    IlPoolOf(Pointer)::UnLock((IlAny*)nodes);
    graph->reDraw();
}

// ----------------------------------------------------------------
// Accelerator ('n' && 'l') : Toggles the visibility of nodes 
// and links
static void 
ToggleVisibilityAcc(IlvManager* mgr,
		    IlvView* view,
		    IlvEvent& evt,
		    IlAny)
{
    int layer = (evt.key() == 'n') ? NodeLayer : LinkLayer;
    mgr->setVisible(view, layer, !mgr->isVisible(view, layer));
    mgr->reDraw();
}

// ----------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    srand(4043);
    //== Initialize the display.
    IlvDisplay* dpy = new IlvDisplay("GraphLayout", "", argc, argv);
    if (!dpy || dpy->isBad()) {
	IlvFatalError("Couldn't create display");
	if (dpy)
	    delete dpy;
	return -1;
    }
    IlPathName localPath(dpy->getHomePath());
    localPath.addDirectory("samples/grapher/spring/data");
    dpy->prependToPath(localPath);
    
    IlvEventLoop::getEventLoop()->setLazyRedraw(0);

    //== Toggle quadtree optimization ON
    IlvSetOptimizeMode(IlTrue);
    
    //== Create a main view.
    IlvRect size(0, 0, 800, 600);
    IlvView* view = new IlvView(dpy, "GraphView", title, size, IlFalse);

    //== Create an overview view.
    IlvRect osize(size.w() + 10, size.y(), size.w() / 4, size.h() / 4);
    IlvView* overview = new IlvView(dpy, "Overview", title, osize, IlFalse);
    
    //== Create a grapher and connects the views
    IlvGrapher* graph = new IlvGrapher(dpy, 2, IlTrue);

    //== Read the file passed as argument
    graph->read(argc > 1 ? argv[--argc] : "balls.ilv");

    graph->addView(view);
    IlvBitmap* bgbmp = dpy->readBitmap("bgbitmap.png");
    graph->setBackground(view, 0, bgbmp);
    view->setDestroyCallback(Quit, graph);

    //== Hide link layer in main view
    graph->setVisible(view, LinkLayer, IlFalse);

    graph->addView(overview);
    graph->setBackground(overview, dpy->getColor("black"));
    overview->setDestroyCallback(Quit, graph);

    //== Hide the nodes in the overview window and
    //== make sure that their selection objects are invisible
    //== in the same view
    graph->setVisible(overview, NodeLayer, IlFalse);
    IlvDrawSelection::SetVisibleWhenObjectIsInvisible(IlFalse);

    //== Adjust the transformer on the overview window
    graph->fitTransformerToContents(overview, IlFalse, IlTrue);
    graph->zoomView(overview,
		    IlvPoint(osize.w() / 2, osize.h() / 2), .5, .5, IlFalse);
    
    //== Create the layout handler
    new LayoutHandler(graph);
  
    //== Add several accelerators
    graph->addAccelerator(ScrambleAcc, IlvKeyDown, ' ');
    graph->addAccelerator(ShrinkAcc, IlvKeyUp, 'w');
    graph->addAccelerator(RunLayoutAcc, IlvKeyUp, 'r');
    graph->addAccelerator(StopLayoutAcc, IlvKeyUp, 's');
    graph->addAccelerator(ToggleAnimateLayoutAcc, IlvKeyUp, 'a');
    graph->addAccelerator(ToggleVisibilityAcc, IlvKeyUp, 'n');
    graph->addAccelerator(ToggleVisibilityAcc, IlvKeyUp, 'l');
    
    //== Adds an interactor to manipulate the nodes
    IlvGraphSelectInteractor* selinter =
        new SpringSelectInteractor(graph, view);
    graph->setInteractor(selinter, view);
    graph->allowEnsureVisible(IlFalse);

    graph->setDoubleBuffering(view, IlTrue);
    graph->setDoubleBuffering(overview, IlTrue);  
    graph->reDraw();

    view->show();
    overview->show();

    IlvMainLoop();
    return 1;
}
