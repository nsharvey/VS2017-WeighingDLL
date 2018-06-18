// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/amatrix.h
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
// Declaration of the IlvAbstractMatrix class
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Amatrix_H
#define __Ilv_Gadgets_Amatrix_H

#if !defined(__Ilv_Gadgets_Scgadget_H)
#  include <ilviews/gadgets/scgadget.h>
#endif

class IlvMatrixTable;
class IlvAbstractMatrix;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvAbstractMatrixLFHandler
    : public IlvObjectLFHandler
{
public:
    IlvAbstractMatrixLFHandler(IlvLookFeelHandler* lf);

    virtual IlvPalette*	getGridPalette(const IlvAbstractMatrix*) const = 0;
    virtual void	setMode(IlvAbstractMatrix*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvAbstractMatrix*, IlBoolean) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvAbstractMatrix : public IlvScrolledGadget
{
public:
    ~IlvAbstractMatrix ();

    // -- Properties

    virtual IlUShort	rows() const = 0;

    virtual IlUShort	columns() const = 0;

    virtual IlBoolean	rowSameHeight() const = 0;

    virtual IlBoolean	columnSameWidth() const = 0;

    virtual IlvDim	getRowHeight(IlUShort rowno) const = 0;

    virtual IlvDim	getColumnWidth(IlUShort colno) const = 0;

    virtual IlvDim	getRowPosition(IlUShort row) const;

    virtual IlvDim	getColumnPosition(IlUShort col) const;

    virtual IlvDim	getColumnsDistance(IlUShort fromcol,
					   IlUShort tocol)const;

    virtual IlvDim	getRowsDistance(IlUShort fromrow,
					IlUShort torow) const;

    inline IlUShort	firstRow() const { return _firstRow; }

    inline IlUShort	firstColumn() const { return _firstColumn; }

    inline IlUShort	getNbFixedRow() const { return _nbFixedRow; }

    inline IlUShort	getNbFixedColumn() const {return _nbFixedColumn;}

    void		setNbFixedRow(IlUShort count);

    void		setNbFixedColumn(IlUShort count);

    inline IlBoolean	isShowingGrid() const  { return _showGrid; }

    inline IlBoolean	showGrid(IlBoolean value)
			{
			    _showGrid = value;
			    return _showGrid;
			}

    virtual IlvPalette*	getGridPalette() const;

    virtual void	scrollTo(IlUShort colno, IlUShort rowno);

    void		scrollToRow(IlUShort rowno);

    void		scrollToColumn(IlUShort colno);

    void		adjustFirstVisible (IlBoolean redraw = IlTrue);

    virtual void	applyTransform(const IlvTransformer*t);

    // -- Geometry
    virtual void	scrollBarBBox(IlvDirection dir,
				      IlvRect& bbox,
				      const IlvTransformer* t = 0) const;

    virtual IlBoolean	rowBBox(IlUShort rowno,
				IlvRect& rect,
				const IlvTransformer* t = 0) const;

    virtual IlBoolean	columnBBox(IlUShort colno,
				   IlvRect& rect,
				   const IlvTransformer* t = 0) const;

    virtual IlBoolean	cellBBox(IlUShort colno,
				 IlUShort rowno,
				 IlvRect& rect,
				 const IlvTransformer* t = 0) const;

    virtual IlBoolean	pointToPosition(const IlvPoint& point,
					IlUShort& colno,
					IlUShort& rowno,
					const IlvTransformer* t = 0) const;

    virtual void	getVisibleItems(IlUShort& fromcol,
					IlUShort& tocol,
					IlUShort& fromrow,
					IlUShort& torow,
					const IlvTransformer* t = 0) const;

    virtual void	ensureVisible(IlUShort	colno,
				      IlUShort	rowno,
				      IlBoolean	redraw = IlTrue);

    // -- Cell managment
    inline IlBoolean	allowCellMode() const { return _allowCellMode;}

    virtual void	cellInfo(IlUShort	colno,
				 IlUShort	rowno,
				 IlUShort&	startcol,
				 IlUShort&	startrow,
				 IlUShort&	nbcol,
				 IlUShort&	nbrow) const;

    // -- Drawing
    virtual void	drawRect(const IlvRect&		clip,
				 IlvPort*		dst,
				 const IlvTransformer*	t = 0) const;
    virtual void	drawGadgetContents(IlvPort* dst,
					   const IlvTransformer* t = 0,
					   const IlvRegion* clip = 0) const;
    virtual void	drawItem(IlvPort*	dst,
				 IlUShort	colno,
				 IlUShort	rowno,
				 const IlvRect&	itembbox,
				 const IlvRect&	clip) const;

    // redrawing methods
    virtual void	invalidateColumn(IlUShort colno) const;

    virtual void	invalidateRow(IlUShort rowno) const;

    virtual void	invalidateRect(const IlvRect& rect) const;

    virtual void	copyArea(const IlvRect&		rect,
				 const IlvPoint&	at) const;

    // Event handling
    virtual IlBoolean	handleGadgetEvent(IlvEvent&);

    virtual IlBoolean	handleMatrixEvent(IlvEvent& event);

    virtual IlBoolean	classFocusable() const;

    IlUShort		posInColumns(IlvDim x) const;
    IlUShort		posInRows(IlvDim y) const;
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    inline
    IlvMatrixTable*	getMatrixTable() const { return _table; }

    // -- For compatibility
    inline IlBoolean	isUsingRelief() const { return isShowingFrame(); }
    inline IlBoolean	useRelief(IlBoolean v)
			{
			    showFrame(v, IlFalse);
			    return v;
			}
    inline IlBoolean	isFillingBackground() const
			{
			    return !isTransparent();
			}
    inline IlBoolean	fillBackground(IlBoolean v)
			{
			    setTransparent(!v);
			    return v;
			}
    virtual void	computeVerticalScrollbarRect(IlvRect& rect,
						const IlvTransformer* t) const;
    virtual void	computeHorizontalScrollbarRect(IlvRect& rect,
						const IlvTransformer* t) const;
    virtual
    IlvScrollBar*	newScrollBar(IlvPosition direction);
    virtual void	scrollBarsHaveMoved(IlInt where, IlvPosition dir);

    virtual void	changeLayoutAttributes(IlAny, IlAny);

    DeclareGraphicAccessors();

    static IlSymbol*	_rowCountValue;
    static IlSymbol*	_columnCountValue;
    static IlSymbol*	_allowCellModeValue;
    static IlSymbol*	_showGridValue;
    static IlSymbol*	_useReliefValue;
    static IlSymbol*	_fillBackgroundValue;
    static IlSymbol*	_fixedColumnCountValue;
    static IlSymbol*	_fixedRowCountValue;

    // -- New scrolling methods
    virtual void	scrollBarHasMoved(IlvDirection pos);

private:
    IlvMatrixTable*	_table;

protected:
    // Persistent members
    IlBoolean		_allowCellMode;
    IlBoolean		_showGrid;
    IlUShort		_nbFixedRow;
    IlUShort		_nbFixedColumn;
    IlUShort		_firstRow;
    IlUShort		_firstColumn;

    void		computeAreas(IlvRect&			fixedRect,
				     IlvRect&			fixedcol,
				     IlvRect&			fixedrow,
				     IlvRect&			matrix,
				     const IlvTransformer*	t) const;

    // -- New scrolling methods
    virtual
    IlvScrollBar*	createScrollBar(const IlvRect&	r,
					IlvDirection	dir,
					IlUShort	t,
					IlvPalette*	p);
    virtual void	adjustScrollBarValue(IlvScrollBar*	sb,
					     IlvDirection	dir);
    virtual void	adjustFromScrollBar(const IlvScrollBar*	sb,
					    IlvDirection	dir);
    virtual void	beforeAdjustScrollBarVisibility(const IlvRect&);
    virtual void	afterAdjustScrollBarVisibility(const IlvRect&);

    IlvAbstractMatrix(IlvDisplay*	display,
		      const IlvRect&	rect,
		      IlUShort		thickness = IlvDefaultGadgetThickness,
		      IlvPalette*	palette   = 0);
    IlvAbstractMatrix(const IlvAbstractMatrix&);
    IlvAbstractMatrix(IlvInputFile& is, IlvPalette* palette);

    DeclareLazyTypeInfo();
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(amatrix);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/amatrix.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/amatrix.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Amatrix_H */
