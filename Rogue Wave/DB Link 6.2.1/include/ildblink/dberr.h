// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/dberr.h
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
// Error Handler class
// --------------------------------------------------------------------------
#ifndef __ILD_DBERR_H
#define __ILD_DBERR_H

#ifndef __ILD_ILDDBMS_H
#  include <ildblink/ilddbms.h>
#endif
#ifndef __ILD_ILDREQ_H
#  include <ildblink/ildreq.h>
#endif

#ifdef IL_STD
#  ifndef _IOSTREAM_
#    include <iostream>
#  endif
#else
#  ifndef _IOSTREAM_H_
#    include <iostream.h>
#  endif
#endif
#ifndef __Il_Env_H
#  include <ildblink/ilenv.h>
#endif

IL_STDUSE

class IldRelation;
class IldDbmsImp;
class IldRequestImp;

// ==========================================================================
// Interface to retrieve a message text from the code defined in file ild.h
// [section 'Internal Db Link errors and warnings']
// ==========================================================================
ILD_EXPORTEDFUNCTION(const char*)
    IldGetMessage(int code);

// ==========================================================================
// Interface to retrieve a message identifier from the code defined in file
//  ild.h [section 'Internal Db Link errors and warnings']
// ==========================================================================
ILD_EXPORTEDFUNCTION(const char*)
    IldGetMessageId(int code);

// ==========================================================================
// Interface to retrieve a function name from the code defined in file ild.h
// [section 'Db Link function Ids']
// ==========================================================================
ILD_EXPORTEDFUNCTION(const char*)
    IldGetFuncName(IldFuncId code);

// ==========================================================================
// DB Link specific SQLSTATE
// Note: class is always IL
// ==========================================================================
#define ILD_SQS_FATAL	"IL000"	/* Fatal error or memory exhausted  */
#define ILD_SQS_TYPE	"IL001"	/* Unknown datatype                 */
#define ILD_SQS_REQ	"IL002"	/* Request required                 */
#define ILD_SQS_UNKRE	"IL003"	/* Unknown table                    */
#define ILD_SQS_BDBS	"IL004"	/* Invalid connection string        */
#define ILD_SQS_BCOLN	"IL005"	/* Unknown column name              */
#define ILD_SQS_BCNT	"IL006"	/* Bad count for multiple execute   */
#define ILD_SQS_PRIV	"IL007"	/* Accessing private request        */
#define ILD_SQS_EOBJ	"IL008"	/* Using error object               */
#define ILD_SQS_BFIL	"IL009"	/* Can not create file              */
#define ILD_SQS_NREP	"IL010"	/* No error reporter                */
#define ILD_SQS_INVS	"IL011"	/* Invalid calls sequence           */
#define ILD_SQS_NOPR	"IL012"	/* No statement prepared            */
#define ILD_SQS_NOSCR   "IL013" /* Scroll mode not activated        */
#define ILD_SQS_NV   "IL014" /* Accessing a null value	        */

// ----------------------------------
// Sqlstate for informational message
// ----------------------------------
#define ILD_SQS_INFO "01000"
// ==========================================================================
// SQL92 standard SQLSTATEs
// ==========================================================================
#define ILD_SQS_ACON	"08002"
#define ILD_SQS_NCON	"08003"
#define ILD_SQS_TMSM	"22005"
#define ILD_SQS_RNGE	"21000"
#define ILD_SQS_NROW	"02000"
#define ILD_SQS_NIMP	"0A000"
#define ILD_SQS_BIND	"07009"
#define ILD_SQS_NINT	"22005" 
#define ILD_SQS_DEIP    "22023" 

// ==========================================================================
// IldErrorReporter class.
// ==========================================================================
class ILD_EXPORTED IldErrorReporter {

public:
    IldErrorReporter();
    virtual ~IldErrorReporter();

    inline void		incr		();
    inline int		decr		();
    inline
    void		setOStream	(IL_STDPREF ostream& ostr);
    inline
    IL_STDPREF ostream& getOStream	() const;
    const char*		getMessage	() const;

    IlInt		getCode		() const;

    inline
    IldDbms*		getDbms		() const;

    inline
    IldRequest*		getRequest	() const;

    inline
    IldRelation*	getRelation	() const;

    inline
    const char*		getQuery	() const;

    const char*		getConnectStr	() const;

    inline
    IlInt		getIndex	() const;

    inline
    IlInt		getSize		() const;

    const char*		getName		() const;

    // Called when exception raised by RDBM server
    virtual
    void		dbmsError	(IlInt code, 
					 const char* functionName, 
					 const char* message,
					 IldDbms* dbms,
					 IldRequest* request = 0,
					 const char* query = 0) const;

    // Called when error caught in DB Link API
    virtual
    void		dblinkError	(IlInt code,
					 const char* functionName,
					 const char* message,
					 IldDbms* dbms,
					 IldRequest* request = 0,
					 const char* query = 0,
					 IlInt index = 0,
					 const IldRelation* rel = 0) const;

    // Information action
    virtual
    void		warn		(IlInt,
					 IldFuncId,
					 const char*,
					 IldDbms* = 0,
					 IldRequest* = 0) const;

    // Error calls. WARNING : internal use only, should be private
    void		rdbmsError	(IlInt,
					 IldFuncId,
					 const char*,
					 IldDbms*,
					 const char* = 0,
					 const char* = 0);
    void		rdbmsError	(IlInt,
					 IldFuncId,
					 const char*,
					 IldRequest*,
					 const char* = 0,
					 const char* = 0);
    void		setInformation	(IlInt,
					 IldFuncId,
					 const char*,
					 IldDbms* = 0,
					 IldRequest* = 0);
    void		alreadyConnected(IldFuncId,
					 IldDbms*,
					 const char*);
    void		dbmsNotConnected(IldFuncId,
					 IldDbms*);
    void		dbmsFatalError	(IldFuncId,
					 IldDbms*,
					 const char*);
    void		unknownType	(IldFuncId,
					 IldRequest*,
					 const char*);
    // Only used with Sybase
    void		requestRequired (IldFuncId,
					 IldDbms*);
    void		typeMismatch	(IldFuncId,
					 IldRequest*,
					 IlInt);
    void		memoryExhausted (IldFuncId,
					 IldDbms* = 0,
					 IldRequest* = 0,
					 IldRelation* = 0);
    void		outOfRange	(IldFuncId,
					 IldDbms*,
					 IldRequest*,
					 IldRelation*,
					 IlInt);
    void		noMoreTuples	(IldFuncId,
					 IldRequest*);
    void		unknownRelation (IldFuncId,
					 IldDbms*,
					 const char*);
    void		notImplemented	(IldFuncId,
					 IldDbms*,
					 IldRequest*);
    void		badDbSpec	(IldFuncId,
					 IldDbms*,
					 const char*);
    void		badDbName	(IldFuncId,
					 const char*);
    void		badColumnName	(IldFuncId,
					 IldDbms*,
					 IldRequest*,
					 const char*);
    void		badColumnIndex	(IldFuncId,
					 IldDbms*,
					 IldRequest*,
					 IlInt);
    void		cannotResizeTuple(IldFuncId,
					  IldRequest*,
					  const char* = 0);
    void		badDataSize	(IldFuncId,
					 IldRequest*,
					 const char*,
					 IlInt);
    void		badCount	(IldFuncId,
					 IldRequest*,
					 IlInt);
    void		usingErrorDbms	(IldFuncId,
					 IldDbms*);
    void		usingErrorRequest(IldFuncId,
					  IldRequest*);
    void		badFile		(IldFuncId,
					 IldRequest*,
					 const char*);
    void		noReporter	(IldFuncId,
					 IldDbms* = 0,
					 IldRequest* = 0);
    void		scrollModeOff	(IldFuncId,
					 IldDbms* = 0,
					 IldRequest* = 0);
    void		invalidSequence (IldFuncId,
					 IldDbms*,
					 IldRequest* = 0);
    void		invalidParameter(IldFuncId,
					 IldDbms*,
					 IldRequest* = 0);
    void		undefLinkMode	(IldFuncId,
					 IldDbms*);
    void		nullValue	(IldFuncId,
					 IldDbms*,
					 IldRequest*);
protected:
    int			_refCount;
    IldDbms*		_dbms;
    IldRequest*   	_request;
    IldRelation*	_relation;
    const char*		_query;
    IlInt		_index;
    IlInt		_size;
    IL_STDPREF ostream*	_ostr;

    void		reset		();
    void		handler		(IlInt,
					 IldFuncId,
					 IldErrorOrigin,
					 const char*,
					 const char*,
					 const char* = 0,
					 const char* = 0) const;

private:
    void		dbmsError	(IlInt, 
					 const char*, 
					 const char*,
					 IldDbmsImp*,
					 IldRequestImp* = 0,
					 const char* = 0) const;
    void		dblinkError	(IlInt,
					 const char*,
					 const char*,
					 IldDbmsImp*,
					 IldRequestImp* = 0,
					 const char* = 0,
					 IlInt = 0,
					 const IldRelation* = 0) const;
};

// ----------------------------------------------------------------------------
// Inlines for class IldErrorReporter
// ----------------------------------------------------------------------------
inline void
IldErrorReporter::incr ()
{
    _refCount++;
}

inline int
IldErrorReporter::decr ()
{
    return --_refCount;
}

inline void
IldErrorReporter::setOStream (IL_STDPREF ostream& ostr)
{
    _ostr = &ostr;
}

inline IL_STDPREF ostream&
IldErrorReporter::getOStream () const 
{
    return *_ostr;
}

inline IldDbms*
IldErrorReporter::getDbms () const
{
    return _dbms;
}

inline IldRequest*
IldErrorReporter::getRequest () const
{
    return _request;
}

inline IldRelation*
IldErrorReporter::getRelation () const 
{
    return _relation;
}

inline const char*
IldErrorReporter::getQuery () const
{
    return _query;
}

inline IlInt
IldErrorReporter::getIndex () const
{
    return _index;
}

inline IlInt
IldErrorReporter::getSize () const
{
    return _size;
}

#endif/* __ILD_DBERR_H */
