// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/iurlstr.h
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
// Declaration of the IlIUrlStream class
// --------------------------------------------------------------------------
#ifndef __Il_Iurlstr_H
#define __Il_Iurlstr_H

#if !defined(__Il_Macros_H)
#  include <ilog/macros.h>
#endif
#if defined(IL_STD)
#  include <istream>
#else  /* !IL_STD */
#  include <iostream.h>
#endif /* !IL_STD */

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlIUrlStream
: public IL_STDPREF istream
{
public:
    enum StreamHint {
	Normal = 0,
	NoRandomAccess
    };
    IlIUrlStream(const char* url, IlBoolean binaryMode = IlFalse);
    IlIUrlStream(IL_STDPREF istream&);
    IlIUrlStream(IL_STDPREF istream*);
    virtual ~IlIUrlStream();
    // ____________________________________________________________
    const char*		getHeader() const;
    static IlBoolean	IsAnURL(const char* name);
    void		setBufferLimit(IlUInt sizelimit);
    IlUInt		getBufferLimit() const;
    void		setHints(StreamHint hints);
    StreamHint		getHints() const;
private:
    // No copy constructor
    IlIUrlStream(const IlIUrlStream&);
};

#endif /* !__Il_Iurlstr_H */
