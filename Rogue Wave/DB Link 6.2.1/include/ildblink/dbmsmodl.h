// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/dbmsmodl.h
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
// Model for inheritance of DBLink Connection class : IldDbms.
// ----------------------------------------------------------------------------

#ifndef __ILD_DBMSMODL_H
#define __ILD_DBMSMODL_H

#ifndef __ILD_DBERR_H
#include <ildblink/dberr.h>
#endif
#ifndef __ILD_BASEMODL_H
# include <ildblink/basemodl.h>
#endif

class IldSchemaEntity;
class IldRelation;
class IldSQLType;
class IldCallable;
class IldSynonym;
class IldADTDescriptor;
class IldRequest;
class IldDriver;

#ifdef WINDOWS
// MSVC not really STD conformant: using clause!
#pragma warning(disable : 4250)
#endif
// ============================================================================
// IldDbms class.
// ============================================================================
class ILD_EXPORTED IldDbmsModel : public IldBaseModel, public IldDbms {
    friend class IldRequestModel;

 private:
    IldRequest*		getRequest		(IldRequest*);

 protected:
    IldDbms*		_dbmsPtr;
    IldDbms&		setErrorReporter	();

			IldDbmsModel		(IldDbmsModel&);
    // getFreeRequest() is not publicly available for IldRequestModel class.
    // It is used only internally.
    // The constructor of the class must be used instead.
    IldRequest*		getFreeRequest		();

 public:
    using IldBaseModel::initializeError;
    using IldBaseModel::fillError;
    using IldBaseModel::fillInformation;
    using IldBaseModel::operator!;
    using IldBaseModel::isErrorRaised;
    using IldBaseModel::isInformationRaised;
    using IldBaseModel::getError;
    using IldBaseModel::getInformation;
    using IldBaseModel::getInformationCode;
    using IldBaseModel::getInformationMessage;
    using IldBaseModel::getErrorCode;
    using IldBaseModel::getErrorMessage;
    using IldBaseModel::getErrorOrigin;
    using IldBaseModel::getErrorSqlstate;
    using IldBaseModel::getErrorConnection;
    using IldBaseModel::getErrorName;
    using IldBaseModel::useStringDate;
    using IldBaseModel::setStringDateUse;
    using IldBaseModel::useStringNumeric;
    using IldBaseModel::setStringNumericUse;
    using IldBaseModel::useNumeric;
    using IldBaseModel::setNumericUse;
			IldDbmsModel		(const char* dbmsName,
						 const char* conStr);

			IldDbmsModel		(const char* dbmsName,
						 const char* database,
						 const char* userName,
						 const char* password);
    virtual
			~IldDbmsModel		();

    inline
    void*		getDbmsPtr		() const
    { return _dbmsPtr; }

    inline
    IlBoolean		isDbms			() const
    { return IlTrue; }

    // ---------------------------
    // Readers
    // ---------------------------
    IlInt		getNumberOfActiveConnections() const;

    const char*		getName			() const;

    const char*		getUser			() const;

    virtual
    const char*        getDbmsVersions		();

    virtual
    IlUInt		getDbmsVersion		();

    const char*		getDatabase		() const;

    const char*		getDbmsServer		() const;

    virtual
    IldDbms&		getInfo			(IldInfoItem info,
						 IlInt* intVal,
						 char* charVal);

    virtual
    IlBoolean		isReadOnlyCapable	() const;

    virtual
    IlBoolean		isScrollableCapable	() const;

    // ---------------------------
    // Connection control
    // ---------------------------
    virtual
    IldDbms&		connect			(const char* connString);

    virtual
    IldDbms&		connect			(const char* database,
						 const char* userName,
						 const char* password);

    virtual
    IldDbms&		disconnect		();

    virtual
    IlBoolean		isConnected		() const;

    // ---------------------------
    // Transaction control
    // ---------------------------
    virtual
    IlBoolean		isTransactionEnabled	();

    virtual
    IldDbms&		setTransactionReadOnly	(IlBoolean flag = IlTrue);

    virtual
    IlBoolean		isTransactionReadOnly	() const;

    virtual
    IldDbms&		startTransaction	(IldRequest* request = 0,
						 const char* transName = 0);

    virtual
    IldDbms&		commit			(IldRequest* request = 0,
						 const char* transName = 0);

    virtual
    IldDbms&		rollback		(IldRequest* request = 0,
						 const char* transName = 0);

    virtual
    IldDbms&		autoCommitOn		(IldRequest* request = 0,
						 const char* transName = 0);

    virtual
    IldDbms&		autoCommitOff		(IldRequest* request = 0,
						 const char* transName = 0);

    // ---------------------------
    // Schema accesses
    // ---------------------------
    virtual
    char**		readOwners		();

    virtual
    IldRelation*	readRelation		(const char* relName,
						 const char* owner = 0);

    virtual
    IldRelation*	readRelation		(IlInt relId);

    virtual
    IldCallable*	readProcedure		(const char* procName,
						 const char* owner = 0);

    virtual
    IldCallable*	readProcedure		(IlInt procId);

    virtual
    IldADTDescriptor*	readAbstractType	(const char* typeName,
						 const char* owner = 0);

    virtual
    IldADTDescriptor*	readAbstractType	(IlInt typeId);

    virtual
    IldSynonym*		readSynonym		(const char* synName,
						 const char* owner = 0);

    virtual
    IldSynonym*		readSynonym		(IlInt synId);

    virtual
    char**		readRelationOwners	(const char* relName = 0);

    virtual
    IldRequest*		readEntityNames		(IldEntityType entType,
						 const char* owner = 0);

    virtual
    char**		readRelationNames	(char**& owners);

    virtual
    char**		readRelationNames	(const char* owner = 0);

    virtual
    char**		readProcedureNames	(const char* owner = 0);

    virtual
    char**		readSynonymNames	(const char* owner = 0);

    virtual
    char**		readAbstractTypeNames	(const char* owner = 0);

    virtual
    IldDbms&		freeNames		(char** names,
						 char** owners = 0);

    virtual
    void		removeRelation		(IldRelation* rel);

    virtual
    void		removeEntity		(IldSchemaEntity* ent);

    virtual
    IlUInt		getNumberOfEntities	();

    virtual
    IldRelation*	getRelation		(const char* relName,
						 const char* owner = 0);

    virtual
    IldRelation*	getRelation		(IlInt relId);

    virtual
    IldCallable*	getProcedure		(const char* procName,
						 const char* owner = 0);

    virtual
    IldCallable*	getProcedure		(IlInt procId);

    virtual
    IldSynonym*		getSynonym		(const char* synName,
						 const char* owner = 0);

    virtual
    IldSynonym*		getSynonym		(IlInt synId);

    virtual
    IldADTDescriptor*	getAbstractType		(const char* typeName,
						 const char* owner = 0);

    virtual
    IldADTDescriptor*	getAbstractType		(IlInt typeId);

    virtual
    void		freeEntity		(IldSchemaEntity* ent);

    virtual
    const IldSQLType**	getTypeInfo		(short cTy = IldSQLAllTypes);

    virtual
    void		freeTypeInfo		(const IldSQLType**);

    // ----------------------
    // Table keys description
    // ----------------------
    virtual
    IldDbms&		readPrimaryKey		(IldRelation* relation);
    virtual
    IldDbms&		readForeignKeys		(IldRelation* relation);
    virtual
    IldDbms&		readIndexes		(IldRelation* relation);
    virtual
    IldDbms&		readSpecialColumns	(IldRelation* relation);

    virtual
    IldRequest*		readTablePrivileges	(const char* catalog,
						 const char* schema,
						 const char* table);

    // -----------------
    // Notification API
    // -----------------
    virtual
    IldDbms&		subscribeEvent		(const char* name,
						 IldNotifFunction usrCB,
						 IlAny usrData);

    virtual
    IldDbms&		unSubscribeEvent	(const char* name);

    // ---------------------------
    // Interfaces to request objects
    // ---------------------------
    virtual
    IlUInt		getNumberOfRequests	() const;

    // ---------------------------
    // Session configuration
    // ---------------------------
    virtual
    IldDbms&		setDefaultColArraySize	(IlUInt size);

    virtual
    IlUInt		getDefaultColArraySize	() const;

    virtual
    IldDbms&		setDefaultParamArraySize(IlUInt size);

    virtual
    IlUInt		getDefaultParamArraySize() const;

    virtual
    IldDbms&		setTimeOut		(short secs);

    // ---------------------------
    // Miscellaneous
    // ---------------------------
    // Error handler
    virtual
    IldErrorReporter*	getErrorReporter	() const;

    virtual
    IldDbms&		setErrorReporter	(IldErrorReporter* reporter);

    // ------------------
    // Extension purpose
    // ------------------
    // Probably useless for this class
    virtual
    IlAny		getHook			() const;

    virtual
    IldDbms&		setHook			(IlAny hook);

    // --------------------------
    // Immediate execution
    // --------------------------
    IldDbms&		execute			(const char* query,
						 IlInt* rowCount = 0);

    void		setClean		(void* ptr);

    // --------------------------
    // Asynchronous processing
    // --------------------------
    // To be defined for ports that implement Asynchronous processing :
    // Odbc, Oledb, Oracle, Mssql, Sybase.

    // Test wether Asynchronous management is implemented for this dbms.
    virtual
    IlBoolean		isAsyncSupported	() const;

    // Tests wether the Dbms is in asynchronous mode (IlTrue if yes).
    virtual
    IlBoolean		isAsync			() const;

    // Set asynchronous mode to IlTrue / IlFalse.
    virtual
    IldDbms&		setAsync		(IlBoolean);

    // Cancel current request.
    virtual
    IldDbms&		cancel			();

    virtual
    IlBoolean		isCompleted		() const;

};

#endif // __ILD_DBMSMODEL_H
