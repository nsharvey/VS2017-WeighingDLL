// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/sample.cpp
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
// This program connects itself to a database, creates a table, inserts
// some tuples, selects and prints them, drops the table and then
// disconnects itself from the database.
//
// Notes:
//	+ This example is independent of the RDBMS; hence, it needs the
//	RDBMS name (argv[1]), and of course the database name (argv[2]).
//
//	+ The program prints the name of selected items before printing
//	the values. Those values are returned by specialized accessors
//	of the C++ class "IldRequest". The
//	"IldRequest::getColType" member function (not used in
//	the following code because not necessary) helps you choose the
//	correct value accessor at each position in the current tuple.
//
//	+ The deletion of "dbms" ensures the deletion of the "IldRequest"
//	instance "request".
//
//	+ The helper functions (IldDisplayHeader, IldEndSample, ...) code
//	can be found in the file ildutil.cpp.
// ----------------------------------------------------------------------------

#include "ildutil.h"

#ifdef IL_STD
# ifndef _CSTDIO_
#  include <cstdio>
# endif
# ifndef _CSTDLIB_
#  include <cstdlib>
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
# ifndef _IOSTREAM_H
#  include <iostream.h>
# endif
#endif

IL_STDUSE

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int
main(int argc,
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
	IldEndSample(dbms, 0, 0, "Connection failed.", 1);
    cout << endl;
    
    cout << "Creating a request: " << endl;
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, request, 0, "Creation of request failed", 1);
    cout << endl;
  
    // Table creation. 
    const char* createStr = "create table ATABLE(F1 int,F2 char(20))";
    cout << "Creating a table: " << createStr << endl;
    if (!request->execute(createStr))
	IldEndSample(dbms, request, 0, "Table creation failed", 1);

    // Data insertion.
    cout << "Data insertion: " << endl;
    const char* insertStr1 = "insert into ATABLE values(40,'Forty')";
    cout << "Row #1: " << insertStr1 << endl;
    if (!request->execute(insertStr1)) 
	IldDisplayError("Insertion failed:", request);
    const char* insertStr2 =
	"insert into ATABLE values(-3,'Minus Three')";
    cout << "Row #2: " << insertStr2 << endl;
    if (!request->execute(insertStr2))
	IldDisplayError("Insertion failed:", request);
    const char* insertStr3 =
	"insert into ATABLE values(-10,'Minus Ten')";
    cout << "Row #3: " << insertStr3 << endl;
    if (!request->execute(insertStr3))
	IldDisplayError("Insertion failed:", request);
    const char* insertStr4 = "insert into ATABLE values(6,'Six')";
    cout << "Row #4: " << insertStr4 << endl;
    if (!request->execute(insertStr4))
	IldDisplayError("Insertion failed:", request);
    cout << endl;
    
    // Data selection.
    const char* selectStr = "select * from ATABLE";
    cout << "Retrieving all rows: " << selectStr << endl;
    if (!request->execute(selectStr))
	IldDisplayError("Select failed: ", request);
    else {
	// Print selected item names.
	cout << "\t ATABLE" << endl;
	IldPrintTuple(request, IldNames);
	IldPrintTuple(request, IldSeparators);
	
	// Print selected item values.
	while (request->fetch().hasTuple())
	    IldPrintTuple(request);
    }
    if (request->isErrorRaised())
	IldDisplayError("Fetch failed", request);
    cout << endl;
    // Cleaning up and exiting.
    IldEndSample(dbms, request, 
		 "drop table ATABLE", "Cleaning up and exiting", 0);
}
