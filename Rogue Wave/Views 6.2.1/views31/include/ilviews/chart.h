// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/chart.h
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
// Definition of the IlvChart, IlvChartData and their predefined subtypes.
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Chart_H
#define __Ilv31_Chart_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvChartPointInfo
{
public:
    IlvChartPointInfo(IlUInt index, IlvGraphic* graphic,
		      IlvPos dx=0, IlvPos dy=0)
	: _graphic(graphic), _index(index) { _offset.move(dx, dy); }
    virtual ~IlvChartPointInfo();
    // ____________________________________
    IlvGraphic* getGraphic() const { return _graphic; }
    void setGraphic(IlvGraphic* graphic);
    void getOffset(IlvPoint& p) const { p = _offset; }
    void setOffset(const IlvPoint& p) { _offset = p; }
    IlInt getIndex() const { return _index; }
    void setIndex(IlUInt index) { _index = index; }
    virtual IlvChartPointInfo* copy() const;
protected:
    IlvGraphic* _graphic;
    IlvPoint	_offset;
    IlInt	_index;
};

// --------------------------------------------------------------------------
#define DeclareChartDataInfoRO() IlvDeclareClassInfo();	\
    static IlvChartData* read(IlvInputFile&);		\
    virtual IlvChartData* copy() const
#define DeclareChartDataInfo() DeclareChartDataInfoRO(); \
    virtual void write(IlvOutputFile&) const
#define DeclareChartDataIOConstructors(classname) public:	\
    classname(IlvInputFile& file);				\
    classname(const classname& source)

class ILV31VWSEXPORTED IlvChartData
{
public:
    IlvChartData(IlFloat tmin, IlFloat tmax, IlUInt count);
    virtual ~IlvChartData();
    // ____________________________________________________________
    void lock()	  { _refCount++; }
    void unLock();
    virtual void getPoint(IlUInt num, IlvFloatPoint& p) const =0;
    virtual void setPoint(IlUInt, const IlvFloatPoint&);
    virtual IlvFloatPoint* getPoints(IlUInt& num) const;
    virtual IlvFloatPoint* getPoints(const IlvFloatRect& rect,
				     IlUInt& num) const;
    void addPointInfo(IlvChartPointInfo*);
    void removePointInfo(IlUInt num, IlBoolean destroyIt = IlTrue);
    IlvChartPointInfo* getPointInfo(IlUInt num) const;
    IlvChartPointInfo** getAllPointInfo(IlUInt& num) const;
    virtual void boundingBox(IlvFloatRect&) const;
    virtual IlBoolean isReadOnly() const;
    IlUInt getCount() const {return _count;}
    IlUInt count()    const {return _count;} // Backward Compatibility
    IlFloat getMin() const {return _tmin;}
    IlFloat getMax() const {return _tmax;}
    void setMin(IlFloat tmin)	 { _tmin = tmin; }
    void setMax(IlFloat tmax)	 { _tmax = tmax; }
    void setCount(IlUInt count) {_count = count;}
    virtual void write(IlvOutputFile&) const = 0;
    virtual IlvChartData* copy() const = 0;
    IlvDeclareClassInfo();
    DeclareChartDataIOConstructors(IlvChartData);
protected:
    IlFloat  _tmin;
    IlFloat  _tmax;
    IlUInt   _count;
    IlFloat  _delta;
    IlUInt   _refCount;
    IlArray  _pointInfo;
};

typedef IlFloat (* IlvFloatFunction)(IlFloat);

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvChartDataFunction
: public IlvChartData {
public:
    IlvChartDataFunction(IlFloat tmin, IlFloat tmax, IlUInt count,
			 IlvFloatFunction f)
	: IlvChartData(tmin, tmax, count), _function(f) {}
    // ____________________________________________________________
    virtual void getPoint(IlUInt num, IlvFloatPoint& p) const;
    IlvFloatFunction getFunction() const { return _function;}
    DeclareChartDataInfo();
    DeclareChartDataIOConstructors(IlvChartDataFunction);
protected:
    IlvFloatFunction _function;
};

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvChartDataPoints
: public IlvChartData {
public:
    IlvChartDataPoints(IlUInt count, IlvFloatPoint* points,
		       IlBoolean owner = IlTrue);
    virtual ~IlvChartDataPoints();
    // ____________________________________________________________
    void computeBBox();
    virtual void getPoint(IlUInt num, IlvFloatPoint& p) const;
    virtual IlvFloatPoint* getPoints(IlUInt& num) const;
    virtual IlvFloatPoint* getPoints(const IlvFloatRect& rect,
				     IlUInt& num) const;
    virtual void boundingBox(IlvFloatRect& rect) const;
    virtual IlBoolean isReadOnly() const;
    virtual void setPoint(IlUInt num, const IlvFloatPoint& p);
    void setValues(IlUInt count, IlvFloatPoint* points,
		   IlBoolean owner = IlTrue);
    IlBoolean isOwner() const {return _owner;}
    void setOwner(IlBoolean owner) { _owner = owner;}
    DeclareChartDataInfo();
    DeclareChartDataIOConstructors(IlvChartDataPoints);
protected:
    IlvFloatPoint* _points; //sorted
    IlvFloatRect   _bbox;
    IlBoolean	   _owner;
};

// --------------------------------------------------------------------------
//$doc:Chypt
class ILV31VWSEXPORTED IlvChartDataYPoints
: public IlvChartData {
public:
    IlvChartDataYPoints(IlUInt count, IlFloat* points,
			IlBoolean owner = IlTrue);
    virtual ~IlvChartDataYPoints();
    // ____________________________________________________________
    void	 computeBBox();
    virtual void getPoint(IlUInt num, IlvFloatPoint& p) const;
    virtual void boundingBox(IlvFloatRect& rect) const;
    virtual IlBoolean isReadOnly() const;
    virtual void setPoint(IlUInt num, const IlvFloatPoint& p);
    IlFloat*	 getValues(IlUInt& count) const
	{ count = _count; return _yvalues; }
    void	 setValues(IlUInt count, IlFloat* points,
		   IlBoolean owner = IlTrue);
    IlBoolean	 isOwner() const { return _owner; }
    IlFloat	 getYMin() const { return _ymin; }
    IlFloat	 getYMax() const { return _ymax; }
    void	 setOwner(IlBoolean owner) { _owner = owner;}
    DeclareChartDataInfo();
    DeclareChartDataIOConstructors(IlvChartDataYPoints);
protected:
    IlFloat*  _yvalues;
    IlFloat   _ymin;
    IlFloat   _ymax;
    IlBoolean _owner;
};
//end:Chypt

//---------------------------------------------------------------------
// IlvAbstractChart
//---------------------------------------------------------------------
class ILV31VWSEXPORTED IlvAbstractChart
: public IlvSimpleGraphic {
public:
    IlvAbstractChart(IlvDisplay*     display,
		     IlvPalette*     palette = 0)
    : IlvSimpleGraphic(display, palette),
      _origin(),
      _scalex((IlFloat)1),
      _scaley((IlFloat)1) {}
    IlvAbstractChart(IlvDisplay*     display,
		     const IlvPoint& origin,
		     IlFloat	     scalex, IlFloat scaley,
		     IlvPalette*     palette = 0)
    : IlvSimpleGraphic(display, palette),
      _origin(origin),
      _scalex(scalex),
      _scaley(scaley) {}
    // ____________________________________________________________
    virtual void applyTransform(const IlvTransformer* t);
    void getOrigin(IlvPoint& p) const { p = _origin; }
    void setOrigin(const IlvPoint& p) { _origin = p; }
    IlFloat getScaleX() const { return _scalex; }
    IlFloat getScaleY() const { return _scaley; }
    void setScaleX(IlFloat s) { _scalex = s;}
    void setScaleY(IlFloat s) { _scaley = s;}
    virtual IlBoolean isFilled() const { return IlFalse; }
    virtual IlvDirection getOrientation() const { return IlvVertical; }
    virtual void drawPointInfo(IlvPort* dst,
			       const IlvTransformer* t = 0,
			       const IlvRegion* clip = 0) const = 0;
    void getDataPoint(const IlvChartData*, IlUInt num, IlvPoint& p,
		      const IlvTransformer* t = 0) const;
    void setDataPoint(IlvChartData*, IlUInt num,
		      const IlvPoint&, const IlvTransformer* t = 0);
    virtual IlBoolean intersection(const IlvRect& rect,
				   const IlvFloatRect& allrect,
				   IlvFloatRect& frect,
				   const IlvTransformer* t=0) const;
    virtual void boundingBoxOfChart(IlvRect& rect,
				    const IlvTransformer* t = 0) const = 0;
    virtual void chartBBox(IlvFloatRect& frect,
			   const IlvRect* rect = 0,
			   const IlvTransformer* t = 0) const = 0;
    virtual void dataPointBBox(const IlvChartData*, IlUInt num, IlvRect&,
			       const IlvTransformer* t = 0) const;
    virtual void bboxPoint(IlUInt num, IlvRect&,
			   const IlvTransformer* t = 0) const = 0;
    virtual void adjust(const IlvRect&);
    static IlvChartData* readData(IlvInputFile&);
    DeclareTypeInfo();
    DeclareIOConstructors(IlvAbstractChart);
protected:
    IlvPoint	  _origin;
    IlFloat	  _scalex;
    IlFloat	  _scaley;
};

//---------------------------------------------------------------------
// IlvChart
//---------------------------------------------------------------------
#define IlvChartSize 4
#define IlvChartSpacing 10

class ILV31VWSEXPORTED IlvChart
    : public IlvAbstractChart {
public:
    IlvChart(IlvDisplay*     display,
	     IlvChartData*   data,
	     IlvPalette*     palette=0);
    IlvChart(IlvDisplay*     display,
	     IlvChartData*   data,
	     const IlvPoint& origin,
	     IlFloat	     scalex, IlFloat scaley,
	     IlvPalette*     palette=0);
    ~IlvChart();
    // ____________________________________________________________
    virtual void apply(IlvApplyObject, IlAny);
    virtual void setMode(IlvDrawMode m);
    virtual void setOverwrite(IlBoolean value);
    virtual void getPoint(IlUInt num, IlvPoint& p,
			  const IlvTransformer* t = 0) const;
    virtual void setPoint(IlUInt num, const IlvPoint&,
			  const IlvTransformer*t = 0);
    IlvChartData* getData() const { return _data;  }
    void	  setData(IlvChartData* chart);
    virtual void  adjustFromData();
    virtual void boundingBoxOfChart(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    virtual void chartBBox(IlvFloatRect& frect,
			   const IlvRect* rect = 0,
			   const IlvTransformer* t = 0) const;
    virtual void boundingBox(IlvRect& rect,
			     const IlvTransformer* t=0) const;
    virtual IlInt whichPoint(IlvDim, const IlvPoint& p, const IlvPoint& tp,
			      const IlvTransformer* t) const;
    IlBoolean isReadOnly() const { return _data->isReadOnly(); }
    virtual void draw(IlvPort* dst, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const =0;
    virtual void drawPointInfo(IlvPort* dst, const IlvTransformer* t = 0,
			       const IlvRegion* clip = 0) const;
    virtual void bboxPoint(IlUInt num, IlvRect&,
			   const IlvTransformer* t = 0) const;
    virtual const char* getDefaultInteractor() const;
    virtual void scroll(IlFloat y, IlvRect&,
			IlvSystemPort* dst=0, const IlvTransformer* t=0);
    DeclareTypeInfo();
    DeclareIOConstructors(IlvChart);
protected:
    IlvChartData* _data;
    virtual IlvPoint* getPoints(IlUInt& count,
				const IlvRegion* clip = 0,
				const IlvTransformer* t = 0) const;
};

// --------------------------------------------------------------------------
//	  Polyline
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvPolylineChart
: public IlvChart {
public:
    IlvPolylineChart(IlvDisplay*     display,
		     IlvChartData*   data,
		     IlvPalette*     palette=0)
	: IlvChart(display, data, palette) {}
    IlvPolylineChart(IlvDisplay*     display,
		     IlvChartData*   data,
		     const IlvPoint& origin,
		     IlFloat	     scalex, IlFloat scaley,
		     IlvPalette*     palette=0)
	: IlvChart(display, data, origin, scalex, scaley, palette) {}
    // ____________________________________________________________
    virtual IlBoolean contains(const IlvPoint&, const IlvPoint&,
			       const IlvTransformer* t=0) const;
    virtual void draw(IlvPort* dst, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvPolylineChart);
};

// --------------------------------------------------------------------------
//	  Polygon
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvPolygonChart
: public IlvChart {
 public:
    IlvPolygonChart(IlvDisplay*	    display,
		    IlvChartData*   data,
		    IlvPalette*	    palette=0)
	: IlvChart(display, data, palette) {}
    IlvPolygonChart(IlvDisplay*	    display,
		    IlvChartData*   data,
		    const IlvPoint& origin,
		    IlFloat	    scalex, IlFloat scaley,
		    IlvPalette*	    palette=0)
	: IlvChart(display, data, origin, scalex, scaley, palette) {}
    // ____________________________________________________________
    virtual void boundingBoxOfChart(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    virtual IlBoolean contains(const IlvPoint&, const IlvPoint&,
				const IlvTransformer* t = 0) const;
    virtual void draw(IlvPort* dst, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    virtual IlBoolean isFilled() const { return IlTrue; }
    virtual void dataPointBBox(const IlvChartData*, IlUInt num, IlvRect&,
			       const IlvTransformer*t = 0) const;
    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvPolygonChart);
protected:
    virtual IlvPoint* getPoints(IlUInt& count,
				const IlvRegion* clip = 0,
				const IlvTransformer* t = 0) const;
};

// --------------------------------------------------------------------------
//	  Stair
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvStairChart
: public IlvPolygonChart {
public:
    IlvStairChart(IlvDisplay*	  display,
		  IlvChartData*	  data,
		  IlvPalette*	  palette=0)
	: IlvPolygonChart(display, data, palette)  {}
    IlvStairChart(IlvDisplay*	  display,
		  IlvChartData*	  data,
		  const IlvPoint& origin,
		  IlFloat	  scalex, IlFloat scaley,
		  IlvPalette*	  palette=0)
	: IlvPolygonChart(display, data, origin, scalex, scaley, palette)  {}
    // ____________________________________________________________
    virtual IlBoolean contains(const IlvPoint&, const IlvPoint&,
				const IlvTransformer* t = 0) const;
    virtual void draw(IlvPort* dst, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvStairChart);
};

// --------------------------------------------------------------------------
//	  Bar
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvBarChart
: public IlvChart {
public:
    IlvBarChart(IlvDisplay*	display,
		IlvChartData*	data,
		IlvDirection	orientation = IlvVertical,
		IlvDim		size	    = IlvChartSize,
		IlvPalette*	palette=0)
	: IlvChart(display, data, palette),
	  _size(size), _orientation(orientation) {}
    IlvBarChart(IlvDisplay*	display,
		IlvChartData*	data,
		const IlvPoint& origin,
		IlFloat	scalex, IlFloat scaley,
		IlvDirection	orientation = IlvVertical,
		IlvDim		size	    = IlvChartSize,
		IlvPalette*	palette=0)
	: IlvChart(display, data, origin, scalex, scaley, palette),
	  _size(size), _orientation(orientation) {}
    // ____________________________________________________________
    virtual void boundingBoxOfChart(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    virtual IlBoolean contains(const IlvPoint& p, const IlvPoint& tp,
			       const IlvTransformer* t = 0) const;
    virtual void draw(IlvPort* dst, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    virtual void applyTransform(const IlvTransformer* t);
    virtual IlBoolean isFilled() const { return IlTrue; }
    IlvDim getSize() const     { return _size;	}
    void  setSize(IlvDim size) { _size = size; }
    virtual IlvDirection getOrientation() const { return _orientation; }
    void setOrientation(IlvDirection o) { _orientation=o; }
    virtual void dataPointBBox(const IlvChartData*, IlUInt num, IlvRect&,
			       const IlvTransformer*t = 0) const;
    DeclareTypeInfo();
    DeclareIOConstructors(IlvBarChart);
protected:
    IlvDim	 _size;
    IlvDirection _orientation;
};

// --------------------------------------------------------------------------
//	Plots
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvScatterChart
: public IlvChart {
public:
    IlvScatterChart(IlvDisplay*	    display,
		    IlvChartData*   data,
		    IlvMarkerType   marker  = IlvMarkerFilledSquare,
		    IlvPalette*	    palette = 0)
	: IlvChart(display, data, palette),
	  _size(IlvChartSize), _marker(marker) {}
    IlvScatterChart(IlvDisplay*	    display,
		    IlvChartData*   data,
		    const IlvPoint& origin,
		    IlFloat	    scalex, IlFloat scaley,
		    IlvMarkerType   marker  = IlvMarkerFilledSquare,
		    IlvPalette*	    palette = 0)
	: IlvChart(display, data, origin, scalex, scaley, palette),
	  _size(IlvChartSize), _marker(marker) {}
    // ____________________________________________________________
    virtual IlBoolean contains(const IlvPoint&, const IlvPoint&,
			       const IlvTransformer* t = 0) const;
    virtual void draw(IlvPort* dst, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    virtual void boundingBoxOfChart(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    virtual void applyTransform(const IlvTransformer* t);
    IlvDim getSize()	const { return _size; }
    void setSize(IlvDim size) { _size = size; }
    IlvMarkerType getMarker()		    const { return _marker; }
    void	  setMarker(IlvMarkerType marker) { _marker=marker; }
    virtual void dataPointBBox(const IlvChartData*, IlUInt num, IlvRect&,
			       const IlvTransformer*t = 0) const;
    DeclareTypeInfo();
    DeclareIOConstructors(IlvScatterChart);
protected:
    IlvDim	  _size;
    IlvMarkerType _marker;
};

// --------------------------------------------------------------------------
//	  3d Bar
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED Ilv3dBarChart
: public IlvChart
{
public:
    Ilv3dBarChart(IlvDisplay*	  display,
		  IlvChartData*	  data,
		  IlvDim	  size = IlvChartSize,
		  IlvDim	  depth = IlvChartSize,
		  IlvPalette*	  palette=0)
    : IlvChart(display, data, palette),
      _topshadow(0),
      _bottomshadow(0),
      _size(size),
      _depth(depth) { computePalettes(); }
    Ilv3dBarChart(IlvDisplay*	  display,
		  IlvChartData*	  data,
		  const IlvPoint& origin,
		  IlFloat	  scalex, IlFloat scaley,
		  IlvDim size = IlvChartSize,
		  IlvDim depth = IlvChartSize,
		  IlvPalette*	  palette=0)
    : IlvChart(display, data, origin, scalex, scaley, palette),
      _topshadow(0),
      _bottomshadow(0),
      _size(size),
      _depth(depth) { computePalettes(); }
    virtual ~Ilv3dBarChart();
    // ____________________________________________________________
    virtual void applyTransform(const IlvTransformer* t);
    virtual IlBoolean contains(const IlvPoint&, const IlvPoint&,
			       const IlvTransformer* t = 0) const;
    virtual void draw(IlvPort* dst, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    virtual void boundingBoxOfChart(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    virtual IlBoolean isFilled() const { return IlTrue; }
    IlvDim getSize()	    const { return _size; }
    void   setSize(IlvDim size)	  { _size = size; }
    IlvDim getDepth()	    const { return _depth;  }
    void   setDepth(IlvDim depth) { _depth = depth; }
    void setBackground(IlvColor* c);
    void setForeground(IlvColor* c);
    virtual void setMode(IlvDrawMode m);
    virtual void setOverwrite(IlBoolean value);
    virtual void dataPointBBox(const IlvChartData*, IlUInt num, IlvRect&,
			       const IlvTransformer*t = 0) const;
    DeclareTypeInfo();
    DeclareIOConstructors(Ilv3dBarChart);
protected:
    IlvPalette* _topshadow;
    IlvPalette* _bottomshadow;
    IlvDim	_size;
    IlvDim	_depth;
    void computePalettes();
};

// --------------------------------------------------------------------------
// Multi-Data Chart
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvMultiChart
: public IlvAbstractChart {
public:
    IlvMultiChart(IlvDisplay*	       display,
		  IlvPalette*	       palette = 0);
    IlvMultiChart(IlvDisplay*	       display,
		  const IlvPoint&      origin,
		  IlFloat	       scalex,
		  IlFloat	       scaley,
		  IlvPalette*	       palette = 0);
    ~IlvMultiChart();
    // ____________________________________________________________
    virtual void apply(IlvApplyObject, IlAny);
    virtual void setMode(IlvDrawMode m);
    virtual void setOverwrite(IlBoolean value);
    virtual void boundingBoxOfChart(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    virtual IlBoolean contains(const IlvPoint&, const IlvPoint&,
			       const IlvTransformer* t = 0) const;
    virtual void draw(IlvPort* dst, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const = 0;
//$doc:Mulch
    IlUShort	  getCardinal() const { return _dataCount; }
    IlInt	  getIndex(const IlvChartData*) const;
    IlvChartData* const* getDataArray(IlUShort& count) const {
	count = _dataCount; return _dataArray; }

    IlvChartData* getData(IlUShort index) const { return _dataArray[index]; }
    virtual void  setData(IlUShort index,
			  IlvChartData* data, IlvPalette* palette);
    virtual void  addData(IlvChartData* data, IlvPalette* palette);
    virtual void  insertData(IlUShort index,
			     IlvChartData* data, IlvPalette* palette);
    virtual IlBoolean removeData(IlUShort index);
    IlvPalette* const* getDataPalettes(IlUShort& count) const {
	count = _dataCount; return _dataPalettes; }
    IlvPalette* getDataPalette(IlUShort i) const {
	return _dataPalettes[i]; }
//end:Mulch
    DeclareTypeInfo();
    DeclareIOConstructors(IlvMultiChart);
protected:
    IlvChartData** _dataArray;
    IlvPalette**   _dataPalettes;
    IlUShort	   _dataCount;
    IlUShort	   _dataAlloc;
};

// --------------------------------------------------------------------------
// SideBySide Chart
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvSideBySideChart
: public IlvMultiChart {
public:
    IlvSideBySideChart(IlvDisplay*	    display,
		       IlUShort		    spacing = IlvChartSpacing,
		       IlvPalette*	    palette = 0)
	: IlvMultiChart(display, palette), _spacing(spacing) {}
    IlvSideBySideChart(IlvDisplay*	    display,
		       const IlvPoint&	    origin,
		       IlFloat		    scalex,
		       IlFloat		    scaley,
		       IlUShort		    spacing = IlvChartSpacing,
		       IlvPalette*	    palette = 0)
	: IlvMultiChart(display, origin, scalex, scaley, palette),
	  _spacing(spacing) {}
    ~IlvSideBySideChart();
    // ____________________________________________________________
    IlUShort getSpacing() const { return _spacing; }
    void   setSpacing(IlUShort spacing)   { _spacing = spacing; }
    virtual void bboxPoint(IlUInt num, IlvRect&,
			   const IlvTransformer* t = 0) const;
    IlInt whichDataPoint(IlvDim, IlUShort& index,
			 const IlvPoint& tp, const IlvTransformer* t=0) const;
    virtual void drawPointInfo(IlvPort* dst, const IlvTransformer* t = 0,
			       const IlvRegion* clip = 0) const;
    virtual void chartBBox(IlvFloatRect& frect, const IlvRect* rect = 0,
			   const IlvTransformer* t = 0) const;
    virtual void boundingBox(IlvRect& rect,
			     const IlvTransformer* t=0) const;
    virtual void dataPointRelativeBBox(const IlvChartData*,
				       IlUInt num, IlvRect&,
				       const IlvTransformer* t = 0) const;
    virtual const char* getDefaultInteractor() const;
    void getDataRelativePoint(const IlvChartData*, IlUInt num, IlvPoint&,
			      const IlvTransformer* t=0) const;
    void setDataRelativePoint(IlvChartData*, IlUInt num, const IlvPoint&,
			      const IlvTransformer* t=0);
    DeclareTypeInfo();
    DeclareIOConstructors(IlvSideBySideChart);
protected:
    IlUShort _spacing;
};

// --------------------------------------------------------------------------
// SideBySide BarChart
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvSideBySideBarChart
: public IlvSideBySideChart {
public:
    IlvSideBySideBarChart(IlvDisplay*	   display,
			  IlUShort	   spacing = IlvChartSpacing,
			  IlvDim	   size = IlvChartSize,
			  IlvPalette*	   palette = 0)
	: IlvSideBySideChart(display, spacing, palette), _size(size) {}
    IlvSideBySideBarChart(IlvDisplay*	   display,
			  const IlvPoint&  origin,
			  IlFloat	   scalex,
			  IlFloat	   scaley,
			  IlUShort	   spacing = IlvChartSpacing,
			  IlvDim	   size = IlvChartSize,
			  IlvPalette*	   palette = 0)
	: IlvSideBySideChart(display, origin, scalex, scaley, spacing,palette),
	  _size(size) {}
    // ____________________________________________________________
    virtual void draw(IlvPort* dst, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    virtual IlBoolean isFilled() const { return IlTrue; }
    virtual void dataPointBBox(const IlvChartData*, IlUInt num, IlvRect&,
			       const IlvTransformer* t = 0) const;
    IlvDim getSize() const { return _size; }
    void   setSize(IlvDim size)	  { _size = size; }
    DeclareTypeInfo();
    DeclareIOConstructors(IlvSideBySideBarChart);
protected:
    IlvDim	 _size;
};

// --------------------------------------------------------------------------
// Stacked Chart
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvStackedChart
: public IlvMultiChart {
public:
    IlvStackedChart(IlvDisplay*		 display,
		    IlvPalette*		 palette = 0)
	: IlvMultiChart(display, palette) {}
    IlvStackedChart(IlvDisplay*		 display,
		    const IlvPoint&	 origin,
		    IlFloat		 scalex,
		    IlFloat		 scaley,
		    IlvPalette*		 palette = 0)
	: IlvMultiChart(display, origin, scalex, scaley, palette) {}
    ~IlvStackedChart();
    // ____________________________________________________________
    virtual void bboxPoint(IlUInt num, IlvRect&,
			   const IlvTransformer* t = 0) const;
    IlInt whichDataPoint(IlvDim, IlUShort& index,
			  const IlvPoint& tp, const IlvTransformer* t=0) const;
    virtual void drawPointInfo(IlvPort* dst, const IlvTransformer* t = 0,
			       const IlvRegion* clip = 0) const;
    virtual void chartBBox(IlvFloatRect& frect, const IlvRect* rect = 0,
			   const IlvTransformer* t = 0) const;
    virtual void boundingBox(IlvRect& rect,
			     const IlvTransformer* t=0) const;
    virtual void dataPointRelativeBBox(const IlvChartData*,
				       IlUInt num, IlvRect&,
				       const IlvTransformer* t = 0) const;
    virtual const char* getDefaultInteractor() const;
    void getDataRelativePoint(const IlvChartData*, IlUInt num, IlvPoint&,
			      const IlvTransformer* t=0) const;
    void setDataRelativePoint(IlvChartData*, IlUInt num, const IlvPoint&,
			      const IlvTransformer* t=0);
    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvStackedChart);
};

// --------------------------------------------------------------------------
// Stacked BarChart
// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvStackedBarChart
: public IlvStackedChart {
public:
    IlvStackedBarChart(IlvDisplay*	    display,
		       IlvDim		    size    = IlvChartSize,
		       IlvPalette*	    palette = 0)
	: IlvStackedChart(display, palette), _size(size) {}
    IlvStackedBarChart(IlvDisplay*	    display,
		       const IlvPoint&	    origin,
		       IlFloat		    scalex, IlFloat scaley,
		       IlvDim		    size	= IlvChartSize,
		       IlvPalette*	    palette=0)
	: IlvStackedChart(display, origin, scalex, scaley, palette),
	  _size(size) {}
    // ____________________________________________________________
    virtual void draw(IlvPort* dst, const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    virtual IlBoolean isFilled() const { return IlTrue; }
    virtual void dataPointBBox(const IlvChartData*, IlUInt num, IlvRect&,
			       const IlvTransformer* t = 0) const;
    IlvDim getSize() const { return _size; }
    void   setSize(IlvDim size)	  { _size = size; }
    DeclareTypeInfo();
    DeclareIOConstructors(IlvStackedBarChart);
protected:
    IlvDim	 _size;
};

ILV31VWSEXPORTEDFUNCTION(IlvFloatPoint*)
IlvReadChartPoints(IlvInputFile& ifile, IlUInt& count);
ILV31VWSEXPORTEDFUNCTION(IlFloat*)
IlvReadChartYPoints(IlvInputFile& ifile, IlUInt& count);
ILV31VWSEXPORTEDFUNCTION(void)
IlvReadChartPointInfo(IlvInputFile& ifile, IlvChartData* data);
ILV31VWSEXPORTEDFUNCTION(void)
IlvWriteChartPointInfo(IlvOutputFile& out, const IlvChartData* data);

// --------------------------------------------------------------------------
typedef IlvChartData* (* Ilv31ChartDataConstructor)(IlvInputFile&);

class ILV31VWSEXPORTED Ilv31ChartDataClassInfo
: public IlvClassInfo
{
public:
    Ilv31ChartDataClassInfo(const char*		  className,
			    IlvClassInfo**	  superClass,
			    Ilv31ChartDataConstructor constructor)
    : IlvClassInfo(className, superClass),
      _constructor(constructor) {}
    // ____________________________________________________________
    Ilv31ChartDataConstructor getConstructor() const { return _constructor; }
protected:
    Ilv31ChartDataConstructor _constructor;
};

#define Ilv31RegisterChartDataClass(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,			\
		new Ilv31ChartDataClassInfo(#classname,	\
					  &superclass::_classinfo,\
					  (Ilv31ChartDataConstructor)\
					  classname::read))
#define Ilv31PostRegisterChartDataClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
		new Ilv31ChartDataClassInfo(#classname,		\
					  &superclass::_classinfo,\
					  (Ilv31ChartDataConstructor)\
					  classname::read))
#define Ilv31PredefinedChartDataIOMembers(classname) \
IlvChartData* classname::copy() const { return new classname(*this); } \
IlvChartData* classname::read(IlvInputFile& i) \
{ return new classname(i); }
#define Ilv31PreRegisterChartDataClass(classname) ILVPREDEFINECLASSINFOMEMBERS(classname)

// Add for a problem of compatibility with the new charts
#if !defined(__Ilv_Charts_Data_H)
#define IlvChartDataConstructor Ilv31ChartDataConstructor
#define IlvChartDataClassInfo Ilv31ChartDataClassInfo
#define IlvRegisterChartDataClass Ilv31RegisterChartDataClass
#define IlvPreRegisterChartDataClass Ilv31PreRegisterChartDataClass
#define IlvPostRegisterChartDataClass Ilv31PostRegisterChartDataClass
#endif
#if !defined(__Ilv_Charts_Macros_H)
#define IlvPredefinedChartDataIOMembers Ilv31PredefinedChartDataIOMembers
#endif

ILV31VWSMODULEINIT(chart);

#endif /* !__Ilv31_Chart_H */
