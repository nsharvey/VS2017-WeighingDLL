// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/renderer.h
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
// Definition of the IlvFeatureRenderer class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Renderer_H
#define __Ilv_Maps_Renderer_H

#if !defined(__Ilv_Maps_Mapfeature_H)
#  include <ilviews/maps/mapfeature.h>
#endif
#if !defined(__Ilv_Maps_Mapinfo_H)
#  include <ilviews/maps/mapinfo.h>
#endif
#if !defined(__Ilv_Maps_Macros_H)
#  include <ilviews/maps/macros.h>
#endif
#if !defined(__Ilv_Maps_Clssinfo_H)
#  include <ilviews/maps/clssinfo.h>
#endif

ILVMAPSMODULEINIT(renderer);

class ILVMAPSEXPORTED IlvFeatureRenderer
{
public:
    virtual ~IlvFeatureRenderer();

    virtual IlvGraphic* makeGraphic(const IlvMapFeature& feature,
				    const IlvMapInfo& targetMapInfo,
				    IlvMapsError& status) const = 0;
    virtual void write(IlvOutputFile& file) const = 0;
    void save(IlvOutputFile& file) const;
    static IlvFeatureRenderer* Load(IlvInputFile& file);
    IlBoolean isPersistent() const {return _persistent;}
    virtual IlvFeatureRenderer* copy() const = 0;
    IlvDisplay* getDisplay() const {return _display;}

    // ClassInfo functions
    virtual IlvMapClassInfo* getClassInfo() const = 0;
    static IlvMapClassInfo* ClassInfo();
    static IlvClassInfo** ClassInfoRef();

    IlvMapsIcFriend(renderer, ILVMAPSEXPORTED);
protected:
    IlvFeatureRenderer(IlvDisplay* display, IlBoolean persistent = IlTrue);
private:
    static IlvClassInfo* _classinfo;
    IlBoolean _persistent;
    IlvDisplay* _display;
};

// Useful MACROS
// Class declaration
#define ILVMAPS_DECLMANDATORYRENDERERMEMBERS(className)	\
public:							\
    virtual IlvFeatureRenderer* copy() const;		\
    IlvMapsDeclareIO(className)

// Class definition
#define ILVMAPS_DEFRENDERER(className, superClass)		\
IlvFeatureRenderer* className::copy() const			\
    { return new className(*this); }				\
IlvMapsPreregisterIO(className)

#endif /* !__Ilv_Maps_Renderer_H */
