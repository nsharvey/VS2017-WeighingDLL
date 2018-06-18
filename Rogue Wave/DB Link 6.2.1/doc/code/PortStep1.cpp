// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: doc/code/PortStep1.cpp
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
char* IldGetOdbcDbms(IldDbms* dbms);
const char* IldGetDateTypeName(const char* dbmsName,
			       const char* dbOdbc);
void createTable(IldDbms* dbms);
void insertData(IldDbms* dbms);

// ----------------------------------------------------------------------------
void Ending(IldDbms* dbms)
{
    // Drop this table before leaving the program.
    const char* dropStr = "drop table PORTS1";
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

// ----------------------------------------------------------------------
// If connected via Odbc, returns the actual RDBMS connected to.
// ----------------------------------------------------------------------
char* IldGetOdbcDbms(IldDbms* dbms)
{
    // If Odbc, get DBMS connected to via Odbc.
    char *dbOdbc = new char [256];
    IldInt notUsed = 0;
    if (!strcmp(dbms->getName(), "odbc")) {
	dbms->getInfo(IldDBMSName, &notUsed, dbOdbc);
	if (!IldStrICaseCmp("oracle7", dbOdbc))
	    // We use oracle for oracle7.
	    dbOdbc[strlen(dbOdbc) - 1] = 0;
    } else
	dbOdbc[0] = 0;
    return dbOdbc;
}

// -----------------------------------------------------------------------
// Find out RDBMS name for DATETIME column type
// -----------------------------------------------------------------------
const char* 
IldGetDateTypeName(IldDbms* dbms)
{
    const char* dbmsName = dbms->getName();
    const char* typeName;

    char* dbOdbc = IldGetOdbcDbms(dbms);

    if (!strncmp(dbmsName, "oracle", 6) 
	|| !IldStrNICaseCmp(dbOdbc, "oracle", 6))
	typeName = "DATE";
    else if (!strncmp(dbmsName, "informix", 8) ||
	     !IldStrNICaseCmp(dbOdbc, "informix", 8))
	// can be set to "date" as well
	typeName = "datetime year to fraction(3)"; 
    else if (!strcmp(dbmsName, "sybase") ||
	     !IldStrNICaseCmp(dbOdbc, "SQL Server", 10))
	typeName = "DATETIME";
    else if (!strcmp(dbmsName, "mssql") ||
	     !IldStrNICaseCmp(dbOdbc, "Microsoft SQL Server", 20))
	typeName = "DATETIME";
    else if (!strcmp(dbmsName, "odbc"))
	typeName = "DATE"; // To do

    delete [] dbOdbc;
    return typeName;
}

// ----------------------------------------------------------------------------
void createTable(IldDbms* dbms)
{
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed : ", dbms);
	delete dbms;
	exit(1);
    }

    // Create a new table.
    char createStr[80];
    strcpy(createStr, "create table PORTS1(D ");
    strcat(createStr, IldGetDateTypeName(dbms));
    strcat(createStr, ")");
    cout << "Creating a table: " << createStr << endl;
    request->execute(createStr);
    if (request->isErrorRaised()) {
	IldDisplayError("Table creation failed : ", request);
	delete dbms;
	exit(1);
    }
    request->release();
}

// ----------------------------------------------------------------------------
void displayData(IldDbms* dbms)
{
    static const char* selectStr = "select D from PORTS1";
    const char* dateStr = 0;
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed: ", dbms);
	delete dbms;
	exit(1);
    }

    if (!request->execute(selectStr)) {
	IldDisplayError("Could not run select query: ", request);
	delete dbms;
	exit(1);
    }

    cout << "\t PORTS1" << endl;
    cout << "\t   " << request->getColName(0) << endl;

    while (request->fetch().hasTuple()) {
	dateStr = request->getColStringValue(0);
	cout << dateStr << endl;
    }
    request->release();
}

// ----------------------------------------------------------------------------
void insertData(IldDbms* dbms)
{
    static const IldUShort nbParam = 2;
    IldInt rowCount = 0;
    IldUShort i = 0 
	//Array of dates we will use to send records to the table:
	IldDateTime dates[nbParam];
    short dateNulls[nbParam];
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
    // Activate "date as object" mode:
    request->setStringDateUse(IldFalse);

    const char* insertStr =
	(!strncmp(dbms->getName(), "oracle", 6)) ?
	"insert into PORTS1 values (:1)":
	"insert into PORTS1 values (?)";

    cout << "Parse request: " << insertStr << endl;
    if (!request->parse(insertStr)) {
	IldDisplayError("Could not parse insert query: ", request);
	Ending(dbms);
	exit(1);
    }

    // Binding of the parameter as a datetime object:
    if (!request->bindParam((IldUShort)0, IldDateTimeType, sizeof(IldDateTime),
			    dates, dateNulls)) {
	IldDisplayError("Bind parameter failed: ", request);
	Ending(dbms);
	exit(1);
    }

    // Set the values for the dates:
    for (i = 0 ; i < nbParam ; ++i) {
	dates[i].setYear(1999);
	dates[i].setMonth(10);
	dates[i].setDay(i + 1);
	dates[i].setHour(10);
	dates[i].setMinute(30);
	dateNulls[i] = 0;
    }

    // Initialize null buffer:
    memset(dateNulls, 0, sizeof(short) * nbParam);

    // Execute the query:
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
    char dbName[128], connStr[128];

    if (argc != 3) {
	cout << "Usage: " << argv[0] << " <database> <connection string>"
	     << endl;
	// Get The parameters required to the connection.
	cout << "Enter the database to connect to : ";
	cin >> dbName;
	cout << "Enter the connection string to use : ";
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

    createTable(dbms);

    insertData(dbms);

    displayData(dbms);

    Ending(dbms);
    cout << "Leaving the program ..." << endl;

    return 0;
}

