// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/i8211fieldcol.h
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
// Rogue Wave Views - Maps add-on.
// --------------------------------------------------------------------------
#ifndef __Ilv_I8211fieldcol_H
#define __Ilv_I8211fieldcol_H

#include <ilviews/maps/format/s57/i8211util.h>
#include <ilviews/maps/format/s57/i8211decl.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211FieldDeclCollection
{
public:
    IlvI8211FieldDeclCollection();
    ~IlvI8211FieldDeclCollection();

    IlvI8211FieldDeclaration*	find(const char*);
    void			add(IlvI8211FieldDeclaration* itm);

    IlInt			count() const;

protected:
    IlvI8211HashTable _array;
};

#endif /* !__Ilv_I8211fieldcol_H */
