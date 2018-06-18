// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: doc/code/OptimStep1.cpp
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
#include <stdlib.h>

#include <ildblink/dblink.h>


void Ending(IldDbms* dbms);
void IldDisplayError(const char* operation,
		     const IldIldBase* ildobj);
void runStep1(IldDbms* dbms);

// ----------------------------------------------------------------------------
void Ending(IldDbms* dbms)
{
    // Drop this table before leaving the program.
    const char* dropStr = "drop table OPTIMS1";
    cout << "Dropping table: " << dropStr << endl;
    if (!dbms->execute(dropStr))
	IldDisplayError("Drop table failed: ", dbms);
    // Disconnect and release memory.
    delete dbms;
}

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
// This will display the data recorded in the table.
void runDisplay(IldDbms* dbms)
{
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed: ", dbms);
	Ending(dbms);
	exit(1);
    }

    const char* selectStr = "select I, S from OPTIMS1";
    if (!request->execute(selectStr))
	IldDisplayError("Select failed: ", request);
    else {
	cout << "\t OPTIMS1" << endl;
	cout << "  " << request->getColName(0)
	     << "\t\t" << request->getColName(1) << endl;
	while (request->fetch().hasTuple()) {
	    cout << "  " << request->getColIntegerValue(0)
		 << "\t'" << request->getColStringValue(1) << "'" << endl;
	}
	cout << endl;
    }
    if (!request->release())
	IldDisplayError("Could not release request: ", request);
}

// ----------------------------------------------------------------------------
void runStep1(IldDbms* dbms)
{
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed: ", dbms);
	Ending(dbms);
	exit(1);
    }

    const char* insertStr = 0;
    if (!strncmp(dbms->getName(), "oracle", 6))
	insertStr = "insert into OPTIMS1 values (:1, :2)";
    else
	insertStr = "insert into OPTIMS1 values (?, ?)";

    if (!request->parse(insertStr)) {
	IldDisplayError("Parse of query failed: ", request);
	Ending(dbms);
	exit(1);
    }

    if (!request->bindParam((IldUShort)0, IldIntegerType)) {
	IldDisplayError("Bind first parameter failed: ", request);
	Ending(dbms);
	exit(1);
    }
    if (!request->bindParam((IldUShort)1, IldStringType)) {
	IldDisplayError("Bind second parameter failed: ", request);
	Ending(dbms);
	exit(1);
    }

    static const IldUShort strLen = 20;
    IldUShort i, j;
    IldInt nbRows, nVal;
    // strBuf will be used to build a different string for each execution.
    char strBuf[strLen + 1];
    strBuf[strLen] = 0;
    for (i = 0 ; i < 5 ; i++) {
	nVal = i;
	// Build a new string value for this execution.
	for (j = 0 ; j < strLen ; ++j)
	    strBuf[j] = 'a' + i;
	// Set parameter values.
	if (!request->setParamValue(nVal, 0) ||
	    !request->setParamValue(strBuf, 1)) {
	    IldDisplayError("Set parameter value failed:", request);
	    Ending(dbms);
	    exit(1);
	}
	// Execute the query.
	if (!request->execute(&nbRows, 1)) {
	    IldDisplayError("Insertion failed: ", request);
	    Ending(dbms);
	    exit(1);
	} else
	    cout << "\t" << nbRows << " row inserted." << endl;
    }

    if (!request->release())
	IldDisplayError("Could not release request:", request);

    runDisplay(dbms);

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

    // Connection to the RDBMS.
    IldDbms* dbms = IldNewDbms(dbName, connStr);

    // Check Connection is OK.
    if (dbms->isErrorRaised()) {
	IldDisplayError("Connection failed: ", dbms);
	delete dbms;
	exit(1);
    } else
	cout << "Connection established." << endl;

    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed: ", dbms);
	delete dbms;
	exit(1);
    }

    // Create a new table.
    const char* createStr = "create table OPTIMS1(I int, S char(20))";
    cout << "Creating a table: " << createStr << endl;
    request->execute(createStr);
    if (request->isErrorRaised()) {
	IldDisplayError("Table creation failed: ", request);
	delete dbms;
	exit(1);
    }
    request->release();

    runStep1(dbms);

    Ending(dbms);
    cout << "Leaving the program ..." << endl;

    return 0;
}
