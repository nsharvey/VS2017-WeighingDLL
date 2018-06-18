// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbms/dblndbms.h
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
// Declaration of the IliDblinkDbms class
// Defined in library dbaccess
// --------------------------------------------------------------------------
#ifndef __Ili_Dblndbms_H
#define __Ili_Dblndbms_H

#ifndef __Ili_Dbmsdriv_H
#  include <ilviews/dataccess/dbms/dbmsdriv.h>
#endif

#define USE_DBLINK_CATALOG_INFO

class ILV_DBI_EXPORTED IliDblinkDbms
  : public IliDbmsDriver
{
public:
  static void GetLinkedDrivers (IlBoolean* linked);

  virtual IlBoolean isDblinkDriver() const;

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

  virtual IlBoolean getEffectiveUserName(IlAny sid,const char* userName,
					  IliString&);

  virtual IlBoolean errorRaised (IlAny sid);

  virtual void getErrorMessage (IlAny sid,IliErrorMessage& msg) const;

  virtual char** readOwners(IlAny sid, IlInt& count);

  virtual char** readAbstractTypeNames(IlAny sid,IlInt& count,
				       const char* owner = 0);
  virtual const IliDatatype* readAbstractType(IlAny sid,const char* typeName,
					      const char* owner = 0);
  virtual const IliDatatype* readAbstractType(IlAny sid,IlInt typeId);

  virtual char** readTableOwners (IlAny sid,IlInt& count,
				  const char* tableName = 0);
  virtual char** readTableNames (IlAny sid,IlInt& count,
				 const char* tableOwner = 0);
  virtual char** readTableNames (IlAny sid,IlInt& count,
				 char**& ownerNames);
  virtual char** readSynonymNames(IlAny sid, IlInt& count,
				  const char* synOwner = 0) ;
  virtual void freeNames(IlAny sid, char** names, char** ownerNames = 0);

  virtual IliSQLTableDef* readTableDefinition (IlvDisplay*,IlAny sid,
						 const char* tableName,
						 const char* tableOwner,
						 IliErrorMessage& errmsg,
					       IlBoolean isSynonym = IlFalse);

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
  virtual IlBoolean execute (IlAny sid,IlAny cid,const char* stmt,IlInt* cnt);
  virtual IlBoolean execute (IlAny sid, IlAny cid, IlInt* pcnt);
  virtual IlBoolean select (IlAny sid, IlAny cid, const char* stmt);

  virtual IlBoolean writeLongString(IlAny sid,IlAny cid,const char* data,
				    IlUInt size,const char* tabName,
				    const char* colName,
				    const char* whereCond);
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

  static const char* GetErrorMsg(IldIldBase* sOrCid);

  static void AtInit ();
  static void AtExit ();
protected:
  IliDblinkDbms (IliDbmsDriverId id,const char* name):IliDbmsDriver(id, name)
    { AtInit(); }
  IliDblinkDbms (const IliDblinkDbms& o):IliDbmsDriver(o)
    { AtInit(); }
  virtual ~IliDblinkDbms ();

  friend class IliModuleCLASS(IliDblinkDbms);
};

// --

IliModuleDECL_exp(ILV_DBI_EXPORTED,IliDblinkDbms);

#endif
