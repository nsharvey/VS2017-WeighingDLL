// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/include/ilviews/highlow.h
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
// Declaration of the IlvHighLowChart, IlvChartDataHighLow
// and their predefined subtypes.
// --------------------------------------------------------------------------
#ifndef __Ilv1X_Highlow_H
#define __Ilv1X_Highlow_H

#if !defined(__Ilv1x_Macros_H)
#include <ilviews/macros1x.h>
#endif
#if !defined(__Ilv_Chart_H)
#include <ilviews/chart.h>
#endif

// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvChartDataHighLow
: public IlvChartData {
public:
    IlvChartDataHighLow(IlvUInt count, IlvFloat* maxPpoints,
			IlvFloat*  minPpoints,
			IlvBoolean owner = IlvTrue);
    virtual ~IlvChartDataHighLow();
    // ____________________________________________________________
    void computeBBox();
    virtual void getPoint(IlvUInt num, IlvFloatPoint& p) const;
    virtual IlvFloatPoint* getPoints(IlvUInt& num) const;
    virtual IlvFloatPoint* getPoints(const IlvFloatRect& rect,
				     IlvUInt& num) const;
    virtual void boundingBox(IlvFloatRect& rect) const;
    virtual IlvBoolean isReadOnly() const;
    virtual void setPoint(IlvUInt num, const IlvFloatPoint& p);
    void getMinPoint(IlvUInt num, IlvFloatPoint& p) const;
    IlvFloatPoint* getMinPoints(IlvUInt& num) const;
    IlvFloatPoint* getMinPoints(const IlvFloatRect& rect, IlvUInt& num) const;
    virtual void setMinPoint(IlvUInt num, const IlvFloatPoint& p);
    IlvFloat* getMaxValues(IlvUInt& count) const
	{ count = _count; return _ymaxvalues; }
    IlvFloat* getMinValues(IlvUInt& count) const
	{ count = _count; return _yminvalues; }
    void setValues(IlvUInt count, IlvFloat* maxpoints,IlvFloat* minpoints,
		   IlvBoolean owner = IlvTrue);
    IlvBoolean isOwner() const { return _owner; }
    IlvFloat getYMin() const { return _ymin; }
    IlvFloat getYMax() const { return _ymax; }
    void setOwner(IlvBoolean owner) { _owner = owner;}
    static const char* _className;
    const char* className() const;
    static IlvChartData* read(IlvInputFile&);
    virtual void         write(IlvOutputFile&) const;
    virtual IlvChartData* copy() const;
protected:
    IlvFloat*  _ymaxvalues;
    IlvFloat*  _yminvalues;
    IlvFloat   _ymin;
    IlvFloat   _ymax;
    IlvBoolean _owner;
};

// --------------------------------------------------------------------------
//        HighLow
// --------------------------------------------------------------------------
class ILV1XVWSEXPORTED IlvHighLowChart
: public IlvChart {
public:
    IlvHighLowChart(IlvDisplay*          display,
		    IlvChartDataHighLow* data,
		    const IlvPoint&      origin,
		    IlvFloat scalex, IlvFloat scaley,
		    IlvDim               size = IlvChartSize,
		    IlvPalette*          palette = 0)
    : IlvChart(display, data, origin, scalex, scaley, palette),
      _size(size) {}
    // ____________________________________________________________
    virtual IlvBoolean contains(const IlvPoint&, const IlvPoint&,
				const IlvTransformer* t = 0) const;
    virtual void draw(IlvPort* dst, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    virtual void boundingBox(IlvRect& rect,
			     const IlvTransformer* t = 0) const;
    IlvDim getSize() const    { return _size; }
    void setSize(IlvDim size) { _size = size; }
    virtual void bboxPoint(IlvUInt num, IlvRect&,
			   const IlvTransformer* t = 0) const;
    void getMinPoint(IlvUInt num, IlvPoint& p,
		     const IlvTransformer*t = 0) const;
    void setMinPoint(IlvUInt num, const IlvPoint&,
		     const IlvTransformer* t = 0);
    IlvInt whichMinPoint(IlvDim, const IlvPoint& p, const IlvPoint& tp,
			 const IlvTransformer* t) const;
    DeclareTypeInfo();
protected:
    IlvDim        _size;
};

ILV1XVWSMODULEINIT(highlow);

#endif /* !__Ilv1X_Highlow_H */
