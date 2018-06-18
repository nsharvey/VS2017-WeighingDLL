// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/vfincl/truetype.h
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
// Declaration of the TrueType implementation of vectorial fonts on Windows.
// --------------------------------------------------------------------------

#ifndef __Ilv_Vectfont_Truetype_H
#define __Ilv_Vectfont_Truetype_H

#if defined(WINDOWS)
#include <windows.h>
#if !defined(__Ilv_Vectfont_Vect_H)
#include <vfincl/vect.h>
#endif

// --------------------------------------------------------------------------
class ILVVFEXPORTED IlvVirtualTrueTypeFont
: public IlvVirtualVectFont
{
public:
    IlvVirtualTrueTypeFont(const char* fontname);
    // ____________________________________________________________
    void       markAsGood() { _first = 0; _last = 1; }
    void       markAsBad()  { _first = 0; _last = 0; }
    IlBoolean isBad() { return (IlBoolean)(_last == _first); }
    virtual IlBoolean isTrueType() const { return IlTrue; }
};

// --------------------------------------------------------------------------
class ILVVFEXPORTED IlvTrueTypeFont
: public IlvVectFont
{
public:
    IlvTrueTypeFont(IlvVirtualTrueTypeFont* font,
		    IlInt                   sizex,
		    IlInt                   sizey,
		    IlFloat                 angle,
		    IlvFontStyle	    style   = IlvNormalFontStyle,
		    IlvFontQuality	    quality = IlvDefaultFontQuality);
    virtual ~IlvTrueTypeFont();
    // ____________________________________________________________
    virtual void drawString(IlvPort* port, const IlvPalette* pal,
			    const IlvPoint& origin,
			    const char* text, int length,
			    const IlvTransformer* t = 0) const;
    virtual void boundingBox(const IlvPoint& origin,
			     const char* text, int length,
			     IlvRect& bbox,
			     const IlvTransformer* t = 0) const;
    // ____________________________________________________________
    virtual IlBoolean contains(const IlvPoint& origin,
			       const char*, int,
			       const IlvPoint&, const IlvPoint&,
			       const IlvTransformer* t) const;
    virtual IlBoolean intersects(const IlvPoint& origin,
				 const char*, int,
				 const IlvRect&, const IlvRect&,
				 const IlvTransformer*) const;
    virtual void write(IlvOutputFile&) const;
    static IlvVectFont* read(IlvInputFile&, IlvVirtualTrueTypeFont*);
    static void loadClass();
protected:
    static double  _divPI;
    double	   _sx;
    double	   _sy;
    HFONT          _hFont, _hFontInit;
    IlvTransformer _t;
    void updateHFont(const IlvTransformer* t);
private:
    IlBoolean     _drawable;
};

#endif /* WINDOWS */

#endif /* __Ilv_Vectfont_Truetype_H */
