// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/i8211subdecl.h
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
#ifndef __Ilv_I8211subdecl_H
#define __Ilv_I8211subdecl_H

#include <ilviews/base/value.h>
#include <ilviews/maps/format/s57/i8211pos.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211SubFieldDeclaration
: public IlvI8211FieldPosition
{
public:
    IlvI8211SubFieldDeclaration(IlString& name,
				char      type,
				int       length,
				int       pos);
    virtual ~IlvI8211SubFieldDeclaration();

    IlvValue*		computeValue(const char*,IlInt);
    const char*		computeStringValue(const char*,IlInt);
    IlInt		computeIntegerValue(const char*,IlInt);
    IlDouble		computeDoubleValue(const char*,IlInt);

    virtual char*	extractFrom(const char*,IlInt,IlInt&);

    char		getType();

protected:
    char		_type;
    IlString		_buffer;
};

#endif /* !__Ilv_I8211subdecl_H */
