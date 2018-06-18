// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbms/dbmsdriv.h
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
// Declaration of the IliDbmsDriver class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Dbmsdriv_H
#define __Ili_Dbmsdriv_H

#ifndef __Ili_Datatype_H
#  include <ilviews/dataccess/datatype.h>
#endif

#ifndef __Ili_Systype_H
#  include <ilviews/dataccess/dbms/systype.h>
#endif

#ifndef __Ili_Error_H
#  include <ilviews/dataccess/error.h>
#endif

#ifndef __Ili_Sqlbind_H
#  include <ilviews/dataccess/dbms/sqlbind.h>
#endif

#ifndef __Ili_Tblref_H
#  include <ilviews/dataccess/tblref.h>
#endif

#ifndef __Ili_Schema_H
#  include <ilviews/dataccess/schema.h>
#endif

class ILVDSPEXPORTED IlvAbstractView;
class ILV_DBI_EXPORTED IliSQLTableDef;
class ILV_DBI_EXPORTED IliSQLTableRef;
class ILV_DBI_EXPORTED IliSQLStmtBuf;
class ILV_INF_EXPORTED IliSchema;

enum IliDbmsDriverId {
  IliDriver_Null,
  IliDriver_Db2,
  IliDriver_Db29x,
  IliDriver_Oracle,
  IliDriver_Oracle9,
  IliDriver_Oracle10,
  IliDriver_Oracle11,
  IliDriver_Informix,
  IliDriver_Informix9,
  IliDriver_Sybase,
  IliDriver_Odbc,
  IliDriver_Mssql,
  IliDriver_Oledb,
  IliDriver_Count
};

enum IliIdentifiersQuotedRule {
  IliQuoteAutomatic = 0,
  IliQuoteAlways,
  IliQuoteNever
};

enum IliCaseSensitivity {
  IliCaseSensitive,
  IliUppercase,
  IliLowercase
};

enum IliOuterJoinStyle {
  IliOJ_InWherePart,
  IliOJ_InFromPart,
  IliOJ_InBothParts
};

typedef void (*IliGetDriverInfoFn)(IlBoolean*);
typedef void (*IliReadDbmsDriverErrorMessagesFn)(IlvDisplay*);

// --------------------------------------------------------------------------
// IliFromItem
// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliFromItem {
public:
  IliFromItem() { _alias = NULL; }
  virtual ~IliFromItem();

  virtual void emitTableExpr(IliSQLStmtBuf&) const;
  IliSQLTableRef getTableRef() const { return _tblRef; }
  void setTableRef(const IliSQLTableRef& ref) { _tblRef = ref; }
  const char* getAlias() const { return _alias; }
  void setAlias(const char* alias) { _alias = alias; }

  virtual IlBoolean needsAlias() const;

private:
  IliSQLTableRef _tblRef;
  const char* _alias;
};

// --------------------------------------------------------------------------
// IliOuterJoinDesc
// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliOuterJoinDesc {
public:
  IliOuterJoinDesc();
  ~IliOuterJoinDesc();

  IliFromItem* getOuterItem() const { return _outerItem; }
  void setOuterItem(IliFromItem* outerItem) { _outerItem = outerItem; }

  void emitOuterTableExpr(IliSQLStmtBuf&) const;
  IliSQLTableRef getOuterTableRef() const;
  const char* getOuterTableAlias() const;

  IliFromItem* getInnerItem() const { return _innerItem; }
  void setInnerItem(IliFromItem* innerItem) { _innerItem = innerItem; }

  void emitInnerTableExpr(IliSQLStmtBuf&) const;
  IliSQLTableRef getInnerTableRef() const;
  const char* getInnerTableAlias() const;

  IlInt getTermsCount() const;
  void getTermAt(IlInt idx,IliAttributePath& outerColumn,
		 IliAttributePath& innerColumn) const;
  void addTerm(const IliAttributePath& outerColumn,
	       const IliAttributePath& innerColumn);


private:
  struct Term {
    IliAttributePath outerColumn;
    IliAttributePath innerColumn;
  };

  IliFromItem* _outerItem;
  IliFromItem* _innerItem;
  IlvArray _terms;
};

// --------------------------------------------------------------------------
// IliDbmsDriver
// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliDbmsDriver : public IliRefCounted {
public:
  static IlInt GetDriverCount();

  static IliDbmsDriver* GetDriverByName (const char*);
  static IliDbmsDriver* GetDriverById (IliDbmsDriverId);
  static IliDbmsDriver* GetNullDriver ();

  static IliDbmsDriverId GetDriverIdByName (const char*);
  static const char* GetDriverNameById (IliDbmsDriverId);

  static const char* const* GetDriversNames (IlInt& count);

  static void SetNewDbmsFunction (IliSQLNewDbmsFunction);

  // -- identity

  inline IliDbmsDriverId getDriverId () const;
  inline const char* getDriverName () const;
  virtual const char* getFullDriverName (IlAny sid) const;

  virtual IlBoolean isDblinkDriver() const;
  inline IlBoolean isOracleFamily() const;
  inline IlBoolean isInformixFamily() const;
  inline IlBoolean isSybaseFamily() const;
  inline IlBoolean isOpIngresFamily() const;

  // -- ref counting

  virtual IliDbmsDriver* clone ();

  // -- information
  virtual IlBoolean isCommitEnabled();

  virtual IlBoolean hasStartTransaction (IlAny sid);
  virtual IlBoolean isTransctionCursorNeeded();
  virtual IlBoolean isMultiCursor (IlAny sid);
  virtual char identifierQuoteChar (IlAny sid);
  virtual IlInt lockVerbPosition (IlAny sid);
  virtual const char* lockVerb (IlAny sid);
  virtual IlBoolean hasAnsiReferentialIntegerity (IlAny sid);
  virtual IlBoolean hasCreateIndex (IlAny sid);
  virtual IliCaseSensitivity identifierCaseSensitivity (IlAny sid);
  virtual IliCaseSensitivity userNameCaseSensitivity (IlAny sid);
  virtual IlBoolean hasDefineVar (IlAny sid);
  virtual IlBoolean hasNamedVars (IlAny sid);
  virtual IlBoolean hasSearchOnNullVar (IlAny);
  virtual IlBoolean isParseLostAtTransactionBoundaries (IlAny);
  virtual IlBoolean canBindNullVar (IlAny);
  virtual IlBoolean supportsDateStructs (IlAny);
  virtual IlBoolean supportsOwners (IlAny);
  virtual IlBoolean hasLargeVars(IlAny);
  virtual IlBoolean canLockMultiTableRows(IlAny);
  virtual IlBoolean supportsOuterJoins(IlAny);
  virtual IliOuterJoinStyle getOuterJoinStyle(IlAny);
  virtual const char* emitWhere(IlInt joinCount,IlBoolean hasOuter) const;
  virtual void emitOuterJoinFromPart(IlAny sid,IliSQLStmtBuf& dest,
				     const IliOuterJoinDesc& ojd);
  virtual void emitOuterJoinWherePart(IlAny sid,IliSQLStmtBuf& dest,
				      const char* outerAlias,
				      const IliAttributePath& outerColumn,
				      const char* innerAlias,
				      const IliAttributePath& innerColumn);
  virtual void emitFromItem(IlAny sid,IliSQLStmtBuf& dest,IliFromItem& item);
  virtual void emitInnerJoin(IlAny sid,IliSQLStmtBuf& dest,
			     const char* leftAlias,
			     const IliAttributePath& leftColumn,
			     const char* rightAlias,
			     const IliAttributePath& rightColumn);


  virtual IlBoolean hasUserParam () const;
  virtual IlBoolean hasPasswordParam () const;
  virtual IlBoolean hasDatabaseParam () const;
  virtual IlBoolean hasOptionsParam () const;

  virtual void emitTypeClause (IlAny sid,IliString&,const IliSQLSystemType&);
  virtual void emitNullableClause (IlAny sid,IliString&,IlBoolean nullable);
  virtual void emitDefaultClause (IlAny sid,IliString&,const char* defval);
  virtual void emitPrimaryKeyClause (IlAny sid,IliString&,
				     const IliSQLTableDef*);
  virtual void emitCandidateKeyClause (IlAny sid,IliString&,
				       const IliSQLTableDef*,IlInt ckno);
  virtual void emitForeignKeyClause (IlAny sid,IliString&,
				     const IliSQLTableDef*,IlInt fkno);
  virtual void emitCreateTableTrail (IlAny sid,IliString&,
				     const IliSQLTableDef*);

  virtual IlBoolean identifierNeedsQuote (IlAny sid, const char*);
  virtual void emitIdentifier (IlAny sid, IliString&,const char*);
  virtual void emitPath (IlAny sid, IliString&, const IliAttributePath&);
  virtual void emitStringLiteral (IlAny sid,IliString&,const char*);

  virtual void emitBinaryLiteral (IlAny sid,IliString&,const IliBinary&);
  virtual void emitOwnerName (IlAny sid,IliString&,const char* ownerName);
  virtual void emitTableRef (IlAny sid,IliString&,const IliSQLTableRef&,
			     IliStatementType);
  virtual void emitSynonymRef (IlAny sid, IliString&, const IliSQLTableRef&,
			       IliStatementType) ;
  virtual void emitDate (IlAny sid,IliString&, const IliDate&);
  virtual void emitTime (IlAny sid,IliString&,const IliTime&);

  virtual void emitDateParam (IlAny sid,IliString&, const IliDate&);
  virtual void emitTimeParam (IlAny sid,IliString&, const IliTime&);

  virtual IlBoolean parseDate (IlAny sid, const char*, IliDate&);
  virtual const IliFormat& getDbmsDateFormat ();
  virtual const IliFormat& getDbmsDateTimeFormat ();
  virtual const IliFormat& getDbmsTimeFormat ();

  virtual IlInt getCreateStatementsCount (IlAny sid,const IliSQLTableDef*);
  virtual IlBoolean makeCreateStatement (IlAny sid,const IliSQLTableDef*,
					 IlInt index,IliString& stmt,
					 IliErrorMessage& errMsg);

  virtual const char* const* getSystemTypes (IlAny sid, IlInt& count);

  virtual IlBoolean getDefaultSystemType (IlAny,const IliDatatype* type,
					  IlInt maxlen,
					   IliSQLSystemType& sysType);

  virtual IlBoolean isTypeSearchable(IlAny,const IliDatatype* type,
				     IlInt maxlen);

  virtual void unpackParameters (const char* params,IliCxnParamRec& rec);
  virtual void packParameters (const IliCxnParamRec& rec,IliString& params);

  // -- Async

  virtual IlBoolean supportsAsyncMode(IlAny sid);
  virtual IlBoolean isInAsyncMode(IlAny sid);
  virtual IlBoolean setAsyncMode(IlAny sid,IlBoolean flag);
  virtual IlBoolean cancel(IlAny sid);
  virtual IlBoolean isCompleted(IlAny sid);
  virtual IlBoolean isCompleted(IlAny sid,IlAny cid);


  // -- session

  virtual IlBoolean connect (const char* params, IlAny& sid);
  virtual IlBoolean disconnect (IlAny sid);
  virtual IlBoolean isConnected (IlAny sid);

  virtual void setTimeout(IlAny sid, short nsecs);

  virtual IlBoolean getEffectiveUserName (IlAny sid,const char* userName,
					   IliString&);

  virtual IlBoolean errorRaised (IlAny sid);

  virtual void getErrorMessage(IlAny sid,IliErrorMessage& msg) const;


  virtual char** readOwners(IlAny sid,IlInt& count);

  virtual char** readAbstractTypeNames(IlAny sid,IlInt& count,
				       const char* owner = 0);
  virtual const IliDatatype* readAbstractType(IlAny sid,const char* typeName,
					      const char* owner = 0);
  virtual const IliDatatype* readAbstractType(IlAny sid,IlInt typeId);


  virtual char** readTableOwners (IlAny sid,IlInt& count,
				  const char* tableName = 0);

  virtual char** readTableNames (IlAny sid,IlInt& count,
				 const char* tableOwner = 0);
  virtual char** readTableNames (IlAny sid,IlInt& count,char**& ownerNames);
  virtual char** readSynonymNames(IlAny sid, IlInt& count,
				  const char* synOwner = 0) ;
  virtual void freeNames(IlAny sid, char** names, char** ownerNames = 0);

  virtual IliSQLTableDef* readTableDefinition (IlvDisplay*,IlAny sid,
					       const char* tableName,
					       const char* tableOwner,
					       IliErrorMessage& errmsg,
					       IlBoolean isSynonym = IlFalse);

  virtual const char* getColumnNameForCollection() const;

  // -- cursors

  virtual IlAny newCursor (IlAny sid);
  virtual void freeCursor (IlAny sid, IlAny cid);
  virtual IlBoolean closeCursor(IlAny sid, IlAny cid);

  virtual IlBoolean startTransaction (IlAny sid, IlAny cid);
  virtual IlBoolean autoCommitOn (IlAny sid, IlAny cid);
  virtual IlBoolean autoCommitOff (IlAny sid, IlAny cid);
  virtual IlBoolean commit (IlAny sid, IlAny cid);
  virtual IlBoolean rollback (IlAny sid, IlAny cid);

  virtual IlBoolean setBufferedRowsCount (IlAny sid, IlAny cid, IlInt);
  virtual IlInt getBufferedRowsCount (IlAny sid, IlAny cid);

  virtual IlBoolean parse (IlAny sid, IlAny cid, const char*);
  virtual void cancelResultSet (IlAny sid, IlAny cid);

  virtual IlBoolean bindCol(IlAny sid,IlAny cid,IlInt colno,
			    const IliDatatype* type,IlInt size = 0);

  virtual IlBoolean defineVar (IlAny sid,IlAny cid,const char* varname,
			       IlInt varno,const IliDatatype* type,
			       IlUInt maxlen);
  virtual IlInt getVarBufferSize (IlAny sid,IlAny cid,IlInt varno);
  virtual IlBoolean setVar (IlAny sid,IlAny cid,IlInt varno,const IliValue&);
  virtual IlBoolean getVar (IlAny sid,IlAny cid,IlInt varno,IliValue&);
  virtual IlBoolean execute (IlAny sid,IlAny cid,const char* stmt,IlInt*);
  virtual IlBoolean execute (IlAny sid, IlAny cid, IlInt* pcnt);
  virtual IlBoolean select (IlAny sid, IlAny cid, const char* stmt);

  virtual IlBoolean writeLongString(IlAny sid,IlAny cid,const char* data,
				    IlUInt size,const char* tabName,
				    const char* colName,const char* whereCond);
  virtual IlBoolean writeLongBinary(IlAny sid,IlAny cid,const IliBinary& bin,
				    const char* tabName,const char* colName,
				    const char* whereCond);

  virtual IlBoolean fetchNext (IlAny sid, IlAny cid);
  virtual IlBoolean hasTuple (IlAny sid, IlAny cid);
  virtual void getSchema (IlAny sid, IlAny cid, IliSchema& schema);
  virtual IlInt getColumnsCount (IlAny sid, IlAny cid);
  virtual IlBoolean getValue (IlAny sid,IlAny cid,IlInt colno,IliValue&);

  virtual IlBoolean errorRaised (IlAny sid, IlAny cid);

  virtual void getErrorMessage(IlAny sid,IlAny cid,IliErrorMessage& msg) const;

  const char* adjustOwnerName (IlAny sid, IliString&, const char* src);
  void capitalise (IliString& dest, const char* src, IliCaseSensitivity);

  // -- Trace

  static IliSQLTraceOptions GetTraceOptions();
  static void SetTraceOptions (const IliSQLTraceOptions&);

  static IlBoolean IsTraceEnabled ();
  static void EnableTrace (IlBoolean);

  static IlBoolean IsTracingConnect ();
  static void TraceConnect (IlBoolean);

  static IlBoolean IsTracingCursors ();
  static void TraceCursors (IlBoolean);

  static IlBoolean IsTracingSQL ();
  static void TraceSQL (IlBoolean);

  static void EmitTrace(const char*);

  // -- Error messages i18n

  static void ReadMessageDatabase(IlvDisplay*);
  static void ConnectToMessageDatabase(IlvDisplay*);

  /* Identifiers */

  static IliIdentifiersQuotedRule getIdentifiersQuotedRule();
  static void setIdentifiersQuotedRule(IliIdentifiersQuotedRule);

  /* Enabled */

  static IlBoolean IsSQLEnabled();
  static void EnableSQL(IlBoolean);

  static void AddSQLEnableHook(IliCallback*);
  static void RemoveSQLEnableHook(IliCallback*);

  // --

  static IliSQLCallHookFn GetBeforeCallHook();
  static void SetBeforeCallHook(IliSQLCallHookFn fn);

  static IliSQLCallHookFn GetAfterCallHook();
  static void SetAfterCallHook(IliSQLCallHookFn fn);

  inline void beforeCall(IlAny sid, IlAny cid);
  inline void afterCall(IlAny sid, IlAny cid);

  // --

  virtual void dbctl(IlInt op, IlAny sid, IlAny cid, IlAny arg);

  // --

  static IliDbmsDriverId CreateDriverId();
  static IliDbmsDriver* Register (IliDbmsDriver*);

  static void AtInit ();
  static void AtExit ();
protected:
  IliDbmsDriverId _driverId;
  IliString _driverName;
  IlBoolean _unique;
  IliString _dateBuf;
  IliDate _tempDate;
  IliFormat _dbmsDateFormat;
  IliFormat _dbmsDateTimeFormat;
  IliFormat _dbmsTimeFormat;

  static const char** _driversNames;
  static IlInt _driversCount;
  static IlvList* _drivers;
  static IliDbmsDriver* _nullDriver;
  static IliSQLNewDbmsFunction _newDbmsFunction;
  static IliSQLTraceOptions* _traceOptions;
  static IlInt _sessionsCount;
  static IlInt _cursorsCount;
  static IliGetDriverInfoFn _getDriverInfoFn;
  static IliReadDbmsDriverErrorMessagesFn _readDbmsDriverErrorMessagesFn;
  static IliIdentifiersQuotedRule _QuoteRule;

  static IlBoolean _isSQLEnabled;
  static IliCallbackArray* _enableHooks;

  static IliSQLCallHookFn _beforeCallHook;
  static IliSQLCallHookFn _afterCallHook;
  static IliDbmsDriverId _nextDriverId;


  static IlBoolean HasSQLEnableHook(IliCallback*);

  IliDbmsDriver (IliDbmsDriverId,
		   const char* name);
  IliDbmsDriver (const IliDbmsDriver&);
  virtual ~IliDbmsDriver ();

  void initialiseDbmsDateFormat (const char* defaultDateFormat,
				 const char* defaultTimeFormat = NULL);

  void unpackHelper (const char* params,IliCxnParamRec& rec,const char* fmt);

  void emitTableRef (IlAny sid,
		     IliString& str,
		     const IliSQLTableRef& tblRef,
		     IliStatementType,
		     IlBoolean emitSynRef) ;

  friend class IliModuleCLASS(IliDbmsDriver);
};

// --

inline IliDbmsDriverId
IliDbmsDriver::getDriverId () const {
  return _driverId;
}

inline const char*
IliDbmsDriver::getDriverName () const {
  return _driverName;
}

inline IlBoolean
IliDbmsDriver::isOracleFamily() const {
  return (_driverId == IliDriver_Oracle
	  || _driverId == IliDriver_Oracle9
	  || _driverId == IliDriver_Oracle10
	  || _driverId == IliDriver_Oracle11);
}

inline IlBoolean
IliDbmsDriver::isInformixFamily() const {
  return (_driverId == IliDriver_Informix
	  || _driverId == IliDriver_Informix9);
}

inline IlBoolean
IliDbmsDriver::isSybaseFamily() const {
  return (_driverId == IliDriver_Sybase);
}

inline IlBoolean
IliDbmsDriver::isOpIngresFamily() const {
  return IlFalse;
}

inline void
IliDbmsDriver::EmitTrace(const char* msg) {
  if (GetTraceOptions()._printFn)
    GetTraceOptions()._printFn(msg);
}

inline void
IliDbmsDriver::beforeCall(IlAny sid, IlAny cid) {
  if (_beforeCallHook)
    _beforeCallHook(sid, cid);
}

inline void
IliDbmsDriver::afterCall(IlAny sid, IlAny cid) {
  if (_afterCallHook)
    _afterCallHook(sid, cid);
}

// --

IliModuleDECL_exp(ILV_DBI_EXPORTED,IliDbmsDriver);

#endif
