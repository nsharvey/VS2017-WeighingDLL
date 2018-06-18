// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/frlamber.h
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
// Declaration of the IlvFrenchLambertProjection class
// Defined in library ilvmaps
// --------------------------------------------------------------------------


#ifndef __Ilv_Maps_FrenchLambert_H
#define __Ilv_Maps_FrenchLambert_H

#include <ilviews/maps/projection/lconfcon.h>

ILVMAPSMODULETERM(IlvFrenchLambertProjection);

enum IlvFrenchLambertMode {
    IlvFrenchLambert_I,
    IlvFrenchLambert_II,
    IlvFrenchLambert_III,
    IlvFrenchLambert_IV,
    IlvFrenchLambert_II_extended,
    IlvFrenchLambert_93
};

class ILVMAPSEXPORTED IlvFrenchLambertProjection
: public IlvLambertConformalConicProjection 
{
public:

    IlvFrenchLambertProjection(IlvFrenchLambertMode mode =
			       IlvFrenchLambert_II_extended);
    IlvFrenchLambertProjection(IlvInputFile& stream);
    IlvFrenchLambertProjection(const IlvFrenchLambertProjection&);

    virtual IlvProjectionClassInfo* getClassInfo() const;
    static IlvProjectionClassInfo* ClassInfo()
    {return (IlvProjectionClassInfo*) _classInfo;}
    static IlvClassInfo** ClassInfoRef() {return &_classInfo;}

    virtual IlvProjection* copy() const;

    IlvFrenchLambertMode getMode() const {return _mode;}

    void setMode(IlvFrenchLambertMode mode);

    IlDouble getNorthLimit() const { return GetNorthLimit(_mode);}
    IlDouble getSouthLimit() const { return GetSouthLimit(_mode);}

    static IlDouble GetParisMeridian()
    { return _parisMeridian;}

    static const IlvEllipsoid* GetNTFEllipsoid()
    { return _clrk80IGN;}

    static const IlvEllipsoid* GetRGF93Ellipsoid()
    { return _grs80Ellipsoid;}


    static IlDouble GetNorthLimit(IlvFrenchLambertMode mode);
    static IlDouble GetSouthLimit(IlvFrenchLambertMode mode);

    virtual void setLLCenter(double , double );
    virtual void setScaleFactor(double);
    virtual  IlvMapsError setSecantLatitudes(const IlvCoordinate& secant);
    virtual void write(IlvOutputFile&) const ;


    static void SetModeLabels(const char* lambert1,
			      const char* lambert2,
			      const char* lambert3,
			      const char* lambert4,
			      const char* lambert2extended,
			      const char* lambert93);

private:
    static void Init();
    static void Finalize();

private:
    IlvFrenchLambertMode _mode;

    static IlvClassInfo* _classInfo;

    static const IlDouble _parisMeridian;
    static const IlvEllipsoid* _clrk80IGN;
    static const IlvEllipsoid* _grs80Ellipsoid;

    IlvMapsIcFriend(IlvFrenchLambertProjection, ILVMAPSEXPORTED);
};

#endif
