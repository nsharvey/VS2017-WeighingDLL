// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/hsheet.h
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
// Declaration of the IlvHierarchicalSheet class
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Hsheet_H
#define __Ilv_Gadgets_Hsheet_H

#if !defined(__Ilv_Gadgets_Sheet_H)
#  include <ilviews/gadgets/sheet.h>
#endif
#if !defined(__Ilv_Gadgets_Tree_H)
#  include <ilviews/gadgets/tree.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#  include <ilviews/gadgets/macrosadv.h>
#endif

#define IlvDefaultSheetIndent 10

class IlvHierarchicalSheet;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvHierarchicalSheetLFHandler
    : public IlvObjectLFHandler
{
public:
    IlvHierarchicalSheetLFHandler(IlvLookFeelHandler* lfh);

    virtual IlvPalette*
	getGridPalette(const IlvHierarchicalSheet* hsheet) const = 0;
    virtual IlvPalette*
	getLinkPalette(const IlvHierarchicalSheet* hsheet) const = 0;
    virtual IlvPalette*
	getSelectedLinkPalette(const IlvHierarchicalSheet* hsheet) const = 0;
    virtual void	drawButton(const IlvHierarchicalSheet* hsheet,
				   IlvPort* dst,
				   const IlvTreeGadgetItem* item,
				   const IlvRect& rect,
				   const IlvRegion* clip) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDefaultHierarchicalSheetLFHandler
    : public IlvHierarchicalSheetLFHandler
{
public:
    IlvDefaultHierarchicalSheetLFHandler(IlvLookFeelHandler* lf)
	: IlvHierarchicalSheetLFHandler(lf)
    {}

    virtual void	drawButton(const IlvHierarchicalSheet*,
				   IlvPort*,
				   const IlvTreeGadgetItem*,
				   const IlvRect&,
				   const IlvRegion*) const;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvHierarchicalSheet : public IlvSheet
{
    friend class IlvHierarchicalSheetItem;
    friend class IlvHierarchicalGadgetItemHolder;

public:

    IlvHierarchicalSheet(IlvDisplay* display,
			 const IlvRect& rect,
			 IlUShort nbcol,
			 IlUShort nbrow,
			 IlvDim xgrid = IlvDefaultMatrixWidth,
			 IlvDim ygrid = IlvDefaultMatrixHeight,
			 IlvDim thickness = IlvDefaultGadgetThickness,
			 IlBoolean  showVSB = IlTrue,
			 IlBoolean  showHSB = IlTrue,
			 IlvPalette* palette = 0);

    ~IlvHierarchicalSheet();
    // ____________________________________________________________
    void		removeRow(IlUShort r, IlBoolean destroy = IlTrue);

    inline IlvDim	getIndent() const { return _indent; }

    void		setIndent(IlvDim indent, IlBoolean redraw = IlTrue);

    IlUInt		getItemsCount() const;

    IlUInt		getVisibleItemsCount() const;

    void		removeItem(IlvTreeGadgetItem* item,
				   IlBoolean destroy = IlTrue);

    void		removeAllItems();

    void		addItem(IlvTreeGadgetItem* parent,
				IlvTreeGadgetItem* item,
				IlInt index = -1);

    IlvTreeGadgetItem*	addItem(IlvTreeGadgetItem* parent,
				const char* label,
				IlInt index = -1,
				IlvBitmap* bitmap = 0,
				IlvBitmap* selectionBitmap = 0);

    inline IlBoolean	areLinesVisible() const { return _hasLines; }

    void		showLines(IlBoolean value, IlBoolean redraw = IlTrue);

    virtual IlvPalette*	getLinkPalette() const;

    void		setLinkPalette(IlvPalette* palette);

    virtual IlvPalette*	getSelectedLinkPalette() const;
    void		setSelectedLinkPalette(IlvPalette*);

    virtual IlUShort	getTreeColumn() const;

    IlvTreeGadgetItem*	getTreeItem(IlUShort row) const;

    IlUShort		getItemRow(IlvTreeGadgetItem* item) const;

    void		shrinkItem(IlvTreeGadgetItem* item);

    void		expandItem(IlvTreeGadgetItem* item,
				   IlBoolean expandAll = IlFalse);

    virtual void	fitHeightToSize(IlUShort = 0);
    virtual IlBoolean	handleResizeColumn(IlvEvent&);
    virtual IlBoolean	handleMatrixEvent(IlvEvent&);
    virtual void	updateLook();
    virtual void	changeLayoutAttributes(IlAny, IlAny);
    virtual void	setBackground(IlvColor* color);
    virtual void	setForeground(IlvColor* color);
    virtual void	setPalette(IlvPalette* palette);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	reinitialize(IlUShort c, IlUShort r);

    inline
    IlvTreeGadgetItem*	getRoot() const { return _root; }

    static
    IlSymbol*		ShrinkCallbackType();
    inline
    static IlSymbol*	ShrinkSymbol() { return ShrinkCallbackType(); }

    static IlSymbol*	ExpandCallbackType();
    inline
    static IlSymbol*	ExpandSymbol() { return ExpandCallbackType(); }

    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlSymbol* const**) const;

    DeclareGraphicAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvHierarchicalSheet);

protected:
    void		makePalette();
    void		recomputeScrollBars();

    virtual void	expand(IlvTreeGadgetItem* item);

    virtual void	shrink(IlvTreeGadgetItem* item);

    virtual void	drawButton(IlvPort*,
				   IlvTreeGadgetItem*,
				   const IlvRect&,
				   const IlvRegion*) const;
    void		itemRemoved(IlUShort row);
    void		itemInserted(IlvTreeGadgetItem* item,
				     IlUShort &row);
    void		setRowVisible(IlUShort row, IlBoolean show);
    inline
    IlvTreeGadgetItemHolder* getTreeHolder() const
			{
			    return _treeHolder;
			}
    IlvTreeGadgetItem*		_root;
    IlvTreeGadgetItemHolder*	_treeHolder;
    IlvPalette*			_linkPalette;
    IlvPalette*			_selectedLinkPalette;
    IlvDim			_indent;
    IlBoolean			_hasLines;

private:
    void		mapTreeOnSheet(IlvTreeGadgetItem*, IlUShort&);
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(hsheet);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/hsheet.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/hsheet.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/hsheet.h>
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#    include <ilviews/gadgets/winxp/hsheet.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/hsheet.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Hsheet_H */
