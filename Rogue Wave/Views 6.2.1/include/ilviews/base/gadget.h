// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/gadget.h
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
// Declaration of the IlvGadget class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Gadget_H
#define __Ilv_Base_Gadget_H

#if !defined(ILVNODEFAULTLOOK)
#  include <ilviews/looks/default.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Base_Inter_H)
#  include <ilviews/base/inter.h>
#endif
#if !defined(__Ilv_Base_Look_H)
#  include <ilviews/base/look.h>
#endif
#if !defined(__Ilv_Base_Stylable_H)
#  include <ilviews/base/stylable.h>
#endif

#define IlvDefaultGadgetThickness 2

#define ILVGADGETREADALPHAFLAG		25
#define ILVGADGETHIDEFRAMEFLAG		26
#define ILVGADGETDEFAULTSIZEFLAG	27
#define ILVGADGETTRANSPARENTFLAG	28
#define ILVGADGETINACTIVEFLAG		29
#define ILVGADGETINVERTEDFLAG		30
#define ILVGADGETFOCUSABLEFLAG		31    // 2.21 compatibility

class IlvGraphicHolder;
class IlvGadget;

#define IlvNewPalette(oldPal, pal)					\
    if (oldPal == pal) { return; }					\
    if (pal)           { pal->lock(); }					\
    if (oldPal)        { oldPal->unLock(); }				\
    oldPal = pal

#define IlvDefineCallbackFromSymbol(name, symbol)			\
IlSymbol* get##name##CallbackName() const { return getCallbackName(symbol);}\
IlvGraphicCallback get##name##Callback() const {return getCallback(symbol);}\
void		   set##name##Callback(IlvGraphicCallback callback)	\
{ setCallback(symbol, callback); }					\
void		   set##name##Callback(IlSymbol* callbackName)		\
{ setCallback(symbol, callbackName); }					\
void		   add##name##Callback(IlvGraphicCallback callback)	\
{ addCallback(symbol, callback); }					\
void		   set##name##Callback(IlvGraphicCallback cback, IlAny arg)\
{ setCallback(symbol, cback, arg); }					\
void		   add##name##Callback(IlvGraphicCallback cback, IlAny arg)\
{ addCallback(symbol, cback, arg); }					\
void		   add##name##Callback(IlSymbol* callbackName)		\
{ addCallback(symbol, callbackName); }					\
void		   set##name##Callback(IlSymbol* cbackName, IlAny arg)  \
{ setCallback(symbol, cbackName, arg); }				\
void		   add##name##Callback(IlSymbol* cbackName, IlAny arg)  \
{ addCallback(symbol, cbackName, arg); }				\
void		   call##name##Callback()				\
{ callCallbacks(symbol); }

#define IlvDefineCallback(name)						\
IlvDefineCallbackFromSymbol(name, name##Symbol())

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGadgetLFHandler
    : public IlvObjectLFHandler
{
public:
    IlvGadgetLFHandler(IlvLookFeelHandler* lf);
    virtual void	setMode(IlvGadget*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvGadget*, IlBoolean) const = 0;
    virtual void	computePalettes(IlvGadget*) const = 0;
    virtual void	drawBackground(const IlvGadget*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const = 0;
    virtual void	drawFrame(const IlvGadget*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual void	invert(IlvGadget*, IlBoolean) const = 0;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGadget
    : public IlvSimpleGraphic,
      public IlvStylable
{
public:
    IlvGadget(IlvDisplay*	display,
              const IlvRect&	rect,
              IlUShort		thickness = IlvDefaultGadgetThickness,
              IlvPalette*	palette = 0);
    virtual ~IlvGadget();

    virtual void	setHolder(IlvGraphicHolder* holder);
    virtual IlBoolean	classFocusable() const;
    virtual void	fitToContents(IlvDirection direction = (IlvDirection)
				      (IlvHorizontal|IlvVertical));
    virtual IlBoolean	usesDefaultButtonKeys() const;
    virtual void	reDraw() const;
    inline IlBoolean	isActive() const
	{ return !getFlag(ILVGADGETINACTIVEFLAG); }
    inline void		setActive(IlBoolean active)
	{ setFlag(ILVGADGETINACTIVEFLAG, !active); }
    inline IlUShort	getThickness() const
	{ return _thickness; }
    virtual void	setThickness(IlUShort thickness);
    inline IlBoolean	usesDefaultSize() const
	{ return getFlag(ILVGADGETDEFAULTSIZEFLAG); }
    virtual void	useDefaultSize(IlBoolean value);
    inline IlBoolean	isTransparent() const
	{ return getFlag(ILVGADGETTRANSPARENTFLAG); }
    inline IlBoolean	isOpaque() const
	{ return !isTransparent(); }
    virtual void	setTransparent(IlBoolean value);
    inline void		setOpaque(IlBoolean o)
	{ setTransparent(!o); }
    virtual IlBoolean	useDefaultColors() const;
    inline IlBoolean	isInverted() const
	{ return getFlag(ILVGADGETINVERTEDFLAG); }
    virtual IlvPalette*	getInsensitivePalette() const;
    virtual IlvPalette* getSelectionPalette() const;

    virtual IlvPalette* getSelectionTextPalette() const;

    inline void		callCallback()
	{ callCallbacks(CallbackSymbol());}

    IlvTransformer*	getTransformer() const;

    virtual IlBoolean	handleEvent(IlvEvent& event);

    virtual void	focusIn();
    virtual void	focusOut();
    virtual void	enterGadget();
    virtual void	leaveGadget();

    IlBoolean		isShowingFrame() const;
    virtual void	showFrame(IlBoolean show);

    virtual void	drawBackground(IlvPort*              dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion*      clip = 0) const;
    virtual void	drawFrame(IlvPort*		dst,
				  const IlvTransformer* t = 0,
				  const IlvRegion*	clip = 0) const;
    virtual void	drawContents(IlvPort*              dst,
				     const IlvTransformer* t = 0,
				     const IlvRegion*      clip = 0) const;

    void		setLookFeelHandler(IlvLookFeelHandler* handler);

    // Predefined callbacks
    IlvDefineCallback(FocusIn);
    IlvDefineCallback(FocusOut);
    IlvDefineCallback(EnterGadget);
    IlvDefineCallback(LeaveGadget);
    inline static IlSymbol*	FocusInSymbol()
	{ return _focusInSymbol; }
    inline static IlSymbol*	FocusOutSymbol()
	{ return _focusOutSymbol; }
    inline static IlSymbol*	EnterGadgetSymbol()
	{ return _enterGadgetSymbol; }
    inline static IlSymbol*	LeaveGadgetSymbol()
	{ return _leaveGadgetSymbol; }

    // Styling - Implementing IlvStylable
    virtual IlvDisplay* getStylableDisplay() const;
    virtual IlvStylist* getStylist() const;
    virtual const char* getStylableClassName() const;
    virtual const char* getStylableName() const;
    virtual const IlSymbol* const* getStylableTags(IlUInt&) const;
    virtual IlvStylable::State getStylableState() const;

protected:
    IlvLookFeelHandler*	_cachedLfh;
    IlvLookFeelHandler*	_lfh;
    IlvRect		_drawrect;
    IlUShort		_thickness;
    IlvPalette*		_invpalette;
    IlvPalette*		_topshadow;
    IlvPalette*		_bottomshadow;
    IlvPalette*		_selpalette;
    IlvPalette*		_sensitivePalette;
    IlvPalette*		_seltextpalette;
    IlvPalette*		_textpalette;
    IlvPalette*		_bgpalette;
    IlUInt		_flags;
    IlvIntensity	_alpha;

    IlvGadget(IlvDisplay*	display,
              IlUShort		thickness = IlvDefaultGadgetThickness,
              IlvPalette*	palette = 0);

public:
    inline IlvObjectLFHandler*	getObjectLFHandler(IlvClassInfo* c) const
	{
	    IlvLookFeelHandler* lf = getLookFeelHandler();
	    return lf ? lf->getObjectLFHandler(c) : 0;
	}
    virtual IlvLookFeelHandler*	getLookFeelHandler() const;
    virtual IlvIntensity	getAlpha() const;
    virtual IlvAntialiasingMode	getAntialiasingMode() const;
    inline void		setInsensitivePalette(IlvPalette* pal)
	{ IlvNewPalette(_sensitivePalette, pal); }
    inline void		setSelectionPalette(IlvPalette* pal)
	{ IlvNewPalette(_selpalette, pal); }
    inline void		setTopShadowPalette(IlvPalette* pal)
	{ IlvNewPalette(_topshadow, pal); }
    inline void		setBottomShadowPalette(IlvPalette* pal)
	{ IlvNewPalette(_bottomshadow, pal); }
    inline void		setInvertedPalette(IlvPalette* pal)
	{ IlvNewPalette(_invpalette, pal); }
    inline void		setSelectionTextPalette(IlvPalette* pal)
	{ IlvNewPalette(_seltextpalette, pal); }
    inline void		setNormalTextPalette(IlvPalette* pal)
	{ IlvNewPalette(_textpalette, pal); }
    inline void		setBgPalette(IlvPalette* pal)
	{ IlvNewPalette(_bgpalette, pal); }
    void		computePalettes();
    inline void		unLockPalettes()
	{
	    _invpalette->unLock();
	    _topshadow->unLock();
	    _bottomshadow->unLock();
	    _selpalette->unLock();
	    _sensitivePalette->unLock();
	    _seltextpalette->unLock();
	    _textpalette->unLock();
	    _bgpalette->unLock();
	}
    inline IlBoolean	getFlag(IlUShort fl) const
	{
	    return (_flags & ((IlUInt)(1) << fl))
		   ? IlTrue
		   : IlFalse;
	}
    inline void		setFlag(IlUShort fl)
	{ _flags |= (IlUInt(1) << fl); }
    inline void		setFlag(IlUShort fl, IlBoolean v)
	{
	    IlUInt f = IlUInt(1) << fl;
	    if (v) {
		_flags |=  f;
	    }
	    else {
		_flags &= ~f;
	    }
	}
    inline void		unSetFlag( IlUShort fl)
	{ _flags &= ~(IlUInt(1) << fl); }
    inline void		invertFlag(IlUShort fl)
	{
	    IlUInt f = IlUInt(1) << fl;
	    if (_flags & f) {
		_flags &= ~f;
	    }
	    else {
		_flags |=  f;
	    }
	}
    virtual IlvPalette*	getNormalTextPalette() const;
    virtual void	draw(IlvPort*,
			     const IlvTransformer*    = 0,
			     const IlvRegion* = 0) const;
    virtual void	applyTransform(const IlvTransformer*);
    inline IlvPalette*	getSensitivePalette() const // For compatibility
	{ return getInsensitivePalette(); }
    inline IlvPalette*	getTopShadowPalette()    const
	{ return _topshadow;   }
    inline IlvPalette*	getBottomShadowPalette() const
	{ return _bottomshadow;}
    inline IlvPalette*	getInvertedPalette()     const
	{ return _invpalette;  }
    inline IlvPalette*	getBgPalette()           const
	{ return _bgpalette;   }

    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer* = 0) const;
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* = 0) const;
    virtual void	invert(IlBoolean = IlFalse);

    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setLineStyle(IlvLineStyle*);
    virtual void	setLineWidth(IlUShort);
    virtual void	setFillStyle(IlvFillStyle);
    virtual void	setPattern(IlvPattern*);
    virtual void	setColorPattern(IlvColorPattern*);
    virtual void	setGradientPattern(IlvGradientPattern*);
    virtual void	setFont(IlvFont*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setArcMode(IlvArcMode);
    virtual void	setFillRule(IlvFillRule);
    virtual void	setPalette(IlvPalette*);
    virtual void	setAlpha(IlvIntensity);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);
    inline IlvRect	getDefinitionRect() const
	{ return _drawrect; }

    IlvBitmap*		getBitmap() const;
    IlvSystemPort*	getPort() const;
    IlvView*		getView() const;

    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlSymbol* const**) const;

    // callback functions not documented. Kept for compatibility only
    inline void		setFocusInCallbackName(IlSymbol* callbackName)
	{ setCallback(FocusInSymbol(), callbackName); }
    inline void		setFocusOutCallbackName(IlSymbol* callbackName)
	{ setCallback(FocusOutSymbol(), callbackName); }
    inline void		setEnterGadgetCallbackName(IlSymbol* callbackName)
	{ setCallback(EnterGadgetSymbol(), callbackName); }
    inline void		setLeaveGadgetCallbackName(IlSymbol* callbackName)
	{ setCallback(LeaveGadgetSymbol(), callbackName); }

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvGadget);

    DeclareGraphicAccessors();
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    static IlSymbol*	_showFrameValue;
    static IlSymbol*	_thicknessValue;
    static IlSymbol*	_activeValue;
    static IlSymbol*	_transparentValue;
    static IlSymbol*	_invertedValue;
    static IlSymbol*	_focusableValue;
    static IlSymbol*	_redrawMethod;
    static IlSymbol*	_fitToContentsMethod;

    virtual void	changeLanguage(const IlSymbol*);
    virtual void	changeLook(const IlvLookFeelHandler*);
    virtual void	updateLook();
    virtual void	changeLayoutAttributes(IlAny, IlAny);

    static IlSymbol*	ToolTipSymbol();
    static IlSymbol*	_focusInSymbol;
    static IlSymbol*	_focusOutSymbol;
    static IlSymbol*	_enterGadgetSymbol;
    static IlSymbol*	_leaveGadgetSymbol;
};

// --------------------------------------------------------------------------
inline IlBoolean
IsAnIlvGadget(const IlvGraphic* object)
{
    return object->isSubtypeOf(IlvGadget::ClassInfo());
}

class IlvHGadgetInteractor;
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGadgetInteractor
    : public IlvInteractor
{
public:
    IlvGadgetInteractor();
    virtual ~IlvGadgetInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic*,
				    IlvEvent&,
				    const IlvTransformer*);
    virtual IlBoolean	accept(const IlvGraphic*) const;
    virtual void	getCallbackTypes(IlUInt&,
					 const char* const**,
					 const IlSymbol* const**) const;
    inline void		setHGadgetInteractor(IlvHGadgetInteractor* inter)
	{ _hGadgetInteractor = inter; }
    inline IlvHGadgetInteractor*	getHGadgetInteractor() const
	{ return _hGadgetInteractor; }
    DeclareLazyInteractorTypeInfoRO(IlvGadgetInteractor);

protected:
    IlvHGadgetInteractor*	_hGadgetInteractor;
};

// --------------------------------------------------------------------------
ILVVWSMODULEINIT(gadget);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/gadget.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/gadget.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/gadget.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/gadget.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Base_Gadget_H */
