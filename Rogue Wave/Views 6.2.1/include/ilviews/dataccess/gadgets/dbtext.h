// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dbtext.h
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
// Declaration of the IliDbText class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbtext_H
#define __Ili_Dbtext_H

#if !defined(__Ilv_Gadgets_Text_H)
#  include <ilviews/gadgets/text.h>
#endif
#if !defined(__Ili_Fielditf_H)
#  include <ilviews/dataccess/fielditf.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbText
    : public IlvText, public IliFieldItf
{
public:
    IliDbText(IlvDisplay* display,
	      const IlvRect& rect,
	      IlUShort thickness = IlvDefaultGadgetThickness,
	      IlvPalette* palette = 0);
    virtual ~IliDbText();

    // -- implement IliFieldItf

    virtual const IliValue&	f_getValue(IlBoolean = IlFalse) const;
    virtual IlBoolean		f_setValue(const IliValue&,
					   IlBoolean = IlFalse);

    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean);

    virtual IlBoolean	f_isConsistent() const;
    virtual void	f_selectTextForAppend();
    virtual void	f_selectTextForOverwrite();

    virtual void	f_internalToExternal();
    virtual IlBoolean	f_externalToInternal();

    DeclareTypeInfo();
    DeclareIOConstructors(IliDbText);

    virtual void	setHolder(IlvGadgetHolder*);
    virtual void	valueChanged();
    void		applyReferences(IlvApplyObject, IlAny);
    virtual IlBoolean	handleEvent(IlvEvent&);

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
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliDbText);

#endif /* !__Ili_Dbtext_H */
