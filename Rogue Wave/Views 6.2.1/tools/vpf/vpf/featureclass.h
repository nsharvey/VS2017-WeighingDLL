// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/featureclass.h
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
    VpfCoverage*	getCoverage() const { return _coverage; }
    inline const char*		getName() const { return _name; }
    inline const char*		getDescription() const { return _description; }

    inline const char*		getTable() const { return _table; }
    inline const char*		getJoinTableName() const
				{
				    return _joinTableName;
				}
    inline const char*		getPrimIdName() const { return _primIdName; }
    inline const char*		getJoinTableForeignKeyName() const
				{
				    return _joinTableForeignKeyName;
				}
    inline const char*		getPrimitiveTableName() const
				{
				    return _primitiveTableName;
				}
    inline const VpfFeatureType* getType() const { return _type; }
    inline VpfUInt		getNAttributes() const { return _nAttributes; }
    inline VpfAttribute*	getAttribute(VpfUInt i) const
				{
				    return _attributes[i];
				}

    const char*			getPath() const;
    void			loadAttributes();

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
