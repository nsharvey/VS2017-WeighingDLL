// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/pyrrect.cpp
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
//
// --------------------------------------------------------------------------
#include <ilviews/pyrrect.h>
#include <ilviews/util/util.h>

#if defined(ILVSTD)
#include <iostream>
#include <cstring>
#else  /* !ILVSTD */
#include <iostream.h>
#include <string.h>
#endif /* ILVSTD */

ILVSTDUSE

static IlvPoint _pyrpgon[4];

// --------------------------------------------------------------------------
IlvPyramidRectangle::IlvPyramidRectangle(IlvDisplay*     display,
					 const IlvRect&  rect,
					 const IlvPoint& point,
					 IlvPalette*     palette)
: IlvSimpleGraphic(display, palette), _rect(rect), _point(point)
{
    _rectpalette = 0;
    _edgespalette = 0;
    computePalettes();
}

// --------------------------------------------------------------------------
IlvPyramidRectangle::~IlvPyramidRectangle()
{
    _edgespalette->unLock();
    _rectpalette->unLock();
}

// --------------------------------------------------------------------------
void
IlvPyramidRectangle::computePalettes()
{
    IlvPalette*  newpalette =
	getDisplay()->getPalette(_palette->getForeground(),
				 _palette->getBackground(),
				 _palette->getPattern(),
				 _palette->getColorPattern(),
				 _palette->getFont(),
				 _palette->getLineStyle(),
				 _palette->getLineWidth(),
				 _palette->getFillStyle(),
				 _palette->getArcMode(),
				 _palette->getFillRule(),
				 IlvFullIntensity,
				 IlvDefaultAntialiasingMode,
				 _palette->getGradientPattern());
    newpalette->lock();
    if (_rectpalette)
	_rectpalette->unLock();
    _rectpalette = newpalette;
    newpalette =
	getDisplay()->getPalette(_palette->getBackground(),
				 _palette->getForeground(),
				 getDisplay()->grayPattern(),
				 _palette->getColorPattern(),
				 _palette->getFont(),
				 _palette->getLineStyle(),
				 _palette->getLineWidth(),
				 IlvFillMaskPattern,
				 _palette->getArcMode(),
				 _palette->getFillRule(),
				 IlvFullIntensity,
				 IlvDefaultAntialiasingMode,
				 _palette->getGradientPattern());
    newpalette->lock();
    if (_edgespalette)
	_edgespalette->unLock();
    _edgespalette = newpalette;
}

// --------------------------------------------------------------------------
void
IlvPyramidRectangle::setForeground(IlvColor* fg)
{
    IlvSimpleGraphic::setForeground(fg);
    computePalettes();
}

// --------------------------------------------------------------------------
void
IlvPyramidRectangle::setBackground(IlvColor* bg)
{
    IlvSimpleGraphic::setBackground(bg);
    computePalettes();
}

// --------------------------------------------------------------------------
void
IlvPyramidRectangle::setFont(IlvFont* font)
{
    IlvSimpleGraphic::setFont(font);
    computePalettes();
}

// --------------------------------------------------------------------------
void
IlvPyramidRectangle::setMode(IlvDrawMode m)
{
    IlvSimpleGraphic::setMode(m);
    _edgespalette->setMode(m);
    _rectpalette->setMode(m);
}

// --------------------------------------------------------------------------
void
IlvPyramidRectangle::setOverwrite(IlvBoolean m)
{
    IlvSimpleGraphic::setOverwrite(m);
    _edgespalette->setOverwrite(m);
    _rectpalette->setOverwrite(m);
}

// --------------------------------------------------------------------------
IlvPosition
IlvPyramidRectangle::locatePoint(const IlvRect& r, const IlvPoint& p)const
{
    if (p.x() < r.x()) {          // Point at left of rangle
	if (p.y() < r.y())            return IlvTopLeft;
	else if (p.y() >= r.bottom()) return IlvBottomLeft;
	else                          return IlvLeft;
    } else
	if (p.x() >= r.right()) { // Point at right of rangle
	    if (p.y() < r.y())            return IlvTopRight;
	    else if(p.y() >= r.bottom()) return IlvBottomRight;
	    else                         return IlvRight;
	} else {                          // Point over or under rangle
	    if (p.y() < r.y())            return IlvTop;
	    else if(p.y() >= r.bottom()) return IlvBottom;
	    else                         return IlvCenter;
	}
}

// --------------------------------------------------------------------------
int
IlvPyramidRectangle::createPolygon(const IlvRect& r, const IlvPoint& p)const
{
    _pyrpgon[0] = p;
    IlvPoint ptl(r.x(),       r.y()),
            pbl(r.x(),       r.bottom()-1),
            ptr(r.right()-1, r.y()),
            pbr(r.right()-1, r.bottom()-1);
    switch (locatePoint(r, p)) {
    case IlvTopLeft:
	_pyrpgon[1] = ptr; _pyrpgon[2] = ptl; _pyrpgon[3] = pbl; return 4;
    case IlvLeft:
	_pyrpgon[1] = ptl; _pyrpgon[2] = pbl; return 3;
    case IlvBottomLeft:
	_pyrpgon[1] = ptl; _pyrpgon[2] = pbl; _pyrpgon[3] = pbr; return 4;
    case IlvTop:
	_pyrpgon[1] = ptl; _pyrpgon[2] = ptr; return 3;
    case IlvCenter:
	return 0;
    case IlvBottom:
	_pyrpgon[1] = pbl; _pyrpgon[2] = pbr; return 3;
    case IlvTopRight:
	_pyrpgon[1] = pbr; _pyrpgon[2] = ptr; _pyrpgon[3] = ptl; return 4;
    case IlvRight:
	_pyrpgon[1] = ptr; _pyrpgon[2] = pbr; return 3;
    case IlvBottomRight:
	_pyrpgon[1] = pbl; _pyrpgon[2] = pbr; _pyrpgon[3] = ptr; return 4;
    }
    return 0;
}

// --------------------------------------------------------------------------
void
IlvPyramidRectangle::boundingBox(IlvRect& bbox, const IlvTransformer* t)const
{
    IlvRect  r(_rect);
    IlvPoint p(_point);
    if (t) {
	t->apply(r);
	t->apply(p);
    }
    IlvPos d1x = r.right()  - p.x(),
	   d2x = p.x()      - r.x(),
	   d1y = r.bottom() - p.y(),
	   d2y = p.y()      - r.y();
    switch (locatePoint(r, p)) {
    case IlvTopLeft:
	bbox.move(p.x(), p.y()); bbox.resize((IlvDim)d1x, (IlvDim)d1y); break;
    case IlvLeft:
	bbox.move(p.x(), r.y()); bbox.resize((IlvDim)d1x, r.h());   break;
    case IlvBottomLeft:
	bbox.move(p.x(), r.y()); bbox.resize((IlvDim)d1x, (IlvDim)d2y); break;
    case IlvTop:
	bbox.move(r.x(), p.y()); bbox.resize(r.w(), (IlvDim)d1y);   break;
    case IlvCenter:
	bbox = r;                                                break;
    case IlvBottom:
	bbox.move(r.x(), r.y()); bbox.resize((IlvDim)d1x, (IlvDim)d2y); break;
    case IlvTopRight:
	bbox.move(r.x(), p.y()); bbox.resize((IlvDim)d2x, (IlvDim)d1y); break;
    case IlvRight:
	bbox.move(r.x(), r.y()); bbox.resize((IlvDim)d2x, r.h());   break;
    case IlvBottomRight:
	bbox.move(r.x(), r.y()); bbox.resize((IlvDim)d2x, (IlvDim)d2y); break;
    }
}

// --------------------------------------------------------------------------
void
IlvPyramidRectangle::applyTransform(const IlvTransformer* t)
{
    if (t) {
	t->apply(_rect);
	t->apply(_point);
    }
}

// --------------------------------------------------------------------------
void
IlvPyramidRectangle::internalDraw(IlvPort* dst,
				  const IlvRegion* clip,
				  const IlvRect& r,
				  const IlvPoint& p) const
{
    int n_points = createPolygon(r, p);
    if (clip) {
	_rectpalette->setClip(clip);
	getDisplay()->fillRectangle(dst, _rectpalette, r);
	_rectpalette->setClip();
	_palette->setClip(clip);
	getDisplay()->drawRectangle(dst, _palette, r);
	if (n_points) {
	    _edgespalette->setClip(clip);
	    getDisplay()->fillPolyLine(dst, _edgespalette, n_points, _pyrpgon);
	    _edgespalette->setClip();
	    for (int loop = 1; loop < n_points; loop++)
		getDisplay()->drawLine(dst,
				       _palette,
				       _pyrpgon[0],
				       _pyrpgon[loop]);
	}
	_palette->setClip();
    } else {
	getDisplay()->fillRectangle(dst, _rectpalette, r);
	getDisplay()->drawRectangle(dst, _palette, r);
	if(n_points) {
	    getDisplay()->fillPolyLine(dst, _edgespalette, n_points, _pyrpgon);
	    for (int loop=1; loop < n_points; loop++)
		getDisplay()->drawLine(dst,
				       _palette,
				       _pyrpgon[0],
				       _pyrpgon[loop]);
	}
    }
}

// --------------------------------------------------------------------------
void
IlvPyramidRectangle::draw(IlvPort* dst,
			  const IlvTransformer* t,
			  const IlvRegion* clip)const
{
    IlvRect  tRect  = _rect;
    IlvPoint tPoint = _point;
    if (t) {
	t->apply(tRect);
	t->apply(tPoint);
    }
    internalDraw(dst, clip, tRect, tPoint);
}

// ----------------------------------------------------------------------
void
IlvPyramidRectangle::symmetry(IlvDirection axis)
{
    IlvRect bbox;
    boundingBox(bbox);
    IlvPos dx = bbox.w() & 1,
	   dy = bbox.h() & 1;
    switch (axis) {
    case IlvHorizontalCenter:
	_point.y(2*bbox.centery() - _point.y() + dy);
	_rect.y(2*bbox.centery() - _rect.bottom() + dy);
	break;
    case IlvVerticalCenter:
	_point.x(2*bbox.centerx() - _point.x() + dx);
	_rect.x(2*bbox.centerx() - _rect.right() + dx);
	break;
    case IlvCenter:
	_point.move(2*bbox.centerx() - _point.x() + dx,
		    2*bbox.centery() - _point.y() + dy);
	_rect.move(2*bbox.centerx() - _rect.right() + dx,
		   2*bbox.centery() - _rect.bottom() + dy);
	break;
    }
    if (_rect.x() < bbox.x()) _rect.x(bbox.x());
    if (_rect.y() < bbox.y()) _rect.y(bbox.y());
    if (_point.x() < bbox.x()) _point.x(bbox.x());
    if (_point.y() < bbox.y()) _point.y(bbox.y());
}

// ----------------------------------------------------------------------
IlvBoolean
IlvPyramidRectangle::contains(const IlvPoint& p,
			      const IlvPoint&,
			      const IlvTransformer*) const
{
    if (_rect.contains(p)) return IlvTrue;
    int n_points = createPolygon(_rect, _point);
    return IlvPointInPolygon(p, n_points, _pyrpgon);
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvPyramidRectangle::copy() const
{
    return new IlvPyramidRectangle(_palette->getDisplay(),
				   _rect,
				   _point,
				   _palette);
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvPyramidRectangle::read(IlvInputFile& is, IlvPalette* pal)
{
    IlvRect _rect;
    is.getStream() >> _rect;
    IlvPoint p;
    is.getStream() >> p;
    return new IlvPyramidRectangle(pal->getDisplay(), _rect, p, pal);
}

// --------------------------------------------------------------------------
void
IlvPyramidRectangle::write(IlvOutputFile& f) const
{
    f.getStream() << _rect  << " ";
    f.getStream() << _point << " ";
}

//-------------------------------------------------------------------------
// PyramidLabel
//-------------------------------------------------------------------------

// --------------------------------------------------------------------------
IlvPyramidLabel::IlvPyramidLabel(IlvDisplay*     display,
				 const char*     label,
				 const IlvRect&  rect,
				 const IlvPoint& point,
				 IlvPalette*     palette)
: IlvPyramidRectangle(display, rect, point, palette)
{
    if (label) {
	_label = new char[strlen(label)+1];
	strcpy(_label, label);
    } else
	_label = 0;
}

// --------------------------------------------------------------------------
void
IlvPyramidLabel::draw(IlvPort* dst,
		      const IlvTransformer* t,
		      const IlvRegion* clip) const
{
    IlvPyramidRectangle::draw(dst, t, clip);
    if (_label) {
	if (t) {
	    IlvRect t_rect = _rect;
	    t->apply(t_rect);
	    getDisplay()->drawLabel(dst,
				    _palette,
				    _label,
				    (int)strlen(_label),
				    t_rect,clip);
	} else
	    getDisplay()->drawLabel(dst,
				    _palette,
				    _label,
				    (int)strlen(_label),
				    _rect,
				    clip);
    }
}

// --------------------------------------------------------------------------
void
IlvPyramidLabel::setLabel(const char* label)
{
    if (label) {
	if (strlen(_label) <= strlen(label)) {
	    delete _label;
	    _label = new char[strlen(label)+1];
	}
	strcpy(_label, label);
    } else {
	delete _label;
	_label = 0;
    }
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvPyramidLabel::copy() const
{
    return new IlvPyramidLabel(_palette->getDisplay(),
			       _label, _rect, _point, _palette);
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvPyramidLabel::read(IlvInputFile& is, IlvPalette* pal)
{
    IlvRect _rect;
    is.getStream() >> _rect;
    IlvPoint p;
    is.getStream() >> p;
    char* buffer = IlvReadString(is.getStream());
    return new IlvPyramidLabel(pal->getDisplay(), buffer, _rect, p, pal);
}

// --------------------------------------------------------------------------
void
IlvPyramidLabel::write(IlvOutputFile& f) const
{
    f.getStream() << _rect  << " ";
    f.getStream() << _point << " ";
    IlvWriteString(f.getStream(), _label);
}

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvPreRegisterClass(IlvPyramidRectangle);
IlvPreRegisterClass(IlvPyramidLabel);
ILVDEFINEINITCLASS(pyrrect, IlvRegisterClass2(IlvPyramidRectangle,IlvSimpleGraphic); IlvRegisterClass2(IlvPyramidLabel,IlvPyramidRectangle);)
#else
IlvRegisterClass(IlvPyramidRectangle,IlvSimpleGraphic);
IlvRegisterClass(IlvPyramidLabel,IlvPyramidRectangle);
#endif
