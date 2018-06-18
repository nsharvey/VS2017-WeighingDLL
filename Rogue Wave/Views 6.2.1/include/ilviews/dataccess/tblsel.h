// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/tblsel.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliMultiSelection and IliTableSelection classes
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Tblsel_H
#define __Ili_Tblsel_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ili_Macros_H)
#  include <ilviews/dataccess/macros.h>
#endif

// --------------------------------------------------------------------------
enum IliTableSelectionType {
    IliSelectNone,
    IliSelectAll,
    IliSelectColumn,
    IliSelectRow,
    IliSelectCell
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliMultiSelection
{
public:
    IliMultiSelection();
    IliMultiSelection(const IliMultiSelection&);
    ~IliMultiSelection();

    IliMultiSelection& operator =(const IliMultiSelection&);
    int operator	==(const IliMultiSelection&) const;
    inline int operator	!=(const IliMultiSelection& multi) const
	{ return !(*this == multi); }

    void		read(IL_STDPREF istream&);
    void		write(IL_STDPREF ostream&) const;

    inline void		reset() { _count = 0; }

    IlInt		getRangesCount() const { return _count; }
    void		getRange(IlInt, IlInt&, IlInt&) const;
    void		addRange(IlInt, IlInt);
    void		removeRange(IlInt, IlInt);

    IlInt		getPointsCount() const;
    IlInt		getPoint(IlInt) const;
    inline void		addPoint(IlInt pt) { addRange(pt, pt); }
    inline void		removePoint(IlInt pt) { removeRange(pt, pt); }

    IlBoolean		contains(IlInt) const;
    IlBoolean		containsRange(IlInt, IlInt) const;
    IlBoolean		contains(const IliMultiSelection&) const;

    IlInt		getClosestPoint(IlInt) const;

    void		pointsInserted(IlInt, IlInt);
    void		pointInserted(IlInt);
    void		pointDeleted(IlInt);
    void		pointMoved(IlInt, IlInt);

private:
    class Range {
    public:
	IlInt	_from;
	IlInt	_to;
    };
    Range*		_ranges;
    IlInt		_count;
    IlInt		_size;

    void		tidy();
    void		expand();
    void		init();
    void		insert(IlInt, IlInt, IlInt);
    void		replace(IlInt, IlInt, IlInt, IlInt);
    void		deleteRange(IlInt, IlInt);
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableSelection
{
public:
    IliTableSelection(IliTableSelectionType type = IliSelectNone,
		      IlInt rowno = 0,
		      IlInt colno = 0)
    {
	_type = type;
	_rowno = rowno;
	_colno = colno;
    }

    IliTableSelection& operator=(const IliTableSelection&);
    void		read(IL_STDPREF istream&);
    void		write(IL_STDPREF ostream&) const;

    inline int operator==(const IliTableSelection& o) const
	{ return equiv(o); }
    inline int operator!=(const IliTableSelection& o) const
	{ return !equiv(o); }
    inline IliTableSelectionType getType() const { return _type; }
    void		setType(IliTableSelectionType type);
    inline IlInt	getRow() const { return _rowno; }
    void		setRow(IlInt rowno);
    inline IlInt	getColumn() const { return _colno; }
    void		setColumn(IlInt colno);
    inline IlBoolean	isEmpty() const { return _type == IliSelectNone; }
    inline IlBoolean	isFull() const { return _type == IliSelectAll; }
    inline IlBoolean	isCell() const { return _type == IliSelectCell; }
    inline IlBoolean	isRow() const { return _type == IliSelectRow; }
    inline IlBoolean	isColumn() const { return _type == IliSelectColumn; }
    inline IlBoolean	isRowOrCell() const { return isRow() || isCell(); }
    inline IlBoolean	isColumnOrCell() const
    {
	return isColumn() || isCell();
    }

    IlBoolean		equiv(const IliTableSelection&) const;
    IlBoolean		isValid() const;

    // Multi-selection
    inline IlBoolean	isMulti() const
	{ return (_multi.getRangesCount() > 0); }
    void		reset(IliTableSelectionType);
    IlInt		getRowsCount() const;
    IlInt		getRowAt(IlInt idx) const;
    void		addRow(IlInt rowno);
    void		removeRow(IlInt rowno);
    IlInt		getColumnsCount() const;
    IlInt		getColumnAt(IlInt idx) const;
    void		addColumn(IlInt colno);
    void		removeColumn(IlInt colno);
    IlInt		getRangesCount() const;
    void		getRangeAt(IlInt idx, IlInt& from, IlInt& to) const;
    void		addRange(IlInt from, IlInt to);
    void		removeRange(IlInt from, IlInt to);
    IlBoolean		containsRange(IlInt from, IlInt to) const;
    IlBoolean		contains(const IliTableSelection& sel) const;
    IlBoolean		containsCell(IlInt rowno, IlInt colno) const;
    IlBoolean		containsRow(IlInt rowno) const;
    IlBoolean		containsColumn(IlInt colno) const;

    void		columnInserted(IlInt);
    void		columnDeleted(IlInt);
    void		columnMoved(IlInt, IlInt);

    void		allRowsDeleted();
    void		rowsInserted(IlInt, IlInt);
    void		rowInserted(IlInt);
    void		rowDeleted(IlInt);
    void		rowMoved(IlInt, IlInt);

private:
    IliMultiSelection	_multi;
    IliTableSelectionType _type;
    IlInt		_rowno;
    IlInt		_colno;

    void		empty();
    IlInt&		point();
    IlInt		point() const;
};

#endif /* !__Ili_Tblsel_H */
