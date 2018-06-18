// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/inspvali.h
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
// Declaration of generic validator classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Inspvali_H
#define __IlvSt_Inspectors_Inspvali_H

#if !defined(__IlvSt_Inspectors_Genprop_H)
#  include <ivstudio/inspectors/genprop.h>
#endif

class IlvStIError;
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIValidator
    : public IlvStNamedObject
{
    IlvDeclareInspClassInfo();
public:
    IlvStIValidator(const char* name = 0, IlBoolean validateOnApp = IlTrue);

    virtual IlvStIError* check(const IlvStIProperty* prop) const = 0;
    IlBoolean getValidateOnApply() const;

    void setValidateOnApply(IlBoolean validate);

    void lock();

    void unLock();

protected:
    IlUInt _locks;
    IlBoolean _validateOnApply;
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIRangeValidator
    : public IlvStIValidator
{
    IlvDeclareInspClassInfo();
public:
    IlvStIRangeValidator(IlInt minVal = 0,
			 IlInt maxVal = 0,
			 const char* msg = 0,
			 IlBoolean validateOnApp = IlTrue);
    IlvStIRangeValidator(IlUInt minVal,
			 IlUInt maxVal,
			 const char* msg = 0,
			 IlBoolean validateOnApp = IlTrue);
    IlvStIRangeValidator(IlFloat minVal,
			 IlFloat maxVal,
			 const char* msg = 0,
			 IlBoolean validateOnApp = IlTrue);
    IlvStIRangeValidator(IlDouble minVal,
			 IlDouble maxVal,
			 const char* msg = 0,
			 IlBoolean validateOnApp = IlTrue);
    IlvStIRangeValidator(const ILV_TM_PREF tm* minVal,
			 const ILV_TM_PREF tm* maxVal,
			 const char* msg = 0,
			 IlBoolean validateOnApp = IlTrue);

    // ----------------------------------------------------------------------
    virtual IlvStIError* check(const IlvStIProperty*) const;
protected:
    IlvValue   _minValue, _maxValue;
    int        _testingMinMax; // 3: test min & max, 1: test min, 2: test max
};

// --------------------------------------------------------------------------
// IlvStIPathValidator class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPathValidator
    : public IlvStIValidator
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPathValidator(IlvDisplay*,
			IlBoolean = IlFalse,
			const char* = "&invalidFileName",
		        IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
    virtual IlvStIError* check(const IlvStIProperty*) const;
protected:
    IlvDisplay* _display;
    IlBoolean  _mustExist;
    const char* getFullPath(const IlvStIProperty*) const;

    virtual IlvStIError* checkPath(const char*) const;
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_inspvali)
#endif /* !__IlvSt_Inspectors_Inspvali_H */
