// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/unitconv.h
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
// Declaration of the IlvUnitConverter class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Unitconv_H
#define __Ilv_Maps_Unitconv_H

#if !defined(__Ilv_Maps_Macros_H)
#  include <ilviews/maps/macros.h>
#endif
#if !defined(__Ilv_Maps_Maps_H)
#  include <ilviews/maps/maps.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif

class ILVDSPEXPORTED IlvAlist;
class ILVDSPEXPORTED IlvInputFile;
class ILVDSPEXPORTED IlvOutputFile;
ILVMAPSMODULETERM(unitconv);

class ILVMAPSEXPORTED IlvUnitConverter
{
public:
    IlvUnitConverter(IlDouble toMeters,
		     const char* unit,
		     const char* description = 0);
    IlvUnitConverter(const IlvUnitConverter&);
    IlvUnitConverter(IlvInputFile&);
    ~IlvUnitConverter(void);

    inline IlDouble toMeters(IlDouble units) const
	{ return units * _toMeters; }
    inline IlDouble getToMeters() const
	{ return _toMeters; }
    inline IlDouble fromMeters(IlDouble meters) const
	{ return meters * _fromMeters; }
    inline const char* getUnit() const { return _unit; }

    inline const char* getDescription() const { return _description; }

    // IO functions
    void save(IlvOutputFile& file) const;
    static IlvUnitConverter* Load(IlvInputFile& file,
				  IlvMapsError* status = 0);

    // Misc
    inline IlvUnitConverter* copy() const
	{ return new IlvUnitConverter(*this); }

    // Error management
    inline IlvMapsError getError() const { return _error; }
    inline IlBoolean isBad() const
	{ return _error != IlvMaps::NoError(); }

    // Registered Unit converters management
    static const IlvUnitConverter* GetRegisteredConverter(const char* unit);

    static const IlvUnitConverter* const*
	GetRegisteredConverters(IlUInt& count);

    // Frequently used units
    static const IlvUnitConverter* METERS();
    static const IlvUnitConverter* FT();
    static const IlvUnitConverter* KILOMETERS();
    static const IlvUnitConverter* KMI();
    static const IlvUnitConverter* MI();


    // Not documented.
    static IlvUnitConverter* GetConverter(IlStringHashTable*,
					  IlvMapsError&);
    static IlvUnitConverter* Register(IlvUnitConverter*);

private:
    inline void setError(IlvMapsError error) { _error = error; }

    static void Init();
    static void Finalize();

private:
    IlDouble _fromMeters;
    IlDouble _toMeters;
    char* _unit;
    char* _description;
    static IlDouble GetToMeters(const char *string, IlvMapsError *outError);
    IlvMapsError _error;

    IlvMapsIcFriend(unitconv, ILVMAPSEXPORTED);
};

#endif /* !__Ilv_Maps_Unitconv_H */
