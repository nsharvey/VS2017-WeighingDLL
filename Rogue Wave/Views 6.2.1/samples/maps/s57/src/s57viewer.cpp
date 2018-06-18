// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/s57/src/s57viewer.cpp
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
// Implementation of the s57viewer.
// --------------------------------------------------------------------------

#include <ilviews/maps/projection/unknownp.h>
#include <ilviews/maps/rendering/all.h>
#include <ilviews/maps/format/s57/s57reader.h>
#include <ilviews/maps/format/s57/s57loader.h>

#include <ilviews/maps/attribute/intattr.h>
#include <ilviews/maps/attribute/doubleattr.h>
#include <ilviews/maps/attribute/boolattr.h>
#include <ilog/pathname.h>

#include "s57viewer.h"

#if defined(IL_STD)
#  include <iostream>
#  include <fstream>
#  include <ctime>
IL_STDUSE
#else
#  include <stdio.h>
#  include <iostream.h>
#  include <fstream.h>
#  if !defined(WINDOWS)
#    include <unistd.h>
#  endif
#    include <stdlib.h>
#    include <time.h>
#endif

#if 1 // OPTIMIZE
#include <ilviews/util/runtime.h>
#endif


// --------------------------------------------------------------------------
// S57Viewer
// --------------------------------------------------------------------------
S57Viewer::S57Viewer(IlvDisplay* display,
		     IlvMapInfo* mapInfo,
		     IlvProjection* sourceProjection)
    : Gui()
{
    _mapInfo = mapInfo;
    _sourceProjection = sourceProjection;
    if (_sourceProjection) {
	_sourceProjection->lock();
    }
    _layerIndex = 0;

    createGui(display);

    _mapInfo->attach(getManagerRectangle()->getManager());
}

// --------------------------------------------------------------------------
S57Viewer::~S57Viewer()
{
    if (_sourceProjection) {
	_sourceProjection->unLock();
    }
    _sourceProjection = 0;
}

// --------------------------------------------------------------------------
// Lists the attributes of the given IlvGraphic
// --------------------------------------------------------------------------
void
S57Viewer::buttonDown(IlvGraphic* g)
{
    if (!g) {
	return;
    }
    PopupS57Info* popup = getPopupInfo();
    popup->clear();
    char buf[512];

    IlvFeatureAttributeProperty* ap = (IlvFeatureAttributeProperty*)
	g->getNamedProperty(IlvFeatureAttributeProperty::GetName());
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
	    const IlvMapClassInfo* clsinfo = info->getAttributeClass(i);
	    const IlvFeatureAttribute* fa = ap->getAttribute(i);
	    if (clsinfo->isSubtypeOf(IlvStringAttribute::ClassInfo())) {
		const char *str = ((IlvStringAttribute*)fa)->getValue();
		if (str) {
		    sprintf(buf, "%s %s", name ? name : "",
			    str ? str : "");
		}
	    }
	    else if (clsinfo->isSubtypeOf(IlvIntegerAttribute::ClassInfo())) {
		int in = ((IlvIntegerAttribute*)fa)->getValue();
		sprintf(buf, "%s %d", name ? name : "", in);
	    }
	    else if (clsinfo->isSubtypeOf(IlvDoubleAttribute::ClassInfo())) {
		double dbl = ((IlvDoubleAttribute*)fa)->getValue();
		sprintf(buf, "%s %g", name ? name : "", dbl);
	    }
	    else if (clsinfo->isSubtypeOf(IlvBooleanAttribute::ClassInfo())) {
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
		popup->addLabel(buf);
	    }
	}
    }
    popup->show();
}

// --------------------------------------------------------------------------
void
S57Viewer::checkError(const IlvMapsError& status, IlBoolean end)
{
    char buffer[1024];
    if (status != IlvMapInput::EndOfFileError() &&
	status != IlvMaps::NoError()) {
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
void
S57Viewer::loadFile(const char* fileName)
{
    char buffer[1024];
    wait(IlvTrue);
    sprintf(buffer, "Loading %s ...", fileName);
    getStatusBar()->setLabel(buffer);
    getStatusBar()->reDraw();

    IlvMapsError status = IlvMaps::NoError();

    IlvS57Loader reader(getDisplay());
    reader.setFilename(fileName);
    if ((status = reader.getInitStatus()) != IlvMaps::NoError()) {
	checkError(status, IlTrue);
    }
    else if (status == IlvMaps::NoError()) {
	getManager()->deleteAll(IlTrue,IlFalse);
	getManager()->addLayer();
	IlvDisplay* display = getDisplay();
	IlvFeatureRenderer* renderer =
		reader.getDefaultFeatureRenderer(display);
	IlvMapsError status = IlvMaps::NoError();
	IlvGraphic* graphic;
	IlvManager* m = getManager();
	IlvSetContentsChangedUpdate(IlFalse);
	m->initReDraws();
	const IlvFeatureAttributeProperty* ap;
	// read all graphics
	for (const IlvMapFeature* f = reader.getNextFeature(status);
	     status == IlvMaps::NoError() && f ;
	     f = reader.getNextFeature(status)) {
	    graphic = renderer->makeGraphic(*f,*_mapInfo,status);
	    if (graphic) {
		ap = f->getAttributes();
		m->addObject(graphic, IlvFalse);
		m->invalidateRegion(graphic);
		if (ap) {
		    graphic->setNamedProperty(ap->copy());
		}
	    }
	}
	// check that if an error exists, it is an EOF error
	checkError(status, IlTrue);
	if (renderer) {
	    delete renderer;
	}
	renderer = 0;
	_layerIndex++;
	IlvSetContentsChangedUpdate(IlTrue);
	m->reDrawViews();
    }

    wait(IlvFalse);
}

// --------------------------------------------------------------------------
// Main
// --------------------------------------------------------------------------
int
main(int argc, char** argv)
{
    IlvDisplay* display = new IlvDisplay("s57Viewer", 0, argc, argv);
    if (display->isBad()) {
	IlvPrint("Couldn't open display");
	return 1;
    }
    IlPathName localPath(display->getHomePath());
    display->prependToPath(localPath);

    double precision = .0001;
    int firstFile = 1;
    if (argc > 1) {
	if (strcmp(argv[1],"-a") == 0) {
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

    S57Viewer viewer(display,
		     mapInfo,
		     (IlvProjection*)mapInfo->getProjection());
    if ((argc-firstFile) >= 1) {
	for (int i = 1; i < argc; i++) {
	    viewer.loadFile(argv[i]);
	}
    }
    viewer.showAll();
    viewer.getContainer()->show();

    IlvMainLoop();

    return 0;
}
