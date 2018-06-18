// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/slist.h
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
// Declaration of the IlvStringList class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Slist_H
#define __Ilv_Gadgets_Slist_H

#if !defined(__Ilv_Gadgets_Scgadget_H)
#  include <ilviews/gadgets/scgadget.h>
#endif
#if !defined(__Ilv_Gadgets_Itemgdt_H)
#  include <ilviews/gadgets/itemgdt.h>
#endif

class IlvTimer;
class IlvStringList;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvStringListLFHandler : public IlvObjectLFHandler
{
public:
    IlvStringListLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawGadgetItem(const IlvStringList* slist,
				       const IlvGadgetItem* item,
				       IlvPort* dst,
				       const IlvRect& bbox,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawSelection(const IlvStringList*,
				      IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem* item,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const = 0;
    virtual void	drawHighlight(const IlvStringList*,
				      IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem* item,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const = 0;
    virtual void	drawFrame(const IlvStringList* slist,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawBackground(const IlvStringList* slist,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawGadgetContents(const IlvStringList* slist,
					   IlvPort* dst,
					   const IlvTransformer* t,
					   const IlvRegion* clip) const = 0;
    virtual void	drawFullSelection(const IlvStringList*,
					  IlvPort*,
					  const IlvTransformer*,
					  const IlvRect&,
					  const IlvRegion*) const = 0;
    virtual void	computeFocusItemRect(IlvRect& focusRect,
					     const IlvStringList* slist,
					     IlUShort pos,
					     const IlvTransformer*) const = 0;
    virtual void	drawFocusItem(const IlvStringList* slist,
				      IlvPort*       dst,
				      const IlvTransformer*,
				      const IlvRect&,
				      const IlvRegion* clip,
				      IlBoolean selected) const = 0;
    virtual IlvDim	getItemMargin(const IlvStringList*) const = 0;
    virtual IlBoolean	itemBBox(const IlvStringList*,
				 IlUShort pos,
				 IlvRect& rect,
				 const IlvTransformer* t) const = 0;
    virtual IlBoolean	focusFollowSelection() const = 0;
    virtual IlvDim	getItemHeight(const IlvStringList* slist,
				      IlUShort pos) const = 0;
    virtual IlBoolean	handleGadgetEvent(IlvStringList* slist,
					  IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultStringListLFHandler
    : public IlvStringListLFHandler
{
public:
    IlvDefaultStringListLFHandler(IlvLookFeelHandler* lf)
	: IlvStringListLFHandler(lf)
    {}

    virtual void	drawGadgetItem(const IlvStringList*,
				       const IlvGadgetItem*,
				       IlvPort* port,
				       const IlvRect& rect,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const;
    virtual void	drawSelection(const IlvStringList*,
				      IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem* item,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;
    virtual void	drawHighlight(const IlvStringList*,
				      IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem* item,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;
    virtual void	drawFrame(const IlvStringList*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawBackground(const IlvStringList*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawGadgetContents(const IlvStringList*,
					   IlvPort*,
					   const IlvTransformer*,
					   const IlvRegion*) const;
    virtual IlBoolean	handleGadgetEvent(IlvStringList*,
					  IlvEvent& event) const;
};

enum IlvStringListSelectionMode
{
    IlvStringListBrowseSelection	= 0,
    IlvStringListSingleBrowseSelection	= 1,
    IlvStringListMultipleSelection	= 2,
    IlvStringListExtendedSelection	= 3,
    IlvStringListSingleSelection	= 4
};

#define IlvStringListCompareFunction IlvListCompareFunction

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvStringList
    : public IlvScrolledGadget,
      public IlvListGadgetItemHolder
{
    friend class IlvDefaultStringListLFHandler;
public:
    IlvStringList(IlvDisplay*		display,
		  const IlvPoint&	point,
		  const char* const*	labels = 0,
		  IlUShort		count = 0,
		  IlUShort		thickness = IlvDefaultGadgetThickness,
		  IlvPalette*		palette = 0);
    IlvStringList(IlvDisplay*		display,
		  const IlvRect&	rect,
		  const char* const*	labels    = 0,
		  IlUShort		count     = 0,
		  IlUShort		thickness = IlvDefaultGadgetThickness,
		  IlvPalette*		palette   = 0);
    IlvStringList(IlvDisplay*		display,
		  const IlvPoint&	point,
		  const char* const*	labels,
		  IlAny const*		itemData,
		  IlUShort		count,
		  IlUShort		thickness = IlvDefaultGadgetThickness,
		  IlvPalette*		palette   = 0);
    IlvStringList(IlvDisplay*		display,
		  const IlvRect&	rect,
		  const char* const*	labels,
		  IlAny const*		itemData,
		  IlUShort		count,
		  IlUShort		thickness = IlvDefaultGadgetThickness,
		  IlvPalette*		palette   = 0);
    virtual ~IlvStringList();

    virtual IlvPalette*	getOpaquePalette() const;
    virtual IlvPalette*	getSelectionPalette() const;
    virtual IlvPalette*	getSelectionTextPalette() const;
    virtual IlvPalette*	getInsensitivePalette() const;
    virtual IlvPalette*	getNormalTextPalette() const;
    virtual void	recomputeAllItems();
    virtual
    const IlvGadget*	getGadget() const;
    virtual
    const IlvStylable*	getItemHolderStylable() const;

    virtual IlvDim	getLabelOffset() const;
    void		setLabelOffset(IlvDim		offset,
				       IlBoolean	redraw = IlTrue);
    void		autoLabelAlignment(IlBoolean align,
					   IlBoolean redraw = IlTrue);
    IlBoolean		autoLabelAlignment() const;
    IlUShort		getLastVisibleItem(const IlvTransformer* t = 0) const;
    IlUShort		getLastFullVisibleItem() const;

    inline IlShort	getFocusItem() const { return _lastKeyboardItem; }
    inline IlUShort	getFirstItem() const { return _firstItem; }
    virtual void	setItems(IlvGadgetItem* const* items, IlUShort count);
    virtual void	empty();
    IlShort		pointToPosition(const IlvPoint&		point,
					const IlvTransformer*	t = 0) const;

    const char* const*	getLabels(IlUShort& count) const;
    virtual void	setSelected(IlUShort	index,
				    IlBoolean	value = IlTrue,
				    IlBoolean	redraw = IlFalse);
    void		setSelectionIndices(IlUShort const*	indexArray,
					   IlUShort		count);
    inline IlShort	getLastSelectedItem() const { return _lastSelected; }

    virtual void	applyTransform(const IlvTransformer* t);
    IlBoolean		itemBBox(IlUShort		index,
				 IlvRect&		bbox,
				 const IlvTransformer*	t = 0) const;
    inline IlBoolean	isExclusive() const { return _exclusive; }
    void		setExclusive(IlBoolean value = IlTrue);
    IlBoolean		hasFullSelection() const;
    void		useFullSelection(IlBoolean value = IlTrue,
					 IlBoolean redraw = IlTrue);
    IlvDim		getDefaultItemHeight() const;
    IlvDim		getItemHeight(IlUShort pos) const;

    void		setDefaultItemHeight(IlvDim	height,
					     IlBoolean	redraw = IlTrue);
    virtual IlBoolean	isEditable() const;
    void		setEditable(IlBoolean value = IlTrue);
    virtual IlBoolean	isShowingLabel() const;
    void		showLabel(IlBoolean value = IlTrue,
				  IlBoolean redraw = IlTrue);
    virtual IlBoolean	isShowingPicture() const;
    void		showPicture(IlBoolean value = IlTrue,
				    IlBoolean redraw = IlTrue);
    virtual IlvPosition	getLabelPosition() const;
    void		setLabelPosition(IlvPosition	position,
					 IlBoolean	redraw = IlTrue);
    virtual void	getLabelOrientation(IlvOrientation&	orientation,
					    IlBoolean&		flip) const;
    void		setLabelOrientation(IlvOrientation orientation,
					    IlBoolean flip = IlFalse,
					    IlBoolean redraw = IlTrue);
    virtual IlBoolean	hasToolTips() const;
    void		useToolTips(IlBoolean value = IlTrue);
    virtual IlBoolean	allowDragDrop() const;
    void		allowDragDrop(IlBoolean allow);
    inline IlvDim	getOffset() const { return _xoffset; }

    void		setOffset(IlvDim offset);

    virtual IlvDim	rowToPos(IlUShort pos, IlUShort from = 0) const;
    void		ensureVisible(IlUShort	index,
				      IlBoolean	redraw = IlFalse,
				      IlBoolean	horizontal = IlFalse);

    virtual void	removeSelections(IlBoolean redraw = IlFalse);
    IlvStringListSelectionMode	getSelectionMode() const;
    void		setSelectionMode(IlvStringListSelectionMode mode);
    // Callbacks
    IlvDefineCallback(Select);
    inline void		setSelectCallbackName(const IlSymbol* callbackName)
			{
			    setSelectCallback((IlSymbol*)callbackName);
			}

    inline static
    IlSymbol*		SelectSymbol() { return SCallbackSymbol(); }
    inline static
    IlSymbol*		SelectCBSymbol() { return SelectSymbol(); }

    virtual void	apply(IlvApplyObject f,IlAny arg);
    virtual void	scrollBarChanged(IlvScrollBar* scrollbar,
					 IlvOrientation direction);

    const char*		getDefaultInteractor() const;
    virtual void	setFirstItem(IlUShort p,
				     IlBoolean redraw = IlFalse);
    virtual void	changeOffset(IlvDim	offset,
				     IlBoolean	redraw = IlFalse);
    virtual void	setPalette(IlvPalette* palette);
    virtual void	setFont(IlvFont* fnt);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);

    inline IlvDim	getSpacing() const { return _spacing; }
    virtual void	setSpacing(IlvDim spacing, IlBoolean redraw = IlFalse);
    inline IlShort	getSelectionLimit() const { return _selectionLimit; }
    void		setSelectionLimit(IlShort limit);
    IlBoolean		selectionLimitReached() const;

    virtual void	sort(IlvListCompareFunction = 0);

    // event handling methods
    virtual IlBoolean	handleGadgetEvent(IlvEvent& event);
    virtual IlBoolean	handleExclusive(IlvEvent& event);
    virtual void	select(IlUShort index);
    virtual void	unSelect(IlUShort index);
    virtual void	doIt();

    virtual void	doSelect();
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	updateLook();
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlSymbol* const**) const;

    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvStringList);

protected:
    IlBoolean		iHandleGadgetEvent(IlvEvent& event);
    void		iSetLabelOffset(IlvDim offset);
    virtual IlUShort	getGadgetItemHLabelMargin() const;
    inline void		allowInvalidateItem(IlBoolean allow)
			{
			    _adjustEnabled = allow;
			}
    virtual IlBoolean	allowInvalidateItem() const;
    virtual void	prepareItemEdition(IlvGadgetItem*,
					   IlvView*&,
					   IlvRect&,
					   IlvRect&,
					   IlvPalette*&);
    virtual void	prepareToolTip(IlvGadgetItem*,
				       IlvView*&,
				       IlvRect&,
				       IlvPalette*&);
    virtual void	invalidateItem(IlvGadgetItem*,
				       const IlvGadgetItemGeometry&,
				       const IlvGadgetItemGeometry&);
    virtual void	remove(IlUShort pos, IlBoolean destroy = IlTrue);
    virtual IlUShort	insert(IlvGadgetItem*, IlShort pos = -1);
    virtual void	drawSelection(IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem* item,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;
    virtual void	drawHighlight(IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem* item,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;
    void		setSelectionAnchor(IlUShort pos);
    void		setLastSelected(IlUShort pos);
    void		extendSelection(IlUShort pos);
    void		selectRange(IlUShort pos);
    void		setFocusItem(IlShort pos, IlBoolean redraw = IlTrue);
    void		computeMaxWidth();
    void		computeMaxHeight();
    void		computeMaxWidth(const IlvGadgetItem*);
    void		computeLabelOffset();
    void		computeLabelOffset(IlvDim offset);
    void		highlightFocusItem(IlBoolean draw);
    virtual IlBoolean	classFocusable() const;
    void		iCallSelect(IlUShort pos);
    void		iCallUnSelect(IlUShort pos);
    void		iCallDoIt();

    virtual void	scrollBarHasMoved(IlvDirection dir);
    virtual void	adjustFromScrollBar(const IlvScrollBar* sb,
					    IlvDirection dir);
    virtual void	afterAdjustScrollBarVisibility(const IlvRect&);
    virtual void	adjustScrollBarValue(IlvScrollBar* sb,
					     IlvDirection dir);
    virtual
    IlvGadgetItemArray&	getItemsArray() const;

    static void		StopTimer();

    IlUShort		_firstItem;
    IlvGadgetItemArray*	_items;
    IlBoolean		_exclusive;
    IlShort		_selectionLimit;
    IlvDim		_xoffset;
    IlvDim		_labelOffset;
    IlvDim		_spacing;
    IlShort		_lastKeyboardItem;
    IlShort		_lastSelected;
    IlUShort		_selectionAnchor;
    IlvStringListSelectionMode	_selectionMode;
    IlBoolean		_allowEditOnButtonUp;
    IlBoolean		_adjustEnabled;
    static IlvStringList*	_cStringList;
    char **		_labels; // For compatibility
    IlBoolean		_dragging;
    IlvPosition		_labelPosition;
    IlvPosition		_labelOrientation;
    IlBoolean		_flipLabel;
    IlvPoint		_pointDragged;
    IlvPoint		_deltaDrag;
    IlBoolean		_beginDrag;
    IlBoolean		_callDoSelect;
    IlShort		_clickPos;
    IlUShort		_marquee;
    IlvDim		_itemsHeight;
    IlvDim		_maxLabelOffset;

    static IlvTimer*	_timer;

public:
    static  IlSymbol*	_addLabelMethod;
    static  IlSymbol*	_getLabelMethod;
    static  IlSymbol*	_getItemMethod;
    static  IlSymbol*	_setLabelMethod;
    static  IlSymbol*	_isSelectedMethod;
    static  IlSymbol*	_removeLabelMethod;
    static  IlSymbol*	_exclusiveValue;
    static  IlSymbol*	_countValue;
    static  IlSymbol*	_labelsValue;
    static  IlSymbol*	_selectionValue;
    static  IlSymbol*	_selectionLimitValue;
    static  IlSymbol*	_spacingValue;
    static  IlSymbol*	_fullSelectionValue;
    static  IlSymbol*	_firstSelectedItemValue;
    static  IlSymbol*	_selectionModeValue;
    static  IlSymbol*	_tempoSymbol;
    static  IlSymbol*	_itemsHeightValue;
    static  IlSymbol*	_automaticLabelAlignmentValue;

    inline static
    IlvStringList*	CurrentStringList() { return _cStringList; }
    static inline void	CurrentStringList(IlvStringList* cStringList)
			{
			    _cStringList = cStringList;
			}
    void		setInList(IlBoolean f);
    void		adjustFirstVisible(IlBoolean redraw = IlFalse);
    inline IlvDim	getMaxLabelOffset() const
			{
			    return _maxLabelOffset;
			}
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawGadgetItem(const IlvGadgetItem*,
				       IlvPort* port,
				       const IlvRect& rect,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const;
    virtual void	drawGadgetContents(IlvPort* dst,
					   const IlvTransformer* t = 0,
					   const IlvRegion* clip=0) const;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* ) const;
    IlUShort		getNextSensitiveItem(IlUShort pos,
					     IlvDirection dir);
    IlvDim		getItemMargin() const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvHStringListInteractor : public IlvHGadgetInteractor
{
public:
    virtual void	select(IlvStringList*, IlUShort) = 0;
    virtual void	unSelect(IlvStringList*, IlUShort) = 0;
    virtual void	doIt(IlvStringList*) = 0;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(slist);
#if defined(ILVMOTIFLOOK) && !defined(__Ilv_Gadgets_Motif_Slist_H)
#if !defined(__Ilv_Gadgets_Motif_Slist_H)
#  include <ilviews/gadgets/motif/slist.h>
#endif
#endif
#if defined(ILVWINDOWSLOOK) && !defined(__Ilv_Gadgets_Windows_Slist_H)
#if !defined(__Ilv_Gadgets_Windows_Slist_H)
#  include <ilviews/gadgets/windows/slist.h>
#endif
#endif
#endif /* !__Ilv_Gadgets_Slist_H */
