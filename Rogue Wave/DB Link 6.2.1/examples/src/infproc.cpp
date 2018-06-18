// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/infproc.cpp
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
// This sample illustrates calling an INFORMIX stored procedure using 
// Rogue Wave DB Link.
//
// The first procedure takes two parameters:
//     the first one is a user name,
//     the second one is the name of a table.
//
// The second procdure takes only one parameter:
//     an integer value.
//
// Parameter bindings:
// -------------------
//
// Procedure execution:
// --------------------
// The procedures return a results set.
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
// Globals
// ----------------------------------------------------------------------------
static const char* getProcIdDef =
"CREATE PROCEDURE getProcId \
		(uNameIn CHAR(10), tNameIn CHAR(15)) RETURNING CHAR(15), INT \
	DEFINE tNameOut CHAR(15) ;\
	DEFINE tIdOut INT ;\
\
	FOREACH \
		SELECT tabname, tabid INTO tNameOut, tIdOut \
			FROM systables \
			WHERE owner = uNameIn AND tabname LIKE tNameIn \
		RETURN tNameOut, tIdOut WITH RESUME ; \
	END FOREACH ; \
END PROCEDURE ;";

static const char* insTmpDef =
"CREATE PROCEDURE insTmp (n INT) \
	INSERT INTO tmpTable values (n) ; \
END PROCEDURE ;";

static const char* getProcIdExec =
"EXECUTE PROCEDURE getProcId(USER, ?) ;";

static const char* insTmpExec =
"EXECUTE PROCEDURE insTmp(?) ;";

static const char* DropTmpT = "DROP TABLE tmptable ;";
static const char* DropTemp = "DROP TABLE temp ;";

// ----------------------------------------------------------------------------
// Execute procedure getProcId
// ----------------------------------------------------------------------------
IlInt
IldGetProcIdExec(IldRequest* request)
{
    // User memory spaces
    char tName[15 + 1];  // Table Name.
  
    cout << "Parsing command: " << getProcIdExec << endl;
    if (!request->parse(getProcIdExec)) {
	IldDisplayError("Parsing command:", request);
	return 0;
    }
    cout << "Binding parameter table name of type string" << endl;
    if (!request->bindParam((IlUShort)0, IldStringType, 15, tName)) {
	IldDisplayError("Binding table Name:", request);
	return 0;
    }

    // ----------------------------------------
    // First value
    strcpy(tName, "tmptable");
    cout << "Executing procedure call with parameter = "
	 << tName << endl;
    if (!request->execute()) {
	IldDisplayError("Execution failed:", request);
	return 0;
    }
    // ----------------------------------------
    // Results
    cout << "Results from procedure call:" << endl;
    IldPrintResults(request);

    // ----------------------------------------
    // Second value
    strcpy(tName, "t%");
    // ----------------------------------------
    cout << "Executing procedure call with parameter = "
	 << tName << endl;
    if (!request->execute()) {
	IldDisplayError("Execution failed:", request);
	return 0;
    }
    // ----------------------------------------
    // Results
    cout << "Results from procedure call:" << endl;
    IldPrintResults(request);
    cout << endl;
    return 1;
}

// ----------------------------------------------------------------------------
// Execute procedure insTmp
// ----------------------------------------------------------------------------
IlInt
IldInsTmpExec(IldRequest* request)
{
    cout << "Parsing command: " << insTmpExec << endl;
    if (!request->parse(insTmpExec)) {
	IldDisplayError("Parsing command :", request);
	return 0;
    }

    // ----------------------------------------
    // Set cursor parameter array size.
    if (!request->setParamArraySize(3)) {
	IldDisplayError("Could not set cursor parameter array size : ",
			request);
	return 0;
    }
    cout << "Binding parameter of type integer" << endl;
    if (!request->bindParam((IlUShort)0, IldIntegerType, -1, 0))
	IldDisplayError("Binding integer parameter:", request);

    // ----------------------------------------
    // Set values.
    request->setParamValue((IlInt)12, 0, 0);
    request->setParamValue((IlInt)33, 0, 1);
    request->setParamValue((IlInt)54, 0, 2);
    // ----------------------------------------
    cout << "Executing procedure call." << endl;
    if (!request->execute()) {
	IldDisplayError("Execution failed:", request);
	return 0;
    }
    // ----------------------------------------
    // Results
    cout << "Results from procedure call:" << endl;
    IldPrintResults(request);
    // ----------------------------------------
    // Reset cursor parameter array size to 0.
    if (!request->setParamArraySize(0)) {
	IldDisplayError("Could not reset cursor parameter array size: ",
			request);
	return 0;
    }
    // ----------------------------------------
    // Check values inserted into the table.
    if (!request->execute("select * from tmpTable ;")) {
	IldDisplayError("Could not access values of tmpTable: ",
			request);
	return 0;
    }
    // ----------------------------------------
    // Results
    cout << "Results from insertion:" << endl;
    IldPrintResults(request);
    cout << endl;
    return 1;
}

// ----------------------------------------------------------------------------
// Cleaning up
// ----------------------------------------------------------------------------
void
IldDropAll (IldDbms* dbms)
{
    cout << "Dropping tables and procedures." << endl;
    if (!dbms->execute("DROP PROCEDURE insTmp ;"))
	IldDisplayError("Drop procedure insTmp failed:", dbms);
    if (!dbms->execute("DROP PROCEDURE getProcId ;"))
	IldDisplayError("Drop procedure getProcId failed:", dbms);
    if (!dbms->execute(DropTemp))
	IldDisplayError("Drop table temp failed:", dbms);
    if (!dbms->execute(DropTmpT))
	IldDisplayError("Drop table tmptable failed:", dbms);
}

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    if (argc != 3) {
	cout << "Usage: " << argv[0]
	     << "informix{ |72|9} <connection string>" << endl;
	return 1;
    }
    IldDisplayHeader("Informix stored procedure");
  
    // ----------------------------------------
    // Connection
    cout << "Connecting to: " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed: ", 1);
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, request, 0, "Request allocation failed: ", 1);

    // ----------------------------------------
    // Create tables
    cout << "Tables creation." << endl;
    if (!request->execute("create table tmptable (i int) ;"))
	IldEndSample(dbms, request, 0, "Table tmpTable creation failed:", 1);
    if (!request->execute("create table temp (s char(12), d date) ;"))
	IldEndSample(dbms, request, DropTmpT, "Table temp creation failed", 1);

    // ----------------------------------------
    // Create procedures
    cout << "Procedures creation." << endl << endl;
    if (!request->execute(getProcIdDef)) {
	IldDropAll(dbms);
	IldEndSample(dbms, request, 0,
		     "Procedure getProcId creation failed:", 1);
    }
    if (!request->execute(insTmpDef)) {
	IldDropAll(dbms);
	IldEndSample(dbms, request, 0, "Procedure insTmp creation failed:", 1);
    }
  
    // First procedure execution
    // ----------------------------------------
    if (!IldGetProcIdExec(request)) {
	IldDropAll(dbms);
	IldEndSample(dbms, request, 0, 0, 1);
    }
    // Second procedure execution
    // ----------------------------------------
    if (!IldInsTmpExec(request)) {
	IldDropAll(dbms);
	IldEndSample(dbms, request, 0, 0, 1);
    }
  
    // ----------------------------------------
    // Drop tables and procedures
    IldDropAll(dbms);

    // Never returns
    IldEndSample(dbms, request, 0, "Cleaning up and exiting.");
}
