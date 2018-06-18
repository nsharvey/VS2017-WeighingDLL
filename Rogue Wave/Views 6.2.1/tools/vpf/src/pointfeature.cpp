// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/pointfeature.cpp
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
// Definition of the VpfPointFeature class
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
#include <stdio.h>

// --------------------------------------------------------------------------
// CND table management
// --------------------------------------------------------------------------
class VpfCndCursor
: public VpfCursor
{
public:
    VpfCndCursor(VpfTable* table, VpfUInt topo = 0)
    : VpfCursor(table)
    {
	static const char* Class = "VpfCndCursor::VpfCndCursor";
	VPF_IMPL_FIELD(Class, ID,            "ID",         1, I);
	VPF_IMPL_FIELD(Class, FirstEdge,     "FIRST_EDGE", topo >= 1, IKX);
	VPF_IMPL_FIELD(Class, CndCoordinate, "COORDINATE", 1, BCYZ);
    }
    // ____________________________________________________________
    virtual VpfRow* getNewRow();
protected:
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(FirstEdge);
    VPF_DEF_FIELD(CndCoordinate);
    friend class VpfCndRow;
};

// --------------------------------------------------------------------------
class VpfCndRow
: public VpfRow {
public:
    VpfCndRow(VpfCndCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_COORDFIELD(VpfCndCursor, CndCoordinate);
    VpfInt getFirstEdge() const;
};

// --------------------------------------------------------------------------
VpfRow*
VpfCndCursor::getNewRow()
{
    return new VpfCndRow(this);
}

// --------------------------------------------------------------------------
VpfInt
VpfCndRow::getFirstEdge() const
{
    VpfInt fre = ((VpfCndCursor*)_cursor)->_fieldFirstEdge;
    return (_cursor->getHeader(fre)->getType() == 'K')
	? getTripletIDPart(fre, 0)
	: getInt(fre);
}

// --------------------------------------------------------------------------
// VpfPointFeature
// --------------------------------------------------------------------------
VpfPointFeature::VpfPointFeature(VpfFeatureClass* featureClass,
                                 const VpfExtent& extent)
: VpfFeature(featureClass, extent, VpfExModeContained),
  _pointTable(0),
  _pointCursor(0),
  _pointRow(0)
{
}

// --------------------------------------------------------------------------
VpfPointFeature::~VpfPointFeature()
{
    if (_pointRow)
	delete _pointRow;
    if (_pointCursor)
	delete _pointCursor;
    if (_pointTable)
	delete _pointTable;
}

// --------------------------------------------------------------------------
VpfFeatureItem*
VpfPointFeature::getNextObject()
{
    VpfInt tileID;
    VpfInt primitiveID;

    int found = 0;
    VpfLibrary* lib = _coverage->getLibrary();
    VpfPoint* t = 0;

    int& index = _layerIndex;

    while(!found) {
	if (index >= _nbFeatures)
	    return 0;

	if ((getTileAndPrimId(index, tileID, primitiveID)) || (tileID < 0)) {
	    //ecs_SetError(&(s->result), 1, "The VRF tiles are badly defined");
	    return 0;
	}

	if (lib->getTile(tileID
			 ? (tileID - 1)
			 : 0)->isSelected()) {
	    if (selectTile(tileID)) {
		// Something went wrong while selecting the tile
		return 0;
	    }
	    t = (VpfPoint*)getFeature(primitiveID);
	    if (!t)
		// Something went wrong while reading the primitive
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
VpfPointFeature::selectTile(VpfInt tileID)
{
    char buffer[256];
    const char* primitiveTableName = _class->getPrimitiveTableName();
    VpfLibrary* lib = _coverage->getLibrary();

    if (_coverage->isTiled()) {
	if (_currentTileID != tileID) {
	    if (_currentTileID != -1) {
		if (_pointRow)
		    delete _pointRow;
		if (_pointCursor)
		    delete _pointCursor;
		if (_pointTable)
		    delete _pointTable;
		_pointTable = 0;
		_pointCursor = 0;
		_pointRow = 0;
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
	    sprintf(buffer, "%s/%s", _coverage->getPath(), primitiveTableName);
	    _currentTileID = 1;
	}	else
	    return 0; // Don't open anything
    }

    _pointTable = new VpfTable(buffer);
    if (!_pointTable || _pointTable->isBad())
	return 1;

    _pointCursor = new VpfCndCursor(_pointTable);
    if (!_pointCursor || _pointCursor->isBad())
	return 1;

    _pointRow = (VpfCndRow*) _pointCursor->getNewRow();
    if (!_pointRow || _pointRow->isBad())
	return 1;

    return 0;
}

// --------------------------------------------------------------------------
VpfFeatureItem*
VpfPointFeature::getFeature(VpfInt primitiveID)
{
    _pointCursor->setCurrentRow(primitiveID - 1);
    if (_pointCursor->getNextRow(_pointRow))
	return 0;

    VpfCoordinate* c = _pointRow->getCndCoordinate();
    VpfCoordinate* nc = c
	? new VpfCoordinate(*c)
	: 0;
    if (!c || !nc)
	return 0;
    return new VpfPoint(nc);
}
