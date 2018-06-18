// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/adapter.h
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
// This file defines the Coordinate Adapter Class.
// This persistant class (it can be saved into an ivl file)
// defines a scaling operation to convert float coordinates
// to integer coordinates (The Manager coordinate system) while
// keeping an appropriate precision.
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Adapter_H
#define __Ilv_Maps_Adapter_H

#if !defined(__Ilv_Maps_Maps_H)
#  include <ilviews/maps/maps.h>
#endif
#if !defined(__Ilv_Maps_Projection_Project_H)
#  include <ilviews/maps/projection/project.h>
#endif

class ILVMAPSEXPORTED IlvMapAdapter
{
    public:
    IlvMapAdapter(const IlvProjection* projection,
		  IlDouble extension = 1.);
    IlvMapAdapter(IlDouble precision,
		  IlvCoordinate* center = 0,
		  IlBoolean invertY = IlTrue);
    IlvMapAdapter(const IlvCoordinate& ul,
		  const IlvCoordinate& lr,
		  IlDouble precision = 0);
    IlvMapAdapter(const IlvCoordinate& ul,
		  const IlvCoordinate& lr,
		  const IlvRect& destination);
    IlvMapAdapter(const IlvMapAdapter& source);
    IlvMapAdapter(IlvInputFile&);
    ~IlvMapAdapter();

    IlBoolean		isBad() const
	{ return _fail; }

    IlDouble		getPrecision() const
	{ return 1. / _scaleFactor; }
    IlDouble		getScaleFactor() const
	{ return _scaleFactor; }
    IlvCoordinate	getCenter() const { return _center; }
    inline void		fromViews(const IlvPoint& p, IlvCoordinate& c) const
	{
	    c.x(((IlDouble) p.x() / _scaleFactor) + _center.x());
	    c.y(((IlDouble) p.y() / _scaleFactor * _invertY) + _center.y());
	}
    IlvCoordinate	fromViews(const IlvPoint& point) const;
    IlDouble		fromViews(IlDouble distance) const
	{ return distance / _scaleFactor; }
    void		fromViews(const IlvRect& src,
				  IlvCoordinate& ul,
				  IlvCoordinate& lr) const;
    inline void		toViews(const IlvCoordinate& c, IlvPoint& p) const
	{
	    p.move((IlvPos)floor((c.x() - _center.x())
				 * _scaleFactor + 0.5),
		   (IlvPos)floor((c.y() - _center.y())
				 * _scaleFactor * _invertY + 0.5));
	}
    IlvPoint		toViews(const IlvCoordinate& coord) const;
    IlDouble		toViews(IlDouble distance) const
	{ return distance * _scaleFactor; }
    IlvRect		toViews(const IlvCoordinate& ul,
				const IlvCoordinate& lr) const;
    void		ensureVisible(IlvView* view,
				      const IlvCoordinate& point) const;
    void		ensureVisible(IlvView* view,
				      const IlvCoordinate& ul,
				      const IlvCoordinate& lr) const;
    void		fitTransformerToRect(IlvView* view,
					     const IlvCoordinate& ul,
					     const IlvCoordinate& lr,
					     IlBoolean redraw = IlTrue,
					     IlBoolean keepAspectRatio
							     = IlTrue) const;
    IlvMapAdapter*	copy() const;

    void		getMaxExtension(IlvCoordinate& ul,
					IlvCoordinate& lr) const;
    IlBoolean		isInRange(const IlvCoordinate& point) const;
    inline IlBoolean	isInvertingY() const
	{ return (_invertY == -1.); }

    void		save(IlvOutputFile& file) const;
    static
    IlvMapAdapter*	Load(IlvInputFile& file);
private:
    inline void		setInvertingY(IlBoolean invertY)
	{ _invertY = invertY ? -1. : 1.; }

    IlDouble		_scaleFactor;
    IlvCoordinate	_center;
    IlBoolean		_fail;
    IlDouble		_invertY;
};

#endif /* __Ilv_Maps_Adapter_H */
