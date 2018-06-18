// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/readrel.cpp
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
// After a connection to a database, this program tries to get a supposed
// non existant relation. Then it prints the error message and creates
// the relation. The program gets the relation back by name and prints it.
// The program destroys the relation and tries to get it
// again; then the program prints the error message and disconnects itself
// from the database.
//
// NB: + The database relations (tables) are represented by instances of
//       the C++ "IldRelation" class.
//
//     + When the program looks for the relation by name, it must try the
//       lowercase name because of some RDBMS identifier case setting.
//
//     + The "dbms" deletion removes all "IldRequest" and "IldRelation"
//       instances that it has created.
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
static const char* indexStr =
"create unique index f1ind on ATABLE (F2)";

static const char* 
DropStr = "drop table ATABLE";
// ----------------------------------------------------------------------------
// If odbc connects to Oracle, numeric type is "decimal(5, 2)",
// while it is "currency" if it connects to access.
// ==> check if server name is "ACCESS" to use proper type name.
const char*
IldGetOdbcNumericTypeName(IldDbms* dbms)
{
    static char serverName[256];
    IlInt dummy;
    dbms->getInfo(IldServerName, &dummy, serverName);
    return (!strncmp(serverName, "ACCESS", 6)
	    ? "create table ATABLE (F1 currency, F2 char(20))"
	    : "create table ATABLE (F1 numeric(5, 2), F2 char(20))");
}

// ----------------------------------------------------------------------------
static const char*
IldGetCreateTableStr(IldDbms* dbms,
		     const char* dbmsName)
{
    const char* reqStr ;
    if (!strncmp(dbmsName, "db2", 3))
	reqStr = "create table ATABLE(F1 decimal(5, 2) not null primary key, F2 char(20))";
    else if (!strcmp(dbmsName, "odbc"))
	reqStr = IldGetOdbcNumericTypeName(dbms);
    else
	reqStr = "create table ATABLE(F1 decimal(5,2) primary key, F2 char(20))";
    return reqStr;
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
	     << " <RDBMS name> <connection string>" << endl;
	return 1;
    }
  
    IldDisplayHeader("Read a relation");
    cout << "Connection to : " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed: ", 1);
    cout << endl;
  
    const char* intentErr = "This error is intentionally printed: ";
    // We try to get a relation which does not exist.
    cout << "Trying to retrieve an unknown relation : " << endl;
    IldRelation* relation = 0 ;
    relation = dbms->getRelation("ATABLE");
    if (!relation)
	relation = dbms->getRelation("atable", "");
    if (!relation)
	// We print the error message.
	if (dbms->isErrorRaised())
	    IldDisplayError(intentErr, dbms);
    cout << endl;
  
    // We create the relation.
    static const char* requestStr =
	IldGetCreateTableStr(dbms, dbms->getName());
    cout << "Creating the relation : " << requestStr << endl;
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, request, 0, "Request allocation failed:", 1);
    if (!request->execute(requestStr))
	IldEndSample(dbms, request, 0, "Table creation failed: ", 1);
    cout << endl;
  
    cout << "Adding an index for the table: " << indexStr << endl;
    if (!request->execute(indexStr))
	IldEndSample(dbms, request, DropStr, "Index creation failed: ", 1);
    cout << endl;
  
    // We read the relation and print it. 
    cout << "Reading the new relation : " << endl;
    relation = dbms->getRelation("ATABLE");
    if (!relation)
	relation = dbms->getRelation("atable");
    if (relation)
	IldPrintRelation(*relation);
  
    cout << "Deleting the relation" << endl;
    // We destroy the C++ relation: it is removed from the cache
    delete relation;
  
    // We remove the relation from the database.
    cout << "Droping the table : " << DropStr << endl;
    if (!request->execute(DropStr))
	IldDisplayError("Drop failed: ", request);

    // The following code must generate an error.
    cout << "Then we try to read it in again : " << endl;
    relation = dbms->getRelation("ATABLE");
    if (!relation)
	relation = dbms->getRelation("atable");
    if (dbms->isErrorRaised())
	// We print the error message.
	IldDisplayError(intentErr, dbms);
    cout << endl;
  
    // This disconnects the application from the database.
    IldEndSample(dbms, request, 0, "Cleaning up and exiting.");
}
