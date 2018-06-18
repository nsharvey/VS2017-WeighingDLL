// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/textfeature.cpp
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
// Definition of the VpfTextFeature feature class
// --------------------------------------------------------------------------

#include <vpf/feature.h>
#include <vpf/library.h>
#include <vpf/coverage.h>
#include <vpf/featureclass.h>
#include <vpf/text.h>
#include <vpf/tile.h>
#include <vpf/table.h>
#include <vpf/cursor.h>
#include <vpf/row.h>
#include <vpf/txt.h>
#include <stdio.h>

// --------------------------------------------------------------------------
VpfTextFeature::VpfTextFeature(VpfFeatureClass* featureClass,
                               const VpfExtent& extent)
: VpfFeature(featureClass, extent, VpfExModeContained),
  _textTable(0),
  _textCursor(0),
  _textRow(0)
{
}

// --------------------------------------------------------------------------
VpfTextFeature::~VpfTextFeature()
{
    if (_textRow)
	delete _textRow;
    if (_textCursor)
	delete _textCursor;
    if (_textTable)
	delete _textTable;
}

// --------------------------------------------------------------------------
VpfFeatureItem*
VpfTextFeature::getNextObject()
{
    VpfInt tileID;
    VpfInt primitiveID;
    int found = 0;
    VpfLibrary* lib = _coverage->getLibrary();
    VpfText* t = 0;

    int& index = _layerIndex;

    while (!found) {
	if (index >= _nbFeatures)
	    return 0;
	if ((getTileAndPrimId(index, tileID, primitiveID)) || (tileID < 0)) {
	    //ecs_SetError(&(s->result), 1, "The VRF tiles are badly defined");
	    return 0;
	}

	if (lib->getTile(tileID ? tileID - 1 : 0)->isSelected()) {
	    if (selectTile(tileID)) {
		// Something went wrong while selecting the tile
		return 0;
	    }
	    t = (VpfText*) getFeature(primitiveID);
	    if (!t)
		return 0;
	    if (_extent.contains(*t->getCoordinate())) {
		found = 1;
	    } else
		delete t;
	}
	index++;
    }

    return found
	? t
	: 0;
}

// --------------------------------------------------------------------------
int
VpfTextFeature::selectTile(VpfInt tileID)
{
    char buffer[256];
    const char* primitiveTableName = _class->getPrimitiveTableName();
    VpfLibrary* lib = _coverage->getLibrary();

    if (_coverage->isTiled()) {
	if (_currentTileID != tileID) {
	    if (_currentTileID != -1) {
		if (_textRow)
		    delete _textRow;
		if (_textCursor)
		    delete _textCursor;
		if (_textTable)
		    delete _textTable;
		_textTable = 0;
		_textCursor = 0;
		_textRow = 0;
	    }

	    if (tileID != 0) {
		const char* tilePath = lib->getTile(tileID - 1)->getPath();
		sprintf(buffer, "%s/%s/%s",
			_coverage->getPath(), tilePath, primitiveTableName);
	    } else {
		sprintf(buffer, "%s/%s",
			_coverage->getPath(), primitiveTableName);
	    }
	    _currentTileID = tileID;
	} else
	    return 0; // Dont't open anything
    } else {
	if (_currentTileID == -1) {
	    sprintf(buffer, "%s/%s",
		    _coverage->getPath(), primitiveTableName);
	    _currentTileID = 1;
	} else
	    return 0; // Don't open anything
    }

    _textTable = new VpfTable(buffer);
    if (!_textTable || _textTable->isBad())
	return 1;
    _textCursor = new VpfTxtCursor(_textTable);
    if (!_textCursor || _textCursor->isBad())
	return 1;
    _textRow = (VpfTxtRow*) _textCursor->getNewRow();
    if (!_textRow || _textRow->isBad())
	return 1;
    return 0;
}

// --------------------------------------------------------------------------
VpfFeatureItem*
VpfTextFeature::getFeature(int primitiveID)
{
    _textCursor->setCurrentRow(primitiveID - 1);
    if (_textCursor->getNextRow(_textRow))
	return 0;

    VpfCoordinate* c = _textRow->getShapeLine();
    VpfCoordinate* nc = c ? new VpfCoordinate(*c) : 0;
    char* t = _textRow->getTxtString();

    if (!nc || !t)
	return 0;
    return new VpfText(nc, t);
}
