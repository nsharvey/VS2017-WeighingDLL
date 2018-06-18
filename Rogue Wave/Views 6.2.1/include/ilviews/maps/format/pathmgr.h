// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/pathmgr.h
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
// ilog.views.maps.format
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Format_MapDataPathResolver_H
#define __ILV_maps_Format_MapDataPathResolver_H

#include <ilog/array.h>
#include <ilviews/maps/format/pathrslv.h>

IlDefineListOf(MapDataPathResolver,
	       IlvMapDataPathResolver*);

class ILVMAPSEXPORTED IlvMapDataPathManager
{
private:
    static IlListOf(MapDataPathResolver)* _list;
    IlvMapDataPathManager();

public:
  static IlBoolean AddDataPathResolver(IlvMapDataPathResolver* resolver);

  static IlBoolean RemoveDataPathResolver(IlvMapDataPathResolver* resolver);

  static IlListIteratorOf(MapDataPathResolver) GetDataPathResolvers();

  static char* ResolvePath(const char* filename);
};

#endif
