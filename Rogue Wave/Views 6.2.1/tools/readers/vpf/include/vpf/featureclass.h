// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/featureclass.h
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
// Declaration of the VpfFeatureClass class
// --------------------------------------------------------------------------
#ifndef VPF_FEATURECLASS_H
#define VPF_FEATURECLASS_H

#include <vpf/basictypes.h>
#include <vpf/string.h>

class VpfCoverage;
class VpfAttribute;
class VpfFeatureType;

// --------------------------------------------------------------------------
class VpfFeatureClass
{
public:
    VpfFeatureClass(VpfCoverage* coverage,
		    const char* name,
		    const char* description,
		    const char* featureTableName,
		    const char* featureTablePrimIdName,
		    const char* primitiveTableName,
		    const char* joinTableName,
		    const char* joinTableForeignKeyName);
    ~VpfFeatureClass();
    // ____________________________________________________________
    VpfCoverage* getCoverage() const { return _coverage; }
    const char* getName() const { return _name; }
    const char* getDescription() const { return _description; }

    const char* getTable() const { return _table; }
    const char* getJoinTableName() const { return _joinTableName; }
    const char* getPrimIdName() const { return _primIdName; }
    const char* getJoinTableForeignKeyName() const
	{ return _joinTableForeignKeyName; }
    const char* getPrimitiveTableName() const { return _primitiveTableName; }
    const VpfFeatureType* getType() const { return _type; }
    VpfUInt getNAttributes() const { return _nAttributes; }
    VpfAttribute* getAttribute(VpfUInt i) const { return _attributes[i]; }

    const char* getPath() const;
    void loadAttributes();
protected:
    VpfCoverage*		_coverage;
    VpfString			_name;
    VpfString			_path;
    VpfString			_table;
    VpfString			_description;
    VpfString			_primIdName;
    VpfString			_primitiveTableName;
    VpfString			_joinTableName;
    VpfString			_joinTableForeignKeyName;
    const VpfFeatureType*	_type;
    VpfUInt			_nAttributes;
    VpfAttribute**		_attributes;
};

#endif /* VPF_FEATURECLASS_H */
