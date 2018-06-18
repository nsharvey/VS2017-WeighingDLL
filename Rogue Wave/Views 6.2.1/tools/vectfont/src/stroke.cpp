// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/src/stroke.cpp
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
// Implementation of the IlvStrokeCharDesc class
// --------------------------------------------------------------------------

#include <vfincl/vect.h>
#include <ilviews/util/util.h>
#include <stdarg.h>

#if defined(WINDOWS)
#define MINWIDTH 4
#else  /* !WINDOWS */
#define MINWIDTH 1
#endif /* !WINDOWS */

// --------------------------------------------------------------------------
static const IlvPoint&
transformPoint(IlvPos px, IlvPos py,
	       const IlvPoint& orig,
	       IlInt sizex, IlInt sizey,
	       IlFloat cosangle, IlFloat sinangle,
	       IlFloat tanslant)
{
    static IlvPoint pt;
    pt.move((IlvPos)(orig.x()+sizex*(cosangle*px+(tanslant - sinangle)*py)),
	    (IlvPos)(orig.y()+sizey*(sinangle*px+ cosangle            *py)));
    return pt;
}

// --------------------------------------------------------------------------
IlvVectCharDesc::~IlvVectCharDesc()
{
}

// --------------------------------------------------------------------------
// IlvStrokeCharDesc member functions
// --------------------------------------------------------------------------
IlvStrokeCharDesc::IlvStrokeCharDesc(IlvDim width, IlUInt count, ...)
    : IlvVectCharDesc(width),
      _count(count)
{
    if (count) {
	_from = new IlvPoint[count];
	_to   = new IlvPoint[count];
	va_list list;
	va_start(list, count);
	for (IlUInt loop = 0; loop < count; ++loop) {
	    IlvPos x = (IlvPos)(va_arg(list, int)),
		y = (IlvPos)(va_arg(list, int));
	    _from[loop].move(x, y);
	    x = (IlvPos)(va_arg(list, int));
	    y = (IlvPos)(va_arg(list, int));
	    _to[loop].move(x, y);
	}
	va_end(list);
	computeBBox();
    } else {
	_from = _to = 0;
	_bbox.move(0,0);
	_bbox.resize(0,0);
    }
    //computeWidth();
}

// --------------------------------------------------------------------------
IlvStrokeCharDesc::~IlvStrokeCharDesc()
{
    delete [] _to;
    delete [] _from;
}

// --------------------------------------------------------------------------
void
IlvStrokeCharDesc::computeBBox()
{
    IlvPos xmin = IlMin(_from[0].x(), _to[0].x()),
	xmax = IlMax(_from[0].x(), _to[0].x()),
	ymin = IlMin(_from[0].y(), _to[0].y()),
	ymax = IlMax(_from[0].y(), _to[0].y());
    for (IlUInt loop = 1; loop < _count; ++loop) {
	xmin = IlMin(_from[loop].x(), IlMin(_to[loop].x(), xmin));
	xmax = IlMax(_from[loop].x(), IlMax(_to[loop].x(), xmax));
	ymin = IlMin(_from[loop].y(), IlMin(_to[loop].y(), ymin));
	ymax = IlMax(_from[loop].y(), IlMax(_to[loop].y(), ymax));
    }
    _bbox.move(xmin, ymin);
    _bbox.resize((IlvDim)(xmax - xmin), (IlvDim)(ymax - ymin));
}

// --------------------------------------------------------------------------
void
IlvStrokeCharDesc::computeWidth()
{
    if (!_count)
	_width = MINWIDTH;
    else {
	IlvPos xmin = IlMin(_from[0].x(), _to[0].x()),
	    xmax = xmin;
	for (IlUInt i = 1; i < _count; ++i) {
	    xmin = IlMin(IlMin(xmin, _from[i].x()), _to[i].x());
	    xmax = IlMax(IlMax(xmax, _from[i].x()), _to[i].x());
	}
	_width = MINWIDTH + (IlvDim)(xmax - xmin);
    }
}

// --------------------------------------------------------------------------
void
IlvStrokeCharDesc::setData(IlUInt count,
			   IlvPoint* from,
			   IlvPoint* to)
{
    _count = count;
    _from = new IlvPoint[count];
    _to   = new IlvPoint[count];
    for (IlUInt loop = 0; loop < count; ++loop) {
	_from[loop] = from[loop];
	_to[loop]   = to[loop];
    }
    computeBBox();
}

// --------------------------------------------------------------------------
void
IlvStrokeCharDesc::draw(IlvPort* dst, const IlvPalette* palette,
			const IlvPoint& origin,
			IlInt sizex, IlInt sizey,
			IlFloat ca, IlFloat sa, IlFloat ts,
			const IlvTransformer* t) const
{
    for (IlUInt loop = 0; loop < _count; ++loop) {
	IlvPoint from(transformPoint(_from[loop].x(), _from[loop].y(),
				     origin, sizex, sizey, ca, sa, ts)),
	    to(transformPoint(_to[loop].x(), _to[loop].y(),
			      origin, sizex, sizey, ca, sa, ts));
	if (t) {
	    t->apply(from);
	    t->apply(to);
	}
	dst->drawLine(palette, from, to);
    }
}

// --------------------------------------------------------------------------
void
IlvStrokeCharDesc::boundingBox(const IlvPoint& origin,
			       IlInt sizex, IlInt sizey,
			       IlFloat ca, IlFloat sa, IlFloat ts,
			       IlvRect& bbox,
			       const IlvTransformer* t) const
{
    IlvPoint p1(transformPoint(_bbox.left(),  _bbox.bottom(),
			       origin, sizex, sizey, ca, sa, ts)),
	p2(transformPoint(_bbox.right(), _bbox.bottom(),
			  origin, sizex, sizey, ca, sa, ts)),
	p3(transformPoint(_bbox.left(),  _bbox.top(),
			  origin, sizex, sizey, ca, sa, ts)),
	p4(transformPoint(_bbox.right(), _bbox.top(),
			  origin, sizex, sizey, ca, sa, ts));
    // Must apply transformation now, not after !
    if (t) {
	t->apply(p1);
	t->apply(p2);
	t->apply(p3);
	t->apply(p4);
    }
    bbox.move(IlMin(p1.x(), IlMin(p2.x(), IlMin(p3.x(), p4.x()))),
	      IlMin(p1.y(), IlMin(p2.y(), IlMin(p3.y(), p4.y()))));
    bbox.resize((IlvDim)(IlMax(p1.x(), IlMax(p2.x(), IlMax(p3.x(), p4.x())))
			 - bbox.x()),
		(IlvDim)(IlMax(p1.y(), IlMax(p2.y(), IlMax(p3.y(), p4.y())))
			 - bbox.y()));
}

// --------------------------------------------------------------------------
IlBoolean
IlvStrokeCharDesc::contains(const IlvPoint& origin,
			    IlInt sizex, IlInt sizey,
			    IlFloat ca, IlFloat sa, IlFloat ts,
			    const IlvPoint& p, const IlvPoint&,
			    const IlvTransformer*) const
{
    for (IlUInt loop = 0; loop < _count; ++loop) {
	IlvPoint from(transformPoint(_from[loop].x(), _from[loop].y(),
				     origin, sizex, sizey, ca, sa, ts)),
	    to(transformPoint(_to[loop].x(), _to[loop].y(),
			      origin, sizex, sizey, ca, sa, ts));
	if (IlvPointInLine(p, from, to))
	    return IlTrue;
    }
    return IlFalse;
}

// --------------------------------------------------------------------------
IlBoolean
IlvStrokeCharDesc::intersects(const IlvPoint& origin,
			      IlInt sizex, IlInt sizey,
			      IlFloat ca, IlFloat sa, IlFloat ts,
			      const IlvRect& rect, const IlvRect&,
			      const IlvTransformer*) const
{
    IlvRect newrect;
    for (IlUInt loop = 0; loop < _count; ++loop) {
	IlvPoint from(transformPoint(_from[loop].x(), _from[loop].y(),
				     origin, sizex, sizey, ca, sa, ts)),
	    to(transformPoint(_to[loop].x(), _to[loop].y(),
			      origin, sizex, sizey, ca, sa, ts));
	if (from.x() > to.x()) {
	    newrect.x(to.x());
	    newrect.w((IlvDim)(from.x() - to.x()));
	} else {
	    newrect.x(from.x());
	    newrect.w((IlvDim)(to.x() - from.x()));
	}
	if (from.y() > to.y()) {
	    newrect.y(to.y());
	    newrect.h((IlvDim)(from.y() - to.y()));
	} else {
	    newrect.y(from.y());
	    newrect.h((IlvDim)(to.y() - from.y()));
	}
	if (rect.intersects(newrect))
	    return IlTrue;
    }
    return IlFalse;
}
