// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/sqltblex.h
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
// Declaration of miscellaneous classes used by class IliSQLTable
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Sqltblex_H
#define __Ili_Sqltblex_H

#ifndef __Ili_Sqlbind_H
#  include <ilviews/dataccess/dbms/sqlbind.h>
#endif

class IliOuterJoinDesc;
class ILV_DBI_EXPORTED IliSQLTable;
class ILV_DBI_EXPORTED IliSQLTableAlias;

// --

class ILV_DBI_EXPORTED IliSQLTableColumn : public IliTableColumn
{
public:
  IliSQLTableColumn ();
  IliSQLTableColumn (const IliSQLTableColumn&);
  IliSQLTableColumn (IL_STDPREF istream&);

  IliDeclareTypeInfo(IliSQLTableColumn);
  virtual void write (IL_STDPREF ostream&) const;
  int operator == (const IliSQLTableColumn&) const;

  const char* getSQLText () const { return _sqltext; }
  void setSQLText (const char* t);

  IliSQLOrderByType getOrderBy () const { return _orderBy; }
  void setOrderBy (IliSQLOrderByType ob) { _orderBy = ob; }

  IliSQLOperation getOperation () const { return _operation; }
  void setOperation (IliSQLOperation op) { _operation = op; }

  IlBoolean isFetched () const { return !!_isFetched; }
  void setFetched (IlBoolean f) { _isFetched = !!f; }

  IliSQLTableAlias* getTableAlias () const { return _tableAlias; }
  void setTableAlias (IliSQLTableAlias* a) { _tableAlias = a; }

  IlBoolean isApart () const { return !!_isApart; }
  void setApart (IlBoolean ap) { _isApart = !!ap; }

  IlInt getDesignWidth () const { return _designWidth; }
  void setDesignWidth (IlInt w) { _designWidth = w; }

  IlBoolean isNameFixed () const { return !!_isNameFixed; }
  void fixName (IlBoolean f) { _isNameFixed = !!f; }

  IlBoolean hasDot() const { return !!_hasDot; }

protected:
  IliString _sqltext;
  IliSQLOrderByType _orderBy;
  IliSQLOperation _operation;
  IliSQLTableAlias* _tableAlias;
  IlBoolean _isFetched;
  IlBoolean _isApart;
  IlBoolean _isNameFixed;
  IlBoolean _hasDot;
  IlInt _designWidth;
};

IliDeclareTypeInit_exp(ILV_DBI_EXPORTED,IliSQLTableColumn);

// --

class ILV_DBI_EXPORTED IliSQLColumnFilter
{
public:
  virtual IlBoolean isNull() const = 0;
  virtual IlBoolean matches(const IliSQLTable*,const IliSQLTableColumn*,
			    const IliTableBuffer*) const = 0;
};

// --

class ILV_DBI_EXPORTED IliSQLTablePtr : public IliTablePtr
{
public:
  IliSQLTablePtr();
  IliSQLTablePtr(const IliSQLTablePtr&);

  IliSQLTablePtr& operator = (const IliSQLTablePtr&);

  const IliSQLTable* getSQLTable() const;
  IliSQLTable* getSQLTable();

protected:
  IliSQLTablePtr(const IliTablePtr&);

  friend class IliSQLTable;
};

// --

class ILV_DBI_EXPORTED IliSQLTableAlias : public IliCollectable
{
public:
  IliSQLTableAlias (IlInt token);
  IliSQLTableAlias (const IliSQLTableAlias&);
  IliSQLTableAlias (IL_STDPREF istream&);

  IliDeclareTypeInfo(IliSQLTableAlias);
  void write (IL_STDPREF ostream&) const;
  int operator == (const IliSQLTableAlias&) const;

  const IliSQLTableRef& getTableRef () const { return _tblRef; }
  void setTableRef (const IliSQLTableRef& tblRef) { _tblRef = tblRef; }

  const char* getAlias () const { return _alias; }
  void setAlias (const char* alias) { _alias = alias; }

  IlInt getAliasNo () const { return _aliasNo; }
  void setAliasNo (IlInt no) { _aliasNo = no; }

  IlInt getToken () const { return _token; }
  void setToken (IlInt t) { _token = t; }

  IlvRect getRect () const { return _rect; }
  void setRect (const IlvRect& r) { _rect = r; }

  IlBoolean isUpdatable() const { return _isUpdatable; }
  void setUpdatable(IlBoolean u) { _isUpdatable = !!u; }

  IlBoolean hasParentTableAlias() const;

  const char* getParentDataSourceName() const { return _parentDSName; }
  void setParentDataSourceName(const char* name) { _parentDSName = name; }

  IliSQLTable* getParentSQLTable() const;
  void setParentSQLTable(IliSQLTable* sqlTbl);

  const char* getParentTableAlias() const { return _parentTableAlias; }
  void setParentTableAlias(const char* name) { _parentTableAlias = name; }
  IlInt getParentTableIndex(IliSQLTable* parentTable) const;
  IlInt getParentTableIndex(IlvGraphicHolder* holder) const;

  const IliRowPtr& getParentRow() const { return _parentRow; }
  void setParentRow(const IliRowPtr& row) { _parentRow = row; }

  const IliAttributePath& getParentPath() const { return _parentPath; }
  void setParentPath(const IliAttributePath& path) { _parentPath = path; }

  IlInt getParentColumnIndex(IliSQLTable* parentTable) const;

  IliSQLTable* getEffectiveParentSQLTable(IlvGraphicHolder*) const;
  IliRowPtr getEffectiveParentRow(IlvGraphicHolder*) const;

protected:
  IliSQLTableRef _tblRef;
  IliString _alias;
  IlInt _aliasNo;
  IlInt _token;
  IlvRect _rect;
  IlBoolean _isUpdatable;
  IliString _parentDSName;
  IliSQLTablePtr _parent;
  IliString _parentTableAlias;
  IlInt _parentTableIndex;
  IliRowPtr _parentRow;
  IliAttributePath _parentPath;
  IlInt _parentColumnIndex;
};

IliDeclareTypeInit_exp(ILV_DBI_EXPORTED,IliSQLTableAlias);
IliDeclareCollection(DBI,IliSQLTableAliasCollection,IliSQLTableAlias);

// --

class ILV_DBI_EXPORTED IliFromClause
  : public IliSQLTableAliasCollection {
public:
  IliFromClause () {}
  ~IliFromClause ();
  IliFromClause& operator = (const IliFromClause&);

  IlInt addTable (const IliSQLTableRef&, IlInt token);
  IlBoolean removeTable (IlInt tblno);

  const IliSQLTableRef& getTableRef (IlInt tblno) const;
  void setTableRef (IlInt tblno, const IliSQLTableRef&);

  IlBoolean isTableRefUpdatable (IlInt tblno) const;
  void setTableRefUpdatable (IlInt tblno, IlBoolean f);

  const char* getTableAlias (IlInt tblno) const;

protected:
  void normalize ();
};

// --

class ILV_DBI_EXPORTED IliSQLConditionTerm : public IliCollectable 
{
public:
  IliSQLConditionTerm (IliSQLTableColumn*, const char*);
  IliSQLConditionTerm (const IliSQLConditionTerm&);
  IliSQLConditionTerm (IL_STDPREF istream&);

  IliDeclareTypeInfo(IliSQLConditionTerm);
  void write (IL_STDPREF ostream&) const;
  int operator == (const IliSQLConditionTerm&) const;

  IliSQLTableColumn* _column;
  IliString _rhs;
};

IliDeclareTypeInit_exp(ILV_DBI_EXPORTED,IliSQLConditionTerm);
IliDeclareCollection(DBI,IliSQLConditionTermCollection,IliSQLConditionTerm);

// --

class ILV_DBI_EXPORTED IliSQLConditionList : public IliCollectable 
{
public:
  IliSQLConditionList () {}
  IliSQLConditionList (const IliSQLConditionList&);
  IliSQLConditionList (IL_STDPREF istream&);
  ~IliSQLConditionList ();

  IliDeclareTypeInfo(IliSQLConditionList);
  void write (IL_STDPREF ostream&) const;
  int operator == (const IliSQLConditionList&) const;

  IlInt count () const { return terms.count(); }
  const IliSQLConditionTerm* at (IlInt i) const { return terms.at(i); }
  IliSQLConditionTerm* at (IlInt i) { return terms.at(i); }
  const IliSQLConditionTerm* at (const IliColumn*) const;
  IliSQLConditionTerm* at (IliColumn*);
  void append (IliSQLConditionTerm* t) { terms.append(t); }
  void remove (IliSQLConditionTerm* t) { terms.deleteItem(t); }

  void emit (IliSQLStmtBuf&,const IliSQLTable*,IlBoolean op) const;
  void columnLost (IliColumn*);

  IlBoolean isNull () const;

  IliSQLConditionTermCollection terms;
};

IliDeclareTypeInit_exp(ILV_DBI_EXPORTED,IliSQLConditionList);
IliDeclareCollection(DBI,IliSQLConditionListCollection,IliSQLConditionList);

// --

class ILV_DBI_EXPORTED IliSQLCondition
  : public IliSQLConditionListCollection {
public:
  IliSQLCondition () {}
  ~IliSQLCondition ();

  IliSQLCondition& operator = (const IliSQLCondition&);

  void emit (IliSQLStmtBuf&,const IliSQLTable*, IlBoolean op) const;
  void columnLost (IliColumn*);

  IlInt nonNullCount () const;
};

// --

class ILV_DBI_EXPORTED IliSQLQueryJoin : public IliCollectable 
{
public:
  IliSQLQueryJoin ();
  IliSQLQueryJoin (const IliSQLQueryJoin&);
  IliSQLQueryJoin (IL_STDPREF istream&);

  IliDeclareTypeInfo(IliSQLQueryJoin);
  void write (IL_STDPREF ostream&) const;
  int operator == (const IliSQLQueryJoin&) const;

  void emit (const IliSQLSession*, IliSQLStmtBuf&) const;

  IlInt _token;
  IliSQLJoinType _type;
  IliSQLTableAlias* _tableAlias1;
  IliAttributePath _colName1;
  IliSQLTableAlias* _tableAlias2;
  IliAttributePath _colName2;
};

// ----------------------------------------------------------------

IliDeclareTypeInit_exp(ILV_DBI_EXPORTED,IliSQLQueryJoin);
IliDeclareCollection(DBI,IliSQLQueryJoinCollection,IliSQLQueryJoin);

#endif
