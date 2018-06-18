// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/thematicindex.h
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
// Declaration of the VpfThematicIndex class
// --------------------------------------------------------------------------
#ifndef VPF_THEMATICINDEX_H
#define VPF_THEMATICINDEX_H

#include <vpf/file.h>
#include <vpf/set.h>

// --------------------------------------------------------------------------
class VpfThematicIndex
{
public:
    VpfThematicIndex(char    elementType,
		     VpfUInt elementCount,
		     VpfUInt nElements);
    virtual ~VpfThematicIndex();
    // ____________________________________________________________
    VpfSet*		getAssociated(const char*) const;
    VpfSet*		getAssociated(VpfInt) const;
    VpfSet*		getAssociated(double) const;
    inline VpfSet*	getAssociatedFromIndex(VpfUInt i) const { return _sets[i]; }

    virtual int		readDirectory(VpfFile*);
    virtual int		readIndexData(VpfFile*) = 0;

    static VpfThematicIndex*	Open(const char*);

protected:
    char		_elementType;
    VpfUInt		_elementCount;
    VpfUInt		_nElements;
    VpfUInt*		_positions;
    VpfUInt*		_nRecords;
    void**		_elements;
    VpfSet**		_sets;
};

// --------------------------------------------------------------------------
class VpfThematicInvertedIndex : public VpfThematicIndex
{
public:
    VpfThematicInvertedIndex(char    elementType,
			     VpfUInt elementCount,
			     VpfUInt nElements,
			     char    IDType);
    virtual ~VpfThematicInvertedIndex();
    // ____________________________________________________________
    virtual int	readIndexData(VpfFile*);

protected:
    char	_IDType;
};

// --------------------------------------------------------------------------
class VpfThematicBitArrayIndex : public VpfThematicIndex
{
public:
    VpfThematicBitArrayIndex(char    elementType,
			     VpfUInt elementCount,
			     VpfUInt nElements);
    virtual ~VpfThematicBitArrayIndex();
    // ____________________________________________________________
    virtual int	readIndexData(VpfFile*);
};

#endif /* VPF_THEMATICINDEX_H */
