// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/include/simplePolylineReader.h
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

#ifndef _SimplePolylineRender_h
#define _SimplePolylineRender_h

#ifdef IL_STD
#include <fstream>
using namespace std;
#else
#include <fstream.h>
#endif

#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/format/mapinput.h>
#include <ilviews/maps/rendering/curverdr.h>

class SimplePolylineReader
   : public IlvMapFeatureIterator
{
public:
    SimplePolylineReader(IlvDisplay* display,
                         const char* filename);
    virtual ~SimplePolylineReader();
    
    virtual IlvMapsError getInitStatus() const;

    virtual const IlvMapFeature* getNextFeature(IlvMapsError& status);

    virtual IlBoolean getLowerRightCorner(IlvCoordinate& coordinate) const;

    virtual IlBoolean getUpperLeftCorner(IlvCoordinate&) const;

    IlvFeatureRenderer* getDefaultFeatureRenderer(IlvDisplay *);

    const IlvProjection* getProjection() const;

    IlBoolean emptyLine(const char* line);

    IlBoolean readHeader(const char* line);

    int parseLine(const char* line,
                  IlDouble* lng,
                  IlDouble* lat,
                  char* comment);
    
    IlvFeatureAttributeProperty* attributes(IlString& buffer,
                                            IlvMapsError& status);
    
    IlvMapFeatureIteratorDeclareClassInfo();
    
private:
    static IlvMapsError _formatError;

    IlvDisplay* _display;
    IlvMapsError _status;
    ifstream _stream;
    IlvMapLineString* _geometry;
    IlvMapFeature* _feature;
    IlvProjection* _projection;

    static IlvMapsError FormatError();
    static void Init();
    const IlvMapFeature* readPolyline(IlvMapsError& status);
};

#endif /* _SimplePolylineRender_h */
