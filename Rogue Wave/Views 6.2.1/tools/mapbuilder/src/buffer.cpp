// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/src/buffer.cpp
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
// The implementation of MapBuffer methods.
// --------------------------------------------------------------------------
#include "buffer.h"
#include "readctrl.h"
#include "builder.h"

#include <ilviews/gadgets/toggle.h>
#include <ilviews/manager/rectangl.h>
#include <ilviews/manager/magview.h>
#include <ilog/pathname.h>
#include <ilviews/graphics/all.h>
#include <ilviews/maps/geometry/all.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/format/maploader.h>
#include <ilviews/maps/mapinfo.h>
#include <ilviews/maps/projection/allprojs.h>
#include <ilviews/maps/projection/hshiftdatum.h>
#include <ilviews/maps/renderer.h>
#include <ilviews/maps/format/dted/dtedreader.h>
#include <ilviews/maps/format/dted/dtedlayer.h>
#include <ilviews/maps/format/geotiff/gtifflayer.h>
#include <ilviews/maps/format/geotiff/gtiffreader.h>
#include <ilviews/maps/format/geotiff/gtifftloader.h>
#include <ilviews/maps/format/shapefile/shplayer.h>
#include <ilviews/maps/format/shapefile/shpreader.h>
#include <ilviews/maps/format/shapefile/shpfile.h>
#include <ilviews/maps/format/shapefile/shptloader.h>
#include <ilviews/maps/format/cadrg/cadrgread.h>
#include <ilviews/maps/format/cadrg/cadrglayer.h>
#include <ilviews/maps/format/cadrg/cadrgtoc.h>
#include <ilviews/maps/format/s57/s57loader.h>
#include <ilviews/base/sstream.h>

#if defined(IL_STD)
#  include <cstring>
#  include <fstream>
#  include <cctype>
IL_STDUSE
#else  /* !IL_STD */
#  if !defined(WINDOWS)
#    include <strings.h>
#  endif
#  include <fstream.h>
#  include <stdlib.h>
#  include <ctype.h>
#  include <stdio.h>
#endif /* !IL_STD */

IL_NO_UNSECURE_CRT_WARNINGS

// --------------------------------------------------------------------------
static IlString*
idxFileName(IlString& shpFileName)
{
    if (shpFileName.endsWith(".shp")) {
	return new IlString(shpFileName.getSubString(0,
					  (int)shpFileName.getLength() - 4) +
			    IlString(".idx"));
    }
    else {
	return new IlString(shpFileName.getSubString(0,
					  (int)shpFileName.getLength() - 4) +
			    IlString(".IDX"));
    }
}

// --------------------------------------------------------------------------
static IlString*
shxFileName(IlString& shpFileName)
{
    if (shpFileName.endsWith(".shp")) {
	return new IlString(shpFileName.getSubString(0,
					  (int)shpFileName.getLength() - 4) +
			    IlString(".shx"));
    }
    else {
	return new IlString(shpFileName.getSubString(0,
					  (int)shpFileName.getLength() - 4) +
			    IlString(".SHX"));
    }
}

// --------------------------------------------------------------------------
static IlString*
dbfFileName(IlString& shpFileName)
{
    if (shpFileName.endsWith(".shp")) {
	return new IlString(shpFileName.getSubString(0,
					  (int)shpFileName.getLength() - 4) +
			    IlString(".dbf"));
    }
    else {
	return new IlString(shpFileName.getSubString(0,
					  (int)shpFileName.getLength() - 4) +
			    IlString(".DBF"));
    }
}

#if 0
// --------------------------------------------------------------------------
inline static IlString
ToEvendenString(const IlvProjection* object)
{
    if (object) {
	ostrstream  stream;
	object->printPROJ4Descriptor(stream);
	stream << ends;
	char* s = stream.str();
	IlvString   result(s);
	stream.rdbuf()->freeze(0);
	return result;
    }
    IlvString nullString("NULL");
    return nullString;
};
#endif
			
// --------------------------------------------------------------------------
// Creates a Geotiff layer
// --------------------------------------------------------------------------
static IlvTiledLayer*
CreateGeoTIFFLayer(const char* fileName, const IlvMapAdapter* adapter)
{
    IlvGeoTIFFTileLoader* loader = new IlvGeoTIFFTileLoader(fileName,
							    adapter);
    IlvGeoTIFFLayer* layer = new IlvGeoTIFFLayer(loader);
    return layer;
}
						
// --------------------------------------------------------------------------
// Creates a Shapefile layer
// --------------------------------------------------------------------------
static IlvTiledLayer*
CreateShapefileLayer(const char* fileName, const IlvMapAdapter* adapter)
{
    IlString fname(fileName);
    IlString* dbfFName = dbfFileName(fname);
    IlString* shxFName = shxFileName(fname);
    IlString* idxFName = idxFileName(fname);
    IlvShapeFileTileLoader* tileLoader =
	new IlvShapeFileTileLoader(fileName,
				   dbfFName->getValue(),
				   shxFName->getValue(),
				   idxFName->getValue(),
				   adapter);
    delete dbfFName;
    delete shxFName;
    delete idxFName;
    IlvShapeFileLayer* layer = new IlvShapeFileLayer(tileLoader);
    return layer;
}

// --------------------------------------------------------------------------
// Creates a DTED layer
// --------------------------------------------------------------------------
static IlvTiledLayer*
CreateDTEDLayer(const char* filename, const IlvMapAdapter* adapter)
{
    IlPathName p(filename);
    IlPathName dteddirname(p.getDirName());
    dteddirname += IlPathName("..");
    return new IlvDTEDLayer(dteddirname, 0, adapter);
}

// --------------------------------------------------------------------------
// Creates a CADRG layer
// --------------------------------------------------------------------------
static IlvTiledLayer*
CreateCADRGLayer(const char* filename, const IlvMapAdapter* adapter)
{
    IlPathName path(filename);
    IlString s(path.getDirName().toLower());
    int res = s.getIndexOf(IlPathName("/rpf/"));
    if (res < 0) {
	return 0;
    }
    res += 5;
    IlPathName toc(path.getString().getSubString(0, res));
    IlPathName copy(toc);
    toc += IlPathName("a.toc");
    const char* atoc = 0;
    if (toc.doesExist()) {
	atoc = (const char*)toc;
    }
    else {
	copy += IlPathName("A.TOC");
	if (copy.doesExist()) {
	    atoc = (const char*)copy;
	}
    }
    if (!atoc) {
	return 0;
    }
    IlvCADRGTocReader tocReader(atoc);
    if (tocReader.getInitStatus() != IlvMaps::NoError()) {
	return 0;
    }
    IlPathName cov(path.getDirName());
    IlString covstr = path.getDirName().getSubString(res - 1);
    covstr.prepend(IlString("."));
    const char* value = covstr.getValue();
    IlUShort coverageCount = 0;
    const IlvCADRGCoverage* const* coverages =
				       tocReader.getCoverages(coverageCount);
    for (int i = 0; i < coverageCount ; i++) {
	const IlvCADRGFrame* ff = 0;
	for (int r = 0; (ff == 0) && (r < coverages[i]->getRows()); r++) {
	    for (int c = 0;
		 (ff == 0) && (c < coverages[i]->getColumns()); c++) {
		if (coverages[i]->getFrame(r,c) != 0) {
		    ff = coverages[i]->getFrame(r,c);
		}
	    }
	}
	if (ff
	    && (IL_STRCASECMP((const char*)IlPathName(ff->getPathName()),
			      (const char *)IlPathName(value)) == 0)) {
	    IlvCADRGLayer* layer = new IlvCADRGLayer(*(coverages[i]),
						     adapter);
	    return layer;
	}
    }
    // Cannot find coverage
    return 0;
}

// --------------------------------------------------------------------------
static void
RemoveAttribute(IlvManagerLayer* layer, const char* name)
{
    IlvNamedProperty* p = layer->removeNamedProperty(IlvGetSymbol(name));
    if (p) {
	delete p;
    }
}

// --------------------------------------------------------------------------
static void
RemoveAttributes(IlvManagerLayer* layer)
{
    if (layer) {
	RemoveAttribute(layer, "_AREA_COLOR_");
	RemoveAttribute(layer, "_AREA_BITMAP_");
	RemoveAttribute(layer, "_LINE_COLOR_");
	RemoveAttribute(layer, "_LINE_WIDTH_");
	RemoveAttribute(layer, "_LINE_STYLE_");
	RemoveAttribute(layer, "_MARKER_TYPE_");
	RemoveAttribute(layer, "_MARKER_COLOR");
	RemoveAttribute(layer, "_MARKER_BITMAP_");
	RemoveAttribute(layer, "_MULTIRES_");
    }
}

static IlvRect* NextFrameSize = 0;
static IlUInt CurrentUntitledIndex = 0;

// --------------------------------------------------------------------------
MapBuffer::MapBuffer(MapBuilder* builder,
		     MapDesktopManager* desktop,
		     const char* frameTitle)
: frame(0),
  view(0),
  desktopManager(desktop),
  title(0),
  filename(0),
  manager(0),
  mapbuilder(builder),
  rasterFactory(0),
  shapeFactory(0)
{
    // Create title and filename
    if (frameTitle == 0) {
	char b[256];
	CurrentUntitledIndex++;
	sprintf(b, "Untitled %d", (int)CurrentUntitledIndex);
	title = IlCopyString(b, IlFalse);
    }
    else {
	title = IlCopyString(frameTitle, IlFalse);
    }
    // Get desktop
    IlvView* desktopView = desktopManager->getView();
    // Create the frame, eventually maximized if the current frame is already
    // maximized.
    if (!NextFrameSize) {
	NextFrameSize = new IlvRect(0, 0, 300, 300);
    }
    NextFrameSize->translate(IlvPoint(16, 16));
    frame = new IlvViewFrame(desktopView, title, *NextFrameSize, IlFalse);
    frame->setBackground(desktopView->getDisplay()->getColor("white"));
    if (desktopManager->isMaximizing()) {
	frame->maximizeFrame();
    }
    // create a gadget container
    IlvRect r;
    frame->getClientBBox(r);
    r.move(0, 0);
    IlvGadgetContainer* container = new IlvGadgetContainer(frame, r);
    // create a scrolled manager rectangle
    IlvManagerRectangle* rectangle =
	 new IlvManagerRectangle(desktopManager->getView()->getDisplay(), r);
    container->addObject(rectangle);
    container->getHolder()->attach(rectangle, IlvHorizontal, 0, 1, 0);
    container->getHolder()->attach(rectangle, IlvVertical, 0, 1, 0);
    rectangle->getView()->setBackground(desktopView->getDisplay()
					           ->getColor("white"));
    frame->registerClientView(rectangle->getView());
    manager = rectangle->getManager();
    manager->setKeepingAspectRatio(rectangle->getView(),IlTrue);
    manager->setBackground(rectangle->getView(),
			   desktopView->getDisplay()->getColor("white"));
    manager->setDoubleBuffering(rectangle->getView(), IlTrue);
    view = rectangle->getView();
}

// --------------------------------------------------------------------------
MapBuffer::~MapBuffer()
{
    if (frame) {
	frame->unRegisterClientView(view);
    }
    if (title) {
	delete [] title; 
    }
    if (filename) {
	delete [] filename;
    }
    if (rasterFactory) {
	delete rasterFactory;
    }
    if (shapeFactory) {
	delete shapeFactory;
    }
}

// --------------------------------------------------------------------------
void
MapBuffer::destroyFrame()
{
    if (frame) {
	IlUInt count;
	IlvView** views = getManager()->getViews(count);
	for (IlUInt i = 0; i < count; i++) {
	    IlvManagerViewInteractor* inter =
				       getManager()->getInteractor(views[i]);
	    if (inter) {
		inter->abort();
		getManager()->removeInteractor(views[i]);
		delete inter;
	    }
	}
	frame->hide();
	IlvUInt layersCount = manager->getNumLayers();
	for (IlvUInt j = 0; j < layersCount; j++) {
	    RemoveAttributes(manager->getManagerLayer(j));
	}
	delete frame;
	frame = 0;
    }
}

// --------------------------------------------------------------------------
IlvMapsError
MapBuffer::loadFile(const char* name)
{
    manager->read(name);
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
void
MapBuffer::UpdateLayerAttributes(IlvManagerLayer* layer,
				 PaletteEditor* palEditor,
				 IlBoolean removeProperties)
{
    
    IlvToggle* save = 0;
    if (palEditor) {
	save = (IlvToggle*)
	palEditor->getContainer()->getObject("saverendering");
    }
    if (removeProperties || !save || !save->getState()) {
	RemoveAttributes(layer);
	return;
    }
    RemoveAttributes(layer);
    IlvPalette* fp = palEditor->getFillColorCombo()->getCurrentPalette();
    if (fp) {
	if (!palEditor->getFillColorCombo()->hasTexture()) {
	    IlvColor* c = fp->getForeground();
	    IlString color = IlString("r") + IlString(c->getRed())
			   + IlString("g") + IlString(c->getGreen())
			   + IlString("b") + IlString(c->getBlue());
	    layer->setNamedProperty(
			  new IlvStringProperty(IlvGetSymbol("_AREA_COLOR_"),
						color.getValue()));
	    layer->removeNamedProperty(IlvGetSymbol("_AREA_BITMAP_"));
	}
	else {
	    IlvFileBrowser* fb =
			 palEditor->getFillColorCombo()->getTextureBrowser();
	    const char* pathName = fb->getPathName();
	    if (pathName && pathName[0]) {
		layer->setNamedProperty(
			 new IlvStringProperty(IlvGetSymbol("_AREA_BITMAP_"),
					       pathName));
		layer->removeNamedProperty(IlvGetSymbol("_AREA_COLOR_"));
	    }
	    layer->removeNamedProperty(IlvGetSymbol("_AREA_COLOR_"));
	}
    }
    IlvPalette* lp = palEditor->getLineColorCombo()->getCurrentPalette();
    if (lp) {
	IlvColor* c = lp->getForeground();
	IlString color = IlString("r") + IlString(c->getRed())
		       + IlString("g") + IlString(c->getGreen())
		       + IlString("b") + IlString(c->getBlue());
	layer->setNamedProperty(
			  new IlvStringProperty(IlvGetSymbol("_LINE_COLOR_"),
						color.getValue()));
    }
    lp = palEditor->getLineThicknessCombo()->getCurrentPalette();
    if (lp) {
	layer->setNamedProperty(
	     new IlvStringProperty(IlvGetSymbol("_LINE_WIDTH_"),
				   IlString(lp->getLineWidth()).getValue()));
    }
    lp = palEditor->getLineDashCombo()->getCurrentPalette();
    if (lp) {
	layer->setNamedProperty(
		       new IlvStringProperty(IlvGetSymbol("_LINE_STYLE_"),
					     lp->getLineStyle()->getName()));
    }
    if (!palEditor->getMarkerBitmap()) {
	if (palEditor->getMarkerType() != 0) {
	    layer->setNamedProperty(
		new IlvStringProperty(IlvGetSymbol("_MARKER_TYPE_"),
		           IlString(palEditor->getMarkerType()).getValue()));
	    IlvColor* c = palEditor->getMarkerColor();
	    IlString color = IlString("r") + IlString(c->getRed())
			   + IlString("g") + IlString(c->getGreen())
			   + IlString("b") + IlString(c->getBlue());
	    layer->setNamedProperty(
			new IlvStringProperty(IlvGetSymbol("_MARKER_COLOR_"),
					      color.getValue()));
	    layer->removeNamedProperty(IlvGetSymbol("_MARKER_BITMAP_"));
	}
    }
    else {
	IlvFileBrowser* fb =
		       palEditor->getPointSymbolCombo()->getTextureBrowser();
	const char* pathName = fb->getPathName();
	if (pathName && pathName[0]) {
	    layer->setNamedProperty(
		       new IlvStringProperty(IlvGetSymbol("_MARKER_BITMAP_"),
					     pathName));
	}
    }
}

// --------------------------------------------------------------------------
IlvMapsError
MapBuffer::loadMap(const char* name, IlBoolean visible)
{
    // Variables for the processing of the map
    IlBoolean shouldDeleteRenderer = IlTrue;
    IlBoolean canLOD = IlFalse;
    IlBoolean isLOD = IlFalse;
    IlBoolean isDataCD = IlFalse;
    IlvClassInfo* iteratorInfo = 0;
    IlvProjection* sourceProjection = 0;
    IlvMapLoader loader(manager);
    IlvMapFeatureIterator* iterator = 0;
    // Check if this is the data CD root
    IlPathName pathname(name);
    pathname.forceDirectory();

    if ((RasterLayerFactory::IsMultiRasterDirectory(pathname, 9)) ||
	(ShapeLayerFactory::IsMultiShapeDirectory(pathname))) {
	isLOD = IlTrue;
	isDataCD = IlTrue;
	sourceProjection = new IlvGeographicProjection();
	sourceProjection->setDatum(IlvHorizontalShiftDatum::WGS84());
	sourceProjection->setShared();
	sourceProjection->lock();
    }
    else { // Let's try the various feature iterators from lib
	iterator = loader.makeFeatureIterator(name);
    }
    // Case of unknown format
    if (!isDataCD &&
	(!iterator || (iterator->getInitStatus() != IlvMaps::NoError()))) {
	mapbuilder->reportInfo("Bad directory.\n"); // III
	if (iterator) {
	    delete iterator;
	}
	iterator = 0;
	return IlvMaps::FormatError();
    }
    // Determine wether this iterator is load-on-demandable
    if (iterator) {
	iteratorInfo = iterator->getClassInfo();
    }
    if (iteratorInfo != 0) {
	if (iteratorInfo->isSubtypeOf(IlvDTEDReader::ClassInfo()) ||
	    iteratorInfo->isSubtypeOf(IlvCADRGFrameReader::ClassInfo()) ||
	    iteratorInfo->isSubtypeOf(IlvShapeFileReader::ClassInfo()) ||
	    (iteratorInfo->isSubtypeOf(IlvGeoTIFFReader::ClassInfo()) &&
	     (((IlvGeoTIFFReader*)iterator)->isTiled()))) {
	    canLOD = IlTrue;
	}
    }
    ReaderController r(manager->getDisplay(),
		       desktopManager->getView()->getSystemView());
    r.getContainer()->moveToView(getBuilder()->getMainWindow());

    if (isDataCD) {
	r.setRequestingForVisibilityFilter(IlFalse);
	r.setSourceProjection(sourceProjection);
    }    
    // case of asking for setRequestingForDestProjectionsource projection
    IlBoolean sourceProjectionDefined = IlFalse;
    if (iterator) {
	sourceProjectionDefined =
	    !(iterator->getProjection() == 0 ||
	      iterator->getProjection()->getClassInfo()
			   ->isSubtypeOf(IlvUnknownProjection::ClassInfo()));
    }
    else {
	sourceProjectionDefined = IlTrue;
    }
    if (!sourceProjectionDefined) {
	r.setRequestingForSourceProjection(IlTrue);
    }
    // case of asking for destination projection
    IlvMapInfo* destMapinfo = IlvMapInfo::Get(manager);
    if (!destMapinfo && r.isRequestingForSourceProjection()) {
	r.setRequestingForDestProjection(IlTrue);
    }
    if (!destMapinfo ) {
	r.setRequestingForDestAdapter(IlTrue);
    }
    r.initReaderSpecific(iterator, name);
    //---- ask for user parameters -----
    if (!r.getParameters()) {
	if (iterator) { 
	    delete iterator;
	}
	iterator = 0;
	return IlvMaps::NoError();
    }
    // get parameters
    if (sourceProjection == 0) {
	if (r.isRequestingForSourceProjection()) {
	    sourceProjection = r.getSourceProjection();
	}
	else {
	    sourceProjection = (IlvProjection*)iterator->getProjection();
	}
    }
    
    IlvProjection* destinationProjection = 0;
    if (r.isRequestingForDestProjection()) {
	destinationProjection = r.getDestProjection();
    }
    else if (!destMapinfo) {
	destinationProjection = sourceProjection;
    }
    IlvMapAdapter* destinationAdapter = 0;
    if (r.isRequestingForDestAdapter())
	destinationAdapter = r.getDestAdapter(destinationProjection
					      ? destinationProjection
					      : sourceProjection);
    if (r.isRequestingForLOD() && r.isLOD()) {
	isLOD = IlTrue;
	r.setRequestingForDestProjection(IlFalse);
    }
    IlvScaleVisibilityFilter* filter = r.getVisibilityFilter();
    if (visible) {
	setVisible(IlTrue);
    }
    if (!destMapinfo) {
	// Set mapinfo only in this case. Otherwise, destination projection
	// is already known
	IlvMapInfo* info = new IlvMapInfo(destinationProjection,
					  destinationAdapter,
					  IlFalse);
	info->attach(manager);
    } 
    // renderer
    IlvFeatureRenderer* renderer = 0;
    if (iteratorInfo->isSubtypeOf(IlvS57Loader::ClassInfo())) {
	renderer = ((IlvS57Loader*)iterator)
			  ->getDefaultFeatureRenderer(manager->getDisplay());
    }
    else {
	renderer = r.getRenderer();
    }
    // Check for attributes
    IlBoolean attachingAttributes = IlFalse;
    if (iteratorInfo != 0 &&
	iteratorInfo->isSubtypeOf(IlvShapeFileReader::ClassInfo())) {
	if (r.isRequestingForAttributes()) {
	    if (r.isAttachingAttributes()) {
		attachingAttributes = IlTrue;
	    }
	    else {
		attachingAttributes = IlFalse;
	    }
	}
	else {
	    attachingAttributes = IlFalse;
	}
    }
    IlString layername(name);
    layername = layername.getSubString(layername.getLastIndexOf(
					   IlString(
#if defined(WINDOWS)
					       "\\"
#else
					       "/"
#endif
					       )) + 1,
				       (IlInt)layername.getLength());
    // Load data as non LOD layer
    if (!isLOD) {
	manager->addLayer(-1);
	IlInt numLayers = manager->getNumLayers();
	IlvManagerLayer* insertionLayer =
				     manager->getManagerLayer(numLayers - 1);
	if (filter) {
	    insertionLayer->addVisibilityFilter(filter);
	}
	manager->setInsertionLayer(numLayers - 1);
	// Add a way to avoid duplicated layer names
	if (!layername.isEmpty()) {
	    insertionLayer->setName(layername.getValue());
	}
	IlvMapsError status = IlvMaps::NoError();
	IlvMapInfo* mapinfo = IlvMapInfo::Get(manager);
	IlvMapsError renderingStatus = IlvMaps::NoError();
	IlvMapFeature* feature = 0;
	int count = 0;
	IlvSetContentsChangedUpdate(IlFalse);
	manager->initReDraws();
	// Case of using a sub iterator : save the true iterator,
	// use the sub iterator, then after the make graphic loop,
	// restore and free the true iterator
	IlvMapFeatureIterator* savedIterator=0;
	if (iteratorInfo->isSubtypeOf(IlvShapeFileReader::ClassInfo())) {
	    if (!attachingAttributes) {
		savedIterator = iterator;
		IlvShapeFileReader* shapefilereader =
					       (IlvShapeFileReader*)iterator;
		iterator = shapefilereader->getSHPReader();
	    }
	}
	IlvClassInfo* clsinfo = 0;
	for (feature = (IlvMapFeature*)iterator->getNextFeature(status);
	     feature && (status == IlvMaps::NoError());
	     feature = (IlvMapFeature*)iterator->getNextFeature(status))
	    {
		if (!clsinfo && feature) {
		    clsinfo = feature->getGeometry()->getClassInfo();
		    insertionLayer->setNamedProperty(
			    new IlvStringProperty(IlvGetSymbol("_GEOMETRY_"),
						  clsinfo->getClassName()));
		    UpdateLayerAttributes(insertionLayer,
					  r.getPaletteEditor());
		}
		feature->setProjection(sourceProjection);
		// render graphic
		IlvGraphic* g = renderer->makeGraphic(*feature, *mapinfo,
						      renderingStatus);
		if (g) {
		    if (iteratorInfo && 
			iteratorInfo->isSubtypeOf(
					    IlvGeoTIFFReader::ClassInfo())) {
			if (g->isSubtypeOf(IlvIcon::ClassInfo())) {
			    IlvIcon* icon = (IlvIcon*) g; 
			    icon->getBitmap()->setName(name); 		    
			}
		    }
		    if (renderingStatus == IlvMaps::NoError()) {
			if (attachingAttributes) {
			    const IlvFeatureAttributeProperty* ap =
						    feature->getAttributes();
			    if (ap) {
				g->setNamedProperty(ap->copy());
			    }
			}
			manager->addObject(g, IlFalse);
			manager->invalidateRegion(g);
		    }
		    else {
			if (g) {
			    delete g;
			}
		    }
		    count++;
		}
	    }
	IlvSetContentsChangedUpdate(IlTrue);
	manager->contentsChanged();
	if (r.getPaletteEditor()) {
	    insertionLayer->setAntialiasingMode(
				r.getPaletteEditor()->getAntialiasingMode());
	    insertionLayer->setTransparency(
				    r.getPaletteEditor()->getTransparency());
	}
	manager->reDrawViews();
	if (savedIterator) {
	    iterator = savedIterator;
	}
	char buf1[500];
	sprintf(buf1, "%d objects added\n", count);
	mapbuilder->reportInfo(buf1);
    }
    else {
	//
	// Process Load On Demand
	//
	IlvMapInfo* mapinfo = IlvMapInfo::Get(manager);
	// keep the UL/LR of the iterator, for further centering
	IlvCoordinate UL, LR;
	IlBoolean ULLRok = IlFalse;
	if (iterator) {
	    ULLRok = (iterator->getUpperLeftCorner(UL) &&
		      iterator->getLowerRightCorner(LR));
	}
	else if (isDataCD) {
	    ULLRok = IlFalse;
	}
	IlvTiledLayer* layer = 0;
	//
	// We are necessarly in case of shapefile or raster multires if
	// iterator is 0 at this point
	//
	if (!iteratorInfo) {
	    IlInt numLayers = 0;
	    IlvTiledLayer** layers = 0;
	    IlBoolean isRaster = IlFalse;
	    if (RasterLayerFactory::IsMultiRasterDirectory(pathname, 9)) {
		rasterFactory = new RasterLayerFactory(pathname);
		numLayers = rasterFactory->getNumLayers();
		layers = new IlvTiledLayer*[numLayers];
		IlInt i;
		for (i = 0 ; i < numLayers; i++) {
		    IlvImageLayer* l =
			      rasterFactory->makeLayer(manager->getDisplay(),
						       mapinfo->getAdapter(),
						       i);
		    manager->addLayer(l);
		    layers[i] = l;
		}
		isRaster = IlTrue;
	    }
	    else if (ShapeLayerFactory::IsMultiShapeDirectory(pathname)) {
		shapeFactory = new ShapeLayerFactory(pathname);
		numLayers = shapeFactory->getNumLayers();
		layers = new IlvTiledLayer*[numLayers];
		IlInt i;
		for (i = 0 ; i < numLayers; i++) {
		    IlvShapeFileLayer* l =
			       shapeFactory->makeLayer(manager->getDisplay(),
						       mapinfo->getAdapter(),
						       i);
		    manager->addLayer(l);
		    layers[i] = l;
		}
	    }
	    IlvCoordinate UL(-180, 90);
	    IlvCoordinate LR(180, -90);
	    IlUInt c;
	    manager->getObjects(c);
	    if (c == 0) {
		mapinfo->getAdapter()->fitTransformerToRect(view, UL, LR,
							    IlFalse, IlTrue);
	    }
	    IlUInt count;
	    for (IlInt i = 0; i < numLayers; i++) {
		IlString aName(layername);
		if (isRaster) {
		    aName += IlString("Raster_");
		}
		else {
		    aName += IlString("Poline_");
		}
		aName += IlString(i);
		aName += IlString(" (LOD)");
		layers[i]->setName(aName.getValue());
		layers[i]->start();
		layers[i]->getTileController()->updateView(
						manager->getViews(count)[0]);
	    }
	    if (layers) {
		delete layers;
	    }
	    layers = 0;
	    IlvManagerViewInteractor* inter =
			 manager->getInteractor(manager->getViews(count)[1]);
	    manager->reDraw();
	    if (renderer && shouldDeleteRenderer) {
		delete renderer;
	    }
	    renderer = 0;
	    mapbuilder->updateBufferDependentUI();
	    return IlvMaps::NoError();
	}
	else if (iteratorInfo->isSubtypeOf(
					   IlvShapeSHPReader::ClassInfo()) ||
		 iteratorInfo->isSubtypeOf(
					  IlvShapeFileReader::ClassInfo())) {
	    //
	    // Case of Shapefile layer
	    //
	    layer = CreateShapefileLayer(name, mapinfo->getAdapter());
	    if (!layer || (layer->getInitStatus() != IlvMaps::NoError())) {
		mapbuilder->reportError("Can't create Shapefile layer\n");
		IlvMapsError error;
		if (layer) {
		    error = layer->getInitStatus();
		    delete layer;
		}
		else {
		    error = IlvMaps::IllegalArgument();
		}
		return error;
	    }
	    ((IlvMapTileLoader*)layer->getTileLoader())
					      ->setFeatureRenderer(renderer);
	    ((IlvMapTileLoader*)layer->getTileLoader())
			       ->setAttachingAttributes(attachingAttributes);
	    shouldDeleteRenderer = IlFalse;
	}
	else if (iteratorInfo->isSubtypeOf(IlvGeoTIFFReader::ClassInfo())) {
	    //
	    // Case of GeoTIFF layer
	    //
	    layer = CreateGeoTIFFLayer(name, mapinfo->getAdapter());
	    if (!layer || (layer->getInitStatus() != IlvMaps::NoError())) {
		mapbuilder->reportError("Can't create GeoTIFF layer\n");
		IlvMapsError error;
		if (layer) {
		    error = layer->getInitStatus();
		    delete layer;
		}
		else {
		    error = IlvMaps::IllegalArgument();
		}
		return error;
	    }
	}
	else if (iteratorInfo->isSubtypeOf(IlvDTEDReader::ClassInfo())) {
	    //
	    // Case of DTED layer
	    //
	    layer = CreateDTEDLayer(name, mapinfo->getAdapter());
	    if (!layer || (layer->getInitStatus() != IlvMaps::NoError())) {
		mapbuilder->reportError("Can't create DTED layer\n");
		IlvMapsError error;
		if (layer) {
		    error = layer->getInitStatus();
		    delete layer;
		}
		else {
		    error = IlvMaps::IllegalArgument();
		}
		return error;
	    }
	}
	else if (iteratorInfo->isSubtypeOf(
					 IlvCADRGFrameReader::ClassInfo())) {
	    //
	    // Case of CADRG layer
	    // 
	    layer = CreateCADRGLayer(name, mapinfo->getAdapter());
	    if (!layer || (layer->getInitStatus() != IlvMaps::NoError())) {
		mapbuilder->reportError("Can't create CADRG layer\n");
		IlvMapsError error;
		if (layer) {
		    error = layer->getInitStatus();
		    delete layer;
		}
		else {
		    error = IlvMaps::IllegalArgument();
		}
		return error;
	    }
	}
	// Adds the layer to manager
	if (layer) {
	    if (!layername.isEmpty()) {
		layername += IlString(" (LOD)");
		layer->setName(layername.getValue());
	    }
	    manager->addLayer(layer);
	    UpdateLayerAttributes(layer, r.getPaletteEditor());
	    if (iteratorInfo->isSubtypeOf(IlvDTEDReader::ClassInfo())) {
		if (!ULLRok) {
		    layer->fitTransformerToTile(view, 0, 0);
		}
		else {
		    // convert UL/LR to manager coordinates
		    const IlvMapAdapter* adapter = mapinfo->getAdapter();
		    adapter->fitTransformerToRect(view, UL, LR,
						  IlFalse, IlTrue);
		}
	    }
	    if (filter) {
		layer->addVisibilityFilter(filter);
	    }
	    IlUInt count;
	    if (!isDataCD) { // Don't ignore the overview for multires data
		IlvTileController::IgnoreView(manager->getViews(count)[1]);
	    }
	    layer->start();
	    if (r.getPaletteEditor()) {
		layer->setAntialiasingMode(
				r.getPaletteEditor()->getAntialiasingMode());
		layer->setTransparency(r.getPaletteEditor()
				       ->getTransparency());
	    }
	    layer->getTileController()->updateView(
						manager->getViews(count)[0]);
	    IlvManagerViewInteractor* inter =
			 manager->getInteractor(manager->getViews(count)[1]);
	}
	else {
	    if (iterator) {
		delete iterator;
	    }
	    iterator = 0;
	    return IlvMaps::FormatError();
	}
	if (iterator) {
	    delete iterator;
	}
	iterator = 0;
	manager->reDraw();
    }
    if (iterator) {
	delete iterator;
    }
    iterator = 0;
    if (renderer && shouldDeleteRenderer) {
	delete renderer;
    }
    renderer = 0;
    // update ui dependent from current view
    mapbuilder->updateBufferDependentUI();
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
IlvMapsError
MapBuffer::save(const char* name)
{
    // check parameters
    if (!name && !filename) {
	return IlvMaps::IllegalArgument();
    }
    // Save the manager
    const char* fileName = name ? name : filename;
#ifdef ILVMAPS_STD_STREAM
    // STL
    ofstream output(fileName, ios::out | ios::binary);
#else
#if defined (WINDOWS)
    // PC without STL
    ofstream output(fileName, ios::out |  ios::binary);
#else
    // unix
    ofstream output(fileName, ios::out);
#endif
#endif
    manager->save(output);
    output.close();

    // store this file name, if relevant
    if (name) {
	if (filename) {
	    delete [] filename;
	}
	filename = IlCopyString(name, IlFalse);
    }
    return IlvMaps::NoError();
}

// --------------------------------------------------------------------------
void
MapBuffer::setVisible(IlBoolean set)
{
    if (set) {
	frame->show();
    }
    else if (frame->isVisible()) {
	frame->hide();
    }
    if (set) {
	desktopManager->setCurrentFrame(frame,IlTrue);
    }
}
