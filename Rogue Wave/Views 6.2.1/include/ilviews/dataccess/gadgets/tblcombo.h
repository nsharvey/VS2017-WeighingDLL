// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/tblcombo.h
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
// Declaration of the IliTableComboBox class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Tblcombo_H
#define __Ili_Tblcombo_H

#if !defined(__Ilv_Gadgets_Scombo_H)
#  include <ilviews/gadgets/scombo.h>
#endif
#if !defined(__Ili_Abscombo_H)
#  include <ilviews/dataccess/gadgets/abscombo.h>
#endif
#if !defined(__Ili_MapTable_H)
#  include <ilviews/dataccess/maptable.h>
#endif
#if !defined(__Ili_Tablegad_H)
#  include <ilviews/dataccess/gadgets/tablegad.h>
#endif

class IliAbstractTablePopupView;

class ILV_DBG_EXPORTED IliScrolledComboBox
    : public IlvScrolledComboBox,
      public IliFieldItf
{
public:
    IliScrolledComboBox(IlvDisplay*		display,
			const IlvPoint&		point,
			const char*		label,
			const char* const*	labels	  = 0,
			IlUShort		count	  = 0,
			IlUShort		thickness =
			                            IlvDefaultGadgetThickness,
			IlvPalette*		palette	  = 0);
    IliScrolledComboBox(IlvDisplay*		display,
			const IlvRect&		rect,
			const char*		label,
			const char* const*	labels	  = 0,
			IlUShort		count	  = 0,
			IlUShort		thickness =
			                            IlvDefaultGadgetThickness,
			IlvPalette*		palette	  = 0);

    virtual ~IliScrolledComboBox();

    DeclareTypeInfo();
    DeclareIOConstructors(IliScrolledComboBox);

    virtual void	setHolder(IlvGadgetHolder*);
    virtual IlBoolean	handleEvent(IlvEvent&);
    virtual void	doIt();

    virtual void	changeSelection(IlUShort);

    // -- implements IliFieldItf

    virtual
    const IliValue&	f_getValue(IlBoolean = IlFalse) const;
    virtual IlBoolean	f_setValue(const IliValue&, IlBoolean = IlFalse);
    virtual void	f_refresh();
    virtual IlBoolean	f_isConsistent() const;
    virtual void	f_internalToExternal();
    virtual IlBoolean	f_externalToInternal();
    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean);

    virtual void	f_setForeignTable(IliTable*, IlBoolean = IlFalse);
    virtual void	f_setForeignValueColumnName(const char*);
    virtual void	f_setForeignDisplayColumnName(const char*);

    virtual const IlvValueTypeClass* getValueType(const IlvSymbol*) const;
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static void		GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    virtual IlBoolean	f_supportsAccessor(IliFieldAccessorTag) const;
    static IlBoolean	F_supportsAccessor(IliFieldAccessorTag);

protected:
    IliValue		_value;
    IlBoolean		_readOnly;
    IliTableHook*	_tableHook;
    IlUInt		_batchCount;
    IlBoolean		_refreshRequested;

    void		init();
    void		startOfBatch();
    void		endOfBatch();
    IlInt		posInTable(const IliValue&, IlInt) const;
    IlInt		getValueColumn() const;
    IlInt		getDisplayColumn() const;
    void		refreshValuesList();

    friend class IliScrolledComboBoxHook;
};

class ILV_DBG_EXPORTED IliTableComboBox
    : public IliAbstractComboBox
{
public:
    IliTableComboBox(IlvDisplay*	display,
		     const IlvRect&	rect,
		     IlUShort		thickness = IlvDefaultGadgetThickness,
		     IlvPalette*	palette = 0);
    IliTableComboBox(IlvDisplay*	display,
		     const IlvRect&	rect,
		     IliTable*		table,
		     IlBoolean		owner,
		     IlUShort		thickness = IlvDefaultGadgetThickness,
		     IlvPalette*	palette = 0);
    IliTableComboBox(IlvDisplay*	display,
		     const IlvRect&	rect,
		     const IliMapEntry*	map,
		     IlBoolean		owner,
		     IlUShort		thickness = IlvDefaultGadgetThickness,
		     IlvPalette*	palette = 0);
    virtual ~IliTableComboBox();

    IlBoolean		selectRow(IlInt rowno);
    IlBoolean		selectNextRow();
    IlBoolean		selectPreviousRow();

    virtual void	openAt(const IlvPoint&, IlBoolean);
    virtual void	close();
    virtual IlBoolean	isOpen() const;

    // overrides IliEntryField
    virtual IlBoolean	isMappingEnabled() const;

    // overrides IliFieldItf
    virtual IlBoolean	f_setValue(const IliValue&, IlBoolean = IlFalse);
    virtual void	f_refresh();
    virtual IlBoolean	f_isConsistent() const;
    virtual IlBoolean	f_complete();
    virtual IlBoolean	f_canMapValue() const;
    virtual IlBoolean	f_externalToInternal();
    virtual void	f_mapValue(IliValue&) const;
    virtual void	f_setForeignTable(IliTable*, IlBoolean = IlFalse);
    virtual void	f_setForeignValueColumnName(const char*);
    virtual void	f_setForeignDisplayColumnName(const char*);
    virtual IlBoolean	f_isAutoFitPullDown() const;
    virtual void	f_setAutoFitPullDown(IlBoolean);

    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static void		GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    virtual IlBoolean	f_supportsAccessor(IliFieldAccessorTag) const;
    static  IlBoolean	F_supportsAccessor(IliFieldAccessorTag);

    // -- Popup view
    void		setUserComboBoxWindow(IliAbstractTablePopupView* dlg);
    IliAbstractTablePopupView* getUserComboBoxWindow() const;
    IliAbstractTablePopupView* getUserComboBoxWindow();
    IliAbstractTablePopupView* getComboBoxWindow();
    IliAbstractTablePopupView* getComboBoxWindow() const;

    // -- Columns display

    IlInt		getValueColumn() const;
    IlInt		getDisplayColumn() const;
    void		setTableColumns(const char* list);
    const char*		getTableColumns() const;
    IlInt		getDisplayColumnsCount() const;
    IlInt		getDisplayColumns(IlInt*) const;
    IlBoolean		isMultiColumnsMode() const;
    IlInt		getPullDownWidth() const;
    void		setPullDownWidth(IlInt width);
    IlBoolean		isAutoFitting() const;
    void		setAutoFitting(IlBoolean flag);

    // overrides IlvGadget
    DeclareTypeInfo();
    DeclareIOConstructors(IliTableComboBox);

    IlBoolean		handleEvent(IlvEvent&);

protected:
    IlInt		_displayColumnToken;
    IlInt		_valueColumnToken;
    IlInt		_pullDownWidth;
    IlBoolean		_autoFitting;

    IliAbstractTablePopupView* _userPopupView;
    IlBoolean		_multiColumns;
    IliString		_tableColumns;

    void		init();

    IlBoolean		mapExternalToInternal(const char*, IliValue&) const;
    IlBoolean		findRow(const IliValue&,
				IlInt&, IlInt,
				IlBoolean = IlFalse) const;

    virtual IlBoolean	completeLabel(const char*, IliValue&) const;
    virtual IlBoolean	labelToValue(const char*,
				     IliValue&,
				     IlBoolean) const;
    virtual void	valueToLabel(const IliValue&);

    virtual void	onUpKey();
    virtual void	onDownKey();

    IlInt		strColToIntCol(const char* colname) const;
};

// --------------------------------------------------------------------------
// IliAbstractTablePopupView
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliAbstractTablePopupView
    : public IlvGadgetContainer
{
public:
    IliAbstractTablePopupView(IlvDisplay*	display,
			      IlvSystemView	transient = 0);

    virtual ~IliAbstractTablePopupView();

    virtual void	makeTable();
    virtual void	prepareOpen(IlInt* dispcol, IlInt count, IlInt rowno);
    virtual void	closeDone();
    virtual void	selectInitialRow(IlInt rowno);
    virtual void	makeWindowResize(IlvDim w, IlvDim h);
    virtual IlvDim	getWindowWidth() const;
    virtual IlvDim	getWindowHeight() const;
    virtual IlvCursor*	getWindowCursor();
    virtual void	handleInput(IlvEvent& event);
    virtual void	processEvent(IlvEvent& event, const IlvRect& bbox);
    virtual IlBoolean	processInputEvent(IlvEvent& event);
    virtual void	select();
    IlBoolean		isOpenOn(const IliTableComboBox* combo) const;
    IlBoolean		isOpen() const;
    IlBoolean		isWindowsLook() const;
    IlBoolean		isGrabbed() const;
    void		setComboBox(IliTableComboBox* combo);
    IliTableComboBox*	getComboBox() const;

    // Internals
    void		close();
    void		open(IliTableComboBox*,
			     const IlvPoint&,
			     IlInt*, IlInt, IlInt,
			     IlBoolean);
    void		holderHadGrab(IlBoolean);
    IlBoolean		hadGrabHolder() const;

    IlBoolean		isMakeDone() const;

protected:
    IliTableComboBox*	_combo;
    IlBoolean		_isGrabbed;
    IlBoolean		_isOpen;
    IlBoolean		_dontInvertArrow;
    IlBoolean		_holderHadGrab;
    IlBoolean		_makeDone;
};

// --------------------------------------------------------------------------
// IliTablePopupView
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliTablePopupView
    : public IliAbstractTablePopupView
{
public:
    IliTablePopupView(IlvDisplay* display, IlvSystemView transient = 0);
    virtual ~IliTablePopupView();

    virtual void	makeTable();
    virtual void	closeDone();
    virtual void	selectInitialRow(IlInt);
    virtual void	prepareOpen(IlInt*, IlInt, IlInt);
    virtual void	makeWindowResize(IlvDim, IlvDim);
    virtual IlvDim	getWindowHeight() const;
    virtual IlvDim	getWindowWidth() const;

    virtual void	processEvent(IlvEvent&, const IlvRect&);
    virtual IlBoolean	processInputEvent(IlvEvent&);
    virtual void	select();
    virtual IliTable*	getTableForDisplay();

    // -- Others
    IliTableGadget*	getTableGadget() const { return _tg; }

    virtual void	bufferedDraw(const IlvRegion&);

    static
    IliTablePopupView*	GetView(IlvDisplay*, IlvSystemView = 0);
    static void		AtExit();

protected:
    IliTableGadget*		_tg;
    static IliTablePopupView*	_theView;
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliTableComboBox);

#endif /* !__Ili_Tblcombo_H */
