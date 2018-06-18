// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/laiterator.h
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
// This file defines the look ahead feature iterator
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Laiterator_H
#define __Ilv_Maps_Laiterator_H

#if !defined(__Ilv_Maps_Macros_H)
#  include <ilviews/maps/macros.h>
#endif
#if !defined(__Ilv_Maps_Maps_H)
#  include <ilviews/maps/maps.h>
#endif
#if !defined(__Ilv_Maps_Mapfeature_H)
#  include <ilviews/maps/mapfeature.h>
#endif

class ILVMAPSEXPORTED IlvLookAheadFeatureIterator
: public IlvMapFeatureIterator
{
public:
    virtual ~IlvLookAheadFeatureIterator();

    virtual IlvMapFeatureId* getNextFeatureId(IlvMapsError& status) = 0;
    virtual IlBoolean skipNextFeature(IlvMapsError& status) = 0;

protected:
    IlvMapFeatureIteratorDeclareClassInfo();

protected:
    IlvLookAheadFeatureIterator();
};

#endif /* !__Ilv_Maps_Laiterator_H */