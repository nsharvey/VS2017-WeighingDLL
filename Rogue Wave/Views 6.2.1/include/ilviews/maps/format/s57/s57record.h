// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/s57record.h
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
// --------------------------------------------------------------------------
#ifndef __Ilv_S57Record_H
#define __Ilv_S57Record_H

#include <ilviews/maps/format/s57/i8211util.h>
#include <ilviews/maps/format/s57/s57enum.h>

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57Record : public IlvI8211RefCount
{
public:
    IlvS57Record();

    IlvS57PropertyTable&	getProperties();
    void			setProperty(IlvS57Enumeration* key,
					    IlAny value);

protected:
    virtual ~IlvS57Record();

    IlvS57PropertyTable _properties;

    static IlvS57EnumerationArray	_STattrTypeEnum;
    static IlvS57EnumerationArray	_STobjCodeEnum;
    static IlvS57EnumerationArray	_STcounEnum;
    static IlvS57EnumerationArray	_STmaskEnum;
    static IlvS57EnumerationArray	_STorntEnum;
    static IlvS57EnumerationArray	_STprimEnum;
    static IlvS57EnumerationArray	_STrindEnum;
    static IlvS57EnumerationArray	_STruinEnum;
    static IlvS57EnumerationArray	_STtopiEnum;
    static IlvS57EnumerationArray	_STusagEnum;
    static IlvS57EnumerationArray	_STvrTypeEnum;
    static IlvS57EnumerationArray	_STintuEnum;

public:
    static void		Initialize(IlvDisplay* display);
    static void		LoadResourceAttributes(IlvDisplay* display);
    static void		LoadResourceObjects(IlvDisplay* display);
};

#endif /* !__Ilv_S57Record_H */
