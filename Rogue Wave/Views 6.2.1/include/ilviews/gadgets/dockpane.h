// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/dockpane.h
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
// Declaration of IlvDockablePanedContainer class and retative classes
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Dockpane_H
#define __Ilv_Gadgets_Dockpane_H

#ifndef __Ilv_Gadgets_Panecont_H
#include <ilviews/gadgets/panecont.h>
#endif
#ifndef __Ilv_Gadgets_Toolbar_H
#include <ilviews/gadgets/toolbar.h>
#endif
#if !defined(__Ilv_Gadgets_Arrowb_H)
#include <ilviews/gadgets/arrowb.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

class IlvDockable;
class IlvDockingHandlePane;
class IlvDockingHandleTitleBar;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockableLFHandler : public IlvObjectLFHandler
{
public:
    IlvDockableLFHandler(IlvLookFeelHandler* lfh);
    // ____________________________________________________________
    virtual void	drawGripper(const IlvDockingHandlePane* handle,
				    const IlvGadget* gadget,
				    IlvPort* dst,
				    const IlvRect& rect,
				    IlvDirection direction,
				    const IlvRegion* clip) const = 0;
    virtual void	drawSmallCaption(const IlvDockingHandlePane* handle,
					 const IlvGadget* gadget,
					 IlvPort* dst,
					 const IlvRect& rect,
					 IlvDirection direction,
					 const IlvRegion* clip) const = 0;
    virtual void	drawHideButton(const IlvDockingHandlePane* handle,
				       const IlvButton* button,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawExpandContractButton(const IlvDockingHandlePane*,
						 const IlvArrowButton* button,
						 IlvPort* dst,
						 const IlvTransformer* t,
						 const IlvRegion*) const = 0;
    virtual IlvDim	getHandleSize(IlBoolean) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultDockableLFHandler
    : public IlvDockableLFHandler
{
public:
    IlvDefaultDockableLFHandler(IlvLookFeelHandler* lfh)
	: IlvDockableLFHandler(lfh)  {}
    // ____________________________________________________________
    virtual void	drawGripper(const IlvDockingHandlePane* handle,
				    const IlvGadget* gadget,
				    IlvPort* dst,
				    const IlvRect& rect,
				    IlvDirection direction,
				    const IlvRegion* clip) const;
    virtual void	drawSmallCaption(const IlvDockingHandlePane* handle,
					 const IlvGadget* gadget,
					 IlvPort* dst,
					 const IlvRect& rect,
					 IlvDirection direction,
					 const IlvRegion* clip) const;
    virtual void	drawHideButton(const IlvDockingHandlePane* handle,
				       const IlvButton* button,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const;
    virtual void	drawExpandContractButton(const IlvDockingHandlePane*,
						 const IlvArrowButton* button,
						 IlvPort* dst,
						 const IlvTransformer* t,
						 const IlvRegion* clip) const;
    virtual IlvDim	getHandleSize(IlBoolean) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockableContainer : public IlvPanedContainer
{
public:
    IlvDockableContainer(IlvDisplay*      display,
			 const char*      name,
			 const char*      title,
			 const IlvRect&   rect,
			 IlvDirection     direction,
			 IlUInt           properties = 0,
			 IlBoolean        visible = IlTrue,
			 IlvSystemView    transientFor = 0);
    IlvDockableContainer(IlvAbstractView* parent,
			 const IlvRect&   rect,
			 IlvDirection     direction,
			 IlBoolean        visible = IlTrue);

    IlvDockableContainer(IlvDisplay*      display,
			 IlvSystemView    parent,
			 const IlvRect&   rect,
			 IlvDirection     direction,
			 IlBoolean        visible = IlTrue);

    IlvDockableContainer(IlvDisplay*      display,
			 IlvSystemView    window,
			 IlvDirection     direction);

    ~IlvDockableContainer();
    // ______________________________________________________________________

    IlBoolean		isDockable() const { return _dockable; }

    void		setDockable(IlBoolean enable) { _dockable = enable; }

    IlBoolean		createOrthogonalDockableContainer() const
			{
			    return _createOrthogonalDockableContainer;
			}

    void		createOrthogonalDockableContainer(IlBoolean enable)
			{
			    _createOrthogonalDockableContainer = enable;
			}

    IlvPane* const*	getDockingPanes(IlUInt& count,
					IlBoolean visible = IlTrue,
					int mode = -1) const;

    IlvPane* const*	getAllDockingPanes(IlUInt& count,
					   IlBoolean visible = IlTrue,
					   int mode = -1) const;

    virtual IlBoolean	acceptDocking(const IlvPane* pane,
				      IlUInt index) const;

    IlvDockable*	addDockingPane(IlvPane* pane,
				       IlUInt index = (IlUInt)-1);

    virtual IlvDockable*	createDockable(IlvPane* pane) const;

protected:
    DeclareLazyViewProperties();

    IlBoolean		_dockable;
    IlBoolean		_createOrthogonalDockableContainer;
    IlvDockable*	_draggedDockable;

    virtual void	iUpdatePanes();
    void		updateDockingHandlePanes();

public:
    virtual void	changeLook();
    virtual IlBoolean	dispatchToObjects(IlvEvent& event);
    static
    IlvDockableContainer* GetDockableContainer(const IlvAbstractView*);
    virtual IlBoolean	isDecoration(const IlvPane* pane) const;
    virtual void	removePane(IlUInt rank,
				   IlBoolean destroy = IlFalse);
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockable
{
public:

    IlvDockable(IlvPane* pane = 0);

    virtual ~IlvDockable();

    // ______________________________________________________________________

    IlvPane*		getPane() const { return _pane; }

    void		setPane(IlvPane* pane) { _pane = pane; }

    static IlvDockable*	GetDockable(const IlvPane* pane);

    static void		SetDockable(IlvPane* pane, IlvDockable* dockable);

    const char*		getTitle() const { return _title; }

    void		setTitle(const char* title);

    IlBoolean		isDocked() const { return _docked; }

    virtual void	dock(IlvDockableContainer* container,
			     IlUInt index,
			     const IlvRect& rect);

    virtual
    IlvPanedContainer*	unDock(const IlvRect& rect,
			       IlBoolean show = IlTrue);

    virtual IlBoolean	acceptDocking(const IlvDockableContainer* container,
				      IlUInt index) const;

    IlvDirection	getDockingDirection() const
			{
			    return _dockingDirection;
			}

    void		setDockingDirection(IlvDirection direction)
			{
			    _dockingDirection = direction;
			}

protected:
    IlBoolean		_dragging;
    IlBoolean		_docked;
    IlvPoint		_buttonDownPoint;
    IlvRect		_dockedHorRect;
    IlvRect		_dockedVerRect;
    IlvRect		_topRect;
    IlvRect		_draggedRect;
    IlvPane*		_pane;
    IlvPane*		_dockingMark;
    IlvDockableContainer*    _destinationContainer;
    IlInt		_destinationIndex;
    IlBoolean		_preventDocking;
    IlBoolean		_defaultButtons;
    IlvDirection	_dockingDirection;
    char*		_title;

public:
    IlvDisplay*		getDisplay() const
			{
			    return _pane->getContainer()->getDisplay();
			}
    IlBoolean		hasDefaultButtons() const { return _defaultButtons; }
    void		useDefaultButtons(IlBoolean b) { _defaultButtons = b; }
    virtual void	dockingContainerDeleted();
    const IlvRect&	getTopRect() const { return _topRect; }
    void		setTopRect(const IlvRect& rect) { _topRect = rect; }
    const IlvRect&	getDockedRect(IlvDirection dir) const;
    void		setDockedRect(IlvDirection dir, const IlvRect&);
    void		removeDockingArea();
    void		getDockingArea(IlvDockableContainer*& cont,
				       IlUInt& index) const;
    void		setDockingArea(IlvDockableContainer* cont,
				       IlUInt index);
    void		setDocked(IlBoolean b) { _docked = b; }
    void		getDockableBBox(IlvRect&) const;
    void		updateRects();

    // Interactor members
    virtual void	destroy();
    virtual IlBoolean	handleEvent(IlvEvent& event);
    IlBoolean		isDragging() const { return _dragging; }
    virtual void	beginDrag(const IlvPoint&);
    virtual void	drag(const IlvPoint&);
    virtual void	endDrag();
    virtual void	restoreFocus(IlvEvent&);
    virtual void	doIt(const IlvPoint&);
    virtual void	drawGhost(const IlvRect&);
    virtual void	getDockingLocation(const IlvPoint&,
					   IlvDockableContainer*&,
					   IlInt&,
					   IlvAbstractView* = 0) const;
    virtual void	getDockingRect(const IlvDockableContainer*,
				       IlUInt,
				       IlvRect&) const;
    virtual
    IlvPanedContainer*	createUndockedContainer(IlvDisplay* display,
						IlvPane* pane,
						const IlvRect& rect,
						IlvDirection dir,
						IlvSystemView = 0) const;
    virtual
    IlvDockingHandlePane* createDockingHandlePane() const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockingHandleTitleBarFactory
{
public:
    virtual ~IlvDockingHandleTitleBarFactory() {}
    virtual IlvDockingHandleTitleBar*
			createTitleBar(IlvDisplay* display,
				       IlvDockingHandlePane*     pane,
				       IlvDirection dir,
				       IlBoolean smallSize = IlFalse) = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockingHandlePane : public IlvGraphicPane
{
public:
    IlvDockingHandlePane(IlvPane*,
			 IlBoolean defaultButtons = IlTrue);
    ~IlvDockingHandlePane();
    // ______________________________________________________________________
    virtual const char*	getType() const;
    IlvDockable*	getDockable() const;
    IlvPane*		getDockingPane() const { return _pane; }
    void		setDockingPane(IlvPane* pane);
    IlBoolean		isExpanded() const { return _expanded; }
    virtual void	expand();
    virtual void	contract();
    virtual void	destroy();

protected:
    IlBoolean		_expanded;
    IlvPane*		_pane;
    IlvPaneListener*	_paneListener;
    IlvDockingHandleTitleBar* _titleBar;

    static IlvDockingHandleTitleBarFactory* _SmallFactory;
    static IlvDockingHandleTitleBarFactory* _DefaultFactory;

public:
    void		setExpanded(IlBoolean);
    virtual void	moveResize(const IlvRect&);
    virtual void	updateExpandContractButton();
    virtual void	titleChanged();
    virtual void	lookChanged();
    static void		UseTitledHandlePanes(IlBoolean smallSize);
    static void		UseDefaultHandlePanes(IlBoolean smallSize);
    static void		UseCustomHandlePanes(IlBoolean smallSize,
				IlvDockingHandleTitleBarFactory* factory);
    static IlvDockingHandlePane*
			GetDockingHandlePane(const IlvPane*);
    static void              SetDockingHandlePane(IlvPane*,
						  IlvDockingHandlePane*);
    static IlvDim	DefaultSize;
    static IlvDim	SmallSize;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockingHandleTitleBar
{
public:
    IlvDockingHandleTitleBar(IlvDockingHandlePane*     pane,
			     IlvDirection              dir,
			     IlBoolean                 smallSize = IlFalse);
    virtual ~IlvDockingHandleTitleBar() {}
    IlvDockingHandlePane*	getPane() const { return _pane; }
    IlvDockable*	getDockable() const {return _pane->getDockable();}
    IlvDirection	getDirection() const { return _direction; }
    IlBoolean		hasSmallSize() const { return _smallSize; }
    virtual IlvGraphic* getGraphic() const = 0;
    virtual void	titleChanged();
    virtual void	initialize();
    virtual void	updateExpandContractButton();

protected:
    IlvDockingHandlePane*    _pane;
    IlvDirection	_direction;
    IlBoolean		_smallSize;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDockingHandleToolBar : public IlvToolBar
{
public:
    IlvDockingHandleToolBar(IlvDisplay*			display,
			    IlvDockingHandlePane*	pane,
			    IlvDirection		dir,
			    IlvDim			size,
			    IlvPalette*			palette  = 0);
    // ______________________________________________________________________
    virtual void	internalBBox(IlvRect& rect,
				     const IlvTransformer* t) const;
    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t,
			     const IlvRegion* clip) const;
    IlvDirection	getFlushingDirection() const;
    void		setFlushingDirection(IlvDirection direction);

protected:
    IlBoolean		_topOrLeft;
    IlvDockingHandlePane* _pane;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvTitledDockingHandleToolBar : public IlvToolBar
{
public:
    IlvTitledDockingHandleToolBar(IlvDisplay*		display,
				  IlvDockingHandlePane*	pane,
				  IlvDirection		dir,
				  IlvDim		size,
				  IlvPalette*		palette  = 0);
    virtual void	drawBackground(IlvPort* dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
protected:
    IlBoolean		_defaultPalette;
    IlvDockingHandlePane* _pane;

    virtual void	updateLook();
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvUndockedTopContainer : public IlvPanedContainer
{
public:
    IlvUndockedTopContainer(IlvDisplay*    display,
			    IlvPane*       pane,
			    const IlvRect& rect,
			    IlvDirection   direction,
			    IlUInt         properties = 0,
			    IlvSystemView  transientFor = 0);
    ~IlvUndockedTopContainer();

    void		setPane(IlvPane* pane);
    virtual IlBoolean	dispatchToObjects(IlvEvent& event);
    virtual void	paneVisibilityChanged(IlvPane*);
    virtual void	removePane(IlUInt rank, IlBoolean = IlFalse);
    virtual void	destroy();
    IlvDockable*	getDockable() const;
    IlvPane*		getDockingPane() const { return _pane; }
    IlBoolean		isDragging() const
			{
			    return getDockable()->isDragging();
			}
    void		beginDrag(const IlvPoint&);
    void		drag(const IlvPoint&);
    void		endDrag(const IlvPoint&);
    void		dock(const IlvPoint& point);
    void		dock();
    void		checkGeometry();

    DeclareLazyViewProperties();

protected:
    IlvPane*		_pane;

    void		initUndockedTopContainer();
    virtual void	iUpdatePanes();
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvAbstractBarPane : public IlvGraphicPane
{
public:

    IlvAbstractBarPane(const char* name, IlvAbstractBar* bar);

    ~IlvAbstractBarPane();

    virtual const char*	getType() const;
    IlvAbstractBar*	getBar() const {return (IlvAbstractBar*)_object;}
    IlvDirection	getOrientation() const
			{
			    return getBar()->getOrientation();
			}
    void		setOrientation(IlvDirection dir);
    void		checkOrientation(const IlvRect&);
    void		updateResizeMode();
    virtual void	moveResize(const IlvRect&);
    virtual void	setContainer(IlvPanedContainer*);

    virtual void	orientationChanged();

    virtual void	geometryChanged();
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvAbstractBarDockable : public IlvDockable
{
public:
    IlvAbstractBarDockable(IlvAbstractBarPane* pane = 0);

    IlvAbstractBarPane*	getBarPane() const
			{
			    return (IlvAbstractBarPane*)getPane();
			}
    virtual void	dock(IlvDockableContainer*,
			     IlUInt,
			     const IlvRect&);
    virtual
    IlvPanedContainer*	unDock(const IlvRect&, IlBoolean = IlTrue);
    virtual
    IlvPanedContainer*	createUndockedContainer(IlvDisplay* display,
						IlvPane* pane,
						const IlvRect& rect,
						IlvDirection dir,
						IlvSystemView tr) const;
    virtual void	beginDrag(const IlvPoint& point);
    virtual IlBoolean	acceptDocking(const IlvDockableContainer* cont,
				      IlUInt index) const;
    virtual void	getDockingLocation(const IlvPoint&,
					   IlvDockableContainer*&,
					   IlInt&,
					   IlvAbstractView* = 0) const;
    virtual void	getDockingRect(const IlvDockableContainer* cont,
				       IlUInt i,
				       IlvRect& rect) const;
    IlBoolean		getConstraintMode() const
			{
			    return _constraintMode;
			}
    void		setConstraintMode(IlBoolean mode)
			{
			    _constraintMode = mode;
			}
protected:
    IlBoolean		_constraintMode;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(dockpane);
#if defined(ILVWINDOWSXPLOOK)
#include <ilviews/gadgets/winxp/dockpane.h>
#endif
#endif /* !__Ilv_Gadgets_Dockpane_H */
