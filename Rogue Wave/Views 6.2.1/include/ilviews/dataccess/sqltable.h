// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/sqltable.h
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
// Declaration of the IliSQLTable class
// Defined in library dbaccess
// --------------------------------------------------------------------------
#ifndef __Ili_Sqltable_H
#define __Ili_Sqltable_H

#if !defined(__Ili_Memtable_H)
#  include <ilviews/dataccess/memtable.h>
#endif
#if !defined(__Ili_Session_H)
#  include <ilviews/dataccess/dbms/session.h>
#endif
#if !defined(__Ili_Tblref_H)
#  include <ilviews/dataccess/tblref.h>
#endif
#if !defined(__Ili_Intset_H)
#  include <ilviews/dataccess/intset.h>
#endif
#if !defined(__Ili_Tbldef_H)
#  include <ilviews/dataccess/tbldef.h>
#endif

class IliSQLOuterJoinDesc;

// --------------------------------------------------------------------------
enum IliSQLOperation {
    IliSQLScalar,
    IliSQLGroupBy,
    IliSQLCount,
    IliSQLSum,
    IliSQLAvg,
    IliSQLMin,
    IliSQLMax
};

// --------------------------------------------------------------------------
enum IliSQLJoinType {
    IliInnerJoin,
    IliLeftOuterJoin,
    IliRightOuterJoin,
    IliJoinTypeCount
};

#include <ilviews/dataccess/sqltblex.h>

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLTable
: public IliMemoryTable
{
public:
    enum CursorTag {
	NoCursor     = -1,
	SelectCursor,
	FetchCursor,
	InsertCursor,
	UpdateCursor,
	DeleteCursor,
	CursorCount
    };

    IliSQLTable(IlvDisplay* display);
    IliSQLTable(const IliSQLTable&);
    IliSQLTable(IlvDisplay*, IL_STDPREF istream& input);

    IliDeclareDTypeInfo(IliSQLTable);
    virtual void write(IL_STDPREF ostream& output) const;
    int operator==(const IliSQLTable&) const;

    IliSQLTable& operator=(const IliSQLTable&);
    void copyStructure(const IliSQLTable&, IlBoolean keepRows);

    IliSQLTablePtr getSQLTablePtr() const;
    IliSQLTablePtr getSQLTablePtr();
    IliTable* getCache() const;
    void setCache(IliTable* cache);
    IliSQLSession* getSQLSession() const;
    void setSQLSession(IliSQLSession* session);
    IliSQLSession* getEffectiveSQLSession() const;

    IlBoolean isCursorKept(CursorTag tag) const;
    void keepCursor(CursorTag tag, IlBoolean flag);
    IlInt getCursorBufferedRowsCount() const;
    void setCursorBufferedRowsCount(IlInt count);
    IlBoolean makeQuery();
    const char* getQuery() const;
    void setQuery(const char* query);
    IlBoolean setQueryFrom(const IliSQLTableRef& tblRef);
    const char* getQueryConjunct() const;
    void setQueryConjunct(const char* condition);
    inline IlBoolean getConcurrencyControl() const { return !!_cc; }
    void setConcurrencyControl(IlBoolean cc);
    IliFetchPolicy getFetchPolicy() const;
    void setFetchPolicy(IliFetchPolicy fp);
    inline IlBoolean getAutoCommit() const { return !!_autoCommit; }
    void setAutoCommit(IlBoolean f);
    inline IlBoolean getAutoRefresh() const { return !!_autoRefresh; }

    void setAutoRefresh(IlBoolean f);
    inline IlBoolean isInsertingNulls() const { return !!_insertNulls; }
    void insertNulls(IlBoolean f);
    inline IlBoolean isUsingDynamicSQL() const { return !!_dynamicSQL; }
    void useDynamicSQL(IlBoolean f);
    inline IlBoolean isUsingBoundVariables() const
	{ return !!_useBoundVars; }
    void useBoundVariables(IlBoolean f);
    inline IlBoolean isDistinct() const { return !!_distinct; }
    void setDistinct(IlBoolean f);
    IlInt getRowsCountLimit() const;
    void setRowsCountLimit(IlInt size);

    IlBoolean areColumnNamesComputed() const;
    void computeColumnNames(IlBoolean);

    void computeColumnNamesOnce();

    // Tables

    IlInt getTablesCount() const;
    IlInt addTable(const IliSQLTableRef& tblRef);
    IlBoolean removeTable(IlInt tblno);
    const IliSQLTableRef& getTableRef(IlInt tblno) const;
    void setTableRef(IlInt tblno, const IliSQLTableRef& tblRef);
    const char* getTableAlias(IlInt tblno) const;
    IlInt getTableIndex(const char* alias) const;
    IlInt getTableIndex(const IliSQLTableRef&) const;
    IlInt getTableIndex(IlInt token) const;
    IlInt getTableToken(IlInt tblno) const;
    IlvRect getTableRect(IlInt tblno) const;
    void setTableRect(IlInt tblno, const IlvRect& rect);

    IlBoolean hasUpdatableTables() const;
    IlBoolean isTableUpdatable(IlInt tblno) const;
    void setTableUpdatable(IlInt tblno, IlBoolean flag);

    // Table parent
    const char* getTableParentDataSourceName(IlInt tblno) const;
    void setTableParentDataSourceName(IlInt tblno, const char* name);
    IliSQLTable* getTableParentSQLTable(IlInt tblno) const;
    void setTableParentSQLTable(IlInt tblno, IliSQLTable* sqlTbl);
    const char* getTableParentTableAlias(IlInt tblno) const;
    void setTableParentTableAlias(IlInt tblno, const char* name);
    IlInt getTableParentTableIndex(IlInt tblno) const;
    IliAttributePath getTableParentPath(IlInt tblno) const;
    void setTableParentPath(IlInt tblno, const IliAttributePath& path);
    IliRowPtr getTableParentRow(IlInt tblno) const;
    void setTableParentRow(IlInt tblno, const IliRowPtr& row);

    IliSQLTable* getEffectiveTableParentSQLTable(IlInt tblno) const;
    IliRowPtr getEffectiveTableParentRow(IlInt tblno) const;

    // Catalog
    const IliSQLCatalog& getCatalog() const { return _catalog; }
    IliSQLCatalog& getCatalog() { return _catalog; }

    // Joins
    IlInt getJoinsCount() const;
    IlInt getJoinIndex(IlInt token) const;
    IlInt getJoinToken(IlInt jno) const;
    IlBoolean getJoin(IlInt jno, IlInt& tblNo1, IliAttributePath& colName1,
		      IlInt& tblNo2, IliAttributePath& colName2) const;
    IliSQLJoinType getJoinType(IlInt jno) const;
    IlInt findJoin(IlInt tblNo1, const IliAttributePath& colName1,
		   IlInt tblNo2, const IliAttributePath& colName2) const;
    IlInt addJoin(IlInt tblNo1, const IliAttributePath& colName1,
		  IlInt tblNo2, const IliAttributePath& colName2);
    IlInt addJoin(IlInt tblNo1, const char* colName1,
		  IlInt tblNo2, const char* colName2);
    void setJoinType(IlInt jno, IliSQLJoinType type);
    void deleteJoin(IlInt jno);
    void deleteAllJoins();

    // Where and having clause
    IlInt getConjunctsCount(IlBoolean wherePart) const;
    void insertConjunct(IlInt cno, IlBoolean wherePart);
    void deleteConjunct(IlInt cno, IlBoolean wherePart);
    void deleteAllConjuncts(IlBoolean wherePart);
    const char* getColumnPredicat(IlInt colno, IlInt cno,
				  IlBoolean wherePart) const;
    void setColumnPredicat(IlInt colno, IlInt cno,
			   const char* predicat, IlBoolean wherePart);

    // Columns
    IlInt addTableColumn(const IliSQLTableDef* tblDef,
			 IlInt tblno, IlInt colno);

    IlBoolean isColumnNameFixed(IlInt) const;
    void fixColumnName(IlInt, IlBoolean);
    const char* getColumnSQLText(IlInt colno) const;
    virtual void setColumnSQLText(IlInt colno, const char* text);
    IliSQLOrderByType getColumnOrderBy(IlInt colno) const;
    virtual void setColumnOrderBy(IlInt colno, IliSQLOrderByType order);
    IliSQLOperation getColumnOperation(IlInt colno) const;
    virtual void setColumnOperation(IlInt colno, IliSQLOperation op);
    IlBoolean isColumnFetched(IlInt colno) const;
    virtual void setColumnFetched(IlInt colno, IlBoolean f);
    IlInt getColumnTable(IlInt colno) const;
    virtual void setColumnTable(IlInt colno, IlInt tblno);
    IlInt getColumnDesignWidth(IlInt colno) const;
    void setColumnDesignWidth(IlInt colno, IlInt width);

    virtual IlBoolean allowColumnMove() const;

    // Values
    IlBoolean isInAsyncMode() const;
    IlBoolean isAsyncCallCompleted() const;
    IlBoolean cancelAsyncCall();
    CursorTag getAsyncCursorTag() const;
    IlBoolean continueAsyncCall();

    virtual void clearRows();
    virtual IlBoolean select();
    virtual IlBoolean isSelectDone() const;

    IlBoolean selectAndReadSchema();

    virtual IlInt getRowsCount() const;
    virtual IlBoolean fetchCompleted() const;
    virtual IlInt fetchNext(IlInt = 1);
    virtual IlInt fetchAll();

    virtual IlBoolean getValue(IlInt, IlInt, IliValue&) const;

    virtual IlBoolean insertRow(IlInt, IliTableBuffer*);
    virtual IlBoolean updateRow(IlInt, IliTableBuffer*);
    virtual IlBoolean deleteRow(IlInt);
    virtual IlBoolean moveRow(IlInt, IlInt);
    virtual IlBoolean exchangeRows(IlInt, IlInt);

    virtual IlBoolean refreshRow(IlInt rowno);
    virtual IlBoolean refreshAndLockRow(IlInt rowno);
    IlBoolean isNoWaitOnLockRowEnabled() const;
    IlBoolean isNoWaitOnLockRowSupported() const;
    void enableNoWaitOnLockRow(IlBoolean nowait);

    // Query mode
    virtual IlBoolean isQueryModeSupported() const;
    virtual IliTable* makeQueryTable() const;
    virtual IlBoolean applyQueryMode(IliTable*);

    void deleteEverything(IlBoolean = IlTrue);
    void appendSQLSchema(const IliSQLTableRef&, const IliSchema&);

    void normalizeConjunct(IlBoolean);

    void separateNonFetchedColumns();
    void mergeNonFetchedColumns();

    void removeAnonymousColumns();

    void makeAugmentedQuery(IliString&) const;
    void makeAugmentedQuery(const char*, IliString&) const;

    // Internal
    void onSessionEvent(IliSQLSession*, IliSQLSessionEvent);

    virtual IlBoolean checkRowConstraints(IlInt, IliTableBuffer*) const;

    IlBoolean emitTableExpr(IliSQLStmtBuf&, IlInt) const;

    class StmtProducer
    {
    public:
	StmtProducer() {}
	virtual ~StmtProducer();
	virtual void produce(IliSQLStmtBuf&) = 0;
    };

protected:
    enum State {
	DefaultState,
	ParseState,
	SelectState,
	FetchState
    };

    IliTableBuffer* _fetchBuffer;
    IliTableBuffer* _rowBuffer;
    IliTableBuffer* _xchgBuffer;
    IliColumnCollection _nonFetchedColumns;
    IliString _query;
    IliString _queryConjunct;
    IliString _cookedQuery;
    IlInt _rowsCountLimit;
    IlBoolean _areNamesComputed;
    IlBoolean _dynamicSQL;
    IlBoolean _useBoundVars;
    IlBoolean _insertNulls;
    IlBoolean _autoCommit;
    IlBoolean _autoRefresh;
    IlBoolean _cc;
    IlBoolean _fetchCompleted;
    IlBoolean _distinct;
    IlBoolean _selectDone;
    IlBoolean _dontClearRows;
    IlBoolean _queryMadeByUs;
    IlBoolean _busy;
    IlBoolean _noWaitOnLockRowEnabled;
    IliString _queryMadeFor;
    IlInt _nextTableToken;
    IlInt _nextJoinToken;
    IliFetchPolicy _fetchPolicy;
    IliFromClause _fromClause;
    IliSQLQueryJoinCollection _joins;
    IliSQLCondition _where;
    IliSQLCondition _having;
    IliSQLCatalog _catalog;
    IlInt _bufferedRowsCount;
    State _state;
    CursorTag _asyncCursorTag;
    int _cursorKeptMask;

    IliSQLStmtBuf _insertStmt;
    IliSQLStmtBuf _fetchStmt;
    IliSQLStmtBuf _updateStmt;
    IliSQLStmtBuf _deleteStmt;

    IliSQLCursor* _cursors[CursorCount];
    IliSQLSession* _session;
    IliSQLSession* _effectiveSession;

    virtual ~IliSQLTable();

    inline IlBoolean isBusy() const { return !!_busy; }
    inline IlBoolean setBusy(IlBoolean f)
	{
	    IlBoolean p = !!_busy;
	    _busy = !!f;
	    return p;
	}

    inline State getState() const { return _state; }
    inline void setState(State state) { _state = state; }

    virtual IlvValueInterface* makeItf() const;
    virtual IlvValueInterface* makeColumnItf(IlInt) const;

    inline IlBoolean isQueryMadeByUs() const { return _queryMadeByUs; }
    inline void setQueryMadeByUs(IlBoolean f) { _queryMadeByUs = !!f; }

    inline void setColumnNamesComputed(IlBoolean f)
	{ _areNamesComputed = !!f; }

    inline IlBoolean dontClearRows() const { return  _dontClearRows; }
    inline void dontClearRows(IlBoolean f) { _dontClearRows = !!f; }

    inline void setFetchCompleted(IlBoolean f) { _fetchCompleted = !!f; }

    inline void setSelectDone(IlBoolean f) { _selectDone = !!f; }

    inline IlBoolean inBounds(CursorTag tag) const
	{ return (tag > NoCursor && tag < CursorCount); }

    virtual IlBoolean checkCanInsertRow();
    virtual IlBoolean checkCanUpdateRow(IlInt);
    virtual IlBoolean checkCanDeleteRow(IlInt);

    virtual IlBoolean acceptUpdateRow(IlInt, IliTableBuffer*,
				      IliTableBuffer*);
    virtual IlBoolean acceptInsertRow(IlInt, IliTableBuffer*);
    virtual IlBoolean acceptDeleteRow(IlInt, IliTableBuffer*);
    virtual IlBoolean acceptMoveRow(IlInt, IlInt);
    virtual IlBoolean acceptExchangeRows(IlInt, IlInt);

    virtual IlBoolean dbmsUpdateRow(IliTableBuffer*,
				    IliTableBuffer*&, IlBoolean, IlInt);
    virtual IlBoolean dbmsInsertRow(IliTableBuffer*&, IlBoolean, IlInt);
    virtual IlBoolean dbmsDeleteRow(IliTableBuffer*, IlInt);
    virtual IlBoolean dbmsMoveRow(IlInt, IlInt);
    virtual IlBoolean dbmsExchangeRows(IlInt, IlInt);

    IlBoolean refreshSchemaIds(IlInt) const;

    IlBoolean isAvoidingBlobs() const;
    IlBoolean needsBlobInterface(IlInt) const;

    IliSQLTable(IlvDisplay*, const IliClassInfo*);
    IliSQLTable(const IliSQLTable&, const IliClassInfo*);
    IliSQLTable(IlvDisplay*, IL_STDPREF istream&, const IliClassInfo*);

    void deepCopy(const IliSQLTable&);

    void copySQLTable(const IliSQLTable&, const IliClassInfo*);
    void readSQLTable(IL_STDPREF istream&, const IliClassInfo*);

    virtual IliColumn* newColumn();

    IlBoolean isColumnSQLNameAmbiguous(IlInt) const;
    void computeColumnName(IlInt);

    IlBoolean checkRowsCountLimit() const;

    void deleteTableUsers(IliSQLTableAlias*);

    IlInt getUpdatableTableCount() const;

    IlInt getColumnsCountEx(IlBoolean) const;
    IlInt getColumnTableEx(IlInt, IlBoolean) const;
    const char* getColumnSQLTextEx(IlInt, IlBoolean) const;
    void setColumnSQLTextEx(IlInt, const char*, IlBoolean);
    void deleteColumnEx(IlInt, IlBoolean);

    void renumberNonFetchedColumns();

    IlBoolean getOuterJoins(IlInt&, IliSQLOuterJoinDesc*,
			    IlBoolean*, IlInt) const;

    void init();
    void initFlags();
    void initCursors();
    void invalidateStatements();

    IlBoolean postAsyncCall(CursorTag, State);

    IlBoolean newCursor(CursorTag);
    IlBoolean retrieveCursor(CursorTag, const char*);
    void releaseCursor(CursorTag);
    void closeCursor(CursorTag);
    void endFetch();

    const char* getFullDriverName() const;
    IlBoolean mustRecomputeStatement() const;
    IlBoolean mustRecomputeInsertStatement() const;

    IlBoolean hasNestedTableAlias() const;
    IlBoolean areAllNestedTablesWellDefined() const;
    IlBoolean hasStructuredColumns(IlInt = -1) const;

    IlBoolean emitTableName(IliSQLStmtBuf&, IlInt) const;
    void emitColumnName(IliString&, IlInt, IlInt) const;
    void emitColumnRef(IliString&, IliSQLTableColumn*, IlBoolean,
		       IlInt) const;
    void emitLockClause(IliString&, IlInt) const;

    IlBoolean checkModifiedColumns(IliTableBuffer*);

    void defineUserParams(IliSQLCursor*) const;
    void setUserParams(IliSQLCursor*) const;

    void defineParams(IliSQLCursor*,
		      IliBindInfoEnum) const;
    IlBoolean setParams(IliSQLCursor*,
			IliBindInfoEnum) const;
    IlBoolean refreshColumns(IliSQLCursor*);

    IlBoolean loopTest(IliColumn*, const IliSQLColumnFilter&,
			const IliTableBuffer*) const;
    IlBoolean loopOnColumns(IliSQLStmtBuf&,
			    const IliSQLColumnFilter&, IlInt,
			    const char*, const char* = 0,
			     IlInt* = 0) const;
    IlBoolean getAnyCursor(CursorTag, const IliSQLStmtBuf&);
    IlBoolean executeCursor(CursorTag, IlInt* = 0);
    IlBoolean executeCursor2(CursorTag, IlInt* = 0);
    IlBoolean selectCursor(CursorTag);
    IlBoolean advanceCursor(CursorTag);

    IlBoolean writeBlobs();

    IlBoolean emitFromClause(IliSQLStmtBuf&) const;
    const char* emitWhere(IlInt, IlBoolean) const;
    IlBoolean emitWhereClause(IliSQLStmtBuf&, IlBoolean,
			      const char* = 0) const;
    void emitGroupByClause(IliSQLStmtBuf&) const;
    void emitOrderByClause(IliSQLStmtBuf&) const;

    IlBoolean makeSelectStatement(IliSQLStmtBuf&);

    IlBoolean isNullTableError(CursorTag) const;
    IlBoolean makeCreateParentTableStatement(IliSQLStmtBuf&, IlInt) const;
    IlBoolean createParentTable(CursorTag, IlInt);

    IlBoolean sqlInsert();
    virtual IlBoolean makeInsertStatement(IlInt);
    IlBoolean getInsertCursor(IlInt);

    virtual IlBoolean makeFetchStatementEx(IliSQLStmtBuf&,
					   IliTableBuffer*,
					   IlBoolean, IlBoolean,
					   StmtProducer&,
					   const char* = 0) const;
    IlBoolean makeParentFetchStatement(IliSQLStmtBuf&, IlInt,
				       const char* = 0) const;
    IlBoolean makeFetchStatement(IliTableBuffer*, IlBoolean, IlBoolean);
    IlBoolean getFetchCursor(IlBoolean);

    IlBoolean sqlUpdate();
    IlBoolean makeUpdateStatementEx(IliSQLStmtBuf&, IlInt,
				    const IliSQLColumnFilter&) const;
    virtual IlBoolean makeUpdateStatement(IlInt);
    IlBoolean getUpdateCursor(IlInt);

    IlBoolean sqlDelete();
    virtual IlBoolean makeDeleteStatement(IlInt);
    IlBoolean getDeleteCursor(IlInt);

    IlBoolean genericRefreshRow(IlInt, IlBoolean, IlBoolean, IlBoolean);

    IlBoolean readRow(IliTableBuffer*, IliTableBuffer*,
		      IlBoolean, IlBoolean, IlBoolean);
    IlBoolean fetchRow(IliTableBuffer*, IlBoolean, IlBoolean);

    IlBoolean checkOneRow(CursorTag, IlInt);
    const char* opname(CursorTag) const;

    IlBoolean sessionError(IliSQLSession*);
    IlBoolean cursorError(IliSQLSession*, IliSQLCursor*);
    IlBoolean unexpectedStateError();

    IlBoolean checkSQLConnect();
    IlBoolean checkAsyncMode();
    IlBoolean checkNoAsyncMode();
    IlBoolean startTransactionIfNeeded();
    IlBoolean commitIfNeeded();
    IlBoolean rollbackIfNeeded();

    // Hooks
    virtual void columnInserted(IlInt);
    virtual void columnChanged(IlInt);
    virtual void columnToBeDeleted(IlInt);
    virtual void columnMoved(IlInt, IlInt);

    virtual void tableInserted(IlInt);
    virtual void tableToBeDeleted(IlInt);

    virtual void joinInserted(IlInt);
    virtual void joinToBeDeleted(IlInt);

    virtual void conjunctInserted(IlInt, IlBoolean);
    virtual void conjunctToBeDeleted(IlInt, IlBoolean);
    virtual void conjunctDeleted(IlInt, IlBoolean);

    virtual void aliasesChanged();
    virtual void sqlTextChanged(IlInt);

    virtual void tableParentPathChanged(IlInt);

    // Friends
    static const IliSQLTable* topSQLTable();

    friend class IliFetchStmtProducer;
    friend class IliParentFetchStmtProducer;
    friend class IliSQLConditionTerm;
    friend class IliSQLConditionList;
    friend class IliSQLQueryJoin;
    friend class IliSQLColumnFilter;
    friend class IliSQLTableEx;
};

#if !defined(__Ili_Sqltbitf_H)
#  include <ilviews/dataccess/intrface/sqltbitf.h>
#endif

IliDeclareTypeInit_exp(ILV_DBI_EXPORTED, IliSQLTable);

#endif /* !__Ili_Sqltable_H */
