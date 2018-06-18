// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/dxf/include/dxfbasic.h
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
// Declaration of the DXF Entities used by the reader
// --------------------------------------------------------------------------

#ifndef DXFBasic_H
#define DXFBasic_H

#include <ilviews/macros.h>
#include <ilviews/maps/projection/project.h>

/**
 * A DXF Group.
 * A group is composed of a code, an a value.
 * The value of a group can be a short, a double
 * or a string.
 */
class DXFGroup
{
  public:
    DXFGroup();
    DXFGroup(const DXFGroup& source);

    ~DXFGroup();
    
    void release();

    void set(IlInt code, IlShort value);
    void set(IlInt code, IlDouble value);
    void set(IlInt code,  const char* value);

    IlInt getCode() const {return _code;}

    IlShort getShort() const { return _value.shortValue;}
    IlDouble   getDouble() const { return _value.doubleValue;}
    const char* getString() const { return _value.stringValue;}
    IlBoolean   match(IlInt code, const char* string) const;
    
  public:
    static const IlShort STRING_TYPE;
    static const IlShort SHORT_TYPE;
    static const IlShort DOUBLE_TYPE;
    static const IlShort NO_TYPE;

  private:
    IlInt     _code;
    IlShort   _type;
    union DXFValue {
	char* stringValue;
	IlDouble doubleValue;
	IlShort   shortValue;
    } _value;
 
};

class DXFElementList;

class DXFElement
{
  public:
    DXFElement(const DXFGroup& group);
    DXFElement(const DXFElement& source);
    ~DXFElement();
    
    void empty();
 
    IlInt getLength()  const {return _size;}
    IlvAny getData() const {return _data;}
    void setData(IlvAny data) {_data = data;}

    void addGroup(const DXFGroup& newGroup);
    DXFGroup* getGroup(IlInt code)  const;
    
    IlShort getShort(IlInt group) const;
    IlDouble getDouble(IlInt group) const;
    const char* getString(IlInt group) const;

    void setPalette(IlvPalette* palette);
    IlvPalette* getPalette() const {return _palette;}

    void setEntities(DXFElementList* entites) {_entities = entites;}
    DXFElementList* getEntities() const {return _entities;}
  
  private:
    void grow();
    
  private:
    // contains DXFGroup
    IlvAny _data;
    DXFGroup** _elements;
    IlInt _size;
    IlInt _maxSize;
    IlvPalette* _palette;
    DXFElementList* _entities;
};

class DXFElementList
{
  public:
    DXFElementList(DXFElement* first = 0);
    ~DXFElementList();
 
    IlInt getLength()  const {return _size;}
    void addElement(DXFElement* element);
    DXFElement* getElement(IlInt index)  const {return _elements[index];}

    void setData(IlvAny* data) {_data = data;}
    IlvAny getData() {return _data;}

  private:
    void grow();
    
  private:
    DXFElement** _elements;
    IlInt _size;
    IlInt _maxSize;
    IlvAny _data;
};

class DXFCoordinateArray
{
  public:
    DXFCoordinateArray();
    ~DXFCoordinateArray();

    void reset();
    
    IlInt getLength()  const {return _size;}
    void addElement(const IlvCoordinate& element);
    const IlvCoordinate& getPoint(IlInt index)  const
    {return _points[index];}
    const IlvCoordinate* getPoints() const {return _points;}

  private:
    void grow();
    
  private:
    IlvCoordinate* _points;
    IlInt _size;
    IlInt _maxSize;
};

class DXFTransformer {
  public:
    DXFTransformer();
};

#endif
