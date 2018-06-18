// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/geometry.h
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
// General Class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Geometry_H
#define __Ilv_Maps_Geometry_H

#if defined(IL_STD)
#  include <cmath>
#else  /* !IL_STD */
#  include <math.h>
#endif /* IL_STD */

#if !defined(__Ilv_Maps_Coord_H)
#  include <ilviews/maps/coord.h>
#endif
#if !defined(__Ilv_Maps_Clssinfo_H)
#  include <ilviews/maps/clssinfo.h>
#endif

ILVMAPSMODULEINIT(IlvMapGeometry);

class ILVMAPSEXPORTED IlvMapGeometry
{
public:
    virtual ~IlvMapGeometry();

    virtual IlvMapGeometry* copy() const = 0;
    virtual IlBoolean isCollection() const = 0;
    virtual IlUInt getSubElementCount() const = 0;
    virtual const IlvMapGeometry* getSubElement(IlUInt index) const = 0;

    // ClassInfo functions
    virtual IlvClassInfo* getClassInfo() const = 0;
    static IlvClassInfo* ClassInfo();
    static IlvClassInfo** ClassInfoRef();
protected:
    IlvMapGeometry();
private:
    static IlvClassInfo* _classinfo;

    static void Init();

    IlvMapsIcFriend(IlvMapGeometry, ILVMAPSEXPORTED);
};

#define ILVMAPS_DECL_GEOM_MEMBERS()				\
public:                                                         \
    inline static IlvClassInfo** ClassInfoRef()			\
	{ return &_classinfo; }					\
    inline static IlvClassInfo* ClassInfo()			\
	{ return _classinfo; }					\
private:							\
    static IlvClassInfo* _classinfo


#define ILVMAPS_DEFINE_GEOM_CLASSINFO_MEMBERS(className)	\
IlvClassInfo* className::_classinfo = 0;			\
IlvClassInfo* className::getClassInfo() const			\
    { return ClassInfo(); }					\
IlvMapGeometry* className::copy() const			        \
    { return new className(*this); }

#define ILVMAPS_DEFINE_GEOM_MEMBERS(className, superClass)	\
ILVMAPS_DEFINE_GEOM_CLASSINFO_MEMBERS(className)		\
ILVMAPS_BEGINMODULEINITDEF(className)				\
    ILVMAPS_MODINIT(superClass)();				\
if (!className::_classinfo) {					\
    className::_classinfo = IlvClassInfo::Create(#className,	\
	superClass::ClassInfoRef());				\
}								\
ILVMAPS_ENDMODULEINITDEF(className)

#endif /* !__Ilv_Maps_Geometry_H */
