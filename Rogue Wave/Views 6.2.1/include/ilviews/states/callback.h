// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/callback.h
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
// Declaration of States callback
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_States_Callback_H
#define __Ilv_States_Callback_H

#if !defined(__Ilv_States_Genctx_H)
#  include <ilviews/states/gencxt.h>
#endif
#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif
#include <ilviews/gadgets/amenu.h>
#include <ilviews/base/graphic.h>
#include <ilviews/base/view.h>

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvStateCallbackData
{
    IlvGraphicCallback _Callback;
    IlAny _ClientData;
public:
    IlvStateCallbackData(IlvGraphicCallback cb,
			 IlAny data = 0)
	: _Callback(cb),
	_ClientData(data) {}
    ILVSTATES_READWRITE(IlvGraphicCallback, Callback);
    ILVSTATES_READWRITE(IlAny, ClientData);
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvGraphicCallbackRequirementType
    : public IlvStateRequirement
{
protected:
    IlvGraphic*          _Object;
    IlvStateCallbackData _Stored;
    IlvStateCallbackData _Required;
public:
    IlvGraphicCallbackRequirementType(IlvGraphic* obj,
				      IlvStateCallbackData cbd)
	: IlvStateRequirement(),
	_Object(obj),
	_Stored(0),
	_Required(cbd)
    {}
    void copyStoredFrom(IlvStateRequirement* from)
    {
	_Stored = ((IlvGraphicCallbackRequirementType*)from)->_Stored;
    }
    void copyRequiredFrom(IlvStateRequirement* from)
    {
	_Stored = ((IlvGraphicCallbackRequirementType*)from)->_Required;
    }
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvMenuItemCallbackRequirementType
    : public IlvStateRequirement
{
protected:
    IlvMenuItem*	 _Object;
    IlvStateCallbackData _Stored;
    IlvStateCallbackData _Required;
public:
    IlvMenuItemCallbackRequirementType(IlvMenuItem*	    obj,
				       IlvStateCallbackData cbd)
	: IlvStateRequirement(),
	_Object(obj),
	_Stored(0),
	_Required(cbd)
    {}
    void copyStoredFrom(IlvStateRequirement* from)
    {
	_Stored = ((IlvMenuItemCallbackRequirementType*)from)->_Stored;
    }
    void copyRequiredFrom(IlvStateRequirement* from)
    {
	_Stored = ((IlvMenuItemCallbackRequirementType*)from)->_Required;
    }
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvViewInputCallbackRequirementType
    : public IlvStateRequirement
{
protected:
    IlvView*          _Object;
    IlvInputCallback _Stored;
    IlvInputCallback _Required;
public:
    IlvViewInputCallbackRequirementType(IlvView* obj,
					IlvInputCallback cbd)
	: IlvStateRequirement(),
        _Object(obj),
        _Stored(0),
        _Required(cbd)
    {}
    void copyStoredFrom(IlvStateRequirement* from)
    {
        _Stored = ((IlvViewInputCallbackRequirementType*)from)->_Stored;
    }
    void copyRequiredFrom(IlvStateRequirement* from)
    {
        _Stored = ((IlvViewInputCallbackRequirementType*)from)->_Required;
    }
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvViewExposeCallbackRequirementType
    : public IlvStateRequirement
{
protected:
    IlvView*          _Object;
    IlvExposeCallback _Stored;
    IlvExposeCallback _Required;
public:
    IlvViewExposeCallbackRequirementType(IlvView* obj,
					 IlvExposeCallback cbd)
	: IlvStateRequirement(),
	_Object(obj),
	_Stored(0),
	_Required(cbd)
    {}
    void copyStoredFrom(IlvStateRequirement* from)
    {
	_Stored = ((IlvViewExposeCallbackRequirementType*)from)->_Stored;
    }
    void copyRequiredFrom(IlvStateRequirement* from)
    {
	_Stored = ((IlvViewExposeCallbackRequirementType*)from)->_Required;
    }
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvViewResizeCallbackRequirementType
    : public IlvStateRequirement
{
protected:
    IlvView*          _Object;
    IlvResizeCallback _Stored;
    IlvResizeCallback _Required;
public:
    IlvViewResizeCallbackRequirementType(IlvView* obj,
					 IlvResizeCallback cbd)
	: IlvStateRequirement(),
	_Object(obj),
	_Stored(0),
	_Required(cbd)
    {}
    void copyStoredFrom(IlvStateRequirement* from)
    {
	_Stored = ((IlvViewResizeCallbackRequirementType*)from)->_Stored;
    }
    void copyRequiredFrom(IlvStateRequirement* from)
    {
	_Stored = ((IlvViewResizeCallbackRequirementType*)from)->_Required;
    }
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvViewDestroyCallbackRequirementType
    : public IlvStateRequirement
{
 protected:
    IlvView*	       _Object;
    IlvDestroyCallback _Stored;
    IlvDestroyCallback _Required;
 public:
    IlvViewDestroyCallbackRequirementType(IlvView* obj,
					  IlvDestroyCallback cbd)
	: IlvStateRequirement(),
	_Object(obj),
	_Stored(0),
	_Required(cbd)
    {}
    void copyStoredFrom(IlvStateRequirement* from)
    {
	_Stored = ((IlvViewDestroyCallbackRequirementType*)from)->_Stored;
    }
    void copyRequiredFrom(IlvStateRequirement* from)
    {
	_Stored = ((IlvViewDestroyCallbackRequirementType*)from)->_Required;
    }
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvGraphicCallbackRequirement
    : public IlvGraphicCallbackRequirementType
{
public:
    ILVSTATES_TYPE_INFO;
    // constructors
    IlvGraphicCallbackRequirement(IlvGraphic* g,
				  IlvStateCallbackData cbd)
	: IlvGraphicCallbackRequirementType(g, cbd)
    {
	assert(g != 0);
    }
    // accessors
    IlvGraphic* getGraphic() { return _Object; }
    //protocol
    IlInt getInt() {
	assert (getGraphic() != 0);
	return IlCastIlAnyToIlInt(getGraphic()) >> 3;
    }
    IlInt isDifferentOf(IlvStateRequirement* s) {
	assert(s != 0);
	assert(getType() == s->getType());
	IlvGraphicCallbackRequirement* s2 = (IlvGraphicCallbackRequirement*)s;
	return getGraphic() != s2->getGraphic();
    }
    void apply()
    {
	getGraphic()->setCallback(_Required.getCallback());
	getGraphic()->setClientData(_Required.getClientData());
    }
    void restore()
    {
	getGraphic()->setCallback(_Stored.getCallback());
	getGraphic()->setClientData(_Stored.getClientData());
    }
    void storeObjectData()
    {
	_Stored.setCallback(getGraphic()->getCallback());
	_Stored.setClientData(getGraphic()->getClientData());
    }
};

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvMenuItemCallbackRequirement
    : public IlvMenuItemCallbackRequirementType
{
public:
    ILVSTATES_TYPE_INFO;
    // constructors
    IlvMenuItemCallbackRequirement(IlvMenuItem* g,
				   IlvStateCallbackData cbd)
	: IlvMenuItemCallbackRequirementType(g, cbd)
    {
	assert(g != 0);
    }
    // accessors
    IlvMenuItem* getMenuItem() { return _Object; }
    //protocol
    IlInt getInt() {
	assert(getMenuItem() != 0);
	return IlCastIlAnyToIlInt(getMenuItem()) >> 3;
    }
    IlInt isDifferentOf(IlvStateRequirement* s)
    {
	assert(s != 0);
	assert(getType() == s->getType());
	IlvMenuItemCallbackRequirement* s2 = (IlvMenuItemCallbackRequirement*)s;
	return getMenuItem() != s2->getMenuItem();
    }
    void apply()
    {
	getMenuItem()->setCallback(_Required.getCallback());
	getMenuItem()->setClientData(_Required.getClientData());
    }
    void restore()
    {
	getMenuItem()->setCallback(_Stored.getCallback());
	getMenuItem()->setClientData(_Stored.getClientData());
    }
    void storeObjectData()
    {
	_Stored.setCallback(getMenuItem()->getCallback());
	_Stored.setClientData(getMenuItem()->getClientData());
    }
};

// callback name table functions
ILVSTATESEXPORTEDFUNCTION(void) IlvSiRegisterCallback(char*, IlvGraphicCallback);
ILVSTATESEXPORTEDFUNCTION(IlvGraphicCallback) IlvSiGetCallback(char*);
ILVSTATESEXPORTEDFUNCTION(IlBoolean) IlvSiHasCallback (char*);
ILVSTATESEXPORTEDFUNCTION(IlvGraphicCallback) IlvSiGetCallback();
ILVSTATESEXPORTEDFUNCTION(IlvSuKeyTable*) IlvSiGetCallbackTranslationTable();

ILVSTATESMODULEINIT(statecb);

#endif /* !__Ilv_States_Callback_H */
