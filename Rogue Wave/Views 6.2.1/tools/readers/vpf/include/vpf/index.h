// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/index.h
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
// Declaration of the VpfIndex class
// --------------------------------------------------------------------------
#ifndef VPF_INDEX_H
#define VPF_INDEX_H

#include <vpf/basictypes.h>

// --------------------------------------------------------------------------
class VpfIndex
{
public:
    VpfIndex()
    : _position(0),
	_length(0)
    {}
    // ____________________________________________________________
    long getPosition() const { return _position; }
    void setPosition(long position) { _position = position; }
    unsigned int getLength() const { return _length; }
    void setLength(unsigned int length) { _length = length; }
public:
    long		_position;
    unsigned int	_length;
};

#endif /* VPF_INDEX_H */
