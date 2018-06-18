// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/table.h
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
// Definition of the IlvTable class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Table_H
#define __Ilv_Util_Table_H

#if !defined(__Ilv_Util_Util_H)
#include <ilviews/util/util.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTable
{
public:
    IlvTable();
    // ____________________________________________________________
    //drawing properties
    virtual IlBoolean	isShowingGrid () const = 0;
    virtual IlBoolean	rowSameHeight() const = 0;
    virtual IlBoolean	columnSameWidth() const = 0;
    virtual IlvDim	getRowHeight(IlUShort rowno) const = 0;
    virtual IlvDim	getColumnWidth(IlUShort colno) const = 0;
    virtual IlvDim	getColumnsDistance(IlUShort fromcol,
					   IlUShort tocol) const;
    virtual IlvDim	getRowsDistance(IlUShort fromrow,
					IlUShort torow) const;

    IlBoolean		pointToPosition(const IlvRect& bbox,
					const IlvPoint& p,
					IlUShort  firstcol,
					IlUShort  firstrow,
					IlUShort  nbcol,
					IlUShort  nbrow,
					IlUShort& colno,
					IlUShort& rowno)  const;
    void		getVisibleItems(const IlvRect& bbox,
					IlUShort  firstcol,
					IlUShort  firstrow,
					IlUShort  nbcol,
					IlUShort  nbrow,
					IlUShort& fromx,
					IlUShort& tox,
					IlUShort& fromy,
					IlUShort& toy) const;

    // -- cell managment
    virtual IlBoolean	allowCellMode() const = 0;
    virtual void	cellInfo(IlUShort  rowno,    IlUShort  colno,
				 IlUShort& startrow, IlUShort& startcol,
				 IlUShort& nbrow,    IlUShort& nbcol) const;
    IlBoolean		cellBBox(IlvRect bbox,
				 IlUShort row,      IlUShort col,
				 IlUShort startrow, IlUShort startcol,
				 IlvRect& rect) const;

    // -- drawing
    virtual void	drawItem(IlvPort*       dst,
				 IlUShort       rowno,
				 IlUShort       colno,
				 const IlvRect& itembbox,
				 const IlvRect& clip) const = 0;

    // redrawing methods
    virtual void	invalidateRect(IlvPort* dst,
				       const IlvRect& rect) const;
    virtual void	copyArea(IlvSystemPort*  dst,
				 const IlvRect&  rect,
				 const IlvPoint& at) const;
    void		draw(IlvPort*  dst,
			     IlUShort firstcol,
			     IlUShort firstrow,
			     IlUShort nbCol,
			     IlUShort nbRow,
			     IlvPalette* palette,
			     const IlvRect& bbox,
			     const IlvRect& clip) const;
    void		scrollTo(IlvSystemPort* dst,
				 IlUShort       oldrow,
				 IlUShort       oldcolumn,
				 IlUShort       row,
				 IlUShort       column,
				 const IlvRect& bbox);
    void		resizeRow(IlvSystemPort* dst,
				  const IlvRect& bbox,
				  IlUShort       rw,
				  IlvPos         delta,
				  IlUShort       firstrow) const;
    void		resizeColumn(IlvSystemPort* dst,
				     const IlvRect& bbox,
				     IlUShort       col,
				     IlvPos         delta,
				     IlUShort      firstcol) const;

    virtual IlBoolean	isRightToLeft() const; // ILVBIDI

private:
    IlUShort		posInColumns(IlvDim x, IlUShort, IlUShort) const;
    IlUShort		posInRows(IlvDim y, IlUShort, IlUShort) const;

    void		drawGrid(IlvPort* dst,
				 IlUShort fromx,
				 IlUShort tox ,
				 IlUShort fromy,
				 IlUShort toy,
				 IlUShort firstcol,
				 IlUShort firstrow,
				 IlUShort nbcol,
				 IlUShort nbrow,
				 IlvPalette* palette,
				 const IlvRect& bbox,
				 const IlvRect* clip) const;

};

#endif /* !__Ilv_Util_Table_H */
