// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/i8211reader.h
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
#ifndef __Ilv_I8211reader_H
#define __Ilv_I8211reader_H

#include <ilviews/maps/format/s57/i8211field.h>
#include <ilviews/maps/format/s57/i8211fieldcol.h>
#include <ilviews/maps/format/s57/i8211dico.h>
#include <ilviews/maps/format/s57/i8211record.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#define FIRST_RECORDS_FOR_DEBUG -1
#define LAST_RECORDS_FOR_DEBUG -1
#define TRACE_DDR  8
#define TRACE_FIELDS 2
#define TRACE_SUBFIELDS 1
#define TRACE_VALUES 4

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvI8211Reader
{
public:
    IlvI8211Reader();
    virtual ~IlvI8211Reader();

    void		addRecord(IlvI8211Record* rec);
    IlvI8211Record**	getI8211Records();
    IlInt		getI8211RecordCount() const;

    void		read(IL_STDPREF ifstream* stream);
    char*		readData(IL_STDPREF ifstream* stream,
				 IlvI8211FieldDictionary& tags,
				 IlInt& length);
    void		parseDictionary(IlvI8211FieldDictionary& t,
					const char* descr,
					int nbCharLength, 
					int nbCharPos,
					int nbCharName);
    IlvI8211FieldDeclCollection* readDDR(IL_STDPREF ifstream* stream, 
					 IlvI8211FieldDictionary& tags);
    char*		extractStringField(char* data,
					   IlInt length,
					   IlInt& len,
					   IlvI8211SubFieldDeclaration* fpos);
    IlvI8211FieldDeclaration*	parseFields(const char* name,
					    const char* descr);

protected:
    void		reset();

    IlvI8211Record**	_records;
    IlInt		_count;
    IlInt		_size;
};


#endif /* !__Ilv_I8211reader_H */
