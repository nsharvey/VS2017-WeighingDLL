// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/assert.h
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
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Assert_H
#define __Ilv31_Variable_Assert_H

#include <assert.h>

#if defined(__alpha) && !defined(WIN32)
#  if defined(ILVDEBUG)
#  define ILVV_ASSERT(EX)
# else
// cast into integer otherwise
#  define ILVV_ASSERT(EX) ((EX)?(void)0:__assert(#EX,__FILE__,__LINE__))
# endif
#else
# define ILVV_ASSERT(EX) assert(EX)
#endif

#endif
