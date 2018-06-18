// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/i8211record.h
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
#ifndef __Ilv_I8211record_H
#define __Ilv_I8211record_H

#include <ilviews/maps/format/s57/i8211field.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211Record
{
public:
    IlvI8211Record();
    virtual ~IlvI8211Record();

    void		addField(IlvI8211Field*);

    IlvI8211Field**	getFields();
    IlvI8211Field**	getFields(const IlString& name, IlInt& count);

    IlvI8211Field*	getFirstField(const IlString& name) const;

    IlvI8211Field*	getFirstField(IlInt& pos, const IlString& name) const;

    IlvI8211Field*	getNextField(IlInt& after, const IlString& name) const;

protected:
    IlvI8211Field**	_fields;
    IlInt		_count;
    IlInt		_size;
};

#endif /* !__Ilv_I8211record_H */
