// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/mapoutput.h
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
// Rogue Wave Views - Maps add-on.
// ilog.views.maps.format
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Format_IlvMapOutput_H
#define __ILV_maps_Format_IlvMapOutput_H

#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/base/iostream.h>

#ifndef IL_STD
#include <iostream.h>
#include <fstream.h>
#else
#include <iostream>
#include <fstream>
IL_STDUSE
#endif

ILVMAPSMODULEINIT(format_IlvMapOutput);

// --------------------------------------------------------------------------
// Class IlvMapOutput
// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvMapOutput
{
public:

    IlvMapOutput(IL_STDPREF ofstream& stream);

    IlvMapOutput(const char* fileName);

    virtual ~IlvMapOutput();

    inline IlvMapsError getLastError() { return _lastError; }

    inline
    IL_STDPREF ofstream* getStream() const
			{
			    return (IL_STDPREF ofstream*) &_stream;
			}

    inline IlvMapsError	writeLittleInt(IlInt value)
			{
			    return IsLSBFirst()
				? writeInt(value)
				: invertAndWriteInt(value);
			}

    inline IlvMapsError	writeBigInt(IlInt value)
			{
			    return IsLSBFirst()
				? invertAndWriteInt(value)
				: writeInt(value);
			}

    inline IlvMapsError writeLittleDouble(IlDouble value)
			{
			    return IsLSBFirst()
				? writeDouble(value)
				: invertAndWriteDouble(value);
			}

    inline IlvMapsError writeBigDouble(IlDouble value) 
			{
			    return IsLSBFirst()
				? invertAndWriteDouble(value)
				: writeDouble(value);
			}

    IlvMapsError	flush();
    IlvMapsError	close();    
    IlvMapsError	seek(streampos off);
    IlvMapsError	size(streampos& size);
    inline
    static IlBoolean	IsLSBFirst() { return _isLSBFirst; }

private:

    IlvMapsError	updateStatus(int rdstate);
    IlvMapsError	writeInt(IlInt value);
    IlvMapsError	invertAndWriteInt(IlInt value);
    IlvMapsError	invertAndWriteDouble(IlDouble value);
    IlvMapsError	writeDouble(IlDouble value);

    static void		Init();

    IlvMapsIcFriend(format_IlvMapOutput, ILVMAPSEXPORTED);

    static IlvMapsError	_WriteError;
    static IlBoolean	_isLSBFirst;

    IL_STDPREF
    ofstream&		_stream;
    IlvMapsError	_lastError;
    IlInt		_index; 
    IlBoolean		_ownStream;

};

#endif
