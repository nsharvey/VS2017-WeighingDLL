// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/manip.h
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
//
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Manip_H
#define __Ilv31_Variable_Manip_H

#include <iostream.h>

// streams contains a strange way to save and restore states
class IlvvStreamState
{
public:
   IlvvStreamState(ostream& o, long format = ios::dec)
   : _oldfield(getField(o)),
     _oldbase(setf(o, format)),
     _stream(o) {}
    // ____________________________________________________________
    ostream& restore() { _stream.setf(_oldbase, _oldfield); return _stream; }
    // return the field, non intrusive
    static long getField(ostream&);
    // sets the format, computes the field and returns the old base
    static long setf(ostream&, long);
private:
    long     _oldbase;
    long     _oldfield;
    ostream& _stream;
};

#endif /* !__ilvv__manip */
