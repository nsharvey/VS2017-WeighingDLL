// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/graphic.h
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
// Declaration of the IlvGraphic and IlvSimpleGraphic classes
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Graphic_H
#define __Ilv_Base_Graphic_H

#if !defined(__Ilv_Base_Iostream_H)
// This include needs to be out of util.h because of a limit of the
// preprocessor of msvc5 for the #if blocks.
#  include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Util_Util_H)
#  include <ilviews/util/util.h>
#endif
#if !defined(__Ilv_Base_Region_H)
#  include <ilviews/base/region.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Graphics_Io_H)
#  include <ilviews/graphics/io.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#  include <ilviews/intrface/value.h>
#endif
#if !defined(__Ilv_Util_Im_H)
#  include <ilviews/util/im.h> // for IlvImValue
#endif
#if !defined(__Ilv_Util_Proplist_H)
#  include <ilviews/util/proplist.h>
#endif
#if !defined(__Ilv_Bidi_Interf_H)
#  include <ilviews/bidi/interf.h>
#endif

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "views.lib")
#endif

class IlvValue;
class IlvValueTypeClass;
class IlvObjectProperty;
class IlvGraphicCallbackStruct;
class IlvLookFeelHandler;
class IlvObjectLFHandler;

#define DeclareTypeInfoRO_()						\
    inline IlvGraphicClassInfo* getGraphicClassInfo() const		\
	{ return (IlvGraphicClassInfo*)getClassInfo(); }		\
    static IlvGraphic* read(IlvInputFile&, IlvPalette*);		\
    virtual IlvGraphic* copy() const
#define DeclareTypeInfoRO() IlvDeclarePropClassInfo();			\
    DeclareTypeInfoRO_()
#define DeclareLazyTypeInfoRO() IlvDeclareLazyPropClassInfo();		\
    DeclareTypeInfoRO_()

#define DeclareTypeInfo() DeclareTypeInfoRO();				\
    virtual void write(IlvOutputFile&) const
#define DeclareLazyTypeInfo() DeclareLazyTypeInfoRO();			\
    virtual void write(IlvOutputFile&) const
// 2.1 compatibility:
#define DeclareTypeInfo1() DeclareTypeInfoRO()

#define DeclareIOConstructors(classname) public:			\
    classname(IlvInputFile& file, IlvPalette* palette = 0);		\
    classname(const classname& source)

#define DeclareGraphicAccessors() DeclareValueAccessors()

class IlvInteractor;
class IlvGraphic;
class IlvSmartSet;
class IlvShapeInterface;
class IlvSelectionInterface;

#define DeclareShapeInterface()						\
	virtual void initShapeInterface() const

#define DeclareInterface(Name)						\
	virtual void init##Name##Interface() const

#define DeclareRootInterface(Name)					\
	DeclareInterface(Name);						\
	virtual Ilv##Name##Interface* get##Name##Interface() const


#if defined(ILVUSEAPPLYCLASS)
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvApplyHook
{
public:
    IlvApplyHook() {}
    virtual ~IlvApplyHook();

    virtual void	apply(IlvGraphic*) = 0;
};

// --------------------------------------------------------------------------
typedef void (* IlvApplyObject)(IlvGraphic* obj, IlAny);

class ILVVWSEXPORTED IlvApplyObjectHook : public IlvApplyHook
{
public:
    IlvApplyObjectHook(IlvApplyObject function, IlAny arg = 0)
	: IlvApplyHook(),
	_function(function),
	_arg(arg)
    {}

    virtual void	apply(IlvGraphic*);

private:
    IlvApplyObject	_function;
    IlAny		_arg;
};
#else  /* !ILVUSEAPPLYCLASS */
typedef void (* IlvApplyObject)(IlvGraphic* graphic, IlAny userArg);
IL_DEFINEFPTRTOANYCAST(IlvApplyObject);
#endif /* !ILVUSEAPPLYCLASS */
typedef IlvApplyObject IlvGraphicCallback;
IL_DEFINEFPTRTOANYCAST(IlvGraphicCallback);

typedef IlBoolean (*IlvGraphicCallbackHook)(IlvGraphicHolder*,
					    IlvGraphic*,
					    const IlSymbol*,
					    IlAny);

class IlvAbstractAttribute;
typedef IlBoolean (* IlvCheckAttributeFunction)(IlvAbstractAttribute*);

// --------------------------------------------------------------------------
// IlvGraphic class
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGraphic
    : public IlvValueInterface,
      public IlvBidiInterface
{
public:
    virtual ~IlvGraphic();

    virtual void	apply(IlvApplyObject function, IlAny arg);
    virtual void	applyReferences(IlvApplyObject function, IlAny arg);

    // User Properties
    virtual IlBoolean	zoomable() const;

    // Graphic properties
    virtual IlvDisplay*	getDisplay() const;
    virtual void	setBackground(IlvColor* background);
    virtual void	setForeground(IlvColor* foreground);
    virtual void	setFont(IlvFont* font);
    virtual void	setColorPattern(IlvColorPattern* pattern);
    virtual void	setGradientPattern(IlvGradientPattern* pattern);
    virtual void	setPattern(IlvPattern* pattern);
    virtual void	setOverwrite(IlBoolean over);
    virtual void	setMode(IlvDrawMode mode);
    virtual void	setFillStyle(IlvFillStyle style);
    virtual void	setLineStyle(IlvLineStyle* style);
    virtual void	setLineWidth(IlUShort width);
    virtual void	setPlaneMask(unsigned int);
    virtual void	setArcMode(IlvArcMode mode);
    virtual void	setFillRule(IlvFillRule rule);
    virtual void	setAlpha(IlvIntensity alpha);
    virtual void	setAntialiasingMode(IlvAntialiasingMode mode);
    virtual void	setPalette(IlvPalette* palette);
    virtual void	invert(IlBoolean temp = IlFalse);
    virtual IlUShort	getLineWidth() const;
    virtual IlvIntensity getAlpha() const;
    virtual
    IlvAntialiasingMode	getAntialiasingMode() const;

    // Geometric properties
    virtual void	getPreferredSize(IlvDim& w, IlvDim& h) const;
    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const = 0;
    virtual void	drawPalette(const IlvPalette*,
				    IlvPort*,
				    const IlvTransformer* = 0,
				    const IlvRegion* = 0) const;
    virtual IlBoolean	contains(const IlvPoint&	p,
				 const IlvPoint&	tp,
				 const IlvTransformer*	t = 0) const;
    inline IlBoolean	contains(const IlvPoint& p) const
	{ return contains(p, p); }
    virtual IlBoolean	intersects(const IlvRegion&		r,
				   const IlvTransformer*	t = 0) const;
    IlBoolean		intersects(const IlvRect&		r,
				   const IlvRect&		tr,
				   const IlvTransformer*	t = 0) const;
    inline IlBoolean	intersects(const IlvRect& r) const
	{ return intersects(r, r); }
    virtual IlBoolean	inside(const IlvRegion&		r,
			       const IlvTransformer*	t = 0) const;
    IlBoolean		inside(const IlvRect&        r,
			       const IlvRect&        tr,
			       const IlvTransformer* t = 0) const;
    inline IlBoolean	inside(const IlvRect& r) const
	{ return inside(r, r); }
    virtual void	boundingBox(IlvRect&		  bbox,
				    const IlvTransformer* t = 0) const = 0;
    inline IlvRect	bbox(const IlvTransformer* t = 0) const
	{
	    IlvRect r;
	    boundingBox(r, t);
	    return r;
	}
    inline IlvPos	x() const
	{
	    IlvRect b;
	    boundingBox(b);
	    return b.x();
	}
    inline void		x(IlvPos x)
	{
	    IlvRect b;
	    boundingBox(b);
	    move(x, b.y());
	}
    inline IlvPos	y() const
	{
	    IlvRect b;
	    boundingBox(b);
	    return b.y();
	}
    inline void		y(IlvPos y)
	{
	    IlvRect b;
	    boundingBox(b);
	    move(b.x(), y);
	}
    inline IlvDim	w() const
	{
	    IlvRect b;
	    boundingBox(b);
	    return b.w();
	}
    inline void		w(IlvDim w)
	{
	    IlvRect b;
	    boundingBox(b);
	    resize(w, b.h());
	}
    inline IlvDim	h() const
	{
	    IlvRect b; boundingBox(b);
	    return b.h();
	}
    inline void		h(IlvDim h)
	{
	    IlvRect b;
	    boundingBox(b);
	    resize(b.w(), h);
	}
    inline void		draw(IlvPort*			dst,
			     const IlvTransformer*	t,
			     const IlvRect*		clip) const
	{
	    if (clip) {
		IlvRegion region(*clip);
		draw(dst, t, &region);
	    }
	    else {
		draw(dst, t);
	    }
	}
    virtual void	move(IlvPos x, IlvPos y);
    inline void		move(const IlvPoint& p)
	{ move(p.x(), p.y()); }
    void		moveResize(const IlvRect& size);
    virtual void	translate(IlvPos dx, IlvPos dy);
    virtual void	applyTransform(const IlvTransformer* t)=0;
    virtual void	rotate(const IlvPoint& center, IlFloat angle);
    virtual void	scale(IlFloat zoomX, IlFloat zoomY);
    virtual void	resize(IlvDim newW, IlvDim newH);
    virtual void	symmetry(IlvDirection axis);
    virtual void	applyResources(const char* storageName,
				       const char* storageClassName,
				       const char* objectName,
				       const char* objectClassName,
				       IlvDisplay* display = 0);
    virtual IlvGraphic*	copy() const = 0;
    virtual void	write(IlvOutputFile& output) const = 0;
    virtual void	print(ILVSTDPREF ostream&, int = 0) const;
    void		bufferedDraw(IlvPort*,
				     const IlvTransformer* = 0,
				     const IlvRegion*      = 0,
				     IlvBitmap*            = 0) const;

    // Holder management
    inline IlvObjectProperty*	getObjectProperty() const
	{ return _objProp; }
    IlvObjectProperty*	setObjectProperty(IlvObjectProperty*);
    virtual
    IlvGraphicHolder*	getHolder() const;
    virtual void	setHolder(IlvGraphicHolder*);

    // Specific graphic methods, using its holder
    virtual void	reDraw() const;

    // Interfaces
    DeclareRootInterface(Shape);
    //virtual IlvShapeInterface* getShapeInterface() const;
    //DeclareShapeInterface();

    DeclareRootInterface(Selection);

    // Generic accessors
    DeclareGraphicAccessors();
    virtual void	getAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&) const;
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    virtual IlBoolean	beforeChangeValues(const IlvValue* = 0,
					   IlUShort = 0);
    virtual void	afterChangeValues(const IlvValue* = 0,
					  IlUShort = 0);

    static IlSymbol*	_xValue;
    static IlSymbol*	_yValue;
    static IlSymbol*	_widthValue;
    static IlSymbol*	_heightValue;
    static IlSymbol*	_foregroundValue;
    static IlSymbol*	_backgroundValue;
    static IlSymbol*	_fontValue;
    static IlSymbol*	_patternValue;
    static IlSymbol*	_colorPatternValue;
    static IlSymbol*	_gradientPatternValue;
    static IlSymbol*	_lineStyleValue;
    static IlSymbol*	_fillStyleValue;
    static IlSymbol*	_fillRuleValue;
    static IlSymbol*	_lineWidthValue;
    static IlSymbol*	_arcModeValue;
    static IlSymbol*	_alphaValue;
    static IlSymbol*	_antialiasingModeValue;
    static IlSymbol*	_sensitiveValue;
    static IlSymbol*	_containerValue;
    static IlSymbol*	_managerValue;
    static IlSymbol*	_visibleValue;
    static IlSymbol*	_interactorValue;
    static IlSymbol*	_moveMethod;
    static IlSymbol*	_reshapeMethod;
    static IlSymbol*	_translateMethod;
    static IlSymbol*	_boundingBoxMethod;
    static IlSymbol*	_containsMethod;
    static IlSymbol*	_intersectsMethod;
    static IlSymbol*	_insideMethod;
    static IlSymbol*	_setCallbackMethod;
    static IlSymbol*	_copyMethod;
    static IlSymbol*    _getChildCountValue;
    static IlSymbol*    _getChildByNameMethod;
    static IlSymbol*    _getChildAtMethod;
    static IlSymbol*    _getChildIndexMethod;
    static IlSymbol*    _getPropertyMethod;
    static IlSymbol*    _removePropertyMethod;
    static IlSymbol*    _setPropertyMethod;

    // Gadget-oriented properties
    virtual IlBoolean	needsInputContext() const;
    virtual void	setNeedsInputContext(IlBoolean val);
    virtual const char*	getDefaultInteractor() const;
    inline IlAny	getClientData() const
	{ return getProperty(ClientDataSymbol()); }
    inline void		setClientData(IlAny clientData)
	{ setProperty(ClientDataSymbol(), clientData); }
    inline const char*	getName() const
	{ return (const char*)getProperty(NameSymbol()); }
    virtual void	setName(const char* name);
    inline IlSymbol*	getNextFocusGraphic() const
	{
	    return IL_REINTERPRETCAST(IlSymbol*,
				      getProperty(NextFocusSymbol()));
	}
    inline void		setNextFocusGraphic(IlSymbol* name)
	{ setProperty(NextFocusSymbol(), IL_REINTERPRETCAST(IlAny, name)); }
    inline IlSymbol*	getPreviousFocusGraphic() const
	{
	    return IL_REINTERPRETCAST(IlSymbol*,
				      getProperty(PrevFocusSymbol()));
	}
    inline void		setPreviousFocusGraphic(IlSymbol* name)
	{ setProperty(PrevFocusSymbol(), (IlAny)name); }
    void		setLastFocusGraphic();
    void		setFirstFocusGraphic();
    IlBoolean		isLastFocusGraphic() const;
    IlBoolean		isFirstFocusGraphic() const;
    inline IlBoolean	isSensitive() const
	{ return !hasProperty(SensitiveSymbol()); }
    virtual void	setSensitive(IlBoolean value);
    IlBoolean		isVisible() const;
    virtual void	setVisible(IlBoolean);
    inline IlBoolean	isHighlighting() const
	{ return hasProperty(HighlightSymbol()); }
    virtual void	setHighlight(IlBoolean);
    inline IlBoolean	hasFocus() const
	{ return hasProperty(FocusSymbol()); }
    void		setFocus(IlBoolean);
    virtual IlBoolean	handleAccelerator(IlvEvent&) const;
    virtual IlBoolean	allowToolTip() const;

    virtual
    IlvGraphic* const*	getChildren(IlUInt& count) const;

    virtual IlUInt	getChildCount() const;

    virtual IlvGraphic* getChildAt(IlUInt index) const;

    virtual IlvGraphic* getChildByName(const char* name) const;

    virtual IlInt	getChildIndex(const IlvGraphic* object) const;

    // Tags management
    void		addTag(const IlSymbol* tag);
    void		removeTag(const IlSymbol* tag);
    IlBoolean		hasTag(const IlSymbol* tag) const;
    const IlSymbol* const*	getTags(IlUInt& count) const;

    // Interactors
    IlvInteractor*	getInteractor() const;

    IlBoolean		setInteractor(IlvInteractor* inter);

    IlBoolean		setInteractor(const char* name);

    inline void		removeInteractor()
	{ setInteractor((IlvInteractor*)0); }

    // Callbacks management
    inline IlAList*	getCallbacks() const
	{
	    return IL_REINTERPRETCAST(IlAList*,
				      getProperty(CallbackListSymbol()));
	}
    IlList*		getCallbacks(const IlSymbol*) const;
    virtual void	callCallbacks(const IlSymbol* callbackType);
    static void AddToCallbackTypeList(IlUInt& count,
				      const char* const**	names,
				      const IlSymbol* const**	types,
				      const char*		newName,
				      const IlSymbol*		newType);
    virtual IlUInt getCallbackTypes(const char* const**		names,
				    const IlSymbol* const**	types) const;

    // Main Callback functions
    void		addCallback(const IlSymbol*,
				    IlvGraphicCallbackStruct*);
    void		removeCallback(const IlSymbol*,
				       IlvGraphicCallbackStruct*);
    IlvGraphicCallbackStruct*
			getCallback(const IlSymbol*,
				    const IlvGraphicCallbackStruct&) const;
    IlvGraphicCallback	getCallback(const IlSymbol* callbackType) const;
    IlSymbol*		getCallbackName(const IlSymbol* callbackType) const;
    void		setCallback(const IlSymbol*	callbackType,
				    IlvGraphicCallback	callback);
    void		setCallback(const IlSymbol* callbackType,
				    const IlSymbol* callbackName,
				    const IlSymbol* script = 0);
    void		setCallback(const IlSymbol*	callbackType,
				    IlvGraphicCallback	callbackName,
				    IlAny		data);
    void		setCallback(const IlSymbol*,
				    const IlSymbol*,
				    IlAny,
				    const IlSymbol* = 0);
    void		setCallback(const IlSymbol*,
				    const IlSymbol*,
				    const IlvValue&,
				    const IlSymbol* = 0);
    void		setCallback(const IlSymbol*,
				    const IlSymbol*,
				    const IlvValue&,
				    IlAny,
				    const IlSymbol* = 0);
    void		addCallback(const IlSymbol*    callbackType,
				    IlvGraphicCallback callback);
    void		addCallback(const IlSymbol* callbackType,
				    const IlSymbol* callbackName,
				    const IlSymbol* script = 0);
    void		addCallback(const IlSymbol*	callbackType,
				    IlvGraphicCallback	callbackName,
				    IlAny		data);
    void		addCallback(const IlSymbol*,
				    const IlSymbol*,
				    IlAny,
				    const IlSymbol* = 0);
    void		addCallback(const IlSymbol*,
				    IlvGraphicCallback,
				    const IlvValue&);
    void		addCallback(const IlSymbol*,
				    const IlSymbol*,
				    const IlvValue&,
				    const IlSymbol* = 0);
    void		addCallback(const IlSymbol*,
				    IlvGraphicCallback,
				    const IlvValue&,
				    IlAny);
    void		addCallback(const IlSymbol*,
				    const IlSymbol*,
				    const IlvValue&,
				    IlAny,
				    const IlSymbol* = 0);
    const IlvValue*	getCallbackValue(const IlSymbol*,
					 const IlSymbol*) const;
    const IlvValue*	getCallbackValue(const IlSymbol*,
					 IlvGraphicCallback) const;
    void		setCallbackData(const IlSymbol*		callbackType,
					IlvGraphicCallback	callback,
					IlAny			data);
    void		setCallbackData(const IlSymbol*	callbackType,
					const IlSymbol*	callbackName,
					IlAny		data);
    void		setCallbackLanguage(const IlSymbol*,
					    const IlSymbol*,
					    const IlSymbol*);
    const IlSymbol*	getCallbackLanguage(const IlSymbol*,
					    const IlSymbol*) const;
    void		removeCallback(const IlSymbol*		callbackType,
				       IlvGraphicCallback	callback);
    void		removeCallback(const IlSymbol* callbackType,
				       const IlSymbol* callbackName);
    IlBoolean		hasCallback(const IlSymbol*	callbackType,
				    IlvGraphicCallback	callback) const;
    IlBoolean		hasCallback(const IlSymbol* callbackType,
				    const IlSymbol* callbackName) const;
    IlAny		getCallbackData(const IlSymbol*    callbackType,
					IlvGraphicCallback callback) const;
    IlAny		getCallbackData(const IlSymbol* callbackType,
					const IlSymbol* callbackName) const;
    IlBoolean		hasCallbackData(const IlSymbol*    callbackType,
					IlvGraphicCallback callback) const;
    IlBoolean		hasCallbackData(const IlSymbol* callbackType,
					const IlSymbol* callbackName) const;

    inline IlvGraphicCallback	getCallback() const
	{ return getCallback(CallbackSymbol()); }
    inline void		addCallback(IlvGraphicCallbackStruct* callback)
	{ addCallback(CallbackSymbol(), callback); }
    inline void		removeCallback(IlvGraphicCallbackStruct* callback)
	{ removeCallback(CallbackSymbol(), callback); }
    inline void		setCallback(IlvGraphicCallback callback)
	{ setCallback(CallbackSymbol(), callback); }
    inline void		addCallback(IlvGraphicCallback callback)
	{ addCallback(CallbackSymbol(), callback); }
    inline void		removeCallback(IlvGraphicCallback callback)
	{ removeCallback(CallbackSymbol(), callback); }

    inline void		setCallback(IlvGraphicCallback callback, IlAny data)
	{ setCallback(CallbackSymbol(), callback, data); }
    inline void		addCallback(IlvGraphicCallback callback, IlAny data)
	{ addCallback(CallbackSymbol(), callback, data); }
    inline void		setCallback(const IlSymbol* callbackName)
	{ setCallback(CallbackSymbol(), callbackName); }
    inline void		setCallback(const IlSymbol* cbName, IlAny data)
	{ setCallback(CallbackSymbol(), cbName, data); }
    inline void		setCallbackName(const IlSymbol* callbackName)
	{ setCallback(CallbackSymbol(), callbackName); }
    inline IlSymbol*	getCallbackName() const
	{ return getCallbackName(CallbackSymbol()); }
    inline IlvGraphicCallback	getSecondaryCallback() const
	{ return getCallback(SCallbackSymbol()); }
    inline void		setSecondaryCallback(IlvGraphicCallback callback)
	{ setCallback(SCallbackSymbol(), callback); }
    inline void		setSecondaryCallback(const IlSymbol* callbackName)
	{ setCallback(SCallbackSymbol(), callbackName); }
    inline void		setSecondaryCallbackName(const IlSymbol* cbName)
	{ setCallback(SCallbackSymbol(), cbName); }
    inline IlSymbol*	getSecondaryCallbackName() const
	{ return getCallbackName(SCallbackSymbol()); }
    IlBoolean		hasPersistentCallbacks() const;
    void		readCallbacks(IlvInputFile&);
    void		writeCallbacks(IlvOutputFile&) const;

    // Protection against deletion
    IlAny		startCheckingDeletion(IlBoolean&);
    void		stopCheckingDeletion(IlAny);

    // SmartSet connection
    inline IlBoolean	isInSmartSet() const
	{ return hasProperty(SmartSetSymbol()); }
    inline IlvSmartSet*	getSmartSet() const
	{
	    return IL_REINTERPRETCAST(IlvSmartSet*,
				      getProperty(SmartSetSymbol()));
	}

    // Attributes
    IlBoolean		applyAttribute(const char*	attributeClassName,
				       IlInt		value,
				       IlAny		checkData = 0) const;
    IlBoolean		applyAttribute(const char*	attributeClassName,
				       IlFloat		value,
				       IlAny		checkData = 0) const;
    IlBoolean		applyAttribute(const char*	attributeClassName,
				       const char*	value,
				       IlAny		checkData = 0) const;

    //keyboard focus
    virtual IlBoolean	classFocusable() const;
    IlBoolean		isFocusable() const;
    void		setFocusable(IlBoolean value);

    // Others...
    inline static IlBoolean	IsZoomAllowed()
	{ return _allowZoom; }
    inline static void		AllowZoom(IlBoolean az)
	{ _allowZoom = az; }

    inline static IlSymbol*	NameSymbol()
	{ return _nameSymbol; }
    inline static IlSymbol*	SensitiveSymbol()
	{ return _sensitiveSymbol; }
    inline static IlSymbol*	HighlightSymbol()
	{ return _highlightSymbol; }
    inline static IlSymbol*	CallbackListSymbol()
	{ return _callbackListSymbol; }
    inline static IlSymbol*	CallbackSymbol()
	{ return _callbackSymbol; }
    inline static IlSymbol*	SCallbackSymbol()
	{ return _sCallbackSymbol; }
    inline static IlSymbol*	DeleteCallbackSymbol()
	{ return _deleteCallbackSymbol; }
    inline static IlSymbol*	ClientDataSymbol()
	{ return _clientDataSymbol; }
    inline static IlSymbol*	FocusSymbol()
	{ return _focusSymbol; }
    inline static IlSymbol*	NextFocusSymbol()
	{ return _nextFocusSymbol; }
    inline static IlSymbol*	PrevFocusSymbol()
	{ return _prevFocusSymbol; }
    inline static IlSymbol*	TagsSymbol()
	{ return _tagsSymbol; }
    inline static IlSymbol*	AttributesSymbol()
	{ return _attributesSymbol; }
    inline static IlSymbol*	SmartSetSymbol()
	{ return _smartSetSymbol; }
    inline static IlSymbol*	NamedPropSymbol()
	{ return _namedPropSymbol; }
    inline static IlSymbol*	FocusPropSymbol()
	{ return _focusablePropSymbol; }

    inline static const IlvValue*	GetCurrentCallbackValue()
	{ return _currentCallbackValue; }
    inline static const IlSymbol*	GetCurrentCallbackType()
	{ return _currentCallbackType; }
    inline static const IlSymbol*	GetCurrentCallbackName()
	{ return _currentCallbackName; }
    inline static IlvGraphicHolder*	GetCurrentCallbackHolder()
	{ return _currentCallbackHolder; }
    inline static const IlSymbol*	GetCurrentCallbackLanguage()
	{ return _currentCallbackLanguage; }
    inline static void	       SetCurrentCallbackHolder(IlvGraphicHolder* hd)
	{ _currentCallbackHolder = hd; }

    const char*		getNameInSmartSet() const;
    virtual void	initialize(IlvPalette*);
    virtual void	drawFocus(IlvPort*		dst,
				  const IlvPalette*	palette,
				  const IlvTransformer*	t = 0,
				  const IlvRegion*	clip = 0) const;
    virtual void	computeFocusRegion(IlvRegion& r,
					   const IlvTransformer* t = 0) const;
    virtual void	computeHighlightRegion(IlvRegion&,
					    const IlvTransformer* = 0) const;
    void		copyProperties(const IlvGraphic&);
    void		removeProperties();

    virtual
    IlvLookFeelHandler*	getLookFeelHandler() const;
    virtual void	changeLook(const IlvLookFeelHandler*);
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);

    static IlBoolean	_allowZoom;
    static IlSymbol*	_nameSymbol;
    static IlSymbol*	_sensitiveSymbol;
    static IlSymbol*	_highlightSymbol;
    static IlSymbol*	_callbackListSymbol;
    static IlSymbol*	_callbackSymbol;
    static IlSymbol*	_sCallbackSymbol;
    static IlSymbol*	_deleteCallbackSymbol;
    static IlSymbol*	_clientDataSymbol;
    static IlSymbol*	_focusSymbol;
    static IlSymbol*	_nextFocusSymbol;
    static IlSymbol*	_prevFocusSymbol;
    static IlSymbol*	_tagsSymbol;
    static IlSymbol*	_attributesSymbol;
    static IlSymbol*	_smartSetSymbol;
    static IlSymbol*	_namedPropSymbol;
    static IlSymbol*	_focusablePropSymbol;

    static const IlvValue*	_currentCallbackValue;
    static const IlSymbol*	_currentCallbackType;
    static const IlSymbol*	_currentCallbackName;
    static IlvGraphicHolder*	_currentCallbackHolder;
    static const IlSymbol*	_currentCallbackLanguage;

    // Named callback hook
    static void		SetCallbackHook(IlvGraphicCallbackHook);
    static IlvGraphicCallbackHook	GetCallbackHook();
    static IlBoolean	CallCallbackHook(IlvGraphicHolder*,
					 IlvGraphic*,
					 const IlSymbol*,
					 IlAny);
    // Bidi interface
    virtual IlvBidiContext*	getBidiContext(IlBoolean = IlTrue) const;
    virtual IlvBidiContext*	getDefaultBidiContext() const;
    virtual IlBoolean		setBidiContext(IlvBidiContext*);

private:
    // No assignment operator
    IlvGraphic& operator=(const IlvGraphic&);
    IlvObjectProperty*			_objProp;
    static IlvGraphicCallbackHook	_CallbackHook;

protected:
    IlvGraphic() : _objProp(0) {}
    IlvGraphic(const IlvGraphic&);

    IlvDeclarePropertyListOwnerWithNotify(NamedPropSymbol());
    IlvDeclareLazyPropRootClassInfo();
};

// --------------------------------------------------------------------------
inline IlBoolean
IlvAllowZoom()
{
    return IlvGraphic::IsZoomAllowed();
}
inline void
IlvAllowZoom(IlBoolean az)
{
    IlvGraphic::AllowZoom(az);
}

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGradientGraphicBBoxManager
{
public:
    IlvGradientGraphicBBoxManager(IlvPalette* palette,
				  IlvGraphic* graphic,
				  const IlvTransformer* t = 0);
    IlvGradientGraphicBBoxManager(IlvPalette* palette, IlvRect bbox);

    ~IlvGradientGraphicBBoxManager();

private:
    IlvGradientPattern* _gradient;
    IlBoolean		_unSet;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvSimpleGraphic
    : public IlvGraphic
{
public:
    IlvSimpleGraphic(IlvDisplay* display, IlvPalette* palette = 0)
	: IlvGraphic()
    {
	_palette = palette ? palette : display->defaultPalette();
	_palette->lock();
    }
    virtual ~IlvSimpleGraphic();

    virtual IlvDisplay*	getDisplay() const;
    inline IlvColor*	getBackground() const
	{ return _palette->getBackground(); }
    inline IlvColor*	getForeground() const
	{ return _palette->getForeground(); }
    inline IlvFont*	getFont() const
	{ return _palette->getFont(); }
    inline IlvPattern*	getPattern() const
	{ return _palette->getPattern(); }
    inline IlvColorPattern*	getColorPattern() const
	{ return _palette->getColorPattern(); }
    inline IlvGradientPattern*	getGradientPattern() const
	{ return _palette->getGradientPattern(); }
    inline IlvLineStyle*	getLineStyle() const
	{ return _palette->getLineStyle(); }
    inline IlBoolean	getOverwrite() const
	{ return _palette->getOverwrite(); }
    inline IlvDrawMode	getMode() const
	{ return _palette->getMode(); }
    inline IlvFillStyle	getFillStyle() const
	{ return _palette->getFillStyle(); }
    IlUShort		getLineWidth() const;
    inline unsigned int	getPlaneMask() const
	{ return _palette->getPlaneMask(); }
    inline IlvArcMode	getArcMode() const
	{ return _palette->getArcMode(); }
    inline IlvFillRule	getFillRule() const
	{ return _palette->getFillRule(); }
    IlvIntensity	getAlpha() const;
    IlvAntialiasingMode getAntialiasingMode() const;

    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setPattern(IlvPattern*);
    virtual void	setColorPattern(IlvColorPattern*);
    virtual void	setGradientPattern(IlvGradientPattern*);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);
    virtual void	setFillStyle(IlvFillStyle);
    virtual void	setLineStyle(IlvLineStyle*);
    virtual void	setLineWidth(IlUShort);
    virtual void	setPlaneMask(unsigned int);
    virtual void	setArcMode(IlvArcMode);
    virtual void	setFillRule(IlvFillRule);
    virtual void	setAlpha(IlvIntensity);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);
    virtual void	invert(IlBoolean = IlFalse);
    virtual
    IlvLookFeelHandler* getLookFeelHandler() const;

    inline IlvPalette*	getPalette() const
	{ return _palette; }
    virtual void	setPalette(IlvPalette* palette);
    virtual void	drawPalette(const IlvPalette*,
				    IlvPort*,
				    const IlvTransformer* = 0,
				    const IlvRegion* = 0) const;
    virtual void	initialize(IlvPalette*);
    virtual void	applyResources(const char*,
				       const char*,
				       const char*,
				       const char*,
				       IlvDisplay* = 0);

    virtual void	setHolder(IlvGraphicHolder*);

    DeclareGraphicAccessors();
    DeclareIOConstructors(IlvSimpleGraphic);

    virtual void	registerInputMethod() const;
    virtual void	unRegisterInputMethod() const;
    virtual void	setFocusValuesInputMethod(IlUShort count,
						  const IlvImValue*
						  values) const;
    virtual void	unsetFocusInputMethod() const;
    virtual void	setValuesInputMethod(IlUShort count,
					     const IlvImValue* values) const;
    virtual int		getLookupStringInputMethod(IlvEvent&	event,
						   char*	bufferReturn,
						   int		bytesBuffer,
						   int*		statusReturn);

    // Bidi interface
    virtual
    IlvBidiContext*	getDefaultBidiContext() const;

protected:
    IlvSimpleGraphic(IlvPalette* palette)
	: IlvGraphic(),
	  _palette(palette)
    {
	_palette->lock();
    }

    IlvPalette*		_palette;

private:
    IlvSimpleGraphic() {} // Forbidden

    IlvDeclareLazyPropClassInfo();
};

// --------------------------------------------------------------------------
inline IlBoolean
IsAnIlvSimpleGraphic(const IlvGraphic* object)
{
    return object->isSubtypeOf(IlvSimpleGraphic::ClassInfo());
}

// --------------------------------------------------------------------------
typedef IlvGraphic* (* IlvTypeConstructor)(IlvInputFile&, IlvPalette*);
typedef void (* IlvGetGraphicAccessors)(const IlSymbol* const**,
					const IlvValueTypeClass* const**,
					IlUInt&);

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGraphicClassInfo
    : public IlvValuedClassInfo
{
public:
    inline IlvGraphicClassInfo*	getSuperGraphicClass() const
	{ return IL_DYNAMICCAST(IlvGraphicClassInfo*, getSuperClass()); }
    inline IlvTypeConstructor	getConstructor() const
	{ return _constructor; }
    static IlvGraphicClassInfo*	Create(const char*, IlvClassInfo**,
				       IlvTypeConstructor,
				       IlvGetAccessorsFunction = 0);
    static IlvGraphicClassInfo*	Create(const char*,
				       IlvGraphicClassInfo*);

protected:
    IlvGraphicClassInfo(const char*		className,
			IlvClassInfo**		superClass,
			IlvTypeConstructor	constructor,
			IlvGetAccessorsFunction	ga = 0)
	: IlvValuedClassInfo(className, superClass, ga),
	  _constructor(constructor)
    {}
    IlvGraphicClassInfo(const char*		className,
			IlvGraphicClassInfo*	alias)
	: IlvValuedClassInfo(className,
			     alias->_superClass,
			     alias->getGetAccessorsFunction()),
	  _constructor(alias->getConstructor())
    {}
    IlvTypeConstructor	_constructor;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGraphicNamedPropertyReader
{
public:
    IlvGraphicNamedPropertyReader(IlvInputFile&);
    void		copyTo(IlvGraphic*);
    IlvDeclarePropertyListOwner(IlvGraphic::NamedPropSymbol());
};

#define IlvRegisterClass(classname, superclass)				\
ILVDEFINECLASSINFOMEMBERS(classname,					\
    IlvGraphicClassInfo::Create(#classname,				\
				superclass::ClassPtr(),			\
				(IlvTypeConstructor)classname::read,	\
				0))

#define IlvRegisterClassAlias(classname, alias)				\
static IlvClassInfo* classname##_info =					\
    IlvGraphicClassInfo::Create(#classname,				\
				(IlvGraphicClassInfo*)alias::_classinfo)

#define IlvRegisterClassWithAccessors(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,					\
    IlvGraphicClassInfo::Create(#classname,				\
				superclass::ClassPtr(),			\
				(IlvTypeConstructor)classname::read,	\
				classname::GetAccessors))

#define IlvPostRegisterClass(classname, superclass)			\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
    IlvGraphicClassInfo::Create(#classname,				\
				superclass::ClassPtr(),			\
				(IlvTypeConstructor)classname::read,	\
				0))

#define IlvPostRegisterClassAlias(classname, alias)			\
    IlvGraphicClassInfo::Create(#classname,				\
				(IlvGraphicClassInfo*)alias::_classinfo)

#define IlvPostRegisterClassWithAccessors(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
    IlvGraphicClassInfo::Create(#classname,				\
				superclass::ClassPtr(),			\
				(IlvTypeConstructor)classname::read,	\
				classname::GetAccessors))

#define IlvPredefinedIOMembers(classname)				\
IlvGraphic* classname::copy() const					\
{ classname* o = new classname(*this); o->copyProperties(*this); return o; }\
IlvGraphic* classname::read(IlvInputFile& i, IlvPalette* pal)		\
{ return new classname(i, pal); }

#define IlvPreRegisterClass(clssname) ILVPREDEFINECLASSINFOMEMBERS(clssname)
// 2.1 compatibility:
#define IlvRegisterClass1(c, unused) IlvPreRegisterClass(c)
#define IlvRegisterClass2(c, s) IlvPostRegisterClass(c, s)

ILVVWSEXPORTEDFUNCTION(const char* const*)
IlvGetRegisteredGraphicClassNames(IlUInt&);

ILVVWSMODULEINIT(g0graphic);
#endif /* !__Ilv_Base_Graphic_H */
