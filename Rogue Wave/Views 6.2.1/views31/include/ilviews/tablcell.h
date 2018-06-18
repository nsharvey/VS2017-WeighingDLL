// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/tablcell.h
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
// Defintion of the IlvCellManagerTable class
// Defined in library views31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Tablcell_H
#define __Ilv31_Tablcell_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Cellmgr_H)
#include <ilviews/cellmgr.h>
#endif
#if !defined(__Ilv_Util_Table_H)
#include <ilviews/util/table.h>
#endif

// --------------------------------------------------------------------------
class ILV31VWSEXPORTED IlvCellManagerTable
: public IlvTable
{
public:
    IlvCellManagerTable (IlvCellManager*);

    //drawing properties

    virtual IlBoolean isShowingGrid () const;

    virtual IlBoolean rowSameHeight() const;
    virtual IlBoolean columnSameWidth() const;

    virtual IlvDim getRowHeight (IlUShort rowno) const;
    virtual IlvDim getColumnWidth (IlUShort colno) const;

    //  virtual IlvDim getRowPosition (IlUShort colno) const;
    // virtual IlvDim getColumnPosition (IlUShort rowno) const;

    virtual IlvDim getColumnsDistance (IlUShort fromcol, IlUShort tocol) const;
    virtual IlvDim getRowsDistance (IlUShort fromrow, IlUShort torow) const;

    // -- cell managment
    virtual IlBoolean allowCellMode() const;
    virtual void  cellInfo(IlUShort rowno, IlUShort colno,
			   IlUShort& startrow, IlUShort& startcol,
			   IlUShort& nbrow, IlUShort& nbcol ) const;
    // -- drawing

    virtual void drawItem (IlvPort* dst,
			   IlUShort rowno,
			   IlUShort colno,
			   const IlvRect& itembbox,
			   const IlvRect& clip) const;

    // redrawing methods
    virtual void invalidateRect(IlvPort*, const IlvRect&) const;
    virtual void copyArea(IlvSystemPort*, const IlvRect&, const IlvPoint&) const;
private:
    IlvCellManager* _cellmgr;

};

#endif /* !__Ilv31_Tablcell_H */
