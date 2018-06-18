// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/filters/noise.h
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
// Declaration of Perlin noise 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Filters_Noise_H
#define __Ilv_Bitmaps_Filters_Noise_H

#if !defined(__Ilv_Bitmap_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif

#if !defined(__Ilv_Bitmaps_Filters_Macros_H)
#include <ilviews/bitmaps/filters/macros.h>
#endif


class ILVFLTEXPORTED IlvPerlinNoise
{
public:
    IlvPerlinNoise(IlInt seed = 0);
    void		init(IlInt seed);
    inline void		noise2(IlFloat x, IlFloat y, IlFloat* result);

private:
    static IlInt	BM;
    static IlFloat	PerlinN;
    static IlInt	BSize;
    IlFloat		_gradient[2056];
    IlInt		_lattice[257];
};

static inline IlFloat 
Lerp(IlFloat t, IlFloat a, IlFloat b) 
{ 
    return (a + t * (b - a));
}

static inline IlFloat
SCurve(IlFloat t)
{
    return (t * t * ((IlFloat)3.0 - (IlFloat)2.0 * t));
}

inline void
IlvPerlinNoise::noise2(IlFloat x, IlFloat y, IlFloat* result) 
{
    int b0, b1;
    int i, j;
    IlFloat rx0, rx1, ry0, ry1, sx, sy;

    x += PerlinN;
    b0 = ((int)x) & BM;

    i = _lattice[b0];
    j = _lattice[b0 + 1];

    rx0 = x - (int)x;
    rx1 = rx0 - (float)1.0;
    sx  = SCurve(rx0);

    y += PerlinN;
    b0 = (int)y;

    // The gradient array already has the latticeSelector applied
    // to it, So we can avoid doing the last lookup.
    b1 = ((j + b0) & BM) << 3;
    b0 = ((i + b0) & BM) << 3;

    ry0 = y - (int)y;
    ry1 = ry0 - (float)1.0;
    sy = SCurve(ry0);

    result[3] = Lerp(sy, 
		     Lerp(sx, 
			  rx0 * _gradient[b0 + 6] + ry0 * _gradient[b0 + 7],
			  rx1 * _gradient[b1 + 6] + ry0 * _gradient[b1 + 7]),
		     Lerp(sx, 
			  rx0 * _gradient[b0 + 8 + 6] + ry1 * _gradient[b0 + 8 + 7],
			  rx1 * _gradient[b1 + 8 + 6] + ry1 * _gradient[b1 + 8 + 7]));
    result[2] = Lerp(sy, 
		     Lerp(sx, 
			  rx0 * _gradient[b0 + 4] + ry0 * _gradient[b0 + 5],
			  rx1 * _gradient[b1 + 4] + ry0 * _gradient[b1 + 5]),
		     Lerp(sx, 
			  rx0 * _gradient[b0 + 8 + 4] + ry1 * _gradient[b0 + 8 + 5],
			  rx1 * _gradient[b1 + 8 + 4] + ry1 * _gradient[b1 + 8 + 5]));
    result[1] = Lerp(sy, 
		     Lerp(sx, 
			  rx0 * _gradient[b0 + 2] + ry0 * _gradient[b0 + 3],
			  rx1 * _gradient[b1 + 2] + ry0 * _gradient[b1 + 3]),
		     Lerp(sx, 
			  rx0 * _gradient[b0 + 8 + 2] + ry1 * _gradient[b0 + 8 + 3],
			  rx1 * _gradient[b1 + 8 + 2] + ry1 * _gradient[b1 + 8 + 3]));
    result[0] = Lerp(sy, 
		     Lerp(sx, 
			  rx0 * _gradient[b0 + 0] + ry0 * _gradient[b0 + 1],
			  rx1 * _gradient[b1 + 0] + ry0 * _gradient[b1 + 1]),
		     Lerp(sx, 
			  rx0 * _gradient[b0 + 8 + 0] + ry1 * _gradient[b0 + 8 + 1],
			  rx1 * _gradient[b1 + 8 + 0] + ry1 * _gradient[b1 + 8 + 1]));
}

#endif /* __Ilv_Bitmaps_Filters_Noise_H */
