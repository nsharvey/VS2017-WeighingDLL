// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/tablegad.h
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
// Declaration of the IliTableGadget class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Tablegad_H
#define __Ili_Tablegad_H

#if !defined(__Ilv_Base_Error_H)
#  include <ilviews/base/error.h>
#endif
#if !defined(__Ilv_Graphics_Tooltip_H)
#  include <ilviews/graphics/tooltip.h>
#endif
#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgets_Scrollb_H)
#  include <ilviews/gadgets/scrollb.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ili_Palspec_H)
#  include <ilviews/dataccess/palspec.h>
#endif
#if !defined(__Ili_Tblgmisc_H)
#  include <ilviews/dataccess/gadgets/tblgmisc.h>
#endif
#if !defined(__Ili_Errorrep_H)
#  include <ilviews/dataccess/errorrep.h>
#endif
#if !defined(__Ili_Entryfld_H)
#  include <ilviews/dataccess/gadgets/entryfld.h>
#endif
#if !defined(__Ili_Memtable_H)
#  include <ilviews/dataccess/memtable.h>
#endif
#if !defined(__Ili_Tblcombo_H)
#  include <ilviews/dataccess/gadgets/tblcombo.h>
#endif
#if !defined(__Ili_Tblsel_H)
#  include <ilviews/dataccess/tblsel.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliTableGadgetToolTip
    : public IlvToolTip
{
public:
    IliTableGadgetToolTip();

    DeclarePropertyInfoRO();
    DeclarePropertyIOConstructors(IliTableGadgetToolTip);

    virtual void	init(const IlvView*,
			     const IlvGraphic*,
			     const IlvPoint&);
    virtual void	reInit(const IlvView*,
			       const IlvGraphic*,
			       const IlvPoint&);
    virtual void	show(IlvView*, IlvRect&);
};

// --------------------------------------------------------------------------
struct IliDrawCellStruct
{
    IlvPort* dst;
    IlInt rowno;
    IlInt tblColno;
    const char* label;
    IlvAlignment align;
    IlBoolean selected;
    IlvRect bbox;
    IlvPalette* palette;
    const IlvRegion* clip;
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliCellPaletteStruct
{
public:
    IliCellPaletteStruct();
    ~IliCellPaletteStruct();

    IlInt		getRowno() const;

    IlInt		getTableColno() const;

    IlBoolean		isSelected();

    IlvPalette*		getFillPalette() const;

    void		setFillPalette(IlvPalette* pal);

    IlvPalette*		getTextPalette() const;

    void		setTextPalette(IlvPalette* pal);

    // Compatibility
    IlInt		rowno;
    IlInt		tblColno;
    IlBoolean		selected;
    IlvPalette*		fillPalette;
    IlvPalette*		textPalette;

protected:
    IlvPalette*		_fillPalette;
    IlvPalette*		_textPalette;

    friend class IliTableGadget;
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliTableGadget
    : public IlvGadget,
      public IliFieldItf
{
public:
    IliTableGadget(IlvDisplay*		display,
		   const IlvRect&	rect,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette = 0);
    IliTableGadget(IlvDisplay*		display,
		   IliTable*		table,
		   IlBoolean		owner,
		   const IlvRect&	rect,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette = 0);
    virtual ~IliTableGadget();

    // Values
    const IliTable*	getTable() const;
    IliTable*		getTable();
    virtual void	setTable(IliTable* table, IlBoolean owner = IlTrue);

    IlBoolean		isTableOwner() const;

    inline
    IliTableContext*	getTableContext() const { return _context; }

    IlInt		getRowsCount() const;
    IlInt		getExtendedRowsCount() const;
    IlInt		getColumnsCount() const;
    IliValue		at(IlInt rowno, IlInt colno) const;
    IliValue		at(IlInt rowno, const char* colname) const;
    const IliValue&	getValue(IlInt colno) const;
    const IliValue&	getValue(IliName colname) const;
    IlBoolean		setValue(IlInt colno, const IliValue& value);
    IlBoolean		setValue(IliName colname, const IliValue& value);

    virtual IlBoolean	validate(IlBoolean interactive = IlFalse);
    virtual void	cancel();

    // State
    IlBoolean		isInsertRow(IlInt rowno) const;
    IlBoolean		isInInsertMode() const;
    IlBoolean		isInUpdateMode() const;
    inline IlBoolean	isOnInsertRow() const
	{ return isInsertRow(getCurrentRow()); }

    // Properties
    IlBoolean		isShowingHeaders() const;
    void		showHeaders(IlBoolean flag);
    IlBoolean		isShowingMarkers() const;
    void		showMarkers(IlBoolean flag);
    IlBoolean		isShowingInsertRow() const;
    IlBoolean		showInsertRow(IlBoolean flag);
    IlBoolean		isUsingRelief() const;
    void		useRelief(IlBoolean flag);

    IlBoolean		isFillingBackground() const;
    void		fillBackground(IlBoolean);
    IlBoolean		isShowingGrid() const;
    void		showGrid(IlBoolean flag);
    IlBoolean		isKeyboardDeleteRowEnabled() const;
    void		enableKeyboardDeleteRow(IlBoolean flag);
    IlBoolean		isConfirmOnDeleteRequired() const;
    void		requireConfirmOnDelete(IlBoolean flag);
    IlBoolean		isKeyboardRefreshEnabled() const;
    void		enableKeyboardRefresh(IlBoolean flag);
    IlvDim		getRowHeight() const;
    void		setRowHeight(IlvDim h);
    IlvDim		getHeaderHeight() const;
    void		setHeaderHeight(IlvDim h);
    IlvDim		getMarkerWidth() const;
    void		setMarkerWidth(IlvDim w);
    IlInt		getVisibleRowsCount(IlBoolean& lastRowClipped) const;
    void		setVisibleRowsCount(IlInt count);

    IlvDim		getCellsMaxWidth() const;
    IlvDim		getCellsMaxHeight() const;

    IlvDim		getCellsVisibleWidth() const;
    IlvDim		getCellsVisibleHeight() const;

    IlvRect		getCellsRect(const IlvTransformer* t = 0) const;
    IlInt		computeBestColumnWidth(IlInt colno) const;
    IlvScrollBar*	getScrollBar(IlvPosition which) const;
    void		showScrollBar(IlvPosition which, IliShowMode mode);
    IliShowMode		getScrollBarShowMode(IlvPosition which) const;
    IlInt		getFirstRow() const;
    IlInt		getFirstColumn() const;
    IlInt		getFixedColumnsCount() const;
    IlBoolean		setFixedColumnsCount(IlInt count);
    IlBoolean		isReadOnly() const;
    IlBoolean		setReadOnly(IlBoolean flag);
    IlBoolean		isRowSelectEnabled() const;
    void		enableRowSelect(IlBoolean flag);
    IlBoolean		isCellEditorShown() const;
    void		showCellEditor(IlBoolean flag);
    IlvFont*		getCellFont() const;
    virtual void	setCellFont(IlvFont* font);
    IlvColor*		getCellBackground() const;
    virtual void	setCellBackground(IlvColor* color);
    IlvColor*		getCellForeground() const;
    virtual void	setCellForeground(IlvColor* color);
    IliTableFittingMode getAutoFittingMode() const;
    void		setAutoFittingMode(IliTableFittingMode mode);
    IlBoolean		isColumnGeometryLocal() const;
    void		setColumnGeometryLocal(IlBoolean flag);
    IlBoolean		isColumnMoveAllowed() const;
    void		allowColumnMove(IlBoolean flag);
    IlBoolean		isColumnResizeAllowed() const;
    void		allowColumnResize(IlBoolean flag);
    IlBoolean		isRowMoveAllowed() const;
    void		allowRowMove(IlBoolean flag);
    IlBoolean		isRowResizeAllowed() const;
    void		allowRowResize(IlBoolean flag);
    IlBoolean		isSelectionAlwaysShown() const;
    void		showSelectionAlways(IlBoolean flag);
    IlBoolean		isSortEnabled() const;
    void		enableSort(IlBoolean flag);
    void		sortColumn(IlInt colno);
    void		setCompareFunction(IliCompareFunction	fct,
					   IlAny		arg = 0);
    IliCompareFunction	getCompareFunction() const;
    IlAny		getCompareData() const;

    IlBoolean		isLookSensitive() const;
    void		setLookSensitive(IlBoolean);

    IlBoolean		isSelectionLookSensitive() const;
    void		setSelectionLookSensitive(IlBoolean);

    IlBoolean		isUsingTableProperties() const;
    void		useTableProperties(IlBoolean flag);
    const char*		getTablePropertyManagerName() const;
    void		setTablePropertyManagerName(const char* name);
    const IliTablePropertyManager* getTablePropertyManager() const;

    IliTablePropertyManager* getTablePropertyManager();
    void		setTablePropertyManager(IliTablePropertyManager* pMgr);

    const IliTablePropertyManager* getEffectiveTablePropertyManager() const;
    IliTablePropertyManager* getEffectiveTablePropertyManager();

    // Columns
    IlInt		getRealIndex(IlInt colno) const;
    IlInt		getVisualIndex(IlInt colno) const;
    IlBoolean		moveColumn(IlInt from, IlInt to);
    IliFieldItf*	getColumnEditor(IlInt colno) const;
    IlBoolean		setColumnEditor(IlInt		colno,
					IliFieldItf*	fld,
					IlBoolean	owner = IlTrue);
    IlInt		getColumnDisplayWidth(IlInt colno) const;
    void		setColumnDisplayWidth(IlInt colno, IlInt width);
    IlBoolean		isColumnVisible(IlInt colno) const;
    void		setColumnVisible(IlInt colno, IlBoolean flag);
    IlInt		getFirstViewableColumn();
    IlInt		getNextViewableColumn(IlInt);
    IlInt		getPreviousViewableColumn(IlInt);
    IlInt		getLastViewableColumn();

    // Selection
    void		getSelection(IliTableSelection& sel) const;
    IlInt		getCurrentRow() const;
    IlInt		getCurrentColumn() const;
    virtual IlBoolean	setSelection(const IliTableSelection& sel);
    IlBoolean		selectCell(IlInt rowno, IlInt colno);
    IlBoolean		selectRow(IlInt rowno);
    IlBoolean		selectColumn(IlInt colno);
    IlBoolean		selectAll();
    IlBoolean		selectNone();
    virtual IlBoolean	gotoNextColumn();
    virtual IlBoolean	gotoPreviousColumn();
    virtual IlBoolean	gotoNextRow();
    virtual IlBoolean	gotoPreviousRow();
    inline IlBoolean	gotoInsertRow()
	{ return isShowingInsertRow() ? selectRow(getRowsCount()) : IlFalse; }

    IlBoolean		isBoundToDataSource() const;
    void		bindToDataSource(IlBoolean flag);

    IlBoolean		isMultiSelectionEnabled() const;
    void		enableMultiSelection(IlBoolean flag);

    // Clipboard
    void		copyToClipboard(const IliTableSelection& sel) const;
    void		copyToClipboard() const;
    void		pasteFromClipboard(const IliTableSelection& sel);
    void		pasteFromClipboard();

    // Geometry
    IlBoolean		cellBBox(const IliTableSelection&	sel,
				 IlvRect&			rect,
				 const IlvTransformer*		t = 0) const;

    IlvPos		getRowTop(IlInt, IlvTransformer* = 0);
    IlvPos		getColumnLeft(IlInt, IlvTransformer* = 0);

    IlBoolean		pointToSelection(const IlvPoint&	pt,
					 IliTableSelection&	sel,
					 const IlvTransformer*	t = 0) const;
    void		ensureVisible(IliTableSelection sel);
    void		ensureSelectionVisible();
    virtual void	scrollTo(IlInt rowno, IlInt colno);
    void		scrollToRow(IlInt rowno);
    void		scrollToColumn(IlInt colno);
    void		fitColumns(IliTableFittingMode fm);

    // Refresh
    void		refreshCell(IlInt rowno, IlInt colno);
    void		refreshRow(IlInt rowno);
    void		refreshColumn(IlInt colno);
    void		refreshAll();
    void		refreshCellPalettes(IlInt rowno, IlInt tblColno);

    void		startOfBatch();
    void		endOfBatch();
    IlInt		getBatchCount() const;

    // Error reporting
    void		addErrorMessage(const IliErrorMessage& msg);
    void		addErrorMessage(const char* msg);
    void		addErrorSink(IliErrorSink* sink);
    void		removeErrorSink(IliErrorSink* sink);
    IliErrorReporter*	getErrorReporter() const;
    void		setErrorReporter(IliErrorReporter* reporter);
    void		reportErrors(const IliErrorList& errorList) const;
    void		forwardErrorMessage(const IliErrorMessage&);

    // Callbacks
    IlvSymbol*		getCallbackContext() const;
    virtual void	onDoubleClick();
    virtual void	onValidateCell();
    virtual void	onValidateRow();
    virtual void	onEnterCell();
    virtual void	onQuitCell();
    virtual void	onEnterRow();
    virtual void	onQuitRow();
    virtual void	onSelectionChange();
    virtual void	onEnterUpdateMode();
    virtual void	onPrepareUpdate();
    virtual void	onQuitUpdateMode();
    virtual void	onEnterInsertMode();
    virtual void	onPrepareInsert();
    virtual void	onQuitInsertMode();
    virtual void	onPrepareDeleteRow();
    virtual void	onCancelEdits();
    virtual void	onDeleteRow();
    virtual void	onFetchRow();
    virtual void	onDrawCell();
    virtual void	onGetCellPalette();

    // Callback information
    void		dontValidateCell();
    void		dontValidateRow();
    void		dontDeleteRow();
    IlInt		getDeletedRow() const;
    IlInt		getFetchedRow() const;
    IlInt		getInsertedRow() const;

    IliDrawCellStruct*	getDrawCellStruct() const;
    void		defaultDrawCell() const;
    IliCellPaletteStruct* getCellPaletteStruct() const;
    IlBoolean		hasCustomCellPalettes() const;
    void		setCustomCellPalettes(IlBoolean flag);

    // Customization
    virtual void	drawCell(IlvPort*		dst,
				 IlInt			rowno,
				 IlInt			colno,
				 const char*		label,
				 IlvAlignment		align,
				 IlBoolean		selected,
				 const IlvRect&		bbox,
				 IlvPalette*		palette,
				 const IlvRegion*	clip) const;
    virtual IlvPalette* getHeaderTextPalette(IlInt colno) const;
    virtual void	drawHeader(IlvPort*		dst,
				   IlInt		colno,
				   const char*		label,
				   IlBoolean		selected,
				   const IlvRect&	bbox,
				   const IlvRegion*	clip) const;
    virtual void	drawMarker(IlvPort*		dst,
				   IlInt		rowno,
				   IlBoolean		selected,
				   IlBoolean		current,
				   const IlvRect&	bbox,
				   const IlvRegion*	clip) const;
    virtual void	drawCorner(IlvPort*		dst,
				   IlBoolean		selected,
				   const IlvRect&	bbox,
				   const IlvRegion*	clip) const;
    virtual void	drawVertRule(IlvPort*		dst,
				     IlvPos		y1,
				     IlvPos		y2,
				     IlvPos		x,
				     IlInt		colno,
				     IlInt		rownoTop,
				     IlInt		rownoBot,
				     IlvPalette*	palette,
				     const IlvRegion*	clip) const;

    virtual void	drawHorzRule(IlvPort*		dst,
				     IlvPos		x1,
				     IlvPos		x2,
				     IlvPos		y,
				     IlInt		rowno,
				     IlInt		colnoLeft,
				     IlInt		colnoRight,
				     IlvPalette*	palette,
				     const IlvRegion*	clip) const;

    virtual
    IliFieldItf*	getCustomEditor(IlInt		rowno,
					IlInt		colno,
					IliFieldItf*	fld) const;

    // Accessors
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static  void	GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    virtual IlBoolean	f_supportsAccessor(IliFieldAccessorTag) const;
    static  IlBoolean	F_supportsAccessor(IliFieldAccessorTag);

    // Methods
    static const char*	GetValidateValueName();
    static const char*	GetCancelValueName();
    static const char*	GetGetColumnValueName();
    static const char*	GetGetColumnAtValueName();
    static const char*	GetIsInInsertModeValueName();
    static const char*	GetAddErrorMessageValueName();
    static const char*	GetDontValidateRowValueName();
    static const char*	GetDontValidateCellValueName();
    static const char*	GetDontDeleteRowValueName();

    // Symbols
    static IlvSymbol*	DoubleClickSymbol();
    static IlvSymbol*	ValidateCellSymbol();
    static IlvSymbol*	ValidateRowSymbol();
    static IlvSymbol*	EnterCellSymbol();
    static IlvSymbol*	QuitCellSymbol();
    static IlvSymbol*	EnterRowSymbol();
    static IlvSymbol*	QuitRowSymbol();
    static IlvSymbol*	SelectionChangeSymbol();
    static IlvSymbol*	EnterUpdateModeSymbol();
    static IlvSymbol*	PrepareUpdateSymbol();
    static IlvSymbol*	QuitUpdateModeSymbol();
    static IlvSymbol*	EnterInsertModeSymbol();
    static IlvSymbol*	PrepareInsertSymbol();
    static IlvSymbol*	QuitInsertModeSymbol();
    static IlvSymbol*	PrepareDeleteRowSymbol();
    static IlvSymbol*	CancelEditsSymbol();
    static IlvSymbol*	DeleteRowSymbol();
    static IlvSymbol*	FetchRowSymbol();
    static IlvSymbol*	DrawCellSymbol();
    static IlvSymbol*	GetCellPaletteSymbol();

    // Misc
    virtual
    IliTableResizeTag	resizeTest(IlvPoint&,
				   IlInt&,
				   IlInt&,
				   const IlvTransformer*) const;

    IlBoolean		isEditing() const;
    IlBoolean		isEditorVisible() const { return _editorVisible; }

    void		emptyInvalidRegion() { _invalidRgn.empty(); }
    void		extendInvalidRegion(const IlvRect& rect)
	{ _invalidRgn.add(rect); }
    const IlvRegion&	getInvalidRegion() const { return _invalidRgn; }
    void		reDrawInvalidRegion();

    void		invalidateCell(IliTableSelectionType, IlInt, IlInt);
    void		invalidateRow(IlInt);
    void		invalidateColumn(IlInt);

    // Implements IliFieldItf
    virtual IlBoolean	f_isAutoFitPullDown() const;
    virtual void	f_setAutoFitPullDown(IlBoolean);

    virtual IlBoolean	f_isConsistent() const;
    virtual void	f_internalToExternal();
    virtual IlBoolean	f_externalToInternal();
    virtual IlBoolean	f_complete();
    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean);
    virtual
    const IliValue&	f_getValue(IlBoolean = IlFalse) const;
    virtual IlBoolean	f_setValue(const IliValue&,
				   IlBoolean = IlFalse);
    virtual IlBoolean	f_isInputModified() const;
    virtual void	f_setInputModified(IlBoolean);
    virtual void	f_enableAutoReDraw(IlBoolean);
    virtual void	f_refresh();
    virtual IlBoolean	f_doConnect();
    virtual void	f_doDisconnect();
    virtual void	f_dataSourceToField(IlInt);
    virtual void	f_fieldToDataSource(IlInt);
    virtual IlBoolean	f_isColumnModified(IlInt) const;

    virtual void	f_useTableProperties(IlBoolean);
    virtual void	f_setTablePropertyManagerName(const char*);
    virtual
    const IliTablePropertyManager* f_getEffectiveTablePropertyManager() const;
    virtual IliTablePropertyManager* f_getEffectiveTablePropertyManager();

    // Overrides
    DeclareTypeInfo();
    DeclareIOConstructors(IliTableGadget);

    virtual void	draw(IlvPort*,
			     const IlvTransformer* = 0,
			     const IlvRegion* = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer*) const;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	applyTransform(const IlvTransformer*);
    virtual void	boundingBox(IlvRect&,
				    const IlvTransformer* = 0) const;

    virtual IlBoolean	zoomable() const;
    virtual void	setBackground(IlvColor*);
    virtual void	setForeground(IlvColor*);
    virtual void	setFont(IlvFont*);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setAlpha(IlvIntensity);
    virtual void	setAntialiasingMode(IlvAntialiasingMode);
    virtual void	setPalette(IlvPalette*);
    virtual void	reDraw() const;
    void		apply(IlvApplyObject, IlAny);
    void		applyReferences(IlvApplyObject, IlAny);

    virtual void	setHolder(IlvGadgetHolder*);

    virtual IlBoolean	handleEvent(IlvEvent&);

    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlvSymbol* const**) const;

    // Scrollbars

    void		scrollBarValueChanged(IlvScrollBar*);

    IlBoolean		hasComboStyle() const;
    void		setComboStyle(IlBoolean);

    virtual void	setDefaultResources();

    void		onDataSourceGotoRow(IlInt rowno);
    IlBoolean		isReallyBoundToDataSource() const;

    // Compatibility
    IlBoolean		isColumnsGeometryLocal() const
	{ return isColumnGeometryLocal(); }
    void		setColumnsGeometryLocal(IlBoolean f)
	{ setColumnGeometryLocal(f); }

    // Tooltips
    virtual void	getToolTipsText(const IlvPoint& pt, IliString& s);

    void		enableToolTips(IlBoolean flag);

    IlBoolean		areToolTipsEnabled() const;

    // Short cuts
    static void		GetRefreshShortCut(IlUShort& modifiers,
					   IlUShort& key);
    static void		SetRefreshShortCut(IlUShort modifiers, IlUShort key);

    virtual IlvPalette* getReliefPalette() const;

    void		setReliefPalette(IlvPalette* pal);

    void		disableImmediateRefresh(IlBoolean disable);

    IlBoolean		isImmediateRefreshDisabled() const;

protected:
    enum IliTG_ToDoTag {
	f_autoFit			= 0x001,
	f_adjustHeaders			= 0x002,
	f_resizeScrollBars		= 0x004,
	f_ensureSelectionVisible	= 0x008,
	f_adjustScrollBars		= 0x010,
	f_showScrollBarsIfNeeded	= 0x020,
	f_resizeEditor			= 0x040,
	f_refreshEditorLook		= 0x080,
	f_syncEditor			= 0x100
    };

    enum IliTG_Constant {
	IliMargin			= 2,
	IliDefaultMarkerWidth		= 21
    };

    // persistent members
    IliTable*		_table;
    IlBoolean		_showHeaders;
    IlBoolean		_showMarkers;
    IlBoolean		_showGrid;
    IlBoolean		_showInsertRow;
    IlBoolean		_useRelief;
    IlBoolean		_fillbg;
    IlBoolean		_fillWithCellBg;
    IlBoolean		_readOnly;
    IlBoolean		_rowSelect;
    IlBoolean		_showCellEditor;
    IlBoolean		_enableKbdDelRow;
    IlBoolean		_confirmDeletes;
    IlBoolean		_enableKbdRefresh;
    IlBoolean		_allowColumnMove;
    IlBoolean		_allowColumnResize;
    IlBoolean		_allowRowMove;
    IlBoolean		_allowRowResize;
    IlBoolean		_localColumnsGeometry;
    IlBoolean		_comboStyle;
    IlBoolean		_isLookSensitive;
    IlBoolean		_isSelectionLookSensitive;
    IlBoolean		_showSelectionAlways;
    IlBoolean		_isBoundToDataSource;
    IlBoolean		_isMultiSelEnabled;
    IlBoolean		_isSortingEnabled;
    IlBoolean		_autoFitPullDown;
    IlBoolean		_disableImmediateRefresh;

    IliTableGadgetToolTip* _tgToolTip;
    IliCompareFunction	_compareFunction;
    IlAny		_compareData;

    IliTableFittingMode _autoFittingMode;
    IlInt		_firstRow;
    IlInt		_firstColumn;
    IlInt		_fixedColumnsCount;
    IliTableSelection	_selection;
    IlvDim		_rowHeight;
    IlvDim		_headerHeight;
    IlvDim		_markerWidth;
    IliTableHeaderList	_headers;
    IliTextPalette	_textpal;
    IliShowMode		_horzSBMode;
    IliShowMode		_vertSBMode;

    // transient members
    IliTablePropertyManager* _propMgr;
    IlvRegion		_invalidRgn;
    IliReliefPalette	_relfpal;
    IlvScrollBar*	_verticalSB;
    IlvScrollBar*	_horizontalSB;
    IliTableHeaderList	_shownHeaders;
    IliTableBuffer*	_tableBuffer;
    IliTableHook*	_tableHook;
    IlvList		_errorSinks;
    IlInt		_inHandleEvent;
    IliErrorReporter*	_errorReporter;
    IliErrorSink*	_dsErrorSink;
    IliTableSelection	_prevSel;
    IlvSymbol*		_callbackContext;
    IliValue		_nullValue;
    IliFieldItf*	_focusField;
    IliTableSelection	_targetSel;
    IliDrawCellStruct*	_drawCellStruct;
    IliCellPaletteStruct* _cellPaletteStruct;
    IlInt		_lastSortedColumn;
    IliTablePropertyObserver* _propObserver;
    IliTableContext*	_context;

    IlBoolean		_forceSetSelection;
    IlBoolean		_tableOwner;
    IlBoolean		_inAutoFit;

    IlBoolean		_validateCell;
    IlBoolean		_validateRow;
    IlBoolean		_doDeleteRow;

    IlBoolean		_editorVisible;
    IlBoolean		_editorActive;
    IlBoolean		_forInsert;
    IlBoolean		_bufferModified;
    IlBoolean		_focusIn;
    IlBoolean		_inEndOfBatch;
    IlBoolean		_inBtnDown;
    IlBoolean		_inSetSelection;
    IlBoolean		_hasDrawCellCallback;
    IlBoolean		_hasGetPaletteCallback;
    IlBoolean		_callOnGetPalette;
    IlBoolean		_isContextOwner;

    IlInt		_fetchedRow;
    IlInt		_deletedRow;
    IlInt		_insertedRow;

    IlInt		_batchCount;
    IlUInt		_toDo;

    static IlUShort	_refreshShortCutKey;
    static IlUShort	_refreshShortCutModifiers;

    // Initialization
    void		adjustTableContext();
    void		setTableContext(IliTableContext*, IlBoolean);

    void		initTransientMembers();
    void		initTableGadget(IliTable* = 0);

    // Interaction
    virtual IlBoolean	handleKeyEvent(IlvEvent&);
    virtual IlBoolean	handleEditorEvent(IlvEvent&);

    // Headers
    void		insertHeader(IlInt, IlBoolean);
    void		removeHeader(IlInt);
    void		moveHeader(IlInt, IlInt);
    void		initHeaders();
    void		resetHeaders();
    void		adjustHeaders();

    // Selection
    virtual IlBoolean	doSetSelection(const IliTableSelection&);
    void		adjustTableBuffer();

    // Editopn
    IlBoolean		getValueEx(IlInt, IlInt, IliValue&) const;
    IlBoolean		editorToCache(IlBoolean = IlFalse,
				      IlBoolean = IlFalse);
    void		cacheToEditor();
    void		resizeEditor();
    void		sendFocusEvent(IlvGadget*,
				       IlvEventType,
				       IlBoolean) const;
    void		setFocusField(IliFieldItf*);
    void		setBufferModified(IlBoolean);
    void		prepareEditor(IlInt, IlInt, IliFieldItf*) const;
    void		prepareCurrentEditor() const;
    IliFieldItf*	makeDefaultEditor(IliTable*, IlInt) const;

    // Invalidate
    void		invalidateAllCells();
    void		invalidateAllRows();
    void		invalidateAllColumns();
    void		invalidateAggregate(const IliTableSelection&);
    void		invalidate();
    void		invalidateRect(const IlvRect&);
    void		invalidateGeometry();
    void		invalidateHeaders();
    void		invalidateFocus();

    // Scrollbars
    void		computeScrollRecord(IliTG_ScrollRecord&) const;
    void		createScrollBar(IlvPosition);
    void		deleteScrollBar(IlvPosition);
    void		showScrollBarsIfNeeded();
    void		resizeScrollBars();
    void		adjustScrollBars();

    // Geometry
    void		getLeftMostResizeColumns(IlInt&, IlInt&) const;
    IlvRect		getClientRect() const;

    void		computeRects(IlvRect&,
				     IlvRect&,
				     IlvRect&,
				     IlvRect&,
				     const IlvTransformer* = 0) const;

    void		computeRowsRecord(IliTG_RowsRecord&,
					  const IlvTransformer*,
					  IlvPos,
					  IlvPos,
					  IlBoolean = IlTrue) const;
    void		computeRowsRecord(IliTG_RowsRecord&,
					  const IlvTransformer* = 0,
					  IlBoolean = IlTrue) const;

    void		autoFit(IliTableFittingMode);

    // Drawing
    IlBoolean		hasGetCellPaletteCallback() const;
    IlBoolean		hasDrawCellCallback() const;

    void		draw(const IlvRect&, IlvPort*,
			     const IlvTransformer*) const;
    void		drawFrameTG(IliTG_DrawRecord&) const;
    void		callDrawCorner(IliTG_DrawRecord&) const;
    void		drawScrollBars(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    void		drawMarkers(IliTG_DrawRecord&) const;
    void		drawColumn(IliTG_DrawRecord&, IliTableHeader*) const;
    void		drawGrid(IliTG_DrawRecord&) const;

    void		drawBorderRect(IlvPort*,
				       const IlvRect&,
				       const IlvRegion*,
				       IlUShort =
				       IlvDefaultGadgetThickness) const;
    void		drawReliefRect(IlvPort*,
				       const IlvRect&,
				       const IlvRegion*,
				       IlUShort =
				       IlvDefaultGadgetThickness) const;
    void		drawReliefRectVxLook(IlvPort*,
					     const IlvRect&,
					     const IlvRegion*,
					     IlUShort =
					     IlvDefaultGadgetThickness) const;
    void		drawPluggedRect(IlvPort*,
					const IlvRect&,
					const IlvRegion*,
					IlUShort =
					IlvDefaultGadgetThickness) const;
    void		drawInvertedRect(IlvPort*,
					 const IlvRect&,
					 const IlvRegion*,
					 IlUShort =
					 IlvDefaultGadgetThickness) const;

    void		drawInvertedRectVxLook(IlvPort*,
					       const IlvRect&,
					       const IlvRegion*,
					       IlUShort =
					     IlvDefaultGadgetThickness) const;
    // Overrides

    virtual IlBoolean	classFocusable() const;
    virtual void	focusIn();
    virtual void	focusOut();
    virtual void	changeLook(const IlvLookFeelHandler*);

    // Utilities
    IlInt		getVRowsCount() const;
    void		fetchMoreRows();
    void		fetchUntilRow(IlInt);
    IliFieldItf*	getActiveEditor() const;
    void		transformOrigin(IlvRect&,
					const IlvTransformer*) const;
    void		gotoVisibleColumn(IlInt = -1);
    IlBoolean		nearestViewableColumn(IlInt&, IlInt = -1);
    IlBoolean		gotoFirstCell();
    IlBoolean		checkSelection();
    void		needs(IlUInt);
    void		copyRow(IliString&, IlInt,
				const IliTableSelection&) const;
    void		copyRow(IliString&, IlInt) const;
    IlBoolean		pasteRow(IlInt,
				 const char*&,
				 const IliTableSelection&);
    IlBoolean		pasteRow(IlInt, const char*&);

    void		forceButtonUp() const;
    void		editorLost(IliFieldItf*);

    IlInt		getLastSortedColumn() const;
    void		setLastSortedColumn(IlInt);

    IlBoolean		callPrepareDeleteRow(IlInt);

    void		tablePropertyManagerGot(IliTablePropertyManager*);
    void		tablePropertyManagerLost();
    void		checkTablePropertyManager();

    // Compatibility
    IlInt		getRealColno(IlInt colno) const
	{ return getRealIndex(colno); }
    IlInt		getVisualColno(IlInt tblColno) const
	{ return getVisualIndex(tblColno); }

    // Hooks
    virtual void	tableChanged();

    virtual void	columnInserted(IlInt);
    virtual void	columnChanged(IlInt);
    virtual void	columnToBeDeleted(IlInt);
    virtual void	columnDeleted(IlInt);
    virtual void	columnMoved(IlInt, IlInt);

    virtual void	rowsInserted(IlInt, IlInt);
    virtual void	rowInserted(IlInt);
    virtual void	rowChanged(IlInt);
    virtual void	rowToBeDeleted(IlInt);
    virtual void	rowDeleted(IlInt);
    virtual void	rowMoved(IlInt, IlInt);
    virtual void	rowsFetched(IlInt, IlInt);
    virtual void	rowFetched(IlInt);

    virtual void	columnCellsChanged(IlInt);
    virtual void	cellChanged(IlInt, IlInt);

    virtual void	namedPropertyManagerAdded(const char*);
    virtual void	namedPropertyManagerRemoved(const char*);

    friend class IliTableGadgetHook;
    friend class IliTableGadgetInteractor;
    friend class IliTableHeader;
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliTGPaletteHelper
{
public:
    IliTGPaletteHelper(const IliTableGadget*);

    IlvDisplay*		getDisplay() const { return _tg->getDisplay(); }
    IlBoolean		getProp(IlInt,
				IlInt,
				IlvSymbol*,
				IliValue&) const;
    IlvColor*		getColorProp(IlInt, IlInt, IlvSymbol*) const;
    IlvFont*		getFontProp(IlInt, IlInt, IlvSymbol*) const;
    IlBoolean		getBoolProp(IlInt, IlInt, IlvSymbol*,
				    IlBoolean&) const;
    IlBoolean		getFormatProp(IlInt,
				      IlInt,
				      IlvSymbol*,
				      IliFormat&) const;
    IlBoolean		getMaskProp(IlInt,
				    IlInt,
				    IlvSymbol*,
				    IliInputMask&) const;
    IlvPalette*		getFillPaletteProp(IlInt,
					   IlInt,
					   IlBoolean,
					   IlvPalette* palette);
    IlvPalette*		getTextPaletteProp(IlInt,
					   IlInt,
					   IlBoolean,
					   IlvPalette* palette);

private:
    const IliTableGadget*	_tg;
    const IliTable*		_table;
    const IliTablePropertyManager* _propMgr;
    IliPaletteManip		_fillPaletteManip;
    IliPaletteManip		_textPaletteManip;
};

// --------------------------------------------------------------------------
#if !defined(__Ili_Tblgitf_H)
#  include <ilviews/dataccess/intrface/tblgitf.h>
#endif

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliTableGadget);

#if defined(_MSC_VER)
#  if !defined(ILI_BUILDLIBS)
#    pragma comment(lib, "dbgadget")
#  endif
#endif

#endif /* !__Ili_Tablegad_H */
