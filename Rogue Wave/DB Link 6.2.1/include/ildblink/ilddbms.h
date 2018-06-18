// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ilddbms.h
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
// Db Link Connection class
// ----------------------------------------------------------------------------
#ifndef __ILD_ILDDBMS_H
#define __ILD_ILDDBMS_H

#ifndef __Il_Array_H
# include <ilog/array.h>
#endif

#ifndef __ILD_ILDCONST_H
# include <ildblink/ildconst.h>
#endif
#ifndef __ILD_ILDBASE_H
# include <ildblink/ildbase.h>
#endif
#ifndef __ILD_ILDREL_H
# include <ildblink/ildrel.h>
#endif
#ifndef __ILD_ILDTYPE_H
# include <ildblink/ildtype.h>
#endif

typedef void (*IldNotifFunction)(IlAny);

class IldSchemaEntity;
class IldRelation;
class IldCallable;
class IldSynonym;
class IldADTDescriptor;
class IldRequest;
class IldDriver;

// ============================================================================
// IldDbms class.
// ============================================================================
class ILD_EXPORTED IldDbms : public virtual IldIldBase {

public:
    virtual
    ~IldDbms		() {};

    virtual
    IlBoolean		isDbms			() const
    { return IlTrue; }

    // ---------------------------
    // Readers
    // ---------------------------
    virtual
    IlInt	getNumberOfActiveConnections	() const = 0;

    virtual
    const char*		getName			() const = 0;

    virtual
    const char*		getUser			() const = 0;

    virtual
    const char*		getDbmsVersions		() = 0;

    virtual
    IlUInt		getDbmsVersion		() = 0;

    virtual
    const char*		getDatabase		() const = 0;

    virtual
    const char*		getDbmsServer		() const = 0;

    virtual
    IldDbms&		getInfo			(IldInfoItem info,
						 IlInt* intVal,
						 char* charVal) = 0;

    virtual
    IlBoolean		isReadOnlyCapable	() const = 0;

    virtual
    IlBoolean		isScrollableCapable	() const = 0;

    // ---------------------------
    // Connection control
    // ---------------------------
    virtual
    IldDbms&		connect			(const char* cString) = 0;

    virtual
    IldDbms&		connect			(const char* database,
						 const char* userName,
						 const char* password) = 0;

    virtual
    IldDbms&		disconnect		() = 0;

    virtual
    IlBoolean		isConnected		() const = 0;

    // ---------------------------
    // Transaction control
    // ---------------------------
    virtual
    IlBoolean		isTransactionEnabled	() = 0;

    virtual
    IldDbms&		setTransactionReadOnly	(IlBoolean f = IlTrue) = 0;

    virtual
    IlBoolean		isTransactionReadOnly	() const = 0;

    virtual
    IldDbms&		startTransaction	(IldRequest* r = 0,
						 const char* tN = 0) = 0;

    virtual
    IldDbms&		commit			(IldRequest* r = 0,
						 const char* tN = 0) = 0;

    virtual
    IldDbms&		rollback		(IldRequest* r = 0,
						 const char* tN = 0) = 0;

    virtual
    IldDbms&		autoCommitOn		(IldRequest* r = 0,
						 const char* tN = 0) = 0;

    virtual
    IldDbms&		autoCommitOff		(IldRequest* r = 0,
						 const char* tN = 0) = 0;

    // ---------------------------
    // Schema accesses
    // ---------------------------
    virtual
    char**		readOwners		() = 0;

    virtual
    IldRelation*	readRelation		(const char* relName,
						 const char* owner = 0) = 0;

    virtual
    IldRelation*	readRelation		(IlInt relId) = 0;

    virtual
    IldCallable*	readProcedure		(const char* procName,
						 const char* owner = 0) = 0;

    virtual
    IldCallable*	readProcedure		(IlInt procId) = 0;

    virtual
    IldADTDescriptor*	readAbstractType	(const char* typeName,
						 const char* owner = 0) = 0;

    virtual
    IldADTDescriptor*	readAbstractType	(IlInt typeId) = 0;

    virtual
    IldSynonym*		readSynonym		(const char* synName,
						 const char* own = 0) = 0;

    virtual
    IldSynonym*		readSynonym		(IlInt synId) = 0;

    virtual
    char**		readRelationOwners	(const char* rN = 0) = 0;

    virtual
    IldRequest*		readEntityNames		(IldEntityType entType,
						 const char* owner = 0) = 0;

    virtual
    char**		readRelationNames	(char**& owners) = 0;

    virtual
    char**		readRelationNames	(const char* owner = 0) = 0;

    virtual            
    char**		readProcedureNames	(const char* owner = 0) = 0;

    virtual
    char**		readSynonymNames	(const char* owner = 0) = 0;

    virtual
    char**		readAbstractTypeNames	(const char* owner = 0) = 0;

    virtual
    IldDbms&		freeNames		(char** names,
						 char** owners = 0) = 0;

    virtual
    void		removeRelation		(IldRelation* rel) = 0;

    virtual
    void		removeEntity		(IldSchemaEntity* ent) = 0;

    virtual
    IlUInt		getNumberOfEntities	() = 0;
    #define getNumberOfRelations getNumberOfEntities
    virtual
    IldRelation*	getRelation		(const char* relName,
						 const char* owner = 0) = 0;

    virtual
    IldRelation*	getRelation		(IlInt relId) = 0;

    virtual
    IldCallable*	getProcedure		(const char* procName,
						 const char* owner = 0) = 0;

    virtual
    IldCallable*	getProcedure		(IlInt procId) = 0;

    virtual
    IldSynonym*		getSynonym		(const char* synName,
						 const char* owner = 0) = 0;

    virtual
    IldSynonym*		getSynonym		(IlInt synId) = 0;

    virtual
    IldADTDescriptor*	getAbstractType		(const char* typeName,
						 const char* owner = 0) = 0;

    virtual
    IldADTDescriptor*	getAbstractType		(IlInt typeId) = 0;

    virtual
    void		freeEntity		(IldSchemaEntity* ent) = 0;

    virtual
    const IldSQLType**	getTypeInfo		(short cTy = IldSQLAllTypes)
	= 0;

    virtual
    void		freeTypeInfo		(const IldSQLType** types) = 0;

    // ----------------------
    // Table keys description
    // ----------------------
    virtual
    IldDbms&		readPrimaryKey		(IldRelation* rel) = 0;

    virtual
    IldDbms&		readForeignKeys		(IldRelation* rel) = 0;

    virtual
    IldDbms&		readIndexes		(IldRelation* rel) = 0;

    virtual
    IldDbms&		readSpecialColumns	(IldRelation* rel) = 0;

    virtual
    IldRequest*		readTablePrivileges	(const char* catalog,
						 const char* schema,
						 const char* table) = 0;

    // -----------------
    // Notification API
    // -----------------
    virtual
    IldDbms&		subscribeEvent		(const char* name,
						 IldNotifFunction usrCB,
						 IlAny usrData) = 0;

    virtual
    IldDbms&		unSubscribeEvent	(const char* name) = 0;

    // ---------------------------
    // Interfaces to request objects
    // ---------------------------
    virtual
    IldRequest*		getFreeRequest		() = 0;

    virtual
    IlUInt		getNumberOfRequests	() const = 0;

    // ---------------------------
    // Session configuration
    // ---------------------------
    virtual
    IldDbms&		setDefaultColArraySize	(IlUInt size) = 0;

    virtual
    IlUInt		getDefaultColArraySize	() const = 0;

    virtual
    IldDbms&           setDefaultParamArraySize (IlUInt size) = 0;

    virtual
    IlUInt		getDefaultParamArraySize () const = 0;

    virtual
    IldDbms&		setTimeOut		(short secs) = 0;

    // ---------------------------
    // Error handler
    // ---------------------------
    virtual 
    IldErrorReporter*	getErrorReporter	() const = 0;

    virtual
    IldDbms&		setErrorReporter	(IldErrorReporter* r) = 0;

    // --------------------
    // Extension purpose
    // --------------------
    virtual
    IlAny		getHook			() const = 0;

    virtual
    IldDbms&		setHook			(IlAny hook) = 0;

    // --------------------------
    // Immediate execution
    // --------------------------
    virtual
    IldDbms&		execute			(const char* query,
						 IlInt* rowCount = 0) = 0;
    virtual
    void		setClean		(void* ptr) = 0;

    // -------------------------
    // Asynchronous processing
    // -------------------------
    // To be defined for ports that implement asynchronous processing :
    // DB2, Odbc, Oledb, Oracle, Mssql, Sybase.

    virtual
    IlBoolean		isAsyncSupported	() const = 0;

    virtual
    IlBoolean		isAsync			() const = 0;

    virtual
    IldDbms&		setAsync		(IlBoolean flag) = 0;

    virtual
    IldDbms&		cancel			() = 0;

    virtual
    IlBoolean		isCompleted		() const = 0;

protected:
    IldDbms()
	: IldIldBase()
    {};
};

#endif // __ILD_ILDDBMS_H
