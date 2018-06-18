// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/vdt.h
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
// Declaration of the VDT tables related classes
// --------------------------------------------------------------------------
#ifndef VPF_VDT_H
#define VPF_VDT_H

#include <vpf/cursor.h>
#include <vpf/row.h>

// --------------------------------------------------------------------------
class VpfIntVdtCursor : public VpfCursor
{
public:
    VpfIntVdtCursor(VpfTable*);
    // ____________________________________________________________
    virtual VpfRow* getNewRow();

private:
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(Table);
    VPF_DEF_FIELD(Attribute);
    VPF_DEF_FIELD(Value);
    VPF_DEF_FIELD(Description);

    friend class VpfIntVdtRow;
};

// --------------------------------------------------------------------------
class VpfIntVdtRow : public VpfRow
{
 public:
    VpfIntVdtRow(VpfIntVdtCursor* cursor)
    : VpfRow(cursor) {}
    // ____________________________________________________________
    VPF_QUERY_TEXTFIELD(VpfIntVdtCursor, Table);
    VPF_QUERY_TEXTFIELD(VpfIntVdtCursor, Attribute);
    VPF_QUERY_INTFIELD(VpfIntVdtCursor, Value);
    VPF_QUERY_TEXTFIELD(VpfIntVdtCursor, Description);
};

// --------------------------------------------------------------------------
class VpfCharVdtCursor : public VpfCursor
{
public:
    VpfCharVdtCursor(VpfTable*);
    // ____________________________________________________________
    virtual VpfRow* getNewRow();

private:
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(Table);
    VPF_DEF_FIELD(Attribute);
    VPF_DEF_FIELD(Value);
    VPF_DEF_FIELD(Description);

    friend class VpfCharVdtRow;
};

// --------------------------------------------------------------------------
class VpfCharVdtRow : public VpfRow
{
public:
    VpfCharVdtRow(VpfCharVdtCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_TEXTFIELD(VpfCharVdtCursor, Table);
    VPF_QUERY_TEXTFIELD(VpfCharVdtCursor, Attribute);
    VPF_QUERY_TEXTFIELD(VpfCharVdtCursor, Value);
    VPF_QUERY_TEXTFIELD(VpfCharVdtCursor, Description);
};

#endif /* VPF_VDT_H */
