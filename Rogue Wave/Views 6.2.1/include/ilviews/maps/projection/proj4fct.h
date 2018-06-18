// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/proj4fct.h
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
// A Factory to create projections from a PROJ4 description
// Defined in library ilvmaps
// --------------------------------------------------------------------------

#ifndef __Ilv_Maps_Proj4_Factory_H
#define __Ilv_Maps_Proj4_Factory_H

#include <ilviews/maps/macros.h>
#include <ilviews/base/hash.h>
#include <ilviews/maps/maps.h>

class ILVMAPSEXPORTED IlvProjectionClassInfo;
class ILVMAPSEXPORTED IlvProjection;

// Undocumented class.

class ILVMAPSEXPORTED _ilvMapsProj4Factory
{
    public:
    static IlvProjection* CreateProjection(const char* params,
					   IlvMapsError& status);

    static void AddProjectionClass(IlvProjectionClassInfo*);

    // formatting functions
    static void WriteDouble(const IlDouble &d, IL_STDPREF ostream& os);

    private:
    static IlStringHashTable*  MakeProperties(const char* params,
					      IlvMapsError& status);

    private:
    static IlStringHashTable*  _classes;
};


#endif
