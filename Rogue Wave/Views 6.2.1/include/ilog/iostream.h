// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/iostream.h
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
// Forward declaration of the iostream classes
// --------------------------------------------------------------------------
#ifndef __Il_Iostream_H
#define __Il_Iostream_H

#ifndef __Il_Macros_H
#include <ilog/macros.h>
#endif

#if defined(IL_STD)
#if defined(_MSC_VER)
#include <wchar.h>
#endif
#include <iostream>
#if (defined(WINDOWS) || defined(PM)) && !defined(MAINWIN)
#define IlInputStreamMode  (std::ios::in|std::ios::binary)
#define IlOutputStreamMode (std::ios::out|std::ios::binary)
#define IlBinaryInputStreamMode  (std::ios::in|std::ios::binary)
#define IlBinaryOutputStreamMode (std::ios::out|std::ios::binary)
#else  /* (!WINDOWS && !PM) || MAINWIN */
#define IlInputStreamMode  (std::ios::in)
#define IlOutputStreamMode (std::ios::out)
#define IlBinaryInputStreamMode  IlInputStreamMode
#define IlBinaryOutputStreamMode IlOutputStreamMode
#endif /* (!WINDOWS && !PM) || MAINWIN */
#else  /* !IL_STD */
#  if defined(__SUNPRO_CC_COMPAT) && (__SUNPRO_CC_COMPAT >= 5)
#     include <iostream.h>
#  else
class istream;
class ostream;
#  endif
#if (defined(WINDOWS) || defined(PM)) && !defined(MAINWIN)
#define IlInputStreamMode  (ios::in|ios::binary)
#define IlOutputStreamMode (ios::out|ios::binary)
#define IlBinaryInputStreamMode  (ios::in|ios::binary)
#define IlBinaryOutputStreamMode (ios::out|ios::binary)
#else  /* (!WINDOWS && !PM) || MAINWIN */
#define IlInputStreamMode  (ios::in)
#define IlOutputStreamMode (ios::out)
#define IlBinaryInputStreamMode  IlInputStreamMode
#define IlBinaryOutputStreamMode IlOutputStreamMode
#endif /* (!WINDOWS && !PM) || MAINWIN */
#endif /* !IL_STD */

#endif /* !__Il_Iostream_H */
