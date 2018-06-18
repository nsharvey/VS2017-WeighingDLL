// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/attribute.h
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
#ifndef __Ilv_Maps_Attribute_H
#define __Ilv_Maps_Attribute_H

#if !defined(__Ilv_Maps_Clssinfo_H)
#  include <ilviews/maps/clssinfo.h>
#endif
#if !defined(__Ilv_Graphics_Io_H)
#  include <ilviews/graphics/io.h>
#endif

ILVMAPSMODULEINIT(IlvFeatureAttribute);

class ILVMAPSEXPORTED IlvFeatureAttribute
{
protected:
    IlvFeatureAttribute();

public:
    virtual ~IlvFeatureAttribute();

    virtual void	write(IlvOutputFile& output) const = 0;
    virtual
    IlvFeatureAttribute* copy() const = 0;
    void		save(IlvOutputFile& file) const;
    static
    IlvFeatureAttribute* Load(IlvInputFile& file);
private:
    static IlvClassInfo* _classinfo;

public:
    inline static
    IlvMapClassInfo*	ClassInfo() { return (IlvMapClassInfo*) _classinfo; }
    inline static
    IlvClassInfo**	ClassInfoRef() { return &_classinfo; }
    virtual
    IlvMapClassInfo*	getClassInfo() const;

private:
    static void		Init();
    IlvMapsIcFriend(IlvFeatureAttribute, ILVMAPSEXPORTED);
};

// Class declaration
#define ILVMAPS_DECLMANDATORYATTRMEMBERS(className)	     \
private:						     \
    static void Init();					     \
    static void Finalize();				     \
    IlvMapsIcFriend(attribute_##className, ILVMAPSEXPORTED); \
    IlvMapsDeclareIO(className)

// Class definition
#define ILVMAPS_DEFATTRIBUTE(className, superClass)             \
ILVMAPS_BEGINMODULEINITDEF(attribute_##className)               \
className::Init();                                              \
ILVMAPS_ENDMODULEINITDEF(attribute_##className)                 \
ILVMAPS_BEGINMODULETERMDEF(attribute_##className)               \
className::Finalize();                                          \
ILVMAPS_ENDMODULETERMDEF(attribute_##className)                 \
IlvFeatureAttribute*                                            \
className::copy() const                                         \
{                                                               \
    return new className(*this);                                \
}                                                               \
IlvMapsPreregisterIO(className);

#endif /* __Ilv_Maps_Attribute_H */
