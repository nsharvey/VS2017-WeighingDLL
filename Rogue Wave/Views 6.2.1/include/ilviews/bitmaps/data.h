// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/data.h
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
// Declaration of bitmap data utilities
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Data_H
#define __Ilv_Bitmaps_Data_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif

#if defined(IL_STD)
#  include <cstring>
#else  /* !IL_STD */
#  include <string.h>
#endif /* !IL_STD */

class IlvBitmapStreamer;
class IlvBWBitmapData;
class IlvColorMap;
class IlvBitmapInformation;

typedef IlFloat (*IlvResampleFunction)(IlFloat);

typedef enum IlvResampleFilter {
    IlvBoxFilter = 0,
    IlvTriangleFilter,
    IlvHermiteFilter,
    IlvHanningFilter,
    IlvHammingFilter,
    IlvBlackmanFilter,
    IlvGaussianFilter,
    IlvQuadraticFilter,
    IlvBellFilter,
    IlvCubicFilter,
    IlvCatromFilter,
    IlvMitchellFilter,
    IlvLanczosFilter,
    IlvBesselFilter,
    IlvSincFilter,
    IlvCustomFilter
} _IlFilterMethod;

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvBitmapData
{
public:
    IlvBitmapData(IlUInt    width,
		  IlUInt    height,
		  IlUShort  depth,
		  IlUInt    padding     = 32);
    virtual ~IlvBitmapData();
    // ____________________________________________________________
    IlUInt		getWidth() const;
    IlUInt		getHeight() const;
    IlUShort		getDepth() const;
    inline IlInt	getX() const { return _x; }
    inline IlInt	getY() const { return _y; }
    inline void		setX(IlInt x) { _x = x; }
    inline void		setY(IlInt y) { _y = y; }
    inline const char*	getName() const { return _name; }
    void		setName(const char* name);
    IlUChar*		getData() const;
    IlUInt		getPadding() const;
    IlUInt		getByteWidth() const;
    inline IlUChar*	getRowStartData(IlUInt idx) const
			{
			    return _rowstart[idx];
			}
    IlBoolean		hasMask() const;
    virtual IlvBWBitmapData*	getMask() const;
    virtual void	setMask(IlvBWBitmapData* mask);
    virtual IlUChar*	getRGBPixels(const IlvRect& rect,
				     IlUInt&        size,
				     IlUChar*       data = 0) const;
    virtual void	getRGBPixel(IlUInt   x,
				    IlUInt   y,
				    IlUChar& r,
				    IlUChar& g,
				    IlUChar& b) const = 0;

    virtual void	setRGBPixels(IlUChar*        data,
				     IlUInt          byteWidth,
				     const IlvRect&  rect,
				     const IlvPoint& to);
    virtual void	setRGBPixel(IlUInt  x,
				    IlUInt  y,
				    IlUChar r,
				    IlUChar g,
				    IlUChar b) = 0;
    virtual void	fill(const IlvRect& rect,
			     IlUChar        r,
			     IlUChar        g,
			     IlUChar        b,
			     IlUChar        a = 255);
    virtual void	copyPixel(IlUInt               xdst,
				  IlUInt               ydst,
				  const IlvBitmapData* src,
				  IlUInt               xsrc,
				  IlUInt               ysrc);
    virtual void	copy(const IlvBitmapData* src,
			     const IlvRect&       srcrect,
			     const IlvPoint&      to);
    virtual void	blendPixel(IlUInt xdst,
				   IlUInt ydst,
				   const IlvBitmapData* src,
				   IlUInt xsrc,
				   IlUInt ysrc,
				   IlUChar blend);
    virtual void	blend(const IlvBitmapData* src,
			      const IlvRect&        srcrect,
			      const IlvPoint&       to,
			      IlUChar               blend);
    void		lock();
    void		unLock();
    IlUInt		getCount() const;
    virtual void	allocateData();
    virtual IlUInt	getUsedColorNum() = 0;
    void		setInformation(IlvBitmapInformation* info);
    inline IlvBitmapInformation* getInformation() const { return _info; }
    virtual IlBoolean	hasAlpha() const; // ALPHA_BLEND

protected:
    IlUInt			_padding;
    IlInt			_x;
    IlInt			_y;
    IlUInt			_width;
    IlUInt			_height;
    IlUShort			_depth;
    IlUChar**			_rowstart;
    IlUInt			_byterowlength;
    IlUChar*			_data;
    IlvBWBitmapData*		_mask;
    IlUInt			_refcount;
    char*			_name;
    IlvBitmapInformation*	_info;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvIndexedBitmapData : public IlvBitmapData
{
public:
    IlvIndexedBitmapData(IlUInt       width,
			 IlUInt       height,
			 IlvColorMap* cmap = 0);
    ~IlvIndexedBitmapData();

    void		setColorMap(IlvColorMap* colormap);
    IlvColorMap*	getColorMap() const;
    IlInt		getTransparentIndex() const;
    void		setTransparentIndex(IlInt index);
    virtual void	computeMask();
    virtual IlUChar*	getRGBPixels(const IlvRect& rect,
				     IlUInt&        size,
				     IlUChar*       data = 0) const;
    virtual void	setRGBPixels(IlUChar*        data,
				     IlUInt          byteWidth,
				     const IlvRect&  rect,
				     const IlvPoint& to);
    virtual void	setRGBPixel(IlUInt  x,
				    IlUInt  y,
				    IlUChar r,
				    IlUChar g,
				    IlUChar b);
    virtual void	getRGBPixel(IlUInt x,
				    IlUInt y,
				    IlUChar& r,
				    IlUChar& g,
				    IlUChar& b) const;
    virtual void	setPixels(IlUChar*        data,
				  IlUInt          byteWidth,
				  const IlvRect&  rect,
				  const IlvPoint& to);
    virtual void	setPixel(IlUInt x, IlUInt y, IlUChar pixel);
    IlUChar		getPixel(IlUInt x, IlUInt y) const;
    virtual IlUInt	getUsedColorNum();
    void		computeHistogram();
    void		stretch(const IlvIndexedBitmapData* srcdata,
				const IlvRect&              srcrect,
				const IlvRect&              dstrect);
protected:
    IlvColorMap*	_cmap;
    IlInt		_tindex;
    IlUInt*		_h;
};

enum IlvGradientMode {
    IlvLinearGradientMode = 0,
    IlvRadialGradientMode,
    IlvSquareGradientMode
};

enum IlvGradientRepeatMode {
    IlvClampGradientRepeat = 0,
    IlvSawToothGradientRepeat,
    IlvTriangleGradientRepeat
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvRGBBitmapData : public IlvBitmapData
{
public:
    enum Channel {
	Alpha = 0x1,
	Red = 0x2,
	Green = 0x4,
	Blue = 0x8,
	All = Alpha | Red | Green | Blue
    };
    IlvRGBBitmapData(IlUInt    width,
		     IlUInt    height);
    virtual IlUChar*	getRGBPixels(const IlvRect& rect,
				     IlUInt&        size,
				     IlUChar*       data = 0) const;
    virtual void	getRGBPixel(IlUInt   x,
				    IlUInt   y,
				    IlUChar& r,
				    IlUChar& g,
				    IlUChar& b) const;

    inline void		fastSetRGBPixel(IlUInt  x,
					IlUInt  y,
					IlUChar r,
					IlUChar g,
					IlUChar b);
    inline void		fastGetRGBPixel(IlUInt   x,
					IlUInt   y,
					IlUChar& r,
					IlUChar& g,
					IlUChar& b) const;
    inline void		fastGetARGBPixel(IlUInt   x,
					 IlUInt   y,
					 IlUChar& a,
					 IlUChar& r,
					 IlUChar& g,
					 IlUChar& b) const;
    virtual void	setRGBPixel(IlUInt  x,
				    IlUInt  y,
				    IlUChar r,
				    IlUChar g,
				    IlUChar b);
    void		setARGBPixel(IlUInt x,
				     IlUInt y,
				     IlUChar alpha,
				     IlUChar r,
				     IlUChar g,
				     IlUChar b);
    virtual void	setRGBPixels(IlUChar*        data,
				     IlUInt          byteWidth,
				     const IlvRect&  rect,
				     const IlvPoint& to);
    void		setAlpha(IlUInt x, IlUInt y, IlUChar alpha);
    IlUChar		getAlpha(IlUInt x, IlUInt y) const;
    void		fillAlpha(const IlvRect& rect, IlUChar alpha);
    virtual void	fill(const IlvRect& rect,
			     IlUChar        r,
			     IlUChar        g,
			     IlUChar        b,
			     IlUChar        a = 255);
    virtual void	copy(const IlvBitmapData* src,
			     const IlvRect&       srcrect,
			     const IlvPoint&      to);
    virtual void	copyA(const IlvRGBBitmapData* src,
			      const IlvRect&          srcrect,
			      const IlvPoint&         to);
    virtual void	copyRGB(const IlvRGBBitmapData* src,
				const IlvRect&          srcrect,
				const IlvPoint&         to);
    virtual void	blend(const IlvBitmapData* src,
			      const IlvRect&       srcrect,
			      const IlvPoint&      to,
			      IlUChar              blend);
    inline void		fastCopyPixel(IlUInt                  xdst,
				      IlUInt                  ydst,
				      const IlvRGBBitmapData* src,
				      IlUInt                  xsrc,
				      IlUInt                  ysrc);
    void		alphaCompose(const IlvRGBBitmapData* src,
				     const IlvRect&          srcrect,
				     const IlvPoint&         to,
				     IlUChar                 blend = 255);
    virtual IlUInt	getUsedColorNum();
    void	fillGradient(IlvColorMap* cmap,
			     const IlvPoint& from,
			     const IlvPoint& to,
			     IlvGradientMode mode = IlvLinearGradientMode,
			     IlvGradientRepeatMode rmode = IlvClampGradientRepeat);
    void	tile(IlvBitmapData* src, const IlvPoint& offset);
    void	tileCompose(IlvRGBBitmapData* src,
			    const IlvPoint&   offset,
			    IlUChar           blend = 255);
    void	tileRGB(IlvRGBBitmapData* src, const IlvPoint& offset);
    void	tileA(IlvRGBBitmapData* src, const IlvPoint& offset);
    void	stretch(const IlvBitmapData* srcdata,
			const IlvRect&       srcrect,
			const IlvRect&       dstrect);
    void	stretchSmooth(const IlvBitmapData* srcdata,
			      const IlvRect&       srcrect,
			      const IlvRect&       dstrect,
			      IlvResampleFilter    filter = IlvMitchellFilter,
			      IlvResampleFunction  func = 0,
			      IlFloat              support = 0);
    IlBoolean	isAlphaPremultiplied() const;
    void	alphaMultiply();
    void	alphaDivide();
    void	setAlphaPremultiplied(IlBoolean);
    void	activateChannels(Channel channels);
    void	deactivateChannels(Channel channels);
    inline Channel	getActiveChannels() const { return _activeChannels; }

    // ALPHA_BLEND
    virtual IlBoolean	hasAlpha() const;
    void		setHasAlpha(IlBoolean val);

protected:
    IlBoolean	_isAlphaPremultiplied;
    Channel	_activeChannels;
    IlBoolean	_hasAlpha; // ALPHA_BLEND

};


// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvBWBitmapData : public IlvBitmapData
{
public:
    IlvBWBitmapData(IlUInt width, IlUInt height);
    virtual IlUChar*	getRGBPixels(const IlvRect& rect,
				     IlUInt&        size,
				     IlUChar*       data = 0) const;
    virtual void	getRGBPixel(IlUInt   x,
				    IlUInt   y,
				    IlUChar& r,
				    IlUChar& g,
				    IlUChar& b) const;
    virtual void	setRGBPixel(IlUInt  x,
				    IlUInt  y,
				    IlUChar r,
				    IlUChar g,
				    IlUChar b);
    void		setPixel(IlUInt x, IlUInt y, IlUChar pixel);
    // internal use only
    void		setData(const IlUChar* data,
				IlvRect        rect,
				IlUInt         bytesperline);
    virtual IlUInt	getUsedColorNum();
    void		stretch(const IlvBWBitmapData* srcdata,
				const IlvRect& srcrect,
				const IlvRect& dstrect);
};

// --------------------------------------------------------------------------
inline void
IlvRGBBitmapData::fastSetRGBPixel(IlUInt  x, IlUInt  y,
				  IlUChar r, IlUChar g, IlUChar b)
{
    IlUChar* dstptr = _rowstart[y] + x * 4;
    *dstptr++ = 0xff;
    *dstptr++ = r;
    *dstptr++ = g;
    *dstptr = b;
}

// --------------------------------------------------------------------------
inline void
IlvRGBBitmapData::fastGetRGBPixel(IlUInt x, IlUInt y,
				  IlUChar& r, IlUChar& g, IlUChar& b) const
{
    IlUChar* srcptr = _rowstart[y] + x * 4 + 1;
    r = *srcptr++;
    g = *srcptr++;
    b = *srcptr;
}

// --------------------------------------------------------------------------
inline void
IlvRGBBitmapData::fastGetARGBPixel(IlUInt x, IlUInt y,
				   IlUChar& a,
				   IlUChar& r, IlUChar& g, IlUChar& b) const
{
    IlUChar* srcptr = _rowstart[y] + x * 4;
    a = *srcptr++;
    r = *srcptr++;
    g = *srcptr++;
    b = *srcptr;
}

// --------------------------------------------------------------------------
inline void
IlvRGBBitmapData::fastCopyPixel(IlUInt xdst, IlUInt ydst,
				const IlvRGBBitmapData* src,
				IlUInt xsrc, IlUInt ysrc)
{
#if !defined(_MSC_VER)
# if !(defined(sgi) && defined(_STANDARD_C_PLUS_PLUS))
    ILVSTDPREF
# endif /* ! sgi CC73 -LANG:std */
#endif
    memcpy((void*)(getRowStartData(ydst) + 4 * xdst),
	   (void*)(src->getRowStartData(ysrc) + 4 * xsrc),
	   (size_t)4);
}

// --------------------------------------------------------------------------
inline void
IlvIndexedBitmapData::setPixel(IlUInt x, IlUInt y, IlUChar pixel)
{
    *(_rowstart[y] + x) = pixel;
}

// --------------------------------------------------------------------------
inline IlUChar
IlvIndexedBitmapData::getPixel(IlUInt x, IlUInt y) const
{
    return *(_rowstart[y] + x);
}

#endif /* __Ilv_Bitmaps_Data_H */
