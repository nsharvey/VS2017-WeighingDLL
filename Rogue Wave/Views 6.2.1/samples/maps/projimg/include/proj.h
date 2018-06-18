// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/projimg/include/proj.h
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
// Declaration of image projector class
// --------------------------------------------------------------------------
#ifndef _Proj_H
#define _Proj_H

#include "gui.h"

#include <ilviews/gadgets/combo.h>
#include <ilviews/maps/projection/allprojs.h>
#include <ilviews/maps/projection/projdict.h>
#include <ilviews/maps/mapinfo.h>

// --------------------------------------------------------------------------
class ImageProjector
    : public Gui
{
public:
    ImageProjector(IlvDisplay*);
    virtual ~ImageProjector();

    virtual const char** getLabels(IlUShort& count);
    virtual void comboItemSelected(const char*);

    void showProjection(IlvProjection*);
    void setUnknown(IlInt,
		    IlInt,
		    IlShort,
		    IlvUChar*);
    void setColor(IlInt,
		  IlInt,
		  IlInt,
		  IlInt,
		  IlvDim,
		  IlShort,
		  IlvUChar*);
    void centerProjection(IlvView*, IlvEvent&);
    virtual void showGrid(IlBoolean s);
    IlBoolean getViewCenter(IlvCoordinate& ll) const;
    void setViewCenter(IlvCoordinate& ll);
    void makeBitmap();

    IlvMapInfo* getMapInfo() const
	{ return _mapInfo; }

private:
    IlvUChar* _sourceData;
    IlvMapInfo* _mapInfo;
    IlvDim _sourceWidth;
    IlvDim _sourceHeight;
    IlvBitmapData* _sourceBitmapData;
    IlvProjectionDictionary _dictionary;
};

#endif
