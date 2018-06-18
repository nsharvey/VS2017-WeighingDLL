// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/rendering/cmodel.h
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
#ifndef __ILV_maps_Rendering_IlvMapColorModel_H
#define __ILV_maps_Rendering_IlvMapColorModel_H


#include <ilviews/maps/maps.h>
#include <ilviews/maps/clssinfo.h>
#include <ilviews/base/resource.h>

ILVMAPSMODULEINIT(cmodel);

class ILVMAPSEXPORTED IlvMapColorModel
{
private:
    static IlvClassInfo* _classinfo;

protected:
    IlvMapColorModel();

public:
    virtual ~IlvMapColorModel();

    virtual IlvMapColorModel* copy() const = 0;

    // ClassInfo functions
    virtual IlvMapClassInfo* getClassInfo() const = 0;
    static IlvMapClassInfo* ClassInfo();
    static IlvClassInfo** ClassInfoRef();

    virtual IlBoolean isPersistent() const;

    virtual IlUChar getAlpha(IlInt pixel) const = 0;

    virtual IlUChar getBlue(IlInt pixel) const = 0;

    virtual IlUChar getGreen(IlInt pixel) const = 0;

    virtual IlUChar getRed(IlInt pixel) const = 0;

    virtual void getRGBA(IlInt pixel,
			 IlUChar& red,
			 IlUChar& green,
			 IlUChar& blue,
			 IlUChar& alpha) const;
    virtual void write(IlvOutputFile& file) const = 0;

    void save(IlvOutputFile& file) const;
private:
    static void Init();
    IlvMapsIcFriend(cmodel, ILVMAPSEXPORTED);
};


// Useful MACROS
// Class declaration
#define ILVMAPS_DECLMANDATORYCMODELMEMBERS(className) \
public:                                                       \
    virtual IlvMapColorModel* copy() const;                   \
    IlvMapsDeclareIO(className)

// Class definition
#define ILVMAPS_DEFCMODEL(className,                          \
			  superClass)                         \
IlvMapColorModel*                                             \
className::copy() const                                       \
{                                                             \
    return new className(*this);                              \
}                                                             \
IlvMapsPreregisterIO(className)




class ILVMAPSEXPORTED IlvIntervalColorModel
    : public IlvMapColorModel
{
private:
    IlUChar*   _red;
    IlUChar*   _green;
    IlUChar*   _blue;
    IlUInt      _colorsNum;
    IlInt*     _limits;
    IlUInt      _limitsNum;

public:   
    virtual ~IlvIntervalColorModel();

    IlvIntervalColorModel(const IlUChar*   redMap,
			  const IlUChar*   greenMap,
			  const IlUChar*   blueMap,
			  IlUInt colorCount,
			  const IlInt* limits,
			  IlUInt limitCount);
    IlvIntervalColorModel(const IlvIntervalColorModel& model);

    virtual IlUChar getAlpha(IlInt pixel) const;

    virtual IlUChar getBlue(IlInt pixel) const;

    virtual IlUChar getGreen(IlInt pixel) const;

    virtual IlUChar getRed(IlInt pixel) const;

    IlUInt getColors(IlUChar*& redmap,
		     IlUChar*& greenmap,
		     IlUChar*& bluemap) const;


    IlUInt getLimits(IlInt*& limits) const;

    IlBoolean isPersistent() const;

    static IlvIntervalColorModel* MakeElevationColorModel();

private:
    IlUInt getIntervalIndex(IlInt pixel) const;

    static void Init();
    IlvMapsIcFriend(cmodel, ILVMAPSEXPORTED);

    ILVMAPS_DECLMANDATORYCMODELMEMBERS(IlvIntervalColorModel);
};


#endif // __ILV_maps_Rendering_IlvMapColorModel_H
