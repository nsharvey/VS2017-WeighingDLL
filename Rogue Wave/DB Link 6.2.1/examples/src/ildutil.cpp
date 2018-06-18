// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: examples/src/ildutil.cpp
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
// This file contains functions used by most sample and test programs:
//
//     + "IldFormatLine" which takes an array of items as argument.
//       Each item has a value, an identation mode (right, left, or
//       middle) and a length.
//       The function fills an output buffer up with item values using
//       formatting information.
//
//     + "IldPrintRelation" uses the previous function to print a
//       relation.
//
//     + "IldPrintTuple" prints a tuple.
//
//     + "IldGetOdbcDbms" get the name of the RDBMS connected to
//                        via ODBC..
//
//     + "IldGetDateTypeName" get date type for various dbms.
//
//     + "IldGetNumericTypeName" get numeric type for various dbms.
//
//     + "IldGetLongBinaryTypeName" get long binary type for various
//                                  dbms.
//
//     + "IldGetLongTextTypeName" get Long text type for various Dbms.
//
//     + "IldEndSample" drops the table and terminates the application,
//                      optionaly displaying a final message.
//
//     + "IldPrintResults" display all rows returned by a query.
//
//     + "IldDisplayError" print the error code and messge.
//
//     + "IldDisplayDiags" print the diagnostics of the object. Both
//	                  error and information will be printed.
//
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

#ifdef IL_STD
# ifndef _STRSTREAM_
#  include <strstream>
# endif
#else
# ifndef _STRSTREAM_H_
#  ifndef WINDOWS
#   include <strstream.h>
#  else
#   include <strstrea.h>
#  endif
# endif
#endif

IL_STDUSE

// ----------------------------------------------------------------------------
// Globals
// ----------------------------------------------------------------------------

static char* Buffers = 0;
static int Size = 0;
static IldItemStruct* Items = 0;

static const char SPC = ' ';
static const char PIP = '|';
static const char QTE = '\'';
static const char STR = '*';
static const char DSH = '-';
static const char VBR = '|';

static const char* EQUAL = "=";
static const char* DASH = "-";
static const char* CPAR = ")";
static const char* OPAR = "(";
static const char* COMM = ", ";
static const char* SCOL = "; ";
static const char* COLN = ": ";
static const char* DOT = ".";
static const char* QUOT = "'";

// ----------------------------------------------------------------------------
// IldCleanMemory function
// ----------------------------------------------------------------------------
void
IldCleanMemory()
{
    if (Buffers) {
	delete[] Buffers;
	Buffers = 0;
    }
    if (Items) {
	delete[] Items;
	Items = 0;
    }
}

// ----------------------------------------------------------------------------
// IldCleanBuffers function
// ----------------------------------------------------------------------------
void
IldCleanBuffers(int size)
{
    int i;
    for (i = 0 ; i < size ; ++i)
	Items[i]._quote = 0;
    Size = size;
}

// ----------------------------------------------------------------------------
// Memory (re)allocation
// ----------------------------------------------------------------------------
IlBoolean 
IldAllocMemory(int size)
{
    if (Size < size) {
	IldCleanMemory();
	Buffers = new char [size * ILD_FIELD_SIZE];
	Items = (IldItemStruct*)(new char [sizeof(IldItemStruct) * size]);
	if (!Buffers || !Items) {
	    cerr << "--- Out of memory ---" << endl;
	    return IlFalse;
	}
	IldCleanBuffers(size);
    }
    return IlTrue;
}

// ----------------------------------------------------------------------------
// IldFormatLine function
// ----------------------------------------------------------------------------
char*
IldFormatLine(IlInt count,
	      IldItemStruct* items,
	      IlBoolean colSep)
{
    static char buf[4096]; // For very long lines (many columns).
    buf[0] = (colSep) ? PIP : SPC;
    buf[1] = SPC;
    int o  = 2, i = 0;
    for (; i < count ; ++i) {
	int s, e = items[i]._width, p;
	const char* v = items[i]._buffer;
	if (!v)
	    v = DASH;
	int size = 0;
	switch (items[i]._mode) {
	case IldRight:
	    if (items[i]._width > (size = (int)strlen(v))) {
		s = items[i]._width - size;
		for (p = 0 ; p < s ; p++)
		    buf[o++] = SPC;
	    }
	    for (p = 0 ; v[p] && (p < e); ++p)
		buf[o++] = v[p];
	    for (p = 0 ; p < items[i]._space ; ++p)
		buf[o++] = SPC;
	    break;
	case IldCenter:
	    if (items[i]._width > (size = (int)strlen(v))) {
		s = (items[i]._width - size) / 2;
		for (p = 0 ; p < s ; p++)
		    buf[o++] = SPC;
		e = (int)items[i]._width - s;
	    }
	    for (p = 0 ; v[p] && (p < e); ++p)
		buf[o++] = v[p];
	    for (; p < e; p++)
		buf[o++] = SPC;
	    break;
	case IldLeft:
	    if (items[i]._quote) {
		buf[o++] = QTE;
		--e;
	    }
	    for (p = 0 ; v[p] && (p < e); ++p)
		buf[o++] = v[p];
	    if (items[i]._quote) {
		if (p + 1 < e) {
		    buf[o++] = QTE;
		    ++p;
		}
	    }
	    for (; p < e ; p++)
		buf[o++] = SPC;
	    break;
	}
	if (colSep) {
	    int m = items[i]._space / 2;
	    for (p = 0 ; p < m ; ++p)
		buf[o++] = SPC;
	    buf[o++] = VBR;
	    for (; p < items[i]._space ; ++p)
		buf[o++] = SPC;
	} else
	    for (p = 0 ; p < items[i]._space ; ++p)
		buf[o++] = SPC;
    }
    buf[o] = 0;
    return buf;
}

// -----------------------------------------------------------------------
// Demo header display
// -----------------------------------------------------------------------
static const char* DbLHeader = "\t  DB Link ";
void
IldDisplayHeader(const char* title,
		 ostream& ostr)
{
    int len = (int)(strlen(DbLHeader) + strlen(IldVersion()) + 2
		    + strlen(title));
    int i = 0;
    ostr << "\t";
    for (; i < len ; ++i)
	ostr << EQUAL;
    ostr << endl;
    ostr << DbLHeader << IldVersion() << COLN << title << endl;
    ostr << "\t";
    for (i = 0 ; i < len ; i++)
	ostr << EQUAL;
    ostr << endl << endl;
}

// ----------------------------------------------------------------------------
// Error display
// ----------------------------------------------------------------------------
void
IldDisplayError(const char* msg,
		const IldIldBase* ildobj,
		ostream& ostr)
{
    ostr << "Error: " << (msg ? msg : " ") << endl
	 << "   Code    : " << ildobj->getErrorCode() << endl
	 << "   SqlState: " << ildobj->getErrorSqlstate() << endl
	 << "   Message : " << ildobj->getErrorMessage() << endl;
}

// ----------------------------------------------------------------------------
// Warning display
// ----------------------------------------------------------------------------
void
IldDisplayWarning(const char* msg,
		  const IldIldBase* ildobj,
		  ostream& ostr)
{
    ostr << "Warning: " << (msg ? msg : " ") << endl
	 << "   Code    : " << ildobj->getInformationCode() << endl
	 << "   Message : " << ildobj->getInformationMessage() << endl;
}

// ----------------------------------------------------------------------------
// Diagnostics display
// ----------------------------------------------------------------------------
void
IldDisplayDiags(const char* op,
		IldIldBase* ildobj,
		ostream& ostr)
{
    if (ildobj->isInformationRaised())
	IldDisplayWarning(op, ildobj, ostr);
    if (ildobj->isErrorRaised())
	IldDisplayError(op, ildobj, ostr);
    ildobj->clearDiagnostics();
}

// ----------------------------------------------------------------------------
// Table and view printer
// ----------------------------------------------------------------------------
static void
IldPrintRelationHeader(const IldRelation& relation,
		       ostream& ostr = cout,
		       IlBoolean printRelId = IlFalse)
{
    static char col1Title[8] = "Name";
    static char col2Title[8] = "Owner";
    static char col3Title[8] = "Kind";
    static char col4Title[8] = "Id";
    static char tKind[8] = "Table";
    static char vKind[8] = "View";
    static char iKind[8] = "Index";
    IlInt nbCols = printRelId ? 4 : 3;
    Items[0]._width = 20;
    Items[1]._width = 8;
    Items[2]._width = 6;
    Items[3]._width = 8 ;
    Items[0]._mode = Items[1]._mode = Items[2]._mode =
	Items[3]._mode = IldCenter;
    Items[0]._space = Items[1]._space = Items[2]._space =
	Items[3]._space = 10;
  
    Items[0]._buffer = col1Title;
    Items[1]._buffer = col2Title;
    Items[2]._buffer = col3Title;
    Items[3]._buffer = col4Title;
    ostr << IldFormatLine(nbCols, Items, IlFalse) << endl;
  
    char* name = (char*)relation.getName();
    char* owner = (char*)relation.getOwner();
    char* kind;
    IlInt id = relation.getId();
    switch (relation.getEntityType()) {
    case IldTableEntity: 
	kind = tKind;
	break;
    case IldViewEntity: 
	kind = vKind;
	break;
    default:
	kind = iKind;
    }
    int size = (int)strlen(name);
    Items[0]._buffer = &Buffers[0];
    if (size < 8) size = 8;
    memset(Items[0]._buffer, STR, size);
    Items[0]._buffer[size] = 0;
  
    Items[1]._buffer = &Buffers[ILD_FIELD_SIZE];
    size = (owner ? (int)strlen(owner) : 0);
    if (size < 5) size = 5;
    memset(Items[1]._buffer, STR, size);
    Items[1]._buffer[size] = 0;
  
    Items[2]._buffer = &Buffers[2 * ILD_FIELD_SIZE];
    size = (int)strlen(kind);
    if (size < 4) size = 4;
    memset(Items[2]._buffer, STR, size);
    Items[2]._buffer[size] = 0;

    Items[3]._buffer = &Buffers[3 * ILD_FIELD_SIZE];
    sprintf(Items[3]._buffer, "%d", id);
    size = (int)strlen(Items[3]._buffer);
    if (size < 2) size = 2;
    memset(Items[3]._buffer, STR, size);
    Items[3]._buffer[size] = 0;
    ostr << IldFormatLine(nbCols, Items, IlFalse) << endl;
  
    Items[0]._buffer = name;
    Items[1]._buffer = owner;
    Items[2]._buffer = kind;
    sprintf(Items[3]._buffer, "%d", id);
    ostr << IldFormatLine(nbCols, Items, IlFalse) << endl << endl;
}

// ----------------------------------------------------------------------------
// Local : prints formated column headers of a table or view
// ----------------------------------------------------------------------------
static void
IldPrintRelationColumnHeaders (int maxNameSize,
			       ostream& ostr)
{
    static char c1Title[8] = "Column";
    static char c2Title[6] = "Type";
    static char c3Title[6] = "Size";
    static char c4Title[10] = "Nullable?";
    static char underlineTitle[18] = "----------------";
    Items[0]._space = Items[1]._space
	= Items[2]._space = Items[3]._space = 5;
    Items[0]._width = Items[1]._width
	= Items[2]._width = Items[3]._width = 20;
    Items[3]._mode = IldCenter;
  
    Items[0]._width = maxNameSize;
    Items[0]._buffer = c1Title;
    Items[1]._buffer = c2Title;
    Items[2]._buffer = c3Title;
    Items[3]._buffer = c4Title;
    Items[1]._width = Items[2]._width = Items[3]._width = 16;
    ostr << IldFormatLine(4, Items, IlFalse) << endl;
  
    Items[0]._buffer = &Buffers[0];
    memset(Items[0]._buffer, DSH, maxNameSize);
    Items[0]._buffer[maxNameSize] = 0;
    Items[1]._buffer = Items[2]._buffer =
	Items[3]._buffer = underlineTitle;
    ostr << IldFormatLine(4, Items, IlFalse) << endl;
}

// ----------------------------------------------------------------------------
// Local : prepare for printing a SQL type textual description
// ----------------------------------------------------------------------------
static char IldColTypeStr[80];
char*
IldBuildColType(const IldDescriptor* col)
{
    ostrstream ostr(IldColTypeStr, 40);
    switch (col->getSqlType()) {
    case IldSQLChar:
    case IldSQLVarchar:
    case IldSQLBin:
    case IldSQLBitVarying:
	ostr << col->getSqlTypeName() << OPAR << col->getSize() << CPAR;
	break;
    case IldSQLNumeric:
    case IldSQLDecimal:
    case IldSQLMoney:
    case IldSQLInteger:
    case IldSQLFloat:
	ostr << col->getSqlTypeName();
	if (!IldStrICaseCmp(col->getSqlTypeName(), "numeric")
	    || !IldStrICaseCmp(col->getSqlTypeName(), "decimal")
	    || !IldStrICaseCmp(col->getSqlTypeName(), "number")
	    || !IldStrICaseCmp(col->getSqlTypeName(), "money")) {
	    if (col->getPrecision()) {
		ostr << OPAR << col->getPrecision();
		if (col->getScale())
		    ostr << COMM << col->getScale();
		ostr << CPAR;
	    }
	}
	break;
    case IldSQLRef:
	ostr << "REF" << OPAR << col->getSqlTypeName() << CPAR;
	break;
    default:
	if (col->getADTDescriptor() && col->getADTDescriptor()->isNamedType())
	    ostr << col->getSqlTypeName();
	else if (col->getADTDescriptor())
	    ostr << col->getADTDescriptor()->getLitteralTypeName();
	else
	    ostr << col->getSqlTypeName();
	break;
    }
    ostr << ends;
    return IldColTypeStr;
}

// ----------------------------------------------------------------------------
// Local : prints column descriptions for a table or view
// ----------------------------------------------------------------------------
static void
IldPrintRelationColumns (const IldRelation& relation,
			 ostream& ostr = cout)
{
    int i;
    int nbColumns = (int)relation.getCount();
    static char ColumnSizeStr[32];
    static char notNullDisplay[2] = " ", nullDisplay[10] = "not null";
    Items[0]._mode = IldLeft;
    Items[0]._quote = 0;
    Items[1]._mode = IldLeft;
    Items[1]._quote = 0;
    Items[2]._buffer = ColumnSizeStr;
    for (i = 0 ; i < nbColumns ; ++i) {
	ostrstream cstr(ColumnSizeStr, ILD_NAME_SIZE);
	cstr << relation.getColSize((IlUShort) i) << ends;
	Items[0]._buffer = (char*)relation.getColName((IlUShort)i);
	Items[1]._buffer = IldBuildColType(relation.getColumn((IlUShort)i));
	Items[3]._buffer = (relation.isColNullable((IlUShort) i) ?
			    notNullDisplay : nullDisplay);
	ostr << IldFormatLine(4, Items, IlFalse) << endl;
    }
}

// ----------------------------------------------------------------------------
// Local : prints keys and indexes of a relation 
// ----------------------------------------------------------------------------
void 
IldPrintKeys(IldRelation& relation,
	     ostream& ostr,
	     IldAscState* state)
{
    IlUShort i = 0;
    // Primary key
    if (!state || (state &&
		   ((*state == IldAscNone) || (*state == IldAscGetPKey)))) {
	IldKey* pkey = 0;
	do {
	    pkey = relation.getPrimaryKey();
	} while (!state && !((relation.getDbms())->isCompleted()));
	if (state && !((relation.getDbms())->isCompleted()))
	    *state = IldAscGetPKey;
	else {
	    if (state)
		*state = IldAscNone;
	    if (pkey) {
		ostr << "Primary key: " << OPAR;
		for (i = 0 ; i < pkey->getCount() ; ++i) {
		    const IldColumn* col = pkey->getColumn(i);
		    if (i != 0)
			ostr << COMM;
		    ostr << col->getName();
		}
		ostr << CPAR << endl;
	    }
	}
	if (relation.getDbms()->isErrorRaised())
	    IldDisplayDiags("Read primary key failed:", relation.getDbms(),
			    ostr);
    }
    // Foreign keys
    if (!state || (state &&
		   ((*state == IldAscNone) || (*state == IldAscGetFKeys)))) {
	IldFKey** fkeys = 0;
	do {
	    fkeys = relation.getForeignKeys();
	} while (!state && !((relation.getDbms())->isCompleted()));
	if (state && !((relation.getDbms())->isCompleted()))
	    *state = IldAscGetFKeys;
	else {
	    if (state)
		*state = IldAscNone;
	    if (fkeys) {
		ostr << "Foreign keys: ";
		for (i = 0 ; fkeys[i] ; ++i) {
		    IldFKey* fkey = fkeys[i];
		    IlUShort j;
		    if (fkey->getName())
			ostr << fkey->getName();
		    ostr << OPAR;
		    for (j = 0; j < fkey->getCount() ; ++j) {
			const IldColumn* col = fkey->getColumn(j);
			if (j != 0)
			    ostr << COMM;
			ostr << col->getName();
		    }
		    ostr << CPAR << " references " << fkey->getPTable()
			 << OPAR;
		    for (j = 0; j < fkey->getPrimaryColCount() ; ++j) {
			if (j != 0)
			    ostr << COMM;
			ostr << fkey->getPrimaryColumn((IlUShort)j);
		    }
		    ostr << CPAR << flush;
		    if (fkeys[i + 1])
			ostr << SCOL;
		}
		ostr << endl;
	    }
	}
	if (relation.getDbms()->isErrorRaised())
	    IldDisplayDiags("Read foreign keys failed:", relation.getDbms(),
			    ostr);
    }
    // Indexes
    if (!state || (state &&
		   ((*state == IldAscNone) || (*state == IldAscGetIdxs)))) {
	IldTableIndex** idxs = 0;
	do {
	    idxs = relation.getIndexes();
	} while (!state && !relation.getDbms()->isCompleted());
	if (state && !relation.getDbms()->isCompleted())
	    *state = IldAscGetIdxs;
	else {
	    if (state)
		*state = IldAscNone;
	    if (idxs) {
		ostr << "Indexes: ";
		for (i = 0 ; idxs[i] ; ++i) {
		    IldTableIndex* idx = idxs[i];
		    if (idx->getOwner() && relation.getOwner() &&
			strcmp(idx->getOwner(), relation.getOwner()))
			ostr << idx->getOwner() << DOT;
		    ostr << idx->getName() << OPAR;
		    if (idx->isUnique())
			ostr << "unique: ";
		    IlUShort j;
		    for (j = 0; j < idx->getCount() ; ++j) {
			const IldColumn* col = idx->getColumn(j);
			if (j != 0)
			    ostr << COMM;
			ostr << col->getName();
		    }
		    ostr << CPAR << flush;
		}
		ostr << endl;
	    }
	}
	if (relation.getDbms()->isErrorRaised())
	    IldDisplayDiags("Read indexes failed:", relation.getDbms(),
			    ostr);
    }
    // Special Columns
    if (!state ||
	(state && ((*state == IldAscNone) || (*state == IldAscGetSpecCols)))) {
	IldKey* scols = 0;
	do {
	    scols = relation.getSpecialColumns();
	} while (!state && !relation.getDbms()->isCompleted());
	if (state && !relation.getDbms()->isCompleted())
	    *state = IldAscGetSpecCols;
	else {
	    if (state)
		*state = IldAscNone;
	    if (scols) {
		ostr << "Special columns: " << OPAR;
		const IldColumn* col = 0;
		for (i = 0 ; i < scols->getCount() ; ++i) {
		    col = scols->getColumn(i);
		    if (i != 0)
			ostr << COMM;
		    ostr << col->getName();
		}
		ostr << CPAR << endl;    
	    }
	}
	if (relation.getDbms()->isErrorRaised())
	    IldDisplayDiags("Read special columns failed:",
			    relation.getDbms(), ostr);
    }
}

// ----------------------------------------------------------------------------
// Local : prints a table or view description
// ----------------------------------------------------------------------------
void
IldPrintRelation (const IldRelation& relation,
		  ostream& ostr,
		  IldAscState* state,
		  IlBoolean printRelId)
{
    int i;
    if (Size < 4) {
	if (!IldAllocMemory(4))		// Memory exhausted
	    return;
    } else 
	IldCleanBuffers(4);

    if (!state || (state && (*state == IldAscNone)))
	IldPrintRelationHeader(relation, ostr, printRelId);

    // We look for the max name length.
    int nbColumns = (int)relation.getCount();
    int maxNameSize = 11;
    for (i = 0 ; i < nbColumns ; ++i) {
	int nameSize = (int)strlen((char*)relation.getColName((IlUShort) i));
	if (nameSize > maxNameSize)
	    maxNameSize = nameSize;
    }
    if (!state || (state && (*state == IldAscNone)))
	IldPrintRelationColumnHeaders(maxNameSize, ostr);
    if (!state || (state && (*state == IldAscNone)))
	IldPrintRelationColumns(relation, ostr);
    IldPrintKeys((IldRelation&)relation, ostr, state);
    if (!state || (state && (*state == IldAscNone)))
	ostr << endl;
}

// ----------------------------------------------------------------------------
// Local : prints a procedure or function description
// ----------------------------------------------------------------------------
void
IldPrintCallable(const IldCallable* proc,
		 IlBoolean printProcId,
		 ostream& ostr)
{
    IlUShort nArgs = proc->getArgumentsCount(),
	nRes = proc->getResultsCount();
    IldArgument** args = proc->getArguments();
    IlUShort i = 0;
    ostr << (proc->isProcedure() ? "PROCEDURE " : "FUNCTION ")
	 << proc->getName() << OPAR;
    for (i = 0 ; i < nArgs ; ++i) {
	IldArgument* arg = args[i];
	if (i > 0)
	    ostr << COMM;
	ostr << arg->getName() <<
	    (arg->isInOutArgument() ? " IN OUT "
	     : (arg->isInArgument() ? " IN " : " OUT "));
	IldColumnType argSqlType = arg->getType();
	if ((argSqlType == IldCollectionType) ||
	    (argSqlType == IldObjectType)) {
	    const char* typeOwner = arg->getADTDescriptor()->getOwner();
	    if (strcmp(typeOwner, proc->getOwner()))
		ostr << typeOwner << DOT;
	    ostr << arg->getADTDescriptor()->getName();
	} else
	    ostr << (!strncmp(proc->getDbms()->getName(), "oracle", 6)
		     ? arg->getSqlTypeName() : IldBuildColType(arg));
    }
    ostr << CPAR;
    if (nRes) {
	IldDescriptor** res = proc->getResults();
	ostr << " RETURNING ";
	for (i = 0 ; i < nRes ; ++i) {
	    if (i)
		ostr << COMM;
	    IldColumnType argSqlType = res[i]->getType();
	    if ((argSqlType == IldCollectionType) ||
		(argSqlType == IldObjectType)) {
		const char* typeOwner = res[i]->getADTDescriptor()->getOwner();
		if (strcmp(typeOwner, proc->getOwner()))
		    ostr << typeOwner << DOT;
		ostr << res[i]->getADTDescriptor()->getName();
	    } else
		ostr << (!strncmp(proc->getDbms()->getName(), "oracle", 6)
			 ? res[i]->getSqlTypeName()
			 : IldBuildColType(res[i]));
	}
    }
    if (printProcId)
	ostr << " ; PROCEDURE ID = " << proc->getId();
    ostr << endl;
}

// ----------------------------------------------------------------------------
// Schema entities printer
// ----------------------------------------------------------------------------
void
IldPrintEntity (const IldSchemaEntity* ent,
		IlBoolean printId,
		ostream& ostr)
{
    switch (ent->getEntityType()) {
    case IldUnknownEntity:
	ostr << "Internal error: IldUnknownEntity" << endl;
	break;
    case IldTableEntity:
    case IldViewEntity:
	IldPrintRelation(*(IldRelation*)ent, ostr, 0, printId);
	break;
    case IldADTEntity: {
	IldADTDescriptor* adt = (IldADTDescriptor*)ent;
	const IldCallable* const* methods = adt->getMethods();
	IlUShort i = 0;
	ostr << adt->getLitteralTypeName() << endl;
	if (adt->getMethodsCount()) {
	    ostr << adt->getName() << " MEMBER FUNCTIONS :" << endl;
	    for (i = 0 ; i < adt->getMethodsCount() ; ++i) {
		ostr << "\t";
		IldPrintCallable(methods[i], printId, ostr);
	    }
	}
	break;
    }
    case IldCallableEntity: {
	IldCallable* proc = (IldCallable*)ent;
	IldPrintCallable(proc, printId, ostr);
	break;
    }
    case IldSynonymEntity: {
	IldSynonym* syn = (IldSynonym*)ent;
	ostr << "SYNONYM " << syn->getName() << " FOR "
	     << syn->getTargetOwner() << DOT << syn->getTarget();
	if (syn->getLink())
	    ostr << " ; LINK TO : " << syn->getLink();
	if (printId)
	    ostr << " ; SYNONYM ID : " << syn->getId();
	ostr << endl;
	break;
    }
    }
}

// ----------------------------------------------------------------------------
// Prints a date/time/timestamp value from a row in a result set
// ----------------------------------------------------------------------------
char*
IldDateTimeToString(IldDateTime dt)
{
    static char str[32];
    sprintf(str, "%04hd/%02hd/%02hd %02hd:%02hd:%02hd.%03hd",
	    dt.getYear(), dt.getMonth(), dt.getDay(),
	    dt.getHour(), dt.getMinute(), dt.getSecond(), dt.getMSecond());
    return str;
}

// ----------------------------------------------------------------------------
// Print an ADT value from a row of a result set
// ----------------------------------------------------------------------------
void
IldPrintADT(IldADTValue* v,
	    ostream& ostr)
{
    const char* startStruct, * endStruct;
    const char* dbName = v->getDescriptor()->getDbms()->getName();
    if (!strncmp(dbName, "oracle", 6) || !strncmp(dbName, "db2", 3)) {
	startStruct = OPAR;
	endStruct = CPAR;
    } else if (!strncmp(dbName, "informix", 8)) {
	if (v->getDescriptor()->getType() == IldADTObject) {
	    startStruct = OPAR;
	    endStruct = CPAR;
	} else {
	    startStruct = "{";
	    endStruct = "}";
	}
    } else { // Actually cannot happen but make the checker happy
	startStruct = OPAR;
	endStruct = CPAR;
    }
    ostr << v->getTypeName() << startStruct;
    IlUInt slot = 0, count = v->getCount();
    IlBoolean isObj = (IlBoolean)(v->getADTType() == IldADTObject);
    for ( ; slot < count ; ++slot) {
	if (slot)
	    ostr << COMM;
	if (v->isNull(slot))
	    ostr << DASH;
	else {
	    IldColumnType type = isObj ? v->getType(slot) : v->getType(0);
	    switch (type) {
	    case IldByteType:
		ostr << (short)v->getByteValue(slot);
		break;
	    case IldDateType:
		ostr << QUOT << v->getDateValue(slot) << QUOT;
		break;
	    case IldDecfloatType:
	    case IldStringType:
	    case IldLongTextType:
		ostr << QUOT << v->getStringValue(slot) << QUOT;
		break;
	    case IldIntegerType:
		ostr << v->getIntegerValue(slot);
		break;
	    case IldMoneyType:
	    case IldRealType:
		ostr << v->getRealValue(slot);
		break;
	    case IldDateTimeType: {
		IldDateTime dt = v->getDateTimeValue(slot);
		ostr << IldDateTimeToString(dt);
		break;
	    }
	    case IldNumericType: {
		IlNumeric num = v->getNumericValue(slot);
		char buff[IL_MAX_NUM_LEN];
		num.get(buff, IL_MAX_NUM_LEN);
		ostr << buff;
		break;
	    }
	    case IldBinaryType: {
		IldBytes bytes = v->getBytesValue(slot);
		ostr << "Ox(" << bytes._size << CPAR;
		break;
	    }
	    case IldObjectType:
	    case IldCollectionType:
		IldPrintADT(v->getADTValue(slot), ostr);
		break;
	    case IldRefType: {
		IldBytes ref = v->getRefValue(slot);
		ostr.write((const char*)ref._value, (int)ref._size);
		break;
	    }
	    case IldBLOBType:
		ostr << "BLOB locator";
		break;
	    case IldCLOBType:
		ostr << "CLOB locator";
		break;
	    case IldCursorType:
		ostr << "cursor";
		break;
	    case IldUnknownType:
		ostr << "Internal error: unknown type";
	    }
	}
    }
    ostr << endStruct;
}

// ----------------------------------------------------------------------------
// Prints values of a row from a result set
// ----------------------------------------------------------------------------
void
IldPrintColumn(IldRequest* request,
	       int i)
{
    Items[i]._buffer = &Buffers[i * ILD_FIELD_SIZE];
    ostrstream ostr(Items[i]._buffer, (int)ILD_FIELD_SIZE);
    // Selection of the data accessor.
    if (request->isColNull((IlUShort) i))
	ostr << DASH;
    else {
	Items[i]._mode = IldLeft;
	IldColumnType colType = request->getColType((IlUShort)i);
	switch (colType) {
	case IldMoneyType:
	    Items[i]._mode = IldCenter;
	    ostr << '$' << request->getColMoneyValue((IlUShort)i);
	    break;
	case IldByteType:
	    ostr << (short)request->getColByteValue((IlUShort)i);
	    break;
	case IldBinaryType :
	    ostr << "...(" << request->getColBinaryValue((IlUShort)i)._size
		 << CPAR;
	    break;
	case IldLongTextType: {
	    char* value = (char*)request->getColLongTextValue((IlUShort)i);
	    if (!request->isErrorRaised()) {
		Items[i]._quote = 1;
		Items[i]._mode = IldLeft;
		int j = 0 ;
		IldStrRTrim(value, ILD_LONG_SIZE);
		while (value[j]) ostr << value[j++];
	    }
	    break;
	}
	case IldNumericType: {
	    IlNumeric num = request->getColNumericValue((IlUShort)i);
	    static char numStr[IL_MAX_NUM_LEN];
	    memset(numStr, 0, IL_MAX_NUM_LEN);
	    num.get(numStr, IL_MAX_NUM_LEN);
	    ostr << numStr;
	    break;
	}
	case IldIntegerType:
	    Items[i]._mode = IldCenter;
	    ostr << request->getColIntegerValue((IlUShort)i);
	    break;
	case IldRealType:
	    Items[i]._mode = IldCenter;
	    ostr << request->getColRealValue((IlUShort)i);
	    break;
	case IldDecfloatType: {
	    Items[i]._quote = 1;
	    int j = 0 ;
	    while (request->getColStringValue((IlUShort)i)[j])
		ostr << request->getColStringValue((IlUShort)i)[j++];
	    break;
	}
	case IldStringType: {
	    Items[i]._quote = 1;
	    ostr << request->getColStringValue((IlUShort)i);
	    break;
	}
	case IldDateType:
	    ostr << IldStrRTrim((char*)request->getColDateValue((IlUShort)i));
	    break;
	case IldDateTimeType:
	    ostr << IldDateTimeToString(request
					->getColDateTimeValue((IlUShort)i));
	    break;
	case IldObjectType:
	case IldCollectionType: {
	    IldADTValue* value = request->getColADTValue((IlUShort)i);
	    if (!request->isErrorRaised()) {
		IldPrintADT(value, ostr);
		delete value;
	    }
	    break;
	}
	case IldRefType: {
	    IldBytes ref = request->getColRefValue((IlUShort)i);
	    if (!request->isErrorRaised()) {
		ostr.write((const char*)ref._value, (int)ref._size);
		delete [] ref._value;
	    }
	    break;
	}
	case IldBLOBType:
	    ostr << "BLOB locator";
	    break;
	case IldCLOBType:
	    ostr << "CLOB Locator";
	    break;
	case IldCursorType:
	    ostr << "cursor";
	    break;
	case IldUnknownType:
	    ostr << "Internal error: unknown type" ;
	    break;
	} 
    }
    ostr << ends;
}

// ----------------------------------------------------------------------------
// Prints a row from a result set
// ----------------------------------------------------------------------------
void
IldPrintTuple(IldRequest* request,
	      IldPrintMode mode,
	      ostream& ostr)
{
    int count = (int)request->getColCount();
    int i;
    if (Size < count) {
	if (!IldAllocMemory(count))
	    return;				// Memory exhausted
    } else
	IldCleanBuffers(count);
    int colSize = 0, nameSize = 0;
    IldColumnType type;
    for (i = 0 ; i < count ; ++i) {
	// Always recompute all this for asynchronous processing.
	type = request->getColType((IlUShort)i);
	colSize = (int)request->getColSize((IlUShort)i);
	nameSize = (int)strlen(request->getColName((IlUShort)i));
	if (nameSize > colSize)
	    colSize = nameSize;
	if ((type == IldStringType) || (type == IldLongTextType))
	    colSize += 4;
	else if (type == IldIntegerType)
	    colSize = 10;
	else if ((type == IldObjectType)
		 || (type == IldCollectionType))
	    colSize = 60;
	Items[i]._width =
	    (colSize < ILD_FIELD_SIZE) ? colSize : ILD_FIELD_SIZE - 1;
	Items[i]._space = 2;
	Items[i]._mode = IldCenter;
    
	switch (mode) {
	case IldNames:
	    Items[i]._buffer = (char*)request->getColName((IlUShort)i);
	    break;
	case IldSeparators:
	    Items[i]._buffer = &Buffers[i * ILD_FIELD_SIZE];
	    memset(Items[i]._buffer, DSH, Items[i]._width);
	    Items[i]._buffer[Items[i]._width] = 0;
	    break;
	default:
	    IldPrintColumn(request, i);
	}
	if (request->isErrorRaised())
	    break;
    }
    if (!request->isErrorRaised())
	ostr << IldFormatLine(count, Items, IlTrue) << endl;
}

// ----------------------------------------------------------------------
// If connected via Odbc, returns the actual RDBMS connected to.
// ----------------------------------------------------------------------
char*
IldGetOdbcDbms(IldDbms* dbms)
{
    // If Odbc, get DBMS connected to via Odbc.
    char *dbOdbc = new char [256];
    IlInt notUsed = 0;
    if (!strcmp(dbms->getName(), "odbc")
	|| !strcmp(dbms->getName(), "oledb")) {
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
    const char* typeName = 0;
    char* dbOdbc = IldGetOdbcDbms(dbms);
    if (!strncmp(dbmsName, "oracle", 6)
	|| !IldStrNICaseCmp(dbOdbc, "oracle", 6))
	typeName = "DATE";
    else if (!strncmp(dbmsName, "db2", 3))
	typeName = "TIMESTAMP";
    else if (!strncmp(dbmsName, "informix", 8)
	     || !IldStrNICaseCmp(dbOdbc, "informix", 8))
	// can be set to "date" as well
	typeName = "datetime year to fraction(3)"; 
    else if (!strcmp(dbmsName, "sybase")
	     || !IldStrNICaseCmp(dbOdbc, "SQL Server", 10)
	     || !strcmp(dbmsName, "mysql")
	     || !IldStrNICaseCmp(dbOdbc, "Microsoft SQL Server", 20))
	typeName = "DATETIME";
    else if (!strcmp(dbmsName, "odbc"))
	typeName = "DATE";
    delete [] dbOdbc;
    return typeName;
}

// -----------------------------------------------------------------------
// Find out RDBMS name for NUMERIC column type
// -----------------------------------------------------------------------
const char* 
IldGetNumericTypeName(IldDbms* dbms)
{
    const char* dbmsName = dbms->getName();
    const char* typeName = 0;
    char *dbOdbc = IldGetOdbcDbms(dbms);
    if (!strncmp(dbmsName, "oracle", 6)
	|| !IldStrNICaseCmp(dbOdbc, "oracle", 6)
	|| !strncmp(dbmsName, "informix", 8)
	|| !IldStrNICaseCmp(dbOdbc, "informix", 8)
	|| !strcmp(dbmsName, "sybase")
	|| !IldStrNICaseCmp(dbOdbc, "SQL Server", 10)
	|| !strcmp(dbmsName, "mysql"))
	typeName = "NUMERIC(32, 9)";
    else if (!strncmp(dbmsName, "db2", 3))
	typeName = "NUMERIC(31, 9)";
    else if (!strcmp(dbmsName, "mssql")
	     || !IldStrNICaseCmp(dbOdbc, "Microsoft SQL Server", 20))
	typeName = "NUMERIC(28, 9)";
    else if (!strcmp(dbmsName, "odbc"))
	typeName = "NUMERIC";
    delete [] dbOdbc;
    return typeName;
}

// -----------------------------------------------------------------------
// Find out RDBMS native SQL type name
// -----------------------------------------------------------------------
const char*
IldGetTypeName(IldDbms* dbms,
	       short type)
{
    const char* name = 0;
    const IldSQLType** types = dbms->getTypeInfo(type);
    if (dbms->isErrorRaised())
	IldDisplayDiags("Could not get Types Info.", dbms);
    else if (!types)
	cout << "No database type for type : " << type << " !!!" << endl;
    else if (types[0]) {
	name = types[0]->getName();
	if ((type == IldSQLLongBin) && types[1])
	    // Double-byte strings are also handled as binaries by DBLink since
	    // we have no specific type for them ==> we check the delimitor
	    // to make sure we really got the binary type.
	    if (types[0]->getPrefix())
		// No delimitor for binary values ==> use the second type
		name = types[1]->getName();
	// Get rid of the array, the pointed to name is valid until dbms 
	// is deleted
	dbms->freeTypeInfo(types);
    }
    return name;
}

// ----------------------------------------------------------------------------
// Get the RDBMS name for long binary
// ----------------------------------------------------------------------------
const char*
IldGetLongBinaryTypeName(IldDbms* dbms)
{
    return IldGetTypeName(dbms, IldSQLLongBin);
}

// ----------------------------------------------------------------------------
// Syntactic sugar
// ----------------------------------------------------------------------------
const char*
IldGetLongTextTypeName(IldDbms* dbms)
{
    return IldGetTypeName(dbms, IldSQLText);
}

const char*
IldGetBLobTypeName(IldDbms* dbms)
{
    return IldGetTypeName(dbms, IldSQLBLOB);
}

const char*
IldGetCLobTypeName(IldDbms* dbms)
{
    return IldGetTypeName(dbms, IldSQLCLOB);
}

// ------------------------------------------------------------------------
// Retrieve a line ended by '\n' from an input stream.
// ------------------------------------------------------------------------
char*
getLine(char* buffer,
	IlInt size,
	istream& istr)
{
    buffer[0] = buffer[1] = 0;
    istr.getline(buffer, size, '\n');
    return buffer;
}

// ------------------------------------------------------------------------
// Drop the table and exit the app
// ------------------------------------------------------------------------
void
IldEndSample(IldDbms* dbms,
	     IldRequest* request,
	     const char* dropStr,
	     const char* endMsg,
	     int status)
{
    if (dbms && dbms->isErrorRaised())
	IldDisplayDiags(endMsg, dbms);
    else if (request && request->isErrorRaised())
	IldDisplayDiags(endMsg, request);
    else if (endMsg)
	cout << endMsg << endl;
    if (request)
	// Make sure any operation in progress is given up.
	if (!request->closeCursor())
	    IldDisplayDiags("Cannot close cursor: ", request);
    if (dbms) {
	if (dropStr)
	    if (!dbms->execute(dropStr))
		IldDisplayDiags("Drop failed: ", dbms);
	IldCleanMemory(); // In case print Tuple was used
	delete dbms;
    }
    // Using Unix convention: 0 (default) means program ran OK
    exit(status);
}

// ----------------------------------------------------------------------------
// Display results from commands.
// ----------------------------------------------------------------------------
IlInt
IldPrintResults(IldRequest* r,
		ostream& ostr)
{
    IlInt res = 1 ;
    if (r->fetch().hasTuple()) {
	IldPrintTuple(r, IldNames, ostr);
	IldPrintTuple(r, IldSeparators, ostr);
	do {
	    if (r->isInformationRaised())
		ostr << "Warning: " << r->getInformationMessage() << endl;
	    IldPrintTuple(r, IldTupleData, ostr);
	} while (r->fetch().hasTuple());
	if (r->isErrorRaised()) {
	    IldDisplayDiags("Fetch failed : ", r, ostr);
	    res = 0;
	}
    } else if (r->isErrorRaised()) 
	IldDisplayDiags("Fetch failed: ", r, ostr);
    else {
	IlInt count = r->getStatus();
	if (count)
	    ostr << count << " modified row"
		 << (count > 1 ? "s." : DOT) << endl;
	else
	    ostr << "No modified row." << endl;
    }
    return res;
}

// ----------------------------------------------------------------------------
// Run Time Measurement
// ----------------------------------------------------------------------------

// Windows requirements
// --------------------
#if defined(WINDOWS)
#if defined(IL_STD)
#include <ctime>
#else  /* !IL_STD */
#include <time.h>
#endif /* IL_STD */

IlDouble
IlRunTime()
{
    clock_t c = clock();
    return c/(IlDouble)(CLK_TCK);
}
#endif /* WINDOWS */

// IBM-RS6000 compiler requirements
// --------------------------------
#if defined(_AIX)
#if defined(IL_STD)
#include <ctime>
IL_STDUSE
#else  /* !IL_STD */
#include <time.h>
#endif /* IL_STD */
#include <sys/param.h>
#include <sys/times.h>
#if !defined(TIMEUNIT)
#  define TIMEUNIT HZ
#endif /* !TIMEUNIT */
#endif /* _AIX */

#if defined(__hpux) || defined(__SVR4)
// HP-UX & Solaris requirements
#if defined(IL_STD)
#include <ctime>
IL_STDUSE
#else  /* !IL_STD */
#include <time.h>
#endif /* ILV_TD */
#include <sys/param.h>
#include <sys/times.h>
#if !defined(TIMEUNIT)
#  define TIMEUNIT HZ
#endif /* TIMEUNIT */
#endif /* __hpux || __SVR4 */
#if defined(_AIX) || (defined(__SVR4) && !defined(sun)) || defined(__hpux)
IlDouble
IlRunTime()
{
    struct tms timebuffer;
    times(&timebuffer);
    return (timebuffer.tms_utime / (IlDouble)TIMEUNIT);
}
#endif /* _AIX || (__SVR4 && !sun) */

// Solaris requirement
// -------------------
#if defined(__SVR4) && defined(sun)
extern "C" long _sysconf(int);
#if defined(IL_STD)
#include <climits>
#else  /* !IL_STD */
#include <limits.h>
#endif /* IL_STD */

IlDouble
IlRunTime()
{
    struct tms timebuffer;
    times(&timebuffer);
    return (timebuffer.tms_utime / (IlDouble)CLK_TCK);
}
#endif /* __SVR4 && sun */

// __alpha && linux requirements
// -----------------------------
#if defined(linux)
#include <sys/times.h>
#include <unistd.h>

IlDouble
IlRunTime()
{
    struct tms buffer;
    times(&buffer);
    return (buffer.tms_utime / (IlDouble)sysconf(_SC_CLK_TCK));
}
#endif /* linux */
