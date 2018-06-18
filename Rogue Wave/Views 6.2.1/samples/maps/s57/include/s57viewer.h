// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/s57/include/s57viewer.h
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
// Declaration of the S57 Viewer
// --------------------------------------------------------------------------
#include "gui.h"

#include <ilviews/maps/mapinfo.h>
#include <ilviews/maps/rendering/all.h>

// --------------------------------------------------------------------------
class S57Viewer
    : public Gui
{
public:
    S57Viewer(IlvDisplay* display,
	      IlvMapInfo* mapInfo,
	      IlvProjection* sourceProjection);
    ~S57Viewer();

    void parseFeatureAttributeProperty(IlvFeatureAttributeProperty* ap);
    void loadFile(const char*);
    virtual void buttonDown(IlvGraphic* g);
    void checkError(const IlvMapsError& error, IlBoolean end = IlFalse);

private:
    IlvMapInfo* _mapInfo;
    IlvProjection* _sourceProjection;
    IlvUInt _layerIndex;
};
