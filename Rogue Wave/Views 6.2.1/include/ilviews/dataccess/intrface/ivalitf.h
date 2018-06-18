// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/intrface/ivalitf.h
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
// Declaration of the IlvValueIterface related utility classes
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Ivalitf_H
#define __Ili_Ivalitf_H

#if !defined(__Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Base_Script_H)
#  include <ilviews/base/script.h>
#endif
#if !defined(__Ili_Common_H)
#  include <ilviews/dataccess/common.h>
#endif
#if !defined(__Ili_Value_H)
#  include <ilviews/dataccess/value.h>
#endif

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliRefCountedValueInterface
: public IlvValueInterface
{
public:
    IliRefCountedValueInterface()
    {
	_refCount = 0;
    }

    virtual void lock();
    virtual void unLock();

    virtual const IlvValueTypeClass* getValueType(const IlvSymbol*) const;
    virtual IlBoolean getValueDescriptor(IlvValue&) const;

    ILI_MLK_DECL();
protected:
    IlUInt _refCount;

    virtual IlBoolean getValueValueDescriptor(IlvValue&) const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliClassItf
: public IliRefCountedValueInterface
{
public:
    IliClassItf(const char*);

    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    virtual IlBoolean describe(IlvValue&) const;
    virtual IlBoolean construct(const IlvValue&);
    virtual IlvValueInterface* newObject(const IlvValue&);

protected:
    IliString _scriptVarName;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvSafePointer;

class ILV_INF_EXPORTED IliJsUtil
{
public:
    static IlvDisplay* GetTheDisplay();
    static void Bind(IlvValueInterface*, const char*);

    static IlBoolean ILVCALLBACK
    MakeArgList(IlvValue&, IlInt, ...);

    static IlBoolean IsA(IlvValueInterface*, const IlvClassInfo*);
    static IlBoolean IsAFuncItf(IlvValueInterface*);
    static IlBoolean IsNumericType(const IlvValueTypeClass*);
    static IlvValue& GetArg(const IlvValue&, int);
    static IlBoolean GetIntArg(const IlvValue&, int, IlInt&);
    static IlBoolean GetDoubleArg(const IlvValue&, int, IlDouble&);
    static IlBoolean GetStringArg(const IlvValue&, int, const char*&);
    static IlvValueInterface*
			GetValueInterfaceArg(const IlvValue&, int,
					     const IlvClassInfo* = 0);
    static IlBoolean GetDatatypeArg(const IlvValue&, int,
				    const IliDatatype*&);

#if !(defined(__alpha) && !defined(WIN32))
    static IlBoolean SetRetVal(const IlvValue&, IlBoolean);
#else
    static IlBoolean SetRetVal(const IlvValue&, int);
#endif

    static IlBoolean SetIntRetVal(const IlvValue&, IlInt);
    static IlBoolean SetRetVal(const IlvValue&, IlDouble);
    static IlBoolean SetRetVal(const IlvValue&, const char*);
    static IlBoolean SetRetVal(const IlvValue&, IlvValueInterface*);
    static IlBoolean SetRetVal(const IlvValue&, IlvColor*);
    static IlBoolean SetRetVal(const IlvValue&, const IliValue&);
    static IlBoolean SetRetVal(const IlvValue&, const IlvValue&);
    static void SetBoolean(IlvValue&, IlBoolean b);
    static IlBoolean AsBoolean(const IlvValue&);
    static IlBoolean AllDigits(const char*);
};

#define IliITFDYNCAST(itf, cls)						\
    (IliJsUtil::IsA(itf, cls::ClassInfo()) ? (cls##Itf*)itf : (cls##Itf*)0)

const char* const IliNmReturn	 = "return";

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliValueVariantTypeClass
: public IlvValueTypeClass
{
public:
    IliValueVariantTypeClass();

    virtual void copy(IlvValue&, const IlvValue&) const;
    virtual void deleteValue(IlvValue&) const;

    virtual IlUInt getCapacities() const;
    virtual const char* toString(const IlvValue&) const;
    virtual IlBoolean fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlBoolean isPersistent() const;
    virtual IlInt compareValues(const IlvValue&, const IlvValue&) const;

private:
    IliString _buffer;
};

extern ILV_INF_EXPORTEDVAR(IliValueVariantTypeClass*) IliValueVariantType;

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliValueItf
: public IliRefCountedValueInterface
{
public:
    IliValueItf(const IliValue&);

    virtual IlBoolean getValueValueDescriptor(IlvValue&) const;
    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    IlvDeclarePropRootClassInfo();

    const IliValue& getValue() const;
    IliValue& getValue();

protected:
    IliValue _value;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDecimalItf
: public IliRefCountedValueInterface
{
public:
    IliDecimalItf(const IliDecimal&);

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    const IliDecimal& getDecimal() const;
    IliDecimal& getDecimal();

protected:
    IliDecimal _decimal;
    IliString _name;

    enum Op {
	Add,
	Substract,
	Multiply
    };
    IlBoolean binOp(const IlvValue&, Op) const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDataAccessItf
: public IliRefCountedValueInterface
{
public:
    IliDataAccessItf();

    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);
    virtual const char* getName() const;

    IlvDeclarePropRootClassInfo();

    typedef  void (*QuitCallback)(IlAny);
    static void SetQuitCallback(QuitCallback, IlAny userData = 0);

protected:
    static QuitCallback _OnQuit;
    static IlAny _OnQuitData;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliObserverItf
: public IliRefCountedValueInterface {
public:
    IliObserverItf(IlvValueInterface*);
    virtual ~IliObserverItf();

    virtual IlvValue& queryValue(IlvValue&) const;
    virtual IlBoolean applyValue(const IlvValue&);
    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    IlvDeclarePropRootClassInfo();

    inline IlvValueInterface* getFunction() const { return _funcItf; }

    IlBoolean callFunction(IlvValue&);
protected:
    IlvValueInterface*	_funcItf;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliObserverClassItf
: public IliClassItf
{
public:
    IliObserverClassItf();

    static void GetAccessors(const IlvSymbol* const**,
			     const IlvValueTypeClass* const**,
			     IlUInt&);

    virtual IlBoolean describe(IlvValue&) const;
    virtual IlvValueInterface* newObject(const IlvValue&);
    IlvDeclarePropRootClassInfo();
};

// --------------------------------------------------------------------------
#define IliDefineEnum(name, descr)			\
    IlvValue##name##TypeClass* IliValue##name##Type;	\
    IliModuleDEF(name,					\
		 IliValue##name##Type =			\
		 new IlvValue##name##TypeClass (descr); \
		 ,					\
		 delete IliValue##name##Type; )		\
    extern IlInt IliTrurlututu

// --------------------------------------------------------------------------
// Accessors macros
// --------------------------------------------------------------------------
#define IliScriptAccessor(cl, sym, typ, accs, typs, count)		\
    DeclareAccessor(cl##sym##LocalSymbol(), typ, accs, typs, count)

#define IliScriptEnumAccessor(accs, typs, count)			\
    DeclareAccessor(_enumMethodValue, IlvValueStringType, accs, typs, count)

#define IliScriptApply(cl, sym, res, var, exp)		\
    if (var.getName() == cl##sym##LocalSymbol()) {	\
	if (res) { exp; }				\
	return res;					\
    }

#define IliScriptQuery(cl, sym, res, var, exp)		\
    if (var.getName() == cl##sym##LocalSymbol()) {	\
	if (res) { exp; }				\
	return var;					\
    }

#define IliScriptParam(cl, sym, var, exp)			\
    if (var.getName() == cl##sym##LocalSymbol()) { exp; }

#define IliScriptIs(cl, sym, var) (var.getName() == cl##sym##LocalSymbol())

// --------------------------------------------------------------------------
IliModuleDECL_exp(ILV_INF_EXPORTED, IliIvalitfModule);

#endif /* !__Ili_Ivalitf_H */
