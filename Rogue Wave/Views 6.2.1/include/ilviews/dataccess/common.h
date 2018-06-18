// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/common.h
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
// Inclusion of commonly used header files
// --------------------------------------------------------------------------
#ifndef __Ili_Common_H
#define __Ili_Common_H

#ifndef __Ilv_Macros_H
#  include <ilviews/macros.h>
#endif

#ifdef IL_STD
#  include <iostream>
#else
#  include <iostream.h>
#endif

#ifndef __Ilv_H
#  include <ilviews/ilv.h>
#endif

#ifndef __Ili_Collect_H
#  include <ilviews/dataccess/collect.h>
#endif

#ifndef __Ili_String_H
#  include <ilviews/dataccess/string.h>
#endif

#ifndef __Ili_Refcount_H
#  include <ilviews/dataccess/refcount.h>
#endif

#ifndef __Ili_Util_H
#  include <ilviews/dataccess/util.h>
#endif

#if defined(_MSC_VER)
#  if !defined(ILI_BUILDLIBS)
#    pragma comment(lib, "dataccess")
#  endif
#endif

#endif
