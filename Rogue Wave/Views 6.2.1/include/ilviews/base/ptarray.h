// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/ptarray.h
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
// Declaration of the IlvPointArray class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Ptarray_H
#define __Ilv_Base_Ptarray_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif

#if !defined(__Ilv_Util_Util_H)
#include <ilviews/util/util.h>
#endif

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvPointArray
{
public:
    IlvPointArray()
    : _npoints(0),
      _points(0),
      _dynPoints(0),
      _bbox(),
      _bboxReady(IlFalse),
      _owner(IlTrue) {}
    IlvPointArray(IlUInt count, const IlvPoint* points,
		  IlBoolean copy = IlTrue,
		  IlBoolean owner = IlTrue)
    : _npoints(0),
      _points(0),
      _dynPoints(0),
      _bbox(),
      _bboxReady(IlFalse),
      _owner(owner) { setPoints(count, points, copy); }
    IlvPointArray(const IlvPointArray& source);
    ~IlvPointArray();

    // ____________________________________________________________
    IlBoolean		isOwner() const { return _owner; }
    void		setOwner(IlBoolean b) { _owner = b; }

    IlUInt		npoints() const 
    { return _points ? _npoints : (_dynPoints ? _dynPoints->getLength() : 0); }
    const IlvPoint*	points() const 
    { return _points ? _points : (_dynPoints ? _dynPoints->getArray() : 0); }
    const IlvPoint*	points(IlUInt index) const
	{ return points() + index ;  }

    const IlvPoint*	getPoints(IlUInt& count) const
    {	
	if (_points) { 
	    count=_npoints; return _points; 
	} else if (_dynPoints) { 
	    count = _dynPoints->getLength(); return _dynPoints->getArray();
	} else {
	    count = 0;
	    return 0;
	}
    }

    const IlvRect&	bbox() const;
    void		boundingBox(IlvRect& box,
				    const IlvTransformer* t = 0) const;
    void		setPoints(IlUInt count, const IlvPoint* points,
				  IlBoolean copy = IlTrue);
    void		applyTransform(const IlvTransformer* t);
    IlBoolean		outlineContains(const IlvPoint& p) const;
    IlUInt		nbHorizontalIntersect(const IlvPoint& p,
					      IlInt* rtol) const;

    void		movePoint(const IlvPoint& pos, IlUInt which);
    void		addPoints(IlUInt count, const IlvPoint* points,
				  IlUInt where);
    IlBoolean		removePoints(IlUInt start, IlUInt count);
    IlInt		area(const IlvTransformer* t = 0) const;
    IlInt		orientation() const;

private:
    IlUInt     _npoints;
    IlvPoint*  _points;
    IlvArrayOfPoints* _dynPoints;
    IlvRect    _bbox;
    IlBoolean  _bboxReady;
    IlBoolean  _owner;

    // used to optimize addPoint and addPoints methods
    void extendBBox(IlUInt, const IlvPoint*);
    void beforeWrite();
};

#endif /* !__Ilv_Base_Ptarray_H */
