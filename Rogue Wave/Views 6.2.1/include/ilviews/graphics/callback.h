// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/callback.h
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
// Declaration of the IlvGraphicCallbackStruct and subclasses
// Defined in library views
// --------------------------------------------------------------------------

#ifndef __Ilv_Graphics_Callback_H
#define __Ilv_Graphics_Callback_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif

class IlvGraphicHolder;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGraphicCallbackStruct
{
public:
    IlvGraphicCallbackStruct()
    : _hasData(IlFalse),
      _data(0)
    {}
    IlvGraphicCallbackStruct(IlAny v)
    : _hasData(IlTrue),
      _data(v)
    {}
    virtual ~IlvGraphicCallbackStruct();
    // ____________________________________________________________
    IlBoolean			isSame(const IlvGraphicCallbackStruct&) const;
    virtual IlBoolean		isPersistent() const;
    virtual void		write(IlvOutputFile&) const;
    virtual void		call(IlvGraphic*,
				     const IlvGraphicHolder*) const = 0;
    inline IlAny		getData(IlvGraphic* object) const
				{
				    return hasData()
					? (IlAny)_data
					: object->getClientData();
				}
    inline IlBoolean		hasData() const { return _hasData; }
    inline IlAny		getData() const { return _data; }
    inline void			setData(IlAny v) 
				{
				    _data = v;
				    _hasData = IlTrue;
				}
    inline void			unsetData() { _hasData = IlFalse; }
    virtual IlSymbol*		getCallbackName() const;
    virtual IlvGraphicCallback	getCallback()     const;
    virtual const IlvValue*	getValue()        const;
    virtual void		setValue(const IlvValue&) = 0;
    virtual const IlSymbol*	getLanguage() const;
    virtual void		setLanguage(const IlSymbol*);

private:
    IlBoolean			_hasData;
    IlAny			_data;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvNamedGraphicCallbackStruct
: public IlvGraphicCallbackStruct
{
public:
    IlvNamedGraphicCallbackStruct(const IlSymbol* name,
				  const IlSymbol* script = 0)
    : IlvGraphicCallbackStruct(),
      _name(name),
      _value(),
      _script(script)
    {}
    IlvNamedGraphicCallbackStruct(const IlSymbol* name,
				  IlAny d,
				  const IlSymbol* script = 0)
    : IlvGraphicCallbackStruct(d),
      _name(name),
      _value(),
      _script(script)
    {}
    IlvNamedGraphicCallbackStruct(const IlSymbol* name,
				  const IlvValue& v,
				  const IlSymbol* script = 0)
    : IlvGraphicCallbackStruct(),
      _name(name),
      _value(v),
      _script(script)
    {}
    IlvNamedGraphicCallbackStruct(const IlSymbol* name,
				  const IlvValue& v,
				  IlAny d,
				  const IlSymbol* script = 0)
    : IlvGraphicCallbackStruct(d),
      _name(name),
      _value(v),
      _script(script)
    {}
    // ____________________________________________________________
    inline IlSymbol*		getCallbackName() const
				{
				    return (IlSymbol*)_name;
				}
    virtual void		call(IlvGraphic*,
				     const IlvGraphicHolder*) const;
    virtual const IlvValue*	getValue() const;
    IlBoolean			isPersistent() const;
    void			write(IlvOutputFile&) const;
    virtual void		setValue(const IlvValue&);
    virtual const IlSymbol*	getLanguage() const;
    virtual void		setLanguage(const IlSymbol* script);

private:
    const IlSymbol*		_name;
    IlvValue			_value;
    const IlSymbol*		_script;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvUnnamedGraphicCallbackStruct
: public IlvGraphicCallbackStruct
{
public:
    IlvUnnamedGraphicCallbackStruct(IlvGraphicCallback callback)
    : IlvGraphicCallbackStruct(), _callback(callback), _value() {}
    IlvUnnamedGraphicCallbackStruct(IlvGraphicCallback callback,
				    IlAny d)
    : IlvGraphicCallbackStruct(d), _callback(callback), _value() {}
    IlvUnnamedGraphicCallbackStruct(IlvGraphicCallback callback,
				    const IlvValue& v)
    : IlvGraphicCallbackStruct(), _callback(callback), _value(v) {}
    IlvUnnamedGraphicCallbackStruct(IlvGraphicCallback callback,
				    const IlvValue& v,
				    IlAny d)
    : IlvGraphicCallbackStruct(d), _callback(callback), _value(v) {}
    // ____________________________________________________________
    inline IlvGraphicCallback	getCallback() const { return _callback; }
    virtual void		call(IlvGraphic*,
				     const IlvGraphicHolder*) const;
    virtual const IlvValue*	getValue() const;
    virtual void		setValue(const IlvValue&);

private:
    IlvGraphicCallback		_callback;
    IlvValue			_value;
};

#endif /* !__Ilv_Graphics_Callback_H */
