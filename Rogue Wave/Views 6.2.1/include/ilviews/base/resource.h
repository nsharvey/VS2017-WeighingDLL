// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/resource.h
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
// Declaration of basic IlogViews resource classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Resource_H
#define __Ilv_Base_Resource_H

#if !defined(__Ilv_Base_Region_H)
#  include <ilviews/base/region.h>
#endif

#if !defined(__Il_String_H)
#  include <ilog/string.h>
#endif
class IlvBidiString; // ILVBIDI

enum IlvDrawMode {
    IlvModeSet,
    IlvModeOr,
    IlvModeAnd,
    IlvModeXor,
    IlvModeNot,
    IlvModeInvert,
    IlvModeNotOr,
    IlvModeNotAnd,
    IlvModeNotXor
};

enum IlvFillStyle {
    IlvFillPattern,
    IlvFillMaskPattern,
    IlvFillColorPattern,
    IlvFillGradientPattern
};

enum IlvArcMode {
    IlvArcPie,
    IlvArcChord
};

enum IlvFillRule {
    IlvEvenOddRule,
    IlvWindingRule
};

enum IlvFontStyle {
    IlvNormalFontStyle     = 0,
    IlvBoldFontStyle       = 1,
    IlvUnderlinedFontStyle = 2,
    IlvItalicFontStyle     = 4,
    IlvSystemStyle         = 0x1000
};

typedef IlUShort IlvFontSize;

enum IlvAntialiasingMode {
    IlvDefaultAntialiasingMode	= 0,
    IlvNoAntialiasingMode	= 1,
    IlvUseAntialiasingMode	= 2
};

class IlvDisplay;

class IlvColor;
class IlvFont;
class IlvBitmap;
class IlvPattern;
class IlvColorPattern;
class IlvGradientPattern;
class IlvColorStop;

enum IlvGradientTransformMode {
    IlvGradientTransformGraphic = 0,
    IlvGradientTransformGraphicNoResize,
    IlvGradientNoTransform
};

enum IlvGradientAspectRatio {
    IlvGradientAspectRatioNo = 0,
    IlvGradientAspectRatioInside,
    IlvGradientAspectRatioOutside
};

enum IlvGradientSpread {
    IlvGradientPadSpread = 0,
    IlvGradientRepeatSpread,
    IlvGradientReflectSpread
};

class IlvLineStyle;

// May require an include file on some compilers.
typedef wchar_t IlvWChar;

typedef IlUShort IlvIntensity;
#define IlvFullIntensity ((IlvIntensity)-1)

// --------------------------------------------------------------------------
//    IlvResource
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvResource
{
public:
    IlvResource(IlvDisplay* display = 0)
	: _display(display),
	  _refcount(0),
	  _internal(0),
	  _name(0)
    {}
    virtual ~IlvResource();

    inline IlvDisplay*	getDisplay()  const { return _display;  }
    inline void		lock() { _refcount++; }
    virtual void	unLock();
    inline IlUInt	refCount()    const { return _refcount; }
    inline const char*	getName() const { return _name; }
    virtual void	setName(const char* name);
    inline IlAny	getInternal() const { return _internal; }

protected:
    IlvDisplay*		_display;
    IlUInt		_refcount;
    IlAny		_internal;
    char*		_name;

private:
    // Intentionally not defined.
    IlvResource(IlvResource const& other);
    // Intentionally not defined.
    IlvResource& operator=(IlvResource const& other);
};

// --------------------------------------------------------------------------
//    IlvLineStyle
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvLineStyle : public IlvResource
{
    friend class IlvDisplay;
    friend void _IlvDeleteLineStyle(IlAny, IlAny);

public:
    IlvLineStyle(IlvDisplay*		display,
		 IlUShort		count,
		 const unsigned char*	dashes,
		 IlUShort		offset = 0);
    ~IlvLineStyle();

    inline IlUShort	getOffset() const { return _offset; }
    inline IlUShort	getCount() const  { return _count;  }
    inline
    unsigned char*	getDashes() const { return _dashes; }
    // Compat 3.x
    inline IlUShort	offset() const { return getOffset(); }
    inline IlUShort	count () const { return getCount();  }
    inline
    unsigned char*	dashes() const { return _dashes; }

protected:
    IlUShort		_offset;
    IlUShort		_count;
    unsigned char*	_dashes;
};

// --------------------------------------------------------------------------
//    IlvPalette
// --------------------------------------------------------------------------
#if defined(WINDOWS)
class IlvWindowsPalette;
typedef IlvWindowsPalette* IlvPaletteInternal;
#else  /* !WINDOWS */
typedef IlAny IlvPaletteInternal;
#endif /* !WINDOWS */
class ILVDSPEXPORTED IlvPalette : public IlvResource
{
    friend void _IlvDeletePalette(IlAny, IlAny, IlAny);
    friend class IlvHashTablePalette;
    friend class IlvDisplay;

public:
    IlvPalette(IlvDisplay* display);
    IlvPalette(IlvDisplay* display,
	       IlvColor* background,
	       IlvColor* foreground,
	       IlvFont* font,
	       IlvPattern* pattern);
    IlvPalette(IlvPalette const* palette);
    IlvPalette(IlvPalette const& palette);
    ~IlvPalette();

    virtual void	unLock();
    inline IlvColor*	getBackground() const { return _bg; }
    inline IlvColor*	getForeground() const { return _fg; }
    inline IlvFont*	getFont() const { return _font; }
    inline
    IlvLineStyle*	getLineStyle() const { return _line_style; }
    inline IlvPattern*	getPattern() const { return _pattern; }
    inline
    IlvColorPattern*	getColorPattern() const { return _pixpattern; }
    inline
    IlvGradientPattern*	getGradientPattern() const { return _gradpattern; }
    inline IlBoolean	getOverwrite() const { return _overwrite; }
    inline IlvDrawMode	getMode() const { return _mode; }
    inline IlvFillStyle getFillStyle() const { return _fill_style; }
    inline IlUShort	getLineWidth() const { return _line_width; }
    inline unsigned int getPlaneMask() const { return _plane_mask; }
    inline IlvArcMode	getArcMode() const { return _arc_mode; }
    inline IlvFillRule	getFillRule() const { return _fill_rule; }
    inline IlvIntensity	getAlpha() const { return _alpha; }
    inline
    IlvAntialiasingMode	getAntialiasingMode() const {return _antialias;}
    inline
    const IlvRegion&	getClip() const { return _clip; }
    void		invert();
    void		setBackground(IlvColor* color);
    void		setForeground(IlvColor* color);
    void		setFont(IlvFont* font);
    void		setGradientPattern(IlvGradientPattern* pattern);
    void		setColorPattern(IlvColorPattern* pattern);
    void		setPattern(IlvPattern* pattern);
    void		setOverwrite(IlBoolean over) const;
    void		setMode(IlvDrawMode drawMode) const;
    void		setClip(const IlvRect* rect = 0) const;
    void		setClip(const IlvRegion* clip) const;
    void		setClip(IlvPos, IlvPos, const IlvBitmap*) const;
    void		setClipOrigin(IlvPos, IlvPos) const;
    void		setFillStyle(IlvFillStyle fillStyle);
    void		setLineStyle(IlvLineStyle* style, IlUShort width);
    inline void		setLineStyle(IlvLineStyle* style)
			{
			    setLineStyle(style, _line_width);
			}
    inline void		setLineWidth(IlUShort width)
			{
			    setLineStyle(_line_style, width);
			}
    void		setPlaneMask(unsigned int);
    void		setArcMode(IlvArcMode arcMode);
    void		setFillRule(IlvFillRule fillRule);
    void		setAlpha(IlvIntensity alpha);
    void		setAntialiasingMode(IlvAntialiasingMode antialias);

    inline IlBoolean	isShared() const { return _shared; }
    inline IlBoolean	isBad() const
			{
			    return (_internal == 0) ? IlTrue : IlFalse;
			}
    inline IlBoolean	isUpdated() const { return _updated; }
    inline void		update(IlBoolean upd) { _updated = upd; }
    inline void		getOffsets(IlvPos& xOffset, IlvPos& yOffset) const
			{
			    xOffset = _xOffset;
			    yOffset = _yOffset;
			}
    inline void		setOffsets(IlvPos  xOffset, IlvPos  yOffset)
			{
			    _xOffset = xOffset;
			    _yOffset = yOffset;
			}
    inline
    IlvPaletteInternal	getInternal() const
			{
			    return (IlvPaletteInternal)_internal;
			}
#if defined(X11)
    inline IlBoolean	isGCClipEmpty() const { return _gcClip.isEmpty(); }
#endif /* X11 */

protected:
    IlvPalette(IlvDisplay*		display,
	       IlvColor*		bgg,
	       IlvColor*		fgg,
	       IlvFont*			f,
	       IlvPattern*		pat,
	       IlvColorPattern*		pixpat,
	       IlvLineStyle*		sty,
	       IlUShort			wi,
	       IlBoolean		over,
	       IlvFillStyle		fill,
	       IlvArcMode		arcMode  = IlvArcPie,
	       IlvFillRule		fillRule = IlvEvenOddRule,
	       IlvIntensity		alpha = IlvFullIntensity,
	       IlvAntialiasingMode	antialias = IlvDefaultAntialiasingMode,
	       IlvGradientPattern*	gradpat = 0);

    IlBoolean		_shared;
    IlvColor*		_bg;
    IlvColor*		_fg;
    IlvFont*		_font;
    IlvColorPattern*	_pixpattern;
    IlvGradientPattern*	_gradpattern;
    IlvPattern*		_pattern;
    IlvLineStyle*	_line_style;
    IlUShort		_line_width;
    IlvDrawMode		_mode;
    IlvFillStyle	_fill_style;
    unsigned int	_plane_mask;
    IlvArcMode		_arc_mode;
    IlvFillRule		_fill_rule;
    IlBoolean		_overwrite;
    IlvRegion		_clip;
    IlBoolean		_bmClip;
    IlBoolean		_updated;
    IlvPos		_xOffset;
    IlvPos		_yOffset;
    IlvIntensity	_alpha;
    IlvAntialiasingMode _antialias;

private:
    // Intentionally not defined to forbid the assignment.
    IlvPalette& operator=(IlvPalette const& other);
#if defined(X11)
    IlvRegion		_gcClip;
#endif /* X11 */
};

// --------------------------------------------------------------------------
//    IlvColor
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvColor : public IlvResource
{
public:
    IlvColor(IlvDisplay*,
	     IlUInt	pixel,
	     IlBoolean	isMut    = IlFalse,
	     IlAny	colormap = 0);

    virtual void	unLock();
    virtual void	setName(const char* name);
    inline IlvIntensity getRed() const { return _r; }
    inline IlvIntensity getGreen() const { return _g; }
    inline IlvIntensity getBlue() const { return _b; }
    void		setRed(IlvIntensity red);
    void		setGreen(IlvIntensity green);
    void		setBlue(IlvIntensity blue);
    void		setRGB(IlvIntensity red,
			       IlvIntensity green,
			       IlvIntensity blue);
    void		getRGB(IlvIntensity& red,
			       IlvIntensity& green,
			       IlvIntensity& blue) const;

    IlFloat		getHue() const;
    IlFloat		getSaturation() const;
    IlFloat		getValue() const;
    void		setHue(IlFloat hue);
    void		setSaturation(IlFloat saturation);
    void		setValue(IlFloat value);
    void		setHSV(IlFloat hue,
			       IlFloat saturation,
			       IlFloat value);
    void		getHSV(IlFloat& hue,
			       IlFloat& saturation,
			       IlFloat& value) const;
    // ____________________________________________________________
    inline IlBoolean	isMutable() const { return _mutable; }
    inline IlBoolean	isOwner() const { return _owner; }
    inline IlAny	getColormap() const { return _colormap; }
    inline IlBoolean	isBad() const
			{
			    return (_internal == IL_REINTERPRETCAST(void*, -1))
				? IlTrue
				: IlFalse;
			}
    IlUInt		getIndex() const;
    inline const char*	getAlias() const { return _alias; }
    IlUInt		getDistance(IlvIntensity,
				    IlvIntensity,
				    IlvIntensity) const;
    static void		HSVToRGB(IlFloat       h,
				 IlFloat       s,
				 IlFloat       v,
				 IlvIntensity& red,
				 IlvIntensity& green,
				 IlvIntensity& blue);
    static void		RGBToHSV(IlvIntensity red,
				 IlvIntensity green,
				 IlvIntensity blue,
				 IlFloat&     h,
				 IlFloat&     s,
				 IlFloat&     v);
    static void		ComputeReliefColors(const IlvColor* reference,
					    IlvColor*&	     topShade,
					    IlvColor*&	     bottomShade,
					    IlvColor*&	     select);

protected:
    IlvColor(IlvDisplay*, const char*, IlBoolean isMut = IlFalse);
    IlvColor(IlvDisplay*,
	     IlvIntensity	r,
	     IlvIntensity	g,
	     IlvIntensity	b,
	     IlBoolean		isMut = IlFalse);
    ~IlvColor();
    virtual void	setAlias(const char* alias);

private:
    IlBoolean		_mutable;
    IlvIntensity	_r, _g, _b;
    IlAny		_colormap; // IlvColormap, or device dependant
    IlBoolean		_owner;
    char*		_alias;

    friend class IlvDisplay;
    friend void _IlvDeleteColor(IlAny, IlAny, IlAny);
    friend void _IlvDeleteMutableColor(IlAny value, IlAny);
};

#define IlvHSVToRGB IlvColor::HSVToRGB
#define IlvRGBToHSV IlvColor::RGBToHSV
#define IlvComputeReliefColors IlvColor::ComputeReliefColors

// --------------------------------------------------------------------------
//    IlvFont
// --------------------------------------------------------------------------
typedef IlAny IlvFontInternal;
class ILVDSPEXPORTED IlvFont : public IlvResource
{
public:
    virtual void	setName(const char* name);
    IlvFontSize		getSize() const;
    IlvFontStyle	getStyle() const;
    const char*		getFamily() const;
    const char*		getFoundry() const;
    inline const char*	getFoundary() const { return getFoundry(); } // 2.0
    IlvDim		ascent() const;
    IlvDim		descent() const;
    IlvDim		height() const;
    IlvDim		stringWidth(const char* string,
				    int length = -1) const;
    IlvDim		stringHeight(const char*	string,
				     int		length = -1) const;
    IlvDim		xBaseString(const char*, int length = -1) const;
    IlvDim		yBaseString(const char*, int length = -1) const;
    IlBoolean		isFixed() const;
    void		sizes(const char*	string,
			      int		length,
			      IlvDim&		w,
			      IlvDim&		h,
			      IlvDim&		d) const;
    IlvDim		maxWidth() const;
    IlvDim		minWidth() const;
    inline IlBoolean	isBad() const
			{
			    return (_internal == 0) ? IlTrue : IlFalse;
			}
#if defined(WINDOWS)
    IlBoolean		isTrueType() const;
#endif
#if defined(X11)
    IlBoolean		isAFontSet() const;
    void		bbox(IlvRect&		box,
			     const char*	s,
			     int		length = -1) const;
    void		bbox(IlvRect&		box) const;
    void		bbox(IlvRect&		box,
			     const IlvWChar*	s,
			     int		length = -1) const;
#endif /* X11 */
    inline
    IlvFontInternal	getInternal() const
			{
			    return IL_CAST(IlvFontInternal, _internal);
			}

    void		wcharSizes(const IlvWChar*,
				   int,
				   IlvDim&,
				   IlvDim&,
				   IlvDim&) const;
    IlvDim		wcharWidth(const IlvWChar*, int length = -1) const;
    IlvDim		wcharHeight(const IlvWChar*, int length = -1) const;

    inline const char*	getAlias() const { return _alias; }

    IlString		getSavedName() const;

    // ILVBIDI
    IlvDim		stringWidth(const IlvBidiString*, int len = -1) const;
    IlvDim		stringHeight(const IlvBidiString*, int len = -1) const;
    IlvDim		xBaseString(const IlvBidiString*, int len = -1) const;
    IlvDim		yBaseString(const IlvBidiString*, int len = -1) const;
    void		bbox(IlvRect&	box,
			     const IlvBidiString*,
			     int	len = -1) const;
    void		sizes(const IlvBidiString*,
			      int	len,
			      IlvDim&	w,
			      IlvDim&	h,
			      IlvDim&	d) const;
    // ILVBIDI end

    struct _FP;
    _FP*		_fP;

protected:
    friend class IlvRenderer;
    friend class IlvFontRenderer;

    IlvFont(IlvDisplay*		display,
	    const char*		name,
	    IlvFontSize		size,
	    IlvFontStyle	style,
	    const char*		foundry = 0);
    ~IlvFont();

    virtual void	setAlias(const char* alias);

private:
    char*		_alias;

    friend class IlvDisplay;
    friend class IlvSystemPort;
    friend void _IlvDeleteFont(IlAny, IlAny, IlAny);
};

// --------------------------------------------------------------------------
//    IlvCursor
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvCursor : public IlvResource
{
    friend class IlvDisplay;
    friend void _IlvDeleteCursor(IlAny, IlAny, IlAny);

public:
    IlvCursor(IlvDisplay* display, const char* name);
    IlvCursor(IlvDisplay*	display,
	      IlvPos		hotX,
	      IlvPos		hotY,
	      const char*	name,
	      IlvBitmap*	image,
	      IlvBitmap*	mask);
    ~IlvCursor();
    // ____________________________________________________________
    inline IlBoolean	isBad() const
			{
			    return (_internal == 0) ? IlTrue : IlFalse;
			}
#if defined(WINDOWS)
    IlvCursor(IlvDisplay*	display,
	      IlAny		cursor,
	      const char*	name,
	      IlBoolean		owner = IlFalse);

protected:
    inline void		setOwner(IlBoolean owner) { _owner = owner; }
    inline IlBoolean	getOwner() const { return _owner; }

private:
    IlBoolean		_owner;
#endif /* WINDOWS */
};

// --------------------------------------------------------------------------
//    IlvPushClip
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvPushClip
{
public:
    inline
    IlvPushClip(IlvPalette const& palette, IlvRect const* newClip)
	: _palette(palette),
	  _oldClip(newClip ? new IlvRegion(palette.getClip()) : 0)
    {
	if (_oldClip) { // So newClip is not null.
	    IlvRegion actualClip(*_oldClip);
	    actualClip.intersection(*newClip);
	    _palette.setClip(&actualClip);
	}
    }
    inline
    IlvPushClip(IlvPalette const& palette, IlvRegion const* newClip)
	: _palette(palette),
	  _oldClip(newClip ? new IlvRegion(palette.getClip()) : 0)
    {
	if (_oldClip) { // So newClip is not null.
	    IlvRegion actualClip(*_oldClip);
	    actualClip.intersection(*newClip);
	    _palette.setClip(&actualClip);
	}
    }
    inline
    IlvPushClip(IlvPalette const&	palette,
		IlvRect const&		newClip,
		IlvRegion const*	globalClip)
	: _palette(palette),
	  _oldClip(new IlvRegion(palette.getClip()))
    {
	IlvRegion actualClip(*_oldClip);
	actualClip.intersection(newClip);
	if (globalClip) {
	    actualClip.intersection(*globalClip);
	}
	palette.setClip(&actualClip);
    }
    inline ~IlvPushClip()
    {
	if (_oldClip) {
	    _palette.setClip(_oldClip);
	    delete _oldClip;
	}
    }

private:
    // This member function is intentionally not defined.
    IlvPushClip(IlvPushClip const&);
    // This member function is intentionally not defined.
    IlvPushClip& operator=(IlvPushClip const&);

    IlvPalette const&	_palette;
    IlvRegion*		_oldClip;
};

// --------------------------------------------------------------------------

ILVDSPEXPORTEDFUNCTION(IlvFillStyle)
IlvStringToFillStyle(const char*);
ILVDSPEXPORTEDFUNCTION(const char*)
IlvFillStyleToString(IlvFillStyle);
ILVDSPEXPORTEDFUNCTION(IlvArcMode)
IlvStringToArcMode(const char*);
ILVDSPEXPORTEDFUNCTION(const char*)
IlvArcModeToString(IlvArcMode);
ILVDSPEXPORTEDFUNCTION(IlvAntialiasingMode)
IlvStringToAntialiasingMode(const char*);
ILVDSPEXPORTEDFUNCTION(const char*)
IlvAntialiasingModeToString(IlvAntialiasingMode);
ILVDSPEXPORTEDFUNCTION(IlvFillRule)
IlvStringToFillRule(const char*);
ILVDSPEXPORTEDFUNCTION(const char*)
IlvFillRuleToString(IlvFillRule);

ILVDSPEXPORTEDFUNCTION(IlvFont*)
IlvGetFontAlias(IlvDisplay*,
		const char* alias,
		const char* resource = 0,	// resource name to check
		const char* fallback = 0);	// fallback font name

#endif /* __Ilv_Base_Resource_H */
