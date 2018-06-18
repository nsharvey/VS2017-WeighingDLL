// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/piechart.h
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
// Declaration of the IlvPieChart class
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Piechart_H
#define __Ilv31_Piechart_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Chart_H)
#include <ilviews/chart.h>
#endif

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvPieChart
: public IlvChart {
public:
    IlvPieChart(IlvDisplay*    display,
		const IlvRect& pierect,
		IlvChartData*  data,
		IlFloat        start        = (IlFloat)0,
		IlFloat        range        = (IlFloat)360,
		IlvDim         tearOffDelta = 20,
		IlvPalette*    palette      = 0);
    virtual ~IlvPieChart();
    // ____________________________________________________________
    IlFloat  getStart()         const      { return _start;  }
    void     setStart(IlFloat start)       { _start = start; }
    IlFloat  getRange()         const      { return _range;  }
    void     setRange(IlFloat range);
    IlFloat  getRatio()         const      { return _ratio;  }
    void     computeRatio();
    IlvDim   getTearOffDelta()  const      { return _delta;  }
    void     setTearOffDelta(IlvDim delta) { _delta = delta;  }
    IlUInt  getSliceCount() const;
    IlBoolean isSliceTearedOff(IlUInt i) const {return _isSliceTearedOff[i];}
    void tearOffSlice(IlUInt i,IlBoolean v=IlTrue) {_isSliceTearedOff[i]=v;}
    IlInt   firstTearedOffSlice() const;
    void     getGraphicOffset(IlvPoint& p) const { p = _offset; }
    void     setGraphicOffset(const IlvPoint& p) { _offset = p; }
    IlvPalette* getSlicePalette(IlUInt i) const { return _slicePalettes[i]; }
    IlvGraphic* getSliceGraphic(IlUInt i) const { return _sliceGraphics[i]; }
    void setSlicePalette(IlUInt pos, IlvPalette* palette);
    void setSliceGraphic(IlUInt pos, IlvGraphic* graphic);
    virtual void adjustFromData();
    virtual void getPoint(IlUInt num, IlvPoint& p,
			  const IlvTransformer* t = 0) const;
    virtual void setPoint(IlUInt num, const IlvPoint&,
			  const IlvTransformer*t = 0);
    virtual void bboxPoint(IlUInt num, IlvRect&,
                           const IlvTransformer* t = 0) const;
    virtual IlBoolean isFilled() const { return IlTrue; }
    virtual void adjust(const IlvRect& rect);
    virtual void draw(IlvPort*, const IlvTransformer* t=0,
		      const IlvRegion* clip=0) const;
    virtual void drawSliceFilledArc(IlvPort* dst, IlUInt pos,
				    IlFloat start, IlFloat range,
				    const IlvTransformer* t = 0,
				    const IlvRegion* clip = 0) const;
    virtual void drawSliceSeparators(IlvPort* dst, IlUInt pos,
				     IlFloat start, IlFloat range,
				     const IlvTransformer* t = 0,
				     const IlvRegion* clip = 0) const;
    virtual void drawSliceBorder(IlvPort* dst, IlUInt pos,
				 IlFloat start, IlFloat range,
				 const IlvTransformer* t = 0,
				 const IlvRegion* clip = 0) const;
    virtual void drawSliceGraphic(IlvPort* dst, IlUInt pos,
				  IlFloat start, IlFloat range,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void applyTransform(const IlvTransformer* t);
    virtual void setMode(IlvDrawMode mode);
    virtual void setOverwrite(IlBoolean over);
    virtual void boundingBoxOfChart(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    virtual void slicePieBBox(IlvRect&, IlUInt pos, IlFloat start,
			      IlFloat range, const IlvTransformer* t=0) const;
    virtual void sliceBBox(IlvRect&, IlUInt pos,
			   const IlvTransformer* t = 0) const;
    virtual void sliceFilledArcBBox(IlvRect&, const IlvRect& pierect,
				    IlUInt pos, IlFloat start, IlFloat range,
				    const IlvTransformer* t = 0) const;
    virtual void sliceGraphicBBox(IlvRect&, const IlvRect& pierect,
				  IlUInt pos, IlFloat start, IlFloat range,
				  const IlvTransformer* t = 0) const;
    virtual IlBoolean contains(const IlvPoint& p, const IlvPoint& tp,
				const IlvTransformer* t = 0) const;
    virtual IlBoolean sliceContains(const IlvPoint& tp, IlUInt pos,
				    const IlvTransformer*) const;
    virtual IlInt whichSlice(const IlvPoint& tp,
			     const IlvTransformer* t = 0) const;
    void sliceStartRange(IlUInt pos, IlFloat& start, IlFloat& range,
			 const IlvTransformer* t = 0) const;
    DeclareTypeInfo();
    DeclareIOConstructors(IlvPieChart);
protected:
    IlFloat		_start;
    IlFloat		_range;
    IlvRect		_pierect;
    IlvDim		_delta;
    IlFloat		_ratio;
    IlvPoint		_offset;
    IlvPalette**	_slicePalettes;
    IlvGraphic**	_sliceGraphics;
    IlBoolean*		_isSliceTearedOff;
    virtual IlvPoint* getPoints(IlUInt& count, const IlvRegion* clip = 0,
                                const IlvTransformer* t = 0) const;
};

ILV31VWSMODULEINIT(piechart);
#endif /* !__Ilv31_Piechart_H */
