// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/alloc.h
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
// Declaration of the ILI_USEMALLOC macro
// --------------------------------------------------------------------------
#ifndef __Ili_Alloc_H
#define __Ili_Alloc_H

#ifndef __Ilv_Base_Alloc_H
#  include <ilviews/base/alloc.h>
#endif

#ifndef __Ili_Macros_H
#  include <ilviews/dataccess/macros.h>
#endif

#ifdef ILI_USEMALLOC

#  define ILI_MLK_DECL() friend void Ili_turlututu()
#  define ILI_MLK_DEF(cl)

static inline void*
IliAlloc (size_t size) {
  return (void*)new char[size];
}
static inline void
IliFree (void *p, size_t size) {
  delete [] (char*)p;
}

#else // ILI_USEMALLOC
#  define ILI_MLK_DECL() \
void* operator new(size_t); \
static void operator delete(void*, size_t)

#if IlvVersion < 310
#  define ILI_MLK_DEF(cl) \
void * cl :: operator new(size_t size){ \
   return (size < IL_MLK_ALIGNMENT*IL_MLK_THRESHOLD) \
	  ? IlvGetMemoryManager().alloc(size) \
	  : (void*)new char[size]; } \
void cl :: operator delete(void *addr, size_t size) { \
   if (size < IL_MLK_ALIGNMENT*IL_MLK_THRESHOLD) \
     IlvGetMemoryManager().release(addr, (size_t)size); \
   else \
     delete [] (char*)addr; }
#else
#  define ILI_MLK_DEF(cl) \
void * cl :: operator new(size_t size){ \
   return (size < IL_MLK_ALIGNMENT*IL_MLK_THRESHOLD) \
	  ? IlMemoryManager::GetInstance().alloc(size) \
	  : (void*)new char[size]; } \
void cl :: operator delete(void *addr, size_t size) { \
   if (size < IL_MLK_ALIGNMENT*IL_MLK_THRESHOLD) \
     IlMemoryManager::GetInstance().release(addr, (size_t)size); \
   else \
     delete [] (char*)addr; }
#endif

static inline void*
IliAlloc (size_t size) {
#if IlvVersion < 310
  return (size < IL_MLK_ALIGNMENT*IL_MLK_THRESHOLD
	  ? (void*)IlvGetMemoryManager().alloc(size)
	  : (void*)new char[size]);
#else
  return (size < IL_MLK_ALIGNMENT*IL_MLK_THRESHOLD
	  ? (void*)IlMemoryManager::GetInstance().alloc(size)
	  : (void*)new char[size]);
#endif
}
static inline void
IliFree (void *p, size_t size) {
  if (size < IL_MLK_ALIGNMENT*IL_MLK_THRESHOLD)
#if IlvVersion < 310
    IlvGetMemoryManager().release(p, size);
#else
    IlMemoryManager::GetInstance().release(p, size);
#endif
  else
    delete [] (char*)p;
}

#endif // ILI_USEMALLOC

#endif

