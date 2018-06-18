// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/set.h
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
// Declaration of the VpfSet class
// --------------------------------------------------------------------------
#ifndef VPF_SET_H
#define VPF_SET_H

#include <vpf/basictypes.h>

// --------------------------------------------------------------------------
class VpfSet
{
public:
    VpfSet(VpfUInt);
    VpfSet(VpfUInt, char*, int isOwner = 0);
    VpfSet(const VpfSet&);
    ~VpfSet();
    // ____________________________________________________________
    VpfUInt getSize() const { return _nBits; }

    void clear();

    int isSet(VpfUInt) const;
    void set(VpfUInt, int);
    void setAll();

    VpfInt getNthSet(VpfUInt) const;
    VpfUInt getNSet() const;

    VpfSet* logor(const VpfSet*) const;
    VpfSet* logand(const VpfSet*) const;
    VpfSet* logxor(const VpfSet*) const;
    VpfSet* lognot() const;
protected:
    VpfUInt	_nBits;
    char*	_bitArray;
    int		_isOwner;
};

#endif /* VPF_SET_H */
