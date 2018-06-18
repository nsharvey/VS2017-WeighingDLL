// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/mdatasrc.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliMemoryDataSource class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Mdatasrc_H
#define __Ili_Mdatasrc_H

#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ili_Memtable_H)
#  include <ilviews/dataccess/memtable.h>
#endif
#if !defined(__Ili_Datasrc_H)
#  include <ilviews/dataccess/gadgets/datasrc.h>
#endif

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliMemoryDataSource
: public IliDataSource
{
public:
    IliMemoryDataSource(IlvDisplay* display,
			const IlvPoint& at,
			IlUShort thickness = IlvDefaultGadgetThickness,
			IlvPalette* palette = 0);
    virtual ~IliMemoryDataSource();

    DeclareTypeInfo();
    DeclareIOConstructors(IliMemoryDataSource);

    inline const IliMemoryTable* getMemoryTable() const
	{ return (const IliMemoryTable*)getTable(); }
    inline IliMemoryTable*	getMemoryTable()
	{ return (IliMemoryTable*)getTable(); }
    inline void		setMemoryTable(IliMemoryTable* table,
				       IlBoolean owner = IlTrue)
	{ setTable(table, owner); }

    virtual IlvBitmap*	getBitmap() const;
};

IliModuleDECL_exp(ILV_INF_EXPORTED, IliMemoryDataSource);

#endif /* !__Ili_Mdatasrc_H */
