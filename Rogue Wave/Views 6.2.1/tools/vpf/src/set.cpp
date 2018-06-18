// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/set.cpp
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
// Definition of the VpfSet class
// --------------------------------------------------------------------------

#include <vpf/set.h>
#include <memory.h>

#define NBYTES(N) ((N + 7) / 8)

// --------------------------------------------------------------------------
VpfSet::VpfSet(const VpfSet& set)
: _nBits(set._nBits),
  _bitArray(new char[NBYTES(set._nBits)]),
  _isOwner(1)
{
    memcpy(_bitArray, set._bitArray, NBYTES(set._nBits));
}

// --------------------------------------------------------------------------
VpfSet::VpfSet(VpfUInt nBits)
: _nBits(nBits),
  _bitArray(new char[NBYTES(nBits)]),
  _isOwner(1)
{
    clear();
}

// --------------------------------------------------------------------------
VpfSet::VpfSet(VpfUInt nBits, char* bitArray, int isOwner)
: _nBits(nBits),
  _bitArray(bitArray),
  _isOwner(isOwner)
{
    clear();
}

// --------------------------------------------------------------------------
VpfSet::~VpfSet()
{
    if (_bitArray && _isOwner)
	delete [] _bitArray;
}

// --------------------------------------------------------------------------
void
VpfSet::clear()
{
    memset(_bitArray, '\0', NBYTES(_nBits));
}

// --------------------------------------------------------------------------
int
VpfSet::isSet(VpfUInt i) const
{
    return _bitArray[(int)(i / 8)] & (0x80 >> (i % 8));
}

// --------------------------------------------------------------------------
void
VpfSet::set(VpfUInt i, int value)
{
    int byte = i / 8;
    int bit = 0x80 >> (i % 8);

    if (value)
	_bitArray[byte] |= (unsigned char)bit;
    else
	_bitArray[byte] &= (unsigned char)bit;
}

// --------------------------------------------------------------------------
void
VpfSet::setAll()
{
    memset(_bitArray, 255, NBYTES(_nBits));
}

// --------------------------------------------------------------------------
VpfInt
VpfSet::getNthSet(VpfUInt j) const
{
    if (j == 0)
	return -1;
    for (VpfUInt i = 0; i < _nBits; i++)
	if (isSet(i))
	    if (--j == 0)
		return i;
    return -1;
}

// --------------------------------------------------------------------------
VpfUInt
VpfSet::getNSet() const
{
    VpfUInt j = 0;
    for (VpfUInt i = 0; i < _nBits; ++i)
	if (isSet(i))
	    j++;
    return j;
}
