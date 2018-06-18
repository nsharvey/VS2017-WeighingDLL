// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/featureclass.cpp
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
// Definition of the VpfFeatureClass class
// --------------------------------------------------------------------------

#include <vpf/featureclass.h>
#include <vpf/featuretype.h>
#include <vpf/coverage.h>
#include <vpf/library.h>
#include <vpf/database.h>
#include <vpf/attribute.h>
#include <vpf/string.h>
#include <vpf/table.h>
#include <vpf/cursor.h>
#include <vpf/row.h>
#include <vpf/header.h>
#include <vpf/vdt.h>
#include <vpf/error.h>

#include <ilviews/base/memory.h>

#if defined(ILVSTD)
# include <cstring>
#else
# include <string.h>
#endif

// --------------------------------------------------------------------------
VpfFeatureClass::VpfFeatureClass(VpfCoverage* coverage,
                                 const char* name,
                                 const char* description,
                                 const char* featureTableName,
                                 const char* featureTablePrimIdName,
                                 const char* primitiveTableName,
                                 const char* joinTableName,
                                 const char* joinTableForeignKeyName)
: _coverage(coverage),
  _name(name),
  _path(coverage->getPath()),
  _table(featureTableName),
  _description(description),
  _primIdName(featureTablePrimIdName),
  _primitiveTableName(primitiveTableName),
  _joinTableName(joinTableName),
  _joinTableForeignKeyName(joinTableForeignKeyName),
  _type(0),
  _nAttributes(0),
  _attributes(0)
{
    char* p = strrchr(_table, '/');
    
    if (!p)
	p = _table;
    else
	p++;

    if (!ILVSTRCASECMP(featureTableName + strlen(featureTableName) - 4,
		       ".aft"))
	_type = VpfFeatureType::Area;
    else if (!ILVSTRCASECMP(featureTableName + strlen(featureTableName) - 4,
			    ".lft"))
	_type = VpfFeatureType::Line;
    else if (!ILVSTRCASECMP(featureTableName + strlen(featureTableName) - 4,
			    ".pft"))
	_type = VpfFeatureType::Point;
    else if (!ILVSTRCASECMP(featureTableName + strlen(featureTableName) - 4,
			    ".tft"))
	_type = VpfFeatureType::Text;
    
    loadAttributes();
}

// --------------------------------------------------------------------------
VpfFeatureClass::~VpfFeatureClass()
{
    if (_attributes) {
	for (VpfUInt i = 0; i < _nAttributes; i++)
	    if (_attributes[i])
		delete _attributes[i];
	delete [] _attributes;
    }
}

// --------------------------------------------------------------------------
const char*
VpfFeatureClass::getPath() const
{
    return _coverage ?_coverage->getPath() : 0;
}

// --------------------------------------------------------------------------
void
VpfFeatureClass::loadAttributes()
{
    VpfString table(_path);
    table += '/';
    table += _table;
    VpfTable* attTable = new VpfTable(table);
    if (!attTable || attTable->isBad()) {
	delete attTable;
	return;
    }
    _nAttributes = attTable->getNFields();
    if (!_nAttributes) {
	delete attTable;
	return;
    }
    _attributes = new VpfAttribute*[_nAttributes];
    if (!_attributes) {
	_nAttributes = 0;
	delete attTable;
	return;
    }

    VpfTable* cvdtTable = 0;
    {
	VpfString cvdt(_path);
	cvdt += "/char.vdt";
	VpfErrorReporter::Push();
	cvdtTable = new VpfTable(cvdt);
	VpfErrorReporter::Pop();
	if (!cvdtTable || cvdtTable->isBad()) {
	    delete cvdtTable;
	    cvdtTable = 0;
	}
    }

    VpfTable* ivdtTable = 0;
    {
	VpfString ivdt(_path);
	ivdt += "/int.vdt";
	VpfErrorReporter::Push();
	ivdtTable = new VpfTable(ivdt);
	VpfErrorReporter::Pop();
	if (!ivdtTable || ivdtTable->isBad()) {
	    delete ivdtTable;
	    ivdtTable = 0;
	}
    }

    for (VpfUInt i = 0; i < _nAttributes; i++) {
	_attributes[i] = 0;
	VpfHeader* header = attTable->getHeader(i);
	switch(header->getType()) {
	case 'T':
	case 'L':
	case 'M':
	case 'N':
	    if (cvdtTable) {
		VpfCharVdtCursor* cvdtCursor = 0;
		VpfCharVdtRow*    cvdtRow    = 0;
		cvdtCursor = new VpfCharVdtCursor(cvdtTable);
		if (!cvdtCursor || cvdtCursor->isBad()) {
		    delete cvdtCursor;
		    break;
		}
		cvdtRow = (VpfCharVdtRow*)cvdtCursor->getNewRow();
		if (!cvdtRow || cvdtRow->isBad()) {
		    delete cvdtRow;
		    delete cvdtCursor;
		    break;
		}
		cvdtCursor->setTrim(1);
		VpfAttribute* attr = new VpfAttribute(header->getName(),
						      header->getDescription(),
						      cvdtCursor->getNRows());
		_attributes[i] = attr;
		for (VpfUInt k = 0; k < cvdtCursor->getNRows(); k++) {
		    attr->setValue(k, 0);
		    VpfValue* v = 0;
		    if (cvdtCursor->getNextRow(cvdtRow)) {
			delete cvdtRow;
			delete cvdtCursor;
			break;
		    }
		    if (!VpfStrICmp(cvdtRow->getTable(), _table) &&
			!VpfStrICmp(cvdtRow->getAttribute(),
				    header->getName()))
			v = new VpfValue(cvdtRow->getDescription(),
					 cvdtRow->getValue());
		    attr->setValue(k, v);
		}
		delete cvdtRow;
		delete cvdtCursor;
	    }
	    break;
	case 'I':
	case 'S':
	    if (ivdtTable) {
		VpfIntVdtCursor* ivdtCursor = new VpfIntVdtCursor(ivdtTable);
		if (!ivdtCursor || ivdtCursor->isBad()) {
		    delete ivdtCursor;
		    break;
		}
		VpfIntVdtRow* ivdtRow = (VpfIntVdtRow*)ivdtCursor->getNewRow();
		if (!ivdtRow || ivdtRow->isBad()) {
		    delete ivdtRow;
		    delete ivdtCursor;
		    break;
		}
		ivdtCursor->setTrim(1);
		VpfAttribute* attr = new VpfAttribute(header->getName(),
						      header->getDescription(),
						      ivdtCursor->getNRows());
		_attributes[i] = attr;
		for (VpfUInt k = 0; k < ivdtCursor->getNRows(); k++) {
		    attr->setValue(k, 0);
		    VpfValue* v = 0;
		    if (ivdtCursor->getNextRow(ivdtRow)) {
			delete ivdtRow;
			delete ivdtCursor;
			break;
		    }
		    if (!VpfStrICmp(ivdtRow->getTable(), _table) &&
			!VpfStrICmp(ivdtRow->getAttribute(),
				    header->getName()))
			v = new VpfValue(ivdtRow->getDescription(),
					 ivdtRow->getValue());
		    attr->setValue(k, v);
		}
		delete ivdtRow;
		delete ivdtCursor;
	    }
	    break;
	}
	if (!_attributes[i])
	    _attributes[i] = new VpfAttribute(header->getName(),
					      header->getDescription());
    }  // for i
    delete ivdtTable;
    delete cvdtTable;
    delete attTable;
}
