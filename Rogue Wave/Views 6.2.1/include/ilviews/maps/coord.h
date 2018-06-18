// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/coord.h
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
// General Class
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Coord_H
#define __Ilv_Maps_Coord_H

#if !defined(__Ilv_Maps_Macros_H)
#  include <ilviews/maps/macros.h>
#endif

#if defined(IL_STD)
#  include <cmath>
#else  /* !IL_STD */
#  include <math.h>
#endif /* IL_STD */

class ILVMAPSEXPORTED IlvCoordinate
{

public:

    // documented methods
    IlvCoordinate(IlDouble x = 0.0, IlDouble y = 0.0)
    : _x(x),
      _y(y)
    {}

    inline IlDouble x() const { return _x; }
    inline void x(IlDouble x) { _x = x; }
    inline IlDouble y() const { return _y; }
    inline void y(IlDouble y) { _y = y; }
    inline void move(IlDouble x, IlDouble y) { _x = x; _y = y; }

    inline void translate(IlDouble dx, IlDouble dy) { _x += dx; _y += dy;}
    inline void translate(const IlvCoordinate& dc) { _x += dc._x; _y += dc._y;}

    inline int operator==(const IlvCoordinate& c) const
	{ return (_x == c._x) && (_y == c._y); }
    inline IlBoolean isCloseTo(const IlvCoordinate& other,
			       IlDouble tolerance = 0.0)
	{
	    return ((fabs(other._x - _x) <= tolerance) &&
		    (fabs(other._y - _y) <= tolerance));
	}
    inline IlvCoordinate& operator=(const IlvCoordinate& c)
	{ _x = c._x; _y = c._y; return *this; }


    // Undocumented
    inline int operator!=(const IlvCoordinate& c) const
	{ return (_x != c._x) || (_y != c._y); }
    inline void operator+=(const IlvCoordinate& c) { _x += c._x; _y += c._y; }
    inline void operator-=(const IlvCoordinate& c) { _x -= c._x; _y -= c._y; }

    IlDouble getX() const { return _x; }
    IlDouble getY() const { return _y; }
    void setX(IlDouble xx) { _x = xx; }
    void setY(IlDouble yy) { _y = yy; }
    void set(IlDouble x,  IlDouble y) { _x  =  x; _y  =  y; }
private:
    IlDouble _x;
    IlDouble _y;
};

#endif /* !__Ilv_Maps_Coord_H */
