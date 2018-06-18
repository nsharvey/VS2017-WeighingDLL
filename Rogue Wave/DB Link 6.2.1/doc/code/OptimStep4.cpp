// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: doc/code/OptimStep4.cpp
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
void readData(IldDbms* dbms,
	      IldInt values[],
	      IldUShort nbVal);
void insertData(IldDbms* dbms);

// ----------------------------------------------------------------------------
void Ending(IldDbms* dbms)
{
    // Drop this table before leaving the program.
    const char* dropStr = "drop table OPTIMS4";
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
void readData(IldDbms* dbms,
	      IldInt values[],
	      IldUShort nbVal)
{
    static const char* selectStr = "select I from OPTIMS4";
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed: ", dbms);
	Ending(dbms);
	exit(1);
    }

    if (!request->execute(selectStr)) {
	IldDisplayError("Could not run select query : ", request);
	Ending(dbms);
	exit(1);
    }

    IldUShort i = 0;
    if (!request->bindCol((IldUShort)0, IldIntegerType, &values[i])) {
	IldDisplayError("Could not bind column: ", request);
	Ending(dbms);
	exit(1);
    }
    while (request->fetch().hasTuple())
	if (++i == nbVal)
	    break;
	else if (!request->bindCol((IldUShort)0, IldIntegerType, &values[i])) {
	    IldDisplayError("Could not bind column: ", request);
	    Ending(dbms);
	    exit(1);
	}

    request->release();
}

// ----------------------------------------------------------------------------
void insertData(IldDbms* dbms)
{
    static const IldUShort nbParam = 20;
    IldInt rowCount = 0;
    IldUShort i = 0;
    // Array of integers to insert:
    IldInt values[nbParam];
    short valNulls[nbParam];
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed: ", dbms);
	delete dbms;
	exit(1);
    }
    if (!request->setParamArraySize(nbParam)) {
	IldDisplayError("Could not set parameter array size: ", request);
	Ending(dbms);
	exit(1);
    }
    const char* insertStr =
	(!strncmp(dbms->getName(), "oracle", 6) ||
	 !strcmp(dbms->getName(), "sqlbase")) ?
	"insert into OPTIMS4 values (:1)":
	"insert into OPTIMS4 values (?)";

    cout << "Parse request: " << insertStr << endl;
    if (!request->parse(insertStr)) {
	IldDisplayError("Could not parse insert query: ", request);
	Ending(dbms);
	exit(1);
    }

    if (!request->bindParam((IldUShort)0, IldIntegerType, sizeof(IldInt),
			    values, valNulls)) {
	IldDisplayError("Bind parameter failed : ", request);
	Ending(dbms);
	exit(1);
    }

    // Set the values:
    for (i = 0 ; i < nbParam ; ++i)
	values[i] = 10 * i;

    // Initialize null buffers:
    memset(valNulls, 0, sizeof(short) * nbParam);

    // Execute the query :
    if (!request->execute(&rowCount, nbParam)) {
	IldDisplayError("Could not execute insert query: ", request);
	Ending(dbms);
	exit(1);
    } else
	cout << rowCount << " rows inserted." << endl;

    request->release();
}

// ----------------------------------------------------------------------------
int main(int argc,
	 char* argv[])
{
    static const IldUShort nbVal = 10;
    char dbName[128], connStr[128];
    IldInt values[nbVal];
    IldUShort i = 0;

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
    const char* createStr = "create table OPTIMS4(I int)";
    cout << "Creating a table: " << createStr << endl;
    request->execute(createStr);
    if (request->isErrorRaised()) {
	IldDisplayError("Table creation failed: ", request);
	delete dbms;
	exit(1);
    }
    request->release();

    insertData(dbms);

    readData(dbms, values, nbVal);

    Ending(dbms);

    cout << "Connection with the RDBMS is closed, but we can still access"
	 << endl << "the data we got : " << endl;
    for (i = 0 ; i < nbVal ; i++)
	cout << values[i] << (i < nbVal - 1 ? ", " : ""); 
    cout << endl;

    cout << "Leaving the program ..." << endl;

    return 0;
}
