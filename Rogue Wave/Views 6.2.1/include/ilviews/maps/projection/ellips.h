// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/ellips.h
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
// Definition of the IlvEllipsoid class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Ellips_H
#define __Ilv_Maps_Ellips_H

#include <ilviews/maps/macros.h>
#include <ilviews/maps/maps.h>
#include <ilviews/base/hash.h>

ILVMAPSMODULETERM(ellips);

class ILVDSPEXPORTED IlvInputFile;
class ILVDSPEXPORTED IlvOutputFile;

class ILVMAPSEXPORTED IlvEllipsoid
{
public:
    IlvEllipsoid(IlDouble		radius,
		 IlDouble		eccentricity = 0.0,
		 const char*	name = 0,
		 const char*	comment = 0);
    IlvEllipsoid(const IlvEllipsoid&);
    IlvEllipsoid(IlvInputFile &file);
    ~IlvEllipsoid();

    IlvMapsError getError() const {return _error;}

    IlBoolean isBad() const {return _error != IlvMaps::NoError();}

    // Ellipsoid properties
    IlBoolean isSphere() const {return (_es == 0) ? IlTrue : IlFalse;}

    IlDouble getA() const  {return _a;}

    IlDouble getB() const  {return _b;}

    IlDouble getES() const {return _es;}

    const char *getName() const {return _name;}

    const char *getComment() const {return _comment;}

    IlBoolean equivalent(const IlvEllipsoid *e) const;

    // Equivalent spheres
    IlvEllipsoid* createSphereOfSameArea() const;

    IlvEllipsoid* createSphereOfSameVolume() const;

    IlvEllipsoid* createASphere() const;

    IlvEllipsoid* createASphere(IlDouble phi) const;

    IlvEllipsoid* createGSphere() const;

    IlvEllipsoid* createGSphere(IlDouble phi) const;

    IlvEllipsoid* createHSphere() const;

    // utilities
    static IlDouble ESFromPolarRadius(IlDouble a, IlDouble b)
    {return 1. - (b * b)/(a * a);}

    static IlDouble ESFromFlattening(IlDouble f) {return f * (2. - f);}

    // IO functions
    void save(IlvOutputFile& outputFile) const;

    static IlvEllipsoid* Load(IlvInputFile&, IlvMapsError* = 0);

    // miscllaneous
    IlvEllipsoid* copy() const {return new IlvEllipsoid(*this);}

    // Registered Ellipsoids management.
    static const IlvEllipsoid* GetRegisteredEllipsoid(const char* name);

    static const IlvEllipsoid* const*
	GetRegisteredEllipsoids(IlUInt& count);

    // Frequently used ellipsoids
    static const IlvEllipsoid* SPHERE();

    static const IlvEllipsoid* SGS85();

    static const IlvEllipsoid* CPM();

    static const IlvEllipsoid* WGS60();

    static const IlvEllipsoid* WGS66();

    static const IlvEllipsoid* WGS72();

    static const IlvEllipsoid* WGS84();

    // Common Ellipsoid errors
    static IlvMapsError ESGreaterThanOne();

    static IlvMapsError ESLessThanZero();

    static IlvMapsError ALessThanZero();

    // For internal use in the library
    // Not documented
    IlDouble getCMeridinalDistance(IlDouble phi,
				    IlDouble sphi,
				    IlDouble cphi) const;
    IlDouble phiFromCMeridinalDistance(IlDouble d,
					IlvMapsError& errorCode) const;
    IlDouble inverseAuthalicLatitude(IlDouble beta) const;
    static IlvEllipsoid* GetEllipsoid(IlStringHashTable*  proj4Values,
				      IlvMapsError& status);
    IlDouble getE() const  {return _e; }
    IlDouble getRone_es() const {return _rone_es;}
    static IlvEllipsoid* Register(IlvEllipsoid* ellipsoid);
    IL_STDPREF ostream& printPROJ4Descriptor(IL_STDPREF ostream&) const;


private:
    void computeParameters();
    void initMeridinalDistancePolynome();
    void initAuthalicInversePolynome();
    void setError(IlvMapsError error) {_error = error;}
    static void Init();
    static void InitErrorMessages();
    static void InitPredefinedEllipsoids();
    static void Finalize();
    IlvMapsIcFriend(ellips, ILVMAPSEXPORTED);

private:
    IlDouble _a;   // semi major axis or radius if es==0
    IlDouble _b;   // semi minor axis or radius if es==0
    IlDouble _e;   // eccentricity
    IlDouble _es;  // eccentricity squared (stored for optim)
    IlDouble _rone_es; // 1 / _es
    char* _name;
    char* _comment;
    IlDouble* _mDP;
    IlDouble* _APA;
    IlvMapsError _error;
};

#endif /* __Ilv_Maps_Ellips_H */
