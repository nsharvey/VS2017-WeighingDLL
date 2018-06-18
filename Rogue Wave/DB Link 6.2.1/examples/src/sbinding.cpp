// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/sbinding.cpp
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
// After connecting to a dbms, it creates a table in which it inserts five 
// rows using variables binding.
// Then it retrieves the rows, one at a time, after having bound two slots
// of a user defined object to receive the results.
//
// NB : If the data was to be retrieved in different objects, the binding
//      stage would have to be reprocessed before each fetch.
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
// A simple user class
// ----------------------------------------------------------------------------
class Customer
{
public:
    Customer();
    ~Customer();
    IlInt age;
    char* name;
};

// ----------------------------------------------------------------------------
Customer::Customer()
{
    name = new char[21];
    age = 0;
}

// ----------------------------------------------------------------------------
Customer::~Customer()
{
    delete [] name;
}

// ----------------------------------------------------------------------------
// Constants
// ----------------------------------------------------------------------------
static const char* requeststr =
    "create table BINDTABLE(NAME char(20), AGE int)";

static const char* DropStr =
    "drop table BINDTABLE";

// ----------------------------------------------------------------------------
void 
Usage(int argc,
      char* argv[])
{
    if (argc != 3) {
	cout << "Usage: " << argv[0]
	     << " <RDBMS name> <connection string>" << endl;
	exit(1);
    }
}

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    Usage(argc, argv);  
    IldDisplayHeader("Input/ouput bindings");
    
    // Stage 1 : connection and table creation
    // ----------------------------------------
    cout << "Connection to: " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed:", 1);
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Request allocation failed:", 1);
    
    cout << "Creating table using: " << requeststr << endl;
    do {
	if (!request->execute(requeststr))
	    IldEndSample(dbms, 0, 0, "Table creation failed:", 1);
    } while (!request->isCompleted());
    cout << endl;

    // Stage 2 : Insert rows using input variables
    // -------------------------------------------
    cout << "=============================================" << endl;
    cout << " Memory internaly allocated" << endl;
    cout << "=============================================" << endl;
  
    //   1/ parse the insertion request
    const char* parseStr =
	(!strncmp(dbms->getName(), "oracle", 6) ?
	 "insert into BINDTABLE (NAME , AGE) values (:1 , :2)"
	 : "insert into BINDTABLE (NAME , AGE) values (? , ?)");
    cout << "Parsing insertion request: " << parseStr << endl;
    if (!request->parse(parseStr))
	IldEndSample(dbms, request, DropStr, "Parse failed: ", 1);
    cout << endl;
  
    //   3/ declare the variables: since we're using internal mode, null 
    // indicators are not needed, DB Link will use allocate them.
    cout << "Binding first input variable (name) as string type." << endl;
    if (!request->bindParam((IlUShort)0, IldStringType, 21))
	IldEndSample(dbms, request, DropStr, "Variable binding failed:", 1);
    cout << "Binding second input variable (age) as integer type." << endl;
    if (!request->bindParam(1, IldIntegerType))
	IldEndSample(dbms, request, DropStr, "Variable binding failed:", 1);
    cout << endl;
  
    //   4/ iterate while giving them some values
    const char* names[5] = {"Agathe", "Agnes", "Richard",
			    "Francoise", "Daniel"};
    IlInt ages[5] = {23, 5, 66, 43, 50};
    IlInt n = 0;
    int i;
    for (i = 0; i < 5; i++) {
	cout << "Set " << i << "th variable to name: " 
	     << names[i] << " and age: " << ages[i] << endl;
	request->setParamValue(names[i], 0, 0);
	request->setParamValue(ages[i], 1, 0);
    
	//  execute the insertion
	cout << "Inserting row:" << endl;
	if (!request->execute(&n))
	    IldEndSample(dbms, request, DropStr, "Execution failed: ", 1);
	cout << n << "row(s) inserted." << endl;
    }

    // Stage 3 : retrieving the data into user's slots
    // -----------------------------------------------
    //   1/ parse a selection request
    const char* selectStr = "select NAME, AGE from BINDTABLE";
    cout << "Selection request: " << selectStr << endl;

    if (!request->execute(selectStr))
	IldEndSample(dbms, request, DropStr, "Select failed: ", 1);
    cout << endl;
  
    Customer* cust = new Customer();
    
    //   2/ declare binding of outputs: allways in internal mode, thus not 
    // indicator buffers ; will use the internaly allocated ones.
    cout << "Binding output: " << endl;
    cout << "  column NAME bound to customer name slot" <<   endl;
    if (!request->bindCol((IlUShort)0, IldStringType, cust->name, 21)) {
	delete cust;
	IldEndSample(dbms, request, DropStr, "Column binding failed:", 1);
    }
    cout << "  column AGE bound to customer age slot" << endl;
    if (!request->bindCol(1, IldIntegerType, &(cust->age))) {
	delete cust;
	IldEndSample(dbms, request, DropStr, "Column binding failed:", 1);
    }
    cout << endl;
  
    //   3/ fetch the rows : the binding brings the data in the object slots
    i = 1;
    cout << "Fetching the selected rows: " << endl;
    while (request->fetch().hasTuple())
	cout <<"   Customer[" << i++ << "]: "
	     << cust->name << "   " << cust->age << endl;
    if (request->isErrorRaised()) 
	IldDisplayError("Fetch failed: ", request);
    cout << endl;
  
    // Empty the table
    request->execute("delete from BINDTABLE");
    if (request->isErrorRaised()) {
	delete cust;
	IldEndSample(dbms, request, DropStr, "Deletion failed:", 1);
    }
    cout << "===================================================" << endl;
    cout << "Memory externaly allocated" << endl;
    cout << "===================================================" << endl;
    cout << "Parsing insertion request : " << parseStr << endl;
    if (!request->parse(parseStr)) {
	delete cust;
	IldEndSample(dbms, request, DropStr, "Parse failed: ", 1);
    }
    cout << endl;
    
    //   3/ declare the variables: here we have turned to external mode,
    //      the indicator buffers are mandatory.
    char charVal[21];
    IlInt intVal = 0;
    short cNull = 0, iNull = 0;
    cout << "Binding first parameter as type string" << endl;
    if (!request->bindParam((IlUShort)0, IldStringType,
			    21, charVal, &cNull)) {
	delete cust;
	IldEndSample(dbms, request, DropStr, "Variable binding failed:", 1);
    }
    cout << "Binding second parameter as type integer" << endl;
    if (!request->bindParam(1, IldIntegerType,
			    -1, &intVal, &iNull)) {
	delete cust;
	IldEndSample(dbms, request, DropStr, "Variable binding failed:", 1);
    }
    cout << endl;
    for (i = 0; i < 5; i++) {
	cout << "Set " << i << "th variable to name : " 
	     << names[i] << " and age : " << ages[i] << endl;
	strcpy(charVal, names[i]);
	intVal = ages[i];
	//  execute the insertion
	cout << "Inserting row" << endl;
	if (!request->execute(&n)) {
	    delete cust;
	    IldEndSample(dbms, request, DropStr, "Execution failed: ", 1);
	}
	cout << n << "row(s) inserted." << endl;
    }
    
    // Stage 3 : retrieving the data into user's slots
    // -----------------------------------------------
    //   1/ parse a selection request
    cout << "Parsing select request: " << selectStr << endl;
    if (!request->execute(selectStr)) {
	delete cust;
	IldEndSample(dbms, request, DropStr, "Parse failed: ", 1);
    }
    cout << endl;
    
    //   2/ declare binding of outputs: still external mode, thus use the
    // indicator buffers despite we know beforehand that no value will be null.
    cout << "Binding output : " << endl;
    cout << "  column NAME bound to customer name slot" <<   endl;
    if (!request->bindCol((IlUShort)0, IldStringType,
			  cust->name, 21, &cNull)) {
	delete cust;
	IldEndSample(dbms, request, DropStr, "Column binding failed:", 1);
    }
    cout << "  column AGE bound to customer age slot" << endl;
    if (!request->bindCol(1, IldIntegerType,
			  &(cust->age), 0, &iNull)) {
	delete cust;
	IldEndSample(dbms, request, DropStr, "Column binding failed:", 1);
    }
    cout << endl;
    i = 1;
    cout << "Fetching the selected rows : " << endl;
    while (request->fetch().hasTuple())
	cout <<"   Customer " << i++ << " : "
	     << cust->name << "   " << cust->age << endl;
    if (request->isErrorRaised())
	IldDisplayError("Fetch failed: ", request);
    cout << endl; 
    
    // Stage 4 : drop table, disconnect and quit
    delete cust;
    IldEndSample(dbms, request, DropStr, "Cleaning up and exiting.");
}
