// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/intl.h
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
#ifndef __Ili_Compat_Intl_H
#define __Ili_Compat_Intl_H

#include <ilviews/dataccess/intl.h>

#ifdef ILI_COMPAT_PREFIX
#  define IlvSwWideCharGenerator  IliWideCharGenerator
#  define IlvSwIsMultibyte        IliIsMultibyte
#  define IlvSwChToWc             IliChToWc
#  define IlvSwMbLen              IliMbLen
#  define IlvSwSafeStrStr         IliSafeStrStr
#  define IlvSwMbStringLength     IliMbStringLength
#  define IlvSwMbToChar           IliMbToChar
#  define IlvSwMbToWc             IliMbToWc
#  define IlvSwWcToMb             IliWcToMb
#  define IlvSwIsAscii            IliIsAscii
#  define IlvSwWCharToChar        IliWCharToChar
#  define IlvSwIsSpace            IliIsSpace
#  define IlvSwIsDigit            IliIsDigit
#  define IlvSwIsAlpha            IliIsAlpha
#  define IlvSwIsAlnum            IliIsAlnum
#  define IlvSwIsUpper            IliIsUpper
#  define IlvSwIsLower            IliIsLower
#  define IlvSwToUpper            IliToUpper
#  define IlvSwToLower            IliToLower
#  define IlvSwWideCharGenerator          IliWideCharGenerator
#  define IlvSwIstreamWideCharGenerator   IliIstreamWideCharGenerator
#  define IlvSwStringWideCharGeneratorRef IliStringWideCharGeneratorRef
#  define IlvSwStringWideCharGenerator    IliStringWideCharGenerator
#  define IlvSwRevStringWideCharGenerator IliRevStringWideCharGenerator
#  define ILVSW_MB_LEN_MAX ILI_MB_LEN_MAX
#endif

#endif
