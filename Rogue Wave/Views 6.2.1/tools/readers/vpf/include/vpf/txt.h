// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/txt.h
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
// Declaration of the TXT tables-related classes
// --------------------------------------------------------------------------
#ifndef VPF_TXT_H
#define VPF_TXT_H

#include <vpf/cursor.h>
#include <vpf/row.h>

// --------------------------------------------------------------------------
class VpfTxtCursor
: public VpfCursor
{
public:
    VpfTxtCursor(VpfTable*);
    // ____________________________________________________________
    virtual VpfRow* getNewRow();
private:
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(TxtString);
    VPF_DEF_FIELD(ShapeLine);

    friend class VpfTxtRow;
};

// --------------------------------------------------------------------------
class VpfTxtRow
: public VpfRow {
public:
    VpfTxtRow(VpfTxtCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_TEXTFIELD(VpfTxtCursor, TxtString);
    VPF_QUERY_COORDFIELD(VpfTxtCursor, ShapeLine);
};

#endif /* VPF_TXT_H */
