// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dsusage.h
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
// Declaration of the IliDataSourceUsage class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dsusage_H
#define __Ili_Dsusage_H

#ifndef __Ili_Reposit_H
#  include <ilviews/dataccess/reposit.h>
#endif

#ifndef __Ili_String_H
#  include <ilviews/dataccess/string.h>
#endif

#ifndef __Ili_Tblhook_H
#  include <ilviews/dataccess/tblhook.h>
#endif

#ifndef __Ili_Datasrc_H
#  include <ilviews/dataccess/gadgets/datasrc.h>
#endif

#ifndef __Ili_Gdtmodel_H
#  include <ilviews/dataccess/gadgets/gdtmodel.h>
#endif

class IliDataSourceUsage;
class IliSubscribeInfo;

typedef void (*IliDsUsageHookCallback)(const IliModelHookInfo&);

enum IliDsUsageEvent {
    IliDsUsageEventRefresh = 0,
    IliDsUsageEventStartOfBatch,
    IliDsUsageEventEndOfBatch,
    IliDsUsageEventTableChanged,
    IliDsUsageEventTableDeleted,
    IliDsUsageEventRowInserted,
    IliDsUsageEventRowToBeChanged,
    IliDsUsageEventRowChanged,
    IliDsUsageEventRowToBeDeleted,
    IliDsUsageEventRowDeleted,
    IliDsUsageEventRowFetched,
    IliDsUsageEventRowMoved,
    IliDsUsageEventRowsExchanged,
    IliDsUsageEventRowsInserted,
    IliDsUsageEventRowsFetched,
    IliDsUsageEventColInserted,
    IliDsUsageEventColChanged,
    IliDsUsageEventColToBeDeleted,
    IliDsUsageEventColDeleted,
    IliDsUsageEventColMoved,
    IliDsUsageEventCellChanged,
    IliDsUsageEventCurrentRowChanged,
    IliDsUsageEventCount
};

enum IliDsUsageRefreshFrom {
    IliDsUsageFromInternal = 0,
    IliDsUsageFromEndOfBatch,
    IliDsUsageFromSetDataSource,
    IliDsUsageFromTableChanged,
    IliDsUsageFromTableDeleted,
    IliDsUsageFromRowInserted,
    IliDsUsageFromRowChanged,
    IliDsUsageFromRowDeleted,
    IliDsUsageFromRowMoved,
    IliDsUsageFromRowsExchanged,
    IliDsUsageFromRowsInserted,
    IliDsUsageFromRowsFetched,
    IliDsUsageRefreshFromCount
};

// -------------------------------------------------------------------------
// IliDsUsageHook
// -------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDsUsageHook : public IliTableHook
{
public:
    IliDsUsageHook(IliDataSourceUsage* = 0, IlInt dsi = 0);

    virtual void	startOfBatch();
    virtual void	endOfBatch();

    virtual void	tableDeleted();
    virtual void	tableChanged();

    virtual void	rowInserted(IlInt rowno);
    virtual void	rowToBeChanged(IlInt rowno);
    virtual void	rowChanged(IlInt rowno);
    virtual void	rowToBeDeleted(IlInt rowno);
    virtual void	rowDeleted(IlInt rowno);
    virtual void	rowFetched(IlInt rowno);
    virtual void	rowMoved(IlInt src, IlInt dest);
    virtual void	rowsExchanged(IlInt row1, IlInt row2);
    virtual void	rowsInserted(IlInt fromRow, IlInt toRow);
    virtual void	rowsFetched(IlInt fromRow, IlInt toRow);
    virtual void	columnInserted(IlInt colno);
    virtual void	columnChanged(IlInt colno);
    virtual void	columnToBeDeleted(IlInt colno);
    virtual void	columnDeleted(IlInt colno);
    virtual void	columnMoved(IlInt src, IlInt dest);

    virtual void	cellChanged(IlInt rowno, IlInt colno);

    virtual void	currentRowChanged(IlInt rowno);

protected:
    IliDataSourceUsage*	_usage;
    IlInt		_identifier;

    friend class IliSubscribeInfo;
};

// -------------------------------------------------------------------------
// IliSubscribeInfo
// -------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliSubscribeInfo : public IliRefCounted
{
public:
    IliSubscribeInfo(IliDataSourceUsage*);

    void		setIndex(IlInt index);
    IlInt		getIndex() const;

    void		setUsage(IliDataSourceUsage* usa);
    IliDataSourceUsage*	getUsage() const;

    void		setSubscribed(IlBoolean);
    IlBoolean		isSubscribed() const;

    void		setDataSource(IliDataSource*);
    IliDataSource*	getDataSource() const;

    void		setBufferInfo(IliTableBuffer*);
    IliTableBuffer*	getBufferInfo() const;

    void		setDataSourceName(const char*);
    const char*		getDataSourceName() const;
    IlBoolean		isThisDataSourceName(const char*) const;

    IliDsUsageHook*	getHook() const;

protected:
    IliDsUsageHook	_dsHook;
    IliDataSource*	_ds;
    IliString		_dsName;
    IlBoolean		_subscribed;
    IliTableBuffer*	_buffInfo;

    ~IliSubscribeInfo() {}
};

// -------------------------------------------------------------------------
// IliDataSourceUsage
// -------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDataSourceUsage
{
public:
    IliDataSourceUsage(IlvGraphic* g, IlBoolean = IlTrue);
    IliDataSourceUsage(IlBoolean = IlTrue);
    IliDataSourceUsage(const IliDataSourceUsage&);
    virtual ~IliDataSourceUsage();

    void		initialize();

    //---- Connection ----
    void		setGraphic(IlvGraphic*);
    IlvGraphic*		getGraphic() const;

    void		setReceiver(IlAny);
    IlAny		getReceiver() const;

    //---- current row ----
    void		enableCurrentRowEvent(IlBoolean);
    IlBoolean		isCurrentRowEventEnabled() const;

    //---- Error reporting ----
    void		addErrorSink(IliErrorSink*);
    void		removeErrorSink(IliErrorSink*);
    void		setErrorReporter(IliErrorReporter* reporter);
    IliErrorReporter*	getErrorReporter() const;
    void		reportErrors(const IliErrorList&) const;

    //---- Refresh ----
    void		startOfBatch();
    void		endOfBatch();
    void		refresh(IliDsUsageRefreshFrom);
    void		needRefresh(IlBoolean = IlTrue);
    IlBoolean		isRefreshNeeded() const;
    void		setAutomaticRefresh(IlBoolean);
    IlBoolean		isAutomaticRefresh() const;

    //---- IO ----
    void		enableIO();
    void		disableIO();
    IlBoolean		isIOEnabled() const;

    //---- Holders -----
    virtual void	beforeSetHolder();
    virtual void	setHolder(IlvGraphicHolder*);
    virtual
    IlvGraphicHolder*	getHolder() const;

    //---- Data Sources ----
    IlInt		getDataSourceCount() const;
    void		setDataSource(IliDataSource*, IlInt dsi = 0);
    IliDataSource*	getDataSource(IlInt dsi = 0) const;
    void		setDataSourceName(const char*, IlInt dsi = 0);
    const char*		getDataSourceName(IlInt dsi = 0) const;

    void		subscribeDataSource(IlInt dsi = 0);
    void		unsubscribeDataSource(IlInt dsi = 0);
    void		setDataSourceFromSubscribe(IliDataSource*,
						   IlInt dsi = 0);

    //---- Data Source Public Interface ----
    virtual void	addDataSourceName(const char*);
    virtual
    IliSubscribeInfo*	getSubscriber(IlInt dsi = 0) const = 0;

    //---- Tables ----
    IlBoolean		appendRow(IliTableBuffer*, IlInt dsi = 0);
    IlBoolean		updateRow(IlInt, IliTableBuffer*, IlInt dsi = 0);
    IlBoolean		select(IlBoolean force = IlFalse, IlInt dsi = 0);
    IliTable*		getTable(IlInt dsi = 0) const;
    IliTableBuffer*	getBuffer(IlInt dsi = 0) const;
    IliTableBuffer*	getBufferInfo(IlInt dsi = 0) const;
    void		releaseBuffer(IliTableBuffer*, IlInt dsi = 0);
    IlInt		getRowCount(IlInt dsi = 0) const;

    //---- Table Hook ----
    void		eventTableHook(IliDsUsageEvent,
				       IlInt,
				       IlInt,
				       IlInt,
				       IlBoolean,
				       IlBoolean,
				       IlBoolean);
    void		setCallback(IliDsUsageEvent, IliDsUsageHookCallback);
    void		callCallback(IliDsUsageEvent, IlInt, IlInt, IlInt);

    void		enableHook() { _hookEnable = IlTrue; }
    void		disableHook() { _hookEnable = IlFalse; }

    void		setHook(IlInt dsi = 0);
    void		removeHook(IlInt dsi = 0);

protected:
    //---- hook events ----
    IliDsUsageHookCallback _callbackEvent[IliDsUsageEventCount];
    IlBoolean		_hookEnable;
    IliModelHookInfo	_info;

    //---- Data sources ----
    IlInt		_dsCount;

    //---- Refresh ----
    IlBoolean		_needRefresh;
    IlBoolean		_inEndOfBatch;
    IlInt		_batchCount;
    IlBoolean		_autoRefresh;

    //---- Other ----
    IlvGraphic*		_graphic;
    IlvGraphicHolder*	_holder;
    IliErrorReporter*	_errorReporter;

    //---- Flags ----
    IlBoolean		_enableIO;
    IlBoolean		_enableCurrentRow;

    //---- Internal Interface ----
    virtual void	computeColumnIndex(IlInt dsi = -1,
					   IlInt col = -1) const = 0;
};

// -------------------------------------------------------------------------
// IliSingleDataSourceUsage
// -------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliSingleDataSourceUsage : public IliDataSourceUsage
{
public:
    IliSingleDataSourceUsage(IlvGraphic*, IlInt, IlBoolean = IlTrue);
    IliSingleDataSourceUsage(IlInt, IlBoolean = IlTrue);
    IliSingleDataSourceUsage(const IliSingleDataSourceUsage&);
    virtual ~IliSingleDataSourceUsage();

    IliSingleDataSourceUsage& operator=(const IliSingleDataSourceUsage&);

    void		read(IL_STDPREF istream& from);
    void		write(IL_STDPREF ostream& to) const;

    //---- Table API ----
    IlBoolean		deleteRow(IlInt);

    //---- Columns ----
    void		setColumnCount(IlInt);
    inline IlInt	getColumnCount() const { return _columnCount; }
    void		setColumnName(IlInt, const char*);
    void		addColumnName(const char*);
    inline const char*	getColumnName(IlInt index) const
			{
			    return ((index >= 0) && (index < _columnCount))
				? (const char*)(_columns[index])
				: (const char*)0;
			}
    inline IlInt	getColumnIndex(IlInt index) const
			{
			    IlInt tmpIndex = -1;
			    if ((index >= 0) && (index < _columnCount)) {
				if (_ndxColumns[index] == -1)
				    computeColumnIndex(index);
				tmpIndex = _ndxColumns[index];
			    }
			    return tmpIndex;
			}

    //---- Other ----
    IlBoolean		isDefined() const;
    IliSingleDataSourceUsage& copyFrom(const IliSingleDataSourceUsage&);

    //---- Data Source Public Interface ----
    virtual
    IliSubscribeInfo*	getSubscriber(IlInt dsi = 0) const;

protected:
    //---- Initialize ----
    void		initializeSingle(IlInt);

    //---- Data Source ----
    IliSubscribeInfo*	_subscriber;

    //---- columns ----
    IlInt*		_ndxColumns;
    IliString*		_columns;
    IlInt		_columnCount;

    //---- Internal Interface ----
    virtual void	computeColumnIndex(IlInt dsi = -1,
					   IlInt col = -1) const;
};

// -------------------------------------------------------------------------
// IliMultiDataSourceUsage
// -------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliMultiDataSourceUsage : public IliDataSourceUsage
{
public:
    IliMultiDataSourceUsage(IlvGraphic*, IlInt, IlInt, IlBoolean = IlTrue);
    IliMultiDataSourceUsage(IlInt, IlInt, IlBoolean = IlTrue);
    IliMultiDataSourceUsage(const IliMultiDataSourceUsage&);
    virtual ~IliMultiDataSourceUsage();

    IliMultiDataSourceUsage& operator=(const IliMultiDataSourceUsage&);

    void		read(IL_STDPREF istream& from);
    void		write(IL_STDPREF ostream& to) const;

    //---- DataSource ----
    void		resetDataSources();
    void		setDataSourceCount(IlInt, IlInt);

    //---- Table API ----
    IlBoolean		deleteRow(IlInt, IlInt);

    //---- Columns ----
    inline IlInt	getColumnCount() const { return _columnCount; }
    void		setColumnName(IlInt, IlInt, const char*);
    inline const char*	getColumnName(IlInt dsi, IlInt index) const
			{
			    return ((dsi >= 0) && (dsi < _dsCount) &&
				    (index >= 0) && (index < _columnCount))
				? ((const char*)(_columns[dsi][index]))
				: ((const char*)0);
			}

    inline IlInt	getColumnIndex(IlInt dsi, IlInt index) const
			{
			    IlInt tmpIndex = -1;
			    if ((index >= 0) && (index < _columnCount) &&
				(dsi >= 0) && (dsi < _dsCount)) {
				if (_ndxColumns[dsi][index] == -1)
				    computeColumnIndex(dsi, index);
				tmpIndex = _ndxColumns[dsi][index];
			    }
			    return tmpIndex;
			}

    void		addColumnName(IlInt, const char*);

    //---- Other ----
    IlBoolean isDefined(IlInt) const;
    IliMultiDataSourceUsage& copyFrom(const IliMultiDataSourceUsage&);

    //---- Data Source Public Interface ----
    virtual void	addDataSourceName(const char*);

    virtual IliSubscribeInfo* getSubscriber(IlInt dsi = 0) const;

protected:
    //---- Initialize ----
    void		init();
    void		initializeMulti(IlInt, IlInt);

    //---- Data Source ----
    IliSubscribeInfo**	_subscriber;

    //---- columns ----
    IlInt**		_ndxColumns;
    IliString**		_columns;
    IlInt		_columnCount;

    //---- Internal Interface ----
    virtual void	computeColumnIndex(IlInt dsi = -1,
					   IlInt col = -1) const;
};

// -------------------------------------------------------------------------
// IliListDataSourceUsage
// -------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliListDataSourceUsage : public IliDataSourceUsage
{
public:
    IliListDataSourceUsage(IlvGraphic*, IlInt, IlInt, IlBoolean = IlTrue);
    IliListDataSourceUsage(IlInt, IlInt, IlBoolean = IlTrue);
    IliListDataSourceUsage(const IliListDataSourceUsage&);
    virtual ~IliListDataSourceUsage();

    IliListDataSourceUsage& operator=(const IliListDataSourceUsage&);

    //---- DataSource ----
    void		resetDataSources();

    //---- Data Source Public Interface ----
    virtual void	setDataSourceCount(IlInt);
    virtual void	addDataSourceName(const char*);
    virtual
    IliSubscribeInfo*	getSubscriber(IlInt dsi = 0) const;

    //---- Read / Write ----
    void		read(IL_STDPREF istream& from);
    void		write(IL_STDPREF ostream& to) const;

    //---- Table API ----
    IlBoolean		deleteRow(IlInt, IlInt);

    //---- Columns ----
    void		setColumnCount(IlInt dsi, IlInt);
    IlInt		getColumnCount(IlInt dsi) const;

    void		setColumnName(IlInt dsi, IlInt, const char*);
    void		addColumnName(IlInt dsi, const char*);
    const char*		getColumnName(IlInt dsi, IlInt) const;
    IlInt		getColumnIndex(IlInt dsi, IlInt) const;

    //---- Other ----
    IlBoolean		isDefined(IlInt) const;
    IliListDataSourceUsage& copyFrom(const IliListDataSourceUsage&);

protected:
    void		init();
    void		initializeList(IlInt, IlInt);

    //---- Data sources ----
    IliSubscribeInfo** _subscribers;

    //---- Columns ----
    IliString**		_columns;
    IlInt**		_ndxColumns;
    IlInt*		_columnCount;

    //---- Internal Interface ----
    virtual void	computeColumnIndex(IlInt dsi = -1,
					   IlInt col = -1) const;
};

// -------------------------------------------------------------------------
// Macros for IliDataSourceUsage
// -------------------------------------------------------------------------
#define IliDsUsageInitBatch(usage, id)					\
    usage->setCallback(IliDsUsageEventStartOfBatch, id##StartOfBatch);	\
    usage->setCallback(IliDsUsageEventEndOfBatch, id##EndOfBatch);

#define IliDsUsageInitConnect(usage, id)				\
    usage->setCallback(IliDsUsageEventRefresh, id##Refresh);		\
    usage->setCallback(IliDsUsageEventTableChanged, id##TableChanged);	\
    usage->setCallback(IliDsUsageEventTableDeleted, id##TableDeleted);	\
    usage->setCallback(IliDsUsageEventRowInserted, id##RowInserted);	\
    usage->setCallback(IliDsUsageEventRowToBeChanged, id##RowToBeChanged); \
    usage->setCallback(IliDsUsageEventRowChanged, id##RowChanged);	\
    usage->setCallback(IliDsUsageEventRowToBeDeleted, id##RowToBeDeleted); \
    usage->setCallback(IliDsUsageEventRowDeleted, id##RowDeleted);	\
    usage->setCallback(IliDsUsageEventRowFetched, id##RowFetched);	\
    usage->setCallback(IliDsUsageEventRowMoved, id##RowMoved);		\
    usage->setCallback(IliDsUsageEventRowsExchanged, id##RowsExchanged); \
    usage->setCallback(IliDsUsageEventRowsInserted, id##RowsInserted);	\
    usage->setCallback(IliDsUsageEventRowsFetched, id##RowsFetched);	\
    usage->setCallback(IliDsUsageEventColInserted, id##ColInserted);	\
    usage->setCallback(IliDsUsageEventColChanged, id##ColChanged);	\
    usage->setCallback(IliDsUsageEventColToBeDeleted, id##ColToBeDeleted); \
    usage->setCallback(IliDsUsageEventColDeleted, id##ColDeleted);	\
    usage->setCallback(IliDsUsageEventColMoved, id##ColMoved);		\
    usage->setCallback(IliDsUsageEventCellChanged, id##CellChanged)

#define IliDsUsageInitCurrentRowConnect(usage, id)			\
    usage->setCallback(IliDsUsageEventCurrentRowChanged, id##CurrentRowChanged)

#define IliDsUsageDeclareFctConnect(idcl)				\
    virtual void idcl##Refresh(const IliModelHookInfo&);		\
    virtual void idcl##TableChanged(const IliModelHookInfo&);		\
    virtual void idcl##TableDeleted(const IliModelHookInfo&);		\
    virtual void idcl##RowInserted(const IliModelHookInfo&);		\
    virtual void idcl##RowToBeChanged(const IliModelHookInfo&);		\
    virtual void idcl##RowChanged(const IliModelHookInfo&);		\
    virtual void idcl##RowToBeDeleted(const IliModelHookInfo&);		\
    virtual void idcl##RowDeleted(const IliModelHookInfo&);		\
    virtual void idcl##RowFetched(const IliModelHookInfo&);		\
    virtual void idcl##RowMoved(const IliModelHookInfo&);		\
    virtual void idcl##RowsExchanged(const IliModelHookInfo&);		\
    virtual void idcl##RowsInserted(const IliModelHookInfo&);		\
    virtual void idcl##RowsFetched(const IliModelHookInfo&);		\
    virtual void idcl##ColumnInserted(const IliModelHookInfo&);		\
    virtual void idcl##ColumnChanged(const IliModelHookInfo&);		\
    virtual void idcl##ColumnToBeDeleted(const IliModelHookInfo&);	\
    virtual void idcl##ColumnDeleted(const IliModelHookInfo&);		\
    virtual void idcl##ColumnMoved(const IliModelHookInfo&);		\
    virtual void idcl##CellChanged(const IliModelHookInfo&)

#define IliDsUsageDeclareCurrentRowFct(idcl)				\
    virtual void idcl##CurrentRowChanged(const IliModelHookInfo&)

#define IliDsUsageDeclareBatch(idcl)		\
    virtual void idcl##StartOfBatch();		\
    virtual void idcl##EndOfBatch()

#define IliDsUsageCBConnect(idcb, idcl, cl)				\
    static void idcb##Refresh(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##Refresh(info); }		\
    static void idcb##TableChanged(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->idcl##TableChanged(info); }		\
    static void idcb##TableDeleted(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->idcl##TableDeleted(info); }		\
    static void idcb##RowInserted(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##RowInserted(info); }		\
    static void idcb##RowToBeChanged(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->idcl##RowToBeChanged(info); }	\
    static void idcb##RowChanged(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##RowChanged(info); }		\
    static void idcb##RowToBeDeleted(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->idcl##RowToBeDeleted(info); }	\
    static void idcb##RowDeleted(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##RowDeleted(info); }		\
    static void idcb##RowFetched(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##RowFetched(info); }		\
    static void idcb##RowMoved(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##RowMoved(info); }		\
    static void idcb##RowsExchanged(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->idcl##RowsExchanged(info); }		\
    static void idcb##RowsInserted(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->idcl##RowsInserted(info); }		\
    static void idcb##RowsFetched(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##RowsFetched(info); }		\
    static void idcb##ColInserted(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##ColumnInserted(info); }	\
    static void idcb##ColChanged(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##ColumnChanged(info); }		\
    static void idcb##ColToBeDeleted(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->idcl##ColumnToBeDeleted(info); }	\
    static void idcb##ColDeleted(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##ColumnDeleted(info); }		\
    static void idcb##ColMoved(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##ColumnMoved(info); }		\
    static void idcb##CellChanged(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##CellChanged(info); }

#define IliDsUsageCBCurrentRowConnect(idcb, idcl, cl) \
    static void idcb##CurrentRowChanged(const IliModelHookInfo& info) \
    { ((cl*)(info.getReceiver()))->idcl##CurrentRowChanged(info); } \

#define IliDsUsageCBBatch(idcb, idcl, cl)				\
    static void idcb##StartOfBatch(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->idcl##StartOfBatch(); }		\
    static void idcb##EndOfBatch(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->idcl##EndOfBatch(); }

#define IliDsUsageCodeNothing(cl, name, event)		\
    void cl::name##event(const IliModelHookInfo&) {} //

#define IliDsUsageDeclareFctConnectDirect()			\
    virtual void refresh(const IliModelHookInfo&);		\
    virtual void tableChanged(const IliModelHookInfo&);		\
    virtual void tableDeleted(const IliModelHookInfo&);		\
    virtual void rowInserted(const IliModelHookInfo&);		\
    virtual void rowToBeChanged(const IliModelHookInfo&);	\
    virtual void rowChanged(const IliModelHookInfo&);		\
    virtual void rowToBeDeleted(const IliModelHookInfo&);	\
    virtual void rowDeleted(const IliModelHookInfo&);		\
    virtual void rowFetched(const IliModelHookInfo&);		\
    virtual void rowMoved(const IliModelHookInfo&);		\
    virtual void rowsExchanged(const IliModelHookInfo&);	\
    virtual void rowsInserted(const IliModelHookInfo&);		\
    virtual void rowsFetched(const IliModelHookInfo&);		\
    virtual void columnInserted(const IliModelHookInfo&);	\
    virtual void columnChanged(const IliModelHookInfo&);	\
    virtual void columnToBeDeleted(const IliModelHookInfo&);	\
    virtual void columnDeleted(const IliModelHookInfo&);	\
    virtual void columnMoved(const IliModelHookInfo&);		\
    virtual void cellChanged(const IliModelHookInfo&)

#define IliDsUsageDeclareCurrentRowFctDirect()			\
    virtual void currentRowChanged(const IliModelHookInfo&)

#define IliDsUsageDeclareBatchDirect()		\
    virtual void startOfBatch();		\
    virtual void endOfBatch()

#define IliDsUsageCBConnectDirect(idcb, cl)				\
    static void idcb##Refresh(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->refresh(info); }			\
    static void idcb##TableChanged(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->tableChanged(info); }		\
    static void idcb##TableDeleted(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->tableDeleted(info); }		\
    static void idcb##RowInserted(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->rowInserted(info); }			\
    static void idcb##RowToBeChanged(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->rowToBeChanged(info); }		\
    static void idcb##RowChanged(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->rowChanged(info); }			\
    static void idcb##RowToBeDeleted(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->rowToBeDeleted(info); }		\
    static void idcb##RowDeleted(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->rowDeleted(info); }			\
    static void idcb##RowFetched(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->rowFetched(info); }			\
    static void idcb##RowMoved(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->rowMoved(info); }			\
    static void idcb##RowsExchanged(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->rowsExchanged(info); }		\
    static void idcb##RowsInserted(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->rowsInserted(info); }		\
    static void idcb##RowsFetched(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->rowsFetched(info); }			\
    static void idcb##ColInserted(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->columnInserted(info); }		\
    static void idcb##ColChanged(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->columnChanged(info); }		\
    static void idcb##ColToBeDeleted(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->columnToBeDeleted(info); }		\
    static void idcb##ColDeleted(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->columnDeleted(info); }		\
    static void idcb##ColMoved(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->columnMoved(info); }			\
    static void idcb##CellChanged(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->cellChanged(info); }

#define IliDsUsageCBCurrentRowConnectDirect(idcb, cl) \
    static void idcb##CurrentRowChanged(const IliModelHookInfo& info) \
    { ((cl*)(info.getReceiver()))->currentRowChanged(info); } \

#define IliDsUsageCBBatchDirect(idcb, cl)				\
    static void idcb##StartOfBatch(const IliModelHookInfo& info)	\
    { ((cl*)(info.getReceiver()))->startOfBatch(); }			\
    static void idcb##EndOfBatch(const IliModelHookInfo& info)		\
    { ((cl*)(info.getReceiver()))->endOfBatch(); }

#define IliDsUsageCodeNothingDirect(cl, event)		\
    void cl::event(const IliModelHookInfo&) {} //

// -------------------------------------------------------------------------
// Macros for IliSingleDataSourceUsage
// -------------------------------------------------------------------------
#define IliSingleDsUsageDeclareColAccess(name)		\
    inline void set##name##ColumnName(const char*);	\
    inline const char* get##name##ColumnName() const;	\
    inline IlInt get##name##ColumnIndex() const

#define IliSingleDsUsageDeclareColAccessSingle()	\
    inline void setColumnName(IlInt, const char*);	\
    inline const char* getColumnName(IlInt) const;	\
    inline IlInt getColumnIndex(IlInt) const

#define IliSingleDsUsageDeclareDSAccess(name)			\
    inline void set##name##DataSource(IliDataSource*);		\
    inline IliDataSource* get##name##DataSource() const;	\
    inline void set##name##DataSourceName(const char*);		\
    inline const char* get##name##DataSourceName() const

#define IliSingleDsUsageDeclareDSAccessDirect()		\
    inline void setDataSource(IliDataSource*);		\
    inline IliDataSource* getDataSource() const;	\
    inline void setDataSourceName(const char*);		\
    inline const char* getDataSourceName() const

#define IliSingleDsUsageCodeColAccess(cl, name, usage, index)	\
    inline void cl::set##name##ColumnName(const char* colname)	\
    { (usage)->setColumnName(index, colname); }			\
    inline const char* cl::get##name##ColumnName() const	\
    { return (usage)->getColumnName(index); }			\
    inline IlInt cl::get##name##ColumnIndex() const		\
    { return (usage)->getColumnIndex(index); } //

#define IliSingleDsUsageCodeColAccessDirect(cl, usage)			\
    inline void cl::setColumnName(IlInt index, const char* colname)	\
    { (usage)->setColumnName(index, colname); }				\
    inline const char* cl::getColumnName(IlInt index) const		\
    { return (usage)->getColumnName(index); }				\
    inline IlInt cl::getColumnIndex(IlInt index) const			\
    { return (usage)->getColumnIndex(index); } //

#define IliSingleDsUsageCodeDSAccess(cl, name, usage)			\
    inline void cl::set##name##DataSource(IliDataSource* ds)		\
    { usage->setDataSource(ds); }					\
    inline IliDataSource* cl::get##name##DataSource() const		\
    { return usage->getDataSource(); }					\
    inline void cl::set##name##DataSourceName(const char* dsname)	\
    { usage->setDataSourceName(dsname); }				\
    inline const char* cl::get##name##DataSourceName() const		\
    { return usage->getDataSourceName(); } //

#define IliSingleDsUsageCodeDSAccessDirect(cl, usage)		\
    inline void cl::setDataSource(IliDataSource* ds)		\
    { usage->setDataSource(ds); }				\
    inline IliDataSource* cl::getDataSource() const		\
    { return usage->getDataSource(); }				\
    inline void cl::setDataSourceName(const char* dsname)	\
    { usage->setDataSourceName(dsname); }			\
    inline const char* cl::getDataSourceName() const		\
    { return usage->getDataSourceName(); } //

// -------------------------------------------------------------------------
// Macros for IliMultiDataSourceUsage
// -------------------------------------------------------------------------
#define IliMultiDsUsageDeclareColAccess(name)			\
    inline void set##name##ColumnName(IlInt, const char*);	\
    inline const char* get##name##ColumnName(IlInt) const;	\
    inline IlInt get##name##ColumnIndex(IlInt) const

#define IliMultiDsUsageDeclareDSAccess(name)			\
    inline void set##name##DataSource(IlInt, IliDataSource*);	\
    inline IliDataSource* get##name##DataSource(IlInt) const;	\
    inline void set##name##DataSourceName(IlInt, const char*);	\
    inline const char* get##name##DataSourceName(IlInt) const;	\
    inline IlInt get##name##DataSourceCount() const;		\
    inline void set##name##DataSourceCount(IlInt, IlInt);	\
    inline void add##name##DataSourceName(const char*)

#define IliMultiDsUsageCodeColAccess(cl, name, usage, index)		\
    inline void cl::set##name##ColumnName(IlInt dsi, const char* col)	\
    { (usage)->setColumnName(dsi, index, col); }			\
    inline const char* cl::get##name##ColumnName(IlInt dsi) const	\
    { return (usage)->getColumnName(dsi, index); }			\
    inline IlInt cl::get##name##ColumnIndex(IlInt dsi) const		\
    { return (usage)->getColumnIndex(dsi, index); }

#define IliMultiDsUsageCodeDSAccess(cl, name, usage)			\
    inline void cl::set##name##DataSource(IlInt dsi, IliDataSource* ds) \
    { usage->setDataSource(ds, dsi); }					\
    inline IliDataSource* cl::get##name##DataSource(IlInt dsi) const	\
    { return usage->getDataSource(dsi); }				\
    inline void cl::set##name##DataSourceName(IlInt dsi, const char* dsname) \
    { usage->setDataSourceName(dsname, dsi); }				\
    inline const char* cl::get##name##DataSourceName(IlInt dsi) const	\
    { return usage->getDataSourceName(dsi); }				\
    inline IlInt cl::get##name##DataSourceCount() const			\
    { return usage->getDataSourceCount(); }				\
    inline void cl::set##name##DataSourceCount(IlInt ds, IlInt col)	\
    { usage->setDataSourceCount(ds, col); }				\
    inline void cl::add##name##DataSourceName(const char* dsname)	\
    { usage->addDataSourceName(dsname); } //

#endif
