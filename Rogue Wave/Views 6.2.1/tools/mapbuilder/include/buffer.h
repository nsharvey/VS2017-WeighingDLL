// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/buffer.h
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
// Declaration of the MapBuffer class
// -------------------------------------------------------------------------

#ifndef _MapBuffer_h_
#define _MapBuffer_h_

#include <ilviews/ilv.h>
#include <ilviews/manager/manager.h>
#include <ilviews/gadgets/desktop.h>
#include <ilviews/gadgets/vframe.h>
#include <ilviews/maps/maps.h>
#include "desktop.h"
#include "multiraster.h"
#include "multishape.h"

class PaletteEditor;
class MapBuilder;

// --------------------------------------------------------------------------
class MapBuffer
{
public:
    MapBuffer(MapBuilder* builder,
	      MapDesktopManager* manager,
	      const char* frameTitle = 0);
    ~MapBuffer();

    void destroyFrame();

    IlvMapsError loadFile(const char* name);
    IlvMapsError loadMap(const char* name,IlBoolean setVisible);
    IlvMapsError save(const char* name = 0);


    IlBoolean isVisible() { return frame->isVisible(); }
    void setVisible(IlBoolean set);
    // Accessors
    IlvViewFrame* getFrame() const { return frame; }
    void setFrame(IlvViewFrame*f) { frame = f; }
    IlvView* getView() const { return view; }
    IlvManager* getManager() const { return manager; }
    const char* getFileName() const { return filename; }
    MapBuilder* getBuilder() const { return mapbuilder; };
    static void UpdateLayerAttributes(IlvManagerLayer*, PaletteEditor*,
				      IlBoolean = IlFalse);

private:
    IlvViewFrame*  frame;
    IlvView*       view;
    MapDesktopManager* desktopManager;
    char* title;
    char* filename;
    IlvManager* manager;
    MapBuilder* mapbuilder; // the associated builder
    RasterLayerFactory* rasterFactory;
    ShapeLayerFactory* shapeFactory;

};

#endif /* _MapBuffer_h_ */
