// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/scombo.h
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
// Declaration of the IlvScrolledComboBox class
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Scombo_H
#define __Ilv_Gadgets_Scombo_H

#if !defined(__Ilv_Gadgets_Combo_H)
#  include <ilviews/gadgets/combo.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#  include <ilviews/gadgets/slist.h>
#endif

class IlvContainer;
class IlvScrolledComboBox;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvScrolledComboBoxLFHandler
    : public IlvObjectLFHandler
{
public:
    IlvScrolledComboBoxLFHandler(IlvLookFeelHandler* lfh);

    virtual void	setSelectionCursor(IlvScrolledComboBox*) = 0;
    virtual void	internalBBox(const IlvScrolledComboBox*,
				     const IlvStringList*,
				     IlvRect& rect,
				     const IlvTransformer* t) const = 0;
    virtual void	scrollBarBBox(const IlvScrolledComboBox*,
				      const IlvStringList*,
				      IlvOrientation dir,
				      IlvRect& bbox,
				      const IlvTransformer* t) const = 0;
    virtual void	drawFrame(const IlvScrolledComboBox*,
				  const IlvStringList*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const = 0;
    virtual IlBoolean	allowSelectWithMove() const = 0;
    virtual IlBoolean	handleEvent(IlvScrolledComboBox* scombo,
				    IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultScrolledComboBoxLFHandler
    : public IlvScrolledComboBoxLFHandler
{
public:
    IlvDefaultScrolledComboBoxLFHandler(IlvLookFeelHandler* lf)
	: IlvScrolledComboBoxLFHandler(lf)
    {}

    virtual void	internalBBox(const IlvScrolledComboBox*,
				     const IlvStringList*,
				     IlvRect& rect,
				     const IlvTransformer* t) const;
    virtual void	scrollBarBBox(const IlvScrolledComboBox*,
				      const IlvStringList*,
				      IlvOrientation dir,
				      IlvRect& bbox,
				      const IlvTransformer* t) const;
    virtual void	drawFrame(const IlvScrolledComboBox*,
				  const IlvStringList*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual IlBoolean	allowSelectWithMove() const;
    virtual IlBoolean	handleEvent(IlvScrolledComboBox*, IlvEvent&) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvScrolledComboBox : public IlvComboBox
{
    friend class IlvDefaultScrolledComboBoxLFHandler;
public:

    IlvScrolledComboBox(IlvDisplay* display,
			const IlvPoint& point,
			const char* label,
			const char* const* labels = 0,
			IlUShort count = 0,
			IlUShort thickness = IlvDefaultGadgetThickness,
			IlvPalette* palette = 0);
    IlvScrolledComboBox(IlvDisplay* display,
			const IlvRect& rect,
			const char* label,
			const char* const* labels = 0,
			IlUShort count = 0,
			IlUShort thickness = IlvDefaultGadgetThickness,
			IlvPalette* palette = 0);

    virtual ~IlvScrolledComboBox();

    inline
    IlvStringList*	getStringList() const { return _list; }

    virtual const char*	getDefaultInteractor() const;

    inline IlUShort	getVisibleItems() const { return _visibleItems; }

    void		setVisibleItems(IlUShort count);

    virtual void	showList(IlBoolean grab = IlTrue);

    virtual void	hideList();
    virtual IlBoolean	isListVisible() const;
    virtual void	setListItemSelected(IlShort pos);

    inline
    IlvContainer*	getListView() const { return _listView; }
    inline void		removeListView() { _listView = 0; }
    inline IlBoolean	isGrabbed() const { return _grabbed; }
    virtual void	setPalette(IlvPalette*);
    virtual void	setFont(IlvFont* fnt);
    virtual IlBoolean	handleEvent(IlvEvent& event);

    inline IlvPosition	hasLargeList() const { return _largeList; }

    inline void		enableLargeList(IlvPosition pos = IlvLeft)
			{
			    _largeList = pos;
			}

    inline void		disableLargeList() { _largeList = IlvBadPosition; }

    // ------------------------------------------------------------
    // Bidi interface
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    virtual IlBoolean	setBidiContext(IlvBidiContext*);

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvScrolledComboBox);

protected:
    virtual IlBoolean	iHandleEvent(IlvEvent& event);
    void		makeList(const char* const* labels, IlUShort count);
    void		makeListView(const IlvRect&);

    IlvStringList*	_list;
    IlUShort		_visibleItems;
    IlBoolean		_showList;
    IlvContainer*	_listView;
    IlBoolean		_grabbed;
    IlvPosition		_largeList;

    static IlvScrolledComboBox*	_currentComboBox;

public:
    DeclareGraphicAccessors();

    inline static
    IlvScrolledComboBox* GetCurrentComboBox() { return _currentComboBox; }
    void		adjustStringList();

    static IlSymbol*	_nbVisibleItemsValue;
    static IlSymbol*	_visibleItemsValue;
    static IlSymbol*	_largeListValue;

};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(scombo);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/scombo.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/scombo.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/scombo.h>
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#    include <ilviews/gadgets/winxp/scombo.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/scombo.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Scombo_H */
