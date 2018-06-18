// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/mgrview.h
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
// Declaration of the IlvMgrView class
// Declaration of the IlvManagerViewInteractor class
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Mgrview_H
#define __Ilv_Manager_Mgrview_H

#if !defined(__Ilv_Manager_Macros_H)
#  include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Base_View_H)
#  include <ilviews/base/view.h>
#endif
#if !defined(__Ilv_Base_Inter_H)
#  include <ilviews/base/inter.h>
#endif

class IlvManager;
class IlvManagerViewInteractor;
class IlvManagerViewHook;
class IlvManagerGrid;
class IlvNavigationInteractor;

// --------------------------------------------------------------------------
// Manager View
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvMgrView
{
public:
    IlvMgrView(IlvManager*, IlvView*, const IlvTransformer* = 0);
    virtual ~IlvMgrView();
    // ____________________________________________________________
    inline IlvManager*		manager() const { return _manager; }
    inline IlvView*		view() const { return _view; }

    inline void			grid(IlvManagerGrid* g) { _grid = g; }
    inline IlvManagerGrid*	grid() const { return _grid; }

    inline IlvTransformer*	getTransformer() const { return _transform; }
    inline IlvTransformer*	transformer() const
	{ return getTransformer();}
    void			addTransformer(IlvTransformer*);
    void			setTransformer(IlvTransformer*);

    inline IlvManagerViewInteractor*	getInteractor() const
	{ return _interactor; }
    void			setInteractor(IlvManagerViewInteractor*);
    void			pushInteractor(IlvManagerViewInteractor*);

    inline IlBoolean	keepAspectRatio() const
	{ return _keepAspectRatio; }
    IlBoolean		keepAspectRatio(IlBoolean);
    IlBoolean		checkAspectRatio();
    inline IlvBitmap*	bitmap()          const { return _bitmap;  }
    inline void		setBitmap(IlvBitmap* b) { _bitmap = b;     }
    inline IlvPalette*	palette()         const { return _palette; }
    void		updateBackground();
    void		makeBitmap();
    void		freeBitmap();
    void		initCallbacks();
    void		deleteCallbacks();
    void		flushRedraw();
    inline IlvRegion*	getRegion()             { return &_region; }

    // Region management __________________________________________
    IlvRegionOptimizer* getRegionOptimizer() const { return _regOptimizer; }
    inline void		setRegionOptimizer(IlvRegionOptimizer* optimizer)
	{
	    delete _regOptimizer;
	    _regOptimizer = optimizer;
	}
    inline void		invalidateRegion(const IlvRect& r)
	{
	    IlvDim w, h;
	    _view->size(w, h);
	    IlvRect viewRect(0, 0, w, h);
	    viewRect.intersection(r);
	    if (viewRect.w() && viewRect.h()) {
		optimizeRegion(viewRect);
	    }
	}
    virtual void	optimizeRegion(const IlvRect&);
    virtual void	finalizeRegion(IlvRegion* = 0);
    // Layers management __________________________________________
    void		initLayers(int);
    void		insertLayer(int, int);
    void		removeLayer(int, int);
    IlBoolean		isVisible(int       layer,
				  IlBoolean filter = IlTrue) const;
    void		setVisible(int, IlBoolean);
    void		swapLayers(int, int);

    // View hooks _________________________________________________
    inline IlvLink*	getHooks() const { return _hooks; }
    inline void		addHook(const IlvManagerViewHook* hook)
	{ _hooks = new IlvLink((IlAny)hook, _hooks); }
    inline void		removeHook(const IlvManagerViewHook* hook)
	{
	    if (_hooks) {
		_hooks = _hooks->remove((IlAny)hook);
	    }
	}

    void		beforeDraw(IlvPort*,
				   const IlvTransformer* = 0,
				   const IlvRegion*      = 0,
				   const IlvRegion*      = 0);
    void		afterDraw(IlvPort*,
				  const IlvTransformer* = 0,
				  const IlvRegion*      = 0,
				  const IlvRegion*      = 0);
    void		afterExpose(const IlvRect&);
    void		handleExpose(IlvRegion* = 0);
    void		interactorChanged(IlvManagerViewInteractor*,
					  IlvManagerViewInteractor*);
    void		transformerChanged(const IlvTransformer*,
					   const IlvTransformer*);
    void		viewResized();
    void		viewRemoved();
    void		contentsChanged();
    inline void		getPreviousSizes(IlvDim& w, IlvDim& h)
	{
	    w = _previousWidth;
	    h = _previousHeight;
	}
    inline void		setPreviousSizes(IlvDim w, IlvDim h)
	{
	    _previousWidth  = w;
	    _previousHeight = h;
	}
    inline IlvNavigationInteractor* getNavigationInteractor() const
	{ return _navigationInter; }
protected:
    IlvManager*			_manager;
    IlvView*			_view;
    IlvTransformer*		_transform;
    IlvManagerViewInteractor*	_interactor;
    IlUShort			_flags;
    IlBoolean                   _keepAspectRatio;
    IlvBitmap*			_bitmap;
    IlvPalette*			_palette;
    IlvManagerGrid*		_grid;
    IlvRegion			_region;
    IlBoolean*			_layers;
    IlvLink*			_hooks;
    IlvDim			_previousWidth;
    IlvDim			_previousHeight;
    IlvViewHandler*		_viewHandler;
    IlvRegionOptimizer*		_regOptimizer;
    IlvNavigationInteractor*	_navigationInter;

private:
    enum {
	TMPDBLBUF = 0,
	KEEPRATIO = 1
    };
};

// --------------------------------------------------------------------------
// Manager Interactor Class Information
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerViewInteractorClassInfo
    : public IlvValuedClassInfo
{
public:
    static
    IlvManagerViewInteractorClassInfo* Create(const char*,
					      IlvClassInfo**,
					      IlvGetAccessorsFunction = 0);
protected:
    IlvManagerViewInteractorClassInfo(const char*             className,
				      IlvClassInfo**          superClass,
				      IlvGetAccessorsFunction ga = 0)
	: IlvValuedClassInfo(className, superClass, ga) {}
};


// --------------------------------------------------------------------------
// Manager Interactor
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerViewInteractor
    : public IlvStackInteractorInterface,
      public IlvValueInterface
{
public:
    IlvManagerViewInteractor()
    : _previous(0),
      _mgrview(0),
      _allowDrawGhost(IlTrue)
    {}
    IlvManagerViewInteractor(IlvManager* manager, IlvView* view);
    IlvManagerViewInteractor(IlvInputFile&);
    virtual ~IlvManagerViewInteractor();

    IlvDeclareLazyClassInfo();
    virtual void		write(IlvOutputFile&) const;

    // ____________________________________________________________
    virtual void		attach(IlvManager*, IlvView*);
    virtual void		detach();
    inline IlvMgrView*		managerView()    const { return _mgrview; }
    inline IlvTransformer*	getTransformer() const
	{ return _mgrview ? _mgrview->getTransformer() : 0; }
    inline IlvTransformer*	transformer() const
	{ return getTransformer(); }
    inline IlvView*		getView() const
	{ return _mgrview ? _mgrview->view() : 0; }
    inline IlvView*		view()    const { return getView(); }
    inline IlvManager*		getManager() const
	{ return _mgrview ? _mgrview->manager() : 0; }
    inline IlvManager*		manager() const { return getManager(); }
    inline IlvDisplay*		getDisplay() const
	{ return _mgrview ? _mgrview->view()->getDisplay() : 0; }
    virtual void		ensureVisible(const IlvPoint& point);
    IlvCursor*			getCursor() const;
    void			setCursor(IlvCursor*);
    virtual IlBoolean		handleEvent(IlvEvent& event) = 0;
    virtual void		handleExpose(IlvRegion* clip = 0);
    virtual void		drawGhost();
    virtual void		abort();
    virtual void		init();
    inline IlvManagerViewInteractor*	getPreviousInteractor() const
	{ return _previous; }
    inline void		setPreviousInteractor(IlvManagerViewInteractor* i)
	{ _previous = i; }
    void			callPrevious(IlvEvent* e = 0);
    inline void			setAllowDrawGhost(IlBoolean v)
	{ _allowDrawGhost = v; }
    inline IlBoolean		getAllowDrawGhost() const
	{ return _allowDrawGhost; }

    // IlvStackInteractorInterface ________________________________
    virtual IlvInteractor*	getCurrent() const;
    virtual void		push(IlvInteractor*);
    virtual void		pop();
    virtual IlvStackInteractorInterface*	getParent() const;
    virtual void		setParent(IlvStackInteractorInterface*);

protected:
    IlvManagerViewInteractor*	_previous;
    IlvMgrView*			_mgrview;
    IlBoolean			_allowDrawGhost;
    IlList			_interactors;
};


#define DeclareManagerViewInteractorInfoRO()			\
	IlvDeclareClassInfo();					\
	static IlvManagerViewInteractor* read(IlvInputFile&)

#define DeclareLazyManagerViewInteractorInfoRO()		\
	IlvDeclareLazyClassInfo();				\
	static IlvManagerViewInteractor* read(IlvInputFile&)

#define DeclareManagerViewInteractorInfo()			\
	DeclareManagerViewInteractorInfoRO();			\
	virtual void write(IlvOutputFile&) const

#define DeclareLazyManagerViewInteractorInfo()			\
	DeclareLazyManagerViewInteractorInfoRO();		\
	virtual void write(IlvOutputFile&) const

#define DeclareManagerViewInteractorIOConstructors(classname)	\
	public:							\
	classname(IlvInputFile&)

#define PredefinedManagerViewInteractorMembers(classname)	\
IlvManagerViewInteractor* classname::read(IlvInputFile& i)	\
{ return new classname(i); }					\
IlvPreRegisterClass(classname)					\

#define IlvPreRegisterManagerViewInteractorClass(classname)		\
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvRegisterManagerViewInteractorClass(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,					\
	IlvManagerViewInteractorClassInfo::Create(#classname,		\
						  superclass::ClassPtr()))

#define IlvRegisterManagerViewInteractorClassWithAccessors(classname,	\
							   superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,					\
	IlvManagerViewInteractorClassInfo::Create(#classname,		\
						  superclass::ClassPtr(), \
						  classname::GetAccessors))

#define IlvPostRegisterManagerViewInteractorClass(classname, superclass)\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	IlvManagerViewInteractorClassInfo::Create(#classname,		\
						  superclass::ClassPtr()))

#define IlvPostRegisterManagerViewInteractorClassWithAccessors(classname,\
							       superclass)\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	IlvManagerViewInteractorClassInfo::Create(#classname,		\
						  superclass::ClassPtr(), \
						  classname::GetAccessors))

ILVMGRMODULEINIT(m0_mgrview);

#endif /* !__Ilv_Manager_Mgrview_H */
