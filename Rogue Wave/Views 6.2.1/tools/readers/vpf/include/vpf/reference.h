// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/reference.h
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
// Declaration of the VpfReference class
// --------------------------------------------------------------------------
#ifndef VPF_REFERENCE_H
#define VPF_REFERENCE_H

#include <vpf/basictypes.h>

// --------------------------------------------------------------------------
class VpfReference
{
public:
    VpfReference()
    : _refcount(1)
    {}
    virtual ~VpfReference() {}
    // ____________________________________________________________
    void reference() { _refcount++; }
    void unreference() {
	if (--_refcount == 0)
	    delete this;
    }
    VpfUInt getNReferences() const { return _refcount; }
protected:
    VpfUInt	_refcount;
};

#endif /* VPF_REFERENCE_H */
