// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/ildsql.cpp
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
// This program connects itself to a database, reads and prints the
// relations and interactively executes any SQL request.
// If a SELECT is executed, it prints the selected tuples.
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

IL_STDUSE

// ----------------------------------------------------------------------------
// Constants
// ----------------------------------------------------------------------------
static IlBoolean IldAsync = IlFalse;
static char* IldDbmsName = 0;
static char* IldConString = 0;
static int IldBufferSize = 1024;
static int IldRowCount = 20;

// ----------------------------------------------------------------------------
// Arguments parsing
// ----------------------------------------------------------------------------
static void
IldParseArgs(int argc,
	     char* argv[])
{
    if (argc < 3) {
	cout << "Usage: " << argv[0]
	     << " [<options>] <RDBMS name> <connection string>" << endl;
	exit(-1);
    }
    int i = 1;
    while (i < argc) {
	if (argv[i][0] == '-') {
	    switch (argv[i][1]) {
	    case 'b':
		IldBufferSize = atoi(argv[++i]);
		break;
	    case 'r':
		IldRowCount = atoi(argv[++i]);
		if (IldRowCount < 1)
		    IldRowCount = 1;
		break;
	    case 'a':
		IldAsync = IlTrue;
		break;
	    default:
		cout << "Unknown option: " << argv[1] << " ignored !" << endl;
	    }
	} else if (strchr(argv[i], (int)'/'))
            IldConString = argv[i];
        else
            IldDbmsName = argv[i];
	i++;
    }
    if (!IldDbmsName) {
	cout << "Usage: " << argv[0]
	     << " [<options>] <RDBMS name> <connection string>" << endl;
	exit(-1);
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
void
DisplayUse()
{
    cout << "Recognized commands:" << endl
	 << "\th[elp]               : displays this text." << endl
	 << "\tq[uit]               : exits the interpretor." << endl
	 << "\tautocommit {on|off}  : sets auto commit more." << endl
	 << "\tstart [tran[saction]]: initiates a transaction." << endl
	 << "\tcommit               : commits current transaction." << endl
	 << "\trollback             : rolls back current transaction." << endl
	 << "\tdescribe <table name>: describes the given table." << endl
	 << "\t<SQL command>        : immediately executes the command." << endl;
}

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------

int
main(int argc,
     char** argv)
{
    char* queryBuffer;
    IldParseArgs(argc, argv);
    IldDisplayHeader("A tiny SQL interpretor");
    cout << "Connecting to: " << IldDbmsName << endl;
    IldDbms* dbms = IldAllocConnect(IldDbmsName, IldConString);
    if (dbms->isInformationRaised())
	IldDisplayWarning("Connecting", dbms);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed:", 1);
    if (IldAsync) {
	if (!dbms->setAsync(IlTrue))
	    IldEndSample(dbms, 0, 0, "Switch asynchronous mode failed:", 1);
	if (!dbms->isAsync())
	    IldEndSample(dbms, 0, 0, "Asynchronous mode is not turned ON:", 1);
    }
    
    dbms->setDefaultColArraySize(10);
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, request, 0, "Request allocation failed:", 1);
    cout << "Entering the interpretor loop, use 'q' to quit." << endl;
    queryBuffer = new char [IldBufferSize];
    for (;;) {
	IlInt count = 0;
	cout << "Ildsql >> ";
	getLine(queryBuffer, IldBufferSize, cin);
	cout << endl;
	if (!queryBuffer[0])
	    continue; 
	if (queryBuffer[0] == 'q' || queryBuffer[0] == 'Q')
	    break;
	if (queryBuffer[0] == 'h')
	    DisplayUse();
	else if (strncmp(queryBuffer, "autocommit", 10) == 0) {
	    if (queryBuffer[11] != 'o')
		cout << "Unrecognized option: " << &queryBuffer[11] << endl;
	    else if (queryBuffer[12] == 'n')
		if (!dbms->autoCommitOn(request))
		    IldDisplayError("Set autocommit on failed: ", dbms);
		else
		    cout << "Autocommit set on." << endl;
	    else if (queryBuffer[12] == 'f')
		if (!dbms->autoCommitOff(request))
		    IldDisplayError("Set autocommit off failed: ", dbms);
		else
		    cout << "Autocommit set off." << endl;
	} else if (strncmp(queryBuffer, "start", 5) == 0) {
	    if (!dbms->startTransaction(request))
		IldDisplayError("Begin work failed: ", dbms);
	    else
		cout << "Transaction begins." << endl;
	} else if (strcmp(queryBuffer, "commit") == 0) {
	    if (!dbms->commit(request))
		IldDisplayError("Commit failed: ", dbms);
	    else
		cout << "Transaction commited." << endl;
	} else if (strcmp(queryBuffer, "rollback") == 0) {
	    if (!dbms->rollback(request))
		IldDisplayError("Rollback failed: ", dbms);
	    else
		cout << "Transaction rolled back." << endl;
	} else if (strncmp(queryBuffer, "describe", 8) == 0) {
	    IldRelation* relation = 0;
	    do {
		relation = dbms->getRelation(&queryBuffer[9]);
	    } while (!dbms->isCompleted());
	    if (dbms->isErrorRaised())
		IldDisplayError("Get relation failed: ", dbms);
	    else
		IldPrintRelation(*relation);
	} else {
	    IlBoolean stopFetch = IlFalse;
	    do {
		request->execute(queryBuffer, &count);
	    } while (!request->isCompleted());
	    if (request->isErrorRaised())
		IldDisplayError("Executing: ", request);
	    else if (!request->fetch())
		IldDisplayError("Fetching: ", request);
	    else {
		if (request->isInformationRaised())
		    cout << "Warning: " << request->getInformationMessage()
			 << endl;
		// Loop with two levels, since ODBC, Sybase, and MS SQL Server
		// can have several results sets for one command.
		do {
		    int rCount = 0;
		    if (request->getColCount()) {	// That's a select
			if (request->hasTuple()) {
			    // Column's headers
			    IldPrintTuple(request, IldNames);
			    IldPrintTuple(request, IldSeparators);
			    IldPrintTuple(request);	// First row
			    rCount++;
			    while (request->fetch().hasTuple() ||
				   !request->isCompleted()) {	// Other rows
				if (request->isCompleted()) {
				    if (rCount == IldRowCount) {
					cout << "Next: ";
					getLine(queryBuffer, IldBufferSize,
						cin);
					rCount = 0;
					if ((queryBuffer[0] == 'q') ||
					    (queryBuffer[0] == 'Q'))
					    stopFetch = IlTrue;
				    }
				    IldPrintTuple(request);
				    if (request->isErrorRaised() || stopFetch)
					break;
				    rCount++;
				}
			    }
			    cout << endl;
			    if (stopFetch) {
				request->closeCursor();
				break;
			    }
			    if (request->isErrorRaised())
				IldDisplayDiags("Fetching: ", request);
			} else	// Empty result set
			    if (request->isCompleted())
				cout << endl << "No row found." << endl;
		    }	// Was not a select
		    else if (count)
			cout << "Affected rows: " << count << endl;
		} while (request->fetch().hasTuple() ||
			 !request->isCompleted());
	    }
	}
    }
    delete [] queryBuffer;
    if (dbms->isErrorRaised())
	dbms->clearDiagnostics();
    if (request->isErrorRaised())
	request->clearDiagnostics();
    IldEndSample(dbms, request);
}
