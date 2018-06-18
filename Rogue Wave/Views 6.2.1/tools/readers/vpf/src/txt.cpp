// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/txt.cpp
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
// Definition of the TXT tables related classes
// --------------------------------------------------------------------------

#include <vpf/txt.h>
#include <vpf/table.h>
#include <vpf/error.h>

// --------------------------------------------------------------------------
VpfTxtCursor::VpfTxtCursor(VpfTable* table)
: VpfCursor(table)
{
    static const char* Class = "VpfTxtCursor::VpfTxtCursor";

    VPF_IMPL_FIELD(Class, ID,        "ID",         1, I);
    VPF_IMPL_FIELD(Class, TxtString, "STRING",     1, TLMN);
    VPF_IMPL_FIELD(Class, ShapeLine, "SHAPE_LINE", 1, BCYZ);
}

// --------------------------------------------------------------------------
VpfRow*
VpfTxtCursor::getNewRow()
{
    return new VpfTxtRow(this);
}
