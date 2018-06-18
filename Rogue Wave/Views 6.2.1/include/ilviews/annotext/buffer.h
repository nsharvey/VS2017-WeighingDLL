// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/buffer.h
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
// Declaration of the IlvATBuffer class
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Buffer_H
#define __Ilv_Annotext_Buffer_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Annotext_Atmacros_H)
#  include <ilviews/annotext/atmacros.h>
#endif

#define IlvATBufferLength 1024
#define IlvATBufferNumzones 100

class ILVATEXPORTED IlvATTextRope;
class IlvATBufExtension;

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATBuffer
{
public:
    IlvATBuffer(IlUInt   length   = IlvATBufferLength,
		IlUShort numzones = IlvATBufferNumzones);
    ~IlvATBuffer();
    // ____________________________________________________________
    inline IlUInt	getLength() const		{ return _length; }
    inline void		setLength(IlUInt length)	{ _length = length; }
    inline const char*	getZone(IlUShort i) const	{ return _zones[i]; }
    inline void		setZone(IlUShort i, const char* z) { _zones[i] = z; }
    inline 
    const char* const*	getZones() const		{ return _zones; }
    inline void		setZones(const char** zones)	{  _zones = zones; }
    inline IlUShort	getNumZones() const		{ return _numZones; }
    inline void		setNumZones(IlUShort nb)	{ _numZones = nb; }
    inline IlUShort	getFreeZone() const		{ return _freeZone; }
    inline void		setFreeZone(IlUShort fz)	{ _freeZone = fz; }
    inline void		incFreeZone()			{ _freeZone++; }
    inline const char*	getFree() const			{ return _free; }
    inline void		setFree(const char* free)	{ _free = free; }
    inline void		incFree()			{ _free++; }
    inline IlUInt	getFreeLength() const	      { return _freeLength; }
    inline void		setFreeLength(IlUInt fl)	{ _freeLength = fl; }
    inline void		decFreeLength()			{ _freeLength--; }

    IlvATPos		appendText(const char* c, IlvATPos len);
    void		appendChar(char c);
    void		allocateZone();
    IlBoolean		isAtEnd(IlvATTextRope*);
    void		clear();
    IlUInt		compactZones();
    inline IlUInt	getRef(IlUShort i) const { return _refCount[i]; }
    inline void		incRef(IlUShort i)		{ _refCount[i]++; }
    inline void		decRef(IlUShort i)		{ _refCount[i]--; }

    inline IlvATBufExtension*	getExtension() const   { return _extension; }

private:
    friend class IlvATBufExtension;

    IlUInt		_length;	// Length of each text zone
    const char**	_zones;		// Array of text zones
    IlUShort		_numZones;	// Length of above table
    IlUShort		_freeZone;	// Index of the first free zone
    const char*		_free;		// Start of the unused zone
					// (of the last text zone allocated)
    IlUInt		_freeLength;	// Length of the unused zone
					// (of the last text zone allocated)
    IlUInt*		_refCount;	// Table of references per zone
    IlvATBufExtension*  _extension;
};

#endif /* !__Ilv_Annotext_Buffer_H */
