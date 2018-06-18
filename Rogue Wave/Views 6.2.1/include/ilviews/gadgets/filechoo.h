// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/filechoo.h
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
// Declaration of the classes IlvFileChooser
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Filechoo_H
#define __Ilv_Gadgets_Filechoo_H

#if !defined(__Ilv_Gadgets_Idialog_H)
#  include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Gadgets_Panecont_H)
#  include <ilviews/gadgets/panecont.h>
#endif
#if !defined(__Ilv_Gadgets_Toolbar_H)
#  include <ilviews/gadgets/toolbar.h>
#endif
#if !defined(__Ilv_Gadgets_Sheet_H)
# include <ilviews/gadgets/sheet.h>
#endif
#if !defined(__Ilv_Gadgets_Combo_H)
#  include <ilviews/gadgets/combo.h>
#endif
#if !defined(__Ilv_Gadgets_Tree_H)
#  include <ilviews/gadgets/tree.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#  include <ilviews/gadgets/button.h>
#endif
#if !defined(__Il_Pathname_H)
#  include <ilog/pathname.h>
#endif
#if !defined(__Ilv_Gadgets_Toolpath_H)
#  include <ilviews/gadgets/toolpath.h>
#endif
#if !defined(__Ilv_Gadgets_Matsel_H)
#  include <ilviews/gadgets/matsel.h>
#endif

typedef enum IlvFileChooserType {
    IlvFileChooserOpen,
    IlvFileChooserSave
} _IlvFileChooserType;

typedef enum IlvFileChooserDisplayMode {
    IlvFileChooserListMode,
    IlvFileChooserMatrixMode
} _IlvFileChooserDisplayMode;

typedef enum IlvFileChooserSelection {
    IlvFileChooserFileSelection,
    IlvFileChooserDirectorySelection,
    IlvFileChooserFileAndDirectorySelection
} _IlvFileChooserSelection;

typedef enum IlvFileChooserBitmapName {
    IlvFileChooserUpBmpName,
    IlvFileChooserCreateBmpName,
    IlvFileChooserMatrixBmpName,
    IlvFileChooserListBmpName,
    IlvFileChooserShowAllBmpName,
    IlvFileChooserHiddenBmpName,
    IlvFileChooserDirectoryBmpName,
    IlvFileChooserFileBmpName,
    IlvFileChooserDiskBmpName,
    IlvFileChooserDiskErrorBmpName,
    IlvFileChooserNetworkBmpName,
    IlvFileChooserCdromBmpName,
    IlvFileChooserRemovableBmpName,
    IlvFileChooserBmpNameCount
} _IlvFileChooserBitmapName;

typedef enum IlvFileChooserToolTip {
    IlvFileChooserToolTipUp,
    IlvFileChooserToolTipCreate,
    IlvFileChooserToolTipMatrix,
    IlvFileChooserToolTipList,
    IlvFileChooserToolTipShowAll,
    IlvFileChooserToolTipHidden,
    IlvFileChooserToolTipCount
} _IlvFileChooserToolTip;

typedef enum IlvFileChooserLabel {
    IlvFileChooserLabelFilename,
    IlvFileChooserLabelFilter,
    IlvFileChooserLabelApply,
    IlvFileChooserLabelCancel,
    IlvFileChooserLabelName,
    IlvFileChooserLabelType,
    IlvFileChooserLabelSize,
    IlvFileChooserLabelSizeKB,
    IlvFileChooserLabelSizeMB,
    IlvFileChooserLabelSizeGB,
    IlvFileChooserLabelCreateDirectory,
    IlvFileChooserLabelDirectoryName,
    IlvFileChooserLabelError,
    IlvFileChooserLabelWarning,
    IlvFileChooserLabelCreateDirFailed,
    IlvFileChooserLabelFile,
    IlvFileChooserLabelFolder,
    IlvFileChooserLabelNotExist,
    IlvFileChooserLabelOverwrite,
    IlvFileChooserLabelCount
} _IlvFileChooserLabel;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFileChooserOptions
{
public:
    IlvFileChooserOptions(IlvFileChooserType typ = IlvFileChooserOpen,
			  IlvFileChooserSelection sel
			  = IlvFileChooserFileSelection);

    virtual ~IlvFileChooserOptions();

    void		setTitle(const IlString& title);
    virtual
    const IlString&	getTitle() const;

    void		setLabel(IlvFileChooserLabel name,
				 const IlString& label);
    virtual
    const IlString&	getLabel(IlvFileChooserLabel name) const;
    virtual const char*	getLabel(IlvDisplay* display,
				 IlvFileChooserLabel name) const;

    void		setLabelWidth(IlInt width);
    virtual IlInt	getLabelWidth() const;

    void		setButtonWidth(IlInt width);
    virtual IlInt	getButtonWidth() const;

    void		setButtonHeight(IlInt height);
    virtual IlInt	getButtonHeight() const;

    void		setToolBarHeight(IlInt height);
    virtual IlInt	getToolBarHeight() const;

    void		setOptionsButtonWidth(IlInt width);
    virtual IlInt	getOptionsButtonWidth() const;

    void		showUpDirectoryButton(IlBoolean show);
    virtual IlBoolean	isUpDirectoryButtonShown() const;

    void		showCreateDirectoryButton(IlBoolean show);
    virtual IlBoolean	isCreateDirectoryButtonShown() const;

    void		showMatrixModeButton(IlBoolean show);
    virtual IlBoolean	isMatrixModeButtonShown() const;

    void		showListModeButton(IlBoolean show);
    virtual IlBoolean	isListModeButtonShown() const;

    void		showShowAllButton(IlBoolean show);
    virtual IlBoolean	isShowAllButtonShown() const;

    void	       setDefaultDisplayMode(IlvFileChooserDisplayMode mode);
    virtual
    IlvFileChooserDisplayMode	getDefaultDisplayMode() const;

    void		showAllByDefault(IlBoolean showAll);
    virtual IlBoolean	isShowAllByDefault() const;

    void		enableMultiSelection(IlBoolean enable);
    virtual IlBoolean isMultiSelectionEnabled() const;

    void		setBitmapName(IlvFileChooserBitmapName name,
				      const IlString& filename);
    virtual
    const IlString&	getBitmapName(IlvFileChooserBitmapName name) const;

    void		setButtonToolTip(IlvFileChooserToolTip name,
					 const IlString& tooltip);
    virtual
    const IlString&	getButtonToolTip(IlvFileChooserToolTip name) const;

    void		addFilter(const IlString& text, const IlString& ext);
    void		removeAllFilters();
    IlUShort		getFilterCount() const;
    const IlString&	getFilterText(IlUShort index) const;
    const IlString&	getFilterExtension(IlUShort index) const;
    const IlString&	getDefaultFilterExtension() const;
    void		setDefaultFilter(IlUShort index);
    virtual IlUShort	getDefaultFilter() const;
    void		useCompactSize(IlBoolean compact);
    virtual IlBoolean	isCompactSizeUsed() const;

    virtual IlBoolean	isFilterShown() const;

    IlvFileChooserType	getType() const;
    IlvFileChooserSelection	getSelectionType() const;

    void		initialize(IlvFileChooserType = IlvFileChooserOpen,
				   IlvFileChooserSelection
				   = IlvFileChooserFileSelection);

protected:
    IlvFileChooserType		_type;
    IlvFileChooserSelection	_selectionType;

    IlString			_title;

    IlBoolean			_showUpDirectory;
    IlBoolean			_showCreateDirectory;
    IlBoolean			_showMatrixMode;
    IlBoolean			_showListMode;
    IlBoolean			_showShowAll;
    IlBoolean			_multiSelection;
    IlBoolean			_compactSize;
    IlBoolean			_showAll;

    IlString*			_labels;
    IlString*			_bitmapNames;
    IlString*			_toolTips;

    IlInt			_labelWidth;
    IlInt			_buttonWidth;
    IlInt			_buttonHeight;
    IlInt			_toolbarHeight;
    IlInt			_optionsWidth;

    IlvFileChooserDisplayMode	_defaultMode;

    IlList			_filters;
    IlUShort			_defaultFilter;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvPathGadgetItem : public IlvGadgetItem
{
public:
    IlvPathGadgetItem(const char*  label,
		      IlvBitmap*   bitmap   = 0,
		      IlvPosition  position = IlvDefaultGadgetItemPosition,
		      IlUShort     spacing  = IlvDefaultGadgetItemSpacing,
		      IlBoolean    copy     = IlTrue);
    IlvPathGadgetItem(const char*  label,
		      IlvGraphic*  graphic,
		      IlvPosition  position = IlvDefaultGadgetItemPosition,
		      IlUShort     spacing  = IlvDefaultGadgetItemSpacing,
		      IlBoolean    copy     = IlTrue);

    void		setPathName(const IlPathName& path);
    const IlPathName&	getPathName() const;

protected:
    IlPathName		_pathname;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvTreePathGadgetItem : public IlvTreeGadgetItem
{
public:
    IlvTreePathGadgetItem(const char*  label,
			  IlvBitmap*   bitmap   = 0,
			  IlvPosition  position = IlvRight,
			  IlUShort     spacing  = IlvDefaultGadgetItemSpacing,
			  IlBoolean    copy     = IlTrue);
    IlvTreePathGadgetItem(const char*  label,
			  IlvGraphic*  graphic,
			  IlvPosition  position = IlvRight,
			  IlUShort     spacing  = IlvDefaultGadgetItemSpacing,
			  IlBoolean    copy     = IlTrue);

    void		setPathName(const IlPathName& path);
    const IlPathName&	getPathName() const;

protected:
    IlPathName		_pathname;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFileChooserTree : public IlvTreeGadget
{
public:
    IlvFileChooserTree(IlvDisplay*    display,
		       const IlvRect& rect,
		       IlUShort       thickness = IlvDefaultGadgetThickness,
		       IlvPalette*    palette   = 0);
    virtual
    IlvGadgetItem*	createItem(const char* label,
				   IlvGraphic* graphic = 0,
				   IlvBitmap*  bitmap  = 0,
				   IlvBitmap*  selbitmap = 0,
				   IlBoolean   copy    = IlTrue) const;
    virtual
    IlvTreeGadgetItem*	createItem(IlvTreeGadgetItem* parent,
				   const char* label,
				   IlvBitmap* bitmap,
				   IlvBitmap* selectionBitmap);
};

class IlvFileChooser;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFileChooserSheet : public IlvSheet
{
public:
    IlvFileChooserSheet(IlvDisplay* display,
			const IlvRect& rect,
			IlvFileChooser* fc);
    virtual ~IlvFileChooserSheet();

    virtual IlBoolean	handleMatrixEvent(IlvEvent&);

    virtual
    IlvGadgetItem*	createItem(const char* label,
				   IlvGraphic* graphic = 0,
				   IlvBitmap*  bitmap  = 0,
				   IlvBitmap*  selbitmap = 0,
				   IlBoolean   copy    = IlTrue) const;

    IlvMatrixCoordinate** getSelectionRange(IlUShort& count) const;

    // The following methods are already documented in matrix.h
    virtual void	set(IlUShort col,
			    IlUShort row,
			    IlvAbstractMatrixItem* item);

    virtual IlBoolean	remove(IlUShort col,
			       IlUShort row,
			       IlBoolean destroy = IlTrue);

    virtual void	insertColumn(IlUShort col = 0, IlUShort count = 1);
    virtual void	insertRow(IlUShort row = 0, IlUShort count = 1);
    virtual void	removeColumn(IlUShort col, IlBoolean d = IlTrue);
    virtual void	removeRow(IlUShort row, IlBoolean destroy = IlTrue);

    virtual void	setRowSelected(IlUShort row,
				       IlBoolean selected = IlTrue);
    virtual void	setColumnSelected(IlUShort col,
					  IlBoolean selected = IlTrue);
    virtual void	setItemSelected(IlUShort col,
					IlUShort row,
					IlBoolean selected = IlTrue);
    virtual void	deSelect();
    virtual void	deSelectAll();
    virtual void	changeSelectionTo(IlUShort col, IlUShort row);

protected:
    IlvFileChooser*	_fileChooser;
    IlvMatrixSelection	_mgrSel;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFileChooser : public IlvDialog
{
public:
    static IlPathName::SortMode _DefaultSortMode;
    IlvFileChooser(IlvDisplay*			display,
		   const char*			dir   = 0,
		   const char*			title = 0,
		   IlvFileChooserOptions*	options = 0,
		   IlvSystemView		transientFor = 0,
		   IlUInt			properties   = 0);

    ~IlvFileChooser();

    IlInt		get(IlBoolean grab = IlFalse, IlvCursor* cursor = 0);

    IlInt		getResultCount() const;
    const IlString&	getResult(IlInt index = 0) const;

    // Layouts
    void		initLayout(const IlvRect&);
    IlvPanedContainer*	initLayoutToolBar(IlvPanedContainer* parent,
					  const IlvRect& size);
    IlvPanedContainer*	initLayoutContain(IlvPanedContainer* parent,
					  const IlvRect& size);
    IlvPanedContainer*	initLayoutSelection(IlvPanedContainer* parent,
					    const IlvRect& size);
    IlvPanedContainer*	initLayoutFilter(IlvPanedContainer* parent,
					 const IlvRect& size);
    virtual
    IlvToolBarPath*	createToolBar(const IlvRect& rect) const;
    virtual
    IlvFileChooserTree*	createTreeGadget(const IlvRect& rect) const;
    virtual
    IlvFileChooserSheet* createSheet(const IlvRect& rect) const;
    virtual
    IlvTextField*	createTextField(const IlvRect& rect) const;
    virtual
    IlvComboBox*	createFilterComboBox(const IlvRect& rect)const;
    virtual IlvButton*	createCancelButton(const IlvRect& rect,
					   const IlString& label) const;
    virtual IlvButton*	createApplyButton(const IlvRect& rect,
					  const IlString& label) const;
    virtual
    IlvMessageLabel*	createMsgLabel(const IlvRect& rect,
				       const IlString& label) const;
    virtual IlvButton*	createUpButton(const IlvRect& rect) const;
    virtual IlvButton*	createCreateButton(const IlvRect& rect) const;
    virtual IlvButton*	createMatrixButton(const IlvRect& rect) const;
    virtual IlvButton*	createListButton(const IlvRect& rect) const;
    virtual IlvButton*	createShowAllButton(const IlvRect& rect) const;
    virtual IlvButton*	createHiddenButton(const IlvRect& rect) const;
    virtual IlvTreePathGadgetItem*	
			createTreeItem(const IlPathName& path) const;
    virtual
    IlvPathGadgetItem*	createSheetItem(const IlPathName& filepath,
					IlvFileChooserDisplayMode mode) const;
    virtual
    IlvTreePathGadgetItem* createDeviceItem(const IlPathName& filepath,
					    IlInt genre) const;
    virtual IlBoolean	getNewDirectoryName(IlString& name);

    IlvToolBarPath*	getToolBar() const;
    IlvFileChooserTree*	getTreeGadget() const;
    IlvFileChooserSheet*	getSheet() const;
    IlvTextField*	getTextField() const;
    IlvComboBox*	getFilterComboBox() const;
    IlvButton*		getUpButton() const;
    IlvButton*		getCreateButton() const;
    IlvButton*		getMatrixButton() const;
    IlvButton*		getListButton() const;
    IlvButton*		getShowAllButton() const;

    virtual void	initSheet();
    virtual void	initSheetForMatrixMode();
    virtual void	initSheetForListMode();
    virtual void	refreshSheet();
    virtual void	updateSheet(IlPathName& path);
    virtual void	updateToolBar(IlPathName& path);
    virtual void	addFileToSheet(const IlPathName& file);
    virtual void	addFileInMatrixMode(const IlPathName& file,
					    IlvPathGadgetItem* item);
    virtual void	addFileInListMode(const IlPathName& file,
					  IlvPathGadgetItem* item);
    virtual void	setTreePath(const IlPathName& path);
    virtual void	updateTree(IlPathName& path,
				   IlvTreePathGadgetItem* item);
    virtual IlvTreePathGadgetItem*
			fillTree(IlPathName& path,
				 IlvTreePathGadgetItem* parent,
				 IlPathName* ref = 0);
    virtual void	updateDisplayButtons();
    virtual void	updateShowAllButton();

    virtual void	matrixModeButtonClicked();
    virtual void	listModeButtonClicked();
    virtual void	upDirectoryButtonClicked();
    virtual void	createDirectoryButtonClicked();
    virtual void	filterChanged();
    virtual void	newShowAllMode(IlBoolean show);
    virtual void	adjustSheetForMatrixMode();
    virtual void	selectionChanged();
    virtual void	handleSheetDoubleClick(IlvEvent& evt);
    virtual void	processApply();

    // Events from dialog
    virtual void	resize(IlvDim w, IlvDim h);
    virtual void	moveResize(const IlvRect& rect);
    virtual void	callResize(IlvRect& rect);

    // Events from toolbar
    virtual void	rewindPath(const IlPathName& path);
    virtual void	changePath(const IlPathName& path);
    virtual void	convertSizeToLabel(IlUInt size, IlString& label) const;
    void		setCurrentPath(const IlPathName& path);
    IlvFileChooserDisplayMode	getSheetMode() const;
    void		setSortMode(IlPathName::SortMode mode);
    void		sort(IlBoolean byName);
    virtual IlBoolean	isSortedByName() const;
    void		setFilterExtension(const IlString& ext);
    virtual
    const IlString&	getFilterExtension() const;
    IlvFileChooserOptions*	getOptions() const;

protected:
    IlPathName			_currentPath;
    IlvFileChooserOptions*	_options;

    IlString**			_resultData;
    IlInt			_resultCount;
    IlInt			_resultSize;

    // Graphic objects
    IlvPanedContainer*		_mainCnt;
    IlvFileChooserTree*		_directoriesTree;
    IlvToolBarPath*		_pathToolbar;
    IlvFileChooserSheet*	_folderSheet;
    IlvComboBox*		_filterCombo;
    IlvTextField*		_choiceTfd;

    IlvButton*			_upButton;
    IlvButton*			_createButton;
    IlvButton*			_matrixModeButton;
    IlvButton*			_listModeButton;
    IlvButton*			_showAllButton;

    IlvGraphicPane*		_showAllPane;

    // Display
    IlvFileChooserDisplayMode	_sheetMode;
    IlBoolean			_showAll;

    // Sheet properties
    IlPathName::SortMode	_sortMode;
    IlInt			_columnWidth;
    IlInt			_rowCount;
    IlInt			_columnCount;
    IlInt			_itemCount;
    IlString			_filterExtension;

    // Util
    IlvBitmap*		getBitmap(IlvFileChooserBitmapName name) const;
    const char*		getLabel(IlvFileChooserLabel name) const;
    void		setToolTip(IlvGadget* gad,
				   IlvFileChooserToolTip tooltip) const;

    IlvTreePathGadgetItem*	addFilesSystem(const IlPathName& device);

    void		freeResults();
    void		buildResults(const IlString& str);
    void		addResult(const IlString& str);
    IlBoolean		getFirstDirectoryFromResults(IlString& str) const;

    virtual const char*	formatSize(IlDouble val) const;
    virtual const char*	formatSize(IlUInt val) const;
};

#endif /* ! __Ilv_Gadgets_Filechoo_H */
