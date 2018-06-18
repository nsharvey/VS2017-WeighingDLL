// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/highlow.cpp
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
// Definition of the IlvChartHighLow (& Data) classes
// --------------------------------------------------------------------------
#include <ilviews/highlow.h>
#include <ilviews/base/memory.h>
#if defined(ILVSTD)
#include <iostream>
using std::endl;
#else  /* !ILVSTD */
#include <iostream.h>
#endif /* !ILVSTD */

// --------------------------------------------------------------------------
// ChartDataHighLow
// --------------------------------------------------------------------------
IlvChartDataHighLow::IlvChartDataHighLow(IlvUInt    count,
					 IlvFloat*  maxPoints,
					 IlvFloat*  minPoints,
					 IlvBoolean owner)
: IlvChartData((IlvFloat)0, (IlvFloat)count, count),
  _ymaxvalues(maxPoints),
  _yminvalues(minPoints),
  _owner(owner)
{
    computeBBox();
}

// --------------------------------------------------------------------------
IlvChartDataHighLow::~IlvChartDataHighLow()
{
    if (_owner) {
	delete  [] _ymaxvalues;
	delete  [] _yminvalues;
    }
}
const char* IlvChartDataHighLow::_className = "IlvChartDataHighLow";

// --------------------------------------------------------------------------
const char*
IlvChartDataHighLow::className() const
{
    return _className;
}

// --------------------------------------------------------------------------
void
IlvChartDataHighLow::setValues(IlvUInt    count,
			       IlvFloat*  maxpoints,
			       IlvFloat*  minpoints,
			       IlvBoolean owner)
{
    _tmin = (IlvFloat)0;
    _tmax = (IlvFloat)count;
    if (_owner && (maxpoints != _ymaxvalues)) {
	delete  [] _ymaxvalues;
	delete  [] _yminvalues;
    }
    _count = count;
    _owner = owner;
    _ymaxvalues = maxpoints;
    _yminvalues = minpoints;
    computeBBox();
}

// --------------------------------------------------------------------------
IlvFloatPoint*
IlvChartDataHighLow::getPoints(const IlvFloatRect& frect,
			       IlvUInt&		   count) const
{
    IlvInt tmin = (IlvInt)(frect.left()) -1;
    IlvInt tmax = (IlvInt)(frect.right()) + 1;
    if (tmin < 0)
	tmin = 0;
    if (tmax >= (IlvInt)_count)
	tmax = _count-1;
    IlMemoryPoolBlock* block;
    IlvFloatPoint* floatpoints =
	IlPoolOf(IlvFloatPoint)::AllocBlock(block, tmax-tmin+1);
    IlvInt x =  tmin;
    for (IlvUInt i = tmin; i <= (IlvUInt)tmax; i++, x++)
	floatpoints[i-tmin].move((IlvFloat)x, _ymaxvalues[i]);
    count = tmax-tmin +1;
    return IlPoolOf(IlvFloatPoint)::ReleaseBlock(block);
}

// --------------------------------------------------------------------------
void
IlvChartDataHighLow::computeBBox()
{
    _ymin = _ymax = _ymaxvalues[0];
    IlvUInt i;
    for (i = 1; i < _count; i++) {
	_ymin = IlvMin(_ymin,_ymaxvalues[i]);
	_ymax = IlvMax(_ymax,_ymaxvalues[i]);
    }
    for (i = 0; i < _count; i++) {
	_ymin = IlvMin(_ymin,_yminvalues[i]);
	_ymax = IlvMax(_ymax,_yminvalues[i]);
    }
}

// --------------------------------------------------------------------------
void
IlvChartDataHighLow::getPoint(IlvUInt num, IlvFloatPoint& p) const
{
    p.move((IlvFloat)num , _ymaxvalues[num]);
}

// --------------------------------------------------------------------------
IlvFloatPoint*
IlvChartDataHighLow::getPoints(IlvUInt& num) const
{
    IlMemoryPoolBlock* block;
    IlvFloatPoint* floatpoints =
	IlPoolOf(IlvFloatPoint)::AllocBlock(block, _count);
    for (IlvUInt i = 0; i < _count; i++)
	floatpoints[i].move((IlvFloat)i , _ymaxvalues[i]);
    num = _count;
    return IlPoolOf(IlvFloatPoint)::ReleaseBlock(block);
}

// --------------------------------------------------------------------------
void
IlvChartDataHighLow::boundingBox(IlvFloatRect& rect) const
{
    rect.left(_tmin); rect.right(_tmax);
    rect.top(_ymin); rect.bottom(_ymax);
}

// --------------------------------------------------------------------------
IlvBoolean
IlvChartDataHighLow::isReadOnly() const
{
    return IlvFalse;
}

// --------------------------------------------------------------------------
void
IlvChartDataHighLow::setPoint(IlvUInt num, const IlvFloatPoint& p)
{
    _ymaxvalues[num] = p.y();
    computeBBox();
}

// --------------------------------------------------------------------------
void
IlvChartDataHighLow::write(IlvOutputFile& out) const
{
    out.getStream() << (long)getCount() << endl;
    IlvUInt i;
    for (i = 0; i < getCount(); i++) {
	out.getStream() << _ymaxvalues[i] << IlvSpc();
	if (!(i % 10))
	    out.getStream() << endl;
    }
    for (i = 0; i < getCount(); i++) {
	out.getStream() << _yminvalues[i] << IlvSpc();
	if (!(i % 10))
	    out.getStream() << endl;
    }
}

// --------------------------------------------------------------------------
IlvChartData*
IlvChartDataHighLow::read(IlvInputFile& in)
{
    long count;
    in.getStream() >> count;
    IlvFloat* fmax = new IlvFloat[count];
    IlvFloat* fmin = new IlvFloat[count];
    IlvInt i;
    for (i = 0; i < count; i++)
	in.getStream() >> fmax[i];
    for (i = 0; i < count; i++)
	in.getStream() >> fmin[i];
    return new IlvChartDataHighLow((IlvUInt)count, fmax, fmin, IlvTrue);
}

// --------------------------------------------------------------------------
IlvChartData*
IlvChartDataHighLow::copy() const
{
    IlvUInt count = getCount();
    IlvFloat* fmax = new IlvFloat[count];
    IlvMemMove(fmax, _ymaxvalues, (unsigned int)(count*sizeof(IlvFloat)));
    IlvFloat* fmin = new IlvFloat[count];
    IlvMemMove(fmin, _yminvalues, (unsigned int)(count*sizeof(IlvFloat)));
    return new IlvChartDataHighLow(count, fmax, fmin, IlvTrue);
}

// --------------------------------------------------------------------------
IlvFloatPoint*
IlvChartDataHighLow::getMinPoints(const IlvFloatRect& frect,
				  IlvUInt&	      count) const
{
    IlvInt tmin = (IlvInt)(frect.left()) -1;
    IlvInt tmax = (IlvInt)(frect.right()) + 1;
    if (tmin < 0)
	tmin = 0;
    if (tmax >= (IlvInt)_count)
	tmax = _count - 1;
    IlMemoryPoolBlock* block;
    IlvFloatPoint* floatpoints =
	IlPoolOf(IlvFloatPoint)::AllocBlock(block, tmax-tmin+1);
    IlvInt x =  tmin;
    for (IlvUInt i = (IlvUInt)tmin; i <= (IlvUInt)tmax; i++, x++)
	floatpoints[i-tmin].move((IlvFloat)x, _yminvalues[i]);
    count = tmax-tmin +1;
    return IlPoolOf(IlvFloatPoint)::ReleaseBlock(block);
}

// --------------------------------------------------------------------------
IlvFloatPoint*
IlvChartDataHighLow::getMinPoints(IlvUInt& num) const
{
    IlMemoryPoolBlock* block;
    IlvFloatPoint* floatpoints =
	IlPoolOf(IlvFloatPoint)::AllocBlock(block, _count);
    for (IlvUInt i = 0; i < _count; i++)
	floatpoints[i].move((IlvFloat)i , _yminvalues[i]);
    num = _count;
    return IlPoolOf(IlvFloatPoint)::ReleaseBlock(block);
}
// --------------------------------------------------------------------------
void
IlvChartDataHighLow::setMinPoint(IlvUInt num, const IlvFloatPoint& p)
{
    _yminvalues[num] = p.y();
    computeBBox();
}

// --------------------------------------------------------------------------
void
IlvChartDataHighLow::getMinPoint(IlvUInt num, IlvFloatPoint& p) const
{
    p.move((IlvFloat)num , _yminvalues[num]);
}

// --------------------------------------------------------------------------
// HighLowChart
// --------------------------------------------------------------------------
void
IlvHighLowChart::draw(IlvPort*		    dst,
		      const IlvTransformer* t,
		      const IlvRegion*	    clip) const
{
    //Get Max and Min Points;
    IlvInt tmin,
	   tmax;
    IlvUInt count = getData()->getCount();
    if (clip) {
	IlvFloatRect frect;
	IlvRect clipRect(clip->boundingBox());
	chartBBox(frect, &clipRect, t);
	tmin = (IlvInt)(frect.left())  - 1;
	tmax = (IlvInt)(frect.right()) + 1;
	if (tmin < 0)
	    tmin = 0;
	if ((IlvUInt)tmax >= count)
	    tmax = count - 1;
    } else {
	tmin = 0;
	tmax = getData()->getCount() - 1;
    }
    if (clip)
	_palette->setClip(clip);
    IlvRect rect;
    IlvDisplay* display = getDisplay();
    IlvPoint top, bottom;
    for (IlvInt i = tmin; i <= tmax; i++) {
	getMinPoint(i, bottom, t);
	getPoint(i, top, t);
	rect.move(top.x()-_size, top.y()-_size);
	rect.resize(2*_size, (IlvDim)IlvAbs(bottom.y()-top.y()));
	display->fillRectangle(dst, _palette, rect);
    }
    if (clip)
	_palette->setClip();
}

// --------------------------------------------------------------------------
void
IlvHighLowChart::getMinPoint(IlvUInt		   num,
			     IlvPoint&		   p,
			     const IlvTransformer* t) const
{
    IlvFloatPoint rp;
    ((IlvChartDataHighLow*)getData())->getMinPoint(num, rp);
    p.move(_origin.x()+(IlvPos)(_scalex*rp.x()),
	   _origin.y()-(IlvPos)(_scaley*rp.y()));
    if (t)
	t->apply(p);
}

// --------------------------------------------------------------------------
void
IlvHighLowChart::setMinPoint(IlvUInt		   num,
			     const IlvPoint&	   p,
			     const IlvTransformer* t)
{
    if (!getData()->isReadOnly()) {
	IlvPoint tp=p;
	if (t)
	    t->inverse(tp);
	((IlvChartDataHighLow*)
	 getData())->setMinPoint(num,
			     IlvFloatPoint((IlvFloat)(tp.x()-_origin.x())/
					   _scalex,
					   (IlvFloat)(_origin.y()-tp.y())/
					   _scaley));
    }
}

// --------------------------------------------------------------------------
void
IlvHighLowChart::bboxPoint(IlvUInt		 num,
			   IlvRect&		 rect,
			   const IlvTransformer* t) const
{
    IlvPoint top,bottom;
    getPoint(num,top,t);
    getMinPoint(num,bottom,t);
    rect.move(top.x()-_size,top.y()-_size);
    rect.resize(2*_size,(IlvDim)IlvAbs(bottom.y()-top.y()));
}

// --------------------------------------------------------------------------
IlvBoolean
IlvHighLowChart::contains(const IlvPoint&,
			  const IlvPoint&	tp,
			  const IlvTransformer* t) const
{
    IlvRect rect;
    for (IlvUInt count = 0; count < getData()->getCount(); count++) {
	bboxPoint(count,rect,t);
	if (rect.contains(tp))
	    return IlvTrue;
    }
    return IlvFalse;
}

// --------------------------------------------------------------------------
void
IlvHighLowChart::boundingBox(IlvRect& rect, const IlvTransformer* t) const
{
    IlvChart::boundingBox(rect, t);
    rect.translate(-(IlvPos)_size, -(IlvPos)_size);
    rect.grow(2*_size, 2*_size);
}

// --------------------------------------------------------------------------
IlvInt
IlvHighLowChart::whichMinPoint(IlvDim		     size,
			       const IlvPoint&,
			       const IlvPoint&	     tp,
			       const IlvTransformer* t) const
{
    IlvPoint point;
    IlvRect rect;
    IlvDim twosize=2*size;
    for (IlvUInt count = 0; count < getData()->getCount(); count++) {
	getMinPoint(count,point,t);
	rect.move(point.x()-size, point.y()-size);
	rect.resize(twosize, twosize);
	if (rect.contains(tp))
	    return count;
    }
    return -1;
}

//Read Write Copy

// --------------------------------------------------------------------------
IlvGraphic*
IlvHighLowChart::copy() const
{
    return new IlvHighLowChart(_palette->getDisplay(),
			       (IlvChartDataHighLow*)getData(),
			       _origin, _scalex, _scaley,
			       _size,_palette);
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvHighLowChart::read(IlvInputFile& is, IlvPalette* palette)
{
    IlvPoint origin;
    IlvFloat scalex, scaley;
    IlvDim size;
    is.getStream() >> size >> origin >> scalex >> scaley ;
    IlvChartData* data = IlvChartDataHighLow::read(is);
    return new IlvHighLowChart(palette->getDisplay(),
			       (IlvChartDataHighLow*)data, origin,
			       scalex, scaley, size,palette);
}

// --------------------------------------------------------------------------
void
IlvHighLowChart::write(IlvOutputFile& os) const
{
    os.getStream() << _size << IlvSpc()
		   << _origin << IlvSpc()
		   << _scalex << IlvSpc()
		   << _scaley << endl;
    getData()->write(os);
}

#if defined(IlvDECLAREINITCLASS)
IlvPreRegisterClass(IlvHighLowChart);
ILVDEFINEINITCLASS(highlow, IlvPostRegisterClass(IlvHighLowChart, IlvChart);)
#else  /* !IlvDECLAREINITCLASS */
IlvRegisterClass(IlvHighLowChart, IlvChart);
#endif /* !IlvDECLAREINITCLASS */
