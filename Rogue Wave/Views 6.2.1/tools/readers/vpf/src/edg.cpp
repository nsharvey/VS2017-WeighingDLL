// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/edg.cpp
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
// Definition of the EDG tables related classes
// --------------------------------------------------------------------------

#include <vpf/edg.h>
#include <vpf/table.h>
#include <vpf/error.h>

// --------------------------------------------------------------------------
VpfEdgCursor::VpfEdgCursor(VpfTable* table, VpfUInt topo)
: VpfCursor(table)
{
    static const char* Class = "VpfEdgCursor::VpfEdgCursor";

    VPF_IMPL_FIELD(Class, ID,          "ID",          1, I);
    VPF_IMPL_FIELD(Class, StartNode,   "START_NODE",  topo >= 1, I);
    VPF_IMPL_FIELD(Class, EndNode,     "END_NODE",    topo >= 1, I);
    VPF_IMPL_FIELD(Class, RightFace,   "RIGHT_FACE",  topo >= 3, IK);
    VPF_IMPL_FIELD(Class, LeftFace,    "LEFT_FACE",   topo >= 3, IK);
    VPF_IMPL_FIELD(Class, RightEdge,   "RIGHT_EDGE",  topo >= 1, IK);
    VPF_IMPL_FIELD(Class, LeftEdge,    "LEFT_EDGE",   topo >= 1, IK);
    VPF_IMPL_FIELD(Class, Coordinates, "COORDINATES", 1, BCYZ);
}

// --------------------------------------------------------------------------
VpfRow*
VpfEdgCursor::getNewRow()
{
    return new VpfEdgRow(this);
}

// --------------------------------------------------------------------------
VpfInt
VpfEdgRow::getRightFace() const
{
    VpfInt frf = ((VpfEdgCursor*)_cursor)->_fieldRightFace;
    return (_cursor->getHeader(frf)->getType() == 'K')
	? getTripletIDPart(frf, 0)
	: getInt(frf);
}

// --------------------------------------------------------------------------
VpfInt
VpfEdgRow::getLeftFace() const
{
    VpfInt flf = ((VpfEdgCursor*)_cursor)->_fieldLeftFace;
    return (_cursor->getHeader(flf)->getType() == 'K')
	? getTripletIDPart(flf, 0)
	: getInt(flf);
}

// --------------------------------------------------------------------------
VpfInt
VpfEdgRow::getRightEdge() const
{
    VpfInt fre = ((VpfEdgCursor*)_cursor)->_fieldRightEdge;
    return (_cursor->getHeader(fre)->getType() == 'K')
	? getTripletIDPart(fre, 0)
	: getInt(fre);
}

// --------------------------------------------------------------------------
VpfInt
VpfEdgRow::getLeftEdge() const
{
    VpfInt fle = ((VpfEdgCursor*)_cursor)->_fieldLeftEdge;
    return (_cursor->getHeader(fle)->getType() == 'K')
	? getTripletIDPart(fle, 0)
	: getInt(fle);
}
