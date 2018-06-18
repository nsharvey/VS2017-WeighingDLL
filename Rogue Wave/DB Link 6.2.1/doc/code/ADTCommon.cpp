// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: doc/code/ADTCommon.cpp
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
#include <ctype.h>

#include <ildblink/dblink.h>

// ----------------------------------------------------------------------------
void Ending(IldDbms* dbms);
void IldDisplayError(const char* operation,
		     const IldIldBase* ildObj);
char* checkCase(char* name,
		IldDbms* dbms,
		IldBoolean itself = IldTrue);
void createADT(IldDbms* dbms);
IldDbms* checkUsageOk(int argc,
		      char* argv[]);

// ----------------------------------------------------------------------------
static char createPoint[100];
static char createLine[100];
static char createBridge[100];
static char createBridgeLst[100];
static char dropPoint[100];
static char dropLine[100];
static char dropBridge[100];
static char dropBridgeLst[100];

// ----------------------------------------------------------------------------
void Ending(IldDbms* dbms)
{
    if (dropBridgeLst[0] && !dbms->execute(dropBridgeLst))
	IldDisplayError("Could not drop BRIDGELST datatype: ", dbms);
    if (!dbms->execute(dropBridge))
	IldDisplayError("Could not drop BRIDGE datatype: ", dbms);
    if (!dbms->execute(dropLine))
	IldDisplayError("Could not drop LINE datatype: ", dbms);
    if (!dbms->execute(dropPoint))
	IldDisplayError("Could not drop POINT datatype: ", dbms);
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
char* checkCase(char* name,
		IldDbms* dbms,
		IldBoolean itself)
{
    char* resName = 0;
    char cv[254];
    IldInt iv = 0;
    int i = 0;
    if (!dbms->getInfo(IldIdentifierCase, &iv, cv))
	IldDisplayError("Could not access RDBMS case mode: ", dbms);
    else {
	if (itself)
	    resName = name;
	else {
	    resName = new char [strlen(name) + 1];
	    strcpy(resName, name);
	}
	switch (iv) {
	case IldIdentifierUpper:
	    for ( ; i < (int)strlen(name) ; ++i)
		resName[i] = (char) toupper(name[i]);
	    break;
	case IldIdentifierLower:
	    for ( ; i < (int)strlen(name) ; ++i)
		resName[i] = (char) tolower(name[i]);
	    break;
	default:
	    break;
	}
    }
    return resName;
}

// ----------------------------------------------------------------------------
void createADT(IldDbms* dbms)
{
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed: ", dbms);
	delete dbms;
	exit(1);
    }

    if (!strcmp(dbms->getName(), "informix9")) {
	strcpy(createPoint, "create row type POINT (X int, Y int)");
	strcpy(createLine, "create row type LINE (P1 POINT, P2 POINT)");
	strcpy(createBridge,
	       "create row type BRIDGE (L LINE, NAME VARCHAR(20))");
	strcpy(createBridgeLst, "");
	strcpy(dropPoint, "drop row type POINT restrict");
	strcpy(dropLine, "drop row type LINE restrict");
	strcpy(dropBridge, "drop row type BRIDGE restrict");
	strcpy(dropBridgeLst, "");
    } else {
	// Oracle
	// We want to use integers, but Oracle only handles numbers
	// ==> to get an integer value, we specify number(10, 0).
	strcpy(createPoint,
	       "create type POINT as object (X number(10, 0), Y number(10, 0))");
	strcpy(createLine, "create type LINE as object (P1 POINT, P2 POINT)");
	strcpy(createBridge,
	       "create type BRIDGE as object (L LINE, NAME VARCHAR(20))");
	strcpy(createBridgeLst,
	       "create type BRIDGELST as varray(20) of bridge");
	strcpy(dropPoint, "drop type POINT");
	strcpy(dropLine, "drop type LINE");
	strcpy(dropBridge, "drop type BRIDGE");
	strcpy(dropBridgeLst, "drop type BRIDGELST");
    }

    cout << "Create POINT datatype: " << createPoint << endl;
    if (!request->execute(createPoint)) {
	IldDisplayError("Could not create POINT datatype: ", request);
	delete dbms;
	exit(-1);
    }
    cout << "Create LINE datatype: " << createLine << endl;
    if (!request->execute(createLine)) {
	IldDisplayError("Could not create LINE datatype: ", request);
	if (!request->execute(dropPoint))
	    IldDisplayError("Could not drop POINT datatype: ", request);
	delete dbms;
	exit(-1);
    }
    cout << "Create BRIDGE datatype: " << createBridge << endl;
    if (!request->execute(createBridge)) {
	IldDisplayError("Could not create BRIDGE datatype: ", request);
	if (!request->execute(dropLine))
	    IldDisplayError("Could not drop LINE datatype: ", request);
	if (!request->execute(dropPoint))
	    IldDisplayError("Could not drop POINT datatype: ", request);
	delete dbms;
	exit(-1);
    }
    if (createBridgeLst[0]) {
	cout << "Create BRIDGELST datatype: " << createBridgeLst << endl;
	if (!request->execute(createBridgeLst)) {
	    IldDisplayError("Could not create BRIDGELST datatype: ", request);
	    if (!request->execute(dropBridge))
		IldDisplayError("Could not drop BRIDGE datatype: ", request);
	    if (!request->execute(dropLine))
		IldDisplayError("Could not drop LINE datatype: ", request);
	    if (!request->execute(dropPoint))
		IldDisplayError("Could not drop POINT datatype: ", request);
	    delete dbms;
	    exit(-1);
	}
    }

    if (!dbms->commit(request))
	IldDisplayError("Commit failed: ", dbms);

    request->release();
}

// ----------------------------------------------------------------------------
// Check program arguments are OK, and open the connection.
IldDbms* checkUsageOk(int argc,
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
    if (strcmp(dbName, "informix9") && strncmp(dbName, "oracle", 6)) {
	cout << "ADT is implemented only for Informix 9 or Oracle" << endl
	     << "<database> parameter must be one of those." << endl;
	exit(1);
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

    return dbms;
}
