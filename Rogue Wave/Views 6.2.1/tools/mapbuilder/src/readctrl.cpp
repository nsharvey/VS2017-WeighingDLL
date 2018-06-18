// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/readctrl.cpp
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
// The implementation of ReaderController methods.
// --------------------------------------------------------------------------
#include <ilviews/gadgets/toggle.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/maps/geometry/all.h>
#include <ilviews/maps/rendering/all.h>
#include <ilviews/maps/format/geotiff/gtiffreader.h>
#include <ilviews/maps/format/dted/dtedreader.h>
#include <ilviews/maps/format/dted/dtedlayer.h>
#include <ilviews/maps/format/shapefile/shpreader.h>
#include <ilviews/maps/format/shapefile/shpfile.h>
#include <ilviews/maps/format/cadrg/cadrgread.h>
#include <ilviews/maps/format/cadrg/cadrglayer.h>
#include <ilviews/maps/format/cadrg/cadrgtoc.h>
#if defined(HAS_SDO_SUPPORT)
#include <ilviews/maps/format/oracle/sdoutil.h>
#include <ilviews/maps/format/oracle/objectmodel/8iutil.h>
#include <ildblink/ilddbms.h>
#endif
#include <readctrl.h>

#if defined(IL_STD)
#  include <cstring>
#  include <cctype>
IL_STDUSE
#else  /* !IL_STD */
#  if !defined(WINDOWS)
#    include <strings.h>
#  endif
#  include <ctype.h>
#  include <stdio.h>
#endif /* !IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
// Utility
static void
NotebookSelectPage(IlvNotebook* n, IlvNotebookPage* p)
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
static IlBoolean
NotebookRemovePage(IlvNotebook*n,IlvNotebookPage*p)
{
    int count = n->getPagesCardinal();
    IlvNotebookPage** pages = n->getPages();
    for (int i = 0; i <  count; i ++) {
	if (pages[i] == p) {
	    n->removePage(i);
	    return IlTrue;
	}
    }
    return IlFalse;
}

// --------------------------------------------------------------------------
static void
SelectSensitiveAO(IlvGraphic* object, IlvAny arg)
{
    if (arg) {
	if (!object->isSensitive()) {
	    object->setSensitive(IlTrue);
	}
    }
    else {
	if (object->isSensitive()) {
	    object->setSensitive(IlFalse);
	}
    }
}

// --------------------------------------------------------------------------
static void
SelectSensitivity(IlvContainer* container, IlBoolean set)
{
    container->applyToObjects(SelectSensitiveAO,(IlvAny)set,IlTrue);
}

// --------------------------------------------------------------------------
// Callbacks
static void
ControllerOkCB(IlvGraphic* g, IlvAny arg)
{
    ReaderController* rc = (ReaderController*)arg;
    rc->okClicked();
}

// --------------------------------------------------------------------------
static void
ControllerCancelCB(IlvGraphic* g, IlvAny arg)
{
    ReaderController* rc = (ReaderController*)arg;
    rc->cancelClicked();
}

// --------------------------------------------------------------------------
static void
LODToggleCB(IlvGraphic* g, IlvAny arg)
{
    ReaderController* rc = (ReaderController*)arg;
    if (rc->getPreviewToggle()->getState()) {
	if (rc->getLodParams()) {
	    SelectSensitivity(rc->getLodParams()->getGadgetContainer(),
			      IlFalse);
	}
	if (rc->getAoiParams()) {
	    SelectSensitivity(rc->getAoiParams()->getGadgetContainer(),
			      IlTrue);
	}
	if (rc->getDestProjectionRequestPage()) {
	    rc->getDestProjectionRequestPage()->setSensitive(IlTrue);
	    rc->setRequestForDestProjection(IlTrue);
	}
    }
    else {
	if (rc->getLodParams()) {
	    SelectSensitivity(rc->getLodParams()->getGadgetContainer(), IlTrue);
	}
	if (rc->getAoiParams()) {
	    SelectSensitivity(rc->getAoiParams()->getGadgetContainer(),
			      IlFalse);
	}
	if (rc->getDestProjectionRequestPage()
#if defined(HAS_SDO_SUPPORT)
	    && !rc->isRequestingForSDOLayer()
#endif
	    ) {
	    rc->getDestProjectionRequestPage()->setSensitive(IlFalse);
	    rc->setRequestForDestProjection(IlFalse);
	}
    }
}

// --------------------------------------------------------------------------
static IlString*
idxFileName(IlString& shpFileName)
{
    if (shpFileName.endsWith(".shp")) {
	return new IlString(shpFileName.getSubString(0, (int)
						     shpFileName.getLength()
						     - 4) +
			    IlString(".idx"));
    }
    else {
	return new IlString(shpFileName.getSubString(0, (int)
						     shpFileName.getLength()
						     - 4) +
			    IlString(".IDX"));
    }
    
}

// --------------------------------------------------------------------------
static IlString*
shxFileName(IlString& shpFileName)
{
    if (shpFileName.endsWith(".shp")) {
	return new IlString(shpFileName.getSubString(0, (int)
						     shpFileName.getLength()
						     - 4) +
			    IlString(".shx"));
    }
    else {
	return new IlString(shpFileName.getSubString(0, (int)
						     shpFileName.getLength()
						     - 4) +
			    IlString(".SHX"));
    }
}

// --------------------------------------------------------------------------
ReaderController::ReaderController(IlvDisplay* d,
				   IlvSystemView transientFor)
: display(d),
  container(0),
  notebook(0),
  rendererEditorPage(0),
  sourceProjectionRequestPage(0),
  destProjectionRequestPage(0),
  destAdapterRequestPage(0),
  lodRequestPage(0),
#if defined(HAS_SDO_SUPPORT)
  sdoLayerRequestPage(0),
#endif
  visibilityFilterPage(0),
  attributeRequestPage(0),
  status(IlFalse),
  autohide(IlTrue),
  requestForSourceProjection(IlFalse),
  sourceProjection(0),
  sourceProjectionPanel(0),
  requestForDestProjection(IlFalse),
  destinationProjection(0),
  destProjectionPanel(0),
  requestForDestAdapter(IlFalse),
  destAdapterPanel(0),
  requestForVisibilityFilter(IlTrue),
  largeScaleCombo(0),
  smallScaleCombo(0),
  requestForLOD(IlFalse),
  lodSelector(0),
  previewToggle(0),
  lodToggle(0),
  lodParams(0),
  tileWidthTF(0),
  tileHeightTF(0),
  requestForLODTileSize(IlFalse),
  aoiParams(0),
  aoiULxTF(0),
  aoiULyTF(0),
  aoiLRxTF(0),
  aoiLRyTF(0),
  requestForAOI(IlFalse),
  paletteEditor(0),
  geometry(0),
  loadAttributeToggle(0),
  requestForAttributes(IlFalse),
  pagesCreated(IlFalse),
#if defined(HAS_SDO_SUPPORT)
  sdoDbms(0),
  sdoLayerList(0),
  sdoLayerNameCount(0),
  sdoLayerNames(0),
#endif
  okButton(0),
  cancelButton(0)
{
    container = new IlvGadgetContainer(display,
				       "ReaderController",
				       "Source file parameters",
				       IlvRect(0,0,600,400),
				       IlvStandardBorder,
				       IlTrue,
				       IlFalse,
				       transientFor);
    notebook = new IlvNotebook(display, IlvRect(5,5,590,360));
    container->addObject(notebook);
    container->getHolder()->attach(notebook, IlvHorizontal, 0, 1, 0);
    container->getHolder()->attach(notebook, IlvVertical, 0, 1, 0);
    // add buttons
    okButton = new IlvButton(display, "Ok", IlvRect(200, 370, 80, 24));
    container->addObject(okButton);
    okButton->setCallback(ControllerOkCB,this);
    container->getHolder()->attach(okButton,IlvHorizontal,1,0,1);
    container->getHolder()->attach(okButton,IlvVertical,1,0,0);

    cancelButton = new IlvButton(display, "Cancel", IlvRect(370,370,80,24));
    container->addObject(cancelButton);
    cancelButton->setCallback(ControllerCancelCB,this);

    container->getHolder()->attach(cancelButton,IlvHorizontal,1,0,1);
    container->getHolder()->attach(cancelButton,IlvVertical,1,0,0);
}

// --------------------------------------------------------------------------
ReaderController::ReaderController(IlvDisplay* d,
				   PaletteEditor* pe,
				   IlvClassInfo* info)
: display(d),
  container(0),
  notebook(0),
  rendererEditorPage(0),
  sourceProjectionRequestPage(0),
  destProjectionRequestPage(0),
  destAdapterRequestPage(0),
  lodRequestPage(0),
#if defined(HAS_SDO_SUPPORT)
  sdoLayerRequestPage(0),
#endif
  visibilityFilterPage(0),
  attributeRequestPage(0),
  status(IlFalse),
  autohide(IlTrue),
  requestForSourceProjection(IlFalse),
  sourceProjection(0),
  sourceProjectionPanel(0),
  requestForDestProjection(IlFalse),
  destinationProjection(0),
  destProjectionPanel(0),
  requestForDestAdapter(IlFalse),
  destAdapterPanel(0),
  requestForVisibilityFilter(IlTrue),
  largeScaleCombo(0),
  smallScaleCombo(0),
  requestForLOD(IlFalse),
  lodSelector(0),
  previewToggle(0),
  lodToggle(0),
  lodParams(0),
  tileWidthTF(0),
  tileHeightTF(0),
  requestForLODTileSize(IlFalse),
  aoiParams(0),
  aoiULxTF(0),
  aoiULyTF(0),
  aoiLRxTF(0),
  aoiLRyTF(0),
  requestForAOI(IlFalse),
  paletteEditor(pe),
  geometry(info),
  loadAttributeToggle(0),
  requestForAttributes(IlFalse),
  pagesCreated(IlFalse),
#if defined(HAS_SDO_SUPPORT)
  sdoDbms(0),
  sdoLayerList(0),
  sdoLayerNameCount(0),
  sdoLayerNames(0),
#endif
  okButton(0),
  cancelButton(0)
{
}

// --------------------------------------------------------------------------
ReaderController::~ReaderController()
{
    if (container) {
	delete container;
    }
    if (sourceProjection && sourceProjection->isShared()) {
	sourceProjection->unLock();
    }
    if (destinationProjection && destinationProjection->isShared()) {
	destinationProjection->unLock();    
    }
}

// --------------------------------------------------------------------------
void
ReaderController::cancelClicked()
{
    setStatus(IlFalse);
    if (isAutoHidding()) {
	container->hide();
    }
}

// --------------------------------------------------------------------------
void
ReaderController::okClicked()
{
    setStatus(IlTrue);
    // copy the source and destination projection fields
    if (requestForSourceProjection) {
	sourceProjection = sourceProjectionPanel->getProjection();
	if (sourceProjection && sourceProjection->isShared()) {
	    sourceProjection->lock();
	}
    }
    if (requestForDestProjection) {
	destinationProjection = destProjectionPanel->getProjection();
	if (destinationProjection && destinationProjection->isShared()) {
	    destinationProjection->lock();
	}
    }
    if (isAutoHidding()) {
	if (isRequestingForSourceProjection() && !getSourceProjection()) {
	    IlvIErrorDialog dial(display,
				 "Please specify a source Projection");
	    dial.moveToView(container);
	    dial.get();
	    NotebookSelectPage(notebook, sourceProjectionRequestPage);
	    return;
	}
	if (isRequestingForDestProjection() &&
	    (getDestProjection() == 0)) {
	    IlvIErrorDialog dial(display,
				 "Please specify a destination Projection");
	    dial.moveToView(container);
	    dial.get();
	    NotebookSelectPage(notebook, destProjectionRequestPage);
	    return;
	}
	container->hide();
    }
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::getParameters()
{
    // ask for additionnal parameters
    autohide = IlTrue;
    if (!pagesCreated) {
	createPages();
    }
    // if no parameters set, just return
    if (notebook->getPagesCardinal() == 0) {
	return IlTrue;
    }
    container->showModal();
  
    // report values, if any
    return status;
}

// --------------------------------------------------------------------------
void
ReaderController::show()
{
    autohide = IlFalse;
    if (!pagesCreated) {
	createPages();
    }
    container->show();
    return;
}

// --------------------------------------------------------------------------
void
ReaderController::hide()
{
    container->hide();
}

// --------------------------------------------------------------------------
void
ReaderController::createPages()
{
    if (requestForSourceProjection) {
	addSourceProjectionRequestPage();
    }
    if (requestForDestProjection) {
	addDestProjectionRequestPage();
    }
    if (requestForDestAdapter) {
	addDestAdapterRequestPage();
    }
    if (requestForLOD) {
	addLODRequestPage();
    }
#if defined(HAS_SDO_SUPPORT)
    if (sdoDbms) {
	addSDOLayerPage();
    }
#endif
    if (requestForVisibilityFilter) {
	addVisibilityFilterPage();
    }
    if (requestForAttributes) {
	addAttributeRequestPage();
    }
    pagesCreated = IlTrue;
    if (lodRequestPage) {
	NotebookSelectPage(notebook, lodRequestPage);
    }
    return;
}

// --------------------------------------------------------------------------
// Methods for reader specific features
// --------------------------------------------------------------------------
void
ReaderController::initReaderSpecific(IlvMapFeatureIterator* reader,
				     const char* fileName)
{
    if (!reader) {
	return;
    }
    IlvClassInfo* readerClass = reader->getClassInfo();
    if (readerClass->isSubtypeOf(IlvShapeSHPReader::ClassInfo()) ||
	readerClass->isSubtypeOf(IlvShapeFileReader::ClassInfo())) {
	initShapeParameters(reader, fileName);
    }
    else if (readerClass->isSubtypeOf(IlvCADRGFrameReader::ClassInfo())) {
	initCADRGParameters(reader);
    }
    else if (readerClass->isSubtypeOf(IlvDTEDReader::ClassInfo())) {
	initDTEDParameters(reader);
    }
    else if (readerClass->isSubtypeOf(IlvGeoTIFFReader::ClassInfo())) {
	initGeoTIFFParameters(reader);
    }
} // initReaderSpecific()

// --------------------------------------------------------------------------
// For shape file
void
ReaderController::initShapeParameters(IlvMapFeatureIterator* reader,
				      const char* fileName)
{
    IlvClassInfo* readerClass = reader->getClassInfo();
    IlvShapeSHPReader* shpReader = 0;
    if (readerClass->isSubtypeOf(IlvShapeSHPReader::ClassInfo())) {
	setRequestingForAttributes(IlFalse);
	shpReader = (IlvShapeSHPReader*)reader;
    }
    else {
	setRequestingForAttributes(IlTrue);
	shpReader = ((IlvShapeFileReader*)reader)->getSHPReader();
    }    
    // decide which renderer panel is to be put...
    IlvShapeType shapeType = shpReader->getShapeType();
    switch (shapeType) {
    case IlvShapeTypePoint:
    case IlvShapeTypePointZ:
    case IlvShapeTypePointM:
	addRendererEditorPage(IlvMapPoint::ClassInfo());
	break;
    case IlvShapeTypeMultipoint:
    case IlvShapeTypeMultipointZ:
    case IlvShapeTypeMultipointM:
	addRendererEditorPage(IlvMapMultiPoint::ClassInfo());
	break;
    case IlvShapeTypePolyline:
    case IlvShapeTypePolylineZ:
    case IlvShapeTypePolylineM:
	addRendererEditorPage(IlvMapCurve::ClassInfo());
	break;
    case IlvShapeTypePolygon:
    case IlvShapeTypePolygonZ:
    case IlvShapeTypePolygonM:
	addRendererEditorPage(IlvMapPolygon::ClassInfo());
	break;
    case IlvShapeTypeNull:
    case IlvShapeTypeMultipatch:
    default:
	break;
    }
    IlString fname(fileName);
    IlString* shxFName = shxFileName(fname);
    IlString* idxFName = idxFileName(fname);
    if (IlPathName::doesExist(*shxFName) &&
	IlPathName::doesExist(*idxFName)) {
	requestForLOD = IlTrue;
    }
    delete shxFName;
    delete idxFName;
}

// --------------------------------------------------------------------------
void
ReaderController::addRendererEditorPage(IlvClassInfo* geomclass)
{
    if (!rendererEditorPage) {
	rendererEditorPage = new IlvNotebookPage(notebook, "Rendering", 0,
						 IlFalse, 0);
	IlvGadgetContainer* pageView =
			  (IlvGadgetContainer*)rendererEditorPage->getView();
	IlvRect rect;
	pageView->sizeVisible(rect);
	rect.h(rect.h() - 20);
	paletteEditor = new PaletteEditor(display, rect);
	pageView->addObject(paletteEditor);
	pageView->getHolder()->attach(paletteEditor, IlvHorizontal, 0, 1, 0);
	pageView->getHolder()->attach(paletteEditor, IlvVertical, 0, 1, 0);
	notebook->addPage(rendererEditorPage);
    }
    // change sensitivity of items
    geometry = geomclass;
    if (geomclass->isSubtypeOf(IlvMapCurve::ClassInfo())) {
	paletteEditor->setLineEditingMode(IlTrue);
	paletteEditor->setFillEditingMode(IlFalse);
	paletteEditor->setPointEditingMode(IlFalse);
    }
    else if (geomclass->isSubtypeOf(IlvMapArea::ClassInfo()) &&
	     !(geomclass->isSubtypeOf(IlvMapRaster::ClassInfo()) ||
	       geomclass->isSubtypeOf(IlvMapImage::ClassInfo()))) {
	paletteEditor->setLineEditingMode(IlTrue);
	paletteEditor->setFillEditingMode(IlTrue);
	paletteEditor->setPointEditingMode(IlFalse);
    }
    else if (geomclass->isSubtypeOf(IlvMapGeometryCollection::ClassInfo())) {
	paletteEditor->setLineEditingMode(IlTrue);
	paletteEditor->setFillEditingMode(IlTrue);
	paletteEditor->setPointEditingMode(IlTrue);
    }
    else if (geomclass->isSubtypeOf(IlvMapPoint::ClassInfo())
	     || geomclass->isSubtypeOf(IlvMapMultiPoint::ClassInfo())) {
	paletteEditor->setLineEditingMode(IlFalse);
	paletteEditor->setFillEditingMode(IlFalse);
	paletteEditor->setPointEditingMode(IlTrue);
    }
}

// --------------------------------------------------------------------------
IlvFeatureRenderer*
ReaderController::getEditedCurveRenderer()
{
    if (paletteEditor && paletteEditor->isLineEditingMode()) {
	IlvDefaultCurveRenderer* renderer =
					new IlvDefaultCurveRenderer(display);
	IlvMapLineRenderingStyle* style = renderer->getLineRenderingStyle();
	if (getLinePalette()) {
	    style->setPalette(getLinePalette());
	}
	return renderer;
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvFeatureRenderer*
ReaderController::getEditedAreaRenderer()
{
    if (paletteEditor && paletteEditor->isFillEditingMode()) {
	IlvDefaultAreaRenderer* renderer =
	    new IlvDefaultAreaRenderer(display);
	IlvMapAreaRenderingStyle* areastyle =
					   renderer->getAreaRenderingStyle();
	IlvMapLineRenderingStyle* linestyle =
					  areastyle->getLineRenderingStyle();
	areastyle->setDrawingStroke(IlFalse);
	areastyle->setFillingObject(IlFalse);
	IlvPalette* linePal = getLinePalette();
	IlvPalette* fillPal = getFillPalette();
	if (linePal) {
	    areastyle->setDrawingStroke(IlTrue);
	    linestyle->setPalette(linePal);
	}
	if (fillPal) {
	    areastyle->setFillingObject(IlTrue);
	    areastyle->setPalette(fillPal);
	}
	return renderer;
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvFeatureRenderer*
ReaderController::getEditedPointRenderer()
{
    if (paletteEditor && paletteEditor->isPointEditingMode()) {
	IlvBitmap* bitmap = paletteEditor->getMarkerBitmap();
	if (bitmap) {
	    IlvIconPointRenderer* renderer =
					   new IlvIconPointRenderer(display);
	    renderer->setBitmap(bitmap);
	    return renderer;
	}
	else {
	    IlvDefaultPointRenderer* renderer =
					new IlvDefaultPointRenderer(display);
	    renderer->setMarkerType(paletteEditor->getMarkerType());
	    renderer->setForeground(paletteEditor->getMarkerColor());
	    renderer->setMarkerSize(
				   (IlUShort)paletteEditor->getMarkerSize());
	    return renderer;
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvFeatureRenderer*
ReaderController::getRenderer()
{
    if (!geometry ||
	geometry->isSubtypeOf(IlvMapGeometryCollection::ClassInfo())) {
	IlvDefaultFeatureRenderer* renderer =
				      new IlvDefaultFeatureRenderer(display);
	IlvFeatureRenderer* r = getEditedAreaRenderer();
	renderer->setAreaRenderer(r);
	delete r;
	r = getEditedPointRenderer();
	renderer->setPointRenderer(r);
	delete r;
	r = getEditedCurveRenderer();
	renderer->setCurveRenderer(r);
	delete r;
	return renderer;
    }
    if (geometry->isSubtypeOf(IlvMapCurve::ClassInfo())) {
	return getEditedCurveRenderer();
    }
    else if (geometry->isSubtypeOf(IlvMapArea::ClassInfo()) &&
	     !(geometry->isSubtypeOf(IlvMapRaster::ClassInfo()) ||
	       geometry->isSubtypeOf(IlvMapImage::ClassInfo()))) {
	return getEditedAreaRenderer();
    }
    else if (geometry->isSubtypeOf(IlvMapPoint::ClassInfo())) {
	return getEditedPointRenderer();
    }
    else if (geometry->isSubtypeOf(IlvMapMultiPoint::ClassInfo())) {
	IlvDefaultFeatureRenderer* dft =
				      new IlvDefaultFeatureRenderer(display);
	IlvFeatureRenderer* r = getEditedPointRenderer();
	dft->setPointRenderer(r);
	delete r;
	return dft;
    }
    return new IlvDefaultFeatureRenderer(display);
}

// --------------------------------------------------------------------------
IlvPalette*
ReaderController::getFillPalette() const
{
    if (paletteEditor) {
	return paletteEditor->getFillPalette();
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvPalette*
ReaderController::getLinePalette() const
{
    if (paletteEditor) {
	return paletteEditor->getLinePalette();
    }
    return 0;
}

// --------------------------------------------------------------------------
// For GeoTIFF files
void
ReaderController::initGeoTIFFParameters(IlvMapFeatureIterator* reader)
{
    if (((IlvGeoTIFFReader*)reader)->isTiled()) {
	setRequestingForLOD(IlTrue);
    }
    setRequestingForDestProjection(IlFalse);
}

// --------------------------------------------------------------------------
// For cadrg files
void
ReaderController::initCADRGParameters(IlvMapFeatureIterator* reader)
{
    setRequestingForLOD(IlTrue);
}

// --------------------------------------------------------------------------
// For dted files
void
ReaderController::initDTEDParameters(IlvMapFeatureIterator* reader)
{
    setRequestingForLOD(IlTrue);
}

// --------------------------------------------------------------------------
// Methods to handle source projection
void
ReaderController::setRequestingForSourceProjection(IlBoolean set)
{
    requestForSourceProjection = set;
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::isRequestingForSourceProjection() const
{
    return requestForSourceProjection;
}

// --------------------------------------------------------------------------
void
ReaderController::addSourceProjectionRequestPage()
{
    if (!sourceProjectionRequestPage) {
	sourceProjectionRequestPage = new IlvNotebookPage(notebook,
							 "Source projection",
							  0,
							  IlFalse,
							  0);
	IlvGadgetContainer* pageView =
		 (IlvGadgetContainer*)sourceProjectionRequestPage->getView();
	IlvRect rect;
	pageView->sizeVisible(rect);
	rect.h(rect.h() - 20);
	sourceProjectionPanel = new ProjectionSelector(display,
						       rect,
						       sourceProjection);
	pageView->addObject(sourceProjectionPanel);
	pageView->getHolder()->attach(sourceProjectionPanel, IlvHorizontal,
				      0, 1, 0);
	pageView->getHolder()->attach(sourceProjectionPanel, IlvVertical,
				      0, 1, 0);
	notebook->addPage(sourceProjectionRequestPage);
    }
}

// --------------------------------------------------------------------------
// Methods to handle destination projection
void
ReaderController::setRequestingForDestProjection(IlBoolean set)
{
    requestForDestProjection = set;
    if (requestForDestProjection && pagesCreated &&
	!destProjectionRequestPage) {
	addDestProjectionRequestPage();
    }
    else if (!requestForDestProjection && pagesCreated &&
	     destProjectionRequestPage) {
	NotebookRemovePage(notebook, destProjectionRequestPage);
	destProjectionRequestPage = 0;
    }
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::isRequestingForDestProjection() const
{
    return requestForDestProjection;
}

// --------------------------------------------------------------------------
IlvProjection*
ReaderController::getDestProjection() const
{
    return destinationProjection;
}

// --------------------------------------------------------------------------
void
ReaderController::addDestProjectionRequestPage()
{
    if (!destProjectionRequestPage) {
	destProjectionRequestPage = new IlvNotebookPage(notebook,
						    "Destination projection",
							0,
							IlFalse,
							0);
	IlvGadgetContainer* pageView =
		   (IlvGadgetContainer*)destProjectionRequestPage->getView();
	IlvRect rect;
	pageView->sizeVisible(rect);
	rect.h(rect.h() - 20);
	destProjectionPanel = new ProjectionSelector(display,
						     rect,
						     destinationProjection);
	pageView->addObject(destProjectionPanel);
	pageView->getHolder()->attach(destProjectionPanel, IlvHorizontal,
				      0, 1, 0);
	pageView->getHolder()->attach(destProjectionPanel, IlvVertical,
				      0, 1, 0);
	notebook->addPage(destProjectionRequestPage);
    }
}

// --------------------------------------------------------------------------
// Methods to handle destination adapter
void
ReaderController::setRequestingForDestAdapter(IlBoolean set)
{
    requestForDestAdapter = set;
    if (requestForDestAdapter && pagesCreated && !destAdapterRequestPage) {
	addDestAdapterRequestPage();
    }
    else if (!requestForDestAdapter && pagesCreated &&
	     destAdapterRequestPage) {
	NotebookRemovePage(notebook,destAdapterRequestPage);
	destAdapterRequestPage = 0;
    }
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::isRequestingForDestAdapter() const
{
    return requestForDestAdapter;
}

// --------------------------------------------------------------------------
IlvMapAdapter*
ReaderController::getDestAdapter(const IlvProjection* p) const
{
    return destAdapterPanel->getAdapter(p);
}

// --------------------------------------------------------------------------
void
ReaderController::addDestAdapterRequestPage()
{
    if (!destAdapterRequestPage) {
	destAdapterRequestPage = new IlvNotebookPage(notebook,
						     "Destination adapter",
						     0,
						     IlFalse,
						     0);
	IlvGadgetContainer* pageView =
	    (IlvGadgetContainer*)destAdapterRequestPage->getView();
	IlvRect rect;
	pageView->sizeVisible(rect);
	rect.h(rect.h() - 20);
	destAdapterPanel = new AdapterSelector(display, rect);
	pageView->addObject(destAdapterPanel);
	pageView->getHolder()->attach(destAdapterPanel,IlvHorizontal,0,1,0);
	pageView->getHolder()->attach(destAdapterPanel,IlvVertical,0,1,0);
	notebook->addPage(destAdapterRequestPage);
    }
}

// --------------------------------------------------------------------------
// Methods to handle LOD request
void
ReaderController::setRequestingForLOD(IlBoolean set)
{
    requestForLOD = set;
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::isRequestingForLOD() const
{
    return requestForLOD;
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::isLOD() const
{
    if (lodSelector &&
	(lodSelector->whichSelected() == 1)) {
	return IlTrue;
    }
    else {
	return IlFalse;
    }
}

// --------------------------------------------------------------------------
void
ReaderController::addLODRequestPage()
{
    if (lodRequestPage == 0) {
	lodRequestPage = new IlvNotebookPage(notebook,
					     "Load On Demand",
					     0,
					     IlFalse,
					     0);
	IlvGadgetContainer* pageView =
	    (IlvGadgetContainer*)lodRequestPage->getView();
	IlvRect rect;
	pageView->sizeVisible(rect);
	rect.h(rect.h() - 20);

	lodSelector = new IlvSelector();

	previewToggle = new IlvToggle(display, IlvPoint(20, 20), "Preview");
	previewToggle->setRadio(IlTrue);
	lodSelector->addObject(previewToggle);
	lodSelector->setSelected(previewToggle);

	IlvPoint lodTogglePoint(20,
				previewToggle->y() +
				previewToggle->h() + 10);
	// case of request for AOI
	if (requestForAOI) {
	    // The frame to individualize the Area of interest part.
	    IlvRect aoiFrameRect(20,
				 previewToggle->h()+previewToggle->y()+10,
				 rect.w()-40,
				 80);
	    aoiParams =	new IlvGadgetContainerRectangle(display,
							aoiFrameRect);
	    pageView->addObject(aoiParams);
	    pageView->getHolder()->attach(aoiParams, IlvHorizontal, 0, 1, 0);
	    pageView->getHolder()->attach(aoiParams, IlvVertical, 0, 0, 1);
	    lodTogglePoint.y(aoiFrameRect.y() + aoiFrameRect.h() + 10);
	    
	    aoiFrameRect.move(0,0);
	    IlvGadgetContainer* c = aoiParams->getGadgetContainer();
	    IlvFrame* frame = new IlvFrame(display, "Area Of Interest",
					   aoiFrameRect);
	    c->addObject(frame);
	    c->getHolder()->attach(frame,IlvHorizontal,0,1,0);
	    c->getHolder()->attach(frame,IlvVertical,0,1,0);

	    // Create the labels now
	    IlvLabel* aoiULxLabel = new IlvLabel(display, IlvPoint(0, 0),
						 "Upper left X = ");
	    IlvLabel* aoiLRxLabel = new IlvLabel(display, IlvPoint(0, 0),
						 "Lower right X = ");
	    IlvLabel* aoiULyLabel = new IlvLabel(display, IlvPoint(0, 0),
						 "Y = ");
	    IlvLabel* aoiLRyLabel = new IlvLabel(display, IlvPoint(0, 0),
						 "Y = ");
	    int comboWidth = 80;
	    int xcomboPosX = 20 + IlvMax(aoiULxLabel->w(), aoiLRxLabel->w());
	    int ycomboPosX = xcomboPosX + comboWidth + 20 + aoiULyLabel->w();
	    // Text fields
	    aoiULxTF = new IlvNumberField(display, IlvPoint(xcomboPosX, 20),
					  (IlDouble)0.0);
	    aoiULxTF->w(comboWidth);
	    c->addObject(aoiULxTF);
	    aoiULyTF = new IlvNumberField(display, IlvPoint(ycomboPosX, 20),
					  (IlDouble)0.0);
	    aoiULyTF->w(comboWidth);
	    c->addObject(aoiULyTF);
	    aoiLRxTF = new IlvNumberField(display,
					  IlvPoint(xcomboPosX,
						   aoiULxTF->y()
						   + aoiULxTF->h() + 10),
					  (IlDouble)0.0);
	    aoiLRxTF->w(comboWidth);
	    c->addObject(aoiLRxTF);
	    aoiLRyTF = new IlvNumberField(display,
					  IlvPoint(ycomboPosX,
						   aoiULxTF->y()
						   + aoiULxTF->h() + 10),
					  (IlDouble)0.0);
	    aoiLRyTF->w(comboWidth);
	    c->addObject(aoiLRyTF);
	    // Change the position of labels
	    IlvLabel* label = aoiULxLabel;
	    int ypos = (((int)aoiULxTF->h()) - ((int)label->h())) / 2;
	    label->move(10, aoiULxTF->y() + ypos);
	    c->addObject(label);

	    label = aoiULyLabel;
	    ypos = (((int)aoiULyTF->h()) - ((int)label->h())) / 2;
	    label->move(xcomboPosX + comboWidth + 10, 
			aoiULyTF->y() + ypos);
	    c->addObject(label);

	    label = aoiLRxLabel;
	    ypos = (((int)aoiLRxTF->h()) - ((int)label->h())) / 2;
	    label->move(10,
			aoiLRxTF->y() + ypos);
	    c->addObject(label);

	    label = aoiLRyLabel;
	    ypos = (((int)aoiLRyTF->h()) - ((int)label->h())) / 2;
	    label->move(xcomboPosX + comboWidth + 10, 
			aoiLRyTF->y() + ypos);
	    c->addObject(label);
	    
	    SelectSensitivity(c,IlTrue);
	}

	// Load on demand toggle
	lodToggle = new IlvToggle(display, lodTogglePoint, "Load on demand");
	lodToggle->setRadio(IlTrue);
	lodSelector->addObject(lodToggle);
	lodSelector->setInteractor(IlvInteractor::Get("Selector"));

	lodSelector->setCallback(LODToggleCB);
	lodSelector->setClientData((IlvAny)this);
	
	pageView->addObject(lodSelector);
	
	notebook->addPage(lodRequestPage);

	if (requestForLODTileSize) {
	    IlvRect lodParamFrameRect(20,
				      lodToggle->h() + lodToggle->y() + 10,
				      rect.w() - 40,
				      80);
	    lodParams = new IlvGadgetContainerRectangle(display,
							lodParamFrameRect);
	    pageView->addObject(lodParams);
	    pageView->getHolder()->attach(lodParams, IlvHorizontal, 0, 1, 0);
	    pageView->getHolder()->attach(lodParams, IlvVertical, 0, 0, 1);
	
	    lodParamFrameRect.move(0,0);
	    IlvGadgetContainer* c = lodParams->getGadgetContainer();
	    IlvFrame* frame = new IlvFrame(display, "Load on demand",
					   lodParamFrameRect);
	    c->addObject(frame);
	    c->getHolder()->attach(frame, IlvHorizontal, 0, 1, 0);
	    c->getHolder()->attach(frame, IlvVertical, 0, 1, 0);
	    // the text fields
	    tileWidthTF = new IlvNumberField(display, IlvPoint(100, 20),
					     (IlDouble)100.0);
	    tileWidthTF->w(80);
	    c->addObject(tileWidthTF);
	    tileHeightTF = new IlvNumberField(display,
					      IlvPoint(100,
						       tileWidthTF->y()
						       + tileWidthTF->h()
						       + 10),
					      (IlDouble)100.0);
	    tileHeightTF->w(80);
	    c->addObject(tileHeightTF);
	    // the associated labels
	    // for width
	    IlvLabel* label = new IlvLabel(display,
					   IlvPoint(0,0),
					   "Tile Width");
	    int ypos = (((int)tileWidthTF->h()) - ((int)label->h())) / 2;
	    label->move(10,
			tileWidthTF->y() + ypos);
	    c->addObject(label);
	    label = new IlvLabel(display,
				 IlvPoint(0,0),
				 "km");
	    label->move(tileWidthTF->x() + tileWidthTF->w() + 10,
			tileWidthTF->y() + ypos);
	    c->addObject(label);

	    // for height
	    label = new IlvLabel(display,
				 IlvPoint(0,0),
				 "Tile Height");
	    ypos = (((int)tileHeightTF->h()) - ((int)label->h())) / 2;
	    label->move(10,
			tileHeightTF->y() + ypos);
	    c->addObject(label);
	    label = new IlvLabel(display,
				 IlvPoint(0,0),
				 "km");
	    label->move(tileHeightTF->x() + tileHeightTF->w() + 10,
			tileHeightTF->y() + ypos);
	    c->addObject(label);
	    SelectSensitivity(c,IlFalse);
	}
    }
}

// --------------------------------------------------------------------------
void
ReaderController::setRequestingForLODTileSize(IlBoolean set)
{
    requestForLODTileSize = set;
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::isRequestingForLODTileSize() const
{
    return requestForLODTileSize;
}

// --------------------------------------------------------------------------
void
ReaderController::getLODTileSize(IlvCoordinate& result,
				 const IlvUnitConverter* destUnit)
{
    IlBoolean error;
    IlDouble width = tileWidthTF->getFloatValue(error);
    IlDouble height = tileHeightTF->getFloatValue(error);

    if (destUnit) {
	width = destUnit->fromMeters(width * 1000.0);
	height = destUnit->fromMeters(height * 1000.0);	
    }
    result.x(width);
    result.y(height);
}

// --------------------------------------------------------------------------
void
ReaderController::setRequestingForAOI(IlBoolean set)
{
    requestForAOI = set;
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::isRequestingForAOI() const
{
    return requestForAOI;
}

// --------------------------------------------------------------------------
void
ReaderController::getAOI(IlvCoordinate& UL, IlvCoordinate& LR)
{
    IlBoolean error;

    UL.x(aoiULxTF->getFloatValue(error));
    UL.y(aoiULyTF->getFloatValue(error));
    LR.x(aoiLRxTF->getFloatValue(error));
    LR.y(aoiLRyTF->getFloatValue(error));
    
    return;
}

#if defined(HAS_SDO_SUPPORT)
// --------------------------------------------------------------------------
// Methods to handle SDO Layer request
void
ReaderController::setRequestingForSDOLayer(IldDbms* dbms)
{
    sdoDbms = dbms;
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::isRequestingForSDOLayer() const
{
    return (sdoDbms != 0);
}

// --------------------------------------------------------------------------
void
ReaderController::addSDOLayerPage()
{
    if (!sdoLayerRequestPage) {
	sdoLayerRequestPage = new IlvNotebookPage(notebook,
						  "SDO Layer",
						  0,
						  IlFalse,
						  0);
	IlvGadgetContainer* pageView =
			 (IlvGadgetContainer*)sdoLayerRequestPage->getView();
	IlvRect rect;
	pageView->sizeVisible(rect);
	rect.h(rect.h() - 20);
	sdoLayerList = new IlvStringList(display, IlvRect(10, 10, 300, 300));
	sdoLayerList->setSelectionMode(IlvStringListSingleSelection);
	sdoLayerList->setExclusive(IlTrue);
	sdoLayerList->scrollBarShowAsNeeded(IlTrue, IlTrue);
	pageView->addObject(sdoLayerList);
	notebook->addPage(sdoLayerRequestPage);
    }
    // Get all layer names
    IlvMapsError error;
    sdoLayerNames = IlvObjectSDOUtil::GetAllLayers(sdoLayerNameCount,
						   sdoDbms,
						   sdoDbms->getUser(),
						   IlTrue,
						   error);
    sdoLayerList->setLabels((const char* const*)sdoLayerNames,
			    (IlvAny const*)0,
			    sdoLayerNameCount);
}

// --------------------------------------------------------------------------
char*
ReaderController::getSDOLayerTableName()
{
    int which = sdoLayerList->getSelectionIndex();
    if ((which < 0) || (which >= sdoLayerNameCount)) {
	return 0;
    }
    char* buf = new char[strlen(sdoLayerNames[which]) + 1];
    sprintf(buf, sdoLayerNames[which]);
    char* ptr = strchr(buf,'.');
    if (ptr) {
	*ptr = 0;
	return buf;
    }
    else {
	if (buf) {
	    delete buf;
	}
	return 0;
    }
}

// --------------------------------------------------------------------------
char*
ReaderController::getSDOLayerGeometryName()
{
    int which = sdoLayerList->getSelectionIndex();
    if ((which < 0) || (which >= sdoLayerNameCount)) {
	return 0;
    }
    char* buf = new char[strlen(sdoLayerNames[which]) + 1];
    sprintf(buf, sdoLayerNames[which]);
    char* ptr = strchr(buf, '.');
    if (ptr) {
	char* retbuf = new char[strlen(ptr+1)+1];
	sprintf(retbuf, "%s", ptr+1);
	if (buf) {
	    delete buf;
	}
	buf = 0;
	return retbuf;
    }
    else {
	if (buf) {
	    delete buf;
	}
	return 0;
    }
}
#endif /* HAS_SDO_SUPPORT */

// --------------------------------------------------------------------------
// For visibility filter
void
ReaderController::setRequestingForVisibilityFilter(IlBoolean set)
{
    requestForVisibilityFilter = set;
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::isRequestingForVisibilityFilter() const
{
    return requestForVisibilityFilter;
}

// --------------------------------------------------------------------------
void
ReaderController::addVisibilityFilterPage()
{
    if (visibilityFilterPage == 0) {
	visibilityFilterPage =
	    new IlvNotebookPage(notebook,
				"Scale control",
				0,
				IlFalse,
				0);
	IlvGadgetContainer* pageView =
	    (IlvGadgetContainer*)visibilityFilterPage->getView();
	IlvRect rect;
	pageView->sizeVisible(rect);
	rect.h(rect.h() - 20);

	// Create the labels (so that positioning is good)
	IlvLabel* largeScaleLabel = new IlvLabel(display,
						 IlvPoint(0,0),
						 "Large scale limit 1 / ");
	IlvLabel* smallScaleLabel = new IlvLabel(display,
						 IlvPoint(0,0),
						 "Small scale limit 1 / ");
	int combopos = IlvMax(largeScaleLabel->w(),
			      smallScaleLabel->h())
	    + 10;
	// The large scale combo
	largeScaleCombo = new ScaleCombo(display,
					 IlvPoint(combopos,20));
	largeScaleCombo->h(24);
	largeScaleCombo->w(100);
	pageView->addObject(largeScaleCombo);
	// the corresponding label
	IlvLabel* label = largeScaleLabel;
	int ypos = (((int)largeScaleCombo->h()) - ((int)label->h())) / 2;
	int xpos = ((int)largeScaleCombo->x()) - ((int)label->w() + 5);
	label->move(xpos,
		    largeScaleCombo->y() + ypos);
	pageView->addObject(label);

	// the small scale combo
	smallScaleCombo = new ScaleCombo(display,
					 IlvPoint(combopos,50));
	smallScaleCombo->h(24);
	smallScaleCombo->w(100);
	pageView->addObject(smallScaleCombo);
	// the corresponding label
	label = smallScaleLabel;
	ypos = (((int)smallScaleCombo->h()) - ((int)label->h())) / 2;
	xpos = ((int)smallScaleCombo->x()) - ((int)label->w() + 5);
	label->move(xpos,
		    smallScaleCombo->y() + ypos);
	pageView->addObject(label);

	// The small scale combo
	notebook->addPage(visibilityFilterPage);
    }
}

// --------------------------------------------------------------------------
IlvScaleVisibilityFilter*
ReaderController::getVisibilityFilter()
{
    if ((requestForVisibilityFilter == 0) ||
	(largeScaleCombo == 0)) {
	return 0;
    }
    
    IlDouble largeScale = IlvScaleVisibilityFilter::NoLimit();
    IlDouble smallScale = IlvScaleVisibilityFilter::NoLimit();

    IlDouble largeS = largeScaleCombo->getScale();
    if (largeS > 0.0) {
	largeScale = 1. / largeS;
    }
    IlDouble smallS = smallScaleCombo->getScale();
    if (smallS > 0.0) {
	smallScale = 1. / smallS;
    }

    if ((smallS <= 0.0) && (largeS <= 0.0)) {
	return 0;
    }
    return new IlvScaleVisibilityFilter(smallScale,
					largeScale);
}

// --------------------------------------------------------------------------
// Methods to handle Attribute request
void
ReaderController::setRequestingForAttributes(IlBoolean set)
{
    requestForAttributes = set;
    if (requestForAttributes &&
	pagesCreated             &&
	(attributeRequestPage == 0)) {
	addAttributeRequestPage();
    }
    else if (!requestForAttributes && pagesCreated &&
	     (attributeRequestPage != 0)) {
	NotebookRemovePage(notebook,attributeRequestPage);
	attributeRequestPage = 0;
    }
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::isRequestingForAttributes() const
{
    return requestForAttributes;
}

// --------------------------------------------------------------------------
IlBoolean
ReaderController::isAttachingAttributes() const
{
    if (loadAttributeToggle &&
	loadAttributeToggle->getState()) {
	return IlTrue;
    }
    else {
	return IlFalse;
    }
}

// --------------------------------------------------------------------------
void
ReaderController::addAttributeRequestPage()
{
    if (attributeRequestPage == 0) {
	attributeRequestPage = new IlvNotebookPage(notebook,
						   "Attributes",
						   0,
						   IlFalse,
						   0);
	IlvGadgetContainer* pageView =
			(IlvGadgetContainer*)attributeRequestPage->getView();
	IlvRect rect;
	pageView->sizeVisible(rect);
	rect.h(rect.h() - 20);

	loadAttributeToggle = new IlvToggle(display,
					    IlvPoint(20,20),
					    "Load attributes");
	pageView->addObject(loadAttributeToggle);
	notebook->addPage(attributeRequestPage);
    }
}
