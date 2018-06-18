// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/legend.cpp
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// The implementation of the Legend methods.
// --------------------------------------------------------------------------
#include <builder.h>
#include <legend.h>
#include <scalecombo.h>
#include <ilviews/manager/holder.h>
#include <ilviews/manager/layer.h>
#include <ilviews/graphics/all.h>
#include <ilviews/gadgets/rectgadc.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/slider.h>
#include <ilviews/gadgets/slist.h>
#include <ilviews/gadgets/scombo.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/maps/format/maptloader.h>
#include <ilviews/maps/projection/allprojs.h>
#include <ilviews/maps/projection/projitf.h>
#include <ilviews/maps/adapter.h>
#include <ilviews/maps/mapinfo.h>
#include <ilviews/maps/graphics/mapgenpath.h>
#include <ilviews/maps/scalefilter.h>
#include <ilviews/maps/geometry/all.h>
#if defined(HAS_SDO_SUPPORT)
#include <ilviews/maps/format/oracle/objectmodel/8ilayer.h>
#include <ilviews/maps/format/oracle/objectmodel/8itileload.h>
#endif
#include <ilviews/maps/rendering/all.h>

#if defined(IL_STD)
#  include <cstring>
IL_STDUSE
#else  /* !IL_STD */
#  include <string.h>
#  include <stdio.h>
#endif /* !IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

// -------------------------------------------------------------------------
static const char* stdDashNames[] = {
    "solid",
    "dot",
    "dash",
    "dashdot",
    "dashdoubledot",
    "alternate",
    "doubledot",
    "longdash"
};

// -------------------------------------------------------------------------
class LegendManagerObserver
: public IlvManagerObserver
{
public:
    LegendManagerObserver(IlvManager* manager, Legend* legend)
    : IlvManagerObserver(manager,
			 IlvMgrMsgViewMask | IlvMgrMsgLayerMask |
			 IlvMgrMsgContentsMask),
			 theLegend(legend)
    {}

    void update(IlvObservable* o, IlAny arg);
private:
    Legend* theLegend;
};

// -------------------------------------------------------------------------
void
LegendManagerObserver::update(IlvObservable* o, IlAny arg)
{
    IlvManagerMessage* message = (IlvManagerMessage*)arg;
    if (!theLegend->_currentView) {
	return;
    }
    IlvManager* theManager = (IlvManager*)
	theLegend->_currentView->getProperty(IlGetSymbol("Manager"));
    if (!theManager) {
	return;
    }
    IlvMatrix* matrix = theLegend->_matrix;

    if (message->_reason == IlvMgrMsgAddLayer) {
	// ------------------------------------- Processing layer adding
 	IlvManagerLayerMessage* layerMessage =
	    (IlvManagerLayerMessage*) message;
	if (layerMessage->getLayer() > theManager->getNumLayers()) {
	    return;
	}
 	theLegend->createLayerLegend(layerMessage->getLayer());
	matrix->invalidateColumn(0);
	matrix->invalidateColumn(1);
	matrix->invalidateColumn(2);
	matrix->reDraw();
    }
    else if (message->_reason == IlvMgrMsgRemoveLayer) {
	// ------------------------------------- Layer removing
	IlvManagerLayerMessage* layerMessage =
	    (IlvManagerLayerMessage*) message;
	matrix->removeRow(layerMessage->getLayer());
 	theLegend->createAllLegend();
	matrix->reDraw();
    }
    else if (message->_reason == IlvMgrMsgLayerName) {
	// ------------------------------------- Processing name change
	IlvManagerLayerMessage* layerMessage =
	    (IlvManagerLayerMessage*) message;
	if (layerMessage->getLayer() >= theManager->getNumLayers()) {
	    return;
	}
	if (theLegend->updateLayerLegendName(layerMessage->getLayer())) {
	    matrix->invalidateRow(layerMessage->getLayer());
	    matrix->reDraw();
	}
    }
    else if ((message->_reason == IlvMgrMsgAddObject) ||
	     (message->_reason == IlvMgrMsgRemoveObject)) {
	// ------------------------------------- Contents changed
	IlvManagerContentsMessage* contentsMessage =
	    (IlvManagerContentsMessage*) message;
	if (theLegend->updateLayerRepresentation(contentsMessage->_layer)) {
	    matrix->invalidateRow(contentsMessage->_layer);
	    matrix->reDraw();
	}
    }
    else if (message->_reason == IlvMgrMsgSwapLayer) {
	// ------------------------------------- Layer swap
	IlvManagerSwapLayerMessage* swapMessage =
	    (IlvManagerSwapLayerMessage*) message;
	IlUShort layer1 = swapMessage->getLayer();
	IlUShort layer2 = swapMessage->_layer2;
	IlvMatrix* matrix = theLegend->_matrix;
	// copy layer 1 items
	IlvAbstractMatrixItem* l1_label = matrix->getItem(1, layer1)->copy();
	IlvAbstractMatrixItem* l1_representation =
	    matrix->getItem(2, layer1)
	    ? matrix->getItem(2, layer1)->copy()
	    : 0;
	// copy layer 2 items
	IlvAbstractMatrixItem* l2_label = matrix->getItem(1, layer2)->copy();
	IlvAbstractMatrixItem* l2_representation =
	    matrix->getItem(2, layer2)
	    ? matrix->getItem(2, layer2)->copy()
	    : 0;
	// set l1 to l2
	matrix->set(1, layer2, l1_label);
	matrix->set(2, layer2, l1_representation);
	matrix->set(1, layer1, l2_label);
	matrix->set(2, layer1, l2_representation);
	matrix->invalidateRow(layer2);
	matrix->invalidateRow(layer1);
	matrix->reDraw();
    }
    else if (message->_reason == IlvMgrMsgLayerVisibility) {
	// ------------------------------------- Layer visibility
	IlvManagerLayerVisibilityMessage* vMessage =
	    (IlvManagerLayerVisibilityMessage*) message;
	IlUShort layerindex = vMessage->getLayer();
	IlBoolean layervisible =
	    theManager->getManagerLayer(layerindex)->isVisible();
	IlvMatrix* matrix = theLegend->_matrix;
	IlvGadgetMatrixItem* gaditem = (IlvGadgetMatrixItem*)
	    matrix->getItem(1, layerindex);
	if (gaditem) {
	    IlvToggle* toggle = (IlvToggle*)gaditem->getGadget();
	    if (toggle) {
		if (layervisible != toggle->getState()) {
		    toggle->setState(layervisible);
		    matrix->invalidateRow(layerindex);
		    matrix->reDraw();
		}
	    }
	}
    }
}

// --------------------------------------------------------------------------
// Callbacks
// --------------------------------------------------------------------------
void
LegendVisibilityChangeCallback(IlvGraphic* g, IlAny arg)
{
    Legend* legend = (Legend*)arg;
    if (!legend->getCurrentView()) {
	return;
    }
    IlvManager* manager = (IlvManager*)
	legend->getCurrentView()->getProperty(IlGetSymbol("Manager"));
    if (!manager) {
	return;
    }
    IlInt layerindex = -1;
    for (IlUInt i = 0; i < legend->getMatrix()->rows(); i++) {
	IlvGadgetMatrixItem* gadgetItem =
	    (IlvGadgetMatrixItem*) legend->getMatrix()->getItem(1,
								(IlUShort)i);
	IlvToggle* toggle = (IlvToggle*)gadgetItem->getGadget();
	if (toggle == g) {
	    layerindex = i;
	    break;
	}
    }
    if (layerindex == -1) {
	return;
    }
    IlvToggle* toggle = (IlvToggle*)g;
    // get the layer
    IlvManagerLayer* layer = manager->getManagerLayer(layerindex);
    IlBoolean layerVisible = layer->isVisible();
    IlBoolean toggleVisible = toggle->getState();
    if (layerVisible != toggleVisible) {
	layer->setVisible(toggleVisible);
#if defined(HAS_SDO_SUPPORT)
	if (toggleVisible) {
	    if (layer->getClassInfo()
		->isSubtypeOf(IlvObjectSDOLayer::ClassInfo())) {
		IlvObjectSDOLayer* ol = (IlvObjectSDOLayer*)layer;
		ol->getTileController()
		    ->updateView(GetBuilder()->getCurrentBuffer()
					     ->getView());
	    }
	}
#endif
	manager->reDraw();
    }
}


// --------------------------------------------------------------------------
// Legend implementation
// --------------------------------------------------------------------------
Legend::Legend(IlvDisplay* display,const IlvRect& rect)
: IlvGadgetContainerRectangle(display,rect),
  _currentView(0),
  _managerObserver(0),
  _matrix(0),
  _lastSelectedItem(-1)
{
}

// --------------------------------------------------------------------------
Legend::~Legend()
{
    if (_currentView) {
	IlvManager* manager =
	    (IlvManager*)_currentView->getProperty(IlGetSymbol("Manager"));
	if (manager) {
	    if (_managerObserver) {
		_managerObserver->detach(manager->getObservable(IlTrue));
	    }
	    delete _managerObserver;
	    _managerObserver = 0;
	}
    }
    _currentView = 0;
}

// --------------------------------------------------------------------------
static void
dragItemCB(IlvGraphic* g, IlAny a)
{
    IlvMatrix* m = (IlvMatrix*)g;
    IlvGadgetItem* item = m->getDraggedItem();
    IlvMessageLabel* message = (IlvMessageLabel*)item->getGraphic();
    const char* layerNumber = message->getLabel();
    IlString lnumSpace(layerNumber);
    lnumSpace.remove(IlString(" "));
    IlString lnum = lnumSpace;
    IlInt num = atoi(lnum.getValue()); // the number of the dragged layer
    IlvDisplay* display = m->getDisplay();
    IlvPos x, y;
    IlUShort modifiers;
    display->queryPointer(x, y, modifiers);
    IlvContainer* cont = IlvContainer::getContainer(m);
    IlvRect bbox;
    cont->globalBBox(bbox);
    IlUShort col, row;
    IlvPoint matPoint(x - bbox.x(), y - bbox.y());
    m->pointToItem(matPoint, col, row);
    message->setForeground(display->getColor("black"));
    m->invalidateColumn(0);
    m->reDraw();
    if (row > 100) {
	return; // if dropped outside
    }
    if (a) {
	IlvView* v = (IlvView*)a;
	IlvManager* m = (IlvManager*)v->getProperty(IlGetSymbol("Manager"));
	m->swapLayers(num, row);
    }
}

// --------------------------------------------------------------------------
static void
startDragItemCB(IlvGraphic* g, IlAny a)
{
    IlvMatrix* m = (IlvMatrix*)g;
    IlvDisplay* display = m->getDisplay();
    IlvGadgetItem* item = m->getDraggedItem();
    IlvPalette* palette = display->getPalette(display->getColor("red"),
					      display->getColor("red"));
    IlvRectangle* rectangle = new IlvRectangle(m->getDisplay(),
					       IlvRect(0, 0, 28, 28),
					       palette);
    IlvMessageLabel* label = (IlvMessageLabel*)item->getGraphic();
    label->setForeground(display->getColor("red"));
    m->setDraggedImage(rectangle);
    m->invalidateColumn(0);
    m->reDraw();
}

// --------------------------------------------------------------------------
IlvView*
Legend::createView(IlvAbstractView* parent, const IlvRect& rect)
{
    IlvView* view = IlvGadgetContainerRectangle::createView(parent, rect);
    IlvGadgetContainer* container = (IlvGadgetContainer*)view;
    container->setDoubleBuffering(IlTrue);
    IlvRect copy = rect;
    copy.move(0, 0);
    _matrix = new IlvMatrix(parent->getDisplay(), copy, 3, 1, copy.w());
    _matrix->allowDragDrop(IlTrue);
    _matrix->showGrid(IlTrue);
    _matrix->scrollBarShowAsNeeded(IlTrue, IlFalse);
    _matrix->setClientData(this);
    container->addObject(_matrix);
    container->getHolder()->attach(_matrix, IlvHorizontal, 0, 1, 0);
    container->getHolder()->attach(_matrix, IlvVertical, 0, 1, 0);
    _matrix->setInteractor(new LegendGadgetInteractor(this));
    _matrix->resizeColumn(1, 36);
    _matrix->resizeColumn(2, 150);
    _matrix->resizeColumn(3, 64);
    _matrix->autoFitToSize(IlTrue);
    // create all legend table
    createAllLegend();
    return view;
}

// --------------------------------------------------------------------------
void
Legend::setTargetView(IlvView* view)
{
    // if the view is the same as current view, return
    if (view == _currentView)
	return;
    IlvManager* newManager = view
		? (IlvManager*)view->getProperty(IlGetSymbol("Manager"))
		: 0;
    // remove every listeners attached to current view
    if (_currentView) {
	IlvManager* oldManager =
	    (IlvManager*)_currentView->getProperty(IlGetSymbol("Manager"));
	// remove listeners on old view
	if (oldManager && _managerObserver) {
	    delete _managerObserver;
	}
    }
    // install listeners on the new manager
    _currentView = view;
    _matrix->setCallback(IlvGadgetItemHolder::StartDragItemCallbackType(),
			 startDragItemCB,
			 _currentView);
    _matrix->setCallback(IlvGadgetItemHolder::EndDragItemCallbackType(),
			 dragItemCB,
			 _currentView);
    if (newManager) {
	createAllLegend();
	IlvManagerObservable* a = newManager->getObservable(IlTrue);
	_managerObserver = new LegendManagerObserver(newManager, this);
	_managerObserver->attach(a);
	_matrix->reDraw();
    }
    else {
	_matrix->reinitialize(3, 0);
	_matrix->invalidateColumn(0);
	_matrix->invalidateColumn(1);
	_matrix->invalidateColumn(2);
	_matrix->reDraw();
    }
}

// --------------------------------------------------------------------------
IlBoolean
Legend::updateLayerLegendName(IlInt layerindex)
{
    if (!_currentView) {
	return IlFalse;
    }
    IlvManager* myManager =
	(IlvManager*)_currentView->getProperty(IlGetSymbol("Manager"));
    if (!myManager) {
	return IlFalse;
    }
    if (layerindex >= _matrix->rows()) {
	return IlFalse;
    }
    IlvManagerLayer* layer = myManager->getManagerLayer(layerindex);
    const char* layername = layer->getName() ? layer->getName() : "no name";
    IlvGadgetMatrixItem* toggleItem =
	(IlvGadgetMatrixItem*) _matrix->getItem(1, (IlUShort)layerindex);
    IlvToggle* toggle = (IlvToggle*) toggleItem->getGadget();
    toggle->setLabel(layername);
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
Legend::updateLayerRepresentation(IlInt layerindex)
{
    if (!_currentView) {
	return IlFalse;
    }
    IlvManager* myManager = (IlvManager*)
	_currentView->getProperty(IlGetSymbol("Manager"));
    if (!myManager) {
	return IlFalse;
    }
    if (layerindex < 0) {
	return IlFalse;
    }
    if (layerindex >= _matrix->rows()) {
	return IlFalse;
    }
    IlvManagerLayer* layer = myManager->getManagerLayer(layerindex);
    IlvGraphicMatrixItem* graphicItem =
	(IlvGraphicMatrixItem*)_matrix->getItem(2, (IlUShort)layerindex);
    // case of all items deleted
    if (graphicItem && layer->getCardinal() == 0) {
	_matrix->set(2, (IlUShort)layerindex, 0);
	return IlTrue;
    } // case of first item added
    else if (!graphicItem) {
	IlvGraphic* representation = getLayerRepresentation(layer);
	if (representation) {
	    _matrix->set(2,
			 (IlUShort) layerindex,
			 new IlvGraphicMatrixItem(representation));
	    return IlTrue;
	}
    }
    return IlFalse;
}

// --------------------------------------------------------------------------
void
Legend::createLayerLegend(IlInt layerindex)
{
    if (!_currentView) {
	return;
    }
    IlvManager* myManager =
	(IlvManager*)_currentView->getProperty(IlGetSymbol("Manager"));
    if (!myManager) {
	return;
    }
    if (layerindex >= _matrix->rows()) {
	IlInt difference = _matrix->rows() - layerindex + 1;
	_matrix->insertRow(_matrix->rows(), (IlUShort)difference);
    }
    else if (_matrix->rows() != myManager->getNumLayers()) {
	_matrix->insertRow((IlUShort)layerindex, 1);
    }
    IlvManagerLayer* layer = myManager->getManagerLayer(layerindex);
    const char* layername = layer->getName() ? layer->getName() : "no name";
    IlvRect rectSize(0, 0, 250, 32);
    IlvMessageLabel* b =
	new IlvMessageLabel(getDisplay(),
			    (IlString(" ") + IlString(layerindex))
			    .getValue(),
			    IlvRect(0, 0, 30, 20));
    b->setBackground(myManager->getDisplay()->getColor("white"));
    IlvGadgetItem* gdtItem = new IlvGadgetItem(b);
    _matrix->set(0,
		 (IlUShort)layerindex,
		 new IlvGadgetItemMatrixItem(gdtItem));
    _matrix->setItemReadOnly(0, (IlUShort)layerindex, IlTrue);
    _matrix->setItemSensitive(0, (IlUShort)layerindex, IlFalse);
    _matrix->setItemGrayed(0, (IlUShort)layerindex, IlFalse);
    // The toggle with layer name
    IlvToggle* t = new IlvToggle(getDisplay(), IlvPoint(5, 0), layername);
    t->setRadio(IlFalse);
    t->setCallback(LegendVisibilityChangeCallback);
    t->setClientData(this);
    if (layer->isVisible()) {
	t->setState(IlTrue);
    }
    IlvGadgetMatrixItem* toggleItem = new IlvGadgetMatrixItem(t);
    _matrix->set(1, (IlUShort)layerindex, toggleItem);
    // The representation component
    IlvGraphic* representation = getLayerRepresentation(layer);
    IlvGadgetItemMatrixItem* graphicItem = 0;
    if (representation) {
	graphicItem =
	    new IlvGadgetItemMatrixItem(new IlvGadgetItem(representation));
    }
    _matrix->set(2, (IlUShort)layerindex, graphicItem);
    _matrix->setItemReadOnly(2, (IlUShort)layerindex, IlTrue);
    _matrix->setItemSensitive(2, (IlUShort)layerindex, IlFalse);
    _matrix->setItemGrayed(2, (IlUShort)layerindex, IlFalse);
    _matrix->resizeRow((IlUShort)layerindex + 1, rectSize.h());
}

// --------------------------------------------------------------------------
void
Legend::createAllLegend()
{
    if (!_currentView) {
	return;
    }
    IlvManager* myManager = (IlvManager*)
	_currentView->getProperty(IlGetSymbol("Manager"));
    if (!myManager) {
	return;
    }
    IlUInt numLayers = myManager->getNumLayers();
    _matrix->reinitialize(3, (IlUShort) numLayers);
    _matrix->setLabelPosition(IlvLeft, IlFalse);
    for (IlUInt i = 0; i < numLayers; i++) {
	createLayerLegend(i);
    }
    _matrix->resizeColumn(1, 36);
    _matrix->resizeColumn(2, 150);
    _matrix->resizeColumn(3, 64);
    _matrix->invalidateColumn(0);
    _matrix->invalidateColumn(1);
    _matrix->invalidateColumn(2);
}

// --------------------------------------------------------------------------
static IlvGraphic*
GetRepresentation(IlvDisplay* display, const IlvGraphic* g)
{
    IlvGraphic* representation = 0;
    // case of line
    if ((g->isSubtypeOf(IlvPolyline::ClassInfo())  &&
	 !g->isSubtypeOf(IlvPolygon::ClassInfo())) ||
	g->isSubtypeOf(IlvLine::ClassInfo())) {
	IlvPoint points[4];
	points[0].move(0, 16);
	points[1].move(20, 0);
	points[2].move(28, 16);
	points[3].move(48, 0);
	IlvPolyline* poly =
	    new IlvPolyline(display,
			    4,
			    points,
			    ((IlvSimpleGraphic*)g)->getPalette());
	representation = poly;
    } // case of map general path
    else if (g->isSubtypeOf(IlvMapGeneralPath::ClassInfo())) {
	IlvMapGeneralPath* path = (IlvMapGeneralPath*)g;
	IlvDrawRule drawRule = path->getDrawRule();
	if (drawRule == IlvStrokeOnly) {
	    IlvPoint points[4];
	    points[0].move(0, 16);
	    points[1].move(20, 0);
	    points[2].move(28, 16);
	    points[3].move(48, 0);
	    IlvPolyline* poly =
		new IlvPolyline(display,
				4,
				points,
				((IlvSimpleGraphic*)g)->getPalette());
	    representation = poly;
	}
	else if (drawRule == IlvFillOnly) {
	    IlvFilledRectangle* rect =
		new IlvFilledRectangle(display,
				       IlvRect(0, 0, 48, 16),
				       path->getFillPalette());
	    representation = rect;
	}
	else if (drawRule == IlvStrokeAndFill) {
	    IlvFilledRectangle* rect =
		new IlvFilledRectangle(display,
				       IlvRect(0, 0, 48, 16));
	    rect->setPalette(path->getFillPalette());
	    IlvRectangle* r =
		new IlvRectangle(display,
				 IlvRect(0, 0, 48, 16),
				 ((IlvSimpleGraphic*)g)->getPalette());
	    IlvGraphicSet* set = new IlvGraphicSet();
	    set->addObject(rect);
	    set->addObject(r);
	    representation = set;
	}
    } // case of graphic path
    else if (g->isSubtypeOf(IlvGraphicPath::ClassInfo())) {
	IlvGraphicPath* path = (IlvGraphicPath*)g;
	IlvDrawRule drawRule = path->getDrawRule();
	if (drawRule == IlvStrokeOnly) {
	    IlvPoint points[4];
	    points[0].move(0,16);
	    points[1].move(20,0);
	    points[2].move(28,16);
	    points[3].move(48,0);
	    IlvPolyline* poly =
		new IlvPolyline(display,
				4,
				points,
				((IlvSimpleGraphic*)g)->getPalette());
	    representation = poly;
	}
	else if (drawRule == IlvFillOnly) {
	    IlvFilledRectangle* rect =
		new IlvFilledRectangle(display,
				       IlvRect(0, 0, 48, 16),
				       ((IlvSimpleGraphic*)g)->getPalette());
	    representation = rect;
	}
	else if (drawRule == IlvStrokeAndFill) {
	    IlvFilledRectangle* rect =
		new IlvFilledRectangle(display,
				       IlvRect(0, 0, 48, 16),
				       ((IlvSimpleGraphic*)g)->getPalette());
	    representation = rect;
	}
    } // case of polygon
    else if (g->isSubtypeOf(IlvPolygon::ClassInfo()) ||
	     g->isSubtypeOf(IlvFilledRectangle::ClassInfo())) {
	IlvFilledRectangle* rect =
	    new IlvFilledRectangle(display,
				   IlvRect(0, 0, 48, 16),
				   ((IlvSimpleGraphic*)g)->getPalette());
	representation = rect;
    } // case of marker
    else if (g->isSubtypeOf(IlvMarker::ClassInfo())) {
	IlvMarker* marker =
	    new IlvMarker(display,
			  IlvPoint(0, 0),
			  ((IlvMarker*)g)->getType(),
			  ((IlvMarker*)g)->getSize(),
			  ((IlvSimpleGraphic*)g)->getPalette());
	representation = marker;
    } // case of icons
    else if (g->isSubtypeOf(IlvIcon::ClassInfo()) ||
	     g->isSubtypeOf(IlvZoomableIcon::ClassInfo())) {
	if (g->isSubtypeOf(IlvIcon::ClassInfo())) {
	    IlvIcon* icon =
		new IlvIcon(display,
			    IlvPoint(0,0),
			    ((IlvIcon*)g)->getBitmap(),
			    ((IlvSimpleGraphic*)g)->getPalette());
	    representation = icon;
	}
	else if (g->isSubtypeOf(IlvZoomableIcon::ClassInfo())) {
	    IlvIcon* icon =
		new IlvIcon(display,
			    IlvPoint(0,0),
			    ((IlvZoomableIcon*)g)->getBitmap(),
			    ((IlvSimpleGraphic*)g)->getPalette());
	    representation = icon;
	}
    }
    else if (g->isSubtypeOf(IlvGraphicSet::ClassInfo())) {
	IlvGraphicSet* gs =  (IlvGraphicSet*)g;
	IlvGraphicSet* set = new IlvGraphicSet();
	IlUInt count = 0;
	IlvGraphic* const* elements = gs->getObjects(count);
	if (count) {
	    for (IlUInt i = 0; i < count; i++) {
		IlvGraphic* e = GetRepresentation(display, elements[i]);
		if (e) {
		    set->addObject(e);
		}
	    }
	    representation = set;
	}
    }
    return representation;
}

// --------------------------------------------------------------------------
IlvGraphic*
Legend::getLayerRepresentation(IlvManagerLayer* layer)
{
    if (layer->getCardinal() == 0) {
	return 0;
    }
    IlUInt count = 0;
    IlvGraphic* const* allObjects = layer->getObjects(count);
    const IlvGraphic* g = allObjects[0];
    return GetRepresentation(getDisplay(), g);
}

//--------------------------------------------------------------------------
// An interactor for contextual popup
//--------------------------------------------------------------------------
static void
ToTopCB(IlvGraphic *g, IlAny a)
{
    Legend* legend = (Legend*)a;
    IlvView* view = legend->getCurrentView();
    if (view) {
	IlvManager* m = (IlvManager*)
	    view->getProperty(IlGetSymbol("Manager"));
	m->swapLayers(legend->getLastSelectedItem(), m->getNumLayers() - 1);
    }
}

// --------------------------------------------------------------------------
static void
ToBottomCB(IlvGraphic *g, IlAny a)
{
    Legend* legend = (Legend*)a;
    IlvView* view = legend->getCurrentView();
    if (view) {
	IlvManager* m = (IlvManager*)
	    view->getProperty(IlGetSymbol("Manager"));
	m->swapLayers(legend->getLastSelectedItem(), 0);
    }
}

// --------------------------------------------------------------------------
struct vfInternStruct
{
    IlvGadgetContainer* c;
    IlBoolean ok;
};

// --------------------------------------------------------------------------
static void
VisibilityFilterOkCB(IlvGraphic*g, IlAny a)
{
    vfInternStruct* s = (vfInternStruct*)a;
    s->c->hide();
    s->ok = IlTrue;
}

// --------------------------------------------------------------------------
static void
VisibilityFilterCancelCB(IlvGraphic*g, IlAny a)
{
    vfInternStruct* s = (vfInternStruct*)a;
    s->c->hide();
    s->ok = IlFalse;
}

// --------------------------------------------------------------------------
static void
VisibilityFilterCB(IlvGraphic *g, IlAny a)
{
    Legend* legend = (Legend*)a;
    IlvView* view = legend->getCurrentView();
    if (view) {
	IlvManager* m = (IlvManager*)
	    view->getProperty(IlGetSymbol("Manager"));
	IlvManagerLayer* layer =
	    m->getManagerLayer(legend->getLastSelectedItem());
	// find the first visibility filter
	IlListOf(IlvLayerVisibilityFilter)& filterList =
	    layer->visibilityFilters();
	IlvScaleVisibilityFilter* filter = 0;
	IlUInt len = filterList.length();
	for (IlUInt i = 0; i < len; i++) {
	    IlvLayerVisibilityFilter* f = filterList[i];
	    if (f->getClassInfo()
		->isSubtypeOf(IlvScaleVisibilityFilter::ClassInfo())) {
		filter = (IlvScaleVisibilityFilter*)f;
		break;
	    }
	}
	// Create a modal dialog with the 2 combos
	IlvDialog cont(view->getDisplay(),
		       "visibilityRequest",
		       "Visibility Filter",
		       IlvRect(0, 0, 280, 150),
		       0,
		       view->getSystemView());
	// The buttons
	vfInternStruct clientData;
	clientData.c = &cont;
	clientData.ok = IlFalse;
	IlvButton* okButton = new IlvButton(view->getDisplay(),
					    "Ok",
					    IlvRect(50, 120, 80, 20));
	okButton->setClientData(&clientData);
	okButton->setCallback(VisibilityFilterOkCB);
	cont.addObject(okButton);
	IlvButton* cancelButton = new IlvButton(view->getDisplay(),
						"Cancel",
						IlvRect(150, 120, 80, 20));
	cancelButton->setClientData(&clientData);
	cancelButton->setCallback(VisibilityFilterCancelCB);
	cont.addObject(cancelButton);
	// The combos
	// Create the labels (so that positioning is good)
	IlvLabel* largeScaleLabel = new IlvLabel(view->getDisplay(),
						 IlvPoint(0, 0),
						 "Large scale limit 1 / ");
	IlvLabel* smallScaleLabel = new IlvLabel(view->getDisplay(),
						 IlvPoint(0, 0),
						 "Small scale limit 1 / ");
	IlInt combopos =
	    IlMax(largeScaleLabel->w(), smallScaleLabel->h()) + 20;
	// The large scale combo
	ScaleCombo* largeScaleCombo = new ScaleCombo(view->getDisplay(),
						     IlvPoint(combopos, 20));
	largeScaleCombo->h(24);
	largeScaleCombo->w(100);
	cont.addObject(largeScaleCombo);
	// the corresponding label
	IlvLabel* label = largeScaleLabel;
	IlInt ypos = (((IlInt)largeScaleCombo->h())-((IlInt)label->h())) / 2;
	IlInt xpos = ((IlInt)largeScaleCombo->x()) - ((IlInt)label->w() + 5);
	label->move(xpos, largeScaleCombo->y() + ypos);
	cont.addObject(label);
	// the small scale combo
	ScaleCombo* smallScaleCombo = new ScaleCombo(view->getDisplay(),
						     IlvPoint(combopos, 50));
	smallScaleCombo->h(24);
	smallScaleCombo->w(100);
	cont.addObject(smallScaleCombo);
	// the corresponding label
	label = smallScaleLabel;
	ypos = (((IlInt)smallScaleCombo->h()) - ((IlInt)label->h())) / 2;
	xpos = ((IlInt)smallScaleCombo->x()) - ((IlInt)label->w() + 5);
	label->move(xpos, smallScaleCombo->y() + ypos);
	cont.addObject(label);

	// set initial values
	if (filter) {
	    // large scale
	    if (filter->getMaxScale() <= 0) {
		largeScaleCombo->setLabel("No limit");
	    }
	    else {
		char buf[500];
		sprintf(buf, "%d", (int) (1./filter->getMaxScale()));
		largeScaleCombo->setLabel(buf);
	    }
	    // small scale
	    if (filter->getMinScale() <= 0) {
		smallScaleCombo->setLabel("No limit");
	    }
	    else {
		char buf[500];
		sprintf(buf, "%d", (int) (1./filter->getMinScale()));
		smallScaleCombo->setLabel(buf);
	    }
	}
	cont.moveToView(GetBuilder()->getMainWindow());
	cont.wait();
	if (clientData.ok) {
	    IlDouble largeScale = IlvScaleVisibilityFilter::NoLimit();
	    IlDouble smallScale = IlvScaleVisibilityFilter::NoLimit();
	    IlDouble large = largeScaleCombo->getScale();
	    if (large > 0.0) {
		largeScale = 1. / large;
	    }
	    IlDouble petit = smallScaleCombo->getScale();
	    if (petit > 0.0) {
		smallScale = 1. / petit;
	    }
	    if (petit <= 0.0 && large <= 0.0) {
		if (filter) {
		    // remove filter
		    filterList.remove(filter);
		    delete filter;
		}
		else {
		    return; // No filter before, no filter after
		    // nothing to redraw
		}
	    }
	    else {
		if (!filter) {
		    filter = new IlvScaleVisibilityFilter(smallScale,
							  largeScale);
		    layer->addVisibilityFilter(filter);
		}
		else {
		    filter->setMinScale(smallScale);
		    filter->setMaxScale(largeScale);
		}
	    }
	    // redraw views
	    m->reDrawViews();
	}
    }
}

// --------------------------------------------------------------------------
static void
RemoveCB(IlvGraphic* g, IlAny a)
{
    Legend* legend = (Legend*)a;
    IlvView* view = legend->getCurrentView();
    if (view) {
	IlvManager* m = (IlvManager*)
	    view->getProperty(IlGetSymbol("Manager"));
	IlvManagerLayer* layer =
	    m->getManagerLayer(legend->getLastSelectedItem());
	IlString name(layer->getName());
	const char* message = 0;
	IlBoolean poline = IlFalse;
	IlBoolean raster = IlFalse;
	if (name.getIndexOf(IlString("Poline_")) != -1 &&
	    layer->getNamedProperty(IlGetSymbol("_MULTIRES_"))) {
	    poline = IlTrue;
	}
	if (name.getIndexOf(IlString("Raster_")) != -1 &&
	    layer->getNamedProperty(IlGetSymbol("_MULTIRES_"))) {
	    raster = IlTrue;
	}
	if (!poline && !raster) {
	    message = "Do you really want to remove layer : %s ?";
	}
	else {
	    message =
		"Do you really want to remove multiresolution layers : %s ?";
	}
	char* buf = new char[strlen(message)
			     + 10
			     + strlen(layer->getName()
				      ? layer->getName()
				      : "No name")];
	sprintf(buf, message, layer->getName()
			      ? layer->getName()
			      : "No name");
	IlvIQuestionDialog dialog(legend->getDisplay(),
				  buf,
				  0,
				  IlvDialogOkCancel,
				  legend->getView()->getSystemView());
	dialog.setTitle("Confirmation of layer removing");
	dialog.moveToView(GetBuilder()->getMainWindow());
	if (dialog.get()) {
	    if (!poline && !raster) {
		IlInt which = legend->getLastSelectedItem();
		layer = m->getManagerLayer(which);
		MapBuffer::UpdateLayerAttributes(layer, 0, IlTrue);
		m->deleteAll(which, IlTrue, IlTrue);
		m->removeLayer(which);
	    }
	    else {
		IlInt count = m->getNumLayers();
		for (IlInt i = 0; i < count; i++) {
		    layer = m->getManagerLayer(i);
		    MapBuffer::UpdateLayerAttributes(layer, 0, IlTrue);
		    IlString layerName(layer->getName());
		    if ((layerName.getIndexOf(IlString("Poline_")) != -1
			 && poline)
			||
			(layerName.getIndexOf(IlString("Raster_")) != -1
			 && raster)) {
			m->deleteAll(i, IlTrue, IlFalse);
			m->removeLayer(i);
			i--;
			count--;
		    }
		}
		m->reDraw();
	    }
	}
	if (buf) {
	    delete buf;
	}
    }
}

// --------------------------------------------------------------------------
static void
closeCB(IlvView* v, IlAny)
{
    v->hide();
}

// --------------------------------------------------------------------------
static void
okCB(IlvGraphic* g, IlAny a)
{
    IlvDialog* d = (IlvDialog*)a;
    d->apply();
    d->hide();
}

// --------------------------------------------------------------------------
static void
cancelCB(IlvGraphic* g, IlAny a)
{
    IlvDialog* d = (IlvDialog*)a;
    d->cancel();
    d->hide();
}

// --------------------------------------------------------------------------
static void
ApplyLinePaletteCB(IlvGraphic* g, IlAny arg)
{
    IlvPalette* pal = (IlvPalette*)arg;
    IlvMapGeneralPath* genpath = (IlvMapGeneralPath*)g;
    genpath->setPalette(pal);
}

// --------------------------------------------------------------------------
static void
ApplyFillPaletteCB(IlvGraphic* g, IlAny arg)
{
    IlvPalette* pal = (IlvPalette*)arg;
    IlvMapGeneralPath* genpath = (IlvMapGeneralPath*)g;
    genpath->setFillPalette(pal);
}

// --------------------------------------------------------------------------
static IlvGraphic*
makeGraphic(IlvGraphic* g, PaletteEditor* palEditor)
{
    if (g->isSubtypeOf(IlvZoomableIcon::ClassInfo()))
	return 0;
    IlvBitmap* bitmap = palEditor->getMarkerBitmap();
    if (bitmap) {
	if (g->isSubtypeOf(IlvIcon::ClassInfo())) {
	    // g is already an icon: change it's bitmap
	    IlvIcon* icon = (IlvIcon*)g;
	    icon->setBitmap(bitmap);
	    return icon;
	}
	else {
	    // g is a Marker: change it into an icon
	    IlvRect bbox;
	    g->addProperty(IlGetSymbol("_TO_REMOVE_"), g);
	    g->boundingBox(bbox);
	    IlvManager* m = ((IlvManagerGraphicHolder*) g->getHolder())
		->getManager();
	    IlvIcon* icon = new IlvIcon(m->getDisplay(),
					IlvPoint(bbox.x(), bbox.y()),
					bitmap);
	    return icon;
	}
    }
    else {
	if (g->isSubtypeOf(IlvMarker::ClassInfo())) {
	    // g is a marker: change it's parameters
	    IlvMarker* marker = (IlvMarker*)g;
	    marker->setType(palEditor->getMarkerType());
	    marker->setForeground(palEditor->getMarkerColor());
	    marker->setSize((IlUShort)palEditor->getMarkerSize());
	    return marker;
	}
	else { // g is a bitmap: change it into a Marker
	    IlvRect bbox;
	    g->addProperty(IlGetSymbol("_TO_REMOVE_"), g);
	    g->boundingBox(bbox);
	    IlvManager* m = ((IlvManagerGraphicHolder*)g->getHolder())
		->getManager();
	    IlvMarker* marker =
		new IlvMarker(m->getDisplay(),
			      IlvPoint(bbox.x(), bbox.y()),
			      palEditor->getMarkerType(),
			      (IlUShort)palEditor->getMarkerSize());
	    marker->setForeground(palEditor->getMarkerColor());
	    return marker;
	}
    }
    return 0; // Unreachable
}

// --------------------------------------------------------------------------
static void
ApplyMarkerCB(IlvGraphic* g, IlAny arg)
{
    PaletteEditor* palEditor = (PaletteEditor*)arg;
    IlvGraphic* transformed = makeGraphic(g, palEditor);
    if (!transformed) {
	return;
    }
    IlvManager* m = ((IlvManagerGraphicHolder*)g->getHolder())->getManager();
    if (transformed != g) {
	m->addObject(transformed, IlFalse);
	transformed->copyProperties(*g);
    }
    m->invalidateRegion(transformed);
}

// --------------------------------------------------------------------------
static void
ApplyMarkerOrIconInGraphicSetCB(IlvGraphicSet* gset,
				IlvGraphic* g,
				PaletteEditor* palEditor)
{
    IlvGraphic* transformed = makeGraphic(g, palEditor);
    gset->removeObject(g);
    gset->insertObject(transformed);
}

// --------------------------------------------------------------------------
static void
ApplyToEachGraphicFromGraphicSetCB(IlvGraphic* g, IlAny arg)
{
    IlvGraphicSet* set = (IlvGraphicSet*)arg;
    IlvManager* m = ((IlvManagerGraphicHolder*)g->getHolder())
	->getManager();
    PaletteEditor* palEditor = (PaletteEditor*)
	set->getProperty(IlGetSymbol("PalEditor"));
    if (g->isSubtypeOf(IlvMapGeneralPath::ClassInfo())) {
	if (!palEditor) {
	    palEditor = (PaletteEditor*)arg;
	}
	IlvPalette* linePal = palEditor->getLinePalette();
	IlvPalette* fillPal = palEditor->getFillPalette();
	ApplyLinePaletteCB(g, linePal);
	ApplyFillPaletteCB(g, fillPal);
	m->invalidateRegion(g);
    }
    else if (g->isSubtypeOf(IlvMarker::ClassInfo()) ||
	     g->isSubtypeOf(IlvIcon::ClassInfo())) {
	ApplyMarkerOrIconInGraphicSetCB(set, g, palEditor);
    }
}

// --------------------------------------------------------------------------
static void
ApplyGeneralPathOrGraphicSetCB(IlvGraphic* g, IlAny arg)
{
    PaletteEditor* palEditor = (PaletteEditor*)arg;
    if (g->isSubtypeOf(IlvMapGeneralPath::ClassInfo())) {
	ApplyToEachGraphicFromGraphicSetCB(g, palEditor);
	return;
    }
    else if (g->isSubtypeOf(IlvGraphicSet::ClassInfo())) {
	IlvGraphicSet* set = (IlvGraphicSet*)g;
	set->addProperty(IlGetSymbol("PalEditor"), palEditor);
	set->apply(ApplyToEachGraphicFromGraphicSetCB, set);
	return;
    }
}

// --------------------------------------------------------------------------
static void
updatePaletteEditor(IlvClassInfo* info, PaletteEditor* editor)
{
    if (info) {
	if (info->isSubtypeOf(IlvMapPoint::ClassInfo()) ||
	    info->isSubtypeOf(IlvMapMultiPoint::ClassInfo())) {
	    editor->setLineEditingMode(IlFalse);
	    editor->setFillEditingMode(IlFalse);
	    editor->setPointEditingMode(IlTrue);
	    return;
	}
	else if (info->isSubtypeOf(IlvMapCurve::ClassInfo())) {
	    editor->setLineEditingMode(IlTrue);
	    editor->setPointEditingMode(IlFalse);
	    editor->setFillEditingMode(IlFalse);
	    return;
	}
	else if (info->isSubtypeOf(IlvMapArea::ClassInfo())) {
	    editor->setLineEditingMode(IlTrue);
	    editor->setPointEditingMode(IlFalse);
	    editor->setFillEditingMode(IlTrue);
	    return;
	}
    }
    editor->setLineEditingMode(IlTrue);
    editor->setPointEditingMode(IlTrue);
    editor->setFillEditingMode(IlTrue);
}

// --------------------------------------------------------------------------
#ifdef WINDOWS
/**
 * These features are only available on a MS Windows platform
 */
static void
antialiasCB(IlvGraphic* g, IlAny a)
{
    IlvManagerLayer* layer = (IlvManagerLayer*)a;
    IlString name(layer->getName());
    IlvToggle* tog = (IlvToggle*)g;
    // check multires layers
    IlvManager* m = layer->getManager();
    IlInt count = m->getNumLayers();
    IlBoolean poline = IlFalse;
    IlBoolean raster = IlFalse;
    if (name.getIndexOf(IlString("Poline_")) != -1 &&
	layer->getNamedProperty(IlGetSymbol("_MULTIRES_"))) {
	poline = IlTrue;
    }
    if (name.getIndexOf(IlString("Raster_")) != -1 &&
	layer->getNamedProperty(IlGetSymbol("_MULTIRES_"))) {
	raster = IlTrue;
    }
    if (poline || raster) {
	for (IlInt i = 0; i < count; i++) {
	    layer = m->getManagerLayer(i);
	    IlString layerName(layer->getName());
	    if (((layerName.getIndexOf(IlString("Poline_")) != -1) && poline)
		|| ((layerName.getIndexOf(IlString("Raster_")) != -1)
		    && raster)) {
		if (tog->getState()) {
		    layer->setAntialiasingMode(IlvUseAntialiasingMode);
		}
		else {
		    layer->setAntialiasingMode(IlvDefaultAntialiasingMode);
		}
	    }
	}
    }
    else {
	if (tog->getState()) {
	    layer->setAntialiasingMode(IlvUseAntialiasingMode);
	}
	else {
	    layer->setAntialiasingMode(IlvDefaultAntialiasingMode);
	}
    }
    layer->getManager()->reDraw();
}

// --------------------------------------------------------------------------
static void
transparencyCB(IlvGraphic* g, IlAny a)
{
    IlvManagerLayer* layer = (IlvManagerLayer*)a;
    IlString name(layer->getName());
    IlvSlider* slider = (IlvSlider*)g;
    // check multires layers
    IlvManager* m = layer->getManager();
    IlInt count = m->getNumLayers();
    IlBoolean poline = IlFalse;
    IlBoolean raster = IlFalse;
    if (name.getIndexOf(IlString("Poline_")) != -1 &&
	layer->getNamedProperty(IlGetSymbol("_MULTIRES_"))) {
	poline = IlTrue;
    }
    if (name.getIndexOf(IlString("Raster_")) != -1 &&
	layer->getNamedProperty(IlGetSymbol("_MULTIRES_"))) {
	raster = IlTrue;
    }
    if (poline || raster) {
	for (IlInt i = 0; i < count; i++) {
	    layer = m->getManagerLayer(i);
	    IlString layerName(layer->getName());
	    if (((layerName.getIndexOf(IlString("Poline_")) != -1) && poline)
		|| ((layerName.getIndexOf(IlString("Raster_")) != -1)
		    && raster)) {
		layer->setTransparency((IlDouble)slider->getValue()
				       / (IlDouble)100);
	    }
	}
    }
    else {
	layer->setTransparency((IlDouble)slider->getValue() / (IlDouble)100);
    }
    layer->getManager()->reDraw();
}
#endif

// --------------------------------------------------------------------------
static IlvSimpleGraphic*
UpdatePaletteEditorColor(IlvDisplay* display,
			 IlvStringProperty* pr,
			 IlvRect size,
			 IlvMarkerType mType,
			 IlBoolean marker)
{
    IlString color(pr->getString());
    IlString tmp =
       color.getSubString(1, color.getLastIndexOf(IlString("g"))).getValue();
    IlvIntensity r = atoi(tmp.getValue());
    tmp = color.getSubString(color.getLastIndexOf(IlString("g")) + 1,
			     color.getLastIndexOf(IlString("b")));
    IlvIntensity g = atoi(tmp.getValue());
    tmp = color.getSubString((int)(color.getLastIndexOf(IlString("b")) + 1),
			     (int)color.getLength());
    IlvIntensity b = atoi(tmp.getValue());
    IlvColor* c = display->getColor(r, g, b);
    if (!marker) {
	IlvReliefRectangle* graphic = new IlvReliefRectangle(display, size);
	graphic->setBackground(c);
	graphic->setForeground(c);
	graphic->setThickness(1);
	return graphic;
    }
    else {
	IlvMarker* m = new IlvMarker(display, IlvPoint(0, 0), mType);
	m->setForeground(c);
	return m;
    }
}

// --------------------------------------------------------------------------
static void
InitPaletteEditor(PaletteEditor* palEditor, IlvManagerLayer* layer)
{
    IlvDisplay* display = layer->getManager()->getDisplay();
#ifdef WINDOWS
    // Antialiasing and transparency (only with gdi+)
    IlvToggle* antialias = (IlvToggle*)
	palEditor->getContainer()->getObject("antialias");
    IlvSlider* slider = (IlvSlider*)
	palEditor->getContainer()->getObject("transparency");
    if (antialias) {
	antialias->setCallback(antialiasCB, layer);
    }
    if (slider) {
	slider->setCallback(transparencyCB, layer);
    }
    IlDouble transparency = layer->getTransparency();
    IlvAntialiasingMode mode = layer->getAntialiasingMode();
    if (mode == IlvUseAntialiasingMode) {
	IlvToggle* antialias = (IlvToggle*)
	    palEditor->getContainer()->getObject("antialias");
	if (antialias) {
	    antialias->setState(IlTrue);
	}
    }
    if (transparency > 0.0) {
	IlvSlider* slider = (IlvSlider*)
	    palEditor->getContainer()->getObject("transparency");
	if (slider) {
	    slider->setValue((IlInt)(transparency * 100.0));
	}
    }
#endif
    // the geometry class
    IlvStringProperty* sp = (IlvStringProperty*)
	layer->getNamedProperty(IlGetSymbol("_GEOMETRY_"));
    IlvClassInfo* geometryInfo = sp ? IlvGetClassInfo(sp->getString()) : 0;
    if (geometryInfo) {
	updatePaletteEditor(geometryInfo, palEditor);
    }
    // Area color
    ColorEditor* areaEditor = palEditor->getFillColorCombo();
    sp = (IlvStringProperty*)
	layer->getNamedProperty(IlGetSymbol("_AREA_COLOR_"));
    if (sp) {
	IlvSimpleGraphic* g =
	    UpdatePaletteEditorColor(display,
				     sp,
				     areaEditor->getPreviewSize(),
				     0,
				     IlFalse);
	int index = areaEditor->addUserColorItem(g);
	areaEditor->getColorCombo()->setSelected(index);
	areaEditor->setCurrentSelection(index);
	areaEditor->setHasTexture(IlFalse);
    }
    else {
	sp = (IlvStringProperty*)
	    layer->getNamedProperty(IlGetSymbol("_AREA_BITMAP_"));
	if (sp) {
	    IlvMapAreaRenderingStyle* style =
		new IlvMapAreaRenderingStyle(display);
	    style->lock();
	    IlvFilledRectangle* g =
		new IlvFilledRectangle(display,
				       areaEditor->getPreviewSize());
	    style->setFillPattern(sp->getString());
	    g->setPalette(style->getPalette());
	    style->unLock();
	    int index = areaEditor->addUserColorItem(g);
	    areaEditor->getColorCombo()->setSelected(index);
	    areaEditor->setCurrentSelection(index);
	    areaEditor->setHasTexture(IlTrue);
	}
    }
    // Line color
    sp = (IlvStringProperty*)
	layer->getNamedProperty(IlGetSymbol("_LINE_COLOR_"));
    if (sp) {
	IlvSimpleGraphic* g =
	    UpdatePaletteEditorColor(display,
				     sp,
				     areaEditor->getPreviewSize(),
				     0,
				     IlFalse);
	palEditor->getLineColorCombo()->addUserColorItem(g);
	palEditor->getLineColorCombo()->getColorCombo()->setSelected(15);
	palEditor->getLineColorCombo()->setCurrentSelection(15);
    }
    // line width
    sp = (IlvStringProperty*)
	layer->getNamedProperty(IlGetSymbol("_LINE_WIDTH_"));
    if (sp) {
	IlString lineWidth(sp->getString());
	const char* tmp = lineWidth.getValue();
	IlUShort lWidth = atoi(tmp);
	palEditor->getLineThicknessCombo()->getColorCombo()
					  ->setSelected(lWidth);
	palEditor->getLineThicknessCombo()->setCurrentSelection(lWidth);
    }
    // line style
    sp = (IlvStringProperty*)
	layer->getNamedProperty(IlGetSymbol("_LINE_STYLE_"));
    if (sp) {
	const char* lineStyle = sp->getString();
	IlUShort i = 0;
	IlBoolean found = IlFalse;
	for (i = 0; i < 8; i++) {
	    if (!strcmp(lineStyle, stdDashNames[i])) {
		found = IlTrue;
		break;
	    }
	}
	if (found) {
	    palEditor->getLineDashCombo()->getColorCombo()->setSelected(i);
	    palEditor->getLineDashCombo()->setCurrentSelection(i);
	}
    }
    // marker type
    PointEditor* pointEditor = palEditor->getPointSymbolCombo();
    sp = (IlvStringProperty*)
	layer->getNamedProperty(IlGetSymbol("_MARKER_TYPE_"));
    if (sp) {
	IlString markerType(sp->getString());
	IlvMarkerType mType = (IlvMarkerType)atoi(markerType);
	IlvSimpleGraphic* m =
	    UpdatePaletteEditorColor(display,
				     (IlvStringProperty*)
				     layer->getNamedProperty(
					      IlGetSymbol("_MARKER_COLOR_")),
				     IlvRect(0, 0, 0, 0),
				     mType,
				     IlTrue);
	int index = pointEditor->addUserPointItem(m);
	pointEditor->getPointCombo()->setSelected(index);
        pointEditor->setCurrentSelection(index);
	pointEditor->setHasTexture(IlFalse);
    }
    // marker bitmap
    sp = (IlvStringProperty*)
	layer->getNamedProperty(IlGetSymbol("_MARKER_BITMAP_"));
    if (sp) {
	IlvBitmap* bitmap = display->getBitmap(sp->getString());
	if (!bitmap) {
	    bitmap = display->readBitmap(sp->getString());
	}
	IlvIcon* icon = new IlvIcon(display, IlvPoint(0, 0), bitmap);
	int index = pointEditor->addUserPointItem(icon);
	pointEditor->getPointCombo()->setSelected(index);
	pointEditor->setCurrentSelection(index);
	pointEditor->setHasTexture(IlTrue);
    }
}

// --------------------------------------------------------------------------
static void
RenderingCB(IlvGraphic* g, IlAny a)
{
    Legend* legend = (Legend*)a;
    IlvView* view = legend->getCurrentView();
    if (view) {
	IlInt selectedLayerNumber = legend->getLastSelectedItem();
	IlvManager* m = (IlvManager*)
	    view->getProperty(IlGetSymbol("Manager"));
	IlvManagerLayer* layer = m->getManagerLayer(selectedLayerNumber);
	IlvDisplay* display = m->getDisplay();
	PaletteEditor* palEditor =
	    new PaletteEditor(display, IlvRect(5, 5, 400, 300));
	IlvDialog dialog(display,
			 "Change the rendering",
			 "Change the rendering",
			 IlvRect(0, 0, 425, 360),
			 0,
			 legend->getView()->getSystemView());
	dialog.setDestroyCallback(closeCB);
	dialog.addObject(palEditor);
	InitPaletteEditor(palEditor, layer);
	IlvButton* ok =
	    new IlvButton(display, "OK", IlvRect(160, 330, 50, 25));
	IlvButton* cancel =
	    new IlvButton(display, "Cancel", IlvRect(260, 330, 50, 25));
	dialog.addObject(ok);
	dialog.addObject(cancel);
	ok->setCallback(okCB, &dialog);
	cancel->setCallback(cancelCB, &dialog);
	dialog.getHolder()->attach(palEditor, IlvHorizontal, 0, 1, 0);
	dialog.moveToView(GetBuilder()->getMainWindow());
	dialog.fitTransformerToContents();
	IlvRect bbox;
	dialog.globalBBox(bbox);
	dialog.resize(bbox.w() + 40, bbox.h() + 5);
	IlUInt count;
	IlvGraphic* const* objects = layer->getObjects(count);
	if (count == 0) {
	    return;
	}
	IlvGraphic* first = objects[0];
	dialog.showModal(IlFalse);
	if (!dialog.wasCanceled()) {
	    IlvSetContentsChangedUpdate(IlFalse);
	    m->initReDraws();
	    if (first->isSubtypeOf(IlvMarker::ClassInfo()) ||
		first->isSubtypeOf(IlvIcon::ClassInfo())) {
		m->applyToObjects(selectedLayerNumber,
				  ApplyMarkerCB,
				  palEditor,
				  IlFalse);
	    }
	    else if (first->isSubtypeOf(IlvMapGeneralPath::ClassInfo()) ||
		     first->isSubtypeOf(IlvGraphicSet::ClassInfo()))
		m->applyToObjects(selectedLayerNumber,
				  ApplyGeneralPathOrGraphicSetCB,
				  palEditor,
				  IlFalse);
	    IlSymbol* remove = IlGetSymbol("_TO_REMOVE_");
	    for (IlUInt i = 0; i < count; i++) {
		if (objects[i]->hasProperty(remove)) {
		    m->invalidateRegion(objects[i]);
		    m->removeObject(objects[i], IlFalse, IlTrue);
		}
	    }
	    if (layer->isSubtypeOf(IlvTiledLayer::ClassInfo())) {
		//update the Renderer
		IlvTiledLayer* tl = (IlvTiledLayer*)layer;
		IlvTileLoader* loader = tl->getTileLoader();
		IlvMapTileLoader* mapLoader =
		    IL_DYNAMICCAST(IlvMapTileLoader*, loader);
		objects = layer->getObjects(count);
		first = objects[0];
		if (mapLoader) {
		    IlvStringProperty* prop = (IlvStringProperty*)
			layer->getNamedProperty(IlGetSymbol("_GEOMETRY_"));
		    IlvClassInfo* info = 0;
		    if (prop) {
			info = IlvGetClassInfo(prop->getString());
		    }
		    ReaderController r(m->getDisplay(), palEditor, info);
		    mapLoader->setFeatureRenderer(r.getRenderer(), IlTrue);
		}
#if defined(HAS_SDO_SUPPORT)
		else {
		    IlvDefaultObjectSDOTileLoader* l =
		      IL_DYNAMICCAST(IlvDefaultObjectSDOTileLoader*, loader);
		    if (l) {
			IlvStringProperty* prop = (IlvStringProperty*)
			  layer->getNamedProperty(IlGetSymbol("_GEOMETRY_"));
			IlvClassInfo* info = 0;
			if (prop) {
			    info = IlvGetClassInfo(prop->getString());
			}
			ReaderController r(m->getDisplay(), palEditor, info);
			((IlvObjectSDOLayer*)layer)
			    ->setFeatureRenderer(r.getRenderer());
		    }
		}
#endif
	    }
	    IlvSetContentsChangedUpdate(IlTrue);
	    m->contentsChanged();
	    m->reDrawViews();
	    legend->createAllLegend();
	    // updating for the next visit
	    MapBuffer::UpdateLayerAttributes(layer, palEditor);
	}
	dialog.removeObjects(IlTrue, IlFalse);
    }
}

// --------------------------------------------------------------------------
IlBoolean
ContextualMenuInteractor::handleEvent(IlvGraphic* obj,
				      IlvEvent& event,
				      const IlvTransformer* t)
{
    // Check that the object is a gadget
    IlvGadget* gadget = accept(obj) ? IL_CAST(IlvGadget*, obj) : 0;
    if (gadget && gadget->isActive()) {
	// Is it time to display the contextual menu ?
	if (shouldShowMenu(obj, event, t)) {
	    // Get the menu
	    IlvPopupMenu* menu = getMenu(obj, event, t);
	    // Show it
	    if (menu) {
		menu->get(IlvPoint(event.gx(), event.gy()),
			  /* transient */ 0);
		return IlTrue;
	    }
	}
    }
    // Default behaviour of the gadget
    return IlvGadgetInteractor::handleEvent(obj, event, t);
}

// --------------------------------------------------------------------------
IlBoolean
ContextualMenuInteractor::shouldShowMenu(IlvGraphic*,
					 IlvEvent& event,
					 const IlvTransformer*) const
{
    // The contextual menu is displayed by default when the right button
    // is released.
    return (event.type() == IlvButtonUp)
	&& (event.button() == IlvRightButton);
}

// --------------------------------------------------------------------------
IlvPopupMenu*
LegendGadgetInteractor::getMenu(IlvGraphic* graphic,
				IlvEvent& event,
				const IlvTransformer* t) const
{
    // Find the item located at the event location
    IlUShort col = 0;
    IlUShort row = 0;
    IlvAbstractMatrixItem* item =
	_legend->getMatrix()->pointToItem(IlvPoint(event.x(),
						   event.y()),
					  col,
					  row,
					  (IlvTransformer*)t);
    if (!item) {
	_legend->setLastSelectedItem(-1);
	return 0;
    }
    _legend->setLastSelectedItem(row);
    // Create the menu if needed
    static IlvPopupMenu* menu = 0;
    if (!menu) {
	// Create the pop-up menu
	menu = new IlvPopupMenu(_legend->getDisplay());
	// for the menu
	static struct {
	    const char* label;
	    IlvGraphicCallback callback;
	} menuDef[] = {
	    { "Bring to front", ToTopCB },
	    { "Send to back", ToBottomCB },
	    { 0, 0 },
	    { "Rendering", RenderingCB },
	    { "Visibility filters", VisibilityFilterCB },
	    { 0, 0 },
	    { "Remove layer", RemoveCB }
	};
	for (IlInt i = 0; i < 7; i++) {
	    if (menuDef[i].label != 0) {
		IlvMenuItem* item = new IlvMenuItem(menuDef[i].label);
		if (menuDef[i].callback) {
		    item->setClientData(_legend);
		    item->setCallback(menuDef[i].callback);
		}
		menu->insertItem(item);
	    }
	    else {
		menu->insertItem(new IlvMenuItem());
	    }
	}
	// Fill it with predefined colors
    }
    // Return the menu
    return menu;
}
