// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/i8211decl.h
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
#ifndef __Ilv_I8211decl_H
#define __Ilv_I8211decl_H

#include <ilviews/maps/format/s57/i8211util.h>
#include <ilviews/maps/format/s57/i8211subdecl.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211FieldDeclaration : public IlvI8211RefCount
{
public:
    IlvI8211FieldDeclaration(const char* name = 0);

    IlvI8211SubFieldDeclaration*	get(IlInt ndx);
    void				add(IlvI8211SubFieldDeclaration* itm);

    IlvI8211SubFieldDeclaration*	getSubField(const IlString& name);

    IlBoolean				hasMoreData();

    void				setData(const char*, IlInt);
    void				nextData();

    IlInt				count() const;

    void				setName(const char*);
    const char*				getName() const;
    inline const IlString&		getStringName() const { return _name; }
    IlBoolean				isThis(const IlString&) const;

protected:
    IlvI8211SubFieldDeclaration**	_array;
    IlInt				_arrayCount;
    IlInt				_curPos;
    char*				_data;
    IlInt				_dataLength;
    IlString				_name;

    ~IlvI8211FieldDeclaration();
};

#endif /* !__Ilv_I8211decl_H */

