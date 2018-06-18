// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/streamer.h
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
// Declaration of bitmap streaming utilities 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Streamer_H
#define __Ilv_Bitmaps_Streamer_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Bitmaps_Data_H)
#  include <ilviews/bitmaps/data.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Bitmaps_Quantize_H_)
#  include <ilviews/bitmaps/quantize.h>
#endif

class IlvBitmapStreamer;
class IlvBitmapInformation;
typedef void (*IlvProgressCallback)(IlvBitmapStreamer* obj,
				    IlUInt current,
				    IlUInt max,
				    IlAny);

// --------------------------------------------------------------------------
IlDefineListOf(IlvBitmapStreamers, IlvBitmapStreamer*);
class ILVDSPEXPORTED IlvBitmapStreamer
: public IlvValueInterface
{
public:
    virtual ~IlvBitmapStreamer();

    virtual IlBoolean	canRead() const;
    virtual IlBoolean	canWrite() const;
    virtual IlBoolean	checkSignature(const IlUChar* data, 
				       IlUInt         size) = 0;
    virtual
    IlvBitmapData*	read(IL_STDPREF istream& stream);
    virtual
    IlvBitmapInformation* readInfo(IL_STDPREF istream& stream);
    virtual IlBoolean	write(IlvBitmapData* bitmapData, 
			      IL_STDPREF     ostream& stream);
    virtual void     setReadProgressCallback(IlvProgressCallback rpCallback, 
					     IlAny arg = 0);

    virtual void	callReadProgressCallback(IlUInt current, 
						 IlUInt max);
    virtual void     setWriteProgressCallback(IlvProgressCallback wpCallback,
					      IlAny arg = 0);
    virtual void	callWriteProgressCallback(IlUInt current,
						  IlUInt max);
    virtual const char*	getName() const;
    void		setQuantizer(IlvQuantizer* quantizer);
    IlvQuantizer*	getQuantizer() const;
    static void		Register(IlvBitmapStreamer* streamer);
    static IlBoolean	UnRegister(IlvBitmapStreamer* streamer);
    static
    IlvBitmapStreamer*	Get(const char* name);
    static IlvBitmap*	Read(IlvDisplay*	 display,
			     IL_STDPREF istream& stream,
			     const IlUChar*	 signature,
			     IlUInt		 signatureLen);
    static
    IlvBitmapData*	ReadBitmapData(IL_STDPREF istream& stream,
				       const IlUChar*	   signature,
				       IlUInt		   signatureLen);
    static
    IlvBitmapInformation* ReadInfo(IL_STDPREF istream&	stream,
				   const IlUChar*	signature,
				   IlUInt		signatureLen);
    static
    IlvBitmapStreamer** GetRegisteredStreamers(IlUInt& count);
    static IlBoolean	CheckInModules(const IlUChar*, const IlUChar* = 0);

    static IlListOf(IlvBitmapStreamers)*	_Streamers;

protected:
    IlvBitmapStreamer();

    IlvProgressCallback	_readProgressCallback;
    IlAny		_argr;
    IlvProgressCallback	_writeProgressCallback;
    IlAny		_argw;
    IlvQuantizer*	_quantizer;
};

IL_MODULETERM(streamer, ILVDSPEXPORTED);

#endif /* __Ilv_Bitmaps_Streamer_H */
