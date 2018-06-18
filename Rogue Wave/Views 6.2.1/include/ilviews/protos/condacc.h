// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/condacc.h
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
// Declaration of user accessors that hold a condition
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Condacc_H
#define __Ilv_Protos_Condacc_H

#if !defined(__Ilv_Protos_Useracc_H)
#include <ilviews/protos/useracc.h>
#endif

// ---------------------------------------------------------------------------
// IlvConditionAccessor	An accessor that changes another value
//				depending on a condition.
// ---------------------------------------------------------------------------
enum IlvConditionAccessorOperator {
    IlvCondNoOp,
    IlvCondEqual,
    IlvCondNotEqual,
    IlvCondLessThan,
    IlvCondGreaterThan,
    IlvCondLessOrEqual,
    IlvCondGreaterOrEqual,
    IlvCondOperator
};

class ILVPROEXPORTED IlvConditionAccessor : public IlvUserAccessor
{
public:
    IlvConditionAccessor(const char* name,
			 const IlvValueTypeClass* type,
			 IlvDisplay* display,
			 IlvConditionAccessorOperator op,
			 const char* operand,
			 const char* assignedAttribute,
			 const char* valueIfTrue,
			 const char* valueIfFalse = 0);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvConditionAccessor);

protected:
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);

    IlvDisplay*				_display;
    IlvConditionAccessorOperator	_op;
    IlSymbol*				_operandValue;
    IlSymbol*				_leftValue;
    IlSymbol*				_rightValue1;
    IlSymbol*				_rightValue2;
};

// ---------------------------------------------------------------------------
// IlvSwitchAccessor	An accessor that implements a switch statement
// ---------------------------------------------------------------------------

class ILVPROEXPORTED IlvSwitchAccessor : public IlvUserAccessor
{
public:
    IlvSwitchAccessor(const char* name,
		      const IlvValueTypeClass* type,
		      IlvDisplay* display,
		      const char* test,
		      IlUInt numValues,
		      const char** values);
    ~IlvSwitchAccessor();
    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvSwitchAccessor);

protected:
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);

    IlvDisplay*		_display;
    IlSymbol*		_test;
    IlUInt		_numValues;
    IlSymbol**		_values;
};

// ---------------------------------------------------------------------------
// IlvOperatorAccessor		Boolean/arithmetic operators.
// ---------------------------------------------------------------------------
enum IlvOperatorAccessorOperation {
    IlvOperatorAccessorAdd,
    IlvOperatorAccessorSubstract,
    IlvOperatorAccessorMultiply,
    IlvOperatorAccessorDivide,
    IlvOperatorAccessorModulo,
    IlvOperatorAccessorAnd,
    IlvOperatorAccessorOr,
    IlvOperatorAccessorNot,
    IlvOperatorAccessorMinus,
    IlvOperatorAccessorEqual,
    IlvOperatorAccessorNotEqual,
    IlvOperatorAccessorLessThan,
    IlvOperatorAccessorGreaterThan,
    IlvOperatorAccessorLessOrEqual,
    IlvOperatorAccessorGreaterOrEqual
};

class ILVPROEXPORTED IlvOperatorAccessor : public IlvUserAccessor
{
public:
    IlvOperatorAccessor(const char* name,
			const IlvValueTypeClass* type,
			IlvDisplay* display,
			IlvOperatorAccessorOperation op,
			IlUInt count,
			const char** operands);
    ~IlvOperatorAccessor();

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvOperatorAccessor);

protected:
    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;

    virtual IlUInt	compareValues(const IlvAccessorHolder* object,
				 const IlvAccessible* ref,
				 IlvValue* values,
				 IlUShort count,
				 IlvValueArray& diffs) const;

    IlvDisplay*				_display;
    IlvOperatorAccessorOperation	_op;
    IlUInt				_count;
    IlSymbol**				_operands;
};

// ---------------------------------------------------------------------------
// IlvMinMaxAccessor		Special case for min/max/other values
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvMinMaxAccessor : public IlvUserAccessor
{
public:
    IlvMinMaxAccessor(const char* name,
		      const IlvValueTypeClass* type,
		      IlvDisplay* display,
		      const char* minimumValue,
		      const char* maximumValue,
		      const char* exceptValue,
		      const char* assignedAttribute,
		      const char* valueIfBelow,
		      const char* valueIfInBetween,
		      const char* valueIfAbove);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvMinMaxAccessor);

protected:
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);

    IlvDisplay*		_display;
    IlSymbol*		_minimumValue;
    IlSymbol*		_maximumValue;
    IlSymbol*		_exceptValue;
    IlSymbol*		_leftValue;
    IlSymbol*		_rightValue1;
    IlSymbol*		_rightValue2;
    IlSymbol*		_rightValue3;
};

// ---------------------------------------------------------------------------
// IlvMultiRepAccessor		Accessor for multi-representation symbols
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvMultiRepAccessor : public IlvUserAccessor
{
public:
    IlvMultiRepAccessor(const char* name,
			const IlvValueTypeClass* type,
			IlUInt count,
			const char** nodenames);
    ~IlvMultiRepAccessor();

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvMultiRepAccessor);

protected:
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);

    IlUInt		_count;
    IlSymbol**		_nodenames;
};

IlvDECLAREINITPROCLASS(condacc)

#endif /* __Ilv_Protos_Condacc_H */
