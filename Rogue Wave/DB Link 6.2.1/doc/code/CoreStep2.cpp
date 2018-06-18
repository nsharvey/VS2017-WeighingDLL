// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: doc/code/CoreStep2.cpp
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
#include <iostream.h>
#include <stdlib.h>

#include <ildblink/dblink.h>

void IldDisplayError(const char* operation,
		     const IldIldBase* ildobj);
void runStep2(IldDbms* dbms);
void runStep1(char* dbName,
	      char* connStr);


// ----------------------------------------------------------------------------
void IldDisplayError(const char* operation,
		     const IldIldBase* ildobj)
{
    cout << operation << endl;
    cout << " Code: " << ildobj->getErrorCode() << endl;
    cout << " SqlState: " << ildobj->getErrorSqlstate() << endl;
    cout << " Message: " << ildobj->getErrorMessage() << endl;
}

// ----------------------------------------------------------------------------
void runStep2(IldDbms* dbms)
{
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed: ", dbms);
	delete dbms;
	exit(1);
    }

    // Create a new table.
    const char* createStr = "create table ATABLE(F1 int, F2 char(20))";
    cout << "Creating a table: " << createStr << endl;
    request->execute(createStr);
    if (request->isErrorRaised()) {
	IldDisplayError("Table creation failed: ", request);
	delete dbms;
	exit(1);
    }

    // Data insertion.
    cout << "Data insertion : " << endl;
    const char* insertStr1 = "insert into ATABLE values(40,'Forty')";
    IldInt nbRows = 0;
    cout << "Row #1: " << insertStr1 << endl;
    if (!request->execute(insertStr1, &nbRows)) 
	IldDisplayError("Insertion failed:", request);
    else
	cout << "\t" << nbRows << " row inserted." << endl;
    const char* insertStr2 =
	"insert into ATABLE values(-3,'Minus Three')";
    cout << "Row #2: " << insertStr2 << endl;
    if (!request->execute(insertStr2, &nbRows))
	IldDisplayError("Insertion failed:", request);
    else
	cout << "\t" << nbRows << " row inserted." << endl;
    const char* insertStr3 =
	"insert into ATABLE values(-10,'Minus Ten')";
    cout << "Row #3: " << insertStr3 << endl;
    if (!request->execute(insertStr3, &nbRows))
	IldDisplayError("Insertion failed:", request);
    else
	cout << "\t" << nbRows << " row inserted." << endl;
    const char* insertStr4 = "insert into ATABLE values(6,'Six')";
    cout << "Row #4: " << insertStr4 << endl ;
    if (!request->execute(insertStr4))
	IldDisplayError("Insertion failed:", request);
    else
	cout << "\t" << nbRows << " row inserted." << endl;
    cout << endl;

    // Drop this table before leaving the program.
    const char* dropStr = "drop table ATABLE";
    cout << "Dropping table: " << dropStr << endl;
    if (!request->execute(dropStr))
	IldDisplayError("Drop table failed: ", request);
}

// ----------------------------------------------------------------------------
void runStep1(char* dbName,
	      char* connStr)
{
    // Connection to the RDBMS.
    IldDbms* dbms = IldNewDbms(dbName, connStr);

    // Check Connection is OK.
    if (dbms->isErrorRaised()) {
	IldDisplayError("Connection failed: ", dbms);
	delete dbms;
	exit(1);
    } else
	cout << "Connection established." << endl;

    runStep2(dbms);

    // Disconnect and release memory.
    delete dbms;

}

// ----------------------------------------------------------------------------
int main(int argc,
	 char* argv[])
{
    char dbName[128], connStr[128];

    if (argc != 3) {
	cout << "Usage: " << argv[0] << " <database> <connection string>"
	     << endl;
	// Get The parameters required to the connection.
	cout << "Enter the database to connect to: ";
	cin >> dbName;
	cout << "Enter the connection string to use: ";
	cin >> connStr;
	cout << endl;
    } else {
	strcpy(dbName, argv[1]);
	strcpy(connStr, argv[2]);
    }

    runStep1(dbName, connStr);

    cout << "Leaving the program ..." << endl;

    return 0;
}
