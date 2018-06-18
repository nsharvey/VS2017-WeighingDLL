// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/maps.h
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
// General definitions for the Rogue Wave Views Maps package.
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_H
#define __Ilv_Maps_H

#include <ilviews/maps/macros.h>
#include <ilviews/base/array.h>

// generator for the list of all error codes
#define IlvMapsListErrors(DECL)					\
DECL(NoError)							\
DECL(Insufficient_memory)					\
DECL(ToleranceCondition__non_convergent_inverse_phi2)		\
DECL(IllegalArgument)						\
DECL(IndexError)						\
DECL(ClassError)						\
DECL(BadProjectionParameter_conic_lat_1_equals_minus_lat_2)	\
DECL(BadProjectionParameter_Azimuthal__limiting__form)		\
DECL(ProjectionAlreadyRegistered)				\
DECL(UnitConverterAlreadyRegistered)				\
DECL(ProjectionFactory_no_projection_specified)			\
DECL(ProjectionFactory_projection_does_not_exist)		\
DECL(ProjectionFactory_parameter_value_without_name)		\
DECL(Projection_cant_instantiate_conic_projection)		\
DECL(Number_format_error)					\
DECL(UnitConverter_unknown_unit_conversion_id)			\
DECL(UnitConverter_zero_divisor)				\
DECL(Object_class_doesnt_exist)					\
DECL(NoMapInfo)							\
DECL(UnknownGeometry)						\
DECL(NoManager)							\
DECL(NoLicenseError)						\
DECL(FormatError)						\
DECL(UninitializedClassInfoError)				\
DECL(BitmapError)						\
DECL(IOError)							\
DECL(NoSuchFile)

#define IlvMapsDeclareErrorVar(NAME)			\
    protected:						\
	static IlvMapsError _##NAME;			\
    public:						\
	static IlvMapsError NAME() { return _##NAME; }

class ILVDSPEXPORTED IlvDisplay;
class ILVDSPEXPORTED IlvBitmap;
class ILVDSPEXPORTED IlvArray;

typedef IlUShort IlvMapsError;

ILVMAPSMODULETERM(maps);

class ILVMAPSEXPORTED IlvMaps
{

public:
    // Error message management
    static const char*	GetErrorMessageId(IlvMapsError error);
    static const char*	GetErrorMessage(IlvMapsError error,
				       IlvDisplay* display);
    static IlvMapsError CreateError(const char* messageId);

    // Conversion utilites
    inline static IlDouble	DegreeToRadian(IlDouble degree)
	{ return degree * Pi() / 180.; }
    inline static IlDouble	RadianToDegree(IlDouble radian)
	{ return radian * 180. / Pi(); }
    static char*	DegreeToDMS(char* buffer,
				    IlDouble degree,
				    IlBoolean lat);
    inline static char*	RadianToDMS(char* buffer,
				    IlDouble radian,
				    IlBoolean lat)
	{ return DegreeToDMS(buffer, RadianToDegree(radian), lat); }
    static IlvMapsError	DMSToRadian(const char* dms, IlDouble& outValue);

    // Constants
    inline static IlDouble	Pi()       { return _Pi;       }
    inline static IlDouble	HalfPi()   { return _HalfPi;   }
    inline static IlDouble	FourthPi() { return _FourthPi; }
    inline static IlDouble	EPS()      { return _EPS;      }
    static IlvBitmap*	CreateBitmap(IlvDisplay* display,
				     IlvDim width,
				     IlvDim height,
				     IlUShort* data,
				     IlUShort nbColors,
				     IlUChar* redColorMap,
				     IlUChar* greenColorMap,
				     IlUChar* blueColorMap);
    static IlvBitmap*	GetBitmap(IlvDisplay*,
				  const char*,
				  IlvMapsError&);

    // Undocumented maths functions
    static IlDouble	Hypot(IlDouble, IlDouble);
    static IlDouble	Ms(IlDouble, IlDouble, IlDouble);
    static IlDouble	Qs(IlDouble, IlDouble, IlDouble);
    static IlDouble	Ts(IlDouble, IlDouble, IlDouble);
    static IlDouble	phi2(IlDouble, IlDouble, IlvMapsError);
    static IlDouble	aasin(IlDouble, IlvMapsError);

    IlvMapsListErrors(IlvMapsDeclareErrorVar)
    IlvMapsIcFriend(maps, ILVMAPSEXPORTED);

    static void		InitErrors();
    static IlDouble	GetDoubleValue(const char *string);

private:
    // One cannot create an instance of this class
    IlvMaps() {}

    const static IlDouble	_Pi;
    const static IlDouble	_HalfPi;
    const static IlDouble	_FourthPi;
    const static IlDouble	_EPS;
    static IlArray*		_errors;
};

#endif /* __Ilv_Maps_H */
