// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/turbulence.h
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
// Declaration of turbulence filter 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Turbulence_H
#define __Ilv_Bitmaps_Filters_Turbulence_H

#if !defined(__Ilv_Bitmap_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif
#if !defined(__Ilv_Bitmap_Filters_Noise_H)
#include <ilviews/bitmaps/filters/noise.h>
#endif
#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class ILVFLTEXPORTED IlvTurbulenceFilter : public IlvBitmapFilter
{
public:
    enum NoiseMode {
	Fractal,
	Turbulence
    };
    IlvTurbulenceFilter(IlFloat baseFrequencyX = 0.05, 
			IlFloat baseFrequencyY = 0.05, 
			IlUInt numOctaves = 1, 
			IlFloat seed = 0.0,
			NoiseMode = Turbulence,
			IlBoolean stitch = IlFalse);
    inline void		setBaseFrequencyX(IlFloat frequency)
			{
			    _baseFrequencyX = frequency;
			}
    inline void		setBaseFrequencyY(IlFloat frequency)
			{
			    _baseFrequencyY = frequency;
			}
    inline void		setNumOctaves(IlUInt octaves)
			{
			    _numOctaves = octaves;
			}
    inline void		setSeed(IlFloat seed)
			{
			    _seed = seed;
			    _noiseGen.init((IlInt)seed);
			}
    inline void		setNoiseMode(NoiseMode mode) { _noisemode = mode; }
    inline void		setStitch(IlBoolean stitch) { _stitch = stitch; }
    inline IlFloat	getBaseFrequencyX() const { return _baseFrequencyX; }
    inline IlFloat	getBaseFrequencyY() const { return _baseFrequencyY; }
    inline IlUInt	getNumOctaves() const { return _numOctaves; }
    inline IlFloat	getSeed() const { return _seed; }
    inline NoiseMode	getNoiseMode() const { return _noisemode; }
    inline IlBoolean	getStitch() const { return _stitch; }
    IlvBitmapData*	apply(IlUInt count = 0, 
			      const IlvBitmapData** datas = 0);

    static IlSymbol*	_baseFrequencyXValue;
    static IlSymbol*	_baseFrequencyYValue;
    static IlSymbol*	_numOctavesValue;
    static IlSymbol*	_seedValue;
    static IlSymbol*	_stitchValue;
    static IlSymbol*	_noiseModeValue;

    IlvDeclareClassInfo();
    DeclareValueAccessors();

protected:
    IlFloat		_baseFrequencyX;
    IlFloat		_baseFrequencyY;
    IlUInt		_numOctaves;
    IlFloat		_seed;
    IlBoolean		_stitch;
    NoiseMode		_noisemode;
    IlvPerlinNoise	_noiseGen;
};

ILVFLTMODULETERM(bitmaps_filters_turbulence);

#endif /* __Ilv_Bitmaps_Filters_Turbulence_H */
