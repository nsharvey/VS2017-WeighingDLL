// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/query.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the classes that are used for building queries
// --------------------------------------------------------------------------
#ifndef VPF_QUERY_H
#define VPF_QUERY_H

#include <vpf/set.h>

class VpfThematicIndex;
class VpfDate;
class VpfTable;
class VpfRow;

// --------------------------------------------------------------------------
class VpfExpression
{
public:
    VpfExpression(VpfUInt nMatches = 0)
    : _nMatches(nMatches)
    {}
    virtual ~VpfExpression() {}
    // ____________________________________________________________
    virtual VpfSet* evaluate(int&) = 0;

    virtual VpfUInt getNExpressions() const { return 0; }
    virtual VpfExpression* getExpression(VpfUInt) const { return 0; }
    virtual int isMatch() const { return 0; }
    
    int getNMatches() const { return _nMatches; }
protected:
    VpfUInt	_nMatches;
};

// --------------------------------------------------------------------------
class VpfAllExpression
: public VpfExpression
{
public:
    VpfAllExpression(VpfTable*);
    virtual ~VpfAllExpression() { if (_set) delete _set; }
    // ____________________________________________________________
    virtual VpfSet* evaluate(int& destroy) { destroy = 0; return _set; }
protected:
    VpfSet*	_set;
};

// --------------------------------------------------------------------------
class VpfUnaryExpression
: public VpfExpression
{
public:
    VpfUnaryExpression(VpfExpression* a)
    : VpfExpression(a->getNMatches()),
	_a(a)
    {}
    virtual ~VpfUnaryExpression() { if (_a) delete _a; }
    // ____________________________________________________________
    virtual VpfUInt getNExpressions() const { return 1; }
    virtual VpfExpression* getExpression(VpfUInt) const { return _a; }
protected:
    VpfExpression*	_a;
};

// --------------------------------------------------------------------------
class VpfBinaryExpression
: public VpfExpression
{
public:
    VpfBinaryExpression(VpfExpression* a, VpfExpression* b)
    : VpfExpression(a->getNMatches() + b->getNMatches()),
	_a(a),
	_b(b)
	{}
    virtual ~VpfBinaryExpression()
	{
	    if (_a)
		delete _a;
	    if (_b)
		delete _b;
	}
    // ____________________________________________________________
    virtual VpfUInt getNExpressions() const { return 2; }
    virtual VpfExpression* getExpression(VpfUInt i) const
	{
	    return i
		? _b
		: _a;
	}
protected:
    VpfExpression*	_a;
    VpfExpression*	_b;
};

// --------------------------------------------------------------------------
class VpfComparisonExpression
: public VpfExpression
{
public:
    VpfComparisonExpression(VpfUInt nMatches = 0)
    : VpfExpression(nMatches)
    {}
    // ____________________________________________________________
    enum Operator {
	EQ, NE,
	LE, GE,
	LT, GT,
	Contains,
	Matches 
    };
    union Value {
	char*	 textval;
	VpfInt	 intval;
	double	 floatval;
	VpfUInt	 fieldval;
	VpfDate* dateval;
    };
    
    static VpfComparisonExpression* Create(VpfUInt field,
					   Operator, const char*);
    static VpfComparisonExpression* Create(VpfUInt field,
					   Operator, VpfInt);
    static VpfComparisonExpression* Create(VpfUInt field,
					   Operator, double);
};

// --------------------------------------------------------------------------
class VpfIndexExpression
: public VpfComparisonExpression
{
public:
    VpfIndexExpression(const VpfThematicIndex*, const char* value);
    VpfIndexExpression(const VpfThematicIndex*, VpfInt value);
    VpfIndexExpression(const VpfThematicIndex*, double value);
    virtual ~VpfIndexExpression()
	{
	    if ((_type == 'T') && (_value.textval))
		delete [] _value.textval;
	}
    // ____________________________________________________________
    virtual VpfSet* evaluate(int&);
protected:
    const VpfThematicIndex*	_index;
    char			_type;
    Value			_value;
};

// --------------------------------------------------------------------------
class VpfMatchExpression
: public VpfComparisonExpression
{
public:
    VpfMatchExpression(VpfTable*, VpfUInt, Operator, const char*);
    VpfMatchExpression(VpfTable*, VpfUInt, Operator, VpfInt);
    VpfMatchExpression(VpfTable*, VpfUInt, Operator, double);
    VpfMatchExpression(VpfTable*, VpfUInt, Operator, VpfUInt);
    VpfMatchExpression(VpfTable*, VpfUInt, Operator, const VpfDate*);
    virtual ~VpfMatchExpression();
    // ____________________________________________________________
    virtual VpfSet* evaluate(int& destroy) { destroy = 0; return _set; }
    virtual void match(VpfRow*);
    virtual int isMatch() const { return 1; }
protected:
    void initSet();
    int assertCompatibleTypes(char valueType);

    VpfTable*	_table;
    VpfUInt	_field;
    char	_fieldType;
    VpfSet*	_set;
    Operator	_op;
    Value	_value;
};

// --------------------------------------------------------------------------
class VpfOrExpression
: public VpfBinaryExpression
{
public:
    VpfOrExpression(VpfExpression* a, VpfExpression* b)
    : VpfBinaryExpression(a, b)
    {}
    // ____________________________________________________________
    virtual VpfSet* evaluate(int& destroy)
	{
	    int da, db;
	    VpfSet* a = _a->evaluate(da);
	    VpfSet* b = _b->evaluate(db);
	    VpfSet* c = a->logor(b);
	    if (da)
		delete a;
	    if (db)
		delete b;
	    destroy = 1;
	    return c;
	}
};

// --------------------------------------------------------------------------
class VpfAndExpression
: public VpfBinaryExpression
{
public:
    VpfAndExpression(VpfExpression* a, VpfExpression* b)
    : VpfBinaryExpression(a, b)
    {}
    // ____________________________________________________________
    virtual VpfSet* evaluate(int& destroy)
	{
	    int da, db;
	    VpfSet* a = _a->evaluate(da);
	    VpfSet* b = _b->evaluate(db);
	    VpfSet* c = a->logand(b);
	    if (da)
		delete a;
	    if (db)
		delete b;
	    destroy = 1;
	    return c;
	}
};

// --------------------------------------------------------------------------
class VpfXorExpression
: public VpfBinaryExpression 
{
public:
    VpfXorExpression(VpfExpression* a, VpfExpression* b)
    : VpfBinaryExpression(a, b)
    {}
    // ____________________________________________________________
    virtual VpfSet* evaluate(int& destroy)
	{
	    int da, db;
	    VpfSet* a = _a->evaluate(da);
	    VpfSet* b = _b->evaluate(db);
	    VpfSet* c = a->logxor(b);
	    if (da)
		delete a;
	    if (db)
		delete b;
	    destroy = 1;
	    return c;
	}
};

// --------------------------------------------------------------------------
class VpfNotExpression
: public VpfUnaryExpression
{
public:
    VpfNotExpression(VpfExpression* a)
    : VpfUnaryExpression(a)
    {}
    // ____________________________________________________________
    VpfSet* evaluate(int& destroy)
	{
	    int da;
	    VpfSet* a = _a->evaluate(da);
	    VpfSet* b = a->lognot();
	    if (da)
		delete a;
	    destroy = 1;
	    return b;
	}
};

// --------------------------------------------------------------------------
class VpfQuery
{
public:
    VpfQuery(VpfTable*, const char*);
    virtual ~VpfQuery();
    // ____________________________________________________________
    int parse(const char*);

    VpfUInt getNMatches() const { return _nMatches; }
    VpfMatchExpression* getMatch(VpfUInt i) const { return _matches[i]; }
    VpfExpression* getExpression() const { return _expression; }
    // Parser:
    static VpfExpression* Parse(VpfTable* table, const char* filter);
    static VpfInt FieldFromName(const char*);
    static void SetResult(VpfExpression*);
    static VpfTable* Table();
protected:
    void buildMatchArray(VpfUInt& i, VpfExpression* expression);
    VpfTable*			_table;
    VpfUInt			_nMatches;
    VpfMatchExpression**	_matches;
    VpfExpression*		_expression;
};

#endif /* VPF_QUERY_H */
