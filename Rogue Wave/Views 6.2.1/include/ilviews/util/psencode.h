// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/psencode.h
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
// Definition of the IlvPostScriptEncoder classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Postscript_Encoder_H
#define __Ilv_Util_Postscript_Encoder_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
#if !defined(__Il_String_H)
#include <ilog/string.h>
#endif

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvPostScriptEncoder
{
public:
    virtual ~IlvPostScriptEncoder();

    virtual const char* getPostScriptDecoderName() const = 0;
    static IlString    GetFullDecoderString(const IlvPostScriptEncoder* pse);
    virtual void	consumeByte(IlUChar byte) = 0;
    virtual void	consumeBytes(IlUInt count, IlUChar const* bytes);
    virtual void	init();
    virtual void	flush();
    virtual void	setStream(ILVSTDPREF ostream* stream);
    ILVSTDPREF ostream*	getStream() const;
    virtual void	emitByte(IlUChar byte);
    virtual void	emitBytes(IlUInt count, IlUChar const* bytes);
    void		setEmitter(IlvPostScriptEncoder* emitter);
    IlvPostScriptEncoder* getEmitter() const;

protected:
    IlvPostScriptEncoder(ILVSTDPREF ostream* stream = 0);

protected:
    ILVSTDPREF ostream*		_stream;
    IlvPostScriptEncoder*	_emitter;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvASCIIHexEncoder
    : public IlvPostScriptEncoder
{
public:
    IlvASCIIHexEncoder(ILVSTDPREF ostream* stream = 0, 
		       IlBoolean           flush  = IlTrue);

    virtual const char*	getPostScriptDecoderName() const;
    virtual void	consumeByte(IlUChar byte);
    virtual void	init();
    virtual void	flush();

protected:
    IlUInt		_count;
    IlBoolean		_flush;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvASCII85Encoder
    : public IlvPostScriptEncoder
{
public:
    IlvASCII85Encoder(ILVSTDPREF ostream* stream = 0);
    virtual ~IlvASCII85Encoder();

    virtual const char*	getPostScriptDecoderName() const;
    virtual void	consumeByte(IlUChar byte);
    virtual void	init();
    virtual void	flush();

protected:
    IlUInt		_count;
    IlUInt		_outcount;
    IlUChar		_buffer[4];

private:
    IlUChar		_output[5];
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvRunLengthEncoder
    : public IlvPostScriptEncoder
{
public:
    IlvRunLengthEncoder(ILVSTDPREF ostream* stream = 0);
    virtual ~IlvRunLengthEncoder();

    virtual const char*	getPostScriptDecoderName() const;
    virtual void	consumeByte(IlUChar byte);
    virtual void	init();
    virtual void	flush();

protected:
    IlUChar		_buffer[128];
    IlUInt		_count;
    IlBoolean		_isARun;
};

#endif /* !__Ilv_Util_Postscript_Encoder_H */
