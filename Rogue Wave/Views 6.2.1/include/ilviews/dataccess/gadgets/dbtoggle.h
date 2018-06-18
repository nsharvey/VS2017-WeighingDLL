// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dbtoggle.h
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
// Declaration of the IliDbToggle class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbtoggle_H
#define __Ili_Dbtoggle_H

#if !defined(__Ilv_Gadgets_Toggle_H)
#  include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ili_Fielditf_H)
#  include <ilviews/dataccess/fielditf.h>
#endif

// NOTE: IliDbToggle has an IliIntegerType
//	 other types are converted if possible
// f_setReadOnly() is not yet fully supported

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbToggle
: public IlvToggle, public IliFieldItf
{
public:
    IliDbToggle(IlvDisplay* display,
		const char* label,
		const IlvRect& rect,
		IlUShort thickness = IlvDefaultGadgetThickness,
		IlvPalette* palette = 0);
    IliDbToggle(IlvDisplay* display,
		const IlvPoint& at,
		const char* label,
		IlUShort thickness = IlvDefaultGadgetThickness,
		IlvPalette* palette = 0);
    IliDbToggle(IlvDisplay* display,
		IlvBitmap* bitmap,
		const IlvRect& rect,
		IlUShort thickness = IlvDefaultGadgetThickness,
		IlvPalette* palette = 0);
    IliDbToggle(IlvDisplay* display,
		const IlvPoint& at,
		IlvBitmap* bitmap,
		IlUShort thickness = IlvDefaultGadgetThickness,
		IlvPalette* palette = 0);

    // Implements IliFieldItf
    virtual const IliValue& f_getValue(IlBoolean = IlFalse) const;
    virtual IlBoolean	f_setValue(const IliValue&, IlBoolean = IlFalse);
    virtual void	set3StatesMode(IlBoolean flag);
    virtual IlBoolean	is3StatesMode() const;

    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean);

    virtual IlBoolean	f_isConsistent() const;
    virtual void	f_internalToExternal();
    virtual IlBoolean	f_externalToInternal();

    virtual void	f_refresh();
    virtual IlBoolean	f_complete();
    virtual IlBoolean	f_canMapValue() const;
    virtual void	f_mapValue(IliValue&) const;
    virtual void	f_setForeignTable(IliTable*, IlBoolean = IlFalse);
    virtual void	f_setForeignValueColumnName(const char*);
    virtual void	f_setForeignDisplayColumnName(const char*);

    virtual IlBoolean	f_hasLabel() const;
    virtual const char* f_getLabel() const;
    virtual void	f_setLabel(const char*);

    DeclareTypeInfo();
    DeclareIOConstructors(IliDbToggle);

    virtual void	setHolder(IlvGadgetHolder*);
    virtual void	activate();
    virtual void	applyReferences(IlvApplyObject, IlAny);
    virtual IlBoolean	handleEvent(IlvEvent&);

    virtual
    const IlvValueTypeClass* getValueType(const IlvSymbol*) const;
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static  void	GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    virtual IlBoolean	f_supportsAccessor(IliFieldAccessorTag) const;
    static  IlBoolean	F_supportsAccessor(IliFieldAccessorTag);

protected:
    IlBoolean		_3StatesMode;
    IlBoolean		_readOnly;
    IliValue		_value;
    IliValue		_valueMap;
    IlInt		_displayColumnToken;
    IlInt		_valueColumnToken;

    void		init();

    IlInt		getValueColumn() const;
    IlInt		getDisplayColumn() const;

    void		stateToValue(IliValue&);
    void		valueToState(const IliValue&);
    IlBoolean		isSameState(const IliValue&);

    IlBoolean		mapExternalToInternal(IliValue&) const;
    IlBoolean		findRow(const IliValue&, IlInt&,
				IlInt, IlBoolean = IlFalse) const;
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliDbToggle);

#endif /* !__Ili_Dbtoggle_H */
