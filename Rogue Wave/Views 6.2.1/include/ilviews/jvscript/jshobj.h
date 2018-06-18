// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/jvscript/jshobj.h
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
// Declaration of the IlvJSHObject class
// Defined in library ilvjs
// --------------------------------------------------------------------------
#ifndef __Ilv_JSHobj_H
#define __Ilv_JSHobj_H

#include <ilviews/base/value.h>
#include <iljscript/hvalue.h>
#include <ilviews/base/safeptr.h>

// --------------------------------------------------------------------------
enum IlvJSHViewsTypes {
    ILV_TYPE_VALUE_INTERFACE = (int)ILJ_USER_VIEWS,
    ILV_TYPE_VALUE_METHOD
};

// --------------------------------------------------------------------------
class IlvJSHObject: public IljHValue
{
public:
    IlvJSHObject(IlvSafePointer* safePointer);
    ~IlvJSHObject();

    IljStatus		getNamedProperty(const IljHSymbolPtr& name,
					 IljHValuePtr& res);
    IljStatus		setNamedProperty(const IljHSymbolPtr& name,
					 const IljHValuePtr& val);
    IljStatus		putNamedProperty(const IljHSymbolPtr& name,
					 const IljHValuePtr& val);
    IljStatus		deleteNamedProperty(const IljHSymbolPtr& name);
    IljStatus		getPropIterator(IljHPropIteratorPtr& res);
    IlvSafePointer*	getSafePointer() const {return _safePointer;}
    IlBoolean		isSafe() const;

    virtual IljStatus	funcall(const IljHValuePtr& that,
				int nargs,
				const IljHValuePtr* args,
				IljHValuePtr& res);
    virtual IljStatus	construct(int nargs,
				  const IljHValuePtr* args,
				  IljHValuePtr& res);
    virtual IljStatus	applyOpEq(const IljHValuePtr& arg,
				  IljBoolean isRight,
				  IljHValuePtr& res);
    virtual IljBoolean	equals(const IljHValuePtr& value);

    IljStatus		toStringDefault(IljHStringPtr& res);
    virtual void	getTypeOf(IljHStringPtr& res);
    virtual int		getType();
    IljStatus		invokeMethod(IlSymbol* method,
				     int nargs,
				     const IljHValuePtr* args,
				     IljHValuePtr& res);

    static IljHValuePtr	GetJSHObjectOf(IlvValueInterface* intf);
    static IljStatus	OnRuntimeError(IlInt errorID,
				       IlInt errInfo = 0,
				       const char* errMsg = 0);
	   IljStatus	onError(IlInt errorID,
				IlInt errInfo = 0,
				const char* errMsg = 0);

protected:
    IlvValue&		queryValue(IlvValue& value) const;
    IlBoolean		changeValue(const IlvValue& value);
    const IlvValueTypeClass* getValueType(const IlSymbol* valueName) const;
    IlBoolean		getValueDescriptor(IlvValue& value) const;

    IlSymbol*		getDefaultMethod() const;
    IlSymbol*		getEnumMethod() const;
    IljStatus		onHelp(IljHValuePtr& res) const;
    IljStatus		noViewsObjectError() const;
    IljStatus		noApplicablePropertyError() const;

private:
    IlvSafePointer*	_safePointer;
};

// --------------------------------------------------------------------------
class IlvJSHMethod: public IljHPrimitive
{
    const IljHValuePtr& getPrototypeU();

public:
    IlvJSHMethod(IlvJSHObject* jshObj, const IlvValue& value);

    virtual IljStatus	getNamedProperty(const IljHSymbolPtr& name,
					 IljHValuePtr& res);
    IljStatus		funcall(const IljHValuePtr& that,
				int nargs,
				const IljHValuePtr* args,
			    IljHValuePtr& res);
    virtual void	getTypeOf(IljHStringPtr& res);
    virtual int		getType();
    IljStatus		toStringDefault(IljHStringPtr& res);

protected:
    IljStatus		onHelp(IljHValuePtr& res) const;

    IlvJSHObject*	_jshObj;
    IlvValue		_value;
};

#endif /* !__Ilv_JSHobj_H */
