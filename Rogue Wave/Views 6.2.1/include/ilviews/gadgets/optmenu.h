// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/optmenu.h
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
// Declaration of the IlvOptionMenu class
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Optmenu_H
#define __Ilv_Gadgets_Optmenu_H

#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgets_Menu_H)
#  include <ilviews/gadgets/menu.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#  include <ilviews/gadgets/macrosadv.h>
#endif

class IlvOptionMenu;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvOptionMenuLFHandler
    : public IlvObjectLFHandler
{
public:
    IlvOptionMenuLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawText(const IlvOptionMenu*	menu,
				 IlvPort*		dst,
				 const IlvRect&		rect,
				 const IlvRegion*	clip) const = 0;
    virtual void	drawArrow(const IlvOptionMenu*	menu,
				  IlvPort*		dst,
				  const IlvRect&	rect,
				  const IlvRegion*	clip) const = 0;
    virtual void	drawFrame(const IlvOptionMenu*	menu,
				  IlvPort*		dst,
				  const IlvTransformer*	t,
				  const IlvRegion*	clip) const = 0;
    virtual void	drawBackground(const IlvOptionMenu* menu,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawContents(const IlvOptionMenu* menu,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;
    virtual void	drawFocus(const IlvOptionMenu*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer* = 0,
				  const IlvRegion* = 0) const = 0;
    virtual void	computeFocusRegion(const IlvOptionMenu*,
					   IlvRegion&,
					   const IlvTransformer* = 0) const=0;
    virtual
    IlvDirection	computeOpenMenuPoint(const IlvOptionMenu*,
					     IlvPoint&) const = 0;
    virtual void	setMode(IlvOptionMenu*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvOptionMenu*, IlBoolean) const = 0;
    virtual IlvPalette*	getSelectionTextPalette(const IlvOptionMenu*) const=0;
    virtual IlBoolean	handleButtonDrag() const;
    virtual IlBoolean	inArrow(const IlvOptionMenu* menu, IlvPoint& p) const;
    virtual IlvDim	getAdjustWidth() const = 0;
    virtual void	getPreferredSize(const IlvOptionMenu*,
					 IlvDim& w,
					 IlvDim& h) const = 0;
    virtual IlBoolean	handleEvent(IlvOptionMenu* menu,
				    IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultOptionMenuLFHandler
    : public IlvOptionMenuLFHandler
{
public:
    IlvDefaultOptionMenuLFHandler(IlvLookFeelHandler* lf)
	: IlvOptionMenuLFHandler(lf)
    {}

    virtual void	getPreferredSize(const IlvOptionMenu*,
					 IlvDim& w,
					 IlvDim& h) const;
    virtual IlBoolean	handleEvent(IlvOptionMenu*, IlvEvent&) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvOptionMenu
    : public IlvGadget,
      public IlvListGadgetItemHolder
{
    friend class IlvDefaultOptionMenuLFHandler;
public:

    IlvOptionMenu(IlvDisplay*		display,
		  const IlvPoint&	point,
		  const char* const*	labels    = 0,
		  IlUShort		count     = 0,
		  IlUShort		thickness = IlvDefaultGadgetThickness,
		  IlvPalette*		palette	  = 0);

    IlvOptionMenu(IlvDisplay*		display,
		  const IlvRect&	rect,
		  const char* const*	labels    = 0,
		  IlUShort		count     = 0,
		  IlUShort		thickness = IlvDefaultGadgetThickness,
		  IlvPalette*		palette   = 0);

    ~IlvOptionMenu();

    virtual IlvPalette*	getOpaquePalette() const;
    virtual IlvPalette*	getSelectionPalette() const;
    virtual IlvPalette*	getSelectionTextPalette() const;
    virtual IlvPalette*	getInsensitivePalette() const;
    virtual IlvPalette*	getNormalTextPalette() const;
    virtual void	empty();
    virtual IlvDim	getLabelOffset() const;
    virtual void	recomputeAllItems();
    virtual void	getPreferredSize(IlvDim& w, IlvDim& h) const;

    virtual
    IlvGadgetItem*	createItem(const char*	label,
				   IlvGraphic*	g = 0,
				   IlvBitmap*	bitmap = 0,
				   IlvBitmap*	sbitmap = 0,
				   IlBoolean	copy = IlTrue) const;
    virtual void	drawFrame(IlvPort*		dst,
				  const IlvTransformer* t,
				  const IlvRegion*	clip) const;
    virtual void	drawBackground(IlvPort*			dst,
				       const IlvTransformer*	t,
				       const IlvRegion*		clip) const;
    virtual void	drawContents(IlvPort*			dst,
				     const IlvTransformer*	t,
				     const IlvRegion*		clip) const;
    virtual void	drawArrow(IlvPort*		dst,
				  const IlvRect&,
				  const IlvRegion*	clip = 0) const;
    virtual void	drawText(IlvPort*		dst,
				 const IlvRect&,
				 const IlvRegion*	clip = 0) const;
    virtual void	setThickness(IlUShort t);
    virtual void	setPalette(IlvPalette*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setFont(IlvFont* fnt);
    virtual void	setBackground(IlvColor* color);
    virtual void	setForeground(IlvColor* color);
    virtual void	setSensitive(IlBoolean);

    const char*		getLabel() const;
    inline const char*	getLabel(IlUShort pos) const
	{ return IlvListGadgetItemHolder::getLabel(pos); }

    inline IlShort	whichSelected() const { return _selected; }

    void		setSelected(IlShort index, IlBoolean redraw = IlFalse);

    inline
    IlvPopupMenu*	getSubMenu() const { return _submenu; }

    virtual const char*	getDefaultInteractor() const;
    // event handling methods
    virtual IlBoolean	handleEvent(IlvEvent& event);

    virtual void	doIt();

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvOptionMenu);

protected:
    IlvPopupMenu*	_submenu;
    IlShort		_selected;
    IlBoolean		_buttonInverted;
    IlvGadgetItem*	_selectedItem;
    IlBoolean		_allowInvalidate;

    IlBoolean		iHandleEvent(IlvEvent& event);
    inline void		allowInvalidateItem(IlBoolean allow)
	{ _allowInvalidate = allow; }
    virtual IlBoolean	allowInvalidateItem() const;
    void		updateSelectedItem();
    void		openSubMenu(IlvEvent& event);
    void		setOpenTime(IlUInt);
    virtual IlUShort	insert(IlvGadgetItem*, IlShort pos = -1);
    virtual void	remove(IlUShort pos, IlBoolean destroy = IlTrue);
    virtual IlBoolean	classFocusable() const;
    virtual void	drawFocus(IlvPort* ,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
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
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* ) const;
    virtual void	invalidateItem(IlvGadgetItem*,
				       const IlvGadgetItemGeometry&,
				       const IlvGadgetItemGeometry&);
    virtual
    IlvGadgetItemArray&	getItemsArray() const;

public:
    friend class _IlvOptionMenuPopup;
    friend class IlvOptionMenuWLFHandler;

    DeclareGraphicAccessors();

    static IlSymbol*	_countValue;
    static IlSymbol*	_labelsValue;
    static IlSymbol*	_selectedValue;
    static IlSymbol*	_selectedIndexValue;
    static IlSymbol*	_subMenuValue;

    inline IlvGadgetItem* getSelectedItem() const { return _selectedItem; }
    virtual
    const IlvGadget*	getGadget() const;
    virtual
    const IlvStylable*	getItemHolderStylable() const;
    inline IlBoolean	isButtonInverted() const { return _buttonInverted; }
    inline void		setButtonInverted(IlBoolean set)
	{ _buttonInverted = set; }
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	updateLook();
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    void		iCallDoIt();
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvHOptionMenuInteractor
    : public IlvHGadgetInteractor
{
public:
    virtual void	doIt(IlvOptionMenu*) = 0;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(optmenu);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#if !defined(__Ilv_Gadgets_Motif_Optmenu_H)
#  include <ilviews/gadgets/motif/optmenu.h>
#endif
#  endif
#  if defined(ILVWINDOWSLOOK)
#if !defined(__Ilv_Gadgets_Windows_Optmenu_H)
#  include <ilviews/gadgets/windows/optmenu.h>
#endif
#  endif
#  if defined(ILVWINDOWS95LOOK)
#if !defined(__Ilv_Gadgets_Win95_Optmenu_H)
#  include <ilviews/gadgets/win95/optmenu.h>
#endif
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#if !defined(__Ilv_Gadgets_Winxp_Optmenu_H)
#  include <ilviews/gadgets/winxp/optmenu.h>
#endif
#  endif
#  if defined(ILVVXLOOK)
#if !defined(__Ilv_Gadgets_Vx_Optmenu_H)
#  include <ilviews/gadgets/vx/optmenu.h>
#endif
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Optmenu_H */
