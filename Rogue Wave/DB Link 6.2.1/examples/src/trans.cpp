// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/trans.cpp
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
// After a connection to a database, this program creates a relation and
// starts a transaction on the given RDBMS.
// After having inserted data in the table, it performs a ROLLBACK on
// the transaction. The data should be destroyed. Then it starts another
// transaction, inserts data again, performs a COMMIT and disconnects
// itself from the database. After a reconnection to the database,
// it selects data from the table, prints them, confirming that
// the previous session has been committed. Then the program destroys
// the relation and quits.
//
// NB: + The "IldDbms::startTransaction" is necessary for SYBASE but is
//       ineffective for ORACLE, and INGRES.
//
//     + With SYBASE and ORACLE, the relation creation is done outside
//       a transaction, but with INGRES, the relations are created
//       inside transactions, and are lost when those transactions are
//       rolled back. Hence the program must check whether the table
//       has been removed after a ROLLBACK.
//
//     + The "request" argument of "IldDbms::startTransaction",
//       "IldDbms::commit" and "IldDbms::rollback" member functions
//       is mandatory for SYBASE, but is not needed and has no
//       effect when it is provided for ORACLE or other. This
//       program provides it to be independent of the RDBMS.
//
//     + The "IldDBms::disconnect" member function removes all
//       "IldRequest" instances (and "IldRelation" instances too,
//       not used in this program) it has previously created.
// ----------------------------------------------------------------------------

#include "ildutil.h"

#ifdef IL_STD
# ifndef _CSTDIO_
#  include <cstdio>
# endif
# ifndef _CSTDLIB_
#  include <cstdlib>
# endif
# ifndef _CCTYPE_
#  include <cctype>
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
# ifndef _CTYPE_H
#  include <ctype.h>
# endif
# ifndef _IOSTREAM_H
#  include <iostream.h>
# endif
#endif

IL_STDUSE

static const char* DropTbl = "drop table ATABLE";

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void
setAsync(IldDbms* dbms,
	 int argc)
{
    if (argc == 4) {
	if (!dbms->setAsync(IlTrue))
	    IldEndSample(dbms, 0, 0, "Switch asynchronous mode failed.", 1);
	if (!dbms->isAsync())
	    IldEndSample(dbms, 0, 0, "Asynchronous mode is not turned ON.", 1);
    }
}

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    if ((argc != 3) && (argc != 4)) {
	cout << "Usage: " << argv[0]
	     << " <RDBMS name> <connection string> [async_mode_ON]" << endl;
	cout << "\tasync_mode_ON : any string ==> switches async mode ON."
	     << endl;
	return 1;
    }
    
    IldDisplayHeader("Transaction processing");
    
    cout << "Connection to : " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed: ", 1);
    setAsync(dbms, argc);
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, request, 0, "Creation of request failed: ", 1);
    
    const char* createStr = "create table ATABLE(F1 int, F2 char(20))";
    cout << "Creating table: " << createStr << endl;
    do {
	if (!request->execute(createStr))
	    IldEndSample(dbms, request, 0, "Table creation failed: ", 1);
    } while (!request->isCompleted());
    if (!strcmp(dbms->getName(), "odbc"))
	// Needed for ODBC / Access so that table creation is not
	// rolled back later.
	if (!dbms->commit(request))
	    IldDisplayError("Commit failed", dbms);
  
    // A new transaction.
    cout << "Initiating a transaction." << endl;
    if (!dbms->startTransaction(request))
	IldDisplayError("Begin transaction failed:", dbms);
    cout << endl;
    const char* insertStr = "insert into ATABLE values(40, 'Forty')";
    cout << "Inserting: " << insertStr << endl;
    do {
	if (!request->execute(insertStr))
	    IldEndSample(dbms, request, DropTbl, "Insertion failed: ", 1);
    } while (!request->isCompleted());
    const char* selectStr = "select * from ATABLE";
    cout << "Selecting : " << selectStr << endl;
    do {
	if (!request->execute(selectStr))
	    IldEndSample(dbms, request, DropTbl, "Selection failed: ", 1);
    } while (!request->isCompleted());
    while (request->fetch().hasTuple() || !request->isCompleted())
	if (request->isCompleted())
	    cout << "Data has been inserted..." << endl;
    
    // Rollback.
    cout << "Rolling back the transaction." << endl;
    if (!dbms->rollback(request))
	IldDisplayError("Rollback failed:", dbms);
    cout << endl;
    // Due to AIX, we must allocate the string in order to modifiy it
    char* tName = new char [8];
    strcpy(tName, "ATABLE");
    char cv[254];
    IlInt iv = 0;
    int i = 0, len = strlen(tName);
    if (!dbms->getInfo(IldIdentifierCase, &iv, cv))
	IldDisplayError("Get identifier case", dbms);
    else
	switch (iv) {
	case IldIdentifierUpper:
	    for ( ; i < len ; ++i)
		tName[i] = (char) toupper(tName[i]);
	    break;
	case IldIdentifierLower:
	    for ( ; i < len ; ++i)
		tName[i] = (char) tolower(tName[i]);
	    break;
	default:
	    break;
	}
  
    do {
	dbms->getRelation(tName);
    } while (!dbms->isCompleted());
    if (!dbms->isErrorRaised()) {
	do {
	    if (!request->execute("select * from ATABLE"))
		IldEndSample(dbms, request, DropTbl, "Selection failed: ", 1);
	} while (!request->isCompleted());
	do {
	    if (!request->fetch())
		IldEndSample(dbms, request, DropTbl, "Selection failed: ", 1);
	} while (!request->isCompleted());
	if (!request->hasTuple())
	    cout << "Data have been removed on ROLLBACK ..." << endl;
	while (request->fetch().hasTuple() || !request->isCompleted());
	// A new transaction.
	cout << "Starting a new transaction." << endl;
	if (!dbms->startTransaction(request))
	    IldDisplayError("Begin transaction failed: ", dbms);
    } else {
	cout << "The table has been removed on ROLLBACK ..." << endl;
	
	// A new transaction.
	cout << "Starting a new transaction." << endl;
	if (!dbms->startTransaction(request))
	    IldDisplayError("Begin transaction failed: ", dbms);
	cout << "New creation of the table." << endl;
	do {
	    if (!request->execute(createStr))
		IldDisplayError("Table creation failed: ", request);
	} while (!request->isCompleted());
    }
    delete [] tName;
    cout << "New insertion." << endl;
    do {
	if (!request->execute(insertStr))
	    IldDisplayError("Insertion failed: ", request);
    } while (!request->isCompleted());
    
    // Commit.
    cout << "Commiting the transaction." << endl;
    if (!dbms->commit(request))
	IldDisplayError("Commit failed: ", dbms);
    cout << endl;
    
    cout << "Disconnecting from : " << argv[1] << endl;
    if (!dbms->disconnect())
	IldDisplayError("Disconnection failed: ", dbms);
    cout << "New connection to : " << argv[1] << endl;
    if (!dbms->connect(argv[2]))
	IldDisplayError("Reconnection failed: ", dbms);
    cout << endl;
    
    // We must get back to asynchronous mode because of disconnection.
    setAsync(dbms, argc);

    // We must create a new request, because
    // the disconnection has removed it.
    request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, request, 0, "Request allocation failed:", 1);
    
    cout << "Checking the table data." << endl;
    do {
	request->execute(selectStr);
    } while (!request->isCompleted());
    do {
	request->fetch();
    } while (!request->isCompleted());
    if (request->hasTuple())
	cout << "Data have been committed..." << endl;
    else
	cout << "Data was not commited!" << endl;
    while (request->fetch().hasTuple() || !request->isCompleted());
    
    cout << "Dropping the table." << endl;
    do {
	if (!request->execute(DropTbl))
	    IldDisplayError("Drop failed: ", request);
    } while (!request->isCompleted());
    if (!strcmp(dbms->getName(), "odbc") ||
	!strcmp(dbms->getName(), "sqlbase"))
	// Needed for ODBC / Access so that table creation is not
	// rolled back later. 
	if (!dbms->commit(request))
	    IldDisplayError("Commit failed", dbms);
    
    // Exiting
    IldEndSample(dbms, request, 0, "Exiting.");
}
