// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/reader.cpp
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
// Definition of the VpfReader class
// --------------------------------------------------------------------------

#include <vpf/reader.h>
#include <vpf/database.h>
#include <vpf/coverage.h>
#include <vpf/featureclass.h>
#include <vpf/feature.h>
#include <vpf/featuretype.h>
#include <vpf/theme.h>
#include <vpf/projectn.h>
#include <vpf/error.h>
#include <vpf/point.h>
#include <vpf/segment.h>
#include <vpf/area.h>
#include <vpf/text.h>

// --------------------------------------------------------------------------
VpfReader::VpfReader(const char* path)
: _database(new VpfDatabase(path)),
  _library(0),
  _projector(0),
  _extent(VpfCoordinate(-180.F, 180.F),
	  VpfCoordinate(-90.F,  90.F)),
  _features(0)
{
    if (_database->isBad()) {
	delete _database;
	_database = 0;
    }
}

// --------------------------------------------------------------------------
VpfReader::~VpfReader()
{
    delete _features;
    delete _projector;
    delete _database;
}

// --------------------------------------------------------------------------
int
VpfReader::isBad()
{
    return (_database == 0);
}

// --------------------------------------------------------------------------
void
VpfReader::setLibrary(const char* libname)
{
    if (!_database)
	return;
    VpfLibrary* library = _database->getLibrary(libname);
    if (library)
	_library = library;
    else {
	VpfError* error = new VpfError("VpfReader::setLibrary:");
	error->getStream() << "No such library: "
			   << libname;
	VpfErrorReporter::Add(error);
    }
}

// --------------------------------------------------------------------------
VpfCoordinate&
VpfReader::whereIs(double x, double y) const
{
    static VpfCoordinate c;
    if (_projector)
	_projector->latlon(x, y);
    c.set(x, y);
    return c;
}

// --------------------------------------------------------------------------
void
VpfReader::project(VpfCoordinate* c) const
{
    if (_projector) {
	double x = c->getLongitude(),
	       y = c->getLatitude();
	_projector->xy(x, y);
	c->set(x, y);
    }
}

// --------------------------------------------------------------------------
void
VpfReader::loadingFeature(VpfUInt, VpfUInt)
{
}

// --------------------------------------------------------------------------
void
VpfReader::load(VpfPoint* point, void* userArg)
{
    if (point) {
	VpfCoordinate coord = *point->getCoordinate();
	project(&coord);
	createNode(coord, userArg);
    }
}

// --------------------------------------------------------------------------
void
VpfReader::load(VpfSegment* segment, void* userArg)
{
    VpfUInt nCoordinates = segment->getNCoordinates();
    VpfCoordinate* output = new VpfCoordinate[nCoordinates];

    VpfCoordinate* previousCoord = segment->getCoordinate(0);
    output[0] = *previousCoord;
    project(&output[0]);
    VpfUInt currentCoord = 1;
    for (VpfUInt j = 1; j < nCoordinates; j++) {
	VpfCoordinate* coord = segment->getCoordinate(j);

	if ((!coord->isNormal() && previousCoord->isNormal()) ||
	    (coord->isNormal() && !previousCoord->isNormal())) {
	    // Feature items might cross the +-180 meridian.
	    // This is not especially nice, but it is so.
	    // To cope with this, we have to split the segment.

	    double dLat = coord->getLatitude()-previousCoord->getLatitude();
	    double dLon = coord->getLongitude()-previousCoord->getLongitude();
	    VpfCoordinate end;
	    if (previousCoord->getLongitude() <= 180.0)
		// This is a -180 positive crossing.
		end.set(-180.0, previousCoord->getLatitude() +
			(-180.0 - previousCoord->getLongitude()) *
			(dLat / dLon));
	    else
	    if (previousCoord->getLongitude() > 180.0)
		// This is a +180 negative crossing
		end.set(180.0, previousCoord->getLatitude() +
			(previousCoord->getLongitude() - 180.0) *
			(dLat / dLon));
	    else
	    if (coord->getLongitude() <= 180.0)
		// This is a -180 negative crossing;
		end.set(-180.0, previousCoord->getLatitude() +
			(-180.0 - previousCoord->getLongitude()) *
			(dLat / dLon));
	    else
		// This is a +180 positive crossing;
		end.set(180.0, previousCoord->getLatitude() +
			(previousCoord->getLongitude() + 180.0) *
			(dLat / dLon));
	    output[currentCoord] = end;
	    project(&output[currentCoord]);
	    createEdge(currentCoord+1, output, userArg);
	    delete [] output;
	    output = new VpfCoordinate[nCoordinates - j + 2];
	    output[0].set(-end.getLongitude(), end.getLatitude());
	    project(&output[0]);
	    output[1] = *coord;
	    project(&output[1]);
	    currentCoord = 2;
	} else {
	    output[currentCoord] = *coord;
	    project(&output[currentCoord]);
	    currentCoord++;
	}
	previousCoord = coord;
    }
    createEdge(currentCoord, output, userArg);
    delete [] output;
}

// --------------------------------------------------------------------------
void
VpfReader::load(VpfArea* area, void* userArg)
{
    if (area) {
	VpfUInt nRings = area->getNRings();
	for (VpfUInt i = 0; i < nRings; i++) {
	    VpfRing* ring = area->getRing(i);
	    if (ring) {
		VpfUInt nSegments = ring->getNSegments();
		VpfUInt nCoordinates = 0;
		VpfUInt i;
		for (i = 0; i < nSegments; i++)
		    nCoordinates += ring->getSegment(i)->getNCoordinates();
		VpfCoordinate* output = new VpfCoordinate[nCoordinates];
		VpfUInt currentCoord = 0;
		for (i = 0; i < nSegments; i++) {
		    VpfSegment* segment = ring->getSegment(i);
		    VpfUInt coordsInSeg = segment->getNCoordinates();
		    for (VpfUInt j = 0; j < coordsInSeg; j++) {
			output[currentCoord] = *segment->getCoordinate(j);
			project(&output[currentCoord]);
			currentCoord++;
		    }
		}
		createFace(nCoordinates, output, userArg);
		delete [] output;
	    }
	}
    }
}

// --------------------------------------------------------------------------
void
VpfReader::load(VpfText* text, void* userArg)
{
    if (text) {
	VpfCoordinate coord = *text->getCoordinate();
	project(&coord);
	createText(coord, text->getText(), userArg);
    }
}

// --------------------------------------------------------------------------
void
VpfReader::loadFeatures(VpfCoverage* coverage, VpfSet* features,
			void** userArgs)
{
    VpfUInt nArg = 0;
    for (VpfUInt loop = 0; loop < coverage->getNFeatureClasses(); loop++) {
	if (!features->isSet(loop))
	    continue;
	VpfFeatureClass* clss = coverage->getFeatureClass(loop);
	const VpfFeatureType* type = clss->getType();
	VpfFeature* f = 0;
	if (type == VpfFeatureType::Point)
	    f = new VpfPointFeature(clss, getExtent());
	else
	if (type == VpfFeatureType::Line)
	    f = new VpfLineFeature(clss, getExtent(),
				   VpfExModeIntersects);
	else
	if (type == VpfFeatureType::Area)
	    f = new VpfAreaFeature(clss, getExtent(),
				   VpfExModeIntersects);
	else
	if (type == VpfFeatureType::Text)
	    f = new VpfTextFeature(clss, getExtent());
	if (f) {
	    int result = f->select();
	    if (!result) {
		VpfUInt n = 0;
		VpfUInt count = f->getNSelected();
		VpfFeatureItem* item = f->getNextObject();
		while (item) {
		    loadingFeature(n, count);
		    if (type == VpfFeatureType::Point)
			load((VpfPoint*)item, userArgs ? userArgs[nArg] : 0);
		    else
		    if (type == VpfFeatureType::Line)
			load((VpfSegment*)item, userArgs ? userArgs[nArg] : 0);
		    else
		    if (type == VpfFeatureType::Area)
			load((VpfArea*)item, userArgs ? userArgs[nArg] : 0);
		    else
		    if (type == VpfFeatureType::Text)
			load((VpfText*)item, userArgs ? userArgs[nArg] : 0);
		    delete item;
		    n++;
		    item = f->getNextObject();
		}
	    }
	    delete f;
	}
	nArg++;
    }
}

// --------------------------------------------------------------------------
void
VpfReader::loadThemes(VpfCoverage*, VpfUInt nThemes,
		      VpfTheme** themes, void** userArgs)
{
    for (VpfUInt loop = 0; loop < nThemes; loop++) {
	VpfFeatureClass* clss = themes[loop]->getFeatureClass();
	const VpfFeatureType* type = clss->getType();
	VpfFeature* f = 0;
	if (type == VpfFeatureType::Point)
	    f = new VpfPointFeature(clss, getExtent());
	else
	if (type == VpfFeatureType::Line)
	    f = new VpfLineFeature(clss, getExtent(),
				   VpfExModeIntersects);
	else
	if (type == VpfFeatureType::Area)
	    f = new VpfAreaFeature(clss, getExtent(),
				   VpfExModeIntersects);
	else
	if (type == VpfFeatureType::Text)
	    f = new VpfTextFeature(clss, getExtent());
	if (f) {
	    int result = f->select(themes[loop]->getAttribute(),
				   themes[loop]->getValue());
	    if (!result) {
		VpfUInt n = 0;
		VpfUInt count = f->getNSelected();
		VpfFeatureItem* item = f->getNextObject();
		while (item) {
		    loadingFeature(n, count);
		    if (type == VpfFeatureType::Point)
			load((VpfPoint*)item, userArgs ? userArgs[loop] : 0);
		    else
		    if (type == VpfFeatureType::Line)
			load((VpfSegment*)item, userArgs ? userArgs[loop] : 0);
		    else
		    if (type == VpfFeatureType::Area)
			load((VpfArea*)item, userArgs ? userArgs[loop] : 0);
		    else
		    if (type == VpfFeatureType::Text)
			load((VpfText*)item, userArgs ? userArgs[loop] : 0);
		    delete item;
		    n++;
		    item = f->getNextObject();
		}
	    }
	}
    }
}
