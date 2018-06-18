// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/inf9obj.cpp
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
// Informix Universal Server user defined types usage
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
// 

// Types
static const char* createTerm =
	"create distinct type term as date";
static const char* createEmployee = 
	"create row type employeeT (firstname varchar(20), lastname varchar(20))";

// Tables
static const char* createPersonels =
	"create table personels (id integer, emp employeeT)";
static const char* createVersions =
	"create table versions (responsible varchar(20), deliveries \
list(term not null))";

// ----------------------------------------------------------------------------
// Cleaning up utility
static void
Ending (IldDbms* dbms,
		IldRequest* request,
		const char* msg,
		int st)
{
    if (!dbms) 
	cout << "Internal Error: Null dbms!" << endl;
    else {
	if (dbms && dbms->isErrorRaised())
	    IldDisplayError(msg, dbms);
	else if (request && request->isErrorRaised())
	    IldDisplayError(msg, request);
	else
	    cout << msg << endl;
	cout << "Cleaning up:" << endl;
	if (request)
	    request->closeCursor();
	const char* DropPersonels = "drop table personels";
	cout << "\t" << DropPersonels << endl;
	if (!dbms->execute(DropPersonels))
	    IldDisplayError("Drop table failed: ", dbms);
	const char* DropVersions = "drop table versions";
	cout << "\t" << DropVersions << endl;
	if (!dbms->execute(DropVersions))
	    IldDisplayError("Drop table failed: ", dbms);
	const char* DropEmpT = "drop row type employeeT restrict";
	cout << "\t" << DropEmpT << endl;
	if (!dbms->execute(DropEmpT))
	    IldDisplayError("Drop type failed: ", dbms);
	const char* DropTermT = "drop type term restrict";
	cout << "\t" << DropTermT << endl;
	if (!dbms->execute(DropTermT))
	    IldDisplayError("Drop type failed: ", dbms);
    }
    // This call never returns
    IldEndSample(dbms, request, 0, 0, st);
}

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int main(int argc,
		 char** argv)
{
    if (argc != 2) {
		cout << "Usage: " << argv[0] << " <connection string>" << endl;
		return 1;
    }
  
    IldDisplayHeader("Informix9: Abstract data types");
  
    // Stage 1 : connection then types and table creation
    // --------------------------------------------------
    cout << "Connection to: " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect("informix9", argv[1]);
    if (dbms->isErrorRaised())
		IldEndSample(dbms, 0, 0, "Connection failed", 1);
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
		IldEndSample(dbms, 0, 0, "Request allocation failed", 1);
  
    cout << "Creating type : " << createTerm << endl;
    if (!request->execute(createTerm))
		IldEndSample(dbms, 0, 0, "Type creation failed", 1);
    cout << "Creating type : " << createEmployee << endl;
    if (!request->execute(createEmployee))
		Ending(dbms, request, "Type creation failed:", 1);
    cout << "Creating table : " << createPersonels << endl;
    if (!request->execute(createPersonels))
		Ending(dbms, request, "Table creation failed:", 1);
    cout << endl;

    cout << "Creating table : " << createVersions << endl;
    if (!request->execute(createVersions))
		Ending(dbms, request, "Table creation failed:", 1);
    cout << endl;

    // Stage 2 : Insert rows using parameters
    // --------------------------------------
    // Create the mandatory first line
	static const char* insStmt = 
		"insert into personels values (1, 'row(''Adam'', ''Ski'')')";
	if (!request->execute(insStmt))
		Ending(dbms, request, "Insertion of first line failed", 1);
    // Object table
    // Now get the type descriptor: it is a named row type
    IldADTDescriptor* adt = dbms->getAbstractType("employeet");
    if (dbms->isErrorRaised())
		Ending(dbms, request, "Can not get employeeT description", 1);
    //   1/ parse the insertion request
    const char* parseObj =
		"insert into personels values (? , ?)";
    cout << "Parsing insertion request: " << parseObj << endl;
    if (!request->parse(parseObj))
		Ending(dbms, request, "Parse failed: ", 1);
    cout << endl;
  
    //   2/ declare the variables
    cout << "Binding first input variable of type string" << endl;
    if (!request->bindParam((IlUShort)0, IldIntegerType))
		Ending(dbms, request, "Variable binding failed:", 1);
    cout << "Binding second input variable of type object" << endl;
    if (!request->bindParam(1, IldObjectType, -1, 0, 0, IlFalse, 0, adt))
		Ending(dbms, request, "Variable binding failed:", 1);
    cout << endl;
  
    //   3/ iterate while giving them some values
    IldADTValue empObj(adt, "personels");
    const char* firstnames[] = {"Joe", "Louis", "Sydney"};
    const char* lastnames[] = {"Barr", "Jempell", "King"};
    int i = 0;
    for ( ; i < 3 ; ++i) {
		empObj.setValue(firstnames[i], 0);
		empObj.setValue(lastnames[i], 1);
		if (!request->setParamValue((IlInt)(i + 2), 0))
			Ending(dbms, request, "Set parameter failed:", 1);
		if (!request->setParamValue(&empObj, 1))
			Ending(dbms, request, "Set parameter failed:", 1);
    
		//  execute the insertion
		cout << "Inserting row" << endl;
		if (!request->execute())
			Ending(dbms, request, "Execution failed: ", 1 );
    }

    // Table with a list
    // Get the ADT descriptor of the collection type column
    IldRelation* rel = dbms->getRelation("versions");
    if (dbms->isErrorRaised())
		Ending(dbms, request, "Get relation failed", 1);
    IldPrintRelation(*rel);
    // We know the column is the second one.
    adt = rel->getColumn(1)->getADTDescriptor();
    // A first line must be present in order to retrieve the collection desc
    if (!request->execute("insert into versions values ('First', 'list{''01/01/1992''}')"))
		Ending(dbms, request, "Initial insert failed", 1);
    // 1/ Parse the insert request
    const char* parseList = "insert into versions values (?, ?)";
    cout << "Parsing insertion statement: " << parseList << endl;
    if (!request->parse(parseList))
		Ending(dbms, request, "Parse failed", 1);
    cout << endl;

    // 2/ Declare variables
    if (!request->bindParam((IlUShort)0, IldStringType, 21))
		Ending(dbms, request, "First bind failed", 1);
    if (!request->bindParam(1, IldCollectionType, -1, 0, 0, IlFalse, 0, adt))
		Ending(dbms, request, "Second bind failed", 1);
    
    IldADTValue termList(adt, "versions");
    termList.setValue("05/20/1994", 0);
    termList.setValue("07/12/2008", 1);
  
    if (!request->setParamValue("Gump", 0))
		Ending(dbms, request, "First set param failed", 1);
    if (!request->setParamValue(&termList, 1))
		Ending(dbms, request, "Second set param failed", 1);
    cout << "Inserting row" << endl;
    if (!request->execute())
		Ending(dbms, request, "Insert failed", 1);
  
    // Stage 3 : select
    // ----------------
    // selection request on objects table
    const char* selectObj = "select * from personels";
    cout << "Straight selection: " << selectObj << endl;
    if (!request->execute(selectObj))
		Ending(dbms, request, "Select failed: ", 1);
    cout << endl;
    IldPrintTuple(request, IldNames);
    IldPrintTuple(request, IldSeparators);
    while (request->fetch().hasTuple())
		IldPrintTuple(request);
    if (request->isErrorRaised()) 
		IldDisplayError("Fetch failed: ", request);
    cout << endl;
    if (!request->closeCursor())
		IldDisplayError("Close cursor failed", request);

    // selection request on table with list
    const char* selectList = "select * from versions";
    cout << "Straight selection: " << selectList << endl;
    if (!request->execute(selectList))
		Ending(dbms, request, "Select failed: ", 1);
    cout << endl;
    IldPrintTuple(request, IldNames);
    IldPrintTuple(request, IldSeparators);
    while (request->fetch().hasTuple())
		IldPrintTuple(request);
    if (request->isErrorRaised()) 
		IldDisplayError("Fetch failed: ", request);
    cout << endl;

    // Stage 4 : drop everything and quit
    // ----------------------------------
    Ending(dbms, request, "Exiting ...", 0);
}
