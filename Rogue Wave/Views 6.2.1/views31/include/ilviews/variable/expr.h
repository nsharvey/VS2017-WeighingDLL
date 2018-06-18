// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/expr.h
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
// Declaration of the  IlvvExpr class and its subtypes.
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Expr_H
#define __Ilv31_Variable_Expr_H

#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv31_Variable_All_H)
#include <ilviews/variable/all.h>
#endif
#if !defined(__Ilv31_Variable_Ccell_H)
#include <ilviews/variable/ccell.h>
#endif
#if !defined(__Ilv31_Variable_Cexpr_H)
#include <ilviews/variable/cexpr.h>
#endif
#if !defined(__Ilv31_Variable_Ostreams_H)
#include <ilviews/variable/ostreams.h>
#endif

#if !defined(ILVV_VSNODE_ATTR_SET)
#define ILVV_VSNODE_ATTR_SET()
#endif

#if !defined(ILVV_VSNODE_ATTR_RESET)
#define ILVV_VSNODE_ATTR_RESET()
#endif

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvExpr
{
    friend class IlvvSheet;
public:
    virtual IlvvFundamental getValue() const =0;
    virtual IlvvOStream& print(IlvvOStream&) const =0;
    virtual ~IlvvExpr(){}
    IlvvExprContext* getContext() const {return _context;}
    void setContext(IlvvExprContext* c){_context=c;}
protected:
    // defined just because the copy constructor is private
    IlvvExpr(): _context(0){}
private:
    // no copy allowed
    IlvvExpr(const IlvvExpr&);
    // this delete function, which is not recursive is added to allow in the
    // class Sheet, to perform the deletion of all the expressions built during
    // a parsing, after a syntax error.
    virtual void shallowDelete();
    IlvvExprContext* _context;
};

IlvvOStream& operator<<(IlvvOStream&, const IlvvExpr*);
IlvvOStream& operator<<(IlvvOStream&, const IlvvExpr&);

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvValue
: public IlvvExpr {
 public:
#if defined(WINDOWS) || defined(PM)
   IlvvValue(IlvvFundamental value);
#else  /* !WINDOWS && !PM */
   IlvvValue(IlvvFundamental value): _value(value) {}
#endif /* !WINDOWS && !PM */
   operator IlvvFundamental() const {return _value;}
   IlvvFundamental getValue() const {return _value;}
   IlvvOStream& print(IlvvOStream& o) const {return o<<_value;}
private:
   virtual void shallowDelete();
   IlvvFundamental _value;
};

#define BASICMEMBERS operator IlvvFundamental() const {return _value;} \
   IlvvFundamental getValue() const {return _value;}

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvChar
: public IlvvExpr {
public:
    IlvvChar(char value): _value(value){}
    BASICMEMBERS;
    IlvvOStream& print(IlvvOStream& o) const {return o<<'\''<<_value<<'\'';}
private:
   virtual void shallowDelete();
   char _value;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvUChar
: public IlvvExpr {
public:
    IlvvUChar(unsigned char value): _value(value){}
    BASICMEMBERS;
    IlvvOStream& print(IlvvOStream& o) const {return o<<_value;}
private:
    virtual void shallowDelete();
    unsigned char _value;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvShort
: public IlvvExpr {
public:
    IlvvShort(short value): _value(value){}
    BASICMEMBERS;
    IlvvOStream& print(IlvvOStream& o) const {return o<<_value;}
private:
    virtual void shallowDelete();
    short _value;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvUShort
: public IlvvExpr
{
public:
    IlvvUShort(unsigned short value): _value(value){}
    BASICMEMBERS;
    IlvvOStream& print(IlvvOStream& o) const {return o<<_value;}
private:
    virtual void shallowDelete();
    unsigned short _value;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvInt
: public IlvvExpr
{
public:
    IlvvInt(int value): _value(value) {}
    BASICMEMBERS;
    IlvvOStream& print(IlvvOStream& o) const {return o<<_value;}
private:
    virtual void shallowDelete();
    int _value;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvUInt
: public IlvvExpr
{
public:
    IlvvUInt(unsigned int value): _value(value){}
    BASICMEMBERS;
    IlvvOStream& print(IlvvOStream& o) const {return o<<_value;}
private:
    virtual void shallowDelete();
    unsigned int _value;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvLong
: public IlvvExpr
{
public:
    IlvvLong(long value): _value(value) {}
    BASICMEMBERS;
    IlvvOStream& print(IlvvOStream& o) const { return o<<_value; }
private:
    virtual void shallowDelete();
    long _value;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvULong
: public IlvvExpr
{
public:
    IlvvULong(unsigned long value): _value(value){}
    BASICMEMBERS;
    IlvvOStream& print(IlvvOStream& o) const {return o<<_value;}
private:
    virtual void shallowDelete();
    unsigned long _value;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvFloat
: public IlvvExpr
{
public:
    IlvvFloat(float value): _value(value){}
    BASICMEMBERS;
    IlvvOStream& print(IlvvOStream& o) const {return o<<_value;}
private:
    virtual void shallowDelete();
    float _value;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvDouble
: public IlvvExpr
{
public:
    IlvvDouble(double value): _value(value){}
    BASICMEMBERS;
    IlvvOStream& print(IlvvOStream& o) const {return o<<_value;}
private:
    virtual void shallowDelete();
    double _value;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvCharP
: public IlvvExpr
{
public:
    IlvvCharP(const char* value);
    ~IlvvCharP() { if (_value) delete [] _value; }
    BASICMEMBERS;
    IlvvOStream& print(IlvvOStream& o) const {return o<<'\"'<<_value<<'\"';}
private:
    virtual void shallowDelete();
    char* _value;
};
#undef BASICMEMBERS

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvUnary
: public IlvvExpr, public virtual IlvvExprContext
{
public:
    IlvvUnary(IlvvExpr*);
    ~IlvvUnary();
    const IlvvExpr* op() const {return _op;}
    int argIsUndef(IlvvFundamental& arg) const;
private:
    void resetExprContext()
	{ if (getContext()) getContext()->resetExprContext(); }
    IlvvPath* computePath();
    void shallowDelete();
    IlvvExpr* _op;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvBinary
: public IlvvExpr, public virtual IlvvExprContext
{
public:
    IlvvBinary(IlvvExpr*, IlvvExpr*);
    ~IlvvBinary();
    const IlvvExpr* lhs() const { return _lhs; }
    const IlvvExpr* rhs() const { return _rhs; }
    int argsAreUndef(IlvvFundamental& l, IlvvFundamental& r) const;
private:
    void resetExprContext()
	{ if (getContext()) getContext()->resetExprContext(); }
    IlvvPath* computePath();
    void shallowDelete();
    IlvvExpr* _lhs;
    IlvvExpr* _rhs;
};

// --------------------------------------------------------------------------
class IlvvCell;
class ILV31VAREXPORTED IlvvCellRef:
public IlvvExpr,
public virtual IlvvCellReferencer
{
public:
    IlvvCellRef(IlvvCell*);
    ~IlvvCellRef();
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
protected:
    void reconnect(IlvvCell& c);
    void removeCell(IlvvCell*);
    void resetCell(IlvvCell*);
    IlvvPath* computePath();
#if defined(__GNUC__)
    IlvvCell* getCell() const {return _cell;}
#endif
private:
    virtual void shallowDelete();
    IlvvCell* _cell;
};

// --------------------------------------------------------------------------
// unary operators
class ILV31VAREXPORTED IlvvUPlus
: public IlvvUnary
{
public:
    IlvvUPlus(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvUMinus
: public IlvvUnary
{
public:
    IlvvUMinus(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvNot
: public IlvvUnary
{
public:
    IlvvNot(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvBitNot
: public IlvvUnary
{
public:
    IlvvBitNot(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvCharCast
: public IlvvUnary
{
public:
    IlvvCharCast(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvUCharCast
: public IlvvUnary
{
public:
    IlvvUCharCast(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvShortCast
: public IlvvUnary
{
public:
    IlvvShortCast(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvUShortCast
: public IlvvUnary
{
public:
    IlvvUShortCast(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvIntCast
: public IlvvUnary
{
public:
    IlvvIntCast(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvUIntCast
: public IlvvUnary
{
public:
    IlvvUIntCast(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvLongCast
: public IlvvUnary
{
public:
    IlvvLongCast(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvULongCast
: public IlvvUnary
{
public:
    IlvvULongCast(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvFloatCast
: public IlvvUnary
{
public:
    IlvvFloatCast(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvDoubleCast
: public IlvvUnary
{
public:
    IlvvDoubleCast(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
// parenthesis
class ILV31VAREXPORTED IlvvPar
: public IlvvUnary
{
public:
    IlvvPar(IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
// binary operators
class ILV31VAREXPORTED IlvvPlus
: public IlvvBinary
{
public:
    IlvvPlus(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvMinus
: public IlvvBinary
{
public:
    IlvvMinus(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvMult
: public IlvvBinary
{
public:
    IlvvMult(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvDiv
: public IlvvBinary
{
public:
    IlvvDiv(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvInf
: public IlvvBinary
{
public:
    IlvvInf(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvSup
: public IlvvBinary
{
public:
    IlvvSup(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvInfEq
: public IlvvBinary
{
public:
    IlvvInfEq(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvSupEq
: public IlvvBinary
{
public:
    IlvvSupEq(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvOr
: public IlvvBinary
{
public:
    IlvvOr(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvAnd
: public IlvvBinary
{
public:
    IlvvAnd(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvBitOr
: public IlvvBinary
{
public:
    IlvvBitOr(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvBitAnd
: public IlvvBinary
{
public:
    IlvvBitAnd(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvXOr
: public IlvvBinary
{
public:
    IlvvXOr(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvCompare
: public IlvvBinary
{
public:
    IlvvCompare(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvDifferent
: public IlvvBinary
{
public:
    IlvvDifferent(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvMod
: public IlvvBinary
{
public:
    IlvvMod(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvLShift
: public IlvvBinary
{
public:
    IlvvLShift(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvRShift
: public IlvvBinary
{
public:
    IlvvRShift(IlvvExpr*, IlvvExpr*);
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvConditional
: public IlvvExpr, public virtual IlvvExprContext
{
public:
    IlvvConditional(IlvvExpr* condition, IlvvExpr* iftrue, IlvvExpr* iffalse);
    ~IlvvConditional();
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream&) const;
    IlvvExpr* condition() const;
    IlvvExpr* iftrue() const;
    IlvvExpr* iffalse() const;
private:
    void resetExprContext(){if (getContext()) getContext()->resetExprContext();}
    IlvvPath* computePath();
    void shallowDelete();
    IlvvExpr* _condition;
    IlvvExpr* _iftrue;
    IlvvExpr* _iffalse;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvArguments
: public virtual IlvvExprContext, public virtual IlvvArgumentsContext
{
public:
    IlvvArguments(IlvvExpr* car, IlvvArguments* cdr);
    ~IlvvArguments(){delete _car; delete _cdr;}
    IlvvExpr* car() const {return _car;}
    IlvvArguments* cdr() const {return _cdr;}
    int size() const;
    void shallowDelete();
    IlvvArgumentsContext* getContext() const {return _context;}
    void setContext(IlvvArgumentsContext* c){_context=c;}
private:
    void resetExprContext(){if (getContext()) getContext()->resetExprContext();}
    IlvvPath* computePath();
    IlvvExpr* _car;
    IlvvArguments* _cdr;
    IlvvArgumentsContext* _context;
};
IlvvOStream& operator<<(IlvvOStream& o, IlvvArguments* args);

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvFunCall
: public IlvvExpr, public virtual IlvvArgumentsContext
{
 public:
    IlvvFunCall(const char* f, IlvvArguments* args);
    ~IlvvFunCall(){delete [] _f;delete _args;}
    char* f() const {return _f;}
    IlvvArguments* args() const {return _args;}
    IlvvFundamental getValue() const;
    IlvvOStream& print(IlvvOStream& o) const {return o<<_f<<'('<<_args<<')';}
    void shallowDelete();
private:
    void resetExprContext(){if (getContext()) getContext()->resetExprContext();}
    IlvvPath* computePath();
    char* _f;
    int _size;
    IlvvArguments* _args;
};

#endif
