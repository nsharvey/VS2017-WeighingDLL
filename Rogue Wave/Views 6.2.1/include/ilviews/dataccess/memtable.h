// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/memtable.h
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
// Declaration of the IliMemoryTable class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Memtable_H
#define __Ili_Memtable_H

#if !defined(__Ili_Table_H)
#  include <ilviews/dataccess/table.h>
#endif

class ILV_INF_EXPORTED IliMemoryTable;

enum IliRowManagerTag {
  IliListOfRows,
  IliArrayOfRows,
  IliCustomRowManager
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliRowManager
{
 public:

    // ----------------------------------------------------------------------
    class Factory {
    public:
	Factory();
	virtual ~Factory();

	static IlInt GetFactoryCount();
	static Factory* GetFactoryAt(IlInt);
	static Factory* Find(const char*);
	static Factory* Find(IlvSymbol*);

	virtual const char* getName() const = 0;
	virtual IliRowManager* create(IliMemoryTable*) = 0;

	static void AtEnd();
    };
    // ----------------------------------------------------------------------
    IliRowManager(IliMemoryTable* owner);
    virtual ~IliRowManager();

    const char* getName() const;
    virtual Factory* getFactory() const = 0;

    inline IliMemoryTable* getOwner() const { return _owner; }

    virtual int operator==(const IliRowManager&) const;
    int operator!=(const IliRowManager&) const;

    virtual void copy(const IliRowManager&);

    virtual void write(IL_STDPREF ostream&) const;
    virtual void read(IL_STDPREF istream&);

    inline IlInt getRowsCount() const { return _rowsCount; }
    IlInt getColumnsCount() const;

    virtual void tidy();
    virtual IlBoolean isColumnNonNull(IlInt) const;

    virtual void reserve(IlInt) = 0;
    virtual void setColumnType(IlInt, const IliDatatype*) = 0;
    virtual void insertColumn(IlInt) = 0;
    virtual void deleteColumn(IlInt) = 0;
    virtual void moveColumn(IlInt, IlInt) = 0;

    virtual IlBoolean getValue(IlInt, IlInt, IliValue&) const = 0;
    virtual IlBoolean rowToBuffer(IlInt, IliTableBuffer*) const;

    virtual IlBoolean insertRow(IliRowStatus, IlInt, IliTableBuffer*,
				IlInt) = 0;
    virtual IlBoolean updateRow(IliRowStatus, IlInt, IliTableBuffer*) = 0;
    virtual IlBoolean deleteRow(IlInt) = 0;

    virtual IlBoolean doSortRows(const IlInt*, IlInt,
				  IlInt, IlInt,
				  IliCompareFunction, IlAny);

    virtual IlBoolean moveRow(IlInt, IlInt) = 0;
    virtual IlBoolean exchangeRows(IlInt, IlInt) = 0;

    virtual IlInt getRowToken(IlInt) const = 0;
    virtual IlInt getRowIndex(IlInt) const = 0;

    virtual IliRowStatus getRowStatus(IlInt) const = 0;
    virtual void setRowStatus(IlInt, IliRowStatus) = 0;

 protected:
    IliMemoryTable* _owner;
    IlInt _rowsCount;

    void setRowsCount(IlInt);
    void assignStructured(IliValue&, const IliValue&, IlInt,
			  IlInt, IlInt);
};

class ILV_INF_EXPORTED IliMemoryTable
  : public IliTable
{
public:
  IliMemoryTable(IlvDisplay* display);
  IliMemoryTable(IlvDisplay* display,
		 IlInt rowsCount,
		 const char* const* values,
		 IlInt columnsCount = 1,
		 const char* const* columnNames = 0);
  IliMemoryTable(const IliMemoryTable& tbl);
  IliMemoryTable(IlvDisplay*, IL_STDPREF istream&);

  IliDeclareDTypeInfo(IliMemoryTable);

  virtual void write(IL_STDPREF ostream& output) const;

  void writeStructure(IL_STDPREF ostream&) const;
  int operator==(const IliMemoryTable&) const;
  IliMemoryTable& operator=(const IliMemoryTable&);

  virtual void clearRows();

  virtual IlInt getRowsCount() const;

  virtual void setColumnType(IlInt, const IliDatatype*);
  virtual void setColumnMaxLength(IlInt, IlInt);
  virtual void setColumnNullable(IlInt, IlBoolean);

  virtual IlBoolean allowColumnMove() const;

  virtual IliRowStatus getRowStatus(IlInt) const;

  virtual IlBoolean rowToBuffer(IlInt, IliTableBuffer*) const;
  virtual IlBoolean getValue(IlInt, IlInt, IliValue&) const;

  virtual IlBoolean insertRow(IlInt, IliTableBuffer*);
  virtual IlBoolean updateRow(IlInt, IliTableBuffer*);
  virtual IlBoolean deleteRow(IlInt);
  virtual IlBoolean moveRow(IlInt, IlInt);
  virtual IlBoolean exchangeRows(IlInt, IlInt);

  virtual IlBoolean updateRowInCache(IlInt, IliTableBuffer*);
  virtual IlBoolean insertRowInCache(IlInt, IliTableBuffer*);
  virtual IlBoolean deleteRowInCache(IlInt);
  virtual IlBoolean moveRowInCache(IlInt, IlInt);
  virtual IlBoolean exchangeRowsInCache(IlInt, IlInt);

  virtual IlBoolean allowRowMove() const;

  virtual void doSortRows(const IlInt*, IlInt, IlInt, IlInt,
			  IliCompareFunction, IlAny);

  // Tokens - internal
  virtual IlBoolean hasRowTokens() const;

  IlBoolean areTokensPersistent() const;
  void setTokensPersistent(IlBoolean);

  virtual IlInt getRowToken(IlInt) const;
  virtual IlInt getRowIndex(IlInt) const;

  void switchTrash();
  void clearTrash();

  IliRowManagerTag getRowManagerTag() const;
  void setRowManager(IliRowManagerTag);

  const char* getRowManagerName() const;
  void setRowManager(const char*);

  void updateContext(IliValue&, IlInt, IlInt, IlInt);

protected:
  friend class IliRowManager;
  friend class IliAbstractRowCollection;
  friend class IliCacheTableHook;

  IlvSymbol* _rowManagerName;
  IlInt _nextToken;
  IlBoolean _tokenPersist;
  IliRowManager* _regularRows;
  IliRowManager* _trashRows;
  IliTableHook* _cacheHook;
  IliTable* _cache;

  IliMemoryTable(IlvDisplay* dpy, const IliClassInfo*);
  IliMemoryTable(const IliMemoryTable&, const IliClassInfo*);
  IliMemoryTable(IlvDisplay*, IL_STDPREF istream&, const IliClassInfo*);
  virtual ~IliMemoryTable();

  void createRowManagers();

  void deepCopy(const IliMemoryTable&);
  void deepCopyStructure(const IliMemoryTable&);

  void copyMemoryTable(const IliMemoryTable&);
  void readMemoryTable(IL_STDPREF istream&);

  void initMemoryTable();

  virtual IlvValueInterface* makeItf() const;

  virtual IliRowPtrIpl* getRowPtrIpl(IlInt);
  virtual IliRowPtr getRowPtrByToken(IlInt, IlInt) const;

  virtual IliTable* iGetCache() const;
  void iSetCache(IliTable*);

  virtual IlBoolean acceptUpdateRow(IlInt, IliTableBuffer*, IliTableBuffer*);
  virtual IlBoolean acceptInsertRow(IlInt, IliTableBuffer*);
  virtual IlBoolean acceptDeleteRow(IlInt, IliTableBuffer*);
  virtual IlBoolean acceptMoveRow(IlInt, IlInt);
  virtual IlBoolean acceptExchangeRows(IlInt, IlInt);

  virtual IlBoolean cancelUpdateRow(IlInt, IliTableBuffer*, IliTableBuffer*);
  virtual IlBoolean cancelInsertRow(IlInt, IliTableBuffer*);
  virtual IlBoolean cancelDeleteRow(IlInt, IliTableBuffer*, IlInt = -1);
  virtual IlBoolean cancelMoveRow(IlInt, IlInt);
  virtual IlBoolean cancelExchangeRows(IlInt, IlInt);

  virtual IlBoolean insertRowInCacheEx(IlInt, IliTableBuffer*, IlInt);

  // -- hooks

  virtual void columnChanged(IlInt);
  virtual void columnInserted(IlInt);
  virtual void columnDeleted(IlInt);
  virtual void columnMoved(IlInt, IlInt);
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliMemoryTableItf
: public IliTableItf
{
public:
  IliMemoryTableItf(IliMemoryTable* table)
  : IliTableItf(table)
  {}

  virtual IlvValue& queryValue(IlvValue&) const;
  virtual IlBoolean applyValue(const IlvValue&);
  static void GetAccessors(const IlvSymbol* const**,
			   const IlvValueTypeClass* const**,
			   IlUInt&);

  IliMemoryTable* getMemoryTable() const;

  IlvDeclarePropClassInfo();
};

// --------------------------------------------------------------------------
IliDeclareTypeInit_exp(ILV_INF_EXPORTED,IliMemoryTable);

#endif /* !__Ili_Memtable_H */
