// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbms/session.h
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
// Declaration of the IliSQLSession class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Session_H
#define __Ili_Session_H

#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ili_Common_H)
#  include <ilviews/dataccess/common.h>
#endif
#if !defined(__Ili_Schema_H)
#  include <ilviews/dataccess/schema.h>
#endif
#if !defined(__Ili_Tblref_H)
#  include <ilviews/dataccess/tblref.h>
#endif
#if !defined(__Ili_Tbldef_H)
#  include <ilviews/dataccess/tbldef.h>
#endif
#if !defined(__Ili_Vsession_H)
#  include <ilviews/dataccess/vsession.h>
#endif
#if !defined(__Ili_Gcallbak_H)
#  include <ilviews/dataccess/gcallbak.h>
#endif
#if !defined(__Ili_Systype_H)
#  include <ilviews/dataccess/dbms/systype.h>
#endif
#if !defined(__Ili_Cursor_H)
#  include <ilviews/dataccess/dbms/cursor.h>
#endif
#if !defined(__Ili_Cxndlg_H)
#  include <ilviews/dataccess/dialogs/cxndlg.h>
#endif

class ILVDSPEXPORTED IlvDisplay;
class ILVDSPEXPORTED IlvAbstractView;
class ILV_DBI_EXPORTED IliDbmsDriver;

// --------------------------------------------------------------------------
enum IliSQLQueryConnectFlag {
    IliSQLQueryPasswordOnly,
    IliSQLQueryIfNeeded,
    IliSQLQueryAlways
};

enum IliSQLSessionEvent {
    IliSQLSessionDisconnect,
    IliSQLSessionCommit,
    IliSQLSessionRollback
};

typedef void (*IliSQLSessionCallback)(IliSQLSession*, IliSQLSessionEvent,
				       IlAny arg);
IL_DEFINEFPTRTOANYCAST(IliSQLSessionCallback);

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLSession
: public IliSession {
public:
    IliSQLSession();
    IliSQLSession(const IliSQLSession&);
    IliSQLSession(const char* dbmsName, const char* params);

    void read(std::istream& input);
    void readToIgnore(IL_STDPREF istream& input);
    void write(std::ostream& output) const;

    inline IliDbmsDriver* getDriver() const { return _driver; }

    inline IlAny getHook() const { return _sno; }

    static void SetNewDbmsFunction(IliSQLNewDbmsFunction fct);
    static const char* const* GetDbmsNames(IlInt& count);
    static IliSQLSession* GetDefault();

    // Parameters
    void setSessionParams(const IliSQLSession* sess);
    IlBoolean hasSameParams(const IliSQLSession* sess) const;

    IlBoolean hasName() const;
    IlBoolean hasDbms() const;
    IlBoolean hasParams() const;
    IlBoolean hasPassword() const;

    const char* getSessionName() const;
    void setSessionName(const char* name);

    IliSQLSession* getEffectiveSQLSession();

    const char* getDbmsName() const;
    void setDbmsName(const char* name);

    IlBoolean isAMoniker() const;
    void setAsMoniker(IlBoolean moniker);

    const char* getUserName() const;
    void setUserName(const char* name);

    const char* getPassword() const;
    void setPassword(const char* pwd);

    IlBoolean isPasswordSaved() const;
    void savePassword(IlBoolean flag);

    const char* getDatabaseName() const;
    void setDatabaseName(const char* name);

    const char* getConnectionOptions() const;
    void setConnectionOptions(const char* opt);

    const char* getConnectionParams() const;
    void setConnectionParams(const char* params);

    // Connecting
    IlBoolean isConnected() const;
    IlBoolean connect();
    IlBoolean queryConnect(IlvDisplay* display, IlvAbstractView* view,
			   IliSQLQueryConnectFlag flag = IliSQLQueryIfNeeded,
			   IlBoolean showName = IlFalse);
    IlBoolean disconnect();
    void setTimeout(short nsecs);

    // Cursors
    IliSQLCursor* newCursor();
    IliSQLCursor* retrieveCursor(const char*);
    void releaseCursor(IliSQLCursor* curs);

    // Transactions
    IlBoolean startTransaction();
    IlBoolean commit();
    IlBoolean rollback();

    // Schema
    char** readOwners(IlInt& count);

    char** readAbstractTypeNames(IlInt& count, const char* = 0);
    const IliDatatype* readAbstractType(const char*,
					const char* = 0);
    const IliDatatype* readAbstractType(IlInt);

    char** readTableOwners(IlInt&, const char* = 0);
    char** readTableNames(IlInt& count, const char* tableOwner = 0);
    char** readTableNames(IlInt&, char**&);
    void freeNames(char**, char** = 0);

    IliSQLTableDef* readTableDefinition(IlvDisplay* display,
					const char* tableName,
					const char* tableOwner = 0,
					IlBoolean isSynonym = IlFalse);
    char** readSynonymNames(IlInt& count, const char* synOwner = 0) ;

    // Async Mode
    IlBoolean supportsAsyncMode();
    IlBoolean isInAsyncMode();
    IlBoolean enterAsyncMode();
    IlBoolean quitAsyncMode();
    IlBoolean cancelAsyncCall();
    IlBoolean isAsyncCallCompleted();

    // Error reporting
    inline IlBoolean isErrorRaised() const { return errorRaised(); }
    IlBoolean errorRaised() const;

    IliErrorMessage getErrorMessage() const;
    static void ForwardErrorToGlobalSink(IlBoolean forward);
    static IlBoolean isForwardErrorToGlobalSink();

    static void ReadMessageDatabase(IlvDisplay* display);
    static void ConnectToMessageDatabase(IlvDisplay* display);

    // Registery
    IlBoolean isRegistered() const;
    static IlBoolean RegisterSession(IliSQLSession* sess);
    static IlBoolean RegisterSession(const char* sessionName,
				     const char* dbmsName,
				     const char* connectionParams);
    static void UnRegisterSession(IliSQLSession* sess);
    static IlInt GetRegisteredSessionsCount();
    static IliSQLSession* GetRegisteredSession(IlInt index);
    static IliSQLSession* GetRegisteredSession(const char* name);

    // Trace options
    static IlBoolean IsSQLTraceEnabled();
    static void EnableSQLTrace(IlBoolean f);
    static IliSQLTraceOptions GetTraceOptions();
    static void SetTraceOptions(const IliSQLTraceOptions& opt);

    // Other
    IlBoolean getEffectiveUserName(IliString&);

    void emitIdentifier(IliString&, const char*) const;
    void emitStringLiteral(IliString&, const char*) const;
    void emitBinaryLiteral(IliString&, const IliBinary&) const;
    void emitTableRef(IliString&, const IliSQLTableRef&,
		      IliStatementType = IliDMLStmt) const;
    void emitSynonymRef(IliString&, const IliSQLTableRef&,
			IliStatementType = IliDMLStmt) const ;
    virtual void emitDate(IliString& dest, IliDate val) const;
    virtual void emitTime(IliString& dest, IliTime val) const;

    IlInt getCreateStatementsCount(const IliSQLTableDef*) const;
    IlBoolean makeCreateStatement(const IliSQLTableDef*, IlInt, IliString&);

    inline IlInt getLockVerbPosition() const { return _lockVerbPosition; }
    inline const char* getLockVerb() const { return _lockVerb; }

    const char* const* getSystemTypes(IlInt&);
    IlBoolean getDefaultSystemType(const IliDatatype*, IlInt,
				    IliSQLSystemType&);

    IlBoolean hasSearchOnNullVar();
    IlBoolean canBindNullVar();
    IlBoolean isTypeSearchable(const IliDatatype*, IlInt);

    // Hooks
    static IliSQLCallHookFn GetBeforeCallHook();
    static void SetBeforeCallHook(IliSQLCallHookFn);

    static IliSQLCallHookFn GetAfterCallHook();
    static void SetAfterCallHook(IliSQLCallHookFn);

    // Callbacks
    void addCallback(IliSQLSessionCallback, IlAny);
    void removeCallback(IliSQLSessionCallback, IlAny);

    // Enabled
    static IlBoolean IsSQLEnabled();
    static void EnableSQL(IlBoolean);

    static void AddSQLEnableHook(IliCallback*);
    static void RemoveSQLEnableHook(IliCallback*);

    IlBoolean debugCheck() const;
    IlvValueInterface* getItf() const;

    static IlBoolean IsBadLicense();

    static void AtInit();
    static void AtExit();

    void attach(IliSQLCursor*);
    void detach(IliSQLCursor*);

protected:
    IliDbmsDriver* _driver;
    IlAny _sno;
    IliString _name;
    IlBoolean _isAMoniker;
    IliString _connectParams;
    IliSQLCursorCollection _cursors;
    IlvStringHashTable _parsedCursors;
    IliCxnParamRec _parametersRecord;
    IlBoolean _savePassword;
    //
    IlBoolean _hasStartTransaction;
    IlBoolean _isMultiCursor;
    IlBoolean _localErrorRaised;
    IlBoolean _isRegistered;
    IlBoolean _inTrans;
    IlInt _lockVerbPosition;
    const char* _lockVerb;
    IliErrorMessage _lastErrorMessage;
    IlvAList _callbacks;
    IlvValueInterface* _itf;

    static IliSQLSession* _defaultSession;
    static IlvArray* _registeryList;
    static IlvStringHashTable* _registeryTable;
    static IlBoolean _ForwardToGlobalSink;

    ~IliSQLSession();

    void resetFlags();
    void readFlags();

    inline IliSQLSession& operator=(const IliSQLSession&) { return *this; }

    inline void clearError() const
	{ ((IliSQLSession*)this)->_lastErrorMessage.unset(); }
    void setErrorMessage(IliErrorMessage&);
    void setErrorMessage(IliErrorCodeTag);
    void alreadyConnectedError();
    void notConnectedError();

    void freeCursor(IliSQLCursor*);
    void cursorsNeedReParse();

    IlAny getCursorHook();
    void callCallbacks(IliSQLSessionEvent);

    friend class IliModuleCLASS(IliSQLSession);
};


#define ILIINITDBMS(driver)						\
    extern ILV_DBI_EXPORTEDFN(int) IliInit##driver##Driver();		\
    static int Ili##driver##InitFlag = IliInit##driver##Driver()

#if !defined(ILI_BUILDLIBS)
#  if defined(ILDALL)
ILIINITDBMS(Db2);
ILIINITDBMS(Informix);
#    ifdef WINDOWS
ILIINITDBMS(MsSql);
ILIINITDBMS(Odbc);
ILIINITDBMS(Oledb);
#    endif
ILIINITDBMS(Oracle);
ILIINITDBMS(Sybase);
#  endif
#endif

#ifdef ILDDB2
ILIINITDBMS(Db2);
#  ifndef ILI_DBMS_DEFINED
#    define ILI_DBMS_DEFINED
#  endif
#endif

#ifdef ILDORACLE
ILIINITDBMS(Oracle);
#  ifndef ILI_DBMS_DEFINED
#    define ILI_DBMS_DEFINED
#  endif
#endif

#ifdef ILDINFORMIX
ILIINITDBMS(Informix);
#  ifndef ILI_DBMS_DEFINED
#    define ILI_DBMS_DEFINED
#  endif
#endif

#if defined(ILDCTSYBASE) || defined(ILDSYBASE)
ILIINITDBMS(Sybase);
#  if !defined(ILI_DBMS_DEFINED)
#    define ILI_DBMS_DEFINED
#  endif
#endif

#if defined(ILDMSSQL)
ILIINITDBMS(MsSql);
#  if !defined(ILI_DBMS_DEFINED)
#    define ILI_DBMS_DEFINED
#  endif
#endif

#if defined(ILDODBC)
ILIINITDBMS(Odbc);
#  if !defined(ILI_DBMS_DEFINED)
#    define ILI_DBMS_DEFINED
#  endif
#endif

#if defined(ILDOLEDB)
ILIINITDBMS(Oledb);
#  if !defined(ILI_DBMS_DEFINED)
#    define ILI_DBMS_DEFINED
#  endif
#endif

#if !defined(ILIDLL)
#  if defined(ILI_DBMS_DEFINED) || defined(ILDALL)
#    define ILI_CUSTOM_NEW_DBMS_NEEDED
#  endif
#endif

#if defined(_MSC_VER)
#  if !defined(ILI_BUILDLIBS)
#    if defined(ILI_DBMS_DEFINED) || defined(ILDALL)
#      pragma comment(lib, "dbaccess")
#    endif
#  endif
#endif

#if !defined(__Ili_Sqlseitf_H)
#  include <ilviews/dataccess/intrface/sqlseitf.h>
#endif

IliModuleDECL_exp(ILV_DBI_EXPORTED, IliSQLSession);

#endif /* !__Ili_Session_H */
