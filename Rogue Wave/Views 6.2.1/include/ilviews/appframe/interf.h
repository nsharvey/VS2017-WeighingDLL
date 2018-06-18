// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/interf.h
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
// Declaration of Document / view macros
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Interf_H)
#define __Ilv_Appframe_Interf_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif

#if defined(ILVSTD)
#include <cstdarg>
#else  /* !ILVSTD */
#include <stdarg.h>
#endif /* !ILVSTD */

class IlvDvActionDescriptor;
class IlvDvValue;
// --------------------------------------------------------------------------
#define ILVDV_CALL_METHOD		1
#define ILVDV_IS_PROCESSING_METHOD	2
#define ILVDV_GET_METHOD_UI		3
#define ILVDV_SET_FIELD_VALUE		4
#define ILVDV_GET_FIELD_VALUE		5
#define ILVDV_GETTING_OBJ_API		6
#define ILVDV_GET_METHOD		7
#define ILVDV_PROCESS_GADGETEVENTS	8

// --------------------------------------------------------------------------
extern ILVDVEXPORTEDVAR(IlvValueTypeClass*) IlvDvValueInterfaceType;
// --------------------------------------------------------------------------
// IlvDvValueInterfaceTypeClass class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvValueInterfaceTypeClass : public IlvValueTypeClass
{
public:
    IlvDvValueInterfaceTypeClass();

    virtual IlBoolean	isPersistent() const;
    virtual const char*	toString(const IlvValue&) const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};


// --------------------------------------------------------------------------
// IlvDvValue class
// --------------------------------------------------------------------------
class IlvDvInterface;
class ILVDVCLASS IlvDvValue : public IlvValue
{
public:
    IlvDvValue() : IlvValue(){}
    IlvDvValue(const IlvValue& src) : IlvValue(src){}
    IlvDvValue(IlAny p, const char* name = "") : IlvValue(name, p){}
    IlvDvValue(IlInt n, const char* name = "") : IlvValue(name, n){}
    IlvDvValue(IlUInt n, const char* name = "") : IlvValue(name, n){}
    IlvDvValue(IlFloat f, const char* name = "") : IlvValue(name, f){}
    IlvDvValue(IlDouble d, const char* name = "") : IlvValue(name, d){}
    IlvDvValue(const ILV_TM_PREF tm* time, const char* name = "")
    : IlvValue(name, time){}
    IlvDvValue(const char* s, const char* name = "") : IlvValue(name, s){}
    IlvDvValue(IlBoolean b, const char* name = "") : IlvValue(name, b){}
    IlvDvValue(IlvColor* c, const char* name = "") : IlvValue(name, c){}
    IlvDvValue(IlvFont* f, const char* name = "") : IlvValue(name, f){}
    IlvDvValue(IlvPattern* p, const char* name = "") : IlvValue(name, p){}
    IlvDvValue(IlvColorPattern* p, const char* name = "") : IlvValue(name, p){}
    IlvDvValue(IlvLineStyle* l, const char* name = "") : IlvValue(name, l){}
    IlvDvValue(IlvFillStyle  f, const char* name = "") : IlvValue(name, f){}
    IlvDvValue(IlvFillRule  f, const char* name = "") : IlvValue(name, f){}
    IlvDvValue(IlvArcMode  f, const char* name = "") : IlvValue(name, f){}
    IlvDvValue(IlvDirection d, const char* name = "") : IlvValue(name, d){}
    IlvDvValue(IlvBitmap* b, const char* name = "") : IlvValue(name, b){}
    IlvDvValue(IlvValueInterface* v, const char* name = "") 
    : IlvValue(name, v){}
    IlvDvValue(IlUShort s, const char* name = "") : IlvValue(name, (IlUInt)s){}
    IlvDvValue(IlvDvInterface* v, const char* name = "")
    : IlvValue(name, (IlAny)v)
    {
	_type = IlvDvValueInterfaceType;
    }
    IlvDvValue(const IlvValueTypeClass* type, const char* name = "")
    : IlvValue(name, (IlAny)0)
    {
	_type = type;
    }


    // ----------------------------------------------------------------------
    // Operators
    inline
    IlvDvValue& operator=(IlvDvInterface* pInterface)
			{
			    *((IlvValue*)this) = (IlAny)pInterface;
			    _type = IlvDvValueInterfaceType;
			    return *this;
			}

    inline operator	IlvDvInterface*() const
			{
			    return (IlvDvInterface*)(IlAny)(*this);
			}
    inline operator	IlUShort() const { return (IlUShort)(IlUInt)(*this); }

    inline operator	IlAny() const {return(IlAny)*(IlvValue*)this; }
    inline operator	IlInt() const {return(IlInt)*(IlvValue*)this; }
    inline operator	IlUInt() const {return(IlUInt)*(IlvValue*)this; }
    inline operator	IlFloat() const {return(IlFloat)*(IlvValue*)this; }
    inline operator	IlDouble() const {return(IlDouble)*(IlvValue*)this; }
    inline operator	ILV_TM_PREF tm*() const 
			{
			    return(ILV_TM_PREF tm*)*(IlvValue*)this;
			}
    inline operator	const char*() const 
			{
			    return (const char*)*(IlvValue*)this;
			}
    inline operator	IlBoolean() const 
			{
			    return (IlBoolean)*(IlvValue*)this;
			}
    inline operator	IlvFillStyle() const
			{
			    return (IlvFillStyle)*(IlvValue*)this;
			}
    inline operator	IlvFillRule() const
			{
			    return (IlvFillRule)*(IlvValue*)this;
			}
    inline operator	IlvArcMode() const
			{
			    return (IlvArcMode)*(IlvValue*)this;
			}
    inline operator	IlvDirection() const
			{
			    return (IlvDirection)*(IlvValue*)this;
			}
    inline operator	IlvValueInterface*() const
			{
			    return (IlvValueInterface*)*(IlvValue*)this;
			}
    inline operator	IlvPoint&() const
			{
			    return (IlvPoint&)*(IlvValue*)this;
			}
    inline operator	IlvRect&() const { return (IlvRect&)*(IlvValue*)this; }
    inline operator	IlvValue*() const
			{
			    return (IlvValue*)*(IlvValue*)this;
			}
    inline
    IlvDvValue& operator=(const IlvValue& source)
			{
			    IlvValue::operator=(source); return *this;
			}
    inline
    IlvDvValue& operator=(IlAny a)
			{
			    IlvValue::operator=(a); return *this;
			}
    inline
    IlvDvValue& operator=(IlInt i)
			{
			    IlvValue::operator=(i); return *this;
			}
    inline
    IlvDvValue& operator=(IlUInt u)
			{
			    IlvValue::operator=(u); return *this;
			}
    inline
    IlvDvValue& operator=(IlFloat f)
			{
			    IlvValue::operator=(f); return *this;
			}
    inline
    IlvDvValue& operator=(IlDouble d)
			{
			    IlvValue::operator=(d); return *this;
			}
    inline
    IlvDvValue& operator=(const ILV_TM_PREF tm* time)
			{
			    IlvValue::operator=(time); return *this;
			}
    inline
    IlvDvValue& operator=(const char* s)
			{
			    IlvValue::operator=(s); return *this;
			}
    inline
    IlvDvValue& operator=(IlBoolean b)
			{
			    IlvValue::operator=(b); return *this;
			}
    inline
    IlvDvValue& operator=(IlvColor* c)
			{
			    IlvValue::operator=(c); return *this;
			}
    inline
    IlvDvValue& operator=(IlvFont* f)
			{
			    IlvValue::operator=(f); return *this;
			}
    inline
    IlvDvValue& operator=(IlvPattern* p)
			{
			    IlvValue::operator=(p); return *this;
			}
    inline
    IlvDvValue& operator=(IlvColorPattern* p)
			{
			    IlvValue::operator=(p); return *this;
			}
    inline
    IlvDvValue& operator=(IlvLineStyle* l)
			{
			    IlvValue::operator=(l); return *this;
			}
    inline
    IlvDvValue& operator=(IlvFillStyle f)
			{
			    IlvValue::operator=(f); return *this;
			}
    inline
    IlvDvValue& operator=(IlvFillRule f)
			{
			    IlvValue::operator=(f); return *this;
			}
    inline
    IlvDvValue& operator=(IlvArcMode f)
			{
			    IlvValue::operator=(f); return *this;
			}
    inline
    IlvDvValue& operator=(IlvDirection f)
			{
			    IlvValue::operator=(f); return *this;
			}
    inline
    IlvDvValue& operator=(IlvBitmap* b)
			{
			    IlvValue::operator=(b); return *this;
			}
    inline
    IlvDvValue& operator=(IlvValueInterface* intf)
			{
			    IlvValue::operator=(intf); return *this;
			}
    inline
    IlvDvValue& operator=(const IlvPoint* point)
			{
			    IlvValue::operator=(point); return *this;
			}
    inline
    IlvDvValue& operator=(const IlvRect* rect)
			{
			    IlvValue::operator=(rect); return *this;
			}
};

// --------------------------------------------------------------------------
// IlvDvMember classes
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvMember
{
public:
    IlvDvMember(const IlSymbol* name) : _name(name) {}
    virtual ~IlvDvMember();

    virtual IlBoolean		isField() const;
    virtual IlBoolean		isMethod() const;
    virtual
    const IlvValueTypeClass*	getType() const;
    inline const char*		getName() const { return _name->name(); }
    inline const IlSymbol*	getNameSymbol() const { return _name; }

protected:
    const IlSymbol*		_name;
};

// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvFieldMember : public IlvDvMember
{
public:
    IlvDvFieldMember(const IlSymbol* name, const IlvValueTypeClass* type)
	: IlvDvMember(name),
	  _type(type) {}

    virtual IlBoolean		isField() const;
    inline
    const IlvValueTypeClass*	getType() const { return _type; }

protected:
    const IlvValueTypeClass*	_type;
};

// --------------------------------------------------------------------------
// IlvDvValueArray
class ILVDVCLASS IlvDvValueArray : public IlvArray
{
public:
    IlvDvValueArray(IlUInt initialLength = 8);
    IlvDvValueArray(const IlvDvValueArray&);
    ~IlvDvValueArray() { emptyValues(); }

    // ----------------------------------------------------------------------
    // Basic properties
    IlvDvValue*		getValue(IlUInt) const;
    void		addValue(const IlvDvValue&);
    void		emptyValues();
    void		copy(const IlvDvValueArray&);
};

// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvMethodMember : public IlvDvMember
{
public:
    IlvDvMethodMember(const IlSymbol* name,
		      const IlvValueTypeClass* returnedType,
		      const IlvDvValueArray& parameters)
	: IlvDvMember(name),
	  _type(returnedType),
	  _parameters(parameters) {}

    virtual IlBoolean		isMethod() const;

    inline
    const IlvValueTypeClass*	getType() const { return _type; }
    inline const
    IlvDvValueArray&		getParameters() const
				{
				    return _parameters;
				}

protected:
    const IlvValueTypeClass*	_type;
    IlvDvValueArray		_parameters;
};

// --------------------------------------------------------------------------
// ExportingAPIProc
// --------------------------------------------------------------------------
typedef union {
    struct {
	const IlSymbol*		_name;
	IlvDvValue*		_value;
    } _field;
    struct {
	const IlSymbol*		_name;
	IlvDvValue*		_returnedValue;
	IlvDvValueArray*	_paramValue;
    } _method;
    struct {
	IlvArray*		_members; // Array of IlvDvMembers
    } _apiDescription;
    struct {
	const IlSymbol*		_name;
	IlvDvMember*		_member;
    } _getMember;
    struct {
	const IlSymbol*		_name;
	IlvDvActionDescriptor*	_ui;
    } _commandUI;
} APIArgType;

// --------------------------------------------------------------------------
#define IlvDvBeginInterface(classname) \
IlBoolean classname::apiMethod(int action, APIArgType& arg) {

#define IlvDvEndInterface() \
if (action == ILVDV_GETTING_OBJ_API) \
    return IlTrue; \
return IlFalse; \
}

#define IlvDvEndInterface1(superclassname) \
    return superclassname::apiMethod(action, arg); \
}

// --------------------------------------------------------------------------
// Field macros
#define Field(externalName, fieldCodeName, fieldType) \
{ IlSymbol* symbol = IlGetSymbol(#externalName);     \
switch(action) { \
case ILVDV_SET_FIELD_VALUE: \
    if (arg._field._name == symbol) { \
	fieldCodeName = (fieldType)*arg._field._value; \
	return IlTrue; \
    } \
    break; \
case ILVDV_GET_FIELD_VALUE: \
    if (arg._field._name == symbol) { \
	*arg._field._value = (fieldType)fieldCodeName; \
	return IlTrue; \
    } \
    break; \
case ILVDV_GET_METHOD: \
    if (arg._getMember._name != symbol) \
	break; \
case ILVDV_GETTING_OBJ_API: \
    { \
	IlvDvValue fieldTypeValue((fieldType)fieldCodeName); \
	IlvDvFieldMember* field = \
		    new IlvDvFieldMember(symbol, \
					 fieldTypeValue.getType()); \
	if (action == ILVDV_GETTING_OBJ_API) {\
	    arg._apiDescription._members->add(field); \
	} else {\
	    arg._getMember._member = field; \
	    return IlTrue; \
	} \
    } \
    break; \
}}

// --------------------------------------------------------------------------
// _Method macros

#define _MethodSymbol(externalName, methodCodeName, callExp, returnedTypeInit, paramsInit) \
switch(action) { \
case ILVDV_CALL_METHOD: \
    if (arg._method._name == externalName) { \
	callExp; \
	return IlTrue; \
    } \
    break; \
case ILVDV_IS_PROCESSING_METHOD: \
    if (arg._method._name == externalName) { \
	return IlTrue; \
    } \
    break; \
case ILVDV_GET_METHOD: \
    if (arg._getMember._name != externalName) \
	break; \
case ILVDV_GETTING_OBJ_API: \
    { \
	IlvDvValue returnedValueType; \
	returnedTypeInit \
	IlvDvValueArray parameters; \
	paramsInit \
	IlvDvMethodMember* member = \
		    new IlvDvMethodMember(externalName, \
					  returnedValueType.getType(), \
					  parameters); \
	if (action == ILVDV_GETTING_OBJ_API) {\
	    arg._apiDescription._members->add(member); \
	} else {\
	    arg._getMember._member = member; \
	    return IlTrue; \
	} \
    } \
    break; \
}

#define _Method(externalName, methodCodeName, callExp, returnedTypeInit, paramsInit) \
{ IlSymbol* symbol = IlGetSymbol(#externalName); \
switch(action) { \
case ILVDV_CALL_METHOD: \
    if (arg._method._name == symbol) { \
	callExp; \
	return IlTrue; \
    } \
    break; \
case ILVDV_IS_PROCESSING_METHOD: \
    if (arg._method._name == symbol) { \
	return IlTrue; \
    } \
    break; \
case ILVDV_GET_METHOD: \
    if (arg._getMember._name != symbol) \
	break; \
case ILVDV_GETTING_OBJ_API: \
    { \
	IlvDvValue returnedValueType; \
	returnedTypeInit \
	IlvDvValueArray parameters; \
	paramsInit \
	IlvDvMethodMember* member = \
		    new IlvDvMethodMember(symbol, \
					  returnedValueType.getType(), \
					  parameters); \
	if (action == ILVDV_GETTING_OBJ_API) {\
	    arg._apiDescription._members->add(member); \
	} else {\
	    arg._getMember._member = member; \
	    return IlTrue; \
	} \
    } \
    break; \
}}

// --------------------------------------------------------------------------
// Method macros

#define Method(externalName, methodCodeName) \
_Method(externalName, methodCodeName, methodCodeName(), ;, ;) \

// --------------------------------------------------------------------------
// TypedMethod macro

#define TypedMethod(externalName, methodCodeName, returnedType) \
_Method(externalName, methodCodeName, \
    *(arg._method._returnedValue)= (returnedType)methodCodeName(), returnedValueType = (returnedType)0;, ;) \

// --------------------------------------------------------------------------
// Method1 macro

#define Method1(externalName, methodCodeName, param1Type, param1Name) \
_Method(externalName, methodCodeName, methodCodeName((param1Type)*arg._method._paramValue->getValue(0)), \
		      ;, IlvDvValue param1((param1Type)0, (const char*)#param1Name); \
			    parameters.addValue(param1);) \

// --------------------------------------------------------------------------
// TypedMethod1 macro

#define TypedMethod1(externalName, methodCodeName, param1Type, param1Name, returnedType) \
_Method(externalName, methodCodeName, \
    *(arg._method._returnedValue)= (returnedType)methodCodeName( \
	     (param1Type)*arg._method._paramValue->getValue(0)), \
    returnedValueType = (returnedType)0;, \
    IlvDvValue param1((param1Type)0, (const char*)#param1Name); \
    parameters.addValue(param1);)

// --------------------------------------------------------------------------
// Method2 macro

#define Method2(externalName, methodCodeName, param1Type, param1Name, param2Type, param2Name) \
_Method(externalName, methodCodeName, \
     methodCodeName((param1Type)*arg._method._paramValue->getValue(0),  \
      (param2Type)*arg._method._paramValue->getValue(1)),\
      ;, \
      IlvDvValue param1((param1Type)0, (const char*)#param1Name); \
      parameters.addValue(param1); \
      IlvDvValue param2((param2Type)0, (const char*)#param2Name); \
      parameters.addValue(param2);) \

// --------------------------------------------------------------------------
// TypedMethod1 macro

#define TypedMethod2(externalName, methodCodeName, param1Type, param1Name, param2Type, param2Name, returnedType) \
_Method(externalName, methodCodeName, \
    *(arg._method._returnedValue)= (returnedType)methodCodeName( \
	     (param1Type)*arg._method._paramValue->getValue(0), \
	      (param2Type)*arg._method._paramValue->getValue(1)),\
	      returnedValueType = (returnedType)0;, \
	      IlvDvValue param1((param1Type)0, (const char*)#param1Name); \
	      parameters.addValue(param1); \
	      IlvDvValue param2((param2Type)0, (const char*)#param2Name); \
	      parameters.addValue(param2);) \

// --------------------------------------------------------------------------
// Method3 macro

#define Method3(externalName, methodCodeName, param1Type, param1Name, param2Type, param2Name, param3Type, param3Name) \
_Method(externalName, methodCodeName, \
     methodCodeName((param1Type)*arg._method._paramValue->getValue(0),  \
      (param2Type)*arg._method._paramValue->getValue(1), \
      (param3Type)*arg._method._paramValue->getValue(2)),\
      ;, \
      IlvDvValue param1((param1Type)0, (const char*)#param1Name); \
      parameters.addValue(param1); \
      IlvDvValue param2((param2Type)0, (const char*)#param2Name); \
      parameters.addValue(param2); \
      IlvDvValue param3((param3Type)0, (const char*)#param3Name); \
      parameters.addValue(param3);) \

// --------------------------------------------------------------------------
// Method4 macro

#define Method4(externalName, methodCodeName, param1Type, param1Name, param2Type, param2Name, param3Type, param3Name, param4Type, param4Name) \
_Method(externalName, methodCodeName, \
     methodCodeName((param1Type)*arg._method._paramValue->getValue(0),  \
      (param2Type)*arg._method._paramValue->getValue(1), \
      (param3Type)*arg._method._paramValue->getValue(2), \
      (param4Type)*arg._method._paramValue->getValue(3)),\
      ;, \
      IlvDvValue param1((param1Type)0, (const char*)#param1Name); \
      parameters.addValue(param1); \
      IlvDvValue param2((param2Type)0, (const char*)#param2Name); \
      parameters.addValue(param2); \
      IlvDvValue param3((param3Type)0, (const char*)#param3Name); \
      parameters.addValue(param3); \
      IlvDvValue param4((param4Type)0, (const char*)#param4Name); \
      parameters.addValue(param4);) \

// --------------------------------------------------------------------------
#define Action(externalName, methodCodeName) \
    Method(externalName, methodCodeName)

#define UnprocessCommand(externalName) \
{ IlSymbol* symbol = IlGetSymbol(#externalName); \
switch(action) { \
case ILVDV_CALL_METHOD: \
    if (arg._method._name == symbol) { \
	return IlFalse; \
    } \
    break; \
case ILVDV_IS_PROCESSING_METHOD: \
    if (arg._method._name == symbol) { \
	return IlFalse; \
    } \
    break; \
case ILVDV_GET_METHOD: \
    if (arg._getMember._name == symbol) \
	return IlFalse; \
}}


// --------------------------------------------------------------------------
#define RefreshAction(externalName, methodCodeName) \
if((action == ILVDV_GET_METHOD_UI) && \
	    (arg._commandUI._name == IlGetSymbol(#externalName))) { \
    methodCodeName(arg._commandUI._ui); \
    return IlTrue; \
} \

// --------------------------------------------------------------------------
#define MethodTyped(externalName, methodCodeName, returnedType) \
{ IlSymbol* symbol = IlGetSymbol(#externalName); \
switch(action) { \
case ILVDV_CALL_METHOD: \
    if (arg._method._name == symbol) { \
	methodCodeName(); \
	return IlTrue; \
    } \
    break; \
case ILVDV_GETTING_OBJ_API: \
    { \
	IlvDvValue returnedValueType((returnedType)0); \
	IlvDvValueArray parameters; \
	arg._apiDescription._members->add( \
		    new IlvDvMethodMember(symbol, \
					  returnedValueType.getType(), \
					  parameters)); \
    } \
    break; \
case ILVDV_GET_METHOD: \
    if (arg._getMember._name == symbol) { \
	IlvDvValue returnedType; \
	IlvDvValueArray parameters; \
	arg._getMember._member = new IlvDvMethodMember(arg._method._name, \
						       returnedType.getType(), \
						       parameters); \
	return IlTrue; \
    } \
    break; \
}}

#define IlvDvDeclareInterface() \
public: \
    virtual IlBoolean apiMethod(int action, APIArgType& arg)

// --------------------------------------------------------------------------
// IlvDvInterface

class ILVDVCLASS IlvDvInterface
{
public:
    virtual IlBoolean	apiMethod(int action, APIArgType& arg) = 0;
    IlvDvMethodMember*	getMethodMember(const IlSymbol* name) const;
    IlBoolean		callMethod(const IlSymbol* methodName,
				   IlvDvValue* returnedValue,
				   ...);
    IlBoolean		vcallMethod(const IlSymbol* methodName,
				    IlvDvValue* returnedValue,
				    va_list);
    IlBoolean		callMethod(const IlSymbol* methodName,
				   const IlvDvValueArray& params,
				   IlvDvValue* returnedValue = 0);
    virtual IlBoolean	processAction(const IlSymbol* actionName);
    virtual IlBoolean	isProcessingAction(const IlSymbol* methodName) const;
    virtual IlBoolean	refreshAction(const IlSymbol* actionName,
				      IlvDvActionDescriptor* desc) const;
    void		getAPIInfos(IlvArray&) const;

    // Field methods
    IlvDvValue&		getFieldValue(const IlSymbol* fieldName,
				      IlvDvValue& value) const;
    void		setFieldValue(const IlSymbol* fieldName,
				      const IlvDvValue& value);

    // Get child interfaces
    virtual IlUInt	getChildInterfacesCount() const;
    virtual
    IlvDvInterface*	getChildInterface(IlUInt nInterface) const;
};

// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(interf);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Interf_H */
