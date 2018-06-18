// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/precond.h
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
// Declaration of IlvStIPrecondition classes
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Precond_H)
#define __IlvSt_Inspectors_Precond_H

#if !defined(__IlvSt_Inspectors_Genacces_H)
#  include <ivstudio/inspectors/genacces.h>
#endif

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPrecondition
    : public IlvStObject
{
    IlvDeclareInspClassInfo();
public:
    virtual IlBoolean isAccessible(IlvStIProperty** props = 0,
	       IlvStIPropertyAccessor::PropertyStatus* status = 0) const = 0;

    // Returns the accessor maybe used to evaluate the condition
    // Redefined in IlvStIPreconditionValue and IlvStICallbackPrecondition
    virtual IlvStIPropertyAccessor* getAccessor() const { return 0; }
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPreconditionValue
    : public IlvStIPrecondition
{
    IlvDeclareInspClassInfo();
public:
    typedef IlBoolean (*PreconditionValueCallback)
	(IlvStIProperty*, IlAny, IlvStIProperty**,
	 IlvStIPropertyAccessor::PropertyStatus*);

    IlvStIPreconditionValue(IlvStIPropertyAccessor* accessor,
			    const IlvStValue& valueToCompare,
			    const IlvStValue& defaultValue);
    ~IlvStIPreconditionValue();

    // ----------------------------------------------------------------------
    virtual IlBoolean isAccessible(IlvStIProperty** = 0,
			  IlvStIPropertyAccessor::PropertyStatus* = 0) const;
    virtual IlvStIPropertyAccessor* getAccessor() const { return _accessor; }

protected:
    IlvStIPropertyAccessor* _accessor;
    IlvValue _valueToCompare;
    IlvValue _defaultValue;
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStICallbackPrecondition
    : public IlvStIPrecondition
{
    IlvDeclareInspClassInfo();
public:
    typedef IlBoolean (*PreconditionValueCallback)
	(IlvStIProperty* prop, IlAny data, IlvStIProperty** val,
	 IlvStIPropertyAccessor::PropertyStatus* status);

    IlvStICallbackPrecondition(IlvStIPropertyAccessor* accessor = 0,
			       PreconditionValueCallback callback = 0,
			       IlAny data = 0);
    virtual ~IlvStICallbackPrecondition();

    // ----------------------------------------------------------------------
    virtual IlBoolean isAccessible(IlvStIProperty** = 0,
			  IlvStIPropertyAccessor::PropertyStatus* = 0) const;
    virtual IlvStIPropertyAccessor* getAccessor() const { return _accessor; }

protected:
    IlvStIPropertyAccessor* _accessor;
    PreconditionValueCallback _callback;
    IlAny                    _callbackParam;
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_precond)
#endif /* !__IlvSt_Inspectors_Precond_H */
