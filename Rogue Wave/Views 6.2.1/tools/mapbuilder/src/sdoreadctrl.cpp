// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/sdoreadctrl.cpp
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
// The implementation of The SDO Reader controller methods.
// --------------------------------------------------------------------------
#if defined(HAS_SDO_SUPPORT)

#include <ilviews/gadgets/stdialog.h>

#include <ilviews/maps/format/oracle/objectmodel/8ilayer.h>
#include <ilviews/maps/format/oracle/objectmodel/8iread.h>
#include <ilviews/maps/format/oracle/objectmodel/8iutil.h>

#include "sdoreadctrl.h"
#include "builder.h"

#if !defined(IL_STD)
#  include <stdio.h>
#endif/* !IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
static void
NotebookSelectPage(IlvNotebook*n, IlvNotebookPage*p)
{
    int count = n->getPagesCardinal();
    IlvNotebookPage** pages = n->getPages();
    for (int i = 0; i <  count; i ++) {
	if (pages[i] == p) {
	    n->changeSelection(i,IlTrue);
	}
    }
}

// --------------------------------------------------------------------------
// A private tile listener class for error reporting
class MyTileListener
: public IlvTileListener
{
public:
    MyTileListener(MapBuilder* builder)
    : _builder(builder) {}

    virtual void beginGroupedNotification(IlvTileController* c) {}
    virtual void endGroupedNotification(IlvTileController* c) {}
    virtual void tileChanged(IlvTile* tile,
			     IlvTileStatus oldStatus,
			     IlvTileStatus newStatus) {}
    virtual void controllerDeleted(IlvTileController*) {}
    // Always, override this method in order to raise the Data Base error
    // that may have occured in an IlvTile load process.
    virtual void loadError(IlvTile* tile, IlvMapsError error)
	{ _builder->reportError(IlvMaps::GetErrorMessageId(error)); }

    virtual void loadComplete(IlvTile* tile)
	{}
    virtual void startEnabled(IlvTileController* c)
	{}

    MapBuilder* _builder;
};

// --------------------------------------------------------------------------
// SdoReaderController methods
// --------------------------------------------------------------------------
SdoReaderController::SdoReaderController(IlvDisplay* d,
					 IlvSystemView transientFor,
					 MapBuilder* builder)
: ReaderController(d,transientFor),
  _builder(builder)
{
    okButton->setLabel("Create layer");
    cancelButton->setLabel("Close");
}

// --------------------------------------------------------------------------
SdoReaderController::~SdoReaderController()
{
}

// --------------------------------------------------------------------------
void
SdoReaderController::updateController()
{
    MapBuffer* buffer = _builder->getCurrentBuffer();
    if (buffer == 0) {
	// make everything unsensitive
	if (notebook->isSensitive()) {
	    notebook->setSensitive(IlFalse);
	}
	if (okButton->isSensitive()) {
	    okButton->setSensitive(IlFalse);
	}
	return;
    }
    if (!notebook->isSensitive()) {
	notebook->setSensitive(IlTrue);
    }
    if (!okButton->isSensitive()) {
	okButton->setSensitive(IlTrue);
    }
    // check that destination toggle is to be activated
    IlvMapInfo* info = IlvMapInfo::Get(buffer->getManager());
    if (info == 0) {
	setRequestingForDestProjection(IlTrue);
	setRequestingForDestAdapter(IlTrue);
    }
    else {
	setRequestingForDestProjection(IlFalse);
	setRequestingForDestAdapter(IlFalse);
    }
    notebook->reDraw();
}

// --------------------------------------------------------------------------
void
SdoReaderController::cancelClicked()
{
    ReaderController::cancelClicked();
    hide();
}

// --------------------------------------------------------------------------
void
SdoReaderController::okClicked()
{
    MapBuffer* buffer = _builder->getCurrentBuffer();
    if (!buffer) {
	return;
    }
    IlvManager* manager = buffer->getManager();
    ReaderController::okClicked();
    //
    // Perform map info checking
    //
    IlvProjection* destProjection = 0;
    IlvMapAdapter* destinationAdapter = 0;

    IlvMapInfo* destMapinfo = IlvMapInfo::Get(manager);

    if (destMapinfo == 0) {
	if (isRequestingForDestProjection() &&
	    (getDestProjection() == 0)) {
	    IlvIErrorDialog dial(notebook->getDisplay(),
				 "Please specify a destination Projection");
	    dial.moveToView(container);
	    dial.get();
	    NotebookSelectPage(notebook, getDestProjectionRequestPage());
	    return;
	}
	if (isRequestingForDestProjection()) {
	    destProjection = getDestProjection();
	}
	if (isRequestingForDestAdapter() && destProjection) {
	    destinationAdapter = getDestAdapter(destProjection);
	}
    }
    // set mapinfo to manager
    if (destMapinfo == 0 && destProjection != 0 && destinationAdapter != 0) {
	destMapinfo = new IlvMapInfo(destProjection,
				     destinationAdapter,
				     IlFalse);
	destMapinfo->attach(manager);
    } else if (destMapinfo != 0) {
	destProjection = (IlvProjection*)destMapinfo->getProjection();
	destinationAdapter = (IlvMapAdapter*)destMapinfo->getAdapter();
    }
    char* tableName = getSDOLayerTableName();
    char* geomName = getSDOLayerGeometryName();
    if (tableName == 0 || geomName == 0) {
	_builder->reportError("No layer selected\n");
	if (tableName) {
	    delete tableName;
	}
	tableName = 0;
	if (geomName) {
	    delete geomName;
	}
	geomName = 0;
	return;
    }
    //
    // Case of no load on demand
    //
    if (!isLOD()) {
	IlvCoordinate UL;
	IlvCoordinate LR;
	getAOI(UL,LR);
	// Should be able to query the rectangle of interest
	// For now, if the rectangle is a null area rectangle,
	// perform a full request.
	IlvMapsError error;
	IlBoolean nullRect;
	nullRect = (IlvAbs(UL.x() - LR.x()) < 1e-10)
	        || (IlvAbs(UL.y() - LR.y()) < 1e-10);
	IldRequest* request = 0;
	IlvObjectSDOFeatureIterator* iterator;
	if (!nullRect) {
	    request = IlvObjectSDOUtil::GetRequestFromRect(_builder
							         ->getDbms(),
							   tableName,
							   geomName,
							   UL, LR,
							   error);
	    if (error != IlvMaps::NoError()) {
		const char* msg = IlvMaps::GetErrorMessageId(error);
		char* message = (char*)"Cannot perform request : %s\n";
		char* buffer = new char[strlen(message) + strlen(msg) + 1];
		sprintf(buffer, message, msg);
		_builder->reportError(buffer);
		delete [] buffer;
		return;
	    }
	}
	if (nullRect) {
	    IlString req("select * from ");
	    req += (IlString)tableName;
	    iterator = new IlvObjectSDOFeatureIterator(_builder->getDbms(),
						       req.getValue(),
						       geomName);
	} else {
		iterator = new IlvObjectSDOFeatureIterator(request, geomName);
	}

	if (iterator->getInitStatus() != IlvMaps::NoError()) {
	    const char* msg = IlvMaps::GetErrorMessageId(iterator
							 ->getInitStatus());
	    char* message = (char*)"Cannot perform request : %s\n";
	    char* buffer = new char[strlen(message) + strlen(msg) + 1];
	    sprintf(buffer, message, msg);
	    _builder->reportError(buffer);
	    delete [] buffer;
	    return;
	}
	// Check for attributes
	IlBoolean attachingAttributes = isAttachingAttributes();
	// add the objects
	manager->addLayer(-1);
	int numLayers = manager->getNumLayers();
	IlvManagerLayer* insertionLayer = manager->getManagerLayer(numLayers
								   - 1);
	manager->setInsertionLayer(numLayers - 1);
	char* buf = new char[strlen(tableName) + strlen(geomName) + 40];
	sprintf(buf, "%s.%s request", tableName, geomName);
	insertionLayer->setName(buf);
	delete [] buf;
	buf = 0;
	IlvScaleVisibilityFilter* filter = getVisibilityFilter();
	if (filter) {
	    insertionLayer->addVisibilityFilter(filter);
	}
	IlvFeatureRenderer* renderer = getRenderer();
	error = IlvMaps::NoError();
	IlvMapInfo* mapinfo = IlvMapInfo::Get(manager);
	IlvMapsError renderingStatus = IlvMaps::NoError();
	IlvMapFeature* feature = 0;
	IlvSetContentsChangedUpdate(IlFalse);
	manager->initReDraws();
	int count = 0;

	for (feature = (IlvMapFeature*)iterator->getNextFeature(error);
	     feature && (error == IlvMaps::NoError());
	     feature = (IlvMapFeature*)iterator->getNextFeature(error)) {
	    // render graphic
	    IlvGraphic* g = renderer->makeGraphic(*feature,
						  *mapinfo,
						  renderingStatus);

	    if (renderingStatus == IlvMaps::NoError()) {
		if (attachingAttributes) {
		    const IlvFeatureAttributeProperty* ap;
		    ap = feature->getAttributes();
		    if (ap)
			g->setNamedProperty(ap->copy());
		}
		manager->addObject(g, IlFalse);
		manager->invalidateRegion(g);
		count ++;
	    }
	    else {
		if (g) {
		    delete g;
		}
	    }
	}
	IlvSetContentsChangedUpdate(IlTrue);
	manager->reDrawViews();
	// updating for the next visit
	MapBuffer::UpdateLayerAttributes(insertionLayer, paletteEditor);
    	char buf1[500];
	sprintf(buf1,"%d objects added\n",count);
	_builder->reportInfo(buf1);

	if (iterator) {
	    delete iterator;
	}
	iterator = 0;
	if (renderer) {
	    delete renderer;
	}
	renderer = 0;
	return;
    } // end of not LOD mode

    // Everything that follow is related to load on demand
    IlvCoordinate tilesize;
    getLODTileSize(tilesize);
    if (destProjection) {
	getLODTileSize(tilesize,destProjection->getUnitConverter());
    }

    // Check if the manager already has objects read
    IlBoolean managerEmpty = (manager->getCardinal() == 0);

    //    IlvSDOUtil::EnableSQLTraces(&cerr);
    IlvObjectSDOLayer* layer = new IlvObjectSDOLayer(destinationAdapter,
						     _builder->getDbms(),
						     tableName,
						     geomName,
						     (IlDouble)tilesize.x(),
						     (IlDouble)tilesize.y());
    if (isAttachingAttributes()) {
	layer->setAttachingAttributes(IlTrue);
    }
    char* buf = new char[strlen(tableName) + strlen(geomName) + 2];
    sprintf(buf,"%s.%s",tableName,geomName);
    layer->setName(buf);
    if (buf) {
	delete [] buf;
    }
    buf = 0;
    IlvMapsError initError = layer->getInitStatus();
    if (initError != IlvMaps::NoError()) {
	_builder->reportError(IlvMaps::GetErrorMessageId(initError));
    }
    // add a listener
    MyTileListener* l = new MyTileListener(_builder);
    layer->getTileController()->addTileListener(l);
    IlvFeatureRenderer* renderer = getRenderer();
    layer->setFeatureRenderer(renderer);
    manager->addLayer(layer);
    if (managerEmpty) {
	IlInt col = 0;
	IlInt row = 0;
	IlInt upperRow, lowerRow, leftCol, rightCol;
	layer->getTileController()->getTileIndexes(layer->getSize(),
						   upperRow,
						   lowerRow,
						   leftCol,
						   rightCol);
	col = leftCol + rightCol / 2;
	row = upperRow + lowerRow / 2;
	layer->fitTransformerToTile(manager->getFirstView(), row, col);
    }
    IlvScaleVisibilityFilter* filter = getVisibilityFilter();
    if (filter) {
	layer->addVisibilityFilter(filter);
    }
    if (tableName) {
	delete tableName;
    }
    if (geomName) {
	delete geomName;
    }
    char* mesg = new char[strlen("Layer %s loaded.") +
			strlen(layer->getName() ? layer->getName() : "") +1];
    sprintf(mesg,"Layer ");
    if (layer->getName()) {
	strcat(mesg, layer->getName());
	strcat(mesg, " ");
    }
    strcat(mesg, "loaded.\n");
    _builder->reportInfo(mesg);
    if (mesg) {
	delete [] mesg;
    }
    mesg = 0;
    MapBuffer::UpdateLayerAttributes(layer, paletteEditor);
    layer->start();
    manager->draw(buffer->getView());
    IlvRect r;
    buffer->getView()->sizeVisible(r);
    manager->initReDraws();
    manager->invalidateRegion(buffer->getView(), r);
    manager->reDrawViews();
} // SdoReaderController::okClicked

#endif /* HAS_SDO_SUPPORT */
