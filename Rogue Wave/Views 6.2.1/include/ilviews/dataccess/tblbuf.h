// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/tblbuf.h
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
// Declaration of the IliTableBuffer class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Tblbuf_H
#define __Ili_Tblbuf_H

#if !defined(__Ili_Common_H)
#  include <ilviews/dataccess/common.h>
#endif
#if !defined(__Ili_Value_H)
#  include <ilviews/dataccess/value.h>
#endif
#if !defined(__Ili_Schema_H)
#  include <ilviews/dataccess/schema.h>
#endif

class ILV_INF_EXPORTED IliTable;
class ILV_INF_EXPORTED IliTableHook;

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableBuffer
: public IliRefCounted
{
public:
    inline IliTable*	getTable() const { return _table; }
    IlInt		count() const;

    IlBoolean		rowToBuffer(IlInt rowno);
    void		clear();
    void		modifyAll();
    void		modifyNone();
    IlBoolean		isModified() const;
    IlBoolean		isNull() const;
    IliValue&		at(IlInt colno);
    IliValue&		at(IliName colname);
    const IliValue&	at(IlInt colno) const;
    const IliValue&	at(IliName colname) const;
    inline IliValue& operator[](IlInt colno)
	{ return at(colno); }
    inline const IliValue& operator[](IlInt colno) const
	{ return at(colno); }
    inline IliValue& operator[](IliName colname)
	{ return at(colname); }
    inline const IliValue& operator[](IliName colname) const
	{ return at(colname); }

    void		set(const IliTableBuffer*);
    void		setAsInverseBuffer(const IliTableBuffer*,
					   const IliTableBuffer*);

    void		debug();

protected:
    IliTable*		_table;
    IliValue*		_values;
    IlInt		_count;
    IliValue		_nullValue;

    IliTableBuffer(IliTable*);
    IliTableBuffer(const IliTableBuffer&):IliRefCounted() {}
    virtual ~IliTableBuffer();

    IliTableBuffer& operator =(const IliTableBuffer&) { return *this; }

    static
    IliTableBuffer*	NewTableBuffer(IliTable*);
    virtual IlBoolean	isUsed() const = 0;
    virtual void	use() = 0;
    virtual void	unUse() = 0;
    virtual void	free() = 0;

    friend class IliTable;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableBufferPtr
{
public:
    IliTableBufferPtr(IliTable* tbl);
    ~IliTableBufferPtr();

    inline IliTableBuffer* operator->() { return _tblBuf; }

    inline IliTableBuffer* getBuffer() { return _tblBuf; }

    inline IliValue& operator[](IlInt i)
	{ return (*_tblBuf)[i]; }
    inline const IliValue& operator[](IlInt i) const
	{ return (*_tblBuf)[i]; }
    inline IliValue& operator[](IliName colname)
	{ return (*_tblBuf)[colname]; }
    inline const IliValue& operator[](IliName colname) const
	{ return (*_tblBuf)[colname]; }

private:
    IliTableBuffer*	_tblBuf;

    // forbidden
    IliTableBufferPtr(const IliTableBufferPtr&) {}

    inline const IliTableBufferPtr& operator=(const IliTableBufferPtr&)
	{ return *this; }
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliCompressedTableBuffer
{
public:
    IliCompressedTableBuffer();
    IliCompressedTableBuffer(const IliTableBuffer*);
    IliCompressedTableBuffer(const IliCompressedTableBuffer&);
    ~IliCompressedTableBuffer();

    const IliCompressedTableBuffer& operator=(const IliCompressedTableBuffer&);
    const IliCompressedTableBuffer& operator=(const IliTableBuffer*);

    void		setAsInverseBuffer(const IliTableBuffer*,
					   const IliTableBuffer*);

    void		clear();
    void		fillBuffer(IliTableBuffer*) const;

private:
    struct Entry {
	IlInt		_token;
	IlInt		_colno;
	IliValue	_value;

	Entry& operator=(const Entry& o) {
	    _token = o._token;
	    _colno = o._colno;
	    _value = o._value;
	    return *this;
	}

	void		set(const IliTableBuffer*, IlInt);
    };
    Entry*		_entries;
    IlInt		_count;
};

#endif /* !__Ili_Tblbuf_H */
