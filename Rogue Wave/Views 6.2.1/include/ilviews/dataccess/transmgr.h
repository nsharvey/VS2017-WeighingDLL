// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/transmgr.h
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
// Declaration of the IliTransactionManager class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Transmgr_H
#define __Ili_Transmgr_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ili_Tblbuf_H)
#  include <ilviews/dataccess/tblbuf.h>
#endif
#if !defined(__Ili_Tblptr_H)
#  include <ilviews/dataccess/tblptr.h>
#endif

class IliTable;

// --------------------------------------------------------------------------
enum IliRowStatus {
    IliNotARow,
    IliRegularRow,
    IliInsertedRow,
    IliUpdatedRow,
    IliDeletedRow
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliRowStatusI
{
public:
    IliRowStatusI(IliTable*, IliRowStatus = IliNotARow);
    ~IliRowStatusI();

private:
    IliTable*		_table;
    IliRowStatus	_prevStatus;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTransactionManager
    : public IliRefCounted
{
public:
    IliTransactionManager();

    static
    IliTransactionManager* Get(const char* name, IlBoolean createIt = IlFalse);

    static IlInt	Count();
    static
    IliTransactionManager* At(IlInt idx);

    static
    IliTransactionManager* ByName(const char*);
    IlBoolean		hasAName() const;

    const char*		getName() const;

    // -- Operations

    enum EventType {
	UndefinedEvent,
	InsertRowEvent,
	UpdateRowEvent,
	DeleteRowEvent,
	MoveRowEvent,
	ExchangeRowsEvent
    };

    IlInt		getEventCount() const;

    IliTable*		getEventTable(IlInt idx) const;

    EventType		getEventType(IlInt idx) const;

    IlBoolean		isStarted() const;

    IlBoolean		isRecording() const;

    void		start();

    void		stop();

    IlBoolean		cancel();

    IlBoolean		accept();
    void		clear();

    // -- Errors
    void		addErrorSink(IliErrorSink* sink);

    void		removeErrorSink(IliErrorSink* sink);

    // -- Implementation
    void		recordInsertRow(IliTable*		tbl,
					IlInt			row,
					const IliTableBuffer*	buff);

    void		recordUpdateRow(IliTable*		tbl,
					IlInt			row,
					const IliTableBuffer*	buff);

    void		recordDeleteRow(IliTable* tbl, IlInt row);

    void		recordMoveRow(IliTable* tbl, IlInt from, IlInt to);

    void		recordExchangeRows(IliTable*	tbl,
					   IlInt	row1,
					   IlInt	row2);

    enum RowRefType {
	ByIndex,
	ByPtr
    };

    class RowRef {
    public:
	RowRef(IliTable*, IlInt index, RowRefType refType);
	RowRef(const RowRef&);

	RowRef& operator	=(const RowRef&);

	IlInt		getRowIndex() const;
    private:
	IlInt		_index;
	IliRowPtr	_rowPtr;
    };

    class Event {
    public:
	EventType	getType() const;
	IliTable*	getTable() const;
	IliRowStatus	getRowStatus() const;
	void		fillBuffer(IliTableBuffer*) const;
	void		fillPrevBuffer(IliTableBuffer*) const;
	IlInt		getRowIndex() const;
	IlInt		getDestinationRowIndex() const;
	IlInt		getPrevToken() const;

	IlBoolean	accept(IliErrorSink* sink);
	IlBoolean	cancel(IliErrorSink* sink);

	ILV_MLK_DECL();

    private:
	IliRowStatus		_status;
	EventType		_type;
	IliTablePtr		_tablePtr;
	RowRef			_rowRef;
	IliCompressedTableBuffer _cBuffer;
	IliCompressedTableBuffer _cPrevBuffer;
	RowRef			_destRowRef;
	IlInt			_prevToken;

	Event(IliTable*			table,
	      EventType			type,
	      IliRowStatus		status,
	      const IliTableBuffer*	buf,
	      IlInt			rowno,
	      RowRefType		rownoType,
	      IlInt			destRowno = -1,
	      RowRefType		destRownoType = ByIndex,
	      const IliTableBuffer*	prevBuf = 0,
	      IlInt			prevToken = -1);
	~Event() {}
	Event& operator =(const Event&) { return *this; }

	IlBoolean	acceptOrCancel(IliErrorSink* sink, IlBoolean acceptP);

	friend class IliTransactionManager;
    };

    const Event*	getEventAt(IlInt idx) const;

    void		forwardErrorMessage(const IliErrorMessage&);

    ILV_MLK_DECL();

protected:
    IlvArray		_events;
    IliString		_name;
    IlBoolean		_isStarted;
    IlBoolean		_isRecording;
    IlvList		_errorSinks;
    IliErrorSink*	_theSink;
    IlBoolean		_inDesignSpace;

    static
    IlvStringHashTable*	_directory;
    static IlvArray*	_enumeration;

    IliTransactionManager(const char* name, IlBoolean inDesignSpace);
    ~IliTransactionManager();

    void		init();
};

#endif /* !__Ili_Transmgr_H */
