// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/table.h
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
// Declaration of the VpfTable class
// --------------------------------------------------------------------------
#ifndef VPF_TABLE_H
#define VPF_TABLE_H

#include <vpf/vpf.h>
#include <vpf/basictypes.h>
#if defined(VPFSTD)
#include <iostream>
VPFSTDUSE
#else
#include <iostream.h>
#endif

class VpfFile;
class VpfHeader;
class VpfRow;
class VpfIndex;
class VpfThematicIndex;

class VpfTable
{
public:
    VpfTable(const char* filename);
    virtual ~VpfTable();
    // ____________________________________________________________
    inline int		isBad() const { return _isBad; }
    inline void		setBad() { _isBad = 1; }

    inline const char*	getName() const { return _name; }
    inline const char*	getPath() const { return _path; }

    inline VpfHeader**	getHeaders() const { return _headers; }
    VpfHeader*		getHeader(VpfUInt) const;
    const VpfThematicIndex*	getThematicIndex(VpfUInt) const;

    inline VpfUInt	getNFields() const { return _nFields; }
    VpfInt		getFieldPosition(const char*) const;

    inline VpfUInt	getNRows() const { return _nRows; }
    long		getRowPosition(VpfUInt) const;
    unsigned int	getRowLength(VpfUInt) const;

    inline Vpf::ByteOrder	getByteOrder() const { return _byteOrder; }
    inline VpfInt	getRecordLength() { return _recordLength; }

    inline const char*	getDescription() const { return _description; }

    void		dump(VPFSTDPREF ostream&, long = -1, long = -1) const;

protected:
    char*		_path;
    char*		_name;
    char*		_description;
    char*		_narrativeTableName;
    int			_isBad;
    VpfIndex*		_index;
    VpfUInt		_nFields;
    VpfHeader**		_headers;
    VpfUInt		_nRows;
    VpfInt		_recordLength;
    VpfUInt		_dataDefinitionLength;
    Vpf::ByteOrder	_byteOrder;

    int			parseDataDefinition(VpfFile*);

    static const char*	CopyToDelimiter(VpfUInt&, char*, char);
    static const char*	GetString(VpfUInt&, char*, char);
    static char		GetChar(VpfUInt&, char*);
    static VpfInt	GetNumber(VpfUInt& ind, char*, char);

    void		readNextRow(VpfRow&);

    static const char	ComponentSeparator;
    static const char	LineContinue ;
    static const char	Comment;
    static const char	EndOfField;
    static const char	FieldCount;
    static const char	FieldSeparator;
    static const char	VariableCount;

    static int		IsNull(const char*);
};

#endif /* VPF_TABLE_H */
