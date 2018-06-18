// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/mlk.h
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
// Defined in library ilvvar
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Mlk_H
#define __Ilv31_Variable_Mlk_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#include <ilviews/variable/compilrs.h>
#if !defined(WINDOWS)
#  include <sys/types.h>
#  if defined(linux)
#    if defined(ILVSTD)
#      include <malloc.h>
#    else  /* !ILVSTD */
#      include <malloc.h>
#    endif /* !ILVSTD */
#  endif
#else
#  if defined(ILVSTD)
#    include <cstdlib>
#    if defined(__BORLANDC__) && (__BORLANDC__ >= 550)
#	define IL_SIZET_PREF std::
#    endif /* !__BORLANDC__ || __BORLANDC__ < 550 */
#  else  /* !ILVSTD */
#    include <malloc.h>
#  endif /* !ILVSTD */
#endif

#if !defined(IL_SIZET_PREF)
#  define IL_SIZET_PREF
#endif /* !IL_SIZET_PREF */

// ~~~~~~~~~~~~~~ READ ME: SCOPE OF USE ~~~~~~~~~~~~~~~
//
// This package offers an optimized memory allocation algorithm
// derived from Kernighan and Richie's single size allocator.
// It is typically less memory and time consuming than the standard
// allocator.
// Its use is prohibited when deleting a pointer can occur when its type
// is a superclass of the effective object, when this superclass has no virtual
// destructor and has a different size from the effective object size.
// C++ built in delete works, but not the delete proposed in this package.
// Violating this rule can lead to very complex bugs.
//
// This package is useful in all other cases that is when pointers:
// - point to the effective object or,
// - have a type with a virtual destructor or,
// - have a type with same size as the effective object
//
// for class dedicated allocator:
// Put ILVV_MLK_DECL(); in class declaration
// Put ILVV_MLK_DEF(classid) outside the header.
//
// for global pool allocator:
// Put ILVV_MLK_GDECL(); in class declaration
// Put ILVV_MLK_GDEF(classid) outside the header.
//
// As new and delete are inherited by derived classes, you need only
// to declare them on root classes in hierarchies.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// MLK_THRESHOLD: number of multiples of the system alignment, specifying the
// threshold past which memory management is delegated to malloc

// Beware, these alignments are on purpose smaller than ::malloc alignment,
// to further improve memory allocation performance. Not any structure can be
// allocated using this alignment. For instance, on Sun, sizeof(long doube)=16
// and you find only an 8 bytes alignement below.
#if defined(__alpha)
#  define ILVV_MLK_ALIGNMENT        16
#  define ILVV_MLK_THRESHOLD        8
#elif defined(IlvvWINDOWS3)
#  define ILVV_MLK_ALIGNMENT        4
#  define ILVV_MLK_THRESHOLD        8
#else
#  define ILVV_MLK_ALIGNMENT        8
#  define ILVV_MLK_THRESHOLD        8
#endif


/*
 * size of an elementary memory block to allocate for small objects, in number
 * of small object bytes packets. Every time a block of memory is full,
 * another block is allocated whose size is
 * ILVV_MLK_BLOCK*ILVV_MLK_THRESHOLD*ILVV_MLK_ALIGNMENT*ILVV_MLK_MULT
 */
#define ILVV_MLK_BLOCK            64
#define ILVV_MLK_MULT             2

#ifdef ILVV_MLK_STATS
#  if defined(ILVSTD)
#    include <ostream>;
ILVSTDUSE;
#  else  /* !ILVSTD */
class ostream;
#  endif /* !ILVSTD */
#endif

class ILV31VAREXPORTED IlvvMemoryManager
{
public:
    IlvvMemoryManager();
#if defined(linux)
    void* internal_malloc(IL_SIZET_PREF size_t);
    void internal_free(void*, IL_SIZET_PREF size_t);
#else
    void* malloc(IL_SIZET_PREF size_t);
    void  free(void*, IL_SIZET_PREF size_t);
#endif

#ifdef ILVV_MLK_STATS
    void status(ILVSTDPREF ostream&);
#endif
private:
    static IL_SIZET_PREF size_t category(IL_SIZET_PREF size_t size) {
	return ((size%ILVV_MLK_ALIGNMENT)
		? (size/ILVV_MLK_ALIGNMENT)
		: ((size/ILVV_MLK_ALIGNMENT)-1));
    }
    static IL_SIZET_PREF size_t alignedSize(IL_SIZET_PREF size_t size) {
	return ((size%ILVV_MLK_ALIGNMENT)
		? ((size/ILVV_MLK_ALIGNMENT+1)*ILVV_MLK_ALIGNMENT)
		: size);
    }
#define ILVV_MLK_FLOC_SIZE (ILVV_MLK_THRESHOLD+1)
    void*		 _floc[ILVV_MLK_FLOC_SIZE];
    void*		 _scratch;
    void*		 _border;
    IL_SIZET_PREF size_t _blocks;
#ifdef ILVV_MLK_STATS
    unsigned long	 _heap;
    unsigned long	 _used;
    int			 _totalAllocated;
    int			 _totalFreed;
    int			 _currentlyUsed;
    int			 _maxUsed;
#endif
    static int		 _invalidated;
    // forbidden
    void operator=(const IlvvMemoryManager&);
    IlvvMemoryManager(const IlvvMemoryManager&);
};

// for use of a single global allocator
IlvvMemoryManager& IlvvGetMemoryManager();
#if defined(linux)
inline void*
IlvvMalloc(IL_SIZET_PREF size_t s)
{
    return IlvvGetMemoryManager().internal_malloc(s);
}
inline void
IlvvFree(void* p, IL_SIZET_PREF size_t s)
{
    IlvvGetMemoryManager().internal_free(p, s);
}
#else  /* !linux */
inline void*
IlvvMalloc(IL_SIZET_PREF size_t s)
{
    return IlvvGetMemoryManager().malloc(s);
}
inline void
IlvvFree(void* p, IL_SIZET_PREF size_t s)
{
    IlvvGetMemoryManager().free(p, s);
}
#endif /* !linux */

/* static before operator delete is facultative */
#define ILVV_MLK_DECL() \
void* operator new(IL_SIZET_PREF size_t); \
static void operator delete(void*, IL_SIZET_PREF size_t); \
ILVV_MAGIC_DECL(IlvvMemoryManager, manager)

#if defined(linux)
#define ILVV_MLK_DEF(cl) \
void* cl::operator \
new(IL_SIZET_PREF size_t size) \
{ \
    return manager().internal_malloc(size); \
} \
void cl::operator \
delete(void* addr, IL_SIZET_PREF size_t size) \
{ \
    manager().internal_free(addr, size); \
} \
ILVV_SMAGIC_DEF(cl, IlvvMemoryManager, manager)
#else  /* !linux */
#define ILVV_MLK_DEF(cl) \
void* cl::operator \
new(IL_SIZET_PREF size_t size) \
{ \
    return manager().malloc(size); \
} \
void cl::operator \
delete(void* addr, IL_SIZET_PREF size_t size) \
{ \
    manager().free(addr, size); \
} \
ILVV_SMAGIC_DEF(cl, IlvvMemoryManager, manager)
#endif /* !linux */

/* static before operator delete is facultative */
#define ILVV_MLK_GDECL() \
void* operator new(IL_SIZET_PREF size_t); \
static void operator delete(void*, IL_SIZET_PREF size_t)

#if defined(linux)
#define ILVV_MLK_GDEF(cl) \
void* cl::operator \
new(IL_SIZET_PREF size_t size) \
{ \
    return IlvvGetMemoryManager().internal_malloc(size); \
} \
void cl::operator \
delete(void* addr, IL_SIZET_PREF size_t size) \
{ \
    IlvvGetMemoryManager().internal_free(addr, size); \
}
#else  /* !linux */
#define ILVV_MLK_GDEF(cl) \
void* cl::operator \
new(IL_SIZET_PREF size_t size) \
{ \
    return IlvvGetMemoryManager().malloc(size); \
} \
void cl::operator \
delete(void* addr, IL_SIZET_PREF size_t size) \
{ \
    IlvvGetMemoryManager().free(addr, size); \
}
#endif /* !linux */

#endif
