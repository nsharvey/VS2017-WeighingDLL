// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/menu.h
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
// Declaration of the IlvPopupMenu class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Menu_H
#define __Ilv_Gadgets_Menu_H

#ifndef __Ilv_Gadgets_Amenu_H
#  include <ilviews/gadgets/amenu.h>
#endif
#ifndef __Ilv_Contain_Contain_H
#  include <ilviews/contain/contain.h>
#endif
#include <string.h>

class IlvPopupMenu;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvPopupMenuLFHandler : public IlvObjectLFHandler
{
public:
    IlvPopupMenuLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawGadgetItem(const IlvPopupMenu* menu,
				       const IlvMenuItem* item,
				       IlvPort* dst,
				       const IlvRect& rect,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvPopupMenu* menu,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip, 
				  IlBoolean drawRelief = IlTrue) const = 0;
    virtual void	drawBackground(const IlvPopupMenu* menu,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip,
				       IlBoolean drawRelief = IlTrue) const=0;
    virtual void	drawContents(const IlvPopupMenu* menu,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip, 
				     IlBoolean drawRelief = IlTrue) const = 0;
    virtual void	drawSelection(const IlvPopupMenu* menu,
				      IlvPort* dst,
				      const IlvRect& rect,
				      const IlvMenuItem* item,
				      const IlvTransformer* t,
				      const IlvRegion* clip) const = 0;
    virtual void	itemBBox(const IlvPopupMenu*,
				 IlUShort,
				 IlvRect&,
				 const IlvTransformer*) const = 0;
    virtual void	getInternalBBox(const IlvPopupMenu*,
					IlvRect&) const = 0;
    virtual void	sizes(const IlvPopupMenu*, IlvDim&, IlvDim&) const = 0;
    virtual void	setSelectionCursor(const IlvPopupMenu*,
					   IlvContainer*) = 0;
    virtual IlBoolean	escapeKeyDown(IlvPopupMenu*, IlvEvent&) const = 0;
    virtual IlBoolean	F10KeyDown(IlvPopupMenu*, IlvEvent&) const = 0;
    virtual
    IlvDirection	subMenuShowPoint(IlvPopupMenu*,
					 IlShort,
					 IlvPoint&) const = 0;
    virtual IlvDim	getDefaultLabelOffset(const IlvPopupMenu*) const = 0;
    virtual int		getMapDelay() const = 0;
    virtual int		getUnMapDelay() const = 0;
    virtual IlvColor*	getBackground(const IlvPopupMenu*) const = 0;

    virtual void	setMode(IlvPopupMenu*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvPopupMenu*, IlBoolean) const= 0;
    virtual IlBoolean	allowSelectWithMove() const = 0;
    virtual
    IlvDirection	getAcceleratorAlignment() const = 0;
    virtual IlUShort	getHMargin() const = 0;
    virtual IlUShort	getVMargin() const = 0;
    virtual IlBoolean	handleEvent(IlvPopupMenu*	menu,
				    IlvEvent&		event) const = 0;
    virtual void	getPreferredSize(const IlvPopupMenu*,
					 IlvDim& w,
					 IlvDim& h) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultPopupMenuLFHandler
    : public IlvPopupMenuLFHandler
{
public:
    IlvDefaultPopupMenuLFHandler(IlvLookFeelHandler* lf)
	: IlvPopupMenuLFHandler(lf)
    {}

    virtual void	drawGadgetItem(const IlvPopupMenu*,
				       const IlvMenuItem*,
				       IlvPort* port,
				       const IlvRect& rect,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const;
    virtual void	drawFrame(const IlvPopupMenu*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*, 
				  IlBoolean drawRelief = IlTrue) const;
    virtual void	drawBackground(const IlvPopupMenu*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*,
				       IlBoolean drawRelief = IlTrue) const;
    virtual void	setSelectionCursor(const IlvPopupMenu*, IlvContainer*);
    virtual IlBoolean	escapeKeyDown(IlvPopupMenu*, IlvEvent&) const;
    virtual IlBoolean	F10KeyDown(IlvPopupMenu*, IlvEvent&) const;
    virtual int		getMapDelay() const;
    virtual int		getUnMapDelay() const;
    virtual IlvColor*	getBackground(const IlvPopupMenu*) const;
    virtual void	setMode(IlvPopupMenu*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvPopupMenu*, IlBoolean) const; 
    virtual IlBoolean	allowSelectWithMove() const;
    virtual
    IlvDirection	getAcceleratorAlignment() const;
    virtual IlUShort	getHMargin() const;
    virtual IlUShort	getVMargin() const;
    virtual IlBoolean	handleEvent(IlvPopupMenu*, IlvEvent& event) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvPopupMenu : public IlvAbstractMenu
{
    friend class IlvDefaultPopupMenuLFHandler;
public:

    IlvPopupMenu(IlvDisplay*        display,
		 IlUShort           count     = 0,
		 const char* const* labels    = 0,
		 IlUShort           thickness = IlvDefaultGadgetThickness,
		 IlvPalette*        palette   = 0);

    IlvPopupMenu(IlvDisplay*  display,
		 IlUShort     count,
		 IlvMenuItem* items,
		 IlUShort     thickness = IlvDefaultGadgetThickness,
		 IlvPalette*  palette   = 0);

    ~IlvPopupMenu();

    virtual void	show(const IlvPoint& point,
			     IlBoolean grab = IlTrue,
			     IlvView* parent = 0);

    IlShort		get(const IlvPoint& point, IlvView* parent = 0);

    virtual void	hide();

    inline IlBoolean	isVisible() const { return _visible; }

    virtual IlBoolean	isGrabbed() const;

    inline
    IlvContainer*	getTopView() const { return _topview; }

    virtual void	setDoubleBuffering(IlBoolean value);

    inline IlBoolean	isDoubleBuffering() const
			{
			    return _doubleBuffering;
			}

    virtual IlvDim	getLabelOffset() const;

    void		setLabelOffset(IlvDim offset,
				       IlBoolean redraw = IlTrue);

    void		autoLabelAlignment(IlBoolean value,
					   IlBoolean redraw = IlTrue);

    IlBoolean		autoLabelAlignment() const;

    // open menu callbacks
    IlvDefineCallback(OpenMenu);

    inline void		setOpenMenuCallbackName(IlSymbol* callbackName)
			{
			    setOpenMenuCallback(OpenMenuSymbol(),
						callbackName);
			}

    virtual void	doIt();

    IlBoolean		hasToolTips() const;

    void		useToolTips(IlBoolean value);

    inline static void	EnableToolTips(IlBoolean value = IlTrue)
			{
			    _EnableToolTips = value;
			}

    inline static
    IlBoolean		AreToolTipsEnabled() { return _EnableToolTips; }

    inline static
    IlSymbol*		OpenMenuCallbackSymbol() { return _openMenuSymbol; }
    inline static
    IlSymbol*		OpenMenuSymbol()
			{
			    return OpenMenuCallbackSymbol();
			}

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvPopupMenu);

protected:
    IlvContainer*	_topview;
    IlBoolean		_doubleBuffering;
    IlBoolean		_visible;
    IlBoolean		_grabbed;
    IlvAbstractMenu*	_parentMenu;
    IlUShort		_positionInParent;
    IlvContainer*	_tearOffPopup;
    IlvPopupMenu*	_tearOffRef;
    IlvDim		_labelOffset;
    IlvDim		_maxAcceleratorSize;
    static IlBoolean	_EnableToolTips;

    virtual IlBoolean	iHandleEvent(IlvEvent& event);
    IlBoolean		iCallIsSelectable(IlvMenuItem*);
    IlShort		iCallSelectNext();
    IlShort		iCallSelectPrevious();
    void		iCallSelect(IlUShort pos);
    void		iCallSelectCascade(IlUShort pos);
    void		iCallUnSelect(IlUShort pos);
    void		iCallDoIt();
    void		cascadeDoIt();
    void		callOpenCallback();
    virtual void	remove(IlUShort pos, IlBoolean destroy = IlTrue);
    virtual IlUShort	insert(IlvGadgetItem*, IlShort pos = -1);
    void		iSetLabelOffset(IlvDim offset);
    virtual IlUShort	getVMargin() const;
    virtual IlUShort	getHMargin() const;
    virtual IlvDim	getDefaultLabelOffset() const;
    virtual void	drawSelection(IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem*,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;
    virtual void	drawHighlight(IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem*,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;
    virtual void	invalidateItem(IlvGadgetItem*,
				       const IlvGadgetItemGeometry&,
				       const IlvGadgetItemGeometry&);

public:
    // --- value accessors ---
    DeclareGraphicAccessors();

    static IlSymbol*	_openMenuSymbol;
    static IlSymbol*	_automaticLabelAlignmentValue;

    // ILVBIDI
    inline IlBoolean	isOpenLeft() const { return _openLeft; }
    inline void		openLeft(IlBoolean set) { _openLeft = set; }
    IlBoolean		_openLeft;
    // ILVBIDI

    // interaction methods
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	selectCascade(IlUShort pos);
    virtual void	select(IlUShort pos);
    virtual void	unSelect(IlUShort pos);

    virtual void	sizes(IlvDim& w,IlvDim& h) const;
    void		itemSize(IlUShort pos,
				 IlvDim& width,
				 IlvDim& height) const;
    inline IlBoolean	isCascadeMenu()
			{
			    return (_parentMenu ? IlTrue : IlFalse);
			}
    virtual
    IlvDirection	getOrientation() const;

    virtual void	changeSelection(IlShort pos);
    virtual void	changeLayoutAttributes(IlAny, IlAny);

    virtual IlUInt	getCallbackTypes(const char*      const**,
					 const IlSymbol* const**) const;

    virtual void	fitToContents(IlvDirection = (IlvDirection)
				      (IlvHorizontal|IlvVertical));
    virtual void	getPreferredSize(IlvDim& w, IlvDim& h) const;
    virtual void	recomputeAllItems();
    virtual IlvPalette*	getHighlightTextPalette() const;
    virtual IlvPalette*	getSelectionTextPalette() const;
    virtual void	setMode(IlvDrawMode m);
    virtual void	setOverwrite(IlBoolean value);
    virtual void	setBackground(IlvColor* color);
    virtual void	draw(IlvPort*dst,
			     const IlvTransformer*t = 0,
			     const IlvRegion* clip = 0) const;
    virtual void	drawGadgetItem(const IlvGadgetItem*,
				       IlvPort*,
				       const IlvRect&,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
    virtual void	drawContents(IlvPort* dst,
				     const IlvTransformer* t = 0,
				     const IlvRegion* clip = 0) const;
    virtual void	drawBackground(IlvPort* dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
    virtual void	drawFrame(IlvPort* dst,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	itemBBox(IlUShort             item,
				 IlvRect&              rect,
				 const IlvTransformer* t = 0) const;
    void		setSelected(IlShort pos);
    virtual void	empty();
    virtual void	internalBBox(IlvRect&,
				     const IlvTransformer* t = 0) const;

    virtual void	computeBBox();
    void		handleInput(IlvEvent& event);
    virtual const char*	getDefaultInteractor() const;
    IlvMenuItem*	matchAccelerator(IlvEvent&,
					 IlvPopupMenu**,
					 IlShort*);
    inline void		removeTopView() { _topview = 0; }
    virtual
    IlvAbstractMenu*	getParentMenu() const;
    inline void		setParentMenu(IlvAbstractMenu* menu, IlUShort pos)
			{
			    _parentMenu = menu;
			    _positionInParent = pos;
			}
    virtual void	grab();
    virtual void	unGrab();
    inline IlUShort	getPositionInParent() const
			{
			    return _positionInParent;
			}
    IlvDim		computeLabelOffset() const;
    static IlUShort	getItemXMargin();
    static IlUShort	getItemYMargin();
    virtual void	updateLook();
    virtual void	setHolder(IlvGraphicHolder* holder);
    void		createTearOffMenu(const IlvPoint&,
					  const char* title = 0);
    void		removeTearOffMenu();
    inline void		removeTearOff() { _tearOffPopup = 0; }
    inline
    IlvPopupMenu*	getTearOffRef() const { return _tearOffRef; }
    IlvPopupMenu*	getTearOff() const;
    void		recomputeTearOffSize(IlBoolean redraw = IlTrue);
    virtual
    IlvDirection	getAcceleratorAlignment() const;
    inline IlvDim	getMaxAcceleratorSize() const
			{
			    return _maxAcceleratorSize;
			}
    inline void		setMaxAcceleratorSize(IlvDim max)
			{
			    _maxAcceleratorSize = max;
			}

    virtual
    const IlvStylable*	getItemHolderStylable() const;
    virtual
    const IlvStylable*	getStylable() const;
    virtual IlvStylist* getStylist() const;
};

// --------------------------------------------------------------------------
inline IlBoolean
IsAnIlvPopupMenu(const IlvGraphic* object)
{
    return object->isSubtypeOf(IlvPopupMenu::ClassInfo());
}

ILVGDTEXPORTEDFUNCTION(void)
_IlvSetMenu(IlvGraphic*, IlvPopupMenu*);
ILVGDTEXPORTEDFUNCTION(IlvPopupMenu*)
_IlvGetMenu(IlvGraphic*);
ILVGDTEXPORTEDFUNCTION(void)
_IlvSendMenuEvent(IlvGraphic*, const IlvEvent&);

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvHPopupMenuInteractor : public IlvHGadgetInteractor
{
public:
    virtual void	select(IlvPopupMenu*, IlUShort) = 0;
    virtual void	unSelect(IlvPopupMenu*, IlUShort) = 0;
    virtual void	doIt(IlvPopupMenu*) = 0;
    virtual IlBoolean	isSelectable(IlvPopupMenu*, IlvMenuItem*) const = 0;
    virtual IlShort	selectNext(IlvPopupMenu*) = 0;
    virtual IlShort	selectPrevious(IlvPopupMenu*) = 0;
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(menu);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/menu.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/menu.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/menu.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/menu.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Menu_H */
