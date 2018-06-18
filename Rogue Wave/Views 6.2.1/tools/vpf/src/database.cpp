// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/database.cpp
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
// Definition of the VpfDatabase class
// --------------------------------------------------------------------------
#include <vpf/database.h>
#include <vpf/library.h>
#include <vpf/string.h>
#include <vpf/date.h>
#include <vpf/table.h>
#include <vpf/cursor.h>
#include <vpf/row.h>
#include <string.h>

// --------------------------------------------------------------------------
// DHT (Database Header Table) table managment
// --------------------------------------------------------------------------
class VpfDhtCursor
: public VpfCursor
{
public:
    VpfDhtCursor(VpfTable* table)
    : VpfCursor(table)
    {
	static const char* Class = "VpfDhtCursor::VpfDhtCursor";
	VPF_IMPL_FIELD(Class, ID,             "ID",             1, I);
	VPF_IMPL_FIELD(Class, Version,        "VPF_VERSION",    0, T);
	VPF_IMPL_FIELD(Class, DatabaseName,   "DATABASE_NAME",  1, T);
	VPF_IMPL_FIELD(Class, DatabaseDesc,   "DATABASE_DESC",  1, T);
	VPF_IMPL_FIELD(Class, MediaStandard,  "MEDIA_STANDARD", 1, T);
	VPF_IMPL_FIELD(Class, Originator,     "ORIGINATOR",     1, T);
	VPF_IMPL_FIELD(Class, Addressee,      "ADDRESSEE",      1, T);
	VPF_IMPL_FIELD(Class, MediaVolumes,   "MEDIA_VOLUMES",  1, T);
	VPF_IMPL_FIELD(Class, SeqNumbers,     "SEQ_NUMBERS",    1, T);
	VPF_IMPL_FIELD(Class, NumDataSets,    "NUM_DATA_SETS",  1, T);
	VPF_IMPL_FIELD(Class, SecurityClass,  "SECURITY_CLASS", 1, T);
	VPF_IMPL_FIELD(Class, Downgrading,    "DOWNGRADING",    1, T);
	VPF_IMPL_FIELD(Class, DowngradeDate,  "DOWNGRADE_DATE", 1, D);
	VPF_IMPL_FIELD(Class, Releasability,  "RELEASABILITY",  1, T);
	VPF_IMPL_FIELD(Class, OtherStdName,   "OTHER_STD_NAME", 0, T);
	VPF_IMPL_FIELD(Class, OtherStdDate,   "OTHER_STD_DATE", 0, D);
	VPF_IMPL_FIELD(Class, OtherStdVer,    "OTHER_STD_VER",  0, T);
	VPF_IMPL_FIELD(Class, TransmittalID,  "TRANSMITTAL_ID", 1, T);
	VPF_IMPL_FIELD(Class, EditionNumber,  "EDITION_NUMBER", 1, T);
	VPF_IMPL_FIELD(Class, EditionDate,    "EDITION_DATE",   1, D);
    }
    // ____________________________________________________________
    virtual VpfRow* getNewRow();
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(Version);
    VPF_DEF_FIELD(DatabaseName);
    VPF_DEF_FIELD(DatabaseDesc);
    VPF_DEF_FIELD(MediaStandard);
    VPF_DEF_FIELD(Originator);
    VPF_DEF_FIELD(Addressee);
    VPF_DEF_FIELD(MediaVolumes);
    VPF_DEF_FIELD(SeqNumbers);
    VPF_DEF_FIELD(NumDataSets);
    VPF_DEF_FIELD(SecurityClass);
    VPF_DEF_FIELD(Downgrading);
    VPF_DEF_FIELD(DowngradeDate);
    VPF_DEF_FIELD(Releasability);
    VPF_DEF_FIELD(OtherStdName);
    VPF_DEF_FIELD(OtherStdDate);
    VPF_DEF_FIELD(OtherStdVer);
    VPF_DEF_FIELD(TransmittalID);
    VPF_DEF_FIELD(EditionNumber);
    VPF_DEF_FIELD(EditionDate);
};

// --------------------------------------------------------------------------
class VpfDhtRow
: public VpfRow {
public:
    VpfDhtRow(VpfDhtCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, Version);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, DatabaseName);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, DatabaseDesc);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, MediaStandard);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, Originator);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, Addressee);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, MediaVolumes);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, SeqNumbers);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, NumDataSets);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, Downgrading);
    VPF_QUERY_DATEFIELD(VpfDhtCursor, DowngradeDate);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, Releasability);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, OtherStdName);
    VPF_QUERY_DATEFIELD(VpfDhtCursor, OtherStdDate);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, OtherStdVer);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, TransmittalID);
    VPF_QUERY_TEXTFIELD(VpfDhtCursor, EditionNumber);
    VPF_QUERY_DATEFIELD(VpfDhtCursor, EditionDate);

    char getSecurityClass() const {
	const char* ptr =
	    getText(((VpfDhtCursor*)_cursor)->VPF_FIELDNAME(SecurityClass));
	return ptr
	    ? ptr[0]
	    : '\0';
    }
};

// --------------------------------------------------------------------------
VpfRow*
VpfDhtCursor::getNewRow()
{
    return new VpfDhtRow(this);
}

// --------------------------------------------------------------------------
// LAT (Library Attribute Table) table managment
// --------------------------------------------------------------------------
class VpfLatCursor
: public VpfCursor
{
public:
    VpfLatCursor(VpfTable* table)
    : VpfCursor(table)
    {
	static const char* Class = "VpfLatCursor::VpfLatCursor";
	VPF_IMPL_FIELD(Class, ID,          "ID",           1, I);
	VPF_IMPL_FIELD(Class, LibraryName, "LIBRARY_NAME", 1, TLMN);
	VPF_IMPL_FIELD(Class, XMin,        "XMIN",         1, FR);
	VPF_IMPL_FIELD(Class, YMin,        "YMIN",         1, FR);
	VPF_IMPL_FIELD(Class, XMax,        "XMAX",         1, FR);
	VPF_IMPL_FIELD(Class, YMax,        "YMAX",         1, FR);
    }
    // ____________________________________________________________
    virtual VpfRow* getNewRow();
private:
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(LibraryName);
    VPF_DEF_FIELD(XMin);
    VPF_DEF_FIELD(YMin);
    VPF_DEF_FIELD(XMax);
    VPF_DEF_FIELD(YMax);
    friend class VpfLatRow;
};

// --------------------------------------------------------------------------
class VpfLatRow
: public VpfRow
{
public:
    VpfLatRow(VpfLatCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_TEXTFIELD(VpfLatCursor, LibraryName);
    VPF_QUERY_FLOATFIELD(VpfLatCursor, XMin);
    VPF_QUERY_FLOATFIELD(VpfLatCursor, YMin);
    VPF_QUERY_FLOATFIELD(VpfLatCursor, XMax);
    VPF_QUERY_FLOATFIELD(VpfLatCursor, YMax);
};

// --------------------------------------------------------------------------
VpfRow*
VpfLatCursor::getNewRow()
{
    return new VpfLatRow(this);
}

// --------------------------------------------------------------------------
// VpfDatabase
// --------------------------------------------------------------------------
VpfDatabase::VpfDatabase(const char* path)
: _dir(path),
  _path(path),
  _version(0),
  _name(0),
  _description(0),
  _mediaStandard(0),
  _originator(0),
  _addressee(0),
  _mediaVolumes(0),
  _sequenceNumbers(0),
  _numberOfDataSets(0),
  _securityClass('\0'),
  _downgrading(0),
  _downgradeDate(0),
  _releasability(0),
  _otherStandardName(0),
  _otherStandardDate(0),
  _otherStandardVersion(0),
  _transmittalID(0),
  _editionNumber(0),
  _editionDate(0),
  _nLibraries(0),
  _libraries(0)
{
    double xmin, ymin, xmax, ymax;

    VpfTable* latTable = 0;
    VpfLatCursor* latCursor = 0;
    VpfLatRow* latRow = 0;

    VpfTable* dhtTable;
    VpfDhtCursor* dhtCursor = 0;
    VpfDhtRow* dhtRow = 0;
    {
	VpfString dhtPath(_path);
	dhtPath += "/dht";
	dhtTable = new VpfTable(dhtPath);
	if (!dhtTable || dhtTable->isBad())
	    goto error;
    }
    dhtCursor = new VpfDhtCursor(dhtTable);
    if (!dhtCursor || dhtCursor->isBad())
	goto error;
    dhtRow = (VpfDhtRow*) dhtCursor->getNewRow();
    if (!dhtRow || dhtRow->isBad())
	goto error;
    dhtCursor->setTrim(1);

    {
	VpfString latPath(_path);
	latPath += "/lat";
	latTable = new VpfTable(latPath);
	if (!latTable || latTable->isBad())
	    goto error;
    }
    latCursor = new VpfLatCursor (latTable);
    if (!latCursor || latCursor->isBad())
	goto error;
    latRow = (VpfLatRow*) latCursor->getNewRow();
    if (!latRow || latRow->isBad())
	goto error;
    dhtCursor->setTrim(1);
    latCursor->setTrim(1);

    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(Version), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(DatabaseName), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(DatabaseDesc), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(MediaStandard), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(Originator), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(Addressee), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(Addressee), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(MediaVolumes), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(SeqNumbers), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(Downgrading), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(Releasability), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(OtherStdName), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(OtherStdVer), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(TransmittalID), 1);
    dhtRow->setMapped(dhtCursor->VPF_FIELDNAME(EditionNumber), 1);

    if (dhtCursor->getNextRow(dhtRow))
	goto error;

    _version = dhtRow->getVersion();
    _name = dhtRow->getDatabaseName();
    _description = dhtRow->getDatabaseDesc();
    _mediaStandard = dhtRow->getMediaStandard();
    _originator = dhtRow->getOriginator();
    _addressee = dhtRow->getAddressee();
    _mediaVolumes = dhtRow->getMediaVolumes();
    _sequenceNumbers = dhtRow->getSeqNumbers();
    _numberOfDataSets = dhtRow->getNumDataSets();
    _securityClass = dhtRow->getSecurityClass();
    _downgrading = dhtRow->getDowngrading();

    _downgradeDate = dhtRow->getDowngradeDate();
    if (_downgradeDate)
	_downgradeDate = new VpfDate(*_downgradeDate);

    _releasability = dhtRow->getReleasability();
    _otherStandardName = dhtRow->getOtherStdName();

    _otherStandardDate = dhtRow->getOtherStdDate();
    if (_otherStandardDate)
	_otherStandardDate = new VpfDate(*_otherStandardDate);

    _otherStandardVersion = dhtRow->getOtherStdVer();
    _transmittalID = dhtRow->getTransmittalID();
    _editionNumber = dhtRow->getEditionNumber();

    _editionDate = dhtRow->getEditionDate();
    if (_editionDate)
	_editionDate = new VpfDate(*_editionDate);

    delete dhtRow; dhtRow = 0;
    delete dhtCursor; dhtCursor = 0;
    delete dhtTable; dhtTable = 0;

    // LAT: Library attribute table

    _nLibraries = latCursor->getNRows();

    _libraries = new VpfLibrary*[_nLibraries];
    if (!_libraries)
	goto error;

    VpfUInt i;
    for (i = 0; i < _nLibraries; i++)
	_libraries[i] = 0;

    for (i = 0; i < _nLibraries; i++) {
	if (latCursor->getNextRow(latRow))
	    goto error;
	const char* libraryName = latRow->getLibraryName();
	xmin = latRow->getXMin();
	ymin = latRow->getYMin();
	xmax = latRow->getXMax();
	ymax = latRow->getYMax();

	_libraries[i] = new VpfLibrary(this,
				       libraryName,
				       VpfExtent(VpfCoordinate(xmin, ymin),
						 VpfCoordinate(xmax, ymax)));
	if (!_libraries[i] || _libraries[i]->isBad()) {
	    if (_libraries[i]) delete _libraries[i];
	    _libraries[i] = 0;
	}
    }

    delete latRow;
    delete latCursor;
    delete latTable;

    return;

error:
    if (dhtRow)
	delete dhtRow;
    if (dhtCursor)
	delete dhtCursor;
    if (dhtTable)
	delete dhtTable;

    if (latRow)
	delete latRow;
    if (latCursor)
	delete latCursor;
    if (latTable)
	delete latTable;

    setBad();
}

// --------------------------------------------------------------------------
VpfDatabase::~VpfDatabase()
{
  if (_version)
      delete [] _version;
  if (_name)
      delete [] _name;
  if (_description)
      delete [] _description;
  if (_mediaStandard)
      delete [] _mediaStandard;
  if (_originator)
      delete [] _originator;
  if (_addressee)
      delete [] _addressee;
  if (_mediaVolumes)
      delete [] _mediaVolumes;
  if (_sequenceNumbers)
      delete [] _sequenceNumbers;
  if (_numberOfDataSets)
      delete [] _numberOfDataSets;
  if (_downgrading)
      delete [] _downgrading;
  if (_downgradeDate)
      delete _downgradeDate;
  if (_releasability)
      delete [] _releasability;
  if (_otherStandardName)
      delete [] _otherStandardName;
  if (_otherStandardDate)
      delete _otherStandardDate;
  if (_otherStandardVersion)
      delete [] _otherStandardVersion;
  if (_transmittalID)
      delete [] _transmittalID;
  if (_editionNumber)
      delete [] _editionNumber;
  if (_editionDate)
      delete _editionDate;

  if (_libraries) {
      for (VpfUInt i = 0; i < _nLibraries; i++)
	  if (_libraries[i])
	      delete _libraries[i];
      delete [] _libraries;
  }
}

// --------------------------------------------------------------------------
VpfLibrary*
VpfDatabase::getLibrary(const char* name) const
{
    for (VpfUInt i = 0; i < _nLibraries; i++)
	if (!strcmp(_libraries[i]->getName(), name))
	    return _libraries[i];
    return 0;
}
