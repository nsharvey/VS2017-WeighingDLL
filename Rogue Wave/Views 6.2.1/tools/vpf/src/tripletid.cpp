// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/tripletid.cpp
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
// Definition of the VpfTripletID class
// --------------------------------------------------------------------------

#include <vpf/tripletid.h>
#include <vpf/string.h>

// --------------------------------------------------------------------------
int
VpfTripletID::getField(const char* name, VpfInt& value) const
{
    if (!VpfStrICmp(name, "ID"))
	value = _ID;
    else
    if (!VpfStrICmp(name, "TILE_ID"))
	value = _tileID;
    else
    if (!VpfStrICmp(name, "EXT_ID"))
	value = _extID;
    else
	return 1;
    return 0;
}
