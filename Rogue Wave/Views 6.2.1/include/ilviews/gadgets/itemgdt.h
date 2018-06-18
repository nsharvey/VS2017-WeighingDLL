// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/itemgdt.h
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
// Declaration of the IlvGadgetItem class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Itemgdt_H
#define __Ilv_Gadgets_Itemgdt_H

#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Gadgets_Itemtool_H)
#  include <ilviews/gadgets/itemtool.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_Alloc_H)
#  include <ilviews/base/alloc.h>
#endif
#if !defined(__Ilv_Util_Animator_H)
#  include <ilviews/util/animator.h>
#endif
#if !defined(__Ilv_Bidi_Interf_H)
#  include <ilviews/bidi/interf.h>
#endif
#if !defined(__Ilv_Base_Stylable_H)
#  include <ilviews/base/stylable.h>
#endif

// Default values
#define IlvDefaultGadgetItemSpacing	4
#define IlvDefaultGadgetItemPosition	IlvRight
#define IlvGadgetItemToolTipPeriod	400
#define IlvGadgetItemStartEditPeriod	300

// Bitmaps indexes
#define MAXITEMBITMAPS			32

class IlvGadget;
class IlvGadgetItem;
class IlvGadgetItemGeometry;

// --------------------------------------------------------------------------
typedef IlBoolean (*IlvApplyGadgetItem)(IlvGadgetItem* item, IlAny arg);

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvGadgetItemBitmapAnimator
    : public IlvBitmapAnimator
{
public:
    IlvGadgetItemBitmapAnimator(IlSymbol*,
				IlvAnimationMode = IlvAnimationForward,
				IlUInt = IlvDefaultAnimationPeriod);

    inline
    IlvGadgetItem*	getItem() const { return _item; }
    virtual void	initReDraws() const;
    virtual void	invalidateRegion() const;
    virtual void	reDrawViews() const;
    virtual IlvBitmap*	getBitmap() const;
    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();

    void		addTo(IlvGadgetItem*);
    void		removeFrom(IlvGadgetItem*);
    static IlvGadgetItemBitmapAnimator*
			Get(const IlvGadgetItem*, const IlSymbol*);
    static inline IlvGadgetItemBitmapAnimator*
			RemoveFrom(IlvGadgetItem* item, const IlSymbol* name)
	{
	    IlvGadgetItemBitmapAnimator* animator = Get(item, name);
	    if (animator) {
		animator->removeFrom(item);
	    }
	    return animator;
	}

    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvGadgetItemBitmapAnimator);

protected:
    IlvGadgetItem*	_item;

    inline void		setItem(IlvGadgetItem* item) { _item = item; }
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvGadgetItemHolder
{
    friend class IlvGadgetItem;
    friend class IlvItemToolTipView;

public:
    virtual IlBoolean	rightToLeft() const;
    virtual
    const IlvGadget*	getGadget() const;
    virtual
    const IlvStylable*	getItemHolderStylable() const;
    virtual
    IlvGraphicHolder*	getGraphicHolder() const;
    virtual
    IlvGadgetItem*	applyToItems(IlvApplyGadgetItem func, IlAny arg);
    virtual
    IlvGadgetItem*	getItemByName(const char* name) const;
    virtual void	recomputeAllItems();
    virtual void	drawToolTip(const IlvGadgetItem*,
				    IlvPort*,
				    IlvPalette*,
				    const IlvRect&,
				    const IlvTransformer* = 0,
				    const IlvRegion* = 0)const;
    virtual void	drawGadgetItem(const IlvGadgetItem* item,
				       IlvPort* port,
				       const IlvRect& rect,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
    virtual
    IlvGadgetItem*	createItem(const char*	label,
				   IlvGraphic*	graphic = 0,
				   IlvBitmap*	bitmap = 0,
				   IlvBitmap*	selbitmap = 0,
				   IlBoolean	copy = IlTrue) const;
    // Palettes
    virtual IlvPalette*	getSelectionPalette() const = 0;
    virtual IlvPalette*	getSelectionTextPalette() const = 0;
    virtual IlvPalette*	getInsensitivePalette() const = 0;
    virtual IlvPalette*	getNormalTextPalette() const = 0;
    virtual IlvPalette*	getOpaquePalette() const;
    virtual IlvPalette*	getHighlightTextPalette() const;
    // Redraw mechanism
    virtual void	initReDrawItems();
    virtual IlBoolean	isInvalidatingItems() const;
    virtual void	reDrawItems();
    virtual IlBoolean	isEditable() const;
    virtual IlBoolean	isShowingLabel() const;
    virtual IlBoolean	isShowingPicture() const;
    virtual IlvPosition	getLabelPosition() const;
    virtual void	getLabelOrientation(IlvOrientation&,
					    IlBoolean&) const;
    virtual IlBoolean	hasToolTips() const;
    virtual IlBoolean	allowDragDrop() const;
    void		editItem(IlvGadgetItem*);
    void		showToolTip(IlvGadgetItem*);
    IlvGadgetItem*	getEditedItem() const;
    IlvGadgetItem*	getToolTipItem() const;
    IlvGadgetItem*	getCallbackItem() const;
    void		setCallbackItem(IlvGadgetItem*);
    IlvGadgetItem*	getDraggedItem() const;
    void		setDraggedItem(IlvGadgetItem* item);
    IlvGraphic*		getDraggedImage() const;
    void		setDraggedImage(IlvGraphic* graphic);
    IlvGadgetItem*	getDragDropTarget() const;
    void		setDragDropTarget(IlvGadgetItem* item);
    inline static
    IlSymbol*		StartEditItemCallbackType() {return _startEditSymbol;}
    inline static
    IlSymbol*		AbortEditItemCallbackType() {return _abortEditSymbol;}
    inline static
    IlSymbol*		EndEditItemCallbackType() { return _endEditSymbol; }
    inline static
    IlSymbol*		StartDragItemCallbackType() {return _startDragSymbol;}
    inline static
    IlSymbol*		DragItemCallbackType() { return _dragSymbol; }
    inline static
    IlSymbol*		AbortDragItemCallbackType() {return _abortDragSymbol;}
    inline static
    IlSymbol*		EndDragItemCallbackType() { return _endDragSymbol; }
    inline static
    IlSymbol*		ActivateCallbackType()
	{ return IlvGraphic::CallbackSymbol(); }

    virtual IlBoolean	allowInvalidateItem() const;
    virtual
    IlvAlignment	getGadgetItemAlignment() const;
    virtual IlUShort	getGadgetItemHLabelMargin() const;
    virtual void	computeItemRects(const IlvGadgetItem*,
					 IlvRect&,
					 IlvRect&) const;
    virtual void	drawSelection(IlvPort*,
				      const IlvRect&,
				      const IlvGadgetItem*,
				      const IlvTransformer* = 0,
				      const IlvRegion* = 0) const;
    virtual void	drawHighlight(IlvPort*,
				      const IlvRect&,
				      const IlvGadgetItem*,
				      const IlvTransformer* = 0,
				      const IlvRegion* = 0) const;

    static void		ToolTipViewDeleted(IlvView*, IlAny);
    static void		EditViewDeleted(IlvView*, IlAny);

    static IlSymbol*	_startEditSymbol;
    static IlSymbol*	_abortEditSymbol;
    static IlSymbol*	_endEditSymbol;
    static IlSymbol*	_startDragSymbol;
    static IlSymbol*	_dragSymbol;
    static IlSymbol*	_abortDragSymbol;
    static IlSymbol*	_endDragSymbol;
    static IlSymbol*	_hasToolTipsValue;
    static IlSymbol*	_editableValue;
    static IlSymbol*	_showLabelValue;
    static IlSymbol*	_showPictureValue;
    static IlSymbol*	_labelPositionValue;
    static IlSymbol*	_labelOrientationValue;
    static IlSymbol*	_flipLabelValue;
    static IlSymbol*	_allowDragDropValue;
    static IlSymbol*	_callbackItemValue;
    static IlSymbol*	_getItemByNameMethod;

protected:
    IlvGadgetItemHolder();
    virtual ~IlvGadgetItemHolder();

    void		itemAdded(const IlvGadgetItem*);
    void		itemRemoved(const IlvGadgetItem*);
    virtual void	invalidateItem(IlvGadgetItem*,
				       const IlvGadgetItemGeometry&,
				       const IlvGadgetItemGeometry&) = 0;

    virtual void	itemSelected(IlvGadgetItem* item);
    virtual void	itemDeSelected(IlvGadgetItem* item);
    virtual void	itemHighlighted(IlvGadgetItem* item);
    virtual void	itemActivated(IlvGadgetItem* item);

    // Item edition
    IlBoolean		editRequested() const;
    void		requestEdit(IlvGadgetItem*,
				    int = IlvGadgetItemStartEditPeriod);
    void		cancelEdit();
    virtual void	startEdit(IlvGadgetItem* item);
    virtual void	abortEdit(IlvGadgetItem* item);
    virtual void	endEdit(IlvGadgetItem* item);

    virtual void	prepareItemEdition(IlvGadgetItem*,
					   IlvView*&,
					   IlvRect&,
					   IlvRect&,
					   IlvPalette*&);
    // Tooltip management
    IlBoolean		tooltipRequested() const;
    void		requestToolTip(IlvGadgetItem*,
				       int = IlvGadgetItemToolTipPeriod);
    void		cancelToolTip();
    virtual void	prepareToolTip(IlvGadgetItem*,
				       IlvView*&,
				       IlvRect&,
				       IlvPalette*&);
    virtual IlvView*	createToolTipView(IlvGadgetItem*,
					  const IlvRect&,
					  IlvView*,
					  IlvPalette*) const;
    virtual IlvView*	createEditItemView(IlvView*,
					   IlvGadgetItem*,
					   const IlvRect&,
					   const IlvRect&,
					   IlvPalette*,
					   const char*) const;
    static void		ToolTipStopped(IlvDisplay*, IlvGadgetItem*);

    // Drag&Drop
    virtual void	startDragItem(IlvGadgetItem* item);
    virtual void	abortDragItem();
    virtual void	endDragItem(const IlvPoint& point);
    virtual void	drawDraggedImage(const IlvPoint& point,
					 const IlvTransformer* t);
    virtual void	itemDragged(const IlvPoint& point);

    IlvView*		getEditView() const;
    void		setEditView(IlvView*);
    IlvTimer*		getEditTimer() const;
    void		setEditTimer(IlvTimer*);
    IlvGadgetItem*	getEditItem() const;
    void		setEditItem(IlvGadgetItem*);
};

// --------------------------------------------------------------------------
#define DeclareGadgetItemInfoRO_()					\
    static IlvGadgetItem* readItem(IlvInputFile&, IlvDisplay*);		\
    virtual IlvGadgetItem* copy() const

#define DeclareGadgetItemInfoRO() IlvDeclarePropClassInfo();		\
    DeclareGadgetItemInfoRO_()

#define DeclareLazyGadgetItemInfoRO() IlvDeclareLazyPropClassInfo();	\
    DeclareGadgetItemInfoRO_()

#define DeclareGadgetItemInfo() DeclareGadgetItemInfoRO();		\
    virtual void write(IlvOutputFile&) const

#define DeclareLazyGadgetItemInfo() DeclareLazyGadgetItemInfoRO();	\
    virtual void write(IlvOutputFile&) const

#define DeclareGadgetItemIOConstructors(classname) public:		\
    classname(IlvInputFile& file, IlvDisplay* holder);			\
    classname(const classname& source)

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvGadgetItem
    : public IlvValueInterface,
      public IlvBidiInterface,
      public IlvStylable
{
    friend class IlvEditItemView;
    friend class IlvGadgetItemHolder;

public:
    ILV_MLK_DECL();
    IlvGadgetItem(const char*	label,
		  IlvBitmap*	bitmap	 = 0,
		  IlvPosition	position = IlvDefaultGadgetItemPosition,
		  IlUShort	spacing	 = IlvDefaultGadgetItemSpacing,
		  IlBoolean	copy	 = IlTrue);
    IlvGadgetItem(const char*	label,
		  IlvGraphic*	graphic,
		  IlvPosition	position	= IlvDefaultGadgetItemPosition,
		  IlUShort	spacing		= IlvDefaultGadgetItemSpacing,
		  IlBoolean	copy		= IlTrue);
    IlvGadgetItem(IlvGraphic* graphic);
    IlvGadgetItem(IlvBitmap* bitmap);
    virtual ~IlvGadgetItem();

    virtual
    IlvGadgetItem*	copy() const;
    static
    IlvGadgetItem*	readItem(IlvInputFile& file, IlvDisplay* display);
    virtual void	write(IlvOutputFile& file) const;
    virtual IlvPalette*	getOpaquePalette() const;
    virtual IlvPalette*	getSelectionPalette() const;
    virtual IlvPalette*	getSelectionTextPalette() const;
    virtual IlvPalette*	getInsensitivePalette() const;
    virtual IlvPalette*	getNormalTextPalette() const;
    virtual IlvPalette*	getHighlightTextPalette() const;
    virtual void	setOpaquePalette(IlvPalette* palette);
    virtual void	setSelectionTextPalette(IlvPalette* palette);
    virtual void	setNormalTextPalette(IlvPalette* palette);
    virtual void	setHighlightTextPalette(IlvPalette* palette);

    virtual void	setOverwrite(IlBoolean);
    virtual void	setMode(IlvDrawMode);
    virtual void	setHolder(IlvGadgetItemHolder*);
    inline
    IlvGadgetItemHolder* getHolder() const { return _holder; }
    void		reDraw();
    // Item States
    virtual IlBoolean	isSelectable() const;
    IlBoolean		isSelected() const;
    IlBoolean		isHighlighted() const;
    IlBoolean		isSensitive() const;
    void		setSensitive(IlBoolean value);
    IlBoolean		isOpaque() const;
    void		setOpaque(IlBoolean value);
    IlBoolean		isEditable() const;
    void		setEditable(IlBoolean value);
    IlBoolean		isDragDropTarget() const;
    // Label management
    inline const char*	getLabel() const { return _label; }
    void		setLabel(const char* label, IlBoolean copy = IlTrue);
    IlvAlignment	getLabelAlignment() const;
    void		setLabelAlignment(IlvAlignment alignment);
    virtual const char*	getMessage() const;
    char		getMnemonic() const;
    // Name management
    const IlSymbol*	getSName() const;
    void		setSName(const IlSymbol*);
    inline const char*	getName() const
	{
	    const IlSymbol* n = getSName();
	    return n ? (const char*) *n : 0;
	}

    inline void		setName(const char* name)
	{ setSName(name ? IlGetSymbol(name) : 0); }
    // Graphic management
    IlvGraphic*		getGraphic() const;
    void		setGraphic(IlvGraphic* graphic);
    // Bitmap management
    IlUShort		getBitmapCount() const;
    virtual IlUInt	getBitmapMask() const;
    IlvBitmap*		getBitmap(IlUShort index = (IlUShort)0) const;
    IlvBitmap*		getBitmap(const IlSymbol* symbol) const;
    virtual IlvBitmap*	getCurrentBitmap() const;
    void		setBitmap(IlUShort index, IlvBitmap* bitmap);
    void		setBitmap(const IlSymbol* symbol, IlvBitmap* bitmap);
    inline void		setBitmap(IlvBitmap* bitmap)
	{ setBitmap((IlUShort)0, bitmap); }
    IlSymbol*		getBitmapSymbol(const IlvBitmap*) const;
    virtual IlvGadgetItemBitmapAnimator*
			createDefaultBitmapAnimator(IlSymbol*) const;
    void		removeAllBitmaps();
    static IlShort	GetItemBitmapIndex(const IlSymbol* symbol);
    static IlSymbol*	GetItemBitmapSymbol(IlUShort index);
    static void		AddItemBitmapSymbol(const IlSymbol* symbol,
					    IlUShort index);
    inline static
    IlSymbol*		BitmapSymbol() { return _bitmapNameSymbol; }
    inline static
    IlSymbol*		SelectedBitmapSymbol()
	{ return _selectedBitmapNameSymbol; }
    inline static
    IlSymbol*		InsensitiveBitmapSymbol()
	{ return _insensitiveBitmapNameSymbol; }
    inline static
    IlSymbol*		HighlightedBitmapSymbol()
	{ return _highlightedBitmapNameSymbol; }
    // Client Data
    IlAny		getClientData() const;
    void		setClientData(IlAny data);
    // Size and position
    void		getLabelOrientation(IlvOrientation& orientation,
					    IlBoolean& flip) const;
    void		setLabelOrientation(IlvOrientation orientation,
					    IlBoolean flip = IlFalse);
    IlBoolean		isShowingLabel() const;
    void		showLabel(IlBoolean value = IlTrue);
    IlBoolean		isShowingPicture() const;
    void		showPicture(IlBoolean value = IlTrue);
    IlUShort		getSpacing() const;
    void		setSpacing(IlUShort spacing);
    IlvPosition		getLabelPosition() const;
    void		setLabelPosition(IlvPosition position);
    virtual void	itemRect(IlvRect& rect, const IlvRect& bbox) const;
    virtual void	labelRect(IlvRect& rect, const IlvRect& bbox) const;
    virtual void	pictureRect(IlvRect& rect, const IlvRect& bbox) const;
    virtual void	selectionRect(IlvRect& rect,
				      const IlvRect& bbox) const;
    virtual void	recomputeSize(IlBoolean redraw = IlTrue);
    virtual IlUShort	getWidth() const;
    virtual IlUShort	getHeight() const;
    virtual void	draw(IlvPort*			dst,
			     const IlvRect&		rect,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;
    virtual void	drawLabel(IlvPort*		dst,
				  IlvPalette*		palette,
				  const IlvRect&	rect,
				  const IlvTransformer*	t = 0,
				  const IlvRegion*	clip = 0) const;
    virtual void	drawPicture(IlvPort*		dst,
				    const IlvRect&	rect,
				    const IlvTransformer* t = 0,
				    const IlvRegion*	clip = 0) const;
    virtual void	edit();
    virtual void	showToolTip();
    virtual void	select();
    virtual void	deSelect();
    virtual void	activate();
    virtual void	highlight(IlBoolean value = IlTrue);

    static void		Write(IlvOutputFile&, IlvGadgetItem*);
    static
    IlvGadgetItem*	Read(IlvInputFile&, IlvDisplay*);

    // --- value accessors ---
    DeclareValueAccessors();
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    virtual IlBoolean	beforeChangeValues(const IlvValue* = 0, IlUShort = 0);
    virtual void	afterChangeValues(const IlvValue* = 0, IlUShort = 0);
    void		getAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&) const;

    static IlSymbol*	_itemSelectedValue;
    static IlSymbol*	_itemSensitiveValue;
    static IlSymbol*	_itemHighlightedValue;
    static IlSymbol*	_itemOpaqueValue;
    static IlSymbol*	_itemEditableValue;
    static IlSymbol*	_itemShowLabelValue;
    static IlSymbol*	_itemShowGraphicValue;
    static IlSymbol*	_labelValue;
    static IlSymbol*	_labelAlignValue;
    static IlSymbol*	_labelPositionValue;
    static IlSymbol*	_currentBitmapValue;
    static IlSymbol*	_bitmapValue;
    static IlSymbol*	_selectedBitmapValue;
    static IlSymbol*	_insensitiveBitmapValue;
    static IlSymbol*	_highlightedBitmapValue;
    static IlSymbol*	_bitmapNameSymbol;
    static IlSymbol*	_selectedBitmapNameSymbol;
    static IlSymbol*	_insensitiveBitmapNameSymbol;
    static IlSymbol*	_highlightedBitmapNameSymbol;
    static IlSymbol*	_graphicValue;
    static IlSymbol*	_spacingValue;
    static IlSymbol*	_activateItemMethod;
    static IlSymbol*	_editItemMethod;
    static IlSymbol*	_copyMethod;
    static IlSymbol*	_tooltipItemMethod;
    static IlSymbol*	_widthValue;
    static IlSymbol*	_heightValue;
    static IlSymbol*	_labelOrientationValue;
    static IlSymbol*	_flipLabelValue;

    static
    const IlSymbol*	NamedPropertiesSymbol();

    // IlvBidiInterface methods
    virtual
    IlvBidiContext*	getBidiContext(IlBoolean = IlTrue) const;
    virtual
    IlvBidiContext*	getDefaultBidiContext() const;
    virtual IlBoolean	setBidiContext(IlvBidiContext*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);

    // IlvStylable methods
    virtual IlvDisplay* getStylableDisplay() const;
    virtual IlvStylist* getStylist() const;
    virtual const char* getStylableClassName() const;
    virtual const char* getStylableName() const;
    virtual const IlvStylable*  getStylable() const;
    virtual const IlvStylable* getStylableParent() const;
    virtual IlvStylable::State getStylableState() const;

    IlvGadgetItem&	operator=(const IlvGadgetItem&);

    IlvDeclareLazyPropRootClassInfo();
    DeclareGadgetItemIOConstructors(IlvGadgetItem);
    IlvDeclarePropertyListOwnerWithNotify(NamedPropertiesSymbol());

protected:
    void		copyProperties(const IlvGadgetItem&);
    void		iSetBitmap(IlUShort index, IlvBitmap*);
    virtual
    IlvAlignment	getAlignment() const;
    virtual IlUShort	getHMargin() const;
    virtual IlUShort	getVMargin() const;
    virtual IlUShort	getHLabelMargin() const;
    virtual void	computeSize(IlUShort& width, IlUShort& height) const;

    virtual void	computeRects(IlvRect& labelRect,
				     IlvRect& pictureRect) const;

    IlUShort		addBitmap(IlvBitmap*);
    void		compactBitmaps();
    void		setHighlighted(IlBoolean);
    void		setSelected(IlBoolean);
    void		setDragDropTarget(IlBoolean);
    virtual void	startEdit();
    virtual void	abortEdit();
    virtual void	endEdit(const char*);
    void		iStartEdit();
    void		iEndEdit();
    virtual void	computeLabelSize(const IlvPalette*,
					 IlvDim&,
					 IlvDim&) const;
    virtual void	drawSelection(IlvPort*,
				      const IlvRect&,
				      const IlvTransformer* = 0,
				      const IlvRegion* = 0) const;
    virtual void	drawHighlight(IlvPort*,
				      const IlvRect&,
				      const IlvTransformer* = 0,
				      const IlvRegion* = 0) const;

    IlUShort		_w;
    IlUShort		_h;
    IlvGadgetItemHolder* _holder;
    IlUInt		_state;
    char*		_label;
    IlShort		_labelx;
    IlShort		_labely;
    IlUShort		_labelw;
    IlUShort		_labelh;
    IlShort		_picturex;
    IlShort		_picturey;
    IlUShort		_picturew;
    IlUShort		_pictureh;
    static IlSymbol*	_BitmapSymbols[MAXITEMBITMAPS];

private:
    IlUInt		getExtendedFlag() const;
    void		setExtendedFlag(IlUInt);
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvGadgetItemGeometry
{
public:
    IlvGadgetItemGeometry(const IlvGadgetItem* = 0);

    inline IlUShort	getWidth() const { return _width; }
    inline IlUShort	getHeight() const { return _height; }
    inline
    const IlvRect&	getLabelRect() const { return _labelRect; }
    inline
    const IlvRect&	getPictureRect() const { return _pictureRect; }
    inline IlBoolean	isNull() const { return !_width || !_height; }
    IlBoolean		isSame(const IlvGadgetItemGeometry&) const;

protected:
    void		init(const IlvGadgetItem* item);

    IlUShort		_width;
    IlUShort		_height;
    IlvRect		_labelRect;
    IlvRect		_pictureRect;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvGadgetItemArray
    : public IlArray
{
public:
    IlvGadgetItemArray() : IlArray(5) {}
    virtual ~IlvGadgetItemArray();

    inline
    IlvGadgetItem*	getItem(IlUInt i) const
			{
			    return (i >= getLength())
				? 0
				: (IlvGadgetItem*)(getArray()[i]);
			}
    inline void		setItem(IlUInt i, const IlvGadgetItem* item)
			{
			    if (i < getLength()) {
				getArray()[i] = (IlAny)item;
			    }
			}
    IlInt		getIndex(IlAny,
				 IlUInt = 0,
				 IlUInt = (IlUInt)-1) const;
    void		setItems(const IlvGadgetItemArray&,
				 IlvGadgetItemHolder&);
};

typedef int (*IlvListCompareFunction)(const char*	string1,
				      const char*	string2,
				      IlAny		data1,
				      IlAny		data2);

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvListGadgetItemHolder
    : public IlvGadgetItemHolder
{
public:
    // Managing items
    virtual
    IlvGadgetItem*	applyToItems(IlvApplyGadgetItem, IlAny);
    IlShort		getIndex(const IlvGadgetItem* item,
				 IlUShort start = 0,
				 IlUShort stop = (IlUShort)-1) const;
    virtual void	addLabel(const char* label, IlAny data = 0);
    virtual void	insertLabel(IlUShort		pos,
				    const char*		label,
				    IlAny		data = 0);
    inline IlUShort	insertGraphic(IlvGraphic* graphic, IlShort pos = -1)
	{ return insert(createItem(0, graphic), pos); }
    inline IlUShort	insertBitmap(IlvBitmap* bitmap, IlShort pos = -1)
	{ return insert(createItem(0, 0, bitmap), pos); }
    inline IlUShort	insertItem(IlvGadgetItem* item, IlShort index = -1)
	{ return insert(item, index); }
    inline void		removeItem(IlUShort index,
				   IlBoolean destroy = IlTrue)
	{ remove(index, destroy); }
    inline void		removeLabel(IlUShort index)
	{ remove(index, IlTrue); }
    inline
    IlvGadgetItem*	getItem(IlUShort index) const
	{ return getItemsArray().getItem(index); }
    inline IlvGadgetItem* const* getItems(IlUShort& count) const
	{
	    IlvGadgetItemArray& array = getItemsArray();
	    count = (IlUShort)array.getLength();
	    return (IlvGadgetItem* const*) array.getArray();
	}
    virtual void	setItems(IlvGadgetItem* const* items, IlUShort count);
    IlShort		getPosition(const char* label,
				    IlUShort	start = 0) const;
    inline IlUShort	getCardinal() const
	{ return (IlUShort)getItemsArray().getLength(); }
    inline const char*	getLabel(IlUShort index) const
	{ return getItem(index) ? getItem(index)->getLabel() : 0; }
    void		setLabel(IlUShort	index,
				 const char*	label,
				 IlBoolean	copy);
    virtual void	setLabel(IlUShort, const char*);
    virtual void	setLabels(const char* const*	labels,
				  IlAny const*		itemData,
				  IlUShort		count,
				  IlBoolean		copy = IlTrue);
    virtual void	setLabels(const char* const*	labels,
				  IlUShort		count,
				  IlBoolean		copy = IlTrue);
    const char* const*	getLabels(IlUShort& count) const;
    inline IlAny	getItemData(IlUShort index) const
	{ return getItem(index) ? getItem(index)->getClientData() : 0; }
    inline void		setItemData(IlUShort index, IlAny itemData)
	{
	    IlvGadgetItem* item = getItem(index);
	    if (item) {
		item->setClientData(itemData);
	    }
	}
    IlAny const*	getUserDataArray(IlUShort& count) const;
    virtual IlvDim	getLabelOffset() const;

    // Selection
    inline IlBoolean	isSelected(IlUShort index) const
	{
	    return (index < getCardinal())
		   ? getItem(index)->isSelected()
		   : IlFalse;
	}
    IlShort		getFirstSelectedItem() const;
    inline IlShort	getSelectionIndex() const
	{ return getFirstSelectedItem(); }
    virtual void	deSelectAll();
    const char* const*	getSelections(IlUShort& count) const;
    IlUShort const*	getSelectionIndices(IlUShort& count) const;
    virtual const char*	getSelection() const;
    virtual void	removeSelections(IlBoolean = IlFalse);
    virtual void	empty() = 0;
    // Reading and writing items
    void		readItems(IlvInputFile&);
    void		writeItems(IlvOutputFile&) const;
    // Sort-related methods
    virtual void	sort(IlvListCompareFunction func = 0);
    virtual int		compareItems(const char*	string1,
				     const char*	string2,
				     IlAny		value1,
				     IlAny		value2);

    static IlSymbol*	_labelOffsetValue;
    static IlSymbol*	_gadgetItemsValue;

protected:
    virtual void	remove(IlUShort, IlBoolean = IlTrue);
    virtual IlUShort	insert(IlvGadgetItem*, IlShort = -1);
    virtual void	computeItemRects(const IlvGadgetItem*,
					 IlvRect&,
					 IlvRect&) const;
    virtual
    IlvGadgetItemArray&	getItemsArray() const = 0;
};

// --------------------------------------------------------------------------
typedef IlvGadgetItem* (*IlvGadgetItemConstructor)(IlvInputFile&,
						   IlvDisplay*);

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvGadgetItemClassInfo
    : public IlvValuedClassInfo
{
public:
    inline IlvGadgetItemConstructor	getConstructor() const
	{ return _constructor; }
    static IlvGadgetItemClassInfo* Create(const char*, IlvClassInfo**,
					  IlvGadgetItemConstructor,
					  IlvGetAccessorsFunction = 0);

protected:
    IlvGadgetItemClassInfo(const char*			className,
			   IlvClassInfo**		superClass,
			   IlvGadgetItemConstructor	constructor,
			   IlvGetAccessorsFunction	getAccessors = 0)
	: IlvValuedClassInfo(className, superClass, getAccessors),
	  _constructor(constructor)
    {}

    IlvGadgetItemConstructor	_constructor;
};

#define IlvRegisterGadgetItemClass(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,					\
    IlvGadgetItemClassInfo::Create(#classname,				\
				   superclass::ClassPtr(),		\
				   (IlvGadgetItemConstructor)		\
				   classname::readItem,			\
				   classname::GetAccessors))

#define IlvPostRegisterGadgetItemClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
    IlvGadgetItemClassInfo::Create(#classname,				\
				   superclass::ClassPtr(),		\
				   (IlvGadgetItemConstructor)		\
				   classname::readItem,			\
				   classname::GetAccessors))

#define IlvPredefinedGadgetItemIOMembers(classname)			\
IlvGadgetItem* classname::copy() const					\
{									\
  classname* obj = new classname(*this);				\
  obj->copyProperties(*this);						\
  return obj;								\
}									\
IlvGadgetItem* classname::readItem(IlvInputFile& i, IlvDisplay* display)\
{ return new classname(i, display); }

#define IlvPreRegisterGadgetItemClass(classname)			\
ILVPREDEFINECLASSINFOMEMBERS(classname)

// --------------------------------------------------------------------------
extern ILVGDTEXPORTEDVAR(IlvValueTypeClass*) IlvValueGadgetItemArrayType;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvValueGadgetItemArrayTypeClass
    : public IlvValueTypeClass
{
public:
    IlvValueGadgetItemArrayTypeClass();

    virtual void	copy(IlvValue&, const IlvValue&) const;
    virtual const char*	name() const;
    virtual const char*	toString(const IlvValue&) const;
    virtual void	deleteValue(IlvValue&) const;
    static
    IlvGadgetItem**	GadgetItemArray(const IlvValue&, IlUShort&);
    static void		SetValue(IlvValue&,
				 IlUShort,
				 IlvGadgetItem* const*);
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvValueGadgetItemArrayValue
{
    IlvValueGadgetItemArrayValue(IlUShort, IlvGadgetItem* const*);
    IlvValueGadgetItemArrayValue(const IlvValueGadgetItemArrayValue&);
    ~IlvValueGadgetItemArrayValue();

    friend class IlvValueGadgetItemArrayTypeClass;

    IlUShort		_size;
    IlvGadgetItem**	_items;
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(itemgdt);
#endif /* !__Ilv_Gadgets_Itemgdt_H */
