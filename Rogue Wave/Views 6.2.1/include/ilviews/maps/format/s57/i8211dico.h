// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/i8211dico.h
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
#ifndef __Ilv_I8211dico_H
#define __Ilv_I8211dico_H

#include <ilviews/maps/format/s57/s57hash.h>
#include <ilviews/maps/format/s57/i8211pos.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211FieldDictionary
{
public:
    IlvI8211FieldDictionary();
    virtual ~IlvI8211FieldDictionary();

    void			reset();

    void			add(IlvI8211FieldPosition* pos);
    void			add(const char* name, int length, int pos);
    IlvI8211FieldPosition*	get(IlInt ndx);

    IlInt			getCount() const;

protected:
    IlvI8211FieldPosition**	_declarations;
    IlInt			_count;
    IlInt			_size;
};

#endif /* !__Ilv_I8211dico_H */
