// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/port.h
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
// Declaration of the IlvPort and IlvBitmap classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Port_H
#define __Ilv_Base_Port_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#  include <ilviews/intrface/value.h>
#endif

class IlvSystemPort;
class IlvBidiString; // ILVBIDI
class IlvBitmapData;

// --------------------------------------------------------------------------
//    IlvPort
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvPort : public IlvValueInterface
{
public:
    IlvPort(IlvDisplay* display = 0)
	: _display(display),
	  _width(0),
	  _height(0),
	  _alpha(IlvFullIntensity),
	  _antialias(IlvDefaultAntialiasingMode)
    {}
    virtual ~IlvPort();

    inline IlvDisplay*	getDisplay() const { return _display; }
    inline IlvDim	width() const { return _width; }
    inline IlvDim	height() const { return _height; }
    inline IlvIntensity	getAlpha() const { return _alpha; }
    inline void		setAlpha(IlvIntensity alpha) { _alpha = alpha; }
    void		composeAlpha(IlvIntensity alpha);
    inline
    IlvAntialiasingMode	getAntialiasingMode() const { return _antialias; }
    inline void		setAntialiasingMode(IlvAntialiasingMode mode)
			{
			    _antialias = mode;
			}
    inline void		size(IlvDim& w, IlvDim& h) const
			{
			    w = _width;
			    h = _height;
			}
    // ____________________________________________________________
    virtual IlBoolean	isASystemPort() const;
    virtual IlBoolean	isAnAbstractView() const;
    virtual IlBoolean	isABitmap() const;
    virtual IlBoolean	isADevice() const;
    virtual IlBoolean	isBad() const = 0;
    virtual IlBoolean	initDevice(const char*	filename,
				   IlvRect*	clip = 0) = 0;
    inline IlBoolean	init(const char* filename, IlvRect* bbox = 0)
			{
			    return initDevice(filename, bbox);
			}
    virtual void	end() = 0;
    virtual IlBoolean	newPage()  const = 0;
    virtual void	setTransformer(const IlvTransformer& t) = 0;
    virtual void	send(const char* string) const = 0;
    virtual void	clip(const IlvRect* rect) const = 0;
    virtual void	clip(const IlvRegion* region) const = 0;

    virtual void	drawPoint(const IlvPalette*	palette,
				  const IlvPoint&	point) const = 0;
    virtual void	drawPoints(const IlvPalette*	palette,
				   IlUInt		count,
				   const IlvPoint*	points) const;
    virtual void	drawLine(const IlvPalette*	palette,
				 const IlvPoint&	point1,
				 const IlvPoint&	point2) const = 0;
    virtual void	drawSegments(const IlvPalette*	palette,
				     IlUInt		count,
				     const IlvPoint*	from,
				     const IlvPoint*	to) const;
    virtual void	drawPolyLine(const IlvPalette*	palette,
				     IlUInt		count,
				     const IlvPoint*	points) const = 0;
    virtual void	drawPolyLine(const IlvPalette*		palette,
				     const IlvPoint&		first,
				     IlUInt			count,
				     const IlvDeltaPoint*	others) const;
    virtual void	fillPolyLine(const IlvPalette*	palette,
				     IlUInt		count,
				     const IlvPoint*	points,
				     IlBoolean convex = IlFalse) const = 0;
    virtual void	fillPolyLine(const IlvPalette*		palette,
				     const IlvPoint&		first,
				     IlUInt			count,
				     const IlvDeltaPoint*	others,
				     IlBoolean convex = IlFalse) const;
    virtual void	drawRectangle(const IlvPalette*	palette,
				      const IlvRect&	rect) const;
    virtual void	fillRectangle(const IlvPalette*	palette,
				      const IlvRect&	rect) const;
    virtual void	drawArc(const IlvPalette*	palette,
				const IlvRect&		rect,
				IlFloat			start,
				IlFloat			range) const = 0;
    virtual void	fillArc(const IlvPalette*	palette,
				const IlvRect&		rect,
				IlFloat			start,
				IlFloat			range) const = 0;
    virtual void	drawBitmap(const IlvPalette*	palette,
				   const IlvSystemPort*	src,
				   const IlvRect&	from,
				   const IlvPoint&	to) const = 0;
    virtual void	drawTransparentBitmap(const IlvPalette* palette,
					      const IlvSystemPort* src,
					      const IlvRect& from,
					      const IlvPoint& to) const = 0;
    virtual void	stretchBitmap(const IlvPalette*	palette,
				      const IlvPoint&	to,
				      const IlvBitmap*	src,
				      const IlvTransformer& t,
				      const IlvRect*	clip = 0)const = 0;
    virtual void	stretchTransparentBitmap(const IlvPalette* palette,
						 const IlvPoint& to,
						 const IlvBitmap* src,
						 const IlvTransformer& t,
						 const IlvRect* clip=0)const=0;
    virtual void	drawString(const IlvPalette* palette,
				   const IlvPoint& position,
				   const char* string,
				   int length,
				   IlvPosition align = IlvLeft) const = 0;
    virtual void	drawIString(const IlvPalette* palette,
				    const IlvPoint& position,
				    const char* string,
				    int length,
				    IlvPosition align = IlvLeft) const = 0;
    virtual void	drawTransformedString(const IlvPalette* palette,
					      const char* string,
					      int length,
					      const IlvTransformer& t,
					      const IlvRegion*
					      clip = 0) const = 0;
    // Drawing functions that rely on previous ones.
    virtual void	clearArea(const IlvRect& rect,
				  IlBoolean	 reDraw = IlFalse) const;
    virtual void	clearArea(const IlvRegion& region,
				  IlBoolean reDraw = IlFalse) const;
    virtual void	drawRoundRectangle(const IlvPalette*	palette,
					   const IlvRect&	rect,
					   IlUShort		radius) const;
    virtual void	fillRoundRectangle(const IlvPalette*	palette,
					   const IlvRect&	rect,
					   IlUShort		radius) const;
    virtual void	fillPaths(const IlvPalette*	palette,
				  IlUInt		count,
				  const IlvPointArray*	pathArray) const;
    virtual void	stretchBitmap(const IlvPalette*	palette,
				      const IlvRect&	from,
				      const IlvBitmap*	src,
				      const IlvRect*	clip = 0) const = 0;
    virtual void	stretchTransparentBitmap(const IlvPalette* palette,
						 const IlvRect& from,
						 const IlvBitmap* src,
						 const IlvRect*
						 clip = 0) const = 0;
    virtual void	drawBitmap(const IlvPalette*,
				   const IlvBitmap*,
				   const IlvRect&,
				   const IlvRect&,
				   const IlvRegion* = 0,
				   IlvPosition = IlvCenter,
				   IlBoolean   = IlFalse) const;
    virtual void	drawBitmap(const IlvPalette* palette,
				   const IlvBitmap* src,
				   const IlvRect& drawRect,
				   const IlvRegion* clip = 0,
				   IlvPosition alignment = IlvCenter,
				   IlBoolean transparent = IlFalse) const;
    virtual void	drawArrow(const IlvPalette*	palette,
				  const IlvPoint&	from,
				  const IlvPoint&	to,
				  IlFloat		position) const;
    virtual void	drawMarker(const IlvPalette* palette,
				   const IlvPoint& location,
				   IlvMarkerType type = IlvMarkerSquare,
				   IlUShort size = IlvDefaultMarkerSize) const;
    virtual void	drawShadowRectangle(const IlvPalette* palette,
					    const IlvPalette* invertedPalette,
					    const IlvRect& bbox,
					    IlUShort thickness,
					    IlvPosition shadowPosition,
					    const IlvRegion* clip = 0) const;
    virtual void	drawReliefPolyline(const IlvPalette*,
					   const IlvPalette*,
					   IlUInt,
					   IlvPoint*,
					   IlUShort,
					   IlBoolean = IlFalse,
					   const IlvRegion* = 0) const;
    virtual void	drawReliefRectangle(const IlvPalette* palette,
					    const IlvPalette* invertedPalette,
					    const IlvPalette* topShade,
					    const IlvPalette* bottomShade,
					    const IlvRect& bbox,
					    IlUShort thickness,
					    const IlvRegion* clip = 0) const;
    virtual void	drawReliefPolygon(const IlvPalette*,
					  const IlvPalette*,
					  const IlvPalette*,
					  IlUInt,
					  IlvPoint*,
					  IlUShort,
					  const IlvRegion* = 0) const;
    virtual void	drawOutlineRectangle(const IlvPalette*	outlinePalette,
					     const IlvPalette*	fillPalette,
					     const IlvRect&	rect,
					     const IlvRegion*	clip = 0)const;
    virtual void	drawReliefDiamond(const IlvPalette*,
					  const IlvPalette* invertedPalette,
					  const IlvPalette* topShade,
					  const IlvPalette* bottomShade,
					  const IlvRect& bbox,
					  IlUShort thickness,
					  const IlvRegion* clip = 0) const;
    virtual void	drawReliefArrow(IlvRect,
					IlvDim,
					IlvOrientation,
					const IlvPalette*,
					const IlvPalette*,
					const IlvPalette*,
					const IlvRegion* = 0) const;
    virtual void	drawWChar(const IlvPalette*,
				  const IlvPoint&,
				  const IlvWChar*,
				  int,
				  IlvAlignment = IlvLeft) const = 0;
    virtual void	drawIWChar(const IlvPalette*,
				   const IlvPoint&,
				   const IlvWChar*,
				   int,
				   IlvAlignment = IlvLeft) const = 0;
    virtual void	drawLabel(const IlvPalette*	palette,
				  const char*		label,
				  int			length,
				  const IlvRect&	drawRect,
				  const IlvRegion*	clip = 0,
				  IlvPosition		align=IlvCenter)const;
    virtual void	drawMnemonicLabel(const IlvPalette*	palette,
					  const char*		label,
					  const IlvRect&	drawRect,
					  const IlvRegion*	clip  = 0,
					  IlvPosition align = IlvCenter,
					  IlBoolean underline = IlTrue) const;
    virtual void	drawILabel(const IlvPalette*	palette,
				   const char*		label,
				   int			length,
				   const IlvRect&	drawRect,
				   const IlvRegion*	clip = 0,
				   IlvPosition		align=IlvCenter)const;
    virtual void	drawPaths(const IlvPalette*	palette,
				  IlUInt		count,
				  const IlvPointArray*	paths) const;
    virtual void	drawBezier(const IlvPalette*	palette,
				   IlUInt		count,
				   const IlvPoint*	points) const;
    virtual void	drawClosedBezier(const IlvPalette*	palette,
					 IlUInt			count,
					 const IlvPoint*	points) const;
    virtual void	fillBezier(const IlvPalette*	palette,
				   IlUInt		count,
				   const IlvPoint*	points) const;

    // ILVBIDI
    virtual void	drawString(const IlvPalette* pal,
				   const IlvPoint& p,
				   const IlvBidiString* s,
				   int length,
				   IlvAlignment align = IlvLeft) const = 0;
    virtual void	drawIString(const IlvPalette* pal,
				    const IlvPoint& p,
				    const IlvBidiString* s,
				    int length,
				    IlvAlignment align = IlvLeft) const = 0;
    virtual void	drawTransformedString(const IlvPalette* pal,
					      const IlvBidiString* label,
					      int length,
					      const IlvTransformer& t,
					      const IlvRegion* clip=0)const=0;
    virtual void	drawLabel(const IlvPalette* palette,
				  const IlvBidiString* label,
				  int length,
				  const IlvRect& drawrect,
				  const IlvRegion* region = 0,
				  IlvPosition position = IlvCenter) const;
    virtual void	drawMnemonicLabel(const IlvPalette* palette,
					  const IlvBidiString* label,
					  const IlvRect& drawrect,
					  const IlvRegion* region = 0,
					  IlvPosition position = IlvCenter,
					  IlBoolean  underline = IlTrue) const;
    virtual void	flushRedraw();
    // ILVBIDI
    virtual void        stretchBitmapData(const IlvPalette*	palette,
					  const IlvBitmapData*	src,
					  const IlvRect&	from,
					  const IlvRect&	to,
					  IlBoolean opaque = IlFalse)const = 0;

protected:
    IlvDisplay*		_display;
    IlvDim		_width;
    IlvDim		_height;
    IlvIntensity	_alpha;
    IlvAntialiasingMode _antialias;
};



// --------------------------------------------------------------------------
//    IlvPushAlpha
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvPushAlpha
{
public:
    inline
    IlvPushAlpha(IlvPort& port, IlvIntensity alpha)
	: _port(port),
	  _oldAlpha(port.getAlpha())
    {
	_port.composeAlpha(alpha);
    }
    ~IlvPushAlpha() { _port.setAlpha(_oldAlpha); }

private:
    // This member function is intentionally not defined.
    IlvPushAlpha(const IlvPushAlpha&);
    // This member function is intentionally not defined.
    IlvPushAlpha& operator=(const IlvPushAlpha&);

    IlvPort&		_port;
    IlvIntensity	_oldAlpha;
};

// --------------------------------------------------------------------------
//    IlvSystemPort
// --------------------------------------------------------------------------
class IlvDC;
class ILVDSPEXPORTED IlvSystemPort : public IlvPort
{
    friend class IlvDisplay;
    friend class IlvDC;
public:
    IlvSystemPort(IlvDisplay* display)
	: IlvPort(display),
#if defined(WINDOWS)
	  _owner(IlFalse),
	  _hasPalette(IlFalse),
	  _dc(0),
	  _ilvdc(0),
#endif /* WINDOWS */
	  _viewport(0),
	  _xOffset(0),
	  _yOffset(0)
    {}
#if defined(WINDOWS)
    IlvSystemPort(IlvDisplay*		display,
		  IlvWindowsHandle	HDC,
		  IlvDim		width  = 0,
		  IlvDim		height = 0);
    IlvWindowsHandle	getDC() const;
    inline void		releaseDC() { releaseIlvDC(); }
#endif /* WINDOWS */
    virtual ~IlvSystemPort();

    virtual IlUShort	depth() const;
    inline IlvViewPort	viewPort() const { return _viewport; }
    virtual IlBoolean	isASystemPort() const;
    virtual IlBoolean	isABitmap() const;
    virtual IlBoolean	isBad() const;
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
#if defined(WINDOWS) 
    IlvDC*		getIlvDC();
    inline IlBoolean	checkIlvDC(const IlvDC* ilvdc) const
			{
			    return _ilvdc == ilvdc ? IlTrue : IlFalse;
			}
    void		releaseIlvDC();
    virtual
    IlvWindowsHandle	computeDC();
    virtual void	deleteDC();
    void		cleanDC();
#endif /* WINDOWS */
    virtual
    IlvClassInfo*	getClassInfo() const;
    virtual IlBoolean	applyValue(const IlvValue&);

    virtual IlBoolean	initDevice(const char*, IlvRect* = 0);
    virtual void	end();
    virtual IlBoolean	newPage() const;
    virtual void	setTransformer(const IlvTransformer&);
    virtual void	send(const char*) const;
    virtual void	clip(const IlvRect*) const;
    virtual void	clip(const IlvRegion*) const;

    virtual void	drawPoint(const IlvPalette*,
				  const IlvPoint&) const;
    virtual void	drawPoints(const IlvPalette*,
				   IlUInt,
				   const IlvPoint*) const;
    virtual void	drawLine(const IlvPalette*,
				 const IlvPoint&,
				 const IlvPoint&) const;
    virtual void	drawSegments(const IlvPalette*,
				     IlUInt,
				     const IlvPoint*,
				     const IlvPoint*) const;
    virtual void	drawPolyLine(const IlvPalette*,
				     IlUInt,
				     const IlvPoint*) const;
    virtual void	drawPolyLine(const IlvPalette*,
				     const IlvPoint&,
				     IlUInt,
				     const IlvDeltaPoint*) const;
    virtual void	fillPolyLine(const IlvPalette*,
				     IlUInt,
				     const IlvPoint*,
				     IlBoolean = IlFalse) const;
    virtual void	fillPolyLine(const IlvPalette*,
				     const IlvPoint&,
				     IlUInt,
				     const IlvDeltaPoint*,
				     IlBoolean = IlFalse) const;
    virtual void	drawRectangle(const IlvPalette*,
				      const IlvRect&) const;
    virtual void	fillRectangle(const IlvPalette*,
				      const IlvRect&) const;
    virtual void	drawArc(const IlvPalette*,
				const IlvRect&,
				IlFloat,
				IlFloat) const;
    virtual void	fillArc(const IlvPalette*,
				const IlvRect&,
				IlFloat,
				IlFloat) const;
    virtual void	drawBitmap(const IlvPalette*,
				   const IlvBitmap*,
				   const IlvRect&,
				   const IlvRect&,
				   const IlvRegion* = 0,
				   IlvPosition = IlvCenter,
				   IlBoolean = IlFalse) const;
    virtual void	drawBitmap(const IlvPalette*,
				   const IlvSystemPort*,
				   const IlvRect&,
				   const IlvPoint&) const;
    virtual void	drawTransparentBitmap(const IlvPalette*,
					      const IlvSystemPort*,
					      const IlvRect&,
					      const IlvPoint&) const;
    virtual void	stretchBitmap(const IlvPalette*,
				      const IlvPoint&,
				      const IlvBitmap*,
				      const IlvTransformer&,
				      const IlvRect* = 0) const;
    virtual void	stretchTransparentBitmap(const IlvPalette*,
						 const IlvPoint&,
						 const IlvBitmap*,
						 const IlvTransformer&,
						 const IlvRect* = 0) const;
    virtual void	drawBitmap(const IlvPalette*,
				   const IlvBitmap*,
				   const IlvRect&,
				   const IlvRegion* = 0,
				   IlvPosition = IlvCenter,
				   IlBoolean = IlFalse) const;
    virtual void	drawString(const IlvPalette*,
				   const IlvPoint&,
				   const char*,
				   int,
				   IlvPosition = IlvLeft) const;
    virtual void	drawIString(const IlvPalette*,
				    const IlvPoint&,
				    const char*,
				    int,
				    IlvPosition = IlvLeft) const;
    virtual void	drawTransformedString(const IlvPalette*,
					      const char*,
					      int,
					      const IlvTransformer&,
					      const IlvRegion* = 0) const;
    virtual void	clearArea(const IlvRect&,
				  IlBoolean = IlFalse) const;
    virtual void	clearArea(const IlvRegion&,
				  IlBoolean = IlFalse) const;
    virtual void	stretchBitmap(const IlvPalette*,
				      const IlvRect&,
				      const IlvBitmap*,
				      const IlvRect* = 0) const;
    virtual void	stretchTransparentBitmap(const IlvPalette*,
						 const IlvRect&,
						 const IlvBitmap*,
						 const IlvRect* = 0) const;
    virtual void	drawRoundRectangle(const IlvPalette*,
					   const IlvRect&,
					   IlUShort) const;
    virtual void	fillRoundRectangle(const IlvPalette*,
					   const IlvRect&,
					   IlUShort) const;
    virtual void	drawWChar(const IlvPalette*,
				  const IlvPoint&,
				  const IlvWChar*,
				  int,
				  IlvAlignment = IlvLeft) const;
    virtual void	drawIWChar(const IlvPalette*,
				   const IlvPoint&,
				   const IlvWChar*,
				   int,
				   IlvAlignment = IlvLeft) const;
    virtual void	fillPaths(const IlvPalette*,
				  IlUInt,
				  const IlvPointArray*) const;
#if defined(WINDOWS)
    virtual void	drawBezier(const IlvPalette*,
				   IlUInt,
				   const IlvPoint*) const;
    virtual void	drawClosedBezier(const IlvPalette*,
					 IlUInt,
					 const IlvPoint*) const;
#endif /* WINDOWS */
    // ILVBIDI
    virtual void	drawString(const IlvPalette*	pal,
				   const IlvPoint&	p,
				   const IlvBidiString*	s,
				   int			length,
				   IlvAlignment		align = IlvLeft) const;
    virtual void	drawIString(const IlvPalette*	pal,
				    const IlvPoint&	p,
				    const IlvBidiString* s,
				    int			length,
				    IlvAlignment	align = IlvLeft) const;
    virtual void	drawTransformedString(const IlvPalette* pal,
					      const IlvBidiString* label,
					      int length,
					      const IlvTransformer& t,
					      const IlvRegion* clip = 0) const;
    // ILVBIDI
    // bitmap data
    static
    IlvBitmapData*	GetBitmapData(IlvSystemPort* port,
				      const IlvRect* rect = 0);
    // draw bitmap data
    virtual void        stretchBitmapData(const IlvPalette*	palette,
					  const IlvBitmapData*	src,
					  const IlvRect&	from,
					  const IlvRect&	to,
					  IlBoolean opaque = IlFalse) const;

protected:
#if defined(WINDOWS)
    virtual void	initIlvDC();
    void		cleanPort();
    virtual void	internalCleanDC() {}

    IlBoolean		_owner;
    IlBoolean		_hasPalette;
    IlvWindowsHandle	_dc;
    IlvDC*		_ilvdc;
#endif /* WINDOWS */
    IlvViewPort		_viewport;
    IlvPos		_xOffset;
    IlvPos		_yOffset;

    IlvSystemPort () :
#if defined(WINDOWS)
      _owner(IlFalse),
      _hasPalette(IlFalse),
      _dc(0),
      _ilvdc(0),
#endif /* WINDOWS */
      _viewport(0),
      _xOffset(0),
      _yOffset(0)
    {}
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvSystemPortWrapper : public IlvSystemPort
{
public:
    IlvSystemPortWrapper() : IlvSystemPort(0), _systemPort(0) {}

    inline
    IlvSystemPort*	getSystemPort() const { return _systemPort; }
    inline void		setSystemPort(IlvSystemPort* port)
			{
			    _systemPort = port;
			    if (_systemPort) {
				_display  = _systemPort->getDisplay();
				_width    = _systemPort->width();
				_height   = _systemPort->height();
				_alpha    = _systemPort->getAlpha();
				_antialias= _systemPort->getAntialiasingMode();
			    }
			    else {
				_display	= 0;
				_width		= 0;
				_height		= 0;
				_alpha		= IlvFullIntensity;
				_antialias	= IlvDefaultAntialiasingMode;
			    }
			}

protected:
    IlvSystemPort*	_systemPort;
};

// --------------------------------------------------------------------------
// IlvBitmapAnimationHandler
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvBitmapAnimationHandler
{
public:
    virtual ~IlvBitmapAnimationHandler();

    virtual IlBoolean	isLastFrame(IlUInt frame) const;
    virtual IlUInt	getFrameDelay(IlUInt frame) const = 0;
    virtual IlUInt	getFramesCount() const = 0;
    virtual void	drawFrame(IlvPort*		dst,
				  IlvPalette*		palette,
				  const IlvRect&	rect,
				  IlUInt		frame,
				  const IlvRegion*	clip,
				  IlvPosition		alignment,
				  IlBoolean		transparent) const = 0;
};

// --------------------------------------------------------------------------
//    IlvBitmap
// --------------------------------------------------------------------------
#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif
#if defined(WINDOWS)
class IlvWindowsBitmap;
typedef IlvWindowsBitmap* IlvBitmapInternal;
#else  /* !WINDOWS */
typedef IlAny IlvBitmapInternal;
#endif /* !WINDOWS */
class ILVDSPEXPORTED IlvBitmap : public IlvSystemPort
{
    friend class IlvDisplay;
    friend class IlvDC;
    friend class IlvGDIPlusPort;
public:
    IlvBitmap(IlvDisplay*	display,
	      IlvDim		width,
	      IlvDim		height,
	      IlUShort		depth,
	      unsigned char*	data,
	      IlBoolean		bitOrder  = IlTrue,
	      IlUShort		padding = 32);
    IlvBitmap(IlvDisplay*, const IlvBitmapData*);
    IlvBitmap(IlvDisplay*,
	      IlvDim,
	      IlvDim,
	      IlUShort,
	      unsigned char ILVHUGE*	data,
	      IlvColor*			bg,
	      IlvColor*			fg,
	      IlUShort			padding = 32);
    IlvBitmap(IlvDisplay*	display,
	      IlvDim		width,
	      IlvDim		height,
	      IlUShort		depth);
    enum MemoryType {
	NoMemory     = 0,
	VideoMemory  = 1,
	SystemMemory = 2
    };
#if defined(WINDOWS)
    IlvBitmap(IlvDisplay*	display,
	      IlvWindowsHandle	hBitmap,
	      IlBoolean		owner = IlFalse);

    MemoryType		getMemoryType() const;
#endif /* WINDOWS */
#if defined(WINDOWS)
    virtual
    IlvWindowsHandle	computeDC();
    virtual void	deleteDC();

protected:
    virtual void	initIlvDC();

public:
#endif /* WINDOWS */
    ~IlvBitmap ();

    void		lock();
    void		unLock();
    void		useColor(IlvColor* color);
    IlUShort		depth() const;
    virtual IlBoolean	isABitmap()  const;
    inline
    IlvBitmapInternal	getInternal() const { return _internal; }
    inline const char*	getName() const { return _name; }
    void		setName(const char* name);
    virtual IlBoolean	save(const char* filename) const;
    virtual IlBoolean	save(ILVSTDPREF ostream&) const;
    IlBoolean		saveAscii(const char* filename) const;
    inline IlInt	getTransparentColorIndex() const { return _tcIndex; }
    inline void		setTransparentColorIndex(IlInt tcIndex)
			{
			    _tcIndex = tcIndex;
			}
    inline IlvBitmap*	getMask() const { return _mask; }
    void		setMask(IlvBitmap* mask);
    // Not documented
    virtual IlBoolean	read(const char*	filename,
			     IlvPos		x = 0,
			     IlvPos		y = 0);
    inline IlUInt	count() const { return _refcount; }
    IlBoolean		computeMask();
    inline IlvBitmapAnimationHandler*	getAnimationHandler() const
					{
					    return _animationHandler;
					}
    inline void		setAnimationHandler(IlvBitmapAnimationHandler* handler)
			{
			    _animationHandler = handler;
			}
    void		drawFrame(IlvPort*		dst,
				  IlvPalette*		palette,
				  const IlvRect&	rect,
				  IlUInt		frame,
				  const IlvRegion*	clip,
				  IlvPosition		alignment,
				  IlBoolean		transparent) const;
protected:
#if defined(WINDOWS)
    IlBoolean		_owner;

    // GDI Plus stuff
    enum GdiPlusBitmapState {
	InvalidBitmap,
	TransparentBitmap,
	OpaqueBitmap
    };
    GdiPlusBitmapState	_gdiplusBitmapState;
    IlAny		_gdiplusBitmap;
    inline IlAny	getGdiPlusBitmap() const { return _gdiplusBitmap; }
    inline IlAny	getGdiPlusBitmap(IlBoolean t) const 
			{
			    return ((_gdiplusBitmapState
				     == TransparentBitmap && t) ||
				    (_gdiplusBitmapState
				     == OpaqueBitmap && !t))
				? _gdiplusBitmap
				: 0;
			}
    inline void		setGdiPlusBitmap(IlAny		bitmap,
					 IlBoolean	transparent)
			{
			    _gdiplusBitmap = bitmap;
			    _gdiplusBitmapState = bitmap
				? (transparent
				   ? TransparentBitmap
				   : OpaqueBitmap)
				: InvalidBitmap;
			}
    inline void		invalidateGdiPlusBitmap() 
			{
			    _gdiplusBitmapState = InvalidBitmap;
			}
#endif /* WINDOWS */

    IlvBitmap()
    : IlvSystemPort(),
#if defined(WINDOWS)
      _owner(IlFalse),
      _gdiplusBitmapState(InvalidBitmap),
      _gdiplusBitmap(0),
#endif /* WINDOWS */
      _name(0),
      _depth(0),
      _data(0),
      _internal(0),
      _refcount(0),
      _colors(),
      _tcIndex(-1),
      _mask(0),
      _animationHandler(0),
      _bmpData(0),
      _hasAlpha(IlFalse)
    {}

    char*		_name;
    IlUShort		_depth;
    unsigned char*	_data;
    IlvBitmapInternal	_internal;
    IlUInt		_refcount;
    IlList		_colors;
    IlInt		_tcIndex;
    IlvBitmap*		_mask;
    IlvBitmapAnimationHandler* _animationHandler;

    // ALPHA_BLEND
    IlvBitmapData*	_bmpData;
    IlBoolean		_hasAlpha;
    static IlBoolean	_UseAlpha;

    void		setBitmapData(IlvBitmapData*);
    void		setHasAlpha(IlBoolean);

public:
    IlvBitmapData*	getBitmapData() const;
    IlBoolean		hasAlpha() const;
    static IlBoolean	GetUseAlpha();
    static void		SetUseAlpha(IlBoolean);

    struct TmpUseAlpha
    {
	TmpUseAlpha(IlBoolean val) { _v = GetUseAlpha(); SetUseAlpha(val); }
	~TmpUseAlpha() { SetUseAlpha(_v); }
	IlBoolean	_v;
    };
};


enum IlvPtrnType {
    IlvPatternType = 0,
    IlvColorPatternType = 1,
    IlvGradientPatternType = 2,
    IlvLinearGradientPatternType = 3,
    IlvRadialGradientPatternType = 4
};

// --------------------------------------------------------------------------
//    IlvPattern
// --------------------------------------------------------------------------
#if defined(X11)
typedef IlvBitmap* IlvPatternInternal;
#elif defined(WINDOWS) /* !X11 */
class IlvWindowsPattern;
typedef IlvWindowsPattern* IlvPatternInternal;
#else  /* !X11 && !WINDOWS */
typedef IlAny IlvPatternInternal;
#endif /* !X11 && !WINDOWS */
class ILVDSPEXPORTED IlvPattern : public IlvResource
{
    friend class IlvDisplay;
public:
    IlvPattern(IlvDisplay*	display,
	       IlvDim		width,
	       IlvDim		height,
	       unsigned char*	data);
    IlvPattern(IlvBitmap* bitmap);
    ~IlvPattern();

    virtual IlvPtrnType	getPatternType() const;

    inline IlvDim	width() const { return _width; }
    inline IlvDim	height() const { return _height; }
    virtual IlUShort	depth()  const;
    unsigned char*	getBitmapData(IlUInt& size) const;
    void		putBitmapData(unsigned char* data, IlUInt size);
    inline
    IlvPatternInternal	getInternal() const
	{
	    return IL_REINTERPRETCAST(IlvPatternInternal, _internal);
	}

protected:
    IlvDim		_width;
    IlvDim		_height;

    IlvPattern(IlvDisplay* display, IlvDim witdh, IlvDim height)
	: IlvResource(display),
	  _width(witdh),
	  _height(height)
    {}
};

extern ILVDSPEXPORTEDFUNCTION(IlvPattern*)
IlvCreatePattern(IlvDisplay*, IlUShort data);
extern ILVDSPEXPORTEDFUNCTION(IlvPattern*)
IlvCreatePattern(IlvDisplay*, IlUInt d1);
extern ILVDSPEXPORTEDFUNCTION(IlvPattern*)
IlvCreatePattern(IlvDisplay*, IlUInt d1, IlUInt d2);
extern ILVDSPEXPORTEDFUNCTION(IlvPattern*)
IlvCreatePattern(IlvDisplay*,
		 IlUShort l1, IlUShort l2,
		 IlUShort l3, IlUShort l4);

// --------------------------------------------------------------------------
//    IlvColorPattern
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvColorPattern : public IlvPattern
{
    friend class IlvDisplay;
public:
    IlvColorPattern(IlvDisplay*    display,
		    IlvDim         w,
		    IlvDim         h,
		    IlUShort       depth,
		    unsigned char* data);
    IlvColorPattern(IlvBitmap* bitmap);
    ~IlvColorPattern();

    virtual IlvPtrnType	getPatternType() const;

    IlUShort		depth() const;

private:
    IlUShort		_depth;
};

// --------------------------------------------------------------------------
//    IlvColorStop
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvColorStop
{
public:

    IlvColorStop(IlvColor*	color,
		 IlFloat	offset,
		 IlvIntensity	alpha = IlvFullIntensity);
    IlvColorStop(IlvColorStop* colorStop);
    virtual ~IlvColorStop();

    inline IlvColor*	getColor() const { return _color; }
    void		setColor(IlvColor* color);
   inline IlFloat	getOffset() const { return _offset; }
    inline void		setOffset(IlFloat offset) { _offset = offset; }
    inline IlvIntensity	getAlpha() const { return _alpha; }
    inline void		setAlpha(IlvIntensity alpha) { _alpha = alpha; }
    virtual IlString	toString() const;

private:
    IlvColor* 		_color;
    IlFloat 		_offset;
    IlvIntensity	_alpha;

};

// --------------------------------------------------------------------------
//    IlvGradientPortBBoxManager
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvGradientPortBBoxManager
{
public:
    IlvGradientPortBBoxManager(IlvPalette*		palette,
			       IlvPort*			port,
			       const IlvTransformer*	t = 0);
    ~IlvGradientPortBBoxManager();

private:
    IlvGradientPattern*	_gradient;
    IlBoolean		_unSet;
};

// --------------------------------------------------------------------------
//    IlvGradientGeometry
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvGradientGeometry
{
    friend class IlvGradientPattern;
public:
    virtual ~IlvGradientGeometry();

    virtual IlString	toString() const;
    virtual IlvPtrnType	getPatternType() const;

    inline
    IlvGradientTransformMode	getTransformMode() const
				{
				    return _transformMode;
				}

    void		setTransformMode(IlvGradientTransformMode mode);

    inline
    IlvGradientAspectRatio	getAspectRatio() const
				{
				    return _aspectRatio;
				}

    void 		setAspectRatio(IlvGradientAspectRatio aspectRatio);
    void		computeAspectRatioBBox(IlvRect& rect);
    virtual void 	adjustValues();

    inline IlvRect 	getGraphicBBox() const { return _graphicBBox; }
    IlBoolean 		setGraphicBBox(IlvRect bbox);
    void 		unSetGraphicBBox();
    inline IlvRect 	getPortBBox() const { return _portBBox; }
    IlBoolean 		setPortBBox(IlvRect bbox);
    void 		unSetPortBBox();

private:
    IlvGradientPattern* getGradientPattern() const;
    void 		setGradientPattern(IlvGradientPattern* gradPat);

protected:

    IlvGradientGeometry(IlvGradientTransformMode	mode,
			IlvGradientAspectRatio		aspectRatio);

    IlvGradientTransformMode	_transformMode;
    IlvGradientAspectRatio	_aspectRatio;
    IlvGradientPattern*		_gradientPattern;
    IlBoolean			_freezePortBBox;
    IlvRect			_portBBox;
    IlBoolean			_freezeGraphicBBox;
    IlvRect			_graphicBBox;
};	    

// --------------------------------------------------------------------------
//    IlvLinearGradientGeometry
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvLinearGradientGeometry : public IlvGradientGeometry
{
public:

    IlvLinearGradientGeometry(
	IlvPoint startPoint,
	IlvPoint endPoint,
	IlvGradientTransformMode mode = IlvGradientTransformGraphic,
	IlvGradientAspectRatio aspectRatio = IlvGradientAspectRatioInside);
    virtual ~IlvLinearGradientGeometry();

    virtual IlString	toString() const;
    virtual IlvPtrnType	getPatternType() const;

    inline IlvPoint	getStartPoint() const { return _startPoint; }

    void		setStartPoint(IlvPoint start);


    inline IlvPoint	getEndPoint() const { return _endPoint; }

    void		setEndPoint(IlvPoint end);
    virtual void	adjustValues();

protected:
    IlvPoint		_startPoint;
    IlvPoint		_endPoint;
};

// --------------------------------------------------------------------------
//    IlvRadialGradientGeometry
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvRadialGradientGeometry : public IlvGradientGeometry
{
public:

    IlvRadialGradientGeometry(	
	IlvPoint startCenter,
	IlvDim startRadius,
	IlvPoint endCenter,
	IlvDim endRadius,
	IlvGradientTransformMode mode = IlvGradientTransformGraphic,
	IlvGradientAspectRatio aspectRatio = IlvGradientAspectRatioNo);
    virtual ~IlvRadialGradientGeometry();

    virtual IlString	toString() const;
    virtual IlvPtrnType	getPatternType() const;

    inline IlvPoint 	getStartCenter() const { return _startCenter; }
    void 		setStartCenter(IlvPoint center);
    inline IlvDim 	getStartRadius() const { return _startRadius; }
    void 		setStartRadius(IlvDim radius);
    inline IlvPoint 	getEndCenter() const { return _endCenter; }
    void 		setEndCenter(IlvPoint center);
    inline IlvDim 	getEndRadius() const { return _endRadius; }
    void 		setEndRadius(IlvDim radius);

    virtual void 	adjustValues();

protected:
    IlvPoint		_startCenter;
    IlvDim		_startRadius;
    IlvPoint		_endCenter;
    IlvDim		_endRadius;
};

// --------------------------------------------------------------------------
//    IlvGradientPattern
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvGradientPattern : public IlvPattern
{
    friend class IlvDisplay;
    friend class IlvGradientGeometry;

public:

    IlvGradientPattern(IlvDisplay*		display,
		       IlvColor*		start,
		       IlvColor*		end,
		       IlvDim			width,
		       IlvDim			height,
		       IlvGradientGeometry*	geometry,
		       IlvGradientSpread	spread,
		       const char*		alias = 0);

    IlvGradientPattern(IlvDisplay*		display,
		       IlvColorStop**		colorStops,
		       IlUInt			nColorStops,
		       IlvDim			width,
		       IlvDim			height,
		       IlvGradientGeometry*	geometry,
		       IlvGradientSpread	spread,
		       const char*		alias = 0);
    ~IlvGradientPattern();

    virtual IlvPtrnType	getPatternType() const;

    virtual IlString	toString() const;

    void		addColorStop(IlvColorStop* colorStop);
    IlUInt		getColorStopsCount() const;
    IlvColorStop*	getColorStop(IlUInt index) const;
    IlBoolean		removeColorStop(IlvColorStop* colorStop);
    IlBoolean		setColorStopOffset(IlvColorStop*	colorStop,
					   IlFloat		offset);
    void		setWidth(IlvDim width);
    void		setHeight(IlvDim height);
    inline
    IlvGradientSpread	getSpread() const { return _spread; }
    void		setSpread(IlvGradientSpread spread);
    inline const char*	getAlias() const { return _alias; }
    void		setAlias(const char* alias);
    inline
    IlvGradientGeometry* getGeometry() const { return _geometry; }

    void		setGeometry(IlvGradientGeometry* geometry);

private:
    void		updateResourceName();

protected:
    IlList			_colorStops;
    IlvGradientGeometry*	_geometry;
    IlvGradientSpread		_spread;
    const char*			_alias;
    IlvPtrnType			_type;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Inlines for compatibility.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawPoint(IlvPort*		dst,
		      const IlvPalette*	pal,
		      const IlvPoint&	p) const
{
    if (_dumping)
	_device->drawPoint(pal, p);
    else dst->drawPoint(pal, p);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawPoints(IlvPort*			dst,
		       const IlvPalette*	pal,
		       IlUInt			count,
		       const IlvPoint*		points) const
{
    if (_dumping)
	_device->drawPoints(pal, count, points);
    else dst->drawPoints(pal, count, points);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawLine(IlvPort*		dst,
		     const IlvPalette*	pal,
		     const IlvPoint&	p1,
		     const IlvPoint&	p2) const
{
    if (_dumping)
	_device->drawLine(pal, p1, p2);
    else dst->drawLine(pal, p1, p2);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawSegments(IlvPort*		dst,
			 const IlvPalette*	pal,
			 IlUInt			count,
			 const IlvPoint*	from,
			 const IlvPoint*	to) const
{
    if (_dumping)
	_device->drawSegments(pal, count, from, to);
    else dst->drawSegments(pal, count, from, to);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawPolyLine(IlvPort*		dst,
			 const IlvPalette*	pal,
			 IlUInt			count,
			 const IlvPoint*	points) const
{
    if (_dumping)
	_device->drawPolyLine(pal, count, points);
    else dst->drawPolyLine(pal, count, points);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawPolyLine(IlvPort*		dst,
			 const IlvPalette*	pal,
			 const IlvPoint&	first,
			 IlUInt			count,
			 const IlvDeltaPoint*	others) const
{
    if (_dumping)
	_device->drawPolyLine(pal, first, count, others);
    else dst->drawPolyLine(pal, first, count, others);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::fillPolyLine(IlvPort*		dst,
			 const IlvPalette*	pal,
			 IlUInt			count,
			 const IlvPoint*	points,
			 IlBoolean		convex) const
{
    if (_dumping)
	_device->fillPolyLine(pal, count, points, convex);
    else dst->fillPolyLine(pal, count, points, convex);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::fillPolyLine(IlvPort*		dst,
			 const IlvPalette*	pal,
			 const IlvPoint&	first,
			 IlUInt			count,
			 const IlvDeltaPoint*	others,
			 IlBoolean		convex) const
{
    if (_dumping)
	_device->fillPolyLine(pal, first, count, others, convex);
    else dst->fillPolyLine(pal, first, count, others, convex);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawRectangle(IlvPort*		dst,
			  const IlvPalette*	pal,
			  const IlvRect&	rect) const
{
    if (_dumping)
	_device->drawRectangle(pal, rect);
    else dst->drawRectangle(pal, rect);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::fillRectangle(IlvPort*		dst,
			  const IlvPalette*	pal,
			  const IlvRect&	rect) const
{
    if (_dumping)
	_device->fillRectangle(pal, rect);
    else dst->fillRectangle(pal, rect);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawRoundRectangle(IlvPort*		 dst,
			       const IlvPalette* pal,
			       const IlvRect&	 rect,
			       IlUShort	 	 radius) const
{
    if (_dumping)
	_device->drawRoundRectangle(pal, rect, radius);
    else dst->drawRoundRectangle(pal, rect, radius);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::fillRoundRectangle(IlvPort*		 dst,
			       const IlvPalette* pal,
			       const IlvRect&	 rect,
			       IlUShort	 	 radius) const
{
    if (_dumping)
	_device->fillRoundRectangle(pal, rect, radius);
    else dst->fillRoundRectangle(pal, rect, radius);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawArc(IlvPort*		dst,
		    const IlvPalette*	pal,
		    const IlvRect&	rect,
		    IlFloat		angle1,
		    IlFloat		angle2) const
{
    if (_dumping)
	_device->drawArc(pal, rect, angle1, angle2);
    else dst->drawArc(pal, rect, angle1, angle2);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::fillArc(IlvPort*		dst,
		    const IlvPalette*	pal,
		    const IlvRect&	rect,
		    IlFloat		angle1,
		    IlFloat		angle2) const
{
    if (_dumping)
	_device->fillArc(pal, rect, angle1, angle2);
    else dst->fillArc(pal, rect, angle1, angle2);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawBezier(IlvPort*			dst,
		       const IlvPalette*	pal,
		       IlUInt			count,
		       const IlvPoint*		points) const
{
    if (_dumping)
	_device->drawBezier(pal, count, points);
    else dst->drawBezier(pal, count, points);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawClosedBezier(IlvPort*		dst,
			     const IlvPalette*	pal,
			     IlUInt		count,
			     const IlvPoint*	points) const
{
    if (_dumping)
	_device->drawClosedBezier(pal, count, points);
    else dst->drawClosedBezier(pal, count, points);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::fillBezier(IlvPort*			dst,
		       const IlvPalette*	pal,
		       IlUInt			count,
		       const IlvPoint*		points) const
{
    if (_dumping)
	_device->fillBezier(pal, count, points);
    else dst->fillBezier(pal, count, points);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawPaths(IlvPort*			dst,
		      const IlvPalette*		pal,
		      IlUInt			count,
		      const IlvPointArray*	paths) const
{
    if (_dumping)
	_device->drawPaths(pal, count, paths);
    else dst->drawPaths(pal, count, paths);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::fillPaths(IlvPort*			dst,
		      const IlvPalette*		pal,
		      IlUInt			count,
		      const IlvPointArray*	paths) const
{
    if (_dumping)
	_device->fillPaths(pal, count, paths);
    else dst->fillPaths(pal, count, paths);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::copyArea(IlvPort*			dst,
		     const IlvPalette*		pal,
		     const IlvSystemPort*	src,
		     const IlvRect&		fromrect,
		     const IlvPoint&		to) const
{
    if (_dumping)
	_device->drawBitmap(pal, src, fromrect, to);
    else dst->drawBitmap(pal, src, fromrect, to);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::copyTransparentArea(IlvPort*		dst,
				const IlvPalette*	pal,
				const IlvSystemPort*	src,
				const IlvRect&		fromrect,
				const IlvPoint&		to) const
{
    if (_dumping)
	_device->drawTransparentBitmap(pal, src, fromrect, to);
    else dst->drawTransparentBitmap(pal, src, fromrect, to);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::copyStretchedBitmap(IlvPort*		dst,
				const IlvPalette*	pal,
				const IlvPoint&		to,
				const IlvBitmap*	b,
				const IlvTransformer&	t,
				const IlvRect*		clip) const
{
    if (_dumping)
	_device->stretchBitmap(pal, to, b, t, clip);
    else dst->stretchBitmap(pal, to, b, t, clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::copyStretchedTransparentBitmap(IlvPort*		 dst,
					   const IlvPalette*	 pal,
					   const IlvPoint&	 to,
					   const IlvBitmap*	 b,
					   const IlvTransformer& t,
					   const IlvRect*	 clip) const
{
    if (_dumping)
	_device->stretchTransparentBitmap(pal, to, b, t, clip);
    else dst->stretchTransparentBitmap(pal, to, b, t, clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawString(IlvPort*			dst,
		       const IlvPalette*	pal,
		       const IlvPoint&		p,
		       const char*		s,
		       int			length,
		       IlvAlignment		align) const
{
    if (_dumping)
	_device->drawString(pal, p, s, length, align);
    else dst->drawString(pal, p, s, length, align);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawIString(IlvPort*		dst,
			const IlvPalette*	pal,
			const IlvPoint&		p,
			const char*		s,
			int			length,
			IlvAlignment		align) const
{
    if (_dumping)
	_device->drawIString(pal, p, s, length, align);
    else dst->drawIString(pal, p, s, length, align);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawWChar(IlvPort*		dst,
		      const IlvPalette*	pal,
		      const IlvPoint&	p,
		      const IlvWChar*	s,
		      int		length,
		      IlvAlignment	align) const
{
    if (_dumping)
	_device->drawWChar(pal, p, s, length, align);
    else dst->drawWChar(pal, p, s, length, align);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawIWChar(IlvPort*			dst,
		       const IlvPalette*	pal,
		       const IlvPoint&		p,
		       const IlvWChar*		s,
		       int			length,
		       IlvAlignment		align) const
{
    if (_dumping)
	_device->drawIWChar(pal, p, s, length, align);
    else dst->drawIWChar(pal, p, s, length, align);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawTransformedString(IlvPort*		dst,
				  const IlvPalette*	pal,
				  const char*		label,
				  int			length,
				  const IlvTransformer&	t,
				  const IlvRegion*	clip) const
{
    if (_dumping)
	_device->drawTransformedString(pal, label, length, t, clip);
    else dst->drawTransformedString(pal, label, length, t, clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::clearArea(IlvPort*		dst,
		      const IlvRect&	rect,
		      IlBoolean		redraw) const
{
    if (_dumping)
	_device->clearArea(rect, redraw);
    else dst->clearArea(rect, redraw);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::clearArea(IlvPort*         dst,
		      const IlvRegion& region,
		      IlBoolean        redraw) const
{
    if (_dumping)
	_device->clearArea(region, redraw);
    else dst->clearArea(region, redraw);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawBitmap(IlvPort*			dst,
		       const IlvPalette*	pal,
		       const IlvBitmap*		src,
		       const IlvRect&		drawrect,
		       const IlvRegion*		region,
		       IlvPosition		position,
		       IlBoolean		transparent) const
{
    if (_dumping)
	_device->drawBitmap(pal, src, drawrect, region, position, transparent);
    else dst->drawBitmap(pal, src, drawrect, region, position, transparent);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::copyStretchedBitmap(IlvPort*	  dst,
				const IlvPalette* pal,
				const IlvRect&	  to,
				const IlvBitmap*  b,
				const IlvRect*	  clip) const
{
    if (_dumping)
	_device->stretchBitmap(pal, to, b, clip);
    else dst->stretchBitmap(pal, to, b, clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::copyStretchedTransparentBitmap(IlvPort*		dst,
					   const IlvPalette*	pal,
					   const IlvRect&	to,
					   const IlvBitmap*	b,
					   const IlvRect*	clip) const
{
    if (_dumping)
	_device->stretchTransparentBitmap(pal, to, b, clip);
    else dst->stretchTransparentBitmap(pal, to, b, clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawArrow(IlvPort*		dst,
		      const IlvPalette*	pal,
		      const IlvPoint&	from,
		      const IlvPoint&	to,
		      IlFloat		atpos) const
{
    if (_dumping)
	_device->drawArrow(pal, from, to, atpos);
    else dst->drawArrow(pal, from, to, atpos);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawMarker(IlvPort*			dst,
		       const IlvPalette*	pal,
		       const IlvPoint&		p,
		       IlvMarkerType		type,
		       IlUShort			size) const
{
    if (_dumping)
	_device->drawMarker(pal, p, type, size);
    else dst->drawMarker(pal, p, type, size);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawShadowRectangle(IlvPort*		dst,
				const IlvPalette*	pal,
				const IlvPalette*	invertedpalette,
				const IlvRect&		bbox,
				IlUShort		thickness,
				IlvPosition		shadowPosition,
				const IlvRegion*	clip) const
{
    if (_dumping)
	_device->drawShadowRectangle(pal,
				     invertedpalette,
				     bbox,
				     thickness,
				     shadowPosition,
				     clip);
    else dst->drawShadowRectangle(pal,
				  invertedpalette,
				  bbox,
				  thickness,
				  shadowPosition,
				  clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawReliefPolyline(IlvPort*			dst,
			       const IlvPalette*	topShadePalette,
			       const IlvPalette*	bottomShadePalette,
			       IlUInt			nbPoints,
			       IlvPoint*		points,
			       IlUShort			thickness,
			       IlBoolean		closed,
			       const IlvRegion*		clip) const
{
    if (_dumping)
	_device->drawReliefPolyline(topShadePalette,
				    bottomShadePalette,
				    nbPoints,
				    points,
				    thickness,
				    closed,
				    clip);
    else dst->drawReliefPolyline(topShadePalette,
				 bottomShadePalette,
				 nbPoints,
				 points,
				 thickness,
				 closed,
				 clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawReliefRectangle(IlvPort*		dst,
				const IlvPalette*	pal,
				const IlvPalette*	invpal,
				const IlvPalette*	ts,
				const IlvPalette*	bs,
				const IlvRect&		bbox,
				IlUShort		thickness,
				const IlvRegion*	clip) const
{
    if (_dumping)
	_device->drawReliefRectangle(pal, invpal, ts, bs, bbox,thickness,clip);
    else dst->drawReliefRectangle(pal, invpal, ts, bs, bbox, thickness, clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawReliefPolygon(IlvPort*		dst,
			      const IlvPalette*	fillPalette,
			      const IlvPalette*	topShadePalette,
			      const IlvPalette*	bottomShadePalette,
			      IlUInt		nbPoints,
			      IlvPoint*		points,
			      IlUShort		thickness,
			      const IlvRegion*	clip) const
{
    if (_dumping)
	_device->drawReliefPolygon(fillPalette,
				   topShadePalette,
				   bottomShadePalette,
				   nbPoints,
				   points,
				   thickness,
				   clip);
    else dst->drawReliefPolygon(fillPalette,
				topShadePalette,
				bottomShadePalette,
				nbPoints,
				points,
				thickness,
				clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawOutlineRectangle(IlvPort*		dst,
				 const IlvPalette*	outline,
				 const IlvPalette*	fill,
				 const IlvRect&		rect,
				 const IlvRegion*	clip) const
{
    if (_dumping)
	_device->drawOutlineRectangle(outline, fill, rect, clip);
    else dst->drawOutlineRectangle(outline, fill, rect, clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawReliefDiamond(IlvPort*		dst,
			      const IlvPalette*	pal,
			      const IlvPalette*	inversepal,
			      const IlvPalette*	topshad,
			      const IlvPalette*	bottomshad,
			      const IlvRect&	bbox,
			      IlUShort		thickness,
			      const IlvRegion*	clip) const
{
    if (_dumping)
	_device->drawReliefDiamond(pal,
				   inversepal,
				   topshad,
				   bottomshad,
				   bbox,
				   thickness,
				   clip);
    else dst->drawReliefDiamond(pal,
				inversepal,
				topshad,
				bottomshad,
				bbox,
				thickness,
				clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawReliefArrow(IlvPort*		dst,
			    IlvRect		rect,
			    IlvDim		thickness,
			    IlvOrientation	direction,
			    const IlvPalette*	pal,
			    const IlvPalette*	topS,
			    const IlvPalette*	botS,
			    const IlvRegion*	clip) const
{
    if (_dumping)
	_device->drawReliefArrow(rect,
				 thickness,
				 direction,
				 pal,
				 topS,
				 botS,
				 clip);
    else dst->drawReliefArrow(rect,
			      thickness,
			      direction,
			      pal,
			      topS,
			      botS,
			      clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawLabel(IlvPort*		dst,
		      const IlvPalette*	pal,
		      const char*	label,
		      int		length,
		      const IlvRect&	drawrect,
		      const IlvRegion*	region,
		      IlvPosition	position) const
{
    if (_dumping)
	_device->drawLabel(pal, label, length, drawrect, region, position);
    else dst->drawLabel(pal, label, length, drawrect, region, position);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawMnemonicLabel(IlvPort*		dst,
			      const IlvPalette*	pal,
			      const char*	label,
			      const IlvRect&	drawrect,
			      const IlvRegion*	region,
			      IlvPosition	position,
			      IlBoolean		underline) const
{
    if (_dumping)
	_device->drawMnemonicLabel(pal,
				   label,
				   drawrect,
				   region,
				   position,
				   underline);
    else dst->drawMnemonicLabel(pal,
				label,
				drawrect,
				region,
				position,
				underline);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void
IlvDisplay::drawILabel(IlvPort*			dst,
		       const IlvPalette*	pal,
		       const char*		label,
		       int			length,
		       const IlvRect&		drawrect,
		       const IlvRegion*		region,
		       IlvPosition		position) const
{
    if (_dumping)
	_device->drawILabel(pal, label, length, drawrect, region, position);
    else dst->drawILabel(pal, label, length, drawrect, region, position);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void // ILVBIDI
IlvDisplay::drawString(IlvPort*			dst,
		       const IlvPalette*	pal,
		       const IlvPoint&		p,
		       const IlvBidiString*	s,
		       int			length,
		       IlvAlignment		align) const
{
    if (_dumping)
	_device->drawString(pal, p, s, length, align);
    else dst->drawString(pal, p, s, length, align);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void // ILVBIDI
IlvDisplay::drawIString(IlvPort*		dst,
			const IlvPalette*	pal,
			const IlvPoint&		p,
			const IlvBidiString*	s,
			int			length,
			IlvAlignment		align) const
{
    if (_dumping)
	_device->drawIString(pal, p, s, length, align);
    else dst->drawIString(pal, p, s, length, align);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void // ILVBIDI
IlvDisplay::drawTransformedString(IlvPort*		dst,
				  const IlvPalette*	pal,
				  const IlvBidiString*	label,
				  int			length,
				  const IlvTransformer&	t,
				  const IlvRegion*	clip) const
{
    if (_dumping)
	_device->drawTransformedString(pal, label, length, t, clip);
    else dst->drawTransformedString(pal, label, length, t, clip);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void // ILVBIDI
IlvDisplay::drawLabel(IlvPort*			dst,
		      const IlvPalette*		pal,
		      const IlvBidiString*	label,
		      int			length,
		      const IlvRect&		drawrect,
		      const IlvRegion*		region,
		      IlvPosition		position) const
{
    if (_dumping)
	_device->drawLabel(pal, label, length, drawrect, region, position);
    else dst->drawLabel(pal, label, length, drawrect, region, position);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void // ILVBIDI
IlvDisplay::drawMnemonicLabel(IlvPort*			dst,
			      const IlvPalette*		pal,
			      const IlvBidiString*	label,
			      const IlvRect&		drawrect,
			      const IlvRegion*		region,
			      IlvPosition		position,
			      IlBoolean			underline) const
{
    if (_dumping)
	_device->drawMnemonicLabel(pal,
				   label,
				   drawrect,
				   region,
				   position,
				   underline);
    else dst->drawMnemonicLabel(pal,
				label,
				drawrect,
				region,
				position,
				underline);
}

#endif /* __Ilv_Base_Port_H */
