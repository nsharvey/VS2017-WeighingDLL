// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/sqldtsrc.h
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
// Declaration of the IliSQLDataSource class
// Defined in library dbsqlgad
// --------------------------------------------------------------------------
#ifndef __Ili_Sqldtsrc_H
#define __Ili_Sqldtsrc_H

#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ili_Sqltable_H)
#  include <ilviews/dataccess/sqltable.h>
#endif
#if !defined(__Ili_Datasrc_H)
#  include <ilviews/dataccess/gadgets/datasrc.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBSQLG_EXPORTED IliSQLDataSource
: public IliDataSource
{
public:
    IliSQLDataSource(IlvDisplay* display,
		     const IlvPoint& at,
		     IlUShort thickness = IlvDefaultGadgetThickness,
		     IlvPalette* palette = 0);
    virtual ~IliSQLDataSource();

    DeclareTypeInfo();
    DeclareIOConstructors(IliSQLDataSource);

    inline const IliSQLTable*	getSQLTable() const
	{ return (const IliSQLTable*)getTable(); }
    inline IliSQLTable* getSQLTable() { return (IliSQLTable*)getTable(); }
    inline void		setSQLTable(IliSQLTable* table,
				    IlBoolean owner = IlTrue)
	{ setTable(table, owner); }

    virtual IlvBitmap*	getBitmap() const;

    virtual IlBoolean	isFreeAccess() const;

    void		apply(IlvApplyObject, IlAny);

private:
    IlUInt		_graphicDrvCount;
    IlvGraphic**	_graphicDrv;

    void		resetDrv(IlUInt);
    void		computeDrv();
};

IliModuleDECL_exp(ILV_DBSQLG_EXPORTED, IliSQLDataSource);

#endif /* !__Ili_Sqldtsrc_H */
