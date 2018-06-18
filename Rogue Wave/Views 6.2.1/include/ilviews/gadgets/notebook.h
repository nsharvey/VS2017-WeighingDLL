// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/notebook.h
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
// Declaration of the IlvNotebook class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Notebook_H
#define __Ilv_Gadgets_Notebook_H

#if !defined(__Ilv_Gadgets_Arrowb_H)
#  include <ilviews/gadgets/arrowb.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Gadgets_Itemgdt_H)
#  include <ilviews/gadgets/itemgdt.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#  include <ilviews/gadgets/macrosadv.h>
#endif

#define IlvNotebookLastPage		((IlUShort)-1)

#define IlvNotebookDefaultXMargin	5

#define IlvNotebookDefaultYMargin	2

#define IlvNotebookDefaultPageMargin	10

class IlvNotebookPage;
class IlvNotebook;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvNotebookLFHandler
    : public IlvObjectLFHandler
{
public:
    IlvNotebookLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawPageBackground(const IlvNotebookPage*,
					   IlvPort*,
					   const IlvTransformer*,
					   const IlvRegion*) const = 0;
    virtual void	drawBody(const IlvNotebook*,
				 IlvPort*,
				 const IlvRect&,
				 const IlvRegion*) const = 0;
    virtual void	computeAreas(const IlvNotebook*,
				     const IlvRect&,
				     IlvRect&,
				     IlvRect&,
				     IlvRect&,
				     IlvRect&) const = 0;
    virtual void	draw(const IlvNotebook*		notebook,
			     IlvPort*			dst,
			     const IlvTransformer*	t,
			     const IlvRegion*		clip) const = 0;
    virtual IlvDim	getArrowSize(const IlvNotebook*) const = 0;
    virtual void	drawTab(const IlvNotebook*	notebook,
				IlUShort		index,
				const IlvRect&		rect,
				IlvPort*		dst,
				const IlvRegion*	clip) const = 0;
    virtual void	setMode(const IlvNotebook*, IlvDrawMode) const=0;
    virtual void	setOverwrite(const IlvNotebook*, IlBoolean) const=0;
    virtual void	drawTabContents(const IlvNotebook* notebook,
					const IlvNotebookPage* page,
					const IlvRect& rect,
					IlvPort* dst,
					const IlvRegion* clip) const = 0;
    virtual void	setViewBackground(const IlvNotebookPage*,
					  IlvView*,
					  IlvColor*) const = 0;
    virtual void	computeShadowColors(const IlvNotebookPage*,
					    IlvColor*&,
					    IlvColor*&) const = 0;
    virtual void	computeFocusRegion(const IlvNotebook*,
					   IlvRegion&,
					   const IlvTransformer*) const = 0;
    virtual void	getTabRect(const IlvNotebook* notebook,
				   IlUShort index,
				   const IlvRect& bbox,
				   IlvRect& rect) const = 0;
    virtual void	getTabSize(const IlvNotebookPage* page,
				   IlvDim& width,
				   IlvDim& height) const = 0;
    virtual IlUShort	getLastVisibleTab(const IlvNotebook* notebook,
					  IlBoolean& arrows,
					  IlBoolean& cuttab,
					  IlBoolean& decr,
					  IlBoolean& incr) const = 0;

    virtual IlBoolean	propagateColors() const = 0;
    virtual IlvDim	getDeltaMargin(const IlvNotebook*) const = 0;
    virtual IlBoolean	handleEvent(IlvNotebook* notebook,
				    IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultNotebookLFHandler
    : public IlvNotebookLFHandler
{
public:
    IlvDefaultNotebookLFHandler(IlvLookFeelHandler* lf)
	: IlvNotebookLFHandler(lf)
    {}

    virtual void	getTabSize(const IlvNotebookPage*,
				   IlvDim&,
				   IlvDim&) const;
    virtual IlBoolean	handleEvent(IlvNotebook*, IlvEvent&) const;
    virtual void	drawPageBackground(const IlvNotebookPage*,
					   IlvPort*,
					   const IlvTransformer*,
					   const IlvRegion*) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvNotebook
    : public IlvGadget,
      public IlvGadgetItemHolder
{
    friend class IlvDefaultNotebookLFHandler;
public:
    IlvNotebook(IlvDisplay*	display,
		const IlvRect&	rect,
		IlvPosition	tabsPosition	= IlvTop,
		IlBoolean	verticalLabels	= IlFalse,
		IlBoolean	flipLabels	= IlFalse,
		IlvDim		xMargin		= IlvNotebookDefaultXMargin,
		IlvDim		yMargin		= IlvNotebookDefaultYMargin,
		IlUShort	thickness	= IlvDefaultGadgetThickness,
		IlvPalette*	palette		= 0);

    virtual ~IlvNotebook();

    virtual
    IlvGadgetItem*	createItem(const char*,
				   IlvGraphic* = 0,
				   IlvBitmap* = 0,
				   IlvBitmap* = 0,
				   IlBoolean = IlTrue) const;
    virtual void	getPreferredSize(IlvDim&, IlvDim&) const;
    virtual
    const IlvGadget*	getGadget() const;
    virtual
    const IlvStylable*	getItemHolderStylable() const;

    virtual IlvPalette* getOpaquePalette() const;
    virtual IlvPalette* getSelectionPalette() const;
    virtual IlvPalette* getSelectionTextPalette() const;
    virtual IlvPalette* getInsensitivePalette() const;
    virtual IlvPalette* getNormalTextPalette() const;
    virtual void	recomputeAllItems();
    virtual
    IlvGadgetItem*	applyToItems(IlvApplyGadgetItem, IlAny);

    virtual IlBoolean	isShowingLabel() const;
    void		showLabel(IlBoolean value = IlTrue,
				  IlBoolean redraw = IlTrue);
    virtual IlBoolean	isShowingPicture() const;    
    void		showPicture(IlBoolean value = IlTrue,
				    IlBoolean redraw = IlTrue);
    virtual IlvPosition	getLabelPosition() const;
    void		setLabelPosition(IlvPosition position,
					 IlBoolean redraw = IlTrue);
    virtual void	getLabelOrientation(IlvOrientation&	orientation,
					    IlBoolean&		flip) const;
    void		setLabelOrientation(IlvOrientation orientation,
					    IlBoolean flip = IlFalse,
					    IlBoolean redraw = IlTrue);

    inline IlUShort	getPagesCardinal() const { return _nPages; }

    IlvNotebookPage*	getPage(const char* name) const;
    inline
    IlvNotebookPage**	getPages() const { return _pages; }

    virtual IlBoolean	allowDragDrop() const;

    void		allowDragDrop(IlBoolean allow);

    inline const IlvArrowButton* getIncrArrow() const { return _incrArrow; }
    inline const IlvArrowButton* getDecrArrow() const { return _decrArrow; }
    inline IlvPosition	getTabsPosition() const { return _tabsPosition; }
    void		setTabsPosition(IlvPosition position);
    inline IlBoolean	areLabelsVertical() const
			{
			    return _labelOrientation == IlvVertical;
			}
    void		setLabelsVertical(IlBoolean value);
    inline IlBoolean	mustFlipLabels() const { return _flipLabel; }
    void		flipLabels(IlBoolean value);
    inline IlvDim	getXMargin() const { return _xMargin; }
    void		setXMargin(IlvDim x);
    inline IlvDim	getYMargin() const { return _yMargin; }
    void		setYMargin(IlvDim y);
    inline IlvDim	getPageTopMargin() const { return _topPageMargin; }
    void		setPageTopMargin(IlvDim margin);
    inline IlvDim	getPageBottomMargin() const
			{
			    return _bottomPageMargin;
			}
    void		setPageBottomMargin(IlvDim margin);
    inline IlvDim	getPageLeftMargin() const { return _leftPageMargin; }
    void		setPageLeftMargin(IlvDim margin);
    inline IlvDim	getPageRightMargin() const { return _rightPageMargin; }
    void		setPageRightMargin(IlvDim margin);
    inline IlUShort	getFirstVisibleTab() const { return _firstTab; }
    void		setFirstVisibleTab(IlUShort index);

    void		ensureVisible(IlUShort index, IlBoolean redraw);

    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer* = 0,
				  const IlvRegion* = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* = 0) const;
    virtual void	setSensitive(IlBoolean);
    virtual void	updateLook();
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    virtual void	setThickness(IlUShort);
    virtual void	setMode(IlvDrawMode);
    virtual void	setForeground(IlvColor*);
    virtual void	setBackground(IlvColor*);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setFont(IlvFont*);
    virtual void	setPalette(IlvPalette*);
    virtual void	getTabsSize(IlvDim&, IlvDim&) const;

    virtual IlBoolean	changeSelection(IlUShort index, IlBoolean redraw);
    virtual IlShort	pointToTabIndex(const IlvPoint& point,
					const IlvTransformer* t) const;

    virtual IlBoolean	handleEvent(IlvEvent&);
    virtual void	applyTransform(const IlvTransformer*);
    virtual void	setHolder(IlvGraphicHolder*);

    virtual void	getPageArea(IlvRect& rect,
				    const IlvTransformer* t = 0) const;
    IlvView*		getParent() const;

    IlvNotebookPage*	getSelectedPage() const;
    IlUShort		getSelectedPageIndex() const;
    void		setSelectedPageIndex(IlUShort index);
    IlvNotebookPage*	addPage(IlvNotebookPage* page,
				IlUShort index = IlvNotebookLastPage);
    IlvNotebookPage*	addPage(const char*	label,
				IlvBitmap*	bitmap = 0,
				IlBoolean	transparent = IlTrue,
				const char*	filename = 0,
				IlUShort	index = IlvNotebookLastPage);
    void		removePage(IlUShort	index,
				   IlBoolean	destroy = IlTrue);
    inline
    static IlSymbol*	PageResizedCallbackType()
			{
			    return _pageResizedSymbol;
			}
    inline
    static IlSymbol*	PageResizedSymbol()
			{
			    return PageResizedCallbackType();
			}

    IlvDefineCallback(PageResized);

    inline
    static IlSymbol*	PageSelectedCallbackType()
			{
			    return CallbackSymbol();
			}
    inline
    static IlSymbol*	PageSelectedSymbol()
			{
			    return PageSelectedCallbackType();
			}

    IlvDefineCallback(PageSelected);
    inline
    static IlSymbol*	PageDeselectedCallbackType()
			{
			    return _pageDeselectedSymbol;
			}
    inline
    static IlSymbol*	PageDeselectedSymbol()
			{
			    return PageDeselectedCallbackType();
			}

    IlvDefineCallback(PageDeselected);
    // Views management
    virtual IlvView*	createView(IlvNotebookPage*	page,
				   IlvAbstractView*	parent,
				   const IlvRect&	size);

    virtual void	deleteView(IlvNotebookPage* page);

    // Callbacks
    virtual void	pageSelected(IlvNotebookPage* page);
    virtual void	pageDeselected(IlvNotebookPage* page);
    virtual void	pageResized(IlvNotebookPage* page);
    virtual void	pagesResized();

    // Not documented
    IlvDim		getArrowSize() const;
    virtual IlBoolean	contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer*) const;
    void		computeAreas(IlvRect&,
				     IlvRect&,
				     IlvRect&,
				     IlvRect&,
				     const IlvTransformer* = 0) const;
    inline
    IlvNotebookPage*	operator[](IlUShort i) const { return _pages[i]; }
    void		getTabRect(IlUShort,
				   IlvRect&,
				   const IlvTransformer*) const;
    void		show();
    void		hide();
    inline IlBoolean	isVisible() const { return _isVisible; }
    virtual void	setVisible(IlBoolean);
    IlBoolean		handleAccelerator(IlvEvent&) const;
    virtual
    IlvNotebookPage*	createNotebookPage(const char*,
					   IlvBitmap* = 0,
					   const char* = 0)const;

    // Bidi interface
    virtual IlBoolean	setBidiContext(IlvBidiContext*);

    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlSymbol* const**) const;

    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

    static IlSymbol*	_countValue;
    static IlSymbol*	_pagesValue;
    static IlSymbol*	_selectedPageValue;
    static IlSymbol*	_tabsPositionPageValue;
    static IlSymbol*	_verticalLabelsValue;
    static IlSymbol*	_flipLabelsValue;
    static IlSymbol*	_tabXMarginValue;
    static IlSymbol*	_tabYMarginValue;
    static IlSymbol*	_topPageMarginValue;
    static IlSymbol*	_bottomPageMarginValue;
    static IlSymbol*	_leftPageMarginValue;
    static IlSymbol*	_rightPageMarginValue;
    static IlSymbol*	_getPageMethod;
    static IlSymbol*	_getPageWithNameMethod;
    static IlSymbol*	_firstVisibleValue;
    static IlSymbol*	_ensureVisibleMethod;
    static IlSymbol*	_pageAreaValue;
    static IlSymbol*	_parentValue;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvNotebook);

    // Callback symbols
    static IlSymbol*	_pageDeselectedSymbol;
    static IlSymbol*	_pageResizedSymbol;

protected:

    IlBoolean		iHandleEvent(IlvEvent&);
    void		checkArrowSensitivity();
    virtual IlBoolean	classFocusable() const;
    void		adjustArrowPosition(const IlvTransformer* = 0);
    virtual void	invalidateItem(IlvGadgetItem*,
				       const IlvGadgetItemGeometry&,
				       const IlvGadgetItemGeometry&);

private:
    void		init();

    IlUShort		_nPages;
    IlvNotebookPage**	_pages;
    IlUShort		_firstTab;
    IlUShort		_selectedPage;
    IlvPosition		_tabsPosition;
    IlvDim		_xMargin;
    IlvDim		_yMargin;
    IlvDim		_topPageMargin;
    IlvDim		_bottomPageMargin;
    IlvDim		_leftPageMargin;
    IlvDim		_rightPageMargin;
    IlvArrowButton*	_incrArrow;
    IlvArrowButton*	_decrArrow;
    IlvArrowButton*	_activeArrow;
    IlBoolean		_isVisible;
    IlvPosition		_labelPosition;
    IlvPosition		_labelOrientation;
    IlBoolean		_flipLabel;
    IlvPoint		_pointDragged;
    IlvPoint		_deltaDrag;
    IlBoolean		_beginDrag;

    friend class IlvNotebookMLFHandler;
    friend class IlvNotebookWLFHandler;
    friend class IlvNotebookVXLFHandler;
    friend class IlvNotebookPage;
};

#define DeclareNotebookPageInfoRO_()					\
    static IlvNotebookPage* create(IlvNotebook*);			\
    static IlvNotebookPage* read(IlvInputFile&, IlvNotebook*);		\
    virtual IlvNotebookPage* copy() const

#define DeclareNotebookPageInfoRO() IlvDeclarePropClassInfo();		\
    DeclareNotebookPageInfoRO_()

#define DeclareLazyNotebookPageInfoRO() IlvDeclareLazyPropClassInfo();	\
    DeclareNotebookPageInfoRO_()

#define DeclareNotebookPageInfo() DeclareNotebookPageInfoRO();		\
    virtual void write(IlvOutputFile&) const

#define DeclareLazyNotebookPageInfo() DeclareLazyNotebookPageInfoRO();	\
    virtual void write(IlvOutputFile&) const

#define DeclareNotebookPageIOConstructors(classname) public:		\
    classname(IlvNotebook*);						\
    classname(IlvNotebook*, IlvInputFile&);				\
    classname(const classname&)

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvNotebookPage
    : public IlvValueInterface
{
    friend class IlvNotebookMLFHandler;
    friend class IlvNotebookWLFHandler;
    friend class IlvNotebookVXLFHandler;
    friend class IlvNotebook;
public:

    IlvNotebookPage(IlvNotebook*	notebook,
		    const char*		label,
		    IlvBitmap*		bitmap,
		    IlBoolean		transparent,
		    const char*		filename);

    virtual ~IlvNotebookPage();

    inline IlvDisplay*	getDisplay() const { return _notebook->getDisplay(); }
    virtual IlvView*	getView();
    inline const char*	getName() const { return _item->getName(); }
    inline void		setName(const char* name) { _item->setName(name); }
    inline const char*	getLabel() const { return _item->getLabel(); }
    inline void		setLabel(const char* label) { _item->setLabel(label); }
    inline IlvBitmap*	getBitmap() const { return _item->getBitmap(); }
    inline void		setBitmap(IlvBitmap* bitmap)
			{
			    _item->setBitmap(bitmap);
			}
    inline IlvBitmap*	getInsensitiveBitmap() const
			{
			    return _item->getBitmap(IlvGadgetItem::
						    InsensitiveBitmapSymbol());
			}
    inline void		setInsensitiveBitmap(IlvBitmap* bitmap)
			{
			    _item->setBitmap(IlvGadgetItem::
					     InsensitiveBitmapSymbol(),
					     bitmap);
			}

    inline IlBoolean	isBitmapTransparent() const { return IlTrue; }
    inline void		setBitmapTransparent(IlBoolean) {}
    inline IlBoolean	isSensitive() const { return _item->isSensitive(); }
    void		setSensitive(IlBoolean value);
    inline const char*	getFileName() const { return _filename; }
    virtual void	setFileName(const char* filename);
    virtual void	draw(IlvPort*			dst,
			     const IlvRect&		pageRect,
			     const IlvTransformer*	t,
			     const IlvRegion*		clip) const;
    virtual void	drawContents(IlvPort*,
				     const IlvRect&,
				     const IlvRegion*) const;
    virtual void	drawPageBackground(IlvPort*,
					   const IlvTransformer*,
					   const IlvRegion*) const;
    virtual IlvView*	createView(IlvAbstractView*	parent,
				   const IlvRect&	rect);

    virtual void	deleteView();

    void		setView(IlvView* view);

    virtual void	select();
    virtual void	deSelect();

    virtual void	resized();

    virtual void	setFont(IlvFont*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);

    void		setBackground(IlvColor* color);

    void		setForeground(IlvColor*);
    virtual void	setViewBackground(IlvColor*);

    virtual void	getTabSize(IlvDim& width, IlvDim& height) const;
    virtual void	drawTab(IlvPort*		dst,
				const IlvRect&		rect,
				const IlvRegion*	clip) const;

    inline IlvNotebook*	getNotebook() const { return _notebook; }

    IlvPalette*		getBackground() const;
    IlvPalette*		getForeground() const;
    IlvPalette*		getTopShadowPalette() const;
    IlvPalette*		getBottomShadowPalette() const;
    IlBoolean		useDefaultColors() const;
    inline void		resetView() { _view = 0;}
    char		getMnemonic() const;
    void		getPreferredSize(IlvDim&, IlvDim&) const;
    void		setPreferredSize(IlvDim, IlvDim);
    inline
    IlvGadgetItem*	getItem() const { return _item; }

    IlBoolean		handleAccelerator(IlvEvent&) const;

    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

    static IlSymbol*	_labelValue;
    static IlSymbol*	_nameValue;
    static IlSymbol*	_sensitiveValue;
    static IlSymbol*	_fileNameValue;
    static IlSymbol*	_viewValue;
    static IlSymbol*	_backgroundValue;
    static IlSymbol*	_notebookValue;

    DeclareLazyNotebookPageInfo();
    DeclareNotebookPageIOConstructors(IlvNotebookPage);
    IlvDeclarePropertyListDelegate(*_item);

protected:
    virtual void	setNotebook(IlvNotebook*);
    void		lookChanged();
    IlvView*		icreateView(IlvAbstractView*,
				    const IlvRect&,
				    const IlvTransformer*);
    IlvView*		_view;
    char*		_filename;
    IlvDim		_prefWidth;
    IlvDim		_prefHeight;

private:
    IlvGadgetItem*	_item;
    IlvPalette*		_background;
    IlvPalette*		_topShade;
    IlvPalette*		_bottomShade;
    IlvNotebook*	_notebook;
};

// --------------------------------------------------------------------------
// NotebookPages IO
// --------------------------------------------------------------------------
typedef IlvNotebookPage* (*IlvNotebookPageConstructor)(IlvInputFile&,
						       IlvNotebook*);
typedef IlvNotebookPage* (*IlvNotebookPageEmptyCtr)(IlvNotebook*);

class ILVADVGDTEXPORTED IlvNotebookPageClassInfo
    : public IlvValuedClassInfo
{
public:
    inline
    IlvNotebookPageConstructor	getConstructor() const { return _constructor; }
    inline
    IlvNotebookPageEmptyCtr	getEmptyCtr() const { return _emptyCtr; }

    static
    IlvNotebookPageClassInfo*	Create(const char*,
				       IlvClassInfo**,
				       IlvNotebookPageConstructor,
				       IlvGetAccessorsFunction,
				       IlvNotebookPageEmptyCtr);

protected:
    IlvNotebookPageClassInfo(const char*		className,
			     IlvClassInfo**		superClass,
			     IlvNotebookPageConstructor constructor,
			     IlvGetAccessorsFunction    getAccessors,
			     IlvNotebookPageEmptyCtr	emptyCtr)
	: IlvValuedClassInfo(className, superClass, getAccessors),
	  _constructor(constructor),
	  _emptyCtr(emptyCtr)
    {}

    IlvNotebookPageConstructor	_constructor;
    IlvNotebookPageEmptyCtr	_emptyCtr;
};

#define IlvPreRegisterNotebookPageClass(classname)			\
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvRegisterNotebookPageClass(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,					\
	  IlvNotebookPageClassInfo::Create(#classname,			\
			  superclass::ClassPtr(),			\
			  (IlvNotebookPageConstructor)classname::read,	\
			  classname::GetAccessors,			\
			  (IlvNotebookPageEmptyCtr)classname::create))

#define IlvPostRegisterNotebookPageClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	  IlvNotebookPageClassInfo::Create(#classname,			\
			      superclass::ClassPtr(),			\
			      (IlvNotebookPageConstructor)classname::read, \
			      classname::GetAccessors,			\
			      (IlvNotebookPageEmptyCtr)classname::create))

#define IlvPredefinedNotebookPageIOMembers(classname)			\
IlvNotebookPage* classname::copy() const { return new classname(*this); } \
IlvNotebookPage* classname::create(IlvNotebook* n)			\
{ return new classname(n); }						\
IlvNotebookPage* classname::read(IlvInputFile& i, IlvNotebook* n)	\
{ return new classname(n, i); }

// --------------------------------------------------------------------------
extern ILVADVGDTEXPORTEDVAR(IlvValueTypeClass*)
IlvValueNotebookPageArrayType;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvValueNotebookPageArrayValue
{
    IlvValueNotebookPageArrayValue(IlUShort, IlvNotebookPage**);
    IlvValueNotebookPageArrayValue(const IlvValueNotebookPageArrayValue&);
    ~IlvValueNotebookPageArrayValue();

    friend class IlvValueNotebookPageArrayTypeClass;

    IlvNotebookPage**	_array;
    IlUShort		_count;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvValueNotebookPageArrayTypeClass
    : public IlvValueTypeClass
{
public:
    IlvValueNotebookPageArrayTypeClass();

    virtual void	copy(IlvValue&, const IlvValue&) const;
    virtual const char*	name() const;
    virtual const char*	toString(const IlvValue&) const;
    virtual void	deleteValue(IlvValue&) const;
    static 
    IlvNotebookPage**	NotebookPageArray(const IlvValue&, IlUShort&);
    static void		SetValue(IlvValue&,
				 IlUShort,
				 IlvNotebookPage**);
};

// --------------------------------------------------------------------------
ILVADVGDTEXPORTEDFUNCTION(IlvNotebookPage*)
IlvCreateNotebookPage(IlvNotebook*, const char*);
ILVADVGDTEXPORTEDFUNCTION(const char* const*)
IlvGetRegisteredNotebookPageClassNames(IlUInt& count);

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(notebook);
#if defined(ILVMOTIFLOOK)
#  include <ilviews/gadgets/motif/notebook.h>
#endif
#if defined(ILVWINDOWSLOOK)
#  include <ilviews/gadgets/windows/notebook.h>
#endif
#if defined(ILVWINDOWSXPLOOK)
#  include <ilviews/gadgets/winxp/notebook.h>
#endif
#if defined(ILVVXLOOK)
#  include <ilviews/gadgets/vx/notebook.h>
#endif
#endif /* !__Ilv_Gadgets_Notebook_H */
