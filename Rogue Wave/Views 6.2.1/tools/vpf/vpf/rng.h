// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/rng.h
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
// Declaration of the RNG (rings) tables related classes
// --------------------------------------------------------------------------
#ifndef VPF_RNG_H
#define VPF_RNG_H

#include <vpf/cursor.h>
#include <vpf/row.h>

// --------------------------------------------------------------------------
class VpfRngCursor : public VpfCursor
{
public:
    VpfRngCursor(VpfTable*);
    // ____________________________________________________________
    virtual VpfRow* getNewRow();
protected:
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(FaceID);
    VPF_DEF_FIELD(StartEdge);

    friend class VpfRngRow;
};

// --------------------------------------------------------------------------
class VpfRngRow : public VpfRow
{
public:
    VpfRngRow(VpfRngCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_INTFIELD(VpfRngCursor, FaceID);
    VPF_QUERY_INTFIELD(VpfRngCursor, StartEdge);
};

#endif /* VPF_RNG_H */
