// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/manager.h
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
// Declaration of the IlvManager class
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Manager_H
#define __Ilv_Manager_Manager_H

#if !defined(__Ilv_Manager_Macros_H)
#  include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Util_Proplist_H)
#  include <ilviews/util/proplist.h>
#endif
#if !defined(__Ilv_Base_View_H)
#  include <ilviews/base/view.h>
#endif
#if !defined(__Ilv_Base_Smartptr_H)
#  include <ilviews/base/smartptr.h>
#endif
#if !defined(__Ilv_Base_Command_H)
#  include <ilviews/base/command.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Graphics_Objprop_H)
#  include <ilviews/graphics/objprop.h>
#endif
#if !defined(__Ilv_Graphics_Select_H)
#  include <ilviews/graphics/select.h>
#endif
#if !defined(__Ilv_Manager_Indexgr_H)
#  include <ilviews/manager/indexgr.h>
#endif
#if !defined(__Ilv_Manager_Mgrview_H)
#  include <ilviews/manager/mgrview.h>
#endif
#if !defined(__Ilv_Manager_Hook_H)
#  include <ilviews/manager/hook.h>
#endif
#if !defined(__Ilv_Manager_Event_H)
#  include <ilviews/manager/event.h>
#endif
#if !defined(__Ilv_Manager_Applylst_H)
#  include <ilviews/manager/applylst.h>
#endif

class IlvManagerInputFile;
class IlvManagerOutputFile;
class IlvDrawSelection;
class IlvSmartSet;
class IlvGraphicFilter;
class IlvEditableFilter;
// --------------------------------------------------------------------------
typedef void (*IlvApplyFunction)(IlAny arg);

// --------------------------------------------------------------------------
typedef IlvDrawSelection* (*IlvMakeSelection)(IlvManager* manager,
					      IlvGraphic* object);

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerObjectInteractor
{
public:
    IlvManagerObjectInteractor(){}
    virtual ~IlvManagerObjectInteractor();

    virtual IlBoolean	handleEvent(IlvManager*		manager,
				    IlvGraphic*		obj,
				    IlvEvent&		event,
				    IlvView*		view,
				    IlvTransformer*	t) = 0;
    virtual IlBoolean	accept(const IlvGraphic* obj) const;
    virtual const char*	className() const;
};


// --------------------------------------------------------------------------
// Managing the double buffer allocation
// --------------------------------------------------------------------------
class IlvManagerDblBufferHandler
{
public:
    virtual ~IlvManagerDblBufferHandler();

    virtual IlvBitmap* createBitmap(IlvView*, IlvDim, IlvDim) = 0;
    virtual void       destroyBitmap(IlvView*, IlvBitmap*)    = 0;
};

// --------------------------------------------------------------------------
// IlvManager class information
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerClassInfo
    : public IlvValuedClassInfo
{
public:
    inline IlvManagerClassInfo* getManagerSuperClass() const
	{ return ILVDYNAMICCAST(IlvManagerClassInfo*, getSuperClass()); }
    static IlvManagerClassInfo* Create(const char*,
				       IlvClassInfo**,
				       IlvGetAccessorsFunction = 0);
protected:
    IlvManagerClassInfo(const char*             className,
			IlvClassInfo**          superClass,
			IlvGetAccessorsFunction ga = 0)
    : IlvValuedClassInfo(className, superClass, ga)
    {}
};
#define IlvRegisterManagerClass(classname, superclass)			\
ILVDEFINECLASSINFOMEMBERS(classname,					\
		IlvManagerClassInfo::Create(#classname,			\
					    superclass::ClassPtr()))
#define IlvRegisterManagerClassWithAccessors(cn, sc)			\
ILVDEFINECLASSINFOMEMBERS(cn,						\
		IlvManagerClassInfo::Create(#cn,			\
					    sc::ClassPtr(),		\
					    cn::GetAccessors))
#define IlvPreRegisterManagerClass(cn) ILVPREDEFINECLASSINFOMEMBERS(cn)
#define IlvPostRegisterManagerClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
		IlvManagerClassInfo::Create(#classname,			\
					    superclass::ClassPtr()))
#define IlvPostRegisterManagerClassWithAccessors(cn, sc)		\
ILVPOSTDEFINECLASSINFOMEMBERS(cn,					\
		IlvManagerClassInfo::Create(#cn,			\
					    sc::ClassPtr(),		\
					    cn::GetAccessors))

class IlvManagerGraphicHolder;

// --------------------------------------------------------------------------
enum IlvReDrawMode {
    IlvReDrawAll,
    IlvReDrawObjects
};

// --------------------------------------------------------------------------
// Manager
// --------------------------------------------------------------------------
class IlvListOfCommand;
class IlvManagerLayer;
class IlvManagerLayerFactory;
class IlvManagerDrawHook;
class IlvManagerSelectionHook;
class IlvManagerMessage;
class IlvManagerObservable;
class IlvGraphicSet;

class ILVMGREXPORTED IlvManager
    : public IlvValueInterface
{
public:
    IlvManager(IlvDisplay*	display,
	       int		layers		= 2,
	       IlBoolean	useacc		= IlTrue,
	       IlUShort		maxInList	= IlvMaxObjectsInList,
	       IlUShort		maxInNode	= IlvMaxObjectsInList);
    virtual ~IlvManager();

    // IlvManager1 Applying Functions to Located Objects
#if !defined(ILVUSEAPPLYCLASS)
    void		applyInside(int			layer,
				    IlvApplyObject	func,
				    IlAny		arg,
				    const IlvRect&	rect,
				    const IlvTransformer* t = 0,
				    IlBoolean		redraw = IlTrue);
    void		applyIntersects(int		layer,
					IlvApplyObject	func,
					IlAny		arg,
					const IlvRect&	rect,
					const IlvTransformer* t = 0,
					IlBoolean	redraw = IlTrue);
#else  /* ILVUSEAPPLYCLASS */

    void		applyInside(int			layer,
				    IlvApplyHook&	hook,
				    const IlvRect&	rect,
				    const IlvTransformer* t = 0,
				    IlBoolean		redraw = IlTrue);
    inline void		applyInside(int			layer,
				    IlvApplyObject	f,
				    IlAny		arg,
				    const IlvRect&	rect,
				    const IlvTransformer* t = 0,
				    IlBoolean		redraw = IlTrue)
			{
			    IlvApplyObjectHook hook(f, arg);
			    applyInside(layer, hook, rect, t, redraw);
			}
    void		applyIntersects(int		layer,
					IlvApplyHook&	hook,
					const IlvRect&	rect,
					const IlvTransformer* t = 0,
					IlBoolean	redraw = IlTrue);
    inline void		applyIntersects(int		layer,
					IlvApplyObject	f,
					IlAny		arg,
					const IlvRect&	rect,
					const IlvTransformer* t = 0,
					IlBoolean	redraw = IlTrue)
			{
			    IlvApplyObjectHook hook(f, arg);
			    applyIntersects(layer, hook, rect, t, redraw);
			}
#endif	/* ILVUSEAPPLYCLASS */

    void		applyInside(IlvApplyObject	func,
				    IlAny		arg,
				    const IlvRect&	rect,
				    const IlvTransformer* t = 0,
				    IlBoolean		redraw = IlTrue);
    void		applyIntersects(IlvApplyObject	func,
					IlAny		arg,
					const IlvRect&	rect,
					const IlvTransformer* t = 0,
					IlBoolean	redraw = IlTrue);
    // ____________________________________________________________
    // End IlvManager1 Applying Functions to Located Objects

    // ____________________________________________________________
    // IlvManager2 Applying Functions to Objects
    inline IlBoolean	isInApply() const { return _isInApply; }

#if defined(ILVUSEAPPLYCLASS)
    virtual void	applyToObjects(IlUInt		  count,
				       IlvGraphic* const* objs,
				       IlvApplyHook&	  hook,
				       IlBoolean	  redraw = IlTrue);
#endif /* ILVUSEAPPLYCLASS */
    virtual void	applyToObjects(IlUInt		  count,
				       IlvGraphic* const* objects,
				       IlvApplyObject	  func,
				       IlAny		  arg,
				       IlBoolean	  redraw = IlTrue);
    virtual void	applyToObjects(IlUInt		  count,
				       IlvGraphic* const* objects,
				       IlvApplyFunction   func,
				       IlAny		  arg,
				       IlBoolean	  redraw = IlTrue);
    virtual void	applyToObjects(int		layer,
				       IlvApplyObject	func,
				       IlAny		arg,
				       IlBoolean	redraw = IlTrue);
    virtual void	applyToObjects(int		layer,
				       IlvApplyFunction	func,
				       IlAny		arg,
				       IlBoolean	redraw = IlTrue);
#if defined(ILVUSEAPPLYCLASS)
    virtual void	applyToObject(IlvGraphic*	obj,
				      IlvApplyHook&	hook,
				      IlBoolean		redraw = IlTrue);
#endif	/* ILVUSEAPPLYCLASS */
    virtual void	applyToObject(IlvGraphic*	object,
				      IlvApplyObject	func,
				      IlAny		arg,
				      IlBoolean		redraw = IlTrue);
    // ____________________________________________________________
    // End IlvManager2 Applying Functions to Objects

    // ____________________________________________________________
    // IlvManager3 Associating an Interactor with an Object or View
    virtual IlBoolean	dispatchToObjects(IlvEvent&, IlvView*);

    // Interactors
    IlvManagerObjectInteractor*
			getObjectInteractor(const IlvGraphic* object) const;
    IlBoolean		setObjectInteractor(IlvGraphic* object,
					    IlvManagerObjectInteractor* i);
    void		setInteractor(IlvManagerViewInteractor* i,
				      const IlvView* view = 0);
    void		removeInteractor(const IlvView* view);
    IlvManagerViewInteractor*	getInteractor(const IlvView* view) const;
    virtual IlBoolean   gadgetShortCut(IlvEvent&);
    void		pushInteractor(IlvManagerViewInteractor* e);
    // ____________________________________________________________
    // End IlvManager3 Associating an Interactor with an Object or View

    // ____________________________________________________________
    // IlvManager4 Binding Views to a Manager
    // _ Views management ___________________________________________
    virtual void	addView(IlvView* view);
    virtual IlBoolean	removeView(IlvView* view);
    IlvView**		getViews(IlUInt& count) const;
    static IlvManager*	Get(const IlvView* view);
    static void		Set(IlvView* view, IlvManager* manager);
    IlvView*		getFirstView() const;
    inline
    IlvTransformer*	getTransformer(const IlvView* view) const
			{
			    IlvMgrView* mv = getView(view);
			    return mv ? mv->getTransformer() : 0;
			}
    virtual void	setTransformer(const IlvView*  view,
				       IlvTransformer* t = 0);
    virtual void	addTransformer(const IlvView*  view,
				       IlvTransformer* t = 0);
    inline void		translateView(const IlvView*	view,
				      IlvPos		dx,
				      IlvPos		dy,
				      IlBoolean		redraw = IlTrue)
			{
			    IlvMgrView* mgrview = getView(view);
			    if (mgrview) {
				translateView(mgrview, dx, dy, redraw);
			    }
			}
    void		zoomView(const IlvView*		view,
				 const IlvPoint&	point,
				 IlFloat		scalex,
				 IlFloat		scaley,
				 IlBoolean		redraw = IlTrue);
    void		rotateView(const IlvView*	view,
				   const IlvPoint&	point,
				   IlFloat		angle,
				   IlBoolean		redraw = IlTrue);
    void		fitTransformerToContents(const IlvView* view,
						 IlBoolean redraw = IlTrue,
						 IlBoolean ratio  = IlFalse);
    void		fitToContents(IlvView* view);
    IlBoolean		isKeepingAspectRatio(const IlvView* view) const;
    void		setKeepingAspectRatio(const IlvView* view,
					    IlBoolean ratio  = IlTrue,
					    IlBoolean redraw = IlTrue) const;
    void		ensureVisible(IlvView* view, const IlvPoint& point);
    void		ensureVisible(IlvView* view, const IlvRect& rect);
    inline void		allowEnsureVisible(IlBoolean v)
			{
			    _allowEnsureVisible = v;
			}
    inline IlBoolean	allowEnsureVisible() const
			{
			    return _allowEnsureVisible;
			}
    // ____________________________________________________________
    // End IlvManager4 Binding Views to a Manager


    // ____________________________________________________________
    // IlvManager5 Callback Management
    // Gadget related members _____________________________________
    // __ Callback management ____________________________________
    void		registerCallback(const char* callbackName,
					 IlvGraphicCallback callback);
    void		unregisterCallback(const char* callbackName);
    const IlAList*	getCallbackNames() const;
    IlvGraphicCallback	getCallback(const IlSymbol* cbName) const;
    inline void		removeCallback(const char* callbackName) // 2.1
			{
			    unregisterCallback(callbackName);
			}
    virtual void	callCallbacks(const IlSymbol* callbackName,
				      IlvGraphic*);
    inline void		callCallback(IlvGraphic* object)
			{
			    callCallbacks(IlvGraphic::CallbackSymbol(),
					  object);
			}
    // ____________________________________________________________
    // End IlvManager5 Callback Management

    // ____________________________________________________________
    // IlvManager6 Cut/Paste
    virtual char*	cut(IlUInt& count);
    virtual char*	copy(IlUInt& count);
    virtual void	paste(const IlvView*	view,
			      const char*	str,
			      IlvPoint&		location);
    void		cutToClipboard();
    void		copyToClipboard();
    void		pasteFromClipboard(const IlvView*	view,
					   IlvPoint&		location);
    // ____________________________________________________________
    // End IlvManager6 Cut/Paste

    // ____________________________________________________________
    // IlvManager7 Draw, Redraw and Group Objects
    // _ Graphic Set management __________________________________________
    virtual IlvGraphicSet*	group(IlUInt			count,
				      IlvGraphic* const*	objects);
    virtual void	unGroup(IlvGraphic*	object,
				IlBoolean	undoCommand = IlTrue);

    // Draw, ReDraw, Group...
    virtual void	eraseRegion(IlvView*		view,
				    const IlvRegion&	region) const;
    virtual void	draw(IlvView*		view,
			     IlBoolean		erase,
			     const IlvRegion*	clip = 0) const;
    void		draw(IlvPort*			dst,
			     const IlvTransformer*	t      = 0,
			     const IlvRegion*		region = 0,
			     const IlvRegion*		clip   = 0) const;
    void		draw(int			layer,
			     IlvPort*			dst,
			     const IlvTransformer*	t      = 0,
			     const IlvRegion*		region = 0,
			     const IlvRegion*		clip   = 0) const;
    // for dump module
    void		draw() const;	// All views
    void		reDraw() const;	// All views
    void		reDraw(const IlvGraphic*	object,
			       IlBoolean		erase = IlTrue) const;
    void		reDraw(IlUInt			count,
			       const IlvGraphic* const*	objects,
			       IlBoolean		erase = IlTrue) const;
    void		bufferedDraw(IlvView* view, const IlvRect& rect) const;
    void		bufferedDraw(IlvView*		view,
				     const IlvRegion&	region) const;
    void		bufferedDraw(IlvView*		view,
				     const IlvGraphic*	object) const;
    void		installDrawHook(IlvManagerDrawHook* hook);
    void		removeDrawHook(IlvManagerDrawHook* hook);
    virtual void	viewResized(const IlvView*, IlvRect&);
    // ____________________________________________________________
    // End IlvManager7 Draw, Redraw and Group Objects

    // ____________________________________________________________
    // IlvManager8 General Purpose Methods
    inline const char*	getName() const { return _name; }
    virtual void	setName(const char* name);
    inline IlvDisplay*	getDisplay() const { return _display; }
    inline IlvPalette*	getPalette() const { return _xor_palette; }
    inline IlBoolean	isModified() const { return _modified; }
    void		setModified(IlBoolean value);

    // _ Adding, removing, getting objects _______________________________
    IlUInt		getCardinal() const;
    virtual
    IlvGraphic* const*	getObjects(IlUInt& count) const;
    virtual
    IlvGraphic* const*	getObjects(int layer, IlUInt& count) const;

    // _ Hit testing _______________________________
    virtual IlvGraphic*	lastContains(const IlvPoint&	p,
				     const IlvView*	view) const;
    IlvGraphic*		lastContains(int		layer,
				     const IlvPoint&	p,
				     const IlvView*	view) const;
    IlvGraphic*		filteredLastContains(const IlvPoint& p,
					     const IlvView* view,
					     const IlvGraphicFilter& f)const;
    IlvGraphic*		filteredLastContains(int             layer,
					     const IlvPoint& p,
					     const IlvView*  view,
					     const IlvGraphicFilter& f)const;
    IlvGraphic* const*	allContains(const IlvPoint&	p,
				    const IlvView*	view,
				    IlUInt&		count) const;
    IlvGraphic* const*	allContains(int			layer,
				    const IlvPoint&	p,
				    const IlvView*	view,
				    IlUInt&		count) const;
    IlvGraphic*		firstIntersects(const IlvRegion&	tr,
					const IlvTransformer*	t) const;
    IlvGraphic*		firstIntersects(int			layer,
					const IlvRegion&	tr,
					const IlvTransformer*	t) const;
    IlvGraphic* const*	allInside(IlUInt&		count,
				  const IlvRect&	rect,
				  const IlvTransformer*	t = 0) const;
    IlvGraphic* const*	allIntersects(IlUInt&			count,
				      const IlvRect&		rect,
				      const IlvTransformer*	t = 0) const;
    IlvGraphic* const*	allIntersects(int			layer,
				      IlUInt&			count,
				      const IlvRect&		rect,
				      const IlvTransformer*	t = 0) const;
    IlvGraphic* const*	allInside(int			layer,
				  IlUInt&		count,
				  const IlvRect&	rect,
				  const IlvTransformer*	t = 0) const;

    // Managing layers ____________________________________________
    IlUInt		getCardinal(int layer) const;
    virtual void	contentsChanged();
    // Setting clean function
    inline void		setCleanFunction(IlvApplyObject func)
	{ _cleanGraphic = func; }
    void		computeBBox(IlvRect&			bbox,
				    const IlvTransformer*	t = 0) const;
    void		computeBBox(IlvRect& bbox, const IlvView* view) const;
    // 1.0 compatibility
    inline IlvGraphic* const*	objects(IlUInt& count) const
	{ return getObjects(count); }
    inline IlvGraphic*	firstIntersects(const IlvRect& r)
	{ return firstIntersects(IlvRegion(r), 0); }
    inline void		setClientData(IlAny data) { _clientData = data; }
    inline IlAny	getClientData() const     { return _clientData; }
    // ____________________________________________________________
    // End IlvManager8 General Purpose Methods

    // ____________________________________________________________
    // IlvManager9 Grid Management
    // _ Grid management _______________________________
    inline IlvManagerGrid*	getGrid(const IlvView* view) const
	{
	    IlvMgrView* mv = getView(view);
	    return mv ? mv->grid() : 0;
	}
    inline void		setGrid(IlvView* const view, IlvManagerGrid* grid)
	{
	    IlvMgrView* mv = getView(view);
	    if (mv) {
		mv->grid(grid);
	    }
	}
    inline void		snapToGrid(const IlvView* view, IlvPoint& p) const
	{
	    IlvMgrView* mv = getView(view);
	    if (mv) {
		snapToGrid(mv, p);
	    }
	}
    inline IlBoolean	transformThroughGrid(const IlvView*	view,
					     IlvPoint&		p) const
	{
	    IlBoolean ret = IlFalse;
	    IlvMgrView* mv = getView(view);
	    if (mv) {
		transformThroughGrid(mv, p);
		ret = IlTrue;
	    }
	    return ret;
	}
    // ____________________________________________________________
    // End IlvManager9 Grid Management

    // ____________________________________________________________
    // IlvManager10 Input/Output
    // IOs ________________________________________________________
    virtual IlvManagerInputFile* createInputFile(ILVSTDPREF istream& stream);
    virtual
    IlvManagerOutputFile* createOutputFile(ILVSTDPREF ostream& stream) const;
    virtual void	save(ILVSTDPREF ostream& stream) const;
    virtual void	read(ILVSTDPREF istream& stream);
    virtual void	read(const char* filename);
    // ____________________________________________________________
    // End IlvManager10 Input/Output

    // ____________________________________________________________
    // IlvManager11 Managing Accelerators
    // Handling events
    IlBoolean		installEventHook(const IlvManagerEventHook* hook);
    IlvManagerEventHook* removeEventHook(const IlvManagerEventHook* hook);
    virtual IlBoolean	shortCut(IlvEvent& event, IlvView* view);

    // Accelerators
    void		addAccelerator(IlvManagerAcceleratorAction f,
				       IlvEventType	type,
				       IlUShort		buttonOrKey	= 0,
				       IlUShort		modifiers	= 0,
				       IlAny		userArg		= 0,
				       IlUShort		optModifiers	= 0);
    void		removeAccelerator(IlvEventType	type,
					  IlUShort	buttonOrKey = 0,
					  IlUShort	modifiers = 0);
    IlBoolean		getAccelerator(IlvManagerAcceleratorAction* f,
				       IlAny*		userArg,
				       IlvEventType	type,
				       IlUShort		buttonOrKey = 0,
				       IlUShort		modifiers   = 0);
    void		removeAccelerators();
    virtual void	handleInput(IlvEvent& event, IlvView* view);
    inline IlvManagerEventHook* getEventHooks() const { return _eventHooks; }
    IlBoolean		handleEventHooks(IlvEvent& event, IlvView* view);
    void		addAccelerator(IlvManagerAccelerator*);
    void		removeAccelerator(IlvManagerAccelerator*);
    IlvManagerAccelerator*	getAccelerator(IlvEventType type,
					       IlUShort     buttonOrKey = 0,
					       IlUShort     modifiers   = 0);
    // ____________________________________________________________
    // End IlvManager11 Managing Accelerators

    // ____________________________________________________________
    // IlvManager12 Managing Double Buffering
    // Managing Double Buffering __________________________________
    IlBoolean		setDoubleBuffering(const IlvView*	view,
					   IlBoolean		useDB,
					   IlBoolean		tmp = IlFalse);
    virtual void	setBackground(IlvView*		view,
				      IlvColor*		color,
				      IlvBitmap*	bitmap = 0);
    IlBoolean		isDoubleBuffering(const IlvView* view) const;
    void		setDoubleBufferingColor(IlvColor* color);// 1.0
    inline IlvManagerDblBufferHandler*	getDoubleBufferingHandler() const
	{ return _dblBufferHandler; }
    void	setDoubleBufferingHandler(IlvManagerDblBufferHandler*);
    IlvBitmap*	getDoubleBufferingBitmap(const IlvView*) const;
    // ____________________________________________________________
    // End IlvManager12 Managing Double Buffering

    // ____________________________________________________________
    // IlvManager13 Managing Object Layers
    IlBoolean		isVisible(int layer) const;
    void		setVisible(int layer, IlBoolean visible);
    IlBoolean		isVisible(const IlvView* view, int layer) const;
    void		setVisible(const IlvView*	view,
				   int			layer,
				   IlBoolean		visible);
    IlBoolean		isSelectable(int layer) const;
    void		setSelectable(int layer, IlBoolean selectable);
    virtual void	pop(IlvGraphic* object, IlBoolean redraw = IlTrue);
    virtual void	push(IlvGraphic* object, IlBoolean redraw = IlTrue);
    IlvManagerLayer*	getManagerLayer(const IlvGraphic* object)const;
    int			getLayer(const IlvGraphic* object) const;
    void		setLayer(IlvGraphic*	object,
				 int		layer,
				 IlBoolean	redraw = IlTrue);
    inline int		getNumLayers() const { return _numlayers - 1; }
    void		setNumLayers(int numLayers);
    void		swapLayers(int		layer1,
				   int		layer2,
				   IlBoolean	redraw = IlTrue);
    void		addLayer(int position = -1,
				 IlUShort maxInList = IlvMaxObjectsInList,
				 IlUShort maxInNode = IlvMaxObjectsInList);
    void		removeLayer(int layer = -1);
    int			addLayer(IlvManagerLayer*	layer,
				 int			position = -1);
    inline IlvManagerLayer*	getManagerLayer(int index) const
	{
	    return ((index >= 0) && (index < _numlayers))
		   ? _layers[index]
		   : (IlvManagerLayer*)0;
	}
    int			getLayerIndex(const IlvManagerLayer* layer) const;
    virtual void	moveLayer(int, int, IlBoolean = IlTrue);
    IlvManagerLayer*	getManagerLayer(const char*) const;
    IlvManagerLayer*	removeLayer(IlvManagerLayer*);
    IlvManagerLayer*	replaceLayer(IlvManagerLayer*, int);
    IlvManagerLayerFactory* setManagerLayerFactory(IlvManagerLayerFactory*);
    // ____________________________________________________________
    // End IlvManager13 Managing Object Layers

    // ____________________________________________________________
    // IlvManager14 Managing Selections
    // _ Managing selections __________________________________________
    inline IlvMakeSelection	setMakeSelection(IlvMakeSelection func)
	{
	    IlvMakeSelection old = _makeSelection;
	    _makeSelection = func;
	    return old;
	}
    IlBoolean		installSelectionHook(const
					     IlvManagerSelectionHook* hook);
    IlvManagerSelectionHook*	removeSelectionHook(const
					      IlvManagerSelectionHook* hook);
    inline void		applyToSelections(IlvApplyObject func,
					  IlAny		arg,
					  IlBoolean	redraw = IlTrue)
	{
	    IlUInt count;
	    IlvGraphic* const* objs = getSelections(count);
	    IlPoolOf(Pointer)::Lock((IlAny*)objs);
	    applyToObjects(count,
			   (IlvGraphic* const*)objs,
			   func,
			   arg,
			   redraw);
	    IlPoolOf(Pointer)::UnLock((IlAny*)objs);
	}
    IlUInt		numberOfSelections() const;
    virtual void	deSelectAll(IlBoolean redraw = IlTrue);
    virtual void	selectAll(IlBoolean redraw = IlTrue);
    IlvGraphic* const*	getSelections(IlUInt& count) const;
    IlvDrawSelection*	getSelection(const IlvGraphic* object) const;

    IlvGraphic* const*	sortObjects(IlvGraphic* const*	objs,
				    IlUInt		count) const;

    // Manipulating Objects
    virtual void	setSelected(IlvGraphic*	object,
				    IlBoolean	selected = IlTrue,
				    IlBoolean	redraw   = IlTrue);
    inline IlBoolean	isSelected(const IlvGraphic* obj) const
	{ return (IlBoolean)(getSelection(obj) != 0); }
    // Object alignment
    virtual void	duplicate(IlvPos dx = 0, IlvPos dy = 0);
    // Unclassified (yet)
    virtual void	deleteSelections(IlBoolean redraw = IlTrue);
    inline IlvManagerSelectionHook*	getSelectionHooks() const
	{ return _selectionHooks; }
    // ____________________________________________________________
    // End IlvManager14 Managing Selections

    // ____________________________________________________________
    // IlvManager15 Managing SmartSets
    // _ Smartset management __________________________________________
    IlvSmartSet*	getSmartSet(const char* name) const;
    virtual IlBoolean	addSmartSet(IlvSmartSet*	set,
				    IlBoolean		redraw = IlTrue);
    virtual IlBoolean	removeSmartSet(IlvSmartSet* set);
    virtual
    IlvSmartSet*	duplicateSmartSet(IlvSmartSet*	set,
					  IlvPos	dx = 0,
					  IlvPos	dy = 0);
    // ____________________________________________________________
    // End IlvManager15 Managing SmartSets

    // ____________________________________________________________
    // IlvManager16 Managing Undo
    // Managing Undo ______________________________________________
    IlBoolean		isUndoEnabled() const;
    void		setUndoEnabled(IlBoolean enable);
    void		forgetUndo();
    virtual void	repeat();
    virtual void	reDo(IlBoolean unused);
    virtual void	unDo();
    virtual void	addCommand(IlvCommand* command);

    inline IlvCommandHistory*	getCommandHistory() const
	{ return _commands; }
    // ____________________________________________________________
    // End IlvManager16 Managing Undo

    // ____________________________________________________________
    // IlvManager17 Managing View Hooks
    // Hooks ______________________________________________________
    void		installViewHook(const IlvManagerViewHook* hook);
    void		removeViewHook(const IlvManagerViewHook* hook);
    IlvManagerViewHook* const*	getViewHooks(const IlvView*	view,
					     IlUInt&		count) const;
    IlvLink*		getViewHookList(const IlvView* view) const;
    // ____________________________________________________________
    // End IlvManager17 Managing View Hooks

    // ____________________________________________________________
    // IlvManager18 Manipulating Objects
    virtual void	translateObject(IlvGraphic*	object,
					IlvPos		dx,
					IlvPos		dy,
					IlBoolean	redraw = IlTrue);
    inline void		moveObject(IlvGraphic*	object,
				   IlvPos	x,
				   IlvPos	y,
				   IlBoolean	redraw = IlTrue)
	{
	    IlvRect rect;
	    object->boundingBox(rect);
	    translateObject(object,
			    x - rect.x(),
			    y - rect.y(),
			    redraw);
	}
    virtual void	reshapeObject(IlvGraphic*	object,
				      const IlvRect&	bbox,
				      IlBoolean		redraw = IlTrue);
    // ____________________________________________________________
    // End IlvManager18 Manipulating Objects

    // ____________________________________________________________
    // IlvManager19 Object Alignment
    virtual void	align(IlvPosition	alignment,
			      IlBoolean		redraw = IlTrue);
    virtual void	makeColumn(IlvDim	spacing = 0,
				   IlBoolean	redraw = IlTrue);
    virtual void	makeRow(IlvDim		spacing = 0,
				IlBoolean	redraw = IlTrue);
    virtual void	sameWidth(IlBoolean redraw = IlTrue);
    virtual void	sameHeight(IlBoolean redraw = IlTrue);
    // ____________________________________________________________
    // End IlvManager19 Object Alignment

    // ____________________________________________________________
    // IlvManager20 Object Creation Interactors
    inline IlvPalette* 	getCreatorPalette() const
	{ return _creatorPalette; }
    void		setCreatorPalette(IlvPalette* palette);
    inline int		getInsertionLayer() const
	{ return _insertionLayer; }
    void		setInsertionLayer(int layer = -1);
    // ____________________________________________________________
    // End IlvManager20 Object Creation Interactors

    // ____________________________________________________________
    // IlvManager21 Object Properties
    virtual void	addObject(IlvGraphic*	object,
				  IlBoolean	redraw = IlTrue,
				  int		layer  = -1);
    virtual void	addObject(const char*	name,
				  IlvGraphic*	object,
				  IlBoolean	redraw = IlTrue,
				  int		layer  = -1);
    virtual IlBoolean	removeObject(IlvGraphic*	object,
				     IlBoolean		redraw    = IlTrue,
				     IlBoolean		destroyIt = IlTrue);

    inline
    IlvGraphic* const*	objects(int layer, IlUInt& count) const //1.0
	{ return getObjects(layer, count); }

    IlvGraphic* const*	getPersistentObjects(IlUInt& count) const;

    IlvDrawSelection*	whichSelection(const IlvPoint&	p,
				       const IlvView*	view) const;
    inline IlvGraphic*	firstIntersects(int layer, const IlvRect& r)
	{ return firstIntersects(layer, IlvRegion(r), 0); }


    // _ Object properties __________________________________________
    IlBoolean		isVisible(const IlvGraphic* object) const;
    inline IlBoolean	isVisible(const IlvGraphic*	graphic,
				  IlvView*		view) const
	{
	    IlvMgrView* mv = getView(view);
	    return mv ? isVisible(graphic, mv) : IlFalse;
	}
    void		setVisible(IlvGraphic*	object,
				   IlBoolean	visible,
				   IlBoolean	redraw = IlFalse);
    inline const char*	getObjectName(const IlvGraphic* object) const
	{ return object->getName(); }
    virtual IlBoolean	setObjectName(IlvGraphic* object, const char* name);
    IlvGraphic*		getObject(const char* name) const;
    virtual IlBoolean	isSelectable(const IlvGraphic* obj) const;
    virtual void	setSelectable(IlvGraphic*	object,
				      IlBoolean		selectable);
    IlBoolean		isMoveable(const IlvGraphic* object) const;
    void		setMoveable(IlvGraphic* object, IlBoolean moveable);
    IlBoolean		isResizeable(const IlvGraphic* object) const;
    void		setResizeable(IlvGraphic* object, IlBoolean resizable);

    IlBoolean		isEditable(const IlvGraphic* object) const;

    IlBoolean		isEditable(const IlvGraphic* object,
				   const IlvView*) const;
    IlvEditableFilter*	getEditableFilter() const;
    IlvEditableFilter*	setEditableFilter(IlvEditableFilter*);

    void		setEditable(IlvGraphic* object, IlBoolean editable);

    IlBoolean		isManaged(const IlvGraphic* object) const;
    static IlvManager*	getManager(const IlvGraphic* object);
    IlBoolean		isASelection(const IlvGraphic* object) const;
    virtual void	deleteAll(IlBoolean destroy, IlBoolean redraw);
    virtual void	deleteAll(int		layer,
				  IlBoolean	destroy,
				  IlBoolean	redraw);
    virtual void	installAccelerators();
    // ____________________________________________________________
    // End IlvManager21 Object Properties

    // ____________________________________________________________
    // IlvManager22 Optimizing Drawing Tasks
    // _ Optimizing drawing tasks _________________________________________
    void		initReDraws();
    void		invalidateRegion(const IlvGraphic* object);
    void		invalidateRegion(const IlvRect& rect);
    void		invalidateRegion(const IlvView* view,
					 const IlvRect& rect);

    void		invalidateRegion(const IlvRegionUpdater& updater,
					 const IlvGraphic* g = 0);

    void		reDrawViews(IlBoolean erase = IlTrue);
    void		abortReDraws();
    virtual void	flushRedraw();
    void		disableRedrawTask();

    inline IlvReDrawMode	getReDrawMode() const { return _reDrawMode; }
    inline void		setReDrawMode(IlvReDrawMode reDrawMode)
	{ _reDrawMode = reDrawMode; }
    inline IlBoolean	isInvalidating() const
	{ return (_invalidating || _redrawTask); }
    inline void		addBefore(const IlvGraphic* g)
	{ invalidateRegion(g); }
    inline void		addAfter(const IlvGraphic* g)
	{ invalidateRegion(g); }
    // ____________________________________________________________
    // End IlvManager22 Optimizing Drawing Tasks

    // ____________________________________________________________
    // IlvManager23 Tag Management
    // _ Managing tags __________________________________________
    IlvGraphic* const*	getTaggedObjects(const IlSymbol*	tag,
					 IlUInt&		count) const;
    void		setTaggedObjectsSelected(const IlSymbol* tag,
						 IlBoolean selected = IlTrue,
						 IlBoolean redraw   = IlTrue);
    void		removeTaggedObjects(const IlSymbol* tag,
					    IlBoolean redraw = IlTrue);
    void		applyToTaggedObjects(const IlSymbol* tag,
					     IlvApplyObject  func,
					     IlAny           arg,
					     IlBoolean redraw = IlTrue);
    // ____________________________________________________________
    // End IlvManager23 Tag Management

    // _ Apply functions __________________________________________
    virtual void	beforeApply(const IlvGraphic*, IlBoolean = IlTrue);
    virtual void	afterApply(const IlvGraphic*, IlBoolean = IlTrue);

    // Obsolete methods
    inline void		deSelect(IlBoolean r = IlTrue)
	{ deSelectAll(r); }
    virtual void	makeSelected(IlvGraphic*, IlBoolean = IlTrue);
    virtual void	makeUnSelected(IlvGraphic*, IlBoolean = IlTrue);
    // End of obsolete methods

    // _ Not documented ___________________________________________

    // Interactors __________________________________________________
    void		abortViewInteractors();
    // Selection hook _______________________________________________
    void		startSelectionChanged();
    void		endSelectionChanged();

    // Mapping functions to objects _________________________________
    void		map(IlvApplyObject, IlAny);
    void		map(int, IlvApplyObject, IlAny);
    void		mapInside(IlvApplyObject,
				  IlAny,
				  const IlvRect&,
				  const IlvTransformer* = 0);
    void		mapIntersects(IlvApplyObject,
				      IlAny,
				      const IlvRect&,
				      const IlvTransformer* = 0);
    void		mapInside(int,
				  IlvApplyObject,
				  IlAny,
				  const IlvRect&,
				  const IlvTransformer* = 0);
    void		mapIntersects(int,
				      IlvApplyObject,
				      IlAny,
				      const IlvRect&,
				      const IlvTransformer* = 0);
    void		mapSelections(IlvApplyObject, IlAny);
    virtual IlvGraphic*	lastContains(const IlvPoint&,
				     const IlvMgrView*) const;
    virtual IlvGraphic*	lastContains(const IlvPoint&,
				     const IlvPoint&,
				     const IlvTransformer*) const;
    inline IlvGraphic*	lastContains(const IlvPoint& p)
	{ return lastContains(p, p, (const IlvTransformer*) 0); }
    IlvGraphic*		filteredLastContains(const IlvPoint&,
					     const IlvMgrView*,
					     const IlvGraphicFilter&) const;
    IlvGraphic*		filteredLastContains(const IlvPoint&,
					     const IlvPoint&,
					     const IlvTransformer*,
					     const IlvGraphicFilter&) const;
    inline IlvGraphic*	filteredLastContains(const IlvPoint& p,
					     const IlvGraphicFilter& f)
	{ return filteredLastContains(p, p, (const IlvTransformer*)0, f); }
    inline const IlvPalette*	getInvertedPalette() const
	{ return _invertpalette; }

    virtual IlBoolean	isFocusClient(const IlvGraphic*) const;
    virtual IlBoolean	isFocusTabClient(const IlvGraphic*) const;
    virtual void	focusIn(IlvEvent&);
    virtual void	focusOut(IlvEvent&);
    virtual IlvGraphic*	getFocus() const;
    virtual void	setFocus(IlvGraphic* = 0, IlBoolean = IlTrue);
    virtual IlBoolean	isFocusAllowed() const;
    virtual IlBoolean	allowFocus(IlBoolean);
    virtual void	moveFocusAfter(IlBoolean = IlTrue);
    virtual void	moveFocusBefore(IlBoolean = IlTrue);
    virtual void	moveFocusFirst();
    virtual void	moveFocusLast();
    virtual void	drawFocus(IlvPort*,
				  const IlvTransformer* = 0,
				  const IlvRegion*      = 0)const;
    virtual IlvGraphic*	getGrab() const;
    virtual void	setGrab(IlvGraphic*);
    virtual void	removeGrab();
    inline IlvManagerGraphicHolder* getHolder() const { return _holder; }
    IlBoolean		handleEvent(IlvGraphic*, IlvEvent&, IlvView*);

    // Observers ____________________________________________________
    IlvManagerObservable* getObservable(IlBoolean = IlFalse);
    inline void		setObservable(IlvManagerObservable* observable)
	{ _observable = observable; }

    static IlSymbol*	_managerProperty;
    static IlSymbol*	_objectSelectionProperty;
    static IlSymbol*	_objectInteractorProperty;

    inline static IlSymbol*	managerProperty()
	{ return _managerProperty; }
    inline static IlSymbol*	objectSelectionProperty ()
	{ return _objectSelectionProperty; }
    inline static IlSymbol*	objectInteractorProperty()
	{ return _objectInteractorProperty; }
    inline IlBoolean	isVisible(const IlvGraphic* g, IlvMgrView* mv) const
	{
	    return isManaged(g)
		   ? (isVisible(g)
		      ? mv->isVisible(getLayer(g))
		      : IlFalse)
		   : IlTrue;
	}
    virtual IlvObjectProperty*	makeObjectProperty(int = 0);
    virtual IlBoolean	cleanObj(IlvGraphic*,
				 IlBoolean = IlTrue,
				 IlBoolean = IlTrue);
    void		translateView(IlvMgrView*,
				      IlvPos, IlvPos,
				      IlBoolean = IlTrue);
    virtual IlBoolean	shortCut(IlvEvent&, IlvMgrView*);
    virtual void	translateSelections(IlvPos, IlvPos,
					    IlvMgrView*,
					    IlBoolean = IlTrue);
    virtual void	draw(IlvMgrView*,
			     IlBoolean,
			     const IlvRegion* = 0) const;
    inline void		draw(IlvMgrView*	mv,
			     IlBoolean		erase,
			     const IlvRect*	clip) const
	{
	    IlvRegion region(*clip);
	    draw(mv, erase, &region);
	}
    void		snapToGrid(IlvMgrView*, IlvPoint&) const;
    void		transformThroughGrid(IlvMgrView*, IlvPoint&) const;
    IlvMgrView*		getView(const IlvView* v) const;
    IlBoolean		removeView(IlvMgrView*) const;
    void		drawSelection(IlvDrawSelection*) const;
    void		eraseSelection(IlvDrawSelection*) const;
    inline IlvGraphic*	getInteractiveObject() const
	{ return _interactiveObject; }
    inline void		setInteractiveObject(IlvGraphic* obj)
	{ _interactiveObject = obj; }
    virtual void	selectionRequest(const IlvGraphic*);
    virtual void	cleanSelection(const IlvGraphic*);

    inline static IlUInt	SetMaxObjectsForPartialReDraw(IlUInt max)
	{
	    IlUInt old = _maxObjectsForPartialReDraw;
	    _maxObjectsForPartialReDraw = max;
	    return old;
	}
    inline const IlList* getMgrViews()  const { return _views;     }
    inline IlvEvent*	 getLastEvent() const { return _lastEvent; }

    IlvDeclarePropertyListDelegation();
    IlvDeclareLazyPropRootClassInfo();

protected:
    IlvManagerGraphicHolder*	_holder;
    IlList*			_views;
    int				_numlayers;
    IlvManagerLayer**		_layers;
    IlvManagerLayerFactory*	_layerFactory;
    IlvPalette*			_xor_palette;
    IlvPalette*			_invertpalette;
    IlvDisplay*			_display;
    IlvpCommandHistory		_commands;
    IlBoolean			_modified;
    IlStringHashTable*		_names;
    IlList			_accelerators;
    IlvApplyObject		_cleanGraphic;
    IlvMakeSelection		_makeSelection;
    IlvManagerDblBufferHandler*	_dblBufferHandler;
    IlvGraphic*			_interactiveObject;
    char*			_name;
    IlUInt			_invalidating;
    IlAny			_redrawTask;

#if defined(X11)
    int				_invalidBitPlanesGroup;
#endif /* X11 */
    IlBoolean			_isInApply;
    IlvReDrawMode		_reDrawMode;
    IlList*			_invalidObjects;
    IlAList			_callbacks;
    IlBoolean			_allowEnsureVisible;
    IlList*			_smartSets;
    IlAny			_clientData;
    int				_selectionHookLevel;
    IlvManagerSelectionHook*	_selectionHooks;
    IlvManagerDrawHook*		_drawHooks;
    IlvManagerObservable*	_observable;
    IlvEvent*			_lastEvent;


    void		scheduleRedrawTask();
    void		drawAll(IlvMgrView*,
				const IlvRegion&,
				const IlvRegion* = 0) const;
    IlvGraphic* const*	getDrawSelections(IlUInt&) const;
    void		setSelection(IlvGraphic*,
				     IlvDrawSelection*);
    void		makeBitmap(const IlvView*);
    void		freeBitmap(const IlvView*);
    void		cleanObjs();

    static IlUInt	_maxObjectsForPartialReDraw;
    static IlBoolean	RedrawTask(IlAny);

private:
    void		selectionChanged(IlvGraphic*, IlBoolean);

    IlvPalette*		_creatorPalette;
    int			_insertionLayer;
    IlBoolean		_cleanObjDone;
    IlvManagerEventHook* _eventHooks;

public:
    virtual IlBoolean wantsNavigationHandler() const;

    // Look, Language and Bidi callbacks _________________________________
    virtual void	changeLook();
    virtual void	changeLanguage();
    virtual void	changeLayoutAttributes(IlAny, IlAny);

    // Accessors
    DeclareValueAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

    static IlSymbol*	_cardinalValue;
    static IlSymbol*	_layerCardinalValue;
    static IlSymbol*	_insertionLayerValue;
    static IlSymbol*	_numberOfSelectionsValue;
    // Methods
    static IlSymbol*	_getObjectMethod;
    static IlSymbol*	_addObjectMethod;
    static IlSymbol*	_removeObjectMethod;
    static IlSymbol*	_deleteAllObjectsMethod;
    static IlSymbol*	_getFirstViewMethod;
    static IlSymbol*	_addViewMethod;
    static IlSymbol*	_removeViewMethod;
    static IlSymbol*	_translateViewMethod;
    static IlSymbol*	_rotateViewMethod;
    static IlSymbol*	_zoomViewMethod;
    static IlSymbol*	_fitTransformerToContentsMethod;
    static IlSymbol*	_ensureVisibleMethod;
    static IlSymbol*	_setBackgroundMethod;
    static IlSymbol*	_useDoubleBufferingMethod;
    static IlSymbol*	_setDoubleBufferingMethod;
    static IlSymbol*	_isSelectableMethod;
    static IlSymbol*	_setSelectableMethod;
    static IlSymbol*	_isMovableMethod;
    static IlSymbol*	_setMovableMethod;
    static IlSymbol*	_isResizableMethod;
    static IlSymbol*	_setResizableMethod;
    static IlSymbol*	_isSelectedMethod;
    static IlSymbol*	_setSelectedMethod;
    static IlSymbol*	_deselectAllMethod;
    static IlSymbol*	_alignMethod;
    static IlSymbol*	_makeColumnMethod;
    static IlSymbol*	_makeRowMethod;
    static IlSymbol*	_sameWidthMethod;
    static IlSymbol*	_sameHeightMethod;
    static IlSymbol*	_lastContainsMethod;
    static IlSymbol*	_setInteractorMethod;
};

// --------------------------------------------------------------------------
// IlvManagerObjectProperty
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerObjectProperty
    : public IlvObjectProperty
{
public:
    IlvManagerObjectProperty(IlvManagerLayer* layer)
	: IlvObjectProperty(),
	  _layer(layer)
    {
	_holder = IL_REINTERPRETCAST(IlvGraphicHolder*,
				     getManager()->getHolder());
    }
    IL_MLK_DECL();

    IlvManager*		getManager() const;
    inline IlvManagerLayer*	getManagerLayer() const { return _layer; }
    inline void			setManagerLayer(IlvManagerLayer* layer)
	{ _layer = layer; }
    IlUShort		getLayer() const;

protected:
    IlvManagerLayer*	_layer;
};

// --------------------------------------------------------------------------
extern "C" {
ILVMGREXPORTEDFUNCTION(IlBoolean)
IlvGetContentsChangedUpdate();
ILVMGREXPORTEDFUNCTION(void)
IlvSetContentsChangedUpdate(IlBoolean value);
}

ILVMGRMODULEINIT(m0_manager);

#endif /* !__Ilv_Manager_Manager_H */
