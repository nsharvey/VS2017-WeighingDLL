// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/header.cpp
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
// Definition of the VpfHeader class
// --------------------------------------------------------------------------

#include <vpf/header.h>
#include <vpf/table.h>
#include <vpf/string.h>
#include <vpf/thematicindex.h>
#include <string.h>

// --------------------------------------------------------------------------
VpfHeader::VpfHeader(VpfTable* table)
: _table(table),
  _name(0),
  _type('X'),
  _keyType('P'),
  _description(0),
  _count(0),
  _valueDescriptionTableName(0),
  _thematicIndexTableName(0),
  _narrativeTableName(0),
  _index(0)
{
}

// --------------------------------------------------------------------------
VpfHeader::~VpfHeader()
{
    if (_name)
	delete [] _name;
    if (_description)
	delete [] _description;
    if (_valueDescriptionTableName)
	delete [] _valueDescriptionTableName;
    if (_thematicIndexTableName)
	delete [] _thematicIndexTableName;
    if (_narrativeTableName)
	delete [] _narrativeTableName;
    if (_index)
	delete _index;
}

// --------------------------------------------------------------------------
void
VpfHeader::setName(const char* name)
{
    if (_name)
	delete [] _name;
    _name = VpfStrDup(name);
}

// --------------------------------------------------------------------------
void
VpfHeader::setDescription(const char* description)
{
    if (_description)
	delete [] _description;
    _description = VpfStrDup(description);
}

// --------------------------------------------------------------------------
void
VpfHeader::setNarrativeTableName(const char* narrativeTableName)
{
    if (_narrativeTableName)
	delete _narrativeTableName; 
    _narrativeTableName = VpfStrDup(narrativeTableName);
}

// --------------------------------------------------------------------------
void
VpfHeader::setThematicIndexTableName(const char* thematicIndexTableName)
{
    if (_thematicIndexTableName)
	delete _thematicIndexTableName;
    _thematicIndexTableName = VpfStrDup(thematicIndexTableName);
}

// --------------------------------------------------------------------------
void
VpfHeader::setValueDescriptionTableName(const char* valueDescriptionTableName) 
{
    if (_valueDescriptionTableName)
	delete _valueDescriptionTableName; 
    _valueDescriptionTableName = VpfStrDup(valueDescriptionTableName);
}

// --------------------------------------------------------------------------
const VpfThematicIndex*
VpfHeader::getThematicIndex()
{
    if (_index)
	return _index;

    if (_thematicIndexTableName) {
	char* filename = strcpy(new char[strlen(_table->getPath()) +
					 strlen(_thematicIndexTableName) + 1],
				_table->getPath());
	char* ptr = strrchr(filename, '/');
	if (!ptr)
	    ptr = filename;
	else
	    ptr++;

	strcpy(ptr, _thematicIndexTableName);
	_index = VpfThematicIndex::Open(filename);
	delete [] filename;
    }

    return _index;
}
