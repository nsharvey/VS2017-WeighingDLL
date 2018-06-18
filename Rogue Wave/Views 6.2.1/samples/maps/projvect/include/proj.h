// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/projvect/include/proj.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of vector projector class
// --------------------------------------------------------------------------
#ifndef _Proj_H
#define _Proj_H

#include "gui.h"

#include <ilviews/gadgets/combo.h>
#include <ilviews/maps/projection/allprojs.h>
#include <ilviews/maps/projection/projdict.h>
#include <ilviews/maps/mapinfo.h>

// --------------------------------------------------------------------------
class VectorProjector
    : public Gui
{
public:
    VectorProjector(IlvDisplay*);
    virtual ~VectorProjector();

    virtual const char** getLabels(IlUShort& count);
    virtual void comboItemSelected(const char*);

    void showProjection(IlvProjection*);

    void centerProjection(IlvView*, IlvEvent&);

    IlvMapInfo* getMapInfo() const
	{ return _mapInfo; }

    virtual void showAll();
    virtual void showGrid(IlBoolean s);
    void loadSourceData(IlvDisplay*,int argc, char** argv );
    void project(IlvGraphic* g);
    IlBoolean getViewCenter(IlvCoordinate& ll);
    void setViewCenter(IlvCoordinate& ll);

    IlvManager* _sourceManager;
    IlvMapInfo* _mapInfo;
    IlvProjectionDictionary _dictionary;
};

#endif
