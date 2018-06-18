// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/edg.h
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
// Declaration of the EDG (edges) tables related classes
// --------------------------------------------------------------------------
#ifndef VPF_EDG_H
#define VPF_EDG_H

#include <vpf/cursor.h>
#include <vpf/row.h>

// --------------------------------------------------------------------------
class VpfEdgCursor : public VpfCursor
{
public:
    VpfEdgCursor(VpfTable*, VpfUInt topo = 0);
    // ____________________________________________________________
    virtual VpfRow* getNewRow();
protected:
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(StartNode);
    VPF_DEF_FIELD(EndNode);
    VPF_DEF_FIELD(RightFace);
    VPF_DEF_FIELD(LeftFace);
    VPF_DEF_FIELD(RightEdge);
    VPF_DEF_FIELD(LeftEdge);
    VPF_DEF_FIELD(Coordinates);

    friend class VpfEdgRow;
};

// --------------------------------------------------------------------------
class VpfEdgRow : public VpfRow
{
public:
    VpfEdgRow(VpfEdgCursor* cursor)
    : VpfRow(cursor),
      _direction(' ')
    {}
    // ____________________________________________________________
    VPF_QUERY_INTFIELD(VpfEdgCursor, StartNode);
    VPF_QUERY_INTFIELD(VpfEdgCursor, EndNode);
    VPF_QUERY_COORDARRAY(VpfEdgCursor, Coordinates);
    VpfInt	getRightFace() const;
    VpfInt	getLeftFace() const;
    VpfInt	getRightEdge() const;
    VpfInt	getLeftEdge() const;
    inline void	setDirection(char direction) { _direction = direction; }
    inline char	getDirection() const { return _direction; }

protected:
    char	_direction;
};

#endif /* VPF_EDG_H */
