// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/ora8obj.cpp
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
// This example illustrates exchanges of Oracle objects and varrays
//
// After connecting, types (see 'Global constants') and tables are created.
// Rows are inserted using bound parameters.
// The inserted values are retrieved using direct execution of queries
// Finally the database is cleaned up before exiting.
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
// Global constants
// ---------------------------------------------------------------------------
// Types
static const char* createTown =
    "create or replace type town as object (name varchar(20), \
inhabitants number(9))";
static const char* createTab = 
    "create type inttab as varray (6) of number(6)";

// Tables
static const char* createCountries =
    "create table countries(name varchar(20), capital town)";
static const char* createVersions =
    "create table pversions (pname varchar(12), pvers inttab)";

// ----------------------------------------------------------------------------
// Cleaning up utility
static void
Ending (IldDbms* dbms,
		IldRequest* request,
		const char* msg,
		int status)
{
    if (!dbms)
	cout << "Internal Error: Null Dbms!" << endl;
    else {
	if (dbms->isErrorRaised())
	    IldDisplayError(msg, dbms);
	else if (request && request->isErrorRaised())
	    IldDisplayError(msg, request);
	else
	    cout << msg << endl;
	cout << "Droping table \"countries\"" << endl;
	if (!dbms->execute("drop table countries"))
	    IldDisplayError("Drop table failed: ", dbms);
	cout << "Droping type \"town\"" << endl;
	if (!dbms->execute("drop type town"))
	    IldDisplayError("Drop type failed: ", dbms);
	cout << "Droping table \"pversions\"" << endl;
	if (!dbms->execute("drop table pversions"))
	    IldDisplayError("Drop table failed: ", dbms);
	cout << "Droping type \"inttab\"" << endl;
	if (!dbms->execute("drop type inttab"))
	    IldDisplayError("Drop type failed: ", dbms);
    }
    IldEndSample(dbms, 0, 0, 0, status);
}

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    if ((argc != 3) || ((argc == 3) &&
			strncmp(argv[1], "oracle", 6))) {
	cout << "Usage: " << argv[0]
	     << " oracle{9|10|11} <connection string>" << endl;
	return 1;
    }
  
    IldDisplayHeader("Oracle : Abstract data types");
  
    // Stage 1 : connection then types and tables creation
    // --------------------------------------------------
    cout << "Connection to: " << argv[2] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed:", 1);
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Request allocation failed:", 1);
  
    // Objects
    cout << "Creating type : " << createTown << endl;
    if (!request->execute(createTown))
	IldEndSample(dbms, request, 0, "Type creation failed:", 1);
    cout << "Creating table : " << createCountries << endl;
    if (!request->execute(createCountries))
	Ending(dbms, request, "Table creation failed:", 1);
    cout << endl;

    // Varrays
    cout << "Creating type : " << createTab << endl;
    if (!request->execute(createTab))
	Ending(dbms, request, "Type creation failed:", 1);
    cout << "Creating table : " << createVersions << endl;
    if (!request->execute(createVersions))
	Ending(dbms, request,"Table creation failed:", 1);
    cout << endl;

    // Stage 2 : Insert rows using parameters
    // --------------------------------------
    // Objects
    // -------
    //   1/ parse the insertion request
    const char* parseObj = "insert into countries values (:name , :town)";
    cout << "Parsing insertion request : " << parseObj << endl;
    if (!request->parse(parseObj))
	Ending(dbms, request, "Parse failed: ", 1);
    cout << endl;
  
    //   2/ declare the variables
    cout << "Binding input variable :name of type string" << endl;
    if (!request->bindParam(":NAME", IldStringType, 21))
	Ending(dbms, request, "Variable binding failed:", 1);
    cout << "Binding input variable :town of type object" << endl;
    IldADTDescriptor* adt = dbms->getAbstractType("TOWN");
    if (dbms->isErrorRaised())
	Ending(dbms, request, "Cannot get type description", 1);
    if (!request->bindParam(":TOWN", IldObjectType, -1, 0, 0,
			    IlFalse, 0, adt))
	Ending(dbms, request, "Variable binding failed:", 1);
    cout << endl;
    
    //   3/ iterate while giving them some values
    const char* capitals[] = {"Washington", "Beijin", "Pretoria"};
    const char* countries[] = {"USA", "China", "S.Africa"};
    const IlInt inhabitants[] = {2000000, 12000000, 4000000};
    IldADTValue* town = new IldADTValue(adt);
    int i = 0;
    for ( ; i < 3 ; ++i) {
	if (!request->setParamValue(countries[i], 0))
	    Ending(dbms, request, "Set parameter failed:", 1);
	town->setValue(capitals[i], 0);
	town->setValue(inhabitants[i], 1);
	if (!request->setParamValue(town, 1))
	    Ending(dbms, request, "Set parameter failed:", 1);
    
	//  execute the insertion
	cout << "Inserting row" << endl;
	if (!request->execute())
	    Ending(dbms, request, "Execution failed: ", 1);
    }
    delete town;
    if (!dbms->commit())
	IldDisplayError("Commit failed:", dbms);

    // Varray
    // ------
    //   1/ parse the insertion request
    const char* parseArr = "insert into pversions values (:pname , :pvers)";
    cout << "Parsing insertion request : " << parseArr << endl;
    if (!request->parse(parseArr))
	Ending(dbms, request, "Parse failed: ", 1);
    cout << endl;
  
    //   2/ declare the variables
    cout << "Binding input variable :name of type string" << endl;
    if (!request->bindParam(":PNAME", IldStringType, 21))
	Ending(dbms, request, "Variable binding failed:", 1);
    cout << "Binding input variable :pvers of type collection" << endl;
    adt = dbms->getAbstractType("INTTAB");
    if (dbms->isErrorRaised())
	Ending(dbms, request, "Cannot get type description", 1);
    if (!request->bindParam(":PVERS", IldCollectionType, -1, 0, 0,
			    IlFalse, 0, adt))
	Ending(dbms, request, "Variable binding failed:", 1);
    cout << endl;
  
    //   3/ iterate while giving them some values
    const char* products[] = {"Views", "Solver", "Dblink"};
    IldADTValue* vers = new IldADTValue(adt);
    for (i = 0 ; i < 3 ; ++i) {
	if (!request->setParamValue(products[i], 0))
	    Ending(dbms, request, "Set parameter failed:", 1);
	vers->setValue((IlInt)i, 0);
	vers->setValue((IlInt)(i + 1), 1);
	vers->setValue((IlInt)(i + 2), 2);
	if (!request->setParamValue(vers, 1))
	    Ending(dbms, request, "Set parameter failed:", 1);
	
	//  execute the insertion
	cout << "Inserting row" << endl;
	if (!request->execute())
	    Ending(dbms, request, "Execution failed: ", 1);
    }
    delete vers;
    if (!dbms->commit())
	IldDisplayError("Commit failed:", dbms);

    // Stage 3 : select
    // ----------------
    // Objects
    // -------
    //   1/ Straight selection
    const char* selectObj = "select * from countries";
    cout << "Straight selection: " << selectObj << endl;
    if (!request->execute(selectObj))
	Ending(dbms, request, "Select failed: ", 1);
    cout << endl;
    //    2/ Show returned rows
    IldPrintTuple(request, IldNames);
    IldPrintTuple(request, IldSeparators);
    while (request->fetch().hasTuple())
	IldPrintTuple(request);
    if (request->isErrorRaised()) 
	IldDisplayError("Fetch failed: ", request);
    cout << endl;
  
    // Varray
    // -------
    //   1/ Straight selection
    const char* selectArr = "select * from pversions";
    cout << "Straight selection: " << selectArr << endl;
    if (!request->execute(selectArr))
	Ending(dbms, request, "Select failed: ", 1);
    cout << endl;
    //    2/ Show results
    IldPrintTuple(request, IldNames);
    IldPrintTuple(request, IldSeparators);
    while (request->fetch().hasTuple())
	IldPrintTuple(request);
    if (request->isErrorRaised()) 
	IldDisplayError("Fetch failed: ", request);
    cout << endl;
    
    // Stage 4 : drop everything and quit
    // ----------------------------------
    Ending(dbms, 0, "End of sample ...", 0);
}
