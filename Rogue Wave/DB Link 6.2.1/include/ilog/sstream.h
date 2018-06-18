// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/sstream.h
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
// Forward declaration of the strstream classes
// --------------------------------------------------------------------------
#ifndef __Il_Sstream_H
#define __Il_Sstream_H

#ifndef __Il_Macros_H
#include <ilog/macros.h>
#endif

#undef IL_USING_STRINGSTREAM
#if defined(IL_STD)
#if 0 && (defined(linux) && ((__GNUC__>3) || ((__GNUC__==3)&&(__GNUC_MINOR__>=2))))
// Disabled section, left here as a reminder.
// <strstream> is deprecated in C++ standard and causes gcc3.2 compilation
// warnings.
// The use of <sstream> on gcc3.2+ suppresses the warnings but may raise some
// compatibility issues for old code.
// Better keep the warnings or compile with -Wno-deprecated.
#  include <sstream>
#define IL_USING_STRINGSTREAM
namespace std {
typedef basic_stringstream<char>  strstream;
typedef basic_istringstream<char> istrstream;
typedef basic_ostringstream<char> ostrstream;
} /* namespace std */
#else  /* !linux, gcc >= 3.2 */
#  include <strstream>
#endif /* !linux, gcc >= 3.2 */
#else  /* !IL_STD */
#  if defined(IL_FATFILENAMES)
#    include <strstrea.h>
#  else  /* !IL_FATFILENAMES */
#    include <strstream.h>
#  endif /* !IL_FATFILENAMES */
#endif /* !IL_STD */

#endif /* !__Il_Sstream_H */
