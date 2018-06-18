// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/value.h
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
// Declaration of the IlvValueXXXTypeClass and IlvValue classes
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Value_H
#define __Ilv_Base_Value_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif

#if !defined(ILV_TM_PREF)
#  if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530)
// Borland C++ Builder 3.0 is STD and has a weird tm declaration
#    define ILV_TM_PREF IL_STDPREF
#  else
#    define ILV_TM_PREF
#  endif
#endif /* !ILV_TM_PREF */

// --------------------------------------------------------------------------
class IlvValue;
class IlvValueInterface;
class IlvPoint;
class IlvRect;
#if defined(sinix)
#include <time.h>
#else  /* !sinix */
struct ILV_TM_PREF tm;
#endif /* !sinix */

// defines for IlvValueTypeClass::getCapacities()
#define IlvValueSupportNothing          0
#define IlvValueSupportToString         1
#define IlvValueSupportFromString       2
#define IlvValueSupportCompare          4
#define IlvValueSupportFromAndToString  \
    (IlvValueSupportFromString|IlvValueSupportToString)

extern "C" {
    ILVDSPEXPORTEDFUNCTION(void) IL_MODTERM(arg)();
}

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueTypeClass
{
    friend ILVDSPEXPORTEDFUNCTION(void) IL_MODTERM(arg)();
public:
    virtual IlvValue*	createValue(const char* name = 0) const;
    virtual void	copy(IlvValue& dest, const IlvValue& src) const;
    virtual const char*	name() const;
    virtual const char*	toString(const IlvValue& value) const;
    virtual IlBoolean	fromString(IlvValue&   value,
				   const char* string,
				   IlAny       arg = 0) const;
    virtual void	deleteValue(IlvValue& value) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlUInt	getCapacities() const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
    static IlvValueTypeClass*	Get(const char* name);
    static IlvValueTypeClass**	GetAll(IlUInt& count);

protected:
    IlvValueTypeClass(const char* name = 0);
    virtual ~IlvValueTypeClass();
    const char*		_name;
public:
    static IlAList*	_allTypes;
    static void		Clean();
};


extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueNoType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueNullType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueAnyType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueIntType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueUIntType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueStringType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueBooleanType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueColorType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueFontType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValuePatternType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueColorPatternType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueGradientPatternType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueLineStyleType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueFillStyleType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueFillRuleType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueArcModeType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueAntialiasingModeType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueDirectionType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueBitmapType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueFloatType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueDoubleType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueTimeType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueStringArrayType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueUIntArrayType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueFloatArrayType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueInterfaceType;
extern ILVDSPEXPORTEDVAR(IlvValueTypeClass*) IlvValueMethodType;
extern ILVDSPEXPORTEDVAR(IlvValue) IlvValueNone;

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValue
{
public:
    virtual ~IlvValue();
    IlvValue(const char* name = 0)
	: _type(IlvValueNoType),
	  _name(name?IlGetSymbol(name):0)
    {
	_value.a = 0;
    }
    IlvValue(const char* name, IlAny a)
	: _type(IlvValueAnyType),
	  _name(IlGetSymbol(name))
    {
	_value.a = a;
    }
    IlvValue(IlSymbol* symb)
	: _type(IlvValueNoType),
	  _name(symb)
    {
	_value.a = 0;
    }
    IlvValue(const char* name, IlInt i)
	: _type(IlvValueIntType),
	  _name(IlGetSymbol(name))
    {
	_value.i = i;
    }
    IlvValue(const char* name, IlUInt u)
	: _type(IlvValueUIntType),
	  _name(IlGetSymbol(name))
    {
	_value.u = u;
    }
    IlvValue(const char* name, IlFloat f)
	: _type(IlvValueFloatType),
	  _name(IlGetSymbol(name))
    {
	_value.f = f;
    }
    IlvValue(const char* name, IlDouble d)
	: _type(IlvValueDoubleType),
	  _name(IlGetSymbol(name))
    {
	_value.d = d;
    }
    IlvValue(const char* name, const ILV_TM_PREF tm* time);
    IlvValue(const char* name, const char* s);
    IlvValue(const char* name, IlBoolean b)
	: _type(IlvValueBooleanType),
	  _name(IlGetSymbol(name))
    {
	_value.b = b;
    }
    IlvValue(const char* name, IlvColor* c)
	: _type(IlvValueColorType),
	  _name(IlGetSymbol(name))
    {
	_value.color = c;
	if (c)
	    c->lock();
    }
    IlvValue(const char* name, IlvFont* f)
	: _type(IlvValueFontType),
	  _name(IlGetSymbol(name))
    {
	_value.font = f;
	if (f)
	    f->lock();
    }
    IlvValue(const char* name, IlvPattern* p)
	: _type(IlvValuePatternType),
	  _name(IlGetSymbol(name))
    {
	_value.pattern = p;
	if (p)
	    p->lock();
    }
    IlvValue(const char* name, IlvColorPattern* p)
	: _type(IlvValueColorPatternType),
	  _name(IlGetSymbol(name))
    {
	_value.cpattern = p;
	if (p)
	    p->lock();
    }
    IlvValue(const char* name, IlvGradientPattern* p)
	: _type(IlvValueGradientPatternType),
	  _name(IlGetSymbol(name))
    {
	_value.gpattern = p;
	if (p)
	    p->lock();
    }
    IlvValue(const char* name, IlvLineStyle* l)
	: _type(IlvValueLineStyleType),
	  _name(IlGetSymbol(name))
    {
	_value.style = l;
	if (l)
	    l->lock();
    }
    IlvValue(const char* name, IlvFillStyle f)
	: _type(IlvValueFillStyleType),
	  _name(IlGetSymbol(name))
    {
	_value.fill_style = f;
    }
    IlvValue(const char* name, IlvFillRule f)
	: _type(IlvValueFillRuleType),
	  _name(IlGetSymbol(name))
    {
	_value.fill_rule = f;
    }
    IlvValue(const char* name, IlvArcMode f)
	: _type(IlvValueArcModeType),
	  _name(IlGetSymbol(name))
    {
	_value.arc_mode = f;
    }
    IlvValue(const char* name, IlvAntialiasingMode f)
	: _type(IlvValueAntialiasingModeType),
	  _name(IlGetSymbol(name))
    {
	_value.antialiasing_mode = f;
    }
    IlvValue(const char* name, IlvDirection d)
	: _type(IlvValueDirectionType),
	  _name(IlGetSymbol(name))
    {
	_value.direction = d;
    }
    IlvValue(const char* name, IlvBitmap* b)
	: _type(IlvValueBitmapType),
	  _name(IlGetSymbol(name))
    {
	_value.bitmap = b;
	if (b)
	    b->lock();
    }
    IlvValue(const char* name, IlvValueInterface* intf)
	: _type(IlvValueInterfaceType),
	  _name(IlGetSymbol(name))
    {
	_value.interf.interf = intf;
	_value.interf.clsinf = 0;
	if (intf)
	    intf->lock();
    }
    IlvValue(const char* name,
	     IlvValue*   value,
	     IlUShort    count,
	     IlUShort    needed = 65535);
    IlvValue(const IlvValue& source)
	: _type(IlvValueNoType),
	  _name(source._name)
    {
	_value.interf.interf = 0;
	_value.interf.clsinf = 0;
	if (source._type)
	    source._type->copy(*this, source);
	_type = source._type;
    }
    // ____________________________________________________________
    inline const IlvValueTypeClass* getType() const { return _type; }
    inline IlSymbol*		getName() const { return _name; }
    inline void			setName(IlSymbol* name) { _name = name; }
    inline void			setName(const char* name)
				{
				    _name = IlGetSymbol(name);
				}
    // Cast operators _____________________________________________
    inline operator		IlAny() const { return _value.a; }
    operator IlInt() const;
    operator IlUInt() const;
    operator IlFloat() const;
    operator IlDouble() const;
    operator ILV_TM_PREF tm*() const;
    operator const char*() const;
    operator IlBoolean() const;
    operator IlvFillStyle() const;
    operator IlvFillRule() const;
    operator IlvArcMode() const;
    operator IlvAntialiasingMode() const;
    operator IlvDirection() const;
    operator IlvValueInterface*() const;
    operator IlvPoint&() const;
    operator IlvRect&() const;
    operator IlvValue*() const;
    // Convertion that need a parameter
    IlvColor*		toIlvColor(IlvDisplay* display) const;
    IlvFont*		toIlvFont(IlvDisplay* display)  const;
    IlvPattern*		toIlvPattern(IlvDisplay* display) const;
    IlvColorPattern*	toIlvColorPattern(IlvDisplay* display)  const;
    IlvGradientPattern*	toIlvGradientPattern(IlvDisplay* display)  const;
    IlvLineStyle*	toIlvLineStyle(IlvDisplay* display)  const;
    IlvBitmap*		toIlvBitmap(IlvDisplay* display) const;
    // operators = ________________________________________________
    IlvValue& operator	=(const IlvValue& source);
    IlvValue& operator	=(IlAny a);
    IlvValue& operator	=(IlInt i);
    IlvValue& operator	=(IlUInt u);
    IlvValue& operator	=(IlFloat f);
    IlvValue& operator	=(IlDouble d);
    IlvValue& operator	=(const ILV_TM_PREF tm* time);
    IlvValue& operator	=(const char* s);
    IlvValue& operator	=(IlBoolean b);
    IlvValue& operator	=(IlvColor* c);
    IlvValue& operator	=(IlvFont* f);
    IlvValue& operator	=(IlvPattern* p);
    IlvValue& operator	=(IlvColorPattern* p);
    IlvValue& operator	=(IlvGradientPattern* p);
    IlvValue& operator	=(IlvLineStyle* l);
    IlvValue& operator	=(IlvFillStyle f);
    IlvValue& operator	=(IlvFillRule f);
    IlvValue& operator	=(IlvArcMode f);
    IlvValue& operator	=(IlvAntialiasingMode f);
    IlvValue& operator	=(IlvDirection f);
    IlvValue& operator	=(IlvBitmap* b);
    IlvValue& operator	=(IlvValueInterface* intf);
    IlvValue& operator	=(const IlvPoint* point);
    IlvValue& operator	=(const IlvRect* rect);

    void		empty();

    inline static
    const IlvValue*	Get(const char* name,
			    IlUShort        nValue,
			    const IlvValue* values)
			{
			    return Get(IlGetSymbol(name), nValue, values);
			}
    static
    const IlvValue*	Get(const IlSymbol* name,
			    IlUShort        nValue,
			    const IlvValue* values);

public:
    const IlvValueTypeClass* _type;
    IlSymbol*		     _name;
    union _IlvValueUnion {
	IlAny			a;
	IlInt			i;
	IlUInt			u;
	IlFloat			f;
	IlDouble		d;
	ILV_TM_PREF tm*		t;
	char*			s;
	IlBoolean		b;
	IlvColor*		color;
	IlvFont*		font;
	IlvPattern*		pattern;
	IlvColorPattern*	cpattern;
	IlvGradientPattern*	gpattern;
	IlvLineStyle*		style;
	IlvFillStyle		fill_style;
	IlvFillRule		fill_rule;
	IlvArcMode		arc_mode;
	IlvAntialiasingMode	antialiasing_mode;
	IlvDirection		direction;
	IlvBitmap*		bitmap;
	struct _IlvInterfaceStruct {
	    IlvValueInterface* interf;
	    IlvClassInfo*      clsinf;
	} interf;
	struct _IlvValuesStruct {
	    IlvValue* value;
	    IlUShort  count;
	    IlUShort  needed;
	} values;
    } _value;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueNoTypeClass : public IlvValueTypeClass
{
public:
    IlvValueNoTypeClass();
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueNullTypeClass : public IlvValueTypeClass
{
public:
    virtual const char*	toString(const IlvValue& val) const;
    static void		SetNull(IlvValue& value);

    IlvValueNullTypeClass();
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueAnyTypeClass : public IlvValueTypeClass
{
public:
    IlvValueAnyTypeClass();

    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueIntTypeClass : public IlvValueTypeClass
{
public:
    IlvValueIntTypeClass();

    virtual IlBoolean	isPersistent() const;
    virtual const char*	toString(const IlvValue&) const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueUIntTypeClass : public IlvValueTypeClass
{
public:
    IlvValueUIntTypeClass();

    virtual IlBoolean	isPersistent() const;
    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueStringTypeClass : public IlvValueTypeClass
{
public:
    IlvValueStringTypeClass();

    void		copy(IlvValue&, const IlvValue&) const;
    virtual IlBoolean	isPersistent() const;
    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual void	deleteValue(IlvValue& val) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueBooleanTypeClass : public IlvValueTypeClass
{
public:
    IlvValueBooleanTypeClass();

    virtual IlBoolean	isPersistent() const;
    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueResourceTypeClass : public IlvValueTypeClass
{
public:
    IlvValueResourceTypeClass(const char*);

    void		copy(IlvValue&, const IlvValue&) const;
    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual void	deleteValue(IlvValue& val) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueColorTypeClass : public IlvValueResourceTypeClass
{
public:
    IlvValueColorTypeClass();

    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueFontTypeClass : public IlvValueResourceTypeClass
{
public:
    IlvValueFontTypeClass();

    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValuePatternTypeClass
    : public IlvValueResourceTypeClass
{
public:
    IlvValuePatternTypeClass();

    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueColorPatternTypeClass
    : public IlvValueResourceTypeClass
{
public:
    IlvValueColorPatternTypeClass();

    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueGradientPatternTypeClass
    : public IlvValueResourceTypeClass
{
public:
    IlvValueGradientPatternTypeClass();

    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueLineStyleTypeClass
    : public IlvValueResourceTypeClass
{
public:
    IlvValueLineStyleTypeClass();

    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueFillStyleTypeClass : public IlvValueTypeClass
{
public:
    IlvValueFillStyleTypeClass();

    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlUInt	getCapacities() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueFillRuleTypeClass : public IlvValueTypeClass
{
public:
    IlvValueFillRuleTypeClass();

    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlUInt	getCapacities() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueArcModeTypeClass : public IlvValueTypeClass
{
public:
    IlvValueArcModeTypeClass();

    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlUInt	getCapacities() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueAntialiasingModeTypeClass
    : public IlvValueTypeClass
{
public:
    IlvValueAntialiasingModeTypeClass();

    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlUInt	getCapacities() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueDirectionTypeClass : public IlvValueTypeClass
{
public:
    IlvValueDirectionTypeClass();

    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlUInt	getCapacities() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueBitmapTypeClass : public IlvValueTypeClass
{
public:
    IlvValueBitmapTypeClass();

    void		copy(IlvValue&, const IlvValue&) const;
    virtual void	deleteValue(IlvValue& val) const;
    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueFloatTypeClass : public IlvValueTypeClass
{
public:
    IlvValueFloatTypeClass();

    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueDoubleTypeClass : public IlvValueTypeClass
{
public:
    IlvValueDoubleTypeClass();

    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueTimeTypeClass : public IlvValueTypeClass
{
public:
    IlvValueTimeTypeClass();

    virtual void	copy(IlvValue& dest, const IlvValue& src) const;
    virtual void	deleteValue(IlvValue& val) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueStringArrayValue
{
    friend class IlvValueStringArrayTypeClass;

    IlvValueStringArrayValue(IlUShort count, const char* const* labels);
    IlvValueStringArrayValue(const IlvValueStringArrayValue&);
    ~IlvValueStringArrayValue();

    char**		_array;
    IlUShort		_size;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueStringArrayTypeClass : public IlvValueTypeClass
{
public:
    IlvValueStringArrayTypeClass();

    void		copy(IlvValue&, const IlvValue&) const;
    virtual const char*	toString(const IlvValue& val) const;
    virtual void	deleteValue(IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
    static char**	StringArray(const IlvValue& val, IlUShort& count);
    static void		SetValue(IlvValue&, IlUShort, const char* const*);
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueUIntArrayValue
{
    friend class IlvValueUIntArrayTypeClass;

    IlvValueUIntArrayValue(IlUShort count, const IlUInt* values);
    IlvValueUIntArrayValue(const IlvValueUIntArrayValue&);
    ~IlvValueUIntArrayValue();

    IlUInt*		_array;
    IlUShort		_size;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueUIntArrayTypeClass : public IlvValueTypeClass
{
public:
    IlvValueUIntArrayTypeClass();

    void		copy(IlvValue&, const IlvValue&) const;
    virtual const char*	toString(const IlvValue& val) const;
    virtual void	deleteValue(IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
    static IlUInt*	UIntArray(const IlvValue& val, IlUShort& count);
    static void		SetValue(IlvValue&, IlUShort, const IlUInt*);
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueFloatArrayValue
{
    friend class IlvValueFloatArrayTypeClass;

    IlvValueFloatArrayValue(IlUShort count, const IlFloat* values);
    IlvValueFloatArrayValue(const IlvValueFloatArrayValue&);
    ~IlvValueFloatArrayValue();

    IlFloat*		_array;
    IlUShort		_size;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueFloatArrayTypeClass : public IlvValueTypeClass
{
public:
    IlvValueFloatArrayTypeClass();

    void		copy(IlvValue&, const IlvValue&) const;
    virtual const char*	toString(const IlvValue& val) const;
    virtual void	deleteValue(IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
    static IlFloat*	FloatArray(const IlvValue& val, IlUShort& count);
    static void		SetValues(IlvValue&, IlUShort, const IlFloat*);
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueInterfaceTypeClass : public IlvValueTypeClass
{
public:
    IlvValueInterfaceTypeClass();

    virtual const char*	toString(const IlvValue& val) const;
    virtual void	copy(IlvValue&, const IlvValue&) const;
    virtual void	deleteValue(IlvValue& val) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvValueMethodTypeClass : public IlvValueTypeClass
{
public:
    IlvValueMethodTypeClass();

    virtual void	copy(IlvValue&, const IlvValue&) const;
    virtual void	deleteValue(IlvValue& val) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

struct IlvEnumDescription
{
    int			_tag;
    const char*		_name;
};

#define IlvDeclBeginEnum(descname) static IlvEnumDescription descname[] = {
#define IlvDeclEnumItem(tag,val) { (int)tag, val }
#define IlvDeclEndEnum()  { 0, NULL } }

class ILVDSPEXPORTED IlvValueEnumTypeClass : public IlvValueTypeClass
{
public:
  virtual IlUInt	getCapacities() const;
  virtual const char*	toString(const IlvValue& val) const;
  virtual IlBoolean	fromString(IlvValue&   val,
				   const char* name,
				   IlAny       = 0) const;
  virtual IlBoolean	isPersistent() const;
  virtual IlInt		compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
  virtual IlBoolean	toInt(const IlvValue& val, IlInt& i) const;
  virtual IlBoolean	fromInt(IlvValue& val, IlInt anInt) const;

protected:
  IlStringHashTable	_nameToTag;
  IlHashTable		_tagToName;

  IlvValueEnumTypeClass(const char* name,IlvEnumDescription* descr);
  virtual ~IlvValueEnumTypeClass();
};

#define IlvDeclareEnumTypeClassEx(exporttag,name,descr) \
   class exporttag IlvValue##name##TypeClass \
     : public IlvValueEnumTypeClass { \
   public: \
    IlvValue##name##TypeClass () \
      : IlvValueEnumTypeClass(ILVSTRING(Ilv##name##Type), descr) \
       {} \
    virtual ~IlvValue##name##TypeClass() {} \
   }

#define IlvDeclareEnumTypeClass(exporttag,name) \
   class exporttag IlvValue##name##TypeClass \
     : public IlvValueEnumTypeClass { \
   public: \
    IlvValue##name##TypeClass (IlvEnumDescription* descr) \
      : IlvValueEnumTypeClass(ILVSTRING(Ilv##name##Type), descr) \
       {} \
    virtual ~IlvValue##name##TypeClass() {} \
   }

ILVDSPMODULEINIT(value);
#endif /* !__Ilv_Base_Value_H */
