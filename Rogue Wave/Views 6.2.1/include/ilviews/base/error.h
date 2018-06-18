// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/error.h
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
// Declaration of the IlvError class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Error_H
#define __Ilv_Base_Error_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if defined(ILVSTD)
#include <iostream>
#else // !ILVSTD
#include <iostream.h>
#include <string.h>
#endif

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvError
{
public:
    virtual ~IlvError();
    // ____________________________________________________________
    virtual void	message(const char* message) const;
    virtual void	fatal(const char* message) const;
    virtual void	warning(const char* message) const;
};

extern "C" {
ILVDSPEXPORTEDFUNCTION(void)
IlvSetErrorHandler(IlvError*);
ILVDSPEXPORTEDFUNCTION(IlvError*)
IlvGetErrorHandler();
}

// ------------------------------------------------------------------------
class IlvStreamBuf : public ILVSTDPREF streambuf
{
public:
    enum OutputType { Message, Warning, Fatal };
    IlvStreamBuf(OutputType outputType);
    IlvStreamBuf(const IlvStreamBuf& buf);
    ~IlvStreamBuf();
    // ____________________________________________________________
    virtual int		overflow(int ch);
    virtual int		underflow();
protected:
    void		myputchar(char c);
    void		flush();
    void		allocateNewBuffer();
private:
    char*		_buffer;
    int			_size;
    int			_length;
    OutputType		_outputType;
};

// ------------------------------------------------------------------------
class IlvOut : public ILVSTDPREF ostream
{
public:
    IlvOut(IlvStreamBuf::OutputType outputType = IlvStreamBuf::Message);
    IlvOut(const IlvOut& o);
    ~IlvOut();
    // ____________________________________________________________
    IlvStreamBuf*	rdbuf() const;

private:
    IlvStreamBuf	_ilvbuf;
};

extern ILVDSPEXPORTEDVAR(IlvOut) IlvCOut;
extern ILVDSPEXPORTEDVAR(IlvOut) IlvCErr;
extern ILVDSPEXPORTEDVAR(IlvOut) IlvCWarn;

#endif /* !__Ilv_Base_Error_H */
