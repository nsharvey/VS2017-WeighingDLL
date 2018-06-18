// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/file.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the VpfFile class
// --------------------------------------------------------------------------
#ifndef VPF_FILE_H
#define VPF_FILE_H

#include <ilviews/macros.h>
#include <vpf/basictypes.h>
#include <stdio.h>

#if defined(sun) && !defined(__SVR4)
#include <unistd.h>
#endif

class VpfCoordinate;
class VpfDate;
class VpfTripletID;

// --------------------------------------------------------------------------
class VpfFile
{
public:
    VpfFile(const char*, const char*);
    ~VpfFile();
    static FILE* OpenFile(const char *name, const char *mode);
    // ____________________________________________________________
    int isBad() const { return !_file; }
    void setBad() { if (_file) fclose(_file); _file = 0; }

    int readText(char*, char = 'T', VpfUInt = 1, int = 1);
    int readInteger(VpfInt*, char = 'I', VpfUInt = 1);
    int readFloat(double*, char = 'L', VpfUInt = 1);
    int readDate(VpfDate*, VpfUInt = 1);
    int readCoordinate(VpfCoordinate*, char = 'C', VpfUInt = 1);
    int readTripletPart(int size, VpfInt& value);
    int readTripletID(VpfTripletID* triplet, VpfUInt count);
    
    void setSwap(int swap) { _swap = swap; }
    int isSwapping() const { return _swap; }

    int seek(long offset, int origin)
	{ return ::fseek(_file, offset, origin); }
    long ftell() { return ::ftell(_file); }
    void rewind() { ::rewind(_file); }
    size_t fread(void* buffer, size_t size, size_t count)
	{ return ::fread((char*)buffer, size, count, _file); }

    long length()
	{
	    long current = ftell();
	    seek(0, SEEK_END);
	    long result = ftell();
	    seek(current, SEEK_SET);
	    return result;
	}
protected:
    FILE*	_file;
    int		_swap;
};

#endif /* VPF_FILE_H */
