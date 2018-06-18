// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/tripletid.h
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
// Declaration of the VpfTripletID class
// --------------------------------------------------------------------------
#ifndef VPF_TRIPLETID_H
#define VPF_TRIPLETID_H

#include <vpf/basictypes.h>

// --------------------------------------------------------------------------
class VpfTripletID
{
public:
    VpfTripletID()
    : _ID(0),
      _tileID(0),
      _extID(0)
    {}
    VpfTripletID(VpfInt ID, VpfInt tileID, VpfInt extID)
    : _ID(ID),
      _tileID(tileID),
      _extID(extID)
    {}
    // ____________________________________________________________
    void set(VpfInt ID, VpfInt tileID, VpfInt extID)
        { _ID = ID; _tileID = tileID; _extID = extID; }
    VpfInt getID() const { return _ID; }
    VpfInt getTileID() const { return _tileID; }
    VpfInt getExtID() const { return _extID; }

    int getField(const char*, VpfInt&) const;
protected:
    VpfInt	_ID;
    VpfInt	_tileID;
    VpfInt	_extID;
};

#endif /* VPF_TRIPLETID_H */
