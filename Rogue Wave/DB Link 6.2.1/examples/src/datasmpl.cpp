// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/datasmpl.cpp
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
// This program illustrates the use of DB Link classes IldDateTime and 
// IldNumeric along with the features "date as object", "numeric as string" and
// "numeric as object". 
//
// It creates a table with columns of these types, proceed
// to a few insertions then retrieves the inserted values.
//
// ----------------------------------------------------------------------------

#include "ildutil.h"

#ifdef IL_STD
# ifndef _CSTDIO_
#  include <cstdio>
# endif
# ifndef _CSTDLIB_
#  include <cstdlib>
# endif
# ifndef _CSTRING_
#  include <cstring>
# endif
# ifndef _IOSTREAM_
#  include <iostream>
# endif
#else
# ifndef _STDIO_H
#  include <stdio.h>
# endif
# ifndef _STDLIB_H
#  include <stdlib.h>
# endif
# ifndef _STRING_H
#  include <string.h>
# endif
# ifndef _IOSTREAM_H
#  include <iostream.h>
# endif
#endif

#ifdef IL_STD
# ifndef _STRSTREAM_
#  include <strstream>
# endif
#else
# ifndef _STRSTREAM_H_
#  ifndef WINDOWS
#   include <strstream.h>
#  else
#   include <strstrea.h>
#  endif
# endif
#endif

IL_STDUSE

// ----------------------------------------------------------------------------
// Constants
// ----------------------------------------------------------------------------
const char* DropStr = "drop table ATABLE";

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void
CreateTable(IldDbms* dbms,
	    IldRequest* request)
{
    // Check if connected via ODBC, and to which RDBMS ?
    if (!strcmp(dbms->getName(), "odbc")) {
	// For ODBC, set Auto Commit Mode ON:
	if (!dbms->autoCommitOn())
	    IldEndSample(dbms, request, 0,
			 "Could not switch autoCommit mode On.", 1);
    }
    char createStr[80];
    ostrstream ostr(createStr, 80);
    ostr << "create table ATABLE(F1 " << IldGetNumericTypeName(dbms)
	 << ", F2 " << IldGetDateTypeName(dbms) <<  ")" << ends;
    cout << "Creating a table: " << createStr << endl;
    if (!dbms->execute(createStr))
	IldEndSample(dbms, request, 0, "Table creation failed", 1);
    cout << endl;
}

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void
ReadData (IldDbms* dbms,
	  IldRequest* request)
{
    // Data selection.
    request->setStringDateUse(IlTrue);
    request->setStringNumericUse(IlTrue);
    const char* selectStr = "select * from ATABLE";
    cout << "Retrieving with datetime and numeric as strings" << endl;
    if (!request->execute(selectStr))
	IldEndSample(dbms, request, DropStr, "Select failed", 1);
    IldPrintResults(request);
    cout << endl;

    request->setStringDateUse(IlFalse);
    cout << "Retrieving with datetime as objects and numeric as strings"
    	 << endl;
    if (!request->execute(selectStr))
    	IldEndSample(dbms, request, DropStr, "Select failed", 1);
    IldPrintResults(request);
    cout << endl;
}

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void
InsertObjects (IldDbms* dbms,
	       IldRequest* request)
{
    IlInt nbRow = 0;
    cout << "Binding first parameter to string type." << endl;
    if (!request->bindParam((IlUShort)0, IldStringType))
	IldEndSample(dbms, request, DropStr,
		     "First variable binding failed", 1);
    cout << "Binding second parameter to datetime type." << endl;
    if (!request->bindParam(1, IldDateTimeType))
	IldEndSample(dbms, request, DropStr,
		     "Second variable binding failed", 1);
    cout << endl;
    
    cout << "Setting parameter values: 123456789.012345, 1996/03/02" << endl;
    request->setParamValue("123456789.012345", 0);
    IldDateTime* dt = new IldDateTime(1996, 3, 2); // 1996/03/02
    request->setParamValue(dt, 1);
    if (!request->execute(&nbRow))
	IldEndSample(dbms, request, DropStr, "First insertion failed", 1);
    else
	cout << "Inserted " << nbRow << " row(s)." << endl;
    cout << "Setting parameter values: 987654321.654321, 1996/01/25" << endl;
    request->setParamValue("987654321.654321", 0);
    dt->setMonth(1);				// 1996/01/25
    dt->setDay(25);
    request->setParamValue(dt, 1);
    if (!request->execute(&nbRow))
	IldEndSample(dbms, request, DropStr, "Second insertion failed", 1);
    else
	cout << "Inserted " << nbRow << " row(s)." << endl;
    
    cout << "Setting parameter values: 987654321.654321, " 
	 << "1996/02/12 14:33:44.000" << endl;
    request->setParamValue("987654321.654321", 0);
    dt->setMonth(2);				// 1996/02/12 14:33:44.000
    dt->setDay(12);
    dt->setTime(14, 33, 44);
    request->setParamValue(dt, 1);
    if (!request->execute(&nbRow))
	IldEndSample(dbms, request, DropStr, "Third insertion failed", 1);
    else
	cout << "Inserted " << nbRow << " row(s)." << endl;
    cout << "Setting parameter values: 00987654321, " 
	 << "1996/02/12 14:33:44.000" << endl;
    request->setParamValue("00987654321", 0);
    request->setParamValue(dt, 1);
    if (!request->execute(&nbRow))
	IldEndSample(dbms, request, DropStr, "Fourth insertion failed", 1);
    else
	cout << "Inserted " << nbRow << " row(s)." << endl;
    cout << "Setting parameter values: -1.0012, 1996/02/12 14:33:44.000"
	 << endl;
    request->setParamValue("-1.0012", 0);
    request->setParamValue(dt, 1);
    if (!request->execute(&nbRow))
	IldEndSample(dbms, request, DropStr, "Fifth insertion failed", 1);
    else
	cout << "Inserted " << nbRow << " row(s)." << endl;
    cout << "Setting parameter values: 1.0012, 1996/02/12 14:33:44.000"
	 << endl;
    request->setParamValue("1.0012", 0);
    request->setParamValue(dt, 1);
    if (!request->execute(&nbRow))
	IldEndSample(dbms, request, DropStr, "Sixth insertion failed", 1);
    else
	cout << "Inserted " << nbRow << " row(s)." << endl;

    if (dt)
	delete dt;
    cout << endl;
    dbms->commit(request);
}

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int main(int argc,
	 char** argv)
{
    if (argc != 3) {
	cout << "Usage: " << argv[0]
	     << " <RDBMS name> <connection string>" << endl;
	exit(1);
    }
    IldDisplayHeader("Data manipulation sample");
    cout << "Connecting to: " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed: ", 1);

    cout << "Creating a request: " << endl;
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Creation of request failed: ", 1);
    cout << endl;

    // Table creation, then parse insertion request
    CreateTable(dbms, request);
    // Use DateTime structures
    request->setStringDateUse(IlFalse);
    // Data insertion: note that SQL code should be in RDBMS native form
    cout << "Data insertion: " << endl;
    char* dbOdbc = IldGetOdbcDbms(dbms);
    const char* insertStr =
	(!strncmp(dbms->getName(), "oracle", 6) ?
	 "insert into ATABLE values(:1, :2)"
	 : ((!strcmp(dbms->getName(), "mssql") ||
	     !strcmp(dbms->getName(), "oledb") ||
	     !IldStrNICaseCmp(dbOdbc, "Microsoft SQL Server", 20)) ?
	    "insert into ATABLE values (convert(numeric(28, 9), ?), ?)"
	    : "insert into ATABLE values(?, ?)"));
    delete [] dbOdbc;
    cout << "Parsing: " << insertStr << endl;
    if (!request->parse(insertStr))
	IldEndSample(dbms, request, DropStr, "Parse of insert failed", 1);
    cout << endl;

    // Insertion using IldDateTime objects
    InsertObjects(dbms, request);

    // Data selection.
    ReadData(dbms, request);

    // Clean up and exit
    IldEndSample(dbms, request, DropStr, "Dropping table", 0);
}
