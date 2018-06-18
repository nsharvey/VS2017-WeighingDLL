// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/table.h
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
// Declaration of the IliTable class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Table_H
#define __Ili_Table_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#  include <ilviews/intrface/value.h>
#endif
#if !defined(__Ili_Error_H)
#  include <ilviews/dataccess/error.h>
#endif
#if defined(__Ili_Schema_H)
#  include <ilviews/dataccess/schema.h>
#endif
#if !defined(__Ili_Value_H)
#  include <ilviews/dataccess/value.h>
#endif
#if !defined(__Ili_Param_H)
#  include <ilviews/dataccess/param.h>
#endif
#if !defined(__Ili_Tblbuf_H)
#  include <ilviews/dataccess/tblbuf.h>
#endif
#if !defined(__Ili_Tblsel_H)
#  include <ilviews/dataccess/tblsel.h>
#endif
#if !defined(__Ili_Tblprop_H)
#  include <ilviews/dataccess/tblprop.h>
#endif
#if !defined(__Ili_Tblptr_H)
#  include <ilviews/dataccess/tblptr.h>
#endif
#if !defined(__Ili_Transmgr_H)
#  include <ilviews/dataccess/transmgr.h>
#endif

// --------------------------------------------------------------------------
#ifdef DOXYGEN_GENERATION
IlInt IliAscOrder(IlInt colno);
#else
#define IliAscOrder(col)   col
#endif

#ifdef DOXYGEN_GENERATION
IlInt IliDescOrder(IlInt colno);
#else
#define IliDescOrder(col)  (-col - 2)
#endif

typedef int (* IliCompareFunction)(IliTableBuffer*	buf1,
				   IliTableBuffer*	buf2,
				   const IlInt*		columns,
				   IlInt		colCount,
				   IlAny		userData);

class ILVVWSEXPORTED IlvPalette;
class ILV_INF_EXPORTED IliTable;

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliFloatingTableSelection
    : public IliTableSelection,
      public IliRefCounted
{
public:
    const IliTable*	getTable() const;

protected:
    friend class IliTable;

    IliTablePtr		_tablePtr;

    IliFloatingTableSelection(const IliTablePtr& tblPtr);
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableColumn
    : public IliColumn
{
public:
    IliTableColumn();
    IliTableColumn(const IliTableColumn&);
    IliTableColumn(IL_STDPREF istream&);
    ~IliTableColumn();

    IliDeclareTypeInfo(IliTableColumn);

    virtual void	write(IL_STDPREF ostream&) const;
    int operator	==(const IliTableColumn&) const;

    inline const char*	getForeignDataSourceName() const
	{ return _foreignDataSourceName; }
    inline void		setForeignDataSourceName(const char* n)
	{ _foreignDataSourceName = n; }

    inline IliTable*	getForeignTable() const	{ return _foreignTable; }
    inline void		setForeignTable(IliTable* t) { _foreignTable = t; }

    inline IlBoolean	isForeignTableOwner() const { return !!_isTableOwner; }
    inline void		setForeignTableOwner(IlBoolean o)
	{ _isTableOwner = !!o; }

    inline const char*	getValueColumn() const { return _valueColumn; }
    inline void		setValueColumn(const char* v) { _valueColumn = v; }

    inline const char*	getDisplayColumn() const { return _displayColumn; }
    inline void		setDisplayColumn(const char* d)	{ _displayColumn = d; }

    inline IlBoolean	isConstrained() const { return !!_isConstrained; }
    inline void		setConstrained(IlBoolean c) { _isConstrained = c; }

    inline IlBoolean	isCompletionEnabled() const { return !!_completionOn; }
    inline void		enableCompletion(IlBoolean e) { _completionOn = e; }

protected:
    IliString		_foreignDataSourceName;
    IliTable*		_foreignTable;
    IliString		_valueColumn;
    IliString		_displayColumn;
    IlBoolean		_isTableOwner;
    IlBoolean		_isConstrained;
    IlBoolean		_completionOn;
};

IliDeclareTypeInit_exp(ILV_INF_EXPORTED,IliTableColumn);

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTable
    : public IliSchema
{
protected:
    virtual ~IliTable();

public:
    enum Index {
	ALL_INDEX		= -1,
	INSERT_ROW_INDEX	= -2,
	VOID_ROW_INDEX		= -3
    };

    IliDeclareDTypeInfo(IliTable);

    virtual void	write(IL_STDPREF ostream&) const;
    int operator	==(const IliTable&) const;

    virtual void	deleteEverything(IlBoolean = IlTrue);

    IliTablePtr		getTablePtr() const;
    IliTablePtr		getTablePtr();

    // Properties
    IlBoolean		isReadOnly() const;
    virtual void	setReadOnly(IlBoolean readOnly);

    // IO
    IliTable*		copyTable() const;
    static IliTable*	ReadTable(IlvDisplay* disp,
				  IL_STDPREF istream& input);
    void		writeTable(IL_STDPREF ostream& output) const;

    // Buffers
    IliTableBuffer*	getBuffer();
    void		releaseBuffer(IliTableBuffer* buff);

    // Parameters
    IlvGadgetHolder*	getGadgetHolder() const;
    void		setGadgetHolder(IlvGadgetHolder* gadHold);
    IlInt		getParametersCount() const;
    IlInt		getParameterIndex(const char* name) const;
    const char*		getParameterName(IlInt paramno) const;
    void		setParameterName(IlInt paramno, const char* name);
    const IliDatatype*	getParameterType(IlInt paramno) const;
    void		setParameterType(IlInt			paramno,
					 const IliDatatype*	type);
    IlInt		getParameterMaxLength(IlInt paramno) const;
    void		setParameterMaxLength(IlInt paramno, IlInt maxlen);
    const char*		getParameterDataSourceName(IlInt paramno) const;
    void		setParameterDataSourceName(IlInt	paramno,
						   const char*	dsname);
    const char*		getParameterColumnName(IlInt paramno) const;
    void		setParameterColumnName(IlInt		paramno,
					       const char*	colname);
    IliValue		getParameterValue(IlInt paramno) const;
    IliValue		getParameterValue(IliName paramName) const;
    void		setParameterValue(IlInt			paramno,
					  const IliValue&	value);
    void		setParameterValue(IliName		paramName,
					  const IliValue&	value);
    IliValue		getParameterDataSourceValue(IlInt paramno) const;
    IlInt		appendParameter(const char*		paramName,
					const IliDatatype*	type,
					IlInt			maxlen = -1);
    void		deleteParameter(IlInt paramno);
    IlvValueInterface*	getParameterItf(IlInt paramno) const;

    // Columns
    const char*		getColumnForeignDataSourceName(IlInt colno) const;
    void		setColumnForeignDataSourceName(IlInt	   colno,
						       const char* dsname);
    IliTable*		getColumnForeignTable(IlInt colno) const;
    void		setColumnForeignTable(IlInt colno, IliTable* table);
    const char*		getColumnForeignValueColumn(IlInt colno) const;
    void		setColumnForeignValueColumn(IlInt	colno,
						    const char*	name);
    const char*		getColumnForeignDisplayColumn(IlInt colno) const;
    void		setColumnForeignDisplayColumn(IlInt		colno,
						      const char*	name);
    IlBoolean		isColumnValueConstrained(IlInt colno) const;
    void		setColumnValueConstrained(IlInt colno, IlBoolean flag);
    IlBoolean		isColumnCompletionEnabled(IlInt colno) const;
    void		enableColumnCompletion(IlInt colno, IlBoolean flag);
    IliTable*		getColumnEffectiveForeignTable(IlInt colno,
						       IlvGraphicHolder* h =
						       0) const;
    IlBoolean		getColumnDisplayValue(IlInt		colno,
					      const IliValue&	value,
					      IliValue&		displayValue,
					      IlvGraphicHolder*	h = 0);

    // Rows
    IlBoolean		isModified() const;
    virtual void	setModified(IlBoolean flag);
    const char*		getTransactionManagerName() const;
    void		setTransactionManagerName(const char* name);
    IliTransactionManager* getTransactionManager() const;
    void		setTransactionManager(IliTransactionManager* tm);
    virtual void	clearRows();
    virtual IlBoolean	select();
    virtual IlBoolean	isSelectDone() const;
    IliRowPtr		getRowPtr(IlInt rowno = -1) const;

    IliFloatingTableSelection* getFloatingSelection() const;
    void		releaseFloatingSelection(IliFloatingTableSelection*);

    IlBoolean		hasContext() const;
    const IliCellPtr&	getContext() const;
    void		setContext(IliCellPtr& context);
    void		notifyContext();
    virtual IlInt	getRowsCount() const;
    virtual IlBoolean	fetchCompleted() const;
    virtual IlInt	fetchNext(IlInt count = 1);
    virtual IlInt	fetchAll();
    virtual IlBoolean	fetchUpToRow(IlInt rowno);
    virtual
    IliRowStatus	getRowStatus(IlInt rowno) const;
    virtual IlBoolean	rowToBuffer(IlInt rowno, IliTableBuffer*) const;
    virtual IlBoolean	getValue(IlInt		rowno,
				 IlInt		colno,
				 IliValue&	value) const;
    virtual IlBoolean	updateRow(IlInt rowno, IliTableBuffer* buff);
    virtual IlBoolean	insertRow(IlInt rowno, IliTableBuffer* buff);
    virtual IlBoolean	deleteRow(IlInt rowno);
    virtual IlBoolean	moveRow(IlInt from, IlInt to);
    virtual IlBoolean	exchangeRows(IlInt rowno1, IlInt rowno2);
    virtual IlBoolean	updateRowInCache(IlInt rowno, IliTableBuffer* buff);
    virtual IlBoolean	insertRowInCache(IlInt rowno, IliTableBuffer* buff);
    virtual IlBoolean	deleteRowInCache(IlInt rowno);
    virtual IlBoolean	moveRowInCache(IlInt from, IlInt to);
    virtual IlBoolean	exchangeRowsInCache(IlInt rowno1, IlInt rowno2);
    virtual IlBoolean	refreshRow(IlInt rowno);
    virtual IlBoolean	refreshAndLockRow(IlInt rowno);
    IlInt		appendRow(IliTableBuffer* tblBuf);
    IlInt		appendRowInCache(IliTableBuffer* tblBuf);
    virtual IlBoolean	allowRowMove() const;
    IlBoolean		isRowNull(IlInt rowno) const;

    // Query mode
    virtual IlBoolean	isQueryModeSupported() const;
    virtual IliTable*	makeQueryTable() const;
    virtual IlBoolean	applyQueryMode(IliTable* queryTable);

    // Sorting and searching
    void		sortRows(const IlInt*		colnoArray,
				 IlInt			columnsCount,
				 IlInt			fromRow = 0,
				 IlInt			toRow = -1,
				 IliCompareFunction	fct = 0,
				 IlAny			data = 0);
    void		sortRows(IlInt			fromRow = 0,
				 IlInt			toRow = -1,
				 IliCompareFunction	fct = 0,
				 IlAny			data = 0);
    void		setCompareFunction(IliCompareFunction	fct,
					   IlAny		arg = 0);
    IliCompareFunction	getCompareFunction() const;
    IlAny		getCompareData() const;
    IlInt		findRow(const IliValue&	value,
				IlInt		colno,
				IlBoolean	complete,
				IlInt		fromRow = 0,
				IlInt		toRow = -1) const;
    IlInt		findFirstRow(const IliValue&	value,
				     IlInt		colno,
				     IlBoolean		complete,
				     IlInt		fromRow = 0,
				     IlInt		toRow = -1) const;

    IlBoolean		rowMatches(IlInt		rowno,
				   const IlInt*		colnoArray,
				   const IliValue*	values,
				   IlInt		columnCount) const;

    class ILV_INF_EXPORTED SearchResults
    {
    public:
	SearchResults() {}
	virtual ~SearchResults();

	virtual IlBoolean	atTop() const = 0;
	virtual IlBoolean	atBot() const = 0;
	virtual IlInt		getRowIndex() const = 0;
	virtual IlBoolean	next() = 0;
    };

    class ILV_INF_EXPORTED SnapshotSearchResults : public SearchResults
    {
    public:
	SnapshotSearchResults();
	virtual ~SnapshotSearchResults();

	virtual IlBoolean	atTop() const;
	virtual IlBoolean	atBot() const;
	virtual IlInt		getRowIndex() const;
	virtual IlBoolean	next();

	void			add(IlInt rowIdx);

    private:
	IlInt			_cIdx;
	IlvArray		_indices;
    };

    virtual
    SearchResults*	search(const IlInt*	colnoArray,
			       const IliValue*	values,
			       IlInt		columnCount) const;
    virtual
    IlBoolean		insertRowsFrom(const IliTable* src,
				       IlInt srcFromRow = 0,
				       IlInt srcToRow = -1,
				       IlBoolean stopAtFirstError = IlTrue,
				       IlInt insertAt = -1);

    virtual int		compareRows(const IliTable*	other,
				    IlInt		otherFromRow = 0,
				    IlInt		otherToRow = -1,
				    IlInt		fromRow = 0,
				    const IlInt*	colnoArray = 0,
				    IlInt		columnsCount = 0,
				    IliCompareFunction	fct = 0,
				    IlAny		data = 0) const;

    // Helpers
    IliValue		at(IlInt rowno, IlInt colno) const;
    IliValue		at(IlInt rowno, IliName colname) const;
    IlBoolean		set(IlInt rowno, IlInt colno, const IliValue& value);
    IlBoolean		set(IlInt		rowno,
			    IliName		colname,
			    const IliValue&	value);
    IlBoolean		setInCache(IlInt		rowno,
				   IlInt		colno,
				   const IliValue&	value);

    // Errors
    void		addErrorSink(IliErrorSink* sink);
    void		removeErrorSink(IliErrorSink* sink);

    // Constraints
    virtual IlBoolean	checkColumnConstraints(IlBoolean forInsert,
					       IliTableBuffer*) const;
    virtual IlBoolean	checkRowConstraints(IlInt rowno,
					    IliTableBuffer*) const;
    virtual IlBoolean	checkConstraints(IlInt			rowno,
					 IliTableBuffer*	buff) const;

    // Properties
    const IliTablePropertyManager* getDefaultPropertyManager() const;
    IliTablePropertyManager* getDefaultPropertyManager();
    virtual
    IliTablePropertyManager* newPropertyManager();
    IliTablePropertyManager* getNamedPropertyManager(const char* name) const;
    IliTablePropertyManager* newNamedPropertyManager(const char* name);
    void		removeNamedPropertyManager(const char* name);
    IlInt		getNamedPropertyManagerCount() const;
    const char*		getPropertyManagerNameAt(IlInt idx) const;
    IlInt		getPropertyCount(IlInt rowno, IlInt colno) const;
    const IlvSymbol*	getPropertyNameAt(IlInt rowno,
					  IlInt colno,
					  IlInt propIndex) const;
    IlBoolean		getProperty(IlInt		rowno,
				    IlInt		colno,
				    const IlvSymbol*	propName,
				    IliValue&		propVal) const;
    void		setProperty(IlInt		rowno,
				    IlInt		colno,
				    const IlvSymbol*	propName,
				    const IliValue&	propVal);
    void		removeProperty(IlInt		rowno,
				       IlInt		colno,
				       const IlvSymbol*	propName);

    // Tokens - internal
    IlBoolean		hasRowTokens() const;
    virtual IlInt	getRowToken(IlInt) const;
    virtual IlInt	getRowIndex(IlInt) const;

    // Debug
    void		dump() const;

    inline IlInt	_getRowsCount() const { return _fRowsCount; }

    virtual void	subTableChanged(IlInt, IlInt);

    IlBoolean		canCombineHookCalls() const;
    void		setCanCombineHookCalls(IlBoolean);

    inline IlBoolean	hasBeenDeleted() const { return _hasBeenDeleted; }

    static IlInt	IndexOf(IlInt, const IlInt*, IlInt);

    // Other
    inline IlBoolean	canRecord() const { return _canRecord; }
    inline void		canRecord(IlBoolean b) { _canRecord = b; }

protected:
    enum Tag {
	MaxFreeBuffers = 3
    };

    IlBoolean			_readOnly;
    IlBoolean			_modified;
    IlBoolean			_hasRowTokens;
    IlBoolean			_canRecord;
    IlBoolean			_canCombineHookCalls;
    IlBoolean			_hasBeenDeleted;
    IlInt			_fRowsCount;
    IlvList			_buffers;
    IliTableBuffer*		_scratchBuffer;
    IlvArray			_freeBuffers;
    IliParameterCollection	_parameters;
    IlvGadgetHolder*		_gadgetHolder;
    IlvList			_errorSinks;
    IliRowPtrIplCollection*	_rowPtrs;
    IliTransactionManager*	_transMgr;
    IliTablePropertyManager*	_props;
    IlvStringHashTable*		_namedPropManagers;
    IlvList			_allStdPropManagers;
    IliRowStatus		_defaultRowStatus;
    IliCellPtr			_context;
    IlvArray			_floatingSelections;

    IliCompareFunction		_compareFunction;
    IlAny			_compareData;

    IliTable(IlvDisplay*);
    IliTable(IlvDisplay*, const IliClassInfo*);
    IliTable(const IliTable&);
    IliTable(const IliTable&, const IliClassInfo*);
    IliTable(IlvDisplay*, IL_STDPREF istream&);
    IliTable(IlvDisplay*, IL_STDPREF istream&, const IliClassInfo*);

    void		init();
    void		init(const IliTable&);
    void		readTable(IL_STDPREF istream&);

    virtual IliTable*	iGetCache() const;

    inline const IliTableColumn* getTableColumnAt(IlInt idx) const
	{ return (const IliTableColumn*)IliSchema::getColumnAt(idx); }
    inline IliTableColumn*	getTableColumnAt(IlInt idx)
	{ return (IliTableColumn*)IliSchema::getColumnAt(idx); }

    inline IliRowStatus getDefaultRowStatus() const
	{ return _defaultRowStatus; }
    inline IliRowStatus setDefaultRowStatus(IliRowStatus newStatus)
	{
	    IliRowStatus prevStatus = _defaultRowStatus;
	    _defaultRowStatus = newStatus;
	    return prevStatus;
	}

    virtual
    IlvValueInterface*	makeItf() const;
    virtual
    IlvValueInterface*	makeColumnItf(IlInt) const;

    void		addStdPropManager(IliTablePropertyManager*);
    void		removeStdPropManager(IliTablePropertyManager*);

    void		hideNamedPropertyManagers();
    void		showNamedPropertyManagers();

    void		deepCopy(const IliTable&);
    IliTable& operator	=(const IliTable&);

    virtual IliColumn*	newColumn();

    friend class IliTableColumn;

    static
    const IliTable*	GetTopTable();

    inline IlBoolean	checkRow(IlInt r) const
	{ return (r >= 0) && (r < getRowsCount()); }
    IlBoolean		checkReadOnly() const;

    IlBoolean		checkSortRowsParams(const IlInt*,
					    IlInt,
					    IlInt&,
					    IlInt&) const;
    virtual void	doSortRows(const IlInt*,
				   IlInt,
				   IlInt,
				   IlInt,
				   IliCompareFunction,
				   IlAny);

    IlBoolean		checkBuffer(IliTableBuffer*) const;
    IlBoolean		importBuffer(IliTableBuffer*,
				     IliTableBuffer*,
				     IlBoolean = IlTrue);
    IliTableBuffer*	adaptBuffer(IliTableBuffer*, IlBoolean = IlTrue);

    virtual
    IliRowPtrIpl*	getRowPtrIpl(IlInt);
    virtual IliRowPtr	getRowPtrByToken(IlInt, IlInt) const;

    void		rowPtrLost(IliRowPtrIpl*);
    void		rowPtrMoved(IlInt, IlInt);

    // Transactions
    IlBoolean		isTMStarted() const;
    IlBoolean		isTMRecording() const;

    virtual IlBoolean	shouldRecord() const;

    virtual IlBoolean	cancelUpdateRow(IlInt,
					IliTableBuffer*,
					IliTableBuffer*);
    virtual IlBoolean	cancelInsertRow(IlInt, IliTableBuffer*);
    virtual IlBoolean	cancelDeleteRow(IlInt, IliTableBuffer*, IlInt = -1);
    virtual IlBoolean	cancelMoveRow(IlInt, IlInt);
    virtual IlBoolean	cancelExchangeRows(IlInt, IlInt);

    virtual IlBoolean	acceptUpdateRow(IlInt,
					IliTableBuffer*,
					IliTableBuffer*);
    virtual IlBoolean	acceptInsertRow(IlInt, IliTableBuffer*);
    virtual IlBoolean	acceptDeleteRow(IlInt, IliTableBuffer*);
    virtual IlBoolean	acceptMoveRow(IlInt, IlInt);
    virtual IlBoolean	acceptExchangeRows(IlInt, IlInt);

    virtual IlBoolean	insertRowInCacheEx(IlInt, IliTableBuffer*, IlInt);

    // Hooks
    virtual void	columnInserted(IlInt);
    virtual void	columnDeleted(IlInt);
    virtual void	columnToBeDeleted(IlInt);
    virtual void	columnMoved(IlInt, IlInt);
    virtual void	tableChanged();

    virtual void	allRowsDeleted();
    virtual void	rowsInserted(IlInt, IlInt);
    virtual void	rowInserted(IlInt rowno);
    virtual void	rowToBeChanged(IlInt rowno);
    virtual void	rowChanged(IlInt rowno);
    virtual void	rowToBeDeleted(IlInt rowno);
    virtual void	rowDeleted(IlInt rowno);
    virtual void	rowMoved(IlInt src, IlInt dest);
    virtual void	rowsFetched(IlInt, IlInt);
    virtual void	rowFetched(IlInt rowno);
    virtual void	rowsExchanged(IlInt, IlInt);

    virtual void	columnCellsChanged(IlInt);
    virtual void	cellChanged(IlInt rowno, IlInt colno);

    virtual void	namedPropertyManagerAdded(const char*);
    virtual void	namedPropertyManagerRemoved(const char*);

    virtual void	parametersChanged();
    virtual void	raiseError(const IliErrorMessage& msg) const;

    void		raiseDataAccessError(IliErrorCodeTag,
					     const char* = 0,
					     IlInt = 0) const;
    void		raiseDataAccessError(IliErrorCodeTag,
					     const char*,
					     const char*) const;

    friend class IliRowStatusI;
    friend class IliStdRowPtrIpl;
    friend class IliStdTablePropertyManager;
    friend class IliTransactionManager;
    friend class IliTransactionManager_Event;
    friend class IliMemoryTable;
};

// --------------------------------------------------------------------------
// These inline methods are defined here because IliTable must be completely
// declared at this point.
// --------------------------------------------------------------------------
inline const IliTable*
IliTablePtr::getTable() const
{
    return IL_DYNAMICCAST(const IliTable*, getSchema());
}
// --------------------------------------------------------------------------
inline IliTable*
IliTablePtr::getTable()
{
    return IL_DYNAMICCAST(IliTable*, getSchema());
}

#if !defined(__Ili_Tblitf_H)
#  include <ilviews/dataccess/intrface/tblitf.h>
#endif

IliDeclareTypeInit_exp(ILV_INF_EXPORTED,IliTable);

#endif /* !__Ili_Table_H */
