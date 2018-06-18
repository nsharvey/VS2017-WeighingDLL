// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/attribut.h
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
// Declaration of the IlvGraphicAttribute class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Attribut_H
#define __Ilv31_Attribut_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv31_Ilvvar_H)
#include <ilviews/ilvvar.h>
#endif

// --------------------------------------------------------------------------
typedef enum IlvAttributeValueType
{
    IlvNoValue, IlvAnyValue,
    IlvIntValue, IlvUIntValue, IlvBooleanValue, IlvFloatValue,
    IlvStringValue, IlvColorValue,
    IlvPatternValue, IlvLineStyleValue,
    IlvFillStyleValue, IlvDirectionValue,
    IlvBitmapValue
} _IlvAttributeValueType;

class IlvGraphicAttribute;

ILV31VAREXPORTEDFUNCTION(void)
IlvRemoveAttribute(IlvGraphic* graphic, IlvGraphicAttribute* attribut);
ILV31VAREXPORTEDFUNCTION(void)
IlvAddAttribute(IlvGraphic* graphic, IlvGraphicAttribute* attribut);
ILV31VAREXPORTEDFUNCTION(IlvGraphicAttribute*)
IlvGetAttribute(IlvGraphic* graphic, const char* classname);
ILV31VAREXPORTEDFUNCTION(void)
IlvApplyAttributes(IlvGraphic* graphic, IlvApplyAttribute f, IlAny arg=0);

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvAttributeValue
{
public:
    IlvAttributeValueType _type;
    union _IlvAttributeValueUnion {
	IlAny        a;
	IlInt        i;
	IlUInt       u;
	IlFloat      f;
	const char*   s;
	IlBoolean    b;
	IlvColor*     color;
	IlvPattern*   pattern;
	IlvLineStyle* style;
	IlvFillStyle  fill_style;
	IlvDirection  direction;
	IlvBitmap*    bitmap;
    } _value;
public:
    IlvAttributeValue()
    :_type(IlvNoValue)        { _value.a = 0;          }
    IlvAttributeValue(IlAny a)
    :_type(IlvAnyValue)       { _value.a          = a; }
    IlvAttributeValue(IlInt i)
    :_type(IlvIntValue)       { _value.i          = i; }
    IlvAttributeValue(IlUInt u)
    :_type(IlvUIntValue)      { _value.u          = u; }
    IlvAttributeValue(IlFloat f)
    :_type(IlvFloatValue)     { _value.f          = f; }
    IlvAttributeValue(const char* s)
    :_type(IlvStringValue)    { _value.s          = s; }
    IlvAttributeValue(IlBoolean b)
    : _type(IlvBooleanValue)  { _value.b          = b; }
    IlvAttributeValue(IlvColor* c)
    :_type(IlvColorValue)     { _value.color      = c; }
    IlvAttributeValue(IlvPattern* p)
    :_type(IlvPatternValue)   { _value.pattern    = p; }
    IlvAttributeValue(IlvLineStyle* l)
    :_type(IlvLineStyleValue) { _value.style      = l; }
    IlvAttributeValue(IlvFillStyle  f)
    :_type(IlvFillStyleValue) { _value.fill_style = f; }
    IlvAttributeValue(IlvDirection  d)
    :_type(IlvDirectionValue) { _value.direction  = d; }
    IlvAttributeValue(IlvBitmap* b)
    :_type(IlvBitmapValue)    { _value.bitmap     = b; }
#if defined(__GNUC__)
    IlvAttributeValue(const IlvAttributeValue& a)
	{ _type = a._type; _value = a._value; }
#endif /* __GNUC__ */
    // ____________________________________________________________
    IlvAttributeValueType getValueType() const { return _type; }
    // Cast operators _____________________________________________
    operator IlAny()        const { return _value.a;          }
    operator IlInt()        const { return _value.i;          }
    operator IlUInt()       const { return _value.u;          }
    operator IlFloat()      const { return _value.f;          }
    operator const char*()   const { return _value.s;          }
    operator IlBoolean()    const { return _value.b;          }
    operator IlvColor*()     const { return _value.color;      }
    operator IlvPattern*()   const { return _value.pattern;    }
    operator IlvLineStyle*() const { return _value.style;      }
    operator IlvFillStyle()  const { return _value.fill_style; }
    operator IlvDirection()  const { return _value.direction;  }
    operator IlvBitmap*()    const { return _value.bitmap;     }
    // operators = ________________________________________________
    IlvAttributeValue& operator=(IlAny a) {
	_type = IlvAnyValue;       _value.a          = a; return *this; }
    IlvAttributeValue& operator=(IlInt i) {
	_type = IlvIntValue;       _value.i          = i; return *this; }
    IlvAttributeValue& operator=(IlUInt u) {
	_type = IlvUIntValue;      _value.u          = u; return *this; }
    IlvAttributeValue& operator=(IlFloat f) {
	_type = IlvFloatValue;     _value.f          = f; return *this; }
    IlvAttributeValue& operator=(const char* s) {
	_type = IlvStringValue;    _value.s          = s; return *this; }
    IlvAttributeValue& operator=(IlBoolean b) {
	_type = IlvBooleanValue;   _value.b          = b; return *this; }
    IlvAttributeValue& operator=(IlvColor* c) {
	_type = IlvColorValue;     _value.color      = c; return *this; }
    IlvAttributeValue& operator=(IlvPattern* p) {
	_type = IlvPatternValue;   _value.pattern    = p; return *this; }
    IlvAttributeValue& operator=(IlvLineStyle* l) {
	_type = IlvLineStyleValue; _value.style      = l; return *this; }
    IlvAttributeValue& operator=(IlvFillStyle f) {
	_type = IlvFillStyleValue; _value.fill_style = f; return *this; }
    IlvAttributeValue& operator=(IlvDirection f) {
	_type = IlvDirectionValue; _value.direction  = f; return *this; }
    IlvAttributeValue& operator=(IlvBitmap* b) {
	_type = IlvBitmapValue;    _value.bitmap     = b; return *this; }
};

#if !defined(__Ilv31_Attrmac_H)
#include <ilviews/attrmac.h>
#endif

ILV31VAREXPORTEDFUNCTION(IlvGraphicAttribute*)
IlvReadAttribute(ILVSTDPREF istream&, IlvContainer*, IlvGraphic*, const char*);
ILV31VAREXPORTEDFUNCTION(IlvGraphicAttribute*)
IlvReadAttribute(ILVSTDPREF istream&, IlvManager*, IlvGraphic*, const char*);
ILV31VAREXPORTEDFUNCTION(IlvGraphicAttribute*)
IlvCreateAttribute(const char*, IlvContainer*, IlvGraphic*, const char* = 0);
ILV31VAREXPORTEDFUNCTION(IlvGraphicAttribute*)
IlvCreateAttribute(const char*, IlvManager*, IlvGraphic*, const char* = 0);

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvGraphicAttribute
: public IlvAttribute {
protected:
    union {
	IlvContainer* container;
	IlvManager*   manager;
    } _usedContainer;
    IlBoolean  _usingContainer; // if False, IlvManager
    IlvGraphic* _graphic;
public:
    IlvGraphicAttribute(IlvContainer*, IlvGraphic* obj = 0,
			const char* name = 0);
    IlvGraphicAttribute(IlvManager*,   IlvGraphic* obj = 0,
			const char* name = 0);
    virtual ~IlvGraphicAttribute();
    // ____________________________________________________________
    IlvContainer* getContainer() const  { return _usedContainer.container; }
    IlvManager*   getManager()   const  { return _usedContainer.manager;   }
    IlBoolean isUsingContainer() const { return _usingContainer; }
    // ____________________________________________________________
    IlvGraphic* getGraphic() const { return _graphic; }
    void        attach(IlvGraphic* graphic) { _graphic=graphic; }
    IlvDisplay* getDisplay() const {
	if (_usingContainer) return getContainer()->getDisplay();
	else                 return getManager()->getDisplay();
    }
    // Set and get value __________________________________________
    virtual void  set(const IlvAttributeValue&, IlBoolean redraw = IlTrue);
    virtual void  apply(const IlvAttributeValue&)=0;
    virtual const IlvAttributeValue& get() const =0;
    inline IlvGraphicAttribute& operator=(const IlvAttributeValue& value)
	{
	    set(value);
	    return *this;
	}
    operator const IlvAttributeValue&() const { return get(); }

    virtual const char* convertToString();
    virtual void setStringValue(const char*, IlBoolean redraw = IlTrue);
    virtual const char* getStringType();

    virtual void read(ILVSTDPREF istream&);
    virtual void write(ILVSTDPREF ostream&) const;
    virtual IlvGraphicAttributeClassInfo* getClassInfo() const = 0;
    const char* className() const { return getClassInfo()->getClassName(); }
#if defined(__GNUC__)
    IlvAttributeValueType getType()
	{
	    return get().getValueType();
	}
#else  /* !__GNUC__ */
    IlvAttributeValueType getType()
	{
	    IlvAttributeValue value = get();
	    return value.getValueType();
	}
#endif /* !__GNUC__ */
    virtual void notifySet(const IlvvFundamental &value);
    virtual void notifyUndefined();
    virtual IlBoolean accept(IlvGraphic*);
    // Inherited from IlvAttribute
    //virtual void setValue(IlFloat f); //Optional
    //virtual void setValue(const char* formula); // Optional

    virtual IlFloat getValue();

#if defined(_MSC_VER)
    operator IlAny() const { return get()._value.a; }
#else  /* !_MSC_VER */
    operator IlAny()        const { return (IlAny)get(); }
#endif /* !_MSC_VER */
    operator IlInt()        const { return (IlInt)get();        }
    operator IlUInt()       const { return (IlUInt)get();       }
    operator IlFloat()      const { return (IlFloat)get();      }
    operator const char*()   const { return (const char*)get();   }
    operator IlBoolean()    const { return (IlBoolean)get();    }
    operator IlvColor*()     const { return (IlvColor*)get();     }
    operator IlvPattern*()   const { return (IlvPattern*)get();   }
    operator IlvLineStyle*() const { return (IlvLineStyle*)get(); }
    operator IlvFillStyle()  const { return (IlvFillStyle)get();  }
    operator IlvDirection()  const { return (IlvDirection)get();  }
    operator IlvBitmap*()    const { return (IlvBitmap*)get();    }
    virtual IlvGraphicAttribute* copy();
};

// --------------------------------------------------------------------------
// Predefined Attributes
// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvXAttribute
: public IlvGraphicAttribute {
public:
    IlvXAttribute(IlvContainer* container,
		  IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvXAttribute(IlvManager* manager,
		  IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    virtual void  apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvYAttribute
: public IlvGraphicAttribute {
public:
    IlvYAttribute(IlvContainer* container,
		  IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvYAttribute(IlvManager* manager,
		  IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvLeftAttribute
: public IlvGraphicAttribute {
public:
    IlvLeftAttribute(IlvContainer* container,
		     IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvLeftAttribute(IlvManager* manager,
		     IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvTopAttribute
: public IlvGraphicAttribute {
public:
    IlvTopAttribute(IlvContainer* container,
		    IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvTopAttribute(IlvManager* manager,
		    IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvRightAttribute
: public IlvGraphicAttribute {
public:
    IlvRightAttribute(IlvContainer* container,
		      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvRightAttribute(IlvManager* manager,
		      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvBottomAttribute
: public IlvGraphicAttribute {
public:
    IlvBottomAttribute(IlvContainer* container,
		       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvBottomAttribute(IlvManager* manager,
		       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvWidthAttribute
: public IlvGraphicAttribute {
public:
    IlvWidthAttribute(IlvContainer* container,
		      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvWidthAttribute(IlvManager* manager,
		      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvHeightAttribute
: public IlvGraphicAttribute {
public:
    IlvHeightAttribute(IlvContainer* container,
		       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvHeightAttribute(IlvManager* manager,
		       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvAngleAttribute
: public IlvGraphicAttribute {
public:
    IlvAngleAttribute(IlvContainer* container,
		      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name),
      _value(0)
    {}
    IlvAngleAttribute(IlvManager* manager,
		      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name),
      _value(0)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
protected:
    IlFloat _value;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvForegroundAttribute
: public IlvGraphicAttribute {
public:
    IlvForegroundAttribute(IlvContainer* container,
			   IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvForegroundAttribute(IlvManager* manager,
			   IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvForegroundRedAttribute
: public IlvGraphicAttribute {
public:
    IlvForegroundRedAttribute(IlvContainer* container,
			      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvForegroundRedAttribute(IlvManager* manager,
			      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvForegroundGreenAttribute
: public IlvGraphicAttribute {
public:
    IlvForegroundGreenAttribute(IlvContainer* container,
				IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvForegroundGreenAttribute(IlvManager* manager,
				IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvForegroundBlueAttribute
: public IlvGraphicAttribute {
public:
    IlvForegroundBlueAttribute(IlvContainer* container,
			       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvForegroundBlueAttribute(IlvManager* manager,
			       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvBackgroundAttribute
: public IlvGraphicAttribute {
public:
    IlvBackgroundAttribute(IlvContainer* container,
			   IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvBackgroundAttribute(IlvManager* manager,
			   IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvBackgroundRedAttribute
: public IlvGraphicAttribute {
public:
    IlvBackgroundRedAttribute(IlvContainer* container,
			      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvBackgroundRedAttribute(IlvManager* manager,
			      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvBackgroundGreenAttribute
: public IlvGraphicAttribute {
public:
    IlvBackgroundGreenAttribute(IlvContainer* container,
				IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvBackgroundGreenAttribute(IlvManager* manager,
				IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvBackgroundBlueAttribute
: public IlvGraphicAttribute {
public:
    IlvBackgroundBlueAttribute(IlvContainer* container,
			       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvBackgroundBlueAttribute(IlvManager* manager,
			       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvLineWidthAttribute
: public IlvGraphicAttribute {
public:
    IlvLineWidthAttribute(IlvContainer* container,
			  IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvLineWidthAttribute(IlvManager* manager,
			  IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvLineStyleAttribute
: public IlvGraphicAttribute {
public:
    IlvLineStyleAttribute(IlvContainer* container,
			  IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvLineStyleAttribute(IlvManager* manager,
			  IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvPatternAttribute
: public IlvGraphicAttribute {
public:
    IlvPatternAttribute(IlvContainer* container,
			IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvPatternAttribute(IlvManager* manager,
			IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvFillStyleAttribute
: public IlvGraphicAttribute {
public:
    IlvFillStyleAttribute(IlvContainer* container,
			  IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvFillStyleAttribute(IlvManager* manager,
			  IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVisibilityAttribute
: public IlvGraphicAttribute {
public:
    IlvVisibilityAttribute(IlvContainer* container,
			   IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvVisibilityAttribute(IlvManager* manager,
			   IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void  apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvInvertAttribute
: public IlvGraphicAttribute {
public:
    IlvInvertAttribute(IlvContainer* container,
		       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name),
      _inverted(IlFalse)
    {}
    IlvInvertAttribute(IlvManager* manager,
		       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name),
      _inverted(IlFalse)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
protected:
    IlBoolean _inverted;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvSymmetryAttribute
: public IlvGraphicAttribute {
public:
    IlvSymmetryAttribute(IlvContainer* container,
			 IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvSymmetryAttribute(IlvManager* manager,
			 IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void  apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvLabelAttribute
: public IlvGraphicAttribute {
public:
    IlvLabelAttribute(IlvContainer* container,
		      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvLabelAttribute(IlvManager* manager,
		      IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    virtual IlBoolean accept(IlvGraphic*);

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvReliefLabelAttribute
: public IlvGraphicAttribute {
public:
    IlvReliefLabelAttribute(IlvContainer* container,
			    IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvReliefLabelAttribute(IlvManager* manager,
			    IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;

    virtual IlBoolean accept(IlvGraphic*);

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvShadowLabelAttribute
: public IlvGraphicAttribute {
public:
    IlvShadowLabelAttribute(IlvContainer* container,
			    IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvShadowLabelAttribute(IlvManager* manager,
			    IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;
    virtual IlBoolean accept(IlvGraphic*);

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvStartAngleAttribute
: public IlvGraphicAttribute {
public:
    IlvStartAngleAttribute(IlvContainer* container,
			   IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvStartAngleAttribute(IlvManager* manager,
			   IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;
    virtual IlBoolean accept(IlvGraphic*);

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvDeltaAngleAttribute
: public IlvGraphicAttribute {
public:
    IlvDeltaAngleAttribute(IlvContainer* container,
			   IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvDeltaAngleAttribute(IlvManager* manager,
			   IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    //set and get value
    virtual void      apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;
    virtual IlBoolean accept(IlvGraphic*);

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvBitmapAttribute
: public IlvGraphicAttribute {
public:
    IlvBitmapAttribute(IlvContainer* container,
		       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(container, object, name)
    {}
    IlvBitmapAttribute(IlvManager* manager,
		       IlvGraphic* object = 0, const char* name = 0)
    : IlvGraphicAttribute(manager, object, name)
    {}
    // ____________________________________________________________
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const;
    virtual IlBoolean accept(IlvGraphic*);

    IlvDeclareAttribute();
};

ILV31VAREXPORTEDFUNCTION(char* const*) 
IlvGetRegisteredAttributeClasses(IlUInt& nAttributeClasses);
ILV31VAREXPORTEDFUNCTION(const char* const*) 
IlvGetValidAttributeClasses(const IlvGraphic*,
			    IlUInt& nAttributeClasses);

ILV31VARMODULEINIT(attribut);
#endif /* __Ilv31_Attribut_H*/
