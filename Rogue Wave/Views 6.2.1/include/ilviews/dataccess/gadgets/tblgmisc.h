// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/tblgmisc.h
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
// Declaration of the miscellaneous classes for the IliTableGadget class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Tblgmisc_H
#define __Ili_Tblgmisc_H

#ifndef __Ilv_Graphics_Io_H
#  include <ilviews/graphics/io.h>
#endif

#ifndef __Ilv_Base_Gadget_H
#  include <ilviews/base/gadget.h>
#endif

#ifndef __Ili_Collect_H
#  include <ilviews/dataccess/collect.h>
#endif

#ifndef __Ili_Fielditf_H
#  include <ilviews/dataccess/fielditf.h>
#endif

class ILV_DBG_EXPORTED IliTableGadget;

class ILV_DBG_EXPORTED IliTableHeader
{
public:
    IliTableHeader(IliTableGadget*, IlInt token);
    IliTableHeader(IliTableGadget*, const IliTableHeader&);
    IliTableHeader(IliTableGadget*, IlvInputFile&);
    ~IliTableHeader();

    void		write(IlvOutputFile&) const;

    inline IliFieldItf*	getEditor() const { return _editor; }
    void		setEditor(IliFieldItf* e,
				  IlBoolean custom,
				  IlBoolean owner);
    inline IlBoolean	isEditorUserDefined() const
			{
			    return _editorIsUserDefined;
			}
    inline IlBoolean	isEditorOwner() const { return _editorOwner; }

    inline
    IliFieldItf*	getCurrentEditor() const { return _currentEditor; }
    void		setCurrentEditor(IliFieldItf* ce);

    inline IlvPos	getOffset() const { return _offset; }
    inline void		setOffset(IlvPos offset) { _offset = offset; }

    const char*		getLabel() const;
    inline IlvDim	getWidth() const { return _width; }
    inline IlvAlignment getAlign() const
			{
			    return _table->getColumnAlignment(_colno);
			}
    inline IlBoolean	isReadOnly() const
			{
			    return _table->isColumnReadOnly(_colno);
			}
    inline IlBoolean	isVisible() const { return _visible; }
    inline
    const IliFormat&	getFormat() const
			{
			    return _table->getColumnFormat(_colno);
			}
    inline
    const IliInputMask&	getMask() const
			{
			    return _table->getColumnMask(_colno);
			}
    inline IlInt	getMaxLength() const
			{
			    return _table->getColumnMaxLength(_colno);
			}

    inline IlvPos	getLeft(IlvPos start) const
			{
			    return start + _offset;
			}
    inline IlvPos	getRight(IlvPos start) const
			{
			    return getLeft(start) + (IlvPos)getWidth();
			}

    inline IlBoolean	isViewable() const
			{
			    return (getWidth() > 0) && isVisible();
			}

    inline void		iSetWidth(IlvDim w) { _width = w; }
    inline void		iSetVisible(IlBoolean b) { _visible = b; }

    inline IlvDim	iGetOrigWidth() const { return _origWidth; }
    inline void		iSetOrigWidth(IlvDim w) { _origWidth = w; }

    void		reset();
    void		resetColno();
    void		resetEditor();
    void		resetGeometry(IlBoolean origToo,
				      IlBoolean* invalidate = 0);

    IlInt		_colno;       // colno in underlying table
    IlInt		_colToken;    // column token in underlying table
    IlInt		_index;       // position in table gadget
    IliTableHeader*	_next;
    IliTableHeader*	_prev;
    IliTableHeader*	_nextShown;
    IlBoolean		_isShown;

    IlvValueInterface*	getItf();

protected:
    IliTableGadget*	_tableGadget;
    IliTable*		_table;
    IliFieldItf*	_editor;
    IliFieldItf*	_currentEditor;
    IlvValueInterface*	_itf;
    IlvDim		_width;
    IlvDim		_origWidth;
    IlBoolean		_visible;
    IlBoolean		_editorOwner;
    IlBoolean		_editorIsUserDefined;
    IlvPos		_offset;

    void		init();
    void		setGeometry();
};

class ILV_DBG_EXPORTED IliTableHeaderList
{
public:
    IliTableHeaderList();

    void		tidy();

    void		copyFrom(IliTableGadget* tg,
				 const IliTableHeaderList& o);
    void		read(IliTableGadget*, IlvInputFile&);
    void		write(IlvOutputFile&) const;

    IliTableHeader*	atIndex(IlInt index) const;
    IliTableHeader*	atColno(IlInt colno) const;

    IlInt		count() const;
    IlBoolean		isEmpty() const { return _first == 0; }

    IliTableHeader*	getFirstShown() const { return _firstShown; }
    void		setFirstShown(IliTableHeader* h) { _firstShown = h; }

    IliTableHeader*	getLastShown() const { return _lastShown; }
    void		setLastShown(IliTableHeader* h) { _lastShown = h; }

    IliTableHeader*	getFirst() const;
    IliTableHeader*	getLast() const;
    IliTableHeader*	getNext(IliTableHeader*) const;
    IliTableHeader*	getPrev(IliTableHeader*) const;

    IlInt		indexToColno(IlInt index) const;
    IlInt		colnoToIndex(IlInt colno) const;

    void		insertHeader(IliTableHeader*, IlInt index);
    void		deleteHeader(IliTableHeader*);
    void		moveHeader(IliTableHeader*, IlInt to);

    void		reset();
    void		resetColno();
    void		setDefaultEditors();
    void		deleteUnboundHeaders();

    enum Tag {
	HashArrayThreshold = 1
    };

protected:
    IlInt		_count;
    IliTableHeader*	_first;
    IliTableHeader*	_last;
    IliTableHeader*	_firstShown;
    IliTableHeader*	_lastShown;
    IlvArray*		_headers;
    IlvHashTable*	_hash;

    void		detachHeader(IliTableHeader*);
    void		attachHeader(IliTableHeader*, IlInt index);

    void		initHash();
};

struct IliTG_RowsRecord
{
    IlvRect bbox;
    IlvRect cornerRect, markersRect, headersRect, cellsRect;
    IlInt firstRow;
    IlInt rowsCnt;
    IlBoolean lastRowClipped;
    IlvPos y1;
    IlvPos y2;
    IlvPos x1;
};

struct IliTG_DrawRecord
{
    IliTG_RowsRecord rr;
    IlvRect clipRect;
    IlvRegion clipRgn;
    IlvPort* dst;
    const IlvTransformer* t;
};

struct IliTG_ScrollRecord
{
    IlInt targetIndex;
    IlInt left;
    IlInt right;
    IlInt sbCount;
    IlInt sbShown;
    IlInt sbCurrent;
    IlInt sbTargetColno;
};


#endif
