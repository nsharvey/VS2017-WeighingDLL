// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dbtree.h
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
// Declaration of the IliDbTreeGadget class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbtreegadget_H
#define __Ili_Dbtreegadget_H

#ifndef __Ilv_Gadgets_Idialog_H
#  include <ilviews/gadgets/idialog.h>
#endif

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ilv_Gadgets_Menu_H
#  include <ilviews/gadgets/menu.h>
#endif

#ifndef __Ilv_Msglabel_H
#  include <ilviews/gadgets/msglabel.h>
#endif

#ifndef __Ilv_Gadgets_Tree_H
#  include <ilviews/gadgets/tree.h>
#endif

#ifndef __Ili_Dbstrlst_H
#  include <ilviews/dataccess/gadgets/dbstrlst.h>
#endif

#ifndef __Ili_Entryfld_H
#  include <ilviews/dataccess/gadgets/entryfld.h>
#endif

#ifndef __Ili_Dsusage_H
#  include <ilviews/dataccess/gadgets/dsusage.h>
#endif

#ifndef __Ili_Gdtmodel_H
#  include <ilviews/dataccess/gadgets/gdtmodel.h>
#endif

enum IliDbTreeColumn {
    IliDbTreeIdentifierColumn = 0,
    IliDbTreeLabelColumn,
    IliDbTreeParentColumn,
    IliDbTreeBitmapColumn,
    IliDbTreeColumnCount
};

class IliDbTreeGadget;
class IliDbTreeModel;

typedef IliDbTreeModel* (*IliDbTreeCreateModel)();

// --------------------------------------------------------------------------
// IliDbTreeItem
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbTreeItem
{
public:
    IliDbTreeItem();
    virtual ~IliDbTreeItem();

    inline void		setValue(const IliValue& v) { _value = v; }
    inline IliValue&	getValue() { return _value; }

    inline void		setDsNumber(IlInt num) { _dsNum = num; }
    inline IlInt	getDsNumber() const { return _dsNum; }

    inline void		setLabel(const IliValue& v) { _label = v; }
    inline IliValue&	getLabel() { return _label; }

    inline void		setBitmap(const IliValue& v) { _bitmap = v; }
    inline IliValue&	getBitmap() { return _bitmap; }

    inline void		setParent(IliDbTreeItem *p) { _parent = p; }
    inline
    IliDbTreeItem*	getParent() const { return _parent; }

    inline void		setRoot() { _parent = 0; }
    inline IlBoolean	isRoot() const { return (_parent) ? IlFalse : IlTrue; }

    inline void		setAdded() { _added = IlTrue; }
    inline IlBoolean	isNotAdded() const { return !_added; }

    inline void		setGhost(IlBoolean ghost) { _ghost = ghost; }
    inline IlBoolean	isAGhost() const { return _ghost; }

    IliDbTreeItem*	addChild(IliDbTreeItem*);
    inline
    IliDbTreeItem*	getFirstChild() const { return _firstChild; }
    inline
    IliDbTreeItem*	getNextBrother() const { return _nextBrother; }

    inline
    IliDbTreeItem*	getNext() const { return _next; }
    inline void		setNext(IliDbTreeItem* n) { _next = n; }

    inline
    IliDbTreeItem*	getPrevious() const { return _previous; }
    inline void		setPrevious(IliDbTreeItem* p) { _previous = p; }

    IlBoolean		remove();

protected:
    IliValue		_value;
    IliValue		_label;
    IliValue		_bitmap;
    IlInt		_dsNum;
    IliDbTreeItem*	_parent;
    IliDbTreeItem*	_firstChild;
    IliDbTreeItem*	_lastChild;
    IliDbTreeItem*	_previous;
    IliDbTreeItem*	_next;
    IliDbTreeItem*	_previousBrother;
    IliDbTreeItem*	_nextBrother;
    IlBoolean		_added;
    IlBoolean		_ghost;
};

// --------------------------------------------------------------------------
// IliDbOldTreeGadget
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbOldTreeGadget
    : public IlvTreeGadget, public IliFieldItf
{
public:
    IliDbOldTreeGadget(IlvDisplay* display,
		       const IlvRect& rect,
		       IlUShort thickness = IlvDefaultGadgetThickness,
		       IlvPalette* palette = 0);
    ~IliDbOldTreeGadget();

    virtual void	initDefaultTree();

    //---- implements IliFieldItf ----

    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean);

    virtual IlBoolean	f_isConsistent() const;
    virtual void	f_internalToExternal();
    virtual IlBoolean	f_externalToInternal();

    virtual void	f_refresh();
    virtual IlBoolean	f_complete();
    virtual IlBoolean	f_canMapValue() const;
    virtual void	f_setDataSource(IliDataSource* ds,
					IlBoolean owner = IlFalse);
    virtual void	f_setForeignTable(IliTable*,
					  IlBoolean owner = IlFalse);
    virtual void	f_setForeignValueColumnName(const char*);
    virtual void	f_setForeignDisplayColumnName(const char*);

    virtual IlBoolean	f_hasLabel() const;

    virtual
    const IliFormat&	f_getFormat() const;
    virtual void	f_setFormat(const IliFormat&);

    //---- tree properties ----
    inline void		setParentColumnName(const char* colname)
			{
			    _columnParent = colname;
			}
    inline const char*	getParentColumnName() const
			{
			    return (const char*)_columnParent;
			}
    inline void		setChildrenColumnName(const char* colname)
			{
			    _columnChildren = colname;
			}
    inline const char*	getChildrenColumnName() const
			{
			    return (const char*)_columnChildren;
			}

    //---- foreign column ----
    void		setForeignBitmapColumnName(const char*);
    const char*		getForeignBitmapColumnName() const;
    IlvBitmap*		getForeignBitmap(IliValue& value);
    IlvBitmap*		loadForeignBitmap(const char* name);

    //---- error ----
    inline void		notIncoherentTreeData() { _treeError = IlFalse; }
    inline void		thereIsIncoherentTreeData() { _treeError = IlTrue; }
    inline IlBoolean	isIncoherentTreeData() const { return _treeError; }
    virtual void	onIncoherentTreeData();

    static IlvSymbol*	IncoherentTreeDataSymbol();

    virtual IlUInt	getCallbackTypes(const char* const** names,
					 const IlvSymbol* const** types) const;

    //---- Tree ----
    virtual void	validateTree();
    virtual void	build();
    void		deleteAll();

    //---- table hook ----
    virtual void	tableChanged();
    virtual void	tableDeleted();
    virtual void	columnInserted(IlInt colno);
    virtual void	columnChanged(IlInt colno);
    virtual void	columnToBeDeleted(IlInt colno);
    virtual void	columnDeleted(IlInt colno);
    virtual void	columnMoved(IlInt src, IlInt dest);
    virtual void	rowInserted(IlInt rowno);
    virtual void	rowChanged(IlInt rowno);
    virtual void	rowToBeDeleted(IlInt rowno);
    virtual void	rowDeleted(IlInt rowno);
    virtual void	rowMoved(IlInt src, IlInt dest);
    virtual void	rowFetched(IlInt rowno);
    virtual void	columnCellsChanged(IlInt colno);
    virtual void	cellChanged(IlInt rowno, IlInt colno);

    virtual void	startOfBatch();
    virtual void	endOfBatch();
    IlInt		getBatchCount() const;

    //---- Other ----

    DeclareTypeInfo();
    DeclareIOConstructors(IliDbOldTreeGadget);

    virtual void	setHolder(IlvGadgetHolder* holder);
    virtual void	activate(IlvTreeGadgetItem*);
    virtual void	applyReferences(IlvApplyObject f, IlAny a);
    virtual IlBoolean	handleEvent(IlvEvent& event);

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    virtual IlvValue&	queryValue(IlvValue& value) const;
    virtual IlBoolean	applyValue(const IlvValue& value);
    static void		GetAccessors(const IlvSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count);
    virtual IlBoolean	f_supportsAccessor(IliFieldAccessorTag) const;
    static  IlBoolean	F_supportsAccessor(IliFieldAccessorTag);

    IlInt		getParentColumnIndex() const;
    IlInt		getChildrenColumnIndex() const;

protected:
    IliString		_columnParent;
    IliString		_columnChildren;
    IliString		_bitmapColumnName;
    IliDbTreeItem*	_root;
    IlBoolean		_treeError;
    IliFormat		_formatItem;
    IliTableHook*	_tableHook;
    IlBoolean		_doCompute;
    IlInt		_batchCount;

    IlInt		_columnValueItem;
    IlInt		_columnDisplayItem;
    IlInt		_columnBitmapItem;

    virtual void	displayRoots();
    IliDbTreeItem*	addDbTree(IliValue&);
    virtual void	addDbTreeItem(IlvTreeGadgetItem*, IliDbTreeItem*);
    IlvTreeGadgetItem*	findDbTreeItem(IlvTreeGadgetItem*,
				       const char*,
				       IliValue&);
    IlInt		getIndexForInsertDbTreeItem(IlvTreeGadgetItem*,
						    const char* name);

    void		init();
    void		initMappingAndFormat();
    const char*		getFormattedValue(IliValue&);

    void		refreshColumn(IlInt);
    inline void		refreshAll()
			{
			    startOfBatch();
			    endOfBatch();
			}
};

// --------------------------------------------------------------------------
// IliDbTreeModel
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbTreeModel : public IliGadgetModel
{
public:
    IliDbTreeModel();
    virtual ~IliDbTreeModel();

    //---- Basic methods ----
    virtual const char*	getName() const;
    virtual IlBoolean	isSubtypeOf(const IliString&) const;

    //---- Data sources events ----
    virtual void	tableChanged(const IliModelHookInfo&);
    virtual void	tableDeleted(const IliModelHookInfo&);
    virtual void	rowInserted(const IliModelHookInfo&);
    virtual void	rowToBeChanged(const IliModelHookInfo&);
    virtual void	rowChanged(const IliModelHookInfo&);
    virtual void	rowToBeDeleted(const IliModelHookInfo&);
    virtual void	rowDeleted(const IliModelHookInfo&);
    virtual void	rowsExchanged(const IliModelHookInfo&);
    virtual void	rowsInserted(const IliModelHookInfo&);
    virtual void	rowsFetched(const IliModelHookInfo&);
    virtual void	rowFetched(const IliModelHookInfo&);
    virtual void	rowMoved(const IliModelHookInfo&);

    //---- Tree events ----
    virtual IlBoolean	buildTree() = 0;
    void		displayTree();
    virtual IlBoolean	validateTree();

    //---- data source ----
    virtual IlInt	computeDataSourceIndex(IlInt, const IliValue&) const;

    //---- deletion ----
    virtual IlBoolean	isSupportDeletionItem(IlInt, const IliValue&) const;
    virtual void	executeDeleteItem(IlInt,
					  const IliValue&,
					  const IliValue&);

    //---- Insertion ----
    virtual IlBoolean	isSupportInsertChildItem(IlInt, const IliValue&) const;
    virtual IlBoolean	executeCreateItem(IlInt,const IliValue&,const char*,
					  const IliValue&,
					  const char*);
    virtual IlInt	computeInsertionPositionDbTreeItem(IlvTreeGadgetItem*,
							   const char*);

    //---- refresh ----
    virtual IlBoolean	refreshAll();

    //---- tools ----
    const char*		computeLabelItem(IliValue&, IliValue&, IlInt dsi = 0);
    IlvBitmap*		computeBitmapItem(IliValue&);
    IlvBitmap*		loadBitmap(const char* name);

    //---- Command to impact tree gadget ----
    IlBoolean		deleteTreeItem(IlInt dsi, const IliValue& id);
    IlBoolean		deleteTreeItem(IlInt dsi,
				       const IliValue& id,
				       const IliValue&);
    IlBoolean		addTreeItem(IlInt dsi,
				    const IliValue& id,
				    const IliValue& label,
				    const IliValue& bmp);
    IlBoolean		addTreeItem(IlInt dsi,
				    const IliValue& id,
				    const IliValue& parent,
				    const IliValue& label,
				    const IliValue& bmp);

    //---- Command to impact data source ----
    void		cmdDsDeleteItem(IliDbTreeItem*,
					const IliValue& parent);

    //---- Other commands ----
    void		cmdDeleteAll();
    IlvTreeGadgetItem*	cmdFindDbTreeItem(IlvTreeGadgetItem* from,
					  const char*,
					  IliValue&);
    void		cmdAddDbTreeItem(IlvTreeGadgetItem* from,
					 IliDbTreeItem* man);

    //---- Tree ----
    void		setTreeGadget(IliDbTreeGadget*);
    IliDbTreeGadget*	getTreeGadget() const;

    //---- columns ----
    void		getColumnValue(IliTableBuffer*, IlInt, IliValue&);
    void		computeIndex(IlInt);

    //---- For inspector ----
    virtual IlBoolean	isFirstColParentNeeded() const;
    virtual IlInt	getDataSourcesMax() const;

protected:
    IliDbTreeGadget*	_tree;
    IliMultiDataSourceUsage* _dsTree;
    IlInt		_cols[IliDbTreeColumnCount];

    IliDbTreeItem*	_root;
    IliDbTreeItem*	_last;

    IlBoolean		_refreshMode;

    IliDbTreeItem*	getDbTreeGadgetItem(IlInt,
					    const IliValue&,
					    const IliValue* parent = 0,
					    IliDbTreeItem* from = 0) const;
};

// --------------------------------------------------------------------------
// IliDbTreeItemDialogModel
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbTreeItemDialogModel : public IliModel
{
public:
    IliDbTreeItemDialogModel();
    virtual ~IliDbTreeItemDialogModel();

    //---- Basic methods ----
    IliDeclareModel();

    //---- Tree Gadget ----
    void		setDbTreeGadget(IliDbTreeGadget*);
    IliDbTreeGadget*	getDbTreeGadget() const;

    void		setNewItemIdentifier(const IliValue& val);
    const IliValue&	getNewItemIdentifier() const;

    void		setNewItemLabel(const char* label);
    const char*		getNewItemLabel() const;

    const IliValue&	getNewItemParent() const;

    void		setNewItemBitmap(const char* bmp);
    const char*		getNewItemBitmap() const;

    IlInt		getNewItemDataSourceIndex() const;

    //---- Dialog ----
    virtual IlBoolean	editValues(IlvDisplay* display,
				   IlvAbstractView* view,
				   IlBoolean edit);

    //---- Models ----
    IliDeclareAccessorForModel(IliDbTreeItemDialogModel);

protected:
    IliDbTreeGadget*	_tree;
};

// --------------------------------------------------------------------------
// IliDbTreePopupMenuModel
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbTreePopupMenuModel : public IliModel
{
public:
    IliDbTreePopupMenuModel();
    virtual ~IliDbTreePopupMenuModel();

    //---- Basic methods ----
    IliDeclareModel();

    //---- Properties ----
    void		setDbTreeGadget(IliDbTreeGadget*);
    IliDbTreeGadget*	getDbTreeGadget() const;

    void		setPopupMenu(IlvPopupMenu*);
    IlvPopupMenu*	getPopupMenu() const;

    //---- Tools ----
    IlBoolean		isItemDeletionEnabled() const;
    IlBoolean		isItemInsertionChildEnabled() const;
    IlBoolean		isItemInsertionSiblingEnabled() const;
    IlBoolean		isItemEditionEnabled() const;

    void		addDeletePopupItem(const char* label = 0) const;
    void		addInsertChildPopupItem(const char* label = 0) const;
    void		addInsertSiblingPopupItem(const char* label = 0) const;
    void		addEditPopupItem(const char* label = 0) const;
    void		addPopupSeparator() const;
    void		addPopupItem(const char* label,
				     IlvGraphicCallback cb,
				     IlAny arg = 0) const;
    IlvMenuItem*	getPopupItem(IlInt) const;

    //---- Popup menu ----
    virtual void	makePopupMenu(IlvDisplay* display) const;

    //---- Models ----
    IliDeclareAccessorForModel(IliDbTreePopupMenuModel);

protected:
    IliDbTreeGadget*	_tree;
    IlvPopupMenu*	_popup;
};

// --------------------------------------------------------------------------
// IliDbTreeGadget
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbTreeGadget : public IlvTreeGadget
{
public:
    IliDbTreeGadget(IlvDisplay* display,
		    const IlvRect& rect,
		    IlUShort thickness = IlvDefaultGadgetThickness,
		    IlvPalette* palette = 0);
    ~IliDbTreeGadget();

    void		init();

    DeclareTypeInfo();
    DeclareIOConstructors(IliDbTreeGadget);

    //---- Data sources ----
    inline void		setTreeDataSource(IlInt dsi, IliDataSource* ds);
    inline
    IliDataSource*	getTreeDataSource(IlInt dsi) const;
    inline void		setTreeDataSourceName(IlInt dsi,const char* name);
    inline const char*	getTreeDataSourceName(IlInt dsi) const;
    inline IlInt	getTreeDataSourceCount() const;
    inline void		setTreeDataSourceCount(IlInt,IlInt);
    inline void		addTreeDataSourceName(const char* name);
    void		setTreeDataSourceCount(IlInt count);

    inline void		setIdentifierColumnName(IlInt dsi,const char* name);
    inline const char*	getIdentifierColumnName(IlInt dsi) const;
    inline IlInt	getIdentifierColumnIndex(IlInt dsi) const;

    inline void		setLabelColumnName(IlInt dsi, const char* name);
    inline const char*	getLabelColumnName(IlInt dsi) const;
    inline IlInt	getLabelColumnIndex(IlInt dsi) const;

    inline void		setParentColumnName(IlInt dsi, const char* name);
    inline const char*	getParentColumnName(IlInt dsi) const;
    inline IlInt	getParentColumnIndex(IlInt dsi) const;

    inline void		setBitmapColumnName(IlInt dsi,const char* name);
    inline const char*	getBitmapColumnName(IlInt dsi) const;
    inline IlInt	getBitmapColumnIndex(IlInt dsi) const;

    //---- Refresh ----
    virtual void	refreshAll();
    void		needRefreshAll(IlBoolean = IlTrue);
    IlBoolean		isRefreshAllNeeded() const;

    IliDsUsageDeclareBatch(tree);
    IliDsUsageDeclareBatchDirect();

    IlInt		getBatchCount() const;
    IlBoolean		isBatchMode() const;

    //---- Hook Event ----
    IliDsUsageDeclareFctConnectDirect();
    virtual void	treeTableChanged(IlInt dsi);
    virtual void	treeTableDeleted(IlInt dsi);
    virtual void	treeRowInserted(IlInt dsi, IlInt rowno);
    virtual void	treeRowToBeChanged(IlInt dsi, IlInt rowno);
    virtual void	treeRowChanged(IlInt dsi, IlInt rowno);
    virtual void	treeRowToBeDeleted(IlInt dsi, IlInt rowno);
    virtual void	treeRowDeleted(IlInt dsi, IlInt rowno);
    virtual void	treeRowFetched(IlInt dsi, IlInt rowno);
    virtual void	treeRowMoved(IlInt dsi, IlInt from, IlInt to);
    virtual void	treeRowsInserted(IlInt dsi, IlInt from, IlInt to);
    virtual void	treeRowsFetched(IlInt dsi, IlInt from, IlInt to);

    //---- Holders -----
    virtual void	setHolder(IlvGraphicHolder*);

    //---- Tree Error ----
    void		notIncoherentTreeData();
    void		thereIsIncoherentTreeData();
    IlBoolean		isIncoherentTreeData() const;
    IlBoolean		hasPreviousEventError() const;
    virtual void	onIncoherentTreeData();
    static IlvSymbol*	IncoherentTreeDataSymbol();
    virtual IlUInt	getCallbackTypes(const char* const**      names,
					 const IlvSymbol* const** types) const;

    //---- Error reporting ----
    void		addErrorSink(IliErrorSink* sink);
    void		removeErrorSink(IliErrorSink* sink);
    void		setErrorReporter(IliErrorReporter* reporter);
    IliErrorReporter*	getErrorReporter() const;
    void		reportErrors(const IliErrorList& list) const;

    //---- Accessors ----
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    virtual IlvValue&	queryValue(IlvValue& value) const;
    virtual IlBoolean	applyValue(const IlvValue& value);
    virtual const IlvValueTypeClass* getValueType(const IlvSymbol* name) const;

    static void		GetAccessors(const IlvSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count);

    //---- properties ----
    const IliFormat&	getFormat(IlInt dsi = 0) const;
    void		setFormat(const IliFormat& fmt, IlInt dsi = -1);

    void		sortItems(IlBoolean enable);

    IlBoolean		isItemsSorted() const;

    void		enableItemDeletion(IlBoolean enable);
    IlBoolean		isItemDeletionEnabled() const;

    void		setRecursiveDeletion(IlBoolean enable);
    IlBoolean		isRecursiveDeletion() const;

    IlBoolean		isConfirmOnDeleteRequired() const;
    void		requireConfirmOnDelete(IlBoolean require);

    void		enableItemInsertion(IlBoolean enable);
    IlBoolean		isItemInsertionEnabled() const;

    void		enableItemEdition(IlBoolean enable);
    IlBoolean		isItemEditionEnabled() const;

    void		useItemDialog(IlBoolean enable);
    IlBoolean		isItemDialogUsed() const;

    void		useItemPopupMenu(IlBoolean enable);
    IlBoolean		isItemPopupMenuUsed() const;

    //---- Edition ----
    virtual IlBoolean	onDeleteItem();
    virtual IlBoolean	onEditItem();
    virtual IlBoolean	onInsertChildItem();
    virtual IlBoolean	onInsertSiblingItem();

    void		setNewItemIdentifier(const IliValue& id);
    const IliValue&	getNewItemIdentifier() const;

    void		setNewItemLabel(const char* label);
    const char*		getNewItemLabel() const;

    void		setNewItemParent(const IliValue& id);
    const IliValue&	getNewItemParent() const;

    void		setNewItemBitmap(const char* bitmap);
    const char*		getNewItemBitmap() const;

    void		setNewItemDataSourceIndex(IlInt dsi);
    IlInt		getNewItemDataSourceIndex() const;

    const IliValue&	getDeletedItemIdentifier() const;
    IlInt		getDeletedItemDataSourceIndex() const;

    const IliValue&	getSelectedItemIdentifier() const;
    IlInt		getSelectedItemDataSourceIndex() const;

    IlInt		getItemRowIndex(IlvTreeGadgetItem*) const;

    IlInt		getItemDataSourceIndex(IlvTreeGadgetItem*) const;

    //---- Dialog item ----
    void		setItemDialogModelName(const char* name);
    const char*		getItemDialogModelName() const;

    IlBoolean		callItemDialog(IlBoolean edit = IlFalse);

    //---- Popup menu ----
    void		setPopupMenuModelName(const char* name);
    const char*		getPopupMenuModelName() const;

    //---- Symbols ----
    static IlvSymbol*	DeleteItemSymbol();
    static IlvSymbol*	InsertChildItemSymbol();
    static IlvSymbol*	InsertSiblingItemSymbol();
    static IlvSymbol*	EditItemSymbol();

    void		dontContinueProcess();

    //---- Models ----
    void		setModel(const char* name);   // OLD
    const char*		getModel() const; // OLD

    void		setModelName(const char* name);
    const char*		getModelName() const;
    IliDbTreeModel*	getModelObject() const;

    IliDeclareDataAccessorForModel(IliDbTreeModel);
    IliDeclareAccessorForModel(IliDbTreeModel);

    //---- About IlvTreeGadget ----
    virtual IlBoolean	handleTreeEvent(IlvEvent&);
    virtual void	startEdit(IlvGadgetItem*);
    virtual void	endEdit(IlvGadgetItem*);

    //---- Event ----
    IlBoolean		handleDeleteEvent();
    IlBoolean		handleEditEvent(IlvTreeGadgetItem*, IlBoolean load);
    IlBoolean		handleInsertEvent(IlBoolean);
    IlBoolean		handleRightBtnEvent();

    //---- Other ----
    IlvTreeGadgetItem*	getTreeGadgetItem(IlInt dsi,
					  const IliValue& id,
					  const IliValue* = 0) const;

protected:
    //---- Menu ----
    IlvPopupMenu*	_popup;
    IliString		_popupModel;

    //---- building ----
    IlBoolean		_treeError;
    IlBoolean		_previousEventError;

    //---- Data sources ----
    IliMultiDataSourceUsage*	_dsTree;

    //---- Refresh ----
    IlBoolean		_needRefreshTree;
    IlBoolean		_inEndOfBatch;
    IlInt		_batchCount;

    //---- Properties ----
    IlBoolean		_sortItems;
    IlBoolean		_deleteItem;
    IlBoolean		_deleteRecursive;
    IlBoolean		_confirmDelete;
    IlBoolean		_insertItem;
    IlBoolean		_editItem;
    IlBoolean		_itemDialog;
    IlBoolean		_itemPopup;

    //---- insertion ----
    IliValue		_newItemId;
    IliValue		_newItemParent;
    IliString		_newItemLabel;
    IliString		_newItemBmp;
    IlInt		_newItemDsNdx;

    IliValue		_oldItemId;
    IliValue		_oldItemParent;
    IliString		_oldItemLabel;
    IliString		_oldItemBmp;
    IlInt		_oldItemDsNdx;

    IlBoolean		_continueProcess;

    //---- Dialog ----
    IliString		_dialogModel;

    //---- Look ----
    IliFormat*		_dsFormat;

    //---- Other ----
    IlInt		getItemLevel(IlvTreeGadgetItem*) const;
    IlBoolean		impactEditedValues(IlvTreeGadgetItem*);
    IlBoolean		loadDataForEdition(IlvTreeGadgetItem*);

private:
    IlBoolean		isPopupItemDeletionEnabled() const;
    IlBoolean		isPopupItemInsertionChildEnabled() const;
    IlBoolean		isPopupItemInsertionSiblingEnabled() const;
    IlBoolean		isPopupItemEditionEnabled() const;

    friend class IliDbTreePopupMenuModel;
    friend class IliDbTreeModel;
};

// --------------------------------------------------------------------------
// IliTreeItemDialog
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliTreeItemDialog : public IlvDialog
{
public:
    IliTreeItemDialog(IlvDisplay*,
		      IlvAbstractView*,
		      IliDbTreeGadget*,
		      IlBoolean);
    ~IliTreeItemDialog();

    void		initGadgets();

    virtual void	apply();
    virtual void	onBnCB(IlInt);

    IlvMessageLabel*	getTXT(IlInt) const;
    IlvButton*		getBTN(IlInt) const;
    IliEntryField*	getEDT(IlInt) const;

protected:
    IliDbTreeGadget*	_tree;
    IlBoolean		_edit;
    IlInt		_columnCount;
    IlInt		_columnsIndex[IliDbTreeColumnCount];
    IlInt		_columnsName[IliDbTreeColumnCount];

    void		getColumnTitle(IlInt, IliString&);
};

// --------------------------------------------------------------------------
// Macro for IliDbTreeModel
// --------------------------------------------------------------------------
#define IliRegisterDbTreeModel(cl) \
  IliDbTreeGadget::RegisterModel(new cl)

// --------------------------------------------------------------------------
// Macro for IliDbTreeItemDialogModel
// --------------------------------------------------------------------------
#ifdef DOXYGEN_GENERATION
void IliRegisterDbTreeItemDialogModel(cl);
#else
#define IliRegisterDbTreeItemDialogModel(cl) \
  IliDbTreeItemDialogModel::RegisterModel(new cl)
#endif

// --------------------------------------------------------------------------
// Macro for IliDbTreePopupMenuModel
// --------------------------------------------------------------------------
#ifdef DOXYGEN_GENERATION
void IliRegisterDbTreePopupMenuModel(cl);
#else
#define IliRegisterDbTreePopupMenuModel(cl) \
  IliDbTreePopupMenuModel::RegisterModel(new cl)
#endif

// --------------------------------------------------------------------------
// Inlines functions for IliDbTreeGadget
// --------------------------------------------------------------------------

IliMultiDsUsageCodeDSAccess(IliDbTreeGadget, Tree, _dsTree)
IliMultiDsUsageCodeColAccess(IliDbTreeGadget,
			     Identifier,
			     _dsTree,
			     IliDbTreeIdentifierColumn)
IliMultiDsUsageCodeColAccess(IliDbTreeGadget,
			     Label,
			     _dsTree,
			     IliDbTreeLabelColumn)
IliMultiDsUsageCodeColAccess(IliDbTreeGadget,
			     Parent,
			     _dsTree,
			     IliDbTreeParentColumn)
IliMultiDsUsageCodeColAccess(IliDbTreeGadget,
			     Bitmap,
			     _dsTree,
			     IliDbTreeBitmapColumn)

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliDbTreeGadget);

#endif
