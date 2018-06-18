// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/contain/contain.h
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
// Declaration of the IlvContainer class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Contain_Contain_H
#define __Ilv_Contain_Contain_H

#if !defined(__Ilv_Util_Accel_H)
#  include <ilviews/util/accel.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Util_Drview_H)
#  include <ilviews/util/drview.h>
#endif
#if !defined(__Ilv_Graphics_Objprop_H)
#  include <ilviews/graphics/objprop.h>
#endif

class ILVVWSEXPORTED IlvContainer;
class ILVVWSEXPORTED IlvContainerGraphicHolder;
class ILVVWSEXPORTED IlvViewInputFile;
class ILVVWSEXPORTED IlvSmartSet;
class ILVVWSEXPORTED IlvNavigationInteractor;
class IlvGraphicFilter;

typedef void (* IlvContainerAction)
	     (IlvContainer* container, IlvEvent& event, IlAny userArg);

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvContainerAccelerator
: public IlvAccelerator
{
public:
    IlvContainerAccelerator(IlvContainerAction	action        = 0,
                            IlvEventType	type = (IlvEventType)0,
                            IlUShort		data          = 0,
                            IlUShort		modifiers     = 0,
                            IlAny		userArg       = 0,
			    IlUShort		optModifiers  = 0)
    : IlvAccelerator(type, data, modifiers, userArg, optModifiers),
      _action(action)
    {}
    // ____________________________________________________________
    virtual void	activate(IlvContainer* cont, IlvEvent& event) const;
    inline
    IlvContainerAction	action() const { return _action; }
    inline void		setAction(IlvContainerAction action,
				  IlAny              userArg)
	{
	    _action = action;
	    _userArg = userArg;
	}

protected:
    IlvContainerAction	_action;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvViewObjectInteractor
{
public:
    IlvViewObjectInteractor(){}
    virtual ~IlvViewObjectInteractor();

    virtual IlBoolean	handleEvent(IlvGraphic*, IlvEvent&,
				    IlvContainer*, IlvTransformer*) = 0;
    virtual IlBoolean	accept(const IlvGraphic*) const;
    virtual const char* className() const;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvContainer
    : public IlvDrawingView
{
public:
    IlvContainer(IlvAbstractView* parent,
                 const IlvRect&   size,
                 IlBoolean        useacc  = IlTrue,
                 IlBoolean        visible = IlTrue);
    IlvContainer(IlvDisplay*	display,
                 IlvSystemView	parent,
                 const IlvRect&	size,
                 IlBoolean	useacc  = IlTrue,
                 IlBoolean	visible = IlTrue);
    IlvContainer(IlvDisplay*	display,
		 IlvSystemView	window,
		 IlBoolean	useacc  = IlTrue);
    IlvContainer(IlvDisplay*	display,
		 const char*	name,
		 const char*	title,
                 const IlvRect&	dims,
                 IlBoolean	useacc  = IlTrue,
                 IlBoolean	visible = IlTrue);
    IlvContainer(IlvDisplay*	display,
		 const char*	name,
		 const char*	title,
                 const IlvRect&	dims,
		 IlUInt		properties,
                 IlBoolean	useacc       = IlTrue,
                 IlBoolean	visible      = IlTrue,
		 IlvSystemView	transientFor = 0);
    virtual ~IlvContainer();

    void		initActions();
    virtual void	setBackground(IlvColor* c);
    virtual void	setBackgroundBitmap(IlvBitmap*);
    IlBoolean		setDoubleBuffering(IlBoolean value);
    IlBoolean		isDoubleBuffering() const;
    inline IlvBitmap*	getBitmap() const { return _bitmap; }
    inline IlvPalette*	getPalette() const { return _palette; }
    void		visibleBBox(IlvRect& bbox) const;
    virtual void	show();
    virtual void	hide();
    inline IlBoolean	isVisible() const
	{ return IlvView::isVisible(); }
    virtual void	fitToContents();
    inline IlvContainerGraphicHolder* getHolder() const
	{ return _holder; }
    // Backward compatibility
    inline static IlvContainer*	getContainer(const IlvGraphic* obj)
	{ return GetContainer(obj); }
    static IlvContainer*	GetContainer(const IlvGraphic* obj);


    // Managing Objects _________________________________________________
    inline IlUInt	getCardinal() const
	{ return _list.getLength(); }
    IlvGraphic*		getObject(IlUInt index) const;
    IlvGraphic*		getObject(const char* name) const;
    IlvGraphic* const*	getObjects(IlUInt& count) const;
    IlInt		getIndex(IlvGraphic* obj) const;
    virtual void	addObject(IlvGraphic* obj,
				  IlBoolean   redraw = IlFalse);
    virtual void	addObject(const char* objectName,
				  IlvGraphic* obj,
				  IlBoolean   redraw = IlFalse);
    virtual void	insertObject(IlvGraphic* obj,
				     IlBoolean   redraw = IlFalse);
    virtual void	insertObjectAt(IlvGraphic*, IlBoolean = IlFalse,
				       IlUInt = 0);
    virtual IlBoolean	removeObject(IlvGraphic* obj,
				     IlBoolean   redraw = IlFalse);
    virtual void	removeObjects(IlBoolean destroy = IlTrue,
				      IlBoolean redraw  = IlTrue);
    virtual void	swap(IlvGraphic* obj1, IlvGraphic* obj2);
    void		pop(IlvGraphic*,  IlBoolean = IlTrue);
    void		push(IlvGraphic*, IlBoolean = IlTrue);
    virtual IlvGraphic*	replace(IlvGraphic* oldObject,
				IlvGraphic* newObject,
				IlBoolean   redraw = IlFalse);
    IlvSmartSet*	getSmartSet(const char* name) const;
    virtual IlBoolean	addSmartSet(IlvSmartSet* set,
				    IlBoolean redraw = IlTrue);
    virtual IlBoolean	removeSmartSet(IlvSmartSet* set);
    const char*		getObjectName(const IlvGraphic* obj) const;
    virtual void         setObjectName(IlvGraphic* obj, const char* name);
    IlvViewObjectInteractor* getObjectInteractor(const IlvGraphic*) const;
    IlBoolean		setObjectInteractor(IlvGraphic*,
					    IlvViewObjectInteractor*);
    IlBoolean		isVisible(const IlvGraphic* obj) const;
    virtual void	setVisible(IlvGraphic* obj,
				   IlBoolean   visible,
				   IlBoolean   redraw = IlFalse);

    // Drawing _________________________________________________________
    void		reDrawObj(IlvGraphic* obj);
    virtual void	draw(const IlvRegion* clip = 0);
    virtual void	draw(IlvPort*              dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion*      clip = 0);
    virtual void	reDraw(const IlvRegion* clip = 0);
    inline void		reDraw(const IlvRect* rect)
	{
	    IlvRegion region(*rect);
	    reDraw(&region);
	}
    inline void		draw(const IlvRect* rect)
	{
	    IlvRegion region(*rect);
	    draw(&region);
	}
    void		bufferedDraw(const IlvRect& rect);
    void		bufferedDraw(const IlvRegion& region);
    void		bufferedDraw(const IlvGraphic* object);
    virtual void	drawFocus(IlvPort*,
				  const IlvTransformer* = 0,
				  const IlvRegion*      = 0);
    virtual void	beforeDraw(IlvPort*              dst,
				   const IlvTransformer* t    = 0,
				   const IlvRegion*	 clip = 0);
    virtual void	afterDraw(IlvPort*              dst,
				  const IlvTransformer* t    = 0,
				  const IlvRegion*      clip = 0);

    // Optimizing drawing tasks
    // obsolete
    void		initReDraw();
    void		invalidateRegion(const IlvGraphic* object);
    void		invalidateRegion(const IlvRect& rect);
    void		invalidateRegion(const IlvRegion& rect);

    void		invalidateRegion(const IlvRegionUpdater& updater,
					 const IlvGraphic*       graphic =0);

    // obsolete
    void		reDrawView(IlBoolean erase    = IlTrue,
				   IlBoolean buffered = IlFalse);
    void		abortReDraw();
    virtual void	flushRedraw();
    void		disableRedrawTask();
    // obsolete
    inline void		initRedraw()  { initReDraw();  }
    inline void		abortRedraw() { abortReDraw(); }
    inline IlBoolean	isInvalidating() const
	{ return (_invalidating || _redrawTask); }
    inline IlvRegion*	updateRegion() const
	{ return (IlvRegion*)&_updateRegion; }

    // Not documented
    virtual void	invalidateObject(const IlvGraphic*);
    void		updateRegionModified();

    // IO _________________________________________________________
    virtual IlBoolean	readFile(const char* filename);
    virtual IlBoolean	read(ILVSTDPREF istream&);
    virtual
    IlvViewInputFile*	createInputFile(ILVSTDPREF istream&);

    // Transformer _________________________________________________________
    inline
    IlvTransformer*	getTransformer() const { return _transformer; }
    virtual void	setTransformer(const IlvTransformer&);
    void		setTransformer(const IlvTransformer* t = 0);
    void		addTransformer(const IlvTransformer& t);
    void		translateView(IlvPos    dx,
				      IlvPos    dy,
				      IlBoolean redraw = IlTrue);
    void		zoomView(const IlvPoint& center,
				 IlFloat         scaleX,
				 IlFloat         scaleY = 0.0,
				 IlBoolean       redraw = IlTrue);
    virtual void	fitTransformerToContents(IlBoolean redraw = IlTrue);

    // Accelerators _______________________________________________
    void		addAccelerator(IlvContainerAccelerator* accelerator);
    void		addAccelerator(IlvContainerAction action,
				       IlvEventType type,
				       IlUShort     data         = 0,
				       IlUShort     modifiers    = 0,
				       IlAny        userArg      = 0,
				       IlUShort     optModifiers = 0);
    void		removeAccelerator(IlvContainerAccelerator* acc);
    void		removeAccelerator(IlvEventType type,
					  IlUShort     buttonOrKey = 0,
					  IlUShort     modifiers = 0);
    IlvContainerAccelerator*	getAccelerator(IlvEventType type,
					       IlUShort button = 0,
					       IlUShort modifiers = 0) const;
    IlBoolean		getAccelerator(IlvContainerAction* action,
				       IlAny*       userArg,
				       IlvEventType type,
				       IlUShort     buttonOrKey = 0,
				       IlUShort     modifiers   = 0) const;

    // ApplyTo functions _____________________________________________
    void		applyToObjects(IlvApplyObject func,
				       IlAny          arg,
				       IlBoolean      redraw = IlFalse);
    virtual void	applyToObject(IlvGraphic*    obj,
				      IlvApplyObject func,
				      IlAny          arg,
				      IlBoolean      reDraw = IlFalse);
    void		applyToTaggedObjects(const IlSymbol* tag,
					     IlvApplyObject  func,
					     IlAny           arg,
					     IlBoolean     reDraw = IlFalse);
    IlvGraphic* const*	getTaggedObjects(const IlSymbol* tag,
					 IlUInt&         count) const;
    void		removeTaggedObjects(const IlSymbol* tag,
					    IlBoolean       destroy = IlTrue,
					    IlBoolean      reDraw  = IlTrue);

    // Callbacks management _______________________________________
    const IlAList*	getCallbackNames() const;
    IlvGraphicCallback	getCallback(const IlSymbol* callbackName) const;
    void		registerCallback(const char*        callbackName,
					 IlvGraphicCallback callback);
    void		unregisterCallback(const char* callbackName);
    inline void		removeCallback(const char* callbackName) // 2.1
	{ unregisterCallback(callbackName); }
    virtual void	callCallbacks(const IlSymbol*, IlvGraphic*);
    inline void		callCallback(IlvGraphic* object)
	{ callCallbacks(IlvGraphic::CallbackSymbol(), object); }

    // Events _________________________________________________________
    virtual void	handleInput(IlvEvent&);
    virtual IlBoolean	shortCut(IlvEvent& event);
    virtual IlBoolean	dispatchToObjects(IlvEvent& event);
    virtual void	handleExpose(IlvEvent&);
    virtual void	handleResize(IlvRect&);
    IlBoolean		handleEvent(IlvGraphic*, IlvEvent&);
    IlBoolean		gadgetShortCut(IlvEvent&);
    inline IlvEvent*    getLastEvent() const { return _lastEvent; }
    virtual IlvGraphic*	getAcceleratorGadget(IlvEvent&) const;
    virtual IlAny	internalHandleAccelerator(IlvEvent&) const;

    // Focus _________________________________________________________
    virtual void	focusIn(IlvEvent&);
    virtual void	focusOut(IlvEvent&);
    virtual IlBoolean	isFocusClient(const IlvGraphic*) const;
    virtual IlBoolean	isFocusTabClient(const IlvGraphic*) const;
    virtual IlvGraphic*	getFocus() const;
    virtual void	setFocus(IlvGraphic* = 0, IlBoolean = IlTrue);
    virtual IlBoolean	isFocusAllowed() const;
    virtual IlBoolean	allowFocus(IlBoolean);
    virtual void	moveFocusAfter(IlBoolean = IlTrue);
    virtual void	moveFocusBefore(IlBoolean = IlTrue);
    virtual void	moveFocusFirst();
    virtual void	moveFocusLast();

    // Grab _________________________________________________________
    virtual IlvGraphic*	getGrab() const;
    virtual void	setGrab(IlvGraphic*);
    virtual void	removeGrab();

    // Selection _________________________________________________________
    virtual void	selectionRequest(const IlvGraphic*);
    virtual void	cleanSelection(const IlvGraphic*);

    inline IlvGraphic*	getInteractiveObject() const
	{ return _interactiveObject; }
    inline void		setInteractiveObject(IlvGraphic* obj)
	{ _interactiveObject = obj; }
    inline IlvNavigationInteractor* getNavigationInteractor() const
	{ return _navInter; }

    // Hit Testing _______________________________________________________
    IlvGraphic*		lastContains(const IlvPoint&) const;
    inline IlvGraphic*	contains(const IlvPoint& p) const
	{ return lastContains(p); }
    IlvGraphic*		filteredLastContains(const IlvPoint&,
					     const IlvGraphicFilter&) const;

    // Look, Language and Bidi callbacks _________________________________
    virtual void	changeLook();
    virtual void	changeLanguage();
    virtual void	changeLayoutAttributes(IlAny, IlAny);

    // Bidi interface ____________________________________________________
    virtual IlvBidiContext*	getBidiContext(IlBoolean = IlTrue) const;
    virtual IlvBidiContext*	getDefaultBidiContext() const;
    virtual IlBoolean		setBidiContext(IlvBidiContext*);
    virtual IlBoolean		changeOrientation();

protected:
    IlvContainerGraphicHolder*	_holder;
    IlList			_list;
    IlUInt			_invalidating;
    IlAny 			_redrawTask;
    IlvRegion			_updateRegion;
    IlvTransformer*		_transformer;
    IlvBitmap*			_bitmap;
    IlvPalette*			_palette;
    IlList			_accelerators;
    IlvGraphic*			_interactiveObject;
    IlList			_smartSets;
    IlBoolean			_overwritePathInRead;
    IlvEvent*			_lastEvent;
    IlBoolean			_navInterInitialized;
    IlvNavigationInteractor*	_navInter;

    static IlBoolean 	RedrawTask(IlAny);
    virtual void	cleanObj(IlvGraphic*);
    void		cleanObjs();
    void		freeBitmap();
    void		makeBitmap();
    void		makePalette();
    virtual void	drawAll(IlvPort*,
				const IlvRegion&,
				const IlvRegion* = 0);
    void		draw(const IlvRegion&,
			     const IlvRegion* = 0);
    virtual void	eraseRegion(const IlvRegion& region);
    IlvNavigationInteractor* createNavigationInteractor(IlBoolean c);

    DeclareLazyViewProperties();

private:
    IlBoolean		_cleanObjDone;
    IlvValueInterface*	_onShow;
    IlvValueInterface*	_onHide;
    IlvValueInterface*	_onDestroy;

    void		init(IlBoolean useacc);

public:
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    inline
    static IlSymbol*	interactorProperty() { return _interactorProperty; }

    // --- Value accessors ---
    DeclareViewAccessors();

    static  IlSymbol*	_doubleBufferingValue;
    static  IlSymbol*	_cardinalValue;
    static  IlSymbol*	_getObjectMethod;
    static  IlSymbol*	_getObjectAtMethod;
    static  IlSymbol*	_getIndexMethod;
    static  IlSymbol*	_addObjectMethod;
    static  IlSymbol*	_insertObjectMethod;
    static  IlSymbol*	_removeObjectMethod;
    static  IlSymbol*	_removeObjectsMethod;
    static  IlSymbol*	_containsMethod;
    static  IlSymbol*	_swapMethod;
    static  IlSymbol*	_translateViewMethod;
    static  IlSymbol*	_zoomViewMethod;
    static  IlSymbol*	_fitToContentsMethod;
    static  IlSymbol*	_fitMethod;
    static  IlSymbol*	_redrawMethod;
    static  IlSymbol*	_readFileMethod;
    static  IlSymbol*	_onShowValue;
    static  IlSymbol*	_onHideValue;
    static  IlSymbol*	_onDestroyValue;
    static  IlSymbol*	_interactorProperty;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvContainerObjectProperty
    : public IlvObjectProperty
{
public:
    IlvContainerObjectProperty(IlvContainer* container)
        :  IlvObjectProperty(IL_REINTERPRETCAST(IlvGraphicHolder*,
						container->getHolder())),
	   _container(container)
    {}
    IL_MLK_DECL();

    inline IlvContainer* getContainer() const { return _container; }

protected:
    IlvContainer*	_container;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvViewInputFile
    : public IlvInputFile
{
public:
    IlvViewInputFile(ILVSTDPREF istream& stream, IlvContainer* container = 0);

    inline IlvContainer* getContainer() const { return _container; }
    static IlvGraphic*	ReadObject(IlvDisplay* display,
				   const char* filename,
				   const char* objectName = 0);
    virtual IlBoolean	readAll(IlvContainer*);
    virtual IlvGraphic*	readObject();
    virtual IlBoolean	parseBlock(const char*);

protected:
    IlvContainer*	_container;
    void		readProperties(IlvContainer*, IlvGraphic*);
};

ILVVWSEXPORTEDFUNCTION(IlvViewObjectInteractor*)
IlvGetViewInteractor(const char*, IlBoolean = IlTrue);

// Define some useful macros
#define ILVSETINTERACTOR(container, graphic, name) \
container->setObjectInteractor(graphic, IlvGetViewInteractor(name))

#define ILVOBJECT(container, name, type) (type*)container->getObject(name)
#define ILVCONTAINER(graphic) IlvContainer::getContainer(graphic)
#define ILVGETOBJECT(name, type) (type*)this->getObject(name)

ILVVWSMODULEINIT(contain);
#endif /* !__Ilv_Contain_Contain_H */
