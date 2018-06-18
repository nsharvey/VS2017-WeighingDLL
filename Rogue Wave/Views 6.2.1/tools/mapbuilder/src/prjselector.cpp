// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/prjselector.cpp
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
// The implementation of ProjectionSelector methods.
// --------------------------------------------------------------------------
#include "prjselector.h"
#include <ilviews/manager/manager.h>
#include <ilviews/graphics/rectview.h>
#include <ilviews/graphics/polyline.h>
#include <ilviews/gadgets/rectgadc.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/slist.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/gadgets/scombo.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/maps/projection/allprojs.h>
#include <ilviews/maps/projection/projitf.h>
#include <ilviews/maps/adapter.h>
#include <ilviews/maps/mapinfo.h>

#if defined(IL_STD)
#  include <cstring>
#  include <cstdio>
IL_STDUSE
#else  /* !IL_STD */
#  include <string.h>
#  include <stdio.h>
#endif /* !IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
static void
ProjectionSelectionCB(IlvGraphic* graphic,IlvAny arg)
{
    ProjectionSelector* selector = (ProjectionSelector*)arg;
    IlvScrolledComboBox* combo = selector->_getProjectionCombo();
    const IlvProjectionDictionary& dict = selector->_getDictionary();
    const char* selection = combo->getSelection();
    if (selection) {
	if (strcmp(selection, "Unknown")) {
	    IlvProjection* projection = dict.createProjection(selection);
	    if (projection != 0) {
		projection->setShared();
		selector->setProjection(projection);
	    }
	}
	else {
	    IlvProjection* projection = new IlvUnknownProjection();
	    projection->setShared();
	    selector->setProjection(projection);
	}
    }
}

// --------------------------------------------------------------------------
void
EllipsoidSelectionCB(IlvGraphic* graphic, IlAny arg)
{
    ProjectionSelector* selector = (ProjectionSelector*)arg;
    IlvScrolledComboBox* combo = selector->_getEllipsoidCombo();
    const char* selection = combo->getSelection();
    if (selection) {
	selector->setEllipsoid(combo->whichSelected());
    }
}

// --------------------------------------------------------------------------
void
ProjectionEditionCB(IlvGraphic* graphic, IlAny arg)
{
    ProjectionSelector* selector = (ProjectionSelector*)arg;
    IlvMatrix* matrix = (IlvMatrix*)graphic;
    IlUShort c, r;
    matrix->getEditedItem(c, r);
    // get list of accessors
    IlvProjectionInterface* interface =
				   selector->getProjection()->getInterface();
    const IlvSymbol* const* accessors = 0;
    const IlvValueTypeClass* const* types = 0;
    IlUInt accessorsCount;
    interface->getAccessors(&accessors,&types,accessorsCount);
    // switch on type of item
    IlvAbstractMatrixItem* item = matrix->getItem(c,r);
    IlBoolean applyOk = IlFalse;
    const char* typeName = types[r]->name();
    if (strcmp(typeName, "Double") == 0) {
	IlvDoubleMatrixItem* ditem = (IlvDoubleMatrixItem*)item;
	IlvValue arg(accessors[r]->name(),(IlDouble)(ditem->getDouble()));
	applyOk = interface->applyValue(arg);
    }
    else if (strcmp(typeName, "String") == 0) {
	IlvLabelMatrixItem* litem = (IlvLabelMatrixItem*)item;
	IlvValue arg(accessors[r]->name(),(const char*)(litem->getLabel()));
	applyOk = interface->applyValue(arg);
    }
    else if (strcmp(typeName, "UInt") == 0) {
	IlvIntMatrixItem* litem = (IlvIntMatrixItem*)item;
	IlvValue arg(accessors[r]->name(),(IlUInt)(litem->getInt()));
	applyOk = interface->applyValue(arg);
    }
    else if (strcmp(typeName, "Boolean") == 0) {
	IlvGadgetMatrixItem* gitem = (IlvGadgetMatrixItem*)item;
	IlvComboBox* gad = (IlvComboBox*)gitem->getGadget();
	if (gad->whichSelected() == 0) {
	    IlvValue arg(accessors[r]->name(),(IlBoolean)IlTrue);
	    applyOk = interface->applyValue(arg);
	}
	else {
	    IlvValue arg(accessors[r]->name(),(IlBoolean)IlFalse);
	    applyOk = interface->applyValue(arg);
	}
    }
    selector->updatePreview();
}

// --------------------------------------------------------------------------
void
PreviewResizeCB(IlvView* view, IlvRect& rect, IlAny arg)
{
    ((IlvManager*)arg)->fitTransformerToContents(view, IlTrue, IlTrue);
}

// --------------------------------------------------------------------------
ProjectionSelector::ProjectionSelector(IlvDisplay* display,
				       const IlvRect& rect,
				       IlvProjection* defaultProjection)
: IlvGadgetContainerRectangle(display, rect),
  _projectionCombo(0),
  _projdict(IlTrue),
  _projection(defaultProjection),
  _matrix(0),
  _ellipsoidNames(0),
  _ellipsoidCount(0),
  _eMatrix(0),
  _currentEllipsoid(0),
  _preview(0),
  _previewManager(0),
  _sourceManager(),
  _previewAdapter(0)
{
     // Load data
    _sourceManager = new IlvManager(getDisplay(),
				    0,
				    IlFalse,
				    30000 /* no quadtree needed */,
				    30000 /* no quadtree needed */);

    // Try to load ILVMAPSHOME/bitmap...
    const char* name = "tools/mapbuilder/data/world.ilv";
    char path[2048];
    const char* home = getDisplay()->getEnvOrResource("ILVMAPSHOME");
    sprintf(path, "%s/%s", home ? home : ".", name);
    if (IlvFileExists(path)) {
	_sourceManager->read(path);
    }
    else {
	home = getDisplay()->getEnvOrResource("ILVHOME");
	sprintf(path, "%s/%s", home ? home : ".", name);
	if (IlvFileExists(path)) {
	    _sourceManager->read(path);
	}
    }
    if (_projection && _projection->isShared()) {
	_projection->lock();
    }
}

// --------------------------------------------------------------------------
ProjectionSelector::~ProjectionSelector()
{
    if (_ellipsoidNames) {
	delete _ellipsoidNames;
    }
    if (_currentEllipsoid) {
	delete _currentEllipsoid;
    }
    if (_sourceManager) {
	delete _sourceManager;
    }
    if (_previewManager) {
	delete _previewManager;
    }
    if (_projection && _projection->isShared()) {
	_projection->unLock();
    }
}

// --------------------------------------------------------------------------
IlvView* ProjectionSelector::createView(IlvAbstractView* parent,
					const IlvRect& rect)
{
    IlvView* view = IlvGadgetContainerRectangle::createView(parent,rect);
    
    IlvGadgetContainer* container = (IlvGadgetContainer*)view;

    // compute some sizes
    IlvRect prjFrameRect(0,0,rect.w()/2-5,rect.h());
    IlvRect prjComboRect(prjFrameRect.x() + 5,
			 prjFrameRect.y() + 20,
			 prjFrameRect.w() - 10,
			 20);
    IlvRect prjMatrixRect(prjFrameRect.x() + 5,
			  prjFrameRect.y() + prjComboRect.y()
			  + prjComboRect.h() + 5,
			  prjFrameRect.w() - 10,
			  prjFrameRect.h() - prjComboRect.h()
			  - prjComboRect.y() - 10);
    IlvRect eFrameRect(prjFrameRect.w() + 5,0,
		       rect.w() - prjFrameRect.w() - 10,
		       120);
    IlvRect eComboRect(eFrameRect.x() + 5,
		       eFrameRect.y() + 20,
		       eFrameRect.w() - 10,
		       20);
    IlvRect eMatrixRect(eFrameRect.x() + 5,
			eFrameRect.y() + eComboRect.y()
			+ eComboRect.h() + 5,
			eFrameRect.w() - 10,
			eFrameRect.h() - eComboRect.h()
			- eComboRect.y() - 10);

    IlvRect previewFrameRect(eFrameRect.x(),
			     eFrameRect.y() + eFrameRect.h() + 5,
			     eFrameRect.w(),
			     prjFrameRect.h() - 5 - eFrameRect.h());

    IlvRect previewRect(previewFrameRect.x() + 5,
			previewFrameRect.y() + 15,
			previewFrameRect.w() - 10,
			previewFrameRect.h() - 20);
    // a frame for projection
    IlvFrame* frame = new IlvFrame(parent->getDisplay(),
				   "Projection",
				   prjFrameRect);
    
    container->addObject(frame);
    container->getHolder()->attach(frame,IlvHorizontal,0,1,1);
    container->getHolder()->attach(frame,IlvVertical,0,1,0);

    // a frame for ellipsoid
    frame = new IlvFrame(parent->getDisplay(),
			 "Ellipsoid",
			 eFrameRect);
    
    container->addObject(frame);
    container->getHolder()->attach(frame, IlvHorizontal, 1, 1, 0);
    container->getHolder()->attach(frame, IlvVertical, 0, 0, 1);

    // a frame Preview
    frame = new IlvFrame(parent->getDisplay(),
			 "Preview",
			 previewFrameRect);
   
    container->addObject(frame);
    container->getHolder()->attach(frame, IlvHorizontal, 1, 1, 0);
    container->getHolder()->attach(frame, IlvVertical, 0, 1, 0);

    // a projection stringlist
    // -> must append the unknown projection
    IlUInt pcount;
    const char** pnames = _projdict.getProjectionNames(pcount);

    IlUInt projectionCount = pcount + 1;
    char** projectionNames = new char*[projectionCount];
    for (IlUInt i = 0; i < pcount; i++) {
	projectionNames[i] = new char[strlen(pnames[i]) + 1];
	sprintf(projectionNames[i], pnames[i]);
    }
    projectionNames[pcount] = new char[strlen("Unknown") + 1];
    sprintf(projectionNames[pcount], "Unknown");
    delete pnames;
    pnames = 0;
    _projectionCombo = new IlvScrolledComboBox(parent->getDisplay(),
					       prjComboRect,
					       0,
					 (const char* const*)projectionNames,
					       (IlUShort)projectionCount);
    _projectionCombo->addCallback(ProjectionSelectionCB);
    _projectionCombo->setClientData((IlvAny)this);
    _projectionCombo->setVisibleItems(20);    
    container->addObject(_projectionCombo);
    container->getHolder()->attach(_projectionCombo,IlvHorizontal,0,1,1);
    container->getHolder()->attach(_projectionCombo,IlvVertical,0,0,1);

    // A matrix for projection parameters
    _matrix = new IlvMatrix(parent->getDisplay(),
			    prjMatrixRect,
			    2,
			    1,
			    prjMatrixRect.w() / 2);
    _matrix->setAutoLineSelect(IlTrue);
    _matrix->useRelief(IlTrue);
    _matrix->setExclusive(IlTrue);
    _matrix->showGrid(IlTrue);
    _matrix->autoFitToSize(IlTrue);
    _matrix->scrollBarShowAsNeeded(IlTrue,IlFalse);
    _matrix->hideScrollBar(IlvHorizontal);

    _matrix->setClientData(this);
    _matrix->setSecondaryCallback(ProjectionEditionCB);
    
    container->addObject(_matrix);
    container->getHolder()->attach(_matrix,IlvHorizontal,0,1,1);
    container->getHolder()->attach(_matrix,IlvVertical,0,1,0);		    
    
    
  
    // create ellipsoid list
    const IlvEllipsoid* const* ellipsoids =
	IlvEllipsoid::GetRegisteredEllipsoids(_ellipsoidCount);
    _ellipsoidNames = (const char**)new char*[_ellipsoidCount];

    for (IlUInt iellipsoid=0; iellipsoid < _ellipsoidCount; iellipsoid++) {
	_ellipsoidNames[iellipsoid] = ellipsoids[iellipsoid]->getName();
    }

    // Create combo box for ellispoid
    
    _ellipsoidCombo = new IlvScrolledComboBox(parent->getDisplay(),
			      eComboRect,
		      	      0,
			      (const char* const*)_ellipsoidNames,
			      (IlUShort)_ellipsoidCount);
    _ellipsoidCombo->setVisibleItems(8);

    _ellipsoidCombo->addCallback(EllipsoidSelectionCB);
    _ellipsoidCombo->setClientData((IlvAny)this);

    container->addObject(_ellipsoidCombo);
    container->getHolder()->attach(_ellipsoidCombo,IlvHorizontal,1,1,0);
    container->getHolder()->attach(_ellipsoidCombo,IlvVertical,0,0,1);

    // Create Matrix for ellipsoid parameters
    _eMatrix = new IlvMatrix(parent->getDisplay(),
			     eMatrixRect,
			     2,
			     2,
			     eMatrixRect.w() / 2);
    _eMatrix->setAutoLineSelect(IlTrue);
    _eMatrix->useRelief(IlTrue);
    _eMatrix->setExclusive(IlTrue);
    _eMatrix->showGrid(IlTrue);
    _eMatrix->autoFitToSize(IlTrue);
    _eMatrix->scrollBarShowAsNeeded(IlTrue,IlFalse);
    _eMatrix->hideScrollBar(IlvHorizontal);

    // Add items to matrix
    // name
    IlvLabelMatrixItem* labelItem =
	new IlvLabelMatrixItem("Semi-Major axis (A)", IlTrue);
    _eMatrix->set(0,0,labelItem);
    _eMatrix->setItemReadOnly(0,0,IlTrue);
    _eMatrix->setItemAlignment(0,0,IlvLeft);
    
    labelItem = new IlvLabelMatrixItem("Semi-Minor axis (B)", IlTrue);
    _eMatrix->set(0,1,labelItem);
    _eMatrix->setItemReadOnly(0,1,IlTrue);
    _eMatrix->setItemAlignment(0,1,IlvLeft);
    
    container->addObject(_eMatrix);
    container->getHolder()->attach(_eMatrix,IlvHorizontal,1,1,0);
    container->getHolder()->attach(_eMatrix,IlvVertical,0,0,1);	
    // a preview
    _preview = new IlvViewRectangle(parent->getDisplay(), previewRect);  
    container->addObject(_preview);
    container->getHolder()->attach(_preview,IlvHorizontal,1,1,0);
    container->getHolder()->attach(_preview,IlvVertical,0,1,0);
    _previewManager = new IlvManager(parent->getDisplay(),
				     0,
				     IlFalse,
				     30000 /* no quadtree needed */,
				     30000 /* no quadtree needed */);
    _previewManager->addView(_preview->getView());
    _previewManager->setKeepingAspectRatio(_preview->getView());
    _preview->getView()->setResizeCallback(PreviewResizeCB,_previewManager);

    // Select projection in combobox
    int position = -1;
    if (_projection) {
	for (IlUInt j = 0; (position == -1) && (j < projectionCount); j++) {
	    if (_projection->getClassInfo()
		->isSubtypeOf(IlvUnknownProjection::ClassInfo())) {
		if (strcmp(projectionNames[j],"Unknown") == 0) {
		    position = j;
		    break;
		}
	    }
	    else if (!strcmp(projectionNames[j],
			     _projection->getClassInfo()->getProjectionName())) {
		position = j;
		break;
	    }
	}
	if (position >= 0) {
	    _projectionCombo->setSelected(position,IlTrue);
	}
    }
    setProjection(_projection);
    for (IlUInt k = 0; k < projectionCount; k++) {
	delete [] projectionNames[k];
    }
    delete [] projectionNames;
    projectionNames = 0;
    // return created view
    return view;
}

// --------------------------------------------------------------------------
void
ProjectionSelector::setProjection(IlvProjection* projection)
{
    if (_projection != projection) {
	if (projection && projection->isShared()) {
	    projection->lock();
	}
	if (_projection) {  
	    if (_projection->isShared()) {
		_projection->unLock();
	    }
	    else {
		delete _projection;
	    }
	}
	_projection = projection;
    }

    // case of setting projection to NULL -> do nothing and return
    if (projection == 0) {
	if (_matrix) {
	    _matrix->reinitialize(2,0);
	    _matrix->ensureVisible(0,0,IlFalse);
	    _matrix->reDraw();
	
	    setEllipsoid((const IlvEllipsoid*)0);
	    _projectionCombo->setLabel(0);
	}
	return;
    } 
    // Select projection in combobox
    _projectionCombo->setLabel(_projection->getClassInfo()
					  ->getProjectionName());

    // Update the projection parameters
    IlvProjectionInterface* interface = projection->getInterface();
    const IlvSymbol* const* accessors = 0;
    const IlvValueTypeClass* const* types = 0;
    IlUInt accessorsCount;
    interface->getAccessors(&accessors,&types,accessorsCount);
    _matrix->reinitialize(2,(IlUShort)accessorsCount);
    
    // add items
    for (IlUInt i=0; i < accessorsCount; i++) {
	// name
	IlvLabelMatrixItem* labelItem =
	    new IlvLabelMatrixItem(accessors[i]->name(),
				   IlTrue);
	
	_matrix->set(0,(IlUShort)i,labelItem);
	_matrix->setItemReadOnly(0,(IlUShort)i,IlTrue);
	_matrix->setItemAlignment(0,(IlUShort)i,IlvLeft);
	// type
	IlvAbstractMatrixItem* fieldItem=0;
	IlvValue arg(accessors[i]->name());
	IlvValue theValue = interface->queryValue(arg);
	// type string
	if (strcmp(types[i]->name(), "String") == 0) {
	    fieldItem = new IlvLabelMatrixItem((const char*)theValue);
	}
	else if (strcmp(types[i]->name(), "Double") == 0) {
	    fieldItem = new IlvDoubleMatrixItem((IlDouble)theValue);
	}
	else if (strcmp(types[i]->name(), "UInt") == 0) {
	    fieldItem = new IlvIntMatrixItem((IlInt)theValue);
	}
	else if (strcmp(types[i]->name(), "Boolean") == 0) {
	    static const char* labels[] = { "True", "False" };
	    IlvComboBox* cb = new IlvComboBox(getDisplay(),
					     IlvPoint(0,0),
					     0,
					     labels,2);
	    if ((IlBoolean)theValue) {
		cb->setSelected(0, IlTrue);
	    }
	    else {
		cb->setSelected(1, IlTrue);
	    }
	    fieldItem = new IlvGadgetMatrixItem(cb);
	}
	else {
	    fieldItem = new IlvLabelMatrixItem("toto", IlTrue);
	}
	_matrix->set(1,(IlUShort)i, fieldItem);
	_matrix->setItemAlignment(1, (IlUShort)i, IlvLeft);
    } // loop on items
    _matrix->ensureVisible(0, 0, IlFalse);
    _matrix->reDraw();
    // Change ellipsoid
    setEllipsoid(_projection->getEllipsoid());
}

// --------------------------------------------------------------------------
void
ProjectionSelector::setEllipsoid(const IlvEllipsoid* e)
{
    if (_currentEllipsoid) {
	delete _currentEllipsoid;
    }
    _currentEllipsoid = e
			? new IlvEllipsoid(*e)
    			: new IlvEllipsoid(*IlvEllipsoid::SPHERE());

    if (_projection) {
	_projection->setEllipsoid(*_currentEllipsoid);
    }

    // update text fields
    IlvDoubleMatrixItem* afield =
	new IlvDoubleMatrixItem(_currentEllipsoid->getA());
    _eMatrix->set(1,0,afield);
    IlvDoubleMatrixItem* bfield =
	new IlvDoubleMatrixItem(_currentEllipsoid->getB());
    _eMatrix->set(1,1,bfield);
    _eMatrix->reDraw();

    // update ellipsoid combo
    if (_currentEllipsoid->getName() != 0) {
	int position = -1;
	for (IlUInt j=0; j < _ellipsoidCount; j++) {
	    if (strcmp(_ellipsoidNames[j],
		       _currentEllipsoid->getName()) == 0) {
		position = j;
		break;
	    }
	}
	if (position >= 0) {
	    _ellipsoidCombo->setSelected(position,IlTrue);
	}
    }
    
    updatePreview();
}

// --------------------------------------------------------------------------
void
ProjectionSelector::setEllipsoid(IlUInt i)
{
    IlUInt count;
    const IlvEllipsoid* const* ellipsoids =
	IlvEllipsoid::GetRegisteredEllipsoids(count);
    if (i < count) {
	setEllipsoid(ellipsoids[i]);
    }
}

// --------------------------------------------------------------------------
static void
ProjectObject(IlvGraphic*g, IlvAny a)
{
    ((ProjectionSelector*)a)->projectObject(g);
}

// --------------------------------------------------------------------------
void
ProjectionSelector::projectObject(IlvGraphic* g)
{
    IlvMapInfo* sourceMapInfo = IlvMapInfo::Get(_sourceManager);
    
    if ((_previewAdapter == 0) || (sourceMapInfo == 0)) {
	return;
    }
    
    if (g->isSubtypeOf(IlvPolyline::ClassInfo())) {
	IlvPolyline* source = (IlvPolyline*)g;
	IlUInt count = source->numberOfPoints();

	IlvPoint* points = new IlvPoint[count];
	source->getPoints(points);
	IlBoolean noError = IlTrue;
	IlvCoordinate c;
	IlDouble distance;
	for (IlUInt i = 0; i < count ; i++) {
	    sourceMapInfo->inverse(points[i],c);
	    if (_projection->forward(c, c) != IlvMaps::NoError()) {
		noError = IlFalse;
		break;
	    }
	    if (!_previewAdapter->isInRange(c)) {
		noError = IlFalse;
		break;
	    }
	    _previewAdapter->toViews(c,points[i]);
	    if (i > 0) {
				IlDouble dx;
		IlDouble dy;
		
		dx = (IlDouble)(points[i].x() - points[i - 1].x());
		dy = (IlDouble)(points[i].y() - points[i - 1].y());
		
		distance = sqrt(dx * dx + dy * dy);
		distance = _previewAdapter->fromViews(distance);
		distance = _projection->getUnitConverter()
				      ->toMeters(distance);
		if (distance > _projection->getEllipsoid()->getA()) {
		    // disc assumed
		    noError = IlFalse;
		    break;
		}
	    }
	} // loop on points
	if (noError) {
	    IlvPolyline* projected =
		new IlvPolyline(_previewManager->getDisplay(),
				count,
				points,
				source->getPalette());
	    _previewManager->addObject(projected,
				       IlFalse);
	}
	delete [] points;
    }
}

// --------------------------------------------------------------------------
void
ProjectionSelector::updatePreview()
{
    _previewManager->deleteAll(IlTrue,IlFalse);

    if (_projection) {
	_previewAdapter = new IlvMapAdapter(_projection,1.);
	
	for (int i=0; i < _sourceManager->getNumLayers(); i++) {
	    _sourceManager->applyToObjects(i,
					   ProjectObject,
					   this,
					   IlTrue);
	}
	_previewManager->fitTransformerToContents(_preview->getView(),
						  IlTrue,IlTrue);
	
	delete _previewAdapter;
	_previewAdapter = 0;
    }
}
