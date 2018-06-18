// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/compilrs.h
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
#ifndef __Ilv31_Variable_Compilrs_H
#define __Ilv31_Variable_Compilrs_H

#include <ilviews/variable/adapter.h>

#if !defined(ILVV_USE_STREAMPATCH)
// on alpha:
// cannot use ends or '\0', ostrstreams are buggy
// cannot use pcount, buggy also
#  if defined(alpha)
#    define ILVV_USE_STREAMPATCH
#  endif
#endif

#endif
