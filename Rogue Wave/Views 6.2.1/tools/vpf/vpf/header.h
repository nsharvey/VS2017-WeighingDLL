// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/header.h
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
// Declaration of the VpfHeader class
// --------------------------------------------------------------------------
#ifndef VPF_HEADER_H
#define VPF_HEADER_H

#include <vpf/basictypes.h>

class VpfTable;
class VpfThematicIndex;

// --------------------------------------------------------------------------
class VpfHeader
{
public:
    VpfHeader(VpfTable*);
    virtual ~VpfHeader();

    inline const char*	getName() const { return _name; }
    void		setName(const char*);
    inline char		getType() const { return _type; }
    inline void		setType(char type) { _type = type; }
    inline char		getKeyType() const { return _keyType; }
    inline void		setKeyType(char keyType) { _keyType = keyType; }
    inline const char*	getDescription() const { return _description; }
    void		setDescription(const char*);
    inline VpfInt	getCount() const { return _count; }
    inline void		setCount(VpfInt count) { _count = count; }
    inline const char*	getNarrativeTableName() const
			{
			    return _narrativeTableName;
			}
    void		setNarrativeTableName(const char*);
    inline const char*	getThematicIndexTableName() const
			{
			    return _thematicIndexTableName;
			}
    void		setThematicIndexTableName(const char*);
    inline const char*	getValueDescriptionTableName() const
			{
			    return _valueDescriptionTableName;
			}
    void		setValueDescriptionTableName(const char*);
    const VpfThematicIndex* getThematicIndex();

protected:
    VpfTable*		_table;
    char*		_name;
    char		_type;
    char		_keyType;
    char*		_description;
    VpfInt		_count;
    char*		_valueDescriptionTableName;
    char*		_thematicIndexTableName;
    char*		_narrativeTableName;
    VpfThematicIndex*	_index;
};

#endif /* VPF_HEADER_H */
