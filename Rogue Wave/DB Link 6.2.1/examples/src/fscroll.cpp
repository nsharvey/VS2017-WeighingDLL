// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/fscroll.cpp
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
// This program illustrates the use of scrollable cursors via Rogue Wave
// DB Link 
// IldRequest fetchScroll() function.
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

#ifdef IL_STD
# ifndef _STRSTREAM_
#  include <strstream>
# endif
#else
# ifndef _STRSTREAM_H_
#  ifndef WINDOWS
#   include <strstream.h>
#  else
#   include <strstrea.h>
#  endif
# endif
#endif

IL_STDUSE

// --------------------------------------------------------------------------
// Constant
// --------------------------------------------------------------------------
static const char* DropStr = "drop table FSCROLL";

static const char* SelectFailed = "Could not select data.";
static const char* FetchFailed = "Could not fetch data.";

// --------------------------------------------------------------------------
// Create a table and fill it with data.
// --------------------------------------------------------------------------
void 
CreateData(IldDbms* dbms,
	   IldRequest* request)
{
    // Table creation. 
    static const char* createStr = "create table FSCROLL (VAL int)";
    cout << "Creating a table: " << createStr << endl;
    if (!dbms->execute(createStr))
	IldEndSample(dbms, 0, 0, "Table creation failed", 1);
    int i = 0;
    const char* insertStr = "insert into FSCROLL values (";
    char query[80];
    ostrstream ostr(query, 80);
    for (i = 0 ; i < 12 ; ++i) {
	ostr.seekp(0, ios::beg);
	ostr << insertStr << (i + 1) << ")" << ends;
	cout << "Running : " << query << endl;
	do {
	    if (!request->execute(query))
		IldEndSample(dbms, request, DropStr, "Insert failed", 1);
	} while (!request->isCompleted());
    }
    if (!dbms->commit())
	IldEndSample(dbms, request, DropStr, "Commit failed", 1);
    cout << endl;
}

// --------------------------------------------------------------------------
// Fetch the nbRows according to direction, offset.
// --------------------------------------------------------------------------
void
FetchRows(IldDbms* dbms,
	  IldRequest* request,
	  IlInt direction,
	  IlInt offset,
	  IlInt count,
	  IlInt lastVal)
{
    do {
	switch (direction) {
	case IldFetchDirectionNext:
	case IldFetchDirectionFirst:
	case IldFetchDirectionLast:
	case IldFetchDirectionPrior:
	    request->fetchScroll(direction);
	    break;
	case IldFetchDirectionAbsolute:
	case IldFetchDirectionRelative:
	    request->fetchScroll(direction, offset);
	    break;
	default :
	    request->fetch();
	}
    } while (!request->isCompleted());
    if (request->isErrorRaised()) {
	request->release();
	IldEndSample(dbms, request, DropStr, FetchFailed, 1);
    } else {
	if (request->isInformationRaised())
	    IldDisplayDiags("Fetch", request, cout);
	if (request->getColCount()) {		// That's a select
	    if (request->hasTuple()) {		// Process the results set
		IldPrintTuple(request, IldNames);	// Column's headers
		IldPrintTuple(request, IldSeparators);
		IldPrintTuple(request);		// First row
		--count;
		while (count > 0) {
		    if (!request->fetch()) {
			request->release();
			IldEndSample(dbms, request, DropStr, FetchFailed, 1);
		    } else {
			if (request->isInformationRaised())
			    IldDisplayDiags("Fetch", request, cout);
			if (request->hasTuple()) {// Process the results set
			    IldPrintTuple(request);	// First row
			    if (request->isInformationRaised())
				IldDisplayDiags("Fetch", request, cout);
			    if (request->isErrorRaised()) {
				request->release();
				IldEndSample(dbms, request, DropStr,
					     FetchFailed, 1);
			    }
			} else if (request->isCompleted()) // End of set
			    break;
		    }
		    if (request->isCompleted())
			--count;
		}
	    } else // Empty result set
		cout << "No more rows." << endl;
	}
    }
    cout << "Expected last value should be : " << lastVal << endl << endl;
}

// --------------------------------------------------------------------------
// Query the table using scrollable cursor capabilities.
// --------------------------------------------------------------------------
void
QueryData(IldDbms* dbms,
	  IldRequest* request)
{
    static const char* query = "select * from FSCROLL order by VAL";
    do {
	if (!request->execute(query))
	    IldEndSample(dbms, request, DropStr, SelectFailed, 1);
    } while (!request->isCompleted());
    cout << "Fetch next row should work ok." << endl;
    if (!request->fetchScroll(IldFetchDirectionNext))
	IldEndSample(dbms, request, DropStr, "Could not fetchScroll", 1);
    cout << "\tFetch is OK as expected." << endl << endl;
    cout << "This fetch should fail since scrollable cursor is not activated."
	 << endl;
    if (!request->fetchScroll(IldFetchDirectionRelative, 5))
	IldDisplayError("This error was expected: ", request);
    else {
	IldEndSample(dbms, request, DropStr,
		     "This fetch should have failed.", 1);
    }
    cout << endl;

    // Activate Scrollable cursor mode :
    if (!request->setScrollable(IlTrue))
	IldEndSample(dbms, request, DropStr, 
		     "Could not turn scroll mode ON", 1);
    if (request->isScrollable())
	cout << "Scrollable cursor mode is now activated." << endl << endl;
    do {
	if (!request->execute(query))
	    IldEndSample(dbms, request, DropStr, SelectFailed, 1);
    } while (!request->isCompleted());
    
    FetchRows(dbms, request, IldFetchDirectionNext, 0, 1, 1);
    FetchRows(dbms, request, IldFetchDirectionNext, 0, 1, 2);
    FetchRows(dbms, request, IldFetchDirectionNext, 0, 2, 4);
    FetchRows(dbms, request, IldFetchDirectionPrior, 0, 3, 5);
    FetchRows(dbms, request, IldFetchDirectionPrior, 0, 1, 4);
    FetchRows(dbms, request, IldFetchDirectionAbsolute, 2, 1, 2);
    FetchRows(dbms, request, IldFetchDirectionRelative, 3, 2, 6);
    FetchRows(dbms, request, IldFetchDirectionRelative, 4, 1, 10);
    FetchRows(dbms, request, IldFetchDirectionFirst, 0, 3, 3);
    
    if (!request->setColArraySize(5))
	IldEndSample(dbms, request, DropStr,
		     "Could not change column array size.", 1);

    do {
	if (!request->execute(query))
	    IldEndSample(dbms, request, DropStr, SelectFailed, 1);
    } while (!request->isCompleted());
    FetchRows(dbms, request, IldFetchDirectionLast, 0, 2, 9);
    // This one will work. We reached the end of the results set, but we may
    // still move in the buffer of 5 rows allocated in memory.
    FetchRows(dbms, request, IldFetchDirectionLast, 0, 5, 12);
    FetchRows(dbms, request, IldFetchDirectionRelative, -2, 2, 11);
    FetchRows(dbms, request, IldFetchDirectionRelative, -4, 1, 7);

    do {
	if (!request->execute(query))
	    IldEndSample(dbms, request, DropStr, SelectFailed, 1);
    } while (!request->isCompleted());
    FetchRows(dbms, request, IldFetchDirectionLast, 0, 1, 8);
    FetchRows(dbms, request, IldFetchDirectionPrior, 0, 1, 3);
    
    do {
	if (!request->execute(query))
	    IldEndSample(dbms, request, DropStr, SelectFailed, 1);
    } while (!request->isCompleted());
    FetchRows(dbms, request, IldFetchDirectionNext, 0, 6, 6);
    FetchRows(dbms, request, IldFetchDirectionPrior, 0, 1, 1);
    FetchRows(dbms, request, IldFetchDirectionRelative, 4, 3, 7);

    do {
	if (!request->execute(query))
	    IldEndSample(dbms, request, DropStr, SelectFailed, 1);
    } while (!request->isCompleted());
    FetchRows(dbms, request, IldFetchDirectionLast, 0, 5, 12);
    FetchRows(dbms, request, IldFetchDirectionPrior, 0, 1, 11);
    FetchRows(dbms, request, IldFetchDirectionAbsolute, 2, 1, 2);    
}

// --------------------------------------------------------------------------
// main function
// --------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    if ((argc != 3) && (argc != 4)) {
	cout << "Usage: " << argv[0]
	     << " <RDBMS name> <connection string> [async_mode_ON]" << endl;
	cout << "\tasync_mode_ON : any string ==> switches async mode ON."
	     << endl;
	exit(1);
    }  
    IldDisplayHeader("Scrollable cursor  sample");
    cout << "Connecting to: " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed.", 1);
    cout << endl;
    if (argc == 4) {
	if (!dbms->setAsync(IlTrue))
	    IldEndSample(dbms, 0, 0, "Switch asynchronous mode failed.", 1);
	if (!dbms->isAsync())
	    IldEndSample(dbms, 0, 0, "Asynchronous mode is not ON.", 1);
    }
    cout << "Creating a request: " << endl;
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Creation of request failed.", 1);
    cout << endl;
    CreateData(dbms, request);
    QueryData(dbms, request);
    
    // Clean up and successful exit
    IldEndSample(dbms, request, DropStr, "Cleaning up and exiting.");
}
