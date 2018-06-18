// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/projdict.h
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
// The Projection dictionary.
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_ProjectionDictionary_H
#define __Ilv_Maps_ProjectionDictionary_H

#include <ilviews/maps/macros.h>
#include <ilviews/base/link.h>

class ILVMAPSEXPORTED IlvProjectionClassInfo;
class ILVMAPSEXPORTED IlvProjection;

class ILVMAPSEXPORTED IlvProjectionDictionary
{
public:
    IlvProjectionDictionary(IlBoolean init = IlTrue);
    virtual ~IlvProjectionDictionary();

    virtual void	registerProjection(IlvProjectionClassInfo* pcInfo);

    virtual IlBoolean	unregisterProjection(IlvProjectionClassInfo* pcInfo);

    IlvProjection*	createProjection(const char* name) const;

    const char**	getProjectionNames(IlUInt& count) const;

private:
    IlvList		_registered;
};

#endif