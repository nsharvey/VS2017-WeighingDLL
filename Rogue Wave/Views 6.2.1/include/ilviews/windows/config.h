// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/windows/config.h
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
// Definition of the IlvWindowsDisplayConfiguration and some utility classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Windows_Config_H
#define __Ilv_Windows_Config_H

#if !defined(__Ilv_Base_Config_H)
#  include <ilviews/base/config.h>
#endif
#if !defined(__Ilv_Base_Port_H)
#  include <ilviews/base/port.h>
#endif
#include <windows.h>

class ILVDSPEXPORTED IlvBitmapAllocationResult
{
public:
    inline
    IlvBitmapAllocationResult(HBITMAP bitmap)
	: _hBitmap(bitmap),
	  _type(HBitmap)
    {}
    enum Type {
	HBitmap,
	Alternative,
	Retry,
	Fail
    };
    inline
    IlvBitmapAllocationResult(Type type)
	: _type(type),
          _hBitmap(0)
    {}

    inline operator	HBITMAP() const { return _hBitmap; }
    inline
    bool operator	==(const IlvBitmapAllocationResult& other)
			{
			    return (_type == other._type)
				&& (_hBitmap == other._hBitmap);
			}

private:
    Type		_type;
    HBITMAP		_hBitmap;
};

extern ILVDSPEXPORTED const IlvBitmapAllocationResult
IlvBitmapAllocationRetry;
extern ILVDSPEXPORTED const IlvBitmapAllocationResult
IlvBitmapAllocationAlternative;
extern ILVDSPEXPORTED const IlvBitmapAllocationResult
IlvBitmapAllocationFail;
typedef IlvBitmapAllocationResult (* IlvBitmapAllocationFailedCallback)
			(IlvDisplay*           display,
			 IlvDim                width,
			 IlvDim                height,
			 IlUShort              depth,
			 IlvBitmap::MemoryType memoryType,
			 IlUInt                attemptCounter);

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvWindowsDisplayConfig : public IlvDisplayConfig
{
    friend class IlvDisplay;
public:
    HINSTANCE		getHInstance() const;
    HPALETTE		getHPalette() const;
    void		setHPalette(HPALETTE hPalette,
				    IlBoolean owner = IlFalse);
    inline void setPreferredBitmapMemoryType(IlvBitmap::MemoryType memoryType)
		{
		    _preferredBitmapMemoryType = memoryType;
		}

    inline IlvBitmap::MemoryType getPreferredBitmapMemoryType() const
		{
		    return _preferredBitmapMemoryType;
		}
    inline void setBitmapAllocationFailedCallback(
	                         IlvBitmapAllocationFailedCallback callback)
		{
		    _bitmapAllocationFailedCallback = callback;
		}

    inline IlvBitmapAllocationFailedCallback
                                   getBitmapAllocationFailedCallback() const
		{
		    return _bitmapAllocationFailedCallback;
		}

    inline IlBoolean	hasLayeredWindows() const
			{
			    return _hasLayeredWindows;
			}
    inline void		allowAlternativeBitmapMemoryType(IlBoolean allowed)
			{
			    _allowAlternativeBitmapMemoryType = allowed;
			}
    inline IlBoolean	isAlternativeBitmapMemoryTypeAllowed() const
			{
			    return _allowAlternativeBitmapMemoryType;
			}

    void		redirect(int stdFd, const IlString& path);

protected:
    IlvWindowsDisplayConfig(IlvDisplay* display, IlAny userArg);

    IlBoolean		              _hasLayeredWindows;
    IlvBitmap::MemoryType             _preferredBitmapMemoryType;
    IlBoolean                         _allowAlternativeBitmapMemoryType;
    IlvBitmapAllocationFailedCallback _bitmapAllocationFailedCallback;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvWindowsPoint : public IlvPoint
{
public:
    IlvWindowsPoint(const POINT& pt) : IlvPoint(pt.x, pt.y) {}
    IlvWindowsPoint(IlvPos x, IlvPos y) : IlvPoint(x, y) {}
    IlvWindowsPoint(const IlvPoint& pt) : IlvPoint(pt) {}
    IlvWindowsPoint() : IlvPoint() {}
    inline operator	const POINT()
			{
			    POINT pt = { x(), y() };
			    return pt;
			}
    inline POINT&	fill(POINT& pt)
			{
			    pt.x = x();
			    pt.y = y();
			    return pt;
			}
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvWindowsRect : public IlvRect
{
public:
    IlvWindowsRect(const RECT& rect)
	: IlvRect(rect.left,
		  rect.top,
		  ILVCAST(IlvDim, rect.right - rect.left),
		  ILVCAST(IlvDim, rect.bottom - rect.top))
    {}
    IlvWindowsRect(IlvPos x, IlvPos y, IlvDim w, IlvDim h)
	: IlvRect(x, y, w, h)
    {}
    IlvWindowsRect(const IlvRect& rect) : IlvRect(rect) {}
    IlvWindowsRect() : IlvRect() {}
    inline operator	const RECT()
			{
			    RECT rect = { x(), y(), right(), bottom() };
			    return rect;
			}
    inline RECT&	fill(RECT& rect)
			{
			    rect.left   = x();
			    rect.top    = y();
			    rect.right  = right();
			    rect.bottom = bottom();
			    return rect;
			}
};

// --------------------------------------------------------------------------
// Dealing with Windows errors (expands GetLastError()).
class ILVDSPEXPORTED IlvWindowsLastError
{
public:
    IlvWindowsLastError();

    inline DWORD	getCode()    const { return _code; }
    inline
    const IlString&	getMessage() const { return _message; }

private:
    DWORD		_code;
    IlString		_message;
};

// --------------------------------------------------------------------------
extern "C" {
ILVDSPEXPORTEDFUNCTION(void)
IlvAddHandleToResPath(HINSTANCE hInstance, int index);

ILVDSPEXPORTEDFUNCTION(void)
IlvRemoveHandleFromResPath(HINSTANCE hInstance);
}
#endif /* __Ilv_Windows_Config_H */
