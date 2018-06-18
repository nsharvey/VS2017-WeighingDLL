// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/sybcomp.cpp
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
// This program shows how to process the results of a query which contains
// "COMPUTE" clauses. This is a SYBASE specific extension to SQL standard.
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
// Clean up utility
// ----------------------------------------------------------------------------
static const char* DropStr = "drop table atable";

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    if ((argc != 2) && (argc != 3)) {
	cout << "Usage: " << argv[0]
	     << " <connection string> [async_mode_ON]" << endl;
	cout << "\tasync_mode_ON : any string ==> switches async mode ON."
	     << endl;
	exit(1);
    }
    
    IldDisplayHeader("Sybase compute clauses");
  
    cout << "Connecting to : " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect("sybase", argv[1]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed: ", 1);
    cout << endl;
    if (argc == 3) {
	if (!dbms->setAsync(IlTrue))
	    IldEndSample(dbms, 0, 0, "Switch asynchronous mode failed.", 1);
	if (!dbms->isAsync())
	    IldEndSample(dbms, 0, 0, "Asynchronous mode is not turned ON.", 1);
    }
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Request allocation failed:", 1);
    // Just in case, don't mind for the result
    do {
	request->execute("drop table atable");
    } while (!request->isCompleted());
    
    // Table creation.
    const char* createStr = "create table atable (f1 int)";
    cout << "Creation of a table : " << createStr << endl;
    do {
	if (!request->execute(createStr))
	    IldEndSample(dbms, request, 0, "Cannot create table:", 1);
    } while (!request->isCompleted());
    cout << endl;
    
    cout << "Inserting four rows" << endl;
    do {
	request->execute("insert into atable values(1)");
    } while (!request->isCompleted());
    do {
	request->execute("insert into atable values(2)");
    } while (!request->isCompleted());
    do {
	request->execute("insert into atable values(3)");
    } while (!request->isCompleted());
    do {
	request->execute("insert into atable values(4)");
    } while (!request->isCompleted());
    const char* selectStr = "select f1 from atable \
compute min(f1), max(f1) compute avg(f1)";
    cout << "Selecting : " << selectStr << endl;
    do {
	if (!request->execute(selectStr))
	    IldEndSample(dbms, request, DropStr, "Selection failed:", 1);
    } while (!request->isCompleted());
    cout << endl;
    
    cout << "Normal result set :" << endl;
    IldPrintTuple(request, IldNames);
    IldPrintTuple(request, IldSeparators);
    while (request->fetch().hasTuple() || !request->isCompleted())
	if (request->isCompleted())
	    IldPrintTuple(request);
    if (request->isErrorRaised())
	IldEndSample(dbms, request, DropStr, "Fetch failed:", 1);
    cout << endl << "First compute clause : MIN & MAX of f1 " << endl;
    while (request->fetch().hasTuple() || !request->isCompleted())
	if (request->isCompleted()) {
	    IldPrintTuple(request, IldNames);
	    IldPrintTuple(request, IldSeparators);
	    IldPrintTuple(request);
	}
    if (request->isErrorRaised())
	IldEndSample(dbms, request, DropStr, "Fetch failed:", 1);
  
    cout << endl << "Second compute clause : AVG of f1 " << endl;
    while (request->fetch().hasTuple() || !request->isCompleted())
	if (request->isCompleted()) {
	    IldPrintTuple(request, IldNames);
	    IldPrintTuple(request, IldSeparators);
	    IldPrintTuple(request);
	}
    if (request->isErrorRaised())
	IldEndSample(dbms, request, DropStr, "Fetch failed:", 1);
    cout << endl;
  
    IldEndSample(dbms, request, DropStr, "Cleaning up and exiting.");
}
