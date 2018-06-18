// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/relnames.cpp
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
// After a connection to a database, this program reads the names of
// all accessible relations (tables) in the database and prints them.
// Then it reads the names of relations belonging to a USER and prints
// them.
//
// NB: The program must delete the array of strings holding the names
//     and the strings too. This array and the strings are allocated
//     and returned by the "IldDbms::readRelationNames" member function.
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
// main function
// ----------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    char str[100];
    int i = 0;
    if ((argc != 3) && (argc != 4)) {
	cout << "Usage: " << argv[0]
	     << " <RDBMS name> <connection string> [async_mode_ON]" << endl;
	cout << "\tasync_mode_ON : any string ==> switches async mode ON."
	     << endl;
	return 1;
    }
  
    IldDisplayHeader("Read relation names");
  
    cout << "Connection to : " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect(argv[1], argv[2]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed:", 1);
    if (argc == 4) {
	if (!dbms->setAsync(IlTrue))
	    IldEndSample(dbms, 0, 0, "Switch asynchronous mode failed.", 1);
	if (!dbms->isAsync())
	    IldEndSample(dbms, 0, 0, "Asynchronous mode is not turned ON.", 1);
    }
    // Get all tables names
    char** names = 0;
    do {
	names = dbms->readRelationNames();
	if (dbms->isErrorRaised())
	    break;
    } while (!dbms->isCompleted());
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Read names failed:", 1);
    if (names) {
	cout << "All relation names:" << endl;
	cout << "===================" << endl;
	for ( ; names[i] != 0 ; i++) {
	    if (i && !(i % 10)) {
		cout << "Nexts:";
		getLine(str, 100, cin);
	    }
	    if (str[0] && str[0] == 'q')
		break;
	    cout << "\t" << names[i] << endl;
	}
	dbms->freeNames(names);
    }
    cout << endl;
    // Get all tables owners
    char** owners = 0;
    do {
	owners = dbms->readRelationOwners();
	if (dbms->isErrorRaised())
	    break;
    } while (!dbms->isCompleted());
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Read owners failed: ", 1);
    if (owners) {
	cout << "All relation owners:" << endl;
	cout << "===================" << endl;
	for ( i = 0 ; owners[i] != 0 ; i++) {
	    if (i && !(i % 10)) {
		cout << "Nexts:";
		getLine(str, 100, cin);
		if (str[0] && str[0] == 'q')
		    break;
	    }
	    cout << "\t" << owners[i] << endl;
	}
	dbms->freeNames(0, owners);
    }
    cout << endl;
    // Do it again with owners names
    owners = 0;
    do {
	names = dbms->readRelationNames(owners);
    } while (!dbms->isCompleted());
    if (names && owners) {
	cout << "All relation names and owners:" << endl;
	cout << "==============================" << endl;
	for ( i = 0 ; names[i] != 0 ; i++) {
	    if (i && !(i % 10)) {
		cout << "Nexts:";
		getLine(str, 100, cin);
		if (str[0] && str[0] == 'q')
		    break;
	    }
	    cout << "\t" << names[i] << " \t"
		 << (owners[i] ? owners[i] : " ") << endl;
	}
	dbms->freeNames(names, owners);
    }
    
    cout << endl << "Give a USER name[CR for no USER]: ";
    getLine(str, 100, cin);
    if (str[0]) {
	// We got a user.
	do {
	    names = dbms->readRelationNames(str);
	    if (dbms->isErrorRaised())
		break;
	} while (!dbms->isCompleted());
	if (dbms->isErrorRaised())
	    IldEndSample(dbms, 0, 0, "Read relation names failed: ", 1);
	if (names) {
	    cout << "Relation names belonging to " << str << ": " << endl;
	    for ( i = 0 ; names[i] != 0 ; i++)
		cout << "\t" << names[i] << endl;
	    dbms->freeNames(names);
	} else
	    cout << "  NONE " << endl; 
    }
    // This disconnects the application from the database.
    IldEndSample(dbms, 0, 0, "End of sample");
}
