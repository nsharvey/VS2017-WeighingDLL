// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/region.h
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
// Declaration of the IlvRegion class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Region_H
#define __Ilv_Base_Region_H

#if !defined(__Ilv_Base_Geometry_H)
#include <ilviews/base/geometry.h>
#endif
#if !defined(__Il_Pool_H)
#include <ilog/pool.h>
#endif

class IlvTransformer;

#define REGIONMAXRECTS 8

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvRegion
{
public:
    IlvRegion();
    IlvRegion(const IlvRect& rect);
    IlvRegion(const IlvRegion&);
    ~IlvRegion();

    inline
    const IlvRect&	boundingBox() const { return _bbox; }
    inline IlUShort	getCardinal() const { return _currentCount; }
    inline
    const IlvRect&	getRect(IlUShort idx) const { return _rects[idx]; }
    void		add(const IlvRect& rect);
    void		add(const IlvRegion& region);
    void		subtract(const IlvRect& rect);
    void		compact();
    inline IlBoolean	isCompacted() const { return _isCompacted; }
    inline void		substract(const IlvRect& r) { subtract(r); }
    void		computeDifference(const IlvRect& rect1,
					  const IlvRect& rect2);
    void		empty();
    IlBoolean		contains(const IlvPoint& point) const;
    IlBoolean		contains(const IlvRect& rect) const;
    IlBoolean		intersects(const IlvRect& rect) const;
    IlBoolean		intersects(const IlvRegion& region) const;
    void		intersection(const IlvRect& rect);
    void		intersection(const IlvRegion& region);
    void		apply(const IlvTransformer* t);
    void		inverse(const IlvTransformer* t);
    IlvRegion*		copy() const;
    IlvRegion& operator	=(const IlvRegion& region);
    void		translate(IlvPos x, IlvPos y);
    void		grow(IlvPos dw, IlvPos dh);
    void		setFull()
			{
			    empty();
			    _isFull = IlTrue;
			    _bbox = _FullRect;
			}
    inline IlBoolean	isFull() const { return _isFull; }
    IlBoolean		isEmpty() const
			{
			    return (_isFull || _currentCount)
				? IlFalse
				: IlTrue;
			}
    IlBoolean operator	==(const IlvRegion&) const;
    IlBoolean operator	!=(const IlvRegion& region) const
			{
			    return (*this == region) ? IlFalse : IlTrue;
			}
protected:
    void		grow();
    void		iAdd(const IlvRect&);
    void		iAdd(const IlvRegion&);

    IlvRect		_bbox;
    IlUShort		_currentCount;
    IlUShort		_maxCount;
    IlMemoryPoolBlock*	_block;
    IlvRect*		_rects;
    IlBoolean		_isFull;
    IlBoolean		_isCompacted;
    IlvRect		_staticRects[REGIONMAXRECTS];
    static IlvRect	_FullRect;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvRegionUpdater
{
public:
    virtual ~IlvRegionUpdater();

    virtual IlBoolean	update(IlvRegion& region,
			       const IlvRect& clip,
			       const IlvTransformer* t = 0) const = 0;
protected:
    IlvRegionUpdater() {}
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvRegionOptimizer
{
public:
    IlvRegionOptimizer() {}
    virtual ~IlvRegionOptimizer();

    virtual IlBoolean	optimize(IlvRegion&	region,
				 const IlvRect&	rect) const;
    virtual IlBoolean	finalize(IlvRegion& region) const;
};

#endif /* !__Ilv_Base_Region_H */
