// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/cursor.h
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
// Declaration of the VpfCursor class
// --------------------------------------------------------------------------
#ifndef VPF_CURSOR_H
#define VPF_CURSOR_H

class VpfTable;
class VpfFile;
class VpfRow;
class VpfQuery;
class VpfSet;

#include <vpf/header.h>

// --------------------------------------------------------------------------
class VpfCursor
{
public:
    VpfCursor(VpfTable*);
    virtual ~VpfCursor();
    // ____________________________________________________________
    int isBad() const { return (!_table || !_file); }
    void setBad() { _table = 0; }

    int query(VpfQuery*);

    virtual VpfRow* getNewRow();

    void setCurrentRow(VpfUInt);
    VpfUInt getCurrentRow() const;

    void setTrim(int trim) { _trim = trim; }
    int getTrim() const { return _trim; }

    int getNextRow(VpfRow*);

    VpfUInt getNRows() const;
    VpfUInt getNFields() const { return _nFields; }
    VpfHeader* getHeader(VpfUInt i) const { return _headers[i]; }
    VpfTable* getTable() const { return _table; }
protected:
    VpfTable*	_table;
    VpfFile*	_file;
    VpfUInt	_nRows;
    VpfUInt	_nFields;
    VpfHeader**	_headers;
    VpfUInt	_currentRow;
    int		_trim;
    VpfSet*	_queried;
    int		_queryDestroy;
    VpfUInt	_inSet;
    int checkField(const char*, VpfInt, const char*, int, const char*);
};

#define VPF_DEF_FIELD(NAME) VpfInt _field##NAME
#define VPF_FIELDNAME(NAME) _field##NAME
#define VPF_IMPL_FIELD(CLASS, NAME, DBNAME, MANDATORY, ALLOWEDTYPES) \
  _field##NAME = _table->getFieldPosition(DBNAME); \
  if (checkField(CLASS, _field##NAME, DBNAME, MANDATORY, #ALLOWEDTYPES)) \
  { setBad(); return; }

#endif /* VPF_CURSOR_H */
