// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/dxf/src/dxfreader.cpp
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
// Definition of the DXF Reader and required classes
// --------------------------------------------------------------------------
#include <ilviews/base/memory.h>
#include <ilviews/manager/layer.h>
#include <ilviews/base/sstream.h>
#include <ilviews/graphics/set.h>
#include <ilog/pool.h>

#ifdef ILVSTD
#include <fstream>
#include <cstring>
using namespace std;
#else
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include "dxfreader.h"
#include "dxffactory.h"
#include <ilog/sstream.h>


IlDeclarePoolOf(char, char);
IlDefinePoolOf(char);


#define binaryFormatHeaderLength 22
static const char* binaryFormatHeader = "AutoCAD Binary DXF\015\012\032";
static char  readAheadBuffer[binaryFormatHeaderLength];

// -------------------------------------------------------------------------

/**
 * non portable filestream creation
 * on PC, the filestream must be opened in binary mode
 */
static ifstream*
createInputStream(const char* fileName)
{
#ifdef ILVSTD
    // STL
    return new ifstream(fileName, ios::in | ios::binary);
#else
#if defined (WINDOWS)    
    // PC without STL
    return new ifstream(fileName, ios::in | ios::nocreate | ios::binary);
#else
    // unix
    return new ifstream(fileName, ios::in | ios::nocreate);
#endif
#endif
}

// --------------------------------------------------------------------------
DXFReader::DXFReader(const char* fileName,
		     IlvManager* manager,
		     DXFGraphicFactory* factory)
    : _currentPolyline(0),
      _stream(createInputStream(fileName)),
      _manager(manager),
      _factory(factory),
      _lowerLeftCornerKnown(IlFalse),
      _upperRightCornerKnown(IlFalse),
      _fail(IlFalse)
{
    strcpy(_errorMessage, "No error");
    DXFGroup group;
    group.set(0, "POLYLINE");
    _currentPolyline = new DXFElement(group);
    read();
    cleanUp();
}

// --------------------------------------------------------------------------
DXFReader::~DXFReader()
{
}

// --------------------------------------------------------------------------
void
DXFReader::cleanUp()
{
    delete _stream;
    if (_layers)
	delete _layers;
    delete _currentPolyline;
    delete _blocks;
}

// --------------------------------------------------------------------------
void
DXFReader::read()
{
    _angbase = 0;
    _angdir = 0;
    
    _lowerLeftCorner.move(0, 0);
    _lowerLeftCornerKnown = IlFalse;
    _upperRightCorner.move(0, 0);
    _upperRightCornerKnown = IlFalse;
    
    _binaryFormat = IlFalse ;
    _currentGroup.release();

    _pushedBack = IlFalse;
    _fileOffset = 0;
    _ltypes = 0;
    _layers = 0;
    _blocks = 0;
    _entities = 0;
    
    _doingAPolyline = IlFalse;
    _insertAttribEntities = 0;
    testBinaryFormat();
    while(IlTrue) {
      if (!readGroup())
	  return;
      if (_currentGroup.match(0, "EOF")) {
	  break;
      }
      if (_currentGroup.match(0, "SECTION")) {
	  readSection();
      }
      else {
	  char buffer[100];
	  sprintf(buffer,
		  "Bad group code %ld at offset %ld. Should be [0-SECTION]",
		  (long int) _currentGroup.getCode(),
		  (long int) _fileOffset);
	  setError(buffer);
	  return;
      }
    }
}

// --------------------------------------------------------------------------
void
DXFReader::testBinaryFormat()
{
    IlInt loop;
    // try to see if this is a binary DXF.
    
    for (loop = 0; loop < binaryFormatHeaderLength; loop++) {
	readAheadBuffer[loop] = _stream->get();
	if (binaryFormatHeader[loop] != readAheadBuffer[loop])
	  break;
    }
    if (loop == binaryFormatHeaderLength) {
	_binaryFormat = IlTrue;
	_fileOffset = binaryFormatHeaderLength;
    }
    else
	_stream->seekg(0, ios::beg);
}


// --------------------------------------------------------------------------
#define ISSPACE(c) (((c)==' ')||((c)=='\r')||((c)=='\t')||((c)=='\n'))

// --------------------------------------------------------------------------
/** 
 * Reads a DXF group from the stream.
 * and store the result in the attribute 'currentGroup'.
 */
IlBoolean
DXFReader::readGroup()
{
    if (_pushedBack) {
	// A group has been pushed back. There is 
	// nothing to read.
	_pushedBack = IlFalse;
	return IlTrue;
    }
    _currentGroup.release();
    if (_binaryFormat) {
	
	// initializing the byte order flag
	static int machineIsLSBFirst = -1;
	if (machineIsLSBFirst < 0) {
	    static int LSBtest = 1;
	    machineIsLSBFirst = (((char*)&LSBtest)[0] == 1);
	}
	
	IlInt code = _stream->get();
	_fileOffset++;
	if ((code < 0))
	    return setError("DXF format error");
	if ((code < 10) ||
	    ((code >= 1000) && (code < 1010))) {
	    
	    char c;
	    strstream bufferStream;
	    int index = 0;
	    while ((c = _stream->get()) != 0) {
		bufferStream << c;
		index++;
		if (_stream->eof())
		    return setError("Unexpected end of file");
	    }
	    bufferStream << ends;
#if defined(IL_USING_STRINGSTREAM)	    
	    int count = bufferStream.str().size();
	    char* buffer = new char[bufferStream.str().size()+1];
	    strcpy(buffer, bufferStream.str().data());
#else
	    char* buffer= bufferStream.str();
#endif
	    for (char* p =  buffer + strlen(buffer);
		 (p >= buffer) && (*p == '\015');
		 p--)
		*p = 0;
	    _currentGroup.set(code, buffer);
#if defined(IL_USING_STRINGSTREAM)
	    delete[] buffer;
#else
	    bufferStream.rdbuf()->freeze(0);
#endif
	    _fileOffset += index + 1;
	}
	else if (((code >= 10) && (code < 60)) ||
		 ((code >= 140) && (code < 148)) ||
		 ((code >= 210) && (code < 240) ||
		  ((code >= 1010) && (code < 1060)))) {
	    IlDouble f;
	    _stream->read((char*)&f, 8);
	    if (!machineIsLSBFirst) {
		char* fp = (char*)&f;
		char c = fp[0];
		fp[0] = fp[7];
		fp[7] = c;
		c = fp[1];
		fp[1] = fp[6];
		fp[6] = c;
		c = fp[2];
		fp[2] = fp[5];
		fp[5] = c;
		c = fp[3];
		fp[3] = fp[4];
		fp[4] = c;
	    }
	    _currentGroup.set(code, f);
	    _fileOffset += 8;
	}
	else if (((code >= 60) && (code < 80)) ||
		 ((code >= 170) && (code < 176)) ||
		 ((code >= 1060) && (code < 1080))) {
	    IlShort i;
	    _stream->read((char*)&i, 2);
	    if (!machineIsLSBFirst) {
		char* ip = (char*)&i;
		char c = ip[0];
		ip[0] = ip[1];
		ip[1] = c;
	    }
	    _currentGroup.set(code, i);
	    _fileOffset += 2;
	}
    }
    else {
	static char buffer[512];
	char* p;
	do {
	    // read the line containing the code
	    _stream->getline(buffer, 512);
	    _fileOffset++;
	    for (p = buffer; *p && ISSPACE(*p); p++);
	} while (!*p && !_stream->eof());
      	if (_stream->eof())
	    return setError("Unexpected end of file");
	IlInt code = atoi(buffer);
	
	// Reads the group value.
	_stream->getline(buffer, 512);
	_fileOffset++;
	if (_stream->eof())
	    return setError("Unexpected end of file");
	if (code == 999)
	    return readGroup();
	
	if (code < 0)
	    return setError("bad code for group");
	
	if ((code < 10) ||
	    ((code >= 1000) && (code < 1010))) {
	    // group value is a String
	    _currentGroup.set(code, buffer);
	}
	else if (((code >= 10) && (code < 60))   ||
		 ((code >= 140) && (code < 148)) ||
		 ((code >= 210) && (code < 240)  ||
		  ((code >= 1010) && (code < 1060)))) {
	    // group value is a double
	    _currentGroup.set(code, atof(buffer));
	}
	else if (((code >= 60) && (code < 80)) ||
		 ((code >= 170) && (code < 176)) ||
		 ((code >= 1060) && (code < 1080))) {
	    // group value is a short
	    _currentGroup.set(code, (IlShort)atoi(buffer));
	}
    }
    return IlTrue;   
}

// --------------------------------------------------------------------------
IlBoolean
DXFReader::setError(const char* error)
{
    strcpy(_errorMessage, error);
    _fail = IlTrue;
    return IlFalse;
}

// --------------------------------------------------------------------------
IlBoolean
DXFReader::readSection()
{
    while (IlTrue) {
	if (!readGroup())
	    return IlFalse;
	if (_currentGroup.match(0, "ENDSEC")) {
	    return IlTrue;
	}
	if (_currentGroup.match(2, "HEADER")) {
	    if (!readHeader())
		return IlFalse;
	    else
		if (_lowerLeftCornerKnown && _upperRightCornerKnown)
		    updateGraphicFactory();
	}
	if (_currentGroup.match(2, "TABLES")) {
	    if (!readTables())
		return IlFalse;
	}
	if (_currentGroup.match(2, "BLOCKS")) {
	    if (!readBlocks())
		return IlFalse;
	}
	if (_currentGroup.match(2, "ENTITIES")) {
	    if (!readEntities(IlFalse))
		return IlFalse;
	}
    }
    return IlFalse; // Should not be reached
}

// --------------------------------------------------------------------------
IlBoolean
DXFReader::readTables()
{
    while (IlTrue) {
	if (!readGroup())
	    return IlFalse;
	if (_currentGroup.match(0, "TABLE")) {
	    if (!readGroup())
		return IlFalse;
	    if (_currentGroup.getCode() != 2) {
		char buffer[80];
		sprintf(buffer,
			"Should be a 2 group at line/byte %ld",
			(long int) _fileOffset);
		setError(buffer);
	    }
	    if (!readTable(_currentGroup.getString()))
		return IlFalse;
	}
	if (_currentGroup.match(0, "ENDSEC")) {
	    pushBackGroup();
	    return IlTrue;
	}
    }
    return IlFalse; // Should not be reached
}

// --------------------------------------------------------------------------
IlBoolean
DXFReader::readTable(const char* tableName)
{
    while (IlTrue) {
      if (!readGroup())
	  return IlFalse;
      if (_currentGroup.match(0, "LTYPE")) {
	  if (!readLtype())
	      return IlFalse;
      }
      else if (_currentGroup.match(0, "LAYER")) {
	  if (!readLayer())
	      return IlFalse;
      }
      else if (_currentGroup.match(0, "ENDTAB")) {
	  pushBackGroup();
	  return IlTrue;
      }
    }
    return IlFalse; // Should not be reached
}

// --------------------------------------------------------------------------
IlBoolean
DXFReader::readLtype()
{
    DXFElement* newLtype = new DXFElement(_currentGroup);
    if (_ltypes == 0)
      _ltypes = new IlvList;
    
    _ltypes->append(newLtype);
    while (IlTrue) {
	if (!readGroup())
	    return IlFalse;
	if (_currentGroup.getCode() == 0) {
	    pushBackGroup();
	    return IlTrue;
	}
	newLtype->addGroup(_currentGroup);
    }
    return IlFalse; // Should not be reached
}
  
// --------------------------------------------------------------------------
IlBoolean
DXFReader::readLayer()
{
    DXFElement* newLayer = new DXFElement(_currentGroup);
    if (_layers == 0)
	_layers = new DXFElementList(newLayer);
    else
	_layers->addElement(newLayer);
    while (IlTrue) {
	if (!readGroup())
	    return IlFalse;
	if (_currentGroup.getCode() == 0) {
	    pushBackGroup();
	    break;
	}
	newLayer->addGroup(_currentGroup);
    }
    DXFGroup* layerName = newLayer->getGroup(2);
    return IlTrue;
}


// --------------------------------------------------------------------------
/**
 * Reads the entity section of the file.
 * This method is used to read the entity section
 * of the file and also the entities of a BLOCK section.
 * When reading a BLOCK section, the parameter store is
 * set to true so that the created graphic objects are 
 * stored in the entities list.
 */
IlBoolean
DXFReader::readEntities(IlBoolean store)
{
    DXFElement* currentEntity = 0;
    IlBoolean allowed =  IlvGetContentsChangedUpdate();
    IlvSetContentsChangedUpdate(IlFalse);
    
    while (!_fail) {
	if (!readGroup())
	    break;
	if (_currentGroup.getCode() == 0) {
	    if (currentEntity) {
		if (store) { // store only when reading the blocks.
		    if (!_entities) 
			_entities =  new DXFElementList();
		    _entities->addElement(new DXFElement(*currentEntity));
		}
		else {
		    IlvGraphic* obj = createGraphicObject(currentEntity);
		    if (obj) {
			if (_doingAPolyline) {
			    _manager->
				addObject(obj,
					  IlFalse,
					  getLayerIndex(_currentPolyline));
			    _doingAPolyline = IlFalse;
			}
			else
			    _manager->
				addObject(obj,
					  IlFalse,
					  getLayerIndex(currentEntity));
		    }
		}
	    }
	    if (_currentGroup.match(0, "ENDBLK") ||
		_currentGroup.match(0, "ENDSEC")) {
		pushBackGroup();
		if (currentEntity)
		    delete currentEntity;
		return IlTrue;
	    }
	    if (!store && currentEntity) { 
		//reuse the  same entity
		currentEntity->empty();
		currentEntity->addGroup(_currentGroup);
	    }
	    else {
		if (currentEntity)
		    delete currentEntity;
		currentEntity = new DXFElement(_currentGroup);
	    }
	}
	else {
	    if (!currentEntity) {
		char buffer[150];
		sprintf(buffer,
			"Group 0 in entities expected at line/byte %ld",
			(long int) _fileOffset);
		setError(buffer);
	    }
	    currentEntity->addGroup(_currentGroup);
	}
    }
    if (currentEntity)
	delete currentEntity;
    IlvSetContentsChangedUpdate(allowed);
    return !_fail;
}

// --------------------------------------------------------------------------
static char*
ParseDXFString(const char* inString, IlvFontStyle& flags)
{
    size_t   inLength  = strlen(inString);
    // char* outString = IlvAllocString(inLength*2+1);	
    char* outString = IlvPoolOf(char)::Alloc((IlUInt)(inLength*2+1));	
    const char* in  = inString;
    char*       out = outString;
    flags = IlvNormalFontStyle;
    for (size_t count = 0; *in; in++, count++) {
	if ((count+3 < inLength) && !strncmp(in, "%%u", 3)) {
	    flags  = (IlvFontStyle)(flags | IlvUnderlinedFontStyle);
	    count += 2;
	    in    += 2;
	}
	else *out++ = *in;
    }
    *out = 0;
    return outString;
}

// --------------------------------------------------------------------------
IlvGraphic*
DXFReader::createGraphicObject(DXFElement* entity,
			       IlvTransformer* transformer)
{
    DXFGroup* typeGroup  = entity->getGroup(0);
    if (!typeGroup)
	return 0;
    
    const char* type = typeGroup->getString();
    DXFGroup* lineTypeGroup = entity->getGroup(6);
    DXFGroup* colorGroup =
	(lineTypeGroup &&
	 !ILVSTRCASECMP(lineTypeGroup->getString(), "bylayer"))
	? 0
	: entity->getGroup(62);
    
    DXFGroup* layerGroup = entity->getGroup(8);
    const char* layer = layerGroup ? layerGroup->getString() : 0;

    IlvPalette* palette = layer
	? (colorGroup
	   ? createPalette(layer, colorGroup->getShort())
	   : createPalette(layer)) : 0;
    if (palette)
	palette->lock();

    
    IlvGraphic* graphic = 0;
    if (!ILVSTRCASECMP(type, "POINT")) {
	IlvCoordinate c(entity->getDouble(10),
			entity->getDouble(20));
	return _factory->createPoint(transformer, c, palette);
    }
    else if (!ILVSTRCASECMP(type, "LINE")) {
	IlvCoordinate from(entity->getDouble(10), entity->getDouble(20));
	IlvCoordinate to(entity->getDouble(11), entity->getDouble(21));
	graphic =  _factory->createLine(transformer, from, to, palette);
    }
    else if (!ILVSTRCASECMP(type, "ARC")) {
      IlDouble cx = entity->getDouble(10);
      IlDouble cy = entity->getDouble(20);
      IlDouble radius = entity->getDouble(40);
      IlvCoordinate ul(cx-radius, cy-radius);
      IlvCoordinate lr(cx+radius, cy+radius);
      IlDouble startAngle = entity->getDouble(50);
      IlDouble endAngle   = entity->getDouble(51);

      
      if (startAngle == endAngle)
	return 0;

      if (_angdir) {
	startAngle = - startAngle;
	endAngle   = - endAngle;
      }
      if (startAngle >  180) startAngle -= 360.;
      if (startAngle < -180) startAngle += 360.;
      
      IlDouble angleRange = entity->getDouble(51)-startAngle;
      if (angleRange >  180) angleRange -= 360;
      if (angleRange < -180) angleRange += 360;
      return _factory->createArc(transformer,
				 ul,
				 lr,
				 startAngle,
				 angleRange,
				 palette);
    }
    else if (!ILVSTRCASECMP(type, "CIRCLE")) {
      IlvCoordinate center(entity->getDouble(10),
			   entity->getDouble(20));
      IlDouble radius = entity->getDouble(40);
      return _factory->createCircle(transformer,
				    center,
				    radius,
				    palette);
    }
    else if (!ILVSTRCASECMP(type, "POLYLINE")) {
	_currentPolyLinePalette = palette;
	if (_currentPolyLinePalette)
	    _currentPolyLinePalette->lock();
	_currentPolyline->empty();
	_currentPolyline->addGroup(*entity->getGroup(0));
	if (layerGroup)
	    _currentPolyline->addGroup(*layerGroup);
	_doingAPolyline = IlTrue;
	_currentPolylineFlags   = entity->getShort(70);
	return 0;
    }
    else if (!ILVSTRCASECMP(type, "VERTEX")) {
	if (_doingAPolyline) 
	    _polylinePoints.addElement(IlvCoordinate(entity->getDouble(10),
						     entity->getDouble(20)));
	return 0;
    }
    else if (!ILVSTRCASECMP(type, "SEQEND")) {
	if (_doingAPolyline) {
	    if ((_currentPolylineFlags & 16) != 0) {
		graphic = _factory->createPolygon(transformer,
						  _polylinePoints.getLength(),
						  _polylinePoints.getPoints(),
						  _currentPolyLinePalette);
	    }
	    else {
		if ((_currentPolylineFlags & 1) != 0) {
		    _polylinePoints.addElement(_polylinePoints.getPoint(0));
		}
		graphic = _factory->createPolyline(transformer,
						   _polylinePoints.getLength(),
						   _polylinePoints.getPoints(),
						   _currentPolyLinePalette);
	    }
	    if (_currentPolyLinePalette)
		_currentPolyLinePalette->unLock();
	    _polylinePoints.reset();
	}
	else if (_insertAttribEntities != 0) {
	    _insertAttribEntities = 0;
	    return 0;
	}
	else IlvWarning("Unexpected SEQEND entity");
    }
    else
	if (!ILVSTRCASECMP(type, "TEXT")) {
	    int hAlign = entity->getShort(72);
	    int vAlign = entity->getShort(73);
	    IlvFontStyle flags;
	    char* string = ParseDXFString(entity->getString(1), flags);
	    IlDouble height = entity->getDouble(40);
	    IlDouble xRatio = 0;
	    if (entity->getGroup(41))
		xRatio = entity->getDouble(41);
	    IlvCoordinate location(entity->getGroup(11)
				   ? entity->getDouble(11)
				   : entity->getDouble(10),
		                   entity->getGroup(21)
				   ? entity->getDouble(21)
				   : entity->getDouble(20));
	    IlvPosition position = IlvLeft;
	    if ((hAlign == 1) || (hAlign == 4))
		position = IlvCenter;
	    if (hAlign == 2)
		position = IlvRight;
	    
	    if (vAlign == 1)
		switch (position) {
		case IlvLeft: position = IlvBottomLeft; break;
		case IlvRight: position = IlvBottomRight; break;
		default: position = IlvBottom; break;
		}

	    if (vAlign == 3)
		switch (position) {
		case IlvLeft: position = IlvTopLeft; break;
		case IlvRight: position = IlvTopRight; break;
		default: position = IlvTop;
		}
	    
	    position = (IlvPosition) (IlvBottom | position);
	    return _factory->createText(transformer,
					string,
					location,
					position,
					height,
					palette);
      
      
    }
    else if (!ILVSTRCASECMP(type, "TRACE") ||
	     !ILVSTRCASECMP(type, "SOLID") ||
	     !ILVSTRCASECMP(type, "3DFACE")) {
	IlBoolean solid =  !ILVSTRCASECMP(type, "SOLID");
	static IlvCoordinate points[5];
	points[0].move(entity->getDouble(10),
		       entity->getDouble(20));
	points[1].move(entity->getDouble(11),
		       entity->getDouble(21));
	points[2].move(entity->getDouble(12),
		       entity->getDouble(22));
	points[3].move(entity->getDouble(13),
		       entity->getDouble(23));
	if (solid) {
	    IlvCoordinate p = points[3];
	    points[3].move(points[2].x(), points[2].y());
	    points[2].move(p.x(), p.y());
	    graphic = _factory->createPolygon(transformer,
					      4,
					      points,
					      palette);
	}
	else {
	    points[4] = points[0];
	    graphic = _factory->createPolyline(transformer,
					       5,
					       points,
					       palette); // 5 points
	}
    }
    else if (!ILVSTRCASECMP(type, "INSERT")) {
	DXFElement* block = getBlock(entity->getString(2));
	if (block && block->getEntities()) {
	    DXFElementList* entitiesList = block->getEntities();
	    DXFGroup* group = entity->getGroup(41);
	    IlDouble sx = (group) ? group->getDouble() : 1.;
	    group = entity->getGroup(42);
	    IlDouble sy = (group) ? group->getDouble() : 1.;
	    if ((group = entity->getGroup(70)) != 0 && 
		(group->getShort() != 1))
		IlvWarning("Column count %d for INSERT not supported",
			   group->getShort());
	    if ((group = entity->getGroup(71)) != 0 && 
		(group->getShort() != 1))
		IlvWarning("Row count %d for INSERT not supported",
			   group->getShort());
	    if ((group = entity->getGroup(44))  != 0 && 
		(group->getDouble() != 0))
		IlvWarning("Column spacing %.2f for INSERT not supported",
			   group->getDouble());
	    if ((group = entity->getGroup(45)) != 0 && 
		(group->getDouble() != 0))
		IlvWarning("Row spacing %.2f for INSERT not supported",
			   group->getDouble());
	    
	    DXFGroup* attribGroup = entity->getGroup(66);
	    if (attribGroup  && ((attribGroup->getShort() & 1) != 0))
		_insertAttribEntities = entitiesList;
	    
	    IlvTransformer localT;
	    localT.translate(-block->getDouble(10),
			     -block->getDouble(20));
	    localT.scale(0, 0, sx, sy);
	    group = entity->getGroup(50);
	    if (group)
		localT.rotate(0,
			      0,
			      _angdir
			      ? - group->getDouble()
			      : group->getDouble());
	    localT.translate(entity->getDouble(10),
			     entity->getDouble(20));
	    if (transformer) 
		localT.compose(*transformer);
	    
	    
	    IlvGraphicSet* graphicSet = 0;
	    IlvGraphic*    firstGraphic = 0;
	    if (entitiesList != 0) {
		int entitiesCount = entitiesList->getLength();
		for (int i = 0; i < entitiesCount; i++) {
		    DXFElement* thisEntity = entitiesList->getElement(i);
		    IlvGraphic* graphic2 =
			createGraphicObject(thisEntity, &localT);
		    if (graphic2) {
			if (graphicSet)
			    graphicSet->addObject(graphic2);
			else
			    if (firstGraphic) {
				graphicSet = new IlvGraphicSet();
				graphicSet->addObject(firstGraphic);
				graphicSet->addObject(graphic2);
			    }
			    else firstGraphic = graphic2;
		    }
		}
	    }
	    graphic = (graphicSet) ? graphicSet : firstGraphic;
	}
    }
    else
	if (ILVSTRCASECMP(type, "ATTRIB")) {
	    if (_insertAttribEntities != 0)
		return 0;
	    else
		IlvWarning("Unexpected ATTRIB entity");
	}
	else
	    if (ILVSTRCASECMP(type, "ATTDEF"))
		return 0;
	    else
		IlvWarning("Entity type %s is not implemented", type);
    if (palette)
	palette->unLock();
    return graphic;
}

// --------------------------------------------------------------------------
/**
 * Returns the index of the manager layer where
 * the entity must be placed depending on the DXF layer
 * name.
 */
int
DXFReader::getLayerIndex(DXFElement* entity) const
{
    DXFGroup* typeGroup  = entity->getGroup(0);
    if (!typeGroup)
	return 0;
    DXFGroup* layerGroup = entity->getGroup(8);
    
    if (layerGroup) {
	const char* groupName = layerGroup->getString();
	int nbLayers = _layers ? _layers->getLength() : 0;
	for (int i = 0; i < nbLayers; i++) {
	    DXFElement* currentLayer = _layers->getElement(i);
	    const DXFGroup* nameGroup = currentLayer->getGroup(2);
	    if (nameGroup) {
		const char* layerName = nameGroup->getString();
		if (!ILVSTRCASECMP(layerName, groupName)) {
		    IlvManagerLayer* layer = (IlvManagerLayer*)
			currentLayer->getData();
		    if (!layer) {
			int layerCount = _manager->getNumLayers();
			_manager->addLayer(-1);
			layer = _manager->getManagerLayer(layerCount);
			layer->setName(layerName);
			currentLayer->setData(layer);
		    }
		    return layer->getIndex();
		}
	    }
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvPalette*
DXFReader::createPalette(const char* layerName, IlShort color) const
{
    IlvDisplay* display = _manager->getDisplay();
    IlvColor* foreground = (color == -1) ? 0 : createColor(color);
    int nbLayers = _layers ? _layers->getLength(): 0;
    for (int i = 0; i < nbLayers; i++) {
	DXFElement* layer = _layers->getElement(i);
	const DXFGroup* nameGroup = layer->getGroup(2);
	if (nameGroup) {
	    const char* currentName = nameGroup->getString();
	    if (!ILVSTRCASECMP(layerName, currentName)) {
		IlvPalette* palette = layer->getPalette();
		if (palette) {
		    if (foreground)
			return display->getPalette(palette->getBackground(),
						   foreground,
						   palette->getPattern(),
						   0,
						   palette->getFont(),
						   palette->getLineStyle(),
						   0,
						   IlvFillPattern);
		    return palette;
		}
		if (!foreground) {
		    DXFGroup* colorGroup = layer->getGroup(62);
		    foreground = colorGroup
			? createColor((int)colorGroup->getShort())
			: display->defaultForeground();
		}
		DXFGroup* lineStyleGroup = layer->getGroup(6);
		IlvLineStyle* lineStyle = lineStyleGroup ?
		    createLineStyle(lineStyleGroup->getString()) :
		    display->defaultLineStyle();
		palette =
		    display->getPalette(display->defaultBackground(),
					foreground,
					display->solidPattern(),
					0,
					display->defaultFont(),
					lineStyle,
					0,
					IlvFillPattern);
		layer->setPalette(palette);
		return palette;
	    }
	}
    }
    return display->getPalette(0, foreground);
}

// --------------------------------------------------------------------------
IlvColor*
DXFReader::createColor(IlShort colorIndex) const
{
    const char* colorName = parseColor(colorIndex);
    return colorName
	? _manager->getDisplay()->getColor(colorName)
	: _manager->getDisplay()->defaultForeground();
}

// --------------------------------------------------------------------------
const char*
DXFReader::parseColor(IlShort colorIndex) const
{
    switch (colorIndex & 0xF) {
    case  0: return "black";
    case  1: return "red";
    case  2: return "yellow";
    case  3: return "green";
    case  4: return "cyan";
    case  5: return "blue";
    case  6: return "magenta";
    case  7: return "black";
    case  8: return "gray";
    case 15: return "white";
    }
    return 0;
}

// --------------------------------------------------------------------------
IlvLineStyle*
DXFReader::createLineStyle(const char* /* lineStyleName */) const
{
    // LineStyle is not converted (yet)
    return _manager->getDisplay()->defaultLineStyle();
}

// --------------------------------------------------------------------------
/**
 * Reads the HEADER section.
 */
IlBoolean
DXFReader::readHeader()
{
    while (IlTrue) {
	if (!readGroup())
	    return IlFalse;
	if (_currentGroup.match(9, "$ANGBASE")) {
	    readGroup(); // Should be a 50-group
	    _angbase = _currentGroup.getDouble();
	}
	else if (_currentGroup.match(9, "$ANGDIR")) {
	    readGroup(); // Should be a 70-group
	    _angdir = (IlInt) _currentGroup.getShort();
	}
	else if (_currentGroup.match(9, "$EXTMIN")) {
	    while (IlTrue) {
		if (!readGroup())
		    return IlFalse;
		if ((_currentGroup.getCode() == 9) ||
		    (_currentGroup.getCode() == 0)) {
		    pushBackGroup();
		    break;
		}
		if (_currentGroup.getCode() == 10) {
		    _lowerLeftCorner.x(_currentGroup.getDouble());
		    _lowerLeftCornerKnown = IlTrue;
		}
		if (_currentGroup.getCode() == 20) {
		    _lowerLeftCorner.y(_currentGroup.getDouble());
		    _lowerLeftCornerKnown = IlTrue;
		}
	    }
	}
	else if (_currentGroup.match(9, "$EXTMAX")) {
	    while (IlTrue) {
		if (!readGroup())
		    return IlFalse;
		if ((_currentGroup.getCode() == 9) ||
		    (_currentGroup.getCode() == 0)) {
		    pushBackGroup();
		    break;
		}
		if (_currentGroup.getCode() == 10) {
		    _upperRightCorner.x(_currentGroup.getDouble());
		    _upperRightCornerKnown = IlTrue;
		}
		if (_currentGroup.getCode() == 20) {
		    _upperRightCorner.y(_currentGroup.getDouble());
		    _upperRightCornerKnown = IlTrue;
		}
	    }
	}
	if (_currentGroup.match(0, "ENDSEC")) {
	    pushBackGroup();
	    return IlTrue;
	}
    }
}

// --------------------------------------------------------------------------
void
DXFReader::updateGraphicFactory()
{
    if (!_factory->getMapInfo()) {
	// test consistency of the data
	if ((_upperRightCorner.y() > _lowerLeftCorner.y()) &&
	    (_upperRightCorner.y() > _lowerLeftCorner.y()))
	    _factory->updateMapInfo(_lowerLeftCorner, _upperRightCorner);
    }
}

// --------------------------------------------------------------------------
IlBoolean
DXFReader::readBlocks()
{
    while (IlTrue) {
	if (!readGroup())
	    return IlFalse;
	if (_currentGroup.match(0, "BLOCK")) {
	    readGroup();
	    if (!readBlock())
		return IlFalse;
	}
	else if (_currentGroup.match(0, "ENDSEC"))
	    return IlTrue;
    }
}


// --------------------------------------------------------------------------
IlBoolean
DXFReader::readBlock()
{
    DXFElement* currentBlock = new DXFElement(_currentGroup);
    if (!_blocks)
	_blocks = new DXFElementList();
    while (IlTrue) {
	if (!readGroup())
	    return IlFalse;
	if (_currentGroup.match(0, "ENDBLK"))
	    break ;
	else
	    if (_currentGroup.getCode() == 0) {
		pushBackGroup();
		if (!readEntities(IlTrue))
		    return IlFalse;
		currentBlock->setEntities(_entities);
		_entities = 0;
	    }
	    else currentBlock->addGroup(_currentGroup);
    }
    DXFGroup* blockName = currentBlock->getGroup(2);
    _blocks->addElement(currentBlock);
    return IlTrue;
}
  
// --------------------------------------------------------------------------
DXFElement*
DXFReader::getBlock(const char* blockName)
{
    if (!_blocks)
	return 0;
    int nbBlocks = _blocks->getLength();
    for (int i = 0; i < nbBlocks; i++) {
	DXFElement* currentBlock = _blocks->getElement(i);
	const DXFGroup* nameGroup = currentBlock->getGroup(2);
	if (nameGroup) {
	    const char* currentGroupName = nameGroup->getString();
	    if (!ILVSTRCASECMP(currentGroupName, blockName)) {
		return currentBlock;
	    }
	}
    }
    return 0;
}

