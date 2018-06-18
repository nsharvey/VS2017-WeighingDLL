// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/tree.h
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
// Declaration of the IlvTreeGadget class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Tree_H
#define __Ilv_Gadgets_Tree_H

#if !defined(__Ilv_Gadgets_Scgadget_H)
#  include <ilviews/gadgets/scgadget.h>
#endif
#if !defined(__Ilv_Gadgets_Itemgdt_H)
#  include <ilviews/gadgets/itemgdt.h>
#endif

class IlvTreeGadget;
class IlvTreeGadgetItem;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvTreeGadgetLFHandler : public IlvObjectLFHandler
{
public:
    IlvTreeGadgetLFHandler(IlvLookFeelHandler* lfh);

    virtual IlvPalette*	getLinkPalette(const IlvTreeGadget* tree) const = 0;
    virtual IlvPalette*	getButtonPalette(const IlvTreeGadget* tree) const = 0;
    virtual IlvPalette*	getWindowBackground(const IlvTreeGadget* tree) const=0;
    virtual void	getButtonSize(const IlvTreeGadget*,
				      const IlvTreeGadgetItem*,
				      IlvDim& width,
				      IlvDim& height) const = 0;
    virtual void	getItemSize(const IlvTreeGadget*,
				    const IlvTreeGadgetItem* item,
				    IlvDim& width,
				    IlvDim& height) const = 0;
    virtual IlvDim	getItemHeight(const IlvTreeGadget*,
				      const IlvTreeGadgetItem* item) const = 0;
    virtual void	drawButton(const IlvTreeGadget*	tree,
				   IlvPort* dst,
				   const IlvTreeGadgetItem* item,
				   const IlvRect& bbox,
				   const IlvRegion* clip) const = 0;
    virtual void	drawLine(const IlvTreeGadget*,
				 IlvPort*		dst,
				 const IlvTreeGadgetItem*,
				 const IlvPoint&	from,
				 const IlvPoint&	to,
				 const IlvRegion*	clip) const = 0;
    virtual void	drawGadgetItem(const IlvTreeGadget* tree,
				       const IlvTreeGadgetItem* item,
				       IlvPort* dst,
				       const IlvRect& bbox,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawSelection(const IlvTreeGadget*,
				      IlvPort* dst,
				      const IlvRect& rect,
				      const IlvTreeGadgetItem* item,
				      const IlvTransformer* t,
				      const IlvRegion* clip) const = 0;
    virtual void	drawHighlight(const IlvTreeGadget*,
				      IlvPort* dst,
				      const IlvRect& rect,
				      const IlvTreeGadgetItem* item,
				      const IlvTransformer* t,
				      const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvTreeGadget*	tree,
				  IlvPort*		dst,
				  const IlvTransformer*	t,
				  const IlvRegion*	clip) const = 0;
    virtual void	drawBackground(const IlvTreeGadget* tree,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion*	clip) const = 0;
    virtual void	drawGadgetContents(const IlvTreeGadget* tree,
					   IlvPort* dst,
					   const IlvTransformer* t,
					   const IlvRegion* clip) const = 0;
    virtual IlBoolean	handleGadgetEvent(IlvTreeGadget* tree,
					  IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultTreeGadgetLFHandler
    : public IlvTreeGadgetLFHandler
{
public:
    IlvDefaultTreeGadgetLFHandler(IlvLookFeelHandler* lf)
	: IlvTreeGadgetLFHandler(lf)
    {}

    virtual IlvPalette*	getWindowBackground(const IlvTreeGadget*) const;
    virtual void	getButtonSize(const IlvTreeGadget*,
				      const IlvTreeGadgetItem*,
				      IlvDim&			width,
				      IlvDim&			height) const;
    virtual void	getItemSize(const IlvTreeGadget*,
				    const IlvTreeGadgetItem*	item,
				    IlvDim&			width,
				    IlvDim&			height) const;
    virtual IlvDim	getItemHeight(const IlvTreeGadget*,
				      const IlvTreeGadgetItem* item) const;
    virtual void	drawButton(const IlvTreeGadget*,
				   IlvPort*			dst,
				   const IlvTreeGadgetItem*	item,
				   const IlvRect&		bbox,
				   const IlvRegion*		clip) const;
    virtual void	drawLine(const IlvTreeGadget*,
				 IlvPort*			dst,
				 const IlvTreeGadgetItem*,
				 const IlvPoint&		from,
				 const IlvPoint&		to,
				 const IlvRegion*		clip) const;
    virtual void	drawGadgetItem(const IlvTreeGadget*,
				       const IlvTreeGadgetItem*,
				       IlvPort*			port,
				       const IlvRect&		rect,
				       const IlvTransformer*	t,
				       const IlvRegion*		clip) const;
    virtual void	drawSelection(const IlvTreeGadget*,
				      IlvPort*			dst,
				      const IlvRect&		rect,
				      const IlvTreeGadgetItem*	item,
				      const IlvTransformer*	t,
				      const IlvRegion*		clip) const;
    virtual void	drawHighlight(const IlvTreeGadget*,
				      IlvPort*			dst,
				      const IlvRect&		rect,
				      const IlvTreeGadgetItem*	item,
				      const IlvTransformer*	t,
				      const IlvRegion*		clip) const;
    virtual void	drawFrame(const IlvTreeGadget*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawBackground(const IlvTreeGadget*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawGadgetContents(const IlvTreeGadget*,
					   IlvPort*,
					   const IlvTransformer*,
					   const IlvRegion*) const;
    virtual IlBoolean	handleGadgetEvent(IlvTreeGadget*,
					  IlvEvent& event) const;
};

enum IlvTreeSelectionMode
{
    IlvTreeExtendedSelection	= 0,
    IlvTreeSingleSelection	= 1
};

// --------------------------------------------------------------------------
typedef int (*IlvTreeGadgetItemCompareFunction)(const IlvTreeGadgetItem* itm1,
						const IlvTreeGadgetItem* itm2);

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvTreeGadgetItemHolder : public IlvGadgetItemHolder
{
    friend class IlvTreeGadgetItem;
public:

    virtual
    IlvTreeGadgetItem*	getRoot() const = 0;

    virtual IlvDim	getIndent() const = 0;
    virtual IlvDim	getTreeLeftMargin() const = 0;
    virtual
    IlvGadgetItem*	applyToItems(IlvApplyGadgetItem f, IlAny arg);
    virtual
    IlvGadgetItem*	createItem(const char*	label,
				   IlvGraphic*	graphic = 0,
				   IlvBitmap*	bitmap = 0,
				   IlvBitmap*	selbitmap = 0,
				   IlBoolean	copy = IlTrue) const;

    void		deSelectAll();

    IlvTreeGadgetItem*	getFirstSelectedItem() const;

    IlUInt		getItemsCount() const;

    IlUInt		getVisibleItemsCount() const;

    void		removeItem(IlvTreeGadgetItem* item);

    void		detachItem(IlvTreeGadgetItem* item);

    void		addItem(IlvTreeGadgetItem*	parent,
				IlvTreeGadgetItem*	item,
				IlInt			index = -1);

    void		moveItem(IlvTreeGadgetItem*	item,
				 IlvTreeGadgetItem*	parent,
				 IlInt			index = -1);

    virtual void	sort(IlvTreeGadgetItem* item = 0,
			     IlUInt levels = (IlUInt)-1,
			     IlvTreeGadgetItemCompareFunction func = 0);

    virtual int		compareItems(const IlvTreeGadgetItem* item1,
				     const IlvTreeGadgetItem* item2) const;

protected:
    virtual void	itemShrinked(IlvTreeGadgetItem* item);
    virtual void	itemExpanded(IlvTreeGadgetItem* item);
    virtual void	itemRemoved(IlvTreeGadgetItem* item);
    virtual void	itemInserted(IlvTreeGadgetItem* item, IlInt index);

public:
    static IlSymbol*	_expandSymbol;
    static IlSymbol*	_shrinkSymbol;
    static IlSymbol*	_indentValue;
    static IlSymbol*	_hasLinesValue;
    static IlSymbol*	_rootValue;
    static IlSymbol*	_shrinkItemMethod;
    static IlSymbol*	_expandItemMethod;
    static IlSymbol*	_removeAllItemsMethod;
    static IlSymbol*	_removeItemMethod;
    static IlSymbol*	_addItemMethod;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvTreeGadgetItem : public IlvGadgetItem
{
    friend class IlvTreeGadgetItemHolder;
    friend class IlvTreeGadget;

public:
    ILV_MLK_DECL();
    IlvTreeGadgetItem(const char*	label,
		      IlvBitmap*	bitmap = 0,
		      IlvPosition	position = IlvRight,
		      IlUShort		spacing = IlvDefaultGadgetItemSpacing,
		      IlBoolean		copy = IlTrue);

    IlvTreeGadgetItem(const char*	label,
		      IlvGraphic*	graphic,
		      IlvPosition	position = IlvRight,
		      IlUShort		spacing = IlvDefaultGadgetItemSpacing,
		      IlBoolean		copy = IlTrue);
    IlvTreeGadgetItem(IlvGraphic* graphic);
    IlvTreeGadgetItem(IlvBitmap* bitmap);
    IlvTreeGadgetItem(IlvTreeGadget* tree, IlvInputFile& is);

    virtual ~IlvTreeGadgetItem();

    inline
    IlvTreeGadgetItemHolder*	getTreeHolder() const
				{
				    return (IlvTreeGadgetItemHolder*)_holder;
				}
    inline IlBoolean	hasChildren() const
			{
			    return _child ? IlTrue : IlFalse;
			}
    IlBoolean		isExpanded() const;
    IlBoolean		isVisible() const;
    IlBoolean		hasUnknownChildCount() const;
    void		setUnknownChildCount(IlBoolean value);
    IlUInt		getCardinal() const;
    IlUInt		getPosition() const;
    inline
    IlvTreeGadgetItem*	getParent() const { return _parent; }
    inline
    IlvTreeGadgetItem*	getFirstChild() const { return _child; }
    IlvTreeGadgetItem*	getLastChild() const;

    inline IlBoolean	isLastChild() const { return _sibling == 0; }
    inline IlBoolean	isFirstChild() const { return _upSibling == 0; }
    inline
    IlvTreeGadgetItem*	getNextSibling() const { return _sibling; }
    inline
    IlvTreeGadgetItem*	getPrevSibling() const { return _upSibling; }
    IlvTreeGadgetItem*	nextVisible() const;

    IlvTreeGadgetItem*	previousVisible() const;

    IlvTreeGadgetItem*	lastVisible() const;

    IlBoolean		isAncestorOf(IlvTreeGadgetItem* item) const;

    IlBoolean		insertChild(IlvTreeGadgetItem* item, IlInt index = -1);

    void		detach();

    void		sortChildren(IlUInt levels = (IlUInt)-1,
				     IlvTreeGadgetItemCompareFunction func=0);

    IlvTreeGadgetItem*	applyToChildren(IlvApplyGadgetItem func,
					IlAny arg = 0) const;

    inline
    static IlSymbol*	ExpandedBitmapSymbol()
			{
			    return _expandedBitmapNameSymbol;
			}
    void		expandAll();
    virtual void	expand();
    virtual void	shrink();
    IlvTreeGadgetItem*	nextSelected() const;

    DeclareLazyGadgetItemInfo();
    DeclareGadgetItemIOConstructors(IlvTreeGadgetItem);

protected:
    IlvTreeGadgetItem(const IlvTreeGadgetItem& source,  IlvTreeGadget& tree);
    IlvTreeGadgetItem(IlvTreeGadget* tree, const char* label);
    IlvTreeGadgetItem(IlvTreeGadget*	tree,
		      const char*	label,
		      IlvBitmap*	bitmap,
		      IlvBitmap*	selectionBitmap);

    void		setExpanded(IlBoolean);
    void		nbVisibleChanged();
    IlvTreeGadgetItem*	next() const;
    IlUInt		igetIndex() const;
    IlvDim		maxWidth(IlBoolean forced = IlFalse) const;
    IlvDim		computeMaxWidth(IlBoolean forced = IlFalse) const;
    IlBoolean		isMaxWidthValid() const;
    void		validateMaxWidth(IlBoolean set);
    virtual void	computeSize(IlUShort&, IlUShort&) const;

    IlvTreeGadgetItem*	_parent;
    IlvTreeGadgetItem*	_sibling;
    IlvTreeGadgetItem*	_upSibling;
    IlvTreeGadgetItem*	_child;
    IlInt		_totalVisibleChilds;
    IlUInt		_totalSelectedChilds;
    IlvDim		_maxWidth;

public:
    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_hasChildrenValue;
    static IlSymbol*	_expandedValue;
    static IlSymbol*	_visibleValue;
    static IlSymbol*	_parentValue;
    static IlSymbol*	_firstChildValue;
    static IlSymbol*	_lastChildValue;
    static IlSymbol*	_isFirstValue;
    static IlSymbol*	_isLastValue;
    static IlSymbol*	_nextSiblingValue;
    static IlSymbol*	_prevSiblingValue;
    static IlSymbol*	_nextVisibleValue;
    static IlSymbol*	_prevVisibleValue;
    static IlSymbol*	_isAncestorOfMethod;
    static IlSymbol*	_expandedBitmapValue;
    static IlSymbol*	_expandedBitmapNameSymbol;
    static IlSymbol*	_nextSelectedValue;
    static IlSymbol*	_detachMethod;
    static IlSymbol*	_insertMethod;
    static IlSymbol*	_sortMethod;

    // For compatibility
    inline IlAny	getData() const { return getClientData(); }
    inline void		setData(IlAny data) { setClientData(data); }
    inline IlvBitmap*	getSelectionBitmap() const
			{
			    return getBitmap(SelectedBitmapSymbol());
			}
    inline void		setSelectionBitmap(IlvBitmap* bitmap)
			{
			    IlvGadgetItem::setBitmap(SelectedBitmapSymbol(),
						     bitmap);
			}

    // Not documented
    virtual IlUInt	getBitmapMask() const;
    virtual IlvBitmap*	getCurrentBitmap() const;
    virtual void	setHolder(IlvGadgetItemHolder*);
    virtual void	select();
    virtual void	deSelect();
    void		deSelectAll(IlvTreeGadgetItem* item = 0);
    IlUInt		getLevel() const;
    IlBoolean		hasAscendantShrunk(IlvTreeGadgetItem**) const;

    inline IlUInt	getNbSelectedChild() const
			{
			    return _totalSelectedChilds;
			}
    IlUInt		getVisibleChildsCount() const;
    IlvTreeGadgetItem*	getItem(const IlSymbol*) const;
    IlvTreeGadgetItem*	getVisibleItem(IlUInt index) const;
    IlvTreeGadgetItem*	nextForRange(IlvTreeGadgetItem*,
				     IlvTreeGadgetItem*) const;
    IlBoolean		getIndex(IlUInt&) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvTreeGadget
    : public IlvScrolledGadget,
      public IlvTreeGadgetItemHolder
{
    friend class IlvTreeGadgetItem;
    friend class IlvDefaultTreeGadgetLFHandler;

public:
    IlvTreeGadget(IlvDisplay*		display,
		  const IlvRect&	rect,
		  IlUShort		thickness = IlvDefaultGadgetThickness,
		  IlvPalette*		palette   = 0);

    ~IlvTreeGadget();

    virtual
    const IlvGadget*	getGadget() const;
    virtual
    const IlvStylable*	getItemHolderStylable() const;
    virtual IlvPalette*	getOpaquePalette() const;
    virtual IlvPalette*	getSelectionPalette() const;
    virtual IlvPalette*	getSelectionTextPalette() const;
    virtual IlvPalette*	getInsensitivePalette() const;
    virtual IlvPalette*	getNormalTextPalette() const;
    virtual
    IlvGadgetItem*	createItem(const char*	label,
				   IlvGraphic*	g	= 0,
				   IlvBitmap*	bitmap	= 0,
				   IlvBitmap*	sbitmap = 0,
				   IlBoolean	copy	= IlTrue) const;

    IlvTreeGadgetItem*	addItem(IlvTreeGadgetItem*	parent,
				const char*		label,
				IlInt			index = -1,
				IlvBitmap*		bitmap = 0,
				IlvBitmap*		expandedBitmap = 0,
				IlBoolean		redraw = IlTrue);
    void		addItem(IlvTreeGadgetItem*	parent,
				IlvTreeGadgetItem*	item,
				IlInt			index = -1);

    void		deSelectAll(IlBoolean redraw = IlTrue);

    void		removeItem(IlvTreeGadgetItem*	item,
				   IlBoolean		redraw = IlTrue);

    virtual void	beginPopulate();

    virtual void	endPopulate(IlBoolean redraw = IlTrue);

    virtual void	constantItemHeightAssumed(IlBoolean assumed);

    virtual IlBoolean	isConstantItemHeightAssumed() const;

    inline
    IlvTreeGadgetItem*	getFirstVisibleItem() const
			{
			    return _firstVisible;
			}

    IlvTreeGadgetItem*	getLastVisibleItem(const IlvTransformer* t = 0) const;

    IlvTreeGadgetItem*	getLastFullVisibleItem(const IlvTransformer* t=0)const;

    IlvDim		getIndent() const;

    void		setIndent(IlvDim indent, IlBoolean redraw = IlTrue);

    inline IlvPalette*	getTextPalette() const
			{
			    return getNormalTextPalette();
			}
    inline IlBoolean	getLinesAtRoot() const { return _linesAtRoot; }
    void		setLinesAtRoot(IlBoolean value,
				       IlBoolean redraw = IlTrue);
    inline IlBoolean	areLinesVisible() const { return _hasLines; }
    void		showLines(IlBoolean value, IlBoolean redraw = IlTrue);
    inline IlBoolean	areButtonsVisible() const { return _hasButtons; }
    void		showButtons(IlBoolean value,
				    IlBoolean redraw = IlTrue);
    inline IlBoolean	areRootsLinked() const { return _connectRoots; }
    void		linkRoots(IlBoolean value, IlBoolean redraw = IlTrue);

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

    virtual void	recomputeAllItems();

    void		shrinkItem(IlvTreeGadgetItem*	item,
				   IlBoolean		redraw = IlTrue);

    void		expandItem(IlvTreeGadgetItem*	item,
				   IlBoolean		redraw = IlTrue,
				   IlBoolean		all = IlFalse);

    void		removeAllItems(IlBoolean redraw = IlTrue);

    IlvTreeGadgetItem*	pointToItem(const IlvPoint&		point,
				    IlBoolean&			button,
				    const IlvTransformer*	t) const;

    IlvTreeGadgetItem*	pointToItemLine(const IlvPoint&		point,
					const IlvTransformer*	t) const;

    IlBoolean		itemBBox(IlvTreeGadgetItem*	item,
				 IlvRect&		bbox,
				 const IlvTransformer*	t = 0) const;

    IlBoolean		buttonBBox(IlvTreeGadgetItem*		item,
				   IlvRect&			bbox,
				   const IlvTransformer*	t = 0) const;

    virtual void	getButtonSize(const IlvTreeGadgetItem*	item,
				      IlvDim&			width,
				      IlvDim&			height) const;
    virtual void	getItemSize(const IlvTreeGadgetItem*	item,
				    IlvDim&			width,
				    IlvDim&			height) const;
    virtual IlvDim	getItemHeight(const IlvTreeGadgetItem*	item) const;

    virtual void	drawButton(IlvPort*			dst,
				   const IlvTreeGadgetItem*	item,
				   const IlvRect&		bbox,
				   const IlvRegion*		clip=0) const;
    virtual void	drawLine(IlvPort*			dst,
				 const IlvTreeGadgetItem*	item,
				 const IlvPoint&		from,
				 const IlvPoint&		to,
				 const IlvRegion*		clip=0) const;

    inline void		setSelectionMode(IlvTreeSelectionMode mode)
			{
			    _selectionMode = mode;
			}
    inline
    IlvTreeSelectionMode getSelectionMode() const
			{
			    return _selectionMode;
			}

    void		selectRange(IlvTreeGadgetItem* item);
    inline
    IlvTreeGadgetItem*	getLastSelectedItem() const
			{
			    return _lastSelected;
			}
    void		selectItem(IlvTreeGadgetItem*	item,
				   IlBoolean		value,
				   IlBoolean		deselectAll = IlTrue,
				   IlBoolean		redraw = IlTrue);

    void		ensureVisible(IlvTreeGadgetItem* item,
				      IlBoolean horizontal = IlTrue,
				      IlBoolean redraw = IlTrue);

    IlvTreeGadgetItem*	getCallbackItem() const;

    void		scrollToItem(IlvTreeGadgetItem*	item,
				     IlBoolean		redraw = IlTrue);
    inline void		scrollToIndex(IlUInt index, IlBoolean redraw = IlTrue)
			{
			    scrollToItem(_root->getVisibleItem(index), redraw);
			}

    inline IlvDim	getOffset() const { return _xoffset; }
    void		setOffset(IlvDim offset, IlBoolean redraw = IlTrue);

    virtual IlBoolean	handleTreeEvent(IlvEvent& event);

    static IlSymbol*	SelectCallbackType();
    inline
    static IlSymbol*	SelectSymbol() { return SelectCallbackType(); }

    IlvDefineCallback(Select);

    static IlSymbol*	ExpandCallbackType();
    inline
    static IlSymbol*	ExpandSymbol() { return ExpandCallbackType(); }

    IlvDefineCallback(Expand);

    static IlSymbol*	ShrinkCallbackType();
    inline
    static IlSymbol*	ShrinkSymbol() { return ShrinkCallbackType(); }

    IlvDefineCallback(Shrink);

    virtual IlBoolean	handleGadgetEvent(IlvEvent& event);

    void		getInternalBBox(IlvRect&		rect,
					const IlvTransformer*	t = 0) const;
    IlvTreeGadgetItem*	getRoot() const;
    void		apply(IlvApplyObject f, IlAny arg);
    virtual void	setFont(IlvFont* fnt);
    virtual void	setPalette(IlvPalette* palette);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    virtual void	drawGadgetItem(const IlvGadgetItem*,
				       IlvPort*			port,
				       const IlvRect&		rect,
				       const IlvTransformer*	t,
				       const IlvRegion*		clip) const;
    virtual void	drawSelection(IlvPort*			dst,
				      const IlvRect&		rect,
				      const IlvGadgetItem*	item,
				      const IlvTransformer*	t = 0,
				      const IlvRegion*		clip=0) const;
    virtual void	drawHighlight(IlvPort*			dst,
				      const IlvRect&		rect,
				      const IlvGadgetItem*	item,
				      const IlvTransformer*	t = 0,
				      const IlvRegion*		clip=0) const;
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlSymbol* const**) const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvTreeGadget);

protected:
    IlvTreeGadgetItem*	_root;
    IlvTreeGadgetItem*	_selectionAnchor;
    IlvTreeGadgetItem*	_lastSelected;
    IlvTreeGadgetItem*	_firstVisible;
    IlUInt		_firstVisibleIndex;
    IlvDim		_indent;
    IlvDim		_xoffset;
    IlBoolean		_linesAtRoot;
    IlBoolean		_hasButtons;
    IlBoolean		_hasLines;
    IlBoolean		_connectRoots;
    IlvTreeSelectionMode _selectionMode;
    IlBoolean		_adjustEnabled;
    IlBoolean		_allowEditOnButtonUp;
    IlvPosition		_labelPosition;
    IlvPosition		_labelOrientation;
    IlBoolean		_flipLabel;
    IlvPoint		_pointDragged;
    IlvPoint		_deltaDrag;
    IlBoolean		_beginDrag;
    IlInt               _startPopulate;
    IlInt               _needPopulateRefresh;
    IlBoolean           _constantItemHeightAssumed;

    virtual void	drawLines(IlvPort*		dst,
				  IlvTreeGadgetItem*	item,
				  const IlvPoint&	dp,
				  IlvPos		xmin,
				  IlvPos		xmax,
				  const IlvRegion*	clip = 0) const;
    inline void		allowInvalidateItem(IlBoolean allow)
			{
			    _adjustEnabled = allow;
			}
    virtual IlBoolean	allowInvalidateItem() const;

    virtual void	select(IlvTreeGadgetItem* item);

    virtual void	deSelect(IlvTreeGadgetItem* item);

    virtual void	activate(IlvTreeGadgetItem* item);

    virtual void	expand(IlvTreeGadgetItem* item);

    virtual void	shrink(IlvTreeGadgetItem* item);

    virtual void	itemSelected(IlvGadgetItem* item);
    virtual void	itemDeSelected(IlvGadgetItem* item);
    virtual void	itemActivated(IlvGadgetItem* item);
    virtual void	itemShrinked(IlvTreeGadgetItem* item);
    virtual void	itemExpanded(IlvTreeGadgetItem* item);
    virtual void	itemRemoved(IlvTreeGadgetItem* item);
    virtual void	itemInserted(IlvTreeGadgetItem* item, IlInt index);
    virtual void	prepareItemEdition(IlvGadgetItem*,
					   IlvView*&,
					   IlvRect&,
					   IlvRect&,
					   IlvPalette*&);
    virtual void	prepareToolTip(IlvGadgetItem*,
				       IlvView*&,
				       IlvRect&,
				       IlvPalette*&);
    IlInt		rowToPos(IlvTreeGadgetItem*) const;
    void		computeMaxWidth(IlBoolean forced = IlFalse);
    void		computeMaxHeight();
    void		computeMaxWidth(IlvTreeGadgetItem*);
    void		adjustFirstVisible(IlBoolean redraw = IlFalse);
    IlvDim		getTreeLeftMargin() const;
    void		adjustOffset();
    void		setLastSelected(IlvTreeGadgetItem*	item,
					IlBoolean		redraw);
    virtual IlBoolean	classFocusable() const;
    IlvDim		getMaxIndent() const;
    IlvPalette*		getWindowBackground() const;
    IlvPalette*		getLinkPalette() const;
    IlvPalette*		getButtonPalette() const;
    virtual void	invalidateItem(IlvGadgetItem*,
				       const IlvGadgetItemGeometry&,
				       const IlvGadgetItemGeometry&);
    virtual
    IlvTreeGadgetItem*	createItem(IlvTreeGadgetItem*	parent,
					   const char*	label,
					   IlvBitmap*	bitmap,
					   IlvBitmap*	selectionBmp);
    virtual void	drawGadgetContents(IlvPort* dst,
					   const IlvTransformer* t = 0,
					   const IlvRegion* clip = 0) const;
    virtual void	adjustFromScrollBar(const IlvScrollBar*	sb,
					    IlvDirection	dir);
    virtual void	afterAdjustScrollBarVisibility(const IlvRect&);
    virtual void	adjustScrollBarValue(IlvScrollBar*	sb,
					     IlvDirection	dir);

public:
    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_selectionSymbol;
    static IlSymbol*	_linesAtRootValue;
    static IlSymbol*	_hasButtonsValue;
    static IlSymbol*	_connectRootsValue;
    static IlSymbol*	_selectionModeValue;
    static IlSymbol*	_itemsCountValue;
    static IlSymbol*	_firstVisibleValue;
    static IlSymbol*	_selectItemMethod;
    static IlSymbol*	_deSelectAllMethod;
    static IlSymbol*	_sortMethod;
    static IlSymbol*	_firstSelectedItemValue;

    IlvDim		getChildsHeight(const IlvTreeGadgetItem*) const;
    void		setItemSelected(IlvTreeGadgetItem* item,
					IlBoolean selected = IlTrue,
					IlBoolean redraw = IlTrue);
    virtual void	sort(IlvTreeGadgetItem* = 0,
			     IlUInt levels = (IlUInt)-1,
			     IlvTreeGadgetItemCompareFunction = 0);

    // For compatibility
    void		setItemLabel(IlvTreeGadgetItem*	item,
				     const char*	label,
				     IlBoolean		redraw = IlTrue);
    void		setItemBitmap(IlvTreeGadgetItem* item,
				      IlvBitmap*	bitmap,
				      IlBoolean		redraw = IlTrue);
    void		setItemSelectionBitmap(IlvTreeGadgetItem* item,
					       IlvBitmap* bitmap,
					       IlBoolean = IlTrue);
    void		setItemEditable(IlvTreeGadgetItem* item,
					IlBoolean editable = IlTrue);
    inline void		setBitmapHeight(IlvDim) {}
    void		setItemUnknownChildCount(IlvTreeGadgetItem*,
						 IlBoolean = IlTrue);
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(tree);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/tree.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/tree.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/tree.h>
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#    include <ilviews/gadgets/winxp/tree.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/tree.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Tree_H */
