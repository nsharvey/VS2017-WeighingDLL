// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/sybtrig.cpp
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
// This program run the sequence :
//	- connect to a database, 
//	- create a request,
//	- if it exists, drop the table it's going to use,
//	- create a test table,
//	- place a trigger on it for delete which will print a message and 
//	  prevent deletion of the first line of the table
//	- try to delete the first row of the table
//	- treat the informative message issued by the print statement and the 
//	  error due to the trigger raiserror statement.
//	
// ----------------------------------------------------------------------------

#include "ildutil.h"

#ifdef IL_STD
# ifndef _IOSTREAM_
#  include <iostream>
# endif
#else
# ifndef _IOSTREAM_H
#  include <iostream.h>
# endif
#endif

IL_STDUSE

// ----------------------------------------------------------------------------
// Clean up utility
// ----------------------------------------------------------------------------
static const char* DropStr = "drop table TrigTest";

// ----------------------------------------------------------------------------
// main function
// ----------------------------------------------------------------------------
int 
main (int argc,
      char* argv[])
{
    if ((argc != 2) && (argc != 3)) {
	cout << "Usage : " << argv[0]
	     << " <connection string> [async_mode_ON]" << endl;
	cout << "\tasync_mode_ON : any string ==> switches async mode ON."
	     << endl;
	return -1;
    }
    
    IldDisplayHeader("Sybase trigger");
    
    cout << "Connecting to : " << argv[1] << endl;
    IldDbms* dbms = IldAllocConnect("sybase", argv[1]);
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Connection failed: ", 1);
    cout << endl;
    if (argc == 3) {
	if (!dbms->setAsync(IlTrue))
	    IldEndSample(dbms, 0, 0, "Switch asynchronous mode failed.", 1);
	if (!dbms->isAsync())
	    IldEndSample(dbms, 0, 0, "Asynchronous mode is not turned ON.", 1);
    }
    cout << "Creating a request." << endl;
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised())
	IldEndSample(dbms, 0, 0, "Request creation failed: ", 1);
    cout << endl;
    
    cout << "Testing the existence of table TrigTest." << endl;
    IldRelation* relation = 0;
    do {
	relation = dbms->getRelation("TrigTest");
    } while (!dbms->isCompleted());
    if (relation) {
	cout << "The table exists, trying to drop it." << endl;
	do {
	    if(!request->execute(DropStr))
		IldEndSample(dbms, request, 0, "Cannot drop table: ", 1);
	} while (!request->isCompleted());
	cout << "Table is dropped and trigger was automatically deleted."
	     << endl;
	delete relation;
	relation = 0;
    }
    cout << endl;
    
    // Stage 1 : create a table, place a trigger on delete for one column
    //           and insert a row that one should not "delete"
    // 1 : table creation
    const char* createStr = "create table TrigTest (f1 int, f2 char(20))";
    cout << "Creating the table : " << createStr << endl;
    do {
	if (!request->execute(createStr))
	    IldEndSample(dbms, request, 0, "Cannot create table: ", 1);
    } while (!request->isCompleted());
    cout << endl;
    
    // 2 : post trigger
    const char* triggerStr = "create trigger nodel1 on TrigTest for delete as \
if (select f1 from deleted) = 1 \
begin \
print \"The line #1 should not be deleted.\" \
rollback transaction \
raiserror 50001 \"Deleting line #1 is not allowed !\" \
end";
    cout << "Adding a trigger : " << triggerStr << endl;
    do {
	if (!request->execute(triggerStr))
	    IldEndSample(dbms, request, DropStr, "Trigger creation failed", 1);
    } while (!request->isCompleted());
    cout << endl;
    
    // 3 : insert rows
    const char* insertStr = "insert into TrigTest values (1, 'Line 1')";
    cout << "Inserting a line : " << insertStr << endl;
    do {
	if (!request->execute(insertStr))
	    IldEndSample(dbms, request, DropStr, "Insertion failed: ", 1);
    } while (!request->isCompleted());
    cout << endl;

    // Stage 2 : try to delete the fatal row, check if trigger got fired by
    //           displaying information and error 
    // 1 : the forbidden delete
    const char* deleteStr ="delete from TrigTest where f1 = 1"; 
    IlInt nRows = 0;
    cout << "Trying to delete : " << deleteStr << endl;
    do {
	request->execute(deleteStr, &nRows);
    } while (!request->isCompleted());
    
    // 2 : any information ?
    if (request->isInformationRaised())  {
	cout << "Information : " << request->getInformationCode() << " " 
	     << request->getInformationMessage() << endl;
    }
    cout << endl;
    
    // 3 : any error ?
    if (request->isErrorRaised()) {
	IldDisplayError("Trigger was fired: ", request);
	if (nRows == 0)
	    cout << "No row modified." << endl;
	else
	    cout << "Error : " << nRows << " modified !" << endl;
    } else 
	cout << " ERROR : trigger was not fired !" << endl;
    cout << endl;
    
    IldEndSample(dbms, request, DropStr, "Cleaning up and exiting.");
}
