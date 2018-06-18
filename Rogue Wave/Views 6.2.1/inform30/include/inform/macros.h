// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/macros.h
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
#ifndef __Ili_Compat_Macros_H
#define __Ili_Compat_Macros_H

#include <ilviews/dataccess/macros.h>

#if defined(ILVLIB_dbstinform30)
#  define ILV_STINFORM30_EXPORTED ILI_BASE_EXPORTED
#  define ILV_STINFORM30_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_STINFORM30_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if defined(ILVLIB_inform30)
#  define ILV_INFORM30_EXPORTED ILI_BASE_EXPORTED
#  define ILV_INFORM30_EXPORTEDFN(type)  ILV_DEF_EXPORTEDFN(type)
#  define ILV_INFORM30_EXPORTEDVAR(type) ILV_DEF_EXPORTEDFN(type)
#  ifndef ILI_BUILDLIBS
#    define ILI_BUILDLIBS
#  endif
#endif

#if !defined(ILV_STINFORM30_EXPORTED)
#  define ILV_STINFORM30_EXPORTED ILI_BASE_IMPORTED
#  define ILV_STINFORM30_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_STINFORM30_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if !defined(ILV_INFORM30_EXPORTED)
#  define ILV_INFORM30_EXPORTED ILI_BASE_IMPORTED
#  define ILV_INFORM30_EXPORTEDFN(type)  ILV_DEF_IMPORTEDFN(type)
#  define ILV_INFORM30_EXPORTEDVAR(type) ILV_DEF_IMPORTEDFN(type)
#endif

#if defined(WINDOWS) && !defined(WIN32)
#  ifdef ILI_COMPAT_PREFIX
#    define ILVSW_NOSTATICDATA
#  endif
#endif

#endif


