// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/streams.h
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
#ifndef __Ilv31_Variable_Streams_H
#define __Ilv31_Variable_Streams_H

#include <ilviews/variable/compilrs.h>

#include <ilviews/variable/ostreams.h>

#if defined(ILVSTD)
# include <strstream>
ILVSTDUSE;
#else  /* !ILVSTD */
#if defined(ILVFATFILENAMES)
# include <strstrea.h>
#else  /* !ILVFATFILENAMES */
# include <strstream.h>
#endif /* !ILVFATFILENAMES */
#endif /* !ILVSTD */

#if !defined(ILVV_USE_STREAMPATCH)
#  if defined(IL_SUNCC2_1)
// 2.1 is very buggy on strstreams
// ostrstream is not initializing the field ios::ospecial,
// used by output operations on char's.
// after allocating an ostrstream, must call this macro
class IlvvOStrStream:
public ILVSTDPREF ostrstream
{
 public:
   IlvvOStrStream(char* str, int size, int m=ios::out):
   ILVSTDPREF ostrstream(str,size,m)
   {
      ospecial=0;
   }
   IlvvOStrStream():
   ILVSTDPREF ostrstream()
   {
      ospecial=0;
   }
   char* str(){
     *this<<ends;
     return ILVSTDPREF ostrstream::str();
   }
};
#  else
class IlvvOStrStream:
public ILVSTDPREF ostrstream
{
 public:
   IlvvOStrStream(char* str, int size, int m=ios::out):
   ILVSTDPREF ostrstream(str,
			 size,
#if defined(linux) && (__GNUC__ >= 3)
			 (std::_Ios_Openmode)
#endif /* linux gcc3 */
			 m),
   _str(0)
     {}
   IlvvOStrStream():
   _str(0)
     {}
   char* str();
 private:
   char* _str;
};
#  endif
#endif

#endif
