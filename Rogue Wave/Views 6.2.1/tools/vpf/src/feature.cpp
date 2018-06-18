// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/feature.cpp
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
// Definition of the VpfFeature class
// --------------------------------------------------------------------------

#include <vpf/feature.h>
#include <vpf/featureclass.h>
#include <vpf/featureitem.h>
#include <vpf/coverage.h>
#include <vpf/library.h>
#include <vpf/tile.h>
#include <vpf/string.h>
#include <vpf/table.h>
#include <vpf/cursor.h>
#include <vpf/row.h>
#include <string.h>

// --------------------------------------------------------------------------
VpfFeature::VpfFeature(VpfFeatureClass* featureClass,
                       const VpfExtent& extent,
                       VpfExtentMatchMode matchMode)
: _coverage(featureClass->getCoverage()),
  _class(featureClass),
  _matchMode(matchMode),
  _currentTileID(-1),
  _index(0),
  _nbFeatures(0),
  _layerIndex(0),
  _fbrTable(0),
  _fbrCursor(0),
  _fbrRow(0),
  _featureTable(0),
  _featureCursor(0),
  _featureRow(0),
  _joinTable(0),
  _joinCursor(0),
  _joinRow(0),
  _extent(extent)
{
    _coverage->getLibrary()->tileSelect(_extent);
}

// --------------------------------------------------------------------------
VpfFeature::~VpfFeature()
{
    if (_index)
	delete [] _index;
    if (_joinRow)
	delete _joinRow;
    if (_joinCursor)
	delete _joinCursor;
    if (_joinTable)
	delete _joinTable;
    if (_featureRow)
	delete _featureRow;
    if (_featureCursor)
	delete _featureCursor;
    if (_featureTable)
	delete _featureTable;
    if (_fbrRow)
	delete _fbrRow;
    if (_fbrCursor)
	delete _fbrCursor;
    if (_fbrTable)
	delete _fbrTable;
}

// --------------------------------------------------------------------------
int
VpfFeature::getTileAndPrimId(VpfInt featureID,
                             VpfInt& tileID,
                             VpfInt& primitiveID)
{
    VpfInt joinID;
    VpfInt pos;
    const char* joinTableForeignKeyName = _class->getJoinTableForeignKeyName();
    const char* joinTableName = _class->getJoinTableName();
    const char* featureTablePrimIdName = _class->getPrimIdName();

    if (_coverage->isTiled()) {
	if (_index[featureID].primitiveID == -1) {
	    // Positions the the cursor on the feature_id'th row
	    // that's to say the one with the ID = feature_id + 1
	    _featureCursor->setCurrentRow(featureID);
	    if (_featureCursor->getNextRow(_featureRow))
		return 1;

	    if (joinTableName) {
		if (joinTableForeignKeyName) {
		    pos = _featureTable->
			getFieldPosition(joinTableForeignKeyName);
		    if (pos != -1)
			_featureRow->getIntField(pos, joinID);
		    else {
			tileID = -1;
			primitiveID = -1;
			return 1;
		    }
		} else
		    joinID = featureID;
		_joinCursor->setCurrentRow(joinID - 1);
		if (_joinCursor->getNextRow(_joinRow))
		    return 1;

		pos = _joinTable->getFieldPosition("TILE_ID");

		if (pos != -1) {
		    _joinRow->getIntField(pos, tileID);
		} else {
		    tileID = -1;
		    primitiveID = -1;
		    return 1;
		}

		pos = _joinTable->getFieldPosition(featureTablePrimIdName);
		_joinRow->getIntField(pos, primitiveID);
	    } else {
		pos = _featureTable->getFieldPosition("TILE_ID");
		_featureRow->getIntField(pos, tileID);
		pos = _featureTable->getFieldPosition(featureTablePrimIdName);
		_featureRow->getIntField(pos, primitiveID);
	    }
	    _index[featureID].tileID = tileID;
	    _index[featureID].primitiveID = primitiveID;
	} else {
	    tileID = _index[featureID].tileID;
	    primitiveID = _index[featureID].primitiveID;
	}
    } else {
	tileID = 1;
	if (_index[featureID].primitiveID == -1) {
	    _featureCursor->setCurrentRow(featureID);
	    _featureCursor->getNextRow(_featureRow);

	    if (joinTableName) {
		if (joinTableForeignKeyName) {
		    pos = _featureTable->
			getFieldPosition(joinTableForeignKeyName);
		    if (pos != -1)
			_featureRow->getIntField(pos, joinID);
		    else {
			tileID = -1;
			primitiveID = -1;
			return 1;
		    }
		} else
		    joinID = featureID;

		_joinCursor->setCurrentRow(joinID - 1);
		if (_joinCursor->getNextRow(_joinRow))
		    return 1;

		pos = _joinTable->getFieldPosition(featureTablePrimIdName);
		_joinRow->getIntField(pos, primitiveID);
	    } else {
		pos = _featureTable->getFieldPosition(featureTablePrimIdName);
		_featureRow->getIntField(pos, primitiveID);
	    }

	    _index[featureID].primitiveID = primitiveID;
	} else
	    primitiveID = _index[featureID].primitiveID;
    }
    return 0;
}

// --------------------------------------------------------------------------
int
VpfFeature::getFeatureMBR(VpfInt rowID, VpfExtent& extent)
{
    _fbrCursor->setCurrentRow(rowID - 1);
    if (!_fbrCursor->getNextRow(_fbrRow)) {
	double xmin, xmax, ymin, ymax;
	_fbrRow->getFloatField(_fbrTable->getFieldPosition("XMIN"), xmin);
	_fbrRow->getFloatField(_fbrTable->getFieldPosition("YMIN"), ymin);
	_fbrRow->getFloatField(_fbrTable->getFieldPosition("XMAX"), xmax);
	_fbrRow->getFloatField(_fbrTable->getFieldPosition("YMAX"), ymax);
	extent.set(VpfCoordinate(xmin, ymin), VpfCoordinate(xmax, ymax));
	return 0;
    } else
	return 1;
}

// --------------------------------------------------------------------------
class CursorFriend
: public VpfCursor
{
public:
    CursorFriend(VpfTable* t) : VpfCursor(t) {}
    void setNRows(VpfUInt nRows) { _nRows = nRows; }
};

// --------------------------------------------------------------------------
int
VpfFeature::select(const char*  attribute,
		   VpfValue*	value)
{
    if (!_featureTable) {
	char* buffer;
	const char* path = _class->getPath();
	const char* table = _class->getTable();
	const char* joinTableName = _class->getJoinTableName();
	size_t ljt = joinTableName ? strlen(joinTableName) : 0;

	buffer = (strlen(table) > ljt)
	    ? new char[strlen(path) + strlen(table) + 2]
	    : new char[strlen(path) + ljt + 2];

	strcpy(buffer, path);
	strcat(buffer, "/");
	strcat(buffer, table);

	_featureTable = new VpfTable(buffer);
	_featureCursor = new VpfCursor(_featureTable);
	_featureCursor->setTrim(1);
	_featureRow = _featureCursor->getNewRow();

	if (joinTableName) {
	    strcpy(buffer, path);
	    strcat(buffer, "/");
	    strcat(buffer, joinTableName);
	    _joinTable = new VpfTable(buffer);
	    _joinCursor = new VpfCursor(_joinTable);
	    _joinRow = _joinCursor->getNewRow();
	}

	delete [] buffer;
    }
    int result = _featureCursor->query(attribute, value);
    _currentTileID = -1;
    _layerIndex = 0;
    _nbFeatures = _featureCursor->getNRows();
    if (_index)
	delete [] _index;
    _index = new VRFIndex[_nbFeatures + 1];
    for (int i = 0; i < (_nbFeatures + 1); ++i)
	_index[i].primitiveID = -1;
    return result;
}

// --------------------------------------------------------------------------
VpfFeatureItem*
VpfFeature::getNextObject()
{
    VpfInt tileID;
    VpfInt primitiveID;

    VpfExtent extent;
    VpfExtent currentExtent = _extent;

    int found = 0;
    VpfLibrary* lib = _coverage->getLibrary();
    int& index = _layerIndex;

    int reshape = 0;
    VpfFeatureItem* item = 0;

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
	    if (getFeatureMBR(primitiveID, extent)) {
		//ecs_SetError(&(s->result), 1, "VRF table mbr not open");
		return 0;
	    }
	    switch(_matchMode) {
	    case VpfExModeContained:
		if (currentExtent.contains(extent)) {
		    found = 1;
		}
		break;
	    case VpfExModeIntersects:
		if (currentExtent.intersects(extent)) {
		    found = 1;
		}
		break;
	    case VpfExModeReshape:
		if (currentExtent.contains(extent)) {
		    found = 1;
		} else
		if (currentExtent.intersects(extent)) {
		    found = 1;
		    reshape = 1;
		}
		break;
	    default:
		return 0;
	    }
	}
	index++;
    }
    if (found) {
	item = getFeature(primitiveID);
	if (reshape && item) {
	    VpfFeatureItem* reshapedItem = item->reshape(extent);
	    if (reshapedItem != item) {
		delete item;
		item = reshapedItem;
	    }
	}
    }
    return item;
}

// --------------------------------------------------------------------------
VpfUInt
VpfFeature::getNSelected() const
{
    return _featureCursor->getNRows();
}
