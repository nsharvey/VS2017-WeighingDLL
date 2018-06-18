// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/event.h
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
// Declaration of the event-related syumbols
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Event_H
#define __Ilv_Base_Event_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

// Keys descriptors: __________________________________________
#define IlvCtrlChar(c) ((unsigned char)(1+ (((c) & ~0x20)-'A')))
#define IlvDeleteKey		((unsigned char)127)

#define IlvBackSpace		((IlUShort)0xFF08)
#define IlvTab			((IlUShort)0xFF09)
#define IlvLinefeed		((IlUShort)0xFF0A)
#define IlvClear		((IlUShort)0xFF0B)
#define IlvReturn		((IlUShort)0xFF0D)
#define IlvPause		((IlUShort)0xFF13)
#define IlvScrollLock		((IlUShort)0xFF14)
#define IlvSysReq		((IlUShort)0xFF15)
#define IlvEscape		((IlUShort)0xFF1B)
#define IlvMultiByteData	((IlUShort)0xFF20)

// Special keys for IM handling
#define IlvIMStartComposition	((IlUShort)0xAA00)


#define IlvF0Key		((IlUShort)0x200)
#define IlvF1Key		((IlUShort)0x201)
#define IlvF2Key		((IlUShort)0x202)
#define IlvF3Key		((IlUShort)0x203)
#define IlvF4Key		((IlUShort)0x204)
#define IlvF5Key		((IlUShort)0x205)
#define IlvF6Key		((IlUShort)0x206)
#define IlvF7Key		((IlUShort)0x207)
#define IlvF8Key		((IlUShort)0x208)
#define IlvF9Key		((IlUShort)0x209)
#define IlvF10Key		((IlUShort)0x20A)
#define IlvF11Key		((IlUShort)0x20B)
#define IlvF12Key		((IlUShort)0x20C)
#define IlvF13Key		((IlUShort)0x20D)
#define IlvF14Key		((IlUShort)0x20E)
#define IlvF15Key		((IlUShort)0x20F)
#define IlvF16Key		((IlUShort)0x210)
#define IlvF17Key		((IlUShort)0x211)
#define IlvF18Key		((IlUShort)0x212)
#define IlvF19Key		((IlUShort)0x213)
#define IlvUpKey		((IlUShort)0x226)
#define IlvLeftKey		((IlUShort)0x227)
#define IlvDownKey		((IlUShort)0x228)
#define IlvRightKey		((IlUShort)0x229)
#define IlvHomeKey		((IlUShort)0x22A)
#define IlvEndKey		((IlUShort)0x22B)
#define IlvPageUpKey		((IlUShort)0x22C)
#define IlvPageDownKey		((IlUShort)0x22D)
#define IlvInsKey		((IlUShort)0x22E)
#define IlvDelKey		((IlUShort)0x22F)
#define IlvHelpKey		((IlUShort)0x230)
#define IlvPauseKey		((IlUShort)0x231)
#define IlvShiftKey		((IlUShort)0x232)
#define IlvRShiftKey		((IlUShort)0x233)
#define IlvAltKey		((IlUShort)0x234)
#define IlvRAltKey		((IlUShort)0x235)
#define IlvCtrlKey		((IlUShort)0x236)
#define IlvRCtrlKey		((IlUShort)0x237)
#define IlvMetaKey		((IlUShort)0x238)
#define IlvRMetaKey		((IlUShort)0x239)
#define IlvNumLockKey		((IlUShort)0x23A)
#define IlvCapsLockKey		((IlUShort)0x23B)
#define IlvPrScreenKey		((IlUShort)0x23C)
#define IlvSelectKey		((IlUShort)0x23D)
#define IlvExecuteKey		((IlUShort)0x23E)
#define IlvBreakKey		((IlUShort)0x23F)
#define IlvCancelKey		((IlUShort)0x240)
#define IlvSystemKey		((IlUShort)0x241)
#define IlvUserKey		((IlUShort)0x242)
#define IlvSpecialKeyMask	((IlUShort)0xFE00)
#define IlvAnyKey		((IlUShort)0xAAAA)

#define IlvIsSpecialKey(c) ((c >= IlvF0Key && c <= IlvUserKey) || \
			    (c >= IlvBackSpace && c <= IlvEscape))

// Mouse buttons descriptors: _________________________________
#define IlvLeftButton		((IlUShort)0x0001)
#define IlvMiddleButton		((IlUShort)0x0002)
#define IlvRightButton		((IlUShort)0x0004)
#define IlvButton4		((IlUShort)0x0008)
#define IlvButton5		((IlUShort)0x0010)
#define IlvAnyButton		((IlUShort)(IlvLeftButton|IlvMiddleButton|\
				      IlvRightButton|IlvButton4|IlvButton5))

// Events modifiers ___________________________________________
#define IlvShiftModifier	((IlUShort)0x0100)
#define IlvCtrlModifier		((IlUShort)0x0200)
#define IlvAltModifier		((IlUShort)0x0400)
#define IlvMetaModifier		((IlUShort)0x0800)
#define IlvNumModifier		((IlUShort)0x1000)
#define IlvLockModifier		((IlUShort)0x2000)
#define IlvAltGModifier		((IlUShort)0x4000)
#define IlvAnyModifier		((IlUShort)0x7F00)
#define IlvForgetModifier	((IlUShort)0x8000)

// --------------------------------------------------------------------------
//    IlvEvent
// --------------------------------------------------------------------------
enum IlvEventType {
    IlvKeyUp		=  1,
    IlvKeyDown		=  2,
    IlvButtonDown	=  3,
    IlvButtonUp		=  4,
    IlvEnterWindow	=  5,
    IlvLeaveWindow	=  6,
    IlvPointerMoved	=  7,
    IlvButtonDragged	=  8,
    IlvRepaint		=  9,
    IlvModifyWindow	= 10,
    IlvVisibility	= 11,
    IlvMapWindow	= 12,
    IlvUnMapWindow	= 13,
    IlvReparent		= 14,
    IlvKeyboardFocusIn	= 15,
    IlvKeyboardFocusOut	= 16,
    IlvDestroyWindow	= 17,
    IlvClientMessage	= 18,
    IlvDoubleClick	= 19,
    IlvMouseEnter	= 20,
    IlvMouseLeave	= 21,
    IlvTripleClick	= 22, // Obsolete !! Here for compatibility only
    IlvMultiClick	= 23,
    IlvDrop		= 24,
    IlvEnterDropSite	= 25,
    IlvLeaveDropSite	= 26,
    IlvLoseSelection	= 27,
    IlvColormapChanged	= 28,
    IlvTimerCallback	= 29,
    IlvMouseWheel	= 30,
    IlvTouchDown	= 31,
    IlvTouchMoved	= 32,
    IlvTouchUp		= 33,
    IlvNullEvent	= 100
};
extern "C"
ILVDSPEXPORTEDFUNCTION(const char*)
IlvGetEventTypeName(IlvEventType);

// Add other events ??? for the VB
// ClientMessage Expose Visibility  Map-UnMap Focus StructureNotify
//

//detail of focus events
enum IlvFocusDetail {
    IlvFocusNormal	= 0,
    IlvFocusButton	= 1,
    IlvFocusBackward	= 2,
    IlvFocusForward	= 3
};

ILVDSPEXPORTEDFUNCTION(IlUShort)
IlvGetDoubleClickPeriod();
ILVDSPEXPORTEDFUNCTION(void)
IlvSetDoubleClickPeriod(IlUShort);

#if !defined(__Ilv_Base_Geometry_H)
#  include <ilviews/base/geometry.h>
#endif

class IlvPort;
class IlvAbstractView;
// ----------------------------------------------------------------------
class ILVDSPEXPORTED IlvEvent
{
public:
    IlvEvent(IlvEventType type = IlvNullEvent)
    : _type(type),
      _modifiers(0),
      _gpos(),
      _pos(),
      _w(0),
      _h(0),
      _b(0),
      _source(0),
      _time(0),
      _internal(0),
      _used(IlFalse),
      _view(0)
    {
	_data.detail = 0;
    }
    // ____________________________________________________________
    inline IlvPos	getGx() const { return _gpos.x(); }
    inline IlvPos	getGy() const { return _gpos.y(); }
    inline IlvPos	gx() const { return getGx(); }
    inline IlvPos	gy() const { return getGy(); }
    inline void		setGx(IlvPos gx) { _gpos.x(gx); }
    inline void		setGy(IlvPos gy) { _gpos.y(gy); }
    inline IlvPos	getX() const { return _pos.x(); }
    inline IlvPos	x()    const { return getX();   }
    inline IlvPos	getY() const { return _pos.y(); }
    inline IlvPos	y()    const { return getY();   }
    inline void		setPos(const IlvPoint& p) { _pos = p;   }
    inline void		setX(IlvPos xx)		  { _pos.x(xx); }
    inline void		setY(IlvPos yy)		  { _pos.y(yy); }
    inline IlvDim	getW() const { return _w; }
    inline IlvDim	getH() const { return _h; }
    inline IlvDim	w() const { return _w; }
    inline IlvDim	h() const { return _h; }
    inline IlvEventType getType()        const { return _type;      }
    inline IlvEventType type()	         const { return _type;      }
    inline IlUShort	getData()        const { return _data.data; }
    inline IlUShort	data()           const { return _data.data; }
    inline void		setData(IlUShort data) { _data.data = data; }
    inline void		data(IlUShort data)    { _data.data = data; }
    inline IlUShort	getButton() const { return _data.data; }
    inline IlUShort	button()    const { return _data.data; }
    inline IlUShort	getKey()    const { return _data.data;   }
    inline IlUShort	key()       const { return _data.data;   }
    inline IlAny	getDetail() const { return _data.detail; }
    inline IlAny	detail()    const { return _data.detail; }
    inline IlUShort	getModifiers() const { return _modifiers; }
    inline IlUShort	modifiers()    const { return _modifiers; }
    inline int		getMultiClickCount() const { return _b; }
    inline int		multiClickCount()    const { return _b; }
    inline IlAny	getInternal()         const { return _internal;	    }
    inline void		setInternal(IlAny internal) { _internal = internal; }
    inline void		setUsed(IlBoolean flag)     { _used = flag;         }
    inline IlBoolean	isUsed()              const { return _used;         }

    inline
    IlvAbstractView*	getView() const { return _view; }
    inline void		getGLocation(IlvPoint& p) const { p = _gpos; }
    inline
    const IlvPoint&	getGLocation() const { return _gpos; }
    inline void		getLocation(IlvPoint& p) const { p = _pos; }
    inline
    const IlvPoint&	getLocation() const		 { return _pos; }
    inline void		setGLocation(const IlvPoint& gp) { _gpos = gp; }
    inline void		setGLocation(IlvPos x, IlvPos y) { _gpos.move(x, y);}
    inline void		setLocation(const IlvPoint& p)   { _pos = p; }
    inline void		setLocation(IlvPos x, IlvPos y)  { _pos.move(x, y); }
    inline IlUShort	getTouchPoint() const { return _data.touchPoint; }

    IlvEventType	_type;
    union IlvEventData {
	IlUShort	data;
	IlAny		detail;
	char		message[20];
	IlUShort	touchPoint;
    }			_data;
    IlUShort		_modifiers;
    IlvPoint		_gpos;
    IlvPoint		_pos;
    IlvDim		_w, _h;
    int			_b;       // Window border, or multi click count
    IlAny		_source;
    IlUInt		_time; // Date of this event (use for multi-click)
    IlAny		_internal;
    IlBoolean		_used;
    IlvAbstractView*	_view;
    static IlBoolean	_AlwaysSetNumLockMod;
    static IlBoolean	_AlwaysSetCapsLockMod;
};

ILVDSPEXPORTEDFUNCTION(IlBoolean)
_IlvIsInputMethodStartEvent(IlvEvent&);
#endif /* !__Ilv_Base_Event_H */
