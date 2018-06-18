// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/src/vectlab.cpp
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
// Definition of the IlvVectLabel class
// --------------------------------------------------------------------------
#include <vfincl/vectlab.h>
#if defined(IL_STD)
#include <cstring>
#include <iostream>
IL_STDUSE
#else  /* !IL_STD */
#include <string.h>
#include <iostream.h>
#endif /* !IL_STD */

#define EXACT

// --------------------------------------------------------------------------
IlvVectLabel::IlvVectLabel(IlvDisplay*         display,
			   IlvVectFont*        font,
			   const IlvPoint&     position,
			   const char*         label,
			   IlvPalette*         palette)
: IlvSimpleGraphic(display, palette),
  _font(font),
  _bbox(),
  _transformer(0),
#if defined (WINDOWS)
  _tbbox(),
  _tt(),
#endif /* WINDOWS */
  _position(position),
  _label(0),
  _length(IL_CAST(unsigned int, strlen(label)))
{
    _font->lock();
    _label = strcpy(new char[_length+1], label);
    computeBBox();
}

// --------------------------------------------------------------------------
IlvVectLabel::~IlvVectLabel()
{
    delete [] _label;
    delete _transformer;
    _font->unLock();
}

// --------------------------------------------------------------------------
void
IlvVectLabel::setLabel(const char* label)
{
    int length = IL_CAST(int, strlen(label));
    if (length > (int)_length) {
	delete [] _label;
	_label = new char[strlen(label)+1];
    }
    strcpy(_label, label);
    _length = length;
    computeBBox();
}

// --------------------------------------------------------------------------
void
IlvVectLabel::computeBBox()
{
    _font->boundingBox(_position, _label, _length, _bbox, _transformer);
#if defined(WINDOWS) && defined(EXACT)
    _tbbox.w(0);
    _tt.setValues((IlvTransfoParam)1, (IlvTransfoParam)0,
		  (IlvTransfoParam)0, (IlvTransfoParam)1,
		  (IlvTransfoParam)0, (IlvTransfoParam)0);
#endif /* WINDOWS && EXACT */
}

// --------------------------------------------------------------------------
void
IlvVectLabel::boundingBox(IlvRect& rect, const IlvTransformer* t) const
{
#if defined(WINDOWS) && defined(EXACT)
    if (_font->getVirtualFont()->isTrueType() && t && !t->isTranslation()) {
	if (!_tbbox.w() || memcmp(t, &_tt, sizeof(IlvTransformer))) {
	    IlvTransfoParam t11, t12, t21, t22, tt11, tt12, tt21, tt22;
	    t->getValues(t11, t12, t21, t22);
	    _tt.getValues(tt11, tt12, tt21, tt22);
	    if (((t11!=tt11) ||
		 (t12!=tt12) ||
		 (t21!=tt21) ||
		 (t22!=t22)) ||
		!_tbbox.w())
		if (_transformer) {
		    IlvTransformer tt(*_transformer);
		    tt.compose(*t);
		    _font->boundingBox(_position,
				       _label,
				       _length,
				       ((IlvVectLabel*)this)->_tbbox,
				       &tt);
		} else
		    _font->boundingBox(_position,
				       _label,
				       _length,
				       ((IlvVectLabel*)this)->_tbbox,
				       t);
	    else {
		t->getValues(t11, t22);
		_tt.getValues(tt11, tt22);
		((IlvVectLabel*)this)->_tbbox.translate((IlvPos)(t11 - tt11),
							(IlvPos)(t22 - tt22));
	    }
	    ((IlvVectLabel*)this)->_tt = *t;
	}
	rect = _tbbox;
	return;
    }
#endif /* WINDOWS && EXACT */
    rect = _bbox;
    if (t)
	t->apply(rect);
}

// --------------------------------------------------------------------------
void
IlvVectLabel::applyTransform(const IlvTransformer* t)
{
    if (_transformer)
	_transformer->compose(*t);
    else {
#if defined(sgi)
	_transformer = new IlvTransformer();
	*_transformer = *t;
#else  /* sgi */
	_transformer = new IlvTransformer(*t);
#endif /* sgi */
    }
    if (_transformer->isIdentity()) {
	delete _transformer;
	_transformer = 0;
    }
    computeBBox();
}

// --------------------------------------------------------------------------
void
IlvVectLabel::scale(IlFloat scalex, IlFloat scaley)
{
   IlvTransfoParam x0 = _bbox.x()*(1 - (IlvTransfoParam)scalex),
                   y0 = _bbox.y()*(1 - (IlvTransfoParam)scaley);
   if (_transformer) {
       IlvTransformer t((IlvTransfoParam)scalex, (IlvTransfoParam)0,
			(IlvTransfoParam)0, (IlvTransfoParam)scaley,
			x0, y0);
       _transformer->compose(t);
   } else
       _transformer = new IlvTransformer((IlvTransfoParam)scalex,
					 (IlvTransfoParam)0,
					 (IlvTransfoParam)0,
					 (IlvTransfoParam)scaley,
					 x0, y0);
   if (_transformer->isIdentity()) {
       delete _transformer;
       _transformer = 0;
   }
   computeBBox();
}

// --------------------------------------------------------------------------
IlBoolean
IlvVectLabel::contains(const IlvPoint&       p,
#if defined(WINDOWS) && defined(EXACT)
		       const IlvPoint&       tp,
		       const IlvTransformer* t
#else  /* !WINDOWS || !EXACT */
		       const IlvPoint& tp,
		       const IlvTransformer* t
#endif /* !WINDOWS || !EXACT */
		       ) const
{
#if defined(WINDOWS) && defined(EXACT)
    if (_bbox.contains(p)) {
	if (_font->getVirtualFont()->isTrueType() && t && !t->isTranslation()){
	    if (!_tbbox.w() || memcmp(t, &_tt, sizeof(IlvTransformer))) {
		IlvTransfoParam t11, t12, t21, t22, tt11, tt12, tt21, tt22;
		t->getValues(t11, t12, t21, t22);
		_tt.getValues(tt11, tt12, tt21, tt22);
		if (((t11!=tt11) || (t12!=tt12) || (t21!=tt21) || (t22!=t22))
		    || !_tbbox.w())
		    if (_transformer) {
			IlvTransformer tt(*_transformer);
			tt.compose(*t);
			_font->boundingBox(_position,
					   _label,
					   _length,
					   ((IlvVectLabel*)this)->_tbbox,
					   &tt);
		    } else
			_font->boundingBox(_position,
					   _label,
					   _length,
					   ((IlvVectLabel*)this)->_tbbox,
					   t);
		else {
		    t->getValues(t11, t22);
		    _tt.getValues(tt11, tt22);
		    ((IlvVectLabel*)this)->
		      _tbbox.translate((IlvPos)(t11-tt11), (IlvPos)(t22-tt22));
		}
		((IlvVectLabel*)this)->_tt = *t;
	    }
	    return _tbbox.contains(tp);
	} else
	    return IlTrue;
    } else
	return IlFalse;
#else  /* !WINDOWS || !EXACT */
    IlvRect r;
    boundingBox(r, t);
    return r.contains(tp);
#endif /* !WINDOWS || !EXACT */
}

// --------------------------------------------------------------------------
void
IlvVectLabel::translate(IlvPos dx, IlvPos dy)
{
    if (_transformer) {
	IlvTransfoParam x0, y0;
	_transformer->getValues(x0, y0);
	x0 += (IlvTransfoParam)dx;
	y0 += (IlvTransfoParam)dy;
	_transformer->setValues(x0, y0);
    } else
	_position.translate(dx, dy);
    _bbox.translate(dx, dy);
#if defined(WINDOWS) && defined(EXACT)
    _tbbox.w(0);
#endif /* WINDOWS && EXACT */
}

// --------------------------------------------------------------------------
void
IlvVectLabel::draw(IlvPort*		 dst,
		   const IlvTransformer* t,
		   const IlvRegion*	 clip) const
{
    IlvPushClip pushClip(*_palette, clip);
    if (t) {
	if (_transformer) {
	    IlvTransformer tt(*_transformer);
	    tt.compose(*t);
	    _font->drawString(dst, _palette, _position, _label, _length, &tt);
	} else
	    _font->drawString(dst, _palette, _position, _label, _length, t);
    } else
	_font->drawString(dst,_palette,_position,_label,_length,_transformer);
}

// --------------------------------------------------------------------------
void
IlvVectLabel::write(IlvOutputFile& o) const
{
    o.getStream() << _position << " ";
    IlvWriteString(o.getStream(), _label);
    o.getStream() << " ";
    if (_transformer)
	o.getStream() << *_transformer << " ";
    else
	o.getStream() << "1 0 0 1 0 0 ";
    _font->write(o);
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvVectLabel::read(IlvInputFile& is, IlvPalette* palette)
{
    IlvPoint position;
    is.getStream() >> position;
    char* buffer = IlvReadString(is.getStream());
    char* label = strcpy(new char[strlen(buffer)+1], buffer);
    IlvTransformer t;
    is.getStream() >> t;
    IlvVectFont* font = IlvVectFont::read(is);
    if (!font)
	return 0;
    IlvVectLabel* vlabel = new IlvVectLabel(palette->getDisplay(),
					    font,
					    position,
					    label,
					    palette);
    delete [] label;
    if (!t.isIdentity())
	vlabel->applyTransform(&t);
    return vlabel;
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvVectLabel::copy() const
{
    IlvVectLabel* vlabel = new IlvVectLabel(getDisplay(),
					    _font,
					    _position,
					    _label,
					    getPalette());
    if (_transformer)
	vlabel->applyTransform(_transformer);
    return vlabel;
}

// --------------------------------------------------------------------------
#if defined(linux) || defined(__TCPLUSPLUS__)
IlvPreRegisterClass(IlvVectLabel);
static int initIlvVectLabel()
{ IlvPostRegisterClass(IlvVectLabel, IlvSimpleGraphic); return 0; }
static int _initIlvVectLabel = initIlvVectLabel();
#else  /* !linux */
IlvRegisterClass(IlvVectLabel, IlvSimpleGraphic);
#endif /* !linux */
