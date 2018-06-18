// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/graphics/mapgenpath.h
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
// Declaration of the IlvMapGeneralPath class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_General_Path_H
#define __Ilv_Maps_General_Path_H

#include <ilviews/base/graphic.h>
#include <ilviews/base/ptarray.h>
#include <ilviews/graphics/path.h>
#include <ilviews/maps/macros.h>
#include <ilog/pool.h>

ILVMAPSMODULEINIT(mapgenpath);

class IlvMapGeneralPathPart;
class ILVMAPSEXPORTED IlvMapGeneralPath
: public IlvSimpleGraphic
{
protected:
    IlvDrawRule		_drawRule;
    IlvRect		_bbox;
    IlBoolean           _badBBox;
    IlUInt                  _subPathNum;
    IlUInt                  _subPathCapacity;
    IlvMapGeneralPathPart** _subPaths;

    IlvPalette*   _bgPal;
public:
    IlvMapGeneralPath(IlvDisplay*      display,
		      IlvDrawRule      drawRule = IlvStrokeAndFill,
		      IlvPalette*      palette = 0);

    virtual ~IlvMapGeneralPath();

    // --------------------------------------------------------------
    void		setDrawRule(IlvDrawRule rule)	{ _drawRule = rule; }
    IlvDrawRule		getDrawRule() 		const	{ return _drawRule; }

    // should have the doc from IlvGraphic
    virtual void draw(IlvPort *dst,
		      const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;

    virtual void boundingBox(IlvRect& bbox,
			     const IlvTransformer* t=0) const;

    IlBoolean contains(const IlvPoint& p,
			const IlvPoint& tp,
			const IlvTransformer* t) const;

    virtual void applyTransform(const IlvTransformer* t);

    void lineTo(const IlvPoint& endPoint);

    void arcTo(const IlvPoint& intermediatePoint,
	       const IlvPoint& endPoint);

    void moveTo(const IlvPoint& newPoint);

    void setForeground(IlvColor* fg);

    void setBackground(IlvColor* bg);

    void setPalette(IlvPalette* pal);

    virtual void setAlpha(IlvIntensity alpha);

    virtual void setAntialiasingMode(IlvAntialiasingMode);

    IlvPalette* getFillPalette() const;

    void setFillPalette(IlvPalette* pal);

    void setFillForeground(IlvColor* fg);

    void setFillBackground(IlvColor* bg);

    // documented in super class
    void setMode(IlvDrawMode mode);
public:
    DeclareTypeInfo();
    DeclareIOConstructors(IlvMapGeneralPath);

protected:
    void ensureSubPathCapacity(IlUInt newCapacity);
    void computeBBox(const IlvTransformer* t);

    IlvMapsIcFriend(mapgenpath, ILVMAPSEXPORTED);
};

#endif /* !__Ilv_Maps_General_Path_H */

