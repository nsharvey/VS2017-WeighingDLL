// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/tblref.h
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
// Declaration of the IliSQLTableRef class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Tblref_H
#define __Ili_Tblref_H

#ifndef __Ili_Common_H
#  include <ilviews/dataccess/common.h>
#endif

// ----------------------------------------------------------------

class ILV_DBI_EXPORTED IliSQLTableRefIpl
  : public IliRefCounted
{
public:
  IliSQLTableRefIpl (const char* tableName = 0,const char* tableOwner = 0,
		     const char* database = 0);
  IliSQLTableRefIpl (const IliSQLTableRefIpl&);
  virtual
  ~IliSQLTableRefIpl ();

  virtual
  IlBoolean isSynonym() const ;

  virtual
  void read (IL_STDPREF istream&);
  virtual
  void write (IL_STDPREF ostream&) const;

  int operator == (const IliSQLTableRefIpl&) const;

  inline const char* getTableName () const;
  inline void setTableName (const char* tableName);

  inline const char* getTableOwner () const;
  inline void setTableOwner (const char* tableOwner);

  inline const char* getDatabase () const;
  inline void setDatabase (const char* database);

  IlInt getAttributeCount() const;
  const char* getAttributeAt(IlInt idx) const;
  void appendAttribute(const char* name);

protected:
  IliString _tableName;
  IliString _tableOwner;
  IliString _database;
  IlvArray _path;
};

inline const char*
IliSQLTableRefIpl::getTableName () const {
  return _tableName;
}

inline void
IliSQLTableRefIpl::setTableName (const char* tableName) {
  _tableName = tableName;
}

inline const char*
IliSQLTableRefIpl::getTableOwner () const {
  return _tableOwner;
}

inline void
IliSQLTableRefIpl::setTableOwner (const char* tableOwner) {
  _tableOwner = tableOwner;
}

inline const char*
IliSQLTableRefIpl::getDatabase () const {
  return _database;
}

inline void
IliSQLTableRefIpl::setDatabase (const char* database) {
  _database = database;
}

class ILV_DBI_EXPORTED IliSQLSynonymRefIpl : public IliSQLTableRefIpl {
public:
  IliSQLSynonymRefIpl (const char* synName = 0, const char* synOwner = 0,
		       const char* link = 0, const char* tableName = 0,
		       const char* tableOwner = 0, const char* database = 0);
  IliSQLSynonymRefIpl (const IliSQLTableRefIpl&) ;

  virtual
  IlBoolean isSynonym() const ;

  virtual
  void read (IL_STDPREF istream&);
  virtual
  void write (IL_STDPREF ostream&) const;

  inline
  const char* getSynName() const ;
  void setSynName(const char* synName) ;
  inline
  const char* getSynOwner() const ;
  void setSynOwner(const char* synOwner) ;
  const char* getSynLink() const ;
  void setSynLink(const char* synTarget) ;

protected:
  IlString _synName ;
  IlString _synOwner ;
  IlString _synLink ;
} ;

inline const char*
IliSQLSynonymRefIpl::getSynName() const {
  return _synName ;
}

inline const char*
IliSQLSynonymRefIpl::getSynOwner() const {
  return _synOwner ;
}

inline const char*
IliSQLSynonymRefIpl::getSynLink() const {
  return _synLink ;
}


// ----------------------------------------------------------------

class ILV_DBI_EXPORTED IliSQLTableRef {
public:
  IliSQLTableRef (const char* tableName = 0,const char* tableOwner = 0,
		  const char* database = 0);
  IliSQLTableRef (const char* synName, const char* synOwner,
		  const char* link, const char* tableName,
		  const char* tableOwner, const char* database) ;
  IliSQLTableRef (const IliSQLTableRef&);
  virtual
  ~IliSQLTableRef ();

  void read (IL_STDPREF istream& input);
  void write (IL_STDPREF ostream& output) const;

  IliSQLTableRef& operator = (const IliSQLTableRef& ref);
  inline int operator == (const IliSQLTableRef& ref) const;

  inline const char* getTableName () const;
  void setTableName (const char* tableName);

  inline const char* getTableOwner () const;
  void setTableOwner (const char* tableOwner);

  inline const char* getDatabase () const;
  void setDatabase (const char* database);

  inline
  IlBoolean isSynonym() const ;
  void setSynonym(IlBoolean flag = IlTrue) ;

  inline const char* getSynName() const ;
  IlBoolean setSynName(const char* synName) ;

  inline const char* getSynOwner() const ;
  IlBoolean setSynOwner(const char* synOwner) ;

  inline const char* getSynLink() const ;
  IlBoolean setSynLink(const char* synLink) ;

protected:
  IliSQLTableRefIpl* _ipl;
  inline
  void resetRef  (IlBoolean isSynonym) ;
  virtual
  void makeSingle();
  void makeSingle(IlBoolean isSynonym);
};

inline int
IliSQLTableRef::operator == (const IliSQLTableRef& o) const {
  return (*_ipl) == (*o._ipl);
}

inline const char*
IliSQLTableRef::getTableName () const {
  return _ipl->getTableName();
}

inline const char*
IliSQLTableRef::getTableOwner () const {
  return _ipl->getTableOwner();
}

inline const char*
IliSQLTableRef::getDatabase () const {
  return _ipl->getDatabase();
}

inline IlBoolean
IliSQLTableRef::isSynonym() const {
  return _ipl->isSynonym() ;
}

inline const char*
IliSQLTableRef::getSynName() const {
  return isSynonym() ?
    IL_DYNAMICCAST(const IliSQLSynonymRefIpl*, _ipl)->getSynName() :
    0 ;
}

inline const char*
IliSQLTableRef::getSynOwner() const {
  return isSynonym() ?
    IL_DYNAMICCAST(const IliSQLSynonymRefIpl*, _ipl)->getSynOwner() :
    0 ;
}

inline const char*
IliSQLTableRef::getSynLink() const {
  return isSynonym() ?
    IL_DYNAMICCAST(const IliSQLSynonymRefIpl*, _ipl)->getSynLink() :
    0 ;
}

#endif
