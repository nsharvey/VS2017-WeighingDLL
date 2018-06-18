// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/strtable.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliStringsTable class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Strtable_H
#define __Ili_Strtable_H

#ifndef __Ili_Table_H
#  include <ilviews/dataccess/table.h>
#endif

// --------------------------------------------------------------------------
// IliStringsTable
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliStringsTable : public IliTable
{
public:
    IliStringsTable(IlvDisplay* display);
    IliStringsTable(IlvDisplay* display,
		    const char* const* strings,
		    IlInt count,
		    IlBoolean copy = IlTrue);
    IliStringsTable(const IliStringsTable&);
    IliStringsTable(IlvDisplay*, IL_STDPREF istream& input);

    IliDeclareDTypeInfo(IliStringsTable);
    virtual void	write(IL_STDPREF ostream& output) const;
    int operator	==(const IliStringsTable&) const;

    virtual IlInt	getRowsCount() const;
    virtual IlBoolean	getValue(IlInt rowno,
				 IlInt colno,
				 IliValue& val) const;

    virtual void	clearRows();
    virtual IlBoolean	updateRow(IlInt, IliTableBuffer*);
    virtual IlBoolean	insertRow(IlInt, IliTableBuffer*);
    virtual IlBoolean	deleteRow(IlInt);
    virtual IlBoolean	moveRow(IlInt, IlInt);

    virtual IlBoolean	allowRowMove() const;
    const char* const*	getStrings(IlInt& count);
    void		setStrings(const char* const* strings,
				   IlInt count,
				   IlBoolean copy = IlTrue);
    const char*		getString(IlInt rowno);
    IlBoolean		setString(IlInt rowno, const char* str);
    IlBoolean		insertString(IlInt rowno, const char* str);
    IlBoolean		deleteString(IlInt rowno);
    IlBoolean		appendString(const char* str);
    IlInt		getStringIndex(const char*, IlInt from = 0);

    void		insertTable(IliTable* tbl,
				    IlInt colno = 0,
				    IlInt rowno = -1);

protected:
    char**		_strings;
    IlInt		_rowsCount;

    virtual ~IliStringsTable();
};

IliDeclareTypeInit_exp(ILV_INF_EXPORTED,IliStringsTable);

#endif
