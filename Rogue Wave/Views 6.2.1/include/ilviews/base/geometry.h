// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/geometry.h
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
// Declaration of IlogViews's basic geometric types
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Geometry_H
#define __Ilv_Base_Geometry_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

// --------------------------------------------------------------------------
//    IlvPoint
// --------------------------------------------------------------------------
class IlvDeltaPoint;
class ILVDSPEXPORTED IlvPoint
{
public:
    IlvPoint(IlvPos x = 0, IlvPos y = 0)
	: _x(x),
	_y(y)
      {}
#if defined(_MSC_VER) && defined(WIN16)
    ~IlvPoint() {} // Needed for the MSVC compiler bug on array.
#endif /* _MSC_VER && WIN16 */

    inline operator	int()  const { return !isNull(); }
    inline int operator	!() const { return isNull(); }
    inline
    IlvPoint& operator	=(const IlvPoint& p)
			{
			    _x = p._x;
			    _y = p._y;
			    return *this;
			}
    inline int operator	==(const IlvPoint& p) const
			{
			    return (_x == p._x) && (_y == p._y);
			}
    inline int operator	!=(const IlvPoint& p) const
			{
			    return (_x != p._x) || (_y != p._y);
			}
    inline void operator+=(const IlvPoint& p) { _x += p._x; _y += p._y; }
    inline void operator-=(const IlvPoint& p) { _x -= p._x; _y -= p._y; }
    inline void operator+=(const IlvDeltaPoint& p);
    inline void operator-=(const IlvDeltaPoint& p);

    inline IlvPos	x() const { return _x; }
    inline IlvPos	getX() const { return _x; }
    inline void		x(IlvPos newX) { _x = newX; }
    inline void		setX(IlvPos newX) { _x = newX; }
    inline IlvPos	y() const { return _y; }
    inline IlvPos	getY() const { return _y; }
    inline void		y(IlvPos newY) { _y = newY; }
    inline void		setY(IlvPos yy) { _y = yy; }
    inline void		set(IlvPos x,  IlvPos y) { _x  =  x; _y  =  y; }
    inline void		move(IlvPos x, IlvPos y) { _x  =  x; _y  =  y; }
    inline void		translate(IlvPos dx, IlvPos dy) { _x += dx; _y += dy; }
    inline void		translate(const IlvPoint& delta)
			{
			    _x += delta.x();
			    _y += delta.y();
			}
    inline IlBoolean	isNull() const
			{
			    return (!_x && !_y) ? IlTrue : IlFalse;
			}

    IlvPos		_x;
    IlvPos		_y;
};

// --------------------------------------------------------------------------
//    IlvDeltaPoint
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvDeltaPoint
{
public:
    IlvDeltaPoint(IlvDeltaPos x = 0, IlvDeltaPos y = 0) : _x(x), _y(y) {}
#if defined(_MSC_VER) && defined(WIN16)
    ~IlvDeltaPoint() {} // Needed for the MSVC compiler bug on array.
#endif /* _MSC_VER && WIN16 */

    inline operator	int()  const { return !isNull(); }
    inline int operator	!() const { return isNull(); }
    inline
    IlvDeltaPoint& operator=(const IlvDeltaPoint& p)
			{
			    _x = p._x; _y = p._y;
			    return *this;
			}
    inline int operator	==(const IlvDeltaPoint& p) const
			{
			    return (_x == p._x) && (_y == p._y);
			}
    inline int operator	!=(const IlvDeltaPoint& p) const
			{
			    return (_x != p._x) || (_y != p._y);
			}
    inline void operator+=(const IlvPoint& p)
			{
			    _x += (IlvDeltaPos)p.x();
			    _y += (IlvDeltaPos)p.y();
			}
    inline void operator-=(const IlvPoint& p)
			{
			    _x -= (IlvDeltaPos)p.x();
			    _y -= (IlvDeltaPos)p.y();
			}
    inline void operator+=(const IlvDeltaPoint& p) { _x += p._x; _y += p._y; }
    inline void operator-=(const IlvDeltaPoint& p) { _x -= p._x; _y -= p._y; }

    inline IlvDeltaPos	getX() const { return _x; }
    inline IlvDeltaPos	x() const { return _x; }
    inline IlvDeltaPos	getY() const { return _x; }
    inline IlvDeltaPos	y() const { return _y; }
    inline void		setX(IlvDeltaPos xx) { _x = xx; }
    inline void		x(IlvDeltaPos xx)    { _x = xx; }
    inline void		setY(IlvDeltaPos yy) { _y = yy; }
    inline void		y(IlvDeltaPos yy)    { _y = yy; }
    inline void		set(IlvDeltaPos x, IlvDeltaPos y)
			{
			    _x =  x;
			    _y  = y;
			}
    inline void		move(IlvDeltaPos x, IlvDeltaPos y)
			{
			    _x =  x;
			    _y  = y;
			}
    inline void		translate(IlvDeltaPos x, IlvDeltaPos y)
			{
			    _x += x;
			    _y += y;
			}
    inline IlBoolean	isNull() const
			{
			    return (!_x && !_y) ? IlTrue : IlFalse;
			}

    IlvDeltaPos		_x;
    IlvDeltaPos		_y;
};

// --------------------------------------------------------------------------
inline void
IlvPoint::operator+=(const IlvDeltaPoint& p)
{
    _x += p.x();
    _y += p.y();
}

inline void
IlvPoint::operator-=(const IlvDeltaPoint& p)
{
    _x -= p.x();
    _y -= p.y();
}

// --------------------------------------------------------------------------
//    IlvFloatPoint
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvFloatPoint
{
public:
    IlvFloatPoint(IlFloat x = (IlFloat)0,
		  IlFloat y = (IlFloat)0)
	: _x(x),
	  _y(y)
    {}
#if defined(_MSC_VER) && defined(WIN16)
    ~IlvFloatPoint() {} // Needed for the MSVC compiler bug on array.
#endif /* _MSC_VER && WIN16 */

    inline operator	int()  const { return !isNull(); }
    inline int operator	!() const { return isNull(); }
    inline
    IlvFloatPoint& operator=(const IlvFloatPoint& p)
			{
			    _x = p._x;
			    _y = p._y;
			    return *this;
			}
    inline int operator	==(const IlvFloatPoint& p) const
			{
			    return (_x == p._x) && (_y == p._y);
			}
    inline int operator	!=(const IlvFloatPoint& p) const
			{
			    return (_x != p._x) || (_y != p._y);
			}

    inline IlFloat	getX() const { return _x; }
    inline IlFloat	x() const { return _x; }
    inline IlFloat	getY() const { return _y; }
    inline IlFloat	y() const { return _y; }
    inline void		setX(IlFloat newX) { _x = newX; }
    inline void		x(IlFloat newX)    { _x = newX; }
    inline void		setY(IlFloat newY) { _y = newY; }
    inline void		y(IlFloat newY)    { _y = newY; }
    inline void		set(IlFloat newX, IlFloat newY)
			{
			    _x  =  newX;
			    _y  =  newY;
			}
    inline void		move(IlFloat x, IlFloat y)
			{
			    _x  =  x;
			    _y  =  y;
			}
    inline void		translate(IlFloat dx, IlFloat dy)
			{
			    _x += dx;
			    _y += dy;
			}
    inline IlBoolean	isNull() const
			{
			    return (!_x && !_y) ? IlTrue : IlFalse;
			}

    IlFloat		_x;
    IlFloat		_y;
};

// --------------------------------------------------------------------------
//    IlvDoublePoint
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvDoublePoint
{
public:
    IlvDoublePoint(IlDouble x = (IlDouble)0,
		   IlDouble y = (IlDouble)0)
	: _x(x),
	  _y(y)
    {}
#if defined(_MSC_VER) && defined(WIN16)
    ~IlvDoublePoint() {} // Needed for the MSVC compiler bug on array.
#endif /* _MSC_VER && WIN16 */

    inline operator	int()  const { return !isNull(); }
    inline int operator	!() const { return isNull(); }
    inline
    IlvDoublePoint& operator=(const IlvDoublePoint& p)
			{
			    _x = p._x;
			    _y = p._y;
			    return *this;
			}
    inline int operator	==(const IlvDoublePoint& p) const
			{
			    return (_x == p._x) && (_y == p._y);
			}
    inline int operator	!=(const IlvDoublePoint& p) const
			{
			    return (_x != p._x) || (_y != p._y);
			}

    inline IlDouble	getX() const { return _x; }
    inline IlDouble	x()    const { return _x; }
    inline IlDouble	getY() const { return _y; }
    inline IlDouble	y()    const { return _y; }
    inline void		setX(IlDouble newX) { _x = newX; }
    inline void		x(IlDouble newX)    { _x = newX; }
    inline void		setY(IlDouble newY) { _y = newY; }
    inline void		y(IlDouble newY)    { _y = newY; }
    inline void		set(IlDouble newX, IlDouble newY)
			{
			    _x = newX;
			    _y = newY;
			}
    inline void		move(IlDouble newX, IlDouble newY)
			{
			    _x = newX;
			    _y = newY;
			}
    inline void		translate(IlDouble dx, IlDouble dy)
			{
			    _x += dx;
			    _y += dy;
			}
    inline IlBoolean	isNull() const
			{
			    return (!_x && !_y) ? IlTrue : IlFalse;
			}

    IlDouble		_x;
    IlDouble		_y;
};

// --------------------------------------------------------------------------
//    IlvRect
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvRect
{
public:
    IlvRect(IlvPos x = 0,
	    IlvPos y = 0,
	    IlvDim w = 0,
	    IlvDim h = 0)
	: _orig(x, y),
	  _w(w),
	  _h(h)
    {}
#if defined(_MSC_VER) && defined(WIN16)
    ~IlvRect() {} // Needed for the MSVC compiler bug on array.
#endif /* _MSC_VER && WIN16 */

    inline operator	int() const { return !isEmpty(); }
    inline
    IlBoolean operator	!() const { return isEmpty(); }
    inline
    IlvRect& operator	=(const IlvRect& r)
			{
			    _orig = r._orig;
			    _w = r._w;
			    _h = r._h;
			    return *this;
			}
    inline int operator	==(const IlvRect& r) const
			{
			    return (_orig == r._orig)
				&& (_w == r._w)
				&& (_h == r._h);
			}
    inline int operator	!=(const IlvRect& r) const
			{
			    return (_orig != r._orig)
				|| (_w != r._w)
				|| (_h != r._h);
			}
    inline
    IlvRect& operator	+=(const IlvRect&  r) { return add(r); }
    inline
    IlvRect& operator	+=(const IlvPoint& p) { return add(p); }

    inline IlvPos	getX() const { return _orig.x(); }
    inline IlvPos	x()    const { return _orig.x(); }
    inline void		setX(IlvPos newX) { _orig.x(newX); }
    inline void		x(IlvPos newX)    { _orig.x(newX); }
    inline IlvPos	getY() const { return _orig.y(); }
    inline IlvPos	y()    const { return _orig.y(); }
    inline void		setY(IlvPos newY) { _orig.y(newY); }
    inline void		y(IlvPos newY)    { _orig.y(newY); }
    inline IlvDim	getW() const { return _w; }
    inline IlvDim	w()    const { return _w; }
    inline void		setW(IlvDim newW) { _w = newW; }
    inline void		w(IlvDim newW)    { _w = newW; }
    inline IlvDim	getH() const { return _h; }
    inline IlvDim	h()    const { return _h; }
    inline void		setH(IlvDim newH) { _h = newH; }
    inline void		h(IlvDim newH)    { _h = newH; }
    inline void		set(IlvPos x, IlvPos y, IlvDim w, IlvDim h)
			{
			    _orig.move(x, y);
			    _w = w;
			    _h = h;
			}
    inline IlvPos	left() const { return _orig.x(); }
    inline IlvPos	top() const { return _orig.y(); }
    inline IlvPos	right() const { return _orig.x() + _w; }
    inline IlvPos	bottom() const { return _orig.y() + _h; }
    inline IlvPos	centerx() const { return _orig.x() + (IlvPos)(_w>>1); }
    inline IlvPos	centery() const { return _orig.y() + (IlvPos)(_h>>1); }
    inline
    const IlvPoint&	orig() const { return _orig; }
    inline
    const IlvPoint&	upperLeft() const  { return orig(); }
    inline IlvPoint	lowerRight() const
			{
			    return IlvPoint(right(), bottom());
			}
    inline IlvPoint	lowerLeft() const
			{
			    return IlvPoint(left(), bottom());
			}
    inline IlvPoint	upperRight() const
			{
			    return IlvPoint(right(), top());
			}
    inline IlvPoint	center() const
			{
			    return IlvPoint(centerx(), centery());
			}
    inline void		move(const IlvPoint& orig) { _orig = orig; }
    inline void		move(IlvPos x, IlvPos y) { _orig.move(x, y); }
    inline void		translate(const IlvPoint& dp)
			{
			    _orig.translate(dp.x(), dp.y());
			}
    inline void		translate(IlvPos dx, IlvPos dy)
			{
			    _orig.translate(dx, dy);
			}
    inline void		size(IlvDim& w, IlvDim& h) const { w = _w; h = _h; }
    inline void		resize(IlvDim w, IlvDim h) { _w = w; _h = h; }
    inline void		grow(IlvPos dw, IlvPos dh)
			{
			    _w = (IlvDim)IlMax((IlvPos)_w + dw, (IlvPos)0);
			    _h = (IlvDim)IlMax((IlvPos)_h + dh, (IlvPos)0);
			}
    inline void		scale(IlFloat sw, IlFloat sh)
			{
			    _w = (IlvDim)(_w * sw);
			    _h = (IlvDim)(_h * sh);
			}
    inline void		expand(IlvPos delta)
			{
			    _orig.translate(-delta, -delta);
			    _w = (IlvDim)IlMax((IlvPos)_w+2*delta, (IlvPos)0);
			    _h = (IlvDim)IlMax((IlvPos)_h+2*delta, (IlvPos)0);
			}
    inline void		expand(IlvPos dx, IlvPos dy)
			{
			    _orig.translate(-dx, -dy);
			    _w = (IlvDim)IlMax((IlvPos)_w + 2*dx, (IlvPos)0);
			    _h = (IlvDim)IlMax((IlvPos)_h + 2*dy, (IlvPos)0);
			}
    inline void		moveResize(IlvPos x, IlvPos y, IlvDim w, IlvDim h)
			{
			    _orig.move(x, y);
			    _w = w;
			    _h = h;
			}
    IlBoolean		isEmpty() const
			{
			    return (!_w || !_h) ? IlTrue : IlFalse;
			}
    IlBoolean		isNull() const
			{
			    return (!_w && !_h && !orig()) ? IlTrue : IlFalse;
			}

    inline IlBoolean	contains(const IlvPoint& p) const
			{
			    return ((p.x() >= left()) && (p.x() <= right()) &&
				    (p.y() >= top())  && (p.y() <= bottom()))
				? IlTrue
				: IlFalse;
			}
    inline IlBoolean	contains(const IlvRect& rect) const
			{
			    return ((rect.left()   >= left())   &&
				    (rect.right()  <= right())  &&
				    (rect.top()    >= top())    &&
				    (rect.bottom() <= bottom()))
				? IlTrue
				: IlFalse;
			}
    inline IlBoolean	inside(const IlvRect& rect) const
			{
			    return rect.contains(*this);
			}
    inline IlBoolean	intersects(const IlvRect& rect) const
			{
			    return ((left()   < rect.right())  &&
				    (right()  > rect.left())   &&
				    (top()    < rect.bottom()) &&
				    (bottom() > rect.top()))
				? IlTrue
				: IlFalse;
			}
    IlvRect&		intersection(const IlvRect&);
    IlvRect&		add(const IlvRect& rect);
    IlvRect&		add(const IlvPoint& point);

    IlvPoint		_orig;
    IlvDim		_w, _h;
};

// --------------------------------------------------------------------------
//    IlvFloatRect
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvFloatRect
{
public:
    IlvFloatRect(IlFloat x1 = (IlFloat)0,
		 IlFloat y1 = (IlFloat)0,
		 IlFloat x2 = (IlFloat)0,
		 IlFloat y2 = (IlFloat)0)
	: _x1(x1),
	  _y1(y1),
	  _x2(x2),
	  _y2(y2)
    {}
#if defined(_MSC_VER) && defined(WIN16)
    ~IlvFloatRect() {} // Needed for the MSVC compiler bug on array.
#endif /* _MSC_VER && WIN16 */

    inline IlFloat	left() const { return _x1; }
    inline IlFloat	top() const { return _y1; }
    inline IlFloat	right() const { return _x2; }
    inline IlFloat	bottom() const { return _y2; }
    inline void		left(IlFloat v) { _x1 = v; }
    inline void		top(IlFloat v) { _y1 = v; }
    inline void		right(IlFloat v) { _x2 = v; }
    inline void		bottom(IlFloat v) { _y2 = v; }

    IlFloat		_x1;
    IlFloat		_y1;
    IlFloat		_x2;
    IlFloat		_y2;
};

#endif /* !__Ilv_Base_Geometry_H */
