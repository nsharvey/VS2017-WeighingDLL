// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/cursor.cpp
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
// Definition of the VpfCursor class
// --------------------------------------------------------------------------
#include <vpf/cursor.h>
#include <vpf/table.h>
#include <vpf/file.h>
#include <vpf/row.h>
#include <vpf/attribute.h>
#include <vpf/set.h>
#include <vpf/thematicindex.h>
#include <vpf/error.h>
#include <vpf/query.h>

#include <string.h>

// --------------------------------------------------------------------------
VpfCursor::VpfCursor(VpfTable* table)
: _table(table),
  _file(0),
  _nRows(0),
  _nFields(0),
  _headers(0),
  _currentRow(0),
  _trim(0),
  _queried(0),
  _queryDestroy(0),
  _inSet(0)
{
    static const char* Class = "VpfCursor::VpfCursor";
    VpfError* error = 0;
    
    if (_table) {
	_nRows = table->getNRows();
	_nFields = table->getNFields();
	_headers = table->getHeaders();
	VpfErrorReporter::Push();
	_file = new VpfFile(table->getPath(), "rb");
	_file->setSwap(table->getByteOrder() != Vpf::MachineByteOrder);
	VpfErrorReporter::Pop();

	if (!_file) {
	    error = new VpfError(Class);
	    error->getStream() << "Table file " << table->getPath()
			       << " could not be opened.";
	    VpfErrorReporter::Add(error);
	    setBad();
	} else
	    setCurrentRow(0);
    } else {
	error = new VpfError(Class);
	error->getStream() << "Cursor initialized with null table pointer.";
	VpfErrorReporter::Add(error);
	setBad();
    }
}

// --------------------------------------------------------------------------
VpfCursor::~VpfCursor()
{
    if (_file)
	delete _file;
    if (_queried && _queryDestroy)
	delete _queried;
}

// --------------------------------------------------------------------------
VpfUInt
VpfCursor::getNRows() const
{
    return _nRows;
}

// --------------------------------------------------------------------------
int
VpfCursor::query(VpfQuery* q)
{
    VpfUInt nMatches = q->getNMatches();

    if (nMatches) {
	VpfRow* row = getNewRow();
	setCurrentRow(0);

	for (VpfUInt i = 0; i < _nRows; i++) {
	    getNextRow(row);
	    for (VpfUInt j = 0; j < nMatches; j++)
		q->getMatch(j)->match(row);
	}
    }

    VpfExpression* expr = q->getExpression();

    if (_queried && _queryDestroy)
	delete _queried;
    _queried = 0;

    if (expr) {
	const VpfSet* result = expr->evaluate(_queryDestroy);
	_queried = result
	    ? new VpfSet(*result)
	    : 0;
	_nRows = _queried
	    ? _queried->getNSet()
	    : 0;
    } else
	_nRows = _table->getNRows();

    setCurrentRow(0);
    return (!expr);
}

// --------------------------------------------------------------------------
VpfRow*
VpfCursor::getNewRow()
{
    return new VpfRow(this);
}

// --------------------------------------------------------------------------
VpfUInt
VpfCursor::getCurrentRow() const
{
    return _currentRow;
}

// --------------------------------------------------------------------------
void
VpfCursor::setCurrentRow(VpfUInt currentRow)
{
    _currentRow = (currentRow > _nRows)
	? _nRows
	: currentRow;

    if (_queried) {
	VpfInt realRow = _queried->getNthSet(currentRow + 1);
	if (realRow >= 0)
	    _file->seek(_table->getRowPosition(_inSet = realRow), SEEK_SET);
	else
	    _currentRow = _nRows;
    } else
	_file->seek(_table->getRowPosition(currentRow), SEEK_SET);
}

// --------------------------------------------------------------------------
int
VpfCursor::getNextRow(VpfRow* row)
{
    if (_currentRow == _nRows)
	return 1;

    if (_queried)
	if (!_queried->isSet(_inSet))
	    setCurrentRow(_currentRow);

    row->read(_currentRow, _file);
    _currentRow++;

    if (_queried)
	_inSet++;

    return 0;
}

// --------------------------------------------------------------------------
int
VpfCursor::checkField(const char* where, VpfInt field,
		      const char* fieldName, int mandatory,
		      const char* allowedTypes)
{
    char type = '\0';
    const VpfHeader* header = 0;
    VpfError* error = 0;
    int returnCode = 0;

    if (field == -1) {
	if (mandatory) {
	    error = new VpfError(where);
	    error->getStream() << "Could not find mandatory field "
			       << fieldName << " in table "
			       << _table->getPath() << ".";
	    VpfErrorReporter::Add(error);
	    returnCode = 1;
	}
    } else {
	header = _table->getHeader(field);
	if (header == 0) {
	    error = new VpfError(where);
	    error->getStream() << "Internal header structure is damaged.";
	    VpfErrorReporter::Add(error);
	    returnCode = 1;
	} else {
	    type = header->getType();
	    if (!strchr(allowedTypes, type)) {
		error = new VpfError(where);
		error->getStream() << "The field " << fieldName
				   << " is from type " << type
				   << ", which is not one of those allowed: "
				   << allowedTypes << ".";
		VpfErrorReporter::Add(error);
		returnCode = 1;
	    }
	}
    }
    return returnCode;
}
