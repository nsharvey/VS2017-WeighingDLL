// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/cellio.h
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
// Declaration of the IlvCellOutputFile and IlvCellInputFile classes
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Cellio_H
#define __Ilv31_Cellio_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Util_Util_H)
#include <ilviews/util/util.h>
#endif
#if !defined(__Ilv31_Cellgr_H)
#include <ilviews/cellgr.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif

class IlvCellOutputFile;
class IlvCellInputFile;

typedef IlvCell* (*IlvCellConstructor)(IL_STDPREF istream&,
				       IlvPalette* palette);
extern int IlvRegisterCellConstructor(const char* className,
				      IlvCellConstructor);
extern  IlvCellConstructor IlvGetCellConstructor(const char* className);

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellOutputFile
{
public:
    IlvCellOutputFile(ILVSTDPREF ostream&);
    virtual ~IlvCellOutputFile();
    // ____________________________________________________________
    inline IL_STDPREF ostream& getStream()            { return *_ostream;   }
    inline void setStream(ILVSTDPREF ostream& stream) { _ostream = &stream; }
    virtual void save(IlvCellManager* cellmgr,
		      IlUShort fromCol, IlUShort toCol,
		      IlUShort fromRow, IlUShort toRow);
    virtual void writeCell(IlvCell*);
protected:
    IL_STDPREF ostream*	_ostream;
    IlUInt		_numpalettes;
    IlvHashTable*	_palettes;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellInputFile
: public IlvBaseInputFile
{
public:
    IlvCellInputFile(IL_STDPREF istream&);
    virtual ~IlvCellInputFile();
    // ____________________________________________________________
    virtual void read(IlvCellManager*,
		      IlUShort colOrig = 0,
		      IlUShort rowOrig = 0);
    virtual void readCell(IlvCell*);
protected:
    IlUInt        _numpalettes;
    IlvPalette**  _palettes;
    // Hash table stuff
    IlvCell**    _cells;
    IlUInt       _count;
    IlvCell**    allocCells(IlUInt);
};

ILV31VWSMODULEINIT(cellio);
#endif /* __Ilv31_Cellio_H */
