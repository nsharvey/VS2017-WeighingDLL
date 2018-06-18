// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/gridrect.h
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
// Declaration of the IlvGridRectangle class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Gridrect_H
#define __Ilv_Graphics_Gridrect_H

#if !defined(__Ilv_Graphics_Rectang_H)
#include <ilviews/graphics/rectangl.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGridRectangle : public IlvFilledRectangle
{
public:
    IlvGridRectangle(IlvDisplay*	display,
		     const IlvRect&	drawrect,
		     IlvDim		nbColumns,
		     IlvDim		nbRows,
		     IlvPalette*	palette = 0)
	: IlvFilledRectangle(display, drawrect, palette),
	  _nbColumns(nbColumns),
	  _nbRows(nbRows),
	  _fixedSize(IlTrue)
    {}

    virtual void	draw(IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;
    inline IlvDim	getColumns() const   { return _nbColumns; }
    inline void		setColumns(IlvDim columns) { _nbColumns = columns; }
    inline IlvDim	getRows() const   { return _nbRows; }
    inline void		setRows(IlvDim rows)    { _nbRows = rows; }
    inline IlBoolean	getFixedSize() const { return _fixedSize; }
    inline void		setFixedSize(IlBoolean fixed) { _fixedSize = fixed; }

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvGridRectangle);

protected:
    IlvDim		_nbColumns;
    IlvDim		_nbRows;
    IlBoolean		_fixedSize;

public:
    DeclareGraphicAccessors();
    static IlSymbol*	_fixedSizeValue;
    static IlSymbol*	_rowsValue;
    static IlSymbol*	_columnsValue;
};

ILVVWSMODULEINIT(g0gridrect);
#endif /* !__Ilv_Graphics_Gridrect_H */
