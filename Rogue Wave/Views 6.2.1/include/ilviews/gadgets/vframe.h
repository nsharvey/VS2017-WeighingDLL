// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/vframe.h
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
// Declaration of IlvViewFrame class
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Vframe_H
#define __Ilv_Gadgets_Vframe_H

#if !defined(__Ilv_Gadgets_Gadcont_H)
#  include <ilviews/gadgets/gadcont.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#  include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Menu_H)
#  include <ilviews/gadgets/menu.h>
#endif
#if !defined(__Ilv_Gadgets_Toolbar_H)
#  include <ilviews/gadgets/toolbar.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#  include <ilviews/gadgets/macrosadv.h>
#endif

class IlvDesktopManager;
class IlvViewFrameIcon;
class IlvViewFrame;
class IlvViewFrameButtons;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvViewFrameLFHandler
    : public IlvObjectLFHandler
{
public:
    IlvViewFrameLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawFrame(const IlvViewFrame* vframe,
				  const IlvGadget* gadget,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawTitle(const IlvViewFrame* vframe,
				  const IlvMessageLabel* gadget,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawCaption(const IlvViewFrame* vframe,
				    const IlvMessageLabel* gadget,
				    IlvPort* dst,
				    const IlvTransformer* t,
				    const IlvRegion* clip) const = 0;
    virtual void	drawIcon(const IlvViewFrame* vframe,
				 const IlvMessageLabel* gadget,
				 IlvPort* dst,
				 const IlvTransformer* t,
				 const IlvRegion* clip) const = 0;
    virtual void	drawMinimizeButton(const IlvViewFrame* vframe,
					   const IlvButton* button,
					   IlvPort* dst,
					   const IlvTransformer* t,
					   const IlvRegion* clip) const = 0;
    virtual void	drawMaximizeButton(const IlvViewFrame* vframe,
					   const IlvButton* button,
					   IlvPort* dst,
					   const IlvTransformer* t,
					   const IlvRegion* clip) const = 0;
    virtual void	drawRestoreButton(const IlvViewFrame* vframe,
					  const IlvButton* button,
					  IlvPort* dst,
					  const IlvTransformer* t,
					  const IlvRegion* clip) const = 0;
    virtual void	drawCloseButton(const IlvViewFrame* vframe,
					const IlvButton* button,
					IlvPort* dst,
					const IlvTransformer* t,
					const IlvRegion* clip) const = 0;
    virtual IlvDim	getTitleBarHeight(IlBoolean minimized) const = 0;
    virtual IlvDim	getBorderSize(IlBoolean minimized) const = 0;
    virtual void	updateLook(const IlvViewFrameButtons*) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultViewFrameLFHandler
    : public IlvViewFrameLFHandler
{
public:
    IlvDefaultViewFrameLFHandler(IlvLookFeelHandler* lfh)
	: IlvViewFrameLFHandler(lfh)
    {}

    virtual void	drawFrame(const IlvViewFrame*,
				  const IlvGadget*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawTitle(const IlvViewFrame*,
				  const IlvMessageLabel*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawCaption(const IlvViewFrame*,
				    const IlvMessageLabel*,
				    IlvPort*,
				    const IlvTransformer*,
				    const IlvRegion*) const;
    virtual void	drawIcon(const IlvViewFrame*,
				 const IlvMessageLabel*,
				 IlvPort*,
				 const IlvTransformer*,
				 const IlvRegion*) const;
    virtual void	drawMinimizeButton(const IlvViewFrame*,
					   const IlvButton*,
					   IlvPort*,
					   const IlvTransformer*,
					   const IlvRegion*) const;
    virtual void	drawMaximizeButton(const IlvViewFrame*,
					   const IlvButton*,
					   IlvPort*,
					   const IlvTransformer*,
					   const IlvRegion*) const;
    virtual void	drawRestoreButton(const IlvViewFrame*,
					  const IlvButton*,
					  IlvPort*,
					  const IlvTransformer*,
					  const IlvRegion*) const;
    virtual void	drawCloseButton(const IlvViewFrame*,
					const IlvButton*,
					IlvPort*,
					const IlvTransformer*,
					const IlvRegion*) const;
    virtual IlvDim	getTitleBarHeight(IlBoolean) const;
    virtual IlvDim	getBorderSize(IlBoolean) const;
    virtual void	updateLook(const IlvViewFrameButtons*) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvViewFrameButtons
    : public IlvToolBar
{
public:
    IlvViewFrameButtons(IlvDisplay*);
    IlvViewFrameButtons(IlvViewFrame*);

    IlvButton*		getMinimizeButton() const;
    IlvButton*		getMaximizeButton() const;
    IlvButton*		getRestoreButton() const;
    IlvButton*		getCloseButton() const;
    void		updateButtons();
    virtual void	closeFrame();
    virtual void	minimizeFrame();
    virtual void	maximizeFrame();
    virtual void	restoreFrame();
    inline
    IlvViewFrame*	getFrame() const { return _frame; }
    inline void		setFrame(IlvViewFrame* frame) { _frame = frame; }
    virtual void	updateLook();

    IlvButton*		insertButton(const char*, IlvBitmap* = 0);
    virtual void	internalBBox(IlvRect&, const IlvTransformer*) const;
    virtual IlUShort	getHMargin() const;
    virtual IlUShort	getVMargin() const;

protected:
    IlvViewFrame*	_frame;

    void		initButtons();
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvViewFrame
    : public IlvGadgetContainer
{
public:

    IlvViewFrame(IlvView*	parent,
		 const char*	title,
		 const IlvRect&	size,
		 IlBoolean	visible = IlTrue);
    virtual ~IlvViewFrame();

    // Geometry
    enum IlvFrameState {
	IlvFrameNormalState = 0,
	IlvFrameMinimizedState,
	IlvFrameMaximizedState
    };

    // Basic properties
    const char*		getTitle() const;
    virtual void	setTitle(const char* title);

    IlvBitmap*		getIcon() const;
    void		setIcon(IlvBitmap* bitmap);

    // Client
    IlvView*		getClient() const;
    virtual void	getClientBBox(IlvRect& bbox) const;
    void		getTitleBarBBox(IlvRect& bbox) const;

    virtual void	restoreFrame();
    virtual void	minimizeFrame();
    virtual void	maximizeFrame();
    virtual void	closeFrame();

    IlvPopupMenu*	getMenu() const;
    void		showMenu(const IlvPoint& point);

    int			getCurrentState() const;

    IlvDesktopManager*	getDesktopManager() const;
    void		setDesktopManager(IlvDesktopManager* desk);

    IlvDim		getMinWidth() const;
    void		setMinWidth(IlvDim size);
    IlvDim		getMinHeight() const;
    void		setMinHeight(IlvDim size);

    static IlBoolean	IsShowingContentsWhileDragging();
    static void		ShowContentsWhileDragging(IlBoolean value);

    void		registerClientView(IlvView* view) const;
    void		unRegisterClientView(IlvView* view) const;

    // IlvContainer overloads
    virtual void	handleInput(IlvEvent&);
    virtual void	resize(IlvDim, IlvDim);
    virtual void	moveResize(const IlvRect&);
    // IlvAbstractView overloads
    virtual void	childNotifyAdd(IlvAbstractView*);

    virtual void	adjustClientSize();
    virtual void	fitToClient();
    virtual void	handleClientEvent(IlvEvent&);
    virtual IlBoolean	handleTitleBarEvent(IlvEvent&);
    IlBoolean		isTitleHighlighted() const;
    void		highlightTitle();
    void		unhighlightTitle();

    DeclareViewAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

protected:

    virtual void	updateTitleBar();
    virtual IlvCursor*	getCursor(int area);
    virtual void	drawGhost(const IlvRect&);
    virtual void	moved(const IlvRect&, const IlvRect&);
    virtual void	resized(const IlvRect&, const IlvRect&);
    virtual IlvPopupMenu* createMenu() const;

    DeclareViewProperties();

public:
    static IlUShort	GetDefaultTitleBarHeight();
    static void		SetDefaultTitleBarHeight(IlUShort);
    static IlUShort	GetDefaultBorderThickness();
    static void		SetDefaultBorderThickness(IlUShort val);
    static IlSymbol*	RestoreItemSymbol();
    static IlSymbol*	MinimizeItemSymbol();
    static IlSymbol*	MaximizeItemSymbol();
    static IlSymbol*	CloseItemSymbol();

    IlvButton*		getCloseButton() const;
    IlvButton*		getMinimizeButton() const;
    IlvButton*		getMaximizeButton() const;
    IlvButton*		getRestoreButton() const;

    virtual void	clientDeleted();
    virtual void	frameSelected();
    virtual void	frameDeselected();
    virtual void	frameRestored();
    virtual void	frameMinimized();
    virtual void	frameMaximized();
    IlUShort		getTitleBarHeight() const;
    IlUShort		getBorderThickness() const;
    virtual void	changeLook();
    virtual void	changeLanguage();
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    IlvPoint*		getMinimizedLocation() const;
    void		resetMinimizedLocation();
    IlBoolean		isDispatchingFocusIn() const;
    void		dispatchFocusIn(IlBoolean = IlTrue);

    struct P;
    struct P*		_p;

    friend class IlvViewFrameIcon;
    friend class IlvViewFrameButtons;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvViewFrameIcon
    : public IlvMessageLabel
{
public:
    IlvViewFrameIcon(IlvViewFrame*, IlvBitmap* = 0);
    IlvViewFrameIcon(IlvDisplay*);

    virtual IlBoolean	handleEvent(IlvEvent&);
    virtual void	showMenu();
    virtual void	closeFrame();
    virtual IlvOrientation getPopupMenuOrientation() const;
    inline IlvViewFrame* getFrame() const { return _frame; }
    inline void		 setFrame(IlvViewFrame* frame) { _frame = frame; }

protected:
    IlvViewFrame*	_frame;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(vframe);
#if defined(ILVMOTIFLOOK)
#  include <ilviews/gadgets/motif/vframe.h>
#endif
#if defined(ILVWINDOWS95LOOK)
#  include <ilviews/gadgets/win95/vframe.h>
#endif
#if defined(ILVWINDOWSXPLOOK)
#  include <ilviews/gadgets/winxp/vframe.h>
#endif
#if defined(ILVVXLOOK)
#  include <ilviews/gadgets/vx/vframe.h>
#endif
#endif /* !__Ilv_Gadgets_Vframe_H */
