// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/gui/serialize.h
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
// Declaration of the Serialize and Unserialize classes
// --------------------------------------------------------------------------
#ifndef VPF_GUI_SERIALIZE_H
#define VPF_GUI_SERIALIZE_H

#ifndef VPF_BASICTYPES_H
# include <vpf/basictypes.h>
#endif

#ifndef __Ilv_Macros_H
# include <ilviews/macros.h>
#endif

#if defined(ILVSTD)
# include <iostream>
ILVSTDUSE
#else
# include <iostream.h>
#endif

// --------------------------------------------------------------------------
class Serialize
{
public:
    Serialize(ostream& s);
    ~Serialize();
    // ____________________________________________________________
    Serialize& operator<<(const char*);
    Serialize& operator<<(VpfInt i)  { _stream << i << ' '; return *this; }
    Serialize& operator<<(VpfUInt i) { _stream << i << ' '; return *this; }
protected:
    ostream& _stream;
};

// --------------------------------------------------------------------------
class Unserialize
{
public:
    Unserialize(istream& s);
    ~Unserialize();
    // ____________________________________________________________
    Unserialize& operator>>(char*&);
    Unserialize& operator>>(VpfInt& i)  { _stream >> i; return *this; }
    Unserialize& operator>>(VpfUInt& i) { _stream >> i; return *this; }
protected:
    istream& _stream;
};

#endif /* VPF_GUI_SERIALIZE_H */

