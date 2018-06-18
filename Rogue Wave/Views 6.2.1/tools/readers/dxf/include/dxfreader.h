// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/dxf/include/dxfreader.h
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
// Declaration of the DXF Reader and required classes
// --------------------------------------------------------------------------

#ifndef DXFReader_H
#define DXFReader_H

#include <ilviews/manager/manager.h>
#include <ilviews/maps/mapinfo.h>

#ifdef ILVSTD
#include <iostream>
#else
#include <iostream.h>
#endif

#include "dxfbasic.h"
#include "dxffactory.h"

class DXFGraphicFactory;

class DXFReader
{
  public:
    DXFReader(const char* fileName,
	      IlvManager* manager,
	      DXFGraphicFactory* factory);
    ~DXFReader();

    // Error management
    IlBoolean isBad() {return _fail;}
    const char* getErrorMessage() {return _errorMessage;}

    // Georefrencement
    const IlvMapInfo* getMapInfo() {return _factory->getMapInfo();}
    
  private:
    void read();
    void cleanUp();
    
    void testBinaryFormat();
    void pushBackGroup() { _pushedBack = IlTrue;}
    
    // Reads a DXF group from the stream.
    // and store the result in the attribute 'currentGroup'.
    IlBoolean readGroup();
    
    IlBoolean readSection();
    IlBoolean readTables();
    IlBoolean readTable(const char*  tableName);
    IlBoolean readLtype();
    IlBoolean readLayer();
    IlBoolean readEntities(IlBoolean store);
    IlBoolean readHeader();
    IlBoolean readBlocks();
    IlBoolean readBlock();

    IlvGraphic* createGraphicObject(DXFElement* entity,
				    IlvTransformer* t = 0);
    
    DXFElement* getBlock(const char* blockName);

    // error management
    IlBoolean setError(const char*);

    // resource management
    int getLayerIndex(DXFElement* entity) const;
    IlvPalette* createPalette(const char* layerName,
			      IlShort color = -1) const;
    IlvColor* createColor(IlShort colorIndex) const;
    const char* parseColor(IlShort colorIndex) const;
    IlvLineStyle* createLineStyle(const char* lineStyleName) const;

    // coordinate space management
    void updateGraphicFactory();

  private:
    // Stores the useful groups of the current polyline
    DXFElement* _currentPolyline;
    IlShort     _currentPolylineFlags;
    
    istream* _stream;
    IlvManager* _manager;
    DXFGraphicFactory* _factory;
    
    IlDouble _angbase; // as read in the DXF file
    IlInt _angdir; // as read in the DXF file
    IlvCoordinate _lowerLeftCorner;  // as read in the DXF file
    IlBoolean _lowerLeftCornerKnown;
    IlvCoordinate _upperRightCorner;  // as read in the DXF file
    IlBoolean _upperRightCornerKnown;
    IlBoolean _binaryFormat; // True if DXF Binary Format
    DXFGroup _currentGroup; // current Group read from the stream

    IlBoolean _pushedBack;
    IlInt _fileOffset; // line number or byte offset
    IlList*  _ltypes;
    DXFElementList* _layers;
    DXFElementList* _blocks;
    DXFElementList* _entities;

    // error management
    char _errorMessage[100];
    IlBoolean _fail;

    DXFCoordinateArray _polylinePoints; // Temporary list of IlvCoordinate
    IlBoolean _doingAPolyline;
    IlvPalette* _currentPolyLinePalette;
    DXFElementList* _insertAttribEntities;

};

#endif
