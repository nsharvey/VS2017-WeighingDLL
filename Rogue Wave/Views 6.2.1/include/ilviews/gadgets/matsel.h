// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/matsel.h
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
// Declaration of the classes IlvMatrixSelection
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Matsel_H
#define __Ilv_Gadgets_Matsel_H

#if !defined(__Ilv_Gadgets_Matrix_H)
#include <ilviews/gadgets/matrix.h>
#endif

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMatrixCoordinate
{
public:
    IlvMatrixCoordinate(IlUShort row = 0, IlUShort col = 0);
    ~IlvMatrixCoordinate();

    IlUShort		getRow() const;
    IlUShort		getColumn() const;
    IlvAbstractMatrixItem* getItem(const IlvMatrix* matrix) const;

protected:
    IlUShort		_row;
    IlUShort		_column;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMatrixRowSelection
{
public:
    IlvMatrixRowSelection(IlUShort row = 0,
			  IlUShort col1 = 0,
			  IlUShort col2 = 0);
    ~IlvMatrixRowSelection();

    IlInt			isNotContain(IlUShort row, IlUShort col);

    void			setPrevious(IlvMatrixRowSelection*);
    IlvMatrixRowSelection*	getPrevious();

    void			setNext(IlvMatrixRowSelection*);
    IlvMatrixRowSelection*	getNext();

    void			setRow(IlUShort row);
    IlUShort			getRow() const;

    void			setColumns(IlUShort col1, IlUShort col2);
    IlUShort			getFirstColumn() const;
    IlUShort			getLastColumn() const;
    IlUShort			getColumnCount() const;

    IlBoolean			mergeColumn(IlUShort);
    IlBoolean			mergeSelection(IlvMatrixRowSelection* after);
    void			cut(IlUShort col);

    void			dump();

    void			disconnect();
    void			connectTo(IlvMatrixRowSelection*,
					  IlBoolean isRef = IlFalse);

protected:
    IlvMatrixRowSelection*	_previous;
    IlvMatrixRowSelection*	_next;

    IlUShort			_row;
    IlUShort			_firstColumn;
    IlUShort			_lastColumn;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMatrixSelection
{
public:
     IlvMatrixSelection();
    virtual ~IlvMatrixSelection();

    IlvMatrixRowSelection*	getSelection() const;

    IlvMatrixCoordinate**	getSelection(IlUShort& count) const; 

    void		cleanArraySelection(IlvMatrixCoordinate** array,
					    IlUShort count);

    virtual void	addSelection(IlUShort row, IlUShort col);

    virtual void	delSelection(IlUShort row, IlUShort col);

    virtual void	addSelectionRow(IlUShort row, IlUShort cols);

    virtual void	delSelectionRow(IlUShort row);

    virtual void	addSelectionColumn(IlUShort col, IlUShort rows);

    virtual void	delSelectionColumn(IlUShort col);

    virtual void	deselectAll();

    virtual void	itemReplaced(IlUShort row, IlUShort col);

    virtual void	itemDeleted(IlUShort row, IlUShort col);

    virtual void	rowInserted(IlUShort row, IlUShort count = 1);

    virtual void	rowDeleted(IlUShort row);

    virtual void	columnInserted(IlUShort col, IlUShort count = 1);

    virtual void	columnDeleted(IlUShort col);

    virtual void	startIgnoreNotification();

    virtual void	stopIgnoreNotification();

    void		dump();

protected:
    IlvMatrixRowSelection*	_first;
    IlInt			_ignoreMode;

    IlvMatrixRowSelection*	getLocation(IlUShort row,
					    IlUShort col,
					    IlInt&);
    IlBoolean		optimizeFrom(IlvMatrixRowSelection*);
};

#endif
