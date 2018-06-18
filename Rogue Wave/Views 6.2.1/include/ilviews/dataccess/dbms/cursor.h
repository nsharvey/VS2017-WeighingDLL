// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbms/cursor.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliSQLCursor class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Cursor_H
#define __Ili_Cursor_H

#if !defined(__Ili_Common_H)
#  include <ilviews/dataccess/common.h>
#endif
#if !defined(__Ili_Value_H)
#  include <ilviews/dataccess/value.h>
#endif
#if !defined(__Ili_Schema_H)
#  include <ilviews/dataccess/schema.h>
#endif
#if !defined(__Ili_Param_H)
#  include <ilviews/dataccess/param.h>
#endif
#if !defined(__Ili_Error_H)
#  include <ilviews/dataccess/error.h>
#endif
#if !defined(__Ili_Tblref_H)
#  include <ilviews/dataccess/tblref.h>
#endif

class ILV_DBI_EXPORTED IliSQLSession;
class ILV_DBI_EXPORTED IliDbmsDriver;

class ILV_DBI_EXPORTED IliSQLCursor
: public IliCollectable, public IliRefCounted
{
public:
    inline IliSQLSession& getSQLSession() const
	{ return *_session; }


    // -- Execute

    IlBoolean execute(const char* stmt, IlInt* pRowCount = 0);
    IlBoolean select(const char* stmt);
    IlBoolean close();

    // -- Parse and execute

    IlBoolean parse(const char* stmt, IlBoolean useBoundVars = IlTrue);
    const char* getParsedStatement() const;
    IlInt defineParam(const char* paramName, const IliDatatype* type);
    IlInt getParamIndex(const char* paramName) const;
    IlBoolean setParam(IlInt paramno, const IliValue& val);
    IlBoolean getParam(IlInt, IliValue&) const;
    IlBoolean getOutputParam(IlInt paramno, IliValue& val) const;
    IlBoolean execute(IlInt* pRowCount = 0);
    IlBoolean select();

    IlBoolean bindColumn(IlInt, const IliDatatype*, IlInt = -1);

    IlBoolean writeLongString(const char*, IlUInt,
			      const IliSQLTableRef&,
			      const char*, const char*);
    IlBoolean writeLongBinary(const IliBinary&, const IliSQLTableRef&,
			      const char*, const char*);

    // -- Result set

    const IliSchema* getSchema() const;
    IlBoolean fetchNext();
    IlBoolean hasTuple() const;
    IlInt getBufferedRowsCount() const;
    IlBoolean setBufferedRowsCount(IlInt count);

    // Values
    IlBoolean isNull(IlInt colno) const;
    IlBoolean getValue(IlInt colno, IliValue& val);
    const char* getStringValue(IlInt colno) const;
    IlInt getIntegerValue(IlInt colno) const;
    IlFloat getFloatValue(IlInt colno) const;
    IlDouble getDoubleValue(IlInt colno) const;
    IliDate getDateValue(IlInt colno) const;
    IliTime getTimeValue(IlInt colno) const;
    IliBinary getBinaryValue(IlInt colno) const;

    // Async Mode
    IlBoolean isAsyncCallCompleted();

    // Error reporting
    inline IlBoolean isErrorRaised() const { return errorRaised(); }


    IlBoolean errorRaised() const;
    IliErrorMessage getErrorMessage() const;

    // Other
    IlvValueInterface* getItf() const;

protected:
    friend class IliSQLSession;

    enum State {
	DefaultState,
	ExecuteState,
	NormalizeState
    };

    IlAny _cno;
    IliSQLSession* _session;
    State _state;
    IliSchema *_schema;
    IliString _stmt;
    IliString _cookedStatement;
    IlBoolean _useCookedStatement;
    IlBoolean _schemaIsValid;
    IlBoolean _parsed;
    IlBoolean _dbmsParsed;
    IlBoolean _needsDbmsParse;
    IlBoolean _paramsDefined;
    IlBoolean _hasIndexedParams;
    IliParameterCollection _params;
    IliParameterCollection _orderedParams;
    IliParameterCollection _indexedParams;
    IliValue* _buffer;
    IlInt _bufferSize;
    IlInt _bufferedRowCount;
    IliErrorMessage _lastErrorMessage;
    IlvValueInterface* _itf;

    inline State getState() const { return _state; }
    inline void setState(State state) { _state = state; }

    void reset();
    void clearError() const;
    void unparse();
    IlBoolean i_execute(const char*, IlInt*);
    IlBoolean i_select(const char*);
    IlBoolean executeParsed(IlInt*);
    IlBoolean checkBindCompat() const;
    void prepareIndexedVars(const char*, IliString&);
    IlBoolean normalize(IliString&, IlBoolean);
    void reallocBuffer(IlInt);
    void clearBuffer();
    IlBoolean cacheValue(IlInt) const;
    IlInt getColumnsCount() const;
    IlBoolean callStartTransaction();
    IlBoolean adjustBufferedRowCount();
    IlBoolean postAsyncCall(State = ExecuteState);

    IliSQLCursor(IliSQLSession*, IlAny);
    inline IliSQLCursor(const IliSQLCursor&) {}
    inline IliSQLCursor& operator=(const IliSQLCursor&) { return *this; }
    ~IliSQLCursor();

    IliDbmsDriver& getDriver() const;
};

IliDeclareCollection(DBI, IliSQLCursorCollection, IliSQLCursor);

#if !defined(__Ili_Sqlcuitf_H)
#  include <ilviews/dataccess/intrface/sqlcuitf.h>
#endif

#endif /* !__Ili_Cursor_H */
