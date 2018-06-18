// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/combo.h
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
// Declaration of the IlvComboBox class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Combo_H
#define __Ilv_Gadgets_Combo_H

#if !defined(__Ilv_Gadgets_Textfd_H)
#  include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Menu_H)
#  include <ilviews/gadgets/menu.h>
#endif

class IlvComboBox;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvComboBoxLFHandler : public IlvObjectLFHandler
{
public:
    IlvComboBoxLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawContents(const IlvComboBox* combo,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;
    virtual void	drawArrow(const IlvComboBox* combo,
				  IlvPort* dst,
				  const IlvRect& rect,
				  const IlvRegion* clip) const = 0;
    virtual void	drawBackground(const IlvComboBox* combo,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvComboBox* combo,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawFocus(const IlvComboBox*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual void	computeFocusRegion(const IlvComboBox*,
					   IlvRegion&,
					   const IlvTransformer*) const = 0;
    virtual void	setMode(IlvComboBox*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvComboBox*, IlBoolean) const = 0;
    virtual IlvDim	getMenuLeftMargin(const IlvComboBox* cb) const = 0;
    virtual void	getArrowBBox(const IlvComboBox*, IlvRect&) const = 0;
    virtual IlvDim	getAdjustWidth() const = 0;
    virtual IlvDim	getMarkerWidth(const IlvComboBox*) const = 0;
    virtual void	getTextBBox(const IlvComboBox*,
				    IlvRect& rect) const = 0;
    virtual void	getPreferredSize(const IlvComboBox*,
					 IlvDim&,
					 IlvDim&) const = 0;
    virtual IlBoolean	handleEvent(IlvComboBox* combo,
				    IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultComboBoxLFHandler
    : public IlvComboBoxLFHandler
{
public:
    IlvDefaultComboBoxLFHandler(IlvLookFeelHandler* lf)
	: IlvComboBoxLFHandler(lf)
	{}

    virtual void	drawBackground(const IlvComboBox*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvComboBox*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	getPreferredSize(const IlvComboBox*,
					 IlvDim&,
					 IlvDim&) const;
    virtual IlBoolean	handleEvent(IlvComboBox*, IlvEvent&) const;
    virtual void	computeFocusRegion(const IlvComboBox*,
					   IlvRegion&,
					   const IlvTransformer*) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvComboBox
    : public IlvTextField,
      public IlvListGadgetItemHolder
{
    friend class IlvDefaultComboBoxLFHandler;
public:

    IlvComboBox(IlvDisplay*        display,
		const IlvPoint&    point,
		const char*        label,
		const char* const* labels      = 0,
		IlUShort           count       = 0,
		IlUShort           thickness   = IlvDefaultGadgetThickness,
		IlvPalette*        palette     = 0,
		IlBoolean          makeSubmenu = IlTrue);
    IlvComboBox(IlvDisplay*        display,
		const IlvRect&     rect,
		const char*        label,
		const char* const* labels      = 0,
		IlUShort           count       = 0,
		IlUShort           thickness   = IlvDefaultGadgetThickness,
		IlvPalette*        palette     = 0,
		IlBoolean          makeSubmenu = IlTrue);

    ~IlvComboBox();

    virtual void	getPreferredSize(IlvDim& w, IlvDim& h) const;
    virtual IlvPalette*	getOpaquePalette() const;
    virtual IlvPalette*	getSelectionPalette() const;
    virtual IlvPalette*	getSelectionTextPalette() const;
    virtual IlvPalette*	getInsensitivePalette() const;
    virtual IlvPalette*	getNormalTextPalette() const;
    virtual void	empty();
    virtual
    IlvGadgetItem*	createItem(const char* label,
				   IlvGraphic* g = 0,
				   IlvBitmap* bitmap = 0,
				   IlvBitmap* sbitmap = 0,
				   IlBoolean copy = IlTrue) const;
    void		pictureBBox(IlvRect& bbox,
				    const IlvTransformer* t = 0) const;
    virtual void	drawPicture(IlvPort* dst,
				    const IlvTransformer* t = 0,
				    const IlvRegion* clip = 0) const;
    virtual void	setThickness(IlUShort thickness);
    virtual void	setPalette(IlvPalette*);
    virtual void	setFont(IlvFont* fnt);
    virtual void	setOverwrite(IlBoolean mode);
    virtual void	setMode(IlvDrawMode mode);
    virtual void	setBackground(IlvColor* color);
    virtual void	setForeground(IlvColor* color);

    const char*		getSelection() const;
    virtual void	setLabel(const char*, IlBoolean redraw = IlFalse);
    void		setLabel(IlUShort pos, const char* label);
    inline const char*	getLabel() const
			{
			    return IlvTextField::getLabel();
			}
    inline const char*	getLabel(IlUShort pos) const
			{
			    return IlvListGadgetItemHolder::getLabel(pos);
			}
    inline
    IlvPopupMenu*	getSubMenu() const { return _submenu; }
    virtual IlBoolean	isListVisible() const;
    void		itemsBBox(IlvRect& labelRect,
				  IlvRect& arrowRect,
				  const IlvTransformer * t = 0) const;
    virtual const char*	getDefaultInteractor() const;
    IlShort		whichSelected() const;
    void		updateSelectedItem(IlBoolean force = IlFalse);
    inline void		invalidateSelectedItem(IlBoolean b = IlTrue)
			{
			    _invalidSelected = b;
			}
    virtual IlShort	computeSelectedItem(IlBoolean& match) const;

    void		setSelected(IlUShort i, IlBoolean redraw = IlTrue);
    virtual void	changeSelection(IlUShort i);
    virtual void	setListItemSelected(IlShort i);

    // event handling methods
    virtual IlBoolean	handleEvent(IlvEvent& event);
    IlBoolean		isEditable() const;
    virtual void	labelChanged();
    virtual void	callOpenListCallback();
    inline
    static IlSymbol*	OpenListSymbol() { return _openListSymbol; }
    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlSymbol* const**)const;

    DeclareLazyTypeInfo();

protected:
    IlvListGadgetItemHolder*	_comboList;
    IlvPopupMenu*		_submenu;
    IlBoolean			_buttonInverted;
    IlShort			_whichSelected;
    IlBoolean			_invalidSelected;

    IlBoolean		iHandleEvent(IlvEvent& event);
    virtual void	getTextBBox(IlvRect&) const;
    virtual void	getTextArea(IlvRect&,
				    const IlvTransformer*) const;
    virtual IlUShort	insert(IlvGadgetItem*, IlShort pos = -1);
    virtual void	remove(IlUShort pos, IlBoolean destroy = IlTrue);
    virtual void	invalidateItem(IlvGadgetItem*,
				       const IlvGadgetItemGeometry&,
				       const IlvGadgetItemGeometry&);
    virtual
    IlvGadgetItemArray&	getItemsArray() const;

    friend class IlvComboBoxWLFHandler;

public:
    DeclareGraphicAccessors();
    static IlSymbol*	_countValue;
    static IlSymbol*	_labelsValue;
    static IlSymbol*	_subMenuValue;
    static IlSymbol*	_selectedValue;
    static IlSymbol*	_openListSymbol;

    IlvComboBox(IlvInputFile&, IlvPalette*, IlUShort from = 0);
    IlvComboBox(const IlvComboBox&);
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* t = 0) const;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawContents(IlvPort* dst,
				     const IlvTransformer* t = 0,
				     const IlvRegion* clip = 0) const;
    virtual void	drawArrow(IlvPort* dst,
				  const IlvRect&,
				  const IlvRegion* clip = 0) const;
    virtual void	drawBackground(IlvPort* dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
    virtual void	drawFrame(IlvPort* dst,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual
    const IlvGadget*	getGadget() const;
    inline IlBoolean	isButtonInverted() const {return _buttonInverted;}
    inline void		setButtonInverted(IlBoolean set)
			{
			    _buttonInverted = set;
			}
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	updateLook();
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    virtual void	setItems(IlvGadgetItem* const* items, IlUShort count);
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(combo);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/combo.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/combo.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/combo.h>
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#    include <ilviews/gadgets/winxp/combo.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/combo.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Combo_H */
