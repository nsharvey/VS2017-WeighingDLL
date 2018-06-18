// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intrface/tblgitf.h
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
// Declaration of the IliTableGadgetItf related accessor classes
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Tblgitf_H
#define __Ili_Tblgitf_H

#if !defined(__Ili_Ivalitf_H)
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif
#if !defined(__Ili_Tablegad_H)
#  include <ilviews/dataccess/gadgets/tablegad.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliTGErrorSinkForItf
: public IliErrorSinkForItf
{
public:
    IliTGErrorSinkForItf(IliTableGadget*, IlvValueInterface*);
    virtual ~IliTGErrorSinkForItf();

    virtual void free();
protected:
    IlvSafePointer* _tgPointer;
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliTableGadgetColumnItf
: public IliRefCountedValueInterface
{
public:
    IliTableGadgetColumnItf(IliTableGadget*, IlInt);
    virtual ~IliTableGadgetColumnItf();

    virtual IlBoolean getValueValueDescriptor(IlvValue&) const;
    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual IlBoolean isBeingDeleted() const;
    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    IliTableGadget* getTableGadget() const;
    IliTable* getTable() const;
protected:
    IlvSafePointer* _tgPointer;
    IlInt _token;
    IlInt _realColno;
    IlInt _visualColno;

    IlBoolean fixColno() const;
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliCellPaletteStructItf
: public IliRefCountedValueInterface
{
public:
    IliCellPaletteStructItf(IliTableGadget*);
    virtual ~IliCellPaletteStructItf();

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual IlBoolean isBeingDeleted() const;
    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    IliTableGadget* getTableGadget() const;
protected:
    IlvSafePointer* _tgPointer;
};

// --------------------------------------------------------------------------
IlvDeclareEnumTypeClass(ILV_DBG_EXPORTED, TableFittingMode);
IlvDeclareEnumTypeClass(ILV_DBG_EXPORTED, ShowMode);

IliModuleDECL_exp(ILV_DBG_EXPORTED, TableFittingMode);
IliModuleDECL_exp(ILV_DBG_EXPORTED, ShowMode);
IliModuleDECL_exp(ILV_DBG_EXPORTED, IliTableGadgetItf);

#endif /* !__Ili_Tblgitf_H */
