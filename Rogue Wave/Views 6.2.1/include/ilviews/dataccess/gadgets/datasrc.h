// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/datasrc.h
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
// Declaration of the IliDataSource class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Datasrc_H
#define __Ili_Datasrc_H

#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_Link_H)
#  include <ilviews/base/link.h>
#endif
#if !defined(__Ilv_Base_Error_H)
#  include <ilviews/base/error.h>
#endif
#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ili_Module_H)
#  include <ilviews/dataccess/module.h>
#endif
#if !defined(__Ili_Table_H)
#  include <ilviews/dataccess/table.h>
#endif
#if !defined(__Ili_Datagem_H)
#  include <ilviews/dataccess/gadgets/datagem.h>
#endif
#if !defined(__Ili_Errorrep_H)
#  include <ilviews/dataccess/errorrep.h>
#endif

class IliFieldData;
class ILV_INF_EXPORTED IliFieldItf;
class ILV_INF_EXPORTED IliTableContext;
class ILV_INF_EXPORTED IliDataSource;

typedef void (*IliTableContextFieldCallback)(IliTableContext*,
					     IliFieldItf*,
					     IlInt colno,
					     IlAny arg);
IL_DEFINEFPTRTOANYCAST(IliTableContextFieldCallback);

// --------------------------------------------------------------------------
typedef void (*IliDataSourceFieldCallback)(IliDataSource* ds,
					   IliFieldItf* field,
					   IlInt colno,
					   IlAny arg);
IL_DEFINEFPTRTOANYCAST(IliDataSourceFieldCallback);

class IliTCPropertyObserver;
class IliDataSource;
class IliTableGadget;
class IliFieldItf;
class IliFieldsHashTable;

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableContext
: public IliRefCounted, public IliTableHook
{
public:
    enum Scope {
	LocalScope,
	GlobalScope
    };

    inline IlvDisplay*	getDisplay() const { return _display; }

    IlvGraphic*		getOwner() const;

    inline IliTable*	getTable() const  { return _table; }
    void		setTable(IliTable*);

    const char*		getName() const;
    virtual void	setName(const char*);

    IlvGraphicHolder*	getHolder() const;
    virtual void	setHolder(IlvGraphicHolder*);

    Scope		getScope() const;
    virtual void	setScope(Scope);

    virtual IlBoolean	isAutoRowLockingEnabled() const;
    virtual IlBoolean	isInsertEnabled() const;

    IlBoolean		isCatchingNestedChanges() const;
    void		catchNestedChanges(IlBoolean);

    IlBoolean		isInputModified() const;
    IlBoolean		isOnInsertRow() const;
    IlBoolean		isCurrentRowNull() const;

    IlInt		getCurrentRow() const;

    IlBoolean		select();

    IlBoolean		gotoFirst();
    IlBoolean		gotoLast();
    IlBoolean		gotoRow(IlInt);
    IlBoolean		gotoPrevious();
    IlBoolean		gotoNext();

    IlBoolean		startInsert();
    IlBoolean		deleteCurrentRow();
    IlBoolean		callPrepareDeleteRow(IlInt);

    IlBoolean		validate();
    void		cancel();

    void		clearRows();

    IlBoolean		refreshCurrentRow(IlBoolean = IlFalse);
    IlBoolean		refreshAndLockCurrentRow(IlBoolean = IlFalse);

    const IliValue&	getValue(IlInt) const;
    const IliValue&	getValue(IliName) const;

    IlBoolean		setValue(IlInt, const IliValue&);
    IlBoolean		setValue(IliName, const IliValue&);

    void		setValueModified(IlInt, IlBoolean);
    void		setValueModified(IliName, IlBoolean);

    IlBoolean		validateField(IliFieldItf*);
    void		applyToFields(IliTableContextFieldCallback, IlAny);

    IlvSymbol*		getCallbackContext() const;

    void		dontValidateRow();
    void		dontDeleteRow();
    IlInt		getDeletedRow() const;
    IlInt		getFetchedRow() const;
    IlInt		getInsertedRow() const;

    // Errors
    void		addErrorMessage(const IliErrorMessage&);
    void		addErrorMessage(const char*);

    void		addErrorSink(IliErrorSink*);
    void		removeErrorSink(IliErrorSink*);

    virtual void	reportErrors(const IliErrorList&) const;

    void		forwardErrorMessage(const IliErrorMessage&);

    // Properties
    IlBoolean		isUsingTableProperties() const;
    void		useTableProperties(IlBoolean);

    const char*		getTablePropertyManagerName() const;
    void		setTablePropertyManagerName(const char*);

    const IliTablePropertyManager* getTablePropertyManager() const;
    IliTablePropertyManager* getTablePropertyManager();
    void		setTablePropertyManager(IliTablePropertyManager*);

    const IliTablePropertyManager* getEffectiveTablePropertyManager() const;
    IliTablePropertyManager* getEffectiveTablePropertyManager();

    virtual void	onPropertiesChanged();
    virtual void	onPropertyChanged(IlInt, IlInt,
					  const IlvSymbol*);

    static IlvSymbol*	ReadOnlySymbol();
    static IlvSymbol*	ForegroundSymbol();
    static IlvSymbol*	BackgroundSymbol();
    static IlvSymbol*	FontSymbol();
    static IlvSymbol*	FormatSymbol();
    static IlvSymbol*	MaskSymbol();
    static IlvSymbol*	AutoFitPullDownSymbol();

    // Callbacks
    enum EventType {
	ValidateRow,
	FetchRow,

	EnterRow,
	QuitRow,

	EnterModifiedState,

	EnterUpdateMode,
	PrepareUpdate,
	QuitUpdateMode,

	EnterInsertMode,
	PrepareInsert,
	QuitInsertMode,

	CancelEdits,

	PrepareDeleteRow,
	DeleteRow,

	Reset,

	EventCount
    };

    void		addCallback(EventType, IlvGraphicCallback, IlAny);
    void		removeCallback(EventType, IlvGraphicCallback, IlAny);

    void		addCallbackTarget(IlvGraphic*);
    void		removeCallbackTarget(IlvGraphic*);

    IlUInt		getBatchCount() const;
    const IliValue&	getBufferedValue(IlInt) const;

    // Masters
    IlInt		getMasterCount() const;
    IlInt		getMasterIndex(const char*) const;
    const char*		getMasterName(IlInt) const;
    virtual void	subscribeToMasters();
    void		subscribeToMaster(const char*);
    void		unSubscribeToMasterAt(IlInt);
    void		unSubscribeToMaster(const char*);
    void		unSubscribeToMasters();

    void		connectToMaster(IliTableContext*, IlAny);
    virtual void	onMastersChanged(IliTableContext**, IlInt);

    static
    IliTableContext*	GetTableContext(IlvGraphic*);
    static IlvSymbol*	ResetSymbol();

    IliFieldData*	getFieldData(IliFieldItf*) const;

protected:
    friend class IliTCPropertyObserver;
    friend class IliDataSource;
    friend class IliTableGadget;
    friend class IliFieldItf;
    friend class IliFieldsHashTable;

    IlvDisplay*		_display;
    IlvGraphic*		_owner;
    IliTable*		_table;
    IliString		_name;
    Scope		_scope;

    union {
	struct {
	    IlBoolean	_isRegistered		  ILIBF(1);
	    IlBoolean	_inputModified		  ILIBF(1);
	    IlBoolean	_isOnInsertRow		  ILIBF(1);
	    IlBoolean	_rowWasCurrent		  ILIBF(1);
	    IlBoolean	_isInRefreshRow		  ILIBF(1);
	    IlBoolean	_paramsChanged		  ILIBF(1);
	    IlBoolean	_mustCallHooks		  ILIBF(1);
	    IlBoolean	_validateRow		  ILIBF(1);
	    IlBoolean	_doDeleteRow		  ILIBF(1);
	    IlBoolean	_useTableProperties	  ILIBF(1);
	    IlBoolean	_catchingNestedChanges	  ILIBF(1);
	} _s;
	int _fill;
    } _u;

    IlInt		_callState;
    IlInt		_errorCount;
    IliTableBuffer*	_tableBuffer;
    IlInt		_batchCount;
    IlInt		_fetchedRow;
    IlInt		_deletedRow;
    IlInt		_insertedRow;
    IliRowPtr		_rowPtr;
    IliFieldsHashTable* _fields;
    IlvArray		_callbackContextStack;
    IlvAList		_callbacks[EventCount];
    IlvList		_callbackTargets;
    IliFieldItf*	_focusField;
    IliFieldItf*	_sourceFieldItf;
    IlvList		_errorSinks;
    IlvArray		_masters;
    IlvGraphicHolder*	_holder;
    IliTablePropertyManager* _propMgr;
    IliString		_tablePropMgrName;
    IliTablePropertyObserver* _propObserver;

    IliTableContext(IlvDisplay*, IlvGraphic*, IliTable* = 0);
    virtual ~IliTableContext();

    void		registerTableContext();
    void		unregisterTableContext();

    IlBoolean		isTableReadOnly() const;

    void		iOnPropertiesChanged(IliFieldItf*);
    void		iOnPropertiesChanged();
    void		iOnPropertyChanged(IlInt, IlInt, const IlvSymbol*);

    IlBoolean		connectField(IliFieldItf*, const char*);
    IlBoolean		connectField(IliFieldItf*, IlInt);
    void		disconnectField(IliFieldItf*);

    void		initColumn(IlInt colno);
    void		inputModified(IliFieldItf*);
    void		inputModifiedFinalizer(IliFieldItf*);
    void		readOnlyError();

    virtual void	cancelToFields();
    virtual void	bufferToFields();
    virtual void	columnToFields(IlInt, IlBoolean = IlTrue);
    IlBoolean		fieldsToBuffer();
    void		setFieldsReadOnly(IlBoolean);

    void		fieldFocusIn(IliFieldItf*);
    void		fieldFocusOut(IliFieldItf*);

    virtual IlBoolean	traverseFields(IliFieldItf*, IliFieldItf*);

    IlInt		getFieldToken(IliFieldItf*) const;
    IlInt		getFieldColumn(IliFieldItf*) const;

    IlBoolean		iGotoRow(IlInt, IlBoolean = IlFalse);
    void		setCurrentRowSilently(IlInt);

    void		pushContext(IlvSymbol*);
    void		popContext();

    static IlvSymbol*	GetCallbackSymbol(EventType);
    virtual void	callCallbacks(EventType);
    virtual void	callResetCallbacks();
    virtual IlBoolean	hasCallback(EventType);

    void		checkTablePropertyManager();
    void		tablePropertyManagerGot(IliTablePropertyManager*);
    void		tablePropertyManagerLost();
    void		namedPropertyManagerAdded(const char*);
    void		namedPropertyManagerRemoved(const char*);

    virtual void	newCurrentRow();

    virtual void	startOfBatch();
    virtual void	endOfBatch();
    virtual void	tableDeleted();
    virtual void	tableChanged();
    virtual void	rowsInserted(IlInt, IlInt);
    virtual void	rowInserted(IlInt);
    virtual void	rowChanged(IlInt);
    virtual void	rowToBeDeleted(IlInt);
    virtual void	rowDeleted(IlInt);
    virtual void	rowsFetched(IlInt, IlInt);
    virtual void	rowFetched(IlInt);
    virtual void	columnCellsChanged(IlInt);
    virtual void	cellChanged(IlInt, IlInt);
    virtual void	parametersChanged();
    virtual void	raiseError(const IliErrorMessage&);
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDataSource
: public IliDataGem
{
public:
    IliDataSource(IlvDisplay* display,
		  const IlvPoint& at,
		  IlUShort thickness = IlvDefaultGadgetThickness,
		  IlvPalette* palette = 0);
    virtual ~IliDataSource();

    inline IliTableContext*	getTableContext() const { return _context; }

    const IliTable*	getTable() const;
    IliTable*		getTable();
    virtual void	setTable(IliTable* table, IlBoolean owner = IlTrue);

    IlBoolean		isReadOnly() const;
    IlBoolean		isEditable() const;
    void		setReadOnly(IlBoolean only);
    IlBoolean		isInputModified() const;
    IlBoolean		isInserting() const;
    IlBoolean		isCurrentRowNull() const;
    inline IlBoolean	isOnInsertRow() const { return isInserting(); }
    IlBoolean		isAutoSelectEnabled() const;
    void		enableAutoSelect(IlBoolean autoSelect);
    IlBoolean		isInsertEnabled() const;
    void		enableInsert(IlBoolean enable);
    IlBoolean		isAutoRowLockingEnabled() const;
    void		enableAutoRowLocking(IlBoolean f);
    IlBoolean		isCatchingNestedChanges() const;
    void		catchNestedChanges(IlBoolean);

    IlInt		getRowsCount() const;
    IlInt		getColumnsCount() const;
    IlInt		getCurrentRow() const;
    void		applyToFields(IliDataSourceFieldCallback cb,
				      IlAny arg);

    // Actions
    IlBoolean		select();
    IlBoolean		gotoFirst();
    IlBoolean		gotoLast();
    IlBoolean		gotoRow(IlInt rowno);
    IlBoolean		gotoPrevious();
    IlBoolean		gotoNext();
    IlBoolean		startInsert();
    IlBoolean		deleteCurrentRow();
    inline IlBoolean	gotoInsertRow() { return startInsert(); }
    IlBoolean		validate(IlBoolean interactive = IlFalse);
    void		cancel();
    void		clear();
    IlBoolean		refreshCurrentRow(IlBoolean keepChanges = IlFalse);
    IlBoolean	refreshAndLockCurrentRow(IlBoolean keepChanges = IlFalse);

    // Values
    const IliValue&	getValue(IlInt colno) const;
    const IliValue&	getValue(IliName colname) const;
    IlBoolean		setValue(IlInt colno, const IliValue& value);
    IlBoolean		setValue(IliName colname, const IliValue& value);
    void		setValueModified(IlInt colno, IlBoolean flag);
    void		setValueModified(IliName colname, IlBoolean flag);

    // Query mode
    IlBoolean		isQueryModeSupported() const;

    IlBoolean		isInQueryMode() const;

    IlBoolean		switchToQueryMode();

    void		cancelQueryMode();

    IlBoolean		applyQueryMode(IlBoolean interactive = IlFalse);

    // Error reporting
    void		addErrorMessage(const IliErrorMessage& msg);

    void		addErrorMessage(const char* msg);

    void		addErrorSink(IliErrorSink* sink);

    void		removeErrorSink(IliErrorSink* sink);

    IliErrorReporter*	getErrorReporter() const;

    void		setErrorReporter(IliErrorReporter* reporter);

    void		reportErrors(const IliErrorList& errorList) const;

    void		forwardErrorMessage(const IliErrorMessage& msg);

    // Callbacks
    IlvSymbol*		getCallbackContext() const;
    virtual void	onEnterModifiedState();
    virtual void	onValidateRow();
    virtual void	onFetchRow();
    virtual void	onEnterRow();
    virtual void	onQuitRow();
    virtual void	onEnterUpdateMode();
    virtual void	onPrepareUpdate();
    virtual void	onQuitUpdateMode();
    virtual void	onEnterInsertMode();
    virtual void	onPrepareInsert();
    virtual void	onQuitInsertMode();
    virtual void	onPrepareDeleteRow();
    virtual void	onCancelEdits();
    virtual void	onDeleteRow();

    // To be called from within callbacks
    void		dontValidateRow();
    void		dontDeleteRow();
    IlInt		getDeletedRow() const;
    IlInt		getFetchedRow() const;
    IlInt		getInsertedRow() const;

    // Callback names
    static IlvSymbol*	EnterModifiedStateSymbol();
    static IlvSymbol*	ValidateRowSymbol();
    static IlvSymbol*	FetchRowSymbol();
    static IlvSymbol*	EnterRowSymbol();
    static IlvSymbol*	QuitRowSymbol();
    static IlvSymbol*	EnterUpdateModeSymbol();
    static IlvSymbol*	PrepareUpdateSymbol();
    static IlvSymbol*	QuitUpdateModeSymbol();
    static IlvSymbol*	EnterInsertModeSymbol();
    static IlvSymbol*	PrepareInsertSymbol();
    static IlvSymbol*	QuitInsertModeSymbol();
    static IlvSymbol*	PrepareDeleteRowSymbol();
    static IlvSymbol*	CancelEditsSymbol();
    static IlvSymbol*	DeleteRowSymbol();

    // Properties
    IlBoolean		isUsingTableProperties() const;
    void		useTableProperties(IlBoolean flag);
    const char*		getTablePropertyManagerName() const;
    void		setTablePropertyManagerName(const char* name);
    const IliTablePropertyManager* getTablePropertyManager() const;
    IliTablePropertyManager* getTablePropertyManager();
    void		setTablePropertyManager(IliTablePropertyManager*);
    const IliTablePropertyManager* getEffectiveTablePropertyManager() const;
    IliTablePropertyManager* getEffectiveTablePropertyManager();

    DeclareTypeInfo();
    DeclareIOConstructors(IliDataSource);

    virtual IlvGraphicHolder* getHolder() const;
    virtual void	setHolder(IlvGadgetHolder*);
    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlvSymbol* const**) const;

    virtual void	setName(const char*);
    virtual void	setGlobalScope(IlBoolean);
    virtual IlvBitmap*	getBitmap() const;

    void		addHook(IlvGraphicCallback, IlAny);
    void		removeHook(IlvGraphicCallback, IlAny);

    const IliValue&	getBufferedValue(IlInt) const;

    // Internals
    IlBoolean		callPrepareDeleteRow(IlInt);

    // Accessors
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    static void		GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);

    IliTableContext*	getContext() const;

    inline IlBoolean	hasBeenDeleted() const { return _hasBeenDeleted; }

protected:
    friend class IliDataSourceContext;

    IliTableContext*	_context;
    IlBoolean		_isInsertEnabled;
    IlBoolean		_isAutoRowLockingEnabled;
    IlBoolean		_isAutoSelectEnabled;
    IlBoolean		_tableOwner;
    IlBoolean		_isInQueryMode;
    IlBoolean		_hasBeenDeleted;
    IliTable*		_originalTable;
    IliTable*		_queryTable;

    IlvList		_errorSinks;
    IliErrorReporter*	_errorReporter;
    IlvValueInterface*	_cxnItf;

    void		init();
    void		setTableEx(IliTable*, IlBoolean, IlBoolean);

    IlBoolean		connectField(IliFieldItf*, const char*);
    void		disconnectField(IliFieldItf*);

    void		inputModified(IliFieldItf*);
    void		inputModifiedFinalizer(IliFieldItf*);
    void		fieldFocusIn(IliFieldItf*);
    void		fieldFocusOut(IliFieldItf*);

    void		onColumnToFields(IlInt colno);
    void		onBufferToFields();
    void		onNewCurrentRow();

    void		subscribeToMasters();
    void		unSubscribeToMasters();

    friend class IliFieldItf;
};

#if !defined(__Ili_Dtsrcitf_H)
#  include <ilviews/dataccess/intrface/dtsrcitf.h>
#endif

IliModuleDECL_exp(ILV_INF_EXPORTED, IliDataSource);

#endif /* !__Ili_Datasrc_H */
