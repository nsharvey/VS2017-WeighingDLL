// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/oracle/objectmodel/kextract.h
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
// Declaration of the IlvObjectSDOKeyExtractor class
// Defined in library ilvdbmap
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Oracle_Objectmodel_Kextract_H
#define __Ilv_Maps_Format_Oracle_Objectmodel_Kextract_H

#include <ilviews/maps/format/oracle/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/maps/tiling/tile.h>

class IlvMapFeatureId;
class IldRequest;

// --------------------------------------------------------------------------
class ILVDBMAPSEXPORTED IlvObjectSDOKeyExtractor
{
public:
    virtual ~IlvObjectSDOKeyExtractor();

    virtual
    IlvMapFeatureId*	extractKey(IldRequest* req, IlvMapsError& error);
    virtual IlBoolean	isPersistent() const;
    static IlvMapsError	ColumnNotFoundError();

    IlvTilingDeclareIO(IlvObjectSDOKeyExtractor);
protected:
    IlvObjectSDOKeyExtractor();

private:
    static IlvMapsError _columnNotFoundError;
};

ILVDBMAPSMODULEINIT(kextract);

#endif /* __Ilv_Maps_Format_Oracle_Objectmodel_Kextract_H */
