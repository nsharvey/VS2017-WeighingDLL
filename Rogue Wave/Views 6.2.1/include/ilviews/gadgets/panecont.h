// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/panecont.h
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
// Declaration of IlvPanedContainer class and related classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Panecont_H
#define __Ilv_Gadgets_Panecont_H

#if !defined(__Ilv_Gadgets_Gadcont_H)
#include <ilviews/gadgets/gadcont.h>
#endif
#if !defined(__Ilv_Graphics_Relfline_H)
#include <ilviews/graphics/relfline.h>
#endif
#if !defined(__Ilv_Base_Gadget_H)
#include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

#define IlvDefaultGraphicPaneMargin 2

class IlvPanedContainer;
class IlvSliderPane;
class IlvPaneListener;
class IlvViewPane;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvPane
{
public:

    IlvPane(const char* name);
    virtual ~IlvPane();

    // required virtual functions
    virtual const char*	getType() const = 0;
    virtual IlBoolean	isAViewPane() const;
    virtual IlBoolean	isAGraphicPane() const;
    virtual IlBoolean	isASlider() const;

    virtual void	setContainer(IlvPanedContainer* container);

    virtual void	hide();
    virtual void	show();

    virtual void	moveResize(const IlvRect& rect);

    virtual void	boundingBox(IlvRect& rect) const = 0;
    void		paneBBox(IlvRect& rect) const;

    virtual void	setFocus(IlvEvent* event = 0) = 0;

    virtual void	realizeVisibility() = 0;

    // optional virtual functions
    virtual IlvPane*	getPane(const char* name,
				IlBoolean recursive = IlFalse) const;

    // basic properties
    inline const char*	getName() const { return _name; }

    inline
    IlvPanedContainer*	getContainer() const { return _container; }

    inline IlBoolean	isVisible() const { return _visible; }

    void		setName(const char* name);

    IlvDim		getMinimumSize(IlvDirection direction) const;

    void		setMinimumSize(IlvDirection dir, IlvDim size);

    void		setMinimumSize(IlvDim size);

    // Elasticity
    enum ResizeMode {
	Fixed      = 1,
	Resizeable = 2, // For compatibility
	Resizable  = 2,
	Elastic    = 6
    };

     int		getResizeMode(IlvDirection direction) const;

    void		setResizeMode(IlvDirection direction, int mode);

    void		setResizeMode(int mode);

    // margins
    inline void		setMargin(IlUShort margin)
			{
			    _topMargin = _bottomMargin =
				_leftMargin = _rightMargin = margin;
			}

    inline IlUShort	getTopMargin() const { return _topMargin; }
    inline void		setTopMargin(IlUShort margin) { _topMargin = margin; }
    inline IlUShort	getRightMargin() const { return _rightMargin; }
    inline void		setRightMargin(IlUShort margin)
			{
			    _rightMargin = margin;
			}
    inline IlUShort	getBottomMargin() const { return _bottomMargin; }
    inline void		setBottomMargin(IlUShort margin)
			{
			    _bottomMargin = margin;
			}
    inline IlUShort	getLeftMargin() const { return _leftMargin; }
    inline void		setLeftMargin(IlUShort margin)
			{
			    _leftMargin = margin;
			}

    // Listeners
    void		addListener(IlvPaneListener* listener);
    void		removeListener(IlvPaneListener* listener);
    IlvPaneListener* const* getListeners(IlUInt& count) const;

protected:
    char*		_name;
    IlvPanedContainer*	_container;
    IlvDim		_minWidth;
    IlvDim		_minHeight;
    IlUShort		_topMargin;
    IlUShort		_rightMargin;
    IlUShort		_bottomMargin;
    IlUShort		_leftMargin;
    IlBoolean		_visible;
    int			_resizeHorMode;
    int			_resizeVerMode;
    IlvArray		_listeners;

    IlvDeclarePropertyListOwner(NamedPropertiesSymbol());

public:
    static
    const IlSymbol*	NamedPropertiesSymbol();

    IlvPos		getPosition(IlvDirection) const;
    IlvDim		getSize(IlvDirection) const;
}; // class IlvPane

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvPaneListener
{
    friend class IlvPane;

public:

    IlvPaneListener();
    virtual ~IlvPaneListener();

    inline IlvPane*	getPane() const { return _pane; }

    // Virtuals

    virtual void	paneNameChanged(const char* name);

    virtual void	paneGeometryChanged();

    virtual void	paneContainerChanged(IlvPanedContainer* container);

    virtual void	paneResizeModeChanged(IlvDirection dir, int mode);

    virtual void	paneVisibilityChanged();

    virtual void	paneMinimumSizeChanged(IlvDirection dir, IlvDim size);

protected:
    inline void		setPane(IlvPane* pane) { _pane = pane; }

    IlvPane*		_pane;
};

// --------------------------------------------------------------------------
typedef IlAny (*IlvApplyPane)(IlvPane* pane, IlAny arg);

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvPanedContainer : public IlvGadgetContainer
{
public:
    IlvPanedContainer(IlvDisplay*    display,
		      const char*    name,
		      const char*    title,
		      const IlvRect& rect,
		      IlvDirection   direction,
		      IlUInt         properties = 0,
		      IlBoolean      visible = IlTrue,
		      IlvSystemView  transientFor = 0);

    IlvPanedContainer(IlvAbstractView* parent,
		      const IlvRect&   rect,
		      IlvDirection     direction,
		      IlBoolean        visible = IlTrue);

    IlvPanedContainer(IlvDisplay*    display,
		      IlvSystemView  parent,
		      const IlvRect& rect,
		      IlvDirection   direction,
		      IlBoolean      visible = IlTrue);

    IlvPanedContainer(IlvDisplay*    display,
		      IlvSystemView  window,
		      IlvDirection   direction);

    virtual ~IlvPanedContainer();

    virtual void	resize(IlvDim w, IlvDim h);
    virtual void	moveResize(const IlvRect& rect);

    IlvViewPane*	getViewPane() const;

    IlvPane*		getPane(const char* name,
				IlBoolean all = IlFalse) const;

    inline IlvPane*	getPane(IlUInt index) const
			{
			    return (IlvPane*)_panes[index];
			}

    virtual void	addPane(IlvPane* pane, IlUInt index = (IlUInt)-1);

    virtual void	removePane(IlUInt index, IlBoolean destroy = IlFalse);

    inline IlUInt	getCardinal() const { return _panes.getLength(); }

    inline IlUInt	getIndex(const IlvPane* pane) const
			{
			    return _panes.getIndex((IlAny)pane);
			}

    inline IlvDirection	getDirection() const { return _direction; }

    inline void		setDirection(IlvDirection direction)
			{
			    _direction = direction;
			}

    virtual void	updatePanes(IlBoolean all = IlFalse);

    virtual void	paneVisibilityChanged(IlvPane* pane);

    virtual void	paneGeometryChanged(IlvPane* pane);
    virtual void	paneResizeModeChanged(IlvPane* pane,
					      IlvDirection direction,
					      int mode);
    inline IlBoolean	isManagingSliders() const { return _autoSliders; }

    inline void		manageSliders(IlBoolean value)
			{
			    _autoSliders = value;
			}

    IlUInt		pointToPane(const IlvPoint& point) const;

    void		paneBBox(const IlvPane* pane, IlvRect& bbox) const;

    IlAny		applyUntil(IlvApplyPane func, IlAny arg = 0);

protected:
    virtual void	iUpdatePanes();
    void		moveForward(IlUInt ndx, IlvPos delta);
    void		moveBackward(IlUInt ndx, IlvPos delta);
    void		getNewSizes(IlvDim*,
				    IlvPos delta,
				    IlBoolean elastic) const;
    void		recomputeSliders();

    virtual
    IlvSliderPane*	createSliderPane(const char*) const;

    inline void		setUpdating(IlBoolean val = IlTrue)
			{
			    _updating = val;
			}
    inline void		setMovingPane(IlBoolean val = IlTrue)
			{
			    _movingPane = val;
			}

    IlvArray		_panes;
    IlvDirection	_direction;
    IlBoolean		_invalidated;
    IlBoolean		_autoSliders;
    IlBoolean		_updating;
    IlBoolean		_movingPane;
    IlvDim		_oldWidth;
    IlvDim		_oldHeight;
    IlInt		_previousAvailableSpace;

    DeclareViewProperties();

public:
    IlvDim		getAvailableSpace(IlUInt from,
					  IlUInt to,
					  IlBoolean elastic) const;
    virtual void	movePane(IlvPane*, IlvPos);
    void		invalidatePane(const IlvPane*);
    IlvPos		getPosition(const IlvPane*) const;
    IlvDim		getSize(const IlvPane*,
				IlvDirection = IlvBadPosition) const;
    void		doMoveResize(IlvPane*, const IlvRect&);
    virtual void	handleResize(IlvRect&);
    inline
    const IlvArray&	getPanes() const { return _panes; }
    inline IlBoolean	isUpdating() const { return _updating; }
    inline IlBoolean	isMovingPane() const { return _movingPane; }
    inline IlBoolean	isInvalidated() const { return _invalidated; }
    inline void		invalidate(IlBoolean val = IlTrue)
			{
			    _invalidated = val;
			}
    IlUInt		getPreviousPaneIndex(IlUInt ndx, int mode = -1) const;
    IlUInt		getNextPaneIndex(IlUInt ndx, int mode = -1) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvViewPane : public IlvPane
{
public:

    IlvViewPane(const char* name, IlvView* view, IlBoolean owner = IlTrue);

    virtual ~IlvViewPane();

    virtual const char*	getType() const;
    virtual IlBoolean	isAViewPane() const;
    virtual void	setContainer(IlvPanedContainer* cont);
    virtual void	moveResize(const IlvRect&);
    virtual void	boundingBox(IlvRect&) const;
    virtual void	realizeVisibility();
    virtual IlvPane*	getPane(const char*, IlBoolean = IlFalse) const;
    virtual void	setFocus(IlvEvent* event = 0);

    inline IlvView*	getView() const { return _view; }
    void		setView(IlvView* view, IlBoolean owner = IlTrue);
    virtual void	viewDeleted();
    static IlvViewPane*	Get(const IlvView* view);

protected:
    IlvView*		_view;
    IlBoolean		_owner;

    static void		Set(IlvView* view, IlvViewPane* pane);
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvGraphicPane : public IlvPane
{
public:

    IlvGraphicPane(const char* name,
		   IlvGraphic* graphic,
		   IlUShort    margin = IlvDefaultGraphicPaneMargin,
		   IlBoolean   owner = IlTrue);

    virtual ~IlvGraphicPane();

    virtual const char*	getType() const;
    virtual IlBoolean	isAGraphicPane() const;
    virtual void	setContainer(IlvPanedContainer* cont);
    virtual void	moveResize(const IlvRect&);
    virtual void	boundingBox(IlvRect&) const;
    virtual void	setFocus(IlvEvent* event = 0);
    virtual void	realizeVisibility();
    virtual void	objectDeleted();

    virtual void	setDoubleBuffering(IlBoolean value);

    inline IlBoolean	isDoubleBuffering() const { return _doubleBuffering; }

    inline IlvGraphic*	getObject() const { return _object; }

    void		setObject(IlvGraphic* obj, IlBoolean owner = IlTrue);

protected:
    IlvGraphic*		_object;
    IlBoolean		_owner;
    IlBoolean		_doubleBuffering;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvBBoxedGraphicPane : public IlvGraphicPane
{
public:
    IlvBBoxedGraphicPane(const char* name,
			 IlvGraphic* obj,
			 IlUShort    margin = IlvDefaultGraphicPaneMargin,
			 IlBoolean   owner = IlTrue);

    virtual void	moveResize(const IlvRect&);
    virtual void	boundingBox(IlvRect&) const;

protected:
    IlvRect		_bbox;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvSeparatorPane : public IlvGraphicPane
{
public:

    IlvSeparatorPane(const char* name,
		     IlvDisplay* display,
		     IlvDirection direction = IlvHorizontal,
		     IlvPalette* palette = 0);

};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvSliderPane : public IlvGraphicPane
{
public:

    IlvSliderPane(const char* name, IlvDisplay* display);

    virtual const char*	getType() const;
    virtual IlBoolean	isASlider() const;
    virtual void	movePane(IlvPos);

    static IlBoolean	_DragGhost;
};

ILVADVGDTMODULEINIT(panecont);

#endif /* !__Ilv_Gadgets_Panecont_H */
