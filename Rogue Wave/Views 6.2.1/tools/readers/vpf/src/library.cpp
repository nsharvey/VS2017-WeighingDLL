// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/library.cpp
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
// Definition of the VpfLibrary class
// --------------------------------------------------------------------------

#include <vpf/database.h>
#include <vpf/library.h>
#include <vpf/coverage.h>
#include <vpf/tile.h>
#include <vpf/string.h>
#include <vpf/extent.h>
#include <vpf/date.h>
#include <vpf/table.h>
#include <vpf/row.h>
#include <vpf/cursor.h>

#include <vpf/error.h>

#include <string.h>

// --------------------------------------------------------------------------
// AFT table management
// --------------------------------------------------------------------------
class VpfAftCursor
: public VpfCursor
{
public:
    VpfAftCursor(VpfTable* table)
    : VpfCursor(table)
    {
	static const char* Class = "VpfAftCursor::VpfAftCursor";
	VPF_IMPL_FIELD(Class, ID,       "ID",        1, I);
	VPF_IMPL_FIELD(Class, TileName, "TILE_NAME", 1, T);
	VPF_IMPL_FIELD(Class, FacID,    "FAC_ID",    0, ISK);

	// use ID when FAC_ID is undefined.
	if(VPF_FIELDNAME(FacID) == -1)
	    VPF_FIELDNAME(FacID) = VPF_FIELDNAME(ID);
	
    }
    // ____________________________________________________________
    virtual VpfRow* getNewRow();
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(TileName);
    VPF_DEF_FIELD(FacID);
};

// --------------------------------------------------------------------------
class VpfAftRow
: public VpfRow {
public:
    VpfAftRow(VpfAftCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_TEXTFIELD(VpfAftCursor, TileName);
    VpfInt getFacID() const
    {
	VpfInt fac = ((VpfAftCursor*)_cursor)->VPF_FIELDNAME(FacID);
	VpfInt retInt;
	if (_cursor->getHeader(fac)->getType() == 'K') {
	    retInt = getTripletIDPart(fac, 0);
	} else 
	    retInt = getInt(fac);
	return retInt;
    }
};

// --------------------------------------------------------------------------
VpfRow*
VpfAftCursor::getNewRow()
{
    return new VpfAftRow(this);
}

// --------------------------------------------------------------------------
// CAT table management
// --------------------------------------------------------------------------
class VpfCatCursor
: public VpfCursor
{
public:
    VpfCatCursor(VpfTable* table)
    : VpfCursor(table)
    {
	static const char* Class = "VpfCatCursor::VpfCatCursor";
	VPF_IMPL_FIELD(Class, ID,           "ID",            1, I);
	VPF_IMPL_FIELD(Class, CoverageName, "COVERAGE_NAME", 1, T);
	VPF_IMPL_FIELD(Class, Description,  "DESCRIPTION",   1, T);
	VPF_IMPL_FIELD(Class, Level,        "LEVEL",         1, IS);
    }
    // ____________________________________________________________
    virtual VpfRow* getNewRow();
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(CoverageName);
    VPF_DEF_FIELD(Description);
    VPF_DEF_FIELD(Level);
};

// --------------------------------------------------------------------------
class VpfCatRow
: public VpfRow {
public:
    VpfCatRow(VpfCatCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_TEXTFIELD(VpfCatCursor, CoverageName);
    VPF_QUERY_TEXTFIELD(VpfCatCursor, Description);
    VPF_QUERY_INTFIELD(VpfCatCursor, Level);
};

// --------------------------------------------------------------------------
VpfRow*
VpfCatCursor::getNewRow()
{
    return new VpfCatRow(this);
}

// --------------------------------------------------------------------------
// FBR (Face Bounding Rectangle) table management
// --------------------------------------------------------------------------
class VpfFbrCursor
: public VpfCursor
{
public:
    VpfFbrCursor(VpfTable* table)
    : VpfCursor(table)
    {
	static const char* Class = "VpfFbrCursor::VpfFbrCursor";
	VPF_IMPL_FIELD(Class, ID,   "ID",   1, I);
	VPF_IMPL_FIELD(Class, XMin, "XMIN", 1, FR);
	VPF_IMPL_FIELD(Class, YMin, "YMIN", 1, FR);
	VPF_IMPL_FIELD(Class, XMax, "XMAX", 1, FR);
	VPF_IMPL_FIELD(Class, YMax, "YMAX", 1, FR);
    }
    virtual VpfRow* getNewRow();
private:
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(XMin);
    VPF_DEF_FIELD(YMin);
    VPF_DEF_FIELD(XMax);
    VPF_DEF_FIELD(YMax);
    friend class VpfFbrRow;
};

// --------------------------------------------------------------------------
class VpfFbrRow
: public VpfRow
{
public:
    VpfFbrRow(VpfFbrCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_FLOATFIELD(VpfFbrCursor, XMin);
    VPF_QUERY_FLOATFIELD(VpfFbrCursor, YMin);
    VPF_QUERY_FLOATFIELD(VpfFbrCursor, XMax);
    VPF_QUERY_FLOATFIELD(VpfFbrCursor, YMax);
};

// --------------------------------------------------------------------------
VpfRow*
VpfFbrCursor::getNewRow()
{
    return new VpfFbrRow(this);
}

// --------------------------------------------------------------------------
// LHT (Library Header Table) table management
// --------------------------------------------------------------------------
class VpfLhtCursor
: public VpfCursor
{
public:
    VpfLhtCursor(VpfTable* table)
    : VpfCursor(table)
    {
	static const char* Class = "VpfLhtCursor::VpfLhtCursor";
	VPF_IMPL_FIELD(Class, ID,             "ID",               1, I);
	VPF_IMPL_FIELD(Class, ProductType,    "PRODUCT_TYPE",     1, T);
	VPF_IMPL_FIELD(Class, LibraryName,    "LIBRARY_NAME",     1, T);
	VPF_IMPL_FIELD(Class, Description,    "DESCRIPTION",      1, T);
	VPF_IMPL_FIELD(Class, DataStructCode, "DATA_STRUCT_CODE", 1, T);
	VPF_IMPL_FIELD(Class, Scale,          "SCALE",            1, I);
	VPF_IMPL_FIELD(Class, SourceSeries,   "SOURCE_SERIES",    1, T);
	VPF_IMPL_FIELD(Class, SourceID,       "SOURCE_ID",        1, T);
	VPF_IMPL_FIELD(Class, SourceEdition,  "SOURCE_EDITION",   1, T);
	VPF_IMPL_FIELD(Class, SourceName,     "SOURCE_NAME",      1, T);
	VPF_IMPL_FIELD(Class, SourceDate,     "SOURCE_DATE",      1, D);
	VPF_IMPL_FIELD(Class, SecurityClass,  "SECURITY_CLASS",   1, T);
	VPF_IMPL_FIELD(Class, Downgrading,    "DOWNGRADING",      1, T);
	VPF_IMPL_FIELD(Class, DowngradeDate,  "DOWNGRADING_DATE", 1, D);
	VPF_IMPL_FIELD(Class, Releasability,  "RELEASABILITY",    1, T);
    }
    // ____________________________________________________________
    virtual VpfRow* getNewRow();
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(ProductType);
    VPF_DEF_FIELD(LibraryName);
    VPF_DEF_FIELD(Description);
    VPF_DEF_FIELD(DataStructCode);
    VPF_DEF_FIELD(Scale);
    VPF_DEF_FIELD(SourceSeries);
    VPF_DEF_FIELD(SourceID);
    VPF_DEF_FIELD(SourceEdition);
    VPF_DEF_FIELD(SourceName);
    VPF_DEF_FIELD(SourceDate);
    VPF_DEF_FIELD(SecurityClass);
    VPF_DEF_FIELD(Downgrading);
    VPF_DEF_FIELD(DowngradeDate);
    VPF_DEF_FIELD(Releasability);
};

// --------------------------------------------------------------------------
class VpfLhtRow
: public VpfRow {
public:
    VpfLhtRow(VpfLhtCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_TEXTFIELD(VpfLhtCursor, ProductType);
    VPF_QUERY_TEXTFIELD(VpfLhtCursor, LibraryName);
    VPF_QUERY_TEXTFIELD(VpfLhtCursor, Description);
    VPF_QUERY_INTFIELD(VpfLhtCursor, Scale);
    VPF_QUERY_TEXTFIELD(VpfLhtCursor, SourceSeries);
    VPF_QUERY_TEXTFIELD(VpfLhtCursor, SourceID);
    VPF_QUERY_TEXTFIELD(VpfLhtCursor, SourceEdition);
    VPF_QUERY_TEXTFIELD(VpfLhtCursor, SourceName);
    VPF_QUERY_DATEFIELD(VpfLhtCursor, SourceDate);
    VPF_QUERY_TEXTFIELD(VpfLhtCursor, Downgrading);
    VPF_QUERY_DATEFIELD(VpfLhtCursor, DowngradeDate);
    VPF_QUERY_TEXTFIELD(VpfLhtCursor, Releasability);
    char getDataStructCode() const {
	const char* ptr =
	    getText(((VpfLhtCursor*)_cursor)->VPF_FIELDNAME(DataStructCode));
	return ptr
	    ? ptr[0]
	    : '\0';
    }
    char getSecurityClass() const {
	const char* ptr =
	    getText(((VpfLhtCursor*)_cursor)->VPF_FIELDNAME(SecurityClass));
	return ptr
	    ? ptr[0]
	    : '\0';
    }
};

// --------------------------------------------------------------------------
VpfRow*
VpfLhtCursor::getNewRow()
{
    return new VpfLhtRow(this);
}

// --------------------------------------------------------------------------
// VpfLibrary
// --------------------------------------------------------------------------
VpfLibrary::VpfLibrary(VpfDatabase* database,
                       const char* name,
                       const VpfExtent& extent)
: _database(database),
  _dir(database->getPath()),
  _path(_dir),
  _extent(extent),
  _productType(0),
  _name(0),
  _description(0),
  _dataStructCode(0),
  _scale(0),
  _sourceSeries(0),
  _sourceID(0),
  _sourceEdition(0),
  _sourceName(0),
  _sourceDate(0),
  _securityClass(0),
  _downgrading(0),
  _downgradeDate(0),
  _releasability(0),
  _isTiled(0),
  _nTiles(0),
  _tiles(0),
  _nCoverages(0),
  _coverages(0)
{
    VpfTable* lhtTable = 0;
    VpfLhtCursor* lhtCursor = 0;
    VpfLhtRow* lhtRow = 0;

    VpfTable* catTable = 0;
    VpfCatCursor* catCursor = 0;
    VpfCatRow* catRow = 0;

    VpfUInt i = 0;

    char* coverageName = 0;
    char* coverageDescription = 0;
    int coverageLevel = 0;

    _path += '/';
    _path += name;

    VpfString lhtPath(_path);
    lhtPath += "/lht";
    VpfString catPath(_path);
    catPath += "/cat";

    lhtTable = new VpfTable(lhtPath);
    if (!lhtTable || lhtTable->isBad())
	goto error;

    lhtCursor = new VpfLhtCursor(lhtTable);
    if (!lhtCursor || lhtCursor->isBad())
	goto error;

    lhtRow = (VpfLhtRow*) lhtCursor->getNewRow();
    if (!lhtRow || lhtRow->isBad())
	goto error;

    catTable = new VpfTable(catPath);
    if (!catTable || catTable->isBad())
	goto error;

    catCursor = new VpfCatCursor (catTable);
    if (!catCursor || catCursor->isBad())
	goto error;

    catRow = (VpfCatRow*) catCursor->getNewRow();
    if (!catRow || catRow->isBad())
	goto error;
 
    lhtCursor->setTrim(1);
    catCursor->setTrim(1);

    lhtRow->setMapped(lhtCursor->VPF_FIELDNAME(ProductType), 1);
    lhtRow->setMapped(lhtCursor->VPF_FIELDNAME(LibraryName), 1);
    lhtRow->setMapped(lhtCursor->VPF_FIELDNAME(Description), 1);
    lhtRow->setMapped(lhtCursor->VPF_FIELDNAME(SourceSeries), 1);
    lhtRow->setMapped(lhtCursor->VPF_FIELDNAME(SourceID), 1);
    lhtRow->setMapped(lhtCursor->VPF_FIELDNAME(SourceEdition), 1);
    lhtRow->setMapped(lhtCursor->VPF_FIELDNAME(SourceName), 1);
    lhtRow->setMapped(lhtCursor->VPF_FIELDNAME(Downgrading), 1);
    lhtRow->setMapped(lhtCursor->VPF_FIELDNAME(Releasability), 1);

    if (lhtCursor->getNextRow(lhtRow)) goto error;

    _productType = lhtRow->getProductType();
    _name = lhtRow->getLibraryName();
    _description = lhtRow->getDescription();
    _sourceSeries = lhtRow->getSourceSeries();
    _sourceID = lhtRow->getSourceID();
    _sourceEdition = lhtRow->getSourceEdition();
    _sourceName = lhtRow->getSourceName();

    _sourceDate = lhtRow->getSourceDate();
    if (_sourceDate)
	_sourceDate = new VpfDate(*_sourceDate);

    _securityClass = lhtRow->getSecurityClass();
    _downgrading = lhtRow->getDowngrading();

    _downgradeDate = lhtRow->getDowngradeDate();
    if (_downgradeDate)
	_downgradeDate = new VpfDate(*_downgradeDate);

    _releasability = lhtRow->getReleasability();

    delete lhtRow;
    lhtRow = 0;
    delete lhtCursor;
    lhtCursor = 0;
    delete lhtTable;
    lhtTable = 0;

    // CAT: Coverage attribute table

    _nCoverages = catCursor->getNRows();

    _coverages = new VpfCoverage*[_nCoverages];
    if (!_coverages)
	goto error;

    for (i = 0; i < _nCoverages; i++)
	_coverages[i] = 0;

    for (i = 0; i < _nCoverages; i++) {
	if (catCursor->getNextRow(catRow))
	    goto error;

	coverageName = catRow->getCoverageName();
	coverageDescription = catRow->getDescription();
	coverageLevel = catRow->getLevel();

	_coverages[i] = new VpfCoverage(this,
					coverageName,
					coverageDescription,
					coverageLevel);
	if (!_coverages[i] || _coverages[i]->isBad()) {
	    if (_coverages[i])
		delete _coverages[i];
	    _coverages[i] = 0;
	}
    }

    delete catRow;
    catRow = 0;
    delete catCursor;
    catCursor = 0;
    delete catTable;
    catTable = 0;

    if (initTiling())
	setBad();

    return;

error:
    if (lhtRow)
	delete lhtRow;
    if (lhtCursor)
	delete lhtCursor;
    if (lhtTable)
	delete lhtTable;

    if (catRow)
	delete catRow;
    if (catCursor)
	delete catCursor;
    if (catTable)
	delete catTable;

    setBad();
}

// --------------------------------------------------------------------------
VpfLibrary::~VpfLibrary()
{
    if (_productType)
	delete [] _productType;
    if (_name)
	delete [] _name;
    if (_description)
	delete [] _description;
    if (_sourceSeries)
	delete [] _sourceSeries;
    if (_sourceID)
	delete [] _sourceID;
    if (_sourceEdition)
	delete [] _sourceEdition;
    if (_sourceName)
	delete [] _sourceName;
    if (_sourceDate)
	delete _sourceDate;
    if (_downgrading)
	delete [] _downgrading;
    if (_downgradeDate)
	delete _downgradeDate;
    if (_releasability)
	delete [] _releasability;

    if (_coverages) {
	for (VpfUInt i = 0; i < _nCoverages; i++)
	    if (_coverages[i])
		delete _coverages[i];
	delete [] _coverages;
    }

    if (_tiles) {
	for (VpfUInt i = 0; i < _nTiles; i++)
	    if (_tiles[i])
		delete _tiles[i];
	delete [] _tiles;
    }
}

// --------------------------------------------------------------------------
static int
InitTilingExit(VpfTable*	aftTable,
	       VpfAftCursor*	aftCursor = 0,
	       VpfAftRow*	aftRow    = 0,
	       VpfTable*	fbrTable  = 0,
	       VpfFbrCursor*	fbrCursor = 0,
	       VpfFbrRow*	fbrRow    = 0,
	       int		code	  = 1)
{
    delete fbrRow;
    delete fbrCursor;
    delete fbrTable;
    delete aftRow;
    delete aftCursor;
    delete aftTable;
    return code;
}

// --------------------------------------------------------------------------
int
VpfLibrary::initTiling()
{
    VpfTable* aftTable = 0;
    {
	VpfString aftPath(_path);
	aftPath += "/tileref/tileref.aft";
	VpfErrorReporter::Push();
	aftTable = new VpfTable(aftPath);
	VpfErrorReporter::Pop();
    }
    if (!aftTable || aftTable->isBad()) {
	delete aftTable;
	_isTiled = 0;
	_nTiles = 1;
	_tiles = new VpfTile*[1];
	_tiles[0] = new VpfTile((char*)"", _extent, 1);
	return 0;
    }
    VpfAftCursor* aftCursor = new VpfAftCursor(aftTable);
    if (!aftCursor || aftCursor->isBad())
	return InitTilingExit(aftTable, aftCursor);
    VpfAftRow* aftRow = (VpfAftRow*)aftCursor->getNewRow();
    if (!aftRow || aftRow->isBad())
	return InitTilingExit(aftTable, aftCursor, aftRow);
    aftCursor->setTrim(1);

    _isTiled = 1;
    _nTiles = aftCursor->getNRows();
    _tiles = _nTiles
	? new VpfTile*[_nTiles]
	: 0;
    if (!_tiles)
	return InitTilingExit(aftTable, aftCursor, aftRow);
    VpfUInt i;
    for (i = 0; i < _nTiles; i++)
	_tiles[i] = 0;
  
    // FBR: Face bounding rectangle
    VpfTable* fbrTable = 0;
    {
	VpfString fbrPath(_path);
	fbrPath += "/tileref/fbr";
	fbrTable = new VpfTable(fbrPath);
	if (!fbrTable || fbrTable->isBad())
	    return InitTilingExit(aftTable, aftCursor, aftRow,
				  fbrTable);
    }
    VpfFbrCursor* fbrCursor = new VpfFbrCursor(fbrTable);
    if (!fbrCursor || fbrCursor->isBad())
	return InitTilingExit(aftTable, aftCursor, aftRow,
			      fbrTable, fbrCursor);
    VpfFbrRow* fbrRow = (VpfFbrRow*)fbrCursor->getNewRow();
    if (!fbrRow || fbrRow->isBad())
	return InitTilingExit(aftTable, aftCursor, aftRow,
			      fbrTable, fbrCursor, fbrRow);
    fbrCursor->setTrim(1);

    for (i = 0; i < _nTiles; i++) {
	if (aftCursor->getNextRow(aftRow))
	    return InitTilingExit(aftTable, aftCursor, aftRow,
				  fbrTable, fbrCursor, fbrRow);
	VpfInt facID = aftRow->getFacID();
	fbrCursor->setCurrentRow(facID - 1);
	if (fbrCursor->getNextRow(fbrRow))
	    return InitTilingExit(aftTable, aftCursor, aftRow,
				  fbrTable, fbrCursor, fbrRow);
	_tiles[i] = new VpfTile(aftRow->getTileName(),
				VpfExtent(VpfCoordinate(fbrRow->getXMin(),
							fbrRow->getYMin()),
					  VpfCoordinate(fbrRow->getXMax(),
							fbrRow->getYMax())),
				0);
	if (!_tiles[i])
	    return InitTilingExit(aftTable, aftCursor, aftRow,
				  fbrTable, fbrCursor, fbrRow);
	_tiles[i]->setSelected(1);
    }
    return InitTilingExit(aftTable, aftCursor, aftRow,
			  fbrTable, fbrCursor, fbrRow,
			  0);
}


// --------------------------------------------------------------------------
void
VpfLibrary::tileSelect(const VpfExtent& extent)
{
    if (!_isTiled)
	return;
    for (VpfUInt i = 0; i < _nTiles; ++i)
	_tiles[i]->setSelected(extent.intersects(_tiles[i]->getExtent())
			       ? 1
			       : 0);
}

// --------------------------------------------------------------------------
VpfCoverage*
VpfLibrary::getCoverage(const char* name) const
{
    for (VpfUInt i = 0; i < _nCoverages; i++)
	if (!strcmp(_coverages[i]->getName(), name))
	    return _coverages[i];
    return 0;
}
