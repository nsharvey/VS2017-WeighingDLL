// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/colormap.h
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
// Declaration of colormap utilities in IlogViews
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Colormap_H
#define __Ilv_Bitmaps_Colormap_H


#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif

enum IlvRampMode {
  IlvLinearRamp = 0,
  IlvCCWRamp,
  IlvCWRamp
};

struct IlARGB
{
    IlARGB(IlUChar rr, IlUChar gg, IlUChar bb, IlUChar aa = 0) 
	: a(aa), r(rr), g(gg), b(bb) {} 
    IlARGB() : a(0), r(0), g(0), b(0) {}
    IlARGB(const IlARGB& argb) : a(argb.a), r(argb.r), g(argb.g), b(argb.b) {}

    IlUChar a;
    IlUChar r;
    IlUChar g;
    IlUChar b;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvColorMap
{
public:
    IlvColorMap(IlUInt numcols = 256);
    virtual ~IlvColorMap();
    IlBoolean		setEntry(IlUInt index, 
				 IlUChar r,
				 IlUChar g,
				 IlUChar b,
				 IlUChar a = 255);
    IlBoolean		getEntry(IlUInt index,
				 IlUChar& r,
				 IlUChar& g,
				 IlUChar& b) const;
    IlBoolean		getEntry(IlUInt index, 
				 IlUChar& r,
				 IlUChar& g,
				 IlUChar& b,
				 IlUChar& a) const;
    const IlUChar*	getARGBInternal(IlUInt index) const;

    inline IlUChar	getA(IlUInt index) const
			{
			    if (index >= _numcols) 
				return 0;
			    else
				return _argb[index * 4];
			}
   inline IlUChar	getR(IlUInt index) const
			{
			    if (index >= _numcols) 
				return 0;
			    else
				return _argb[index * 4 + 1];
			}
    inline IlUChar	getG(IlUInt index) const
			{
			    if (index >= _numcols) 
				return 0;
			    else
				return _argb[index * 4 + 2];
			}

    inline IlUChar	getB(IlUInt index) const
			{
			    if (index >= _numcols) 
				return 0;
			    else
				return _argb[index * 4 + 3];
			}
    inline IlUInt	getColorNum() const { return _numcols; }

    void		grow(IlUInt value);

    void		lock();
    void		unLock();
    inline IlUInt	getRefCount() const { return _refcount; }

    void		ramp(IlUInt from,
			     IlUInt to,
			     IlARGB color1,
			     IlARGB color2,
			     IlvRampMode mode = IlvLinearRamp);
    IlvColorMap*	copy();

protected:
    IlUInt		_numcols;
    IlUChar*		_argb;
    IlUInt		_refcount;
};

#endif /* __Ilv_Bitmaps_Colormap_H */
