// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/src/vect.cpp
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
// Implementation of the IlvVirtualVectFont and IlvVectFont classes
// --------------------------------------------------------------------------
#include <vfincl/vect.h>
#include <ilviews/util/util.h>
#include <vfincl/vfhash.h>
#if defined(IL_STD)
#include <cstring>
#include <iostream>
#include <cmath>
#include <cstdarg>
IL_STDUSE
#else  /* !IL_STD */
#include <string.h>
#include <iostream.h>
#include <math.h>
#include <stdarg.h>
#endif /* !IL_STD */
#if defined(WINDOWS)
#include <vfincl/truetype.h>
#endif /* WINDOWS */

// --------------------------------------------------------------------------
// IlvVirtualVectFont member functions
// --------------------------------------------------------------------------
IlvVectCharDesc*    IlvVirtualVectFont::_nullchar     = 0;

IlvStringHashTable* IlvVirtualVectFont::_allvirtualvectfonts = 0;

// --------------------------------------------------------------------------
ILVEXPORTEDDEF(IlvStringHashTable*)
IlvAllVirtualVectFonts()
{
    return IlvVirtualVectFont::getAllVectFonts();
}

// --------------------------------------------------------------------------
ILVEXPORTEDDEF(IlvVirtualVectFont*)
IlvGetVirtualVectFont(const char* fontname)
{
    IlvStringHashTable* allvectfonts = IlvVirtualVectFont::getAllVectFonts();
    return (allvectfonts) ?
      (IlvVirtualVectFont*)allvectfonts->find((char*)fontname) : 0;
}

// --------------------------------------------------------------------------
IlvVirtualVectFont::IlvVirtualVectFont(const char*	name,
				       IlUShort		first,
				       IlUShort		last,
				       ...)
    : _first(first),
      _last(last),
      _refcount(0)
{
    if (!_allvirtualvectfonts)
	_allvirtualvectfonts = new IlvStringHashTable(17);
    _allvectfonts = new IlvVectFontHashTable(17);
    if (!_nullchar)
	_nullchar     = new IlvStrokeCharDesc(0, 0);
    _name = new char [strlen(name) + 1];
    strcpy(_name, name);
    if (last >= first) {
	va_list list;
	va_start(list, last);
	_chars = new IlvVectCharDesc* [last - first + 1];
	for (IlUShort loop = first; loop < last; ++loop) {
	    IlvVectCharDesc* chardesc = va_arg(list, IlvVectCharDesc*);
	    if (!chardesc)
		IlvWarning("IlvVirtualVectFont: Null char [%d]",loop);
	    _chars[loop] = chardesc;
	}
	va_end(list);
    } else
	_chars = 0;
    _allvirtualvectfonts->insert((char*)_name, this);
}

// --------------------------------------------------------------------------
IlvVirtualVectFont::IlvVirtualVectFont(const char* name)
    : _first(0),
      _last(255),
      _refcount(0)
{
    if (!_allvirtualvectfonts)
	_allvirtualvectfonts = new IlvStringHashTable(17);
    _allvectfonts = new IlvVectFontHashTable(17);
    if (!_nullchar)
	_nullchar     = new IlvStrokeCharDesc(0, 0);
    _name = new char [strlen(name) + 1];
    strcpy(_name, name);
    _chars = new IlvVectCharDesc* [256];
    for (IlUInt loop = 0; loop < 256; ++loop)
	_chars[loop] = _nullchar;
    _allvirtualvectfonts->insert((char*)_name, this);
}

// --------------------------------------------------------------------------
IlvVirtualVectFont::~IlvVirtualVectFont()
{
    delete _allvectfonts;
    _allvirtualvectfonts->remove(_name);
    delete [] _chars;
    if (!_allvirtualvectfonts->getLength()) {
	delete _allvirtualvectfonts;
	_allvirtualvectfonts = 0;
	delete _nullchar;
	_nullchar = 0;
    }
    delete [] _name;
}

// --------------------------------------------------------------------------
void
IlvVirtualVectFont::computeWidths()
{
    for (IlUShort i = 0; i < (IlUShort)(_last - _first + 1); ++i)
	_chars[i]->computeWidth();
}

// --------------------------------------------------------------------------
void
IlvVirtualVectFont::setCharDesc(IlUShort which,
				IlvVectCharDesc* desc)
{
    if ((which >= _first) && (which <= _last)) {
	if (_chars[which] != _nullchar)
	    delete _chars[which];
	_chars[which] = desc;
    }
}

// --------------------------------------------------------------------------
#define FSIZE 22

#define MapOnString(__o, __s, __l, __x, __y, __a, __i, __t, __f)\
{\
    if (__l < 0)\
	__l = IL_CAST(int, strlen(text));\
    IlFloat cosangle = (IlFloat)cos(__a) / FSIZE;\
    IlFloat sinangle = (IlFloat)sin(__a) / FSIZE;\
    IlFloat tanslant = (IlFloat)((cos(__i) != 0.0)?(sin(__i) / cos(__i)):0);\
    IlvPoint orig(__o);\
    IlvPoint zero(0, 0);\
    if (__t)\
	 __t->apply(zero);\
    for (int loop = 0; loop < __l; ++loop) {\
	if (((IlUShort)__s[loop]>=_first) && ((IlUShort)__s[loop]<=_last)) {\
	    IlvVectCharDesc* desc = _chars[__s[loop]];\
	    {__f}\
	    orig.translate((IlvPos)(desc->getWidth() * __x * cosangle),\
			   (IlvPos)(desc->getWidth() * __y * sinangle));\
	}\
    }\
}

// --------------------------------------------------------------------------
void
IlvVirtualVectFont::drawString(IlvPort*			dst,
			       IlvPalette const*	palette,
			       IlvPoint const&		origin,
			       char const*		text,
			       int			length,
			       IlInt			sizex,
			       IlInt			sizey,
			       IlFloat			angle,
			       IlFloat			slant,
			       IlvTransformer const*	t) const
{
    MapOnString(origin, text, length, sizex, sizey, angle, slant, t,
		desc->draw(dst,
			   palette,
			   orig,
			   sizex,
			   sizey,
			   cosangle,
			   sinangle,
			   tanslant,
			   t);
		);
}

// --------------------------------------------------------------------------
void
IlvVirtualVectFont::boundingBox(IlvPoint const&		origin,
				char const*		text,
				int			length,
				IlInt			sizex,
				IlInt			sizey,
				IlFloat			angle,
				IlFloat			slant,
				IlvRect&		bbox,
				IlvTransformer const*	t) const
{
    bbox.move(0, 0);
    bbox.resize(0, 0);
    IlvRect rect;
    MapOnString(origin, text, length, sizex, sizey, angle, slant, t,
		desc->boundingBox(orig,
				  sizex,
				  sizey,
				  cosangle,
				  sinangle,
				  tanslant,
				  rect,
				  t);
		bbox.add(rect);
		);
}

// --------------------------------------------------------------------------
IlBoolean
IlvVirtualVectFont::contains(const IlvPoint&		origin,
			     char const*		text,
			     int			length,
			     IlInt			sizex,
			     IlInt			sizey,
			     IlFloat			angle,
			     IlFloat			slant,
			     IlvPoint const&		p,
			     IlvPoint const&		tp,
			     IlvTransformer const*	t) const
{
    MapOnString(origin, text, length, sizex, sizey, angle, slant, t,
		if (desc->contains(orig,
				   sizex,
				   sizey,
				   cosangle,
				   sinangle,
				   tanslant,
				   p,
				   tp,
				   t))
		    return IlTrue;
		);
    return IlFalse;
}

// --------------------------------------------------------------------------
IlBoolean
IlvVirtualVectFont::intersects(IlvPoint const&		origin,
			       char const*		text,
			       int			length,
			       IlInt			sizex,
			       IlInt			sizey,
			       IlFloat			angle,
			       IlFloat			slant,
			       IlvRect const&		rect,
			       IlvRect const&		trect,
			       IlvTransformer const*	t) const
{
    MapOnString(origin, text, length, sizex, sizey, angle, slant, t,
		if (desc->intersects(orig,
				     sizex,
				     sizey,
				     cosangle,
				     sinangle,
				     tanslant,
				     rect,
				     trect,
				     t))
		    return IlTrue;
		);
    return IlFalse;
}

// --------------------------------------------------------------------------
// IlvVectFont member functions
// --------------------------------------------------------------------------
IlvVectFont::~IlvVectFont()
{
    _font->hashRemove(this);
    _font->unLock();
}

// --------------------------------------------------------------------------
void
IlvVectFont::drawString(IlvPort* dst, const IlvPalette* palette,
			const IlvPoint& origin,
			const char* text, int length,
			const IlvTransformer* t) const
{
    _font->drawString(dst, palette, origin, text, length,
		      _sizex, _sizey, _angle, _slant, t);
}

// --------------------------------------------------------------------------
void
IlvVectFont::boundingBox(const IlvPoint& origin,
			 const char* text, int length,
			 IlvRect& bbox,
			 const IlvTransformer* t) const
{
    _font->boundingBox(origin, text, length, _sizex, _sizey, _angle, _slant,
		       bbox, t);
}

// --------------------------------------------------------------------------
IlBoolean
IlvVectFont::contains(const IlvPoint& origin,
		      const char* text, int length,
		      const IlvPoint& p, const IlvPoint& tp,
		      const IlvTransformer* t) const
{
    return _font->contains(origin, text, length,
			   _sizex, _sizey, _angle, _slant,
			   p, tp, t);
}

// --------------------------------------------------------------------------
IlBoolean
IlvVectFont::intersects(const IlvPoint& origin,
			const char* text, int length,
			const IlvRect& rect,
			const IlvRect& trect, const IlvTransformer* t) const
{
    return _font->intersects(origin, text, length,
			     _sizex, _sizey, _angle, _slant,
			     rect, trect, t);
}

// --------------------------------------------------------------------------
void
IlvVectFont::write(IlvOutputFile& o) const
{
    const char* sp = " ";
    IlvWriteString(o.getStream(), _font->getName());
    o.getStream() << sp << _sizex << sp << _sizey << sp <<
	(double)_angle*180./IlvPi << sp << (double)_slant*180./IlvPi << sp;
}

// --------------------------------------------------------------------------
IlvVectFont*
IlvVectFont::read(IlvInputFile& is)
{
    char* buffer = IlvReadString(is.getStream());
    IlvVirtualVectFont* vfont = IlvGetVirtualVectFont(buffer);
    if (!vfont) {
#if defined(WINDOWS)
    	vfont = new IlvVirtualTrueTypeFont(buffer);
	if (((IlvVirtualTrueTypeFont*)vfont)->isBad()) {
	    delete vfont;
	    IlvWarning("Font '%s' not found", buffer);
	    return 0;
	}
#else  /* !WINDOWS */
	IlvWarning("Font '%s' not found", buffer);
	return 0;
#endif /* !WINDOWS */
    }
#if defined(WINDOWS)
    if (vfont->isTrueType())
	return IlvTrueTypeFont::read(is, (IlvVirtualTrueTypeFont*)vfont);
#endif /* WINDOWS */
    IlInt sizex, sizey;
    double angle, slant;
    is.getStream() >> sizex >> sizey >> angle >> slant;
    IlvVectFont* font =
	vfont->findVectFont(sizex, sizey, (IlFloat)angle, (IlFloat)slant);
    if (font)
	return font;
    return new IlvVectFont(vfont, sizex, sizey, (IlFloat)angle, (IlFloat)slant);
}
