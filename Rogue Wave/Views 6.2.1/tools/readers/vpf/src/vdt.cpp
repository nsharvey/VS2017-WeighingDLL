// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/vdt.cpp
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
// Definition of the VDT tables related classes
// --------------------------------------------------------------------------

#include <vpf/vdt.h>
#include <vpf/table.h>

// --------------------------------------------------------------------------
VpfIntVdtCursor::VpfIntVdtCursor(VpfTable* table)
: VpfCursor(table)
{
    static const char* Class = "VpfIntVdtCursor::VpfIntVdtCursor";
    VPF_IMPL_FIELD(Class, ID,          "ID",          1, I);
    VPF_IMPL_FIELD(Class, Table,       "TABLE",       1, TLMN);
    VPF_IMPL_FIELD(Class, Attribute,   "ATTRIBUTE",   1, TLMN);
    VPF_IMPL_FIELD(Class, Value,       "VALUE",       1, IS);
    VPF_IMPL_FIELD(Class, Description, "DESCRIPTION", 1, TLMN);
}

// --------------------------------------------------------------------------
VpfRow*
VpfIntVdtCursor::getNewRow()
{
    return new VpfIntVdtRow(this);
}

// --------------------------------------------------------------------------
VpfCharVdtCursor::VpfCharVdtCursor(VpfTable* table)
: VpfCursor(table)
{
    static const char* Class = "VpfCharVdtCursor::VpfCharVdtCursor";
    VPF_IMPL_FIELD(Class, ID,          "ID",          1, I);
    VPF_IMPL_FIELD(Class, Table,       "TABLE",       1, TLMN);
    VPF_IMPL_FIELD(Class, Attribute,   "ATTRIBUTE",   1, TLMN);
    VPF_IMPL_FIELD(Class, Value,       "VALUE",       1, TLMN);
    VPF_IMPL_FIELD(Class, Description, "DESCRIPTION", 1, TLMN);
}

// --------------------------------------------------------------------------
VpfRow*
VpfCharVdtCursor::getNewRow()
{
    return new VpfCharVdtRow(this);
}
