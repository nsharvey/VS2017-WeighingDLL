// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dbnavig.h
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
// Declaration of the IliDbNavigator class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbnavig_H
#define __Ili_Dbnavig_H

#if !defined(__Ili_Fielditf_H)
#  include <ilviews/dataccess/fielditf.h>
#endif
#if !defined(__Ili_Gadset_H)
#  include <ilviews/dataccess/gadgets/gadset.h>
#endif

// --------------------------------------------------------------------------
#define	 ILI_NAVIG_UNIT 2

enum IliDbNavigatorOption {
    IliDbNavigOptConfirmDeletes = 0,
    IliDbNavigOptNavigationButtons,
    IliDbNavigOptInsertButton,
    IliDbNavigOptDeleteButton,
    IliDbNavigOptValidationButtons,
    IliDbNavigOptSelectButton,
    IliDbNavigOptClearButton,
    IliDbNavigOptVersion2,
    IliDbNavigOptPositionText,
    IliDbNavigOptRowsCountText,
    IliDbNavigOptQueryModeButton,
    IliDbNavigOptCount
};

// --------------------------------------------------------------------------
enum IliDbNavigatorTag {
    btn_First = 0,
    btn_Previous,
    btn_Next,
    btn_Last,
    btn_Position,
    btn_RowsCount,
    btn_Insert,
    btn_Delete,
    btn_Validate,
    btn_Cancel,
    btn_Select,
    btn_Clear,
    btn_QueryMode,
    btn_Count
};

// --------------------------------------------------------------------------
#ifdef DOXYGEN_GENERATION
void IliDbNavigatorStartAtOne(IlBoolean start);
#else
extern void IliDbNavigatorStartAtOne(IlBoolean start);
#endif

class ILV_INF_EXPORTED IliDataSource;

class ILV_DBG_EXPORTED IliUserBtnsEntry
{
public:
    IliString		_label;
    IlvGraphicCallback	_cb;
    IliString		_toolTip;
    IlInt		_width;

    IliUserBtnsEntry& operator=(IliUserBtnsEntry& o);
};

class ILV_DBG_EXPORTED IliDbNavigator
    : public IliGadgetSet,
      public IliFieldItf
{
public:
    IliDbNavigator(IlvDisplay*		display,
		   const IlvRect&	rect,
		   IlUShort		thickness = IlvDefaultGadgetThickness,
		   IlvPalette*		palette = 0);
    virtual ~IliDbNavigator();

    void		gotoFirst();
    void		gotoPrevious();
    void		gotoNext();
    void		gotoLast();
    void		startInsert();
    void		deleteRow();
    void		validate();
    void		cancel();
    void		select();
    void		clear();
    void		queryMode();

    void		dataSourceModified();
    IlBoolean		isConfirmOnDeleteRequired() const;
    void		requireConfirmOnDelete(IlBoolean flag);
    IlBoolean		areNavigationButtonsShown() const;
    void		showNavigationButtons(IlBoolean flag);
    IlBoolean		isInsertButtonShown() const;
    void		showInsertButton(IlBoolean flag);
    IlBoolean		isDeleteButtonShown() const;
    void		showDeleteButton(IlBoolean flag);
    IlBoolean		areValidationButtonsShown() const;
    void		showValidationButtons(IlBoolean flag);
    IlBoolean		isSelectButtonShown() const;
    void		showSelectButton(IlBoolean flag);
    IlBoolean		isClearButtonShown() const;
    void		showClearButton(IlBoolean flag);
    IlBoolean		isQueryModeButtonShown() const;
    void		showQueryModeButton(IlBoolean flag);
    IlBoolean		isPositionTextShown() const;
    void		showPositionText(IlBoolean flag);
    IlBoolean		isRowsCountTextShown() const;
    void		showRowsCountText(IlBoolean flag);

    virtual void	objectReceivedEvent(IlvGadget*);

    DeclareTypeInfo();
    DeclareIOConstructors(IliDbNavigator);

    // -- 2.0 Compatibiliy
    void		addButton(const char*		name,
				  IlvGraphicCallback	cb,
				  const char*		tooltip = 0,
				  IlInt			width = 1);
    void		removeButtons(IlBoolean gadgets = IlFalse);
    virtual void	adjustButtonsSize();

    virtual void	setSensitive(IlBoolean);
    virtual void	setHolder(IlvGadgetHolder*);
    virtual void	applyTransform(const IlvTransformer*);

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static void		GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt& count);
    virtual IlBoolean	f_supportsAccessor(IliFieldAccessorTag) const;
    static IlBoolean	F_supportsAccessor(IliFieldAccessorTag);

protected:
    IlBoolean		_hasOption[IliDbNavigOptCount];
    IlBoolean		_isButtonVisible[btn_Count];
    IlvGadget*		_stdButtons[btn_Count];
    IliUserBtnsEntry*	_userButtons;
    IlInt		_userButtonsCount;

    void		init();
    virtual void	createStdButtons();
    virtual void	enableStdButton(IlInt, IlBoolean);
    virtual void	showStdButton(IlInt, IlBoolean);
    virtual IlBoolean	canShowStdButton(IlInt, IlBoolean);
    IlBoolean		mustShowStdButton(IlInt);
    IlvGadget*		getStdButton(IlInt) const;
    IlvGadget*		createStdButton(IlvPos, const IlvRect&, IlInt&);

    void		refreshTextFields();
    virtual IlInt	getButtonWidthCount();

    void		checkFocus();
    virtual IlBoolean	f_doConnect();
    virtual void	f_doDisconnect();
    virtual void	objectNeedsReDraw(IlvGadget*);
    virtual void	regionNeedsReDraw(const IlvRegion&);
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliDbNavigator);

#endif /* !__Ili_Dbnavig_H */
