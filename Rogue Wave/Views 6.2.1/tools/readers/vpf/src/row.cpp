// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/row.cpp
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
// Definition of the VpfRow class
// --------------------------------------------------------------------------

#include <vpf/row.h>
#include <vpf/cursor.h>
#include <vpf/header.h>
#include <vpf/file.h>
#include <vpf/date.h>
#include <vpf/string.h>
#include <vpf/tripletid.h>
#include <vpf/table.h>
#include <vpf/error.h>
#include <vpf/coordinate.h>
#include <string.h>

// --------------------------------------------------------------------------
VpfRow::VpfRow(VpfCursor* cursor)
: _cursor(cursor),
  _nFields(0),
  _fields(0),
  _counts(0),
  _mapped(0),
  _number(0)
{
    if (cursor) {
	_nFields = _cursor->getNFields();
	_fields = new Field[_nFields];
	_counts = new VpfUInt[_nFields];
	_mapped = new int[_nFields];
	clear();
    } else {
	VpfError* error = new VpfError("VpfRow::VpfRow");
	error->getStream() << "Row initialized with null cursor.";
	VpfErrorReporter::Add(error);
	setBad();
    }
}

// --------------------------------------------------------------------------
VpfRow::~VpfRow()
{
    if (_fields) {
	free();
	delete [] _fields;
    }
    if (_counts)
	delete [] _counts;
    if (_mapped)
	delete [] _mapped;
}

// --------------------------------------------------------------------------
int
VpfRow::read(VpfUInt number, VpfFile* file)
{
    _number = number;
    VpfError* error = 0;
    int returnCode = 0;
    free();

    for (VpfUInt i = 0; i < _nFields; i++) {
	VpfHeader* header = _cursor->getHeader(i);
	char type = header->getType();
	VpfInt count = header->getCount();
	if (count < 0)
	    file->readInteger(&count);
	_counts[i] = (VpfUInt) count;

	if (count < 0) {
	    error = new VpfError("VpfRow::read");
	    error->getStream() << "Table " << _cursor->getTable()->getPath()
			       << " has a row with a negative field count.";
	    VpfErrorReporter::Add(error);
	    returnCode = 1;
	    break;
	}

	switch(type) {
	case 'T':
	case 'L':
	case 'M':
	case 'N':
	    _fields[i].textval = new char[count + 1];
	    returnCode = file->readText(_fields[i].textval, type, count, 1);
	    if (!returnCode && _cursor->getTrim())
		VpfStrTrim(_fields[i].textval);
	    break;
	case 'F':
	case 'R':
	    _fields[i].doubleval = new double[count];
	    returnCode = file->readFloat(_fields[i].doubleval, type, count);
	    break;
	case 'I':
	case 'S':
	    _fields[i].intval = new VpfInt[count];
	    returnCode = file->readInteger(_fields[i].intval, type, count);
	    break;
	case 'C':
	case 'Z':
	case 'B':
	case 'Y':
	    _fields[i].coordval = new VpfCoordinate[count];
	    returnCode = file->readCoordinate(_fields[i].coordval,
					      type, count);
	    break;
	case 'D':
	    _fields[i].dateval = new VpfDate[count];
	    returnCode = file->readDate(_fields[i].dateval, count);
	    break;
	case 'K':
	    _fields[i].tripletval = new VpfTripletID[count];
	    returnCode = file->readTripletID(_fields[i].tripletval, count);
	    break;
	default:
	    // Should never happen assumed VpfHeader checks this itself
	    ;
	} // switch(type)

	if (returnCode) {
	    error = new VpfError("VpfRow::read");
	    error->getStream() << "Failed to read field "
			       << _cursor->getHeader(i)->getName()
			       << " in table "
			       << _cursor->getTable()->getPath()
			       << " at row " << _number << ".";
	    VpfErrorReporter::Add(error);
	    break;
	} // if
    } // for
    return returnCode;
}

// --------------------------------------------------------------------------
void
VpfRow::free()
{
    // Give back the memory that has been dynamically
    // allocated for fields
    for (VpfUInt i = 0; i < _nFields; i++) {
	if (!_mapped[i]) {
	    char type = _cursor->getHeader(i)->getType();

	    switch(type) {
	    case 'T':
	    case 'L':
	    case 'M':
	    case 'N':
		delete [] _fields[i].textval;
		_fields[i].textval = 0;
		break;
	    case 'F':
	    case 'R':
		delete [] _fields[i].doubleval;
		_fields[i].doubleval = 0;
		break;
	    case 'I':
	    case 'S':
		delete [] _fields[i].intval;
		_fields[i].intval = 0;
		break;
	    case 'C':
	    case 'Z':
	    case 'B':
	    case 'Y':
		delete [] _fields[i].coordval;
		_fields[i].coordval = 0;
		break;
	    case 'D':
		delete [] _fields[i].dateval;
		_fields[i].dateval = 0;
		break;
	    case 'K':
		delete [] _fields[i].tripletval;
		_fields[i].tripletval = 0;
		break;
	    default:
		// Should never happen assumed VpfHeader checks this itself
		;
	    }
	}
    }
}

// --------------------------------------------------------------------------
void
VpfRow::clear()
{
    // Give back the memory that has been dynamically
    // allocated for fields
    for (VpfUInt i = 0; i < _nFields; i++) {
	char type = _cursor->getHeader(i)->getType();

	_counts[i] = 0;
	_mapped[i] = 0;

	switch(type) {
	case 'T':
	case 'L':
	case 'M':
	case 'N':
	    _fields[i].textval = 0;
	    break;
	case 'F':
	case 'R':
	    _fields[i].doubleval = 0;
	    break;
	case 'I':
	case 'S':
	    _fields[i].intval = 0;
	    break;
	case 'C':
	case 'Z':
	case 'B':
	case 'Y':
	    _fields[i].coordval = 0;
	    break;
	case 'D':
	    _fields[i].dateval = 0;
	    break;
	case 'K':
	    _fields[i].tripletval = 0;
	    break;
	default:
	    // Should never happen assumed VpfHeader checks this itself
	    ;
	}
    }
}

// --------------------------------------------------------------------------
int
VpfRow::getTextField(VpfUInt field, char*& text) const
{
    if (field >= _nFields)
	return 1;
    text = _fields[field].textval;
    return !strchr("TLMN", _cursor->getHeader(field)->getType());
}

// --------------------------------------------------------------------------
int
VpfRow::getIntField(VpfUInt field, VpfInt& value, VpfUInt index) const
{
    if ((field >= _nFields) || (index >= _counts[field]))
	return 1;
    value = _fields[field].intval[index];
    return !strchr("IS", _cursor->getHeader(field)->getType());
}

// --------------------------------------------------------------------------
int
VpfRow::getFloatField(VpfUInt field, double& value, VpfUInt index) const
{
    if ((field >= _nFields) || (index >= _counts[field]))
	return 1;
    value =  _fields[field].doubleval[index];
    return !strchr("FR", _cursor->getHeader(field)->getType());
}

// --------------------------------------------------------------------------
int
VpfRow::getDateField(VpfUInt field, VpfDate*& value, VpfUInt index) const
{
    if ((field >= _nFields) || (index >= _counts[field]))
	return 1;
    value = &(_fields[field].dateval[index]);
    return ('D' != _cursor->getHeader(field)->getType());
}

// --------------------------------------------------------------------------
int
VpfRow::getCoordinateField(VpfUInt field, VpfCoordinate*& value,
			   VpfUInt index) const
{
    if ((field >= _nFields) || (index >= _counts[field]))
	return 1;
    value = &(_fields[field].coordval[index]);
    return !strchr("BCYZ", _cursor->getHeader(field)->getType());
}

// --------------------------------------------------------------------------
int
VpfRow::getCoordinateArray(VpfUInt field, VpfCoordinate*& value) const
{
    if (field >= _nFields)
	return 1;
    value = _fields[field].coordval;
    return !strchr("BCYZ", _cursor->getHeader(field)->getType());
}

// --------------------------------------------------------------------------
int
VpfRow::getTripletID(VpfUInt field,
		     VpfTripletID*& value, VpfUInt index) const
{
    if (field >= _nFields)
	return 1;
    value = &(_fields[field].tripletval[index]);
    return ('K' != _cursor->getHeader(field)->getType());
}

// --------------------------------------------------------------------------
int
VpfRow::getTripletID(VpfUInt field, VpfUInt subfield,
		     VpfInt& value, VpfUInt index) const
{
    if (field >= _nFields)
	return 1;
    if ('K' != _cursor->getHeader(field)->getType())
	return 1;

    const VpfTripletID* tripletID = &(_fields[field].tripletval[index]);

    switch(subfield) {
    case 0:
	value = tripletID->getID();
	break;
    case 1:
	value = tripletID->getTileID();
	break;
    case 2:
	value = tripletID->getExtID();
	break;
    default:
	return 1;
    }
    return 0;
}
