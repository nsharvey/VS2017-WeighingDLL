// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbms/sqlbind.h
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
// Declaration of the IliDbmsDriver class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Sqlbind_H
#define __Ili_Sqlbind_H

#if !defined(__Ilv_Base_Array_H)
# include <ilviews/base/array.h>
#endif
#if !defined( __Ili_Common_H)
# include <ilviews/dataccess/common.h>
#endif

#if defined(IL_STD)
# include <cstring>
#else  /* !IL_STD */
# include <string.h>
#endif /* !IL_STD */

class ILV_DBI_EXPORTED IliSQLTable;
class ILV_INF_EXPORTED IliTableBuffer;

static IlInt IliIntStack_Dummy = 0;
// --------------------------------------------------------------------------
// IliIntStack
// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliIntStack
{
public:
    inline IliIntStack() { init(); }
    inline IliIntStack(const IliIntStack& o) { init(); operator = (o); }
    inline ~IliIntStack() { delete [] _array; }

    
    inline IlInt	getCount() const { return _count; }
    inline IlInt	getCapacity() const { return _capacity; }
    void		reserve(IlInt);

    inline void		push(IlInt anInt)
			{
			    reserve(_count + 1);
			    _array[_count++] = anInt;
			}
    inline IlInt	pop()
			{
			    return ((_count > 0)
				    ? _array[--_count]
				    : (IlInt)0);
			}

    inline const IlInt&	top() const	{ return operator [](getCount() - 1); }
    inline IlInt&	top()		{ return operator [](getCount() - 1); }

    inline void		empty()		{ _count = 0; }

    IliIntStack& operator = (const IliIntStack&);
    inline
    const IlInt& operator [](IlInt idx) const
			{
			    return (((idx >= 0) && (idx < _count))
				    ? _array[idx]
				    : IliIntStack_Dummy);
			}
    inline
    IlInt& operator	[](IlInt idx)
			{
			    return (((idx >= 0) && (idx < _count))
				    ? _array[idx]
				    : IliIntStack_Dummy);
			}

private:
    IlInt*		_array;
    IlInt		_count;
    IlInt		_capacity;

    inline void		init() { _array = NULL; _count = 0; _capacity = 0; }
};

// --------------------------------------------------------------------------
// IliBindInfo
// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliBindInfo : public IliCollectable
{
public:
    inline IliBindInfo()
	: _sqlTable(NULL),
	  _colno(-1),
	  _isCondition(IlTrue),
	  _tblBuf(NULL)
    {
    }

    inline IliBindInfo(const IliSQLTable* sqlTable,
		       IlInt colno,
		       const char* paramName,
		       IlBoolean isCondition,
		       const IliTableBuffer* tblBuf)
	: _sqlTable(sqlTable),
	  _colno(colno),
	  _paramName(paramName),
	  _isCondition(isCondition),
	  _tblBuf(tblBuf)
    {
    }

    inline IliBindInfo(const IliBindInfo& o) { operator = (o); }

    inline const IliSQLTable*	getSQLTable() const { return _sqlTable; }
    inline IlInt		getColumnIndex() const { return _colno; }
    inline const char*		getParamName() const { return _paramName; }
    inline IlBoolean		isCondition() const { return _isCondition; }
    inline
    const IliTableBuffer*	getTableBuffer() const { return _tblBuf; }

    IliBindInfo& operator	=(const IliBindInfo&);

private:
    const IliSQLTable*		_sqlTable;
    IlInt			_colno;
    IliString			_paramName;
    IlBoolean			_isCondition;
    const IliTableBuffer*	_tblBuf;
};

IliDeclareCollection(DBI,IliBindInfoCollection,IliBindInfo);

// --------------------------------------------------------------------------
// IliBindInfoEnumIpl
// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliBindInfoEnumIpl
{
public:
    IliBindInfoEnumIpl() {}
    virtual ~IliBindInfoEnumIpl();
    virtual IliBindInfoEnumIpl*	copy() const = 0;
    virtual IlBoolean		getNext(IliBindInfo&) = 0;
    virtual IlInt		getIndex() const = 0;
};

// --------------------------------------------------------------------------
// IliBindInfoEnum
// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliBindInfoEnum
{
public:
    inline IliBindInfoEnum(IliBindInfoEnumIpl* ipl) { _ipl = ipl; }
    inline IliBindInfoEnum(const IliBindInfoEnum& o) { _ipl = o._ipl->copy(); }
    inline ~IliBindInfoEnum() { delete _ipl; }

    inline IlBoolean	getNext(IliBindInfo& bi) { return _ipl->getNext(bi); }
    inline IlInt	getIndex() const { return _ipl->getIndex(); }

    IliBindInfoEnum& operator =(const IliBindInfoEnum&);

private:
    IliBindInfoEnumIpl* _ipl;
};

// --------------------------------------------------------------------------
// IliSQLStmtBuf
// --------------------------------------------------------------------------
class ILV_DBI_EXPORTED IliSQLStmtBuf
{
public:
    inline IliSQLStmtBuf()
	: _bindMandatory(IlFalse),
	  _lastTextEnd(0),
	  _lastTextPos(0),
	  _nextCondVarno(1),
	  _nextValueVarno(1)
    {
	_indentStack.push(0);
    }

    inline ~IliSQLStmtBuf() { _allBindInfo.deleteAll(); }

    inline IlBoolean	isNull() const { return _stmt.isNull(); }
    void		nullify();

    inline
    const IliString&	getStmt() const { return _stmt; }
    inline IliString&	getStmt() { return _stmt; }

    inline
    const IliBindInfoCollection& getBindInfo() const { return _allBindInfo; }
    inline
    IliBindInfoCollection& getBindInfo() { return _allBindInfo; }
    IliBindInfoEnum	getBindInfoEnum() const;

    inline IlBoolean	isBindMandatory() const { return _bindMandatory; }
    IlBoolean		setBindMandatory(IlBoolean f);

    IlInt		getTextPos() const;
    inline void		pushTextPos() { _indentStack.push(getTextPos()); }
    inline void		popTextPos() { _indentStack.pop(); }
    inline void		addToIndent(IlInt d) { _indentStack.top() += d; }
    inline IlInt	getIndent() const { return _indentStack.top(); }
    inline void		setIndent(IlInt v) { _indentStack.top() = v; }

    void		NewLineIndent();

    inline
    IliSQLStmtBuf& operator	=(const char* str)
				{
				    _stmt = str;
				    return *this;
				}

    inline
    IliSQLStmtBuf& operator	<<(char c) { _stmt << c; return *this; }
    inline
    IliSQLStmtBuf& operator	<<(int i) { _stmt << i; return *this; }

    inline
    IliSQLStmtBuf& operator	<<(unsigned u) { _stmt << u; return *this; }
    inline
    IliSQLStmtBuf& operator	<<(long l) { _stmt << l; return *this; }
    inline
    IliSQLStmtBuf& operator	<<(unsigned long ul)
				{
				    _stmt << ul;
				    return *this;
				}

    inline
    IliSQLStmtBuf& operator	<<(double d) { _stmt << d; return *this; }

    inline
    IliSQLStmtBuf& operator	<<(const char* str)
				{
				    _stmt << str;
				    return *this;
				}

    inline
    IliSQLStmtBuf& operator	<<(const IliString& s)
				{
				    _stmt << s;
				    return *this;
				}

    inline
    IliSQLStmtBuf& operator	<<(IliSQLStmtBuf& (*manip)(IliSQLStmtBuf&))
				{
				    return manip(*this);
				}


    void		addConditionParam(const IliSQLTable* sqlTbl,
					  IlInt colno,
					  const IliTableBuffer* tblBuf);
    void		addValueParam(const IliSQLTable* sqlTbl,
				      IlInt colno,
				      const IliTableBuffer* tblBuf);

    enum Type {
	None,
	Select,
	Insert,
	Update,
	Delete,
	OtherDDL,
	DML
    };

    Type		getType() const;
    void		setType(Type type);

    const IliTableBuffer* getValueTableBuffer() const;
    void		setValueTableBuffer(const IliTableBuffer*);

    const IliTableBuffer* getConditionTableBuffer() const;
    void		setConditionTableBuffer(const IliTableBuffer*);

    void		push();
    void		pop();

private:
    IliBindInfoCollection	_allBindInfo;
    IliString			_stmt;
    IlBoolean			_bindMandatory;
    IliString			_tmpBuf;
    IliIntStack			_typeStack;
    IlvArray			_valueTableBufferStack;
    IlvArray			_conditionTableBufferStack;
    IliIntStack			_indentStack;
    IlInt			_lastTextEnd;
    IlInt			_lastTextPos;
    IlInt			_nextCondVarno;
    IlInt			_nextValueVarno;

    class BIEnumIpl : public IliBindInfoEnumIpl {
    public:
	BIEnumIpl(IliBindInfoCollection* abi, IlInt idx = 0)
	    : _abi(abi),
	      _idx(idx)
	{}

	virtual IliBindInfoEnumIpl*	copy() const;
	virtual IlBoolean		getNext(IliBindInfo& bi);
	virtual IlInt			getIndex() const;

	IliBindInfoCollection*		_abi;
	IlInt				_idx;
    };

    inline IliSQLStmtBuf(const IliSQLStmtBuf&) {}
    inline
    const IliSQLStmtBuf& operator =(const IliSQLStmtBuf&) { return *this; }
};

inline
IliSQLStmtBuf&
NewLineIndent(IliSQLStmtBuf& stmt)
{
    stmt.NewLineIndent();
    return stmt;
}

#endif /* !__Ili_Sqlbind_H */
