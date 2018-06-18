// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/im.h
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
// Declaration of the IlvIM and IlvImIC classes.
// Defined in library <display>views
// Input method management.
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Im_H
#define __Ilv_Base_Im_H

#if !defined(__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif
#if !defined(__Ilv_Util_Im_H)
#include <ilviews/util/im.h>
#endif

class ILVDSPEXPORTED IlvGlobalContext;
class IlvIM;

// --------------------------------------------------------------------------
// IlvIC class
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvIC
{
    friend class IlvIM;
public:
    static IlvIC*	GetIC(IlvDisplay*      dpy,
			      IlAny            gadget,
			      IlAny            holder,
			      IlvAbstractView* view,
			      IlvPalette*      = 0,
			      const IlvRect*   = 0,
			      IlBoolean        createIfNeeded = IlFalse);
    void		remove(IlAny gadget);
    void		setFocus(IlvAbstractView* view, IlAny gadget);
    void		unsetFocus(IlvAbstractView* view);
    void		setValues(IlUShort count, const IlvImValue* values);
    void		setInternal(IlBoolean create = IlTrue);
    IlAny		getInternal();
    inline IlAny	getGadgetFocus() const { return _gadget; };
    inline IlBoolean	isShared() const { return _shared; }
    inline IlvAbstractView*	getTopView() const { return _top; }
    inline void		setTopView(IlvAbstractView*  top) { _top = top; }
    inline IlAny	getHolder() const { return _holder; }

#if defined(X11)
    IlBoolean		isPreeditValue(IlSymbol* valueName);
    IlBoolean		isStatusValue(IlSymbol* valueName);
    IlBoolean		isXicValue(IlSymbol* valueName);
#endif /* X11 */

    static IlSymbol*	_imPoint;
    static IlSymbol*	_imArea;
    static IlSymbol*	_imForeground;
    static IlSymbol*	_imBackground;
    static IlSymbol*	_imFont;
    static IlSymbol*	_imLineSpace;
    static IlSymbol*	_imFocus;

protected:
    IlvIC(IlvIM*           im,
	  IlAny            gadget,
	  IlAny            holder,
	  IlvAbstractView* view,
	  IlvPalette*      palette,
	  const IlvRect*   rect,
	  IlBoolean        shared);
    virtual ~IlvIC();

    IlAny		_internal;        // stores the real IC for non-shared
    IlvIM*		_imInfo;
    IlAny		_holder;          // holder for the gadget
    IlvAbstractView*	_top;
    unsigned long	_topInputMask;    // input mask of the top level window
    unsigned long	_filterEventMask; // event mask for the IM
    IlBoolean		_shared;          // is this IC shared
    // for shared IC
    IlList*		_allGadgets;      // list of gadgets
    // for non-shared this is the gadget, and for shared keep the last gadget
    // which had the focus
    IlAny		_gadget;
    // cached info about the XIC
    IlvAbstractView*	_focusView;
    IlAny		_inputStyle;
    IlvPalette*		_palette;
    IlvRect		_rect;

    inline IlvIM*	getImInfo() const { return _imInfo; }
    inline IlList*	getAllGadgets() const { return _allGadgets; }
};

// --------------------------------------------------------------------------
// class IlvIM
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvIM
{
    friend class IlvIC;
    friend class IlvDisplay;
    friend class IlvGlobalContext;
public:
    static IlvIM*	Get(IlvDisplay*, IlBoolean createIfNeeded);
    IlvIC*		getIC(IlAny            gadget,
			      IlAny            holder,
			      IlvAbstractView* view,
			      IlvPalette*      palette = 0,
			      const IlvRect*   rect = 0,
			      IlBoolean        createIfNeeded = IlFalse);
    inline IlAny	getInternal() const { return _internal; }
    // ____________________________________________________________
    static void		Register(IlvDisplay*      dpy,
				 IlAny            gadget,
				 IlAny            holder,
				 IlvAbstractView* view,
				 IlvPalette*      palette,
				 const IlvRect*   rect);
    static void		UnRegister(IlvDisplay*      dpy,
				   IlAny            gadget,
				   IlAny            holder,
				   IlvAbstractView* view);
    static void		SetHolderPort(IlvDisplay*      dpy,
				      IlAny            holder,
				      IlvAbstractView* view);
    static void		SetFocusValues(IlvDisplay*       dpy,
				       IlAny             gadget,
				       IlAny             holder,
				       IlvAbstractView*  view,
				       IlUShort          count,
				       const IlvImValue* values);
    static void		UnsetFocus(IlvDisplay*      dpy,
				   IlAny            gadget,
				   IlAny            holder,
				   IlvAbstractView* view);
    static void		SetValues(IlvDisplay*       dpy,
				  IlAny             gadget,
				  IlAny             holder,
				  IlvAbstractView*  view,
				  IlUShort          count,
				  const IlvImValue* values);
    static int		MbLookupString(IlvDisplay*      dpy,
				       IlAny            gadget,
				       IlAny            holder,
				       IlvAbstractView* view,
				       IlvEvent&        event,
				       char*            buff,
				       int              nbytes,
				       int*             status);

protected:
    IlvIM(IlvDisplay*);
    virtual ~IlvIM();

    inline IlBoolean	isBad() const { return _internal ? IlFalse : IlTrue; }
    inline IlAList*	getAllICs() const { return _allICs; }
    inline IlAList*	getAllHolderICnb() const { return _allHolderICnb; }
    inline IlAList*	getAllHolderSharedICs() const
			{
			    return _allHolderSharedICs;
			}
    inline IlAList*	getAllTopRealICs() const { return _allTopRealICs; }
    static void		FreeAllValues();

    IlvDisplay*		_display;
    IlAny		_internal;
    IlAny		_bestStyle;
    // useful info for non-shared
    IlAList*		_allICs;		// list of gadget/IC pairs
    IlAList*		_allHolderICnb;		// list of holder/number of IC
    // useful info for shared
    IlAList*		_allHolderSharedICs;	// list of holder/IC pairs
    IlAList*		_allTopRealICs;		// list of top window/system
						// dependent IC pairs.


    // static data members
    static IlAny	_supportedStyles; // constant
    static IlAList*	_allIMs;          // list of all IM/display pairs
};

#endif /* !__Ilv_Base_Im_H */
