// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/multidb.cpp
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
// This program tests the multi connection and multi cursors features
// of Rogue Wave DB Link.
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
// With MS SQL, we need to specify Insert Row Lock option on the tables
// to avoid insert dead locks.
void
setMssqlTableOption(IldRequest* req[3][3])
{
    IlBoolean firstRun = IlTrue;
    do {
	if (firstRun || !req[0][0]->isCompleted())
	    if (!req[0][0]->execute("sp_tableoption 'atable0', 'insert row lock', 'true'"))
		IldDisplayError("sp_tableoption for atable0", req[0][0]);
	if (firstRun || !req[1][0]->isCompleted())
	    if (!req[1][0]->execute("sp_tableoption 'atable1', 'insert row lock', 'true'"))
		IldDisplayError("sp_tableoption for atable1", req[1][0]);
	if (firstRun || !req[2][0]->isCompleted())
	    if (!req[2][0]->execute("sp_tableoption 'atable2', 'insert row lock', 'true'"))
		IldDisplayError("sp_tableoption for atable2", req[2][0]);
	firstRun = IlFalse;
    } while (!req[0][0]->isCompleted() ||
	     !req[1][0]->isCompleted() ||
	     !req[2][0]->isCompleted());
}

// With Sybase, we get the same insert lock problem.
// First insert locks the page, and second one which goes in the same page
// can not run ==> we need to create multiple partitions in the tables.
void
setSybaseTablePartition(IldRequest* req[3][3])
{
    IlBoolean firstRun = IlTrue;
    do {
	if (firstRun || !req[0][0]->isCompleted())
	    if (!req[0][0]->execute("alter table atable0 partition 20"))
		IldDisplayError("alter table ATABLE0", req[0][0]);
	if (firstRun || !req[1][0]->isCompleted())
	    if (!req[1][0]->execute("alter table atable1 partition 20"))
		IldDisplayError("alter table ATABLE1", req[1][0]);
	if (firstRun || !req[2][0]->isCompleted())
	    if (!req[2][0]->execute("alter table atable2 partition 20"))
		IldDisplayError("alter table ATABLE2", req[2][0]);
	firstRun = IlFalse;
    } while (!req[0][0]->isCompleted() ||
	     !req[1][0]->isCompleted() ||
	     !req[2][0]->isCompleted());
}

// We need to remove table partition before it can be dropped.
void
unsetSybaseTablePartition(IldRequest* req[3][3])
{
    IlBoolean firstRun = IlTrue;
    do {
	if (firstRun || !req[0][0]->isCompleted())
	    if (!req[0][0]->execute("alter table atable0 unpartition"))
		IldDisplayError("alter table ATABLE0", req[0][0]);
	if (firstRun || !req[1][0]->isCompleted())
	    if (!req[1][0]->execute("alter table atable1 unpartition"))
		IldDisplayError("alter table ATABLE0", req[1][0]);
	if (firstRun || !req[2][0]->isCompleted())
	    if (!req[2][0]->execute("alter table atable2 unpartition"))
		IldDisplayError("alter table ATABLE0", req[2][0]);
	firstRun = IlFalse;
    } while (!req[0][0]->isCompleted() ||
	     !req[1][0]->isCompleted() ||
	     !req[2][0]->isCompleted());
}

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int
main(int argc,
     char** argv)
{
    int i = 0, j = 0;
    const char* title = "Multiple concurrency";
    if ((argc != 3) && (argc != 4)) {
	cout << "Usage: " << argv[0] 
	     << " <RDBMS name> <connection string> [async_mode_ON]" << endl;
	cout << "\tasync_mode_ON : any string ==> switches async mode ON."
	     << endl;
	exit(1);
    }
    IldDisplayHeader(title);
  
    cout << "Build three different connections" << endl;
    IldDbms* db[3];
    for (; i < 3; ++i) {
	db[i] = IldAllocConnect(argv[1], argv[2]);
	if (db[i]->isErrorRaised()) {
	    IldDisplayError("Connection failed: ", db[i]);
	    for (j = 0 ; j <= i ; ++j)
		delete db[j];
	    exit(1);
	}
	// Auto Commit has to be set ON for ODBC / Excel.
	db[i]->autoCommitOn();

	if (argc == 4) {
	    if (!db[i]->setAsync(IlTrue)) {
		IldDisplayError("Could not switch Asynchronous mode ON.",
				db[i]);
		for (j = 0 ; j <= i ; ++j)
		    delete db[j];
		exit(1);
	    }
	    if (!db[i]->isAsync()) {
		IldDisplayError("Asynchronous mode is not turned ON.", db[i]);
		for (j = 0 ; j <= i ; ++j)
		    delete db[j];
		exit(1);
	    }
	}
    }
    cout << endl;
  
    cout << "Build three cursors per connection" << endl;
    IldRequest* r[3][3];
    for (i = 0 ; i < 3 ; ++i) {
	for (j = 0 ; j < 3 ; ++j) {
	    r[i][j] = db[i]->getFreeRequest();
	    if (db[i]->isErrorRaised()) {
		IldDisplayError("Request creation failed:", db[i]);
		break;
	    }
	}
    }
    cout << endl;
  
    cout << "Tables creations" << endl;
    IlBoolean firstRun = IlTrue; // To control the end of the
    // queries when they are ran asynchronously together.
    do {
	if (firstRun || !r[0][0]->isCompleted())
	    if (!r[0][0]->execute("create table atable0(f1 char(20), f2 int)"))
		IldDisplayError("Creation of ATABLE0 failed :", r[0][0]);
	if (firstRun || !r[1][0]->isCompleted())
	    if (!r[1][0]->execute("create table atable1(f1 char(20), f2 int)"))
		IldDisplayError("Creation of table ATABLE1 failed :", r[1][0]);
	if (firstRun || !r[2][0]->isCompleted())
	    if (!r[2][0]->execute("create table atable2(f1 char(20), f2 int)"))
		IldDisplayError("Creation of table ATABLE2 failed :", r[2][0]);
	firstRun = IlFalse;
    } while (!r[0][0]->isCompleted() ||
	     !r[1][0]->isCompleted() ||
	     !r[2][0]->isCompleted());

    if (!strncmp(db[0]->getName(), "mssql", 5) ||
	!strncmp(db[0]->getName(), "oledb", 5))
	setMssqlTableOption(r);
    else if (!strncmp(db[0]->getName(), "sybase", 6))
	setSybaseTablePartition(r);
  
    int maxJ = 1;
    if (!strcmp(db[0]->getName(), "sybase") ||
	!strcmp(db[0]->getName(), "mssql") ||
	!strcmp(db[0]->getName(), "oledb"))
	maxJ = 3;
    cout << "Start transactions" << endl;
    for (i = 0 ; i < 3 ; ++i)
	for (j = 0 ; j < maxJ ; ++j)
	    if (!db[i]->startTransaction(r[i][j]))
		IldDisplayError("Begin transaction failed : ", db[i]);
  
    cout << "Insertions by different requests" << endl;
    firstRun = IlTrue;
    do {
	if (firstRun || !r[0][1]->isCompleted())
	    if (!r[0][1]->execute("insert into atable0 values('Paris', 45)"))
		IldDisplayError("Insertion in ATABLE0 failed :", r[0][1]);
	if (firstRun || !r[1][1]->isCompleted())
	    if (!r[1][1]->execute("insert into atable0 values('London', 101)"))
		IldDisplayError("Insertion in ATABLE0 failed :", r[1][1]);
	if (firstRun || !r[2][1]->isCompleted())
	    if (!r[2][1]->execute("insert into atable1 values('Bonn', 56)"))
		IldDisplayError("Insertion in ATABLE1 failed :", r[2][1]);
	firstRun = IlFalse;
    } while (!r[0][1]->isCompleted() ||
	     !r[1][1]->isCompleted() ||
	     !r[2][1]->isCompleted());
    firstRun = IlTrue;
    do {
	if (firstRun || !r[0][2]->isCompleted())
	    if (!r[0][2]->execute("insert into atable1 values('Warsawa', 37)"))
		IldDisplayError("Insertion into ATABLE1 failed :", r[0][2]);
	if (firstRun || !r[1][2]->isCompleted())
	    if (!r[1][2]->execute("insert into atable2 values('Baltimore', 97)"))
		IldDisplayError("Insertion into ATABLE2 failed :", r[1][2]);
	if (firstRun || !r[2][2]->isCompleted())
	    if (!r[2][2]->execute("insert into atable2 values('Lima', 12)"))
		IldDisplayError("Insertion into ATABLE2 failed :", r[2][2]);
	firstRun = IlFalse;
    } while (!r[0][2]->isCompleted() ||
	     !r[1][2]->isCompleted() ||
	     !r[2][2]->isCompleted());
    cout << endl;
  
    cout << "Commit transactions" << endl;
    for (i = 0 ; i < 3 ; ++i)
	for (j = 0 ; j < maxJ ; ++j)
	    if (!db[i]->commit(r[i][j]))
		IldDisplayError("Commit failed : ", db[i]);
  
    cout << "Concurrent Selections" << endl;
    if (!strcmp(db[0]->getName(), "opingres"))
	for (j = 0 ; j < 3 ; ++j)
	    db[j]->autoCommitOff();
    for (j = 0 ; j < 3 ; ++j) {
	firstRun = IlTrue;
	do {
	    if (firstRun || !r[0][j]->isCompleted())
		if (!r[0][j]->execute("select * from atable0"))
		    IldDisplayError("Select failed :", r[0][j]);
	    if (firstRun || !r[1][j]->isCompleted())
		if (!r[1][j]->execute("select * from atable1"))
		    IldDisplayError("Select failed :", r[1][j]);
	    if (firstRun || !r[2][j]->isCompleted())
		if (!r[2][j]->execute("select * from atable2"))
		    IldDisplayError("Select failed :", r[2][j]);
	    firstRun = IlFalse;
	} while (!r[0][j]->isCompleted() ||
		 !r[1][j]->isCompleted() ||
		 !r[2][j]->isCompleted());
    }
    cout << endl;
  
    cout << "Results :"<< endl;
    for (i = 0; i < 2; ++i) {
	for (j = 0 ; j < 3 ; ++j) {
	    for (int k = 0 ; k < 3 ; ++k)
		do {
		    if (!r[j][k]->fetch())
			IldDisplayError("Fetch failed:", r[j][k]);
		    else if (r[j][k]->isCompleted())
			cout << "\t" << j << k
			     << " : ATABLE" << j << "(F1, F2) = ("
			     << r[j][k]->getColStringValue(0)
			     << ", " << r[j][k]->getColIntegerValue(1)
			     << ")" << endl;
		} while (!r[j][k]->isCompleted());
	}
    }
    for(i = 0 ; i < 3 ; ++i)
	for (j = 0 ; j < 3 ; ++j)
	    do {
		if (r[i][j]->fetch().hasTuple())
		    cout << "Error: " << i << j << " : some data left !"
			 << endl;
	    } while (!r[i][j]->isCompleted());
    cout << endl;
  
    cout << "Cleaning up" << endl;
    if (!strncmp(db[0]->getName(), "sybase", 6))
	unsetSybaseTablePartition(r);
    for (i = 0 ; i < 3 ; ++i)
	delete db[i];
    cout << endl;
    // These are not any more valid: get rid of them
    for(i = 0 ; i < 3 ; ++i) 
	for (j = 0 ; j < 3 ; ++j)
	    r[i][j] = 0;
  
    cout << "Create a new IldDbms" << endl;
    db[1] = IldNewDbms(argv[1], argv[2]);
    if (db[1]->isErrorRaised())
	IldDisplayError("Creation failed:", db[1]);
    else if (argc == 4) {
	if (!db[1]->setAsync(IlTrue)) {
	    IldDisplayError("Could not switch Asynchronous mode ON.", db[1]);
	    delete db[1];
	    exit(1);
	}
	if (!db[1]->isAsync()) {
	    IldDisplayError("Asynchronous mode is not turned ON.", db[1]);
	    delete db[1];
	    exit(1);
	}
    }
    cout << "Creation of an IldRequest for the new IldDbms" << endl;
    r[1][0] = db[1]->getFreeRequest();
    if (db[1]->isErrorRaised())
	IldDisplayError("Creation failed:", db[1]);
    cout << endl;
  
    cout << "Drop the tables" << endl;
    do {
	if (!r[1][0]->execute("drop table atable0"))
	    IldDisplayError("Drop ATABLE0 failed:", r[1][0]);
    } while (!r[1][0]->isCompleted());
    do {
	if (!r[1][0]->execute("drop table atable1"))
	    IldDisplayError("Drop ATABLE1 failed:", r[1][0]);
    } while (!r[1][0]->isCompleted());
    do {
	if (!r[1][0]->execute("drop table atable2"))
	    IldDisplayError("Drop ATABLE2 failed:", r[1][0]);
    } while (!r[1][0]->isCompleted());
    cout << endl;

    db[1]->commit(r[1][0]);
  
    delete db[1];
    cout << "End of sample: " << title << endl;
    return 0;
}
