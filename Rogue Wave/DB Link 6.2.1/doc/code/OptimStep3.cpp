// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: doc/code/OptimStep3.cpp
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

// Length of strings recorded in this sample table.
static const IldUShort strLen = 20;

void Ending(IldDbms* dbms);
void IldDisplayError(const char* operation,
		     const IldIldBase* ildobj);
void runStep1(IldDbms* dbms);

// ----------------------------------------------------------------------------
void Ending(IldDbms* dbms)
{
    // Drop this table before leaving the program.
    const char* dropStr = "drop table OPTIMS3";
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
// This will display the data recorded in the table, using an array, 
// with external binding.
void runDisplay(IldDbms* dbms)
{
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed: ", dbms);
	Ending(dbms);
	exit(1);
    }

    static const IldUShort nbCols = 5;
    char strBuf[nbCols][strLen + 1];
    IldInt intBuf[nbCols];
    short strNulls[nbCols], intNulls[nbCols];

    // Initialize null buffers :
    memset(strNulls, 0, sizeof(short) * nbCols);
    memset(intNulls, 0, sizeof(short) * nbCols);

    if (!request->setColArraySize(nbCols)) {
	IldDisplayError("Could not set columns array size: ", request);
	Ending(dbms);
	exit(1);
    }

    int i = 0;
    const char* selectStr = "select I, S from OPTIMS3";
    if (!request->execute(selectStr))
	IldDisplayError("Select failed: ", request);
    else {
	if (!request->bindCol((IldUShort)0, IldIntegerType, intBuf,
			      sizeof(IldInt), intNulls)) {
	    IldDisplayError("Could not bind first column: ", request);
	    Ending(dbms);
	    exit(1);
	}
	if (!request->bindCol(1, IldStringType, strBuf,
			      strLen + 1, strNulls)) {
	    IldDisplayError("Could not bind second column: ", request);
	    Ending(dbms);
	    exit(1);
	}
	cout << "\t OPTIMS3" << endl;
	cout << "  " << request->getColName(0)
	     << "\t\t" << request->getColName(1) << endl;
	while (request->fetch().hasTuple()) {
	    cout << "  ";
	    if (request->isColNull(0))
		cout << "-";
	    else
		cout << intBuf[i % nbCols];
	    cout << "\t";
	    if (request->isColNull(1))
		cout << "-";
	    else
		cout << "'" << strBuf[i % nbCols] << "'";
	    cout << endl;
	    ++i;
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

    static const IldUShort nbParam = 5;
    // strBuf will be used to store an array of 5 string values.
    char strBuf[nbParam][strLen + 1];
    IldInt intBuf[nbParam];
    short strNulls[nbParam], intNulls[nbParam];

    // Initialize null buffers :
    memset(strNulls, 0, sizeof(short) * nbParam);
    memset(intNulls, 0, sizeof(short) * nbParam);

    if (!request->setParamArraySize(nbParam)) {
	IldDisplayError("Could not set parameter array size: ", request);
	Ending(dbms);
	exit(1);
    }

    const char* insertStr = 0;
    if (!strncmp(dbms->getName(), "oracle", 6))
	insertStr = "insert into OPTIMS3 values (:1, :2)";
    else
	insertStr = "insert into OPTIMS3 values (?, ?)";

    if (!request->parse(insertStr)) {
	IldDisplayError("Parse of query failed: ", request);
	Ending(dbms);
	exit(1);
    }

    if (!request->bindParam((IldUShort)0, IldIntegerType, sizeof(IldInt),
			    intBuf, intNulls)) {
	IldDisplayError("Bind first parameter failed: ", request);
	Ending(dbms);
	exit(1);
    }
    if (!request->bindParam((IldUShort)1, IldStringType, strLen + 1,
			    strBuf, strNulls)) {
	IldDisplayError("Bind second parameter failed: ", request);
	Ending(dbms);
	exit(1);
    }

    IldUShort i, j;
    IldInt nbRows;
    for (i = 0 ; i < nbParam ; i++) {
	intBuf[i] = i;
	// Build a new string value for this set of parameter.
	for (j = 0 ; j < strLen ; ++j)
	    strBuf[i][j] = 'a' + i;
	strBuf[i][j] = 0;
    }
    if (!request->execute(&nbRows, nbParam)) {
	IldDisplayError("Insertion failed: ", request);
	Ending(dbms);
	exit(1);
    } else
	cout << "\t" << nbRows << " row inserted." << endl;

    if (!dbms->commit(request))
	IldDisplayError("Could not commit data: ", dbms);

    if (!request->release())
	IldDisplayError("Could not release request: ", request);

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
	cout << "Connection is OK." << endl;

    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed: ", dbms);
	delete dbms;
	exit(1);
    }

    // Create a new table.
    const char* createStr = "create table OPTIMS3(I int, S char(20))";
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
