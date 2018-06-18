// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/tbldef.h
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
// Declaration of the IliSQLTableDef class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Tbldef_H
#define __Ili_Tbldef_H

#ifndef __Ili_Schema_H
#  include <ilviews/dataccess/schema.h>
#endif

#ifndef __Ili_Tblref_H
#  include <ilviews/dataccess/tblref.h>
#endif

#ifndef __Ili_Systype_H
#  include <ilviews/dataccess/dbms/systype.h>
#endif

#ifndef __Ili_Error_H
#  include <ilviews/dataccess/error.h>
#endif

class ILV_DBI_EXPORTED IliSQLSession;

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLTableDefColumn : public IliColumn
{
public:
    IliSQLTableDefColumn();
    IliSQLTableDefColumn(const IliSQLTableDefColumn&);
    IliSQLTableDefColumn(IL_STDPREF istream&);

    IliDeclareTypeInfo(IliSQLTableDefColumn);
    virtual void	write(IL_STDPREF ostream&) const;
    int operator	==(const IliSQLTableDefColumn&) const;

    const char*		getSQLType() const { return _sqlType; }
    void		setSQLType(const char* t) { _sqlType = t; }

    IlInt		getPrecision() const { return _precision; }
    void		setPrecision(IlInt p) { _precision = p; }

    IlInt		getScale() const { return _scale; }
    void		setScale(IlInt s) { _scale = s; }

    const char*		getSQLDefaultValue() const { return _sqlDefaultValue; }
    void		setSQLDefaultValue(const char* d)
			{
			    _sqlDefaultValue = d;
			}

    const char*		getDescription() const { return _description; }
    void		setDescription(const char* d) { _description = d; }

protected:
    IliString		_sqlType;
    IlInt		_precision;
    IlInt		_scale;
    IliString		_sqlDefaultValue;
    IliString		_description;
};

IliDeclareTypeInit_exp(ILV_DBI_EXPORTED,IliSQLTableDefColumn);

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLCandidateKey : public IliCollectable
{
public:
    IliSQLCandidateKey() {}
    IliSQLCandidateKey(const IliSQLCandidateKey&);
    IliSQLCandidateKey(IL_STDPREF istream&);

    IliDeclareTypeInfo(IliSQLCandidateKey);
    void		write(IL_STDPREF ostream&) const;
    int operator	==(const IliSQLCandidateKey&) const;

    IlBoolean		contains(const IliColumn*) const;
    void		add(const IliColumn* col);
    void		remove(const IliColumn* col);
    void		sort();

    IlInt		count() const { return _columns.count(); }
    const IliColumn*	at(IlInt i) const { return _columns.at(i); }
    IliColumn*		at(IlInt i) { return _columns.at(i); }

protected:
    IliColumnCollection	_columns;
};

IliDeclareTypeInit_exp(ILV_DBI_EXPORTED,IliSQLCandidateKey);
IliDeclareCollection(DBI,IliSQLCandidateKeyCollection,IliSQLCandidateKey);

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLForeignColumn : public IliCollectable
{
public:
    IliSQLForeignColumn(const IliColumn* l, const char* f);
    IliSQLForeignColumn(const IliSQLForeignColumn&);
    IliSQLForeignColumn(IL_STDPREF istream&);

    IliDeclareTypeInfo(IliSQLForeignColumn);

    void		write(IL_STDPREF ostream&) const;
    int operator	==(const IliSQLForeignColumn&) const;

    const IliColumn*	getLocalColumn() const { return _local; }
    const char*		getForeignColumn() const { return _foreign; }

    void		setForeignColumn(const char* f) { _foreign = f; }

protected:
    const IliColumn*	_local;
    IliString		_foreign;
};

IliDeclareTypeInit_exp(ILV_DBI_EXPORTED,IliSQLForeignColumn);
IliDeclareCollection(DBI,IliSQLForeignColumnCollection,IliSQLForeignColumn);

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLForeignKey : public IliCollectable
{
public:
    IliSQLForeignKey(const IliSQLTableRef&);
    IliSQLForeignKey(const IliSQLForeignKey&);
    IliSQLForeignKey(IL_STDPREF istream&);
    ~IliSQLForeignKey() { _columns.deleteAll(); }

    IliDeclareTypeInfo(IliSQLForeignKey);

    void		write(IL_STDPREF ostream&) const;
    int operator	==(const IliSQLForeignKey&) const;

    const IliSQLTableRef& getForeignTable() const { return _foreignTable; }
    void		setForeignTable(const IliSQLTableRef& ft)
			{
			    _foreignTable = ft;
			}

    void		add(const IliColumn* col, const char*);
    void		remove(const IliColumn*);
    void		sort();

    IlBoolean		contains(const IliColumn*) const;
    const IliSQLForeignColumn* find(const IliColumn*) const;
    const char*		getForeignColumnName(const IliColumn*) const;
    IlBoolean		setForeignColumnName(const IliColumn*, const char*);

    IlInt		count() const { return _columns.count(); }
    const IliSQLForeignColumn* at(IlInt i) const { return _columns.at(i); }
    IliSQLForeignColumn* at(IlInt i) { return _columns.at(i); }

protected:
    IliSQLTableRef			_foreignTable;
    IliSQLForeignColumnCollection	_columns;
};

IliDeclareTypeInit_exp(ILV_DBI_EXPORTED,IliSQLForeignKey);
IliDeclareCollection(DBI,IliSQLForeignKeyCollection,IliSQLForeignKey);

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLTableDef : public IliSchema
{
public:
    IliSQLTableDef(IlvDisplay* display);
    IliSQLTableDef(const IliSQLTableDef&);
    IliSQLTableDef(IlvDisplay* display,IL_STDPREF istream& input);

    IliDeclareDTypeInfo(IliSQLTableDef);

    virtual void	write(IL_STDPREF ostream& output) const;

    int operator	==(const IliSQLTableDef&) const;
    IliSQLTableDef& operator =(const IliSQLTableDef&);
    const IliSQLTableRef& getTableRef() const { return _tableRef; }
    void		setTableRef(const IliSQLTableRef& ref);

    const char*		getDescription() const { return _description; }
    void		setDescription(const char* str) { _description = str; }
    IlBoolean		isAView() const { return _isAView; }
    IlBoolean		isABaseTable() const { return !_isAView; }
    void		setAsView(IlBoolean f) { _isAView = !!f; }

    virtual void	deleteEverything(IlBoolean deleteColumnsToo = IlTrue);

    // -- columns
    const char*		getColumnSQLType(IlInt colno) const;
    void		setColumnSQLType(IlInt colno, const char* type);
    IlInt		getColumnPrecision(IlInt colno) const;
    void		setColumnPrecision(IlInt colno, IlInt precision);
    IlInt		getColumnScale(IlInt colno) const;
    void		setColumnScale(IlInt colno, IlInt scale);

    const char*		getColumnSQLDefault(IlInt colno) const;
    void		setColumnSQLDefault(IlInt colno, const char* def);

    const char*		getColumnDescription(IlInt colno) const;
    void		setColumnDescription(IlInt colno, const char*);

    // -- candidate keys (other than the primary key)
    IlInt		getCandidateKeysCount() const
			{
			    return _candidateKeys.count();
			}
    void		insertCandidateKey(IlInt ckno);
    void		appendCandidateKey();
    void		removeCandidateKey(IlInt ckno);
    IlBoolean		isColumnPartOfCandidateKey(IlInt colno,
						   IlInt ckno) const;
    void		setColumnPartOfCandidateKey(IlInt colno,
						    IlInt ckno,
						    IlBoolean f);
    void		normalizeKeys();

    // -- foreign keys
    IlInt		getForeignKeysCount() const
			{
			    return _foreignKeys.count();
			}
    void		insertForeignKey(IlInt fkno,
					 const IliSQLTableRef& ref);
    void		appendForeignKey(const IliSQLTableRef& ref);
    void		removeForeignKey(IlInt fkno);
    const IliSQLTableRef& getForeignKeyTable(IlInt fkno) const;
    void		setForeignKeyTable(IlInt fkno,
					   const IliSQLTableRef& ref);
    IlBoolean		isColumnPartOfForeignKey(IlInt colno,
						 IlInt fkno) const;
    void		setColumnPartOfForeignKey(IlInt colno,
						  IlInt fkno,
						  IlBoolean f);
    const char*		getColumnForeignColumn(IlInt colno, IlInt fkno) const;
    void		setColumnForeignColumn(IlInt colno,
					       IlInt fkno,
					       const char* name);

    // -- SQL

    IlBoolean		isValid(IliSQLSession*, IliErrorMessage& errMsg) const;
    IlInt		getCreateStatementsCount(IliSQLSession* session) const;
    IlBoolean		makeCreateStatement(IliSQLSession* session,
					    IlInt index,
					    IliString& stmt,
					    IliErrorMessage& msg) const;

    // -- external hooks

    virtual IlBoolean	foreignTableRenamed(const IliSQLTableRef&,
					    const IliSQLTableRef&);
    virtual IlBoolean	foreignTableDeleted(const IliSQLTableRef&);
    virtual IlBoolean	foreignColumnRenamed(const IliSQLTableRef&,
					     const char*,
					     const char*);
    virtual IlBoolean	foreignColumnDeleted(const IliSQLTableRef&,
					     const char*);

    IlInt		getToken() const;
    void		setToken(IlInt);

    IlBoolean		hasRect() const;
    const IlvRect&	getRect() const;
    void		setRect(const IlvRect&);
    void		clearRect();

protected:
    IliSQLTableRef			_tableRef;
    IliSQLCandidateKeyCollection	_candidateKeys;
    IliSQLForeignKeyCollection		_foreignKeys;
    IliString				_description;
    IlBoolean				_isAView;
    IlInt				_token;
    IlvRect				_rect;

    IliSQLTableDef(IlvDisplay*, const IliClassInfo*);
    IliSQLTableDef(const IliSQLTableDef&, const IliClassInfo*);
    IliSQLTableDef(IlvDisplay*,IL_STDPREF istream&, const IliClassInfo*);
    virtual ~IliSQLTableDef();

    void		deepCopy(const IliSQLTableDef&);

    void		readSQLTableDef(IL_STDPREF istream& is);
    void		copySQLTableDef(const IliSQLTableDef&);

    virtual IliColumn*	newColumn();

    IlBoolean		getSQLType(IliSQLSession*,
				   IliSQLTableDefColumn* col,
				   IliSQLSystemType&) const;
    IlBoolean		makeFirstCreateStatement(IliSQLSession* session,
						 IliString& stmt,
						 IliErrorMessage& msg) const;

    virtual void	columnToBeDeleted(IlInt colno);

    static const IliSQLTableDef* topTableDef();

    friend class IliSQLSession;
    friend class IliSQLCandidateKey;
    friend class IliSQLForeignColumn;
};

IliDeclareTypeInit_exp(ILV_DBI_EXPORTED,IliSQLTableDef);

IliDeclareCollection(DBI,IliSQLTableDefCollection,IliSQLTableDef);

// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLCatalog
{
public:
    IliSQLCatalog(IlvDisplay* display);
    IliSQLCatalog(const IliSQLCatalog&);
    ~IliSQLCatalog();
    IlvDisplay*		getDisplay() const { return _display; }

    IliSQLCatalog& operator =(const IliSQLCatalog&);
    int operator	==(const IliSQLCatalog&) const;
    void		read(IL_STDPREF istream& input);
    void		write(IL_STDPREF ostream& output) const;
    IlInt		getTableDefsCount() const { return _tables.count(); }
    const IliSQLTableDef* getTableDef(IlInt p) const { return _tables.at(p); }
    IliSQLTableDef*	getTableDef(IlInt p) { return _tables.at(p); }
    IlInt		getTableDefIndex(const IliSQLTableRef& ref) const;
    IlInt		getTableDefIndex(const IliSQLTableDef* tdef) const;
    const IliSQLTableDef* getTableDef(const IliSQLTableRef& ref) const;
    IliSQLTableDef*	getTableDef(const IliSQLTableRef& ref);
    IlBoolean		insertTableDef(IlInt pos, IliSQLTableDef* def);
    IlInt		appendTableDef(IliSQLTableDef* def);
    void		removeTableDef(IlInt index,
				       IlBoolean deleteIt = IlTrue);
    void		deleteAll();

protected:
    IlvDisplay*			_display;
    IliSQLTableDefCollection	_tables;
};

#endif





