// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/intrface/value.h
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
// Declaration of the IlvValueInterface and IlvValueClassInfoInterface
// abstract classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Intrface_Value_H
#define __Ilv_Intrface_Value_H

class IlSymbol;
class IlvValue;
class IlvValueTypeClass;

#if !defined(__Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif

#define IlvValueNoError		0
#define IlvValueNotSupported	1
#define IlvValueReadOnly	2
#define IlvValueWriteOnly	3
#define IlvValueTypeMismatch	4
#define IlvValueBadValue	5
#define IlvValueArgsCountErr	6
#define IlvValueCannotCastType	7
#define IlvValueBadParamName	8
#define IlvValueInternalErr	9

class IlvAccessorsMap;
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueInterface
{
public:
    virtual ~IlvValueInterface();

    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual void	queryValues(IlvValue* values, IlUShort count) const;
    virtual IlBoolean	beforeChangeValues(const IlvValue* = 0, IlUShort = 0);
    virtual void	afterChangeValues(const IlvValue* = 0, IlUShort = 0);
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual IlBoolean	changeValues(const IlvValue*	values,
				     IlUShort		count = 0);
    virtual IlBoolean	applyValue(const IlvValue& value);
    virtual IlBoolean	checkValue(const IlvValue& value) const;
    virtual IlBoolean	callMethod(const IlSymbol*,
				   IlvValue& returned,
				   int nParams ...);
    virtual IlBoolean	callMethod(const IlSymbol*, IlvValue& returned);
    virtual IlBoolean	callMethod(const IlSymbol*,
				   IlvValue&		returned,
				   IlUInt		nParams,
				   const IlvValue*	params);
    virtual void	getAccessors(const IlSymbol* const** names,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;
    void		getClassAccessors(const IlSymbol* const**,
					  const IlvValueTypeClass* const**,
					  IlUInt&,
					  IlBoolean inherited = IlTrue) const;
    virtual const IlvValueTypeClass*	getValueType(const IlSymbol*) const;
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    virtual
    IlvClassInfo*	getClassInfo() const;
    static void		DeclareAccessor(const IlSymbol*,
					const IlvValueTypeClass*,
					const IlSymbol* const** accessors,
					const IlvValueTypeClass* const** types,
					IlUInt& count);
    virtual
    IlvAccessorsMap*	getAccessorsMap() const;

    // Error handling functions
    inline static IlInt	GetError()     { return _errorID; }
    inline static IlInt	GetErrorInfo() { return _errorInfo; }
    static void		SetError(IlInt errorID = 0,
				 IlInt errorInfo = 0);
    static IlBoolean	CheckValueContent(const IlvValue& value);
    static IlBoolean	CheckValueType(const IlvValue& value,
				       const IlvValue& type,
				       IlBoolean typeIsDefault = IlTrue);
    static IlBoolean	CheckArgContent(const IlvValue& value,
					const IlvValue& type,
					IlBoolean typeIsDefault = IlTrue);

    virtual void	lock();
    virtual void	unLock();
    virtual IlBoolean	isBeingDeleted() const;

    virtual const char*	getName() const;

    inline
    static IlSymbol*	GetConstructorSymbol() { return _constructorMethod; }
    inline
    static IlSymbol*	GetHeaderSymbol()  { return _headerValue; }
    inline
    static IlSymbol*	GetLibrarySymbol() { return _libraryValue; }

    static IlSymbol*	_classNameValue;
    static IlSymbol*	_nameValue;
    static IlSymbol*	_headerValue;
    static IlSymbol*	_libraryValue;
    static IlSymbol*	_constructorMethod;
    static IlSymbol*	_enumMethodValue;
    static IlSymbol*	_defaultMethodValue;
    static IlInt	_errorID;
    static IlInt	_errorInfo;

protected:
    IlBoolean		isValueTypeCached(const IlSymbol*) const;
    void		cacheValueType(const IlSymbol*,
				       const IlvValueTypeClass*) const;
};

// --------------------------------------------------------------------------
typedef void (* IlvGetAccessorsFunction)(const IlSymbol* const**,
					 const IlvValueTypeClass* const**,
					 IlUInt&);
typedef IlvValueInterface* (* IlvValueInterfaceConstructor)(IlUShort,
							    const IlvValue*);
IL_DEFINEFPTRTOANYCAST(IlvValueInterfaceConstructor);
#define IlvBeginDefineClassConstructor(className, nP, P)		\
static IlvValueInterface*						\
CConstr##className(IlUShort nP, const IlvValue* P)			\
{

#define IlvEndDefineClassConstructor(object, nP, P)			\
    if (object) {							\
	for (IlUShort _ilvloop = 0; _ilvloop < nP; ++_ilvloop) {	\
	    object->applyValue(P[_ilvloop]);				\
	}								\
    }									\
    return object;							\
}

#define IlvDefineClassConstructor(className, exp)			\
IlvBeginDefineClassConstructor(className, nP, P)			\
    className* o = exp;							\
IlvEndDefineClassConstructor(o, nP, P)

#define IlvDefineClassConstructorWithDisplay(className, exp)		\
IlvBeginDefineClassConstructor(className, nP, P)			\
    const IlvValue* _ilvV = IlvValue::Get("display", nP, P);		\
    IlvDisplay* display = _ilvV ? (IlvDisplay*)(IlAny)*_ilvV : 0;	\
    if (!display) {							\
	return 0;							\
    }									\
    className* o = exp;							\
IlvEndDefineClassConstructor(o, nP, P)

#define IlvRegisterClassConstructor(className)				\
IL_CAST(IlvValuedClassInfo*, className::ClassInfo())->addProperty(	\
	IlvValueInterface::_constructorMethod, (IlAny)			\
 IL_FPTRTOANYCAST(IlvValueInterfaceConstructor)(CConstr##className))

#define IlvRegisterClassCodeInformation(className, header, libs)	\
IL_CAST(IlvValuedClassInfo*, className::ClassInfo())->addProperty(	\
	IlvValueInterface::_libraryValue, (IlAny)libs);			\
IL_CAST(IlvValuedClassInfo*, className::ClassInfo())->addProperty(	\
	IlvValueInterface::_headerValue, (IlAny)header)

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValuedClassInfo
    : public IlvPropClassInfo
{
public:
    void	getClassAccessors(const IlSymbol* const** accessors,
				  const IlvValueTypeClass* const** types,
				  IlUInt& count,
				  IlBoolean expandBaseClasses) const;
    inline IlvGetAccessorsFunction	getGetAccessorsFunction() const
					{
					    return _getAccessors;
					}
    static IlvValuedClassInfo*	Create(const char*, IlvClassInfo**,
				       IlvGetAccessorsFunction);
    static IlvValueInterface*	Create(const char*    className,
				       IlUInt         nParams,
				       const IlvValue params[]);
    virtual const IlvValuedClassInfo*	getValued() const;
    IlvAccessorsMap*	getAccessorsMap() const;

protected:
    friend class IlvAccessorsMap;

    IlvValuedClassInfo(const char*	       className,
		       IlvClassInfo**	       superClass,
		       IlvGetAccessorsFunction getAccessors = 0)
	: IlvPropClassInfo(className, superClass),
	_getAccessors(getAccessors),
	_accessorsMapFactory(0)
	    {}

    IlvGetAccessorsFunction	_getAccessors;
    IlAny			_accessorsMapFactory;
    void			setAccessorsMap(IlAny);
};

// --------------------------------------------------------------------------
#define DeclareValueAccessors()						\
    virtual IlvValue& queryValue(IlvValue&) const;			\
    virtual IlBoolean applyValue(const IlvValue&);			\
    static void GetAccessors(const IlSymbol* const**,			\
			     const IlvValueTypeClass* const**,		\
			     IlUInt&)

// --------------------------------------------------------------------------
#define IlvMakeValueArray(method, argscount)				\
    method.empty();							\
    method._type = IlvValueMethodType;					\
    method._value.values.count = argscount;				\
    method._value.values.value = new IlvValue[argscount];

#define IlvFillValueForArg(method, n, argName, argVal)			\
    method._value.values.value[n] = argVal;				\
    method._value.values.value[n]._name = IlGetSymbol(argName);

#define IlvFillMethodValue(method, argcount, argneed)			\
    method._value.values.count = argcount;				\
    method._value.values.needed = argneed;

#define IlvSetArgClassInfo(count, classinfo)				\
    value._value.values.value[count]._value.interf.clsinf = classinfo;

// --------------------------------------------------------------------------
#define IlvMakeMethodValueForReturn(method, count, needed, retName, retVal) \
    IlvMakeValueArray(method, count)					\
    IlvFillValueForArg(method, 0, retName, retVal)			\
    IlvFillMethodValue(method, count, needed)

#define IlvMakeMethodValueFor1Arg(method, count, needed, retName, retVal) \
    IlvMakeMethodValueForReturn(method, count, needed, retName, retVal)

#define IlvMakeMethodValueFor2Args(method,   count, needed,		\
				   retName,  retVal,			\
				   argName1, argVal1)			\
    IlvMakeValueArray(method, count)					\
    IlvFillValueForArg(method, 0, retName,  retVal)			\
    IlvFillValueForArg(method, 1, argName1, argVal1)			\
    IlvFillMethodValue(method, count, needed)

#define IlvMakeMethodValueFor3Args(method,   count, needed,		\
				   retName,  retVal,			\
				   argName1, argVal1,			\
				   argName2, argVal2)			\
    IlvMakeValueArray(method, count)					\
    IlvFillValueForArg(method, 0, retName,  retVal)			\
    IlvFillValueForArg(method, 1, argName1, argVal1)			\
    IlvFillValueForArg(method, 2, argName2, argVal2)			\
    IlvFillMethodValue(method, count, needed)

#define IlvMakeMethodValueFor4Args(method,   count, needed,		\
				   retName,  retVal,			\
				   argName1, argVal1,			\
				   argName2, argVal2,			\
				   argName3, argVal3)			\
    IlvMakeValueArray(method, count)					\
    IlvFillValueForArg(method, 0, retName,  retVal)			\
    IlvFillValueForArg(method, 1, argName1, argVal1)			\
    IlvFillValueForArg(method, 2, argName2, argVal2)			\
    IlvFillValueForArg(method, 3, argName3, argVal3)			\
    IlvFillMethodValue(method, count, needed)

#define IlvMakeMethodValueFor5Args(method, count, needed,		\
				   retName,  retVal,			\
				   argName1, argVal1,			\
				   argName2, argVal2,			\
				   argName3, argVal3,			\
				   argName4, argVal4)			\
    IlvMakeValueArray(method, count)					\
    IlvFillValueForArg(method, 0, retName,  retVal)			\
    IlvFillValueForArg(method, 1, argName1, argVal1)			\
    IlvFillValueForArg(method, 2, argName2, argVal2)			\
    IlvFillValueForArg(method, 3, argName3, argVal3)			\
    IlvFillValueForArg(method, 4, argName4, argVal4)			\
    IlvFillMethodValue(method, count, needed)

#define IlvMakeMethodValueFor6Args(method, count, needed,		\
				   retName,  retVal,			\
				   argName1, argVal1,			\
				   argName2, argVal2,			\
				   argName3, argVal3,			\
				   argName4, argVal4,			\
				   argName5, argVal5)			\
    IlvMakeValueArray(method, count)					\
    IlvFillValueForArg(method, 0, retName,  retVal )			\
    IlvFillValueForArg(method, 1, argName1, argVal1)			\
    IlvFillValueForArg(method, 2, argName2, argVal2)			\
    IlvFillValueForArg(method, 3, argName3, argVal3)			\
    IlvFillValueForArg(method, 4, argName4, argVal4)			\
    IlvFillValueForArg(method, 5, argName5, argVal5)			\
    IlvFillMethodValue(method, count, needed)

// --------------------------------------------------------------------------
#define ILVMAKEMETHODVALUE0(method)					\
    IlvMakeMethodValueFor1Arg(method, 1, 1, "return", IlvValueNone)

#define ILVMAKEMETHODVALUE1(method, retName, retVal)			\
    IlvMakeMethodValueFor1Arg(method, 1, 1, retName, retVal)

#define ILVMAKEMETHODVALUE2(method,   needed,				\
			    retName,  retVal,				\
			    argName1, argVal1)				\
    IlvMakeMethodValueFor2Args(method, 2, needed,			\
			       retName,  retVal,			\
			       argName1, argVal1)

#define ILVMAKEMETHODVALUE3(method,   needed,				\
			    retName,  retVal,				\
			    argName1, argVal1,				\
			    argName2, argVal2)				\
    IlvMakeMethodValueFor3Args(method, 3, needed,			\
			       retName,  retVal,			\
			       argName1, argVal1,			\
			       argName2, argVal2)

#define ILVMAKEMETHODVALUE4(method,   needed,				\
			    retName,  retVal,				\
			    argName1, argVal1,				\
			    argName2, argVal2,				\
			    argName3, argVal3)				\
    IlvMakeMethodValueFor4Args(method, 4, needed,			\
			       retName,  retVal,			\
			       argName1, argVal1,			\
			       argName2, argVal2,			\
			       argName3, argVal3)

#define ILVMAKEMETHODVALUE5(method,   needed,				\
			    retName,  retVal,				\
			    argName1, argVal1,				\
			    argName2, argVal2,				\
			    argName3, argVal3,				\
			    argName4, argVal4)				\
    IlvMakeMethodValueFor5Args(method, 5, needed,			\
			       retName,  retVal,			\
			       argName1, argVal1,			\
			       argName2, argVal2,			\
			       argName3, argVal3,			\
			       argName4, argVal4)

#define ILVMAKEMETHODVALUE6(method,   needed,				\
			    retName,  retVal,				\
			    argName1, argVal1,				\
			    argName2, argVal2,				\
			    argName3, argVal3,				\
			    argName4, argVal4,				\
			    argName5, argVal5)				\
    IlvMakeMethodValueFor6Args(method, 6, needed,			\
			       retName,  retVal,			\
			       argName1, argVal1,			\
			       argName2, argVal2,			\
			       argName3, argVal3,			\
			       argName4, argVal4,			\
			       argName5, argVal5)

#define ILVSETARGCLASSINFO(method, index, classinfo)			\
    method._value.values.value[index]._value.interf.clsinf = classinfo;

ILVDSPMODULEINIT(b0valueitf);
#endif /* !__Ilv_Intrface_Value_H */
