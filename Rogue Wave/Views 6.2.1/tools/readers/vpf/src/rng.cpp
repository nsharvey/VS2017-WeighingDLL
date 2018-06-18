// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/rng.cpp
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
// Definition of the CND tables related classes
// --------------------------------------------------------------------------

#include <vpf/rng.h>
#include <vpf/table.h>

// --------------------------------------------------------------------------
VpfRngCursor::VpfRngCursor(VpfTable* table)
: VpfCursor(table)
{
    static const char* Class = "VpfRngCursor::VpfRngCursor";
    VPF_IMPL_FIELD(Class, ID,        "ID",         1, I);
    VPF_IMPL_FIELD(Class, FaceID,    "FACE_ID",    1, I);
    VPF_IMPL_FIELD(Class, StartEdge, "START_EDGE", 1, I);
}

// --------------------------------------------------------------------------
VpfRow*
VpfRngCursor::getNewRow()
{
    return new VpfRngRow(this);
}
