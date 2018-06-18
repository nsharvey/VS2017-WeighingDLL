// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/polypts.h
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
// Declaration of the IlvPolyPoints class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Polypts_H
#define __Ilv_Graphics_Polypts_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif

// --------------------------------------------------------------------------
extern ILVVWSEXPORTEDVAR(IlvValueTypeClass*) IlvValuePointArrayType;

class ILVVWSEXPORTED IlvValuePointArrayTypeClass : public IlvValueTypeClass
{
public:
    IlvValuePointArrayTypeClass();

    void		copy(IlvValue&, const IlvValue&) const;
    virtual const char*	toString(const IlvValue& val) const;
    virtual void	deleteValue(IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
    static
    IlvArrayOfPoints*	PointArray(const IlvValue& val);
    static void		SetValue(IlvValue&, IlUInt, const IlvPoint*);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvPolyPoints : public IlvSimpleGraphic
{
public:
    IlvPolyPoints(IlvDisplay*	display,
		  IlUInt	count,
		  IlvPoint*	points,
		  IlvPalette*	palette     = 0,
		  IlBoolean	computeBBox = IlTrue);
    IlvPolyPoints(IlvDisplay*     display,
		  const IlvPoint& center,
		  IlUInt          count,
		  IlvDim          outerRadius,
		  IlvDim          innerRadius = 0,
		  IlBoolean       crossed = IlFalse,
		  IlvPalette*     palette = 0,
		  IlBoolean	  computeBBox = IlTrue);
    IlvPolyPoints(IlvInputFile& is, IlvPalette*, IlBoolean = IlTrue);
    IlvPolyPoints(const IlvPolyPoints&);
    virtual ~IlvPolyPoints();

    virtual void	computeBBox(IlvRect& bbox);
    IlBoolean		inBBox(const IlvPoint& point) const;
    inline IlUInt	numberOfPoints() const { return _nbpoint; }
    virtual void	addPoint(const IlvPoint& point, IlUInt index);
    virtual void	addPoints(IlUInt	count,
				  IlvPoint*	points,
				  IlUInt	index);
    virtual IlBoolean	removePoints(IlUInt start, IlUInt count);
    IlvPoint*		getPoints(IlvPoint* buffer = 0) const;
    inline IlvPoint*	points(IlvPoint* buffer = 0) const
			{
			    return getPoints(buffer);
			}
    void		setPoints(IlUInt count,
				  IlvPoint*,
				  IlBoolean copyIt = IlTrue);
    virtual void	applyTransform(const IlvTransformer*);
    virtual void	draw(IlvPort*,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const = 0;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* t = 0) const;
    virtual void	translatePoint(const IlvPoint& delta, IlUInt index);
    virtual void	setPoint(const IlvPoint& point, IlUInt index);
    virtual void	getPoint(IlvPoint& point, IlUInt index) const;
    virtual void	print(ILVSTDPREF ostream&, int level = 0) const;
    virtual IlvPoint*	transformPoints(const IlvTransformer* t) const;

    DeclareGraphicAccessors();

    static IlSymbol*	_nPointsValue;
    static IlSymbol*	_pointsValue;

    DeclareInterface(Selection);
    DeclareInterface(Shape);
    DeclareLazyTypeInfo();

protected:
    IlvPoint*		_points;
    IlUInt		_nbpoint;
    IlUInt		_maxPoints;
    IlvRect		_bbox;

    void		reallocPoints(IlUInt nSize,
				      IlBoolean exact = IlFalse);
    void		internalAddPoints(IlUInt, const IlvPoint*, IlUInt);
    // used to optimize addPoint and addPoints methods
    virtual void	extendBBox(IlUInt, const IlvPoint*);

    IlvPolyPoints(IlvDisplay* display, IlvPalette* palette = 0)
	: IlvSimpleGraphic(display, palette),
	  _points(0),
	  _nbpoint(0),
	  _maxPoints(0),
	  _bbox()
    {}
    void		readPoints(IlvInputFile&, IlBoolean);
    static void		ApplySetPoints(IlvGraphic*, IlAny arg);
    static void		ApplyRemovePoints(IlvGraphic*, IlAny arg);
};

ILVVWSEXPORTEDFUNCTION(IlvPoint*)
IlvComputePointsFromDeltas(const IlvPoint&      first,
			   IlUInt               count,
			   IlvDeltaPoint const* deltas);

ILVVWSMODULEINIT(g0polypts);
#endif /* !__Ilv_Graphics_Polypts_H */
