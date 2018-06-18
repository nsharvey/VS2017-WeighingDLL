// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/amenu.h
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
// Declaration of the IlvMenuItem and IlvAbstractMenu classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Amenu_H
#define __Ilv_Gadgets_Amenu_H

#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Gadgets_Itemgdt_H)
#  include <ilviews/gadgets/itemgdt.h>
#endif

class IlvContainer;
class IlvTimer;
class IlvPopupMenu;
class IlvAbstractMenu;

enum IlvMenuItemType {
    IlvLabelItem,
    IlvBitmapItem,
    IlvGraphicItem,
    IlvSeparatorItem,
    IlvTearOffItem
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvMenuItem : public IlvGadgetItem
{
    friend class IlvAbstractMenu;
    friend class IlvPopupMenu;

public:
    ILV_MLK_DECL();
    IlvMenuItem(const char* label)
	: IlvGadgetItem(label),
	  _menu(0),
	  _gcallback(0),
	  _callback(0),
	  _promptString(0),
	  _acceleratorText(0),
	  _acceleratorKey(0),
	  _acceleratorModifiers(0),
	  _callbackLang(0)
    {}

    IlvMenuItem(IlvBitmap* bitmap)
	: IlvGadgetItem(bitmap),
	  _menu(0),
	  _gcallback(0),
	  _callback(0),
	  _promptString(0),
	  _acceleratorText(0),
	  _acceleratorKey(0),
	  _acceleratorModifiers(0),
	  _callbackLang(0)
    {}

    IlvMenuItem(IlvGraphic* graphic)
	: IlvGadgetItem(graphic),
	  _menu(0),
	  _gcallback(0),
	  _callback(0),
	  _promptString(0),
	  _acceleratorText(0),
	  _acceleratorKey(0),
	  _acceleratorModifiers(0),
	  _callbackLang(0)
    {}

    IlvMenuItem()
	: IlvGadgetItem((const char*)0),
	  _menu(0),
	  _gcallback(0),
	  _callback(0),
	  _promptString(0),
	  _acceleratorText(0),
	  _acceleratorKey(0),
	  _acceleratorModifiers(0),
	  _callbackLang(0)
    {}
    virtual ~IlvMenuItem();

    IlvMenuItemType	getType() const;

    IlBoolean		isReadOnly() const;

    void		setReadOnly(IlBoolean value);

    IlBoolean		isToggle() const;

    void		setToggle(IlBoolean value);

    IlBoolean		isRadioToggle() const;

    void		setRadioToggle(IlBoolean value);

    IlBoolean		isChecked() const;

    void		setChecked(IlBoolean value);

    inline
    static IlSymbol*	CheckedBitmapSymbol()
			{
			    return _checkedBitmapNameSymbol;
			}

    IlBoolean		isTearOff() const;

    void		setTearOff(IlBoolean value = IlTrue);

    inline
    IlvPopupMenu*	getMenu() const { return _menu; }

    void		setMenu(IlvPopupMenu* menu, IlBoolean copy = IlTrue);

    void		detachMenu(IlBoolean destroy = IlFalse);

    inline const char*	getAcceleratorText() const
			{
			    return _acceleratorText;
			}

    void		setAcceleratorText(const char* text);

    inline IlUShort	getAcceleratorKey() const { return _acceleratorKey; }

    void		setAcceleratorKey(IlUShort key);

    inline IlUShort	getAcceleratorModifiers() const
			{
			    return _acceleratorModifiers;
			}

    void		setAcceleratorModifiers(IlUShort modifiers);

    inline IlSymbol*	getCallbackName() const { return _callback; }

    void		setCallbackName(IlSymbol* callbackName);

    inline
    IlvGraphicCallback	getCallback() const { return _gcallback; }

    void		setCallback(IlvGraphicCallback callback);

    virtual void	sizes(IlvPalette* pal,
			      IlvDim& width,
			      IlvDim& height,
			      IlBoolean margin = IlTrue) const;

    const char*		getToolTip() const;

    void		setToolTip(const char* tooltip);

protected:
    IlvPopupMenu*	_menu;
    IlvGraphicCallback	_gcallback;
    IlSymbol*		_callback;
    char*		_promptString;
    char*		_acceleratorText;
    IlUShort		_acceleratorKey;
    IlUShort		_acceleratorModifiers;
    const IlSymbol*	_callbackLang;

    static IlUShort	lock_tear_off;
    static inline void	stopCheckTearOff()  { lock_tear_off++; }
    static inline void	startCheckTearOff() { lock_tear_off--; }

    void		clean();
    virtual void	computeSize(IlUShort&, IlUShort&) const;
    virtual void	computeLabelSize(const IlvPalette*,
					 IlvDim&,
					 IlvDim&) const;

public:

    DeclareLazyGadgetItemInfo();
    DeclareGadgetItemIOConstructors(IlvMenuItem);

    // --- value accessors ---
    DeclareValueAccessors();
    static IlSymbol*	_typeValue;
    static IlSymbol* 	_toggleValue;
    static IlSymbol* 	_checkedValue;
    static IlSymbol* 	_radioValue;
    static IlSymbol* 	_readOnlyValue;
    static IlSymbol* 	_menuValue;
    static IlSymbol* 	_callbackNameValue;
    static IlSymbol* 	_callbackLanguageValue;
    static IlSymbol* 	_tooltipSymbol;
    static IlSymbol* 	_tooltipValue;
    static IlSymbol* 	_checkedBitmapValue;
    static IlSymbol* 	_checkedBitmapNameSymbol;

    IlvMenuItem(IlvInputFile&, IlvPalette* palette);
    inline void		callCallback(IlvGraphic* g)
			{
			    if (_gcallback)
				_gcallback(g, getClientData());
			}
    void		checkTearOff() const;
    IlBoolean		checkItem(IlvPopupMenu* tear_off,
				  IlvPopupMenu* ref) const;
    IlvDim		getAcceleratorSize(IlvPalette*) const;
    IlvMenuItem&	operator=(const IlvMenuItem&);
    virtual IlBoolean	isSelectable() const;
    virtual void	select();
    virtual void	deSelect();
    inline const char*	getPromptString() const { return _promptString; }
    void		setPromptString(const char* promptString);
    virtual void	drawLabel(IlvPort* dst,
				  IlvPalette* palette,
				  const IlvRect& rect,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual IlvPalette*	getInsensitivePalette() const;
    virtual const char*	getMessage() const;
    virtual IlUInt	getBitmapMask() const;
    virtual IlvBitmap*	getCurrentBitmap() const;
    inline
    const IlSymbol*	getCallbackLanguage() const
			{
			    return _callbackLang;
			}
    inline void		setCallbackLanguage(const IlSymbol* lang)
			{
			    _callbackLang = lang;
			}
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvMenuItemGroup : public IlvNamedProperty
{
public:
    IlvMenuItemGroup(IlSymbol* symbol);
    virtual ~IlvMenuItemGroup();

    static
    IlvMenuItemGroup*	Get(const IlvAbstractMenu* menu,
			    const IlSymbol* name);
    void		addTo(IlvAbstractMenu* menu);
    void		removeFrom(IlvAbstractMenu* menu);
    inline static
    IlvMenuItemGroup*	RemoveFrom(IlvAbstractMenu* menu,
				   const IlSymbol* name)
			{
			    IlvMenuItemGroup* group = Get(menu, name);
			    if (group)
				group->removeFrom(menu);
			    return group;
			}
    inline
    IlvAbstractMenu*	getAbstractMenu() const { return _amenu; }
    const IlSymbol* const* getItemNames(IlUShort& count) const;
    IlvMenuItem* const*	getItems(IlUShort& count) const;
    IlvMenuItem*	getItem(const IlSymbol* name) const;
    IlBoolean		contains(const IlSymbol* name) const;
    void		addItem(IlvMenuItem* item);
    void		addItem(const IlSymbol* name);
    void		removeItem(const IlSymbol* name);
    virtual void	itemAdded(IlvMenuItem*);
    virtual void	itemRemoved(IlvMenuItem*);
    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();

    DeclareValueAccessors();
    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvMenuItemGroup);

protected:
    IlList		_items;
    IlvAbstractMenu*	_amenu;

    const IlSymbol*	computeName(IlvMenuItem* item) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvMenuItemSelector : public IlvMenuItemGroup
{
public:
    IlvMenuItemSelector(IlSymbol* symbol);

    virtual void	doIt(IlvMenuItem* item);
    void		selectItem(IlvMenuItem* item);
    inline
    const IlSymbol*	whichSelected() const { return _selected; }
    inline IlSymbol*	getCallbackName() const { return _callbackName; }
    inline void		setCallbackName(IlSymbol* callbackName)
			{
			    _callbackName = callbackName;
			}
    inline
    IlvGraphicCallback	getCallback() const { return _callback; }
    inline void		setCallback(IlvGraphicCallback callback)
			{
			    _callback = callback;
			}
    inline IlAny	getCallbackData() const { return _callbackData; }
    inline void		setCallbackData(IlAny callbackData)
			{
			    _callbackData = callbackData;
			}

    inline
    const IlSymbol*	getCallbackLanguage() const
			{
			    return _callbackLang;
			}
    inline void		setCallbackLanguage(const IlSymbol* lang)
			{
			    _callbackLang = lang;
			}
    virtual void	itemAdded(IlvMenuItem*);
    virtual void	itemRemoved(IlvMenuItem*);

    DeclareValueAccessors();
    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvMenuItemSelector);

protected:
    const IlSymbol*	_selected;
    IlvGraphicCallback	_callback;
    IlAny		_callbackData;
    IlSymbol*		_callbackName;
    const IlSymbol*	_callbackLang;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvMenuItemHighlighter : public IlvMenuItemGroup
{
public:
    IlvMenuItemHighlighter(IlSymbol* symbol);

    virtual void	doIt(IlvMenuItem* item);
    void		highlightItems(IlvMenuItem* item);
    virtual void	propertyAdded(IlAny);
    virtual void	propertyRemoved();
    virtual void	itemAdded(IlvMenuItem*);
    virtual void	itemRemoved(IlvMenuItem*);

    DeclareLazyPropertyInfo();
    DeclarePropertyIOConstructors(IlvMenuItemHighlighter);
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvAbstractMenuLFHandler : public IlvObjectLFHandler
{
public:
    IlvAbstractMenuLFHandler(IlvLookFeelHandler* lf);

    virtual void	drawSelection(const IlvAbstractMenu*,
				      IlvPort*,
				      const IlvRect&,
				      const IlvGadgetItem*,
				      const IlvTransformer*,
				      const IlvRegion*) const = 0;
    virtual IlUShort	getSeparatorSize() const = 0;
    virtual IlvPalette*	getSelectionTextPalette(const IlvAbstractMenu*) const = 0;
    virtual void	setMode(IlvAbstractMenu*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvAbstractMenu*, IlBoolean) const = 0;
    virtual IlvPalette*	getInsensitivePalette(const IlvMenuItem*) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvAbstractMenu
    : public IlvGadget,
      public IlvListGadgetItemHolder
{
public:

    IlvMenuItem* const*	getItems(IlUShort& count) const;

    inline void		setItems(IlvMenuItem* const* items, IlUShort count)
			{
			    setItems((IlvGadgetItem* const*)items, count);
			}

    IlUShort		insertItem(IlvMenuItem* item, IlShort pos = -1);

    IlUShort		insertItem(IlUShort pos,
				   const char* label,
				   const IlvPopupMenu* menu = 0,
				   IlBoolean copy = IlTrue);

    virtual IlBoolean	isShowingLabel() const;

    void		showLabel(IlBoolean value = IlTrue,
				  IlBoolean redraw = IlTrue);

    virtual IlBoolean	isShowingPicture() const;

    void		showPicture(IlBoolean value = IlTrue,
				    IlBoolean redraw = IlTrue);

    virtual IlvPosition	getLabelPosition() const;

    void		setLabelPosition(IlvPosition position,
					 IlBoolean redraw = IlTrue);

    virtual void	getLabelOrientation(IlvOrientation& orientation,
					    IlBoolean& flip) const;
    void		setLabelOrientation(IlvOrientation orientation,
					    IlBoolean flip = IlFalse,
					    IlBoolean redraw = IlTrue);

    inline IlShort	whichSelected() const { return _selected; }

    virtual void	itemBBox(IlUShort index,
				 IlvRect& bbox,
				 const IlvTransformer* t = 0) const = 0;

    virtual IlShort	pointToPosition(const IlvPoint& point,
					const IlvTransformer* t = 0) const;

    void		setHighlightCallback(IlvGraphicCallback callback,
					     IlBoolean submenus = IlTrue);

    void		setHighlightCallback(const IlSymbol* callbackName,
					     IlBoolean submenus = IlTrue);

    void		addHighlightCallback(IlvGraphicCallback callback,
					     IlBoolean submenus = IlTrue);

    void		addHighlightCallback(const IlSymbol* callbackName,
					     IlBoolean submenus = IlTrue);

    virtual void	select(IlUShort pos);

    virtual void	unSelect(IlUShort pos);

    virtual IlBoolean	isSelectable(const IlvMenuItem* item) const;

    virtual void	drawHighlight(IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem*,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;
    virtual void	drawSelection(IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem*,
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;

protected:

    IlvAbstractMenu(IlvDisplay*        display,
		    IlUShort           count     = 0,
		    const char* const* labels    = 0,
		    IlUShort           thickness = IlvDefaultGadgetThickness,
		    IlvPalette*        palette   = 0);
    IlvAbstractMenu(IlvDisplay*		display,
		    IlUShort		count,
		    IlvMenuItem*	items,
		    IlUShort		thickness = IlvDefaultGadgetThickness,
		    IlvPalette*		palette   = 0);

    IlvAbstractMenu(IlvInputFile&, IlvPalette* p = 0, IlUShort from = 0);
    IlvAbstractMenu(const IlvAbstractMenu&);

    virtual void	remove(IlUShort pos, IlBoolean destroy = IlTrue);
    virtual IlUShort	insert(IlvGadgetItem*, IlShort pos = -1);
    void		initScrollTimer(IlvDirection dir, IlUShort pos);
    inline void		setMaxSize(IlvDim maxSize) {_maxSize = maxSize;}
    virtual void	invalidateItem(IlvGadgetItem*,
				       const IlvGadgetItemGeometry&,
				       const IlvGadgetItemGeometry&);
    virtual void	itemActivated(IlvGadgetItem*);
    virtual
    IlvGadgetItemArray&	getItemsArray() const;
    IlBoolean		callPostedMenu();
    virtual IlBoolean	classFocusable() const;
    static void		highlightSubMenu(IlvAbstractMenu*);

    IlShort			_selected;
    IlUShort			_firstVisible;
    IlvGadgetItemArray*		_items;
    IlvMenuItem*		_menuItems; // For compatibility
    IlvPosition			_labelPosition;
    IlvPosition			_labelOrientation;
    IlBoolean			_flipLabel;
    IlvDim			_maxSize;
    IlvTimer*			_ensureVisibleTimer;
    static IlvAbstractMenu*	_callback_menu;
    static IlList		_tearOffMenuList;

public:
    ~IlvAbstractMenu();
    virtual void	setSelected(IlShort pos);
    virtual IlvPalette*	getOpaquePalette() const;
    virtual IlvPalette*	getSelectionPalette() const;
    virtual IlvPalette*	getSelectionTextPalette() const;
    virtual IlvPalette*	getInsensitivePalette() const;
    virtual IlvPalette*	getNormalTextPalette() const;
    virtual void	recomputeAllItems();
    virtual
    IlvGadgetItem*	createItem(const char*		label,
					   IlvGraphic*	graphic = 0,
					   IlvBitmap*	bitmap = 0,
					   IlvBitmap*	selbitmap = 0,
					   IlBoolean	copy = IlTrue) const;
    virtual void	drawToolTip(const IlvGadgetItem*,
				    IlvPort*		  dst,
				    IlvPalette*		  palette,
				    const IlvRect&	  rect,
				    const IlvTransformer* t    = 0,
				    const IlvRegion*	  clip = 0) const;
    virtual IlvView*	createToolTipView(IlvGadgetItem*,
					  const IlvRect&,
					  IlvView*,
					  IlvPalette*) const;
    virtual void	prepareToolTip(IlvGadgetItem*,
				       IlvView*&,
				       IlvRect&,
				       IlvPalette*&);
    inline
    IlvMenuItem*	getItem(IlUShort index) const
			{
			    return (IlvMenuItem*)
				IlvListGadgetItemHolder::getItem(index);
			}
    virtual void	apply(IlvApplyObject, IlAny);
    virtual void	empty();
    IlvMenuItem*	getItems() const; // For compatibility
    void		addItem(const IlvMenuItem& item, IlShort index = -1);
    void		setItems(IlvMenuItem* items,
				 IlUShort count); // For compatibility
    inline
    IlvPopupMenu*	getSubMenu(IlUShort pos) const
			{
			    return getItem(pos)->getMenu();
			}
    inline void		setSubMenu(IlUShort		pos,
				   IlvPopupMenu*	popup,
				   IlBoolean		copy = IlTrue)
			{
			    getItem(pos)->setMenu(popup, copy);
			}
    virtual
    IlvGadgetItem*	getItemByName(const char* str) const;
    virtual void	internalBBox(IlvRect&,
				     const IlvTransformer* t = 0) const = 0;
    void		setFirstVisible(IlUShort pos,
					IlBoolean redraw = IlTrue);
    virtual void	setItems(IlvGadgetItem* const* items, IlUShort count);
    virtual void	setHolder(IlvGraphicHolder* holder);
    virtual void	setPalette(IlvPalette*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setThickness(IlUShort);
    void		reDrawItem(IlUShort pos);
    virtual
    IlvAbstractMenu*	getParentMenu() const;
    inline void		setHighlightCallbackName(const IlSymbol* cbName,
						 IlBoolean sub)
			{
			    setHighlightCallback(cbName, sub);
			}

    // Highlight Callback
    inline
    static IlSymbol*	HighlightCBSymbol() { return SCallbackSymbol(); }
    void		callHighlightCallbacks(IlShort);
    inline void		callHighlightCallback(IlShort pos)
			{
			    callHighlightCallbacks(pos);
			}

    // Interaction methods
    virtual IlBoolean	handleEvent(IlvEvent&) = 0;
    virtual IlShort	selectNext();
    virtual IlShort	selectPrevious();
    IlShort		getNextSelectableItem(IlShort pos,
					      IlvDirection dir =
					      IlvBottom) const;

    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlSymbol* const**) const;

    virtual void	changeLayoutAttributes(IlAny, IlAny);

    DeclareLazyTypeInfo();

    // --- value accessors ---
    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_selectedItemValue;
    static IlSymbol*	_countValue;
    static IlSymbol*	_itemsValue;
    static IlSymbol*	_getItemMethod;
    static IlSymbol*	_getSubMenuMethod;
    static IlSymbol*	_setSubMenuMethod;
    static IlSymbol*	_addItemMethod;
    static IlSymbol*	_removeItemMethod;
    static IlSymbol*	_getLabelMethod;
    static IlSymbol*	_setLabelMethod;

    virtual
    const IlvGadget*	getGadget() const;
    virtual
    IlvPopupMenu*	getTearOff() const;
    virtual
    IlvDirection	getOrientation() const = 0;
    void		deSelectAll();
    inline IlUShort	getFirstVisible() const { return _firstVisible; }
    virtual void	computeBBox();
    virtual void	itemSize(IlUShort pos,
				 IlvDim& width,
				 IlvDim& height) const = 0;
    void		ensureVisible(IlUShort pos, IlBoolean redraw = IlTrue);
    void		removeScrollTimer();
    IlvAbstractMenu*	getTopMenu();
    inline
    IlvGraphicHolder*	getTopMenuHolder()
			{
			    return getTopMenu()->getHolder();
			}
    IlShort		matchMnemonic(char) const;
    inline IlvDim	getMaxSize() const { return _maxSize; }
    virtual IlBoolean	isGrabbed() const = 0;
    virtual void	grab() =  0 ;
    virtual void	unGrab() =  0;
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	updateLook();
    static inline void	removeTearOffFromList(IlvAbstractMenu* menu)
			{
			    _tearOffMenuList.remove(menu);
			}
    inline
    static IlList*	getTearOffMenuList()
			{
			    return &_tearOffMenuList;
			}
    static IlvPopupMenu* _pendingShowMenu;
    static IlvPopupMenu* _pendingHideMenu;
    static IlvTimer*	_mapDelayTimer;
    static IlvTimer*	_unMapDelayTimer;
};

// --------------------------------------------------------------------------
extern ILVGDTEXPORTEDVAR(IlvValueTypeClass*) IlvValueMenuItemArrayType;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvValueMenuItemArrayTypeClass : public IlvValueTypeClass
{
public:
    IlvValueMenuItemArrayTypeClass();
    virtual void	copy(IlvValue& dest, const IlvValue& src) const;
    virtual const char*	name() const;
    virtual const char*	toString(const IlvValue& val) const;
    virtual void	deleteValue(IlvValue& val) const;
    static IlvMenuItem*	MenuItemArray(const IlvValue& val, IlUShort& count);
    static void		SetValue(IlvValue& val,
				 IlUShort count,
				 IlvMenuItem* items);
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvValueMenuItemArrayValue
{
    IlvValueMenuItemArrayValue(IlUShort count, IlvMenuItem* items);
    IlvValueMenuItemArrayValue(const IlvValueMenuItemArrayValue&);
    ~IlvValueMenuItemArrayValue();
    friend class IlvValueMenuItemArrayTypeClass;
    IlvMenuItem*	_array;
    IlUShort		_size;
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(amenu);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#if !defined(__Ilv_Gadgets_Motif_Amenu_H)
#  include <ilviews/gadgets/motif/amenu.h>
#endif
#  endif
#  if defined(ILVWINDOWSLOOK)
#if !defined(__Ilv_Gadgets_Windows_Amenu_H)
#  include <ilviews/gadgets/windows/amenu.h>
#endif
#  endif
#  if defined(ILVWINDOWS95LOOK)
#if !defined(__Ilv_Gadgets_Win95_Amenu_H)
#  include <ilviews/gadgets/win95/amenu.h>
#endif
#  endif
#  if defined(ILVVXLOOK)
#if !defined(__Ilv_Gadgets_Vx_Amenu_H)
#  include <ilviews/gadgets/vx/amenu.h>
#endif
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Amenu_H */
