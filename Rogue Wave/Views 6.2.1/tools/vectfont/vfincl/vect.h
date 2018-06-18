// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/vfincl/vect.h
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
// Declaration of the virtual fonts-related classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Vectfont_Vect_H
#define __Ilv_Vectfont_Vect_H

#if !defined(__Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Graphics_Io_H)
#include <ilviews/graphics/io.h>
#endif
#if !defined(__Ilv_Vectfont_Vfhash_H)
#include <vfincl/vfhash.h>
#endif

class ILVVFEXPORTED IlvVectFont;

typedef enum IlvFontQuality {
    IlvDefaultFontQuality = 0,
    IlvDraftFontQuality,
    IlvProofFontQuality
} _IlvFontQuality;

// --------------------------------------------------------------------------
class ILVVFEXPORTED IlvVectCharDesc
{
public:
    IlvVectCharDesc(IlvDim width) : _width(width) {}
    virtual ~IlvVectCharDesc();
    // ____________________________________________________________
    void setWidth(IlvDim width) { _width = width; }
    virtual void computeWidth() = 0;
    IlvDim getWidth() { if (!_width) computeWidth(); return _width; }
    // ____________________________________________________________
    virtual void draw(IlvPort* dst, const IlvPalette* palette,
		      const IlvPoint& origin,
		      IlInt sizex, IlInt sizey,
		      IlFloat cosangle, IlFloat sinangle, IlFloat tanslant,
		      const IlvTransformer* t = 0) const = 0;
    virtual void boundingBox(const IlvPoint& origin,
			     IlInt sizex, IlInt sizey,
			     IlFloat cosangle, IlFloat sinangle,
			     IlFloat tanslant,
			     IlvRect& bbox,
			     const IlvTransformer* t = 0) const = 0;
    // ____________________________________________________________
    virtual IlBoolean contains(const IlvPoint& origin,
			       IlInt sizex, IlInt sizey,
			       IlFloat cosangle, IlFloat sinangle,
			       IlFloat tanslant,
			       const IlvPoint&, const IlvPoint&,
			       const IlvTransformer*) const = 0;
    virtual IlBoolean intersects(const IlvPoint& origin,
				 IlInt sizex, IlInt sizey,
				 IlFloat cosangle, IlFloat sinangle,
				 IlFloat tanslant,
				 const IlvRect&, const IlvRect&,
				 const IlvTransformer*) const = 0;
 protected:
    IlvDim  _width;
    IlvRect _bbox;
};

// --------------------------------------------------------------------------
class ILVVFEXPORTED IlvStrokeCharDesc
: public IlvVectCharDesc
{
public:
    IlvStrokeCharDesc(IlvDim width, IlUInt count, ...);
    IlvStrokeCharDesc()
	: IlvVectCharDesc(0), _count(0), _from(0), _to(0) {}
    virtual ~IlvStrokeCharDesc();
    // ____________________________________________________________
    virtual void computeWidth();
    IlUInt count() const { return _count; }
    virtual void computeBBox();
    void setData(IlUInt count, IlvPoint* from, IlvPoint* to);
    // ____________________________________________________________
    virtual void draw(IlvPort* dst, const IlvPalette* palette,
		      const IlvPoint& origin,
		      IlInt sizex, IlInt sizey,
		      IlFloat cosangle, IlFloat sinangle,
		      IlFloat tanslant,
		      const IlvTransformer* t = 0) const;
    virtual void boundingBox(const IlvPoint& origin,
			     IlInt sizex, IlInt sizey,
			     IlFloat cosangle, IlFloat sinangle,
			     IlFloat tanslant,
			     IlvRect& bbox,
			     const IlvTransformer* t = 0) const;
    // ____________________________________________________________
    IlBoolean contains(const IlvPoint& origin,
		       IlInt sizex, IlInt sizey,
		       IlFloat cosangle, IlFloat sinangle,
		       IlFloat tanslant,
		       const IlvPoint&, const IlvPoint&,
		       const IlvTransformer*) const;
    IlBoolean intersects(const IlvPoint& origin,
			 IlInt sizex, IlInt sizey,
			 IlFloat cosangle, IlFloat sinangle,
			 IlFloat tanslant,
			 const IlvRect&, const IlvRect&,
			 const IlvTransformer*) const;
 protected:
    IlUInt   _count;
    IlvPoint* _from;
    IlvPoint* _to;
};

// --------------------------------------------------------------------------
// IlvVirtualVectFont
// --------------------------------------------------------------------------
class ILVVFEXPORTED IlvVirtualVectFont
{
public:
    IlvVirtualVectFont(const char* fontname);
    IlvVirtualVectFont(const char* fontname,
		       IlUShort first, IlUShort last, ...);
    virtual ~IlvVirtualVectFont();
#if defined(WINDOWS)
    virtual IlBoolean isTrueType() const { return IlFalse; }
#endif /* WINDOWS */
    // ____________________________________________________________
    void lock()   { _refcount++; }
    void unLock() { _refcount--; if (!_refcount) delete this; }
    void hashInsert(IlvVectFont* f) { _allvectfonts->insert(f); }
    IlBoolean hashRemove(IlvVectFont* f) { return _allvectfonts->remove(f); }
    IlvVectFont* findVectFont(IlInt   sx,
			      IlInt   sy,
			      IlFloat angle,
			      IlFloat slant,
			      IlUInt  style   = 0,
			      IlUInt  quality = 0) {
	return _allvectfonts->findVectFont(sx, sy,
					   angle, slant,
					   style, quality);
    }
    const char* getName() const { return _name; }
    void setCharDesc(IlUShort which, IlvVectCharDesc* desc);
    IlvVectCharDesc* getCharDesc(IlUShort which) {
	return ((which >= _first) && (which <= _last))
	    ? _chars[which-_first] : _nullchar;
    }
    // ____________________________________________________________
    void drawString(IlvPort* dst, const IlvPalette* palette,
		    const IlvPoint& origin,
		    const char* text, int length,
		    IlInt sizex, IlInt sizey,
		    IlFloat angle, IlFloat slant,
		    const IlvTransformer* t = 0) const;
    void boundingBox(const IlvPoint& origin,
		     const char* text, int length,
		     IlInt sizex, IlInt sizey,
		     IlFloat angle, IlFloat slant,
		     IlvRect& bbox, const IlvTransformer* t = 0) const;
    // ____________________________________________________________
    IlBoolean contains(const IlvPoint&, const char*, int,
		       IlInt sizex, IlInt sizey,
		       IlFloat angle, IlFloat slant,
		       const IlvPoint&, const IlvPoint&,
		       const IlvTransformer*) const;
    IlBoolean intersects(const IlvPoint&, const char*, int,
			 IlInt sizex, IlInt sizey,
			 IlFloat angle, IlFloat slant,
			 const IlvRect&, const IlvRect&,
			 const IlvTransformer*) const;
    void computeWidths();
    static IlvStringHashTable* getAllVectFonts() {
	return _allvirtualvectfonts;
    }
protected:
    char*		       _name;
    IlUShort		       _first;
    IlUShort		       _last;
    IlvVectCharDesc**	       _chars;
    static IlvVectCharDesc*    _nullchar;
    static IlvStringHashTable* _allvirtualvectfonts;
    IlvVectFontHashTable*      _allvectfonts;
private:
    IlUInt		       _refcount;
};
extern ILVVFEXPORTEDFUNCTION(IlvVirtualVectFont*)
IlvGetVirtualVectFont(const char*);
extern ILVVFEXPORTEDFUNCTION(IlvStringHashTable*) IlvAllVirtualVectFonts();

#if !defined(IlvPi)
#define IlvPi 3.1416926535
#endif // !IlvPi
// --------------------------------------------------------------------------
class ILVVFEXPORTED IlvVectFont
{
public:
    IlvVectFont(IlvVirtualVectFont* font,
		IlInt              sizex,
		IlInt              sizey,
		IlFloat            angle,
		IlFloat            slant,
		IlUInt		    style   = IlvNormalFontStyle,
		IlUInt		    quality = IlvDefaultFontQuality)
    : _font(font),
      _sizex(sizex),
      _sizey(sizey),
      _angle((IlFloat)(angle * IlvPi / 180.)),
      _slant((IlFloat)(slant * IlvPi / 180.)),
      _style(style),
      _quality(quality),
      _refcount(0)
    {
	_font->lock();
	_font->hashInsert(this);
    }
    virtual ~IlvVectFont();
    // ____________________________________________________________
    IlvVirtualVectFont* getVirtualFont() const { return _font; }
    void getSizes(IlInt& sizex, IlInt& sizey)
	{ sizex = _sizex; sizey = _sizey; }
    IlFloat getAngle() const { return (IlFloat)(_angle * 180. / IlvPi); }
    void     setAngle(IlFloat angle) { _angle = (IlFloat)(angle * IlvPi / 180.); }
    IlFloat getSlant() const { return (IlFloat)(_slant * 180. / IlvPi); }
    void     setSlant(IlFloat slant) { _slant = (IlFloat)(slant * IlvPi / 180.); }
    IlUInt  getQuality() const { return _quality; }
    IlUInt  getStyle()   const { return _style; }
    // ____________________________________________________________
    virtual void drawString(IlvPort*, const IlvPalette*,
			    const IlvPoint& origin,
			    const char* text, int length,
			    const IlvTransformer* = 0) const;
    virtual void boundingBox(const IlvPoint& origin,
			     const char* text, int length,
			     IlvRect& bbox,
			     const IlvTransformer* = 0) const;
    // ____________________________________________________________
    virtual IlBoolean contains(const IlvPoint& origin,
			       const char*, int,
			       const IlvPoint&, const IlvPoint&,
			       const IlvTransformer*) const;
    virtual IlBoolean intersects(const IlvPoint& origin,
				 const char*, int,
				 const IlvRect&, const IlvRect&,
				 const IlvTransformer*) const;
    void lock()   { _refcount++; }
    void unLock() { _refcount--; if (!_refcount) delete this; }
    // ____________________________________________________________
    virtual void write(IlvOutputFile&) const;
    static IlvVectFont* read(IlvInputFile&);
protected:
    IlvVirtualVectFont* _font;
    IlInt              _sizex, _sizey;
    IlFloat            _angle, _slant;
    IlUInt		_style;
    IlUInt		_quality;
private:
    IlUInt		_refcount;
};

#endif /* !__Ilv_VectfonT_Vect_H */
