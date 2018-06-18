// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/rendering/rdrstyle.h
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
// Rendering Package
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __ILV_maps_Geometry_IlvMapRenderingStyle_H
#define __ILV_maps_Geometry_IlvMapRenderingStyle_H

#include <ilviews/maps/renderer.h>

ILVMAPSMODULEINIT(rdrstyle);

class ILVMAPSEXPORTED IlvMapRenderingStyle
{
private:
    IlInt _lockCount;
    IlvDisplay* _display;
protected:
    IlvMapRenderingStyle(IlvDisplay* display);

    IlvMapRenderingStyle(const IlvMapRenderingStyle& source);

    virtual ~IlvMapRenderingStyle();

public:

    void lock() {_lockCount++;}
    void unLock() {_lockCount--; if (!_lockCount) delete this;}

    IlvDisplay* getDisplay() const {return _display;}

    // not documented
    virtual void write(IlvOutputFile& file) const = 0;

    void save(IlvOutputFile& file) const;

    static IlvMapRenderingStyle* Load(IlvInputFile& file);

    virtual IlvMapRenderingStyle* copy() const = 0;

    // ClassInfo functions
    virtual IlvMapClassInfo* getClassInfo() const = 0;
    static IlvMapClassInfo* ClassInfo()
	{ return (IlvMapClassInfo*)_classinfo; };
    static IlvClassInfo** ClassInfoRef() { return &_classinfo; };
private:
    static IlvClassInfo* _classinfo;
    static void Init();
    IlvMapsIcFriend(rdrstyle, ILVMAPSEXPORTED);
};

// Useful MACROS
// Class declaration
#define ILVMAPS_DECLMANDATORYRDRSTYLEMEMBERS(className)         \
public:                                                         \
    virtual IlvMapRenderingStyle* copy() const;                 \
    IlvMapsDeclareIO(className)

// Class definition
#define ILVMAPS_DEFRDRSTYLE(className,                          \
			    superClass)                         \
IlvMapRenderingStyle*                                           \
className::copy() const                                         \
{                                                               \
    return new className(*this);                                \
}                                                               \
IlvMapsPreregisterIO(className)




#endif // __ILV_maps_Geometry_IlvMapRenderingStyle_H
