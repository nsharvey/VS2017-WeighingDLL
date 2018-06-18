// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/file.h
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
// Declaration of the VpfFile class
// --------------------------------------------------------------------------
#ifndef VPF_FILE_H
#define VPF_FILE_H

#include <vpf/basictypes.h>

#if defined(ILVSTD)
# include <cstdio>
#else
# include <stdio.h>
#endif

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
    // ____________________________________________________________
    inline int	isBad() const { return !_file; }
    inline void	setBad() { if (_file) fclose(_file); _file = 0; }

    int		readText(char*, char = 'T', VpfUInt = 1, int = 1);
    int		readInteger(VpfInt*, char = 'I', VpfUInt = 1);
    int		readFloat(double*, char = 'L', VpfUInt = 1);
    int		readDate(VpfDate*, VpfUInt = 1);
    int		readCoordinate(VpfCoordinate*, char = 'C', VpfUInt = 1);
    int		readTripletPart(int size, VpfInt& value);
    int		readTripletID(VpfTripletID* triplet, VpfUInt count);

    inline void setSwap(int swap) { _swap = swap; }
    inline int	isSwapping() const { return _swap; }

    inline int	seek(long offset, int origin)
		{
		    return ::fseek(_file, offset, origin);
		}
    inline long	ftell() { return ::ftell(_file); }
    inline void	rewind() { ::rewind(_file); }
    inline size_t	fread(void* buffer, size_t size, size_t count)
			{
			    return ::fread((char*)buffer, size, count, _file);
			}

    inline long	length()
		{
		    long current = ftell();
		    seek(0, SEEK_END);
		    long result = ftell();
		    seek(current, SEEK_SET);
		    return result;
		}
    static FILE*	OpenFile(const char *name, const char *mode);

protected:
    FILE*	_file;
    int		_swap;
};

#endif /* VPF_FILE_H */
