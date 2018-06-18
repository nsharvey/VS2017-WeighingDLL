// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/shapefile/src/shapeviewer.cpp
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
// Implementation of the shapeviewer.
// --------------------------------------------------------------------------

#include <ilviews/maps/projection/unknownp.h>
#include <ilviews/maps/rendering/all.h>
#include <ilviews/maps/dftrenderer.h>
#include <ilviews/maps/tiling/tiledlayer.h>
#include <ilviews/maps/format/shapefile/shpfile.h>
#include <ilviews/maps/format/shapefile/shptloader.h>
#include <ilviews/maps/format/shapefile/shptiler.h>
#include <ilviews/util/runtime.h>
#include <ilog/pathname.h>

#include <shapeviewer.h>

#if defined(IL_STD)
#  include <iostream>
#  include <fstream>
#  include <ctime>
IL_STDUSE
#else
#  include <stdio.h>
#  include <iostream.h>
#  include <fstream.h>
#  include <stdlib.h>
#  include <time.h>
#endif

// --------------------------------------------------------------------------
// ShapeViewer
// --------------------------------------------------------------------------
// Creates an new instance of the Shape Viewer.
// fileName is the name of a Shape Frame file.
// --------------------------------------------------------------------------
ShapeViewer::ShapeViewer(IlvDisplay* display,
			 IlvMapInfo* mapInfo,
			 IlvProjection* sourceProjection)
    : Gui(),
      _mapInfo(mapInfo),
      _sourceProjection(sourceProjection),
      _layerIndex(0)
{
    createGui(display);

    _mapInfo->attach(getManagerRectangle()->getManager());
}

// --------------------------------------------------------------------------
ShapeViewer::~ShapeViewer()
{
    if (_sourceProjection
	&& (_sourceProjection != _mapInfo->getProjection())) {
	delete _sourceProjection;
    }
}

// --------------------------------------------------------------------------
// Returns a random color
// --------------------------------------------------------------------------
static IlvColor* RandomColor(IlvDisplay* display)
{
    IlvUShort r, g, b;
    static int initialized = 0;
    if (!initialized) {
	time_t t;
	t = time(&t);
	srand((unsigned int)t);
	initialized = 1;
    }
    r = rand() % ( 256 * 256);
    g = rand() % (256 * 256);
    b = rand() % (256 * 256);
    IlvColor* col = display->getColor(r, g, b);
    if (!col) {
	col = display->getNearestColor(r, g, b);
    }
    return col;
}

// --------------------------------------------------------------------------
// lists the attributes of the given IlvGraphic
// --------------------------------------------------------------------------
void
ShapeViewer::buttonDown(IlvGraphic* g)
{
    if (!g) {
	return;
    }
    PopupShapefileInfo* list = getPopupInfo();
    list->clear();
    char buf[512];

    IlvFeatureAttributeProperty* ap =
	(IlvFeatureAttributeProperty*)g->getNamedProperty(IlvFeatureAttributeProperty::GetName());
    if (!ap) {
	return;
    }
    const IlvFeatureAttributeInfo* info = ap->getInfo();
    if (info) {
	IlvUInt count;
	count = info->getAttributesCount();
	for (IlvUInt i = 0; i < count; i++) {
	    buf[0] = 0;
	    const char* name = info->getAttributeName(i);

	    const IlvMapClassInfo* clsinfo =
		info->getAttributeClass(i);
	    const IlvFeatureAttribute* fa = ap->getAttribute(i);
	    if (clsinfo->isSubtypeOf(IlvStringAttribute::ClassInfo())) {
		const char *str = ((IlvStringAttribute*)fa)->getValue();
		if (str) {
		    sprintf(buf, "%s %s", name ? name : "",
			    str ? str : "");
		}
	    }
	    else if (clsinfo->isSubtypeOf(IlvIntegerAttribute::ClassInfo())){
		int in = ((IlvIntegerAttribute*)fa)->getValue();
		sprintf(buf, "%s %d", name ? name : "", in);
	    }
	    else if (clsinfo->isSubtypeOf(IlvDoubleAttribute::ClassInfo())) {
		double dbl = ((IlvDoubleAttribute*)fa)->getValue();
		sprintf(buf, "%s %g", name ? name : "", dbl);
	    }
	    else if (clsinfo->isSubtypeOf(IlvBooleanAttribute::ClassInfo())){
		IlvBoolean bo = ((IlvBooleanAttribute*)fa)->getValue();
		sprintf(buf, "%s %s", name ? name : "",
			bo ? "true" : "false");
	    }
	    if (buf[0]) {
		size_t l = strlen(buf);
		char* pt = &buf[l - 1];
		if (*pt == ' ') {
		    while ((*pt == ' ') && pt > buf) {
			pt --;
		    }
		    pt ++;
		    *pt = 0;
		}
		list->addLabel(buf);
	    }
	}
    }
    list->show();
}

// --------------------------------------------------------------------------
IlString*
ShapeViewer::GetIDXFileName(IlString& shpFileName)
{
    if (shpFileName.endsWith(".shp")) {
	return new IlString(shpFileName.getSubString(0,
					  (int)shpFileName.getLength() - 4) +
			    IlString(".idx"));
    }
    else if (shpFileName.endsWith(".SHP")) {
	return new IlString(shpFileName.getSubString(0,
					  (int)shpFileName.getLength() - 4) +
			    IlString(".IDX"));
    }
    else {
	return 0;
    }
}

// --------------------------------------------------------------------------
IlString*
ShapeViewer::GetSHXFileName(IlString& shpFileName)
{
    if (shpFileName.endsWith(".shp")) {
	return new IlString(shpFileName.getSubString(0,
					  (int)shpFileName.getLength() - 4) +
			    IlString(".shx"));
    }
    if (shpFileName.endsWith(".SHP")) {
	return new IlString(shpFileName.getSubString(0,
					(int)shpFileName.getLength() - 4) +
			    IlString(".SHX"));
    }
    return 0;
}

// --------------------------------------------------------------------------
IlString*
ShapeViewer::GetDBFFileName(IlString& shpFileName)
{
    if (shpFileName.endsWith(".shp")) {
	return new IlString(shpFileName.getSubString(0,
					  (int)shpFileName.getLength() - 4) +
			    IlString(".dbf"));
    }
    if (shpFileName.endsWith(".SHP")) {
	return new IlString(shpFileName.getSubString(0,
					  (int)shpFileName.getLength() - 4) +
			    IlString(".DBF"));
    }
    return 0;
}

// --------------------------------------------------------------------------
void
ShapeViewer::tuneRenderer(IlvFeatureRenderer* renderer) const
{
    IlvClassInfo* info = renderer->getClassInfo();
    IlvDisplay* display = getDisplay();
    if (info->isSubtypeOf(IlvDefaultCurveRenderer::ClassInfo())) {
	IlvMapLineRenderingStyle* lrs =
				new IlvMapLineRenderingStyle(display);
	lrs->setForeground(RandomColor(display));
	((IlvDefaultCurveRenderer*) renderer)->setLineRenderingStyle(lrs);
    }
    else if (info->isSubtypeOf(IlvDefaultAreaRenderer::ClassInfo())) {
	IlvMapAreaRenderingStyle* ars =
				new IlvMapAreaRenderingStyle(display);
	IlvMapLineRenderingStyle *lrs =
				new IlvMapLineRenderingStyle(display);
	lrs->setForeground(RandomColor(display));
	ars->setFillColor(RandomColor(display));
	ars->setDrawingStroke(IlvTrue);
	ars->setLineRenderingStyle(lrs);
	((IlvDefaultAreaRenderer*) renderer)->setAreaRenderingStyle(ars);
    }
    else if (info->isSubtypeOf(IlvDefaultPointRenderer::ClassInfo())) {
	IlvDefaultPointRenderer* pr = (IlvDefaultPointRenderer*)renderer;
	pr->setForeground(RandomColor(display));
    }
    else if (info->isSubtypeOf(IlvDefaultFeatureRenderer::ClassInfo())) {
	IlvDefaultPointRenderer* pr = (IlvDefaultPointRenderer*)
		((IlvDefaultFeatureRenderer*)renderer)->getPointRenderer();
	tuneRenderer(pr);
	IlvDefaultAreaRenderer* ar = (IlvDefaultAreaRenderer*)
		((IlvDefaultFeatureRenderer*)renderer)->getAreaRenderer();
	tuneRenderer(ar);
	IlvDefaultCurveRenderer* cr = (IlvDefaultCurveRenderer*)
		((IlvDefaultFeatureRenderer*)renderer)->getCurveRenderer();
	tuneRenderer(cr);
    }
}

// --------------------------------------------------------------------------
void
ShapeViewer::checkError(const IlvMapsError& status, IlBoolean end)
{
    char buffer[1024];
    if ((status != IlvMapInput::EndOfFileError())
	&& (status != IlvMaps::NoError())) {
	sprintf(buffer, "Error %s", IlvMaps::GetErrorMessageId(status));
    }
    else if (end) {
	sprintf(buffer, "Done");
    }
    if (end) {
	getStatusBar()->setLabel(buffer);
	getStatusBar()->reDraw();
    }
}

// --------------------------------------------------------------------------
// Load a shape file and its associated dbf file (if any)
// --------------------------------------------------------------------------
void
ShapeViewer::loadFile(const char* fileName, IlBoolean lod)
{
    char buffer[1024];
    wait(IlvTrue);
    sprintf(buffer, "Loading %s ...", fileName);
    getStatusBar()->setLabel(buffer);
    getStatusBar()->reDraw();
    IlvShapeSHPReader* shpReader = new IlvShapeSHPReader(fileName);
    if (shpReader->getInitStatus() != IlvMaps::NoError()) {
	delete shpReader;
	getStatusBar()->setLabel("Cannot load .shp file");
	getStatusBar()->reDraw();
	wait(IlvFalse);
	return;
    }
    // Check if a .dbf file exists
    IlString fn(fileName);
    IlString* dbfFileName = GetDBFFileName(fn);
    // open this dbf file if file exists
    IlvShapeDBFReader* dbfReader = 0;
    if (dbfFileName) {
	dbfReader = new IlvShapeDBFReader(dbfFileName->getValue());
	if (dbfReader->getInitStatus() != IlvMaps::NoError()) {
	    delete dbfReader;
	    dbfReader = 0;
	}
	delete dbfFileName;
    }
    IlvMapsError status = IlvMaps::NoError();
    if (!lod) {
	// load
	IlvShapeFileReader reader(shpReader, dbfReader, IlvTrue);
	if ((status = reader.getInitStatus()) != IlvMaps::NoError()) {
	    checkError(status, IlTrue);
	}
	else if (status == IlvMaps::NoError()) {
	    getManager()->addLayer();
	    IlvDisplay* display = getDisplay();
	    // Computing a random palette for the theme
	    IlvFeatureRenderer* renderer =
			reader.getDefaultFeatureRenderer(display);
	    tuneRenderer(renderer);
	    IlvMapsError status = IlvMaps::NoError();
	    IlvGraphic* graphic;
	    IlvManager* m = getManager();
	    IlvSetContentsChangedUpdate(IlFalse);
	    m->initReDraws();
	    const IlvFeatureAttributeProperty* ap;
	    // Read all graphics
	    for (const IlvMapFeature* f = reader.getNextFeature(status);
		 status == IlvMaps::NoError() && f ;
		 f = reader.getNextFeature(status)) {
		graphic = renderer->makeGraphic(*f,*_mapInfo,status);
		ap = f->getAttributes();
		m->addObject(graphic, IlvFalse);
		m->invalidateRegion(graphic);
		if (ap) {
		    graphic->setNamedProperty(ap->copy());
		}
	    }
	    // Check that if an error exists, it is an EOF error
	    checkError(status, IlTrue);
	    if (renderer) {
		delete renderer;
	    }
	    renderer = 0;
	    _layerIndex++;
	    IlvSetContentsChangedUpdate(IlTrue);
	    m->reDrawViews();
	}
    }
    else {
	// load on demand
	IlString fname(fileName);
	IlString* dbfFileName = GetDBFFileName(fname);
	IlString* shxFileName = GetSHXFileName(fname);
	IlString* idxFileName = GetIDXFileName(fname);
	if (!idxFileName || !shxFileName) {
	    getStatusBar()->setLabel("Index file or SHX file not found");
	    getStatusBar()->reDraw();
	    return;
	}
	IlvShapeFileTileLoader* loader =
		new IlvShapeFileTileLoader(fileName,
					   dbfFileName
					   ? dbfFileName->getValue()
					   : 0,
					   shxFileName->getValue(),
					   idxFileName->getValue(),
					   _mapInfo->getAdapter());
	IlvMapsError error = loader->getInitStatus();
	if (error != IlvMaps::NoError()) {
	    checkError(error, IlTrue);
	    wait(IlvFalse);
	    return;
	}
	IlvFeatureRenderer* renderer =
		new IlvDefaultFeatureRenderer(getDisplay());
	tuneRenderer(renderer);
	if (dbfFileName) {
	    delete dbfFileName;
	}
	delete shxFileName;
	delete idxFileName;
	IlvTiledLayer* layer = new IlvTiledLayer(loader->getTileOrigin());
	layer->setTileLoader(loader);
	loader->setFeatureRenderer(renderer);
	getManager()->addLayer(layer);
	layer->start();
	IlUInt count;
	layer->getTileController()
	     ->updateView(getManager()->getViews(count)[0]);
	getManager()->reDraw();
    }
    wait(IlvFalse);
}

// --------------------------------------------------------------------------
// Main
// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay("shapeViewer", 0, argc, argv);
    if (display->isBad()) {
      IlvPrint("Couldn't open display");
      return 1;
    }
    IlPathName localPath(display->getHomePath());
    display->prependToPath(localPath);
    localPath.addDirectory("samples/maps/shapefile/data");
    display->prependToPath(localPath);

    double precision = .001;
    int firstFile = 1;
    if (argc > 1) {
	if (strcmp(argv[1], "-a") == 0) {
	    if (argc < 3) {
		IlvPrint("-a expects an argument for the adapter precision");
		return 1;
	    }
	    precision = atof(argv[2]);
	    firstFile = 3;
	}
    }

    IlvUnknownProjection proj;
    IlvMapAdapter adapter(precision);
    IlvMapInfo* mapInfo = new IlvMapInfo(&proj,&adapter);

    ShapeViewer viewer(display,
		       mapInfo,
		       (IlvProjection*)
		       mapInfo->getProjection());

    if ((argc-firstFile) >= 1) {
	for (int i = 1; i < argc; i++) {
	    viewer.loadFile(argv[i]);
	}
    }
    else {
	viewer.loadFile(display->findInPath("POLINE.SHP"));
	viewer.loadFile(display->findInPath("PPPOLY.SHP"));
	viewer.loadFile(display->findInPath("PPPOINT.SHP"));
	viewer.loadFile(display->findInPath("RDLINE.SHP"));
    }
    viewer.showAll();
    viewer.getContainer()->show();

    IlvMainLoop();

    return 0;
}
