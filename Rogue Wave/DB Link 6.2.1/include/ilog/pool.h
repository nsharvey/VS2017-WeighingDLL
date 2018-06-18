// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/pool.h
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
// Declaration of memory pools for common usage.
// Defined in library <display>
// --------------------------------------------------------------------------
#ifndef __Il_Pool_H
#define __Il_Pool_H

#if !defined(__Il_Iostream_H)
#include <ilog/iostream.h>
#endif

#if !defined(_Il_Memory_H)
#include <ilog/memory.h>
#endif


// --------------------------------------------------------------------------
class IlMemoryPoolBlock;
class ILOG_EXPORTED IlMemoryPool
{
protected:
    IlMemoryPool(int size)
    : _size(size),
      _blocks(0)
    {}

public:
    ~IlMemoryPool();
    // ____________________________________________________________
    void*	alloc(IlUInt size, IlBoolean lock);
    void*	reAlloc(void*, IlUInt size, IlBoolean lock);
    void*	lock(void*) const;
    void*	unLock(void*) const;
    void	printInformation(IL_STDPREF ostream&, 
				 const char*,
				 IlUShort = 0) const;
protected:
    IlAny		take(IlMemoryPoolBlock*&, IlUInt, IlBoolean);
    IlMemoryPoolBlock*	getBlock(void*) const;
    IlAny		getData(IlMemoryPoolBlock*) const;
    IlAny		grow(IlMemoryPoolBlock*, IlUInt, IlBoolean);
    IlAny		release(IlMemoryPoolBlock*);
private:
    IlMemoryPoolBlock*	find(void*) const;

    int			_size;
    IlMemoryPoolBlock*	_blocks;
};

#define IlPoolOf(name) Il##name##Pool
#define IlPoolNoE
#define IlDeclareExpPoolOf(NAME, TYPE, EXPORT)				\
class EXPORT IlPoolOf(NAME) : public IlMemoryPool {			\
public: static TYPE* Alloc(IlUInt n, IlBoolean lock = IlFalse) {	\
return IL_REINTERPRETCAST(TYPE*, _Pool.alloc(n*sizeof(TYPE), lock)); }	\
static TYPE* AllocBlock(IlMemoryPoolBlock*& block, IlUInt n) {		\
return IL_REINTERPRETCAST(TYPE*, _Pool.take(block, n*sizeof(TYPE), IlTrue));}\
static IlMemoryPoolBlock* GetBlock(TYPE* data){return _Pool.getBlock(data); }	\
static TYPE* GetData(IlMemoryPoolBlock* block) {			\
return IL_REINTERPRETCAST(TYPE*, _Pool.getData(block)); }		\
static TYPE* ReAlloc(TYPE* d, IlUInt n, IlBoolean l = IlFalse) {	\
return IL_REINTERPRETCAST(TYPE*, _Pool.reAlloc((IlAny)d, n*sizeof(TYPE),l));}\
static TYPE* ReAllocBlock(IlMemoryPoolBlock*& block, IlUInt n) {	\
return block								\
? IL_REINTERPRETCAST(TYPE*, _Pool.grow(block, n*sizeof(TYPE), IlFalse))	\
: AllocBlock(block, n); }						\
static TYPE* Lock(TYPE* data)   {					\
return IL_REINTERPRETCAST(TYPE*, _Pool.lock(data)); }			\
static TYPE* UnLock(TYPE* data) {					\
return IL_REINTERPRETCAST(TYPE*, _Pool.unLock(data)); }			\
static TYPE* ReleaseBlock(IlMemoryPoolBlock* block)			\
{ return block ? IL_REINTERPRETCAST(TYPE*, _Pool.release(block)) : 0; }	\
static void PrintInformation(IL_STDPREF ostream& os, IlUShort l=0)      \
{ _Pool.printInformation(os, #NAME, l); }	 		        \
private: IlPoolOf(NAME)() : IlMemoryPool(sizeof(TYPE)) {}		\
static IlPoolOf(NAME) _Pool; }
#define IlDeclarePoolOf(N, T) IlDeclareExpPoolOf(N, T, IlPoolNoE)
#define IlDefinePoolOf(NAME) IlPoolOf(NAME) IlPoolOf(NAME)::_Pool

IlDeclareExpPoolOf(Char,    char,   ILOG_EXPORTED);
IlDeclareExpPoolOf(Pointer, IlAny,  ILOG_EXPORTED);
IlDeclareExpPoolOf(IlUInt,  IlUInt, ILOG_EXPORTED);
#endif /* !__Il_Pool_H */
