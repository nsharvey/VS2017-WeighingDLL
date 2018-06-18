// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/i8211pos.h
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
#ifndef __Ilv_I8211pos_H
#define __Ilv_I8211pos_H

#include <ilviews/base/value.h>
#include <ilviews/maps/format/s57/i8211util.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211FieldPosition : public IlvI8211RefCount
{
public:
    IlvI8211FieldPosition(const char* name, int length, int pos);

    void		setLength(int l);
    int			getLength() const;

    void		setPosition(int pos);
    int			getPosition() const;

    void		setName(const char* n);
    const char*		getName() const;
    IlBoolean		isSameName(const IlString&) const;

    virtual char*	extractFrom(const char* data,
				    IlInt       length,
				    IlInt&      len);

protected:
    virtual ~IlvI8211FieldPosition();

    IlString		_name;
    int			_length;
    int			_position;
};

#endif /* !__Ilv_I8211pos_H */
