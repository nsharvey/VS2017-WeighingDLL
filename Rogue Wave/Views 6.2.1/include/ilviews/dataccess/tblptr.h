// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/tblptr.h
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
// Declaration of the IliTablePtr, IliRowPtr and IliCellPtr classes
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Tblptr_H
#define __Ili_Tblptr_H

#if !defined(__Ili_Table_H)
#  include <ilviews/dataccess/table.h>
#endif

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTablePtr
: public IliSchemaPtr
{
public:
    IliTablePtr();
    IliTablePtr(const IliTablePtr&);

    IliTablePtr& operator=(const IliTablePtr&);

    inline const IliTable* getTable() const;
    inline IliTable* getTable();
protected:
    IliTablePtr(const IliSchemaPtr&);

    friend class IliTable;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliRowPtrIpl
: public IliCollectable
{
public:
    inline const IliTable* getTable() const {
	return _tablePtr.getTable();
    }
    inline IliTable* getTable() {
	return _tablePtr.getTable();
    }

    virtual IlInt getRowIndex() const = 0;

    virtual void lock() = 0;
    virtual void unLock() = 0;

protected:
    IliTablePtr _tablePtr;

    IliRowPtrIpl(IliTable* table);

    friend class IliTable;
    friend class IliRowPtr;
};
IliDeclareCollection(INF,IliRowPtrIplCollection,IliRowPtrIpl);

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliRowPtr
{
public:
    IliRowPtr();
    IliRowPtr(const IliRowPtr&);
    ~IliRowPtr();
    IliRowPtr& operator=(const IliRowPtr& ptr);
    inline IliTable* getTable() const {
	return (_ipl ? _ipl->getTable() : NULL);
    }
    inline IlInt getRowIndex() const {
	return _ipl ? _ipl->getRowIndex() : -1;
    }

private:
    IliRowPtrIpl* _ipl;

    IliRowPtr(IliRowPtrIpl*);

    friend class IliTable;
    friend class IliRowPtrIpl;
};

// ---------------------------------------------------------------------
class ILV_INF_EXPORTED IliCellPtr
{
public:
    IliCellPtr();
    IliCellPtr(const IliTable*, const IliRowPtr&, IlInt);
    IliCellPtr(const IliTable*, IlInt, IlInt);
    IliCellPtr(const IliCellPtr&);
    ~IliCellPtr();

    IliCellPtr& operator=(const IliCellPtr&);

    IlBoolean isDefined() const;

    inline IliTable* getTable() const {
	return _rowPtr.getTable();
    }
    inline IlInt getRowIndex() const {
	return _rowPtr.getRowIndex();
    }
    IlInt getColumnIndex() const;

private:
    IliRowPtr _rowPtr;
    IlInt _columnToken;
    IlInt _columnIndex;
};

#endif /* !__Ili_Tblptr_H */
