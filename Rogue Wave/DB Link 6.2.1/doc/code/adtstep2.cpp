// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: doc/code/adtstep2.cpp
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

// Functions defined in ADTCommon.cpp
extern void Ending(IldDbms* dbms);
extern void IldDisplayError(const char* operation,
			    const IldIldBase* ildObj);
extern char* checkCase(char* name,
		       IldDbms* dbms,
		       IldBoolean itself = IldTrue);
extern void createADT(IldDbms* dbms);
extern IldDbms* checkUsageOk(int argc,
			     char* argv[]);

// Functions defined in this file :
void localEnd(IldDbms* dbms);
void createTable(IldDbms* dbms);
IldADTDescriptor* getSubADTDescriptor(IldDbms* dbms,
				      const IldADTDescriptor* adt,
				      IldUShort idx,
				      const char* ADTName);
void insertData(IldDbms* dbms) ;
void displayADT(IldADTValue* v) ;
void displayData(IldDbms* dbms) ;

// ----------------------------------------------------------------------------
void localEnd(IldDbms* dbms)
{
    // Drop this table before leaving the program.
    static const char* dropStr = "drop table ADTS2";
    cout << "Dropping table : " << dropStr << endl;
    if (!dbms->execute(dropStr))
	IldDisplayError("Drop table failed : ", dbms);
    Ending(dbms);
}

// ----------------------------------------------------------------------------
void createTable(IldDbms* dbms)
{
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed : ", dbms);
	Ending(dbms);
	exit(1);
    }

    // Create a new table.
    static const char* query = 0;
    if (!strcmp(dbms->getName(), "informix9"))
	query = "create table ADTS2 (RIVER varchar(20), LENGTH int, B list(BRIDGE not null))";
    else
	// Oracle
	query = "create table ADTS2 (RIVER varchar(20), LENGTH number(10, 0), B BRIDGELST)";
    cout << "Run : " << query << endl;
    if (!request->execute(query)) {
	IldDisplayError("Table creation failed : ", request);
	Ending(dbms);
	exit(1);
    }

    request->release();
}

// ----------------------------------------------------------------------------
IldADTDescriptor* getSubADTDescriptor(IldDbms* dbms,
				      const IldADTDescriptor* adt,
				      IldUShort idx,
				      const char* ADTName)
{
  IldADTDescriptor* subAdt = 0;
  // Get the descriptor at given position:
  const IldDescriptor* desc = 0;
  if (adt->getType() == IldADTObject) {
    if (adt->getAttributesCount() > idx)
      desc = adt->getAttributes()[idx];
  }
  else
    desc = adt->getCollectionAttribute();
  if (!desc) {
    cout << "Could not get descriptor for : " << ADTName << endl;
    localEnd(dbms);
    exit(1);
  }
  // Get the ADT descriptor:
  subAdt = desc->getADTDescriptor();
  if (!subAdt) {
    cout << "Could not get ADT descriptor for : " << ADTName << endl;
    localEnd(dbms);
    exit(1);
  }
  return subAdt;
}

// ----------------------------------------------------------------------------
void insertData(IldDbms* dbms)
{
    IldInt rowCount = 0;
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed : ", dbms);
	localEnd(dbms);
	exit(1);
    }

    if (!strcmp(dbms->getName(), "informix9")) {
	// Informix needs some data in the table to build ADT parameters.
	const char* insertQuery = "insert into ADTS2 values ('RIVER1', 10, 'list{row(row(row(5, 30), row(10, 50)), ''BRIDGE1'')}')";
	if (!request->execute(insertQuery)) {
	    IldDisplayError("Informix insert query failed : ", request);
	    localEnd(dbms);
	    exit(1);
	}
    }

    // Retrieve the descriptor of the parameter object type.
    IldADTDescriptor* bridgeLstAdt = 0;
    const char* query = "select B from ADTS2";
    if (!request->execute(query)) {
	IldDisplayError("Could not select object column : ", request);
	localEnd(dbms);
	exit(1);
    }
    bridgeLstAdt = request->getColDescriptor(0)->getADTDescriptor();

    // Parse the insert query:
    const char * insertStr = 
	(!strncmp(dbms->getName(), "oracle", 6) ?
	 "insert into ADTS2 values ('River Name', 30, :1)":
	 "insert into ADTS2 values ('River Name', 30, ?)");

    cout << "Parse request : " << insertStr << endl;
    if (!request->parse(insertStr)) {
	IldDisplayError("Could not parse insert query : ", request);
	localEnd(dbms);
	exit(1);
    }

    if (!request->bindParam((IldUShort)0, IldCollectionType, -1, 0, 0,
			    IldFalse, 0, bridgeLstAdt)) {
	IldDisplayError("Could not bind object parameter : ", request);
	localEnd(dbms);
	exit(1);
    }

    // Get the ADT Descriptor for the bridge object:
    IldADTDescriptor* bridgeAdt = getSubADTDescriptor(dbms, bridgeLstAdt,
						      0, "bridge");
    // Get the ADT Descriptor for the line object:
    IldADTDescriptor* lineAdt = getSubADTDescriptor(dbms, bridgeAdt,
						    0, "line");
    // Get the ADT Descriptor for the point object:
    IldADTDescriptor* pointAdt = getSubADTDescriptor(dbms, lineAdt,
						     0, "point");

    // Create values:
    IldADTValue* pointObj1  = new IldADTValue(pointAdt);
    IldADTValue* pointObj2  = new IldADTValue(pointAdt);
    IldADTValue* lineObj1   = new IldADTValue(lineAdt);
    IldADTValue* bridgeObj1 = new IldADTValue(bridgeAdt);
    IldADTValue* bridgeLst  = new IldADTValue(bridgeLstAdt);

    pointObj1->setValue((IldInt)10, 0); // X for point 1.
    pointObj1->setValue((IldInt)20, 1); // Y for point 1.
    pointObj2->setValue((IldInt)10, 0); // X for point 2.
    pointObj2->setValue((IldInt)30, 1); // Y for point 2.

    lineObj1->setValue(pointObj1, 0); // First point of the line.
    lineObj1->setValue(pointObj2, 1); // Second point of the line.

    bridgeObj1->setValue(lineObj1, 0);
    bridgeObj1->setValue("Bridge Name", 1);

    bridgeLst->setValue(bridgeObj1, 0);

    if (!request->setParamValue(bridgeLst, 0)) {
	IldDisplayError("Could not set parameter value : ", request);
	localEnd(dbms);
	exit(1);
    }

    if (!request->execute(&rowCount, 1)) {
	IldDisplayError("Could not execute query : ", request);
	localEnd(dbms);
	exit(1);
    } else
	cout << rowCount << " rows inserted." << endl;

    // Build a second value with more elements in the list:
    IldADTValue* pointObj3  = new IldADTValue(pointAdt);
    IldADTValue* pointObj4  = new IldADTValue(pointAdt);
    IldADTValue* pointObj5  = new IldADTValue(pointAdt);
    IldADTValue* pointObj6  = new IldADTValue(pointAdt);
    IldADTValue* lineObj2   = new IldADTValue(lineAdt);
    IldADTValue* lineObj3   = new IldADTValue(lineAdt);
    IldADTValue* bridgeObj2 = new IldADTValue(bridgeAdt);
    IldADTValue* bridgeObj3 = new IldADTValue(bridgeAdt);

    pointObj3->setValue((IldInt)50, 0); // X for point 3.
    pointObj3->setValue((IldInt)80, 1); // Y for point 3.
    pointObj4->setValue((IldInt)60, 0); // X for point 4.
    pointObj4->setValue((IldInt)100, 1); // Y for point 4.
    pointObj5->setValue((IldInt)75, 0);
    pointObj5->setValue((IldInt)110, 1);
    pointObj6->setValue((IldInt)85, 0);
    pointObj6->setValue((IldInt)130, 1);

    lineObj2->setValue(pointObj3, 0); // First point of the line.
    lineObj2->setValue(pointObj4, 1); // Second point of the line.
    lineObj3->setValue(pointObj5, 0);
    lineObj3->setValue(pointObj6, 1);

    bridgeObj2->setValue(lineObj2, 0);
    bridgeObj2->setValue("Second bridge", 1);
    bridgeObj3->setValue(lineObj3, 0);
    bridgeObj3->setValue("Third bridge", 1);

    bridgeLst->setValue(bridgeObj2, 1);
    bridgeLst->setValue(bridgeObj3, 2);

    if (!request->setParamValue(bridgeLst, 0)) {
	IldDisplayError("Could not set parameter value : ", request);
	localEnd(dbms);
	exit(1);
    }

    if (!request->execute(&rowCount, 1)) {
	IldDisplayError("Could not execute query : ", request);
	localEnd(dbms);
	exit(1);
    } else
	cout << rowCount << " rows inserted." << endl;

    // The release operation will free IldADTValue* allocated previously.
    request->release();
}

// ----------------------------------------------------------------------------
void displayADT(IldADTValue* v)
{
    cout << v->getTypeName() << "(";
    IldUShort slot = 0, nbSlot = 0;
    nbSlot = (IldUShort)v->getCount();
    for (slot = 0 ; slot < nbSlot ; ++slot) {
	if (slot)
	    cout << ", ";
	if (v->isNull(slot))
	    cout << " - ";
	else {
	    switch (v->getType(slot)) {
	    case IldStringType:
		cout << "'" << v->getStringValue(slot) << "'";
		break;
	    case IldIntegerType:
		cout << v->getIntegerValue(slot);
		break;
	    case IldObjectType:
	    case IldCollectionType:
		displayADT(v->getADTValue(slot));
		break;
	    default:
		cout << "Unexpected datatype";
	    }
	}
    }
    cout << ")";
}

// ----------------------------------------------------------------------------
void displayData(IldDbms* dbms)
{
    // Get a new request.
    IldRequest* request = dbms->getFreeRequest();
    if (dbms->isErrorRaised()) {
	IldDisplayError("Creation of request failed : ", dbms);
	localEnd(dbms);
	exit(1);
    }

    const char* query = "select * from ADTS2";
    if (!request->execute(query)) {
	IldDisplayError("Could not select object column : ", request);
	localEnd(dbms);
	exit(1);
    }

    // Print selected item Names.
    IldUShort i = 0;
    IldUShort nbCols = request->getColCount();
    cout << endl << "\t\tADTS2" << endl;
    for (i = 0 ; i < nbCols ; ++i)
	cout << "\t" << request->getColName(i);
    cout << endl;
    while (request->fetch().hasTuple()) {
	cout << "  ";
	for (i = 0 ; i < nbCols ; ++i) {
	    if (request->isColNull(i))
		cout << "-";
	    else
		switch (request->getColType(i)) {
		case IldIntegerType:
		    cout << request->getColIntegerValue(i);
		    break;
		case IldStringType:
		    cout << "'" << request->getColStringValue(i) << "'";
		    break;
		case IldCollectionType: {
		    IldADTValue* value = 0;
		    if (!(value = request->getColADTValue(i)))
			IldDisplayError("Could not get ADT value : ", request);
		    else
			displayADT(value);
		    break;
		}
		default:
		    // Other possible types are not handled here.
		    break;
		}
	    cout << "\t";
	}
	cout << endl;
    }
    cout << endl;

    request->release();
}

// ----------------------------------------------------------------------------
int main(int argc,
	 char* argv[])
{
    // Check program arguments are OK, and open the connection.
    IldDbms* dbms = checkUsageOk(argc, argv);

    createADT(dbms);

    createTable(dbms);

    insertData(dbms);

    displayData(dbms);

    localEnd(dbms);

    cout << "Leaving the program ..." << endl;

    return 0;
}
