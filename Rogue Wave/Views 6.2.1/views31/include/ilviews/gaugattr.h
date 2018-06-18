// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/gaugattr.h
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
// Declaration of the IlvGaugeValueAttribute & IlvChartValueAttribute classes
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Gaugattr_H
#define __Ilv31_Gaugattr_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Attribut_H)
#include <ilviews/attribut.h>
#endif
#if !defined(__Ilv_Graphics_Gauge_H)
#include <ilviews/graphics/gauge.h>
#endif
#if !defined(__Ilv31_Chart_H)
#include <ilviews/chart.h>
#endif

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvGaugeValueAttribute
: public IlvGraphicAttribute {
public:
    IlvGaugeValueAttribute(IlvContainer* container,
			   IlvGraphic* obj=0, const char* name = 0)
    : IlvGraphicAttribute(container, obj, name)
    {}
    IlvGaugeValueAttribute(IlvManager* manager,
			   IlvGraphic* obj=0, const char* name = 0)
    : IlvGraphicAttribute(manager, obj, name)
    {}
    // ____________________________________________________________
    virtual void set(const IlvAttributeValue&, IlBoolean redraw = IlTrue);
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const ;
    virtual IlBoolean accept(IlvGraphic*);

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvChartValueAttribute
: public IlvGraphicAttribute {
public:
    IlvChartValueAttribute(IlvContainer* container,
			   IlvGraphic* obj = 0, const char* name = 0,
			   IlUInt which = 0)
    : IlvGraphicAttribute(container, obj, name),
      _index(which)
    {}
    IlvChartValueAttribute(IlvManager* manager,
			   IlvGraphic* obj = 0, const char* name = 0,
			   IlUInt which = 0)
	: IlvGraphicAttribute(manager, obj, name),
      _index(which)
    {}
    // ____________________________________________________________
    IlUInt getIndex() const { return _index; }
    void setIndex(IlUInt i) { _index = i;    }

    virtual void apply(const IlvAttributeValue&)=0;
    virtual void set(const IlvAttributeValue&, IlBoolean redraw = IlTrue);
    virtual const IlvAttributeValue& get() const =0;
    virtual IlBoolean accept(IlvGraphic*);
    virtual void read(IL_STDPREF istream&);
    virtual void write(IL_STDPREF ostream&) const;

    static IlvGraphicAttributeClassInfo*  _classInfo;
    virtual IlvGraphicAttributeClassInfo* getClassInfo() const;
    virtual IlvGraphicAttribute* copy();
protected:
    IlUInt	_index;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvChartYValueAttribute
: public IlvChartValueAttribute {
public:
    IlvChartYValueAttribute(IlvContainer* container,
			    IlvGraphic* obj = 0, const char* name = 0,
			    IlUInt which = 0)
	: IlvChartValueAttribute(container, obj, name, which)
	{}
    IlvChartYValueAttribute(IlvManager* manager,
			    IlvGraphic* obj = 0, const char* name = 0,
			    IlUInt which = 0)
	: IlvChartValueAttribute(manager, obj, name, which)
    {}
    // ____________________________________________________________
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get()  const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvChartXValueAttribute
: public IlvChartValueAttribute {
public:
    IlvChartXValueAttribute(IlvContainer* container,
			    IlvGraphic* obj = 0, const char* name = 0,
			    IlUInt which = 0)
    : IlvChartValueAttribute(container, obj, name, which)
    {}
    IlvChartXValueAttribute(IlvManager* manager,
			    IlvGraphic* obj = 0, const char* name = 0,
			    IlUInt which = 0)
    : IlvChartValueAttribute(manager, obj, name, which)
    {}
    // ____________________________________________________________
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get()  const;

    IlvDeclareAttribute();
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvScrollChartValueAttribute
: public IlvGraphicAttribute {
public:
    IlvScrollChartValueAttribute(IlvContainer* container,
				 IlvGraphic* obj=0, const char* name = 0)
    : IlvGraphicAttribute(container, obj, name)
    {}
    IlvScrollChartValueAttribute(IlvManager* manager,
				 IlvGraphic* obj=0, const char* name = 0)
    : IlvGraphicAttribute(manager, obj, name)
    {}
    // ____________________________________________________________
    virtual void set(const IlvAttributeValue&, IlBoolean redraw = IlTrue);
    virtual void apply(const IlvAttributeValue&);
    virtual const IlvAttributeValue& get() const ;
    virtual IlBoolean accept(IlvGraphic*);
    IlvDeclareAttribute();
};

ILV31VARMODULEINIT(gaugattr);
#endif /* !__Ilv31_GaugeAttr_H */
