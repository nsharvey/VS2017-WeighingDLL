// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/linefeature.cpp
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
// Definition of the VpfLineFeature class
// --------------------------------------------------------------------------

#include <vpf/feature.h>
#include <vpf/library.h>
#include <vpf/coverage.h>
#include <vpf/featureclass.h>
#include <vpf/tile.h>
#include <vpf/table.h>
#include <vpf/cursor.h>
#include <vpf/row.h>
#include <vpf/edg.h>
#include <vpf/segment.h>
#include <stdio.h>

// --------------------------------------------------------------------------
VpfLineFeature::VpfLineFeature(VpfFeatureClass* featureClass,
                               const VpfExtent& extent,
                               VpfExtentMatchMode matchMode)
: VpfFeature(featureClass, extent, matchMode),
  _edgeTable(0),
  _edgeCursor(0),
  _edgeRow(0)
{
}

// --------------------------------------------------------------------------
VpfLineFeature::~VpfLineFeature()
{
    if (_edgeRow)
	delete _edgeRow;
    if (_edgeCursor)
	delete _edgeCursor;
    if (_edgeTable)
	delete _edgeTable;
}

// --------------------------------------------------------------------------
int
VpfLineFeature::selectTile(VpfInt tileID)
{
    char buffer1[256];
    char buffer2[256];
    const char* primitiveTableName = _class->getPrimitiveTableName();
    VpfLibrary* lib = _coverage->getLibrary();

    if (_coverage->isTiled()) {
	if (_currentTileID != tileID) {
	    if (_currentTileID != -1) {
		if (_edgeRow)
		    delete _edgeRow;
		if (_edgeCursor)
		    delete _edgeCursor;
		if (_edgeTable)
		    delete _edgeTable;

		if (_fbrRow)
		    delete _fbrRow;
		if (_fbrCursor)
		    delete _fbrCursor;
		if (_fbrTable)
		    delete _fbrTable;

		_edgeRow = 0;
		_edgeCursor = 0;
		_edgeTable = 0;
		_fbrRow = 0;
		_fbrCursor = 0;
		_fbrTable = 0;
	    }

	    if (tileID != 0) {
		const char* tilePath = lib->getTile(tileID - 1)->getPath();
		sprintf(buffer1, "%s/%s/%s",
			_coverage->getPath(), tilePath, primitiveTableName);
		sprintf(buffer2, "%s/%s/ebr",
			_coverage->getPath(), tilePath);
	    } else {
		sprintf(buffer1, "%s/%s",
			_coverage->getPath(), primitiveTableName);
		sprintf(buffer2, "%s/ebr", _coverage->getPath());
	    }
	    _currentTileID = tileID;
	} else
	    return 0; // Don't open anything
    } else {
    if (_currentTileID == -1) {
	sprintf(buffer1, "%s/%s",
		_coverage->getPath(), primitiveTableName);
	sprintf(buffer2, "%s/ebr",
		_coverage->getPath());
	_currentTileID = 1;
    } else
	return 0; // Don't open anything
    }
    _edgeTable = new VpfTable(buffer1);
    if (!_edgeTable || _edgeTable->isBad())
	return 1;

    _edgeCursor = new VpfEdgCursor(_edgeTable);
    if (!_edgeCursor || _edgeCursor->isBad())
	return 1;

    _edgeRow = (VpfEdgRow*) _edgeCursor->getNewRow();
    if (!_edgeRow || _edgeRow->isBad())
	return 1;
    else
	_edgeRow->setMapped(_edgeTable->getFieldPosition("COORDINATES"), 1);

    _fbrTable = new VpfTable(buffer2);
    if (!_fbrTable || _fbrTable->isBad())
	return 1;

    _fbrCursor = new VpfCursor(_fbrTable);
    if (!_fbrCursor || _fbrCursor->isBad())
	return 1;

    _fbrRow = _fbrCursor->getNewRow();
    if (!_fbrRow || _fbrRow->isBad())
	return 1;
    return 0;
}

// --------------------------------------------------------------------------
VpfFeatureItem*
VpfLineFeature::getFeature(int primitiveID)
{
    _edgeCursor->setCurrentRow(primitiveID - 1);
    if (!_edgeCursor->getNextRow(_edgeRow)) {
	VpfUInt nPoints = _edgeRow->getCoordinatesCount();
	return new VpfSegment(primitiveID, nPoints,
			      _edgeRow->getCoordinates());
    }
    return 0;
}
