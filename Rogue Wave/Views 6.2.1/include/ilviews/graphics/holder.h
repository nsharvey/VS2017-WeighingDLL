// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/holder.h
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
// Declaration of the IlvGraphicHolder class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Holder_H
#define __Ilv_Base_Holder_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Util_Proplist_H)
#include <ilviews/util/proplist.h>
#endif

// --------------------------------------------------------------------------
class IlvGraphicHolder;
class IlvHGadgetInteractor;
class IlvGuideHandler;
class IlvGeometryHandler;
class IlvManager;
class IlvContainer;
class IlvScriptContext;
class IlvCommandHistory;
class IlvViewRectangle;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGraphicHolder
{
public:
    IlvGraphicHolder(IlvDisplay*);
    virtual ~IlvGraphicHolder();

    void		attach(IlvGraphic*	obj,
			       IlvDirection	dir,
			       IlInt		weightBefore = 0,
			       IlInt		objectWeight = 1,
			       IlInt		weightAfter = 0,
			       IlUInt		guide1ndx = 0,
			       IlUInt		guide2ndx = (IlUInt)-1);
    void		resetAttachments(IlvGraphic* obj, IlvDirection dir);
    void		resetAttachments(IlvGraphic*	obj,
					 IlvDirection	dir,
					 IlInt		weightBefore,
					 IlInt		objectWeight,
					 IlInt		weightAfter);
    void		removeAttachments(IlvGraphic* obj, IlvDirection dir);

    virtual IlvDisplay*	getDisplay() const = 0;
    virtual
    IlvLookFeelHandler* getLookFeelHandler() const;
    virtual void	setLookFeelHandler(IlvLookFeelHandler* lfh);
    inline
    IlvGraphicHolder*	getParent() const { return _parent; }
    inline void		setParent(IlvGraphicHolder* parent) {_parent = parent;}
    void		addChild(IlvGraphicHolder*);
    void		removeChild(IlvGraphicHolder*);
    virtual IlvPalette*	palette() const = 0;

    virtual IlBoolean	isAContainer() const = 0;
    virtual
    IlvContainer*	getContainer() const;
    virtual IlBoolean	isAComposite() const;
    virtual IlvManager*	getManager() const;
    virtual void	moveFocusAfter(IlBoolean redraw = IlTrue) = 0;
    virtual void	moveFocusBefore(IlBoolean redraw = IlTrue) = 0;
    virtual IlBoolean	allowFocus(IlBoolean flag) = 0;
    virtual IlBoolean	isFocusAllowed() const = 0;
    virtual void	removeGrab() = 0;
    virtual void	setGrab(IlvGraphic* obj) = 0;
    virtual IlBoolean	grab(IlvCursor* cursor = 0) = 0;
    virtual void	unGrab() = 0;
    virtual void	handleInput(IlvEvent& event) = 0;
    virtual
    IlvTransformer*	getTransformer() const = 0;
    virtual
    IlvCommandHistory*	getCommandHistory() const;
    virtual IlvEvent*	getLastEvent() const;

    // Callbacks management
    virtual void	enableCallbacks(IlBoolean enable = IlTrue);
    virtual IlBoolean	areCallbacksEnabled();
    inline
    const IlAList*	getCallbackNames() const { return &_callbacks; }
    void		registerCallback(const char*		callbackName,
					 IlvGraphicCallback	callback);
    void		unregisterCallback(const char* callbackName);
    IlvGraphicCallback	getCallback(const IlSymbol* callbackName) const;
    void		callCallbacks(const IlSymbol*, IlvGraphic*);
    inline void		callCallback(IlvGraphic* object)
			{
			    callCallbacks(IlvGraphic::CallbackSymbol(),object);
			}

    virtual void	reDraw() = 0;
    virtual void	reDraw(const IlvRegion* region) = 0;
    virtual void	bufferedDraw(const IlvGraphic*) = 0;
    virtual void	bufferedDraw(const IlvRect& rect) = 0;
    virtual void	bufferedDraw(const IlvRegion& region) = 0;
    virtual void	scrollArea(const IlvRect&	rect,
				   IlvPos		dx,
				   IlvPos		dy,
				   IlBoolean		redraw = IlTrue);
    virtual void	globalBBox(IlvRect& bbox) const = 0;
    IlvSystemPort*	getPort() const;
    virtual IlvView*	getView()   const = 0;
    virtual
    IlvGraphicHolder*	getViewHolder();
    virtual IlvBitmap*	getBitmap() const = 0;
    virtual void	setPropertyToGraphic(IlvGraphic*) const = 0;
    virtual
    IlvHGadgetInteractor* getHGadgetInteractor(const IlvGraphic*) const;
    virtual IlBoolean	objectHasInteractor(const IlvGraphic*) const = 0;
    virtual IlvGraphic* getFocus() const = 0;
    virtual void	setFocus(IlvGraphic* obj = 0,
				 IlBoolean redraw = IlTrue) const = 0;
    virtual void	moveFocusFirst() = 0;
    virtual void	moveFocusLast() = 0;
    virtual void	applyToObject(IlvGraphic*	obj,
				      IlvApplyObject	f,
				      IlAny		arg,
				      IlBoolean		redraw = IlTrue) = 0;
    virtual void	applyToObjects(IlvApplyObject	f,
				       IlAny		arg,
				       IlBoolean	redraw = IlTrue);
    inline
    IlvGraphicHolder*	getNextFocusHolder() const
			{
			    return _nextFocusHolder;
			}
    inline void		setNextFocusHolder(IlvGraphicHolder* holder)
			{
			    if (_nextFocusHolder != holder) {
				if (_nextFocusHolder)
				    _nextFocusHolder->_previousFocusHolder = 0;
				_nextFocusHolder = holder;
				if (holder)
				    holder->_previousFocusHolder = this;
			    }
			}
    inline
    IlvGraphicHolder*	getPreviousFocusHolder() const
			{
			    return _previousFocusHolder;
			}
    inline void		setPreviousFocusHolder(IlvGraphicHolder* holder)
			{
			    if (_previousFocusHolder != holder) {
				if (_previousFocusHolder)
				    _previousFocusHolder->_nextFocusHolder = 0;
				_previousFocusHolder = holder;
				if (holder)
				    holder->_nextFocusHolder = this;
			    }
			}
    IlvGeometryHandler* getGeometryHandler(const IlvGraphic*,
					   IlvDirection) const;
    inline
    IlvGuideHandler*	getGuideHandler(IlvDirection dir) const
			{
			    return (dir == IlvVertical)
				? _verticalGuideHandler
				: _horizontalGuideHandler;
			}
    void		applyResize(IlvRect&	newrect,
				    IlvDim	oldw,
				    IlvDim	oldh);
    void		readGuideHandlers(IlvInputFile&);
    void		writeGuideHandlers(IlvOutputFile&);
    void		resetGuideHandlers();
    void		removeFromHolder(IlvGraphic*);
    void		initializeGuideHandlers(IlvDim w, IlvDim h);
    virtual void	selectionRequest(const IlvGraphic*) = 0;
    virtual void	cleanSelection(const IlvGraphic*) = 0;
    virtual IlBoolean	setObjectName(IlvGraphic* obj, const char*) = 0;
    virtual const char* getObjectName(const IlvGraphic* obj) const = 0;
    virtual const char* getObjectInteractor(const IlvGraphic* obj) const = 0;
    virtual IlBoolean	setObjectInteractor(IlvGraphic* obj, const char*) = 0;

    virtual IlBoolean	isVisible(const IlvGraphic* obj) const = 0;
    virtual IlBoolean	isDisplayed(const IlvGraphic* obj,
				    const IlvPort* dst) const;
    virtual void	setVisible(IlvGraphic*	obj,
				   IlBoolean	visible,
				   IlBoolean	redraw) = 0;
    virtual
    IlvGraphic* const*	getObjects(IlUInt& count) const = 0;
    virtual IlvGraphic*	getObject(const char*) const = 0;
    virtual void	addObject(IlvGraphic* obj, IlBoolean redraw) = 0;
    virtual void	addObject(const char*	objectName,
				  IlvGraphic*	obj,
				  IlBoolean	redraw) = 0;
    virtual IlBoolean	removeObject(IlvGraphic* obj, IlBoolean redraw) = 0;
    virtual void	moveObject(IlvGraphic*,
				   const IlvPoint& p,
				   IlBoolean redraw) = 0;
    virtual void	translateObject(IlvGraphic*,
					IlvPos		dx,
					IlvPos		dy,
					IlBoolean	redraw) = 0;
    virtual void	reshapeObject(IlvGraphic*,
				      const IlvRect&	p,
				      IlBoolean		redraw) = 0;
    virtual void	pop(IlvGraphic*, IlBoolean redraw) = 0;
    virtual void	push(IlvGraphic*, IlBoolean redraw) = 0;
    virtual IlvGraphic* lastContains(const IlvPoint&, const IlvView*) const=0;
    void		invalidateRegion(const IlvRegion& region);
    virtual void	invalidateRegion(const IlvGraphic* obj);
    virtual void	invalidateRegion(const IlvRegionUpdater& updater,
					 const IlvGraphic*	 g = 0);
    virtual void	invalidateRegion(const IlvRect& r) = 0;
    virtual IlBoolean	isInvalidating() const = 0;
    virtual IlvRegion*	updateRegion() const;
    virtual void	flushRedraw();
    virtual void	draw(IlvRegion*);
    inline void		initRedraws() { initReDraws(); } // For compatibility
    virtual void	initReDraws() = 0;
    virtual void	reDrawViews() = 0;

    virtual IlUInt	addGuide(IlvDirection	dir,
				 IlvPos		pos,
				 IlInt		weight = 0,
				 IlInt		limit = 1);
    virtual IlBoolean	removeGuide(IlvDirection dir, IlUInt index);
    IlUInt		getGuideCardinal(IlvDirection dir) const;
    IlvPos		getGuidePosition(IlvDirection dir, IlUInt index) const;
    IlInt		getGuideSize(IlvDirection dir, IlUInt index) const;
    IlInt		getGuideWeight(IlvDirection dir, IlUInt index) const;
    IlInt		getGuideLimit(IlvDirection dir, IlUInt index) const;

    void		setFileName(const char*);
    inline const char*	getFileName() const { return _fileName; }
    void		setPathName(const char*);
    inline const char*	getPathName() const { return _pathName; }

    // Script contexts ____________________________________________
    IlvScriptContext*	makeScriptContext(const IlSymbol* languageName = 0);
    IlvScriptContext*	getScriptContext(const IlSymbol* = 0) const;
    void		setScriptContext(IlvScriptContext*);
    void		saveScriptContexts(IlvOutputFile&) const;
    inline void		compileScriptOnLoad(IlBoolean compileScriptsOnLoad)
			{
			    _compileScriptsOnLoad = compileScriptsOnLoad;
			}
    inline IlBoolean	doesCompileScriptOnLoad() const
			{
			    return _compileScriptsOnLoad;
			}
    inline void		setInDestructor() { _isInDestructor = IlTrue; }
    inline IlBoolean	isInDestructor() const { return _isInDestructor; }

    // View Property
    static IlSymbol* _holderProperty;

    inline
    static IlSymbol*	HolderProperty() { return _holderProperty; }
    static
    IlvGraphicHolder*	Get(const IlvView*);
    static void		Set(IlvView*, IlvGraphicHolder*);

    // Look, Language and Bidi callbacks.
    virtual void	changeLook();
    virtual void	changeLanguage();
    virtual void	changeLayoutAttributes(IlAny, IlAny);

    // Handling of view rectangle like objects
    void		addViewObject(IlvViewRectangle* g);
    void		removeViewObject(IlvViewRectangle* g);
    void		removeViewObjects();
    IlList*		getViewObjects() const;
    void		moveViewObjects(const IlvView*		view,
					const IlvTransformer*	newT,
					const IlvTransformer*	oldT) const;
    void		checkViewObjectsVisibility();

    // Reading files.
    virtual int		read(IL_STDPREF istream& stream);
    virtual int		read(const char* filename);

    // Properties
    static
    const IlSymbol*	NamedPropertiesSymbol();
    void		writeProperties(IlvOutputFile&) const;
    void		readProperties(IlvInputFile&);

    inline IlInt	getError() const { return _ioStatus; }
    inline void		setError(IlInt val) { _ioStatus = val; }
    inline void		addError(IlInt val) { _ioStatus |= val; }

    IlvDeclarePropertyListOwner(NamedPropertiesSymbol());

protected:
    IlBoolean		_isInDestructor;
    IlvGraphicHolder*	_parent;
    IlvGraphicHolder*	_nextFocusHolder;
    IlvGraphicHolder*	_previousFocusHolder;
    IlvGuideHandler*	_verticalGuideHandler;
    IlvGuideHandler*	_horizontalGuideHandler;
    IlAList		_callbacks;
    IlAList*		_scriptContexts;
    char*		_fileName;
    char*		_pathName;
    IlBoolean		_compileScriptsOnLoad;
    IlBoolean		_callbacksEnabled;
    IlArray		_children;
    IlInt		_ioStatus;
    IlvLookFeelHandler* _lfh;

    static IlList*	Holders;

    static void		ChangeLook(IlvDisplay*);
    static void		ChangeLanguage(IlvDisplay*);
    static void		ChangeLayoutAttributes(IlvDisplay*, IlAny, IlAny);
private:
    // No copy constructor
    IlvGraphicHolder(const IlvGraphicHolder&);
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvHGadgetInteractor
{
public:
    virtual ~IlvHGadgetInteractor();
protected:
    IlvHGadgetInteractor() {}
};

// --------------------------------------------------------------------------
// this class allows one to define graphic objects that hold other
// graphic objects. This is specially usefull for IlvTransformedGraphic.

class ILVVWSEXPORTED IlvSubGraphicHolder : public IlvGraphicHolder
{
public:
    IlvSubGraphicHolder(IlvDisplay* d, IlvGraphic* gr)
    	: IlvGraphicHolder(d),
	  _parentG(gr)
    {}
    ~IlvSubGraphicHolder() {}

    IlvDisplay*		getDisplay() const;
    IlvPalette*		palette() const;
    IlBoolean		isAContainer() const;

    void		moveFocusAfter(IlBoolean redraw = IlTrue);
    void		moveFocusBefore(IlBoolean redraw = IlTrue);
    IlBoolean		allowFocus(IlBoolean flag);
    IlBoolean		isFocusAllowed() const;
    void		removeGrab();
    void		setGrab(IlvGraphic*);
    IlBoolean		grab(IlvCursor* cursor = 0);
    void		unGrab();
    void		handleInput(IlvEvent& event) ;
    IlvCommandHistory*	getCommandHistory() const;

    void		reDraw();
    void		reDraw(const IlvRegion* region);
    void		bufferedDraw(const IlvGraphic* g);
    void		bufferedDraw(const IlvRect& rect);
    void		bufferedDraw(const IlvRegion& region);

     void		globalBBox(IlvRect& bbox)  const;
     IlvView*		getView() const;
     IlvBitmap*		getBitmap() const;

     void		setPropertyToGraphic(IlvGraphic* g) const;
     IlvHGadgetInteractor* getHGadgetInteractor(const IlvGraphic* g) const;

    IlBoolean		objectHasInteractor(const IlvGraphic* g) const;
    IlvGraphic*		getFocus() const;

    void		setFocus(IlvGraphic*	g = 0,
				 IlBoolean	b = IlTrue) const;
    void		moveFocusFirst();
    void		moveFocusLast();
    void		applyToObject(IlvGraphic*	obj,
				      IlvApplyObject	f,
				      IlAny		arg,
				      IlBoolean		redraw = IlTrue);
    void		selectionRequest(const IlvGraphic* g);
    void		cleanSelection(const IlvGraphic* g);
    IlBoolean		setObjectName(IlvGraphic* obj, const char* n);
    const char*		getObjectName(const IlvGraphic* obj) const;
    const char*		getObjectInteractor(const IlvGraphic* obj) const;
    IlBoolean		setObjectInteractor(IlvGraphic* obj, const char* n);

     IlBoolean		isVisible(const IlvGraphic* obj) const;
     void		setVisible(IlvGraphic*	obj,
				   IlBoolean	visible,
				   IlBoolean	redraw);
     IlvGraphic* const* getObjects(IlUInt& count) const;
     IlvGraphic*	getObject(const char* n) const;
     void		addObject(IlvGraphic* obj, IlBoolean redraw);
     void		addObject(const char*	objectName,
				  IlvGraphic*	obj,
				  IlBoolean	redraw);
    IlBoolean		removeObject(IlvGraphic* obj, IlBoolean redraw);
    void		moveObject(IlvGraphic*		g,
				   const IlvPoint&	p,
				   IlBoolean		redraw);
    void		translateObject(IlvGraphic*	g,
					IlvPos		dx,
					IlvPos		dy,
					IlBoolean	redraw);
    void		reshapeObject(IlvGraphic*	g,
				      const IlvRect&	p,
				      IlBoolean		redraw);
    void		pop(IlvGraphic* g, IlBoolean redraw);
    void		push(IlvGraphic* g, IlBoolean redraw);
    virtual IlvGraphic* lastContains(const IlvPoint&, const IlvView*) const;
    void		initReDraws();
    void		invalidateRegion(const IlvRect& r);
    void		invalidateRegion(const IlvRegion& region);
    void		invalidateRegion(const IlvGraphic* obj);
    void		invalidateRegion(const IlvRegionUpdater& updater,
					 const IlvGraphic*	 g = 0);
    virtual IlvRegion*	updateRegion() const;
    virtual void	flushRedraw();
    IlBoolean		isInvalidating() const;
    void		reDrawViews();

    IlvManager*		getManager() const;
    IlvContainer*	getContainer() const;
    IlvTransformer*	getTransformer() const;

    // The API extensions to manage subobjects
    IlvGraphicHolder*	getParentHolder() const ;
    virtual
    IlvTransformer*	getLocalTransformer() const;
    virtual IlUInt	getCardinal();
    virtual IlvGraphic* getChild(IlUInt);
    virtual IlBoolean	isChild(IlvGraphic*);

public:
    IlvGraphic*		_parentG;
};

ILVVWSMODULEINIT(holder);
#endif /* __Ilv_Base_Holder_H */
