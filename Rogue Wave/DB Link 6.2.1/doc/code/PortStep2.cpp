// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: doc/code/PortStep2.cpp
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
const char* IldGetNumericTypeName(IldDbms* dbms);
void createTable(IldDbms* dbms);
void displayNumericMode(IldDbms* dbms,
			IldRequest* request,
			const char* message,
			IldColumnType expectedType);
const char* typeAsString(IldColumnType type);
void checkNumericMode(IldDbms* dbms);

// ----------------------------------------------------------------------------
void Ending(IldDbms* dbms)
{
    // Drop this table before leaving the program.
    const char* dropStr = "drop table PORTS2";
    cout << "Dropping table : " << dropStr << endl;
    if (!dbms->execute(dropStr))
	IldDisplayError("Drop table failed : ", dbms);
    // Disconnect and release memory.
    delete dbms;
}

// ----------------------------------------------------------------------------
void IldDisplayError(const char* operation,
		     const IldIldBase* ildobj)
{
    cout << operation << endl;
    cout << " Code : " << ildobj->getErrorCode() << endl;
    cout << " SqlState : " << ildobj->getErrorSqlstate() << endl;
    cout << " Message : " << ildobj->getErrorMessage() << endl;
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
// Find out RDBMS name for NUMERIC column type
// -----------------------------------------------------------------------
const char* 
IldGetNumericTypeName(IldDbms* dbms)
{
    const char* dbmsName = dbms->getName();
    const char* typeName;

    char *dbOdbc = IldGetOdbcDbms(dbms);

    if (!strncmp(dbmsName, "oracle", 6)
	|| !IldStrNICaseCmp(dbOdbc, "oracle", 6)
	|| !strncmp(dbmsName, "informix", 8) ||
	!IldStrNICaseCmp(dbOdbc, "informix", 8)
	|| !strcmp(dbmsName, "sybase") ||
	!IldStrNICaseCmp(dbOdbc, "SQL Server", 10))
	typeName = "NUMERIC(32, 9)";
    else if (!strcmp(dbmsName, "mssql") ||
	     !IldStrNICaseCmp(dbOdbc, "Microsoft SQL Server", 20))
	typeName = "NUMERIC(28, 9)";
    else if (!strcmp(dbmsName, "odbc"))
	typeName = "NUMERIC"; // To do
    
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
    strcpy(createStr, "create table PORTS2(N ");
    strcat(createStr, IldGetNumericTypeName(dbms));
    strcat(createStr, ")");
    cout << "Creating a table : " << createStr << endl;
    if (!request->execute(createStr)) {
	IldDisplayError("Table creation failed : ", request);
	delete dbms;
	exit(1);
    }
    request->release();
}

// ----------------------------------------------------------------------------
void displayData(IldDbms* dbms)
{
    static const char* selectStr = "select N from PORTS2";
    IldNumeric num;
    char numStr[ILD_MAX_NUM_LEN];
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed : ", dbms);
	Ending(dbms);
	exit(1);
    }
    request->setNumericUse(IldTrue);

    if (!request->execute(selectStr)) {
	IldDisplayError("Could not run select query : ", request);
	Ending(dbms);
	exit(1);
    }

    cout << "\t PORTS2" << endl;
    cout << "\t   " << request->getColName(0) << endl;

    while (request->fetch().hasTuple()) {
	num = request->getColNumericValue(0);
	if (request->isErrorRaised())
	    IldDisplayError("Could not get value : ", request);
	else {
	    num.get(numStr, ILD_MAX_NUM_LEN);
	    cout << numStr << endl;
	}
    }
    request->release();
}

// ----------------------------------------------------------------------------
void insertData(IldDbms* dbms)
{
    static const IldUShort nbParam = 2;
    IldInt rowCount = 0;
    // Array of numbers we will use to send records to the table:
    IldNumeric nums[nbParam];
    short numNulls[nbParam];
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed : ", dbms);
	Ending(dbms);
	exit(1);
    }
    if (!request->setParamArraySize(nbParam)) {
	IldDisplayError("Could not set parameter array size : ", request);
	Ending(dbms);
	exit(1);
    }
    // Activate "numeric as object" mode:
    request->setNumericUse(IldTrue);

    const char* insertStr =
	(!strncmp(dbms->getName(), "oracle", 6)) ?
	"insert into PORTS2 values (:1)":
	"insert into PORTS2 values (?)";

    cout << "Parse request : " << insertStr << endl;
    if (!request->parse(insertStr)) {
	IldDisplayError("Could not parse insert query : ", request);
	Ending(dbms);
	exit(1);
    }

    // Binding of the parameter as a numeric object:
    if (!request->bindParam((IldUShort)0, IldNumericType,
			    sizeof(IldNumeric), nums, numNulls)) {
	IldDisplayError("Bind parameter failed : ", request);
	Ending(dbms);
	exit(1);
    }

    // Set the values for the numbers:
    nums[0].set("1234567890.456");
    nums[1].set("-86420.13579");

    // Initialize null buffers:
    memset(numNulls, 0, sizeof(short) * nbParam);

    // Execute the query:
    if (!request->execute(&rowCount, nbParam)) {
	IldDisplayError("Could not execute insert query : ", request);
	Ending(dbms);
	exit(1);
    } else
	cout << rowCount << " rows inserted." << endl;

    request->release();
}

// ----------------------------------------------------------------------------
const char* typeAsString(IldColumnType type)
{
    switch (type) {
    case IldNumericType:
	return "IldNumericType";
    case IldIntegerType:
	return "IldIntegerType";
    case IldRealType:
	return "IldRealType";
    case IldStringType:
	return "IldStringType";
    default:
	return "Unexpected type";
    }
}

// ----------------------------------------------------------------------------
void displayNumericMode(IldDbms* dbms,
			IldRequest* request,
			const char* message,
			IldColumnType expectedType)
{
    static const char* selectStr = "select N from PORTS2";
    cout << message << endl
	 << "* request->useNumeric() = "
	 << (request->useNumeric() ? "IldTrue" : "IldFalse")
	 << ", request->useStringNumeric() = "
	 << (request->useStringNumeric() ? "IldTrue" : "IldFalse") << endl;
    if (!request->execute(selectStr)) {
	IldDisplayError("Select execution failed : ", request);
	Ending(dbms);
	exit(1);
    }
    cout << "Column type should be "
	 << typeAsString(expectedType) << ", and it is: "
	 << typeAsString(request->getColType(0)) << " ==> "
	 << (expectedType != request->getColType(0) ? "ERROR" : "OK")
	 << "." << endl << endl;
}

// ----------------------------------------------------------------------------
void checkNumericMode(IldDbms* dbms)
{
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed : ", dbms);
	Ending(dbms);
	exit(1);
    }

    // Run a first select in default mode :
    displayNumericMode(dbms, request,
		       "Default mode is ativated:", IldRealType);

    // Repeat the operation in "numeric as string" mode:
    request->setStringNumericUse(IldTrue);
    displayNumericMode(dbms, request,
		       "Mode \"Numeric as String\" is activated:",
		       IldStringType);

    // Repeat the operation in "numeric as object" mode :
    request->setNumericUse(IldTrue);
    displayNumericMode(dbms, request,
		       "Mode \"Numeric as Object\" is activated:",
		       IldNumericType);

    // Go back to default mode, and repeat the operation:
    // Default mode can be set either with setNumericUse(IldFalse),
    // or with setStringNumericUse(IldFalse).
    request->setStringNumericUse(IldFalse);
    displayNumericMode(dbms, request,
		       "We are back to default mode: ", IldRealType);

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
	IldDisplayError("Connection failed : ", dbms);
	delete dbms;
	exit(1);
    } else
	cout << "Connection is OK." << endl;

    createTable(dbms);

    checkNumericMode(dbms);

    insertData(dbms);

    displayData(dbms);

    Ending(dbms);
    return 0;
}
