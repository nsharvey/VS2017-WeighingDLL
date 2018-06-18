// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/cellxref.h
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
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Cellxref_H
#define __Ilv31_Variable_Cellxref_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Variable_Compilrs_H)
#include <ilviews/variable/compilrs.h>
#endif
#if !defined(__Ilv31_Variable_Boolean_H)
#include <ilviews/variable/boolean.h>
#endif

class ILV31VAREXPORTED IlvvCellXRefs
{
public:
    IlvvCellXRefs(int size, char** xrefs,
		  IlvvBoolean sortIt = IlvvTrue);
    IlvvCellXRefs(const IlvvCellXRefs&);
    ~IlvvCellXRefs();
    // ____________________________________________________________
    int getSize() const           { return _size; }
    char* operator[](int i) const { return _xrefs[i]; }
private:
    // forbidden
    void operator=(const IlvvCellXRefs&);
    char** _xrefs;
    int    _size;
};

#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
ILVSTDPREF ostream& operator<<(ILVSTDPREF ostream&, const IlvvCellXRefs&);

#endif
