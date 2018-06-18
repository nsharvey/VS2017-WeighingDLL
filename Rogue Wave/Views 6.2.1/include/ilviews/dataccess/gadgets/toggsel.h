// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/toggsel.h
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
// Declaration of the IliToggleSelector class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Toggsel_H
#define __Ili_Toggsel_H

#if !defined(__Ilv_Gadgets_Toggle_H)
#  include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Frame_H)
#  include <ilviews/gadgets/frame.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ili_Fielditf_H)
#  include <ilviews/dataccess/fielditf.h>
#endif
#if !defined(__Ili_Gadset_H)
#  include <ilviews/dataccess/gadgets/gadset.h>
#endif

class ILV_DBG_EXPORTED IliToggleSelector
: public IliGadgetSet, public IliFieldItf
{
public:
    IliToggleSelector(IlvDisplay* display,
		      const IlvRect& rect,
		      IlUShort thickness = IlvDefaultGadgetThickness,
		      IlvPalette* palette = 0);

    ~IliToggleSelector();

    IlInt		getLabelsCount() const;

    const char* const*	getLabels(IlInt& count) const;

    void		setLabels(const char* const* strings, IlInt count);

    const char*		getLabel(IlInt index) const;

    IlInt		getLabelIndex(const char* label, IlInt from = 0) const;

    IlBoolean		setLabel(IlInt index, const char* label);

    IlBoolean		insertLabel(IlInt index, const char* label);

    IlBoolean		removeLabel(IlInt index);

    IlBoolean		appendLabel(const char* label);

    IlInt		whichSelected() const;

    void		setSelected(IlInt which);

    void		getPreferredSize(IlvDim& width, IlvDim& height) const;

    // -- overrides IliGadgetSet

    virtual IlBoolean	setFocusObject(IlvGadget*);

    // -- overrides IlvGadget

    DeclareTypeInfo();
    DeclareIOConstructors(IliToggleSelector);

    virtual void	setHolder(IlvGadgetHolder*);
    virtual void	applyTransform(const IlvTransformer* t);
    virtual IlBoolean	handleEvent(IlvEvent& event);

    // -- implements IliFieldItf

    virtual
    const IliValue&	f_getValue(IlBoolean = IlFalse) const;
    virtual IlBoolean	f_setValue(const IliValue&,
				   IlBoolean = IlFalse);

    virtual void	f_refresh();

    virtual IlBoolean	f_isConsistent() const;
    virtual void	f_internalToExternal();
    virtual IlBoolean	f_externalToInternal();

    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean);

    virtual IlBoolean	f_hasLabel() const;
    virtual const char* f_getLabel() const;
    virtual void	f_setLabel(const char*);

    virtual void	f_setForeignTable(IliTable*,
					  IlBoolean = IlFalse);
    virtual void	f_setForeignValueColumnName(const char*);
    virtual void	f_setForeignDisplayColumnName(const char*);

    virtual
    const IlvValueTypeClass* getValueType(const IlvSymbol*) const;
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
    IlvFrame*		_frame;
    IlvArray		_toggles;
    IliTableHook*	_tableHook;
    IlUInt		_batchCount;
    IlBoolean		_refreshRequested;

    IlvToggle*		getToggle(IlInt) const;
    IlInt		getToggleIndex(IlvToggle*) const;
    void		reformat();
    void		createFrame();
    virtual void	objectNeedsReDraw(IlvGadget*);
    virtual void	regionNeedsReDraw(const IlvRegion&);

    void		init();
    void		startOfBatch();
    void		endOfBatch();
    IlInt		posInTable(const IliValue&, IlInt) const;
    IlInt		getValueColumn() const;
    IlInt		getDisplayColumn() const;
    void		refreshToggles();
    IlInt		getEffectiveVisibleItemsCount() const;

    friend class IliToggleSelectorHook;
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliToggleSelector);

#endif /* !__Ili_Toggsel_H */
