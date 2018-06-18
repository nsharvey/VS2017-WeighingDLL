// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/userman/src/simplePolylineReader.cpp
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

#include <ilviews/maps/projection/geogproj.h>
#include <ilviews/maps/attrinfo.h>
#include <ilviews/maps/attribute/stringattr.h>

#include <simplePolylineReader.h>

#if defined(IL_STD)
#include <cstdlib>
#include <cstring>
#include <cctype>
IL_STDUSE
#else  /* !IL_STD */
#include <stdlib.h.>
#include <string.h>
#include <ctype.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
IlvMapFeatureIteratorDefineClassInfo(SimplePolylineReader,
				     IlvMapFeatureIterator);

IlvMapsError SimplePolylineReader::_formatError;

// --------------------------------------------------------------------------
SimplePolylineReader::SimplePolylineReader(IlvDisplay* display,
                                           const char* filename)
    :_display(display),
     _status(IlvMaps::NoError()),
     _stream(display->findInPath(filename)),
     _geometry(0),
     _feature(0),
     _projection(new IlvGeographicProjection())
{
    _projection->lock();
    char line[1024];
    static int inited = 0;
    if(!inited) {
	inited = 1;
	SimplePolylineReader::Init();
    }
    _stream.getline(line, 1023);
    if(readHeader(line) == IlFalse)
        _status = _formatError;
}

// --------------------------------------------------------------------------
SimplePolylineReader::~SimplePolylineReader() {
    if(_projection)
	_projection->unLock();
    if(_feature)
	delete _feature;
}

// --------------------------------------------------------------------------
IlvMapsError
SimplePolylineReader::getInitStatus() const {
    return _status;
}

// --------------------------------------------------------------------------
IlBoolean
SimplePolylineReader::getLowerRightCorner(IlvCoordinate& c) const {
    return IlFalse;
}

// --------------------------------------------------------------------------
IlBoolean
SimplePolylineReader::getUpperLeftCorner(IlvCoordinate& c) const {
    return IlFalse;
}

// --------------------------------------------------------------------------
IlvMapsError
SimplePolylineReader::FormatError()
{
    static IlvMapsError value = 0;
    if (!value)
	value = IlvMaps::CreateError("&SimplePolylineReaderFormatError");
    return value;
}

// --------------------------------------------------------------------------
const IlvProjection*
SimplePolylineReader::getProjection() const {
    return _projection;
}

// --------------------------------------------------------------------------
IlvFeatureRenderer*
SimplePolylineReader::getDefaultFeatureRenderer(IlvDisplay *display) {
    return new IlvDefaultCurveRenderer(display);
}

// --------------------------------------------------------------------------
const IlvMapFeature*
SimplePolylineReader::getNextFeature(IlvMapsError& status) {
    return readPolyline(status);
}

// --------------------------------------------------------------------------
void
SimplePolylineReader::Init()
{
    _formatError = SimplePolylineReader::FormatError();
}

// --------------------------------------------------------------------------
IlBoolean
SimplePolylineReader::emptyLine(const char* line)
{
    char c;
    const char* ptr = line;

    while((c = *ptr++))
	if(!isspace(c))
	    return IlFalse;

    return IlTrue;
}

// --------------------------------------------------------------------------
IlvFeatureAttributeProperty*
SimplePolylineReader::attributes(IlString& buffer, IlvMapsError& status)
{
    if(buffer.getLength() == 0)
        return 0;

    IlUInt count = 1;
    
    const char* name = "Comment : ";

    const IlvMapClassInfo* attClass = IlvStringAttribute::ClassInfo();
    
    const IlBoolean nullable = IlTrue;

    IlvFeatureAttributeInfo* info =
        new IlvFeatureAttributeInfo( count,
                                     &name,
                                     &attClass,
                                     &nullable);

    const char* val = buffer.getValue();
    IlvStringAttribute att;
    att.setValue(val);
    IlvStringAttribute* aatt = &att;
    IlvFeatureAttributeProperty* prop = 
        new IlvFeatureAttributeProperty(info,
                                        (IlvFeatureAttribute**)&aatt,
                                        status);

    return prop;
}

// --------------------------------------------------------------------------
int 
SimplePolylineReader::parseLine(const char* line,
				IlDouble* lng,
				IlDouble* lat,
				char* comment)
{
    const char* start;
    char* ptr;
    IlDouble val;

    start = line;    
    val = strtod(start, &ptr);
    if(ptr > start)
	*lng = val;
    else
	return -1;

    start = ptr;
    val = strtod(start, &ptr);
    if(ptr > start)
	*lat = val;
    else
	return -1;

    if(emptyLine(ptr))
	return 2;

    strcpy(comment, ptr);
    
    return 3;
}

// --------------------------------------------------------------------------
IlBoolean
SimplePolylineReader::readHeader(const char* line)
{
    if(line[0] == '#')
	return IlTrue;
    return IlFalse;
}

// --------------------------------------------------------------------------
const IlvMapFeature*
SimplePolylineReader::readPolyline(IlvMapsError& status) {   

    if(_stream.eof())
        return 0;
    
    if(!_geometry)
        _geometry = new IlvMapLineString();
    else
        _geometry->removeAll();
            
    if(!_feature) {
        _feature = new IlvMapFeature();
        _feature->setGeometry(_geometry);
        const IlvProjection* proj = getProjection();
        if(proj)
            _feature->setProjection(proj->copy());
    }



    char line[1024];
    int first = 1;
    IlString buffer;
    
    IlvCoordinate c;
    
    while (1) {
	_stream.getline(line, 1023);
        if (_stream.eof() || emptyLine(line)) {
            status = IlvMaps::NoError();
            IlvFeatureAttributeProperty* prop =
                attributes(buffer, status);
            if(status != IlvMaps::NoError())
                IlvWarning(IlvMaps::GetErrorMessage(status, _display));
            IlvFeatureAttributeProperty* ret = _feature->setAttributes(prop);
	    if(ret)
		delete ret;
            buffer = IlString();
            return _feature;       
        }
        


       
        double x, y;
        char comment[1024];
        int i = parseLine(line, &x, &y, comment);

        if(i < 2) {
            status = _formatError;
            return 0;
        }

        c.x(x);
        c.y(y);

        if(i == 3)
            buffer += comment;



        if(first) {
            first = 0;
           _geometry->setStartPoint(c);
        } else {
            _geometry->lineTo(c);
        }
    }
}


