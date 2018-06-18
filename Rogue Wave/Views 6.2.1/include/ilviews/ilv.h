// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/ilv.h
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
// Rogue Wave Views main header file
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Ilv_H
#define __Ilv_Ilv_H

#if !defined(__Ilv_Base_List_H)
#  include <ilviews/base/list.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_Stylist_H)
#  include <ilviews/base/stylist.h>
#endif

class IlString;
class IlPathName;
class IlPathList;
class IlvBidiString; // ILVBIDI
class IlvLocaleExtension;
class IlList;
class IlvBitmapData;

#if defined(X11)
typedef IlAny IlvSystemView;
#  if !defined(OLIT) && !defined(MOTIF) && !defined(ILVXLIB)
#    define MOTIF 1
#  endif /* !OLIT && !MOTIF && !ILVXLIB */
#elif defined(WINDOWS) /* !X11 */
typedef IlvWindowsHandle IlvSystemView; // In fact an actual HWND...
#elif defined(DPS)
typedef IlAny IlvSystemView;
#endif /* !X11 */

#if defined(X11)
typedef IlAny IlvViewPort;	// In fact an actual Drawable
class IlvXDisplayConfig;	// declared in ilviews/x11/config.h
class IlvXColormap;		// declared in ilviews/x11/colormap.h
#elif defined(WINDOWS)
typedef IlvWindowsHandle IlvViewPort;
class IlvWindowsDisplayConfig;	// declared in ilviews/windows/config.h
#elif defined(DPS)
typedef IlAny IlvViewPort; // In fact an actual id
#endif /* DPS */

#if !defined(__Ilv_Base_Resource_H)
#  include <ilviews/base/resource.h>
#endif

// These classes were renamed.
#define IlvGadgetHolder IlvGraphicHolder
#define IlvContainerGadgetHolder IlvContainerGraphicHolder
#define IlvManagerGadgetHolder IlvManagerGraphicHolder

enum IlvPosition {
    IlvBadPosition	= 0,
    IlvLeft		= 0x0001,
    IlvRight		= 0x0002,
    IlvTop		= 0x0004,
    IlvBottom		= 0x0008,
    IlvTopLeft		= IlvLeft|IlvTop,
    IlvBottomLeft	= IlvLeft|IlvBottom,
    IlvTopRight		= IlvRight|IlvTop,
    IlvBottomRight	= IlvRight|IlvBottom,
    IlvCenter		= 0x0010,
    IlvHorizontalCenter = 0x0020,
    IlvVerticalCenter	= 0x0040,
    IlvHorizontal	= IlvHorizontalCenter,
    IlvVertical		= IlvVerticalCenter
};
extern "C" {
ILVDSPEXPORTEDFUNCTION(const char*) IlvToString(IlvPosition);
ILVDSPEXPORTEDFUNCTION(IlvPosition) IlvPositionFromString(const char*);
}
typedef IlvPosition IlvDirection;
typedef IlvPosition IlvOrientation;
typedef IlvPosition IlvAlignment;

enum IlvDrawingPrimitive {
    IlvDrawPrimitive		= 0x10,
    IlvDrawStraightLine		= 0x11,
    IlvDrawRectangle		= 0x12,
    IlvFillPrimitive		= 0x20,
    IlvFillRectangle		= 0x21,
    IlvTextPrimitive		= 0x40,
    IlvBitmapPrimitive		= 0x80
};

class IlvPoint;
class IlvDeltaPoint;
class IlvTransformer;

class IlSymbol;	 // Unique Ilv-managed strings

// General Hash Table to be more efficient when sharing resources.
class IlHashTable;
class IlStringHashTable;

class IlvHashTablePalette;  // (fg, bg, font, ...) to IlvPalette
class IlvColorHashTable;    // (name, cmap, bpg) to IlvColor

class IlvPort;
class IlvSystemPort;
class IlvEvent;

typedef IlUShort IlvMarkerType;
#define IlvMarkerSquare		0x0001
#define IlvMarkerDiamond	0x0002
#define IlvMarkerCircle		0x0004
#define IlvMarkerCross		0x0008
#define IlvMarkerPlus		0x0010
#define IlvMarkerFilledSquare	0x0020
#define IlvMarkerFilledCircle	0x0040
#define IlvMarkerFilledDiamond	0x0080
#define IlvMarkerTriangle	0x0100
#define IlvMarkerFilledTriangle 0x0200
#define IlvDefaultMarkerSize	4

enum IlvLookStyle {
    IlvOtherLook = -1,
    IlvMotifLook = 0,
    IlvWindowsLook = 1,
    IlvWindows95Look = 2,
    IlvWindowsXPLook = 3,
    IlvVXLook = 4
};

#define LOOKNUMBER 6

enum IlvDisplaySystem {
    IlvXWindowDisplaySystem,
    IlvMotifDisplaySystem,
    IlvWindowsDisplaySystem
};

// Some constants
extern ILVDSPEXPORTED const IlUInt IlvBadIndex;

class IlvView;
class IlvTimer;
class IlvAbstractView;
class IlvPointArray;

// Declared in config.h
class IlvDisplayConfig;
typedef void (* IlvDisplayConfigCallback)(IlvDisplayConfig* config);

// --------------------------------------------------------------------------
#define ILV_MSG_UNSET   -1
#define ILV_MSG_SILENT   1
#define ILV_MSG_STD      2
#define ILV_MSG_VERBOSE  3

// --------------------------------------------------------------------------
// IlvDisplay
//     Every Window system connexion is designated by an object of this
//     type.
// --------------------------------------------------------------------------
class IlvDisplayExtension;
#if defined(WINDOWS)
class IlvWindowsDisplay;
typedef IlvWindowsDisplay* IlvDisplayInternal;
#else  /* !WINDOWS */
typedef IlAny		   IlvDisplayInternal;
#endif /* !WINDOWS */

#if !defined(__Ilv_Base_Event_H)
#  include <ilviews/base/event.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif

class IlvMessageDatabase;
class IlvLookFeelHandler;
class IlvObjectLFHandler;
class IlvClassInfo;

typedef void (*IlvDisplayCallback)(IlAny userArg);
IL_DEFINEFPTRTOANYCAST(IlvDisplayCallback);
typedef void (*IlvHolderCallback)(IlvDisplay* d);
typedef void (*IlvLayoutCallback)(IlvDisplay* d, IlAny, IlAny);

typedef void (* IlvInternalInputCallback)  (IlvView*, IlvEvent&, IlAny arg);

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvDisplay
: public IlvStylist {
    friend class IlvPalette;
    friend class IlvPattern;
    friend class IlvColorPattern;
    friend class IlvLookFeelHandler;
public:
    IlvDisplay(const char*		className,
	       const char*		displayName = 0,
	       int			argc	    = 0,
	       char**			argv	    = 0,
	       IlvDisplayConfigCallback dcc	    = 0,
	       IlAny			dccArg	    = 0);
    // Create a display connection from an already opened one
    IlvDisplay(IlAny			internal,
	       const char*		className = 0,
	       IlvDisplayConfigCallback dcc	  = 0,
	       IlAny			dccArg	  = 0);
    virtual ~IlvDisplay();
    // ------------------------------------------------------------
    IlBoolean		init(IlvDisplayConfigCallback);
    inline IlBoolean	isBad() const { return (IlBoolean)(_internal == 0); }
    void		displayInit();
    void		displayClose();

    // Reads an ascii resource (Ex: X Windows : ilv.boldfont: foobar)
    const char*		getResource(const char* resourceName,
				    const char* defaultValue = 0) const;
    const char*		getResource(const char* resourceName,
				    const char* objectName,
				    const char* objectClassName,
				    const char* storageName	 = 0,
				    const char* storageClassName = 0) const;

    const char*		getEnvOrResource(const char* envName,
					 const char* resName	  = 0,
					 const char* defaultValue = 0) const;

    IlBoolean		makePalette(IlvPalette* palette);
    void		freePalette (IlvPalette*);
    IlBoolean		makeNamedColor(IlvColor* color);
    IlBoolean		makeColor(IlvColor* color);
    IlBoolean		makeMutableColor(IlvColor* color);
    void		freeColor(IlvColor*);
    IlBoolean		makeBitmap (IlvBitmap* bitmap);
    IlBoolean		makeBitmapFromData(IlvBitmap* bitmap,
					   IlBoolean invert = IlFalse,
					   IlUShort padding = 32);
    IlBoolean		makePixmapFromData(IlvBitmap* bitmap,
					   IlvColor*  bg	= 0,
					   IlvColor*  fg	= 0,
					   IlUShort   padding	= 32);
    IlBoolean		setMask(IlvBitmap* bitmap, IlvBitmap* mask);
    IlBoolean		computeMask(IlvBitmap* bitmap);
    void		freeBitmap(IlvBitmap*);
    IlBoolean		makeFont(IlvFont*, const char* realname = 0);
    IlvFont*		createSystemFont(const char* realname);
    IlvFont*		createFont(const char*  family,
				   IlvFontSize  size,
				   IlvFontStyle style,
				   const char*  foundry);
    IlvFont*		createFont(const char*  family,
				   IlvFontSize  size,
				   const char*  resolution,
				   IlvFontStyle style,
				   const char*  foundry);
    IlvFont*		dupFont(IlvFont* srcFont, const char* dstAlias);
    void		freeFont(IlvFont*);
    IlBoolean		makeLineStyle(IlvLineStyle*);
    void		makeCursor(IlvCursor*);
    void		makeCursor(IlvCursor*,
				   IlvPos,
				   IlvPos,
				   IlvBitmap*,
				   IlvBitmap*);
    void		freeCursor(IlvCursor*);

    void		removeColor(IlvColor*);
    void		removeMutableColor(IlvColor*);
    void		removeFont(IlvFont*);
    void		removeLineStyle(IlvLineStyle*);
    void		removeBitmap(IlvBitmap*);
    void		removePattern(IlvPattern*);
    void		removeColorPattern(IlvColorPattern*);
    void		removeGradientPattern(IlvGradientPattern*);
    IlBoolean		containsGradientPattern(IlvGradientPattern*);
    void		insertGradientPattern(IlvGradientPattern* p);
    void		removeCursor(IlvCursor*);
    void		removePalette(IlvPalette*);
    IlBoolean		getColorRGB(const char*   name,
				    IlvIntensity& r,
				    IlvIntensity& g,
				    IlvIntensity& b) const;
    IlvColor*		getColor(const char* name,
				 IlBoolean   isMutable = IlFalse);
    IlvColor*		getColor(IlvIntensity r,
				 IlvIntensity g,
				 IlvIntensity b,
				 IlBoolean isMutable = IlFalse);
    inline IlvColor*	get8bitsColor(IlUShort r,
				      IlUShort g,
				      IlUShort b,
				      IlBoolean isMutable = IlFalse)
	{
	    return getColor((IlvIntensity)(r << 8),
			    (IlvIntensity)(g << 8),
			    (IlvIntensity)(b << 8),
			    isMutable);
	}
    IlvColor*		getColor(IlFloat hue,
				 IlFloat saturation,
				 IlFloat value,
				 IlBoolean isMutable = IlFalse);
    IlvFont*		getFont(const char* fontName);
    IlvFont*		getSystemFont(const char*);
    IlvFont*		getFont(const char*  fontFamily,
				IlvFontSize  fontSize,
				IlvFontStyle fontStyle = IlvNormalFontStyle,
				const char*  foundry   = 0);
    IlvFont*		getFont(const char*  fontFamily,
				IlvFontSize  fontSize,
				const char*  fontResolution,
				IlvFontStyle fontStyle = IlvNormalFontStyle,
				const char*  foundry   = 0);
    IlvDim*		getFontSizes(const char*  fontFamily,
				     IlvFontStyle fontStyle,
				     int&         count,
				     const char*  foundry = 0) const;
    IlvPattern*		getPattern(const char* name) const;
    IlvColorPattern*	getColorPattern(const char* name) const;

    IlvGradientPattern*	getGradientPattern(const char* alias) const;

    IlvGradientPattern*	getLinearGradientPattern(IlvColorStop**	colorStops,
	IlUInt				nColorStops,
	IlvPoint			startPoint,
	IlvPoint			endPoint,
	IlvDim				width = 0,
	IlvDim				height = 0,
	IlvGradientTransformMode	mode = IlvGradientTransformGraphic,
	IlvGradientAspectRatio		aspectRatio=IlvGradientAspectRatioNo,
	IlvGradientSpread		spread = IlvGradientPadSpread,
	const char*			alias = 0) const;

    IlvGradientPattern*	getLinearGradientPattern(IlvColor*	startColor,
	IlvColor*			endColor,
	IlvPoint			startPoint,
	IlvPoint			endPoint,
	IlvDim				width = 0,
	IlvDim				height = 0,
	IlvGradientTransformMode	mode = IlvGradientTransformGraphic,
	IlvGradientAspectRatio		aspectRatio=IlvGradientAspectRatioNo,
	IlvGradientSpread		spread = IlvGradientPadSpread,
	const char*			alias = 0) const;

    IlvGradientPattern*	getRadialGradientPattern(IlvColorStop**	colorStops,
	IlUInt				nColorStops,
	IlvDim				width,
	IlvDim				height,
	IlvGradientTransformMode	mode = IlvGradientTransformGraphic,
	IlvGradientAspectRatio		aspectRatio=IlvGradientAspectRatioNo,
	IlvGradientSpread		spread = IlvGradientPadSpread,
	const char*			alias = 0) const;

    IlvGradientPattern*	getRadialGradientPattern(IlvColor*	startColor,
	IlvColor*			endColor,
	IlvDim				width,
	IlvDim				height,
	IlvGradientTransformMode	mode = IlvGradientTransformGraphic,
	IlvGradientAspectRatio		aspectRatio=IlvGradientAspectRatioNo,
	IlvGradientSpread		spread = IlvGradientPadSpread,
	const char*			alias = 0) const;

    IlvGradientPattern*	getRadialGradientPattern(IlvColorStop**	colorStops,
	IlUInt				nColorStops,
	IlvPoint			startCenter,
	IlvDim				startRadius,
	IlvPoint			endCenter,
	IlvDim				endRadius,
	IlvDim				width = 0,
	IlvDim				height = 0,
	IlvGradientTransformMode	mode = IlvGradientTransformGraphic,
	IlvGradientAspectRatio		aspectRatio=IlvGradientAspectRatioNo,
	IlvGradientSpread		spread = IlvGradientPadSpread,
	const char*			alias = 0) const;

    IlvGradientPattern*	getRadialGradientPattern(IlvColor*	startColor,
	IlvColor*			endColor,
	IlvPoint			startCenter,
	IlvDim				startRadius,
	IlvPoint			endCenter,
	IlvDim				endRadius,
	IlvDim				width = 0,
	IlvDim				height = 0,
	IlvGradientTransformMode	mode = IlvGradientTransformGraphic,
	IlvGradientAspectRatio		aspectRatio=IlvGradientAspectRatioNo,
	IlvGradientSpread		spread = IlvGradientPadSpread,
	const char*			alias = 0) const;

    IlvCursor*		getCursor(const char* name);

    const char* const*	getNamedPalettes(IlUInt& count) const;
    IlvPalette*		getPalette(const char* paletteName);
    IlvPalette*		getPalette(IlvColor*	 background= 0,
				   IlvColor*	 foreground= 0,
				   IlvPattern*	 pattern   = 0,
				   IlvColorPattern* colorPattern= 0,
				   IlvFont*	 font	   = 0,
				   IlvLineStyle* lineStyle = 0,
				   IlUShort	 lineWidth = 0,
				   IlvFillStyle	 fillStyle = IlvFillPattern,
				   IlvArcMode	 arcMode   = IlvArcPie,
				   IlvFillRule	 fillRule  = IlvEvenOddRule,
				   IlvIntensity	 alpha 	  = IlvFullIntensity,
				   IlvAntialiasingMode antialias =
				   IlvDefaultAntialiasingMode,
				   IlvGradientPattern* gradientPattern = 0);
    IlvPalette*		getInvertedPalette(const IlvPalette* source);
    IlvLineStyle*	getLineStyle(IlUShort			count,
				     const unsigned char*	dashes,
				     IlUShort			offset = 0);
    IlvLineStyle*	getLineStyle(const char* name) const;

    inline IlList*	getPatterns() const
	{ return _all_patterns; }
    inline IlList*	getColorPatterns() const
	{ return _all_colorpatterns; }
    inline IlList*	getGradientPatterns() const
	{ return _all_gradientpatterns; }
    inline IlList*	getGradientAliasPatterns() const
	{ return _all_gradientaliaspatterns; }
    inline IlList*	getCursors() const
	{ return _all_cursors; }
    inline IlList*	getBitmaps() const
	{ return _all_bitmaps; }
    inline IlList*	getLineStyles() const
	{ return _all_linestyles; }
    inline IlvHashTablePalette* getAllPalettes() const
	{ return _all_palettes; }
    inline IlStringHashTable*	getFonts() const
	{ return _all_fonts; }
    inline IlStringHashTable*	getFontAliases() const
	{ return _all_font_aliases; }

    void		setBackground(IlvPalette*, const IlvColor*) const;
    void		setForeground(IlvPalette*, const IlvColor*) const;
    void		setFont(IlvPalette*, const IlvFont*) const;
    void		setColorPattern(IlvPalette*,
					const IlvColorPattern*) const;
    void		setGradientPattern(IlvPalette*,
					   const IlvGradientPattern*) const;
    void		setPattern(IlvPalette*, const IlvPattern*) const;
    void		setOverwrite(IlvPalette*, IlBoolean) const;
    void		setMode(IlvPalette*, IlvDrawMode) const;
    void		setClip(IlvPalette*, const IlvRect* rect = 0) const;
    void		setClip(IlvPalette*, const IlvRegion*) const;
    void		setClip(IlvPalette*,
				IlvPos,
				IlvPos,
				const IlvBitmap*) const;
    void		setClipOrigin(IlvPalette*, IlvPos, IlvPos) const;
    void		setFillStyle(IlvPalette*, IlvFillStyle) const;
    void		setLineStyle(IlvPalette*,
				     const IlvLineStyle*,
				     IlUShort) const;
    void		setPlaneMask(IlvPalette*, unsigned int) const;
    void		setArcMode(IlvPalette*, IlvArcMode) const;
    void		setFillRule(IlvPalette*, IlvFillRule) const;
    void		setAlpha(IlvPalette*, IlvIntensity) const;
    void		setAntialiasingMode(IlvPalette*,
					    IlvAntialiasingMode) const;

    inline IlInt	getErrorCode() const
	{ return _errorCode; }
    inline void		setErrorCode(IlInt val)
	{ _errorCode = val; }
    void		openDrawing(IlvPort*, const IlvRegion* = 0) const;
    void		closeDrawing() const;
    inline IlvSystemPort*	drawingPort() const
	{ return _drawingPort; }
    void		checkClip(const IlvPalette*) const;

    // For compatibility.
    inline void		drawPoint(IlvPort*, const IlvPalette*,
				  const IlvPoint&) const;
    inline void		drawPoints(IlvPort*, const IlvPalette*,
				   IlUInt, const IlvPoint*) const;
    inline void		drawLine(IlvPort*, const IlvPalette*,
				 const IlvPoint&,
				 const IlvPoint&) const;
    inline void		drawSegments(IlvPort*, const IlvPalette*,
				     IlUInt,
				     const IlvPoint*,
				     const IlvPoint*) const;
    inline void		drawPolyLine(IlvPort*, const IlvPalette*,
				     IlUInt,
				     const IlvPoint*) const;
    inline void		drawPolyLine(IlvPort*, const IlvPalette*,
				     const IlvPoint&,
				     IlUInt,
				     const IlvDeltaPoint*) const;
    inline void		fillPolyLine(IlvPort*, const IlvPalette*,
				     IlUInt,
				     const IlvPoint*,
				     IlBoolean = IlFalse) const;
    inline void		fillPolyLine(IlvPort*, const IlvPalette*,
				     const IlvPoint&,
				     IlUInt,
				     const IlvDeltaPoint*,
				     IlBoolean = IlFalse) const;
    inline void		drawRectangle(IlvPort*, const IlvPalette*,
				      const IlvRect&) const;
    inline void		fillRectangle(IlvPort*, const IlvPalette*,
				      const IlvRect&) const;
    inline void		drawRoundRectangle(IlvPort*, const IlvPalette*,
					   const IlvRect&,
					   IlUShort) const;
    inline void		fillRoundRectangle(IlvPort*, const IlvPalette*,
					   const IlvRect&,
					   IlUShort) const;
    inline void		drawArc(IlvPort*, const IlvPalette*,
				const IlvRect&,
				IlFloat,
				IlFloat) const;
    inline void		fillArc(IlvPort*, const IlvPalette*,
				const IlvRect&,
				IlFloat,
				IlFloat) const;
    inline void		drawBezier(IlvPort*, const IlvPalette*,
				   IlUInt,
				   const IlvPoint*) const;
    inline void		drawClosedBezier(IlvPort*, const IlvPalette*,
					 IlUInt,
					 const IlvPoint*) const;
    inline void		fillBezier(IlvPort*, const IlvPalette*,
				   IlUInt,
				   const IlvPoint*) const;
    inline void		drawPaths(IlvPort*, const IlvPalette*,
				  IlUInt,
				  const IlvPointArray*) const;
    inline void		fillPaths(IlvPort*, const IlvPalette*,
				  IlUInt,
				  const IlvPointArray*) const;
    inline void		copyArea(IlvPort*, const IlvPalette*,
				 const IlvSystemPort*,
				 const IlvRect&,
				 const IlvPoint&) const;
    inline void		copyTransparentArea(IlvPort*, const IlvPalette*,
					    const IlvSystemPort*,
					    const IlvRect&,
					    const IlvPoint&) const;
    inline void		copyStretchedBitmap(IlvPort*, const IlvPalette*,
					    const IlvPoint&,
					    const IlvBitmap*,
					    const IlvTransformer&,
					    const IlvRect* = 0) const;
    inline void		copyStretchedTransparentBitmap(IlvPort*,
						   const IlvPalette*,
						   const IlvPoint&,
						   const IlvBitmap*,
						   const IlvTransformer&,
						   const IlvRect* = 0) const;
    inline void		drawString(IlvPort*, const IlvPalette*,
				   const IlvPoint&,
				   const char*,
				   int,
				   IlvAlignment = IlvLeft) const;
    inline void		drawIString(IlvPort*, const IlvPalette*,
				    const IlvPoint&,
				    const char*,
				    int,
				    IlvAlignment = IlvLeft) const;
    inline void		drawWChar(IlvPort*, const IlvPalette*,
				  const IlvPoint&,
				  const IlvWChar*,
				  int,
				  IlvAlignment = IlvLeft) const;
    inline void		drawIWChar(IlvPort*, const IlvPalette*,
				   const IlvPoint&,
				   const IlvWChar*,
				   int,
				   IlvAlignment = IlvLeft) const;
    inline void		drawTransformedString(IlvPort*, const IlvPalette*,
					      const char*,
					      int,
					      const IlvTransformer&,
					      const IlvRegion* = 0) const;
    inline void		clearArea(IlvPort*,
				  const IlvRect&,
				  IlBoolean = IlFalse) const;
    inline void		clearArea(IlvPort*,
				  const IlvRegion&,
				  IlBoolean = IlFalse) const;
    inline void		drawBitmap(IlvPort*, const IlvPalette*,
				   const IlvBitmap*,
				   const IlvRect&,
				   const IlvRegion* = 0,
				   IlvPosition = IlvCenter,
				   IlBoolean = IlFalse) const;
    inline void		copyStretchedBitmap(IlvPort*, const IlvPalette*,
					    const IlvRect&,
					    const IlvBitmap*,
					    const IlvRect* = 0) const;
    inline void		copyStretchedTransparentBitmap(IlvPort*,
						   const IlvPalette*,
						   const IlvRect&,
						   const IlvBitmap*,
						   const IlvRect* = 0) const;
    inline void		drawArrow(IlvPort*, const IlvPalette*,
				  const IlvPoint&,
				  const IlvPoint&,
				  IlFloat) const;
    inline void		drawMarker(IlvPort*, const IlvPalette*,
				   const IlvPoint&,
				   IlvMarkerType = IlvMarkerSquare,
				   IlUShort = IlvDefaultMarkerSize) const;
    inline void		drawShadowRectangle(IlvPort*, const IlvPalette*,
					    const IlvPalette*,
					    const IlvRect&,
					    IlUShort,
					    IlvPosition,
					    const IlvRegion* = 0) const;
    inline void		drawReliefPolyline(IlvPort*, const IlvPalette*,
					   const IlvPalette*,
					   IlUInt,
					   IlvPoint*,
					   IlUShort,
					   IlBoolean = IlFalse,
					   const IlvRegion*   = 0) const;
    inline void		drawReliefRectangle(IlvPort*, const IlvPalette*,
					    const IlvPalette*,
					    const IlvPalette*,
					    const IlvPalette*,
					    const IlvRect&,
					    IlUShort,
					    const IlvRegion* = 0) const;
    inline void		drawReliefPolygon(IlvPort*, const IlvPalette*,
					  const IlvPalette*,
					  const IlvPalette*,
					  IlUInt,
					  IlvPoint*,
					  IlUShort,
					  const IlvRegion* = 0) const;
    inline void		drawOutlineRectangle(IlvPort*, const IlvPalette*,
					     const IlvPalette*,
					     const IlvRect&,
					     const IlvRegion* = 0) const;
    inline void		drawReliefDiamond(IlvPort*, const IlvPalette*,
					  const IlvPalette*,
					  const IlvPalette*,
					  const IlvPalette*,
					  const IlvRect&,
					  IlUShort,
					  const IlvRegion* = 0) const;
    inline void		drawReliefArrow(IlvPort*,
					IlvRect,
					IlvDim,
					IlvOrientation,
					const IlvPalette*,
					const IlvPalette*,
					const IlvPalette*,
					const IlvRegion* = 0) const;
    inline void		drawLabel(IlvPort*, const IlvPalette*,
				  const char*,
				  int,
				  const IlvRect&,
				  const IlvRegion* = 0,
				  IlvPosition = IlvCenter) const;
    inline void		drawMnemonicLabel(IlvPort*, const IlvPalette*,
					  const char*,
					  const IlvRect&,
					  const IlvRegion* = 0,
					  IlvPosition = IlvCenter,
					  IlBoolean = IlTrue) const;
    inline void		drawILabel(IlvPort*, const IlvPalette*,
				   const char*,
				   int,
				   const IlvRect&,
				   const IlvRegion* = 0,
				   IlvPosition = IlvCenter) const;
    // ____________________________________________________________
    inline IlvBitmap*	getDefaultBitmap() const
	{ return _default_bitmap; }
    IlvBitmap*		transformBitmap(IlvBitmap*,
					const IlvTransformer&,
					IlBoolean = IlTrue) const;
    // ____________________________________________________________
    void		flush() const;
    void		sync() const;
    void		synchronize(IlBoolean value = IlTrue) const;
    IlBoolean		hasEvents() const;
    void		requeueEvent(IlvEvent&) const;
    void		readAndDispatchEvents() const;
    void		waitAndDispatchEvents() const;
    void		movePointer(IlvDeltaPoint& dp) const;
    void		movePointer(IlvPoint& p) const;
    void		queryPointer(IlvPos& x,
				     IlvPos& y,
				     IlUShort& modifiers) const;
    inline IlvPalette*	defaultPalette() const { return _default_palette; }
    inline IlvPalette*	getDefaultGadgetPalette() const
	{ return _default_gadget_palette; }

    // Some useful colors... ______________________________________
    inline IlvColor*	defaultBackground() const
	{ return _default_background; }
    inline IlvColor*	defaultForeground() const
	{ return _default_foreground; }

    // Font Family Names __________________________________________
    const char* const*	getFamilyNames(IlUShort& count) const;

    // Some useful fonts... _______________________________________
    inline IlvFont*	defaultFont() const
	{ return _default_font; }
    inline IlvFont*	defaultNormalFont() const
	{ return _default_normal_font; }
    inline IlvFont*	defaultBoldFont() const
	{ return _default_bold_font; }
    inline IlvFont*	defaultItalicFont() const
	{ return _default_italic_font; }
    inline IlvFont*	defaultLargeFont() const
	{ return _default_large_font; }

    // Some useful line styles... _________________________________
    inline
    IlvLineStyle*	defaultLineStyle() const { return solidLineStyle(); }
    IlvLineStyle*	solidLineStyle()	 const;
    IlvLineStyle*	dotLineStyle()		 const;
    IlvLineStyle*	dashLineStyle()		 const;
    IlvLineStyle*	dashDotLineStyle()	 const;
    IlvLineStyle*	dashDoubleDotLineStyle() const;
    IlvLineStyle*	alternateLineStyle()	 const;
    IlvLineStyle*	doubleDotLineStyle()	 const;
    IlvLineStyle*	longDashLineStyle()	 const;

    // Some useful patterns... ____________________________________
    inline IlvPattern*	defaultPattern() const
	{ return solidPattern(); }
    IlvPattern*		solidPattern()	const;
    IlvPattern*		clearPattern()	const;
    IlvPattern*		dark4Pattern()	const;
    IlvPattern*		dark3Pattern()	const;
    IlvPattern*		dark2Pattern()	const;
    IlvPattern*		dark1Pattern()	const;
    IlvPattern*		grayPattern()	const;
    IlvPattern*		light4Pattern()	const;
    IlvPattern*		light3Pattern()	const;
    IlvPattern*		light2Pattern()	const;
    IlvPattern*		light1Pattern()	const;
    IlvPattern*		diagLRPattern()	const;
    IlvPattern*		diagRLPattern() const;
    IlvPattern*		horizPattern()	const;
    IlvPattern*		vertPattern()	const;
    IlvPattern*		crossPattern()	const;
    IlvPattern*		pattern1()	const;
    IlvPattern*		pattern2()	const;
    IlvPattern*		pattern3()	const;
    IlvPattern*		pattern4()	const;
    IlvPattern*		pattern5()	const;
    IlvPattern*		pattern6()	const;
    IlvPattern*		pattern7()	const;
    IlvPattern*		pattern8()	const;
    IlvPattern*		pattern9()	const;
    IlvPattern*		pattern10()	const;
    IlvPattern*		pattern11()	const;
    IlvPattern*		pattern12()	const;

    // Some useful cursors... _____________________________________
    IlvCursor*		defaultCursor()		const;
    IlvCursor*		waitCursor()		const;
    IlvCursor*		crossCursor()		const;
    IlvCursor*		beamCursor()		const;
    IlvCursor*		sizingCursor()		const;
    IlvCursor*		hsizingCursor()		const;
    IlvCursor*		vsizingCursor()		const;
    IlvCursor*		neswsizingCursor()	const;
    IlvCursor*		nwsesizingCursor()	const;
    inline IlvDim	screenWidth() const
	{ return _max_width;  }
    inline void		setScreenWidth(IlvDim maxWidth)
	{ _max_width = maxWidth; }
    inline IlvDim	screenHeight() const
	{ return _max_height; }
    inline void 	setScreenHeight(IlvDim maxHeight)
	{ _max_height = maxHeight; }
    IlvDim		screenWidthMM() const;
    IlvDim		screenHeightMM() const;
    inline IlUShort	screenDepth() const { return _depth; }
    IlvRect&		screenBBox(IlvRect&       bbox,
				   IlBoolean      workArea = IlTrue,
				   const IlvRect* rect     = 0) const;
    inline IlvAntialiasingMode  getAntialiasingMode() const
	{ return _antialias; }
    inline void		setAntialiasingMode(IlvAntialiasingMode antialias)
	{ _antialias = antialias; }
    IlvAntialiasingMode getAntialiasingMode(const IlvPort&,
					    const IlvPalette&) const;
    inline IlBoolean	isRightButtonValueUsed() const
	{ return _useRightButtonValue; }
    void		useRightButtonValue(IlBoolean flag);
    unsigned char*	getBitmapData(const IlvSystemPort* bitmap,
				      IlUInt&	           size,
				      const IlvRect&       rect) const;
    void		putBitmapData(IlvSystemPort* bitmap,
				      const IlvRect& rect,
				      unsigned char* data,
				      IlUInt         size) const;
    // ____________________________________________________________
    void		stopDump();
    void		restartDump();
    IlBoolean		initDump(IlvPort* device);
    void		endDump();
    inline IlBoolean	isDumping() const
	{ return _dumping; }
    inline IlvPort*	getDumpDevice() const
	{ return _device; }
    IlBoolean		isCairoEnabled() const;

    IlBoolean		isGradientSupported(IlvPort*,
					    const IlvPalette*,
					    IlvDrawingPrimitive);

    // ____________________________________________________________
    inline IlvDisplayInternal	getInternal()   const
	{ return _internal; }
    inline IlvDisplayConfig*	getConfig()     const
	{ return _config;	  }
    inline const char*		getName()       const
	{ return _name;	  }
    inline const char*	getClassName()  const
	{ return _classname; }
    inline IlAny	getColormap()   const
	{ return _colormap;  }
    inline IlAny	getRootWindow() const
	{ return _root;	   }
    inline IlvSystemPort*	screenPort() const
	{
	    return IL_REINTERPRETCAST(IlvSystemPort*,
				      _rootport);
	}

    void		setCursor(IlvSystemPort*, IlvCursor*);
    void		recolorCursor(IlvCursor*,
				      const IlvColor*,
				      const IlvColor*);
    void		pixelToRGB(IlUInt        pixel,
				   IlvIntensity& r,
				   IlvIntensity& g,
				   IlvIntensity& b) const;
    void		colorTable(IlUShort,
				   IlvIntensity*,
				   IlvIntensity*,
				   IlvIntensity*) const;
    IlUShort		colorTable(IlvIntensity*  r,
				   IlvIntensity*  g,
				   IlvIntensity*  b,
				   unsigned char* indexes,
				   IlBoolean	  getMutables=IlFalse) const;
    IlvColor*		getNearestColor(IlvIntensity,
					IlvIntensity,
					IlvIntensity,
					IlUInt* = 0) const;
    IlvColor*		getNearestColor(IlFloat,
					IlFloat,
					IlFloat,
					IlUInt* = 0) const;
    IlvBitmap*		getBitmap(const char* name,
				  IlBoolean   read = IlFalse) const;
    IlvBitmap*		lockBitmap(IlvDim, IlvDim);
    void		releaseBitmap(IlvBitmap*);
    IlvBitmap*		readBitmap(const char* filename);
    IlvBitmap*		readAsciiBitmap(const char* filename);
    IlvBitmapData*	readBitmapData(const char* filename);
    IlvBitmap*		readBitmap(ILVSTDPREF istream&);
    IlvBitmapData*	readBitmapData(ILVSTDPREF istream&);
    void		bell(int volume = 0) const;

    // Clipboard functions ________________________________________
    void		putClipboard(const char*, int = -1) const;
    const char*		getClipboard(int&) const;

    // IlvHome/IlvPath related functions __________________________
    inline const IlPathName&	getHomePath() const
	{ return *_homePath; }
    inline const char*		getHome()     const
	{ return _home; }
    inline const IlPathList*	getPathList() const
	{ return _pathList; }
    const char*		getPath()     const;
    void		setPath(const IlPathName&);
    void		setPath(const char* path);
    void		appendToPath(const char* pathPart);
    void		appendToPath(const IlString&);
    void		appendToPath(const IlPathName&);
    void		prependToPath(const char* pathPart);
    void		prependToPath(const IlString&);
    void		prependToPath(const IlPathName&);
    void		removeFromPath(const char*);
    void		removeFromPath(const IlString&);
    void		removeFromPath(const IlPathName&);
    void		appendToSystemPath(const char*);
    void		appendToSystemPath(const IlString&);
    void		appendToSystemPath(const IlPathName&);
    void		prependToSystemPath(const char*);
    void		prependToSystemPath(const IlString&);
    void		prependToSystemPath(const IlPathName&);
    void		removeFromSystemPath(const char*);
    void		removeFromSystemPath(const IlString&);
    void		removeFromSystemPath(const IlPathName&);
    const char*		findInPath(const IlPathName&,
				   IlBoolean = IlFalse) const;
    const char*		findInPath(const char* fileName,
				   IlBoolean noLocalization = IlFalse) const;
    const char*		findInPath(IlString&, IlBoolean = IlFalse) const;
    char*		createStringInPath(const char*,
					   IlBoolean = IlFalse,
					   IlBoolean = IlFalse) const;
    ILVSTDPREF istream* createStreamInPath(const char*,
					   IlBoolean = IlFalse,
					   IlBoolean = IlTrue,
					   const char** = 0) const;
    IlBoolean		isInDataBlock(const char*) const;
    IlvDim		mnemonicLabelSize(const char*, IlvFont*) const;
    char		getMnemonic(const char*) const;
    IlvBitmap*		getMonochromeBuffer(IlvDim, IlvDim);
    IlvBitmap*		getScreenBuffer(IlvDim, IlvDim);

    // ILVBIDI
    void		drawString(IlvPort*, const IlvPalette*,
				   const IlvPoint&,
				   const IlvBidiString*,
				   int,
				   IlvAlignment = IlvLeft) const;
    void		drawIString(IlvPort*, const IlvPalette*,
				    const IlvPoint&,
				    const IlvBidiString*,
				    int,
				    IlvAlignment = IlvLeft) const;
    void		drawTransformedString(IlvPort*, const IlvPalette*,
					      const IlvBidiString*,
					      int,
					      const IlvTransformer&,
					      const IlvRegion* = 0) const;
    void		drawLabel(IlvPort*, const IlvPalette*,
				  const IlvBidiString*,
				  int,
				  const IlvRect&,
				  const IlvRegion* = 0,
				  IlvPosition = IlvCenter) const;
    void		drawMnemonicLabel(IlvPort*, const IlvPalette*,
					  const IlvBidiString*,
					  const IlvRect&,
					  const IlvRegion* = 0,
					  IlvPosition  = IlvCenter,
					  IlBoolean = IlTrue) const;
    IlvDim		mnemonicLabelSize(const IlvBidiString*,
					  IlvFont*) const;
    inline IlAny	getBidiInfo() const
	{ return _bidiInfo; }
    inline void		setBidiInfo(IlAny val)
	{ _bidiInfo = val; }
    // ILVBIDI
    inline IlvLocaleExtension*	getLocale()    const
	{ return _locale; }
    inline IlvDisplayExtension* getExtension() const
	{ return _extension; }
    inline IlHashTable*	getExtValues() const
	{ return _extValues; }

    IlBoolean          hasMultiTouch() const;

    IlUShort		getTouchPoints(const IlvPoint** relative,
				       const IlvPoint** absolute = 0) const;
    IlUShort		getTouchPointCount() const;
#if defined(X11)
    inline int		getFDDisplay() const { return _file_descriptor; }
    IlAny		topShell() const;
    inline IlAny	defaultDepth1Palette() const
	{ return _default_depth1_palette; }
    int			getScreen() const { return _screen; }
    inline IlvXDisplayConfig*	getXConfig() const
	{
	    return IL_REINTERPRETCAST(IlvXDisplayConfig*,
				      _config);
	}
    inline IlvXColormap*	getXColormap() const
	{
	    return IL_REINTERPRETCAST(IlvXColormap*,
				      _colormap);
	}
    IlUInt		getAllBitPlanesGroupsMask() const
	{ return _allBitPlanesGroupsMask; }
    inline IlUInt	getBitPlanesGroupsMask() const
	{ return _bitPlanesGroupsMask; }
    IlBoolean		setBitPlanesGroupsMask(IlUInt val);
    int			getBitPlanesGroup() const;
    IlBoolean		setBitPlanesGroup(int group = -1);
    IlBoolean		setColormap(IlvXColormap* colormap = 0);
#endif /* X11 */

    IlHashTable*	_allWindows;

#if defined(WINDOWS)
    inline IlvWindowsDisplayConfig* getWindowsConfig() const
	{ return IL_REINTERPRETCAST(IlvWindowsDisplayConfig*, _config); }

    friend class IlvWindowsDisplay;

    IlvWindowsHandle	getInstance() const;
    const char*		getWindowClass() const;
    IlAny		getPaletteHandle() const;
    IlvWindowsHandle	beginDrawing(const IlvSystemPort*,
				     const IlvPalette*,
				     IlvWindowsHandle);
    void		setErrorFlag();
    inline void		resetErrorFlag()
	{ _errorFlag = IlFalse; }
    inline IlBoolean	getErrorFlag() const
	{ return _dumping && _errorFlag; }

    void		initTransparentFrontView(IlUInt,
						IlvInternalInputCallback = 0,
						IlAny = 0);
    void		killTransparentFrontView(IlUInt);
    IlBoolean		useDirectScreenDrawings(IlBoolean = IlTrue);
    void		setTransparentFrontBitmap(IlUInt, IlvBitmap*);
    IlvBitmap*		getTransparentFrontBitmap(IlUInt);
    void 		showTransparentFrontView(IlUInt, IlvRect);
    IlvPalette* 	getTransparentPalette();
    IlvPalette* 	getWhiteGhostPalette();
    IlvPalette* 	getBlackGhostPalette();
    IlUInt		getTranspFrontViewCount();
#endif /* WINDOWS */
    IlvView* const*	getViews(IlUInt& count) const;
    IlvView*		getView(const char* name) const;
    IlvView*		getView(IlvSystemView view) const;
    inline IlvView*	findView(const char* name) const
	{ return getView(name); }
    IlvView*		findView(const IlvPoint& p) const;
    IlvView*		findPointerView() const;
    const char*		getSystemName() const;
    void		addGrab(IlvAbstractView*);
    void		removeGrab(IlvAbstractView*);
    IlBoolean		isInGrabList(IlvAbstractView*) const;
    inline IlList*	getGrabList() { return &_grabList; }
    IlvTimer*		getTimer(const char*) const;
    IlvAbstractView*	getFirstGrabbingView() const;
    inline IlvEvent*	getLastButtonEvent()
	{ return &_lastButtonEvent; }
    void		refreshAllViews();

    // ____________________________________________________________
    inline IlvMessageDatabase*	getDatabase() const
	{ return _database; }
    inline IlSymbol*	getCurrentLanguage() const
	{ return _currentLanguage; }
    void		setCurrentLanguage(IlSymbol* language);
    void		initDatabase();
    void		addChangeLanguageCallback(IlvDisplayCallback cb,
						  IlAny              arg);
    void		removeChangeLanguageCallback(IlvDisplayCallback cb,
						     IlAny              arg);
    inline void		setChangeLanguageCallback(IlvHolderCallback cb)
	{ _languageCallback = cb; }

    const char*		getMessage(const char* msgid) const;

    // ____________________________________________________________
    // Styling
    virtual IlvStylist*			getParentStylist() const;
    virtual std::list<IlvStyleSheet*>*	getStyleSheetList(IlBoolean) const;

    // ____________________________________________________________
    // Look And Feel Management
    inline IlvLookStyle	getCurrentLook() const
	{ return _currentLook; }
    void		setCurrentLook(IlvLookStyle style);
    inline void		setLookFeelHandler(IlvLookFeelHandler* lfh)
	{ setCurrentLookFeelHandler(lfh); }
    void		setCurrentLookFeelHandler(IlvLookFeelHandler*);
    IlvLookFeelHandler*	getLookFeelHandler(IlSymbol* name) const;
    inline IlvLookFeelHandler*	getLookFeelHandler() const
	{
	    if (!_currentLookFeel) {
		IL_CONSTCAST(IlvDisplay*, this)
					      ->makeDefaultLookFeelHandler();
	    }
	    return _currentLookFeel;
	}
    inline IlvLookFeelHandler*	getCurrentLookFeelHandler() const
	{ return getLookFeelHandler(); }
    inline IlBoolean	usesLookFeelHandler() const
	{ return _currentLookFeel ? IlTrue : IlFalse; }

    void		addChangeLookCallback(IlvDisplayCallback cb,
					      IlAny              arg);
    void		removeChangeLookCallback(IlvDisplayCallback cb,
						 IlAny              arg);
    inline void		setChangeLookCallback(IlvHolderCallback cb)
	{ _lookCallback = cb; }
    IlvObjectLFHandler*	getObjectLFHandler(IlvClassInfo*) const;
    void		currentLookChanged(IlvLookFeelHandler*,
					   IlvLookFeelHandler*);
    void		resetCurrentLookFeelHandler();
    void		makeDefaultLookFeelHandler();

    // -------------------------------------------------------------
    inline IlAny	getLayoutAttributes() const
	{ return _layoutAttributes; }
    void		setLayoutAttributes(IlAny);
    void	addChangeLayoutAttributesCallback(IlvDisplayCallback, IlAny);
    inline void	setChangeLayoutAttributesCallback(IlvLayoutCallback cb)
	{ _layoutCallback = cb; }

    // -------------------------------------------------------------
    inline IlvView*	getFocusView() const
	{ return _focusView; }
    inline void		setFocusView(IlvView* v)
	{ _focusView = v;	  }
    inline IlBoolean	getLoseFocus() const
	{ return _loseFocusFlag; }
    inline void		setLoseFocus(IlBoolean set)
	{ _loseFocusFlag = set; }
    IlvView*		getSelectionOwner();

    // --------------------------------------------------------------
    inline IlAny	getToolTipConfig()
	{ return _toolTipConfig;}
    inline void		setToolTipConfig(IlAny cfg)
	{ _toolTipConfig = cfg; }
    inline IlAny	getItemConfig()
	{ return _itemConfig;}
    inline void		setItemConfig(IlAny cfg)
	{ _itemConfig = cfg; }

    void		remove();

    inline IlInt	getBmpMsgMode() const
	{ return _bmpMsgMode; }
    void		setBmpMsgMode(IlInt m);

    static
    IlvDisplaySystem	GetDisplaySystem();

protected:
    // Not documented
    IlvMessageDatabase*	setDatabase(IlvMessageDatabase*);

private:
    void		registerLook(IlvLookFeelHandler*);
    void		unRegisterLook(IlvLookFeelHandler*);
    void		add();

    void		initFonts();
    IlvFont*		findFont(const char*);
    // ____________________________________________________________
    IlvDisplayInternal	_internal;
    IlvDisplayConfig*	_config;
    char*		_name;	   // Name of the Display.
    char*		_classname;// ClassName of the Display.
    IlBoolean		_owner;
    IlvPort*		_device;
    IlBoolean		_dumping;
    IlBoolean		_initialised;
    IlvDim		_max_width, _max_height;
    IlUShort		_depth;
    IlAny		_root;	   // Root Window.
    IlBoolean		_useRightButtonValue;
    IlvAntialiasingMode _antialias;
    IlvBitmap*		_default_bitmap;
    IlAny		_colormap; // Colormap.
    IlvColorHashTable*	_all_colors;
    IlList*		_all_mutablecolors;
    char*		_home;	   // Stores IlvHome string.
    IlPathName*		_homePath; // Stores IlvHome path.
    IlPathList*		_pathList; // Paths.
    char*		_paths;	   // Buffer for getPath.
    int			_pathsSize;// Size of the previous buffer.

    // ____________________________________________________________
    IlvPalette*		 _default_palette;
    IlvPalette*		 _default_gadget_palette;
    IlvHashTablePalette* _all_palettes;
    // Default Colors _____________________________________________
    IlvColor*		_default_background;
    IlvColor*		_default_foreground;
    // Default Fonts ______________________________________________
    IlvFont* 		_default_font,
	   *		_default_normal_font,
	   * 		_default_bold_font,
	   * 		_default_italic_font,
	   * 		_default_large_font;
    IlStringHashTable* _all_fonts,
		     * _all_font_aliases;
    IlUShort		_familyNamesCount;
    char**		_familyNames;
    // Default Patterns ___________________________________________
    IlvPattern*		_solid,
	      *		_clear,
	      * 	_dark4,
	      * 	_dark3,
	      * 	_dark2,
	      * 	_dark1,
	      * 	_gray,
	      *		_light1,
	      *		_light2,
	      *		_light3,
	      *		_light4,
	      *		_diaglr,
	      *		_diagrl,
	      *		_horiz,
	      *		_vert,
	      *		_cross;
    IlList*		_all_patterns;
    IlList*		_all_colorpatterns;
    IlList*		_all_gradientpatterns;
    IlList*		_all_gradientaliaspatterns;
    IlList*		_all_bitmaps;

    // Default Cursors ____________________________________________
    IlvCursor*		_default_cursor,
	     *		_wait_cursor,
	     *		_cross_cursor,
	     *		_beam_cursor,
	     *		_sizing_cursor,
	     *		_hsizing_cursor,
	     *		_vsizing_cursor,
	     *		_neswsizing_cursor,
	     *		_nwsesizing_cursor;
    IlList*		_all_cursors;

    // Default Line Styles ________________________________________
    IlvLineStyle*	_solid_style,
		*	_dot,
		*	_dash,
		*	_dashdot,
		*	_dashdoubledot,
		*	_alternate,
		*	_doubledot,
		*	_longdash;
    IlList*		_all_linestyles;

    // Utilities __________________________________________________
    IlvBitmap*		_rootport;

#if defined(X11)
    IlAny		_topshell;
    int			_file_descriptor;
    int			_screen;
    IlAny		_default_depth1_palette;
    IlUInt		_allBitPlanesGroupsMask;
    IlUInt		_bitPlanesGroupsMask;
    IlvXColormap*	_alternateColormap;
#endif /* X11 */
#if defined(WINDOWS)
    IlBoolean		_errorFlag;

    const char*		findColorName(IlvIntensity,
				      IlvIntensity,
				      IlvIntensity) const;
    IlList*		_resources;

    IlvPalette* 	_transparentPalette;
    IlvPalette* 	_whiteGhostPalette;
    IlvPalette* 	_blackGhostPalette;
    IlArray 		_transpFrontViews;
#endif /* WINDOWS */
    IlInt		_errorCode;
    IlvSystemPort*	_drawingPort;
    IlvBitmap*		_monochromeBuffer;
    IlvBitmap*		_screenBuffer;
    IlList		_grabList;
    IlvEvent		_lastButtonEvent;
    IlvLookStyle	_currentLook;
    IlvLookFeelHandler*	_currentLookFeel;
    IlList		_looks;
    IL_MUTABLE std::list<IlvStyleSheet*>* _styleSheets;
    IlSymbol*		_currentLanguage;
    IlvMessageDatabase*	_database;
    IlAny		_layoutAttributes;
    IlvHolderCallback	_lookCallback;	    // Callback set by the holder.
    IlvHolderCallback	_languageCallback;  // Callback set by the holder.
    IlvLayoutCallback	_layoutCallback;    // Callback set by the holder.
    IlAList		_lookCallbacks;     // Callbacks set by user.
    IlAList		_languageCallbacks; // Callbacks set by user.
    IlAList		_layoutCallbacks;   // Callbacks set by user.
    IlvView*		_focusView;
    IlBoolean		_loseFocusFlag;
    IlInt		_bmpMsgMode;
    IlAny		_bidiInfo;		// ILVBIDI
    IlvLocaleExtension*		_locale;	// For future extension.
    IlvDisplayExtension*	_extension;	// For future extension.
    IlHashTable*	_extValues;
    IlAny		_toolTipConfig;
    IlAny		_itemConfig;
};

// --------------------------------------------------------------------------
//    IlvTransformer
// --------------------------------------------------------------------------
typedef IlDouble IlvTransfoParam;

class ILVDSPEXPORTED IlvTransformer
{
public:
    IlvTransformer();
    IlvTransformer(IlvTransfoParam m11, IlvTransfoParam m12,
		   IlvTransfoParam m21, IlvTransfoParam m22,
		   IlvTransfoParam x0,	IlvTransfoParam y0);
    IlvTransformer(const IlvPoint& center, IlvTransfoParam angle);
    IlvTransformer(IlvTransfoParam sx,
		   IlvTransfoParam sy,
		   IlvPoint* point = 0);
    IlvTransformer(const IlvRect& src, const IlvRect& dst);
    IlvTransformer(const IlvPoint& delta);
    // ____________________________________________________________
    IlBoolean		isBad() const;
    void		apply(IlvPoint& p) const;
    void		apply(IlvFloatPoint& p) const;
    void		apply(IlvDoublePoint& p) const;
    void		apply(IlvRect& rect) const;
    void		apply(IlUInt count, IlvPoint* points) const;
    void		applyAndFill(IlvRect& rect) const;
    void		deltaApply(IlvPoint& p) const;
    void		compose(const IlvTransformer& t);
    IlBoolean		computeInverse(IlvTransformer& t) const;
    IlBoolean		compute(const IlvRect& src, const IlvRect& dst);
    // Find easiest possible transformation. ______________________
    IlBoolean		isIdentity() const;
    inline IlBoolean	isTranslation () const
	{ return _istranslation; }
    inline IlBoolean	isScale() const
	{ return _isscale; }
    inline IlDouble	getDeterminant() const
	{ return _determinant; }
    // ____________________________________________________________
    IlBoolean		inverse(IlvPoint& p) const;
    IlBoolean		inverse(IlvFloatPoint& p) const;
    IlBoolean		inverse(IlvRect& rect) const;
    // ____________________________________________________________
    void		setValues(IlvTransfoParam  x0,  IlvTransfoParam	y0);
    void		setValues(IlvTransfoParam, IlvTransfoParam,
				  IlvTransfoParam, IlvTransfoParam);
    void		setValues(IlvTransfoParam  m11, IlvTransfoParam	m12,
				  IlvTransfoParam  m21, IlvTransfoParam	m22,
				  IlvTransfoParam  x0,  IlvTransfoParam	y0);
    void		getValues(IlvTransfoParam& x0,
				  IlvTransfoParam& y0) const;
    void		getValues(IlvTransfoParam&,
				  IlvTransfoParam&,
				  IlvTransfoParam&,
				  IlvTransfoParam&) const;
    void		getValues(IlvTransfoParam& m11,
				  IlvTransfoParam& m12,
				  IlvTransfoParam& m21,
				  IlvTransfoParam& m22,
				  IlvTransfoParam& x0,
				  IlvTransfoParam& y0)  const;
    // ____________________________________________________________
    void		translate(IlvTransfoParam dx, IlvTransfoParam dy);
    void		scale(IlvTransfoParam fixedx, IlvTransfoParam fixedy,
			      IlvTransfoParam sx,     IlvTransfoParam sy);
    void		rotate(IlvTransfoParam centerx,
			       IlvTransfoParam centery,
			       IlvTransfoParam angle);
    inline IlBoolean isSimilar(const IlvTransformer& other) const
	{
	    IlvTransformer t;
	    if (computeInverse(t)) {
		t.compose(other);
		return t.isIdentity();
	    }
	    else {
		return IlFalse;
	    }
	}
protected:
    void		updateFlags();

    IlDouble		_x11, _x12, _x21, _x22, _x0, _y0;
    IlDouble		_determinant;
    IlBoolean		_istranslation;
    IlBoolean		_isscale;
};

extern "C" {
ILVDSPEXPORTEDFUNCTION(const char*) IlvGetDefaultHome();
ILVDSPEXPORTEDFUNCTION(void)	    IlvSetDefaultHome(const char*);
}

extern "C" {
ILVDSPEXPORTEDFUNCTION(IlvDisplay*) IlvGetDisplay(IlAny);
ILVDSPEXPORTEDFUNCTION(int)	    IlvGetVersion();
ILVDSPEXPORTEDFUNCTION(const char*) IlvGetSystem();
}

extern "C" {
ILVDSPEXPORTEDFUNCTION(void) IlvPrint(const char*, ...);
ILVDSPEXPORTEDFUNCTION(void) IlvWarning(const char*, ...);
ILVDSPEXPORTEDFUNCTION(void) IlvFatalError(const char*, ...);
}

inline const char*
IlvGetMessage(IlvDisplay* display, const char* label)
{
    return display->getMessage(label);
}

extern "C" {
ILVDSPEXPORTEDFUNCTION(unsigned long)
IlvSetCurrentCharSet(unsigned long);
}

extern "C" {
ILVDSPEXPORTEDFUNCTION(IlBoolean) IlvSetLanguage();
ILVDSPEXPORTEDFUNCTION(IlvLocaleExtension*) IlvSetLocale(const char* = 0);
}

#if !defined(__Ilv_Base_Port_H)
#  include <ilviews/base/port.h>
#endif

ILVDSPMODULEINIT(ilv);
#endif /* !__Ilv_Ilv_H */
