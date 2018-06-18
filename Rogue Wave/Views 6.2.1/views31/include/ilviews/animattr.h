// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/animattr.h
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
// Declaration of the Ilv(Hue Saturation Value)ForegroundValueAttribute
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Animattr_H
#define __Ilv31_Animattr_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Attribut_H)
#include <ilviews/attribut.h>
#endif

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvHueForegroundValueAttribute
: public IlvGraphicAttribute {
public:
    IlvHueForegroundValueAttribute(IlvContainer* container,
				   IlvGraphic* obj = 0,
				   const char* name = 0)
    : IlvGraphicAttribute(container, obj, name) {}
    IlvHueForegroundValueAttribute(IlvManager* manager,
				   IlvGraphic* obj = 0,
				   const char* name = 0)
    : IlvGraphicAttribute(manager, obj, name) {}
    // ____________________________________________________________
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const ;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvSaturationForegroundValueAttribute
: public IlvGraphicAttribute {
public:
    IlvSaturationForegroundValueAttribute(IlvContainer* container,
					  IlvGraphic* obj=0,
					  const char* name = 0)
    : IlvGraphicAttribute(container, obj, name) {}
    IlvSaturationForegroundValueAttribute(IlvManager* manager,
					  IlvGraphic* obj=0,
					  const char* name = 0)
    : IlvGraphicAttribute(manager, obj, name) {}
    // ____________________________________________________________
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const ;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvValueForegroundValueAttribute
: public IlvGraphicAttribute {
public:
    IlvValueForegroundValueAttribute(IlvContainer* container,
				     IlvGraphic* obj=0, const char* name = 0)
    : IlvGraphicAttribute(container, obj, name) {}
    IlvValueForegroundValueAttribute(IlvManager* manager,
				     IlvGraphic* obj=0, const char* name = 0)
    : IlvGraphicAttribute(manager, obj, name) {}
    // ____________________________________________________________
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const ;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvAnimatedColorAttribute
: public IlvGraphicAttribute {
public:
    IlvAnimatedColorAttribute(IlvContainer* container,
			      IlvGraphic* obj = 0, const char* name = 0);
    IlvAnimatedColorAttribute(IlvManager* manager,
			      IlvGraphic* obj = 0, const char* name = 0);
    virtual ~IlvAnimatedColorAttribute();
    // ____________________________________________________________
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const ;
    void setValues(IlUInt count, IlFloat* values,
		   IlvIntensity* r, IlvIntensity* g, IlvIntensity* b);
    void setValues(IlUInt count, IlFloat* values,
		   IlFloat* h, IlFloat* s, IlFloat* v);
    IlFloat* getValues(IlUInt& count) const;

    IlvDeclareAttribute();
protected:
    IlUInt    _count;
    IlFloat   _value;
    IlFloat*  _values;
    IlBoolean _hsvmodel;
    union {
	struct {
	    IlvIntensity* r;
	    IlvIntensity* g;
	    IlvIntensity* b;
	} rgb;
	struct {
	    IlFloat* h;
	    IlFloat* s;
	    IlFloat* v;
	} hsv;
    } _colors;
    void freeArrays();
};

ILV31VARMODULEINIT(animattr);
#endif /* __Ilv31_Animattr_H */
