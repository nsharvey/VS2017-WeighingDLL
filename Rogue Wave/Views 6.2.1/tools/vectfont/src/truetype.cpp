// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/src/truetype.cpp
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
// Implementation of the TrueType fonts-related classes
// This file is only meaningful for the Windows version
// --------------------------------------------------------------------------

#include <ilviews/util/util.h>
#if defined(WINDOWS)
#include <vfincl/truetype.h>
#if defined(IL_STD)
#include <cmath>
#include <cstring>
#include <iostream>
IL_STDUSE
#else  /* !IL_STD */
#include <math.h>
#include <string.h>
#include <iostream.h>
#endif /* !IL_STD */

ILVDSPEXPORTEDFUNCTION(COLORREF) ILVCALLBACK FgCol(const IlvPalette* pal);
extern "C" ILVDSPEXPORTEDFUNCTION(unsigned long) IlvGetCurrentCharSet();

// --------------------------------------------------------------------------
static DWORD
GetQuality(IlUInt quality)
{
    switch (quality) {
    case IlvDraftFontQuality:
	return DRAFT_QUALITY;
    case IlvProofFontQuality:
	return PROOF_QUALITY;
    }
    return DEFAULT_QUALITY;
}

// --------------------------------------------------------------------------
// IlvVirtualTrueTypeFont member functions
// --------------------------------------------------------------------------
int PASCAL ILVCALLBACK
CheckIfTrueType(LOGFONT*,
		NEWTEXTMETRIC*,
		int flags,
		LPARAM vttf)
{
    if (!(flags & TRUETYPE_FONTTYPE)) {
	((IlvVirtualTrueTypeFont*)vttf)->markAsBad();
	return 1;
    }
    ((IlvVirtualTrueTypeFont*)vttf)->markAsGood();
    return 0;
}

// --------------------------------------------------------------------------
IlvVirtualTrueTypeFont::IlvVirtualTrueTypeFont(const char* name)
    : IlvVirtualVectFont(name, 1, 0)
{
    // Check if this is a TrueType font -----------------
    HDC dc = GetDC(0);
#if defined(WIN32)
    EnumFontFamilies(dc, name, (FONTENUMPROC)CheckIfTrueType, (LPARAM)this);
#else /* !WIN32 */
    EnumFontFamilies(dc, name, (FONTENUMPROC)CheckIfTrueType, (LPSTR)this);
#endif /* WIN32 */
    ReleaseDC(0, dc);
    if (_first > _last)
	markAsBad();
}

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
IlvTrueTypeFont::IlvTrueTypeFont(IlvVirtualTrueTypeFont* font,
				 IlInt                  sizex,
				 IlInt                  sizey,
				 IlFloat                angle,
				 IlvFontStyle            style,
				 IlvFontQuality          quality)
    : IlvVectFont(font, sizex, sizey, angle, (IlFloat)0, style, quality),
      _sx(0.),
      _sy(0.),
      _hFont(0),
      _hFontInit(0),
      _t((IlFloat)2, (IlFloat)0, (IlFloat)0, (IlFloat)2,
	 (IlFloat)0, (IlFloat)0)
      // Note: This is not the identity to force the updateFont to do something.
{
    if (!font)
	return;
    int anglepi  = (int)(angle * 10.); // Must be in thenth of degrees.
    _hFontInit = CreateFont((int)_sizey, (int)_sizex,
    			    -anglepi, -anglepi,
			    (_style&IlvBoldFontStyle)? FW_BOLD: FW_NORMAL,
			    (_style&IlvItalicFontStyle)? TRUE: FALSE,
			    (_style&IlvUnderlinedFontStyle)? TRUE: FALSE,
			    FALSE,
			    IlvGetCurrentCharSet(),
			    OUT_TT_ONLY_PRECIS,
			    CLIP_STROKE_PRECIS|CLIP_TT_ALWAYS,
#if defined(WIN16)
			    (BYTE)
#endif /* WIN16 */
			    GetQuality(_quality), 0,
			    _font->getName());
    updateHFont(0);
}

// --------------------------------------------------------------------------
IlvTrueTypeFont::~IlvTrueTypeFont()
{
    DeleteObject(_hFontInit);
    DeleteObject(_hFont);
}

// --------------------------------------------------------------------------
double IlvTrueTypeFont::_divPI = 572.95;

// --------------------------------------------------------------------------
void
IlvTrueTypeFont::updateHFont(const IlvTransformer* t)
{
    if (!t && _t.isIdentity())
	return;
    if (t && !memcmp(t, &_t, sizeof(IlvTransformer)))
	return;
    if (t)
	_t = *t;
    else
	_t.setValues((IlFloat)1, (IlFloat)0, (IlFloat)0, (IlFloat)1,
		     (IlFloat)0, (IlFloat)0);
    // Compute new parameters
    IlvTransfoParam x11, x12, x21, x22, x0, y0;
    _t.getValues(x11, x12, x21, x22, x0, y0);
    if ((x11 == 0) && (x12 == 0))
	return;
    if (_hFont)
	DeleteObject(_hFont);
    double tangle = atan2((double)x21, (double)x11);
    double tmp = cos(tangle);
    if (fabs(tmp) > 0.0001) {
	_sx = x11 / tmp;
	_sy = x22 / tmp;
    } else {
    	tmp = sin(tangle);
	_sx =  x12 / tmp;
	_sy = -x21 / tmp;
    }
    if (((int)((double)_sizex*_sx)) || ((int)((double)_sizey*_sy))) {
	int angle = (int)(((double)_angle + tangle) * _divPI); // = +- 1800 / Pi
	_drawable = IlTrue;
	_hFont = CreateFont((int)((double)_sizey*_sy),
			    (int)((double)_sizex*_sx),
			    -angle, -angle,
			    (_style&IlvBoldFontStyle)? FW_BOLD : FW_NORMAL,
			    (_style&IlvItalicFontStyle)? TRUE : FALSE,
			    (_style&IlvUnderlinedFontStyle)? TRUE : FALSE,
			    FALSE,
			    IlvGetCurrentCharSet(),
			    OUT_TT_ONLY_PRECIS,
			    CLIP_STROKE_PRECIS|CLIP_TT_ALWAYS,
#if defined(WIN16)
			    (BYTE)
#endif /* WIN16 */
			    GetQuality(_quality),
			    0,
			    _font->getName());
    } else {
	_drawable = IlFalse;
	_hFont = 0;
    }
}

// --------------------------------------------------------------------------
static void
FontSizes(HDC dc,
	  const char* s,
	  int length,
	  HFONT font,
	  int& w,
	  int& h)
{
    HFONT oldfont;
    if (font)
    	oldfont = (HFONT)SelectObject(dc, font);
#if defined(WIN32)
    SIZE size;
    GetTextExtentPoint(dc, s, length, &size);
    w = size.cx;
    h = size.cy;
#else  /* !WIN32 */
    DWORD size = GetTextExtent(dc, s, length);
    w = LOWORD(size);
    h = HIWORD(size) /*+_descent*/;
#endif /* !WIN32 */
    if (font)
    	SelectObject(dc, oldfont);
}

// --------------------------------------------------------------------------
void
IlvTrueTypeFont::drawString(IlvPort*		  port,
			    const IlvPalette*	  pal,
			    const IlvPoint&	  origin,
			    const char*		  text,
			    int			  length,
			    const IlvTransformer* t) const
{
    ((IlvTrueTypeFont*)this)->updateHFont(t);
    IlvDisplay* display = pal->getDisplay();
    HDC hDC = (HDC)display->beginDrawing(ILVDYNAMICCAST(IlvSystemPort*, port),
					 pal,
					 0);
    if (display->getErrorFlag())
	return;
    int w0, h0;
    FontSizes(hDC, text, length, _hFontInit, w0, h0);
    if (_drawable) {
    	int wf, hf;
	FontSizes(hDC, text, length, _hFont, wf, hf);
	if (_sx != 0.0)
	    w0 = IlAbs((int)((double)wf / _sx));
	if (_sy != 0.0)
	    h0 = IlAbs((int)((double)hf / _sy));
    }
    IlvPoint p1;
    IlvPoint p2;
    IlvPoint p3;
    IlvPoint p4;
    if (_sx < 0.0) {
	if (_sy > 0.0) {
	    p1.move(origin.x(),    origin.y()-h0);
	    p2.move(origin.x(),    origin.y());
	    p3.move(origin.x()+w0, origin.y());
	    p4.move(origin.x()+w0, origin.y()-h0);
	}
    } else
	if (_sy < 0.0) {
	    p1.move(origin.x(),    origin.y()-h0);
	    p2.move(origin.x(),    origin.y());
	    p3.move(origin.x()+w0, origin.y());
	    p4.move(origin.x()+w0, origin.y()-h0);
	} else {
	    p1.move(origin.x(),    origin.y());
	    p2.move(origin.x(),    origin.y()-h0);
	    p3.move(origin.x()+w0, origin.y()-h0);
	    p4.move(origin.x()+w0, origin.y());
	}
    if (t) {
    	t->apply(p1);
    	t->apply(p2);
	t->apply(p3);
	t->apply(p4);
    }
    if ((pal->getMode() != IlvModeSet) || !_drawable) {
	HPEN pen = (HPEN)SelectObject(hDC,
				      CreatePen(PS_DOT,
						0,
						FgCol((IlvPalette*)pal)));
	SelectObject(hDC, GetStockObject(NULL_BRUSH));
	POINT points[5];
#define INITPOINT(i, p) points[i].x = (int)p.x(); points[i].y = (int)p.y();
	INITPOINT(0, p1)
	    INITPOINT(1, p2)
	    INITPOINT(2, p3)
	    INITPOINT(3, p4)
	    INITPOINT(4, p1)
	    if (!Polyline(hDC, points, 5))
		((IlvDisplay*)this)->setErrorFlag();
	DeleteObject(SelectObject(hDC, pen));
    } else {
	HFONT oldFont = (HFONT)SelectObject(hDC, _hFont);
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, FgCol((IlvPalette*)pal));
	UINT fMode = SetTextAlign(hDC, TA_BOTTOM|TA_LEFT);
	if (!TextOut(hDC, (int)p1.x(), (int)p1.y(), text, length))
	    ((IlvDisplay*)this)->setErrorFlag();
	SetTextAlign(hDC, fMode);
	SelectObject(hDC, oldFont);
    }
}

// --------------------------------------------------------------------------
void
IlvTrueTypeFont::boundingBox(const IlvPoint&       origin,
			     const char*           text,
			     int                   length,
			     IlvRect&              bbox,
			     const IlvTransformer* t) const
{
    ((IlvTrueTypeFont*)this)->updateHFont(t);
    HDC dc = GetDC(0);
    HFONT oldFont = (HFONT)SelectObject(dc, _hFont);
    int w0, h0;
    FontSizes(dc, text, length, _hFontInit, w0, h0);
    if (_drawable) {
    	int wf, hf;
	FontSizes(dc, text, length, _hFont, wf, hf);
	if (_sx != 0.0)
	    w0 = IlAbs((int)((double)wf / _sx));
	if (_sy != 0.0)
	    h0 = IlAbs((int)((double)hf / _sy));
    }
    IlvPoint p(origin);
    IlvPoint p1(p.x() + w0, p.y());
    IlvPoint p2(p.x(),      p.y() - h0);
    IlvPoint p3(p.x() + w0, p.y() - h0);
    if (t || (_angle != 0)) {
    	IlvTransformer tcur(origin, (IlFloat)(_angle * 180. / 3.1415926));
	if (t)
	    tcur.compose(*t);
    	tcur.apply(p);
    	tcur.apply(p1);
    	tcur.apply(p2);
    	tcur.apply(p3);
    }
    IlvPos xmin,
	   ymin,
	   xmax,
	   ymax;
    xmin = IlMin(IlMin(IlMin( p.x(), p1.x() ), p2.x() ), p3.x() );
    ymin = IlMin(IlMin(IlMin( p.y(), p1.y() ), p2.y() ), p3.y() );
    xmax = IlMax(IlMax(IlMax( p.x(), p1.x() ), p2.x() ), p3.x() );
    ymax = IlMax(IlMax(IlMax( p.y(), p1.y() ), p2.y() ), p3.y() );
    bbox.move(xmin, ymin);
    bbox.resize((IlvDim)(xmax - xmin), (IlvDim)(ymax - ymin));
    SelectObject(dc, oldFont);
    ReleaseDC(0, dc);
}

// --------------------------------------------------------------------------
IlBoolean
IlvTrueTypeFont::contains(const IlvPoint&,
			  const char*,
			  int,
			  const IlvPoint&,
			  const IlvPoint&,
			  const IlvTransformer*) const
{
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
IlvTrueTypeFont::intersects(const IlvPoint&,
			    const char*,
			    int,
			    const IlvRect&,
			    const IlvRect&,
			    const IlvTransformer*) const
{
    return IlTrue;
}

// --------------------------------------------------------------------------
void
IlvTrueTypeFont::loadClass()
{
}

// --------------------------------------------------------------------------
void
IlvTrueTypeFont::write(IlvOutputFile& o) const
{
    const char* sp = " ";
    IlvVectFont::write(o);
    if (_style || _quality) {
	o.getStream() << "F" << _style << sp;
	if (_quality)
	    o.getStream() << "F" << _quality << sp;
    }
}

// --------------------------------------------------------------------------
IlvVectFont*
IlvTrueTypeFont::read(IlvInputFile& is,
		      IlvVirtualTrueTypeFont* vfont)
{
    IlInt sizex, sizey;
    double angle, slant;
    is.getStream() >> sizex >> sizey >> angle >> slant;
    IlUInt style   = 0, quality = 0;
    // For compatibility with old version.
    // Skip all spaces.
    while (is.getStream().peek() == ' ') {
	is.getStream().get();
	if (is.getStream().eof()) {
	    IlvFatalError("Not a Rogue Wave Views data file");
	    return 0;
	}
    }
    if (is.getStream().peek() == 'F') {
	char c;
	is.getStream().get(c);
	is.getStream() >> style;
	while (is.getStream().peek() == ' ') {
	    is.getStream().get();
	    if (is.getStream().eof()) {
		IlvFatalError("Not a Rogue Wave Views data file");
		return 0;
	    }
	}
	if (is.getStream().peek() == 'F') {
	    is.getStream().get(c);
	    is.getStream() >> quality;
	}
    }
    IlFloat angle2 = (IlFloat)angle; // For MSVC4
    IlvVectFont* font = vfont->findVectFont(sizex,  sizey,
					    angle2, (IlFloat)0,
					    (IlvFontStyle)style,
					    (IlvFontQuality)quality);
    if (font)
	return font;
    return new IlvTrueTypeFont(vfont, sizex, sizey, angle2,
			       (IlvFontStyle)style, (IlvFontQuality)quality);
}
#endif /* WINDOWS */
