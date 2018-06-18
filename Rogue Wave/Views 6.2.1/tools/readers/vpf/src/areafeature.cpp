// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/areafeature.cpp
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
// Reading an Area feature
// --------------------------------------------------------------------------

#include <vpf/feature.h>
#include <vpf/library.h>
#include <vpf/coverage.h>
#include <vpf/featureclass.h>
#include <vpf/tile.h>
#include <vpf/error.h>

#include <vpf/area.h>
#include <vpf/table.h>
#include <vpf/row.h>
#include <vpf/edg.h>
#include <vpf/rng.h>

#include <stdio.h>

// --------------------------------------------------------------------------
// FAC table management
// --------------------------------------------------------------------------
class VpfFacCursor
: public VpfCursor
{
public:
    VpfFacCursor(VpfTable* table)
    : VpfCursor(table)
    {
	static const char* Class = "VpfFacCursor::VpfFacCursor";
	VPF_IMPL_FIELD(Class, ID,       "ID",       1, I);
	VPF_IMPL_FIELD(Class, RingPtr,  "RING_PTR", 1, I);
    }
    virtual VpfRow* getNewRow();
protected:
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(RingPtr);
    friend class VpfFacRow;
};

// --------------------------------------------------------------------------
class VpfFacRow
: public VpfRow {
public:
    VpfFacRow(VpfFacCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_INTFIELD(VpfFacCursor, RingPtr);
};

// --------------------------------------------------------------------------
VpfRow*
VpfFacCursor::getNewRow()
{
    return new VpfFacRow(this);
}

// --------------------------------------------------------------------------
// VpfAreaFeature
// --------------------------------------------------------------------------
VpfAreaFeature::VpfAreaFeature(VpfFeatureClass* featureClass,
                               const VpfExtent& extent,
                               ExtentMatchMode matchMode)
: VpfFeature(featureClass, extent, matchMode),
  _faceTable(0),
  _faceCursor(0), 
  _faceRow(0), 
  _ringTable(0),
  _ringCursor(0), 
  _ringRow(0), 
  _edgeTable(0),
  _edgeCursor(0), 
  _edgeRow(0)
{
}

// --------------------------------------------------------------------------
VpfAreaFeature::~VpfAreaFeature()
{
    if (_faceRow)
	delete _faceRow;
    if (_faceCursor)
	delete _faceCursor;
    if (_faceTable)
	delete _faceTable;
    if (_ringRow)
	delete _ringRow;
    if (_ringCursor)
	delete _ringCursor;
    if (_ringTable)
	delete _ringTable;
    if (_edgeRow)
	delete _edgeRow;
    if (_edgeCursor)
	delete _edgeCursor;
    if (_edgeTable)
	delete _edgeTable;
}

// --------------------------------------------------------------------------
int
VpfAreaFeature::selectTile(VpfInt tileID)
{
    char buffer1[256];
    char buffer2[256];
    char buffer3[256];
    char buffer4[256];

    const char* primitiveTableName = _class->getPrimitiveTableName();
    VpfLibrary* lib = _coverage->getLibrary();

    if (_coverage->isTiled()) {
	if (_currentTileID != tileID) {
	    if (_currentTileID != -1) {
		if (_faceRow)
		    delete _faceRow;
		if (_faceCursor)
		    delete _faceCursor;
		if (_faceTable)
		    delete _faceTable;
		
		if (_ringRow)
		    delete _ringRow;
		if (_ringCursor)
		    delete _ringCursor;
		if (_ringTable)
		    delete _ringTable;

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

		_faceRow = 0; _faceCursor = 0; _faceTable = 0;
		_ringRow = 0; _ringCursor = 0; _ringTable = 0;
		_edgeRow = 0; _edgeCursor = 0; _edgeTable = 0;
		_fbrRow = 0;  _fbrCursor = 0;  _fbrTable = 0;
	    }
	    
	    if (tileID != 0) {
		const char* tilePath = lib->getTile(tileID - 1)->getPath();
		sprintf(buffer1, "%s/%s/fac", _coverage->getPath(), tilePath);
		sprintf(buffer2, "%s/%s/edg", _coverage->getPath(), tilePath);
		sprintf(buffer3, "%s/%s/rng", _coverage->getPath(), tilePath);
		sprintf(buffer4, "%s/%s/fbr",
			_coverage->getPath(), tilePath);
	    } else {
		sprintf(buffer1, "%s/%s",
			_coverage->getPath(), primitiveTableName);
		sprintf(buffer2, "%s/edg", _coverage->getPath());
		sprintf(buffer3, "%s/rng", _coverage->getPath());
		sprintf(buffer4, "%s/fbr", _coverage->getPath());
	    }
	    _currentTileID = tileID;
	} else
	    return 0; // don't open anything
    } else {
	if (_currentTileID == -1) {
	    sprintf(buffer1, "%s/%s",
		    _coverage->getPath(), primitiveTableName);
	    sprintf(buffer2, "%s/edg", _coverage->getPath());
	    sprintf(buffer3, "%s/rng", _coverage->getPath());
	    sprintf(buffer4, "%s/fbr", _coverage->getPath());
	    _currentTileID = 1;			
	} else
	    return 0; // don't open anything
    }
    
    _faceTable = new VpfTable(buffer1);
    if (!_faceTable || _faceTable->isBad())
	return 1;
    _faceCursor = new VpfFacCursor(_faceTable);
    if (!_faceCursor || _faceCursor->isBad())
	return 1;
    _faceRow =(VpfFacRow*)_faceCursor->getNewRow();
    if (!_faceRow || _faceRow->isBad())
	return 1;

    // Open the edge table with a level 3 topology
    // since it is not the default
    if (!(_edgeTable = new VpfTable(buffer2)) || _edgeTable->isBad() ||
	!(_edgeCursor = new VpfEdgCursor(_edgeTable, 3)) ||
	_edgeCursor->isBad() ||
	!(_edgeRow = (VpfEdgRow*)_edgeCursor->getNewRow()) ||
	_edgeRow->isBad())
	return 1;
    else
	_edgeRow->setMapped(_edgeTable->getFieldPosition("COORDINATES"), 1);

    _ringTable = new VpfTable(buffer3);
    if (!_ringTable || _ringTable->isBad())
	return 1;
    _ringCursor = new VpfRngCursor(_ringTable);
    if (!_ringCursor || _ringCursor->isBad())
	return 1;
    _ringRow = (VpfRngRow*) _ringCursor->getNewRow();
    if (!_ringRow || _ringRow->isBad())
	return 1;

    _fbrTable = new VpfTable(buffer4);
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
VpfInt
VpfAreaFeature::nextFaceEdge(VpfInt& previousNode, VpfInt faceID)
{
    VpfInt nextEdge;
    int alternative = 0;

    if (_edgeRow->getRightFace() == faceID) {
	if (_edgeRow->getLeftFace() == faceID) {
	    // Dangle
	    if (previousNode == _edgeRow->getStartNode()) {
		alternative = 1;
	    } else
	    if (previousNode == _edgeRow->getEndNode()) {
		alternative = 2;
	    }
	} else
	    // The face is on the right - take the right forward edge
	    alternative = 2;
    } else
    if (_edgeRow->getLeftFace() == faceID) {
	// The face is on the left - take the left forward edge
	alternative = 1;
    }

    switch(alternative) {
    case 1:
	_edgeRow->setDirection('-');
	nextEdge = _edgeRow->getLeftEdge();
	previousNode = _edgeRow->getStartNode();
	break;

    case 2:
	_edgeRow->setDirection('+');
	nextEdge = _edgeRow->getRightEdge();
	previousNode = _edgeRow->getEndNode();
	break;

    default:
	nextEdge = -1;
    }

    return nextEdge;
}

// --------------------------------------------------------------------------
VpfRing*
VpfAreaFeature::getRingCoords(VpfInt id, VpfInt faceID, VpfInt startEdge)
{
    static const char* Class = "VpfAreaFeature::getRingCoords";
    VpfRing* ring = 0;
    VpfSegment* segment = 0;
    VpfInt nextEdge, previousNode;
    int done = 0;
    VpfUInt nPoints = 0;
    VpfUInt n = 0;
    VpfError* error = 0;

    _edgeCursor->setCurrentRow(startEdge - 1);
    if (_edgeCursor->getNextRow(_edgeRow))
	done = 1;
    else {
	nPoints = _edgeRow->getCoordinatesCount();
	_edgeRow->setDirection('+');
	previousNode = _edgeRow->getStartNode();
	if (_edgeRow->getStartNode() == _edgeRow->getEndNode())
	    done = 1;
	nextEdge = nextFaceEdge(previousNode, faceID);
	//Allocate plenty of space for array of segment addresses 
	ring = new VpfRing(id, VPFMAXSEGS);

	// Load the first segment of the ring 
	segment = new VpfSegment(n + 1, nPoints, _edgeRow->getCoordinates());
	if (_edgeRow->getDirection() == '-')
	    segment->setInverted(1);
	ring->setSegment(n, segment);
	n++;
	while (!done) {
	    if (nextEdge <= 0)
		done = 1;
	    if (nextEdge == startEdge)
		done = 1;
	    if (n >= VPFMAXSEGS) {
		error = new VpfError(Class);
		error->getStream() << "Ring #" << id
				   << " had more than the maximal number of segments. "
				   << "You must increase the VPFMAXSEGS constant.";
		VpfErrorReporter::Add(error);
		done = 1;
	    }
	    if (!done) {
		_edgeCursor->setCurrentRow(nextEdge - 1);
		if (_edgeCursor->getNextRow(_edgeRow)) {
		    done = 1;
		} else {
		    nPoints = _edgeRow->getCoordinatesCount();
		    nextEdge = nextFaceEdge(previousNode, faceID);
		    segment = new VpfSegment(n + 1, nPoints,
					     _edgeRow->getCoordinates());
		    if (_edgeRow->getDirection() == '-')
			segment->setInverted(1);
		    ring->setSegment(n, segment);
		    n++;
		}
	    } /* if (!done) */
	} /* while (!done) */
	
	ring->resize(n);
    }
    return ring;
}

// --------------------------------------------------------------------------
VpfFeatureItem*
VpfAreaFeature::getFeature(int primitiveID)
{
    static const char* Class = "VpfAreaFeature::getFeature";
    VpfError* error = 0;
    VpfUInt n = 0;
    VpfArea* area = 0;
    VpfRing* ring;

    _faceCursor->setCurrentRow(primitiveID - 1);
    if (_faceCursor->getNextRow(_faceRow))
	return 0;

    _ringCursor->setCurrentRow(_faceRow->getRingPtr() - 1);
    if (_ringCursor->getNextRow(_ringRow))
	return 0;

    area = new VpfArea(primitiveID, VPFMAXRINGS);

    ring = getRingCoords(n + 1, primitiveID, _ringRow->getStartEdge());
    if (!ring) {
	delete area;
	return 0;
    }

    area->setRing(n, ring);
    n++;
  
    /* Get the coords for any inner rings that exist */
    while (_ringRow->getFaceID() == primitiveID) {
	if (n >= VPFMAXRINGS) {
	    error = new VpfError(Class);
	    error->getStream() << "Area #" << primitiveID
			       << " exceeds the limit of number of rings. "
			       << "You can increase the VPFMAXRINGS constant.";
	    VpfErrorReporter::Add(error);
	    break;
	}

	if (_ringCursor->getNextRow(_ringRow))
	    break;

	if (_ringRow->getFaceID() == primitiveID) {
	    ring = getRingCoords(n + 1, primitiveID,
				 _ringRow->getStartEdge());
	    if (!ring) {
		delete area;
		return 0;
	    }
	    area->setRing(n, ring);
	    n++;                        
	}
    }
    area->resize(n);
    return area;
}
