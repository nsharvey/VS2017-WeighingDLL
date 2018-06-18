// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/build/datamgnt.h
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
// Declaration of the classes IlvDataBlocks
// Defined in library ilvbuild
// --------------------------------------------------------------------------
#ifndef __Ilv_Build_Datamgnt_H
#define __Ilv_Build_Datamgnt_H

#if !defined(__Ilv_Build_Macros_H)
#include <ilviews/build/macros.h>
#endif
#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

// --------------------------------------------------------------------------
class ILVBLDEXPORTED IlvDataBlocks
{
public:
    IlvDataBlocks(IlvDisplay*,
		  const char* = 0,
		  const char* = 0,
		  IlBoolean  = IlTrue);
    virtual ~IlvDataBlocks();
    // ____________________________________________________________
    virtual void	write(const char*, IlUShort = 0);
    virtual IlBoolean	read(const char*);

    virtual IlBoolean	checkFile(const char*);

    virtual void	addDataBlock(const char*, const char*);
    virtual IlBoolean	removeDataBlock(const char*);
    virtual IlBoolean	replaceDataBlock(const char*,
					 const char*,
					 const char*);
    const char*		getDataBlockFile(const char*) const;
    const char* const*	getKeys(IlUInt&) const;

    virtual void	writeHeader() const;
    virtual IlBoolean	readHeader(IL_STDPREF istream* = 0);

    virtual void	writeDataBlocksHeader() const;
    virtual IlBoolean	readDataBlocksHeader();

    virtual void	writeUnixDataBlock(const char*,
					   IL_STDPREF ostream*,
					   IL_STDPREF istream*,
					   IlUInt = 0) const;
    virtual void	writeUnixDataBlocks();
    virtual void	writeWindowsDataBlock(const char*,
					      IL_STDPREF ostream*,
					      IL_STDPREF istream*,
					      IlUInt = 0) const;
    virtual void	writeWindowsDataBlocks();

protected:
    IlBoolean		isUnixMachine() const { return _unixMachine; }
    void		storeOffset(IL_STDPREF istream*, IlAList* = 0);
    IlUInt		getOffset(const char*) const;

    IlBoolean		checkFileStruct(IL_STDPREF istream*);

    IlvDisplay*		_display;
    IlvStringHashTable*	_resTable;
    IlPathName*		_codeFile;
    IlPathName*		_oldCodeFile;
    IL_STDPREF ostream*	_outFile;
    IL_STDPREF istream*	_inFile;
    IlBoolean		_unixMachine;
    IlAList*		_offsetList;
};

#endif /* ! __Ilv_Build_Datamgnt_H */
