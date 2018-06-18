// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/view.h
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
// Declaration of the IlvView base classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_View_H
#define __Ilv_Base_View_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#  include <ilviews/intrface/value.h>
#endif
#if !defined(__Ilv_Base_Evloop_H)
#  include <ilviews/base/evloop.h>
#endif
#if !defined(__Ilv_Bidi_Interf_H)
#  include <ilviews/bidi/interf.h>
#endif
#if !defined(__Ilv_Base_Stylable_H)
#  include <ilviews/base/stylable.h>
#endif

#if defined(WINDOWS) || DOXYGEN_GENERATION


#  if defined(WIN64)
typedef unsigned int	IlvMsgParam;
typedef IlUIntPtr	IlvWParam;
typedef IlIntPtr	IlvLParam;

inline IlAny IlvCastIlvWParamToIlAny(IlvWParam v)
{
    return IlCastIlUIntPtrToIlAny(v);
}

inline IlAny IlvCastIlvLParamToIlAny(IlvLParam v)
{
    return IlCastIlIntPtrToIlAny(v);
}

inline IlvWParam IlvCastIlAnyToIlvWParam(IlAny v)
{
    return IlCastIlAnyToIlUIntPtr(v);
}

inline IlvLParam IlvCastIlAnyToIlvLParam(IlAny v)
{
    return IlCastIlAnyToIlIntPtr(v);
}
#  elif defined(WIN32)
typedef unsigned int	IlvMsgParam;
typedef unsigned int	IlvWParam;
typedef long		IlvLParam;

inline IlAny IlvCastIlvWParamToIlAny(IlvWParam v)
{
    return IlCastIlUIntToIlAny(v);
}

inline IlAny IlvCastIlvLParamToIlAny(IlvLParam v)
{
    return IlCastIlIntToIlAny(v);
}

inline IlvWParam IlvCastIlAnyToIlvWParam(IlAny v)
{
    return IlCastIlAnyToIlUInt(v);
}

inline IlvLParam IlvCastIlAnyToIlvLParam(IlAny v)
{
    return IlCastIlAnyToIlInt(v);
}
#  else  /* !WIN64 && !WIN32 */
__ERROR__
#  endif /* !WIN64 && !WIN32 */

typedef IlBoolean (* IlvWindowProc)(IlvAbstractView*	view,
				    IlvSystemView	hWnd,
				    IlvMsgParam		iMessage,
				    IlvWParam		wParam,
				    IlvLParam		lParam,
				    IlAny&		returned,
				    IlAny		userArg);
#endif /* WINDOWS */

#if defined(X11)
class IlvXColormap;
#endif /* X11 */

// --------------------------------------------------------------------------
#define DeclareViewProperties()		IlvDeclarePropClassInfo()
#define DeclareLazyViewProperties()	IlvDeclareLazyPropClassInfo()
#define DeclareViewAccessors()		DeclareValueAccessors()

// --------------------------------------------------------------------------
// View Class Information
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvViewClassInfo
    : public IlvValuedClassInfo
{
public:
    inline
    IlvViewClassInfo*	getSuperViewClass() const
	{ return ILVDYNAMICCAST(IlvViewClassInfo*, getSuperClass()); }
    static
    IlvViewClassInfo*	Create(const char*,
			       IlvClassInfo**,
			       IlvGetAccessorsFunction = 0);
protected:
    IlvViewClassInfo(const char*	     className,
		     IlvClassInfo**	     superClass,
		     IlvGetAccessorsFunction ga = 0)
	: IlvValuedClassInfo(className, superClass, ga)
    {}
};

// --------------------------------------------------------------------------
enum IlvUIEffect {
    IlvNoUIEffect,
    IlvScrollUIEffect,
    IlvFadeUIEffect
};

// --------------------------------------------------------------------------
// An AbstractView object definition
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvAbstractView
    : public IlvSystemPort,
      public IlvBidiInterface,
      public IlvStylable
{
    friend class IlvPaintDC;
public:
    virtual ~IlvAbstractView();

    virtual void	move(const IlvPoint& position);
    virtual void	resize(IlvDim w, IlvDim h);
    virtual void	moveResize(const IlvRect& newSize);
    virtual void	position(IlvPoint& position) const;
    virtual void	erase(const IlvRect&	rect,
			      IlBoolean		reDraw = IlFalse);
    virtual void	erase(IlBoolean reDraw = IlFalse);
    virtual void	setBackground(IlvColor* c);
    virtual void	setBackgroundBitmap(IlvBitmap* b);
    virtual void	raise();
    virtual void	lower();
    virtual void	show();
    virtual void	hide();
    virtual IlBoolean	grab(IlvCursor* cursor = 0);
    virtual void	unGrab();
    virtual IlBoolean	isViewable() const;
    virtual IlBoolean	isScrolled() const;

    inline
    IlvAbstractView*	getParent() const { return _parent; }
    IlvSystemView	getSystemView() const;
    IlvSystemView	getShellSystemView() const;
    inline IlBoolean	hasGrab() const { return _hasGrab; }
    inline IlvColor*	getBackground() const { return _background; }
    inline IlvBitmap*	getBackgroundBitmap() const
			{
			    return _backgroundBitmap;
			}
    inline IlvCursor*	getCursor() const { return _cursor; }
    virtual void	globalBBox(IlvRect& bbox)  const;
    virtual void	frameBBox(IlvRect& bbox) const;
    virtual void	sizeVisible(IlvRect& rect) const;
    virtual void	boundingBox(IlvRect& bbox) const;
    void		ensureVisible(const IlvPoint& point);
    void		ensureVisible(const IlvRect& rect);
    void		setCursor(IlvCursor* cursor);

    IlBoolean		enableMultitouch(IlBoolean enable);
    IlBoolean		isMultitouchEnabled();

    void		removeFromParent() const;
    void		borderWidth(IlvDim b);
    void		realize();
    virtual IlBoolean	isAnAbstractView() const;
    inline IlBoolean	isATopView() const { return _isTop; }

#if defined(WINDOWS) || DOXYGEN_GENERATION
    inline void		setXY(IlvPos vx, IlvPos vy)
			{
			    _position.move(vx, vy);
			}
    inline void		setWH(IlvDim vw, IlvDim vh)
			{
			    _width = vw;
			    _height = vh;
			}
    inline IlAny	getOldWindowProc() const { return _oldWindowProc; }
    IlBoolean		getCallOldWindowProc() const
			{
			    return _mustCallOldWindowProc;
			}
    void		setCallOldWindowProc(IlBoolean v)
			{
			    _mustCallOldWindowProc = v;
			}
    void		setWindowProc(IlvWindowProc	windowProc,
				      IlAny		procArgument = 0);
    void		removeWindowProc(IlvWindowProc	windowProc,
					IlAny		procArgument = 0);
    IlBoolean		callWindowProc(IlvSystemView,
				       IlvMsgParam,
				       IlvWParam,
				       IlvLParam,
				       IlAny&);
#endif /* WINDOWS */

#if defined(X11)
    void		setXColormap(const IlvXColormap*) const;
#endif /* X11 */
    IlBoolean		isSensitive() const;
    void		setSensitive(IlBoolean sensitivity);
    IlBoolean		setFocus(IlvEvent* reason = 0);
    inline IlBoolean	isLastFocusOfShell() const { return _lastFocus; }
    inline void		setLastFocusOfShell(IlBoolean last = IlTrue)
			{
			    _lastFocus = last;
			}

    virtual void	callExpose(IlvEvent& event);
    virtual void	callInput(IlvEvent& event);
    virtual void	callResize(IlvRect& rect);
    virtual void	callDestroy();
    // Not documented
    virtual void	childNotifyAdd(IlvAbstractView*);
    virtual void	childNotifyRemove(IlvAbstractView*);
    virtual IlAny	internalHandleMnemonic(char) const;
    virtual IlAny	internalHandleAccelerator(IlvEvent&) const;
    virtual void	updateTitle();
    virtual void	reparent(IlvAbstractView*);
    inline IlBoolean	isSelectionOwner() { return _hasSelection; }
    void		selectionRequest();
    void		loseSelection();
    IlBoolean		internalSetFocus(IlAny);

    DeclareViewAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_xValue;
    static IlSymbol*	_yValue;
    static IlSymbol*	_widthValue;
    static IlSymbol*	_heightValue;
    static IlSymbol*	_backgroundValue;
    static IlSymbol*	_backgroundBitmapValue;
    static IlSymbol*	_boundingBoxValue;
    static IlSymbol*	_globalBBoxValue;
    static IlSymbol*	_grabValue;
    static IlSymbol*	_scrolledValue;
    static IlSymbol*	_sensitiveValue;
    static IlSymbol*	_sizeVisibleValue;
    static IlSymbol*	_moveMethod;
    static IlSymbol*	_resizeMethod;
    static IlSymbol*	_ensurePointVisibleMethod;
    static IlSymbol*	_ensureRectVisibleMethod;
    static IlSymbol*	_raiseMethod;
    static IlSymbol*	_lowerMethod;

    // Bidi interface
    virtual
    IlvBidiContext*	getBidiContext(IlBoolean fallback = IlTrue) const;
    virtual
    IlvBidiContext*	getDefaultBidiContext() const;
    virtual IlBoolean	setBidiContext(IlvBidiContext*);
    virtual IlBoolean	changeOrientation();
#if defined(WINDOWS)
    virtual
    IlvWindowsHandle	computeDC();
    virtual void	deleteDC();
    void		pushIlvDC(IlvDC*);
    void		popIlvDC();
#endif /* WINDOWS */

    // Styling - Implementing IlvStylable
    virtual IlvDisplay* getStylableDisplay() const;
    virtual IlvStylist* getStylist() const;
    virtual const char* getStylableClassName() const;

    // Event compression
    virtual void	setCompressPointerMoved(IlBoolean val);
    virtual void	setCompressButtonDragged(IlBoolean val);
    inline IlBoolean	getCompressPointerMoved() const
			{
			    return _compressMotion;
			}
    inline IlBoolean	getCompressButtonDragged() const
			{
			    return _compressDrag;
			}

protected:
    void		addGrab();
    void		removeGrab();
    virtual void	initSystemCallbacks();
    virtual void	removeSystemCallbacks();

    IlvAbstractView(IlvDisplay* display, IlvAbstractView* parent = 0);
    IlvAbstractView();

#if defined(WINDOWS)
    virtual void	initIlvDC();
    virtual void	internalCleanDC();
#endif /* WINDOWS */

    IlvAbstractView*	_parent;
    IlvSystemView	_window;
    IlvSystemView	_shellWindow;
    IlvPoint		_position;
    IlBoolean		_sensitive;
    IlvColor*		_background;
    IlvBitmap*		_backgroundBitmap;
    IlvCursor*		_cursor;
    IlvCursor*		_oldCursor;
    IlBoolean		_isTop; // Is it a Top window ?
    IlBoolean		_lastFocus;
    IlBoolean		_hasGrab;
    IlBoolean		_hasSelection;
    IlBoolean		_compressMotion;
    IlBoolean		_compressDrag;

#if defined(WINDOWS)
    IlvDC*		_savedIlvDC;
    int			_uiEffectType;
    IlvDirection	_uiEffectDirection;
    IlUInt		_uiEffectDuration;

    IlAny		_oldWindowProc;
    IlvWindowProc	_windowProc;
    IlAny		_windowProcArg;
    IlBoolean		_mustCallOldWindowProc;
    IlvCursor*		_deepCursor;
    IlAny		_backgroundBrush;
#endif /* WINDOWS */

public:
    // (ex IlvCompositeAbstractView) children management. Not documented.
    inline void		addChild(const IlvAbstractView* child)
	{
	    if (_children)
		_children->append(IL_CONSTCAST(IlvAbstractView*, child));
	}
    inline void		removeChild(const IlvAbstractView* child)
	{
	    if (_children)
		_children->remove(IL_CONSTCAST(IlvAbstractView*, child));
	}
    inline IlvView*	childView() const
	{
	    return (_children && _children->getFirst())
		? IL_REINTERPRETCAST(IlvView*,
				     _children->getFirst()->getValue())
		: IL_REINTERPRETCAST(IlvView*, 0);
	}
    inline IlUInt	getCardinal() const
			{
			    return _children ? _children->getLength() : 0;
			}
#if defined(WINDOWS) || DOXYGEN_GENERATION
    virtual IlBoolean	isScrollView() const { return IlFalse; }
    inline void		setDeepCursor(IlvCursor* cur)
			{
			    if (cur != _deepCursor) {
				if (cur)
				    cur->lock();
				if (_deepCursor)
				    _deepCursor->unLock();
				_deepCursor = cur;
			    }
			}
    inline
    const IlvCursor*	getDeepCursor() const { return _deepCursor; }
    inline void		setUIEffect(int			type,
				    IlvDirection	dir = IlvBadPosition,
				    IlUInt		duration = 0)
			{
			    _uiEffectType = type;
			    _uiEffectDirection = dir;
			    _uiEffectDuration=duration;
			}
    inline void		getUIEffect(int&		type,
				    IlvDirection&	dir,
				    IlUInt&		duration) const
			{
			    type = _uiEffectType;
			    dir = _uiEffectDirection;
			    duration = _uiEffectDuration;
			}
    void		setOpacity(IlvIntensity level);
    void		setTransparentColorKey(IlvIntensity r,
					       IlvIntensity g,
					       IlvIntensity b);

    void		setLayered(IlBoolean layered);
#else /* !WINDOWS */
    inline void		setUIEffect(int,
				    IlvDirection = IlvBadPosition,
				    IlUInt = 0) {}
    inline void		getUIEffect(int&, IlvDirection&, IlUInt&) const {}
    inline void		setOpacity(IlvIntensity) {}
    inline void		setLayered(IlBoolean) { _layered = IlFalse; }
    void		setTransparentColorKey(IlvIntensity,
					       IlvIntensity,
					       IlvIntensity) {}

#endif /* !WINDOWS */
    inline IlBoolean	isLayered() const { return _layered; }
    inline IlvIntensity	getOpacity() const { return _opacity; }
    inline void		getTransparentColorKey(IlvIntensity& r,
					       IlvIntensity& g,
					       IlvIntensity& b) const
			{
			    r = _rtransp;
			    g = _gtransp;
			    b = _btransp;
			}
    inline
    const IlList*	getChildren() const { return _children; }

protected:
    IlList*		_children;

    IlvIntensity	_opacity;
    IlBoolean		_layered;
    IlBoolean		_resetTranspColorKey;
    IlvIntensity	_rtransp;
    IlvIntensity	_gtransp;
    IlvIntensity	_btransp;

    IlvDeclareLazyPropRootClassInfo();

private:
    static void		SwapSystemView(IlvAbstractView*,
				       IlvAbstractView*,
				       IlBoolean = IlFalse);
    static void		RemapSystemViews(IlvAbstractView*,
					 IlvAbstractView* = 0,
					 IlBoolean = IlFalse);

    IlBoolean		_multitouchEnabled;
};

// For backward compatibility
#define IlvCompositeAbstractView IlvAbstractView

// --------------------------------------------------------------------------
class IlvView;
typedef void (* IlvExposeCallback) (IlvView*, IlvEvent&, IlAny arg);
IL_DEFINEFPTRTOANYCAST(IlvExposeCallback);
typedef void (* IlvInputCallback)  (IlvView*, IlvEvent&, IlAny arg);
IL_DEFINEFPTRTOANYCAST(IlvInputCallback);
typedef void (* IlvResizeCallback) (IlvView*, IlvRect&,  IlAny arg);
IL_DEFINEFPTRTOANYCAST(IlvResizeCallback);
typedef void (* IlvDestroyCallback)(IlvView*,            IlAny arg);
IL_DEFINEFPTRTOANYCAST(IlvDestroyCallback);

class IlvTopView;

// Topview properties
#define IlvStandardBorder	((IlUInt)0)
#define IlvNoBorder		((IlUInt)(1<< 1))
#define IlvNoResizeBorder	((IlUInt)(1<< 2))
#define IlvSaveUnder		((IlUInt)(1<< 3))
#define IlvNotActivated		((IlUInt)(1<< 4))
#define IlvNoActivate		IlvNotActivated /* 2.3 compat. */
#define IlvNoTitleBar		((IlUInt)(1<< 5))
#define IlvNoSysMenu		((IlUInt)(1<< 6))
#define IlvNoCloseBox		((IlUInt)(1<< 7))
#define IlvNoMinBox		((IlUInt)(1<< 8))
#define IlvNoMaxBox		((IlUInt)(1<< 9))
#define IlvNotInWinList		((IlUInt)(1<<10))
#define IlvIconified		((IlUInt)(1<<11))
#define IlvMaximized		((IlUInt)(1<<12))
#define IlvMDIChild		((IlUInt)(1<<13))
#define IlvTopMost		((IlUInt)(1<<14))
#define IlvToolView		((IlUInt)(1<<15))
#define IlvDropShadow		((IlUInt)(1<<16))
#define IlvNoTouchScreenNavigation	((IlUInt)(1<<17))

enum IlvMDICommand {
    IlvMdiArrangeIcon		= 0,
    IlvMdiCascade		= 1,
    IlvMdiTileHorizontal	= 2,
    IlvMdiTileVertical		= 3,
    IlvMdiTileSkipDisabled	= 4 /* Acts as a flag to MdiTile commands */
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvView
    : public IlvAbstractView
{
public:
    IlvView(IlvAbstractView*	parent,
	    const IlvRect&	size,
	    IlBoolean		visible = IlTrue);
    IlvView(IlvDisplay*		display,
	    IlvSystemView	available);
    IlvView(IlvDisplay*		display,
	    IlvSystemView	parent,
	    const IlvRect&	size,
	    IlBoolean		visible = IlTrue);
    IlvView(IlvDisplay*		display,
	    const char*		name,
	    const char*		title,
	    const IlvRect&	size,
	    IlBoolean		visible = IlTrue);
    IlvView(IlvDisplay*		display,
	    const char*		name,
	    const char*		title,
	    const IlvRect&	size,
	    IlUInt		properties,
	    IlBoolean		visible      = IlTrue,
	    IlvSystemView	transientFor = 0);
    virtual ~IlvView();

    inline const char*	getName() const { return _name; }
    virtual void	setName(const char* name);
    virtual void	setExposeCallback(IlvExposeCallback	expose,
					  IlAny			userArg = 0);
    virtual void	setInputCallback(IlvInputCallback	input,
					 IlAny			userArg = 0);
    IlBoolean		isLastInputCallback(IlvInputCallback input,
					    IlAny userArg = 0) const;
    virtual void	setResizeCallback(IlvResizeCallback	resize,
					  IlAny			userArg = 0);
    virtual void	setDestroyCallback(IlvDestroyCallback	destroy,
					   IlAny		userArg = 0);
    virtual void	setDeleteCallback(IlvDestroyCallback	del,
					  IlAny			userArg = 0);
    virtual void	removeExposeCallback(IlvExposeCallback	expose = 0,
					     IlAny		userArg = 0);
    virtual void	removeInputCallback(IlvInputCallback	input = 0,
					    IlAny		userArg = 0);
    virtual void	removeResizeCallback(IlvResizeCallback	resize = 0,
					     IlAny		userArg = 0);
    virtual void	removeDestroyCallback(IlvDestroyCallback destroy = 0,
					      IlAny		 userArg = 0);
    virtual void	removeDeleteCallback(IlvDestroyCallback	del  = 0,
					     IlAny		userArg = 0);
    virtual void	callExpose(IlvEvent& event);
    virtual void	callInput(IlvEvent& event);
    virtual void	callResize(IlvRect& rect);
    virtual void	callDestroy();
    virtual void	callDelete();
    void		startCheckingDeletion(IlBoolean&);
    void		stopCheckingDeletion(IlBoolean&);
    void		startCheckingViewFocusChange(IlBoolean&);
    void		stopCheckingViewFocusChange(IlBoolean&);
    void		setShapeMask(IlvBitmap*	mask,
				     IlBoolean	useTitle = IlFalse);

#if defined(WINDOWS)
    virtual void	parseWM_SIZE(IlvLParam);
#endif /* WINDOWS */
    void		iconify();
    void		iconBitmap(IlvBitmap* image, IlvBitmap* mask = 0);
#if defined(WINDOWS)
    IlvDim		getMinimumWidth()  const { return _minw; }
    IlvDim		getMinimumHeight() const { return _minh; }
    IlvDim		getMaximumWidth()  const { return _maxw; }
    IlvDim		getMaximumHeight() const { return _maxh; }
    IlvWindowsHandle	getIconBitmap() { return _icon; }
#endif /* WINDOWS */
    virtual void	show();
    virtual void	hide();
    virtual void	move(const IlvPoint& point);
    virtual void	resize(IlvDim w, IlvDim h);
    virtual void	moveResize(const IlvRect& rect);
    inline const char*	getTitle() const { return _title; }
    virtual void	setTitle(const char* title);
    virtual IlBoolean	isIconified() const;
    virtual IlBoolean	showModal(IlBoolean	doesGrab = IlFalse,
				  IlvCursor*	cursor	 = 0);
    void		moveToView(const IlvView* view,
				   IlvDirection   alignment  = IlvCenter,
				   IlvPos	  dx = 0,
				   IlvPos	  dy = 0,
				   IlBoolean	  ensureInScreen = IlTrue);
    void		moveToMouse(IlvDirection alignment  = IlvCenter,
				    IlvPos	 dx = 0,
				    IlvPos	 dy = 0,
				    IlBoolean	 ensureInScreen = IlTrue);
    void		moveToScreen(IlvDirection alignment = IlvCenter,
				     IlvPos	  dx = 0,
				     IlvPos	  dy = 0,
				     IlBoolean    ensureInScreen = IlTrue);
     void		ensureInScreen(IlvPos xMargin = 0,
				       IlvPos yMargin = 0);
     inline IlBoolean	isModal() const
			{
			    return (_isTop && _isModal) ? IlTrue : IlFalse;
			}
    void		setIconTitle(const char* title);
    void		setMinimumSize(IlvDim w, IlvDim h);
    void		setMaximumSize(IlvDim w, IlvDim h);
    inline IlBoolean	isVisible() const { return _visible; }

    void		sendToMDIChildren(IlvMDICommand) const;

    // User Properties
    inline void		addProperty(const IlSymbol* key, IlAny value)
			{
			    if (!_properties) {
				_properties = new IlAList();
			    }
			    _properties->insert((IlAny)key, value);
			}
     inline void	setProperty(const IlSymbol* key, IlAny value)
			{
			    if (value) {
				if (!replaceProperty(key, value)) {
				    addProperty(key, value);
				}
			    }
			    else {
				removeProperty(key);
			    }
			}
    inline IlBoolean	removeProperty(const IlSymbol* key)
			{
			    return _properties
				? _properties->remove((IlAny)key)
				: IlFalse;
			}
    inline IlBoolean	replaceProperty(const IlSymbol* key, IlAny value)
			{
			    return _properties
				? _properties->replace((IlAny)key, value)
				: IlFalse;
			}
    inline IlAny	getProperty(const IlSymbol* key) const
			{
			    return _properties
				? _properties->get((IlAny)key)
				: 0;
			}
    inline IlBoolean	hasProperty(const IlSymbol* key) const
			{
			    return _properties
				? _properties->find((IlAny)key)
				: IlFalse;
			}
    inline IlBoolean	needBC() const { return _bc;  }
    virtual void	updateTitle();
    inline IlUInt	getTopProperties() const { return _topProperties; }

    DeclareViewAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_visibleValue;
    static IlSymbol*	_titleValue;
    static IlSymbol*	_iconTitleValue;
    static IlSymbol*	_propertiesValue;
    static IlSymbol*	_iconifiedValue;
    static IlSymbol*	_isModalValue;
    static IlSymbol*	_showModalMethod;

    // Styling
    virtual const char* getStylableName() const;
protected:
    IlvView()
	: IlvAbstractView(),
	  _owner(IlFalse),
	  _name(0),
	  _expose(),
	  _input(),
	  _destroy(),
	  _resize(),
	  _delete(),
	  _bc(IlFalse),
	  _visible(IlTrue),
	  _title(0),
	  _isModal(IlFalse),
#if defined(WINDOWS)
	  _minw(0),
	  _minh(0),
	  _maxw(0),
	  _maxh(0),
	  _icon(0),
	  _mdiClient(0),
	  _ownicon(IlFalse),
#endif /* WINDOWS */
	  _properties(0),
	  _topProperties(0)
    {}
    IlvView(IlvDisplay* display)
	: IlvAbstractView(display),
	  _owner(IlFalse),
	  _name(0),
	  _expose(),
	  _input(),
	  _destroy(),
	  _resize(),
	  _delete(),
	  _bc(IlFalse),
	  _visible(IlTrue),
	  _title(0),
	  _isModal(IlFalse),
#if defined(WINDOWS)
	  _minw(0),
	  _minh(0),
	  _maxw(0),
	  _maxh(0),
	  _icon(0),
	  _mdiClient(0),
	  _ownicon(IlFalse),
#endif /* WINDOWS */
	  _properties(0),
	  _topProperties(0)
    {}
    IlvView(IlvAbstractView* parent)
	: IlvAbstractView(parent->getDisplay(), parent),
	  _owner(IlFalse),
	  _name(0),
	  _expose(),
	  _input(),
	  _destroy(),
	  _resize(),
	  _delete(),
	  _bc(IlFalse),
	  _visible(IlTrue),
	  _title(0),
	  _isModal(IlFalse),
#if defined(WINDOWS)
	  _minw(0),
	  _minh(0),
	  _maxw(0),
	  _maxh(0),
	  _icon(0),
	  _mdiClient(0),
	  _ownicon(IlFalse),
#endif /* WINDOWS */
	  _properties(0),
	  _topProperties(0)
    {}

    IlBoolean		_owner;
    char*		_name;
    // Callback lists
    IlAList		_expose;
    IlAList		_input;
    IlAList		_destroy;
    IlAList		_resize;
    IlAList		_delete;
    IlBoolean		_bc;  // Do we need Backward compatibility ?
    IlBoolean		_visible;
    char*		_title;
    int			_isModal; // Is the view in modal use ?
#if defined(WINDOWS)
    IlvDim		_minw;
    IlvDim		_minh;
    IlvDim		_maxw;
    IlvDim		_maxh;
    IlvWindowsHandle	_icon;  // In fact a HICON
    IlvSystemView	_mdiClient;
    IlBoolean		_ownicon;
#endif /* WINDOWS */
    IlAList*		_properties;
    IlUInt		_topProperties;

    virtual void	initSystemCallbacks();
    virtual void	removeSystemCallbacks();
    IlBoolean		addModal();
    void		removeModal();

private:
    void		createNewName();
    static IlUInt	_nameCounter;

    IlvDeclareLazyPropClassInfo();
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvViewHandler
{
public:
    enum EventType {
	NoEvent		= 0,
	InputEvent	= 1,
	ExposeEvent	= 2,
	ResizeEvent	= 4,
	DestroyEvent	= 8
    };

    IlvViewHandler(IlvView* view = 0, IlUInt mask = NoEvent);
    virtual ~IlvViewHandler();

    inline IlUInt	getMask() const { return _mask; }

    void		setMask(IlUInt mask);

    inline IlvView*	getView() const { return _view; }

    virtual void	setView(IlvView* view);

    virtual void	viewDeleted();

    virtual void	handleResize(const IlvRect& rect);

    virtual void	handleInput(IlvEvent& event);

    virtual void	handleDestroy();

    virtual void	handleExpose(IlvEvent& event);

protected:
    IlvView*		_view;
    IlUInt		_mask;

    void		initCallbacks();
    void		removeCallbacks();
};

// --------------------------------------------------------------------------
typedef void (* IlvDestroyTopCallback)(IlvTopView*, IlAny);

class ILVDSPEXPORTED IlvTopView
    : public IlvView
{
public:
    IlvTopView(IlvDisplay*	d,
	       const char*	name,
	       const char*	title,
	       const IlvRect&	dims,
	       IlBoolean	visible = IlTrue)
	: IlvView(d, name, title, dims, visible)
    {
	_isTop = IlTrue;
	_bc = IlTrue;
    }
    IlvTopView(IlvDisplay*	d,
	       const char*	name,
	       const char*	title,
	       const IlvRect&	dims,
	       IlUInt		properties,
	       IlBoolean	visible       = IlTrue,
	       IlvSystemView	transientFor  = 0)
	: IlvView(d, name, title, dims, properties, visible, transientFor)
    {
	_isTop = IlTrue;
	_bc = IlTrue;
    }

    // Keep 2.0 compatibility
    virtual void	setDeleteCallback(IlvDestroyCallback, IlAny = 0);
    void		setDeleteCallback(IlvDestroyTopCallback d,
					  IlAny arg = 0)
    	{
	    setDeleteCallback((IlvDestroyCallback)d, arg);
	}
    virtual void	removeDeleteCallback(IlvDestroyCallback   = 0,
					     IlAny = 0);
    void		removeDeleteCallback(IlvDestroyTopCallback d,
					     IlAny		   arg = 0)
	{
	    removeDeleteCallback((IlvDestroyCallback)d, arg);
	}
    virtual void	setDestroyCallback(IlvDestroyCallback,
					   IlAny = 0);
    void		setDestroyCallback(IlvDestroyTopCallback d,
					   IlAny		 arg = 0)
	{
	    setDestroyCallback((IlvDestroyCallback)d, arg);
	}
    virtual void	removeDestroyCallback(IlvDestroyCallback,
					      IlAny = 0);
    void		removeDestroyCallback(IlvDestroyTopCallback d   = 0,
					      IlAny		    arg = 0)
	{
	    removeDestroyCallback((IlvDestroyCallback)d, arg);
	}
    inline void		title(const char* t)     { setTitle(t);     } // 1.0
    inline void		iconTitle(const char* i) { setIconTitle(i); } // 1.0
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvScrollView
    : public IlvAbstractView
{
public:
    IlvScrollView(IlvDisplay*		display,
		  IlvSystemView		parent,
		  const IlvRect&	size,
		  IlBoolean		visible = IlTrue);
    IlvScrollView(IlvAbstractView*	parent,
		  const IlvRect&	size,
		  IlBoolean		visible = IlTrue);
    virtual ~IlvScrollView();

#if defined(WINDOWS)
    inline IlBoolean	isScrollView() const { return IlTrue; }
    IlvDim		visibleWidth() const;
    IlvDim		visibleHeight() const;
    void		updateScrollRange();

    IlvPos		_offsetx;
    IlvPos		_offsety;
#endif /* WINDOWS */
protected:
    virtual void	initSystemCallbacks();
    virtual void	removeSystemCallbacks();
};

// --------------------------------------------------------------------------
// Special View that has a predefined Resize method
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvElasticView
    : public IlvView
{
public:
    IlvElasticView(IlvAbstractView*	parent,
		   const IlvRect&	size,
		   IlBoolean		visible = IlTrue);
    IlvElasticView(IlvDisplay* display, IlvSystemView available);
    IlvElasticView(IlvDisplay*		display,
		   IlvSystemView	parent,
		   const IlvRect&	size,
		   IlBoolean		visible = IlTrue);
    IlvElasticView(IlvDisplay*		display,
		   const char*		name,
		   const char*		title,
		   const IlvRect&	size,
		   IlBoolean		visible = IlTrue);
    IlvElasticView(IlvDisplay*		display,
		   const char*		name,
		   const char*		title,
		   const IlvRect&	dims,
		   IlUInt		properties,
		   IlBoolean		visible      = IlTrue,
		   IlvSystemView	transientFor = 0);

    virtual void	resize(IlvDim w, IlvDim h);
    virtual void	moveResize(const IlvRect& rect);
    void		doResize();
    void		callResize(IlvRect& dims);
    virtual void	childNotifyAdd(IlvAbstractView*);
    virtual void	childNotifyRemove(IlvAbstractView*);
#if defined(WINDOWS)
    virtual void	parseWM_SIZE(long);
#endif /* WINDOWS */

protected:
    IlvDim		_previousw;
    IlvDim		_previoush;
    IlAList		_childDims;	// Initial dims for children,
					// based upon _previousX
    void		initElastic();
};

#define IlvPreRegisterViewClass(classname)				\
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvRegisterViewClass(classname, superclass)			\
ILVDEFINECLASSINFOMEMBERS(classname,					\
	IlvViewClassInfo::Create(#classname, superclass::ClassPtr()))

#define IlvRegisterViewClassWithAccessors(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,					\
	IlvViewClassInfo::Create(#classname, superclass::ClassPtr(),	\
				 classname::GetAccessors))

#define IlvPostRegisterViewClass(classname, superclass)			\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	IlvViewClassInfo::Create(#classname, superclass::ClassPtr()))

#define IlvPostRegisterViewClassWithAccessors(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	IlvViewClassInfo::Create(#classname, superclass::ClassPtr(),	\
				 classname::GetAccessors))

ILVDSPMODULEINIT(b0view);
#endif /* !__Ilv_Base_View_H */
