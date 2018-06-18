// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/gui/databaselist.cpp
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
// Definition of the DatabaseList class
// --------------------------------------------------------------------------

#include <vpf/gui/databaselist.h>
#include <vpf/database.h>
#include <vpf/library.h>
#include <vpf/coverage.h>
#include <vpf/featureclass.h>
#include <string.h>

DatabaseList* DatabaseList::_Head = 0;
unsigned int DatabaseList::_NDatabases = 0;

// --------------------------------------------------------------------------
DatabaseList::DatabaseList(VpfDatabase* ptr)
: _previous(0),
  _pointer(ptr)
{
    _next = _Head;
    _Head = this;
    _NDatabases++;
}

// --------------------------------------------------------------------------
DatabaseList::~DatabaseList()
{
    if (_previous)
	_previous->_next = _next;
    else
	_Head = _next;
    if (_next)
	_next->_previous = _previous;
    _NDatabases--;
}

// --------------------------------------------------------------------------
VpfFeatureClass*
DatabaseList::FromName(const char* databaseName,
		       const char* libraryName,
		       const char* coverageName,
		       const char* featureClassName)
{
    DatabaseList* ptr = _Head;
    while (ptr) {
	if (!strcmp(ptr->_pointer->getName(), databaseName)) {
	    VpfDatabase* database = ptr->_pointer;
	    VpfLibrary* library = database->getLibrary(libraryName);
	    if (library) {
		VpfCoverage* coverage = library->getCoverage(coverageName);
		if (coverage) {
		    VpfFeatureClass* featureClass =
			coverage->getFeatureClass(featureClassName);
		    if (featureClass)
			return featureClass;
		}
	    }
	}
	ptr = ptr->_next;
    }
    return 0;
}

// --------------------------------------------------------------------------
DatabaseList*
DatabaseList::FromPointer(VpfDatabase* database)
{
    DatabaseList* ptr = _Head;
    while(ptr)
	if (ptr->_pointer == database)
	    return ptr;
    return 0;
}
