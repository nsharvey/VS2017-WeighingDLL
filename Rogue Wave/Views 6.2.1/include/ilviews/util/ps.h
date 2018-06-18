// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/ps.h
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
// Definition of the IlvPSDevice class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Ps_H
#define __Ilv_Util_Ps_H

#if !defined(__Ilv_Base_Port_H)
#include <ilviews/base/port.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

// Deprecated enum
enum IlvPSOrientation {
    IlvNone,
    IlvAutomatic,
    IlvPortrait,
    IlvLandScape
};


// --------------------------------------------------------------------------
enum IlvPSColorModel {
    IlvPSGrayScale,
    IlvPSColor
};

// --------------------------------------------------------------------------
class IlvPostScriptEncoder;
class ILVDSPEXPORTED IlvPSDevice : public IlvPort
{
public:
    IlvPSDevice(IlvDisplay*     display,
		IlvPSColorModel colorModel = IlvPSGrayScale);
    virtual ~IlvPSDevice();
    virtual IlBoolean	isADevice() const;

    virtual IlBoolean	initDevice(const char*, IlvRect* = 0);
    virtual IlBoolean	isBad() const;
    virtual void	end();

    virtual IlBoolean	newPage() const;
    virtual void	setTransformer(const IlvTransformer&);
    virtual void	send(const char*) const;
    virtual void	clip(const IlvRect*) const;
    virtual void	clip(const IlvRegion*) const;
    inline
    IlvRegion const&	getClip() const { return _clipRegion; }

    virtual void	drawPoint(const IlvPalette*, const IlvPoint&) const;
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
				     IlUInt count,
				     const IlvPoint*) const;
    virtual void	drawPolyLine(const IlvPalette*,
				     const IlvPoint&,
				     IlUInt,
				     const IlvDeltaPoint*) const;
    virtual void	fillPolyLine(const IlvPalette*,
				     const IlvPoint&,
				     IlUInt,
				     const IlvDeltaPoint*,
				     IlBoolean) const;
    virtual void	fillPolyLine(const IlvPalette*,
				     IlUInt,
				     const IlvPoint*,
				     IlBoolean) const;
    virtual void	drawArc(const IlvPalette*,
				const IlvRect&,
				IlFloat,
				IlFloat) const;
    virtual void	fillArc(const IlvPalette*,
				const IlvRect&,
				IlFloat,
				IlFloat) const;
    virtual void	drawBitmap(const IlvPalette*,
				   const IlvSystemPort*,
				   const IlvRect&,
				   const IlvPoint&) const;
    virtual void	drawBitmap(const IlvPalette*,
				   const IlvBitmap*,
				   const IlvRect&,
				   const IlvRect&,
				   const IlvRegion* = 0,
				   IlvPosition = IlvCenter,
				   IlBoolean = IlFalse) const;
    virtual void	drawBitmap(const IlvPalette*,
				   const IlvBitmap*,
				   const IlvRect&,
				   const IlvRegion* = 0,
				   IlvPosition = IlvCenter,
				   IlBoolean = IlFalse) const;
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
    virtual void	drawRectangle(const IlvPalette*, const IlvRect&) const;
    virtual void	fillRectangle(const IlvPalette*, const IlvRect&) const;
    virtual void	drawBezier(const IlvPalette*,
				   IlUInt,
				   const IlvPoint*) const;
    virtual void	drawClosedBezier(const IlvPalette*,
					 IlUInt,
					 const IlvPoint*) const;
    virtual void	fillBezier(const IlvPalette*,
				   IlUInt,
				   const IlvPoint*) const;
    virtual void	fillPaths(const IlvPalette*,
				  IlUInt,
				  const IlvPointArray*) const;
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
    virtual void	stretchBitmap(const IlvPalette*,
				      const IlvRect&,
				      const IlvBitmap*,
				      const IlvRect* = 0) const;
    virtual void	stretchTransparentBitmap(const IlvPalette*,
						 const IlvRect&,
						 const IlvBitmap*,
						 const IlvRect* = 0) const;
    virtual void	stretchBitmapData(const IlvPalette*    palette,
					  const IlvBitmapData* src,
					  const IlvRect&       from,
					  const IlvRect&       to,
					  IlBoolean opaque = IlFalse) const;
    inline IlvDim	getPaperWidth() const { return _paperWidth; }
    void		setPaperWidth(IlvDim width);
    inline IlvDim	getPaperHeight() const { return _paperHeight; }
    void		setPaperHeight(IlvDim height);
    inline void		setMinLineWidth(IlvDim lw) { _minLineWidth = lw; }
    void		setZoomableLineWidths(IlBoolean flag);

    virtual ILVSTDPREF ostream*	openStream(const char* filename);
    virtual void	closeStream(ILVSTDPREF ostream*);

    // ILVBIDI
    virtual void	drawString(const IlvPalette* pal,
				   const IlvPoint& p,
				   const IlvBidiString* s,
				   int length,
				   IlvAlignment align = IlvLeft) const;
    virtual void	drawIString(const IlvPalette* pal,
				    const IlvPoint& p,
				    const IlvBidiString* s,
				    int length,
				    IlvAlignment align = IlvLeft) const;
    virtual void	drawTransformedString(const IlvPalette* pal,
					      const IlvBidiString* label,
					      int length,
					      const IlvTransformer& t,
					      const IlvRegion* clip = 0) const;
    // ILVBIDI
    virtual void	setPageTransformer(const IlvTransformer& t);
    const IlvTransformer&	getPageTransformer() const;
    // new in 4.1
    void		setPostScriptLevel(IlUInt level);
    IlUInt		getPostScriptLevel() const { return _postScriptLevel; }
    IlvPostScriptEncoder*	getEncoder() const;
    void		setEncoder(IlvPostScriptEncoder* encoder);
    void		initClip(const IlvRect&);

    IlvPSColorModel	getColorModel() const { return _colorModel; }
    void		setColorModel(IlvPSColorModel val);

    static const char*	GetPrefix();
    static void		SetPrefix(const char*);

protected:
    void		initFile();
    void		setCurrentPalette(const IlvPalette*) const;
    void		setFont          (const IlvPalette*) const;
    void		setLineWidth     (const IlvPalette*) const;
    void		setLineStyle     (const IlvPalette*) const;
    virtual void	setForeground(const IlvPalette*) const;
    virtual void	writeImage(const IlvDisplay*,
				   IlvDim,
				   IlvDim,
				   IlvDim,
				   const unsigned char*,
				   IlUInt) const;
    virtual void	fillWithPattern(const IlvPalette*) const;
    void		checkClip(IlvRegion const& region) const;
    virtual IlvDim	imageStringSize(IlvDim) const;
    virtual const char*	imageOperatorString() const;
    void		initReadPattern() const;

    ILVSTDPREF ostream*		_out;		// Output stream
    IlBoolean			_initialized;
    IlvPalette*			_current_palette;
    IlUInt			_pagenumber;
    IlvDim			_paperWidth;
    IlvDim			_paperHeight;
    IlvDim			_minLineWidth;
    IlUInt			_postScriptLevel;
    IlvPostScriptEncoder*	_encoder;
    IlvTransformer		_pageTransformer;

    IlvPSColorModel		_colorModel;
    IlAny			_psExt;

private:
    IlvRect			_initClip;
    IL_MUTABLE IlvRegion	_clipRegion;
    IlvTransformer		_currentTransformer;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvPSColorDevice : public IlvPSDevice
{
public:
    IlvPSColorDevice(IlvDisplay* display) : IlvPSDevice(display, IlvPSColor) {}
};

#endif /* !__Ilv_Util_Ps_H */
