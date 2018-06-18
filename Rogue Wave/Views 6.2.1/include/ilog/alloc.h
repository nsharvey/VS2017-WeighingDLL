// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/alloc.h
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
// Declaration of IlMemoryManager class
// --------------------------------------------------------------------------
#ifndef __Il_Alloc_H
#define __Il_Alloc_H

#if !defined(__Il_Macros_H)
#include <ilog/macros.h>
#endif

#if !defined(IL_SIZE_T)
#  if defined(IL_STD)
#    include <cstddef>
#  else  /* ! IL_STD */
#    include <stddef.h>
#  endif /* ! IL_STD */
#  if defined(_MSC_VER) && (_MSC_VER < 1300) /* msvc6. */
#    define IL_SIZE_T size_t
#  elif defined(sgi) && defined(_STANDARD_C_PLUS_PLUS)
       // <cstddef> seems to be as buggy on sgi as on msvc6
#    define IL_SIZE_T size_t
#else  /* !msvc6 */
#    define IL_SIZE_T IL_STDPREF size_t
#endif /* !msvc6. */
#endif /* !IL_SIZE_T */

// 0.9.1
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
// Put IL_MLK_DECL(); in class declaration
// Put IL_MLK_DEF(classid) outside the header.
//
// for global pool allocator:
// Put IL_MLK_GDECL(); in class declaration
// Put IL_MLK_GDEF(classid) outside the header.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#if defined(__alpha) && !defined(VMS)
#define IL_MLK_ALIGNMENT        16
#define IL_MLK_THRESHOLD        8
#else
#define IL_MLK_ALIGNMENT        8
#define IL_MLK_THRESHOLD        8
#endif

// Number of multiples of the system alignment, specifying the threshold past
// which memory management is delegated to malloc


/*
 * Size of an elementary memory block to allocate for small objects, in number
 * of small object bytes packets. Every time a block of memory is full,
 * another block is allocated whose size is
 * IL_MLK_BLOCK*IL_MLK_THRESHOLD*IL_MLK_ALIGNMENT*IL_MLK_MULT
 */
#define IL_MLK_BLOCK            64
#define IL_MLK_MULT             2

#if defined(IL_STD)
#  include <ostream>
#else  /* !IL_STD */
class ostream;
#endif /* !IL_STD */

class ILOG_EXPORTED IlMemoryManager
{
public:
    IlMemoryManager();
#if defined(WINDOWS)
    ~IlMemoryManager();
#endif /* WINDOWS */
    void*		alloc(IL_SIZE_T);
    void		release(void*, IL_SIZE_T);
    void		status(IL_STDPREF ostream &) const;
    static IlMemoryManager&	GetInstance();

private:
    static inline
    IL_SIZE_T		category(IL_SIZE_T size)
			{
			    return ((size%IL_MLK_ALIGNMENT)
				    ? (size / IL_MLK_ALIGNMENT)
				    : ((size / IL_MLK_ALIGNMENT) - 1));
			}
    static inline
    IL_SIZE_T		alignedSize(IL_SIZE_T size)
			{
			    return ((size%IL_MLK_ALIGNMENT)
				    ? ((size / IL_MLK_ALIGNMENT + 1)
				       * IL_MLK_ALIGNMENT)
				    : size);
			}
#define IL_MLK_FLOC_SIZE (IL_MLK_THRESHOLD + 1)
    void*		_floc[IL_MLK_FLOC_SIZE];
    void*		_scratch;
    void*		_border;
    unsigned int	_blocks;
    unsigned long	_heap;
#if defined(_WIN64)
    IL_SIZE_T		_used;
    IL_SIZE_T		_totalAllocated;
    IL_SIZE_T		_totalFreed;
    IL_SIZE_T		_currentlyUsed;
    IL_SIZE_T		_maxUsed;
#else  /* ! _WIN64 */
    unsigned long	_used;
    int			_totalAllocated;
    int			_totalFreed;
    int			_currentlyUsed;
    int			_maxUsed;
#endif /* ! _WIN64 */
    // No copy constructor
    IlMemoryManager(const IlMemoryManager&);
    // No assignment operator
    IlMemoryManager& operator=(const IlMemoryManager&);
};

/* static before operator delete is facultative */
#define IL_MLK						\
void* operator new(IL_SIZE_T s)				\
{ return IlMemoryManager::GetInstance().alloc(s); }	\
void operator delete(void* a, IL_SIZE_T s)		\
{ IlMemoryManager::GetInstance().release(a, s); }

#define IL_MLK_DECL()				\
void* operator new(IL_SIZE_T);			\
static void operator delete(void*, IL_SIZE_T)

#define IL_MLK_DEF(cl)					\
void* cl::operator new(IL_SIZE_T size)			\
{ return IlMemoryManager::GetInstance().alloc(size); }	\
void cl::operator delete(void* a, IL_SIZE_T s)		\
{ IlMemoryManager::GetInstance().release(a, s); }

#endif /* __Il_Alloc_H */
