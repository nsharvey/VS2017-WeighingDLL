// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/smplbnd.cpp
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
// This example illustrates the use of input and output bindings
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
static const char* DropTbl = "drop table DBLTABLE";

// ----------------------------------------------------------------------------
// Results display
// ----------------------------------------------------------------------------
static void
IldDisplayResults(IldRequest* request)
{
    cout << "Results: " << endl;
    if (request->getColCount()) {
	while (request->fetch().hasTuple() || !request->isCompleted())
	    if (request->isCompleted()) {
		if (!request->isColNull(0))
		    cout << request->getColIntegerValue(0);
		else 
		    cout << "-";
		cout << "\t";
		if (!request->isColNull(1))
		    cout << request->getColStringValue(1);
		else 
		    cout << "-";
		cout << endl;
	    }
    }
}

// -----------------------------------------------------------------------
// main function
// -----------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    if ((argc != 3) && (argc != 4)) {
	cout << "Usage: " << argv[0]
	     << " <RDBMS> <connection string> [async_mode_ON]" << endl;
	cout << "\tasync_mode_ON : any string ==> switches async mode ON."
	     << endl;
	return 1;
    }
  
    IldDisplayHeader("Array bind and fetch");
  
    // Stage 1 : connection to the RDBMS
    // ---------------------------------
    cout << "Connecting to: " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed", 1);
    if (argc == 4) {
	if (!dbms->setAsync(IlTrue))
	    IldEndSample(dbms, 0, 0, "Switch asynchronous mode failed.", 1);
	if (!dbms->isAsync())
	    IldEndSample(dbms, 0, 0, "Asynchronous mode is not turned ON.", 1);
    }

    cout << "Multi-lines mode turned on for all requests" << endl;
    dbms->setDefaultColArraySize(10);
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, request, 0, "Request allocation failed:", 1);
  
    const char* createStr = 
	((strcmp(dbms->getName(), "sybase")
	  && strcmp(dbms->getName(), "mssql")) ?
	 "create table DBLTABLE (num int, name char(20))"
	 : "create table DBLTABLE (num int null, name char(20) null)");
    cout << "Create a table: " << createStr << endl;
    do {
	if (!request->execute(createStr))
	    IldEndSample(dbms, request, 0, "Table creation failed: ", 1);
    } while (!request->isCompleted());
    cout << endl;
  
    // A few insertions 
    cout << "Proceeding to a few hard-coded insertions" << endl;
    do {
	if (!request->execute("insert into DBLTABLE values (1, 'Hi')"))
	    IldEndSample(dbms, request, DropTbl, "Insertion failed: ", 1);
    } while (!request->isCompleted());
    do {
	if (!request->execute("insert into DBLTABLE values (2, 'Saluti')"))
	    IldEndSample(dbms, request, DropTbl, "Insertion failed: ", 1);
    } while (!request->isCompleted());
    do {
	if (!request->execute("insert into DBLTABLE values (3, 'Hello')")) {
	    IldDisplayError("Insertion failed: ", request);
	    IldEndSample(dbms, request, DropTbl, 0, 1);
	}	
    } while (!request->isCompleted());
    do {
	if (!request->execute("insert into DBLTABLE values (4, 'Guten Tag')"))
	    IldEndSample(dbms, request, DropTbl, "Insertion failed: ", 1);
    } while (!request->isCompleted());
    do {
	if (!request->execute("insert into DBLTABLE values (5, 'Bonjour')"))
	    IldEndSample(dbms, request, DropTbl, "Insertion failed: ", 1);
    } while (!request->isCompleted());
    cout << "Inserted five lines" << endl << endl;
  
    // Stage 2 : Select with host variable
    // -----------------------------------
  
    const char* selectStr =
	((!strncmp(dbms->getName(), "oracle", 6) 
	  || !strcmp(dbms->getName(), "sqlbase")) ?
	 "select * from DBLTABLE where num > :1"
	 : "select * from DBLTABLE where num > ?");
    cout << "Parsing : " << selectStr << endl;
    do {
	if (!request->parse(selectStr))
	    IldEndSample(dbms, request, DropTbl, "Parse failed: ", 1);
    } while (!request->isCompleted()) ;
    
    cout << "Binding variable to integer type" << endl;
    if (!request->bindParam((IlUShort)0, IldIntegerType))
	IldEndSample(dbms, request, DropTbl, "Bind failed: ", 1);
    cout << "Variable value set to: 0" << endl;
    request->setParamValue((IlInt)0, 0);
    
    cout << "Execution" << endl;
    do {
	if (!request->execute())
	    IldEndSample(dbms, request, DropTbl, "Execute failed: ", 1);
    } while (!request->isCompleted());
    
    IldPrintResults(request);
    cout << endl;
  
    cout << "Changing value of host variable to 3" << endl;
    request->setParamValue((IlInt)3, 0);
    cout << "Executing with new value" << endl;
    do {
	if (!request->execute())
	    IldEndSample(dbms, request, DropTbl, "Execution failed: ", 1);
    } while (!request->isCompleted());
    
    IldPrintResults(request);
    if (request->isErrorRaised())
	IldEndSample(dbms, request, DropTbl, "Fetch failed:", 1);
    cout << endl;
  
    // Stage 3 : Insertion using host variables
    // ----------------------------------------
    cout << "Host variables array size set to 2" << endl;
    request->setParamArraySize(2);
  
    const char* parseStr =
	((!strncmp(dbms->getName(), "oracle", 6) 
	  || !strcmp(dbms->getName(), "sqlbase")) ?
	 "insert into DBLTABLE values(:1, :2)"
	 : "insert into DBLTABLE values(?, ?)");
    cout << "Parsing: " << parseStr << endl;
    do {
	if (!request->parse(parseStr))
	    IldEndSample(dbms, request, DropTbl, "Parsing failed: ", 1);
    } while (!request->isCompleted());
  
    cout << "Binding input variables" << endl;
    if (!request->bindParam((IlUShort)0, IldIntegerType))
	IldEndSample(dbms, request, DropTbl, "Binding failed: ", 1);
    if (!request->bindParam(1, IldStringType))
	IldEndSample(dbms, request, DropTbl, "Binding failed: ", 1);
    
    cout << "Variable values:" << endl;
    request->setParamValue((IlInt)6, 0, 0);
    request->setParamValue("Guten abend", 1, 0);
    // Variable #1 of row #0 is null : NAME will be null despite the value
    request->setParamNullInd(1, 0);

    request->setParamValue((IlInt)7, 0, 1);
    request->setParamValue("Bye bye", 1, 1);
    // Variable #0 of row #1 is null : NO will be null despite the value
    request->setParamNullInd(0, 1);
    cout << "\tRow Column Value         Null indicator" << endl;
    cout << "\t 0    0    6" << endl;
    cout << "\t 0    1    'Guten abend' set" << endl;
    cout << "\t 1    0    7             set" << endl;
    cout << "\t 1    1    'Bye bye'" << endl;

    cout << "Insertion of two rows at once" << endl;
    IlInt rowCount;
    do {
	if (!request->execute(&rowCount))
	    IldEndSample(dbms, request, DropTbl, "Execution failed : ", 1);
    } while (!request->isCompleted()) ;
    cout << "Row processed count " << rowCount << endl << endl;
  
    cout << "Selection: " << endl;
    do {
	if (!request->execute("select * from DBLTABLE"))
	    IldEndSample(dbms, request, DropTbl, "Selection failed: ", 1);
    } while (!request->isCompleted());
  
    IldDisplayResults(request);
    if (request->isErrorRaised())
	IldEndSample(dbms, request, DropTbl, "Fetch failed:", 1);
    cout << "\tNote that columns #1 of row #6 and #0 of row #7 are null." 
	 << endl << "\tThis was intentionnaly done." << endl << endl;

    // Stage 4: Update with host variables
    // -----------------------------------
    const char* updateStr =
	((!strncmp(dbms->getName(), "oracle", 6)
	  || !strcmp(dbms->getName(), "sqlbase")) ?
	 "update DBLTABLE set name = :1 where num = :2"
	 : "update DBLTABLE set name = ? where num = ?");
    cout << "Parsing: " << updateStr << endl;
    do {
	if (!request->parse(updateStr))
	    IldEndSample(dbms, request, DropTbl, "Parse failed: ", 1);
    } while (!request->isCompleted());
  
    cout << "Bind variables:" << endl;
    if (!request->bindParam((IlUShort)0, IldStringType))
	IldEndSample(dbms, request, DropTbl, "Binding failed: ", 1);
    if (!request->bindParam(1, IldIntegerType)) {
	IldDisplayError("Binding failed: ", request);
	IldEndSample(dbms, request, DropTbl, 0, 1);
    }
    
    cout << "Variable values:" << endl;
    request->setParamValue((IlInt)6, 1, 0);
    request->setParamValue("Good night", 0, 0);
    request->setParamValue((IlInt)7, 1, 1);
    request->setParamValue("Arivederci", 0, 1);
    cout << "\tRow Column Value" << endl;
    cout << "\t 0    0    'Good night'" << endl;
    cout << "\t 0    1    6" << endl;
    cout << "\t 1    0    'Arivederci'" << endl;
    cout << "\t 1    1    7" << endl;
    // Since the "count" argument is set to 1, there will be only one 
    // update performed despite the variable array size set to 2 !!
    cout << "Repeated execute with count set to 1" << endl;
    do {
	if (!request->execute(&rowCount, 1))
	    IldEndSample(dbms, request, DropTbl, "Execution failed : ", 1);
    } while (!request->isCompleted());
    cout << "Row processed count " << rowCount << endl << endl;
    
    cout << "Selection : " << endl;
    do {
	if (!request->execute("select * from DBLTABLE"))
	    IldEndSample(dbms, request, DropTbl, "Selection failed: ", 1);
    } while (!request->isCompleted());

    IldDisplayResults(request);
    cout << "\tNote that only the first row has been updated." 
	 << endl << "\tThis was intentionnaly done." << endl;
    cout << endl;
    
    // Stage 5 : clean up
    // ------------------
    IldEndSample(dbms, request, DropTbl, "Cleaning up and exiting");
}
