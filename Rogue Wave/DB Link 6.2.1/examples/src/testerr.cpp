// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/testerr.cpp
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
// The error management of DB Link is based on the C++
// "IldErrorReporter" class. This program specializes this class
// by defining the "UserErrorReporter" class and recoding the two
// virtual member functions "dbmsError" and "dblinkError". The first one
// is called each time the RDBMS raises an error; the second one when
// DB Link detects an internal error.
//
// NB: + This programs catches bad connections and tries to reconnect
//       before returning to a normal sequence.
//
//     + If the program fails when it attempts to fix a problem,
//       the handler will be called again ... until it fixes it.
// ----------------------------------------------------------------------------

#include "ildutil.h"
#include <ildblink/dberr.h>

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
// UserErrorReporter class definition
// ----------------------------------------------------------------------------
class UserErrorReporter : public IldErrorReporter
{
public:
    virtual void dbmsError(IlInt,
			   const char*,
			   const char*,
			   IldDbms*,
			   IldRequest* = 0,
			   const char* = 0) const;
  
    virtual void dblinkError(IlInt,
			     const char*,
			     const char*,
			     IldDbms*,
			     IldRequest* = 0,
			     const char* = 0,
			     IlInt = (IlInt)0,
			     const IldRelation* = 0) const;
};

// ----------------------------------------------------------------------------
// UserErrorReporter::dbmsError virtual function
// ----------------------------------------------------------------------------
void
UserErrorReporter::dbmsError(IlInt,
			     const char* function,
			     const char*,
			     IldDbms*,
			     IldRequest* request,
			     const char* string) const
{
    if (!strcmp(function, "IldRequest::execute")) {
	cout << endl
	     << "USER ERROR: select failed : ";
	if (string)
	    cout << string;
	cout << endl
	     << "Enter a new request : ";
	char str[90];
	getLine(str, 90, cin);
	do {
	    request->execute(str);
	} while (!request->isCompleted());
    }
}

// ----------------------------------------------------------------------------
// UserErrorReporter::error virtual function
// ----------------------------------------------------------------------------
void
UserErrorReporter::dblinkError(IlInt errorType,
			       const char* function,
			       const char* message,
			       IldDbms* dbms,
			       IldRequest* request,
			       const char* string,
			       IlInt index,
			       const IldRelation* relation) const
{
    char str[90];
    switch (errorType) {
    case ILD_DBMS_NOT_CONNECTED:
	cout << endl << "USER ERROR: connect first: DATABASE? ";
	getLine(str, 90, cin);
	dbms->connect(str);
	break;
    case ILD_ALREADY_CONNECTED:
	cout << endl
	     << "USER WARNING: already connected to: "
	     << dbms->getDatabase()
	     << endl;
	dbms->disconnect();
	// The connection will be performed by DB Link itself.
	break;
    case ILD_BAD_COLUMN_INDEX:
	cout << endl
	     << "USER ERROR: bad index value: " << index
	     << endl
	     << "when calling " << function
	     << endl;
	break;
    default:
	// Call the default handler
	IldErrorReporter::dblinkError(errorType, function,
				      message, dbms,
				      request, string,
				      index, relation);
    }
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

    IldDisplayHeader("Error handling customization");

    // The following UserErrorReporter objects will be
    // destroyed respectively by the IldDbms and IldRequest
    // destructors.
    UserErrorReporter* dbmsReporter = new UserErrorReporter;
    UserErrorReporter* requestReporter = new UserErrorReporter;
    
    cout << "Connecting to : " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Initial connection failed: ", 1);
    cout << endl;

    cout << "Error reporter set to user defined one" << endl;
    dbms->setErrorReporter(dbmsReporter);
    cout << endl;
    
    // We try a new connection (on the same database). As the
    // dbms object is already connected,
    // "UserErrorReporter::dblinkError" is called; it disconnects
    // the dbms object and connects it to the new database.
    // One side effect is the destruction of the request objects.
    cout << "Trying a second connection using an already connected DBMS object"
	 << endl;
    if (!dbms->connect(argv[2]))
	// This message MUST not be printed !
	IldDisplayError("TESTERR[Should not show up]: connection failed: ",
			dbms);
    cout << endl;
    
    cout << "Creating a request object" << endl;
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, request, 0, "TESTERR: ", 1);
    cout << endl;
    
    cout << "Setting request error reporter to user defined one" << endl;
    request->setErrorReporter(requestReporter);
    cout << endl;
    
    const char* createStr = "create table USERTABLE(F1 char(20))";
    cout << "Creation of table : " << createStr << endl;
    do {
	request->execute(createStr);
    } while (!request->isCompleted());
    if (request->isErrorRaised())
	IldEndSample(dbms, request, 0, "Table creation failed: ", 1);
    cout << endl;
    request->execute("insert into USERTABLE values ('First row')");
    
    // We intentionally give a bad SELECT statement.
    // "UserErrorReporter::dbmsError" will ask for
    // a new request, answer : "select * from USERTABLE".
    const char* selectStr1 = "select * from DUMMYTABLE";
    const char* selectStr2 = "select * from USERTABLE";
    cout << "Provoking error on SELECT : " << selectStr1 << endl;
    cout << "  when prompted, enter the command : " << endl;
    cout << "   \"" << selectStr2 << "\"" << endl;
    
    request->execute(selectStr1);
    if (request->isErrorRaised())
	// this message should not show up
	IldDisplayError("TESTERR[Should not show up]: ", request);
    else {
	cout << endl;
	cout << "Field " << flush;
	cout << request->getColName(0) << flush;
	cout << " length is " << flush;
	cout << request->getColSize(0);
	cout << endl;
	
	// We intentionally give a bad index value.
	// "UserErrorReporter::dblinkError" will just print a message.
	cout << endl << "Provoking error on index :" << endl;
	
	request->getColName(40);
	if (request->isErrorRaised())
	    // The error is not corrected by the handler thus this message
	    // will be printed
	    IldDisplayError("TESTERR[Intentional]: ", request);
    }
    
    // End of program.
    if (!request->closeCursor())
	IldDisplayError("Cannot close cursor: ", request);
    const char* dropStr = "drop table USERTABLE";
    IldEndSample(dbms, request, dropStr, "Cleaning up and exiting.");
}
