// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/mapinput.h
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
#ifndef __Ilv_Maps_Format_Mapinput_H
#define __Ilv_Maps_Format_Mapinput_H

#if !defined(__Ilv_Maps_H)
#  include <ilviews/maps/maps.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

ILVMAPSMODULEINIT(format_IlvMapInput);

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvMapInput
{
public:
    IlvMapInput(IL_STDPREF istream& istr);
    IlvMapInput(const char* fileName);

    virtual ~IlvMapInput();

    IL_STDPREF istream*	getStream() const
			{
			    return (IL_STDPREF istream*) &_stream;
			}

    IlvMapsError	readUnsignedByte(IlUChar& value);

    IlvMapsError	readByte(char& value) ;

    IlvMapsError	readLittleDouble(IlDouble& value)
			{
			    return IsLSBFirst()
				? readDouble(value)
				: readAndInvertDouble(value);
			}

    IlvMapsError	readBigDouble(IlDouble& value) 
			{
			    return IsLSBFirst()
				? readAndInvertDouble(value)
				: readDouble(value);
			}

    IlvMapsError	readLittleDoubleArray(const IlDouble* values,
					      IlInt count)
			{
			    return IsLSBFirst()
				? readDoubleArray(values, count)
				: readAndInvertDoubleArray(values, count);
			}

    IlvMapsError	readBigDoubleArray(const IlDouble* values,
					   IlInt count) 
			{
			    return IsLSBFirst()
				? readAndInvertDoubleArray(values, count)
				: readDoubleArray(values, count);
			}

    IlvMapsError	readLittleInt(IlInt& value)
			{
			    return IsLSBFirst()
				? readInt(value)
				: readAndInvertInt(value);
			}
    IlvMapsError	readBigInt(IlInt& value)
			{
			    return IsLSBFirst()
				? readAndInvertInt(value)
				: readInt(value);
			}

    IlvMapsError	readLittleIntArray(const IlInt* values, IlInt count)
			{
			    return IsLSBFirst()
				? readIntArray(values, count)
				: readAndInvertIntArray(values, count);
			}

    IlvMapsError	readBigIntArray(const IlInt* values, IlInt count)
			{
			    return IsLSBFirst()
				? readAndInvertIntArray(values, count)
				: readIntArray(values, count) ;
			}

    IlvMapsError	readBigUnsignedInt(IlUInt& value)
			{
			    return IsLSBFirst()
				? readAndInvertUInt(value)
				: readUInt(value);
			}

    IlvMapsError	readBigUnsignedIntArray(const IlUInt* values,
						IlInt count)
			{
			    return IsLSBFirst()
				? readAndInvertUIntArray(values, count)
				: readUIntArray(values, count);
			}

    IlvMapsError	readLittleShort(IlShort& value)
			{
			    return IsLSBFirst()
				? readShort(value)
				: readAndInvertShort(value);
			}

    IlvMapsError	readBigShort(IlShort& value)
			{
			    return IsLSBFirst()
				? readAndInvertShort(value)
				: readShort(value);
			}

    IlvMapsError	readLittleShortArray(const IlShort* values,
					     IlInt count)
			{
			    return IsLSBFirst()
				? readShortArray(values, count)
				: readAndInvertShortArray(values, count);
			}

    IlvMapsError	readBigShortArray(const IlShort* values, IlInt count)
			{
			    return IsLSBFirst()
				? readAndInvertShortArray(values, count)
				: readShortArray(values, count);
			}

    IlvMapsError	readBigUnsignedShort(IlUShort& value)
			{
			    return IsLSBFirst()
				? readAndInvertUShort(value)
				: readUShort(value);
			}

    IlvMapsError	read(char* data, int length);

    IlvMapsError	skipBytes(IlInt n);

    IlvMapsError	setLocation(IlInt loc)
			{
			    return skipBytes(loc - _index);
			}

    IlInt		getIndex() const { return _index; }

    IlvMapsError	getLastError() const { return _lastError; }

    // not documented
    void		clearError() { _lastError = IlvMaps::NoError(); }

    static IlvMapsError EndOfFileError() { return _EOFError; }
    static IlvMapsError ReadError() { return _ReadError; }

    static IlBoolean	IsLSBFirst() { return _isLSBFirst; }

private:
    IlvMapInput& operator=(const IlvMapInput&);

    IlvMapsError	updateStatus(int rdstate);
    IlvMapsError	readAndInvertDouble(IlDouble& value);
    IlvMapsError	readDouble(IlDouble& value);
    IlvMapsError	readDoubleArray(const IlDouble* values, IlInt count);
    IlvMapsError	readAndInvertDoubleArray(const IlDouble* values,
						 IlInt count);

    IlvMapsError	readAndInvertInt(IlInt& value);
    IlvMapsError	readInt(IlInt& value);
    IlvMapsError	readAndInvertIntArray(const IlInt* values,
					      IlInt count);
    IlvMapsError	readIntArray(const IlInt* values, IlInt count);

    IlvMapsError	readAndInvertUInt(IlUInt& value);
    IlvMapsError	readUInt(IlUInt& value);
    IlvMapsError	readAndInvertUIntArray(const IlUInt* values,
					       IlInt count);
    IlvMapsError	readUIntArray(const IlUInt* values, IlInt count);

    IlvMapsError	readAndInvertShort(IlShort& value);
    IlvMapsError	readShort(IlShort& value);
    IlvMapsError	readAndInvertShortArray(const IlShort* values,
						IlInt count);
    IlvMapsError	readShortArray(const IlShort* values, IlInt count);

    IlvMapsError	readAndInvertUShort(IlUShort& value);
    IlvMapsError	readUShort(IlUShort& value);

    void		invertDouble(char* pointer) const;
    void		invertInt(char* value) const;
    void		invertShort(char* value) const;

    static void		Init();

    IlvMapsIcFriend(format_IlvMapInput, ILVMAPSEXPORTED);

    static IlvMapsError	_EOFError;
    static IlvMapsError	_ReadError;
    static IlBoolean	_isLSBFirst;

    IL_STDPREF istream& _stream;
    IlvMapsError	_lastError;
    IlInt		_index;
    IlBoolean		_ownStream;

};
#endif /* __Ilv_Maps_Format_Mapinput_H */
