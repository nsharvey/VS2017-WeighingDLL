// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/cellfun.h
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
//
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Cellfun_H
#define __Ilv31_Variable_Cellfun_H

#include <assert.h>

#if !defined(__Ilv31_Variable_Compilrs_H)
#include <ilviews/variable/compilrs.h>
#endif
#if !defined(__Ilv31_Variable_All_H)
#include <ilviews/variable/all.h>
#endif
#if !defined(__Ilv31_Variable_Buffer_H)
#include <ilviews/variable/buffer.h>
#endif
#if !defined(__Ilv31_Variable_Hash_H)
#include <ilviews/variable/hash.h>
#endif

ILVV_BUFFER_DECL(IlvvBaseFunArgs,IlvvFundamental)

class IlvvArguments;
class IlvvFunArgs:
public IlvvBaseFunArgs
{
public:
    IlvvFunArgs(): IlvvBaseFunArgs() {}
    IlvvFunArgs(IlvvArguments*);
    IlvvFunArgs& push(const IlvvFundamental& f)
    {IlvvBaseFunArgs::push(f);return *this;}
    IlvvFunArgs& operator<<(const IlvvFundamental& f)
    {IlvvBaseFunArgs::push(f);return *this;}
    IlvvFunArgs& operator>>(IlvvFundamental& f)
    {f=IlvvBaseFunArgs::pop();return *this;}
    // just renaming for a more appropriate name
    IlvvBoolean eoa() const {return (IlvvBoolean)eob();}
    IlvvBoolean empty() const {return (IlvvBoolean)eob();}
};

typedef IlvvFundamental (*IlvvFunc)(IlvvFunArgs);

class ILV31VAREXPORTED IlvvNamedFun
{
public:
    IlvvNamedFun(char* name, IlvvFunc f): _name(name), _f(f){}
    char* name() const {return _name;}
    IlvvFunc f() const {return _f;}
private:
    char* _name;
    IlvvFunc _f;
};

ILVV_HASH_DEF(IlvvBaseNamedFunTable,IlvvNamedFun*, char*)
class ILV31VAREXPORTED IlvvNamedFunTable:
public IlvvBaseNamedFunTable
{
public:
    IlvvNamedFunTable(){}
    ~IlvvNamedFunTable();
};

ILV31VAREXPORTEDFUNCTION(IlvvNamedFunTable&) IlvvGlobalFunTable();

#define ILVV_REGISTER_FUNC(f) \
static char IlvvRegisterFunc##f=(char)(IlvvGlobalFunTable()<<new IlvvNamedFun(ILVSTRING(f),f),0)

#define ILVV_REGISTER_NFUNC(nf,f) \
static char IlvvRegisterFunc##f=(char)(IlvvGlobalFunTable()<<new IlvvNamedFun(nf,f),0)

ILV31VARMODULEINIT(cellfun);
#endif
